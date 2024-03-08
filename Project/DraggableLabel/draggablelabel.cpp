#include "draggablelabel.h"


void DraggableLabel::mousePressEvent(QMouseEvent *mousePressEvent)
{
    if (mousePressEvent->button() == Qt::LeftButton)
    {
        startPosition = mousePressEvent->pos();
    }
}

void DraggableLabel::mouseMoveEvent(QMouseEvent *mouseMoveEvent)
{
    if (mouseMoveEvent->buttons() & Qt::LeftButton)
    {
        newPosition = mapToParent(mouseMoveEvent->pos() - startPosition);
        move(newPosition);
        newPosition += startPosition;
    }
}

void DraggableLabel::mouseReleaseEvent(QMouseEvent *mouseReleaseEvent)
{
    if (mouseReleaseEvent->button() == Qt::LeftButton)
    {
        emit move_label(newPosition);
    }
    else if (mouseReleaseEvent->button() == Qt::RightButton) {}
    QLabel::mouseReleaseEvent(mouseReleaseEvent); // Передача события в базовый класс QLabel
}

void DraggableLabel::adjust_label_position(const QPoint &position)
{
    move(position);
    startPosition = position;
}


