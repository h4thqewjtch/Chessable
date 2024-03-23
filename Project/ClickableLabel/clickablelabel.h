#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QString>
#include <QWidget>



class ClickableLabel : public QLabel
{
    Q_OBJECT

private:
    QString name;
    QPixmap chessBoardPix;
    int chessBoardPixelWidth = 512;
    int chessBoardPixelHeight = 512;


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *) override;

public:
    explicit ClickableLabel(QString name, QWidget *parent = Q_NULLPTR) : QLabel(parent), name(name)
    {
        chessBoardPix = QPixmap(":/Materials/Images/chessboard_white.jpg");
        this->setGeometry(0, 0, chessBoardPixelWidth, chessBoardPixelHeight);
    }

};

#endif // CLICKABLELABEL_H
