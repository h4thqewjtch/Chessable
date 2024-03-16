#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QThread>

#include "../ArchiveTab/archivetab.h"
#include "../GameTab/gametab.h"
#include "../PlayersTab/playerstab.h"
#include "../ProfileTab/profiletab.h"
#include "../PromotionField/promotionfield.h"

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
    void on_offerADrawButton_clicked();

    void on_giveUpButton_clicked();

    void add_piece_labels();

    void slot_to_remove_opponent_piece_label(DraggableLabel *);

    void slot_to_promote_pawn(DraggableLabel *, QString &);

    void slot_to_show_move(QString);

private:
    Ui::MainWindow *ui;

    //QVBoxLayout *layout;
    GameTab *gameTab;
    PlayersTab *playersTab;
    ArchiveTab *archiveTab;
    ProfileTab *profileTab;
};
#endif // MAINWINDOW_H
