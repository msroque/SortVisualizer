// PURPOSE: builds app

// Qt
#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>

// Source
#include "Sort.h"

int main(int argc, char *argv[])
{
    // Build Qt App
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << "Qt application executed!";
    w.show();
    return a.exec();
}

