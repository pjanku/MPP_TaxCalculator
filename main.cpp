#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("UTB");
    QCoreApplication::setOrganizationDomain("utb.cz");
    QCoreApplication::setApplicationName("TaxCalculator");

    MainWindow w;
    w.show();
    return a.exec();
}
