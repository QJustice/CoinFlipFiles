#include "cchooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "cmypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSoundEffect>

CChooseLevelScene::CChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    // 配置选择关卡场景
    this->setFixedSize(320, 588);

    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("选择关卡场景");

    // 创建菜单栏
    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);

    // 创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");

    // 创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    // 点击实现退出游戏
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    // 选择关卡按钮音效
    QSoundEffect *chooseSound  = new QSoundEffect(this);
    chooseSound ->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    // 返回按钮音效
    QSoundEffect *backSound   = new QSoundEffect(this);
    backSound  ->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    // 返回按钮
    CMyPushButton *backBtn = new CMyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    // 点击返回
    connect(backBtn, &CMyPushButton::clicked, [=](){
        // 告诉主场景 我返回了， 主场景监听CChooseLevelScene的返回按钮

        // 播放返回按钮的音效
        backSound->play();
        QTimer::singleShot(500, this, [=](){
             emit this->chooseSceneBack();
        });
    });

    // 创建选择关卡的按钮
    for (int i = 0; i < 20; i++)
    {
        CMyPushButton *menuBtn = new CMyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        connect(menuBtn, &CMyPushButton::clicked, [=](){
            QString str = QString("您选择的是第%1关").arg(i + 1);
            qDebug() << str.toUtf8().data();
            // 播放选择关卡的音效
            chooseSound->play();
            // 进入到游戏场景
            this->hide();   // 将选关场景隐藏掉
            this->play = new CPlayScene(i + 1);  // 创建游戏场景
            // 设置游戏在初始位置
            this->play->setGeometry(this->geometry());
            this->play->show(); // 显示游戏场景
            connect(this->play, &CPlayScene::chooseSceneBack, [=](){
                this->setGeometry(this->play->geometry());
                this->show();
                this->play->hide();
                delete this->play;
                this->play = nullptr;
            });
        });

        QLabel * label = new QLabel(this);
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        // 设置 label的对齐方式  水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        // 设置让鼠标进行穿透 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}

void CChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上图标
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
