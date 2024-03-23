#include <QApplication>

#include "MainWindow\mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowIcon(QIcon(":/Materials/Images/chessable.png"));
    mainWindow.show();
    return a.exec();
}



//пат
//на путь рокировки смотрит вражина
//поворот доски для черных
//поражение при выходе
//поражение при сдаче
//ничья, если противник согласен


