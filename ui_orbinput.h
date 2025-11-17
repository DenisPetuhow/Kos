/********************************************************************************
** Form generated from reading UI file 'orbinput.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORBINPUT_H
#define UI_ORBINPUT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrbInputClass
{
public:
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_sysKA;
    QHBoxLayout *horizontalLayout_3;
    QTreeWidget *treeWidget_sysKA;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButtonAddObj;
    QToolButton *toolButtonDelObj;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_rezKA;
    QListWidget *listWidget_rezKA;
    QGroupBox *groupBox_bal;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableWidget_par;
    QLabel *label_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBoxEtaMounting;
    QDoubleSpinBox *doubleSpinBoxDeltaN;
    QLabel *label_7;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBoxDeltaB;
    QDoubleSpinBox *doubleSpinBoxDeltaTau;
    QListWidget *listWidgetBsa;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBoxAlfaMounting;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBoxGamma;
    QLabel *label_3;
    QComboBox *comboBoxType;
    QLabel *label_4;
    QLineEdit *lineEditName;
    QLabel *label_5;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBoxBetaMounting;
    QDoubleSpinBox *doubleSpinBoxDeltaH;
    QDoubleSpinBox *doubleSpinBoxDeltaV;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBoxDeltaL;
    QLabel *label_15;
    QToolButton *toolButtonAddParam;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBox_Resolving_Power;
    QDoubleSpinBox *doubleSpinBox_focus;
    QDoubleSpinBox *doubleSpinBox_contPZS;
    QDoubleSpinBox *doubleSpinBox_Length_line;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButtonAddBsa;
    QPushButton *pushButtonEditBsa;
    QPushButton *pushButtonDelBsa;
    QPushButton *pushButtonSaveBsa;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonLoadFile;
    QPushButton *pushButtonAddDb;
    QPushButton *pushButtonSystemCreateObj;
    QPushButton *pushButtonCreateObj;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonSaveObj;

    void setupUi(QWidget *OrbInputClass)
    {
        if (OrbInputClass->objectName().isEmpty())
            OrbInputClass->setObjectName(QString::fromUtf8("OrbInputClass"));
        OrbInputClass->resize(965, 867);
        verticalLayout_6 = new QVBoxLayout(OrbInputClass);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_sysKA = new QLabel(OrbInputClass);
        label_sysKA->setObjectName(QString::fromUtf8("label_sysKA"));

        verticalLayout_3->addWidget(label_sysKA);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        treeWidget_sysKA = new QTreeWidget(OrbInputClass);
        treeWidget_sysKA->setObjectName(QString::fromUtf8("treeWidget_sysKA"));
        treeWidget_sysKA->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout_3->addWidget(treeWidget_sysKA);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolButtonAddObj = new QToolButton(OrbInputClass);
        toolButtonAddObj->setObjectName(QString::fromUtf8("toolButtonAddObj"));
        toolButtonAddObj->setArrowType(Qt::RightArrow);

        verticalLayout_2->addWidget(toolButtonAddObj);

        toolButtonDelObj = new QToolButton(OrbInputClass);
        toolButtonDelObj->setObjectName(QString::fromUtf8("toolButtonDelObj"));
        toolButtonDelObj->setArrowType(Qt::LeftArrow);

        verticalLayout_2->addWidget(toolButtonDelObj);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_rezKA = new QLabel(OrbInputClass);
        label_rezKA->setObjectName(QString::fromUtf8("label_rezKA"));

        verticalLayout_4->addWidget(label_rezKA);

        listWidget_rezKA = new QListWidget(OrbInputClass);
        listWidget_rezKA->setObjectName(QString::fromUtf8("listWidget_rezKA"));
        listWidget_rezKA->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_4->addWidget(listWidget_rezKA);


        horizontalLayout_4->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_5);

        groupBox_bal = new QGroupBox(OrbInputClass);
        groupBox_bal->setObjectName(QString::fromUtf8("groupBox_bal"));
        verticalLayout = new QVBoxLayout(groupBox_bal);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(groupBox_bal);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tableWidget_par = new QTableWidget(groupBox_bal);
        if (tableWidget_par->columnCount() < 2)
            tableWidget_par->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_par->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_par->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget_par->setObjectName(QString::fromUtf8("tableWidget_par"));
        tableWidget_par->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableWidget_par);

        label_2 = new QLabel(groupBox_bal);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        widget = new QWidget(groupBox_bal);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_7 = new QVBoxLayout(widget);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        doubleSpinBoxEtaMounting = new QDoubleSpinBox(widget);
        doubleSpinBoxEtaMounting->setObjectName(QString::fromUtf8("doubleSpinBoxEtaMounting"));
        doubleSpinBoxEtaMounting->setEnabled(false);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(0, 0, 0, 128));
        brush1.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush1);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 128));
        brush2.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        doubleSpinBoxEtaMounting->setPalette(palette);
        doubleSpinBoxEtaMounting->setMinimum(-180.000000000000000);
        doubleSpinBoxEtaMounting->setMaximum(180.000000000000000);

        gridLayout->addWidget(doubleSpinBoxEtaMounting, 5, 1, 1, 1);

        doubleSpinBoxDeltaN = new QDoubleSpinBox(widget);
        doubleSpinBoxDeltaN->setObjectName(QString::fromUtf8("doubleSpinBoxDeltaN"));
        doubleSpinBoxDeltaN->setEnabled(false);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush4(QColor(0, 0, 0, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush5(QColor(0, 0, 0, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush6(QColor(0, 0, 0, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
#endif
        doubleSpinBoxDeltaN->setPalette(palette1);

        gridLayout->addWidget(doubleSpinBoxDeltaN, 8, 1, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        doubleSpinBoxDeltaB = new QDoubleSpinBox(widget);
        doubleSpinBoxDeltaB->setObjectName(QString::fromUtf8("doubleSpinBoxDeltaB"));
        doubleSpinBoxDeltaB->setEnabled(false);
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush7(QColor(0, 0, 0, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush8(QColor(0, 0, 0, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush9(QColor(0, 0, 0, 128));
        brush9.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush9);
#endif
        doubleSpinBoxDeltaB->setPalette(palette2);

        gridLayout->addWidget(doubleSpinBoxDeltaB, 10, 1, 1, 1);

        doubleSpinBoxDeltaTau = new QDoubleSpinBox(widget);
        doubleSpinBoxDeltaTau->setObjectName(QString::fromUtf8("doubleSpinBoxDeltaTau"));
        doubleSpinBoxDeltaTau->setEnabled(false);
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush10(QColor(0, 0, 0, 128));
        brush10.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush10);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush11(QColor(0, 0, 0, 128));
        brush11.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush11);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush12(QColor(0, 0, 0, 128));
        brush12.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush12);
#endif
        doubleSpinBoxDeltaTau->setPalette(palette3);

        gridLayout->addWidget(doubleSpinBoxDeltaTau, 7, 1, 1, 1);

        listWidgetBsa = new QListWidget(widget);
        listWidgetBsa->setObjectName(QString::fromUtf8("listWidgetBsa"));

        gridLayout->addWidget(listWidgetBsa, 0, 0, 1, 2);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        doubleSpinBoxAlfaMounting = new QDoubleSpinBox(widget);
        doubleSpinBoxAlfaMounting->setObjectName(QString::fromUtf8("doubleSpinBoxAlfaMounting"));
        doubleSpinBoxAlfaMounting->setEnabled(false);
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush13(QColor(0, 0, 0, 128));
        brush13.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Active, QPalette::PlaceholderText, brush13);
#endif
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush14(QColor(0, 0, 0, 128));
        brush14.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush14);
#endif
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush15(QColor(0, 0, 0, 128));
        brush15.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush15);
#endif
        doubleSpinBoxAlfaMounting->setPalette(palette4);
        doubleSpinBoxAlfaMounting->setMinimum(-180.000000000000000);
        doubleSpinBoxAlfaMounting->setMaximum(180.000000000000000);

        gridLayout->addWidget(doubleSpinBoxAlfaMounting, 4, 1, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 10, 0, 1, 1);

        doubleSpinBoxGamma = new QDoubleSpinBox(widget);
        doubleSpinBoxGamma->setObjectName(QString::fromUtf8("doubleSpinBoxGamma"));
        doubleSpinBoxGamma->setEnabled(false);
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush16(QColor(0, 0, 0, 128));
        brush16.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Active, QPalette::PlaceholderText, brush16);
#endif
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush17(QColor(0, 0, 0, 128));
        brush17.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush17);
#endif
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush18(QColor(0, 0, 0, 128));
        brush18.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush18);
#endif
        doubleSpinBoxGamma->setPalette(palette5);
        doubleSpinBoxGamma->setMinimum(0.000000000000000);
        doubleSpinBoxGamma->setMaximum(180.000000000000000);

        gridLayout->addWidget(doubleSpinBoxGamma, 3, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        comboBoxType = new QComboBox(widget);
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->setObjectName(QString::fromUtf8("comboBoxType"));
        comboBoxType->setEnabled(false);
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush19(QColor(0, 0, 0, 128));
        brush19.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette6.setBrush(QPalette::Active, QPalette::PlaceholderText, brush19);
#endif
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush20(QColor(0, 0, 0, 128));
        brush20.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette6.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush20);
#endif
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush21(QColor(0, 0, 0, 128));
        brush21.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette6.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush21);
#endif
        comboBoxType->setPalette(palette6);
        comboBoxType->setEditable(true);

        gridLayout->addWidget(comboBoxType, 1, 1, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lineEditName = new QLineEdit(widget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setEnabled(false);
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush22(QColor(0, 0, 0, 128));
        brush22.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette7.setBrush(QPalette::Active, QPalette::PlaceholderText, brush22);
#endif
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush23(QColor(0, 0, 0, 128));
        brush23.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette7.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush23);
#endif
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush24(QColor(0, 0, 0, 128));
        brush24.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette7.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush24);
#endif
        lineEditName->setPalette(palette7);

        gridLayout->addWidget(lineEditName, 2, 1, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_11 = new QLabel(widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 6, 0, 1, 1);

        doubleSpinBoxBetaMounting = new QDoubleSpinBox(widget);
        doubleSpinBoxBetaMounting->setObjectName(QString::fromUtf8("doubleSpinBoxBetaMounting"));
        doubleSpinBoxBetaMounting->setEnabled(false);
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush25(QColor(0, 0, 0, 128));
        brush25.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette8.setBrush(QPalette::Active, QPalette::PlaceholderText, brush25);
#endif
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush26(QColor(0, 0, 0, 128));
        brush26.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette8.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush26);
#endif
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush27(QColor(0, 0, 0, 128));
        brush27.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette8.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush27);
#endif
        doubleSpinBoxBetaMounting->setPalette(palette8);
        doubleSpinBoxBetaMounting->setMinimum(-180.000000000000000);
        doubleSpinBoxBetaMounting->setMaximum(180.000000000000000);

        gridLayout->addWidget(doubleSpinBoxBetaMounting, 6, 1, 1, 1);

        doubleSpinBoxDeltaH = new QDoubleSpinBox(widget);
        doubleSpinBoxDeltaH->setObjectName(QString::fromUtf8("doubleSpinBoxDeltaH"));
        doubleSpinBoxDeltaH->setMaximum(180.000000000000000);

        gridLayout->addWidget(doubleSpinBoxDeltaH, 11, 1, 1, 1);

        doubleSpinBoxDeltaV = new QDoubleSpinBox(widget);
        doubleSpinBoxDeltaV->setObjectName(QString::fromUtf8("doubleSpinBoxDeltaV"));
        doubleSpinBoxDeltaV->setMaximum(180.000000000000000);

        gridLayout->addWidget(doubleSpinBoxDeltaV, 12, 1, 1, 1);

        label_12 = new QLabel(widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 11, 0, 1, 1);

        label_13 = new QLabel(widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 12, 0, 1, 1);

        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 13, 0, 1, 1);

        doubleSpinBoxDeltaL = new QDoubleSpinBox(widget);
        doubleSpinBoxDeltaL->setObjectName(QString::fromUtf8("doubleSpinBoxDeltaL"));
        doubleSpinBoxDeltaL->setMaximum(100000.000000000000000);

        gridLayout->addWidget(doubleSpinBoxDeltaL, 13, 1, 1, 1);

        label_15 = new QLabel(widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 18, 0, 1, 1);

        toolButtonAddParam = new QToolButton(widget);
        toolButtonAddParam->setObjectName(QString::fromUtf8("toolButtonAddParam"));
        toolButtonAddParam->setArrowType(Qt::DownArrow);

        gridLayout->addWidget(toolButtonAddParam, 18, 1, 1, 1);

        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 15, 0, 1, 1);

        label_17 = new QLabel(widget);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 14, 0, 1, 1);

        label_18 = new QLabel(widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 16, 0, 1, 1);

        label_19 = new QLabel(widget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 17, 0, 1, 1);

        doubleSpinBox_Resolving_Power = new QDoubleSpinBox(widget);
        doubleSpinBox_Resolving_Power->setObjectName(QString::fromUtf8("doubleSpinBox_Resolving_Power"));

        gridLayout->addWidget(doubleSpinBox_Resolving_Power, 14, 1, 1, 1);

        doubleSpinBox_focus = new QDoubleSpinBox(widget);
        doubleSpinBox_focus->setObjectName(QString::fromUtf8("doubleSpinBox_focus"));

        gridLayout->addWidget(doubleSpinBox_focus, 15, 1, 1, 1);

        doubleSpinBox_contPZS = new QDoubleSpinBox(widget);
        doubleSpinBox_contPZS->setObjectName(QString::fromUtf8("doubleSpinBox_contPZS"));

        gridLayout->addWidget(doubleSpinBox_contPZS, 16, 1, 1, 1);

        doubleSpinBox_Length_line = new QDoubleSpinBox(widget);
        doubleSpinBox_Length_line->setObjectName(QString::fromUtf8("doubleSpinBox_Length_line"));

        gridLayout->addWidget(doubleSpinBox_Length_line, 17, 1, 1, 1);


        verticalLayout_7->addLayout(gridLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pushButtonAddBsa = new QPushButton(widget);
        pushButtonAddBsa->setObjectName(QString::fromUtf8("pushButtonAddBsa"));

        horizontalLayout_6->addWidget(pushButtonAddBsa);

        pushButtonEditBsa = new QPushButton(widget);
        pushButtonEditBsa->setObjectName(QString::fromUtf8("pushButtonEditBsa"));

        horizontalLayout_6->addWidget(pushButtonEditBsa);

        pushButtonDelBsa = new QPushButton(widget);
        pushButtonDelBsa->setObjectName(QString::fromUtf8("pushButtonDelBsa"));

        horizontalLayout_6->addWidget(pushButtonDelBsa);

        pushButtonSaveBsa = new QPushButton(widget);
        pushButtonSaveBsa->setObjectName(QString::fromUtf8("pushButtonSaveBsa"));
        pushButtonSaveBsa->setEnabled(false);

        horizontalLayout_6->addWidget(pushButtonSaveBsa);


        verticalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout->addWidget(widget);


        horizontalLayout_5->addWidget(groupBox_bal);


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonLoadFile = new QPushButton(OrbInputClass);
        pushButtonLoadFile->setObjectName(QString::fromUtf8("pushButtonLoadFile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonLoadFile->setIcon(icon);

        horizontalLayout->addWidget(pushButtonLoadFile);

        pushButtonAddDb = new QPushButton(OrbInputClass);
        pushButtonAddDb->setObjectName(QString::fromUtf8("pushButtonAddDb"));
        pushButtonAddDb->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/triangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddDb->setIcon(icon1);

        horizontalLayout->addWidget(pushButtonAddDb);

        pushButtonSystemCreateObj = new QPushButton(OrbInputClass);
        pushButtonSystemCreateObj->setObjectName(QString::fromUtf8("pushButtonSystemCreateObj"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSystemCreateObj->setIcon(icon2);

        horizontalLayout->addWidget(pushButtonSystemCreateObj);

        pushButtonCreateObj = new QPushButton(OrbInputClass);
        pushButtonCreateObj->setObjectName(QString::fromUtf8("pushButtonCreateObj"));
        pushButtonCreateObj->setIcon(icon2);

        horizontalLayout->addWidget(pushButtonCreateObj);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonSaveObj = new QPushButton(OrbInputClass);
        pushButtonSaveObj->setObjectName(QString::fromUtf8("pushButtonSaveObj"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSaveObj->setIcon(icon3);

        horizontalLayout->addWidget(pushButtonSaveObj);


        verticalLayout_6->addLayout(horizontalLayout);


        retranslateUi(OrbInputClass);

        QMetaObject::connectSlotsByName(OrbInputClass);
    } // setupUi

    void retranslateUi(QWidget *OrbInputClass)
    {
        OrbInputClass->setWindowTitle(QApplication::translate("OrbInputClass", "OrbInputNew", nullptr));
        label_sysKA->setText(QApplication::translate("OrbInputClass", "\320\241\320\270\321\201\321\202\320\265\320\274\320\260", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_sysKA->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("OrbInputClass", "\320\232\320\220 \321\201\320\270\321\201\321\202\320\265\320\274\321\213", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("OrbInputClass", "\320\241\320\270\321\201\321\202\320\265\320\274\320\260", nullptr));
        toolButtonAddObj->setText(QApplication::translate("OrbInputClass", "...", nullptr));
        toolButtonDelObj->setText(QApplication::translate("OrbInputClass", "...", nullptr));
        label_rezKA->setText(QApplication::translate("OrbInputClass", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\265 \320\232\320\220", nullptr));
        groupBox_bal->setTitle(QApplication::translate("OrbInputClass", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\276\320\261\321\212\320\265\320\272\321\202\320\260", nullptr));
        label->setText(QApplication::translate("OrbInputClass", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\321\213\320\265 \321\203\321\201\320\273\320\276\320\262\320\270\321\217 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_par->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("OrbInputClass", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_par->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("OrbInputClass", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200", nullptr));
        label_2->setText(QApplication::translate("OrbInputClass", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\221\320\241\320\232", nullptr));
        label_9->setText(QApplication::translate("OrbInputClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\277\320\276 \320\276\321\201\320\270 N \320\236\320\241\320\232, \320\274</span></p></body></html>", nullptr));
        label_7->setText(QApplication::translate("OrbInputClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\276\321\207\320\275\321\213\320\271 \321\203\320\263\320\276\320\273 \320\276\321\202\320\275\320\276\321\201\320\270\321\202\320\265\320\273\321\214\320\275\320\276 n, \320\263\321\200\320\260\320\264", nullptr));
        label_8->setText(QApplication::translate("OrbInputClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\277\320\276 \320\276\321\201\320\270 Tay \320\236\320\241\320\232, \320\274</span></p></body></html>", nullptr));
        label_6->setText(QApplication::translate("OrbInputClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\276\321\207\320\275\321\213\320\271 \321\203\320\263\320\276\320\273 \320\276\321\202\320\275\320\276\321\201\320\270\321\202\320\265\320\273\321\214\320\275\320\276, \320\263\321\200\320\260\320\264", nullptr));
        label_10->setText(QApplication::translate("OrbInputClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265  \320\277\320\276 \320\276\321\201\320\270 B \320\236\320\241\320\232, \320\274</span></p></body></html>", nullptr));
        label_3->setText(QApplication::translate("OrbInputClass", "\320\242\320\270\320\277 \320\260\320\277\320\277\320\260\321\200\320\260\321\202\321\203\321\200\321\213", nullptr));
        comboBoxType->setItemText(0, QApplication::translate("OrbInputClass", "\320\236\320\261\320\267\320\276\321\200 \320\236\320\255\320\241", nullptr));
        comboBoxType->setItemText(1, QApplication::translate("OrbInputClass", "\320\236\320\261\320\267\320\276\321\200 \320\240\320\233\320\241", nullptr));
        comboBoxType->setItemText(2, QApplication::translate("OrbInputClass", "\320\236\320\261\320\267\320\276\321\200 \320\240T\320\241", nullptr));
        comboBoxType->setItemText(3, QApplication::translate("OrbInputClass", "\320\235\320\260\320\262\320\270\320\263\320\260\321\206\320\270\321\217", nullptr));
        comboBoxType->setItemText(4, QApplication::translate("OrbInputClass", "\320\241\320\262\321\217\320\267\321\214", nullptr));
        comboBoxType->setItemText(5, QApplication::translate("OrbInputClass", "\320\230\320\275\321\201\320\277\320\265\320\272\321\206\320\270\321\217  \320\232\320\236", nullptr));
        comboBoxType->setItemText(6, QApplication::translate("OrbInputClass", "\320\236\320\255\320\241 \321\202\320\265\320\273\320\265\320\262\320\270\320\267.", nullptr));
        comboBoxType->setItemText(7, QApplication::translate("OrbInputClass", "\320\236\320\255\320\241 \321\204\320\276\321\202\320\276", nullptr));
        comboBoxType->setItemText(8, QApplication::translate("OrbInputClass", "\320\235\320\265\320\276\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\276", nullptr));

        label_4->setText(QApplication::translate("OrbInputClass", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_5->setText(QApplication::translate("OrbInputClass", "\320\234\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\321\213\320\271 \321\203\320\263\320\276\320\273 \320\277\320\276\320\273\321\203\321\200\320\260\321\201\321\202\320\262\320\276\321\200\320\260", nullptr));
        label_11->setText(QApplication::translate("OrbInputClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\276\321\207\320\275\321\213\320\271 \321\203\320\263\320\276\320\273 \320\276\321\202\320\275\320\276\321\201\320\270\321\202\320\265\320\273\321\214\320\275\320\276 b, \320\263\321\200\320\260\320\264", nullptr));
        label_12->setText(QApplication::translate("OrbInputClass", "\320\243\320\263\320\276\320\273 \321\200\320\260\321\201\321\202\320\262\320\276\321\200\320\260 \320\277\320\276 \320\263\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\320\270, \320\263\321\200\320\260\320\264", nullptr));
        label_13->setText(QApplication::translate("OrbInputClass", "\320\243\320\263\320\276\320\273 \321\200\320\260\321\201\321\202\320\262\320\276\321\200\320\260 \320\277\320\276 \320\262\320\265\321\200\321\202\320\270\320\272\320\260\320\273\320\270, \320\263\321\200\320\260\320\264", nullptr));
        label_14->setText(QApplication::translate("OrbInputClass", "\320\250\320\270\321\200\320\270\320\275\320\260 \320\277\320\276\320\273\320\276\321\201\321\213 \320\276\320\261\320\267\320\276\321\200\320\260 , \320\272\320\274", nullptr));
        label_15->setText(QApplication::translate("OrbInputClass", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        toolButtonAddParam->setText(QApplication::translate("OrbInputClass", "...", nullptr));
        label_16->setText(QApplication::translate("OrbInputClass", "\320\244\320\276\320\272\321\203\321\201\320\275\320\276\320\265 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\265, \320\274", nullptr));
        label_17->setText(QApplication::translate("OrbInputClass", "\320\240\320\260\320\267\321\200\320\265\321\210. \321\201\320\277\320\276\321\201\320\276\320\261\320\275\320\276\321\201\321\202\321\214, \320\273\320\270\320\275/\320\274\320\274", nullptr));
        label_18->setText(QApplication::translate("OrbInputClass", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\215\320\273\320\265\320\274\320\275\321\202\320\276\320\262 \320\237\320\227\320\241 , \321\210\321\202", nullptr));
        label_19->setText(QApplication::translate("OrbInputClass", "\320\224\320\273\320\270\320\275\320\260 \321\204\320\276\321\202\320\276\320\277\321\200\320\270\320\265\320\274\320\275\320\276\320\271 \320\273\320\270\320\275\320\265\320\271\320\272\320\270, \320\274", nullptr));
        pushButtonAddBsa->setText(QApplication::translate("OrbInputClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButtonEditBsa->setText(QApplication::translate("OrbInputClass", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pushButtonDelBsa->setText(QApplication::translate("OrbInputClass", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        pushButtonSaveBsa->setText(QApplication::translate("OrbInputClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        pushButtonLoadFile->setText(QApplication::translate("OrbInputClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", nullptr));
        pushButtonAddDb->setText(QApplication::translate("OrbInputClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\267 \320\221\320\224", nullptr));
        pushButtonSystemCreateObj->setText(QApplication::translate("OrbInputClass", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\201\320\270\321\201\321\202\320\265\320\274\321\203 \320\232\320\220", nullptr));
        pushButtonCreateObj->setText(QApplication::translate("OrbInputClass", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\276\321\202\320\264\320\265\320\273\321\214\320\275\321\213\320\271 \320\232\320\220", nullptr));
        pushButtonSaveObj->setText(QApplication::translate("OrbInputClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 \321\204\320\260\320\271\320\273\320\265 XML", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrbInputClass: public Ui_OrbInputClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORBINPUT_H
