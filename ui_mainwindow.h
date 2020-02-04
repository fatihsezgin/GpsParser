/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *cboxPortName;
    QLabel *label_2;
    QComboBox *cboxBaudRate;
    QLabel *label_3;
    QComboBox *cboxDataBits;
    QLabel *label_7;
    QComboBox *cboxParity;
    QLabel *label_8;
    QComboBox *cboxStopBits;
    QLabel *label_9;
    QComboBox *cboxFlowControl;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpenPort;
    QPushButton *btnClosePort;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *lEditCommand;
    QPushButton *btnSendCommand;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(867, 632);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 350, 841, 231));
        plainTextEdit->setAutoFillBackground(false);
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color : rgb(211, 215, 207)\n"
""));
        plainTextEdit->setReadOnly(true);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 201, 271));
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 30, 201, 223));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        cboxPortName = new QComboBox(verticalLayoutWidget);
        cboxPortName->setObjectName(QString::fromUtf8("cboxPortName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboxPortName);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        cboxBaudRate = new QComboBox(verticalLayoutWidget);
        cboxBaudRate->setObjectName(QString::fromUtf8("cboxBaudRate"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cboxBaudRate);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        cboxDataBits = new QComboBox(verticalLayoutWidget);
        cboxDataBits->setObjectName(QString::fromUtf8("cboxDataBits"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cboxDataBits);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_7);

        cboxParity = new QComboBox(verticalLayoutWidget);
        cboxParity->setObjectName(QString::fromUtf8("cboxParity"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cboxParity);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_8);

        cboxStopBits = new QComboBox(verticalLayoutWidget);
        cboxStopBits->setObjectName(QString::fromUtf8("cboxStopBits"));

        formLayout->setWidget(4, QFormLayout::FieldRole, cboxStopBits);

        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_9);

        cboxFlowControl = new QComboBox(verticalLayoutWidget);
        cboxFlowControl->setObjectName(QString::fromUtf8("cboxFlowControl"));

        formLayout->setWidget(5, QFormLayout::FieldRole, cboxFlowControl);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnOpenPort = new QPushButton(verticalLayoutWidget);
        btnOpenPort->setObjectName(QString::fromUtf8("btnOpenPort"));

        horizontalLayout->addWidget(btnOpenPort);

        btnClosePort = new QPushButton(verticalLayoutWidget);
        btnClosePort->setObjectName(QString::fromUtf8("btnClosePort"));

        horizontalLayout->addWidget(btnClosePort);


        verticalLayout->addLayout(horizontalLayout);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(290, 310, 561, 27));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lEditCommand = new QLineEdit(layoutWidget);
        lEditCommand->setObjectName(QString::fromUtf8("lEditCommand"));

        horizontalLayout_2->addWidget(lEditCommand);

        btnSendCommand = new QPushButton(layoutWidget);
        btnSendCommand->setObjectName(QString::fromUtf8("btnSendCommand"));

        horizontalLayout_2->addWidget(btnSendCommand);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 867, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Serial Port Settings", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Port Name", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Baud Rate", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Data Bits", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Parity", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "StopBits", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Flow Control", nullptr));
        btnOpenPort->setText(QCoreApplication::translate("MainWindow", "Open Port", nullptr));
        btnClosePort->setText(QCoreApplication::translate("MainWindow", "Close Port", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "$", nullptr));
        btnSendCommand->setText(QCoreApplication::translate("MainWindow", "Send Command", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
