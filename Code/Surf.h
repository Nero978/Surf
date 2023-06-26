#pragma once

#include <QtWidgets/QWidget>
#include <QTimer>
#include <QTextBrowser>
#include "ui_Surf.h"
#include "player.h"
#include "About.h"
#include "Game.h"
#include "Guide.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioOutput>

class Surf : public QWidget
{
    Q_OBJECT

    

public:
    Surf(QWidget *parent = nullptr);
    ~Surf();
    int timerCount = 0;
    bool switchStatus = false;
    QTimer m_timer;
    QTimer switchTimer;
    About aboutWindow;
    Guide guideWindow;
    Game g;
    player player0;


    void initScene();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void chooseAnimo();
    void loadVersion();
    void startGame();
    void welcome();

    static Surf* getpIntence();

private:
    Ui::SurfClass ui;
    static Surf* pIntence; // 声明静态成员变量

};
