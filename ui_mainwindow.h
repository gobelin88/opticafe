/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
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
    QAction *actionMinimize;
    QAction *actionAlgorithms;
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
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *sb_p0_max;
    QSpinBox *sb_Width;
    QDoubleSpinBox *sb_p0_min;
    QDoubleSpinBox *sb_p1_min;
    QDoubleSpinBox *sb_p1_max;
    QSpinBox *sb_Height;
    QComboBox *cb_param2;
    QComboBox *cb_param1;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *cb__color_mode;
    QComboBox *cb_scale_color_mode;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QPushButton *pb_calculate;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_save_conv_setting;
    QPushButton *pb_load_conv_setting;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pbSaveImage;
    QMenuBar *menuBar;
    QMenu *menuOpen;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(561, 644);
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
        actionMinimize = new QAction(MainWindow);
        actionMinimize->setObjectName(QStringLiteral("actionMinimize"));
        actionAlgorithms = new QAction(MainWindow);
        actionAlgorithms->setObjectName(QStringLiteral("actionAlgorithms"));
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
        verticalLayout_8 = new QVBoxLayout(tab_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        sb_p0_max = new QDoubleSpinBox(groupBox);
        sb_p0_max->setObjectName(QStringLiteral("sb_p0_max"));
        sb_p0_max->setDecimals(5);
        sb_p0_max->setMinimum(-10000);
        sb_p0_max->setMaximum(10000);
        sb_p0_max->setValue(2);

        gridLayout_2->addWidget(sb_p0_max, 0, 2, 1, 1);

        sb_Width = new QSpinBox(groupBox);
        sb_Width->setObjectName(QStringLiteral("sb_Width"));
        sb_Width->setMaximum(4096);
        sb_Width->setValue(512);

        gridLayout_2->addWidget(sb_Width, 0, 3, 1, 1);

        sb_p0_min = new QDoubleSpinBox(groupBox);
        sb_p0_min->setObjectName(QStringLiteral("sb_p0_min"));
        sb_p0_min->setDecimals(5);
        sb_p0_min->setMinimum(-10000);
        sb_p0_min->setMaximum(10000);
        sb_p0_min->setValue(-2);

        gridLayout_2->addWidget(sb_p0_min, 0, 1, 1, 1);

        sb_p1_min = new QDoubleSpinBox(groupBox);
        sb_p1_min->setObjectName(QStringLiteral("sb_p1_min"));
        sb_p1_min->setDecimals(5);
        sb_p1_min->setMinimum(-10000);
        sb_p1_min->setMaximum(10000);
        sb_p1_min->setValue(-2);

        gridLayout_2->addWidget(sb_p1_min, 1, 1, 1, 1);

        sb_p1_max = new QDoubleSpinBox(groupBox);
        sb_p1_max->setObjectName(QStringLiteral("sb_p1_max"));
        sb_p1_max->setDecimals(5);
        sb_p1_max->setMinimum(-10000);
        sb_p1_max->setMaximum(10000);
        sb_p1_max->setValue(2);

        gridLayout_2->addWidget(sb_p1_max, 1, 2, 1, 1);

        sb_Height = new QSpinBox(groupBox);
        sb_Height->setObjectName(QStringLiteral("sb_Height"));
        sb_Height->setMaximum(4096);
        sb_Height->setValue(512);

        gridLayout_2->addWidget(sb_Height, 1, 3, 1, 1);

        cb_param2 = new QComboBox(groupBox);
        cb_param2->setObjectName(QStringLiteral("cb_param2"));

        gridLayout_2->addWidget(cb_param2, 0, 0, 1, 1);

        cb_param1 = new QComboBox(groupBox);
        cb_param1->setObjectName(QStringLiteral("cb_param1"));

        gridLayout_2->addWidget(cb_param1, 1, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        verticalLayout_8->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        cb__color_mode = new QComboBox(groupBox_2);
        cb__color_mode->setObjectName(QStringLiteral("cb__color_mode"));

        horizontalLayout_3->addWidget(cb__color_mode);

        cb_scale_color_mode = new QComboBox(groupBox_2);
        cb_scale_color_mode->setObjectName(QStringLiteral("cb_scale_color_mode"));

        horizontalLayout_3->addWidget(cb_scale_color_mode);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_8->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progressBar = new QProgressBar(groupBox_3);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        horizontalLayout->addWidget(progressBar);

        pb_calculate = new QPushButton(groupBox_3);
        pb_calculate->setObjectName(QStringLiteral("pb_calculate"));

        horizontalLayout->addWidget(pb_calculate);


        verticalLayout_7->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);


        verticalLayout_8->addWidget(groupBox_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pb_save_conv_setting = new QPushButton(tab_3);
        pb_save_conv_setting->setObjectName(QStringLiteral("pb_save_conv_setting"));

        horizontalLayout_2->addWidget(pb_save_conv_setting);

        pb_load_conv_setting = new QPushButton(tab_3);
        pb_load_conv_setting->setObjectName(QStringLiteral("pb_load_conv_setting"));

        horizontalLayout_2->addWidget(pb_load_conv_setting);


        verticalLayout_8->addLayout(horizontalLayout_2);

        tabSetting->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_5 = new QVBoxLayout(tab_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        scrollArea = new QScrollArea(tab_5);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 98, 28));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_6->addWidget(scrollArea);

        pbSaveImage = new QPushButton(tab_5);
        pbSaveImage->setObjectName(QStringLiteral("pbSaveImage"));

        verticalLayout_6->addWidget(pbSaveImage);


        verticalLayout_5->addLayout(verticalLayout_6);

        tabSetting->addTab(tab_5, QString());

        verticalLayout_3->addWidget(tabSetting);

        tabSystem->addTab(tab_2, QString());

        verticalLayout->addWidget(tabSystem);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 561, 21));
        menuOpen = new QMenu(menuBar);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOpen->menuAction());
        menuOpen->addAction(actionOpen);
        menuOpen->addAction(actionSave);
        menuOpen->addAction(actionSaveUnder);
        menuOpen->addSeparator();
        menuOpen->addAction(actionAlgorithms);
        menuOpen->addAction(actionMinimize);
        menuOpen->addSeparator();
        menuOpen->addAction(actionQuit);

        retranslateUi(MainWindow);

        tabSystem->setCurrentIndex(1);
        tabSetting->setCurrentIndex(0);
        cb_param1->setCurrentIndex(1);


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
        actionMinimize->setText(QApplication::translate("MainWindow", "Minimize", 0));
        actionMinimize->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", 0));
        actionAlgorithms->setText(QApplication::translate("MainWindow", "Algorithms", 0));
        tabSystem->setTabText(tabSystem->indexOf(tab), QApplication::translate("MainWindow", "System", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Region and Resolution", 0));
        sb_p0_max->setPrefix(QApplication::translate("MainWindow", "p0_max=", 0));
        sb_p0_min->setPrefix(QApplication::translate("MainWindow", "p0_min=", 0));
        sb_p1_min->setPrefix(QApplication::translate("MainWindow", "p1_min=", 0));
        sb_p1_max->setPrefix(QApplication::translate("MainWindow", "p1_max=", 0));
        cb_param2->clear();
        cb_param2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "p0", 0)
         << QApplication::translate("MainWindow", "p1", 0)
         << QApplication::translate("MainWindow", "p2", 0)
         << QApplication::translate("MainWindow", "p3", 0)
         << QApplication::translate("MainWindow", "p4", 0)
         << QApplication::translate("MainWindow", "p5", 0)
         << QApplication::translate("MainWindow", "p6", 0)
         << QApplication::translate("MainWindow", "p7", 0)
         << QApplication::translate("MainWindow", "p8", 0)
         << QApplication::translate("MainWindow", "p9", 0)
        );
        cb_param1->clear();
        cb_param1->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "p0", 0)
         << QApplication::translate("MainWindow", "p1", 0)
         << QApplication::translate("MainWindow", "p2", 0)
         << QApplication::translate("MainWindow", "p3", 0)
         << QApplication::translate("MainWindow", "p4", 0)
         << QApplication::translate("MainWindow", "p5", 0)
         << QApplication::translate("MainWindow", "p6", 0)
         << QApplication::translate("MainWindow", "p7", 0)
         << QApplication::translate("MainWindow", "p8", 0)
         << QApplication::translate("MainWindow", "p9", 0)
        );
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Color rules", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Process", 0));
        pb_calculate->setText(QApplication::translate("MainWindow", "Calculate", 0));
        pb_save_conv_setting->setText(QApplication::translate("MainWindow", "Save", 0));
        pb_load_conv_setting->setText(QApplication::translate("MainWindow", "Load", 0));
        tabSetting->setTabText(tabSetting->indexOf(tab_3), QApplication::translate("MainWindow", "Settings", 0));
        pbSaveImage->setText(QApplication::translate("MainWindow", "Save Image", 0));
        tabSetting->setTabText(tabSetting->indexOf(tab_5), QApplication::translate("MainWindow", "2D", 0));
        tabSystem->setTabText(tabSystem->indexOf(tab_2), QApplication::translate("MainWindow", "Convergence Analysis", 0));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
