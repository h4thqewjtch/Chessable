#include "gametab.h"

void GameTab::slot_to_remove_opponent_piece_label(DraggableLabel *pieceLabel)
{
    emit signal_to_remove_opponent_piece_label(pieceLabel);
}

Batch *GameTab::get_batch()
{
    return batch;
}
