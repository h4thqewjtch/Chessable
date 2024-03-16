#ifndef PIECE_H
#define PIECE_H

#include <QList>
#include <QMap>

#include "../DraggableLabel/draggablelabel.h"

struct PieceInfo
{
    int pixelWidth;
    int pixelHeight;
    DraggableLabel *label;
    int ranksPosition;
    int filesPosition;
    QString color;
    QString type;
    bool readyToCastling;
};

class Piece: public QObject
{
    Q_OBJECT

private:
    static QString currentSideToMove;
    static QMap<QPair<int, int>, PieceInfo> pieces;

    static QPair<int, int> blackKingPosition;
    static QPair<int, int> whiteKingPosition;
    static QPair<int, int> enPassantPawnPosition;
    static QList<QString> movesList;
    //static int superiority;
    PieceInfo pieceInfo;
    QString currentMove;

private slots:
    void initialize_piece_info(int, int, QString, QString);
    void set_piece_label(QString);
    void update_piece_position(const QPoint &);
    void set_piece_position(QPoint &);

    QPair<int, int> find_check_to(QPair<int, int>, QString, QMap <QPair<int, int>, PieceInfo> &);
    QPair<int, int> check_rook_moves(QPair<int, int>, QString, QMap <QPair<int, int>, PieceInfo> &);
    QPair<int, int> check_bishop_moves(QPair<int, int>, QString, QMap <QPair<int, int>, PieceInfo> &);
    QPair<int, int> check_knight_moves(QPair<int, int>, QString, QMap <QPair<int, int>, PieceInfo> &);
    QPair<int, int> check_space_on(QPair<int, int>, QPair<int, int>, QString, QString, QString, QMap <QPair<int, int>, PieceInfo> &);

    bool is_checkmate_to(QPair<int, int>, QPair<int, int>);
    QPair<int, int> get_checkmate_direction_from(QPair<int, int>, QPair<int, int>);
    QPair<int, int> get_checkmate_position(QPair<int, int>, QPair<int, int>, QPair<int, int>);
    bool check_king_moves(QPair<int, int>);

    QString set_rank_letter_from(int);

    QPoint update_pawn_position(int, int);
    void set_new_pawn_position(int, int);
    bool check_pawn_move(int, int);
    bool is_new_space_empty(int, int);
    bool is_pawn_move_correct(int, int);
    bool is_pawn_move_en_passant_capture(int, int);
    bool is_new_space_occupied(int, int);
    bool is_pawn_capture_correct(int, int);
    void set_en_passent_pawn_position(int);
    void capture_en_passant_pawn(int, int);
    bool is_pawn_on_promotion_field(int);

    QPoint update_rook_position(int, int);
    void set_new_rook_position(int, int);
    bool check_rook_move(int, int);
    bool is_rook_move_correct(int, int);

    QPoint update_knight_position(int, int);
    void set_new_knight_position(int, int);
    bool check_knight_move(int, int);
    bool is_knight_move_correct(int, int);

    QPoint update_bishop_position(int, int);
    void set_new_bishop_position(int, int);
    bool check_bishop_move(int, int);
    bool is_bishop_move_correct(int, int);

    QPoint update_queen_position(int, int);
    bool is_queen_move_as_rook(int, int);
    bool is_queen_move_as_bishop(int, int);

    QPoint try_to_castling(QPoint, int, int);
    QPoint update_king_position_on_castling(int, int);
    QPoint update_king_position(int, int);

    int initialize(int, int);
    bool is_enough(int, int, int);
    int change(int, int);

    void remove_opponent_piece_label(int, int);
    void move_piece_on_new_space(int, int);

public slots:
    void update_rook_position_on_castling(int, int);

signals:
    void signal_to_remove_opponent_piece_label(DraggableLabel *);
    void signal_to_castling(QPoint &);
    void signal_to_promote_pawn(DraggableLabel *, QPoint &, QString &);
    void signal_to_show_move(QString);

public:
    Piece(int ranksPosition = 0, int filesPosition = 0, QString pieceColor = "", QString pieceType = "", QString imagePath = "", QObject *parent = nullptr)
        : QObject{parent}
    {
        initialize_piece_info(ranksPosition, filesPosition, pieceColor, pieceType);
        set_piece_label(imagePath);
        pieces.insert(QPair<int, int>(pieceInfo.ranksPosition, pieceInfo.filesPosition), pieceInfo);
        connect(pieceInfo.label, &DraggableLabel::move_label, this, &Piece::update_piece_position);
    }

    ~Piece()
    {
        delete pieceInfo.label;
    }

    DraggableLabel *get_piece_label();
    QMap<int, int> get_exist_white_piece_map();
    QMap<int, int> get_exist_black_piece_map();
    bool is_ready_to_castling() const;

    static QMap<int, int> existWhitePiecesMap;
    static QMap<int, int> existBlackPiecesMap;
};

#endif // PIECE_H
