#include "head.h"
#include <QKeyEvent>

HEAD::HEAD(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(170,170);
    i = 1;
    head_Img[0] = ":/Image/r1_head.png";
    head_Img[1] = ":/Image/r2_head.png";
}

void HEAD::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(head_Img[i]);
    painter.drawPixmap(0,0,170,170,pix);
}
void HEAD::change_Img(int a)
{
    i = a;
}

HEAD::~HEAD()
{

}

