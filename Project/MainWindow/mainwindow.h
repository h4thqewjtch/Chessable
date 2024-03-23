#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QResource>
#include <QTest>
#include <QTextStream>
#include <QThread>

#include "../ArchiveTab/archivetab.h"
#include "../BatchList/batchlist.h"
#include "../BluetoothClient/bluetoothclient.h"
#include "../BluetoothServer/bluetoothserver.h"
#include "../GameTab/gametab.h"
#include "../PromotionField/promotionfield.h"
#include "../ThreadClient/threadclient.h"
#include "../ThreadServer/threadserver.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void add_gif();

    void remove_gif();

    void on_offerADrawButton_clicked();

    void on_giveUpButton_clicked();

    void add_piece_labels();

    void slot_to_remove_opponent_piece_label(DraggableLabel *);

    void slot_to_promote_pawn(DraggableLabel *, QString &);

    void slot_to_show_move(QString, int, QPair<QPoint, QPoint>);

    void drag_and_drop_opponent_piece_label(int, int, int, int);

    void on_whiteButton_clicked();

    void on_blackButton_clicked();

    void show_chessboard_and_pieces();

    void slot_for_error();

    void on_deviceList_doubleClicked(const QModelIndex &index);

    void slot_to_get_devices_list(QStringList);

    void slot_for_accepted_connection(QString);

    void slot_to_receive_to_client(QString);

    void slot_to_receive_to_server(QString);

    void slot_for_error_opponent();

    void slot_to_end_client();

    void slot_to_end_server();

    void end_client_thread();

    void end_server_thread();

    void set_to_return();

    void checkmate_for_black(QString);

    void checkmate_for_white(QString);

    void find_draw(QString);

    void on_batchList_doubleClicked(const QModelIndex &index);

    void initialize_statistics_file();

    void change_statistics(int);

    void show_statistics();

    QString get_statistics_line(int);

    void add_move_to_batch_records(QString);

    void show_batches();

private:
    Ui::MainWindow *ui;

    GameTab *gameTab;
    ArchiveTab *archiveTab;
    QThread *threadClient;
    QThread *threadServer;
    ThreadClient *thClient = nullptr;
    ThreadServer *thServer = nullptr;
    QMovie *movie;
    QLabel *movieLabel;
    int superiority;
    QString piece_from_pawn = "";
    QFile statisticsFile;
    QFile batchesFile;
    // QString playerDeviceName = "Player";
    // QString opponentDeviceName = "Opponent";

signals:
    void signal_to_find_devices();
    void signal_to_create_client(int);
    void signal_to_send_from_client(QString);
    void signal_to_receive_to_client();
    void signal_to_close_client();

    void signal_to_create_server();
    void signal_to_send_from_server(QString);
    void signal_to_receive_to_server();
    void signal_to_close_server();
};
#endif // MAINWINDOW_H
