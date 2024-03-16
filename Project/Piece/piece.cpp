#include "piece.h"

QString Piece::currentSideToMove = "WHITE";

QMap<QPair<int, int>, PieceInfo> Piece::pieces;

QMap<int, int> Piece::existWhitePiecesMap;

QMap<int, int> Piece::existBlackPiecesMap;

QPair<int, int> Piece::blackKingPosition = QPair<int, int>(-1, -1);

QPair<int, int> Piece::whiteKingPosition = QPair<int, int>(-1, -1);

QPair<int, int> Piece::enPassantPawnPosition = QPair<int, int>(-1, -1);

QList<QString> Piece::movesList;

//int Piece::superiority = 0;


void Piece::initialize_piece_info(int ranksPosition = 0, int filesPosition = 0, QString pieceColor = "", QString pieceType = "")
{
    pieceInfo.pixelWidth = 64;
    pieceInfo.pixelHeight = 64;
    pieceInfo.ranksPosition = ranksPosition;
    pieceInfo.filesPosition = filesPosition;
    pieceInfo.color = pieceColor;
    pieceInfo.type = pieceType;
    if (pieceType == "pawn")
    {
        pieceColor == "WHITE" ? existWhitePiecesMap[1]++ : existBlackPiecesMap[1]++;
        pieceInfo.readyToCastling = false;
    }
    else if (pieceType == "knight")
    {
        pieceColor == "WHITE" ? existWhitePiecesMap[3]++ : existBlackPiecesMap[3]++;
        pieceInfo.readyToCastling = false;
    }
    else if (pieceType == "bishop")
    {
        pieceColor == "WHITE" ? existWhitePiecesMap[3]++ : existBlackPiecesMap[3]++;
        pieceInfo.readyToCastling = false;
    }
    else if (pieceType == "rook")
    {
        pieceColor == "WHITE" ? existWhitePiecesMap[5]++ : existBlackPiecesMap[5]++;
        pieceInfo.readyToCastling = true;
    }
    else if (pieceType == "queen")
    {
        pieceColor == "WHITE" ? existWhitePiecesMap[9]++ : existBlackPiecesMap[9]++;
        pieceInfo.readyToCastling = false;
    }
    else if (pieceType == "king")
    {
        pieceColor == "WHITE" ? existWhitePiecesMap[0]++ : existBlackPiecesMap[0]++;
        pieceColor == "WHITE" ? whiteKingPosition = QPair<int, int>(ranksPosition, filesPosition) : blackKingPosition = QPair<int, int>(ranksPosition, filesPosition);
        pieceInfo.readyToCastling = true;
    }
    pieceInfo.label = new DraggableLabel();
}

void Piece::set_piece_label(QString imagePath = "")
{
    QPixmap piecePix(imagePath);
    pieceInfo.label->setPixmap(piecePix.scaled(pieceInfo.pixelWidth, pieceInfo.pixelHeight, Qt::KeepAspectRatio));
    pieceInfo.label->setGeometry(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight, pieceInfo.pixelWidth, pieceInfo.pixelHeight);
}

void Piece::update_piece_position(const QPoint &piecePosition)
{
    QPoint newPiecePosition = piecePosition;
    set_piece_position(newPiecePosition);
    pieceInfo.label->update_label_position(newPiecePosition);
}

void Piece::set_piece_position(QPoint &newPiecePosition)
{
    QPoint currentPiecePosition = QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
    int newRanksPosition = newPiecePosition.x() / pieceInfo.pixelWidth;
    int newFilesPosition = newPiecePosition.y() / pieceInfo.pixelHeight;
    newPiecePosition = QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
    QMap <QPair<int, int>, PieceInfo> futurePieces = pieces;
    futurePieces.remove(QPair<int, int> (pieceInfo.ranksPosition, pieceInfo.filesPosition));
    futurePieces.insert(QPair<int, int> (newRanksPosition, newFilesPosition), pieceInfo);
    QPair<int, int> futureWhiteKingPosition = whiteKingPosition;
    QPair<int, int> futureBlackKingPosition = blackKingPosition;
    if (pieceInfo.type == "king")
    {
        pieceInfo.color == "WHITE" ? futureWhiteKingPosition = QPair<int, int>(newRanksPosition, newFilesPosition)
            : futureBlackKingPosition = QPair<int, int>(newRanksPosition, newFilesPosition);
    }
    QPair<int, int> checkToWhitePosition = find_check_to(futureWhiteKingPosition, "WHITE", futurePieces);
    QPair<int, int> checkToBlackPosition = find_check_to(futureBlackKingPosition, "BLACK", futurePieces);
    if (pieceInfo.color == currentSideToMove
            && ((pieceInfo.color == "WHITE"
                 && checkToWhitePosition == QPair<int, int>(-1, -1))
                || (pieceInfo.color == "BLACK"
                    && checkToBlackPosition == QPair<int, int>(-1, -1))))
    {
        if (pieces.contains(enPassantPawnPosition)
                && pieces.value(enPassantPawnPosition).color == currentSideToMove)
        {
            enPassantPawnPosition = QPair<int, int> (-1, -1);
        }
        if (pieceInfo.type == "pawn")
        {
            QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
            QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
            currentMove = rank + file;

            newPiecePosition = update_pawn_position(newRanksPosition, newFilesPosition);

            if (!currentMove.contains("x"))
            {
                QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
                QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
                currentMove += "-" + rank + file;
            }

            if (newPiecePosition != currentPiecePosition
                    && is_pawn_on_promotion_field(newPiecePosition.y()))
            {
                QPoint pos = QPoint(newRanksPosition, newFilesPosition);
                emit signal_to_promote_pawn(pieceInfo.label, pos, pieceInfo.color);
                checkToWhitePosition = find_check_to(futureWhiteKingPosition, "WHITE", pieces);
                checkToBlackPosition = find_check_to(futureBlackKingPosition, "BLACK", pieces);
            }

        }
        else if (pieceInfo.type == "rook")
        {
            QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
            QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
            currentMove = "R" + rank + file;

            newPiecePosition = update_rook_position(newRanksPosition, newFilesPosition);

            if (!currentMove.contains("x"))
            {
                QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
                QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
                currentMove += "-R" + rank + file;
            }
        }
        else if (pieceInfo.type == "knight")
        {
            QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
            QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
            currentMove = "N" + rank + file;

            newPiecePosition = update_knight_position(newRanksPosition, newFilesPosition);

            if (!currentMove.contains("x"))
            {
                QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
                QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
                currentMove += "-N" + rank + file;
            }
        }
        else if (pieceInfo.type == "bishop")
        {
            QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
            QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
            currentMove = "B" + rank + file;

            newPiecePosition = update_bishop_position(newRanksPosition, newFilesPosition);

            if (!currentMove.contains("x"))
            {
                QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
                QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
                currentMove += "-B" + rank + file;
            }
        }
        else if (pieceInfo.type == "queen")
        {
            QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
            QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
            currentMove = "Q" + rank + file;

            newPiecePosition = update_queen_position(newRanksPosition, newFilesPosition);

            if (!currentMove.contains("x"))
            {
                QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
                QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
                currentMove += "-Q" + rank + file;
            }
        }
        else if (pieceInfo.type == "king")
        {
            QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
            QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
            currentMove = "K" + rank + file;

            if ((pieceInfo.color == "WHITE"
                    && (qAbs(newRanksPosition - blackKingPosition.first) > 1
                        || qAbs(newFilesPosition - blackKingPosition.second) > 1))
                    || (pieceInfo.color == "BLACK"
                        && (qAbs(newRanksPosition - whiteKingPosition.first) > 1
                            || qAbs(newFilesPosition - whiteKingPosition.second) > 1)))
            {
                if (pieces.value(QPair<int, int>(pieceInfo.ranksPosition, pieceInfo.filesPosition)).readyToCastling)
                {
                    if (find_check_to(whiteKingPosition, "WHITE", pieces) == QPair<int, int> (-1, -1)
                            && find_check_to(blackKingPosition, "BLACK", pieces) == QPair<int, int>(-1, -1))
                    {
                        newPiecePosition = try_to_castling(currentPiecePosition, newRanksPosition, newFilesPosition);
                    }
                }
                if (newPiecePosition == currentPiecePosition)
                {
                    newPiecePosition = update_king_position(newRanksPosition, newFilesPosition);
                }
            }

            if (!currentMove.contains("x"))
            {
                QString rank = set_rank_letter_from(pieceInfo.ranksPosition);
                QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
                currentMove += "-K" + rank + file;
            }

            if (newPiecePosition != currentPiecePosition)
            {
                pieceInfo.color == "WHITE" ? whiteKingPosition = QPair<int, int>(newRanksPosition, newFilesPosition)
                    : blackKingPosition = QPair<int, int>(newRanksPosition, newFilesPosition);
            }

        }
        if (newPiecePosition != currentPiecePosition)
        {
            currentSideToMove == "WHITE" ? currentSideToMove = "BLACK" : currentSideToMove = "WHITE";
        }
    }
    if (newPiecePosition != currentPiecePosition)
    {
        movesList.append(currentMove);
    }
    if (checkToWhitePosition != QPair<int, int>(-1, -1))
    {
        qDebug() << "CHECK TO WHITE\n";
        if (is_checkmate_to(whiteKingPosition, checkToWhitePosition))
        {
            qDebug() << "CHECKMATE TO WHITE\n";
            movesList[movesList.size() - 1] += "#";
        }
        else
        {
            movesList[movesList.size() - 1] += "+";
        }
    }
    else if (checkToBlackPosition != QPair<int, int>(-1, -1))
    {
        qDebug() << "CHECK TO BLACK\n";
        if (is_checkmate_to(blackKingPosition, checkToBlackPosition))
        {
            qDebug() << "CHECKMATE TO BLACK\n";
            movesList[movesList.size() - 1] += "#";
        }
        else
        {
            movesList[movesList.size() - 1] += "+";
        }
    }
    else if ((!existWhitePiecesMap[1]
              && existWhitePiecesMap[3] < 2
              && !existWhitePiecesMap[5]
              && !existWhitePiecesMap[9]
              && !existBlackPiecesMap[1]
              && existBlackPiecesMap[3] < 2
              && !existBlackPiecesMap[5]
              && !existBlackPiecesMap[9])
             || (movesList.size() > 8
                 && movesList[movesList.size() - 1] == movesList[movesList.size() - 5]
                 && movesList[movesList.size() - 2] == movesList[movesList.size() - 6]
                 && movesList[movesList.size() - 3] == movesList[movesList.size() - 7]
                 && movesList[movesList.size() - 4] == movesList[movesList.size() - 8]
                 && movesList[movesList.size() - 1] == movesList[movesList.size() - 9]))
    {
        qDebug() << "DRAW\n";
        movesList[movesList.size() - 1] += "=";
    }
    if (newPiecePosition != currentPiecePosition)
    {
        //qDebug() << movesList;
        QString move;
        if (currentSideToMove == "BLACK")
        {
            move += QString::number(movesList.size() / 2 + 1) + ". ";
        }
        move += movesList[movesList.size() - 1];
        emit signal_to_show_move(move);
    }

}


QPair<int, int> Piece::find_check_to(QPair<int, int> kingPosition, QString kingColor, QMap <QPair<int, int>, PieceInfo> &futurePieces)
{
    QPair<int, int> checkPosition = QPair<int, int>(-1, -1);
    checkPosition = check_rook_moves(kingPosition, kingColor, futurePieces);
    if (checkPosition == QPair<int, int>(-1, -1))
    {
        checkPosition = check_bishop_moves(kingPosition, kingColor, futurePieces);
        if (checkPosition == QPair<int, int>(-1, -1))
        {
            checkPosition = check_knight_moves(kingPosition, kingColor, futurePieces);
        }
    }
    return checkPosition;
}

QPair<int, int> Piece::check_rook_moves(QPair<int, int> kingPosition, QString kingColor, QMap <QPair<int, int>, PieceInfo> &futurePieces)
{

    QPair<int, int> checkPosition = QPair<int, int> (-1, -1);
    int i = kingPosition.first - 1;
    int j = kingPosition.second;
    while (checkPosition == QPair<int, int> (-1, -1) && i != -1)
    {
        checkPosition = check_space_on(kingPosition, QPair<int, int>(i, j), kingColor, "queen", "rook", futurePieces);
        i = change(0, i);
    }
    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    i = kingPosition.first;
    j = kingPosition.second - 1;
    while (checkPosition == QPair<int, int> (-1, -1) && j != -1)
    {
        checkPosition = check_space_on(kingPosition, QPair<int, int>(i, j), kingColor, "queen", "rook", futurePieces);
        j = change(0, j);
    }
    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    i = kingPosition.first + 1;
    j = kingPosition.second;
    while (checkPosition == QPair<int, int> (-1, -1) && i != 8)
    {

        checkPosition = check_space_on(kingPosition, QPair<int, int>(i, j), kingColor, "queen", "rook", futurePieces);
        i = change(1, i);
    }

    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    i = kingPosition.first;
    j = kingPosition.second + 1;
    while (checkPosition == QPair<int, int> (-1, -1) && j != 8)
    {

        checkPosition = check_space_on(kingPosition, QPair<int, int>(i, j), kingColor, "queen", "rook", futurePieces);
        j = change(1, j);
    }

    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    return checkPosition;
}

QPair<int, int> Piece::check_bishop_moves(QPair<int, int> kingPosition, QString kingColor, QMap <QPair<int, int>, PieceInfo> &futurePieces)
{
    QPair<int, int> checkPosition = QPair<int, int> (-1, -1);
    int i = kingPosition.first - 1;
    int j = kingPosition.second - 1;
    while (checkPosition == QPair<int, int> (-1, -1) && i != -1 && j != -1)
    {
        checkPosition = check_space_on(kingPosition, QPair<int, int>(i, j), kingColor, "queen", "bishop", futurePieces);
        i = change(0, i);
        j = change(0, j);
    }
    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    i = kingPosition.first + 1;
    j = kingPosition.second - 1;
    while (checkPosition == QPair<int, int> (-1, -1) && i != 8 && j != -1)
    {
        checkPosition = check_space_on(kingPosition, QPair<int, int>(i, j), kingColor, "queen", "bishop", futurePieces);
        i = change(1, i);
        j = change(0, j);
    }
    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    i = kingPosition.first + 1;
    j = kingPosition.second + 1;
    while (checkPosition == QPair<int, int> (-1, -1) && i != 8 && j != 8)
    {
        checkPosition = check_space_on(kingPosition, QPair<int, int>(i, j), kingColor, "queen", "bishop", futurePieces);
        i = change(1, i);
        j = change(1, j);
    }
    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    i = kingPosition.first - 1;
    j = kingPosition.second + 1;
    while (checkPosition == QPair<int, int> (-1, -1) && i != -1 && j != 8)
    {
        checkPosition = check_space_on(kingPosition, QPair<int, int>(i, j), kingColor, "queen", "bishop", futurePieces);
        i = change(0, i);
        j = change(1, j);
    }
    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    return checkPosition;
}

QPair<int, int> Piece::check_knight_moves(QPair<int, int> kingPosition, QString kingColor, QMap <QPair<int, int>, PieceInfo> &futurePieces)
{
    QPair<int, int> checkPosition = QPair<int, int> (-1, -1);
    checkPosition = check_space_on(kingPosition, QPair<int, int>(kingPosition.first - 2, kingPosition.second - 1), kingColor, "knight", "knight", futurePieces);
    if (checkPosition == QPair<int, int>(8, 8))
    {
        checkPosition = QPair<int, int> (-1, -1);
    }
    if (checkPosition == QPair<int, int> (-1, -1))
    {
        checkPosition = check_space_on(kingPosition, QPair<int, int>(kingPosition.first - 1, kingPosition.second - 2), kingColor, "knight", "knight", futurePieces);
        if (checkPosition == QPair<int, int>(8, 8))
        {
            checkPosition = QPair<int, int> (-1, -1);
        }
        if (checkPosition == QPair<int, int> (-1, -1))
        {
            checkPosition = check_space_on(kingPosition, QPair<int, int>(kingPosition.first + 1, kingPosition.second - 2), kingColor, "knight", "knight", futurePieces);
            if (checkPosition == QPair<int, int>(8, 8))
            {
                checkPosition = QPair<int, int> (-1, -1);
            }
            if (checkPosition == QPair<int, int> (-1, -1))
            {
                checkPosition = check_space_on(kingPosition, QPair<int, int>(kingPosition.first + 2, kingPosition.second - 1), kingColor, "knight", "knight", futurePieces);
                if (checkPosition == QPair<int, int>(8, 8))
                {
                    checkPosition = QPair<int, int> (-1, -1);
                }
                if (checkPosition == QPair<int, int> (-1, -1))
                {
                    checkPosition = check_space_on(kingPosition, QPair<int, int>(kingPosition.first + 2, kingPosition.second + 1), kingColor, "knight", "knight", futurePieces);
                    if (checkPosition == QPair<int, int>(8, 8))
                    {
                        checkPosition = QPair<int, int> (-1, -1);
                    }
                    if (checkPosition == QPair<int, int> (-1, -1))
                    {
                        checkPosition = check_space_on(kingPosition, QPair<int, int>(kingPosition.first + 1, kingPosition.second + 2), kingColor, "knight", "knight", futurePieces);
                        if (checkPosition == QPair<int, int>(8, 8))
                        {
                            checkPosition = QPair<int, int> (-1, -1);
                        }
                        if (checkPosition == QPair<int, int> (-1, -1))
                        {
                            checkPosition = check_space_on(kingPosition, QPair<int, int>(kingPosition.first - 1, kingPosition.second + 2), kingColor, "knight", "knight", futurePieces);
                            if (checkPosition == QPair<int, int>(8, 8))
                            {
                                checkPosition = QPair<int, int> (-1, -1);
                            }
                            if (checkPosition == QPair<int, int> (-1, -1))
                            {
                                checkPosition = check_space_on(kingPosition, QPair<int, int>(kingPosition.first - 2, kingPosition.second + 1), kingColor, "knight", "knight", futurePieces);
                                if (checkPosition == QPair<int, int>(8, 8))
                                {
                                    checkPosition = QPair<int, int> (-1, -1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return checkPosition;
}

QPair<int, int> Piece::check_space_on(QPair<int, int> kingPosition, QPair<int, int> possibleEnemyPosition, QString kingColor, QString pieceType1, QString pieceType2, QMap <QPair<int, int>, PieceInfo> &futurePieces)
{
    QPair<int, int> checkPosition = QPair<int, int> (-1, -1);

    if (futurePieces.value(possibleEnemyPosition).color == kingColor)
    {
        checkPosition = QPair<int, int>(8, 8);
    }
    else if (futurePieces.contains(possibleEnemyPosition)
             && futurePieces.value(possibleEnemyPosition).color != kingColor)
    {
        if (futurePieces.value(possibleEnemyPosition).type == pieceType1
                || futurePieces.value(possibleEnemyPosition).type == pieceType2
                || (futurePieces.value(possibleEnemyPosition).type == "pawn"
                    && ((kingColor == "WHITE"
                         && (possibleEnemyPosition.first == kingPosition.first - 1
                             || possibleEnemyPosition.first == kingPosition.first + 1)
                         && possibleEnemyPosition.second == kingPosition.second - 1)
                        || (kingColor == "BLACK"
                            && (possibleEnemyPosition.first == kingPosition.first - 1
                                || possibleEnemyPosition.first == kingPosition.first + 1)
                            && possibleEnemyPosition.second == kingPosition.second + 1))))
        {
            checkPosition = possibleEnemyPosition;
        }
        else
        {

            checkPosition = QPair<int, int>(8, 8);
        }
    }

    return checkPosition;
}


bool Piece::is_checkmate_to(QPair<int, int> kingPosition, QPair<int, int> checkPosition)
{
    int ranksDirection = checkPosition.first - kingPosition.first;
    int filesDirection = checkPosition.second - kingPosition.second;
    QPair<int, int> direction = QPair<int, int>(ranksDirection, filesDirection);
    QPair<int, int> spaces = get_checkmate_direction_from(direction, kingPosition);
    bool can_king_move = check_king_moves(kingPosition);
    //qDebug() << "can_king_move" << can_king_move;
    return (get_checkmate_position(spaces, kingPosition, checkPosition) == QPair<int, int>(-1, -1) && can_king_move == false);
}

QPair<int, int> Piece::get_checkmate_direction_from(QPair<int, int> direction, QPair<int, int> kingPosition)
{
    int ranksDirection = direction.first;
    int filesDirection = direction.second;
    int ranksPosition, filesPosition;
    if (ranksDirection < 0)
    {
        ranksPosition = kingPosition.first - 1;
    }
    else if (ranksDirection > 0)
    {
        ranksPosition = kingPosition.first + 1;
    }
    else
    {
        ranksPosition = kingPosition.first;
    }
    if (filesDirection < 0)
    {
        filesPosition = kingPosition.second - 1;
    }
    else if (filesDirection > 0)
    {
        filesPosition = kingPosition.second + 1;
    }
    else
    {
        filesPosition = kingPosition.second;
    }
    return QPair<int, int>(ranksPosition, filesPosition);
}

QPair<int, int> Piece::get_checkmate_position(QPair<int, int> spaces, QPair<int, int> kingPosition,  QPair<int, int> checkPosition)
{
    QString pieceColor;
    pieces.value(kingPosition).color == "WHITE" ? pieceColor = "BLACK" : pieceColor = "WHITE";
    int ranksPosition = spaces.first;
    int filesPosition = spaces.second;
    QPair<int, int> check = QPair<int, int>(-1, -1);
    if (ranksPosition < kingPosition.first)
    {
        if (filesPosition < kingPosition.second)
        {
            while (check == QPair<int, int>(-1, -1)
                    && ranksPosition != checkPosition.first - 1
                    && filesPosition != checkPosition.second - 1)
            {
                check = find_check_to(QPair<int, int>(ranksPosition, filesPosition), pieceColor, pieces);
                ranksPosition = initialize(0, ranksPosition);
                filesPosition = initialize(0, filesPosition);
            }
        }
        else if (filesPosition > kingPosition.second)
        {
            while (check == QPair<int, int>(-1, -1)
                    && ranksPosition != checkPosition.first - 1
                    && filesPosition != checkPosition.second + 1)
            {
                check = find_check_to(QPair<int, int>(ranksPosition, filesPosition), pieceColor, pieces);
                ranksPosition = initialize(0, ranksPosition);
                filesPosition = initialize(1, filesPosition);
            }
        }
        else
        {
            while (check == QPair<int, int>(-1, -1)
                    && ranksPosition != checkPosition.first - 1)
            {
                check = find_check_to(QPair<int, int>(ranksPosition, filesPosition), pieceColor, pieces);
                ranksPosition = initialize(0, ranksPosition);
            }
        }
    }
    else if (ranksPosition > kingPosition.first)
    {
        if (filesPosition < kingPosition.second)
        {
            while (check == QPair<int, int>(-1, -1)
                    && ranksPosition != checkPosition.first + 1
                    && filesPosition != checkPosition.second - 1)
            {
                check =  find_check_to(QPair<int, int>(ranksPosition, filesPosition), pieceColor, pieces);
                ranksPosition = initialize(1, ranksPosition);
                filesPosition = initialize(0, filesPosition);
            }
        }
        else if (filesPosition > kingPosition.second)
        {
            while (check == QPair<int, int>(-1, -1)
                    && ranksPosition != checkPosition.first + 1
                    && filesPosition != checkPosition.second + 1)
            {
                check =  find_check_to(QPair<int, int>(ranksPosition, filesPosition), pieceColor, pieces);
                ranksPosition = initialize(1, ranksPosition);
                filesPosition = initialize(1, filesPosition);
            }
        }
        else
        {
            while (check == QPair<int, int>(-1, -1)
                    && ranksPosition != checkPosition.first + 1)
            {
                check = find_check_to(QPair<int, int>(ranksPosition, filesPosition), pieceColor, pieces);
                ranksPosition = initialize(1, ranksPosition);
            }
        }
    }
    else
    {
        if (filesPosition < kingPosition.second)
        {
            while (check == QPair<int, int>(-1, -1)
                    && filesPosition != checkPosition.second - 1)
            {
                check = find_check_to(QPair<int, int>(ranksPosition, filesPosition), pieceColor, pieces);
                filesPosition = initialize(0, filesPosition);
            }
        }
        else if (filesPosition > kingPosition.second)
        {
            while (check == QPair<int, int>(-1, -1)
                    && filesPosition != checkPosition.second + 1)
            {
                check = find_check_to(QPair<int, int>(ranksPosition, filesPosition), pieceColor, pieces);
                filesPosition = initialize(1, filesPosition);
            }
        }
    }

    return check;
}

bool Piece::check_king_moves(QPair<int, int> kingPosition)
{
    QMap <QPair<int, int>, PieceInfo> futurePieces = pieces;
    QPair<int, int> futureKingPosition = QPair<int, int>(-1, -1);
    QPair<int, int> check = QPair<int, int> (-1, -1);
    if (kingPosition.first != 0 && kingPosition.second != 0
            && futurePieces.value(QPair<int, int>(kingPosition.first - 1, kingPosition.second - 1)).color != pieces.value(kingPosition).color
            && ((pieces[kingPosition].color == "WHITE"
                 && (qAbs(kingPosition.first - 1 - blackKingPosition.first) > 1
                     || qAbs(kingPosition.second - 1 - blackKingPosition.second) > 1))
                || (pieces[kingPosition].color == "BLACK"
                    && (qAbs(kingPosition.first - 1 - whiteKingPosition.first) > 1
                        || qAbs(kingPosition.second - 1 - whiteKingPosition.second) > 1))))
    {
        futureKingPosition = QPair<int, int>(kingPosition.first - 1, kingPosition.second - 1);
        futurePieces.remove(kingPosition);
        PieceInfo possiblePieceInfo = {0, 0, nullptr, 0, 0, "", "", false};
        if (futurePieces.contains(futureKingPosition))
        {
            possiblePieceInfo = futurePieces[futureKingPosition];
        }
        futurePieces.insert(futureKingPosition, pieces.value(kingPosition));
        QString kingColor = futurePieces.value(futureKingPosition).color;
        check = find_check_to(futureKingPosition, kingColor, futurePieces);
        if (check == QPair<int, int> (-1, -1))
        {
            return true;
        }
        if (possiblePieceInfo.type != "")
        {
            futurePieces.insert(futureKingPosition, possiblePieceInfo);
        }
        else
        {
            futurePieces.remove(futureKingPosition);
        }
        futurePieces.insert(kingPosition, pieces.value(kingPosition));
    }
    if (kingPosition.first != 0
            && futurePieces.value(QPair<int, int>(kingPosition.first - 1, kingPosition.second)).color != pieces.value(kingPosition).color
            && ((pieces[kingPosition].color == "WHITE"
                 && (qAbs(kingPosition.first - 1 - blackKingPosition.first) > 1
                     || qAbs(kingPosition.second - blackKingPosition.second) > 1))
                || (pieces[kingPosition].color == "BLACK"
                    && (qAbs(kingPosition.first - 1 - whiteKingPosition.first) > 1
                        || qAbs(kingPosition.second - whiteKingPosition.second) > 1))))
    {
        //
        futureKingPosition = QPair<int, int>(kingPosition.first - 1, kingPosition.second);
        futurePieces.remove(kingPosition);
        PieceInfo possiblePieceInfo = {0, 0, nullptr, 0, 0, "", "", false};
        if (futurePieces.contains(futureKingPosition))
        {
            possiblePieceInfo = futurePieces[futureKingPosition];
        }
        futurePieces.insert(futureKingPosition, pieces.value(kingPosition));
        QString kingColor = futurePieces.value(futureKingPosition).color;
        check = find_check_to(futureKingPosition, kingColor, futurePieces);
        if (check == QPair<int, int> (-1, -1))
        {

            return true;
        }
        if (possiblePieceInfo.type != "")
        {
            futurePieces.insert(futureKingPosition, possiblePieceInfo);
        }
        else
        {
            futurePieces.remove(futureKingPosition);
        }
        futurePieces.insert(kingPosition, pieces.value(kingPosition));
    }
    if (kingPosition.first != 0 && kingPosition.second != 7
            && futurePieces.value(QPair<int, int>(kingPosition.first - 1, kingPosition.second + 1)).color != pieces.value(kingPosition).color
            && ((pieces[kingPosition].color == "WHITE"
                 && (qAbs(kingPosition.first - 1 - blackKingPosition.first) > 1
                     || qAbs(kingPosition.second + 1 - blackKingPosition.second) > 1))
                || (pieces[kingPosition].color == "BLACK"
                    && (qAbs(kingPosition.first - 1 - whiteKingPosition.first) > 1
                        || qAbs(kingPosition.second + 1 - whiteKingPosition.second) > 1))))
    {
        futureKingPosition = QPair<int, int>(kingPosition.first - 1, kingPosition.second + 1);
        futurePieces.remove(kingPosition);
        PieceInfo possiblePieceInfo = {0, 0, nullptr, 0, 0, "", "", false};
        if (futurePieces.contains(futureKingPosition))
        {
            possiblePieceInfo = futurePieces[futureKingPosition];
        }
        futurePieces.insert(futureKingPosition, pieces.value(kingPosition));
        QString kingColor = futurePieces.value(futureKingPosition).color;
        check = find_check_to(futureKingPosition, kingColor, futurePieces);
        if (check == QPair<int, int> (-1, -1))
        {

            return true;
        }
        if (possiblePieceInfo.type != "")
        {
            futurePieces.insert(futureKingPosition, possiblePieceInfo);
        }
        else
        {
            futurePieces.remove(futureKingPosition);
        }
        futurePieces.insert(kingPosition, pieces.value(kingPosition));
    }
    if (kingPosition.second != 7
            && futurePieces.value(QPair<int, int>(kingPosition.first, kingPosition.second + 1)).color != pieces.value(kingPosition).color
            && ((pieces[kingPosition].color == "WHITE"
                 && (qAbs(kingPosition.first - blackKingPosition.first) > 1
                     || qAbs(kingPosition.second + 1 - blackKingPosition.second) > 1))
                || (pieces[kingPosition].color == "BLACK"
                    && (qAbs(kingPosition.first - whiteKingPosition.first) > 1
                        || qAbs(kingPosition.second + 1 - whiteKingPosition.second) > 1))))
    {
        futureKingPosition = QPair<int, int>(kingPosition.first, kingPosition.second + 1);
        futurePieces.remove(kingPosition);
        PieceInfo possiblePieceInfo = {0, 0, nullptr, 0, 0, "", "", false};
        if (futurePieces.contains(futureKingPosition))
        {
            possiblePieceInfo = futurePieces[futureKingPosition];
        }
        futurePieces.insert(futureKingPosition, pieces.value(kingPosition));
        QString kingColor = futurePieces.value(futureKingPosition).color;
        check = find_check_to(futureKingPosition, kingColor, futurePieces);
        if (check == QPair<int, int> (-1, -1))
        {

            return true;
        }
        if (possiblePieceInfo.type != "")
        {
            futurePieces.insert(futureKingPosition, possiblePieceInfo);
        }
        else
        {
            futurePieces.remove(futureKingPosition);
        }
        futurePieces.insert(kingPosition, pieces.value(kingPosition));
    }
    if (kingPosition.first != 7 && kingPosition.second != 7
            && futurePieces.value(QPair<int, int>(kingPosition.first + 1, kingPosition.second + 1)).color != pieces.value(kingPosition).color
            && ((pieces[kingPosition].color == "WHITE"
                 && (qAbs(kingPosition.first + 1 - blackKingPosition.first) > 1
                     || qAbs(kingPosition.second + 1 - blackKingPosition.second) > 1))
                || (pieces[kingPosition].color == "BLACK"
                    && (qAbs(kingPosition.first + 1 - whiteKingPosition.first) > 1
                        || qAbs(kingPosition.second + 1 - whiteKingPosition.second) > 1))))
    {
        futureKingPosition = QPair<int, int>(kingPosition.first + 1, kingPosition.second + 1);
        futurePieces.remove(kingPosition);
        PieceInfo possiblePieceInfo = {0, 0, nullptr, 0, 0, "", "", false};
        if (futurePieces.contains(futureKingPosition))
        {
            possiblePieceInfo = futurePieces[futureKingPosition];
        }
        futurePieces.insert(futureKingPosition, pieces.value(kingPosition));
        QString kingColor = futurePieces.value(futureKingPosition).color;
        check = find_check_to(futureKingPosition, kingColor, futurePieces);
        if (check == QPair<int, int> (-1, -1))
        {

            return true;
        }
        if (possiblePieceInfo.type != "")
        {
            futurePieces.insert(futureKingPosition, possiblePieceInfo);
        }
        else
        {
            futurePieces.remove(futureKingPosition);
        }
        futurePieces.insert(kingPosition, pieces.value(kingPosition));
    }
    if (kingPosition.first != 7
            && futurePieces.value(QPair<int, int>(kingPosition.first + 1, kingPosition.second)).color != pieces.value(kingPosition).color
            && ((pieces[kingPosition].color == "WHITE"
                 && (qAbs(kingPosition.first + 1 - blackKingPosition.first) > 1
                     || qAbs(kingPosition.second - blackKingPosition.second) > 1))
                || (pieces[kingPosition].color == "BLACK"
                    && (qAbs(kingPosition.first + 1 - whiteKingPosition.first) > 1
                        || qAbs(kingPosition.second - whiteKingPosition.second) > 1))))
    {

        futureKingPosition = QPair<int, int>(kingPosition.first + 1, kingPosition.second);
        futurePieces.remove(kingPosition);
        PieceInfo possiblePieceInfo = {0, 0, nullptr, 0, 0, "", "", false};
        if (futurePieces.contains(futureKingPosition))
        {
            possiblePieceInfo = futurePieces[futureKingPosition];
        }
        futurePieces.insert(futureKingPosition, pieces.value(kingPosition));
        QString kingColor = futurePieces.value(futureKingPosition).color;

        check = find_check_to(futureKingPosition, kingColor, futurePieces);
        if (check == QPair<int, int> (-1, -1))
        {
            return true;
        }
        if (possiblePieceInfo.type != "")
        {
            futurePieces.insert(futureKingPosition, possiblePieceInfo);
        }
        else
        {
            futurePieces.remove(futureKingPosition);
        }
        futurePieces.insert(kingPosition, pieces.value(kingPosition));
    }
    if (kingPosition.first != 7 && kingPosition.second != 0
            && futurePieces.value(QPair<int, int>(kingPosition.first + 1, kingPosition.second - 1)).color != pieces.value(kingPosition).color
            && ((pieces[kingPosition].color == "WHITE"
                 && (qAbs(kingPosition.first + 1 - blackKingPosition.first) > 1
                     || qAbs(kingPosition.second - 1 - blackKingPosition.second) > 1))
                || (pieces[kingPosition].color == "BLACK"
                    && (qAbs(kingPosition.first + 1 - whiteKingPosition.first) > 1
                        || qAbs(kingPosition.second - 1 - whiteKingPosition.second) > 1))))
    {
        futureKingPosition = QPair<int, int>(kingPosition.first + 1, kingPosition.second - 1);
        futurePieces.remove(kingPosition);
        PieceInfo possiblePieceInfo = {0, 0, nullptr, 0, 0, "", "", false};
        if (futurePieces.contains(futureKingPosition))
        {
            possiblePieceInfo = futurePieces[futureKingPosition];
        }
        futurePieces.insert(futureKingPosition, pieces.value(kingPosition));
        QString kingColor = futurePieces.value(futureKingPosition).color;
        check = find_check_to(futureKingPosition, kingColor, futurePieces);
        if (check == QPair<int, int> (-1, -1))
        {

            return true;
        }
        if (possiblePieceInfo.type != "")
        {
            futurePieces.insert(futureKingPosition, possiblePieceInfo);
        }
        else
        {
            futurePieces.remove(futureKingPosition);
        }
        futurePieces.insert(kingPosition, pieces.value(kingPosition));
    }
    if (kingPosition.second != 0
            && futurePieces.value(QPair<int, int>(kingPosition.first, kingPosition.second - 1)).color != pieces.value(kingPosition).color
            && ((pieces[kingPosition].color == "WHITE"
                 && (qAbs(kingPosition.first - blackKingPosition.first) > 1
                     || qAbs(kingPosition.second - 1 - blackKingPosition.second) > 1))
                || (pieces[kingPosition].color == "BLACK"
                    && (qAbs(kingPosition.first - whiteKingPosition.first) > 1
                        || qAbs(kingPosition.second - 1 - whiteKingPosition.second) > 1))))
    {
        futureKingPosition = QPair<int, int>(kingPosition.first, kingPosition.second - 1);
        futurePieces.remove(kingPosition);
        PieceInfo possiblePieceInfo = {0, 0, nullptr, 0, 0, "", "", false};
        if (futurePieces.contains(futureKingPosition))
        {
            possiblePieceInfo = futurePieces[futureKingPosition];
        }
        futurePieces.insert(futureKingPosition, pieces.value(kingPosition));
        QString kingColor = futurePieces.value(futureKingPosition).color;
        check = find_check_to(futureKingPosition, kingColor, futurePieces);
        if (check == QPair<int, int> (-1, -1))
        {

            return true;
        }
        if (possiblePieceInfo.type != "")
        {
            futurePieces.insert(futureKingPosition, possiblePieceInfo);
        }
        else
        {
            futurePieces.remove(futureKingPosition);
        }
        futurePieces.insert(kingPosition, pieces.value(kingPosition));
    }
    return false;

}


QString Piece::set_rank_letter_from(int ranksPosition)
{
    QString rank = "";
    switch (ranksPosition)
    {
        case 0:
            rank = "a";
            break;
        case 1:
            rank = "b";
            break;
        case 2:
            rank = "c";
            break;
        case 3:
            rank = "d";
            break;
        case 4:
            rank = "e";
            break;
        case 5:
            rank = "f";
            break;
        case 6:
            rank = "g";
            break;
        case 7:
            rank = "h";
    }
    return rank;
}


QPoint Piece::update_pawn_position(int newRanksPosition, int newFilesPosition)
{
    set_new_pawn_position(newRanksPosition, newFilesPosition);
    return QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
}

void Piece::set_new_pawn_position(int newRanksPosition, int newFilesPosition)
{
    if (check_pawn_move(newRanksPosition, newFilesPosition))
    {
        set_en_passent_pawn_position(newFilesPosition);
        capture_en_passant_pawn(newRanksPosition, newFilesPosition);

        remove_opponent_piece_label(newRanksPosition, newFilesPosition);
        move_piece_on_new_space(newRanksPosition, newFilesPosition);
    }
}

bool Piece::check_pawn_move(int newRanksPosition, int newFilesPosition)
{
    if (is_new_space_empty(newRanksPosition, newFilesPosition)
            || is_new_space_occupied(newRanksPosition, newFilesPosition))
    {
        return true;
    }
    return false;
}

bool Piece::is_new_space_empty(int newRanksPosition, int newFilesPosition)
{
    if (!pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition))
            && (is_pawn_move_correct(newRanksPosition, newFilesPosition)
                || is_pawn_move_en_passant_capture(newRanksPosition, newFilesPosition)))
    {
        return true;
    }
    return false;
}

bool Piece::is_pawn_move_correct(int newRanksPosition, int newFilesPosition)
{
    if (newRanksPosition - pieceInfo.ranksPosition == 0
            && ((pieceInfo.color == "WHITE"
                 && ((pieceInfo.filesPosition == 6
                      && (newFilesPosition - pieceInfo.filesPosition == -2
                          || newFilesPosition - pieceInfo.filesPosition == -1))
                     || newFilesPosition - pieceInfo.filesPosition == -1))
                || (pieceInfo.color == "BLACK"
                    && ((pieceInfo.filesPosition == 1
                         && (newFilesPosition - pieceInfo.filesPosition == 2
                             || newFilesPosition - pieceInfo.filesPosition == 1))
                        || (newFilesPosition - pieceInfo.filesPosition == 1)))))
    {
        return true;
    }
    return false;
}

bool Piece::is_pawn_move_en_passant_capture(int newRanksPosition, int newFilesPosition)
{
    if (newRanksPosition == enPassantPawnPosition.first
            && pieceInfo.filesPosition == enPassantPawnPosition.second
            && ((pieceInfo.color == "WHITE"
                 && newFilesPosition - pieceInfo.filesPosition == -1
                 && (newRanksPosition - pieceInfo.ranksPosition == 1
                     || newRanksPosition - pieceInfo.ranksPosition == -1))
                || (pieceInfo.color == "BLACK"
                    && newFilesPosition - pieceInfo.filesPosition == 1
                    && (newRanksPosition - pieceInfo.ranksPosition == 1
                        || newRanksPosition - pieceInfo.ranksPosition == -1))))
    {
        return true;
    }
    return false;
}

bool Piece::is_new_space_occupied(int newRanksPosition, int newFilesPosition)
{
    if ((pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition))
            && pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color != pieceInfo.color
            && is_pawn_capture_correct(newRanksPosition, newFilesPosition)))
    {
        return true;
    }
    return false;
}

bool Piece::is_pawn_capture_correct(int newRanksPosition, int newFilesPosition)
{
    if (qAbs(newRanksPosition - pieceInfo.ranksPosition) == 1
            && ((pieceInfo.color == "WHITE" && newFilesPosition - pieceInfo.filesPosition == -1)
                || (pieceInfo.color == "BLACK" && newFilesPosition - pieceInfo.filesPosition == 1)))
    {
        return true;
    }
    return false;
}

void Piece::set_en_passent_pawn_position(int newFilesPosition)
{
    if (qAbs(newFilesPosition - pieceInfo.filesPosition) == 2)
    {
        enPassantPawnPosition = QPair<int, int>(pieceInfo.ranksPosition, newFilesPosition);
    }
}

void Piece::capture_en_passant_pawn(int newRanksPosition, int newFilesPosition)
{
    if (is_pawn_move_en_passant_capture(newRanksPosition, newFilesPosition))
    {
        emit signal_to_remove_opponent_piece_label(pieces.value(QPair<int, int>(newRanksPosition, pieceInfo.filesPosition)).label);
        pieces.remove(QPair<int, int>(newRanksPosition, pieceInfo.filesPosition));
        QString ranks = set_rank_letter_from(newRanksPosition);
        QString file = QString::number(qAbs(pieceInfo.filesPosition + 1 - 9));
        currentMove += "x" + ranks + file;
    }
}

bool Piece::is_pawn_on_promotion_field(int newFilesPosition)
{
    if ((pieceInfo.color == "WHITE"
            && newFilesPosition == 0)
            || (pieceInfo.color == "BLACK"
                && newFilesPosition == 7 * pieceInfo.pixelHeight))
    {
        return true;
    }
    return false;;
}


QPoint Piece::update_rook_position(int newRanksPosition, int newFilesPosition)
{
    set_new_rook_position(newRanksPosition, newFilesPosition);
    return QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
}

void Piece:: update_rook_position_on_castling(int newRanksPosition, int newFilesPosition)
{
    set_new_rook_position(newRanksPosition, newFilesPosition);
    pieceInfo.label->update_label_position(QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight));
}

void Piece::set_new_rook_position(int newRanksPosition, int newFilesPosition)
{
    if (check_rook_move(newRanksPosition, newFilesPosition))
    {
        remove_opponent_piece_label(newRanksPosition, newFilesPosition);
        pieceInfo.readyToCastling = false;
        move_piece_on_new_space(newRanksPosition, newFilesPosition);
    }
}

bool Piece::check_rook_move(int newRanksPosition, int newFilesPosition)
{
    if (is_rook_move_correct(newRanksPosition, newFilesPosition)
            && pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color != pieceInfo.color)
    {
        return true;
    }
    return false;
}

bool Piece::is_rook_move_correct(int newRanksPosition, int newFilesPosition)
{
    int index = 0, limit = -1, j = -1, i = -1;
    if (newRanksPosition == pieceInfo.ranksPosition && pieceInfo.filesPosition < newFilesPosition)
    {
        index = 1;
        i = initialize(index, pieceInfo.filesPosition);
    }
    else if (newRanksPosition == pieceInfo.ranksPosition && pieceInfo.filesPosition > newFilesPosition)
    {
        index = 2;
        i = initialize(index, pieceInfo.filesPosition);
    }
    else if (newFilesPosition == pieceInfo.filesPosition && pieceInfo.ranksPosition < newRanksPosition)
    {
        index = 3;
        i = initialize(index, pieceInfo.ranksPosition);
    }
    else if (newFilesPosition == pieceInfo.filesPosition && pieceInfo.ranksPosition > newRanksPosition)
    {
        index = 4;
        i = initialize(index, pieceInfo.ranksPosition);
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
    return !error;
}


QPoint Piece::update_knight_position(int newRanksPosition, int newFilesPosition)
{
    set_new_knight_position(newRanksPosition, newFilesPosition);
    return QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
}

void Piece::set_new_knight_position(int newRanksPosition, int newFilesPosition)
{
    if (check_knight_move(newRanksPosition, newFilesPosition))
    {
        remove_opponent_piece_label(newRanksPosition, newFilesPosition);
        move_piece_on_new_space(newRanksPosition, newFilesPosition);
    }
}

bool Piece::check_knight_move(int newRanksPosition, int newFilesPosition)
{
    if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color != pieceInfo.color
            && is_knight_move_correct(newRanksPosition, newFilesPosition))
    {
        return true;
    }
    return false;
}

bool Piece::is_knight_move_correct(int newRanksPosition, int newFilesPosition)
{
    if ((qAbs(newRanksPosition - pieceInfo.ranksPosition) == 1
            && qAbs(newFilesPosition - pieceInfo.filesPosition) == 2)
            || (qAbs(newRanksPosition - pieceInfo.ranksPosition) == 2
                && qAbs(newFilesPosition - pieceInfo.filesPosition) == 1))
    {
        return true;
    }
    return false;
}


QPoint Piece::update_bishop_position(int newRanksPosition, int newFilesPosition)
{
    set_new_bishop_position(newRanksPosition, newFilesPosition);
    return QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
}

void Piece::set_new_bishop_position(int newRanksPosition, int newFilesPosition)
{
    if (check_bishop_move(newRanksPosition, newFilesPosition))
    {
        remove_opponent_piece_label(newRanksPosition, newFilesPosition);
        pieceInfo.readyToCastling = false;
        move_piece_on_new_space(newRanksPosition, newFilesPosition);
    }
}

bool Piece::check_bishop_move(int newRanksPosition, int newFilesPosition)
{
    if (is_bishop_move_correct(newRanksPosition, newFilesPosition)
            && pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color != pieceInfo.color)
    {
        return true;
    }
    return false;
}

bool Piece::is_bishop_move_correct(int newRanksPosition, int newFilesPosition)
{
    bool error = false;
    int index;
    if (newRanksPosition < pieceInfo.ranksPosition && newFilesPosition < pieceInfo.filesPosition)
    {
        index = 1;
    }
    else if (newRanksPosition < pieceInfo.ranksPosition && newFilesPosition > pieceInfo.filesPosition)
    {
        index = 2;
    }
    else if (newRanksPosition > pieceInfo.ranksPosition && newFilesPosition < pieceInfo.filesPosition)
    {
        index = 3;
    }
    else if (newRanksPosition > pieceInfo.ranksPosition && newFilesPosition > pieceInfo.filesPosition)
    {
        index = 4;
    }
    else
    {
        error = true;
    }
    int i = initialize(index / 3, pieceInfo.ranksPosition);
    int j = initialize((index - 1) % 2, pieceInfo.filesPosition);
    if (qAbs(newRanksPosition - pieceInfo.ranksPosition) != qAbs(newFilesPosition - pieceInfo.filesPosition))
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
    return !error;
}


QPoint Piece::update_queen_position(int newRanksPosition, int newFilesPosition)
{
    QPoint newPosition = QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
    if (is_queen_move_as_rook(newRanksPosition, newFilesPosition))
    {
        newPosition = update_rook_position(newRanksPosition, newFilesPosition);
    }
    else if (is_queen_move_as_bishop(newRanksPosition, newFilesPosition))
    {
        newPosition = update_bishop_position(newRanksPosition, newFilesPosition);
    }
    return newPosition;
}

bool Piece::is_queen_move_as_rook(int newRanksPosition, int newFilesPosition)
{
    if (newRanksPosition == pieceInfo.ranksPosition
            || newFilesPosition == pieceInfo.filesPosition)
    {
        return true;
    }
    return false;
}

bool Piece::is_queen_move_as_bishop(int newRanksPosition, int newFilesPosition)
{
    if (qAbs(newRanksPosition - pieceInfo.ranksPosition) == qAbs(newFilesPosition - pieceInfo.filesPosition))
    {
        return true;
    }
    return false;
}


QPoint Piece::try_to_castling(QPoint currentPiecePosition, int newRanksPosition, int newFilesPosition)
{
    int previousRookRanksPosition, newRookRanksPosition;
    if (newRanksPosition - pieceInfo.ranksPosition == 2)
    {
        previousRookRanksPosition = 7;
        newRookRanksPosition = 5;
    }
    else if (newRanksPosition - pieceInfo.ranksPosition == -2)
    {
        previousRookRanksPosition = 0;
        newRookRanksPosition = 3;
    }
    if (newFilesPosition == pieceInfo.filesPosition
            && qAbs(newRanksPosition - pieceInfo.ranksPosition) == 2
            && pieces.value(QPair<int, int>(previousRookRanksPosition, pieceInfo.filesPosition)).type == "rook"
            && pieces.value(QPair<int, int>(previousRookRanksPosition, pieceInfo.filesPosition)).readyToCastling)
    {
        QPoint newRookPosition = QPoint(newRookRanksPosition, newFilesPosition);
        emit signal_to_castling(newRookPosition);
        if (!pieces.contains(QPair<int, int>(previousRookRanksPosition, pieceInfo.filesPosition)))
        {
            return update_king_position_on_castling(newRanksPosition, newFilesPosition);
        }
    }
    return currentPiecePosition;
}

QPoint Piece:: update_king_position_on_castling(int newRanksPosition, int newFilesPosition)
{
    if (!pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition)))
    {
        remove_opponent_piece_label(newRanksPosition, newFilesPosition);
        pieceInfo.readyToCastling = false;
        move_piece_on_new_space(newRanksPosition, newFilesPosition);
    }
    return QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
}

QPoint Piece::update_king_position(int newRanksPosition, int newFilesPosition)
{
    QPoint newPosition = QPoint(pieceInfo.ranksPosition * pieceInfo.pixelWidth, pieceInfo.filesPosition * pieceInfo.pixelHeight);
    if ((newRanksPosition == pieceInfo.ranksPosition && qAbs(newFilesPosition - pieceInfo.filesPosition) == 1)
            || (newFilesPosition == pieceInfo.filesPosition && qAbs(newRanksPosition - pieceInfo.ranksPosition) == 1))
    {
        newPosition = update_rook_position(newRanksPosition, newFilesPosition);
    }
    else if (qAbs(newRanksPosition - pieceInfo.ranksPosition) == 1 && qAbs(newFilesPosition - pieceInfo.filesPosition) == 1)
    {
        newPosition = update_bishop_position(newRanksPosition, newFilesPosition);
    }
    return newPosition;
}


void Piece::remove_opponent_piece_label(int newRanksPosition, int newFilesPosition)
{
    if (pieces.contains(QPair<int, int>(newRanksPosition, newFilesPosition)))
    {
        emit signal_to_remove_opponent_piece_label(pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).label);
        if (QPair<int, int>(newRanksPosition, newFilesPosition) == enPassantPawnPosition)
        {
            enPassantPawnPosition = QPair<int, int>(-1, -1);
        }
        if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).type == "pawn")
        {
            QString ranks = set_rank_letter_from(newRanksPosition);
            QString file = QString::number(qAbs(newFilesPosition + 1 - 9));
            currentMove += "x" + ranks + file;

            if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color == "WHITE")
            {
                existWhitePiecesMap[1]--;
                //superiority=-1;
            }
            else
            {
                existBlackPiecesMap[1]--;
                //superiority=-1;
            }
        }
        else if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).type == "knight")
        {
            QString ranks = set_rank_letter_from(newRanksPosition);
            QString file = QString::number(qAbs(newFilesPosition + 1 - 9));
            currentMove += "xN" + ranks + file;

            if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color == "WHITE")
            {
                existWhitePiecesMap[3]--;
                //superiority = -3;
            }
            else
            {
                existBlackPiecesMap[3]--;
                //superiority = 3;
            }
        }
        else if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).type == "bishop")
        {
            QString ranks = set_rank_letter_from(newRanksPosition);
            QString file = QString::number(qAbs(newFilesPosition + 1 - 9));
            currentMove += "xB" + ranks + file;

            if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color == "WHITE")
            {
                existWhitePiecesMap[3]--;
                //superiority -= 3;
            }
            else
            {
                existBlackPiecesMap[3]--;
                //superiority += 3;
            }
        }
        else if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).type == "rook")
        {
            QString ranks = set_rank_letter_from(newRanksPosition);
            QString file = QString::number(qAbs(newFilesPosition + 1 - 9));
            currentMove += "xR" + ranks + file;

            if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color == "WHITE")
            {
                existWhitePiecesMap[5]--;
                //superiority -= 5;
            }
            else
            {
                existBlackPiecesMap[5]--;
                //superiority += 5;
            }
        }
        else if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).type == "queen")
        {
            QString ranks = set_rank_letter_from(newRanksPosition);
            QString file = QString::number(qAbs(newFilesPosition + 1 - 9));
            currentMove += "xQ" + ranks + file;

            if (pieces.value(QPair<int, int>(newRanksPosition, newFilesPosition)).color == "WHITE")
            {
                existWhitePiecesMap[9]--;
                //superiority -= 9;
            }
            else
            {
                existBlackPiecesMap[9]--;
                // superiority += 9;
            }
        }
    }
}

void Piece::move_piece_on_new_space(int newRanksPosition, int newFilesPosition)
{
    pieces.remove(QPair<int, int>(pieceInfo.ranksPosition, pieceInfo.filesPosition));
    pieceInfo.ranksPosition = newRanksPosition;
    pieceInfo.filesPosition = newFilesPosition;
    pieces.insert(QPair<int, int>(pieceInfo.ranksPosition, pieceInfo.filesPosition), pieceInfo);
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
    if (index < 3)
    {
        is_enough = pieces.contains(QPair<int, int>(j, i));
    }
    else
    {
        is_enough = pieces.contains(QPair<int, int>(i, j));
    }
    return is_enough;
}

int Piece::change(int index, int i)
{
    if (i > -1 && i < 8)
    {
        if (index % 2)
        {
            i++;
        }
        else
        {
            i--;
        }
    }
    return i;
}


DraggableLabel *Piece::get_piece_label()
{
    return pieceInfo.label;
}

bool Piece::is_ready_to_castling() const
{
    return pieceInfo.readyToCastling;
}
