#ifndef PORT_H
#define PORT_H

#include <QGraphicsPathItem>

class Connection;
class Block;
class Port : public QGraphicsPathItem
{
public:
    Port(QGraphicsItem *parent = 0);
    ~Port();

    enum { Type = QGraphicsItem::UserType + 1 };
    enum { NamePort = 1, TypePort = 2 };
    int type() const { return Type; }

    void set_block(Block*);
    void set_name(const QString &n);
    void set_is_output(bool o);
    void set_flag(int);
    void set_ptr(quint64);

    bool is_output();
    bool is_connected(Port*);
    int radius();
    bool get_typed();
    Block* get_block();

    const QString& port_name() const { return name; }
    int port_flags() const { return my_port_flag; }

    Block* block() const;
    QVector<Connection*>& connections();
    quint64 ptr();

    QVector<Connection*> my_connections;
    QGraphicsTextItem *label;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    Block *my_block;
    QString name;
    quint64 my_ptr;

    int my_radius;
    int margin;
    int my_port_flag;
    bool output;
    bool typed = false;
};
#endif
