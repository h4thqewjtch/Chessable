#include <QApplication>

#include "MainWindow\mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowIcon(QIcon("../Materials/Images/chessable.png"));
    mainWindow.show();
    return a.exec();
}


