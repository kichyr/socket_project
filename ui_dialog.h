/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QListWidget *log;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *IP;
    QLineEdit *ip;
    QHBoxLayout *horizontalLayout_3;
    QLabel *Port;
    QLineEdit *port;
    QPushButton *but_connect;
    QGroupBox *groupBox_2;
    QPushButton *but_send;
    QLineEdit *message;
    QPushButton *AddFile;
    QPushButton *entName;
    QLineEdit *name;

    void setupUi(QDialog *dialog)
    {
        if (dialog->objectName().isEmpty())
            dialog->setObjectName(QStringLiteral("dialog"));
        dialog->resize(491, 397);
        horizontalLayoutWidget = new QWidget(dialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 461, 191));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        log = new QListWidget(horizontalLayoutWidget);
        log->setObjectName(QStringLiteral("log"));

        horizontalLayout->addWidget(log);

        groupBox = new QGroupBox(dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 210, 481, 41));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 461, 33));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        IP = new QLabel(layoutWidget);
        IP->setObjectName(QStringLiteral("IP"));

        horizontalLayout_2->addWidget(IP);

        ip = new QLineEdit(layoutWidget);
        ip->setObjectName(QStringLiteral("ip"));

        horizontalLayout_2->addWidget(ip);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Port = new QLabel(layoutWidget);
        Port->setObjectName(QStringLiteral("Port"));

        horizontalLayout_3->addWidget(Port);

        port = new QLineEdit(layoutWidget);
        port->setObjectName(QStringLiteral("port"));

        horizontalLayout_3->addWidget(port);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        but_connect = new QPushButton(layoutWidget);
        but_connect->setObjectName(QStringLiteral("but_connect"));

        horizontalLayout_5->addWidget(but_connect);

        groupBox_2 = new QGroupBox(dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 250, 461, 141));
        but_send = new QPushButton(groupBox_2);
        but_send->setObjectName(QStringLiteral("but_send"));
        but_send->setGeometry(QRect(0, 110, 99, 27));
        message = new QLineEdit(groupBox_2);
        message->setObjectName(QStringLiteral("message"));
        message->setGeometry(QRect(0, 10, 461, 101));
        AddFile = new QPushButton(groupBox_2);
        AddFile->setObjectName(QStringLiteral("AddFile"));
        AddFile->setGeometry(QRect(100, 110, 99, 27));
        entName = new QPushButton(groupBox_2);
        entName->setObjectName(QStringLiteral("entName"));
        entName->setGeometry(QRect(360, 110, 99, 27));
        name = new QLineEdit(groupBox_2);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(240, 110, 113, 27));

        retranslateUi(dialog);

        QMetaObject::connectSlotsByName(dialog);
    } // setupUi

    void retranslateUi(QDialog *dialog)
    {
        dialog->setWindowTitle(QApplication::translate("dialog", "dialog", 0));
        groupBox->setTitle(QString());
        IP->setText(QApplication::translate("dialog", "IP", 0));
        ip->setText(QString());
        Port->setText(QApplication::translate("dialog", "Port", 0));
        but_connect->setText(QApplication::translate("dialog", "Connect", 0));
        groupBox_2->setTitle(QString());
        but_send->setText(QApplication::translate("dialog", "Send", 0));
        AddFile->setText(QApplication::translate("dialog", "AddFile", 0));
        entName->setText(QApplication::translate("dialog", "EnerName", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog: public Ui_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
