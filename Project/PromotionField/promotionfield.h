#ifndef PROMOTIONFIELD_H
#define PROMOTIONFIELD_H

#include <QCursor>
#include <QDialog>
#include <QPainter>
#include <QRect>

namespace Ui
{
class PromotionField;
}

class PromotionField : public QDialog
{
    Q_OBJECT

private:
    Ui::PromotionField *ui;

    QString pieceColor;
    QString pieceType;
    QString pieceImagePath;

private slots:
    void set_button_invisible(QPushButton *);

    void on_queenButton_clicked();

    void on_rookButton_clicked();

    void on_knightButton_clicked();

    void on_bishopButton_clicked();

    void on_pawnButton_clicked();

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    explicit PromotionField(QString, QWidget *parent = nullptr);
    ~PromotionField();

    QString get_piece_type();
    QString get_piece_image_path();
    void set_piece(QString, QString, QString);

};

#endif // PROMOTIONFIELD_H
