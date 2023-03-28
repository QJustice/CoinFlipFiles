#ifndef CMYPUSHBUTTON_H
#define CMYPUSHBUTTON_H

#include <QPushButton>

class CMyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CMyPushButton(QWidget *parent = nullptr);

    // 构造函数 参数1 正常显示的图片路径 参数2 按下后显示的图片路径
    explicit CMyPushButton(QString normalImg, QString pressImg = "");
    // 成员属性 保存用户传入的默认显示路径 以及按下后显示的路径
    QString normalImgPath;
    QString pressImgPath;

    // 弹跳特效
    void zoom1();   //向下跳
    void zoom2();   //向上跳

    // 重写按钮 按下 和 释放
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:

};

#endif // CMYPUSHBUTTON_H
