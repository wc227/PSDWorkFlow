﻿#include "cgraphicsscene.h"
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

CGraphicsScene::CGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    b_MousePressInItem = false;
    createContextMenu();

    ShareMemoryBuild();
}

CGraphicsScene::CGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene( x, y, width, height, parent)
{
    createContextMenu();
	m_pCurrentLinePath = NULL;
	m_startAddLine = false;
}

void CGraphicsScene::createContextMenu()
{
    contextMenu = new QMenu;
    m_ActionAddIn = new QAction("In",contextMenu);
    m_ActionAddOut = new QAction("Out",contextMenu);
	m_ActionPathLine = new QAction("Line",contextMenu);
    m_ActionDel = new QAction("Del",contextMenu);

    connect(m_ActionAddIn, SIGNAL(triggered()), this, SLOT(slotAddgraphicsitem()));
    connect(m_ActionAddOut, SIGNAL(triggered()), this, SLOT(slotAddCRedItem()));
    connect(m_ActionDel, SIGNAL(triggered()), this, SLOT(slotDelItem()));
	connect(m_ActionPathLine, SIGNAL(triggered()), this, SLOT(slotADDPathLine()));

    contextMenu->addAction(m_ActionAddIn);
    contextMenu->addAction(m_ActionAddOut);
	contextMenu->addAction(m_ActionPathLine);
    contextMenu->addAction(m_ActionDel);
}

void CGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::RightButton)
    {
		if(m_startAddLine && event->button() == Qt::LeftButton)
		{
			if(m_pCurrentLinePath == NULL)
				return;
			//Q_ASSERT(currentPathItem);
			QPolygonF polygon = m_pCurrentLinePath->getPolygon();

			polygon << event->scenePos();
			m_pCurrentLinePath->setPolygon(polygon);
			QPainterPath path;
			path.addPolygon(polygon);
			m_pCurrentLinePath->setPath(path);
			m_pCurrentLinePath->editEnd();
			update(m_pCurrentLinePath->boundingRect().adjusted(-1, -1, 1, 1));
		}
		else
		{
			QGraphicsScene::mouseDoubleClickEvent(event);
			return;
		}
    }
	else
	{
		if(m_startAddLine)
			m_startAddLine = false;
	}
    qDebug() << "mouse double click";
}

void CGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(!b_MousePressInItem)
    {
        if(b_IsEdit)
        {
            m_RightButtonPos = event->scenePos();
            qDebug()<< event->scenePos();
            qDebug() << event->screenPos();
            contextMenu->exec(event->screenPos());
        }
    }
    else
    {
        QGraphicsScene::contextMenuEvent(event);
        b_MousePressInItem = false;
    }
}

//--slot
void CGraphicsScene::slotAddgraphicsitem()
{
    CBarItem *item = new CBarItem(true);
    qDebug() << m_RightButtonPos;
    item->setPos(m_RightButtonPos.x() - item->m_Width/2, m_RightButtonPos.y() - item->m_Height/2);
    item->setSelected(true);
    this->addItem(item);
}

void CGraphicsScene::slotAddCRedItem()
{
    COutItem *item = new COutItem(true);
    item->setPos(m_RightButtonPos.x() - item->m_Width/2, m_RightButtonPos.y() - item->m_Height/2);
    item->setSelected(true);
    this->addItem(item); 
}

void CGraphicsScene::slotDelItem()
{
    qDebug() << selectedItems().count();
    if(selectedItems().count())
    {
        for(int i=0; selectedItems().count(); i++)
            delete selectedItems().at(i);
    }
}

void CGraphicsScene::slotEVTFileChange(int n)
{
    qDebug() << "change" << n;
    //EVTTaskChange(n);
    EVTFileChange(n);
}

void CGraphicsScene::slotADDPathLine()
{
	if(!m_startAddLine)
		m_startAddLine = true;
	CMyPathItem *pItem = new CMyPathItem(this,false);
	m_pCurrentLinePath = pItem;
	this->addItem(pItem);
}

void CGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
	if(event->button() == Qt::RightButton)
	{
		if(m_startAddLine)
			m_startAddLine = false;
		if(m_pCurrentLinePath)
			m_pCurrentLinePath = NULL;
	}
	QGraphicsScene::mousePressEvent(event);
}
