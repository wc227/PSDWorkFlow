#include "dlgworkflow.h"
#include <QTimer>

DlgWorkFlow::DlgWorkFlow(QWidget *parent)
    : CWidget(parent)
{
    this->showMaximized();
    QTimer::singleShot(1000,this,SLOT(init()));
}

DlgWorkFlow::~DlgWorkFlow()
{

}


void DlgWorkFlow::init()
{
    setIniPath("E:/Test/PSDATC/App/UI/TGanSuOCX3D/pp.ini");
}
