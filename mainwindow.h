#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QNmeaPositionInfoSource>
#include <QPlainTextEdit>
#include <ggasentence.h>

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
    void positionUpdated(QGeoPositionInfo positionInfo);
    void updateTimeout(void);
    void error(QGeoPositionInfoSource::Error positioningError);
    void updateSerialData();


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QNmeaPositionInfoSource *nmeaSource;
    QPlainTextEdit *plainText;
    QTimer *mPollTimer;

    int calculateCheckSum(const char* s);

};
#endif // MAINWINDOW_H
