#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("asit-dhal");
    QCoreApplication::setApplicationName("LogViewer");

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    w.show();

    return a.exec();
}
