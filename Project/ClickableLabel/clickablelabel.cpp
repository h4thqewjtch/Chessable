#include "clickablelabel.h"

void ClickableLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect roundedRect = rect().adjusted(0, 0, -1, -1);

    chessBoardPix = chessBoardPix.scaled(roundedRect.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setBrush(chessBoardPix);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(roundedRect, 10, 10);
    QLabel::paintEvent(event);
}

void ClickableLabel::mousePressEvent(QMouseEvent *mousePressEvent)
{
    QPoint mousePressPosition = mousePressEvent->pos();
    qDebug() << "Clicked on " << name << " at: " << mousePressPosition.x() << ", " << mousePressPosition.y();
    QLabel::mousePressEvent(mousePressEvent);
}
