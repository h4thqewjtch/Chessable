#include "promotionfield.h"
#include "ui_promotionField.h"

PromotionField::PromotionField(QString pieceColor, QWidget *parent) :
    QDialog(parent), ui(new Ui::PromotionField), pieceColor(pieceColor)
{
    ui->setupUi(this);
    setWindowTitle("Change Field");

    pieceType = "queen";

    if (this->pieceColor == "WHITE")
    {
        pieceImagePath = "../Materials/Images/queen_white.png";
        ui->queenButton->setIcon(QIcon("../Materials/Images/queen_white.png"));
        ui->rookButton->setIcon(QIcon("../Materials/Images/rook_white.png"));
        ui->knightButton->setIcon(QIcon("../Materials/Images/knight_white.png"));
        ui->bishopButton->setIcon(QIcon("../Materials/Images/bishop_white.png"));
        ui->pawnButton->setIcon(QIcon("../Materials/Images/pawn_white.png"));
    }
    else
    {
        pieceImagePath = "../Materials/Images/queen_black.png";
        ui->queenButton->setIcon(QIcon("../Materials/Images/queen_black.png"));
        ui->rookButton->setIcon(QIcon("../Materials/Images/rook_black.png"));
        ui->knightButton->setIcon(QIcon("../Materials/Images/knight_black.png"));
        ui->bishopButton->setIcon(QIcon("../Materials/Images/bishop_black.png"));
        ui->pawnButton->setIcon(QIcon("../Materials/Images/pawn_black.png"));
    }
    ui->queenButton->setIconSize(QSize(64, 64));
    ui->rookButton->setIconSize(QSize(64, 64));
    ui->knightButton->setIconSize(QSize(64, 64));
    ui->bishopButton->setIconSize(QSize(64, 64));
    ui->pawnButton->setIconSize(QSize(64, 64));
}

PromotionField::~PromotionField()
{
    delete ui;
}

QString PromotionField::get_piece_type()
{
    return pieceType;
}

QString PromotionField::get_piece_image_path()
{
    return pieceImagePath;
}

void PromotionField::on_queenButton_clicked()
{
    pieceType = "queen";
    if (pieceColor == "WHITE")
    {
        pieceImagePath = "../Materials/Images/queen_white.png";
    }
    else
    {
        pieceImagePath = "../Materials/Images/queen_black.png";
    }
}


void PromotionField::on_rookButton_clicked()
{
    pieceType = "rook";
    if (pieceColor == "WHITE")
    {
        pieceImagePath = "../Materials/Images/rook_white.png";
    }
    else
    {
        pieceImagePath = "../Materials/Images/rook_black.png";
    }
}


void PromotionField::on_knightButton_clicked()
{
    pieceType = "knight";
    if (pieceColor == "WHITE")
    {
        pieceImagePath = "../Materials/Images/knight_white.png";
    }
    else
    {
        pieceImagePath = "../Materials/Images/knight_black.png";
    }
}


void PromotionField::on_bishopButton_clicked()
{
    pieceType = "bishop";
    if (pieceColor == "WHITE")
    {
        pieceImagePath = "../Materials/Images/bishop_white.png";
    }
    else
    {
        pieceImagePath = "../Materials/Images/bishop_black.png";
    }
}


void PromotionField::on_pawnButton_clicked()
{
    pieceType = "pawn";
    if (pieceColor == "WHITE")
    {
        pieceImagePath = "../Materials/Images/pawn_white.png";
    }
    else
    {
        pieceImagePath = "../Materials/Images/pawn_black.png";
    }
}

