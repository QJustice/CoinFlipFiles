#include "cplayscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "cmypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QFont>
#include "cmycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSoundEffect>

CPlayScene::CPlayScene(QWidget *parent)
    : QMainWindow{parent}
{

}

CPlayScene::CPlayScene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug() << str;
    this->leveIndex = levelNum;

    // 初始化游戏场景
    // 设置固定大小
    this->setFixedSize(320, 588);

    // 设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("翻金币");

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
    // 翻金币音效
    QSoundEffect *flipSound   = new QSoundEffect(this);
    flipSound  ->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    // 返回按钮音效
    QSoundEffect *backSound   = new QSoundEffect(this);
    backSound  ->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    // 胜利按钮音效
    QSoundEffect *winSound    = new QSoundEffect(this);
    winSound   ->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    // 返回按钮
    CMyPushButton *backBtn = new CMyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    // 点击返回
    connect(backBtn, &CMyPushButton::clicked, [=](){
        // 告诉主场景 我返回了， 主场景监听CChooseLevelScene的返回按钮

        // 播放音效
        backSound->play();
        QTimer::singleShot(500, this, [=](){
             emit this->chooseSceneBack();
        });
    });

    // 显示当前的关卡数
    QLabel *label = new QLabel(this);
    QFont font;
    font.setFamily("微软雅黑");
    font.setPointSize(20);
    QString str1 = QString("Level:%1").arg(this->leveIndex);
    // 将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height() - 50, 120, 50);

    dataConfig config;
    // 初始化每个关卡的二维数组
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->gameArray[i][j] = config.mData[this->leveIndex][i][j];
        }
    }

    // 胜利图片
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    // 显示金币背景图案
    // 创建金币的背景图片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            // 绘制背景图片
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel* label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i * 50, 200 + j * 50);

            if (1 == this->gameArray[i][j])
            {
                // 显示金币
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }

            // 创建金币
            CMyCoin *coin = new CMyCoin(str);
            coin->setParent(this);
            coin->move(59 + i * 50, 204 + j * 50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; // 1正面 0反面

            // 将金币放入金币的二维数组中以便后期的维护
            this->coinBtn[i][j] = coin;

            connect(coin, &CMyCoin::clicked, [=](){
                // 点击按钮，将所有的按钮先都禁用
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        this->coinBtn[i][j]->isWin = true;
                // 播放翻金币的音乐
                flipSound->play();
                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                // 翻转周围硬币, 延时翻转
                QTimer::singleShot(300, this, [=](){
                    // 周围右侧金币翻转的条件
                    if (coin->posX + 1 <= 3)
                    {
                        this->coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;

                    }

                    // 周围左侧金币翻转的条件
                    if (coin->posX - 1 >= 0)
                    {
                        this->coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                    }

                    // 周围上侧金币翻转的条件

                    if (coin->posY + 1 <= 3)
                    {
                        this->coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
                    }

                    // 周围下侧金币翻转的条件

                    if (coin->posY - 1 >= 0)
                    {
                        this->coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
                    }

                    // 翻完周围的金币后，将所有的按钮先都解开禁用
                    for (int i = 0; i < 4; i++)
                        for (int j = 0; j < 4; j++)
                            this->coinBtn[i][j]->isWin = false;

                    // 判断是否胜利
                    this->isWin = true;
                    for (int i = 0; i < 4; i++)
                        for (int j = 0; j < 4; j++)
                        {
                            if (coinBtn[i][j]->flag == false) // 只要有一个是反面，那就算失败
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    if (isWin == true)
                    {
                        // 将所有的胜利标志改为true, 如果再次点击直接return，不做响应
                        for (int i = 0; i < 4; i++)
                            for (int j = 0; j < 4; j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        winSound->play();
                        // 将胜利图片移动下来
                        QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                    }
                });
            });
        }
    }

}

void CPlayScene::paintEvent(QPaintEvent  *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
