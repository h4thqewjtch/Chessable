#include "draggablelabel.h"

bool DraggableLabel::is_pressed = false;


void DraggableLabel::mousePressEvent(QMouseEvent *mousePressEvent)
{

    if (mousePressEvent->button() == Qt::LeftButton)
    {
        startPosition = mousePressEvent->pos();
    }
    is_pressed = true;
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

void DraggableLabel::update_label_position(const QPoint &position)
{
    move(position);
    startPosition = position;
}

void DraggableLabel::set_pressed_false()
{
    is_pressed = false;
}

void DraggableLabel::simulateMousePress(QPoint pos)
{
    QMouseEvent pressEvent(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(this, &pressEvent);
}

void DraggableLabel::simulateMouseMove(QPoint pos)
{
    QMouseEvent moveEvent(QEvent::MouseMove, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(this, &moveEvent);
}

void DraggableLabel::simulateMouseRelease(QPoint pos)
{
    newPosition = pos;
    QMouseEvent releaseEvent(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(this, &releaseEvent);
}

bool DraggableLabel::pressed()
{
    return is_pressed;
}


