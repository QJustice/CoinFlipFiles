#include "cmainscene.h"
#include <QApplication>
//#include "dataconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMainScene w;
    w.show();

    return a.exec();
}
