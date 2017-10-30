#ifndef WIN_H
#define WIN_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

#include <QKeyEvent>

class WIN : public QWidget
{
    Q_OBJECT
public:
    explicit WIN(QWidget *parent = 0);
    ~WIN();

protected:
    void paintEvent(QPaintEvent *);

private:
    int i; //紀錄圖片編號
    QString win_Img[2];

};

#endif // WIN_H
