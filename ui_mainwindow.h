/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <GLWidget.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCamera_1;
    QAction *actionCamera_2;
    QAction *actionWiki;
    QAction *actionSair;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionGouraud;
    QAction *actionPhong;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLWidget *glwidget;
    QMenuBar *menuBar;
    QMenu *menuCamera;
    QMenu *menuOp_es;
    QMenu *menuAjuda;
    QMenu *menuShaders;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 800);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../usr/share/icons/gnome/16x16/devices/display.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionCamera_1 = new QAction(MainWindow);
        actionCamera_1->setObjectName(QString::fromUtf8("actionCamera_1"));
        actionCamera_1->setCheckable(false);
        actionCamera_2 = new QAction(MainWindow);
        actionCamera_2->setObjectName(QString::fromUtf8("actionCamera_2"));
        actionCamera_2->setCheckable(false);
        actionWiki = new QAction(MainWindow);
        actionWiki->setObjectName(QString::fromUtf8("actionWiki"));
        actionSair = new QAction(MainWindow);
        actionSair->setObjectName(QString::fromUtf8("actionSair"));
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        actionGouraud = new QAction(MainWindow);
        actionGouraud->setObjectName(QString::fromUtf8("actionGouraud"));
        actionPhong = new QAction(MainWindow);
        actionPhong->setObjectName(QString::fromUtf8("actionPhong"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        glwidget = new GLWidget(centralWidget);
        glwidget->setObjectName(QString::fromUtf8("glwidget"));

        horizontalLayout->addWidget(glwidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QString::fromUtf8("menuCamera"));
        menuOp_es = new QMenu(menuBar);
        menuOp_es->setObjectName(QString::fromUtf8("menuOp_es"));
        menuAjuda = new QMenu(menuBar);
        menuAjuda->setObjectName(QString::fromUtf8("menuAjuda"));
        menuShaders = new QMenu(menuBar);
        menuShaders->setObjectName(QString::fromUtf8("menuShaders"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuOp_es->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuBar->addAction(menuShaders->menuAction());
        menuBar->addAction(menuAjuda->menuAction());
        menuCamera->addAction(actionCamera_1);
        menuCamera->addAction(actionCamera_2);
        menuOp_es->addAction(actionSair);
        menuAjuda->addAction(actionWiki);
        menuShaders->addAction(actionGouraud);
        menuShaders->addAction(actionPhong);
        toolBar->addAction(actionZoom_in);
        toolBar->addAction(actionZoom_out);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionCamera_1->setText(QApplication::translate("MainWindow", "Camera 1", 0, QApplication::UnicodeUTF8));
        actionCamera_1->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", 0, QApplication::UnicodeUTF8));
        actionCamera_2->setText(QApplication::translate("MainWindow", "Camera 2", 0, QApplication::UnicodeUTF8));
        actionCamera_2->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", 0, QApplication::UnicodeUTF8));
        actionWiki->setText(QApplication::translate("MainWindow", "Wiki...", 0, QApplication::UnicodeUTF8));
        actionWiki->setShortcut(QApplication::translate("MainWindow", "F1", 0, QApplication::UnicodeUTF8));
        actionSair->setText(QApplication::translate("MainWindow", "Sair", 0, QApplication::UnicodeUTF8));
        actionSair->setShortcut(QApplication::translate("MainWindow", "Shift+Esc", 0, QApplication::UnicodeUTF8));
        actionZoom_in->setText(QApplication::translate("MainWindow", "Zoom in", 0, QApplication::UnicodeUTF8));
        actionZoom_in->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0, QApplication::UnicodeUTF8));
        actionZoom_out->setText(QApplication::translate("MainWindow", "Zoom out", 0, QApplication::UnicodeUTF8));
        actionZoom_out->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0, QApplication::UnicodeUTF8));
        actionGouraud->setText(QApplication::translate("MainWindow", "Gouraud", 0, QApplication::UnicodeUTF8));
        actionGouraud->setShortcut(QApplication::translate("MainWindow", "Ctrl+G", 0, QApplication::UnicodeUTF8));
        actionPhong->setText(QApplication::translate("MainWindow", "Phong", 0, QApplication::UnicodeUTF8));
        actionPhong->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        menuCamera->setTitle(QApplication::translate("MainWindow", "Camera", 0, QApplication::UnicodeUTF8));
        menuOp_es->setTitle(QApplication::translate("MainWindow", "Op\303\247\303\265es", 0, QApplication::UnicodeUTF8));
        menuAjuda->setTitle(QApplication::translate("MainWindow", "Ajuda", 0, QApplication::UnicodeUTF8));
        menuShaders->setTitle(QApplication::translate("MainWindow", "Shaders", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
