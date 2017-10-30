#include "login.h"
#include <QKeyEvent>

LOGIN::LOGIN(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1500,1000);
    i = 0;
    login_Img[0] = ":/Image/login_1.png";
    login_Img[1] = ":/Image/login_2.png";
    login_Img[2] = ":/Image/login_3.png";
    login_Img[3] = ":/Image/login_4.png";
}

void LOGIN::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(login_Img[i]);
    painter.drawPixmap(0,0,1500,1000,pix);
    if(i == 3){
        i = 0;
    }else{
        i = i + 1;
    }
}

LOGIN::~LOGIN()
{

}

