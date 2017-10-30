#include "role1.h"
#include <QKeyEvent>

ROLE1::ROLE1(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(100,100);
    i = 1;
    role1_Img[0] = ":/Image/role1_Up.png";
    role1_Img[1] = ":/Image/role1_Down.png";
    role1_Img[2] = ":/Image/role1_Left.png";
    role1_Img[3] = ":/Image/role1_Right.png";
}

void ROLE1::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(role1_Img[i]);
    painter.drawPixmap(0,0,100,100,pix);
}
void ROLE1::change_Img(int a)
{
    i = a;
}

ROLE1::~ROLE1()
{

}

