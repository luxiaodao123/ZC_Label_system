/********************************************************************************
** Form generated from reading UI file 'labelmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABELMAINWINDOW_H
#define UI_LABELMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyLabel/paintlabel.h"

QT_BEGIN_NAMESPACE

class Ui_LabelMainWindow
{
public:
    QAction *AccountManagement;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_7;
    QAction *createnew;
    QAction *allsave;
    QAction *load;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QToolButton *edit;
    QToolButton *big;
    QToolButton *small;
    QToolButton *save;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QLabel *label_7;
    PaintLabel *label_8;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QListWidget *donot;
    QLabel *label_9;
    QLabel *label_10;
    QListWidget *already;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *last;
    QPushButton *next;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *listWidget;
    QTreeWidget *focuslabel;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LabelMainWindow)
    {
        if (LabelMainWindow->objectName().isEmpty())
            LabelMainWindow->setObjectName(QStringLiteral("LabelMainWindow"));
        LabelMainWindow->resize(1592, 1030);
        AccountManagement = new QAction(LabelMainWindow);
        AccountManagement->setObjectName(QStringLiteral("AccountManagement"));
        action_2 = new QAction(LabelMainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(LabelMainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_4 = new QAction(LabelMainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_5 = new QAction(LabelMainWindow);
        action_5->setObjectName(QStringLiteral("action_5"));
        action_7 = new QAction(LabelMainWindow);
        action_7->setObjectName(QStringLiteral("action_7"));
        createnew = new QAction(LabelMainWindow);
        createnew->setObjectName(QStringLiteral("createnew"));
        allsave = new QAction(LabelMainWindow);
        allsave->setObjectName(QStringLiteral("allsave"));
        load = new QAction(LabelMainWindow);
        load->setObjectName(QStringLiteral("load"));
        centralwidget = new QWidget(LabelMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMaximumSize(QSize(16777215, 30));
        edit = new QToolButton(widget_3);
        edit->setObjectName(QStringLiteral("edit"));
        edit->setGeometry(QRect(10, 10, 37, 18));
        big = new QToolButton(widget_3);
        big->setObjectName(QStringLiteral("big"));
        big->setGeometry(QRect(50, 10, 37, 18));
        small = new QToolButton(widget_3);
        small->setObjectName(QStringLiteral("small"));
        small->setGeometry(QRect(90, 10, 37, 18));
        save = new QToolButton(widget_3);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(130, 10, 37, 18));

        gridLayout->addWidget(widget_3, 1, 1, 1, 1);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(700, 333));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1048, 737));
        label_7 = new QLabel(scrollAreaWidgetContents_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(0, 0, 1000, 666));
        label_8 = new PaintLabel(scrollAreaWidgetContents_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(0, 0, 1000, 666));
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout->addWidget(scrollArea, 2, 1, 2, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(256, 16777215));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("    QTreeWidget{  \n"
"        background-color: #5B677A;  \n"
"      \n"
"        /* set the font properties*/  \n"
"        font-size:17px;  \n"
"        color: white;  \n"
"    } "));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        donot = new QListWidget(widget);
        donot->setObjectName(QStringLiteral("donot"));
        donot->setStyleSheet(QLatin1String("    QListWidget{  \n"
"        background-color: #5B677A;  \n"
"      \n"
"        /* set the font properties*/  \n"
"        font-size:17px;  \n"
"        color: white;  \n"
"    } \n"
"\n"
"QListWidget::item:hover {  \n"
"    background: rgb(69, 187, 217);;  \n"
"}  \n"
"  \n"
"QListWidget::item:selected:active{  \n"
"    background: rgb(63, 147, 168);  \n"
"}  \n"
"  \n"
"QListWidget::item:selected:!active {  \n"
"    background: rgb(63, 147, 168);  \n"
"}"));

        gridLayout_2->addWidget(donot, 2, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setStyleSheet(QLatin1String("QLabel{\n"
"background-color: rgb(0, 255, 255);\n"
"}"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setStyleSheet(QLatin1String("QLabel{\n"
"background-color: rgb(0, 255, 255);\n"
"}"));

        gridLayout_2->addWidget(label_10, 3, 0, 1, 1);

        already = new QListWidget(widget);
        already->setObjectName(QStringLiteral("already"));
        already->setStyleSheet(QLatin1String("    QListWidget{  \n"
"        background-color: #5B677A;  \n"
"      \n"
"        /* set the font properties*/  \n"
"        font-size:17px;  \n"
"        color: white;  \n"
"    } \n"
"\n"
"QListWidget::item:hover {  \n"
"    background: rgb(69, 187, 217);;  \n"
"}  \n"
"  \n"
""));

        gridLayout_2->addWidget(already, 4, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 5, 1);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMaximumSize(QSize(16777215, 140));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_6 = new QLabel(widget_5);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        last = new QPushButton(widget_5);
        last->setObjectName(QStringLiteral("last"));
        last->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(last);

        next = new QPushButton(widget_5);
        next->setObjectName(QStringLiteral("next"));
        next->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(next);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget_5);

        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        horizontalLayout_3 = new QHBoxLayout(widget_6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        listWidget = new QListWidget(widget_6);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout_3->addWidget(listWidget);


        verticalLayout->addWidget(widget_6);


        gridLayout->addWidget(widget_4, 4, 1, 1, 1);

        focuslabel = new QTreeWidget(centralwidget);
        focuslabel->setObjectName(QStringLiteral("focuslabel"));
        focuslabel->setMaximumSize(QSize(256, 16777215));
        focuslabel->setStyleSheet(QLatin1String("    QTreeWidget{  \n"
"        background-color: #5B677A;  \n"
"      \n"
"        /* set the font properties*/  \n"
"        font-size:17px;  \n"
"        color: white;  \n"
"    } \n"
"\n"
"QTreeWidget::item:hover {  \n"
"    background: rgb(69, 187, 217);;  \n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:active{  \n"
"    background: rgb(63, 147, 168);  \n"
"}  \n"
"  \n"
"QTreeWidget::item:selected:!active {  \n"
"    background: rgb(63, 147, 168);  \n"
"}  "));

        gridLayout->addWidget(focuslabel, 1, 2, 4, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(500, 0));

        horizontalLayout->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(500, 0));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addWidget(widget_2, 0, 1, 1, 2);

        LabelMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LabelMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1592, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        LabelMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LabelMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        LabelMainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(createnew);
        menu->addAction(load);

        retranslateUi(LabelMainWindow);

        QMetaObject::connectSlotsByName(LabelMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LabelMainWindow)
    {
        LabelMainWindow->setWindowTitle(QApplication::translate("LabelMainWindow", "MainWindow", 0));
        AccountManagement->setText(QApplication::translate("LabelMainWindow", "\350\264\246\346\210\267\347\256\241\347\220\206", 0));
        action_2->setText(QApplication::translate("LabelMainWindow", "\346\235\203\351\231\220\347\256\241\347\220\206", 0));
        action_3->setText(QApplication::translate("LabelMainWindow", "\347\273\237\350\256\241\345\210\206\346\236\220", 0));
        action_4->setText(QApplication::translate("LabelMainWindow", "\347\273\223\346\236\234\345\257\274\345\207\272", 0));
        action_5->setText(QApplication::translate("LabelMainWindow", "\346\227\245\345\277\227\347\256\241\347\220\206", 0));
        action_7->setText(QApplication::translate("LabelMainWindow", "\345\267\245\344\275\234\346\250\241\345\274\217", 0));
        createnew->setText(QApplication::translate("LabelMainWindow", "\346\226\260\345\273\272", 0));
        allsave->setText(QApplication::translate("LabelMainWindow", "\344\277\235\345\255\230", 0));
        load->setText(QApplication::translate("LabelMainWindow", "\345\257\274\345\205\245", 0));
        edit->setText(QApplication::translate("LabelMainWindow", "...", 0));
        big->setText(QApplication::translate("LabelMainWindow", "...", 0));
        small->setText(QApplication::translate("LabelMainWindow", "...", 0));
        save->setText(QApplication::translate("LabelMainWindow", "...", 0));
        label_7->setText(QString());
        label_8->setText(QString());
        label->setText(QApplication::translate("LabelMainWindow", "\346\225\260\346\215\256\345\210\227\350\241\250", 0));
        label_9->setText(QApplication::translate("LabelMainWindow", "\346\234\252\346\240\207\346\263\250", 0));
        label_10->setText(QApplication::translate("LabelMainWindow", "\345\267\262\346\240\207\346\263\250", 0));
        label_6->setText(QApplication::translate("LabelMainWindow", "\345\233\276\345\203\217", 0));
        last->setText(QApplication::translate("LabelMainWindow", "<\344\270\212\344\270\200\345\274\240", 0));
        next->setText(QApplication::translate("LabelMainWindow", "\344\270\213\344\270\200\345\274\240>", 0));
        QTreeWidgetItem *___qtreewidgetitem = focuslabel->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("LabelMainWindow", "\347\227\205\347\201\266\346\240\207\347\255\276", 0));
        label_2->setText(QApplication::translate("LabelMainWindow", "\346\226\207\344\273\266\345\244\271\345\220\215\357\274\232", 0));
        label_5->setText(QString());
        label_4->setText(QApplication::translate("LabelMainWindow", "\346\226\207\344\273\266\345\220\215\357\274\232", 0));
        label_3->setText(QString());
        menu->setTitle(QApplication::translate("LabelMainWindow", "\347\274\226\350\276\221", 0));
        menu_3->setTitle(QApplication::translate("LabelMainWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class LabelMainWindow: public Ui_LabelMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELMAINWINDOW_H
