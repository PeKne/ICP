/*!
 * School project for subject (The C++ Programming Language).
 * This application is graphical editor of mathematical schemes.
 * For more information check readme.txt
 *
 * @author Petr Knetl
 * @author Marek Kalabza
 */

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>

#include "editor.h"
#include "block.h"

#include "port.h"
#include "connections.h"

/*!
 * Constructor of editor.
 * @param parent superior graphical item of new instance of editor.
 */
Editor::Editor(QObject *parent) :
    QObject(parent)
{
    conn = 0;
}

/*!
 * Setup of event filters of this editor for specific scene.
 * @param s scene where event filters will be set up
 */
void Editor::install(QGraphicsScene *s)
{
    // Nastaveni event filtru pro danou scenu
    s->installEventFilter(this);
    scene = s;
}

/*!
 * Finds graphical object on position of mouse cursor.
 *
 * @param pos position of mouse cursor
 * @return graphical item on success, 0 if method fails
 */
QGraphicsItem* Editor::itemAt(const QPointF &pos)
{
    QList<QGraphicsItem*> items = scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

    // Urceni typu bloku po najeti mysi
    foreach(QGraphicsItem *item, items)
        if (item->type() > QGraphicsItem::UserType)
            return item;

    return 0;
}

/*!
 * Handles Specific events evoked by user actions such mouse click, mouse release etc.
 * Every event produce different action which change some attributes of whole scheme.
 * For more information of specific events read source code.
 *
 * @param o object which catch event
 * @param e specific event
 * @return
 */
bool Editor::eventFilter(QObject *o, QEvent *e)
{
    QGraphicsSceneMouseEvent *m_event = (QGraphicsSceneMouseEvent*) e;

    switch ((int) e->type()){
    case QEvent::GraphicsSceneMousePress:
    {

        switch ((int) m_event->button()){
        case Qt::LeftButton:
        {

            QGraphicsItem *this_item = itemAt(m_event->scenePos());
            if (this_item && this_item->type() == Port::Type)
            {
                conn = new Connection(0);
                scene->addItem(conn);

                conn->set_port1((Port*) this_item);
                conn->set_position1(this_item->scenePos());
                conn->set_position2(m_event->scenePos());

                conn->update_path_conn();

                return true;
            }break;
        }
        case Qt::RightButton:
        {
            // Vymazani bloku / propoje

            QGraphicsItem *this_item = itemAt(m_event->scenePos());
            if (this_item && (this_item->type() == Connection::Type))
            {
                delete this_item;
            }
            if ((this_item->type() == Block::Type) && this_item)
            {
                Block* b = (Block*) this_item;

                foreach (QGraphicsItem *current, scene->items())
                {
                    if (current && (current->type() == Connection::Type))
                    {
                        Connection* conn = (Connection*) current;
                        foreach(QGraphicsItem *port_, b->childItems())
                        {
                            if(conn->port1() == port_ || conn->port2() == port_)
                            {

                                delete current;
                            }
                        }

                    }
                }

                delete this_item;

            }
            break;
        }
        }
    }

    case QEvent::GraphicsSceneMouseRelease:
    {
        if (conn && m_event->button() == Qt::LeftButton)
        {
            QGraphicsItem *this_item = itemAt(m_event->scenePos());
            if (this_item && this_item->type() == Port::Type)
            {
                Port *port1 = conn->port1();
                Port *port2 = (Port*) this_item;

                bool portEmpty = true;

                // Kontrola zda propojujici input porty jsou prazdne
                foreach(QGraphicsItem *item, scene->items())
                {
                    if(item->type() != Port::Type)
                        continue;

                    Port* this_port = (Port*) item;
                    if(!port2->is_output())
                    {
                        if(port2->is_connected(this_port))
                            portEmpty = false;
                    }else{
                        if(port1->is_connected(this_port))
                            portEmpty = false;
                    }
                }

                // Zaktulizovani propoju
                if (portEmpty && port1->block() != port2->block() && port1->is_output() != port2->is_output() && !port1->is_connected(port2))
                {
                    conn->set_position2(port2->scenePos());
                    conn->set_port2(port2);
                    conn->update_path_conn();
                    conn = 0;
                    return true;
                }
            }

            delete conn;
            conn = 0;
            return true;
        }
        break;
    }

    case QEvent::GraphicsSceneMouseMove:
    {
        // Aktualizace propoje na scene pri pohybu mysi
        if (conn)
        {
            conn->set_position2(m_event->scenePos());

            conn->update_path_conn();

            return true;
        }
        break;
    }
    }
    return QObject::eventFilter(o, e);
}

/*!
 * Memory of whole scheme is copied into datastream. Data stream  is saved into file on user request.
 *
 * @param DS datastream where will be copied whole scheme
 */
void Editor::save(QDataStream &DS)
{
    // Ulozeni kazdeho bloku na scene
    foreach(QGraphicsItem *this_item, scene->items()){
        if (this_item->type() == Block::Type){

            DS << this_item->type();
            ((Block*) this_item)->save(DS);
        }
    }

    // Ulozeni kazdeho propoje na scene
    foreach(QGraphicsItem *this_item, scene->items()){
        if (this_item->type() == Connection::Type){

            DS << this_item->type();
            ((Connection*) this_item)->save(DS);
        }
    }
}

/*!
 * From datastream is loaded whole scheme is new instances of classes forming scheme.
 * Data stream  is loaded from file on user request.
 *
 * @param DS datastream from which will be copied whole scheme
 */
void Editor::load(QDataStream &DS)
{
    // Vymazani sceny
    scene->clear();

    QMap<quint64, Port*> port_map;

    // Nacteni vsech radku
    while (!DS.atEnd())
    {
        int type;
        DS >> type;

        // Nacteni bloku
        if (type == Block::Type)
        {
            Block *b = new Block(0);
            scene->addItem(b);
            b->load(DS, port_map);

        }
        // Nacteni propoje
        else if (type == Connection::Type)
        {
            Connection *conn = new Connection(0);
            scene->addItem(conn);
            conn->load(DS, port_map);

            if (conn->port1()->block()->get_def() == true)
            {
                //if previous value defined, set tooltip over connection
                conn->setToolTip(QString::number(conn->port1()->block()->get_value(),'f',3));
            }
        }
    }
}

/*!
 * Deletes all objects (blocks, ports, connections) of scheme.
 */
void Editor::clear()
{
    // Vymazani sceny
    scene->clear();
}
