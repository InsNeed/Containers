/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_name;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_inpuit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_PORT;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QLineEdit *lineEdit_IP;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonSend;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowserDB;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineEdit_inpuitName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QSpinBox *spinBoxNum;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButtonSelect;
    QPushButton *pushButton_clear;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(735, 513);
        horizontalLayout_10 = new QHBoxLayout(Dialog);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(Dialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEdit_name = new QLineEdit(Dialog);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));

        horizontalLayout->addWidget(lineEdit_name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_inpuit = new QLineEdit(Dialog);
        lineEdit_inpuit->setObjectName(QString::fromUtf8("lineEdit_inpuit"));

        horizontalLayout_4->addWidget(lineEdit_inpuit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_PORT = new QLineEdit(Dialog);
        lineEdit_PORT->setObjectName(QString::fromUtf8("lineEdit_PORT"));

        horizontalLayout_2->addWidget(lineEdit_PORT);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_7->addWidget(label);

        lineEdit_IP = new QLineEdit(Dialog);
        lineEdit_IP->setObjectName(QString::fromUtf8("lineEdit_IP"));

        horizontalLayout_7->addWidget(lineEdit_IP);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButtonConnect = new QPushButton(Dialog);
        pushButtonConnect->setObjectName(QString::fromUtf8("pushButtonConnect"));

        horizontalLayout_5->addWidget(pushButtonConnect);

        pushButtonSend = new QPushButton(Dialog);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));

        horizontalLayout_5->addWidget(pushButtonSend);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_9->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textBrowserDB = new QTextBrowser(Dialog);
        textBrowserDB->setObjectName(QString::fromUtf8("textBrowserDB"));

        verticalLayout_2->addWidget(textBrowserDB);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_inpuitName = new QLineEdit(Dialog);
        lineEdit_inpuitName->setObjectName(QString::fromUtf8("lineEdit_inpuitName"));

        horizontalLayout_6->addWidget(lineEdit_inpuitName);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        spinBoxNum = new QSpinBox(Dialog);
        spinBoxNum->setObjectName(QString::fromUtf8("spinBoxNum"));
        spinBoxNum->setMaximum(800);
        spinBoxNum->setValue(10);

        horizontalLayout_3->addWidget(spinBoxNum);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButtonSelect = new QPushButton(Dialog);
        pushButtonSelect->setObjectName(QString::fromUtf8("pushButtonSelect"));

        horizontalLayout_8->addWidget(pushButtonSelect);

        pushButton_clear = new QPushButton(Dialog);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        horizontalLayout_8->addWidget(pushButton_clear);


        verticalLayout_2->addLayout(horizontalLayout_8);


        horizontalLayout_9->addLayout(verticalLayout_2);


        horizontalLayout_10->addLayout(horizontalLayout_9);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "\345\247\223\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "\345\206\205\345\256\271", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "PORT", nullptr));
        lineEdit_PORT->setText(QCoreApplication::translate("Dialog", "8887", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "IP", nullptr));
        lineEdit_IP->setText(QCoreApplication::translate("Dialog", "172.19.19.17", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("Dialog", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        pushButtonSend->setText(QCoreApplication::translate("Dialog", "\345\217\221\351\200\201", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "\346\214\207\345\256\232\345\247\223\345\220\215\346\237\245\350\257\242", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "\346\235\241\346\225\260", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("Dialog", "\346\237\245\350\257\242", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("Dialog", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
