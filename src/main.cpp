#include <QtGui/QApplication>
#include "toplevelwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToplevelWindow w;
    w.show();
    QObject::connect(&w, SIGNAL(destroyed()), &a, SLOT(quit()));
    return a.exec();
}
