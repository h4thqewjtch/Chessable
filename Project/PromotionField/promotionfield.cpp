#include "promotionfield.h"
#include "ui_promotionField.h"

PromotionField::PromotionField(QString pieceColor, QWidget *parent) :
    QDialog(parent), ui(new Ui::PromotionField), pieceColor(pieceColor)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setStyleSheet("border-radius: 100px;");
    QPoint cursorPosition = QCursor::pos();
    this->move(cursorPosition.x(), cursorPosition.y());
    pieceType = "queen";

    if (this->pieceColor == "WHITE")
    {
        pieceImagePath = ":/Materials/Images/queen_white.png";
        ui->queenButton->setIcon(QIcon(":/Materials/Images/queen_white.png"));
        ui->rookButton->setIcon(QIcon(":/Materials/Images/rook_white.png"));
        ui->knightButton->setIcon(QIcon(":/Materials/Images/knight_white.png"));
        ui->bishopButton->setIcon(QIcon(":/Materials/Images/bishop_white.png"));
        ui->pawnButton->setIcon(QIcon(":/Materials/Images/pawn_white.png"));
    }
    else
    {
        pieceImagePath = ":/Materials/Images/queen_black.png";
        ui->queenButton->setIcon(QIcon(":/Materials/Images/queen_black.png"));
        ui->rookButton->setIcon(QIcon(":/Materials/Images/rook_black.png"));
        ui->knightButton->setIcon(QIcon(":/Materials/Images/knight_black.png"));
        ui->bishopButton->setIcon(QIcon(":/Materials/Images/bishop_black.png"));
        ui->pawnButton->setIcon(QIcon(":/Materials/Images/pawn_black.png"));
    }
    set_button_invisible(ui->bishopButton);
    set_button_invisible(ui->knightButton);
    set_button_invisible(ui->rookButton);
    set_button_invisible(ui->queenButton);
    set_button_invisible(ui->pawnButton);

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

void PromotionField::set_piece(QString type, QString whitePiecePath, QString blackPiecePath)
{
    pieceType = type;
    if (pieceColor == "WHITE")
    {
        pieceImagePath = whitePiecePath;
    }
    else
    {
        pieceImagePath = blackPiecePath;
    }
    close();
}

void PromotionField::set_button_invisible(QPushButton *myButton)
{
    // // Установка размеров кнопки равными размерам картинки
    // myButton->setFixedSize(pixmap.size());

    // Сделать кнопку невидимой (прозрачной)
    myButton->setStyleSheet("background-color: transparent; border: none;");

    // Скрыть рамку кнопки
    myButton->setFlat(true);
}

void PromotionField::on_queenButton_clicked()
{
    set_piece("queen", ":/Materials/Images/queen_white.png", ":/Materials/Images/queen_black.png");
}


void PromotionField::on_rookButton_clicked()
{
    set_piece("rook", ":/Materials/Images/rook_white.png", ":/Materials/Images/rook_black.png");
}


void PromotionField::on_knightButton_clicked()
{
    set_piece("knight", ":/Materials/Images/knight_white.png", ":/Materials/Images/knight_black.png");
}


void PromotionField::on_bishopButton_clicked()
{
    set_piece("bishop", ":/Materials/Images/bishop_white.png", ":/Materials/Images/bishop_black.png");
}


void PromotionField::on_pawnButton_clicked()
{
    set_piece("pawn", ":/Materials/Images/pawn_white.png", ":/Materials/Images/pawn_black.png");
}


void PromotionField::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int radius = 10;
    QRect rect = this->rect().adjusted(0, 0, -1, -1);
    painter.setBrush(palette().color(QPalette::Window));
    painter.setPen(Qt::black);
    painter.drawRoundedRect(rect, radius, radius);
}

