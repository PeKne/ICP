/*!
 * @author Petr Knetl
 * @author Marek Kalabza
 */

#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <QGraphicsPathItem>

class Port;
/*!
 * This class contains information about graphical connection and backend attributes of it.
 */
class Connection : public QGraphicsPathItem
{
public:
    Connection(QGraphicsItem *parent = 0);
    ~Connection();

    enum { Type = QGraphicsItem::UserType + 2 };
    int type() const { return Type; }

    void set_name(const QString &n);
    void set_position1(const QPointF &p);
    void set_position2(const QPointF &p);
    void set_port1(Port *p);
    void set_port2(Port *p);
    Port* port1() const;
    Port* port2() const;

    void update_positions_ports();
    void update_path_conn();

    void save(QDataStream&);
    void load(QDataStream&, const QMap<quint64, Port*> &port_map);

private:
    QPointF position1;
    QPointF position2;
    Port *my_port1;
    Port *my_port2;
};
#endif
