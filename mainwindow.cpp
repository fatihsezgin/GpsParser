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
        QList<QString> strlist = ba.split("*");

        if(!strlist.isEmpty()){
            strlist[0].remove(0,1);//removing $
            strlist[1].remove(2,2);//removing line feeds after the data.

            char* firstPart = strlist[0].toUtf8().data();// converting the data in char for calculating the checksum

            int test = calculateCheckSum(firstPart);//result comes in int
            bool ok;
            int result = strlist[1].toInt(&ok,16);// converts hex to int
            if(ok && test == result){

                QList<QString> parts = strlist[0].split(",");

                if(QString::compare(parts[0],"GPGGA") == 0){
                        GGASentence sentence(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10]);
                        qDebug() << sentence.getSentId() << sentence.getFixedDate() << sentence.getLatitude() << sentence.getLongitude() << sentence.getFixQuality() << sentence.getNumberSatallites() << sentence.getHorizontalDilution() << sentence.getAltitude() << sentence.getHeightOfGeoid();
                }
                else if(QString::compare(parts[0],"GPRMC")== 0){
                        RMCSentence sentence(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10],parts[11],parts[12]);
                        qDebug() << sentence.getSentenceIdentifier() << sentence.getFixDate() << sentence.getStatus() << sentence.getLatitude() << sentence.getLongitude() << sentence.getSpeedOverGround() << sentence.getCourseOverGround() << sentence.getDate() << sentence.getMagneticVariation() << sentence.getModeIndicator() ;
                }
                plainText->insertPlainText(ba);
                //qDebug() << strlist[0] << strlist[1] << "test: " << test;
            }else{
                qDebug() << "Invalid data";
            }
        }
    }


    QTextCursor c = plainText->textCursor();
    c.movePosition(QTextCursor::End);
    plainText->setTextCursor(c);
}

int MainWindow::calculateCheckSum(const char* s){
    int  c = 0 ;
    while(*s){
        c ^= *s++;
    }
    return c;
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



