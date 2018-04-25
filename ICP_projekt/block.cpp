#include "block.h"

#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QStyleOptionGraphicsItem>
//#include "port.h"

Block::Block(QGraphicsItem *parent) : QGraphicsPathItem(parent){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    QPainterPath path;
    path.addRect(-50, -15, 100, 30);
    setPath(path);

    //setPen(QPen(Qt::darkGreen));
    setBrush(Qt::red);

    width = 20;
    height = 5;

}

Port* Block::add_port(const QString &name, bool output, int flags, int ptr){
    /*
    Port *port = new Port(this);
    port->setName(name);
    port->setIsOutput(isOutput);
    port->setNEBlock(this);
    port->setPortFlags(flags);
    port->setPtr(ptr);

    QFontMetrics fm(scene()->font());
    int w = fm.width(name);
    int h = fm.height();
    // port->setPos(0, height + h/2);
    if (w > width - horzMargin)
        width = w + horzMargin;
    height += h;

    QPainterPath p;
    p.addRoundedRect(-width/2, -height/2, width, height, 5, 5);
    setPath(p);

    int y = -height / 2 + vertMargin + port->radius();
    foreach(QGraphicsItem *port_, childItems()) {
        if (port_->type() != QNEPort::Type)
            continue;

        QNEPort *port = (QNEPort*) port_;
        if (port->isOutput())
            port->setPos(width/2 + port->radius(), y);
        else
            port->setPos(-width/2 - port->radius(), y);
        y += h;
    }

    return port;
    */
}

void Block::add_input_port(const QString &name){
    add_port(name, false);
}

void Block::add_output_port(const QString &name){
    add_port(name, true);
}

void Block::add_input_ports(const QStringList &names){
    foreach(QString n, names)
        add_input_port(n);
}

void Block::add_output_ports(const QStringList &names){
    foreach(QString n, names)
        add_output_port(n);
}

void Block::save(QDataStream &DS){
    /*
    DS << pos();

    int count(0);

    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() != Port::Type)
            continue;

        count++;
    }

    DS << count;

    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() != Port::Type)
            continue;

        QNEPort *port = (QNEPort*) port_;
        DS << (quint64) port;
        DS << port->portName();
        DS << port->isOutput();
        DS << port->portFlags();
    }
    */
}

void Block::load(QDataStream &DS, QMap<quint64, Port*> &portMap){
    /*
    QPointF p;
    ds >> p;
    setPos(p);
    int count;
    ds >> count;
    for (int i = 0; i < count; i++)
    {
        QString name;
        bool output;
        int flags;
        quint64 ptr;

        ds >> ptr;
        ds >> name;
        ds >> output;
        ds >> flags;
        portMap[ptr] = addPort(name, output, flags, ptr);
    }
    */
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    /*
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (isSelected()) {
        painter->setPen(QPen(Qt::darkYellow));
        painter->setBrush(Qt::yellow);
    } else {
        painter->setPen(QPen(Qt::darkGreen));
        painter->setBrush(Qt::green);
    }

    painter->drawPath(path());
    */
}

Block* Block::clone(){
    Block *b = new Block(0);
    this->scene()->addItem(b);
    /*
    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() == QNEPort::Type)
        {
            QNEPort *port = (QNEPort*) port_;
            b->addPort(port->portName(), port->isOutput(), port->portFlags(), port->ptr());
        }
    }
    */
    return b;
}

QVector<Port*> Block::ports(){
    /*
    QVector<QNEPort*> res;
    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() == QNEPort::Type)
            res.append((QNEPort*) port_);
    }
    return res;
    */
}

QVariant Block::itemChange(GraphicsItemChange change, const QVariant &value){

    Q_UNUSED(change);

    return value;
}
