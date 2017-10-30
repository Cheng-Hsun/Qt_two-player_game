#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

#include <QKeyEvent>

class LOGIN : public QWidget
{
    Q_OBJECT
public:
    explicit LOGIN(QWidget *parent = 0);
    ~LOGIN();

protected:
    void paintEvent(QPaintEvent *);

private:
    int i; //紀錄圖片編號
    QString login_Img[4];

};

#endif // LOGIN_H
