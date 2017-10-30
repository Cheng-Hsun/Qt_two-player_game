#include "win.h"
#include <QKeyEvent>

WIN::WIN(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(520,130);
    i = 0;
    win_Img[0] = ":/Image/win_1.png";
    win_Img[1] = ":/Image/win_2.png";
}

void WIN::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(win_Img[i]);
    painter.drawPixmap(0,0,520,130,pix);
    if(i == 1){
        i = 0;
    }else{
        i = 1;
    }
}

WIN::~WIN()
{

}

