#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <role1.h>
#include <role2.h>
#include <weapon1.h>
#include <win.h>
#include <head.h>
#include <obstacle.h>
#include <easymusic.h>
#include <login.h>
#include <QPushButton>
#include "ui_form.h"

namespace Ui {
class Form;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);    //繪製背景圖
    void mousePressEvent(QMouseEvent *event);	//滑鼠點下事件
    void keyPressEvent(QKeyEvent *event);	//鍵盤事件
    void keyReleaseEvent(QKeyEvent *);      //鍵盤放開事件

private slots:
    void Game_T_Action();
    void Sp_Action();
    void login_Action();
    void role1_ActionW();        //角色一動作
    void role1_ActionS();
    void role1_ActionA();
    void role1_ActionD();
    void role2_ActionUp();        //角色二動作
    void role2_ActionDown();
    void role2_ActionLeft();
    void role2_ActionRight();
    void r1_ult_Action();
    void r2_ult_Action();
    void r1_wp1_Action();
    void r1_wp1_collisDete();
    void r2_wp1_Action();
    void r2_wp1_collisDete();
    void clicked_1p();
    void clicked_2p();
    void clicked_restart();
    void win_Action();

private:
    void create_role1();          // 產生角色一
    void create_role2();          // 產生角色二
    void create_r1_wp1();
    void create_r2_wp1();

    void gameLose();			 //遊戲結束
    void gameStart();			 //遊戲開始
    void gameRedy();             //遊戲預備

    ROLE1 *role1;			// 建立角色一
    ROLE2 *role2;            // 建立角色二
    LOGIN *login_bg;
    WIN *win;
    HEAD *r1_head;
    HEAD *r2_head;


    enum{WP1Count=10};		//  pipe 數量
    WEAPON1 *r1_wp1[WP1Count];
    WEAPON1 *r2_wp1[WP1Count];

    bool first_start = true;
    bool r1_ult_yn = false;
    bool r1_ult_act_yn = true;
    bool r2_ult_yn = false;
    bool r2_ult_act_yn = true;
    bool r1_wp1_Timer_yn = false;
    bool r2_wp1_Timer_yn = false;
    bool r1_win_yn = false;
    bool r2_win_yn = false;
    bool gaming_yn = false;
    bool win_yn = false;

    int r1_wp1_Acting[WP1Count];
    int r2_wp1_Acting[WP1Count];

    QTimer *Game_Timer;
    QTimer *Sp_Timer;
    QTimer *role1_TimerW;
    QTimer *role1_TimerS;
    QTimer *role1_TimerA;
    QTimer *role1_TimerD;
    QTimer *r1_ult_Timer;
    QTimer *r2_ult_Timer;
    QTimer *role2_TimerUp;
    QTimer *role2_TimerDown;
    QTimer *role2_TimerLeft;
    QTimer *role2_TimerRight;
    QTimer *r1_wp1_Timer;
    QTimer *r2_wp1_Timer;
    QTimer *login_Timer;
    QTimer *win_Timer;

    enum{lose=0,start=1,redy=2};  // Enum三個參數, 代表遊戲狀態
    int gamemod;		//目前遊戲狀態, 0=lose, 1=start, 2=redy
    // 遊戲狀態預設流程： redy -> start -> lose -> redy -> start .... 不斷循環

    int Game_Time = 120;
    int r1_win_count = 0;
    int r2_win_count = 0;
    int wp1_demage = 5;
    int wp2_demage = 10;
    int ult_demage = 15;
    int r1_ult_Time = 4;
    int r2_ult_Time = 4;
    int r1_Sp = 0;
    int r2_Sp = 0;
    int r1_Hp = 100;
    int r2_Hp = 100;
    int r1_role_v = 5;         //角色一速度
    int r2_role_v = 5;
    int r1_wp1_Tvalue;
    int r2_wp1_Tvalue;
    int last_r1_wp1;
    int last_r2_wp1;

    int win_width;      // 視窗寬度
    int win_height;     // 視窗高度
    int role1_TValue = 8;
    int role2_TValue = 8;
    int ult_TValue = 1000;
    int role1_Direction = 1;
    int role2_Direction = 1;
    int r1_wp1_Direction[WP1Count][2];
    int r2_wp1_Direction[WP1Count][2];

    easyMusic *login_m;     //背景音樂
    easyMusic *game_m;
    easyMusic *start_m;     //前景音樂
    easyMusic *end_m;
    easyMusic *bomb_m;
    easyMusic *hit_m;

    Ui::Form *ui;
};

#endif // MAINWINDOW_H
