#include "role2.h"

ROLE2::ROLE2(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(100,100);
    i = 1;
    role2_Img[0] = ":/Image/role2_Up.png";
    role2_Img[1] = ":/Image/role2_Down.png";
    role2_Img[2] = ":/Image/role2_Left.png";
    role2_Img[3] = ":/Image/role2_Right.png";
}


void ROLE2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(role2_Img[i]);
    painter.drawPixmap(0,0,100,100,pix);
}
void ROLE2::change_Img(int a)
{
    i = a;
}
ROLE2::~ROLE2()
{

}
