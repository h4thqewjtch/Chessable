#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMainWindow>
#include <QVBoxLayout>

#include "../GameTab/gametab.h"
#include "../PlayersTab/playerstab.h"
#include "../ArchiveTab/archivetab.h"
#include "../ProfileTab/profiletab.h"

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
    void on_minute1Button_clicked();

    void on_minutes3Button_clicked();

    void on_minutes5Button_clicked();

    void on_minutes10Button_clicked();

    void on_minutes15Button_clicked();

    void on_minutes30Button_clicked();

    void on_playButton_clicked();

    void on_offerADrawButton_clicked();

    void on_giveUpButton_clicked();

    void add_piece_labels();

    void slot_to_remove_opponent_piece_label(DraggableLabel *);

private:
    Ui::MainWindow *ui;

    QVBoxLayout *layout;
    GameTab *gameTab;
    PlayersTab *playersTab;
    ArchiveTab *archiveTab;
    ProfileTab *profileTab;
};
#endif // MAINWINDOW_H
