#include "mainwindow.h"
#include <ctime>

#include "obstacle.h"
#include "role1.h"
#include "role2.h"
#include "weapon1.h"
#include "win.h"
#include "head.h"
#include "ui_form.h"
#include "login.h"
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QDockWidget>
#include <QTextEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Form)
{
    ui->setupUi(this);

    ui->r1_SP->hide();
    ui->r2_SP->hide();
    ui->r1_HP->hide();
    ui->r2_HP->hide();
    ui->game_time->hide();
    ui->r1_win_count->hide();
    ui->r2_win_count->hide();
    ui->r1_win_count->setText("0");
    ui->r2_win_count->setText("0");

    win_width = 1500;
    win_height = 1000;
    this->setFixedSize(win_width,win_height);	//視窗大小
    this->setWindowIcon(QIcon(":/Image/icon.png"));
    this->setWindowTitle("Bomber Man");

    Sp_Timer = new QTimer(this);
    connect(Sp_Timer,SIGNAL(timeout()),this,SLOT(Sp_Action()));

    QPixmap button_1p(":/Image/logbutton_1p.png");
    QIcon ButtonIcon_1p(button_1p);
    ui->pushButton_1p->setIcon(ButtonIcon_1p);
    ui->pushButton_1p->setIconSize(button_1p.rect().size());
    connect(ui->pushButton_1p,SIGNAL(clicked()),this,SLOT(clicked_1p()));

    QPixmap button_2p(":/Image/logbutton_2p.png");
    QIcon ButtonIcon_2p(button_2p);
    ui->pushButton_2p->setIcon(ButtonIcon_2p);
    ui->pushButton_2p->setIconSize(button_2p.rect().size());
    connect(ui->pushButton_2p,SIGNAL(clicked()),this,SLOT(clicked_2p()));

    QPixmap button_restart(":/Image/restart.png");
    QIcon ButtonIcon_restart(button_restart);
    ui->pushButton_restart->setIcon(ButtonIcon_restart);
    ui->pushButton_restart->setIconSize(button_restart.rect().size());
    ui->pushButton_restart->hide();

    role1 = new ROLE1(this);
    role1->hide();
    role2 = new ROLE2(this);
    role2->hide();
    win = new WIN(this);
    win->hide();

    r1_head = new HEAD(this);
    r1_head->change_Img(0);
    r1_head->hide();
    r2_head = new HEAD(this);
    r2_head->change_Img(1);
    r2_head->hide();

    login_bg = new LOGIN(this);
    login_bg->lower();
    login_bg->move(0,0);
    login_Timer = new QTimer(this);
    connect(login_Timer, SIGNAL(timeout()), this, SLOT(login_Action()));
    login_Timer->start(100);



    r1_wp1_Timer=new QTimer(this);
    r2_wp1_Timer=new QTimer(this);
    role2_TimerRight=new QTimer(this);
    role2_TimerLeft=new QTimer(this);
    role2_TimerDown=new QTimer(this);
    role2_TimerUp=new QTimer(this);
    role1_TimerD=new QTimer(this);
    role1_TimerA=new QTimer(this);
    role1_TimerS=new QTimer(this);
    role1_TimerW=new QTimer(this);
    Game_Timer = new QTimer(this);

    for(int i=0;i<WP1Count;i++){
        r1_wp1[i]=new WEAPON1(this);
        r1_wp1[i]->move(-300,300);
        r1_wp1_Acting[i] = 0;
        r2_wp1[i]=new WEAPON1(this);
        r2_wp1[i]->move(-300,300);
        r2_wp1_Acting[i] = 0;
    }

    last_r1_wp1 = 0;
    last_r2_wp1 = 0;

    gameRedy();

    login_m =new easyMusic("musicFile/login.mp3",50,1);
    login_m->play();
    /*bgm: 背景音樂
     * 第一個參數要放音樂檔案所在的路徑
     * 第二個參數要放音量大小(0-100)
     * 第三個參數是isLoop 1表示循環撥放 0表示只撥放一次
     */
    game_m =new easyMusic("musicFile/game.mp3",70,0);
    start_m = new easyMusic("musicFile/game_start.mp3",70,0);
    end_m = new easyMusic("musicFile/game_end.mp3",70,0);
    bomb_m = new easyMusic("musicFile/bomb.mp3",100,0);
    hit_m = new easyMusic("musicFile/hit.mp3",100,0);
}
void MainWindow::paintEvent(QPaintEvent *)		//繪圖事件, 用来產生背景
{
    // 可以在這裡新增背景圖片
    QPainter painter(this);  //宣告一個QPainter物件
    QPixmap bgImg;  //用QPixmap處理圖檔
    bgImg.load(":/Image/bg.png");  //載入圖檔路徑
    //使用drawPixmap(int x, int y,int width, int height,const QPixmap &pixmap)繪出圖檔
    painter.drawPixmap(0, 0, 1500, 1000, bgImg);
}

//===========   press     ==================
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 在這裡設定按下滑鼠要觸發的功能
    if(event->button()==Qt::LeftButton)
    {
        if(r2_Sp >= 5){
            bomb_m->play();
            if(!r2_ult_yn){
                r2_Sp -= 5;
                ui->r2_SP->setValue(r2_Sp);
                if(role2_Direction == 0){
                    r2_wp1_Direction[last_r2_wp1][0] = 0;
                    r2_wp1_Direction[last_r2_wp1][1] = -7;
                }else if(role2_Direction == 1){
                    r2_wp1_Direction[last_r2_wp1][0] = 0;
                    r2_wp1_Direction[last_r2_wp1][1] = 7;
                }else if(role2_Direction == 2){
                    r2_wp1_Direction[last_r2_wp1][0] = -7;
                    r2_wp1_Direction[last_r2_wp1][1] = 0;
                }else if(role2_Direction == 3){
                    r2_wp1_Direction[last_r2_wp1][0] = 7;
                    r2_wp1_Direction[last_r2_wp1][1] = 0;
                }
                r2_wp1_Acting[last_r2_wp1] = 1;
                r2_wp1[last_r2_wp1]->move(role2->pos().x(),role2->pos().y()+20);
                create_r2_wp1();
                r2_wp1_Timer->start(8);
            }else{
                if(role2_Direction == 0){
                    r2_wp1_Direction[last_r2_wp1][0] = 0;
                    r2_wp1_Direction[last_r2_wp1][1] = -10;
                }else if(role2_Direction == 1){
                    r2_wp1_Direction[last_r2_wp1][0] = 0;
                    r2_wp1_Direction[last_r2_wp1][1] = 10;
                }else if(role2_Direction == 2){
                    r2_wp1_Direction[last_r2_wp1][0] = -10;
                    r2_wp1_Direction[last_r2_wp1][1] = 0;
                }else if(role2_Direction == 3){
                    r2_wp1_Direction[last_r2_wp1][0] = 10;
                    r2_wp1_Direction[last_r2_wp1][1] = 0;
                }
                r2_wp1_Acting[last_r2_wp1] = 1;
                r2_wp1[last_r2_wp1]->move(role2->pos().x(),role2->pos().y()+20);
                create_r2_wp1();
                r2_wp1_Timer->start(8);
                if(r2_ult_act_yn){
                    r2_ult_Timer = new QTimer(this);
                    r2_ult_Timer->start((ult_TValue));
                    connect(r2_ult_Timer,SIGNAL(timeout()),this,SLOT(r2_ult_Action()));
                    r2_ult_act_yn = false;
                }
            }
            last_r2_wp1++;
            if(last_r2_wp1 == WP1Count){
                last_r2_wp1 = 0;
            }
        }
    }
    if(event->button()==Qt::RightButton)
    {

    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 在這裡設定按下鍵盤要觸發的功能
    if(gaming_yn){
    if(event->key()==Qt::Key_W)
    {
        role1_Direction = 0;
        role1->change_Img(0);
        if(role1_TimerS->isActive())
            role1_TimerS->stop();
        if(role1_TimerA->isActive())
            role1_TimerA->stop();
        if(role1_TimerD->isActive())
            role1_TimerD->stop();

        role1_TimerW=new QTimer(this);
        if(!role1_TimerW->isActive())
            role1_TimerW->start(role1_TValue);
        connect(role1_TimerW,SIGNAL(timeout()),this,SLOT(role1_ActionW()));
    }
    if(event->key()==Qt::Key_S)
    {
        role1_Direction = 1;
        role1->change_Img(1);
        if(role1_TimerW->isActive())
            role1_TimerW->stop();
        if(role1_TimerA->isActive())
            role1_TimerA->stop();
        if(role1_TimerD->isActive())
            role1_TimerD->stop();

        role1_TimerS=new QTimer(this);
        role1_TimerS->start(role1_TValue);
        connect(role1_TimerS,SIGNAL(timeout()),this,SLOT(role1_ActionS()));
    }
    if(event->key()==Qt::Key_A)
    {
        role1_Direction = 2;
        role1->change_Img(2);
        if(role1_TimerW->isActive())
            role1_TimerW->stop();
        if(role1_TimerS->isActive())
            role1_TimerS->stop();
        if(role1_TimerD->isActive())
            role1_TimerD->stop();

        role1_TimerA=new QTimer(this);
        role1_TimerA->start(role1_TValue);
        connect(role1_TimerA,SIGNAL(timeout()),this,SLOT(role1_ActionA()));
    }
    if(event->key()==Qt::Key_D)
    {
        role1_Direction = 3;
        role1->change_Img(3);
        if(role1_TimerW->isActive())
            role1_TimerW->stop();
        if(role1_TimerS->isActive())
            role1_TimerS->stop();
        if(role1_TimerA->isActive())
            role1_TimerA->stop();

        role1_TimerD=new QTimer(this);
        role1_TimerD->start(role1_TValue);
        connect(role1_TimerD,SIGNAL(timeout()),this,SLOT(role1_ActionD()));
    }
    if(event->key()==Qt::Key_Q)
    {
        if(r1_Sp >= 5){
            bomb_m->play();
            if(!r1_ult_yn){
                r1_Sp -= 5;
                ui->r1_SP->setValue(r1_Sp);
                if(role1_Direction == 0){
                    r1_wp1_Direction[last_r1_wp1][0] = 0;
                    r1_wp1_Direction[last_r1_wp1][1] = -7;
                }else if(role1_Direction == 1){
                    r1_wp1_Direction[last_r1_wp1][0] = 0;
                    r1_wp1_Direction[last_r1_wp1][1] = 7;
                }else if(role1_Direction == 2){
                    r1_wp1_Direction[last_r1_wp1][0] = -7;
                    r1_wp1_Direction[last_r1_wp1][1] = 0;
                }else if(role1_Direction == 3){
                    r1_wp1_Direction[last_r1_wp1][0] = 7;
                    r1_wp1_Direction[last_r1_wp1][1] = 0;
                }
                r1_wp1_Acting[last_r1_wp1] = 1;
                r1_wp1[last_r1_wp1]->move(role1->pos().x(),role1->pos().y()+20);
                create_r1_wp1();
                r1_wp1_Timer->start(8);
            }else{
                if(role1_Direction == 0){
                    r1_wp1_Direction[last_r1_wp1][0] = 0;
                    r1_wp1_Direction[last_r1_wp1][1] = -10;
                }else if(role1_Direction == 1){
                    r1_wp1_Direction[last_r1_wp1][0] = 0;
                    r1_wp1_Direction[last_r1_wp1][1] = 10;
                }else if(role1_Direction == 2){
                    r1_wp1_Direction[last_r1_wp1][0] = -10;
                    r1_wp1_Direction[last_r1_wp1][1] = 0;
                }else if(role1_Direction == 3){
                    r1_wp1_Direction[last_r1_wp1][0] = 10;
                    r1_wp1_Direction[last_r1_wp1][1] = 0;
                }
                r1_wp1_Acting[last_r1_wp1] = 1;
                r1_wp1[last_r1_wp1]->move(role1->pos().x(),role1->pos().y()+20);
                create_r1_wp1();
                r1_wp1_Timer->start(8);
                if(r1_ult_act_yn){
                    r1_ult_Timer=new QTimer(this);
                    r1_ult_Timer->start(ult_TValue);
                    connect(r1_ult_Timer,SIGNAL(timeout()),this,SLOT(r1_ult_Action()));
                    r1_ult_act_yn = false;
                }
            }
            last_r1_wp1++;
            if(last_r1_wp1 == WP1Count){
                last_r1_wp1 = 0;
            }
        }
    }
    //======================================================================

    if(event->key()==Qt::Key_8)
    {
        role2_Direction = 0;
        role2->change_Img(0);
        if(role2_TimerDown->isActive())
            role2_TimerDown->stop();
        if(role2_TimerLeft->isActive())
            role2_TimerLeft->stop();
        if(role2_TimerRight->isActive())
            role2_TimerRight->stop();

        role2_TimerUp=new QTimer(this);
        role2_TimerUp->start(role1_TValue);
        connect(role2_TimerUp,SIGNAL(timeout()),this,SLOT(role2_ActionUp()));
    }
    if(event->key()==Qt::Key_5)
    {
        role2_Direction = 1;
        role2->change_Img(1);
        if(role2_TimerUp->isActive())
            role2_TimerUp->stop();
        if(role2_TimerLeft->isActive())
            role2_TimerLeft->stop();
        if(role2_TimerRight->isActive())
            role2_TimerRight->stop();

        role2_TimerDown=new QTimer(this);
        role2_TimerDown->start(role1_TValue);
        connect(role2_TimerDown,SIGNAL(timeout()),this,SLOT(role2_ActionDown()));
    }
    if(event->key()==Qt::Key_4)
    {
        role2_Direction = 2;
        role2->change_Img(2);
        if(role2_TimerUp->isActive())
            role2_TimerUp->stop();
        if(role2_TimerDown->isActive())
            role2_TimerDown->stop();
        if(role2_TimerRight->isActive())
            role2_TimerRight->stop();

        role2_TimerLeft=new QTimer(this);
        role2_TimerLeft->start(role1_TValue);
        connect(role2_TimerLeft,SIGNAL(timeout()),this,SLOT(role2_ActionLeft()));
    }
    if(event->key()==Qt::Key_6)
    {
        role2_Direction = 3;
        role2->change_Img(3);
        if(role2_TimerUp->isActive())
            role2_TimerUp->stop();
        if(role2_TimerDown->isActive())
            role2_TimerDown->stop();
        if(role2_TimerLeft->isActive())
            role2_TimerLeft->stop();

        role2_TimerRight=new QTimer(this);
        role2_TimerRight->start(role1_TValue);
        connect(role2_TimerRight,SIGNAL(timeout()),this,SLOT(role2_ActionRight()));
    }
    if(event->key()==Qt::Key_7)
    {
        if(r2_Sp >= 5){
            bomb_m->play();
            if(!r2_ult_yn){
                r2_Sp -= 5;
                ui->r2_SP->setValue(r2_Sp);
                if(role2_Direction == 0){
                    r2_wp1_Direction[last_r2_wp1][0] = 0;
                    r2_wp1_Direction[last_r2_wp1][1] = -7;
                }else if(role2_Direction == 1){
                    r2_wp1_Direction[last_r2_wp1][0] = 0;
                    r2_wp1_Direction[last_r2_wp1][1] = 7;
                }else if(role2_Direction == 2){
                    r2_wp1_Direction[last_r2_wp1][0] = -7;
                    r2_wp1_Direction[last_r2_wp1][1] = 0;
                }else if(role2_Direction == 3){
                    r2_wp1_Direction[last_r2_wp1][0] = 7;
                    r2_wp1_Direction[last_r2_wp1][1] = 0;
                }
                r2_wp1_Acting[last_r2_wp1] = 1;
                r2_wp1[last_r2_wp1]->move(role2->pos().x(),role2->pos().y()+20);
                create_r2_wp1();
                r2_wp1_Timer->start(8);
            }else{
                if(role2_Direction == 0){
                    r2_wp1_Direction[last_r2_wp1][0] = 0;
                    r2_wp1_Direction[last_r2_wp1][1] = -10;
                }else if(role2_Direction == 1){
                    r2_wp1_Direction[last_r2_wp1][0] = 0;
                    r2_wp1_Direction[last_r2_wp1][1] = 10;
                }else if(role2_Direction == 2){
                    r2_wp1_Direction[last_r2_wp1][0] = -10;
                    r2_wp1_Direction[last_r2_wp1][1] = 0;
                }else if(role2_Direction == 3){
                    r2_wp1_Direction[last_r2_wp1][0] = 10;
                    r2_wp1_Direction[last_r2_wp1][1] = 0;
                }
                r2_wp1_Acting[last_r2_wp1] = 1;
                r2_wp1[last_r2_wp1]->move(role2->pos().x(),role2->pos().y()+20);
                create_r2_wp1();
                r2_wp1_Timer->start(8);
                if(r2_ult_act_yn){
                    r2_ult_Timer = new QTimer(this);
                    r2_ult_Timer->start((ult_TValue));
                    connect(r2_ult_Timer,SIGNAL(timeout()),this,SLOT(r2_ult_Action()));
                    r2_ult_act_yn = false;
                }
            }
            last_r2_wp1++;
            if(last_r2_wp1 == WP1Count){
                last_r2_wp1 = 0;
            }
        }
    }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        role1_TimerW->stop();
    }
    if(event->key()==Qt::Key_S)
    {
        role1_TimerS->stop();
    }
    if(event->key()==Qt::Key_A)
    {
        role1_TimerA->stop();
    }
    if(event->key()==Qt::Key_D)
    {
        role1_TimerD->stop();
    }
    if(event->key()==Qt::Key_8)
    {
        role2_TimerUp->stop();
    }
    if(event->key()==Qt::Key_5)
    {
        role2_TimerDown->stop();
    }
    if(event->key()==Qt::Key_4)
    {
        role2_TimerLeft->stop();
    }
    if(event->key()==Qt::Key_6)
    {
        role2_TimerRight->stop();
    }
}

//===========   create     ==================
void MainWindow::create_role1()
{
    role1->show();
    role1->move(300,150);
}
void MainWindow::create_role2()
{
    role2->show();
    role2->move(1100,850);
}
void MainWindow::create_r1_wp1()
{
    if(!r1_wp1_Timer_yn){
        r1_wp1_Timer=new QTimer(this);
        connect(r1_wp1_Timer,SIGNAL(timeout()),this,SLOT(r1_wp1_Action()));        
        connect(r1_wp1_Timer,SIGNAL(timeout()),this,SLOT(r1_wp1_collisDete()));
        r1_wp1_Timer_yn = true;
    }
}
void MainWindow::create_r2_wp1()
{
    if(!r2_wp1_Timer_yn){
        r2_wp1_Timer=new QTimer(this);
        connect(r2_wp1_Timer,SIGNAL(timeout()),this,SLOT(r2_wp1_Action()));
        connect(r2_wp1_Timer,SIGNAL(timeout()),this,SLOT(r2_wp1_collisDete()));
        r2_wp1_Timer_yn = true;
    }
}

//===========   Action     ==================
void MainWindow::Game_T_Action()
{
    --Game_Time;
    ui->game_time->setText(QString::number(Game_Time));
    if(Game_Time == 0)
        gameLose();

}
void MainWindow::Sp_Action()
{
    if(r1_Sp != 100){
        r1_Sp++;
        ui->r1_SP->setValue(r1_Sp);
    }
    if(r1_Sp < 50){
        r1_wp1[last_r1_wp1]->change_weapon1(0);
        ui->r1_SP->setStyleSheet("::chunk{background-color: rgb(67, 218, 65)}");
    }else if(r1_Sp < 100){
        r1_wp1[last_r1_wp1]->change_weapon1(1);
        ui->r1_SP->setStyleSheet("::chunk{background-color: rgb(42, 136, 40)}");
    }else if(r1_Sp == 100){
        r1_wp1[last_r1_wp1]->change_weapon1(3);
        r1_ult_yn = true;
        r1_role_v = 8;
        ui->r1_SP->setStyleSheet("::chunk{background-color: rgb(22, 70, 20)}");
    }


    if(r2_Sp != 100){
        r2_Sp++;
        ui->r2_SP->setValue(r2_Sp);
    }
    if(r2_Sp < 50){
        r2_wp1[last_r2_wp1]->change_weapon1(0);
        ui->r2_SP->setStyleSheet("::chunk{background-color: rgb(67, 218, 65)}");
    }else if(r2_Sp < 100){
        r2_wp1[last_r2_wp1]->change_weapon1(2);
        ui->r2_SP->setStyleSheet("::chunk{background-color: rgb(42, 136, 40)}");
    }else if(r2_Sp == 100){
        r2_wp1[last_r2_wp1]->change_weapon1(4);
        r2_ult_yn = true;
        r2_role_v = 8;
        ui->r2_SP->setStyleSheet("::chunk{background-color: rgb(22, 70, 20)}");
    }
}

void MainWindow::role1_ActionW()
{
    if(role1->pos().y()-r1_role_v > 95){
        role1->move(role1->pos().x(),role1->pos().y()-r1_role_v);
    }
}
void MainWindow::role1_ActionS()
{
    if(role1->pos().y()+r1_role_v < 890){
        role1->move(role1->pos().x(),role1->pos().y()+r1_role_v);
    }
}
void MainWindow::role1_ActionA()
{
    if(role1->pos().x()-r1_role_v > 190){
        role1->move(role1->pos().x()-r1_role_v,role1->pos().y());
    }
}
void MainWindow::role1_ActionD()
{
    if(role1->pos().x()+r1_role_v < 1210){
        role1->move(role1->pos().x()+r1_role_v,role1->pos().y());
    }
}
void MainWindow::r1_ult_Action()
{
    if(r1_ult_Time != 0){
        r1_Sp = 100;
        ui->r1_SP->setValue(r1_Sp);
        r1_ult_Time--;
    }else{
        r1_ult_Timer->stop();
        r1_ult_Time = 4;
        r1_role_v = 5;
        r1_Sp = 0;
        ui->r1_SP->setValue(r1_Sp);
        r1_ult_yn = false;
        r1_ult_act_yn = true;
    }
}
void MainWindow::r2_ult_Action()
{
    if(r2_ult_Time != 0){
        r2_Sp = 100;
        ui->r2_SP->setValue(r2_Sp);
        r2_ult_Time--;
    }else{
        r2_ult_Timer->stop();
        r2_ult_Time = 4;
        r2_role_v = 5;
        r2_Sp = 0;
        ui->r2_SP->setValue(r2_Sp);
        r2_ult_yn = false;
        r2_ult_act_yn = true;
    }
}
void MainWindow::role2_ActionUp()
{
    if(role2->pos().y()-r2_role_v > 95){
        role2->move(role2->pos().x(),role2->pos().y()-r2_role_v);
    }
}
void MainWindow::role2_ActionDown()
{
    if(role2->pos().y()+r2_role_v < 890){
        role2->move(role2->pos().x(),role2->pos().y()+r2_role_v);
    }
}
void MainWindow::role2_ActionLeft()
{
    if(role2->pos().x()-r2_role_v > 190){
        role2->move(role2->pos().x()-r2_role_v,role2->pos().y());
    }
}
void MainWindow::role2_ActionRight()
{
    if(role2->pos().x()+r2_role_v < 1210){
        role2->move(role2->pos().x()+r2_role_v,role2->pos().y());
    }
}
void MainWindow::r1_wp1_Action()
{
    for(int i=0;i<WP1Count;i++)
    {
        if(r1_wp1_Acting[i] == 1)
        {
            r1_wp1[i]->move(r1_wp1[i]->pos().x()+r1_wp1_Direction[i][0],r1_wp1[i]->pos().y()+r1_wp1_Direction[i][1]);
        }
        if(r1_wp1[i]->pos().x()>1600 || r1_wp1[i]->pos().y()>1100)
        {
            r1_wp1[i]->move(-300,300);
            r1_wp1_Acting[i] = 0;
        }
    }
}
void MainWindow::r1_wp1_collisDete()
{
    for(int i=0;i<WP1Count;i++)
    {
        if(!r1_ult_yn){
            if(role2->pos().x()+50>r1_wp1[i]->pos().x() && role2->pos().x()+50<r1_wp1[i]->pos().x()+80
                    && role2->pos().y()+90>r1_wp1[i]->pos().y() && role2->pos().y()+90<r1_wp1[i]->pos().y()+80){
                r1_wp1[i]->move(-300,300);
                r1_wp1_Acting[i] = 0;
                r2_Sp -= 5;
                ui->r2_SP->setValue(r2_Sp);
                hit_m->play();
                if(r1_wp1[i]->num == 0){
                    r2_Hp -= wp1_demage;
                }else if(r1_wp1[i]->num == 1){
                    r2_Hp -= wp2_demage;
                }
                ui->r2_HP->setValue(r2_Hp);
                if(r2_Hp <= 0){
                    ui->r2_HP->setValue(0);
                    r1_win_yn = true;
                    gameLose();
                }
            }
        }else{
            if(role2->pos().x()+50>r1_wp1[i]->pos().x() && role2->pos().x()+50<r1_wp1[i]->pos().x()+150
                    && role2->pos().y()+90>r1_wp1[i]->pos().y() && role2->pos().y()+90<r1_wp1[i]->pos().y()+150){
                r1_wp1[i]->move(-300,300);
                r1_wp1_Acting[i] = 0;
                r2_Sp -= 15;
                ui->r2_SP->setValue(r2_Sp);
                r2_Hp -= ult_demage;
                ui->r2_HP->setValue(r2_Hp);
                hit_m->play();
                if(r2_Hp <= 0){
                    ui->r2_HP->setValue(0);
                    r1_win_yn = true;
                    r2_ult_yn = false;
                    gameLose();
                }
            }
        }
    }
}
void MainWindow::r2_wp1_Action()
{
    for(int i=0;i<WP1Count;i++)
    {
        if(r2_wp1_Acting[i] == 1)
        {
            r2_wp1[i]->move(r2_wp1[i]->pos().x()+r2_wp1_Direction[i][0],r2_wp1[i]->pos().y()+r2_wp1_Direction[i][1]);
        }
        if(r2_wp1[i]->pos().x()>1600 || r2_wp1[i]->pos().y()>1100)
        {
            r2_wp1[i]->move(-300,300);
            r2_wp1_Acting[i] = 0;
        }
    }
}
void MainWindow::r2_wp1_collisDete()
{
    for(int i=0;i<WP1Count;i++)
    {
        if(!r2_ult_yn){
            if(role1->pos().x()+50>r2_wp1[i]->pos().x() && role1->pos().x()+50<r2_wp1[i]->pos().x()+80
                    && role1->pos().y()+90>r2_wp1[i]->pos().y() && role1->pos().y()+90<r2_wp1[i]->pos().y()+80){
                r2_wp1[i]->move(-300,300);
                r2_wp1_Acting[i] = 0;
                r1_Sp -= 5;
                ui->r1_SP->setValue(r1_Sp);
                if(r2_wp1[i]->num == 0){
                    r1_Hp -= wp1_demage;
                }else if(r2_wp1[i]->num == 2){
                    r1_Hp -= wp2_demage;
                }
                ui->r1_HP->setValue(r1_Hp);
                hit_m->play();
                if(r1_Hp <= 0){
                    ui->r1_HP->setValue(0);
                    r2_win_yn = true;
                    gameLose();
                }
            }
        }else{
            if(role1->pos().x()+50>r2_wp1[i]->pos().x() && role1->pos().x()+50<r2_wp1[i]->pos().x()+150
                    && role1->pos().y()+90>r2_wp1[i]->pos().y() && role1->pos().y()+90<r2_wp1[i]->pos().y()+150){
                r2_wp1[i]->move(-300,300);
                r2_wp1_Acting[i] = 0;
                r1_Sp -= 5;
                ui->r1_SP->setValue(r1_Sp);
                r1_Hp -= ult_demage;
                ui->r1_HP->setValue(r1_Hp);
                hit_m->play();
                if(r1_Hp <= 0){
                    ui->r1_HP->setValue(0);
                    r2_win_yn = true;
                    r1_ult_yn = false;
                    gameLose();
                }
            }
        }
    }
}

void MainWindow::login_Action()
{
    login_bg->move(1,0);
    login_bg->move(0,0);
}

void MainWindow::win_Action()
{
    win->move(win->x()+1,0);
    win->move(win->x()-1,0);
}
void MainWindow::gameRedy()
{
    gamemod=redy;
}
void MainWindow::gameLose()
{
    gamemod=lose;
    end_m->play();
    game_m->stop();

    gaming_yn = false;
    Game_Timer->stop();

    ui->pushButton_restart->show();
    connect(ui->pushButton_restart,SIGNAL(clicked()),this,SLOT(clicked_restart()));

    if(r1_win_yn){
        win->show();
        win->move(60,100);
        win_Timer = new QTimer(this);
        connect(win_Timer, SIGNAL(timeout()), this, SLOT(win_Action()));
        win_Timer->start(200);
    }
    if(r2_win_yn){
        win->show();
        win->move(920,100);
        win_Timer = new QTimer(this);
        connect(win_Timer, SIGNAL(timeout()), this, SLOT(win_Action()));
        win_Timer->start(200);
    }
}
void MainWindow::gameStart()
{
    gaming_yn = true;

    start_m->play();
    game_m->play();
    login_m->stop();

    win->hide();
    if(r1_ult_yn){
        r1_ult_Timer->stop();
    }
    if(r2_ult_yn){
        r2_ult_Timer->stop();
    }
    if(r1_win_yn){
        ++r1_win_count;
        ui->r1_win_count->setText(QString::number(r1_win_count));
        win_Timer->stop();
    }
    if(r2_win_yn){
        ++r2_win_count;
        ui->r2_win_count->setText(QString::number(r2_win_count));
        win_Timer->stop();
    }
    ui->r1_SP->setStyleSheet("::chunk{background-color: rgb(67, 218, 65)}");
    ui->r2_SP->setStyleSheet("::chunk{background-color: rgb(67, 218, 65)}");

    r1_head->move(12,105);
    r1_head->show();
    r2_head->move(1310,95);
    r2_head->show();

    r1_win_yn = false;
    r2_win_yn = false;
    r1_ult_yn = false;
    r1_ult_act_yn = true;
    r2_ult_yn = false;
    r2_ult_act_yn = true;

    r1_wp1_Timer_yn = false;
    r2_wp1_Timer_yn = false;


    ui->pushButton_restart->hide();
    create_role1();
    create_role2();
    Game_Time = 120;
    r1_ult_Time = 3;
    r2_ult_Time = 3;
    r1_Sp = 0;
    r2_Sp = 0;
    r1_Hp = 100;
    r2_Hp = 100;
    r1_role_v = 5;
    r2_role_v = 5;
    ui->r1_SP->setValue(r1_Sp);
    ui->r1_HP->setValue(r1_Hp);
    ui->r2_SP->setValue(r2_Sp);
    ui->r2_HP->setValue(r2_Hp);
    ui->r1_SP->show();
    ui->r1_HP->show();
    ui->r2_SP->show();
    ui->r2_HP->show();
    ui->game_time->show();
    ui->game_time->setText(QString::number(Game_Time));
    ui->r1_win_count->show();
    ui->r2_win_count->show();
    Sp_Timer->start(200);

    ui->pushButton_1p->hide();
    ui->pushButton_2p->hide();

    gamemod=start;

    role1_TimerW->stop();
    role1_TimerS->stop();
    role1_TimerA->stop();
    role1_TimerD->stop();
    role2_TimerUp->stop();
    role2_TimerDown->stop();
    role2_TimerLeft->stop();
    role2_TimerRight->stop();
    r1_wp1_Timer->stop();
    r2_wp1_Timer->stop();

    Game_Timer->start(1000);
    if(first_start){
        connect(Game_Timer,SIGNAL(timeout()),this,SLOT(Game_T_Action()));
        first_start = false;
    }
}
void MainWindow::clicked_1p()
{
    login_bg->hide();
    login_Timer->stop();
    gameStart();
}
void MainWindow::clicked_2p()
{
    login_bg->hide();
    login_Timer->stop();
    gameStart();
}
void MainWindow::clicked_restart()
{
    gameStart();
}
