#ifndef GAMETAB_H
#define GAMETAB_H

#include "../Batch/batch.h"

class GameTab: public QObject
{
    Q_OBJECT

//private:
    Batch *batch;

private slots:
    void slot_to_remove_opponent_piece_label(DraggableLabel *);
    void slot_to_promote_pawn(DraggableLabel *, QString &);
    void slot_to_show_move(QString);

signals:
    void signal_to_remove_opponent_piece_label(DraggableLabel *);
    void signal_to_promote_pawn(DraggableLabel *, QString &);
    void signal_to_show_move(QString);

public:
    GameTab(QObject *parent = nullptr) : QObject{parent}
    {
        set_batch();
    }
    ~GameTab()
    {
        end_batch();
    }
    void set_batch();
    Batch *get_batch();
    void end_batch();
};

#endif // GAMETAB_H
