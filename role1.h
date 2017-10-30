#ifndef ROLE1_H
#define ROLE1_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

#include <QKeyEvent>

class ROLE1 : public QWidget
{
    Q_OBJECT
public:
    explicit ROLE1(QWidget *parent = 0);
    ~ROLE1();
    void change_Img(int a);

protected:
    void paintEvent(QPaintEvent *);

private:
    int i; //紀錄圖片編號
    QString role1_Img[4];

};

#endif // ROLE_H
