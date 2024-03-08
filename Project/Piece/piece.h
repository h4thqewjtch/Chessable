#ifndef PIECE_H
#define PIECE_H

#include <QMap>

#include "../DraggableLabel/draggablelabel.h"

class Piece: public QObject
{
    Q_OBJECT

private:
    int piecePixelWidth = 64;
    int piecePixelHeight = 64;
    DraggableLabel *pieceLabel;
    int ranksPosition = 0;
    int filesPosition = 0;
    QString pieceColor;
    QString pieceType;
    static QMap<QPair<int, int>, QPair<DraggableLabel *, QPair<QString, QString>>> pieces;

private slots:
    void update_piece_position(const QPoint &);
    QPoint update_pawn_position(int, int);
    QPoint update_rook_position(int, int);
    QPoint update_knight_position(int, int);
    QPoint update_bishop_position(int, int);
    QPoint update_queen_position(int, int);
    QPoint update_king_position(int, int);
    int initialize(int, int);
    bool is_enough(int, int, int);
    int change(int, int);

signals:
    void signal_to_remove_opponent_piece_label(DraggableLabel *);

public:
    Piece(int ranksPosition = 0, int filesPosition = 0, QString pieceColor = "", QString pieceType = "", QString imagePath = "", QObject *parent = nullptr)
        : QObject{parent}, ranksPosition(ranksPosition), filesPosition(filesPosition),  pieceColor(pieceColor), pieceType(pieceType)
    {
        pieceLabel = new DraggableLabel();
        QPixmap piecePix(imagePath);
        pieceLabel->setPixmap(piecePix.scaled(piecePixelWidth, piecePixelHeight, Qt::KeepAspectRatio));
        pieceLabel->setGeometry(this->ranksPosition * piecePixelWidth, this->filesPosition * piecePixelHeight, piecePixelWidth, piecePixelHeight);
        pieces.insert(QPair<int, int>(ranksPosition, filesPosition),
                      QPair<DraggableLabel *, QPair<QString, QString>> (pieceLabel, QPair<QString, QString>(this->pieceColor, this->pieceType)));
        connect(pieceLabel, &DraggableLabel::move_label, this, &Piece::update_piece_position);
    }

    ~Piece()
    {
        delete pieceLabel;
    }

    DraggableLabel *get_piece_label();

};

#endif // PIECE_H
