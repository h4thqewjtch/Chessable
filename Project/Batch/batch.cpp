#include "batch.h"

void Batch::slot_to_remove_opponent_piece_label(DraggableLabel *pieceLabel)
{
    emit signal_to_remove_opponent_piece_label(pieceLabel);
}

void Batch::slot_to_castling(QPoint &newRookPosition)
{
    if (newRookPosition.x() == 3)
    {
        if (newRookPosition.y() == 0)
        {
            blackRooks[0]->update_rook_position_on_castling(newRookPosition.x(), newRookPosition.y());
        }
        else
        {
            whiteRooks[0]->update_rook_position_on_castling(newRookPosition.x(), newRookPosition.y());
        }
    }
    else
    {
        if (newRookPosition.y() == 0)
        {
            blackRooks[1]->update_rook_position_on_castling(newRookPosition.x(), newRookPosition.y());
        }
        else
        {
            whiteRooks[1]->update_rook_position_on_castling(newRookPosition.x(), newRookPosition.y());
        }
    }
}

void Batch::slot_to_promote_pawn(DraggableLabel *pieceLabel, QPoint &piecePosition, QString &pieceColor)
{
    currentNewPiecePosition = piecePosition;
    currentNewPieceColor = pieceColor;
    emit signal_to_promote_pawn(pieceLabel, pieceColor);
}

void Batch::slot_to_show_move(QString currentMove)
{
    emit signal_to_show_move(currentMove);
}


void Batch::connect_slots_with_signals()
{
    for (int i = 0; i < 8; i++)
    {
        connect(blackPawns[i], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);
        connect(whitePawns[i], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);

        connect(blackPawns[i], &Piece::signal_to_promote_pawn, this, &Batch::slot_to_promote_pawn);
        connect(whitePawns[i], &Piece::signal_to_promote_pawn, this, &Batch::slot_to_promote_pawn);

        connect(blackPawns[i], &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);
        connect(whitePawns[i], &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);
    }
    for (int i = 0; i < 2; i++)
    {
        connect(blackRooks[i], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);
        connect(whiteRooks[i], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);

        connect(blackRooks[i], &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);
        connect(whiteRooks[i], &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);

    }
    for (int i = 0; i < 2; i++)
    {
        connect(blackKnights[i], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);
        connect(whiteKnights[i], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);

        connect(blackKnights[i], &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);
        connect(whiteKnights[i], &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);

    }
    for (int i = 0; i < 2; i++)
    {
        connect(blackBishops[i], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);
        connect(whiteBishops[i], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);

        connect(blackBishops[i], &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);
        connect(whiteBishops[i], &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);

    }

    connect(blackQueen, &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);
    connect(whiteQueen, &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);

    connect(blackQueen, &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);
    connect(whiteQueen, &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);


    connect(blackKing, &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);
    connect(whiteKing, &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);

    connect(blackKing, &Piece::signal_to_castling, this, &Batch::slot_to_castling);
    connect(whiteKing, &Piece::signal_to_castling, this, &Batch::slot_to_castling);

    connect(blackKing, &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);
    connect(whiteKing, &Piece::signal_to_show_move, this, &Batch::slot_to_show_move);

}


void Batch::put_rooks()
{
    for (int i = 0, j = 0; i < 2; i++, j += 7)
    {
        blackRooks[i] = new Piece(j, 0, "BLACK", "rook", "../Materials/Images/rook_black.png");
        whiteRooks[i] = new Piece(j, 7, "WHITE", "rook", "../Materials/Images/rook_white.png");
    }
}

void Batch::put_knights()
{
    for (int i = 0, j = 1; i < 2; i++, j += 5)
    {
        blackKnights[i] = new Piece(j, 0, "BLACK", "knight", "../Materials/Images/knight_black.png");
        whiteKnights[i] = new Piece(j, 7, "WHITE", "knight", "../Materials/Images/knight_white.png");
    }
}

void Batch::put_bishops()
{
    for (int i = 0, j = 2; i < 2; i++, j += 3)
    {
        blackBishops[i] = new Piece(j, 0, "BLACK", "bishop", "../Materials/Images/bishop_black.png");
        whiteBishops[i] = new Piece(j, 7, "WHITE", "bishop", "../Materials/Images/bishop_white.png");
    }
}

void Batch::put_queens()
{
    blackQueen = new Piece(3, 0, "BLACK", "queen", "../Materials/Images/queen_black.png");
    whiteQueen = new Piece(3, 7, "WHITE", "queen", "../Materials/Images/queen_white.png");
}

void Batch::put_kings()
{
    blackKing = new Piece(4, 0, "BLACK", "king", "../Materials/Images/king_black.png");
    whiteKing = new Piece(4, 7, "WHITE", "king", "../Materials/Images/king_white.png");
}

void Batch::put_pawns()
{
    for (int i = 0, j = 0; i < 8; i++, j++)
    {
        blackPawns[i] = new Piece(j, 1, "BLACK", "pawn", "../Materials/Images/pawn_black.png");
        whitePawns[i] = new Piece(j, 6, "WHITE", "pawn", "../Materials/Images/pawn_white.png");
    }
}


void Batch::clear_rooks()
{
    for (int i = 0; i < 2; i++)
    {
        delete blackRooks[i];
        delete whiteRooks[i];
    }
}

void Batch::clear_knights()
{
    for (int i = 0; i < 2; i++)
    {
        delete blackKnights[i];
        delete whiteKnights[i];
    }
}

void Batch::clear_bishops()
{
    for (int i = 0; i < 2; i++)
    {
        delete blackBishops[i];
        delete whiteBishops[i];
    }
}

void Batch::clear_queens()
{
    delete blackQueen;
    delete whiteQueen;
}

void Batch::clear_kings()
{
    delete blackKing;
    delete whiteKing;
}

void Batch::clear_pawns()
{
    for (int i = 0; i < 8; i++)
    {
        delete blackPawns[i];
        delete whitePawns[i];
    }

}


ClickableLabel *Batch::get_chess_board()
{
    return chessBoard;
}

Piece *Batch::get_piece_on_position(int ranksPosition, int filesPosition)
{
    if (filesPosition == 0)
    {
        switch (ranksPosition)
        {
            case 0:
                return blackRooks[0];
            case 1:
                return blackKnights[0];
            case 2:
                return blackBishops[0];
            case 3:
                return blackQueen;
            case 4:
                return blackKing;
            case 5:
                return blackBishops[1];
            case 6:
                return blackKnights[1];
            case 7:
                return blackRooks[1];

        }
    }
    else if (filesPosition == 1)
    {
        return blackPawns[ranksPosition];
    }
    else if (filesPosition == 6)
    {
        return whitePawns[ranksPosition];
    }
    else
    {
        switch (ranksPosition)
        {
            case 0:
                return whiteRooks[0];
            case 1:
                return whiteKnights[0];
            case 2:
                return whiteBishops[0];
            case 3:
                return whiteQueen;
            case 4:
                return whiteKing;
            case 5:
                return whiteBishops[1];
            case 6:
                return whiteKnights[1];
            case 7:
                return whiteRooks[1];

        }
    }
    return blackKing;

}

void Batch::set_current_new_piece_type_and_image_path(QString pieceType, QString pieceImagePath)
{
    currentNewPieceType = pieceType;
    currentNewPieceImagePath = pieceImagePath;
    newPiecesCount++;
    newPieces[newPiecesCount] = new Piece(currentNewPiecePosition.x(), currentNewPiecePosition.y(), currentNewPieceColor, currentNewPieceType, currentNewPieceImagePath);
    connect(newPieces[newPiecesCount], &Piece::signal_to_remove_opponent_piece_label, this, &Batch::slot_to_remove_opponent_piece_label);
}

Piece *Batch::get_current_new_piece()
{
    return newPieces[newPiecesCount];
}
