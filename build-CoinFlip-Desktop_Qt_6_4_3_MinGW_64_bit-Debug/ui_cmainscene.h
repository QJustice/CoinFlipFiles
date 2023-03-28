/********************************************************************************
** Form generated from reading UI file 'cmainscene.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINSCENE_H
#define UI_CMAINSCENE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainScene
{
public:
    QAction *actionQuit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuStart;

    void setupUi(QMainWindow *CMainScene)
    {
        if (CMainScene->objectName().isEmpty())
            CMainScene->setObjectName("CMainScene");
        CMainScene->resize(800, 600);
        actionQuit = new QAction(CMainScene);
        actionQuit->setObjectName("actionQuit");
        centralwidget = new QWidget(CMainScene);
        centralwidget->setObjectName("centralwidget");
        CMainScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CMainScene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menuStart = new QMenu(menubar);
        menuStart->setObjectName("menuStart");
        CMainScene->setMenuBar(menubar);

        menubar->addAction(menuStart->menuAction());
        menuStart->addAction(actionQuit);

        retranslateUi(CMainScene);

        QMetaObject::connectSlotsByName(CMainScene);
    } // setupUi

    void retranslateUi(QMainWindow *CMainScene)
    {
        CMainScene->setWindowTitle(QCoreApplication::translate("CMainScene", "CMainScene", nullptr));
        actionQuit->setText(QCoreApplication::translate("CMainScene", "\351\200\200\345\207\272", nullptr));
        menuStart->setTitle(QCoreApplication::translate("CMainScene", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMainScene: public Ui_CMainScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINSCENE_H
