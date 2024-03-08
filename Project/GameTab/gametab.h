#ifndef GAMETAB_H
#define GAMETAB_H

#include "../Batch/batch.h"

class GameTab: public QObject
{
    Q_OBJECT

private:
    Batch *batch;

private slots:
    void slot_to_remove_opponent_piece_label(DraggableLabel *);

signals:
    void signal_to_remove_opponent_piece_label(DraggableLabel *);

public:
    GameTab(QObject *parent = nullptr) : QObject{parent}
    {
        batch = new Batch();

        connect(batch, &Batch::signal_to_remove_opponent_piece_label, this, &GameTab::slot_to_remove_opponent_piece_label);
    }
    Batch *get_batch();
};

#endif // GAMETAB_H
