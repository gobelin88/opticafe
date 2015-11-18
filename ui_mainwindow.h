/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *action_levmar;
    QAction *actionSaveUnder;
    QAction *action2D_f_x0_x1;
    QAction *action3D_f_x0_x1_x2;
    QAction *actionQuit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabSystem;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *te_script;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabSetting;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout;
    QDoubleSpinBox *sb_p1_max;
    QComboBox *cb__color_mode;
    QDoubleSpinBox *sb_p0_min;
    QComboBox *cb_scale_color_mode;
    QPushButton *pb_calculate;
    QProgressBar *progressBar;
    QDoubleSpinBox *sb_p0_max;
    QDoubleSpinBox *sb_p1_min;
    QSpinBox *sb_Height;
    QSpinBox *sb_Width;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_save_conv_setting;
    QPushButton *pb_load_conv_setting;
    QSpacerItem *verticalSpacer;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuOpen;
    QMenu *menuMinimize;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(434, 468);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        action_levmar = new QAction(MainWindow);
        action_levmar->setObjectName(QStringLiteral("action_levmar"));
        actionSaveUnder = new QAction(MainWindow);
        actionSaveUnder->setObjectName(QStringLiteral("actionSaveUnder"));
        action2D_f_x0_x1 = new QAction(MainWindow);
        action2D_f_x0_x1->setObjectName(QStringLiteral("action2D_f_x0_x1"));
        action3D_f_x0_x1_x2 = new QAction(MainWindow);
        action3D_f_x0_x1_x2->setObjectName(QStringLiteral("action3D_f_x0_x1_x2"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabSystem = new QTabWidget(centralWidget);
        tabSystem->setObjectName(QStringLiteral("tabSystem"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        te_script = new QTextEdit(tab);
        te_script->setObjectName(QStringLiteral("te_script"));

        verticalLayout_2->addWidget(te_script);

        tabSystem->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tabSetting = new QTabWidget(tab_2);
        tabSetting->setObjectName(QStringLiteral("tabSetting"));
        tabSetting->setTabPosition(QTabWidget::West);
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        sb_p1_max = new QDoubleSpinBox(tab_3);
        sb_p1_max->setObjectName(QStringLiteral("sb_p1_max"));
        sb_p1_max->setDecimals(5);
        sb_p1_max->setMinimum(-10000);
        sb_p1_max->setMaximum(10000);
        sb_p1_max->setValue(2);

        gridLayout->addWidget(sb_p1_max, 1, 1, 1, 1);

        cb__color_mode = new QComboBox(tab_3);
        cb__color_mode->setObjectName(QStringLiteral("cb__color_mode"));

        gridLayout->addWidget(cb__color_mode, 3, 0, 1, 4);

        sb_p0_min = new QDoubleSpinBox(tab_3);
        sb_p0_min->setObjectName(QStringLiteral("sb_p0_min"));
        sb_p0_min->setDecimals(5);
        sb_p0_min->setMinimum(-10000);
        sb_p0_min->setMaximum(10000);
        sb_p0_min->setValue(-2);

        gridLayout->addWidget(sb_p0_min, 0, 0, 1, 1);

        cb_scale_color_mode = new QComboBox(tab_3);
        cb_scale_color_mode->setObjectName(QStringLiteral("cb_scale_color_mode"));

        gridLayout->addWidget(cb_scale_color_mode, 2, 0, 1, 4);

        pb_calculate = new QPushButton(tab_3);
        pb_calculate->setObjectName(QStringLiteral("pb_calculate"));

        gridLayout->addWidget(pb_calculate, 4, 0, 1, 1);

        progressBar = new QProgressBar(tab_3);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 4, 1, 1, 3);

        sb_p0_max = new QDoubleSpinBox(tab_3);
        sb_p0_max->setObjectName(QStringLiteral("sb_p0_max"));
        sb_p0_max->setDecimals(5);
        sb_p0_max->setMinimum(-10000);
        sb_p0_max->setMaximum(10000);
        sb_p0_max->setValue(2);

        gridLayout->addWidget(sb_p0_max, 0, 1, 1, 1);

        sb_p1_min = new QDoubleSpinBox(tab_3);
        sb_p1_min->setObjectName(QStringLiteral("sb_p1_min"));
        sb_p1_min->setDecimals(5);
        sb_p1_min->setMinimum(-10000);
        sb_p1_min->setMaximum(10000);
        sb_p1_min->setValue(-2);

        gridLayout->addWidget(sb_p1_min, 1, 0, 1, 1);

        sb_Height = new QSpinBox(tab_3);
        sb_Height->setObjectName(QStringLiteral("sb_Height"));
        sb_Height->setMaximum(1024);
        sb_Height->setValue(512);

        gridLayout->addWidget(sb_Height, 1, 2, 1, 1);

        sb_Width = new QSpinBox(tab_3);
        sb_Width->setObjectName(QStringLiteral("sb_Width"));
        sb_Width->setMaximum(1024);
        sb_Width->setValue(512);

        gridLayout->addWidget(sb_Width, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pb_save_conv_setting = new QPushButton(tab_3);
        pb_save_conv_setting->setObjectName(QStringLiteral("pb_save_conv_setting"));

        horizontalLayout->addWidget(pb_save_conv_setting);

        pb_load_conv_setting = new QPushButton(tab_3);
        pb_load_conv_setting->setObjectName(QStringLiteral("pb_load_conv_setting"));

        horizontalLayout->addWidget(pb_load_conv_setting);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 4);


        verticalLayout_4->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        tabSetting->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_5 = new QVBoxLayout(tab_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label = new QLabel(tab_5);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_5->addWidget(label);

        tabSetting->addTab(tab_5, QString());

        verticalLayout_3->addWidget(tabSetting);

        tabSystem->addTab(tab_2, QString());

        verticalLayout->addWidget(tabSystem);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 434, 21));
        menuOpen = new QMenu(menuBar);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        menuMinimize = new QMenu(menuOpen);
        menuMinimize->setObjectName(QStringLiteral("menuMinimize"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOpen->menuAction());
        menuOpen->addAction(actionOpen);
        menuOpen->addAction(actionSave);
        menuOpen->addAction(actionSaveUnder);
        menuOpen->addSeparator();
        menuOpen->addAction(menuMinimize->menuAction());
        menuOpen->addSeparator();
        menuOpen->addAction(actionQuit);
        menuMinimize->addAction(action_levmar);

        retranslateUi(MainWindow);

        tabSystem->setCurrentIndex(1);
        tabSetting->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        action_levmar->setText(QApplication::translate("MainWindow", "Levenberg-Marquardt", 0));
        action_levmar->setShortcut(QApplication::translate("MainWindow", "Ctrl+F1", 0));
        actionSaveUnder->setText(QApplication::translate("MainWindow", "Save Under", 0));
        actionSaveUnder->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0));
        action2D_f_x0_x1->setText(QApplication::translate("MainWindow", "2D f(x0,x1)", 0));
        action3D_f_x0_x1_x2->setText(QApplication::translate("MainWindow", "3D f(x0,x1,x2)", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0));
        tabSystem->setTabText(tabSystem->indexOf(tab), QApplication::translate("MainWindow", "System", 0));
        sb_p1_max->setPrefix(QApplication::translate("MainWindow", "p1_max=", 0));
        sb_p0_min->setPrefix(QApplication::translate("MainWindow", "p0_min=", 0));
        pb_calculate->setText(QApplication::translate("MainWindow", "Calculate", 0));
        sb_p0_max->setPrefix(QApplication::translate("MainWindow", "p0_max=", 0));
        sb_p1_min->setPrefix(QApplication::translate("MainWindow", "p1_min=", 0));
        pb_save_conv_setting->setText(QApplication::translate("MainWindow", "Save", 0));
        pb_load_conv_setting->setText(QApplication::translate("MainWindow", "Load", 0));
        tabSetting->setTabText(tabSetting->indexOf(tab_3), QApplication::translate("MainWindow", "Settings", 0));
        label->setText(QString());
        tabSetting->setTabText(tabSetting->indexOf(tab_5), QApplication::translate("MainWindow", "2D", 0));
        tabSystem->setTabText(tabSystem->indexOf(tab_2), QApplication::translate("MainWindow", "Convergence Analysis", 0));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Menu", 0));
        menuMinimize->setTitle(QApplication::translate("MainWindow", "Minimize", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
