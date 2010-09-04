/********************************************************************************
** Form generated from reading UI file 'toplevelwindow.ui'
**
** Created: Tue Aug 17 05:58:47 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPLEVELWINDOW_H
#define UI_TOPLEVELWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToplevelWindow
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *label;

    void setupUi(QWidget *ToplevelWindow)
    {
        if (ToplevelWindow->objectName().isEmpty())
            ToplevelWindow->setObjectName(QString::fromUtf8("ToplevelWindow"));
        ToplevelWindow->resize(559, 459);
        gridLayout = new QGridLayout(ToplevelWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(ToplevelWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(ToplevelWindow);

        QMetaObject::connectSlotsByName(ToplevelWindow);
    } // setupUi

    void retranslateUi(QWidget *ToplevelWindow)
    {
        ToplevelWindow->setWindowTitle(QApplication::translate("ToplevelWindow", "ToplevelWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ToplevelWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ToplevelWindow: public Ui_ToplevelWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPLEVELWINDOW_H
