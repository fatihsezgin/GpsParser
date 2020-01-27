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
    serial->setPortName("ttyUSB2");

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

       /*mPollTimer = new QTimer( this );
        mPollTimer->setInterval( 1000 ); //poll every 1 second
        connect( mPollTimer, SIGNAL( timeout() ), this, SLOT( updateSerialData() ) );
        mPollTimer->start();*/

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
       /* if( !serial->bytesAvailable() )
          return;
*/
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

void MainWindow::processData(QString data)
{
    if(data.isEmpty() || !data.contains("\r\n")) return;

    QList<QString> parts = data.split("\r\n");

    if(parts.isEmpty())  return;


    for(int i = 0; i< parts.size();i++){
        if(parts[i].isEmpty()){
                parts.removeAt(i);
        }else{
            QList<QString> part = parts[i].split('$');

            if(part.size() >3) return; // big data comes in and when parsing there are more than 3 elements will be in the list
            for(int j = 0 ; j < part.size();j++){//after splitting by $ the first item is $ so appears a ""
                if(part[j].isEmpty())
                    part.removeAt(j);
            }
            if(part.size() > 1){
                part.removeAt(0);

            }
            //qDebug() <<"part: " << part;

            QList<QString> strList = part[0].split("*");

            if(!strList.isEmpty()){
                char* firstPart = strList[0].toUtf8().data();// converting the data in char for calculating the checksum
                int test = calculateCheckSum(firstPart);//result comes in int
                bool ok;
                int result = strList[1].toInt(&ok,16);// converts hex to int
                    if(ok && test == result){

                            QList<QString> parts = strList[0].split(",");

                            if(QString::compare(parts[0],"GPGGA") == 0){
                                    GGASentence sentence(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10]);
                                    qDebug() << sentence.getSentId() << sentence.getFixedDate() << sentence.getLatitude() << sentence.getLatitudeDirection()<< sentence.getLongitude()<< sentence.getLongitudeDirection() << sentence.getFixQuality() << sentence.getNumberSatallites() << sentence.getHorizontalDilution() << sentence.getAltitude() << sentence.getHeightOfGeoid();
                            }
                            else if(QString::compare(parts[0],"GPRMC")== 0){
                                    RMCSentence sentence(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10],parts[11],parts[12]);
                                    qDebug() << sentence.getSentenceIdentifier() << sentence.getFixDate() << sentence.getStatus() << sentence.getLatitude() << sentence.getLongitude() << sentence.getSpeedOverGround() << sentence.getCourseOverGround() << sentence.getDate() << sentence.getMagneticVariation() << sentence.getModeIndicator() ;
                            }else if(QString::compare(parts[0],"GPGLL") == 0){
                                    GLLSentence sentence (parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6]);
                                    qDebug() << sentence.getSentenceIdentifier() << sentence.getLatitude() << sentence.getLatitudeDirection() << sentence.getLongitude() << sentence.getLongitudeDirection() << sentence.getFixTime() << sentence.getStatus();
                            }else if (QString::compare(parts[0],"GPVTG") == 0){
                                    VTGSentence sentence (parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9]);
                                    qDebug() << sentence.getSentenceIdentifier() << sentence.getTrackDegree() << sentence.getTrackReference() << sentence.getTrackDegreeMagnetic() << sentence.getTrackDegreeMagRef() << sentence.getSpeedInKnots() << sentence.getSpeedForKnots() << sentence.getSpeedInKm() << sentence.getSpeedForKm() << sentence.getStatus();
                            }
                            //plainText->insertPlainText();
                            //qDebug() << strlist[0] << strlist[1] << "test: " << test;
                  }
            }else{
                return;
            }
        }
    }
}

static QString strData;

void MainWindow::serialReceived()
{
    //qDebug() << "received";
    qint64 bufferSize = serial->bytesAvailable();
    if(bufferSize > 0){
        QString data = QString(serial->readAll());
        strData.append(data);
        //qDebug() << "data appendleniyor";

        if(strData.endsWith("\n")){
            //qDebug() << strData;
            //qDebug() << "\\n ile bitiyor";
            processData(strData);
            strData.clear();
        }else{

        }
    }else{
        //qDebug()<<"buffer a data gelmiyor";
        return;
    }

    /*QByteArray byteArray;
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
    }*/


    /*QTextCursor c = plainText->textCursor();
    c.movePosition(QTextCursor::End);
    plainText->setTextCursor(c);*/
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



