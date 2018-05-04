/*!
 * School project for subject (The C++ Programming Language).
 * This application is graphical editor of mathematical schemes.
 * For more information check readme.txt
 *
 * @author Petr Knetl
 * @author Marek Kalabza
 */


#include "connections.h"
#include "port.h"

#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
/*!
 * Constructor of graphical connection.
 * There are set information such color, information of attached ports are set to undefined.
 *
 * @param parent Superior graphical item of block
 */
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

/*!
 * Destructor of connection. Everything is freed from memory.
 */
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

/*!
 * Sets starting coordinates of connection.
 * @param p position
 */
void Connection::set_position1(const QPointF &p)
{
    position1 = p;
}

/*!
 * Sets end coordinates of connection.
 * @param p position
 */
void Connection::set_position2(const QPointF &p)
{
    position2 = p;
}

/*!
 * Save pointer of input port into connection.
 * @param p pointer of port
 */
void Connection::set_port1(Port *p)
{
    my_port1 = p;

    my_port1->connections().append(this);
}

/*!
 * Save pointer of output port into connection.
 * @param p pointer of port
 */
void Connection::set_port2(Port *p)
{
    my_port2 = p;

    my_port2->connections().append(this);
}

/*!
 * Refresh graphical position of starting and end point of connection depending on position of connected ports.
 */
void Connection::update_positions_ports()
{
    // Na zaklade propojenych portu se nastavi positions
    position1 = my_port1->scenePos();
    position2 = my_port2->scenePos();
}

/*!
 * Updates path to connection.
 */
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

/*!
 * @return input port of connection.
 */
Port* Connection::port1() const
{
    return my_port1;
}
/*!
 * @return output port of connection.
 */
Port* Connection::port2() const
{
    return my_port2;
}
/*!
 * Copy instance of connection into datastream. Whole datastream is save into file on user request.
 *
 * @param DS data-stream where data of connection will be copied
 */
void Connection::save(QDataStream &DS)
{
    DS << (quint64) my_port1;
    DS << (quint64) my_port2;
}

/*!
 * Creates new instance of connection from datastream. Datastream is loaded from file on user request.
 *
 * @param DS data-stream from which data of connection will be copied
 */
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
