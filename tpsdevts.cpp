#include "tpsdevts.h"
#include <QDebug>

TPsdEvts::TPsdEvts(QObject *parent) :
    QObject(parent)
{
    ShareMemoryBuild();
}

TPsdEvts::~TPsdEvts()
{

}

void TPsdEvts::setEventList(QList<QString> &arList, int val)
{
    if (arList.size() == 0)
        return;

    QString  szTmp;
    szTmp.clear();
    int  nTmp  = 0;
    int  nEvt  = 0;
    bool bInvert = false;
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
        nTmp = eventType(szTmp, &nEvt);
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

int TPsdEvts::eventType(QString &pchEvent, int *pnEventNo)
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
        pchEvent.prepend('#');
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

int TPsdEvts::evtCounter(QString &pchEvent)
{
    int nType = -1;  //事件类型
    int nEvt;        //事件值
    int nCounter = 0;
    nType = eventType(pchEvent, &nEvt);

    switch (nType) {
    case EVT_FILE_TYPE:
        nCounter = EVTFileCounter(nEvt);
        break;
    case EVT_TASK_TYPE:
        nCounter = EVTTaskCounter(nEvt);
        break;
    case EVT_STATUS_TYPE:
        break;
    case EVT_APP_TYPE:
        break;
    default:
        break;
    }
    return nCounter;
}
