#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QMetaEnum>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <ggasentence.h>
#include <pmtksentence.h>
#include <rmcsentence.h>
#include <gllsentence.h>
#include <vtgsentence.h>
#include <zdasentence.h>
#include <gnssentence.h>
#include <hdtsentence.h>
#include <gsasentence.h>
#include <gsvdetail.h>
#include <gsvsentence.h>
#include <QStringLiteral>
#include <QDesktopServices>
#include <QScrollArea>
#include <QDir>
#include <QSqlQueryModel>
#include "dbmanager.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void serialReceived();
    void handleError(QSerialPort::SerialPortError error);
    void processData(QString data);
    bool openSerialPort();
    bool closeSerialPort();
    void initCheckBoxes();
    void sendCommand();
    void enableSerialPortSettings();
    void disableSerialPortSettings();


    void on_actionOpen_the_Doc_triggered();
    void on_tabWidget_currentChanged(int index);
    void on_tableView_doubleClicked(const QModelIndex &index);
    void clearDetailLayout();
    void createGroupBox(QString title,QList<QString> list);



private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QPlainTextEdit *plainText;
    QLineEdit *lEditCommand;
    QComboBox *cboxPortName,*cboxBaudRate,*cboxDataBits, *cboxParity,*cboxStopBits,*cboxFlowControl;
    QPushButton *btnOpenPort, *btnClosePort,*btnSendCommand;
    DbManager dbManager;
    QScrollArea *scrollArea;
    QWidget *sAreaContent;
    QVBoxLayout *detailVertical;


};
#endif // MAINWINDOW_H
