#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QWidget>



class ClickableLabel : public QLabel
{
    Q_OBJECT

private:
    QString name;

protected:
    void mousePressEvent(QMouseEvent *) override;

public:
    explicit ClickableLabel(QString name, QWidget *parent = Q_NULLPTR) : QLabel(parent), name(name)  {}

};

#endif // CLICKABLELABEL_H
