#include "block.h"

#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPen>
#include <QPainter>
#include <iostream>

#include "math.h"
#include "connections.h"
#include "port.h"

Block::Block(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    QPainterPath path;

    path.addRoundedRect(-50, -15, 100, 30, 5, 5);
    setPath(path);

    setBrush(Qt::lightGray);

    top_bottom_margin = 50;
    width = top_bottom_margin;

    left_right_margin = 5;
    height = left_right_margin;
}

Port* Block::add_port(const QString &name, bool is_output, int flags, int ptr)
{
    Port *port = new Port(this);

    // Osetreni label-name pozici pri loadu
    if(flags == Port::TypePort){
        port->set_name("");
    }
    else{
        port->set_name(name);
    }

    port->set_is_output(is_output);
    port->set_block(this);
    port->set_flag(flags);
    port->set_ptr(ptr);

    // Zjisteni font parametru
    QFontMetrics fm(scene()->font());

    int w = fm.width(name);

    int h = fm.height();

    // Rozsireni blocku na zaklade textu
    if (w > width - top_bottom_margin){
        width = w + top_bottom_margin;
    }

    height += h;

    QPainterPath path;

    path.addRoundedRect(-width/2, -height/2, width, height, 7, 7);

    setPath(path);

    int y = -height/2 + port->radius() + left_right_margin ;

    // Urceni positon pro porty
    foreach(QGraphicsItem *port_, childItems()) {
        if (port_->type() != Port::Type){
            continue;
        }

        Port *port = (Port*) port_;
        if (port->is_output() && port->port_flags() == Port::TypePort)
            port->setPos(width/2 - width + 40, y);
        else if (port->is_output() && port->port_flags() != Port::TypePort)
            port->setPos(width/2 + port->radius(), y);
        else if (!(port->is_output()) && port->port_flags() == Port::TypePort)
            port->setPos(-width/2, y);
        else if (!(port->is_output()) && port->port_flags() != Port::TypePort)
            port->setPos(-width/2 - port->radius(), y);
        y += h;

    }

    if(flags == Port::TypePort)
        port->set_name(name);

    return port;
}

void Block::add_in_port(const QString &name)
{
    add_port(name, false);
}

void Block::add_out_port(const QString &name)
{
    add_port(name, true);
}

void Block::add_in_ports(const QStringList &names)
{
    foreach(QString n, names)
        add_in_port(n);
}

void Block::add_out_ports(const QStringList &names)
{
    foreach(QString n, names)
        add_out_port(n);
}

void Block::save(QDataStream &DS)
{
    // Postupne ukladani informaci o bloku do DS
    DS << pos();

    int count(0);

    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() != Port::Type)
            continue;

        count++;
    }

    DS << count;

    //
    DS << this->value;
    DS << this->input1;
    DS << this->input2;
    DS << this->input1def;
    DS << this->input2def;
    DS << this->def;
    DS << this->oper;
    DS << this->calculated;
    //

    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() != Port::Type)
            continue;

        Port *port = (Port*) port_;
        DS << (quint64) port;
        DS << port->port_name();
        DS << port->is_output();
        DS << port->port_flags();

    }
}

void Block::load(QDataStream &DS, QMap<quint64, Port*> &port_map)
{
    // Postupne brani informaci z DS

    QPointF p;
    DS >> p;
    setPos(p);
    int count;
    DS >> count;

    //
    DS >> this->value;
    DS >> this->input1;
    DS >> this->input2;
    DS >> this->input1def;
    DS >> this->input2def;
    DS >> this->def;
    DS >> this->oper;
    DS >> this->calculated;
    //

    for (int i = 0; i < count; i++)
    {
        QString name;
        bool output;
        int flags;
        quint64 ptr;

        DS >> ptr;
        DS >> name;
        DS >> output;
        DS >> flags;

        port_map[ptr] = add_port(name, output, flags, ptr);
    }
}

#include <QStyleOptionGraphicsItem>

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // Barevna zmena bloku
    if (isSelected()) {
        painter->setBrush(Qt::green);
    } else {
        painter->setBrush(Qt::lightGray);
    }

    painter->drawPath(path());
}

QVector<Port*> Block::ports()
{
    QVector<Port*> vector;

    foreach(QGraphicsItem *port, childItems())
    {
        if (port->type() == Port::Type)
            vector.append((Port*) port);
    }
    return vector;
}

QVariant Block::itemChange(GraphicsItemChange change, const QVariant &value)
{
    Q_UNUSED(change);
    return value;
}
void Block::fetch_inputs(){
    // Urceni hodnot propojenych bloku
    QVector<Port*> arrayports = this->ports();
    bool first = false;

    // Nadefinuje porty, ktere jsou v bloku jez jsou definovane
    foreach(Port *thisport, arrayports){
        if(!(thisport->is_output()) && !(thisport->get_typed()) && !(thisport->my_connections.empty())){
            if(first == false ){
                first = true;
                if(thisport->my_connections[0]->port1()->block()->def == true && thisport->my_connections[0]->port1()->block()->calculated == false){
                    this->input1 = thisport->my_connections[0]->port1()->block()->value;
                    thisport->my_connections[0]->setToolTip(QString::number(this->input1,'f',3)); // set value for hover over connection
                    this->input1def = true;
                }else{
                    break;
                }

            }else{
                if(thisport->my_connections[0]->port1()->block()->def == true && thisport->my_connections[0]->port1()->block()->calculated == false){
                    this->input2 = thisport->my_connections[0]->port1()->block()->value;
                    thisport->my_connections[0]->setToolTip(QString::number(this->input2,'f',3)); // set value for hover over connection
                    this->input2def = true;
                }
                break;
            }
        }
    }
}
void Block::calculate(){
    //Vypocet propojenych bloku
    if(!(this->oper == 5)){
        this->fetch_inputs();
     }

    // Vypocet jednotlivych operaci
    switch(this->oper){

        // +
        case 1:
            if(this->input1def && this->input2def){
                this->value = this->input1 + this->input2;
                this->def = true;
                this->calculated = true;

            }break;

        // -
        case 2:
            if(this->input1def && this->input2def){
                this->value = this->input1 - this->input2;
                this->def = true;
                this->calculated = true;

            }break;

        // *
        case 3:
            if(this->input1def && this->input2def){
                this->value = this->input1 * this->input2;
                this->def = true;
                this->calculated = true;

            }break;

        // /
        case 4:
            if(this->input1def && this->input2def){
                this->value = this->input1 / this->input2;
                this->def = true;
                this->calculated = true;

            }break;

        // INPUT
        case 5:
            if(this->input1def){
                this->value = this->input1;
                this->def = true;
                this->calculated = true;

            }break;

        // OUTPUT
        case 6:
            if(this->input1def){
                this->value = this->input1;
                this->def = true;
                this->calculated = true;

            }break;

        // ^
        case 7:
            if(this->input1def && this->input2def){
                this->value = pow(this->input1,this->input2);
                this->def = true;
                this->calculated = true;

            }break;


        default:
            break;

    }
}
