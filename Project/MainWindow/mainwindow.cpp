#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Chessable");

    gameTab = new GameTab();
    archiveTab = new ArchiveTab();

    QString appPath = QCoreApplication::applicationDirPath();
    QDir dir = QDir(appPath);
    dir.cd("../../Project/Materials/Archive/");
    QString statisticsFilePath = dir.absolutePath() + "/Statistics.txt";
    statisticsFile.setFileName(statisticsFilePath);
    if (!statisticsFile.size())
    {
        initialize_statistics_file();
    }
    show_statistics();

    appPath = QCoreApplication::applicationDirPath();
    dir = QDir(appPath);
    dir.cd("../../Project/Materials/Archive/");
    QString batchesFilePath = dir.absolutePath() + "/Batches.txt";
    qDebug() << batchesFilePath;
    batchesFile.setFileName(batchesFilePath);
    show_batches();


    connect(gameTab, &GameTab::signal_to_remove_opponent_piece_label, this, &MainWindow::slot_to_remove_opponent_piece_label);
    connect(gameTab, &GameTab::signal_to_promote_pawn, this, &MainWindow::slot_to_promote_pawn);
    connect(gameTab, &GameTab::signal_to_show_move, this, &MainWindow::slot_to_show_move);

    superiority = 0;

    add_gif();

    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameTab;
    delete archiveTab;

    emit signal_to_close_client();
    delete thClient;
    threadClient->quit();
    threadClient->wait();
    delete threadClient;

    emit signal_to_close_server();
    delete thServer;
    threadServer->quit();
    threadServer->wait();
    delete threadServer;
}

void MainWindow::add_gif()
{
    // Создание объекта QMovie и загрузка гиф-изображения
    movie = new QMovie(":/Materials/Images/best_batch.gif");

    // Создаем метку и устанавливаем гиф-изображение в качестве иконки
    movieLabel = new QLabel(ui->widget);

    movieLabel->setMovie(movie);
    movie->start();
    // Устанавливаем размеры изображения такие же, как у виджета
    movieLabel->setScaledContents(true);
    movieLabel->setFixedSize(ui->widget->size()); // Используйте setFixedSize() или setGeometry()

    movieLabel->show();

}

void MainWindow::remove_gif()
{
    // Остановить анимацию гиф-изображения
    movie->stop();

    // Удалить QLabel из ui->widget
    movieLabel->deleteLater(); // Используйте deleteLater() для безопасного удаления виджета

    // Удалить QMovie и QLabel
    delete movie;
    delete movieLabel;

}

void MainWindow::add_piece_labels()
{
    gameTab->get_batch()->get_chess_board()->setParent(ui->widget);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            gameTab->get_batch()->get_piece_on_position(j, i)->get_piece_label()->setParent(ui->widget);
            gameTab->get_batch()->get_piece_on_position(j, i)->get_piece_label()->show();
        }
    }

    for (int i = 7; i > 5; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            gameTab->get_batch()->get_piece_on_position(j, i)->get_piece_label()->setParent(ui->widget);
            gameTab->get_batch()->get_piece_on_position(j, i)->get_piece_label()->show();
        }
    }
    gameTab->get_batch()->get_chess_board()->show();
}

void MainWindow::slot_to_remove_opponent_piece_label(DraggableLabel *pieceLabel)
{
    pieceLabel->deleteLater();
}

void MainWindow::slot_to_promote_pawn(DraggableLabel *pieceLabel, QString &pieceColor)
{
    pieceLabel->deleteLater();
    PromotionField promotionField = PromotionField(pieceColor);
    if (piece_from_pawn.isEmpty())
    {
        promotionField.exec();
    }
    else
    {
        if (piece_from_pawn == "Q")
        {
            promotionField.set_piece("queen", ":/Materials/Images/queen_white.png", ":/Materials/Images/queen_black.png");
        }
        else if (piece_from_pawn == "R")
        {
            promotionField.set_piece("rook", ":/Materials/Images/rook_white.png", ":/Materials/Images/rook_black.png");
        }
        else if (piece_from_pawn == "B")
        {
            promotionField.set_piece("bishop", ":/Materials/Images/bishop_white.png", ":/Materials/Images/bishop_black.png");
        }
        else if (piece_from_pawn == "N")
        {
            promotionField.set_piece("knight", ":/Materials/Images/knight_white.png", ":/Materials/Images/knight_black.png");
        }
        else if (piece_from_pawn == "p")
        {
            promotionField.set_piece("pawn", ":/Materials/Images/pawn_white.png", ":/Materials/Images/pawn_black.png");
        }
        piece_from_pawn.clear();
    }
    gameTab->get_batch()->set_current_new_piece_type_and_image_path(promotionField.get_piece_type(), promotionField.get_piece_image_path());
    gameTab->get_batch()->get_current_new_piece()->get_piece_label()->setParent(ui->widget);
    gameTab->get_batch()->get_current_new_piece()->get_piece_label()->show();
}

void MainWindow::slot_to_show_move(QString currentMoveRecord, int super, QPair<QPoint, QPoint> currentMove)
{
    QString moveToArchive = currentMoveRecord;
    superiority += super;
    QString currentMoveString = QString::number(currentMove.first.x()) + " " + QString::number(currentMove.first.y())
                                + "|" + QString::number(currentMove.second.x()) + " " + QString::number(currentMove.second.y());
    if (currentMoveRecord.contains(":"))
    {
        currentMoveString += "!" + QString(currentMoveRecord[currentMoveRecord.indexOf(":") - 1]);
    }
    if (superiority > 0)
    {
        ui->opponentSuperiority->clear();
        ui->playerSuperiority->setText("+" + QString::number(qAbs(superiority)));
    }
    else if (superiority < 0)
    {
        ui->playerSuperiority->clear();
        ui->opponentSuperiority->setText("+" + QString::number(qAbs(superiority)));
    }
    else
    {
        ui->opponentSuperiority->clear();
        ui->playerSuperiority->clear();
    }
    if (!currentMoveRecord.contains(". "))
    {
        currentMoveRecord = "                           " + currentMoveRecord;
    }
    ui->movesList->addItem(currentMoveRecord);
    ui->movesList->scrollToItem(ui->movesList->item(ui->movesList->count() - 1));

    QWidget *widgetAtPoint = ui->widget->childAt(currentMove.first.x(), currentMove.first.y());
    if (widgetAtPoint)
    {
        DraggableLabel *pieceLabel = qobject_cast<DraggableLabel *>(widgetAtPoint);
        if (pieceLabel->pressed())
        {
            ui->offerADrawButton->setEnabled(false);
            ui->giveUpButton->setEnabled(false);
            if (thClient != nullptr)
            {
                emit signal_to_send_from_client(currentMoveString);
                emit signal_to_receive_to_client();
            }
            else
            {
                emit signal_to_send_from_server(currentMoveString);
                emit signal_to_receive_to_server();
            }
        }
        else
        {
            ui->offerADrawButton->setEnabled(true);
            ui->giveUpButton->setEnabled(true);
        }
    }
    if (currentMoveRecord.contains("#"))
    {
        if (currentMoveRecord.contains(". "))
        {
            checkmate_for_black(moveToArchive);
        }
        else
        {
            checkmate_for_white(moveToArchive);
        }

    }
    else if (currentMoveRecord.contains("="))
    {
        find_draw(moveToArchive);
    }
    else
    {
        add_move_to_batch_records(moveToArchive);
    }
}

void MainWindow::drag_and_drop_opponent_piece_label(int startX, int startY, int endX, int endY)
{
    // Находим виджет по координатам
    QWidget *widgetAtPoint = ui->widget->childAt(startX, startY);
    // Проверяем, является ли найденный виджет DraggableLabel
    if (widgetAtPoint)
    {

        DraggableLabel *pieceLabel = qobject_cast<DraggableLabel *>(widgetAtPoint);
        if (pieceLabel)
        {
            // pieceLabel->simulateMousePress(QPoint(startX, startY));
            // pieceLabel->simulateMouseMove(QPoint(endX, endY));
            pieceLabel->simulateMouseRelease(QPoint(endX, endY));
        }
    }

}

void MainWindow::on_offerADrawButton_clicked()
{

}

void MainWindow::on_giveUpButton_clicked()
{
    qDebug() << "on_giveUpButton_clicked()";
    if (thClient != nullptr)
    {
        change_statistics(7);
        change_statistics(8);
        add_move_to_batch_records("\nBlack win! Opponent resigned\n\n\n");
        ui->movesList->addItem("Black win! Opponent resigned");
        QMessageBox::information(this, "End of game", "Black win! Opponent resigned");
        emit signal_to_send_from_client("");
    }
    else
    {
        change_statistics(7);
        change_statistics(9);
        add_move_to_batch_records("\nWhite win! Opponent resigned\n\n\n");
        ui->movesList->addItem("White win! Opponent resigned");
        QMessageBox::information(this, "End of game", "White win! Opponent resigned");
        emit signal_to_send_from_server("");
    }
}

void MainWindow::on_whiteButton_clicked()
{
    ui->whiteButton->setEnabled(false);
    ui->blackButton->setEnabled(false);

    if (!(threadClient = new QThread(this)))
    {
        QMessageBox::warning(this, "Memory allocation", "Object of QThread was not created!");
    }
    if (!(thClient = new ThreadClient()))
    {
        QMessageBox::warning(this, "Memory allocation", "Object of ThreadClient was not created!");
    }

    QObject::connect(this, SIGNAL(destroyed()), threadClient, SLOT(quit()));
    QObject::connect(this, SIGNAL(signal_to_find_devices()), thClient, SLOT(slot_to_find_devices()));
    QObject::connect(this, SIGNAL(signal_to_create_client(int)), thClient, SLOT(slot_to_create_client(int)));
    QObject::connect(this, SIGNAL(signal_to_send_from_client(QString)), thClient, SLOT(slot_to_send_from_client(QString)));
    QObject::connect(this, SIGNAL(signal_to_receive_to_client()), thClient, SLOT(slot_to_receive_to_client()));
    QObject::connect(this, SIGNAL(signal_to_close_client()), thClient, SLOT(slot_to_close_client()));

    thClient->moveToThread(threadClient);
    threadClient->start();

    QObject::connect(thClient, SIGNAL(signal_for_error()), this, SLOT(slot_for_error()));
    QObject::connect(thClient, SIGNAL(signal_to_get_devices_list(QStringList)), this, SLOT(slot_to_get_devices_list(QStringList)));
    QObject::connect(thClient, SIGNAL(signal_for_accepted_connection(QString)), this, SLOT(slot_for_accepted_connection(QString)));
    QObject::connect(thClient, SIGNAL(signal_to_receive_to_client(QString)), this, SLOT(slot_to_receive_to_client(QString)));
    QObject::connect(thClient, SIGNAL(signal_to_end_client()), this, SLOT(slot_to_end_client()));
    QObject::connect(thClient, SIGNAL(signal_for_error_opponent()), this, SLOT(slot_for_error_opponent()));


    ui->deviceList->addItem("Try to find a worthy opponent...");
    ui->deviceList->setEnabled(false);

    emit signal_to_find_devices();
}

void MainWindow::on_blackButton_clicked()
{
    ui->whiteButton->setEnabled(false);
    ui->blackButton->setEnabled(false);

    if (!(threadServer = new QThread(this)))
    {
        QMessageBox::warning(this, "Memory allocation", "Object of QThread was not created!");
    }
    if (!(thServer = new ThreadServer()))
    {
        QMessageBox::warning(this, "Memory allocation", "Object of ThreadServer was not created!");
    }

    QObject::connect(this, SIGNAL(destroyed()), threadServer, SLOT(quit()));
    QObject::connect(this, SIGNAL(signal_to_create_server()), thServer, SLOT(slot_to_create_server()));
    QObject::connect(this, SIGNAL(signal_to_send_from_server(QString)), thServer, SLOT(slot_to_send_from_server(QString)));
    QObject::connect(this, SIGNAL(signal_to_receive_to_server()), thServer, SLOT(slot_to_receive_to_server()));
    QObject::connect(this, SIGNAL(signal_to_close_server()), thServer, SLOT(slot_to_close_server()));

    thServer->moveToThread(threadServer);
    threadServer->start();

    QObject::connect(thServer, SIGNAL(signal_for_error()), this, SLOT(slot_for_error()));
    QObject::connect(thServer, SIGNAL(signal_for_accepted_connection(QString)), this, SLOT(slot_for_accepted_connection(QString)));
    QObject::connect(thServer, SIGNAL(signal_to_receive_to_server(QString)), this, SLOT(slot_to_receive_to_server(QString)));
    QObject::connect(thServer, SIGNAL(signal_to_end_server()), this, SLOT(slot_to_end_server()));
    QObject::connect(thServer, SIGNAL(signal_for_error_opponent()), this, SLOT(slot_for_error_opponent()));

    ui->deviceList->addItem("Player's device name: " + thServer->get_device_name());
    ui->deviceList->setEnabled(false);

    emit signal_to_create_server();
    emit signal_to_receive_to_server();
}

void MainWindow::show_chessboard_and_pieces()
{
    gameTab->set_batch();
    add_piece_labels();
}

void MainWindow::slot_for_error()
{
    qDebug() << "slot_for_error()";
    add_move_to_batch_records("\nBatch is aborted\n\n\n");
    if (thClient != nullptr)
    {
        ui->movesList->addItem("Batch is aborted");
        QMessageBox::warning(this, "End of game", "Batch is aborted");

        end_client_thread();
    }
    else
    {
        ui->movesList->addItem("Batch is aborted");
        QMessageBox::warning(this, "End of game", "Batch is aborted");

        end_server_thread();
    }

    ui->whiteButton->setEnabled(true);
    ui->blackButton->setEnabled(true);
}

void MainWindow::on_deviceList_doubleClicked(const QModelIndex &index)
{
    int number = ui->deviceList->row(ui->deviceList->itemFromIndex(index));
    emit signal_to_create_client(number);
}

void MainWindow::slot_to_get_devices_list(QStringList list)
{
    ui->whiteButton->setEnabled(true);
    ui->blackButton->setEnabled(true);
    ui->deviceList->setEnabled(true);
    ui->deviceList->clear();
    ui->deviceList->addItems(list);
}

void MainWindow::slot_for_accepted_connection(QString color)
{
    remove_gif();

    show_chessboard_and_pieces();

    gameTab->get_batch()->set_player_color(color);

    ui->whiteButton->setEnabled(false);
    ui->blackButton->setEnabled(false);

    ui->deviceList->clear();

    ui->deviceList->setEnabled(false);

    ui->gameTabWidget->setCurrentIndex(1);

    if (thClient != nullptr)
    {
        change_statistics(1);
        change_statistics(2);
    }
    else
    {
        change_statistics(1);
        change_statistics(3);
        ui->giveUpButton->setEnabled(false);
    }

}

void MainWindow::slot_to_receive_to_client(QString opponentMove)
{
    if (opponentMove.contains("!"))
    {
        piece_from_pawn = opponentMove.split("!")[1];
        opponentMove.remove(opponentMove.indexOf("!"), 2);
    }
    QStringList current_new = opponentMove.split("|");
    QStringList current_ranks_files = current_new[0].split(" ");
    QStringList new_ranks_files = current_new[1].split(" ");
    drag_and_drop_opponent_piece_label(current_ranks_files[0].toInt()
                                       , current_ranks_files[1].toInt()
                                       , new_ranks_files[0].toInt()
                                       , new_ranks_files[1].toInt());
}

void MainWindow::slot_to_receive_to_server(QString opponentMove)
{
    if (opponentMove.contains("!"))
    {
        piece_from_pawn = opponentMove.split("!")[1];
        opponentMove.remove(opponentMove.indexOf("!"), 2);
    }
    QStringList current_new = opponentMove.split("|");
    QStringList current_ranks_files = current_new[0].split(" ");
    QStringList new_ranks_files = current_new[1].split(" ");
    drag_and_drop_opponent_piece_label(current_ranks_files[0].toInt()
                                       , current_ranks_files[1].toInt()
                                       , new_ranks_files[0].toInt()
                                       , new_ranks_files[1].toInt());
}

void MainWindow::slot_for_error_opponent()
{
    qDebug() << "slot_for_error_opponent()";
    if (thClient != nullptr)
    {
        add_move_to_batch_records("\nWhite win! Opponent resigned\n\n\n");
        ui->movesList->addItem("White win! Opponent resigned");
        QMessageBox::warning(this, "End of game", "White win! Opponent resigned");
        change_statistics(4);
        change_statistics(5);
        end_client_thread();
    }
    else
    {
        add_move_to_batch_records("\nBlack win! Opponent resigned\n\n\n");
        ui->movesList->addItem("Black win! Opponent resigned");
        QMessageBox::warning(this, "End of game", "Black win! Opponent resigned");
        change_statistics(4);
        change_statistics(6);
        end_server_thread();
    }
    set_to_return();

}

void MainWindow::slot_to_end_client()
{
    end_client_thread();
    set_to_return();
}

void MainWindow::slot_to_end_server()
{
    end_server_thread();
    set_to_return();
}

void MainWindow::end_client_thread()
{
    qDebug() << "end_client";
    emit signal_to_close_client();
    delete thClient;
    threadClient->quit();
    threadClient->wait();
    delete threadClient;

    ui->batchList->clear();
    show_batches();
    show_statistics();
}

void MainWindow::end_server_thread()
{
    qDebug() << "end_server";
    emit signal_to_close_server();
    delete thServer;
    threadServer->quit();
    threadServer->wait();
    delete threadServer;

    ui->batchList->clear();
    show_batches();
    show_statistics();
}

void MainWindow::set_to_return()
{
    qDebug() << "set_to_return";
    gameTab->end_batch();
    ui->gameTabWidget->setCurrentIndex(0);
    add_gif();
    ui->whiteButton->setEnabled(true);
    ui->blackButton->setEnabled(true);
}

void MainWindow::checkmate_for_black(QString moveToArchive)
{
    moveToArchive += "\nWhite win! Checkmate\n\n\n";
    add_move_to_batch_records(moveToArchive);
    ui->movesList->addItem("White win! Checkmate");
    QMessageBox::information(this, "End of game", "White win! Checkmate");
    if (thClient != nullptr)
    {
        change_statistics(4);
        change_statistics(5);
    }
    else
    {
        change_statistics(7);
        change_statistics(9);
        emit signal_to_send_from_server("checkmate");
    }
}

void MainWindow::checkmate_for_white(QString moveToArchive)
{
    moveToArchive += "\nBlack win! Checkmate\n\n";
    add_move_to_batch_records(moveToArchive);
    ui->movesList->addItem("Black win! Checkmate");
    QMessageBox::information(this, "End of game", "Black win! Checkmate");
    if (thClient != nullptr)
    {
        change_statistics(7);
        change_statistics(8);
        emit signal_to_send_from_client("checkmate");
    }
    else
    {
        change_statistics(4);
        change_statistics(6);
    }
}

void MainWindow::find_draw(QString moveToArchive)
{
    moveToArchive += "\nDraw...\n\n";
    add_move_to_batch_records(moveToArchive);
    ui->movesList->addItem("Draw...");
    QMessageBox::information(this, "End of game", "Draw...");
    if (thClient != nullptr)
    {
        moveToArchive += "\n";
        change_statistics(10);
        change_statistics(11);
        emit signal_to_send_from_client("");
    }
    else
    {
        change_statistics(10);
        change_statistics(12);
        emit signal_to_send_from_server("");
    }
}

void MainWindow::on_batchList_doubleClicked(const QModelIndex &index)
{
    BatchList *batchList = new BatchList();
    batchList->exec();
}

void MainWindow::initialize_statistics_file()
{
    if (statisticsFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&statisticsFile);
        out << "0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0" << Qt::endl;
        statisticsFile.close();
    }
}

void MainWindow::change_statistics(int lineNumber)
{
    if (!statisticsFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&statisticsFile);
    QStringList lines;
    while (!in.atEnd())
    {
        lines.append(in.readLine());
    }

    statisticsFile.resize(0); // Clear the file

    QTextStream out(&statisticsFile);
    for (int i = 1; i <= lines.size(); ++i)
    {
        if (i == lineNumber)
        {
            bool ok;
            lines.replace(i - 1, QString::number(lines.at(i - 1).toInt(&ok) + 1));
        }
        out << lines.at(i - 1) << Qt::endl;
    }
    statisticsFile.close();

    show_statistics();
}

void MainWindow::show_statistics()
{
    ui->allPlayed->setText(get_statistics_line(1));
    ui->whitePlayed->setText(get_statistics_line(2));
    ui->blackPlayed->setText(get_statistics_line(3));
    ui->allWins->setText(get_statistics_line(4));
    ui->whiteWins->setText(get_statistics_line(5));
    ui->blackWins->setText(get_statistics_line(6));
    ui->allLoses->setText(get_statistics_line(7));
    ui->whiteLoses->setText(get_statistics_line(8));
    ui->blackLoses->setText(get_statistics_line(9));
    ui->allDraws->setText(get_statistics_line(10));
    ui->whiteDraws->setText(get_statistics_line(11));
    ui->blackDraws->setText(get_statistics_line(12));
}

QString MainWindow::get_statistics_line(int lineNumber)
{
    if (!statisticsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return "";
    }
    QTextStream in(&statisticsFile);
    QStringList lines;
    while (!in.atEnd())
    {
        lines.append(in.readLine());
    }
    statisticsFile.close();
    return  lines.at(lineNumber - 1);
}

void MainWindow::add_move_to_batch_records(QString moveRecord)
{
    if (batchesFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(&batchesFile);
        out << moveRecord;
        if (moveRecord.contains(". "))
        {
            out << "    ";
        }
        else
        {
            out << Qt::endl;
        }
        batchesFile.close();
    }
}

void MainWindow::show_batches()
{
    if (!batchesFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&batchesFile);
    QStringList lines;
    while (!in.atEnd())
    {
        lines.append(in.readLine());
    }
    batchesFile.close();
    ui->batchList->addItems(lines);
}

