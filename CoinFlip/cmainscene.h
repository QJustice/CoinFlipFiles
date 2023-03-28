#ifndef CMAINSCENE_H
#define CMAINSCENE_H

#include <QMainWindow>
#include "cchooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CMainScene; }
QT_END_NAMESPACE

class CMainScene : public QMainWindow
{
    Q_OBJECT

public:
    CMainScene(QWidget *parent = nullptr);
    ~CMainScene();

    // 重写painEvent事件画背景图
    void paintEvent(QPaintEvent *event) override;

    CChooseLevelScene * choose_scene = nullptr;
private:
    Ui::CMainScene *ui;
};
#endif // CMAINSCENE_H
