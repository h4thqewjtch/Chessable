#include "piece.h"

QMap < QPair<int, int>, QPair<DraggableLabel *, QPair<QString, QString>>> Piece::pieces =
    QMap < QPair<int, int>, QPair<DraggableLabel *, QPair<QString, QString>>>();

void Piece::update_piece_position(const QPoint &piecePosition)
{
    int newRanksPosition = piecePosition.x() / piecePixelWidth;
    int newFilesPosition = piecePosition.y() / piecePixelHeight;
    if (pieceType == "pawn")
    {
        pieceLabel->adjust_label_position(update_pawn_position(newRanksPosition, newFilesPosition));
    }
    else if (pieceType == "rook")
    {
        pieceLabel->adjust_label_position(update_rook_position(newRanksPosition, newFilesPosition));
    }
    else if (pieceType == "knight")
    {
        pieceLabel->adjust_label_position(update_knight_position(newRanksPosition, newFilesPosition));
    }
    else if (pieceType == "bishop")
    {
        pieceLabel->adjust_label_position(update_bishop_position(newRanksPosition, newFilesPosition));
    }
    else if (pieceType == "queen")
    {
        pieceLabel->adjust_label_position(update_queen_position(newRanksPosition, newFilesPosition));
    }
    else if (pieceType == "king")
    {
        pieceLabel->adjust_label_position(update_king_position(newRanksPosition, newFilesPosition));
    }
}

QPoint Piece::update_pawn_position(int newRanksPosition, int newFilesPosition)
{
    if ((!pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition))
            && newRanksPosition - ranksPosition == 0
            && ((pieceColor == "WHITE"
                 && ((filesPosition == 6
                      && (newFilesPosition - filesPosition == -2
                          || newFilesPosition - filesPosition == -1))
                     || newFilesPosition - filesPosition == -1))
                || (pieceColor == "BLACK"
                    && ((filesPosition == 1
                         && (newFilesPosition - filesPosition == 2
                             || newFilesPosition - filesPosition == 1))
                        || (newFilesPosition - filesPosition == 1)))))
            || (pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition))
                && pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).second.first != pieceColor
                && (newRanksPosition - ranksPosition == 1
                    || newRanksPosition - ranksPosition == -1)
                && ((pieceColor == "WHITE" && newFilesPosition - filesPosition == -1)
                    || (pieceColor == "BLACK" && newFilesPosition - filesPosition == 1))))
    {
        if (pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition)))
        {
            emit signal_to_remove_opponent_piece_label(pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).first);
        }
        pieces.remove(QPair<int, int>(ranksPosition, filesPosition));
        ranksPosition = newRanksPosition;
        filesPosition = newFilesPosition;
        pieces.insert(QPair<int, int>(ranksPosition, filesPosition),
                      QPair<DraggableLabel *, QPair<QString, QString>> (pieceLabel, QPair<QString, QString>(pieceColor, pieceType)));
    }

    return QPoint(ranksPosition * piecePixelWidth, filesPosition * piecePixelHeight);
}

QPoint Piece::update_rook_position(int newRanksPosition, int newFilesPosition)
{
    int index = 0, limit = -1, j = -1, i = -1;
    if (newRanksPosition == ranksPosition && filesPosition < newFilesPosition)
    {
        index = 1;
        i = initialize(1, filesPosition);
    }
    else if (newRanksPosition == ranksPosition && filesPosition > newFilesPosition)
    {
        index = 2;
        i = initialize(0, filesPosition);
    }
    else if (newFilesPosition == filesPosition && ranksPosition < newRanksPosition)
    {
        index = 3;
        i = initialize(1, ranksPosition);
    }
    else if (newFilesPosition == filesPosition && ranksPosition > newRanksPosition)
    {
        index = 4;
        i = initialize(0, ranksPosition);
    }
    bool error = false;
    if (index > 2)
    {
        limit = newRanksPosition;
        j = newFilesPosition;
    }
    else if (index > 0)
    {
        limit = newFilesPosition;
        j = newRanksPosition;
    }
    else
    {
        error = true;
    }
    while (!error && i != limit)
    {
        if (is_enough(index, i, j))
        {
            error = true;
            break;
        }
        i = change(index, i);
    }
    if (!error && pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).second.first != pieceColor)
    {
        if (pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition)))
        {
            emit signal_to_remove_opponent_piece_label(pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).first);
        }
        pieces.remove(QPair<int, int>(ranksPosition, filesPosition));
        ranksPosition = newRanksPosition;
        filesPosition = newFilesPosition;
        pieces.insert(QPair<int, int>(ranksPosition, filesPosition),
                      QPair<DraggableLabel *, QPair<QString, QString>> (pieceLabel, QPair<QString, QString>(pieceColor, pieceType)));
    }
    return QPoint(ranksPosition * piecePixelWidth, filesPosition * piecePixelHeight);
}

QPoint Piece::update_knight_position(int newRanksPosition, int newFilesPosition)
{
    if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).second.first != pieceColor
            && ((qAbs(newRanksPosition - ranksPosition) == 1 && qAbs(newFilesPosition - filesPosition) == 2)
                || (qAbs(newRanksPosition - ranksPosition) == 2 && qAbs(newFilesPosition - filesPosition) == 1)))
    {
        if (pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition)))
        {
            emit signal_to_remove_opponent_piece_label(pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).first);
        }
        pieces.remove(QPair<int, int>(ranksPosition, filesPosition));
        ranksPosition = newRanksPosition;
        filesPosition = newFilesPosition;
        pieces.insert(QPair<int, int>(ranksPosition, filesPosition),
                      QPair<DraggableLabel *, QPair<QString, QString>> (pieceLabel, QPair<QString, QString>(pieceColor, pieceType)));
    }
    return QPoint(ranksPosition * piecePixelWidth, filesPosition * piecePixelHeight);

}

QPoint Piece::update_bishop_position(int newRanksPosition, int newFilesPosition)
{
    bool error = false;
    int index;
    if (newRanksPosition < ranksPosition && newFilesPosition < filesPosition)
    {
        index = 1;
    }
    else if (newRanksPosition < ranksPosition && newFilesPosition > filesPosition)
    {
        index = 2;
    }
    else if (newRanksPosition > ranksPosition && newFilesPosition < filesPosition)
    {
        index = 3;
    }
    else if (newRanksPosition > ranksPosition && newFilesPosition > filesPosition)
    {
        index = 4;
    }
    else
    {
        error = true;
    }
    int i = initialize(index / 3, ranksPosition);
    int j = initialize((index - 1) % 2, filesPosition);
    if (qAbs(newRanksPosition - ranksPosition) != qAbs(newFilesPosition - filesPosition))
    {
        error = true;
    }
    while (!error && i != newRanksPosition)
    {
        if (is_enough(3, i, j))
        {
            error = true;
            break;
        }
        i = change(index > 2, i);
        j = change(index + 1, j);
    }
    if (!error && pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).second.first != pieceColor)
    {
        if (pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition)))
        {
            emit signal_to_remove_opponent_piece_label(pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).first);
        }
        pieces.remove(QPair<int, int>(ranksPosition, filesPosition));
        ranksPosition = newRanksPosition;
        filesPosition = newFilesPosition;
        pieces.insert(QPair<int, int>(ranksPosition, filesPosition),
                      QPair<DraggableLabel *, QPair<QString, QString>> (pieceLabel, QPair<QString, QString>(pieceColor, pieceType)));
    }
    return QPoint(ranksPosition * piecePixelWidth, filesPosition * piecePixelHeight);
}

QPoint Piece::update_queen_position(int newRanksPosition, int newFilesPosition)
{
    QPoint newPosition = QPoint(ranksPosition * piecePixelWidth, filesPosition * piecePixelHeight);
    if (newRanksPosition == ranksPosition
            || newFilesPosition == filesPosition)
    {
        newPosition = update_rook_position(newRanksPosition, newFilesPosition);
    }
    else if (qAbs(newRanksPosition - ranksPosition) == qAbs(newFilesPosition - filesPosition))
    {
        newPosition = update_bishop_position(newRanksPosition, newFilesPosition);
    }
    return newPosition;
}

QPoint Piece::update_king_position(int newRanksPosition, int newFilesPosition)
{
    QPoint newPosition = QPoint(ranksPosition * piecePixelWidth, filesPosition * piecePixelHeight);
    if ((newRanksPosition == ranksPosition && qAbs(newFilesPosition - filesPosition) == 1)
            || (newFilesPosition == filesPosition && qAbs(newRanksPosition - ranksPosition) == 1))
    {
        newPosition = update_rook_position(newRanksPosition, newFilesPosition);
    }
    else if (qAbs(newRanksPosition - ranksPosition) == 1 && qAbs(newFilesPosition - filesPosition) == 1)
    {
        newPosition = update_bishop_position(newRanksPosition, newFilesPosition);
    }
    return newPosition;
}

int Piece::initialize(int index, int number)
{
    int result;
    if (index % 2)
    {
        result = number + 1;
    }
    else
    {
        result = number - 1;
    }
    return result;
}

bool Piece::is_enough(int index, int i, int j)
{
    bool is_enough = false;
    switch (index)
    {
        case 1:
            is_enough = pieces.contains(QPair<int, int>(j, i));
            break;
        case 2:
            is_enough = pieces.contains(QPair<int, int>(j, i));
            break;
        case 3:
            is_enough = pieces.contains(QPair<int, int>(i, j));
            break;
        case 4:
            is_enough = pieces.contains(QPair<int, int>(i, j));
            break;
    }
    return is_enough;
}

int Piece::change(int index, int i)
{
    if (index % 2)
    {
        i++;
    }
    else
    {
        i--;
    }
    return i;
}

DraggableLabel *Piece::get_piece_label()
{
    return pieceLabel;
}
