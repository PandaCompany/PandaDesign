#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("pandadesign");
    a.setApplicationDisplayName("Panda Design");
    a.setOrganizationDomain("com.thepandacompany");
    a.setOrganizationName("The Panda Company");

    Window w;
    w.show();

    return a.exec();
}
