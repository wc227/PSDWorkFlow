#include "dlgworkflow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DlgWorkFlow w;
    w.show();

    return a.exec();
}
