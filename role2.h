#ifndef ROLE2_H
#define ROLE2_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class ROLE2 : public QWidget
{
    Q_OBJECT
public:
    explicit ROLE2(QWidget *parent = 0);
    ~ROLE2();
    void change_Img(int a);

protected:
    void paintEvent(QPaintEvent *);

private:
    int i; //紀錄圖片編號
    QString role2_Img[4];

};

#endif // ROLE2_H
