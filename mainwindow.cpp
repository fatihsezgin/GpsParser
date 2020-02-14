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

    dbMenager.open();

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

    connect(serial,&QSerialPort::readyRead,this,&MainWindow::serialReceived);
    connect(btnOpenPort,&QPushButton::clicked, this,&MainWindow::openSerialPort);
    connect(btnClosePort,&QPushButton::clicked,this,&MainWindow::closeSerialPort);
    connect(btnSendCommand,&QPushButton::clicked,this,&MainWindow::sendCommand);
    connect(lEditCommand,&QLineEdit::returnPressed,this,&MainWindow::sendCommand);

}

void MainWindow::processData(QString data)
{
    qDebug() << "dataa"<< data;
    if(data.isEmpty() || !data.contains("\r\n")) return;

    QList<QString> parts = data.split("\r\n");

    if(parts.isEmpty())  return;

    bool gga = false;
    bool rmc = false;
    bool gll = false;
    bool gns = false;
    bool gsa = false;
    bool gsv = false;
    bool hdt = false;
    bool vtg= false;
    bool zda = false;



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
                int test = Helper::calculateCheckSum(firstPart);//result comes in int
                bool ok;
                int result = strList[1].toInt(&ok,16);// converts hex to int
                if(ok && test == result){

                    QList<QString> parts = strList[0].split(",");

                    if(parts[0].contains("GGA")){
                        GGASentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[11]);
                        qDebug() << s.toString();
                        dbMenager.insertGGA(&s);
                        gga = true;
                        plainText->insertPlainText(s.toString());
                    }
                    else if(parts[0].contains("RMC")){
                        RMCSentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10],parts[11],parts[12]);
                        qDebug() << s.toString();
                        dbMenager.insertRMC(&s);
                        rmc = true;
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("GLL")){
                        GLLSentence s (parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6]);
                        qDebug() << s.toString();
                        qDebug() << "gll"<<dbMenager.insertGLL(&s);
                        gll =true;
                        plainText->insertPlainText(s.toString());
                    }else if (parts[0].contains("VTG")){
                        VTGSentence s (parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9]);
                        qDebug() << s.toString();
                        dbMenager.insertVTG(&s);
                        vtg = true;
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("ZDA")){
                        ZDASentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6]);
                        qDebug() << s.toString();
                        dbMenager.insertZDA(&s);
                        zda = true;
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("GNS")){
                        GNSSentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10],parts[11]);
                        qDebug() << s.toString();
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("HDT")){
                        HDTSentence s(parts[0],parts[1],parts[2]);
                        qDebug() << s.getSentenceIdentifier() << s.getDegree() << s.getRelative();
                    }else if(parts[0].contains("GSA")){
                        QList<int> list;
                        for(int i = 3 ; i <= 14 ; i++){
                            list.append(parts[i].toInt());
                        }
                        GSASentence s (parts[0],parts[1],parts[2],list,parts[15],parts[16],parts[17]);
                        plainText->insertPlainText(s.toString());
                        qDebug()  << s.toString();
                    }else if(parts[0].contains("GSV")){
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
                            qDebug() << s.toString();
                            plainText->insertPlainText(s.toString());
                        }
                    }else if(parts[0].contains("PMTK")){
                            PMTKSentence s (parts,this);
                    }
                    dbMenager.commit();
                }
            }else{
                return;
            }
        }
    }
    qDebug() << "gga" << gga << "rmc " << rmc << "vtg" << vtg;
    dbMenager.prepareQuery(gga,rmc,gll,gns,gsa,gsv,hdt,vtg,zda);
    plainText->ensureCursorVisible();
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
        disableSerialPortSettings();


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
        enableSerialPortSettings();
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

    if(!serial->isOpen()){
        QMessageBox::information(this,"Serial Port Closed", "Please open serial port!");
        return;
    } 
    QString cmdFromGUI = lEditCommand->text().toUpper();// Get command from user.

    if(!cmdFromGUI.startsWith("p",Qt::CaseSensitivity::CaseInsensitive)){
        QMessageBox::information(this,"Wrong Command","Only PMTK sentences are supported"); //All commands should be started with P | p
        //lEditCommand->clear();
    }
    //qDebug() << cmdFromGUI;
    //char *cmdChar = cmdFromGUI.toUtf8().data();
    int checksum = Helper::calculateCheckSum(cmdFromGUI.toUtf8().data()); // for calculating the checksum checksum is converted into char *;
    QString hex = QString("%1").arg(checksum,2,16,QLatin1Char('0'));//checksum returns an integer but in the sentence we need as a hex number.


    QString cmdToSend= "";
    cmdToSend.append("$");
    cmdToSend.append(cmdFromGUI);
    cmdToSend.append("*");
    cmdToSend.append(hex);
    cmdToSend.append(QChar(13));// <CR>
    cmdToSend.append(QChar(10));// <LF>

    //cmdToSend = "$PMTK314,-1*04\r\n";

    qDebug() << "serial is writable " << serial->isWritable();
    qDebug() <<  serial->write(cmdToSend.toLocal8Bit(),cmdToSend.size());

    serial->flush();

}

void MainWindow::enableSerialPortSettings()
{
    btnOpenPort->setStyleSheet("");
    btnOpenPort->setEnabled(true);
    cboxParity->setEnabled(true);
    cboxBaudRate ->setEnabled(true);
    cboxDataBits->setEnabled(true);
    cboxPortName->setEnabled(true);
    cboxStopBits->setEnabled(true);
    cboxFlowControl ->setEnabled(true);
}

void MainWindow::disableSerialPortSettings()
{
    btnOpenPort->setStyleSheet("background-color: rgb(0,255,0)");
    btnOpenPort->setEnabled(false);
    cboxParity->setEnabled(false);
    cboxBaudRate ->setEnabled(false);
    cboxDataBits->setEnabled(false);
    cboxPortName->setEnabled(false);
    cboxStopBits->setEnabled(false);
    cboxFlowControl ->setEnabled(false);
    QApplication::processEvents();

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
        //qDebug() << strData;
        if(strData.endsWith("\n")){
            //qDebug() << __PRETTY_FUNCTION__<<   strData;
            processData(strData);
            strData.clear();
        }
    }else{
        return;
    }
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


void MainWindow::on_actionOpen_the_Doc_triggered()
{
    QDesktopServices::openUrl(QUrl(QDir::currentPath()+"/documentation.pdf"));
}
