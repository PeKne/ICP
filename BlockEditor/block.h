#ifndef BLOCK_H
#define BLOCK_H
#include <QLineEdit>
#include <QGraphicsPathItem>

class Port;
class Block : public QGraphicsPathItem
{
public:
    enum { Type = QGraphicsItem::UserType + 3 };
    int type() const { return Type; }
    Block(QGraphicsItem *parent = 0);

    Port* add_port(const QString &name, bool is_output, int flags = 0, int ptr = 0);
    void add_in_port(const QString &name);
    void add_out_port(const QString &name);

    void add_in_ports(const QStringList &names);
    void add_out_ports(const QStringList &names);

    void set_oper(int oper){ this->oper = oper;}
    void set_value(float val){ this->value = val;}
    void set_def(bool definition){ this->def = definition;}
    void set_calculated(bool calc){ this->calculated = calc;}
    void set_input1(float f){ this->input1 = f;}
    void set_input1def(bool def){ this->input1def = def;}
    void set_input2(float f){ this->input2 = f;}
    void set_input2def(bool def){ this->input2def = def;}

    float get_value(){ return this->value;}
    int get_oper(){ return this->oper;}
    bool get_def(){ return this->def;}
    bool get_calculated(){ return this->calculated;}


    QVector<Port*> ports();

    void save(QDataStream&);
    void load(QDataStream&, QMap<quint64, Port*> &port_map);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void calculate();
    void fetch_inputs();


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    float value;
    float input1;
    float input2;
    int top_bottom_margin;
    int left_right_margin;
    int width;
    int height;
    bool input1def = false;
    bool input2def = false;
    bool def = false;
    int oper;
    bool calculated = false;
};
#endif
