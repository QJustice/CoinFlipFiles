#ifndef CMYCOIN_H
#define CMYCOIN_H

#include <QPushButton>

class CMyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit CMyCoin(QWidget *parent = nullptr);
    explicit CMyCoin(QString btnImg);
    // 金币翻转特效 金币的属性
    int posX;   // x坐标位置
    int posY;   // y坐标位置
    bool flag;  // 正反标示
    // 改变标志的方法
    void changeFlag();//改变标志,执行翻转效果
    QTimer *timer1; //正面翻反面 定时器
    QTimer *timer2; //反面翻正面 定时器
    int min = 1; //最小图片
    int max = 8; //最大图片

    // 执行动画标志
    bool isAnimation = false;

    // 重写按下
    void mousePressEvent(QMouseEvent *e) override;

    // 是否胜利
    bool isWin = false;

signals:

};

#endif // CMYCOIN_H
