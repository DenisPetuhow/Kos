/********************************************************************************
** Form generated from reading UI file 'formscene.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSCENE_H
#define UI_FORMSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Formscene
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QLabel *label;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *Formscene)
    {
        if (Formscene->objectName().isEmpty())
            Formscene->setObjectName(QString::fromUtf8("Formscene"));
        Formscene->resize(1008, 638);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Formscene->sizePolicy().hasHeightForWidth());
        Formscene->setSizePolicy(sizePolicy);
        Formscene->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(Formscene);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(Formscene);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMinimumSize(QSize(769, 600));
        graphicsView->setFocusPolicy(Qt::NoFocus);
        graphicsView->setLayoutDirection(Qt::LeftToRight);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        label = new QLabel(Formscene);
        label->setObjectName(QString::fromUtf8("label"));
        label->setContextMenuPolicy(Qt::DefaultContextMenu);
        label->setLayoutDirection(Qt::RightToLeft);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        treeWidget = new QTreeWidget(Formscene);
        treeWidget->headerItem()->setText(0, QString());
        treeWidget->headerItem()->setText(1, QString());
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setMaximumSize(QSize(215, 16777215));
        treeWidget->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        treeWidget->setProperty("showDropIndicator", QVariant(true));
        treeWidget->setColumnCount(2);

        gridLayout->addWidget(treeWidget, 0, 1, 1, 1);


        retranslateUi(Formscene);

        QMetaObject::connectSlotsByName(Formscene);
    } // setupUi

    void retranslateUi(QWidget *Formscene)
    {
        Formscene->setWindowTitle(QApplication::translate("Formscene", "Form", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Formscene: public Ui_Formscene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSCENE_H
