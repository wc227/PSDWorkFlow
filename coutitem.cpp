﻿#include "coutitem.h"
#include <QInputDialog>

COutItem::COutItem(bool isEditState) :
    CGraphicsObjectItem(isEditState),
    nShape(0)
{
    setZValue(0);
    m_EventNumber = 0;
    ShareMemoryBuild();
}

void COutItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(b_IsEditState)
    {
        if (option->state & QStyle::State_Selected) {  //设置虚线
            QPen dashLinepen(Qt::black);
            dashLinepen.setWidth(1);
            dashLinepen.setStyle(Qt::DashLine);
            painter->setPen(dashLinepen);
            painter->drawRect(QRectF(0,0,m_Width,m_Height));
        }
    }

    if(!b_HoverEnter && !this->isSelected())
    {
      painter->setOpacity(0);
    }

    if(b_HoverEnter && !this->isSelected())
    {
        painter->setOpacity(1);
        painter->setPen(Qt::red);
    }

    painter->save();
    //反锯齿
    painter->setRenderHint(QPainter::Antialiasing,true);
    QPen p(Qt::red);
    p.setWidth(3);
    p.setJoinStyle(Qt::RoundJoin);
    painter->setPen(p);
    painter->drawPath(shape());////////////////
    painter->restore();

    if(b_IsEditState)
    {
        if (option->state & QStyle::State_Selected) {
            QPen borderSquarePen(Qt::gray);
            painter->setPen(borderSquarePen);
            painter->setBrush(Qt::gray);
            painter->setOpacity(0.7);
            createBorderSquare();
            drawBorderSquare(painter);
        }
    }
}

void COutItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//    if(!shape().contains(event->pos()))
//        return;
    if(m_CursorPos != MouseNo)
        return;

    if(b_IsEditState)
    {
        COutItemPropertyDialog dlg(static_cast<QWidget*> (this->scene()->views().at(0)), this);
        dlg.exec();
//        QString numbers;
//        for(int i=0; i<m_TaskNumbers.count(); i++)
//        {
//            if(i!=0)
//                numbers.append(":");
//            numbers.append(m_TaskNumbers.at(i).trimmed());
//        }

//        bool ok;
//        QString text = QInputDialog::getText(0, tr("QInputDialog::getText()"),
//                                             tr("User name:"), QLineEdit::Normal,
//                                             numbers, &ok);
//        if (ok && !text.isEmpty())
//            m_Name = text;
    }
    else
    {
//        for(int i=0; i<m_TaskNumbers.count(); i++)
//        {
//            m_EventNumber = m_TaskNumbers[i];
//            emit EvtFileChange(m_EventNumber);
//            qDebug() << m_EventNumber;
//        }
        SetEvtList(m_TaskNumbersList, 1);
    }
}

void COutItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

QString COutItem::getEventNumber()
{
    return m_TaskNumber;
}

void COutItem::setEventNumber(const QString &eventNumbers)
{
    m_TaskNumber = eventNumbers;
    if(!b_IsEditState)
        m_TaskNumbersList = m_TaskNumber.split(":");
}

QString COutItem::getCaptainName()
{
    return m_Name;
}

void COutItem::setCaptainName(const QString &name)
{
    m_Name = name;
    qDebug() << m_Name;
}

int COutItem::getShape()
{
    return nShape;
}

void COutItem::setShape(int i)
{
    nShape = i;
	update();
}

void COutItem::SetEvtList(QList<QString>& arList, int val)
{
    if (arList.size() == 0)
        return;

    QString  szTmp;
    szTmp.clear();
    int  nTmp  = 0;
    int  nEvt  = 0;
    bool bInvert =false;
    int  nMax  = arList.count();
    for (int i = 0; i < nMax; i++)
    {
        QString s = arList.at(i);
        nEvt = 0;
        //反逻辑提取
        s = s.trimmed(); //trimmed()返回值是将 \r \t除去 而不是在原来变量上直接删除
        if(s.isEmpty())
            continue;
        szTmp = s;
        bInvert = false;
        if(s.left(1)=="!")
        {
            bInvert = true;
            szTmp.remove(0,1); //删除掉!
        }
        nTmp = EventType(szTmp, &nEvt);
        switch (nTmp)
        {
        case EVT_FILE_TYPE:
            {
                if(bInvert)
                    val*=-1;
                EVTFileChange(nEvt, val);
            }break;
        case EVT_TASK_TYPE:
            {
                if(bInvert)
                    val*=-1;
                EVTTaskChange(nEvt, val);
                qDebug() << "Current Task Number:" << nEvt << "counter:"<< EVTTaskCounter(nEvt);
            }break;
        case EVT_STATUS_TYPE:
            {//与val无关
                bool b = EVTStatus(nEvt);
                if(bInvert) //反逻辑标记
                    EVTStatusSet(nEvt, !b);
                else
                    EVTStatusSet(nEvt, true); //直接设置为真状态[到应用时修订];
                //	if (val > 0)
                //	else
                // EVTStatusSet(nEvt, false);
            }break;
        case EVT_APP_TYPE:
            {
                if(bInvert)
                    val*=-1;
                PSDAPPChange(nEvt, val);
            }break;
        default:
            {
                //cout<<"***无效事件类型:"<<nTmp<<endl;
            }break;
        }//end switch
    }//end for..
}

//2014年3月6日 15:22:57 新添加功能 用于$#!的复杂事件操作;
int COutItem::EventType( const QString pchEvent, int* pnEventNo )
{
    int Rtn=-1;
    if(pchEvent == NULL)
    {
        return Rtn;
    }//end if
    int nTmp = 0;
    QString szEvent = pchEvent;
    szEvent.trimmed();
    if(szEvent.isEmpty())
        return Rtn;
    QChar ch=szEvent.at(0);
    if(ch=='#')
    {
        szEvent.remove(0,1);
        nTmp = szEvent.toInt();
        if(nTmp>0)
        {
            Rtn = EVT_FILE_TYPE;
            if(pnEventNo)
                *pnEventNo = nTmp;
        }
    }
    else if(ch=='@')
    {
        szEvent.remove(0,1);
        nTmp = szEvent.toInt();
        if(nTmp>0)
        {
            Rtn = EVT_TASK_TYPE;
            if(pnEventNo)
                *pnEventNo = nTmp;
        }
    }
    else if(ch=='$')
    {
        szEvent.remove(0,1);
        nTmp = szEvent.toInt();
        if(nTmp>0)
        {
            Rtn = EVT_STATUS_TYPE;
            if(pnEventNo)
                *pnEventNo = nTmp;
        }
    }
    else if(ch=='?')
    {                           //20140301  进程编码前到标志;
        szEvent.remove(0,1);	 //必须对标记进行清掉;
        nTmp = szEvent.toInt();
        if(nTmp>0)
        {
            Rtn = EVT_APP_TYPE; //缺省的处理内容;
            if(pnEventNo)
                *pnEventNo = nTmp;
        }
    }
    else
    {
        szEvent = szEvent.trimmed();
        nTmp = szEvent.toInt();
        if(nTmp>0)
        {
            Rtn = EVT_FILE_TYPE;  //缺省的处理内容;
            if(pnEventNo)
                *pnEventNo = nTmp;
        }
    }
    return Rtn;
}

//QRectF COutItem::boundingRect() const
//{

//}

QPainterPath COutItem::shape()
{
    QPainterPath path;
    switch (nShape) {
    case 0:
        path = CGraphicsObjectItem::shape();
        break;
    case 1:
        path.addPolygon(QPolygonF() <<QPointF(0,m_Height) << QPointF(m_Width,m_Height));
        break;
    case 2:
        path.addEllipse(0,0,m_Width,m_Height);
        break;
    case 3:
        path.addPolygon(QPolygonF() << QPointF(0,0) << QPointF(m_Width,m_Height/2)
                                        << QPointF(0,m_Height) << QPointF(0,0));
        break;
    default:
        break;
    }
    currentPath = path;
    return path;
}

//////////////////////////////////////////////////////////////
/// \brief COutItemPropertyDialog::COutItemPropertyDialog
/// \param parent
//////////////////////////////////////////////////////////////
COutItemPropertyDialog::COutItemPropertyDialog(QWidget *parent, COutItem *currentItem) :
    QDialog(parent),
    m_CurrentItem(currentItem)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    bDataIsChanged = false;

    QHBoxLayout *pNameLayout = new QHBoxLayout;

    m_pNameLabel = new QLabel("Name:", this);
    m_pNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight); //设置Label文字靠右
    m_pNameLineEdit = new QLineEdit(this);

    pNameLayout->addWidget(m_pNameLabel);
    pNameLayout->addWidget(m_pNameLineEdit);

    QHBoxLayout *pEventLayout = new QHBoxLayout;

    m_pEventLabel = new QLabel("Events:", this);
    m_pEventLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_pEventLineEdit = new QLineEdit(this);

    pEventLayout->addWidget(m_pEventLabel);
    pEventLayout->addWidget(m_pEventLineEdit);

    //2014年5月6日10:04:11
    QHBoxLayout *pShapeLayout = new QHBoxLayout;

    m_pShapeLabel = new QLabel(tr("Shape:"), this);
    m_pShapeComBox = new QComboBox;
    m_pShapeComBox->addItem(tr("default"));
    m_pShapeComBox->addItem(tr("line"));
    m_pShapeComBox->addItem(tr("circle"));
    m_pShapeComBox->addItem(tr("triangle"));

    pShapeLayout->addWidget(m_pShapeLabel);
    pShapeLayout->addWidget(m_pShapeComBox);

    QVBoxLayout *pMainLayout = new QVBoxLayout(this);
    pMainLayout->addLayout(pNameLayout);
    pMainLayout->addLayout(pEventLayout);
    pMainLayout->addLayout(pShapeLayout);

    this->setLayout(pMainLayout);

    setName(m_CurrentItem->getCaptainName());
    setEvents(m_CurrentItem->getEventNumber());
    setShape(m_CurrentItem->getShape());

    connect(m_pEventLineEdit, SIGNAL(editingFinished()),
            this, SLOT(SLOT_EventLineEditChanged()));
    connect(m_pNameLineEdit, SIGNAL(editingFinished()),
            this, SLOT(SLOT_NameLineEditChanged()));
    connect(m_pShapeComBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(SLOT_ShapeComboxChanged(int)));

    this->setWindowTitle(tr("Save"));
}

COutItemPropertyDialog::~COutItemPropertyDialog()
{
    m_ModifiName = m_pNameLineEdit->text().trimmed();
    m_ModifiEvents = m_pEventLineEdit->text().trimmed();
    shapeType = (ItemShape)m_pShapeComBox->currentIndex();

    if(m_ModifiName != m_SaveName || m_ModifiEvents != m_SaveEvents
            || nShape != m_pShapeComBox->currentIndex())
        bDataIsChanged = true;

    if(!bDataIsChanged)
        return;

    QMessageBox::StandardButton button;
    button = QMessageBox::information(this, tr("Save"), tr("数据已被修改，是否要保存"),
                             QMessageBox::Ok, QMessageBox::Cancel);

    if(button == QMessageBox::Ok)
    {
        if( m_ModifiName != m_SaveName)
            m_CurrentItem->setCaptainName(m_ModifiName);

        if( m_ModifiEvents != m_SaveEvents)
            m_CurrentItem->setEventNumber(m_ModifiEvents);

        if( m_CurrentItem->getShape() != (int)shapeType)
            m_CurrentItem->setShape((int)shapeType);
    }
}

void COutItemPropertyDialog::setName(const QString &name)
{
    m_SaveName = name;
    m_ModifiName = name;
    m_pNameLineEdit->setText(name);
}

void COutItemPropertyDialog::setEvents(const QString &events)
{
    m_SaveEvents = events;
    m_pEventLineEdit->setText(events);
}

void COutItemPropertyDialog::setShape(const int &shape)
{
    nShape = shape;
    m_pShapeComBox->setCurrentIndex(nShape);
}

void COutItemPropertyDialog::SLOT_EventLineEditChanged()
{
    m_ModifiEvents = m_pEventLineEdit->text();
    m_ModifiEvents = m_ModifiEvents.trimmed();
}

void COutItemPropertyDialog::SLOT_NameLineEditChanged()
{
    m_ModifiName = m_pNameLineEdit->text();
    m_ModifiName = m_ModifiName.trimmed();
}

void COutItemPropertyDialog::SLOT_ShapeComboxChanged(int index)
{
    QString text = m_pShapeComBox->itemText(index);
    if(text == "default")
        shapeType = Default;

    else if(text == "line")
        shapeType = Line;

    else if(text == "circle")
        shapeType = Circle;

    else if(text == "triangle")
        shapeType = Triangle;
}
