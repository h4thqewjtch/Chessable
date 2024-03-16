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


    add_piece_labels();

    connect(gameTab, &GameTab::signal_to_remove_opponent_piece_label, this, &MainWindow::slot_to_remove_opponent_piece_label);
    connect(gameTab, &GameTab::signal_to_promote_pawn, this, &MainWindow::slot_to_promote_pawn);
    connect(gameTab, &GameTab::signal_to_show_move, this, &MainWindow::slot_to_show_move);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete layout;
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
}

void MainWindow::slot_to_remove_opponent_piece_label(DraggableLabel *pieceLabel)
{
    pieceLabel->deleteLater();
}

void MainWindow::slot_to_promote_pawn(DraggableLabel *pieceLabel, QString &pieceColor)
{
    pieceLabel->deleteLater();
    PromotionField promotionField = PromotionField(pieceColor);
    promotionField.exec();
    gameTab->get_batch()->set_current_new_piece_type_and_image_path(promotionField.get_piece_type(), promotionField.get_piece_image_path());
    gameTab->get_batch()->get_current_new_piece()->get_piece_label()->setParent(ui->widget);
    gameTab->get_batch()->get_current_new_piece()->get_piece_label()->show();
}

void MainWindow::slot_to_show_move(QString currentMove)
{
    if (!currentMove.contains(". "))
    {
        currentMove = "                           " + currentMove;
    }
    ui->movesList->addItem(currentMove);
    ui->movesList->setCurrentRow(ui->movesList->count() - 1);
    if (currentMove.contains("#"))
    {
        if (currentMove.contains(". "))
        {
            QMessageBox::information(this, "End of game", "White win!");
        }
        else
        {
            QMessageBox::information(this, "End of game", "Black win!");
        }
        gameTab->end_batch();
        ui->tabWidget->setCurrentIndex(0);
    }
    else if (currentMove.contains("="))
    {
        QMessageBox::information(this, "End of game", "Draw");
        gameTab->end_batch();
        ui->tabWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_offerADrawButton_clicked()
{

}


void MainWindow::on_giveUpButton_clicked()
{

}

