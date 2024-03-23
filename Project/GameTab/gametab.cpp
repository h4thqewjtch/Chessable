#include "gametab.h"

void GameTab::slot_to_remove_opponent_piece_label(DraggableLabel *pieceLabel)
{
    emit signal_to_remove_opponent_piece_label(pieceLabel);
}

void GameTab::slot_to_promote_pawn(DraggableLabel *pieceLabel, QString &pieceColor)
{
    emit signal_to_promote_pawn(pieceLabel, pieceColor);
}

void GameTab::slot_to_show_move(QString currentMoveRecord, int superiority, QPair<QPoint, QPoint> currentMove)
{
    emit signal_to_show_move(currentMoveRecord, superiority, currentMove);
}

void GameTab::set_batch()
{
    batch = new Batch();

    connect(batch, &Batch::signal_to_remove_opponent_piece_label, this, &GameTab::slot_to_remove_opponent_piece_label);
    connect(batch, &Batch::signal_to_promote_pawn, this, &GameTab::slot_to_promote_pawn);
    connect(batch, &Batch::signal_to_show_move, this, &GameTab::slot_to_show_move);
}

Batch *GameTab::get_batch()
{
    return batch;
}

void GameTab::end_batch()
{
    delete batch;
}
