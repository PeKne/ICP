#include "port.h"

#include "connections.h"

#include <QGraphicsScene>

#include <QFontMetrics>

#include <QPen>

Port::Port(QGraphicsItem *parent):
    QGraphicsPathItem(parent)
{
    label = new QGraphicsTextItem(this);

    my_radius = 5;
    margin = 2;


    QPainterPath p;
    p.addEllipse(-my_radius, -my_radius, 2*my_radius, 2*my_radius);
    setPath(p);

    setBrush(Qt::magenta);

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    my_port_flag = 0;
}

Port::~Port()
{
    foreach(Connection *conn, my_connections)
    {
        delete conn;
    }
}

void Port::set_block(Block *b)
{
    my_block = b;
}

void Port::set_name(const QString &n)
{
    this->name = n;

    label->setPlainText(n);
}

void Port::set_is_output(bool o)
{
    output = o;

    QFontMetrics fm(scene()->font());
    //QRect r = fm.boundingRect(name);

    if (output){
        label->setPos(- my_radius - margin - label->boundingRect().width(), -label->boundingRect().height()/2);
    }
    else{
        label->setPos(margin + my_radius, -label->boundingRect().height()/2);
    }
}

int Port::radius()
{
    return my_radius;
}

bool Port::get_typed(){
    return typed;
}

Block* Port::get_block(){
    return my_block;
}

bool Port::is_output()
{
    return output;
}

QVector<Connection*>& Port::connections()
{
    return my_connections;
}

void Port::set_flag(int f)
{
    my_port_flag = f;

    if (my_port_flag & TypePort)
    {
        this->typed = true;
        QFont font(scene()->font());
        font.setBold(true);
        label->setFont(font);
        setPath(QPainterPath());
    } else if (my_port_flag & NamePort)
    {
        this->typed = true;
        QFont font(scene()->font());
        font.setBold(true);
        font.setUnderline(true);
        label->setFont(font);
        setPath(QPainterPath());
    }
}

Block* Port::block() const
{
    return my_block;
}

quint64 Port::ptr()
{
    return my_ptr;
}

void Port::set_ptr(quint64 p)
{
    my_ptr = p;
}

bool Port::is_connected(Port *other)
{
    foreach(Connection *conn, my_connections)
        if (conn->port1() == other || conn->port2() == other)
            return true;

    return false;
}

QVariant Port::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged)
    {
        foreach(Connection *conn, my_connections)
        {
            conn->update_positions_ports();
            conn->update_path_conn();
        }
    }
    return value;
}
