#ifndef CPLAYSCENE_H
#define CPLAYSCENE_H

#include <QMainWindow>
#include <cmycoin.h>

class CPlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit CPlayScene(QWidget *parent = nullptr);
    explicit CPlayScene(int levelNum);
    int leveIndex; // 内部成员属性， 记录所选的选项卡
    // 重写painEvent事件
    void paintEvent(QPaintEvent *event) override;

    int gameArray[4][4]; // 二维数组数据 维护每个关卡的具体数据
    CMyCoin *coinBtn[4][4];
    // 是否胜利的标志
    bool isWin;

signals:
    void chooseSceneBack();

};

#endif // CPLAYSCENE_H
