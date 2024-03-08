#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Chessable");

    gameTab = new GameTab();
    playersTab = new PlayersTab();
    archiveTab = new ArchiveTab();
    profileTab = new ProfileTab();

    //layout = new QVBoxLayout(ui->widget);

    add_piece_labels();

    connect(gameTab, &GameTab::signal_to_remove_opponent_piece_label, this, &MainWindow::slot_to_remove_opponent_piece_label);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    delete gameTab;
    delete playersTab;
    delete archiveTab;
    delete profileTab;
}

void MainWindow::add_piece_labels()
{
    gameTab->get_batch()->get_chess_board()->setParent(ui->widget);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            gameTab->get_batch()->get_piece_on_position(j, i)->get_piece_label()->setParent(ui->widget);
        }
    }

    for (int i = 7; i > 5; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            gameTab->get_batch()->get_piece_on_position(j, i)->get_piece_label()->setParent(ui->widget);
        }
    }
    //ui->widget->setLayout(layout);
}

void MainWindow::slot_to_remove_opponent_piece_label(DraggableLabel *pieceLabel)
{
    pieceLabel->deleteLater();
}

void MainWindow::on_minute1Button_clicked()
{

}


void MainWindow::on_minutes3Button_clicked()
{

}


void MainWindow::on_minutes5Button_clicked()
{

}


void MainWindow::on_minutes10Button_clicked()
{

}


void MainWindow::on_minutes15Button_clicked()
{

}


void MainWindow::on_minutes30Button_clicked()
{

}


void MainWindow::on_playButton_clicked()
{

}


void MainWindow::on_offerADrawButton_clicked()
{

}


void MainWindow::on_giveUpButton_clicked()
{

}

