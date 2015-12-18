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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
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
    QAction *actionMinimize;
    QAction *actionAlgorithms;
    QAction *a_tiles;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabSystem;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *te_script;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    QSpinBox *sb_p2_res;
    QDoubleSpinBox *sb_p1_max;
    QComboBox *cb_param3;
    QDoubleSpinBox *sb_p0_min;
    QComboBox *cb_param2;
    QSpinBox *sb_p0_res;
    QDoubleSpinBox *sb_p0_max;
    QSpinBox *sb_p1_res;
    QDoubleSpinBox *sb_p1_min;
    QDoubleSpinBox *sb_p2_min;
    QDoubleSpinBox *sb_p2_max;
    QComboBox *cb_param1;
    QCheckBox *rb_1D;
    QCheckBox *rb_2D;
    QCheckBox *rb_3D;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *cb__color_mode;
    QComboBox *cb_gradient_preset;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QPushButton *pb_calculate_func;
    QPushButton *pb_calculate_conv;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_save_conv_setting;
    QPushButton *pb_load_conv_setting;
    QSpacerItem *verticalSpacer;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuOpen;
    QMenu *menuWindows;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(714, 739);
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
        a_tiles = new QAction(MainWindow);
        a_tiles->setObjectName(QStringLiteral("a_tiles"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabSystem = new QTabWidget(centralWidget);
        tabSystem->setObjectName(QStringLiteral("tabSystem"));
        tabSystem->setMinimumSize(QSize(0, 0));
        tabSystem->setMaximumSize(QSize(16777215, 16777215));
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
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        sb_p2_res = new QSpinBox(groupBox);
        sb_p2_res->setObjectName(QStringLiteral("sb_p2_res"));
        sb_p2_res->setMaximum(4096);
        sb_p2_res->setSingleStep(2);
        sb_p2_res->setValue(256);

        gridLayout_2->addWidget(sb_p2_res, 2, 4, 1, 1);

        sb_p1_max = new QDoubleSpinBox(groupBox);
        sb_p1_max->setObjectName(QStringLiteral("sb_p1_max"));
        sb_p1_max->setDecimals(5);
        sb_p1_max->setMinimum(-10000);
        sb_p1_max->setMaximum(10000);
        sb_p1_max->setValue(2);

        gridLayout_2->addWidget(sb_p1_max, 1, 3, 1, 1);

        cb_param3 = new QComboBox(groupBox);
        cb_param3->setObjectName(QStringLiteral("cb_param3"));
        cb_param3->setMaximumSize(QSize(50, 16777215));

        gridLayout_2->addWidget(cb_param3, 2, 1, 1, 1);

        sb_p0_min = new QDoubleSpinBox(groupBox);
        sb_p0_min->setObjectName(QStringLiteral("sb_p0_min"));
        sb_p0_min->setDecimals(5);
        sb_p0_min->setMinimum(-10000);
        sb_p0_min->setMaximum(10000);
        sb_p0_min->setValue(-2);

        gridLayout_2->addWidget(sb_p0_min, 0, 2, 1, 1);

        cb_param2 = new QComboBox(groupBox);
        cb_param2->setObjectName(QStringLiteral("cb_param2"));
        cb_param2->setMaximumSize(QSize(50, 16777215));

        gridLayout_2->addWidget(cb_param2, 1, 1, 1, 1);

        sb_p0_res = new QSpinBox(groupBox);
        sb_p0_res->setObjectName(QStringLiteral("sb_p0_res"));
        sb_p0_res->setMaximum(4096);
        sb_p0_res->setSingleStep(2);
        sb_p0_res->setValue(256);

        gridLayout_2->addWidget(sb_p0_res, 0, 4, 1, 1);

        sb_p0_max = new QDoubleSpinBox(groupBox);
        sb_p0_max->setObjectName(QStringLiteral("sb_p0_max"));
        sb_p0_max->setDecimals(5);
        sb_p0_max->setMinimum(-10000);
        sb_p0_max->setMaximum(10000);
        sb_p0_max->setValue(2);

        gridLayout_2->addWidget(sb_p0_max, 0, 3, 1, 1);

        sb_p1_res = new QSpinBox(groupBox);
        sb_p1_res->setObjectName(QStringLiteral("sb_p1_res"));
        sb_p1_res->setMaximum(4096);
        sb_p1_res->setSingleStep(2);
        sb_p1_res->setValue(256);

        gridLayout_2->addWidget(sb_p1_res, 1, 4, 1, 1);

        sb_p1_min = new QDoubleSpinBox(groupBox);
        sb_p1_min->setObjectName(QStringLiteral("sb_p1_min"));
        sb_p1_min->setDecimals(5);
        sb_p1_min->setMinimum(-10000);
        sb_p1_min->setMaximum(10000);
        sb_p1_min->setValue(-2);

        gridLayout_2->addWidget(sb_p1_min, 1, 2, 1, 1);

        sb_p2_min = new QDoubleSpinBox(groupBox);
        sb_p2_min->setObjectName(QStringLiteral("sb_p2_min"));
        sb_p2_min->setDecimals(5);
        sb_p2_min->setMinimum(-10000);
        sb_p2_min->setMaximum(10000);
        sb_p2_min->setValue(-2);

        gridLayout_2->addWidget(sb_p2_min, 2, 2, 1, 1);

        sb_p2_max = new QDoubleSpinBox(groupBox);
        sb_p2_max->setObjectName(QStringLiteral("sb_p2_max"));
        sb_p2_max->setDecimals(5);
        sb_p2_max->setMinimum(-10000);
        sb_p2_max->setMaximum(10000);
        sb_p2_max->setValue(2);

        gridLayout_2->addWidget(sb_p2_max, 2, 3, 1, 1);

        cb_param1 = new QComboBox(groupBox);
        cb_param1->setObjectName(QStringLiteral("cb_param1"));
        cb_param1->setMaximumSize(QSize(50, 16777215));

        gridLayout_2->addWidget(cb_param1, 0, 1, 1, 1);

        rb_1D = new QCheckBox(groupBox);
        rb_1D->setObjectName(QStringLiteral("rb_1D"));
        rb_1D->setMaximumSize(QSize(20, 16777215));
        rb_1D->setChecked(true);

        gridLayout_2->addWidget(rb_1D, 0, 0, 1, 1);

        rb_2D = new QCheckBox(groupBox);
        rb_2D->setObjectName(QStringLiteral("rb_2D"));
        rb_2D->setMaximumSize(QSize(20, 16777215));

        gridLayout_2->addWidget(rb_2D, 1, 0, 1, 1);

        rb_3D = new QCheckBox(groupBox);
        rb_3D->setObjectName(QStringLiteral("rb_3D"));
        rb_3D->setMaximumSize(QSize(20, 16777215));

        gridLayout_2->addWidget(rb_3D, 2, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab_2);
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

        cb_gradient_preset = new QComboBox(groupBox_2);
        cb_gradient_preset->setObjectName(QStringLiteral("cb_gradient_preset"));

        horizontalLayout_3->addWidget(cb_gradient_preset);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        progressBar = new QProgressBar(groupBox_3);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 0, 0, 1, 2);

        pb_calculate_func = new QPushButton(groupBox_3);
        pb_calculate_func->setObjectName(QStringLiteral("pb_calculate_func"));

        gridLayout->addWidget(pb_calculate_func, 1, 0, 1, 1);

        pb_calculate_conv = new QPushButton(groupBox_3);
        pb_calculate_conv->setObjectName(QStringLiteral("pb_calculate_conv"));

        gridLayout->addWidget(pb_calculate_conv, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout);


        verticalLayout_3->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pb_save_conv_setting = new QPushButton(groupBox_4);
        pb_save_conv_setting->setObjectName(QStringLiteral("pb_save_conv_setting"));

        horizontalLayout_2->addWidget(pb_save_conv_setting);

        pb_load_conv_setting = new QPushButton(groupBox_4);
        pb_load_conv_setting->setObjectName(QStringLiteral("pb_load_conv_setting"));

        horizontalLayout_2->addWidget(pb_load_conv_setting);


        verticalLayout_5->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupBox_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabSystem->addTab(tab_2, QString());

        verticalLayout->addWidget(tabSystem);

        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        verticalLayout->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 714, 21));
        menuOpen = new QMenu(menuBar);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QStringLiteral("menuWindows"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOpen->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuOpen->addAction(actionOpen);
        menuOpen->addAction(actionSave);
        menuOpen->addAction(actionSaveUnder);
        menuOpen->addSeparator();
        menuOpen->addAction(actionAlgorithms);
        menuOpen->addAction(actionMinimize);
        menuOpen->addSeparator();
        menuOpen->addAction(actionQuit);
        menuWindows->addAction(a_tiles);

        retranslateUi(MainWindow);

        tabSystem->setCurrentIndex(1);
        cb_param3->setCurrentIndex(2);
        cb_param2->setCurrentIndex(1);
        cb_param1->setCurrentIndex(0);


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
        a_tiles->setText(QApplication::translate("MainWindow", "Tiles", 0));
        tabSystem->setTabText(tabSystem->indexOf(tab), QApplication::translate("MainWindow", "System", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Region and  Resolution", 0));
        sb_p1_max->setPrefix(QApplication::translate("MainWindow", "max=", 0));
        cb_param3->clear();
        cb_param3->insertItems(0, QStringList()
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
        sb_p0_min->setPrefix(QApplication::translate("MainWindow", "min=", 0));
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
        sb_p0_max->setPrefix(QApplication::translate("MainWindow", "max=", 0));
        sb_p1_min->setPrefix(QApplication::translate("MainWindow", "min=", 0));
        sb_p2_min->setPrefix(QApplication::translate("MainWindow", "min=", 0));
        sb_p2_max->setPrefix(QApplication::translate("MainWindow", "max=", 0));
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
        rb_1D->setText(QString());
        rb_2D->setText(QString());
        rb_3D->setText(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Color rules", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Calculate", 0));
        pb_calculate_func->setText(QApplication::translate("MainWindow", "Evaluate", 0));
        pb_calculate_conv->setText(QApplication::translate("MainWindow", "Convergence", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Save settings", 0));
        pb_save_conv_setting->setText(QApplication::translate("MainWindow", "Save", 0));
        pb_load_conv_setting->setText(QApplication::translate("MainWindow", "Load", 0));
        tabSystem->setTabText(tabSystem->indexOf(tab_2), QApplication::translate("MainWindow", "Analysis", 0));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Menu", 0));
        menuWindows->setTitle(QApplication::translate("MainWindow", "Windows", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
