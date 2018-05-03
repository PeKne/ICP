#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "qnodeseditor.h"
#include "qneblock.h"
#include "qneport.h"
#include "qneconnection.h"


QNodesEditor::QNodesEditor(QObject *parent) :
    QObject(parent)
{
	conn = 0;
}

void QNodesEditor::install(QGraphicsScene *s)
{
	s->installEventFilter(this);
	scene = s;
}

QGraphicsItem* QNodesEditor::itemAt(const QPointF &pos)
{
	QList<QGraphicsItem*> items = scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

	foreach(QGraphicsItem *item, items)
		if (item->type() > QGraphicsItem::UserType)
			return item;

	return 0;
}

bool QNodesEditor::eventFilter(QObject *o, QEvent *e)
{
	QGraphicsSceneMouseEvent *me = (QGraphicsSceneMouseEvent*) e;

	switch ((int) e->type())
	{
	case QEvent::GraphicsSceneMousePress:
	{

		switch ((int) me->button())
		{
		case Qt::LeftButton:
		{
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && item->type() == QNEPort::Type)
			{
                conn = new QNEConnection(0);
                scene->addItem(conn);
				conn->setPort1((QNEPort*) item);
				conn->setPos1(item->scenePos());
				conn->setPos2(me->scenePos());
				conn->updatePath();

				return true;
            }
			break;
		}
		case Qt::RightButton:
		{
			QGraphicsItem *item = itemAt(me->scenePos());
            if (item && (item->type() == QNEConnection::Type))
            {
				delete item;
            }
            if (item && (item->type() == QNEBlock::Type))
            {
                QNEBlock* b = (QNEBlock*) item;

                foreach (QGraphicsItem *current, scene->items())
                {
                    if (current && (current->type() == QNEConnection::Type))
                    {
                        QNEConnection* conn = (QNEConnection*) current;
                        foreach(QGraphicsItem *port_, b->childItems())
                        {
                            if(conn->port1() == port_ || conn->port2() == port_)
                            {
                                delete current;
                            }
                        }

                    }
                }

                delete item;

            }
			break;
		}
		}
	}
	case QEvent::GraphicsSceneMouseMove:
	{   
		if (conn)
		{
			conn->setPos2(me->scenePos());
			conn->updatePath();
			return true;
		}
		break;
	}
	case QEvent::GraphicsSceneMouseRelease:
	{
		if (conn && me->button() == Qt::LeftButton)
		{
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && item->type() == QNEPort::Type)
			{
				QNEPort *port1 = conn->port1();
				QNEPort *port2 = (QNEPort*) item;

                bool portEmpty = true;

                // Kontrola zda propojujici input porty jsou prazdne
                foreach(QGraphicsItem *item, scene->items())
                {
                    if(item->type() != QNEPort::Type)
                        continue;

                    QNEPort* port = (QNEPort*) item;
                    if(!port2->isOutput())
                    {
                        if(port2->isConnected(port))
                            portEmpty = false;
                    }else{
                        if(port1->isConnected(port))
                            portEmpty = false;
                    }
                }

                // Zaktulizovani propoju
                if (portEmpty && port1->block() != port2->block() && port1->isOutput() != port2->isOutput() && !port1->isConnected(port2))
                {
					conn->setPos2(port2->scenePos());
                    conn->setPort2(port2);
					conn->updatePath();
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
	}
	return QObject::eventFilter(o, e);
}

void QNodesEditor::save(QDataStream &ds)
{
	foreach(QGraphicsItem *item, scene->items())
		if (item->type() == QNEBlock::Type)
		{
			ds << item->type();
			((QNEBlock*) item)->save(ds);
		}

	foreach(QGraphicsItem *item, scene->items())
		if (item->type() == QNEConnection::Type)
		{
			ds << item->type();
			((QNEConnection*) item)->save(ds);
		}
}

void QNodesEditor::load(QDataStream &ds)
{
    scene->clear();

	QMap<quint64, QNEPort*> portMap;

	while (!ds.atEnd())
	{
		int type;
		ds >> type;
		if (type == QNEBlock::Type)
		{
            QNEBlock *block = new QNEBlock(0);
            scene->addItem(block);
			block->load(ds, portMap);

		} else if (type == QNEConnection::Type)
        {
            QNEConnection *conn = new QNEConnection(0);
            scene->addItem(conn);
			conn->load(ds, portMap);

            if (conn->m_port1->m_block->def == true){ //if previous value defined, set tooltip over connection
                conn->setToolTip(QString::number(conn->m_port1->m_block->value,'f',3));
            }
		}
	}
}
void QNodesEditor::clear()
{
    scene->clear();
}
