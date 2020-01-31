#include "mainwindow.h"
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
    cboxPortName = ui->cboxPortName;
    cboxBaudRate = ui->cboxBaudRate;
    cboxDataBits = ui->cboxDataBits;
    cboxParity = ui->cboxParity;
    cboxStopBits = ui->cboxStopBits;
    cboxFlowControl = ui->cboxFlowControl;
    btnOpenPort = ui->btnOpenPort;
    btnClosePort = ui->btnClosePort;
    btnSendCommand = ui->btnSendCommand;
    lEditCommand = ui->lEditCommand;

    initCheckBoxes();


    serial = new QSerialPort(this);

    /* serial->setPortName("ttyUSB3");
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


    qDebug() << serial->isOpen();
    qDebug() << serial->isReadable();*/

    connect(serial,&QSerialPort::readyRead,this,&MainWindow::serialReceived);
    connect(btnOpenPort,&QPushButton::clicked, this,&MainWindow::openSerialPort);
    connect(btnClosePort,&QPushButton::clicked,this,&MainWindow::closeSerialPort);
    connect(btnSendCommand,&QPushButton::clicked,this,&MainWindow::sendCommand);


}


void MainWindow::processData(QString data)
{
    //qDebug() << data;
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
                        GGASentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[11]);
                        qDebug() << s.toString();
                        plainText->insertPlainText(s.toString());
                    }
                    else if(QString::compare(parts[0],"GPRMC")== 0){
                        RMCSentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10],parts[11],parts[12]);
                        qDebug() << s.toString();
                        plainText->insertPlainText(s.toString());
                    }else if(QString::compare(parts[0],"GPGLL") == 0){
                        GLLSentence s (parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6]);
                        qDebug() << s.toString();
                        plainText->insertPlainText(s.toString());
                        //qDebug() << s.getSentenceIdentifier() << s.getLatitude() << s.getLatitudeDirection() << s.getLongitude() << s.getLongitudeDirection() << s.getFixTime() << s.getStatus();
                    }else if (QString::compare(parts[0],"GPVTG") == 0){
                        VTGSentence s (parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9]);
                        qDebug() << s.toString();
                        plainText->insertPlainText(s.toString());

                        //                        qDebug() << s.getSentenceIdentifier() << s.getTrackDegree() << s.getTrackReference() << s.getTrackDegreeMagnetic() << s.getTrackDegreeMagRef() << s.getSpeedInKnots() << s.getSpeedForKnots() << s.getSpeedInKm() << s.getSpeedForKm() << s.getStatus();
                    }else if(QString::compare(parts[0],"GPZDA")==0){
                        ZDASentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6]);
                        qDebug() << s.toString();
                        plainText->insertPlainText(s.toString());
                        //                        qDebug() << s.getSentenceIdentifier() << s.getUtcTime() << s.getDate() << s.getLocalZoneHours() << s.getLocalZoneMinutes();
                    }else if(QString::compare(parts[0],"GPGNS")==0){
                        GNSSentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10],parts[11]);
                        //qDebug() << s.getSentenceIdentifier() << s.getFixTime() << s.getLatitude() << s.getLatitudeDirection() << s.getLatitudeDirection() << s.getLongitude() << s.getLongitudeDirection() << s.getMode() << s.getNumberOfStallites() << s.getHDOP() << s.getOrthometricHeight() << s.getGeoidalSeparation() << s.getReferenceStationId();
                        qDebug() << s.toString();
                        plainText->insertPlainText(s.toString());
                    }else if(QString::compare(parts[0],"GPHDT")==0){
                        HDTSentence s(parts[0],parts[1],parts[2]);
                        qDebug() << s.getSentenceIdentifier() << s.getDegree() << s.getRelative();
                    }else if(QString::compare(parts[0],"GPGSA")==0){
                        QList<int> list;
                        for(int i = 3 ; i <= 14 ; i++){
                            list.append(parts[i].toInt());
                        }
                        GSASentence s (parts[0],parts[1],parts[2],list,parts[15],parts[16],parts[17]);
                        //plainText->insertPlainText(s.toString());
                        qDebug()  << s.toString();
                    }else if(QString::compare(parts[0],"GPGSV") == 0){
                        //qDebug() << parts.size();
                        QList<GSVDetail*> list;
                        GSVDetail *detail;
                        if(parts.size() < 20){
                            qDebug() << "message is corrupted.";
                        }else{
                            for(int i = 8 ; i < 20 ; i+=4 ){
                                detail = new GSVDetail(parts[i],parts[i+1],parts[i+2],parts[i+3]);
                                list.append(detail);
                            }
                            GSVSentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],list);
                            //qDebug() << s.getTotalMessageNum() << s.getMessageNumber()  << s.getTotalNumberSatallites() << s.getSatallitePrnNumber() << s.getElevationDegree() << s.getAzimuthDegree() << s.getSNR() << s.getSvlist();
                            qDebug() << s.toString();
                            plainText->insertPlainText(s.toString());
                        }
                    }
                }
            }else{
                return;
            }
        }
    }
}

bool MainWindow::openSerialPort()
{
    serial->setPortName(cboxPortName->currentText());
    serial->setBaudRate(cboxBaudRate->currentText().toInt());
    qDebug() << QMetaEnum::fromType<QSerialPort::DataBits>().valueToKey(cboxDataBits->currentText().toInt());

    serial->setDataBits(static_cast<QSerialPort::DataBits>(cboxDataBits->currentText().toInt()));
    serial->setParity(static_cast<QSerialPort::Parity>(cboxParity->currentText().toInt()));
    serial->setStopBits(static_cast<QSerialPort::StopBits>(cboxStopBits->currentText().toInt()));
    serial->setFlowControl(static_cast<QSerialPort::FlowControl>(cboxFlowControl->currentText().toInt()));
    if(serial->open(QIODevice::ReadWrite)){
        qDebug() << "connected";
        btnOpenPort->setEnabled(false);
        btnOpenPort->setStyleSheet("background-color: rgb(0,255,0)");
    } else{
        qDebug() << serial->errorString();
        QMessageBox::information(this,"Error",serial->errorString());

    }

    return  serial->isOpen();
}

/**
  @returns TRUE when port is successfully closed.
*/
bool MainWindow::closeSerialPort()
{
    if(serial->isOpen()){
        serial->close();
        btnOpenPort->setEnabled(true);
        btnOpenPort->setStyleSheet("");
        QApplication::processEvents();
        QMessageBox::information(this,"Port Closed","Port is closed.");
        return true;
    }
    return false;
}

void MainWindow::initCheckBoxes()
{

    foreach(const QSerialPortInfo &serialPortInfo , QSerialPortInfo::availablePorts()){
        cboxPortName->addItem(serialPortInfo.portName());
    }
    cboxBaudRate->addItem(QString("1200"),QSerialPort::Baud1200);
    cboxBaudRate->addItem(QString("2400"),QSerialPort::Baud2400);
    cboxBaudRate->addItem(QString("4800"),QSerialPort::Baud4800);
    cboxBaudRate->addItem(QString("9600"),QSerialPort::Baud9600);
    cboxBaudRate->addItem(QString("19200"),QSerialPort::Baud19200);
    cboxBaudRate->addItem(QString("38400"),QSerialPort::Baud38400);
    cboxBaudRate->addItem(QString("57600"),QSerialPort::Baud57600);
    cboxBaudRate->addItem(QString("115200"),QSerialPort::Baud115200);
    cboxBaudRate->setCurrentIndex(3);

    cboxDataBits->addItem(QString("5"), QSerialPort::Data5);
    cboxDataBits->addItem(QString("6"), QSerialPort::Data6);
    cboxDataBits->addItem(QString("7"), QSerialPort::Data7);
    cboxDataBits->addItem(QString("8"), QSerialPort::Data8);
    cboxDataBits->setCurrentIndex(3);

    cboxParity->addItem(tr("None"), QSerialPort::NoParity);
    cboxParity->addItem(tr("Even"), QSerialPort::EvenParity);
    cboxParity->addItem(tr("Odd"), QSerialPort::OddParity);
    cboxParity->addItem(tr("Mark"), QSerialPort::MarkParity);
    cboxParity->addItem(tr("Space"), QSerialPort::SpaceParity);

    cboxStopBits->addItem(QString("1"), QSerialPort::OneStop);
    cboxStopBits->addItem(QString("2"), QSerialPort::TwoStop);

    cboxFlowControl->addItem(QString("None"), QSerialPort::NoFlowControl);
    cboxFlowControl->addItem(QString("RTS/CTS"), QSerialPort::HardwareControl);
    cboxFlowControl->addItem(QString("XON/XOFF"), QSerialPort::SoftwareControl);
}

void MainWindow::sendCommand()
{
    QString cmdFromGUI = lEditCommand->text();
    qDebug() << cmdFromGUI;
    char *cmdChar = cmdFromGUI.toUtf8().data();
    int checksum = calculateCheckSum(cmdChar);

    QString hex = QString("%1").arg(checksum,2,16,QLatin1Char('0'));
    qDebug() << hex;


    QString cmdToSend= "";
    cmdToSend.append("$");
    cmdToSend.append(cmdFromGUI);
    cmdToSend.append("*");
    cmdToSend.append(hex);
    cmdToSend.append(QChar(13));
    cmdToSend.append(QChar(10));

    //cmdToSend = "$PMTK314,-1*04\r\n";

    qDebug() <<"yollanacak"<< cmdToSend;
    qDebug() <<"yollanacak byte array"<< cmdToSend.toLocal8Bit();

    qDebug() << "serial is writable " << serial->isWritable();
    qDebug() <<  serial->write(cmdToSend.toLocal8Bit(),cmdToSend.size());

    serial->flush();

}

static QString strData;

void MainWindow::serialReceived()
{

    //qDebug() << __PRETTY_FUNCTION__;
    //qDebug() << "received";
    qint64 bufferSize = serial->bytesAvailable();
    if(bufferSize > 0){
        QString data = QString(serial->readAll());
        strData.append(data);
        //qDebug() << "strData" + strData;
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

MainWindow::~MainWindow()
{
    delete ui;
}



