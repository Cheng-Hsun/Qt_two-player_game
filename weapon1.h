#ifndef WEAPON1_H
#define WEAPON1_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class WEAPON1 : public QWidget
{
    Q_OBJECT
public:
    explicit WEAPON1(QWidget *parent = 0);
    ~WEAPON1();
    void change_weapon1(int a);
    int num;

protected:
    void paintEvent(QPaintEvent *);

private:
    QString weapon1[5];

};

#endif // WEAPON1_H
