#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QApplication>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>

class DraggableLabel : public QLabel
{
    Q_OBJECT

private:
    QPoint startPosition;
    QPoint newPosition;
    static bool is_pressed;

protected:
    void mousePressEvent(QMouseEvent *) override;

    void mouseMoveEvent(QMouseEvent *) override;

    void mouseReleaseEvent(QMouseEvent *) override;

public:
    DraggableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

    void update_label_position(const QPoint &);

    void simulateMousePress(QPoint);

    void simulateMouseMove(QPoint);

    void simulateMouseRelease(QPoint);

    bool pressed();

    void set_pressed_false();

signals:
    void move_label(const QPoint &);

};

#endif // DRAGGABLELABEL_H
