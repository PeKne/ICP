#include "connections.h"
#include "port.h"

#include <QGraphicsScene>
#include <QBrush>
#include <QPen>

Connection::Connection(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{

    // Barva propoje
    setPen(QPen(Qt::red, 3));
    setBrush(Qt::NoBrush);
    setZValue(-1);

    my_port1 = 0;
    my_port2 = 0;

    // Nastaveni hodnoty propoje
    this->setToolTip("undefined");
}

Connection::~Connection()
{
    // Ostraneni portu propoje
    if (my_port1)
    {
        my_port1->connections().remove(my_port1->connections().indexOf(this));
    }
    if (my_port2)
    {
        my_port2->connections().remove(my_port2->connections().indexOf(this));
    }
}

void Connection::set_position1(const QPointF &p)
{
    position1 = p;
}

void Connection::set_position2(const QPointF &p)
{
    position2 = p;
}

void Connection::set_port1(Port *p)
{
    my_port1 = p;

    my_port1->connections().append(this);
}

void Connection::set_port2(Port *p)
{
    my_port2 = p;

    my_port2->connections().append(this);
}

void Connection::update_positions_ports()
{
    // Na zaklade propojenych portu se nastavi positions
    position1 = my_port1->scenePos();
    position2 = my_port2->scenePos();
}

void Connection::update_path_conn()
{
    QPainterPath path;

    path.moveTo(position1);

    QPointF c1(position1.x(), position1.y());
    QPointF c2(position1.x(), position1.y());

    // Propojeni dvou bloku
    path.cubicTo(c1, c2, position2);

    setPath(path);
}

Port* Connection::port1() const
{
    return my_port1;
}

Port* Connection::port2() const
{
    return my_port2;
}

void Connection::save(QDataStream &DS)
{
    DS << (quint64) my_port1;
    DS << (quint64) my_port2;
}

void Connection::load(QDataStream &DS, const QMap<quint64, Port*> &port_map)
{
    quint64 ptr1;
    quint64 ptr2;


    DS >> ptr1;
    DS >> ptr2;

    set_port1(port_map[ptr1]);
    set_port2(port_map[ptr2]);

    update_positions_ports();
    update_path_conn();
}
