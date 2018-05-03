/*!
 * School project for subject (The C++ Programming Language).
 * This application is graphical editor of mathematical schemes.
 * For more information chech readme.txt
 *
 * @author Petr Knetl
 * @author Marek Kalabza
 */

#include "port.h"

#include "connections.h"

#include <QGraphicsScene>

#include <QFontMetrics>

#include <QPen>

/*!
 * constructor of port.
 *
 * @param parent superior graphical item of constructed block.
 */
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

/*!
 * destructor of port. Port is deleted.
 */
Port::~Port()
{
    foreach(Connection *conn, my_connections)
    {
        delete conn;
    }
}

/*!
 * Attach port to specific block.
 *
 * @param b block where is port located
 */
void Port::set_block(Block *b)
{
    my_block = b;
}

/*!
 * Sets name of port.
 * @param n name of port
 */
void Port::set_name(const QString &n)
{
    this->name = n;

    label->setPlainText(n);
}

/*!
 * Specify if port is output or input of block.
 * @param o true if output, false if input
 */
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

/*!
 *
 * @return radius of graphical object of port
 */
int Port::radius()
{
    return my_radius;
}

/*!
 *
 * @return information if port has some special type
 */
bool Port::get_typed(){
    return typed;
}

/*!
 *
 * @return block where is port attached
 */
Block* Port::get_block(){
    return my_block;
}

/*!
 *
 * @return true if port is output, false if input
 */
bool Port::is_output()
{
    return output;
}

/*!
 *
 * @return vector of all connections attached to port
 */
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

/*!
 *
 * @return block where is port attached
 */
Block* Port::block() const
{
    return my_block;
}

/*!
 *
 * @return memory pointer of port
 */
quint64 Port::ptr()
{
    return my_ptr;
}

/*!
 * sets pointer to memory of port
 * @param p pointer
 */
void Port::set_ptr(quint64 p)
{
    my_ptr = p;
}

/*!
 * Return information if current port is connected to 'other'.
 * @param other seccond port
 * @return true if connected, false otherwise.
 */
bool Port::is_connected(Port *other)
{
    foreach(Connection *conn, my_connections)
        if (conn->port1() == other || conn->port2() == other)
            return true;

    return false;
}

/*!
 *
 * @param change
 * @param value
 * @return
 */
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
