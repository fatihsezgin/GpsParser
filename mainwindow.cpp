#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QNmeaPositionInfoSource>
#include <QBuffer>
#include <QTextCodec>
#include <QTimer>


/** /var/lock usb LCK...usb {} datasını sil
*/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    plainText = ui->plainTextEdit;

    serial = new QSerialPort(this);
    serial->setPortName("ttyUSB0");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if(serial->open(QIODevice::ReadOnly)){
        qDebug() << "connected";
    } else{
        qDebug() << serial->errorString();
        qDebug() << "Open error";
    }

       /* mPollTimer = new QTimer( this );
        mPollTimer->setInterval( 1000 ); //poll every 1 second
        connect( mPollTimer, SIGNAL( timeout() ), this, SLOT( updateSerialData() ) );
        mPollTimer->start();
*/
    qDebug() << serial->isOpen();
    qDebug() << serial->isReadable();

    /*nmeaSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode);
    nmeaSource->setDevice(serial);
    nmeaSource->setUpdateInterval(1000);

    connect(nmeaSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        connect(nmeaSource, SIGNAL(updateTimeout()), this, SLOT(updateTimeout()));
        connect(nmeaSource,SIGNAL(error(QGeoPositionInfoSource::Error)),
                this,SLOT(error(QGeoPositionInfoSource::Error)));
        nmeaSource->startUpdates();*/



   connect(serial,&QSerialPort::readyRead,this,&MainWindow::serialReceived);


}

void MainWindow::updateSerialData(){

        char data[100];
        if( !serial->bytesAvailable() )
          return;

         int   charIdx = 0;
         do
         {
            data[charIdx] = 'A';
            serial->read( data, 1 );
         } while( data[charIdx] != '$' );
         charIdx++;

         do
         {
            charIdx += serial->read( &data[charIdx], 1 );
         } while( data[charIdx-1] != '*' );


         // Read check sum
         charIdx += serial->read( &data[charIdx], 2 );
         data[charIdx] = '\0';
         // Copy buffer to QString
         QString a ( data);
         qDebug() << a;

}


static QList<QByteArray> list;
static QString strData;

void MainWindow::serialReceived()
{
    QByteArray byteArray;
    while(serial->canReadLine()){
        byteArray = serial->readLine();
        QString ba(byteArray);
         qDebug() << ba;
        plainText->insertPlainText(ba);
    }


    QTextCursor c = plainText->textCursor();
    c.movePosition(QTextCursor::End);
    plainText->setTextCursor(c);
}

bool calculateCheckSum(QString data){
    QList<QString> packages = data.split("\r\n");

}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        qDebug() << serial->errorString();
    }
    serial->close();
}

void MainWindow::positionUpdated(QGeoPositionInfo positionInfo)
{
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << QString("Lat: %1").arg(QString::number(positionInfo.coordinate().latitude()));
    qDebug() << QString("Lon: %1").arg(QString::number(positionInfo.coordinate().longitude()));
    qDebug() <<QString("Alt : %1").arg(QString::number(positionInfo.coordinate().altitude()));
    qDebug() <<QString("Time : %1").arg(positionInfo.timestamp().toUTC().toString());

}

void MainWindow::updateTimeout(void)
{
    qDebug() << __PRETTY_FUNCTION__;
}

void MainWindow::error(QGeoPositionInfoSource::Error positioningError)
{
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << QString::number(positioningError);
}



MainWindow::~MainWindow()
{
    delete ui;
}



