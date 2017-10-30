#ifndef HEAD_H
#define HEAD_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

#include <QKeyEvent>

class HEAD : public QWidget
{
    Q_OBJECT
public:
    explicit HEAD(QWidget *parent = 0);
    ~HEAD();
    void change_Img(int a);

protected:
    void paintEvent(QPaintEvent *);

private:
    int i; //紀錄圖片編號
    QString head_Img[4];

};

#endif // HEAD_H
