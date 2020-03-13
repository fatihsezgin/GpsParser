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

    dbManager.open();
    qDebug() << "create table " <<dbManager.createTable();

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

    scrollArea = ui->scrollArea;
    sAreaContent = ui->sAreaContent;
    detailVertical = ui->detailVertical;


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
    //qDebug() << "dataa"<< data;
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

    int totalMessage =0 ;
    int currentMessage = 0;
    QList<QString> GSVList ;

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
                        //qDebug() << s.toString();
                        qDebug() << "insertGGA" << dbManager.insertGGA(&s);
                        gga = true;
                        plainText->insertPlainText(s.toString());
                    }
                    else if(parts[0].contains("RMC")){
                        RMCSentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10],parts[11],parts[12]);
                        //qDebug() << s.toString();
                        dbManager.insertRMC(&s);
                        rmc = true;
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("GLL")){
                        GLLSentence s (parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6]);
                        //qDebug() << s.toString();
                        qDebug() << "insertGLL"<<dbManager.insertGLL(&s);
                        gll =true;
                        plainText->insertPlainText(s.toString());
                    }else if (parts[0].contains("VTG")){
                        VTGSentence s (parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9]);
                        //qDebug() << s.toString();
                        qDebug() << "insertVTG" <<dbManager.insertVTG(&s);
                        vtg = true;
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("ZDA")){
                        ZDASentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6]);
                        //qDebug() << s.toString();
                        qDebug() <<  "insertZDA" << dbManager.insertZDA(&s);
                        zda = true;
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("GNS")){
                        GNSSentence s(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5],parts[6],parts[7],parts[8],parts[9],parts[10],parts[11],parts[12]);
                        //qDebug() << s.toString();
                        qDebug() << parts;
                        qDebug() << "insertGNS" <<dbManager.insertGNS(&s);
                        gns = true;
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("HDT")){
                        HDTSentence s(parts[0],parts[1],parts[2]);
                        qDebug() << s.getSentenceIdentifier() << s.getDegree() << s.getRelative();
                        qDebug() << "insertHDT" <<dbManager.insertHDT(&s);
                        hdt = true;
                        plainText->insertPlainText(s.toString());
                    }else if(parts[0].contains("GSA")){
                        QList<int> list;
                        for(int i = 3 ; i <= 14 ; i++){
                            list.append(parts[i].toInt());
                        }
                        GSASentence s (parts[0],parts[1],parts[2],list,parts[15],parts[16],parts[17]);
                        plainText->insertPlainText(s.toString());
                        dbManager.insertGSA(&s);
                        gsa =true;
                        qDebug()  << s.toString();
                    }else if(parts[0].contains("GSV")){
                        gsv = true;
                         totalMessage = parts[1].toInt();
                         currentMessage = parts[2].toInt();

                         if ( totalMessage >= currentMessage){
                             QList<GSVDetail*> list;
                             GSVDetail *detail;
                             if(parts.size() < 20){
                                 qDebug() << "message is corrupted.";
                             }else{
                                 for(int i = 4 ; i < 20 ; i+=4 ){
                                     detail = new GSVDetail(parts[i],parts[i+1],parts[i+2],parts[i+3]);
                                     list.append(detail);
                                 }
                                 GSVSentence s(parts[0],parts[1],parts[2],parts[3],list);
                                 dbManager.insertGSV(&s);
                                 plainText->insertPlainText(s.toString());
                             }
                             if(totalMessage == currentMessage){
                                 qDebug() << "insertTotal"<< dbManager.insertTotalGSV(totalMessage);
                             }
                         }

                    }else if(parts[0].contains("PMTK")){
                            PMTKSentence s (parts,this);
                    }
                    dbManager.commit();
                }
            }else{
                return;
            }
        }
    }

    dbManager.prepareQuery(gga,rmc,gll,gns,gsa,gsv,hdt,vtg,zda);
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

    int checksum = Helper::calculateCheckSum(cmdFromGUI.toUtf8().data()); // for calculating the checksum checksum is converted into char *;
    QString hex = QString("%1").arg(checksum,2,16,QLatin1Char('0'));//checksum returns an integer but in the sentence we need as a hex number.


    QString cmdToSend= "";
    cmdToSend.append("$"+cmdFromGUI+"*"+hex);
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

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
        QSqlQueryModel *model = new QSqlQueryModel();

        QSqlQuery *query = new QSqlQuery(dbManager.getDb());

        query->prepare("select * from GPSDatum");

        query->exec();
        model->setQuery(*query);
        ui->tableView->setModel(model);
    }
}



/**
 *  @todo seçilen item'ın datalarına göre queryler yazılacak ve query boş dönmediyse her sentence ait bir groupbox oluşturulup @gui detailVertical
 * adlı vertical layout a append edilecek
 *
 * @todo
      rmc de bazılarında 12 part var bazılarında 11 gps'i takarak dene
*/

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    clearDetailLayout();

    QItemSelectionModel *select = ui->tableView->selectionModel();
    /*Starts with 1 because the first column in the table is DATAID **/
    for(int i= 1 ; i <= 9 ; i++ ){
        QString headerName = ui->tableView->model()->headerData(i,Qt::Horizontal).toString().mid(0,3);
        QString id = select->selectedRows(i).value(0).data().toString();
        qDebug() << "header name : " <<  headerName << "   id :" << id;
        if(!id.isNull()){
            QList<QString> list = dbManager.getSentenceInfo(headerName,id);
            createGroupBox(headerName,list);
        }
    }
}

void MainWindow::clearDetailLayout()
{

    QLayoutItem *child;
    while((child=ui->detailVertical->takeAt(0))!= nullptr){
        delete child->widget();
    }
}

void MainWindow::createGroupBox(QString title, QList<QString> list)
{

    //QVBoxLayout *vbox = new QVBoxLayout();
    sAreaContent->setLayout(detailVertical);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable( true );
    scrollArea->setWidget( sAreaContent);

    QGroupBox *groupBox = new QGroupBox();
    groupBox->setTitle(title);

    QFormLayout *formLayout = new QFormLayout();

    if(title.compare("GGA")==0){
        formLayout->addRow(new QLabel("FixTime"), new QLabel(list[1]));
        formLayout->addRow(new QLabel("Latitude"), new QLabel(list[2] + " " + list[3]));
        formLayout->addRow(new QLabel("Longitude"), new QLabel(list[4] + " " + list[5]));
        formLayout->addRow(new QLabel("Fixed Quality"), new QLabel(list[6]));
        formLayout->addRow(new QLabel("Satallite Number"), new QLabel(list[7]));
        formLayout->addRow(new QLabel("HDOP"), new QLabel(list[8]));
        formLayout->addRow(new QLabel("Altitude"), new QLabel(list[9]));
        formLayout->addRow(new QLabel("Height of Geoid"), new QLabel(list[10]));
    }else if(title.compare("RMC") == 0){
        formLayout->addRow(new QLabel("FixTime"), new QLabel(list[1]));
        formLayout->addRow(new QLabel("Status"), new QLabel(list[2]));
        formLayout->addRow(new QLabel("Latitude"), new QLabel(list[3] + " " + list[4]));
        formLayout->addRow(new QLabel("Longitude"), new QLabel(list[5] + " " + list[6]));
        formLayout->addRow(new QLabel("Speed Over Ground"), new QLabel(list[7]));
        formLayout->addRow(new QLabel("Course Over Ground"), new QLabel(list[8]));
        formLayout->addRow(new QLabel("Date"), new QLabel(list[9]));
        formLayout->addRow(new QLabel("Magnetic Variation"), new QLabel(list[10] +" " + list[11]));
    }else if(title.compare("GLL") ==0){
        formLayout->addRow(new QLabel("Latitude"), new QLabel(list[1] + " " + list[2]));
        formLayout->addRow(new QLabel("Longitude"), new QLabel(list[3] + " " + list[4]));
        formLayout->addRow(new QLabel("FixTime"), new QLabel(list[5]));
        formLayout->addRow(new QLabel("Status"), new QLabel(list[6]));
    }else if(title.compare("VTG") ==0){
        formLayout->addRow(new QLabel("Track / Degress"), new QLabel(list[1] + " " + list[2]));
        formLayout->addRow(new QLabel("Track / Magnetic"), new QLabel(list[3] + " " + "M"));
        formLayout->addRow(new QLabel("Speed "), new QLabel(list[5] + " " + "N"));
        formLayout->addRow(new QLabel("Speed"), new QLabel(list[6] + " "+ "KM"));
        formLayout->addRow(new QLabel("Status"), new QLabel(list[7]));
    }else if(title.compare("ZDA") ==0){
        formLayout->addRow(new QLabel("UTC"), new QLabel(list[1]));
        formLayout->addRow(new QLabel("Date"), new QLabel(list[2]));
        formLayout->addRow(new QLabel("Local Zone Hours "), new QLabel(list[3]));
        formLayout->addRow(new QLabel("Local Zone Minutes "), new QLabel(list[4]));
    }else if(title.compare("GNS") ==0){
        formLayout->addRow(new QLabel("FixTime"), new QLabel(list[1]));
        formLayout->addRow(new QLabel("Latitude"), new QLabel(list[2] + " " + list[3]));
        formLayout->addRow(new QLabel("Longitude"), new QLabel(list[4] + " " + list[5]));
        formLayout->addRow(new QLabel("Status"), new QLabel(list[6]));
        formLayout->addRow(new QLabel("Number of Satallites"), new QLabel(list[7]));
        formLayout->addRow(new QLabel("HDOP"), new QLabel(list[8]));
        formLayout->addRow(new QLabel("Ortometric Height"), new QLabel(list[9]));
        formLayout->addRow(new QLabel("Geoidal Separation"), new QLabel(list[10]));
        formLayout->addRow(new QLabel("Age of Differential Data"), new QLabel(list[11]));
        formLayout->addRow(new QLabel("Reference Station ID"), new QLabel(list[12]));
    }else if(title.compare("HDT") ==0){
        formLayout->addRow(new QLabel("Heading in  Degrees"), new QLabel(list[1]));
        formLayout->addRow(new QLabel("Relative"), new QLabel(list[2]));
    }else if(title.compare("GSA") ==0){
        formLayout->addRow(new QLabel("Mode"), new QLabel(list[1]));
        formLayout->addRow(new QLabel("Fix"), new QLabel(list[2]));
        formLayout->addRow(new QLabel("PDOP"), new QLabel(list[3]));
        formLayout->addRow(new QLabel("HDOP"), new QLabel(list[4]));
        formLayout->addRow(new QLabel("VDOP"), new QLabel(list[5]));
        for(int i = 8 ; i <= 19 ; i++)
            formLayout->addRow(new QLabel("Satallite "+QString::number(i-7)), new QLabel(list[i]));
    }else if(title.compare("GSV") ==0){
        int j =1;
        for(int i = 1; i < list.size();i+=5){
            formLayout->addRow(new QLabel("Satallite "+QString::number(j++)));
            formLayout->addRow(new QLabel("PRNNO "), new QLabel(list[i]));
            formLayout->addRow(new QLabel("Elevation "), new QLabel(list[i+1]));
            formLayout->addRow(new QLabel("Azimuth "), new QLabel(list[i+2]));
            formLayout->addRow(new QLabel("SNR "), new QLabel(list[i+3]));

        }
    }

    groupBox->setLayout(formLayout);
    detailVertical->addWidget(groupBox);
}


