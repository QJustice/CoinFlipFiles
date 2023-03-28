#include "cmainscene.h"
#include "ui_cmainscene.h"
#include <QPainter>
#include "cmypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSoundEffect>


CMainScene::CMainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainScene)
{
    ui->setupUi(this);

    // 配置主场景

    // 设置固定大小
    this->setFixedSize(320, 588);

    // 设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("翻金币");

    // 准备开始的音效
    QSoundEffect *startSount = new QSoundEffect(this);
    startSount->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    // -1是无限循环
//    startSount->setLoopCount(-1);
//    startSount->play();
    // 退出按钮实现
    connect(ui->actionQuit, &QAction::triggered, [=](){
       this->close();
    });

    // 开始按钮
    CMyPushButton *start_button = new CMyPushButton(":/res/MenuSceneStartButton.png");
    start_button->setParent(this);
    start_button->move(this->width() * 0.5 - start_button->width() * 0.5, this->height() * 0.7);

    // 实例化选择关卡场景中
    this->choose_scene = new CChooseLevelScene(this);

    // 监听选择关卡的返回按钮的信号
    connect(this->choose_scene, &CChooseLevelScene::chooseSceneBack, this, [=](){
        this->choose_scene->hide(); // 将选择关卡场景 隐藏掉
        this->setGeometry(this->choose_scene->geometry());
        this->show(); // 重新显示主场景
    });

    connect(start_button, &CMyPushButton::clicked, [=](){

        // 播放开始音效资源
        startSount->play();

        // 做一个弹起的特效
       start_button->zoom1();
       start_button->zoom2();
       // 延时进入
       QTimer::singleShot(500, this, [=](){
           // 进入到选择关卡场景中
           // 自身隐藏
           this->hide();
           // 设置chooseScene场景在位置
           this->choose_scene->setGeometry(this->geometry());
           // 显示选择关卡场景
           this->choose_scene->show();        
       });

    });
}

CMainScene::~CMainScene()
{
    delete ui;
}

void CMainScene::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(13, 10, pix);


}

