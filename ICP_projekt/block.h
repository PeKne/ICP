#ifndef BLOCK_H
#define BLOCK_H
#include <QGraphicsPathItem>

class Port;

class Block : public QGraphicsPathItem{
public:
    Block(QGraphicsItem *parent = 0);
    int type() const{
        return Type;
    }

    Port* add_port(const QString &name, bool output, int flags = 0, int ptr = 0);
    Block* clone();
    QVector<Port*> ports();

    void add_input_port(const QString &name);
    void add_output_port(const QString &name);
    void add_input_ports(const QStringList &names);
    void add_output_ports(const QStringList &names);

    void save(QDataStream&);
    void load(QDataStream&, QMap<quint64, Port*> &portMap);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    int width;
    int height;
    int horizont;
    int vertical;
};
#endif // BLOCK_H
