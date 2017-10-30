#include "weapon1.h"

WEAPON1::WEAPON1(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(150,150);
    num = 0;
    weapon1[0] = ":/Image/weapon1.png";
    weapon1[1] = ":/Image/weapon2.png";
    weapon1[2] = ":/Image/weapon3.png";
    weapon1[3] = ":/Image/weapon_r1_ult.png";
    weapon1[4] = ":/Image/weapon_r2_ult.png";
}


void WEAPON1::change_weapon1(int a)
{
    num = a;
}

void WEAPON1::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(weapon1[num]);
    if(num == 3 || num == 4){
        painter.drawPixmap(0,0,150,150,pix);
    }else{
        painter.drawPixmap(0,0,80,80,pix);
    }
}

WEAPON1::~WEAPON1()
{

}
