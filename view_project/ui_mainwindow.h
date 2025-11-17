/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "formscene.h"
#include "gui3D/scene3d.h"
#include "orbinput.h"
#include "plotgistogram.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    COrbInput *tab_orbInput;
    QWidget *tab_2;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_9;
    QLineEdit *BPLA_lon_fin;
    QLabel *label_11;
    QLineEdit *BPLA_lat_fin;
    QLabel *label_12;
    QGridLayout *gridLayout_2;
    QDateTimeEdit *dateTimeEdit_end;
    QLabel *label_2;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit_begin;
    QPushButton *pushButton_Run;
    ASDScene3D *m_scene2;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_18;
    QLineEdit *BPLA_speed;
    QLabel *label_4;
    QLineEdit *info_period;
    QPushButton *runBPLA;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_10;
    QLineEdit *lineEdit_13;
    QLabel *label_14;
    QLabel *label_16;
    QLabel *label_15;
    QLabel *label_13;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_15;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_11;
    QLabel *label_19;
    QLabel *label_20;
    QLineEdit *BPLA_lat_0;
    QLineEdit *BPLA_lon_0;
    QSpacerItem *verticalSpacer;
    Formscene *vis2D;
    QWidget *s;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_2;
    CPlotGistogram *widget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *label_5;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_startAction;
    QPushButton *m_stopAction;
    QPushButton *m_pauseAction;
    QDateTimeEdit *dateTimeEdit_curr;
    QLabel *label_3;
    QLabel *label_21;
    QSpinBox *spinBox_step;
    QComboBox *comboBox_step;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1178, 764);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_orbInput = new COrbInput();
        tab_orbInput->setObjectName(QString::fromUtf8("tab_orbInput"));
        tabWidget->addTab(tab_orbInput, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_12 = new QGridLayout(tab_2);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        groupBox_5->setMinimumSize(QSize(250, 0));
        gridLayout_9 = new QGridLayout(groupBox_5);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        BPLA_lon_fin = new QLineEdit(groupBox_5);
        BPLA_lon_fin->setObjectName(QString::fromUtf8("BPLA_lon_fin"));

        gridLayout_9->addWidget(BPLA_lon_fin, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_9->addWidget(label_11, 1, 0, 1, 1);

        BPLA_lat_fin = new QLineEdit(groupBox_5);
        BPLA_lat_fin->setObjectName(QString::fromUtf8("BPLA_lat_fin"));

        gridLayout_9->addWidget(BPLA_lat_fin, 1, 1, 1, 1);

        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_9->addWidget(label_12, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_5, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        dateTimeEdit_end = new QDateTimeEdit(tab_2);
        dateTimeEdit_end->setObjectName(QString::fromUtf8("dateTimeEdit_end"));
        sizePolicy.setHeightForWidth(dateTimeEdit_end->sizePolicy().hasHeightForWidth());
        dateTimeEdit_end->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(dateTimeEdit_end, 1, 1, 1, 1);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        dateTimeEdit_begin = new QDateTimeEdit(tab_2);
        dateTimeEdit_begin->setObjectName(QString::fromUtf8("dateTimeEdit_begin"));
        sizePolicy.setHeightForWidth(dateTimeEdit_begin->sizePolicy().hasHeightForWidth());
        dateTimeEdit_begin->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(dateTimeEdit_begin, 0, 1, 1, 1);

        pushButton_Run = new QPushButton(tab_2);
        pushButton_Run->setObjectName(QString::fromUtf8("pushButton_Run"));

        gridLayout_2->addWidget(pushButton_Run, 2, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout_2, 6, 0, 1, 1);

        m_scene2 = new ASDScene3D(tab_2);
        m_scene2->setObjectName(QString::fromUtf8("m_scene2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_scene2->sizePolicy().hasHeightForWidth());
        m_scene2->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(m_scene2, 0, 1, 7, 2);

        groupBox_7 = new QGroupBox(tab_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        sizePolicy.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy);
        groupBox_7->setMinimumSize(QSize(250, 0));
        verticalLayout_5 = new QVBoxLayout(groupBox_7);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_18 = new QLabel(groupBox_7);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(label_18);

        BPLA_speed = new QLineEdit(groupBox_7);
        BPLA_speed->setObjectName(QString::fromUtf8("BPLA_speed"));
        BPLA_speed->setEnabled(true);
        sizePolicy.setHeightForWidth(BPLA_speed->sizePolicy().hasHeightForWidth());
        BPLA_speed->setSizePolicy(sizePolicy);
        BPLA_speed->setMinimumSize(QSize(146, 0));
        BPLA_speed->setMaximumSize(QSize(16777215, 16777145));

        verticalLayout_5->addWidget(BPLA_speed);

        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(label_4);

        info_period = new QLineEdit(groupBox_7);
        info_period->setObjectName(QString::fromUtf8("info_period"));
        sizePolicy.setHeightForWidth(info_period->sizePolicy().hasHeightForWidth());
        info_period->setSizePolicy(sizePolicy);
        info_period->setMinimumSize(QSize(146, 0));
        info_period->setMaximumSize(QSize(16777215, 16777145));

        verticalLayout_5->addWidget(info_period);

        runBPLA = new QPushButton(groupBox_7);
        runBPLA->setObjectName(QString::fromUtf8("runBPLA"));
        sizePolicy.setHeightForWidth(runBPLA->sizePolicy().hasHeightForWidth());
        runBPLA->setSizePolicy(sizePolicy);
        runBPLA->setMinimumSize(QSize(220, 0));

        verticalLayout_5->addWidget(runBPLA);


        gridLayout_3->addWidget(groupBox_7, 2, 0, 2, 2);

        groupBox_6 = new QGroupBox(tab_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(250);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy3);
        gridLayout_10 = new QGridLayout(groupBox_6);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        lineEdit_13 = new QLineEdit(groupBox_6);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        lineEdit_13->setEnabled(false);
        sizePolicy.setHeightForWidth(lineEdit_13->sizePolicy().hasHeightForWidth());
        lineEdit_13->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(lineEdit_13, 2, 1, 1, 1);

        label_14 = new QLabel(groupBox_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy4);

        gridLayout_10->addWidget(label_14, 3, 0, 1, 1);

        label_16 = new QLabel(groupBox_6);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_10->addWidget(label_16, 0, 0, 1, 1);

        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy4.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy4);

        gridLayout_10->addWidget(label_15, 1, 0, 1, 1);

        label_13 = new QLabel(groupBox_6);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_10->addWidget(label_13, 2, 0, 1, 1);

        lineEdit_16 = new QLineEdit(groupBox_6);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        lineEdit_16->setEnabled(false);
        sizePolicy.setHeightForWidth(lineEdit_16->sizePolicy().hasHeightForWidth());
        lineEdit_16->setSizePolicy(sizePolicy);
        lineEdit_16->setMaximumSize(QSize(16777215, 16777145));

        gridLayout_10->addWidget(lineEdit_16, 3, 1, 1, 1);

        lineEdit_14 = new QLineEdit(groupBox_6);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        lineEdit_14->setEnabled(false);
        sizePolicy.setHeightForWidth(lineEdit_14->sizePolicy().hasHeightForWidth());
        lineEdit_14->setSizePolicy(sizePolicy);
        lineEdit_14->setMaximumSize(QSize(16777215, 16777145));

        gridLayout_10->addWidget(lineEdit_14, 1, 1, 1, 1);

        lineEdit_15 = new QLineEdit(groupBox_6);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        lineEdit_15->setEnabled(false);
        sizePolicy.setHeightForWidth(lineEdit_15->sizePolicy().hasHeightForWidth());
        lineEdit_15->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(lineEdit_15, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_6, 4, 0, 1, 1);

        groupBox_8 = new QGroupBox(tab_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        sizePolicy.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy);
        groupBox_8->setMinimumSize(QSize(250, 0));
        gridLayout_11 = new QGridLayout(groupBox_8);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_19 = new QLabel(groupBox_8);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_11->addWidget(label_19, 0, 0, 1, 1);

        label_20 = new QLabel(groupBox_8);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_11->addWidget(label_20, 1, 0, 1, 1);

        BPLA_lat_0 = new QLineEdit(groupBox_8);
        BPLA_lat_0->setObjectName(QString::fromUtf8("BPLA_lat_0"));

        gridLayout_11->addWidget(BPLA_lat_0, 1, 1, 1, 1);

        BPLA_lon_0 = new QLineEdit(groupBox_8);
        BPLA_lon_0->setObjectName(QString::fromUtf8("BPLA_lon_0"));

        gridLayout_11->addWidget(BPLA_lon_0, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_8, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 5, 0, 1, 1);


        gridLayout_12->addLayout(gridLayout_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        vis2D = new Formscene();
        vis2D->setObjectName(QString::fromUtf8("vis2D"));
        tabWidget->addTab(vis2D, QString());
        s = new QWidget();
        s->setObjectName(QString::fromUtf8("s"));
        s->setEnabled(true);
        gridLayout_4 = new QGridLayout(s);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton = new QPushButton(s);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        gridLayout_4->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new CPlotGistogram(s);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout_2->addWidget(widget);


        gridLayout_4->addLayout(verticalLayout_2, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(s);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setRowCount(1);
        tableWidget->setColumnCount(2);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);

        tabWidget->addTab(s, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setSizeConstraint(QLayout::SetFixedSize);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_2, 0, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(16777186, 16777215));
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_5);


        verticalLayout_3->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab, QString());

        verticalLayout_4->addWidget(tabWidget);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(horizontalSlider);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_startAction = new QPushButton(centralWidget);
        m_startAction->setObjectName(QString::fromUtf8("m_startAction"));

        horizontalLayout->addWidget(m_startAction);

        m_stopAction = new QPushButton(centralWidget);
        m_stopAction->setObjectName(QString::fromUtf8("m_stopAction"));

        horizontalLayout->addWidget(m_stopAction);

        m_pauseAction = new QPushButton(centralWidget);
        m_pauseAction->setObjectName(QString::fromUtf8("m_pauseAction"));

        horizontalLayout->addWidget(m_pauseAction);

        dateTimeEdit_curr = new QDateTimeEdit(centralWidget);
        dateTimeEdit_curr->setObjectName(QString::fromUtf8("dateTimeEdit_curr"));

        horizontalLayout->addWidget(dateTimeEdit_curr);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout->addWidget(label_21);

        spinBox_step = new QSpinBox(centralWidget);
        spinBox_step->setObjectName(QString::fromUtf8("spinBox_step"));
        spinBox_step->setMinimum(1);
        spinBox_step->setMaximum(60);

        horizontalLayout->addWidget(spinBox_step);

        comboBox_step = new QComboBox(centralWidget);
        comboBox_step->addItem(QString());
        comboBox_step->addItem(QString());
        comboBox_step->addItem(QString());
        comboBox_step->setObjectName(QString::fromUtf8("comboBox_step"));

        horizontalLayout->addWidget(comboBox_step);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1178, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(m_startAction, tabWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_orbInput), QApplication::translate("MainWindow", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265 \320\277\320\276 \320\236\320\223 \320\232\320\220", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\320\232\320\276\320\275\320\265\321\207\320\275\320\260\321\217 \321\202\320\276\321\207\320\272\320\260 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\260", nullptr));
        BPLA_lon_fin->setText(QApplication::translate("MainWindow", "33.60", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "\320\250\320\270\321\200\320\276\321\202\320\260 (\320\263\321\200\320\260\320\264)", nullptr));
        BPLA_lat_fin->setText(QApplication::translate("MainWindow", "45.09", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\273\320\263\320\276\321\202\320\260 (\320\263\321\200\320\260\320\264)", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\236\320\272\320\276\320\275\321\207\320\260\320\275\320\270\320\265 \320\274\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\320\276 \320\274\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        pushButton_Run->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214 \321\200\320\260\321\201\321\207\320\265\321\202", nullptr));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272 \320\221\320\237\320\233\320\220", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\221\320\237\320\233\320\220, \320\272\320\274/\321\207", nullptr));
        BPLA_speed->setText(QApplication::translate("MainWindow", "150", nullptr));
        label_4->setText(QApplication::translate("MainWindow", " \320\230\320\275\321\202\320\265\321\200\320\262\320\260\320\273 \320\276\320\277\320\276\320\262\320\265\321\211\320\265\320\275\320\270\320\271, \320\274\320\270\320\275", nullptr));
        info_period->setText(QApplication::translate("MainWindow", "5", nullptr));
        runBPLA->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272", nullptr));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "\320\240\320\260\320\271\320\276\320\275 \320\277\320\260\321\202\321\200\321\203\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217 \320\221\320\237\320\233\320\220", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "\320\250\320\270\321\200\320\276\321\202\320\260 \320\256\320\222 \321\202\320\276\321\207\320\272\320\270", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\263\320\276\321\202\320\260 \320\241\320\227 \321\202\320\276\321\207\320\272\320\270", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "\320\250\320\270\321\200\320\276\321\202\320\260 \320\241\320\227 \321\202\320\276\321\207\320\272\320\270", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\263\320\276\321\202\320\260 \320\256\320\222 \321\202\320\276\321\207\320\272\320\270", nullptr));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\260\321\217 \321\202\320\276\321\207\320\272\320\260 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\260", nullptr));
        label_19->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\273\320\263\320\276\321\202\320\260 (\320\263\321\200\320\260\320\264)", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "\320\250\320\270\321\200\320\276\321\202\320\260 (\320\263\321\200\320\260\320\264)", nullptr));
        BPLA_lat_0->setText(QApplication::translate("MainWindow", "46.41", nullptr));
        BPLA_lon_0->setText(QApplication::translate("MainWindow", "30.71", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(vis2D), QApplication::translate("MainWindow", "2D \320\262\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(s), QApplication::translate("MainWindow", "\320\223\320\270\321\201\321\202\320\276\320\263\321\200\320\260\320\274\320\274\320\260 \320\264\320\276\321\201\321\202\321\203\320\277\320\275\320\276\321\201\321\202\320\270 \320\232\320\220", nullptr));
        label_6->setText(QString());
        label_5->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "2D v2", nullptr));
        m_startAction->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        m_stopAction->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\276\320\277", nullptr));
        m_pauseAction->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "(\320\222\321\200\320\265\320\274\321\217 UTC)                ", nullptr));
        label_21->setText(QApplication::translate("MainWindow", "\321\210\320\260\320\263", nullptr));
        comboBox_step->setItemText(0, QApplication::translate("MainWindow", "\321\201\320\265\320\272", nullptr));
        comboBox_step->setItemText(1, QApplication::translate("MainWindow", "\320\274\320\270\320\275", nullptr));
        comboBox_step->setItemText(2, QApplication::translate("MainWindow", "\321\207\320\260\321\201", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
