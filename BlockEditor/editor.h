#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

class QGraphicsScene;
class Connection;
class Block;
class QGraphicsItem;
class QPointF;
class Editor : public QObject
{
    Q_OBJECT
public:
    explicit Editor(QObject *parent = 0);

    void install(QGraphicsScene *scene);

    bool eventFilter(QObject *, QEvent *);

    void save(QDataStream &DS);
    void load(QDataStream &DS);
    void clear();

private:
    QGraphicsItem *itemAt(const QPointF&);

public:
    Connection *conn;
    QGraphicsScene *scene;
};
#endif
