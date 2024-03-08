#include "clickablelabel.h"

void ClickableLabel::mousePressEvent(QMouseEvent *mousePressEvent)
{
    QPoint mousePressPosition = mousePressEvent->pos();
    qDebug() << "Clicked on " << name << " at: " << mousePressPosition.x() << ", " << mousePressPosition.y();
    QLabel::mousePressEvent(mousePressEvent);
}
