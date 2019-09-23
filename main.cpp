#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QPushButton>
#include <QPropertyAnimation>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile style(":/style.css");
    style.open(QFile::ReadOnly);
    a.setStyleSheet(style.readAll());
    MainWindow w;
    w.show();
    return a.exec();
}
