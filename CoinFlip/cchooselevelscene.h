#ifndef CCHOOSELEVELSCENE_H
#define CCHOOSELEVELSCENE_H

#include <QMainWindow>
#include "cplayscene.h"

class CChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit CChooseLevelScene(QWidget *parent = nullptr);

    // 重写绘图事件
    void paintEvent(QPaintEvent *event) override;

    // 游戏场景的对象指针
    CPlayScene *play = nullptr;

signals:
    // 写一自定义信号，告诉主场景 点击了返回
    void chooseSceneBack();
};

#endif // CCHOOSELEVELSCENE_H
