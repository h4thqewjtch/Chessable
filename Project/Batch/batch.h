#ifndef BATCH_H
#define BATCH_H

#include "../ClickableLabel/clickablelabel.h"
#include "../Piece/piece.h"

class Batch: public QObject
{
    Q_OBJECT

private:
    QString playerColor;

    ClickableLabel *chessBoard;

    Piece *blackPawns[8];
    Piece *whitePawns[8];

    Piece *blackRooks[2];
    Piece *whiteRooks[2];

    Piece *blackKnights[2];
    Piece *whiteKnights[2];

    Piece *blackBishops[2];
    Piece *whiteBishops[2];

    Piece *blackQueen;
    Piece *whiteQueen;

    Piece *blackKing;
    Piece *whiteKing;

    Piece *newPieces[16];
    int newPiecesCount = -1;
    QString currentNewPieceColor;
    QPoint currentNewPiecePosition;
    QString currentNewPieceType;
    QString currentNewPieceImagePath;

private slots:
    void slot_to_get_player_piece_color();
    void slot_to_remove_opponent_piece_label(DraggableLabel *);
    void slot_to_castling(QPoint &);
    void slot_to_promote_pawn(DraggableLabel *, QPoint &, QString &);
    void slot_to_show_move(QString, int, QPair<QPoint, QPoint>);
    void connect_slots_with_signals();

protected:
    void put_rooks();
    void put_knights();
    void put_bishops();
    void put_queens();
    void put_kings();
    void put_pawns();

    void clear_rooks();
    void clear_knights();
    void clear_bishops();
    void clear_queens();
    void clear_kings();
    void clear_pawns();

signals:
    void signal_to_remove_opponent_piece_label(DraggableLabel *);
    void signal_to_promote_pawn(DraggableLabel *, QString &);
    void signal_to_show_move(QString, int, QPair<QPoint, QPoint>);

public:
    Batch(QObject *parent = nullptr) : QObject{parent}
    {
        chessBoard = new ClickableLabel("chessBoard");

        put_rooks();
        put_knights();
        put_bishops();
        put_queens();
        put_kings();
        put_pawns();

        connect_slots_with_signals();
    }

    ~Batch()
    {
        delete chessBoard;

        clear_rooks();
        clear_knights();
        clear_bishops();
        clear_queens();
        clear_kings();
        clear_pawns();
    }

    void set_player_color(QString);

    ClickableLabel *get_chess_board();

    Piece *get_piece_on_position(int, int);

    void set_current_new_piece_type_and_image_path(QString, QString);

    Piece *get_current_new_piece();
};

#endif // BATCH_H
