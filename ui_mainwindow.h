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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
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
    QAction *actionOpen_the_Doc;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
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
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpenPort;
    QPushButton *btnClosePort;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QLineEdit *lEditCommand;
    QPushButton *btnSendCommand;
    QHBoxLayout *horizontalLayout_3;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menubar;
    QMenu *menuDocumentation;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(768, 417);
        actionOpen_the_Doc = new QAction(MainWindow);
        actionOpen_the_Doc->setObjectName(QString::fromUtf8("actionOpen_the_Doc"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        cboxPortName = new QComboBox(groupBox);
        cboxPortName->setObjectName(QString::fromUtf8("cboxPortName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboxPortName);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        cboxBaudRate = new QComboBox(groupBox);
        cboxBaudRate->setObjectName(QString::fromUtf8("cboxBaudRate"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cboxBaudRate);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        cboxDataBits = new QComboBox(groupBox);
        cboxDataBits->setObjectName(QString::fromUtf8("cboxDataBits"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cboxDataBits);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_7);

        cboxParity = new QComboBox(groupBox);
        cboxParity->setObjectName(QString::fromUtf8("cboxParity"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cboxParity);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_8);

        cboxStopBits = new QComboBox(groupBox);
        cboxStopBits->setObjectName(QString::fromUtf8("cboxStopBits"));

        formLayout->setWidget(4, QFormLayout::FieldRole, cboxStopBits);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_9);

        cboxFlowControl = new QComboBox(groupBox);
        cboxFlowControl->setObjectName(QString::fromUtf8("cboxFlowControl"));

        formLayout->setWidget(5, QFormLayout::FieldRole, cboxFlowControl);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnOpenPort = new QPushButton(groupBox);
        btnOpenPort->setObjectName(QString::fromUtf8("btnOpenPort"));

        horizontalLayout->addWidget(btnOpenPort);

        btnClosePort = new QPushButton(groupBox);
        btnClosePort->setObjectName(QString::fromUtf8("btnClosePort"));

        horizontalLayout->addWidget(btnClosePort);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lEditCommand = new QLineEdit(centralwidget);
        lEditCommand->setObjectName(QString::fromUtf8("lEditCommand"));

        horizontalLayout_2->addWidget(lEditCommand);

        btnSendCommand = new QPushButton(centralwidget);
        btnSendCommand->setObjectName(QString::fromUtf8("btnSendCommand"));
        btnSendCommand->setAutoDefault(false);

        horizontalLayout_2->addWidget(btnSendCommand);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setAutoFillBackground(false);
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color : rgb(211, 215, 207)\n"
""));
        plainTextEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(plainTextEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 768, 22));
        menuDocumentation = new QMenu(menubar);
        menuDocumentation->setObjectName(QString::fromUtf8("menuDocumentation"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(btnSendCommand, cboxPortName);
        QWidget::setTabOrder(cboxPortName, cboxBaudRate);
        QWidget::setTabOrder(cboxBaudRate, cboxDataBits);
        QWidget::setTabOrder(cboxDataBits, cboxParity);
        QWidget::setTabOrder(cboxParity, cboxStopBits);
        QWidget::setTabOrder(cboxStopBits, cboxFlowControl);
        QWidget::setTabOrder(cboxFlowControl, btnOpenPort);
        QWidget::setTabOrder(btnOpenPort, btnClosePort);
        QWidget::setTabOrder(btnClosePort, lEditCommand);
        QWidget::setTabOrder(lEditCommand, plainTextEdit);

        menubar->addAction(menuDocumentation->menuAction());
        menuDocumentation->addAction(actionOpen_the_Doc);

        retranslateUi(MainWindow);

        btnSendCommand->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gps Parser", nullptr));
        actionOpen_the_Doc->setText(QCoreApplication::translate("MainWindow", "Open the Doc", nullptr));
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
        menuDocumentation->setTitle(QCoreApplication::translate("MainWindow", "Documentation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
