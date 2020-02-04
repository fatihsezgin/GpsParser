#include "pmtksentence.h"
#include <QMetaEnum>
#include <mainwindow.h>
PMTKSentence::PMTKSentence(QObject *parent) : QObject(parent)
{

}

PMTKSentence::PMTKSentence(QList<QString> pmtkSentence,QWidget *parent)
{
    this->sentence =pmtkSentence;
    this->window = parent;
    process(sentence);
}


void PMTKSentence::process(QList<QString> packetData)
{

    if(packetData[0].contains("001")){//Acknowledgement about the command is processed
        process001(packetData[1],packetData[2]);
    }else if(packetData[0].contains("011")){//"
        process011(packetData[0],packetData[1]);
    }else if(packetData[0].contains("010")){
        process010(packetData[0],packetData[1]);
    }else if(packetData[0].contains("500")){ //Query the rate of position fixing activity
        process500(packetData);
    }else if(packetData[0].contains("513")){ //Query the rate of position fixing activity
        process513(packetData[0],packetData[1]);
    }else if(packetData[0].contains("514")){ //Query the rate of position fixing activity
        process514(packetData);
    }else if(packetData[0].contains("705")){ //Query the rate of position fixing activity
        process705(packetData);
    }else if(packetData[0].contains("707")){ //Query the rate of position fixing activity
        process707(packetData);
    }

}


/**
*  Acknowledge of PMTK Command
*/
void PMTKSentence::process001(QString packetName,QString status)
{
    QString packet;
    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    if(status.compare("0")== 0){
        msgBox->setWindowTitle("Error");
        msgBox->setText(" Invalid Command/Packet");
        msgBox->show();
    }else if(status.compare("1")== 0){
        packet = Helper::getPacketName(packetName.toInt());
        msgBox->setWindowTitle("Error");
        msgBox->setText(packet +" is Unsporrted");
        msgBox->show();
    }else if(status.compare("2")== 0){
        packet = Helper::getPacketName(packetName.toInt());
        msgBox->setWindowTitle("Error");
        msgBox->setText(packet + " is valid but action failed");
        msgBox->show();
    }else if(status.compare("3")== 0){
        packet = Helper::getPacketName(packetName.toInt());
        msgBox->setWindowTitle("Success");
        msgBox->setText(packet + " is delivered, and action is succeded.");
        msgBox->show();
    }else{
        return;
    }
    QCoreApplication::processEvents();
}

/**
 *  PMTK TEXT MESSAGE
*/
void PMTKSentence::process011(QString packetName,QString textMessage)
{
    QString  packet = Helper::getPacketName(packetName.mid(4).toInt());
    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle("Success");
    msgBox->setText(/*"Wanted" + cmdThatHasSend +"  "+*/ packet + " returns " + textMessage);
    msgBox->show();

}

/**
 *  PMTK SYSTEM MESSAGE
*/
void PMTKSentence::process010(QString packetName,QString systemTextMessage)
{
    QString  packet = Helper::getPacketName(packetName.mid(4).toInt());
    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle("Success");
    msgBox->setText(packet + " returns " + systemTextMessage);
    msgBox->show();

}

/**
  * PMTK rate of position fixing activity
**/
void PMTKSentence::process500(QList<QString> data){
     qDebug() << data[0].mid(4).toInt()+100;

    QString  packet = Helper::getPacketName(data[0].mid(4).toInt());
    QString givenPmtkSentence = Helper::getPacketName(data[0].mid(4).toInt()-100);

    data.removeFirst();
    QString fullSentence;
    for (QString piece : data){
        fullSentence.append(piece+ ", ");
    }
    fullSentence.prepend(packet);
    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle("Success");
    msgBox->setText("Given " + givenPmtkSentence + " returned " + fullSentence);
    msgBox->show();
}


/**
 *  PMTK SBAS Enabled
**/
void PMTKSentence::process513(QString packetName,QString textMessage)
{
    QString  packet = Helper::getPacketName(packetName.mid(4).toInt());
    QString givenPmtk = Helper::getPacketName(packetName.mid(4).toInt()-100);


    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle("Success");
    msgBox->setText(packet + " returns " + (textMessage.compare("1") ==0  ? "Enabled" : "Disabled"  ));
    msgBox->show();
}

/**
*   PMTK NMEA output frequency settings
**/
void PMTKSentence::process514(QList<QString> data)
{
    QString  packet = Helper::getPacketName(data[0].mid(4).toInt());
    QString givenPmtk = Helper::getPacketName(data[0].mid(4).toInt()-100);
    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle("Success");
    msgBox->setText("Given " + givenPmtk + " returned : " + "GLL : " +data[1]+ " "+"RMC : " +data[2]+ " "+ "VTG : " +data[3]+ " "+"GGA : " +data[4]+ " "+"GSA : " +data[5]+ " "+"GSV : " +data[6]+" "+ "ZDA : " +data[18] );
    msgBox->show();

}

/**
*   Response of firmware release informations
**/
void PMTKSentence::process705(QList<QString> data)
{
    QString  packet = Helper::getPacketName(data[0].mid(4).toInt());
    QString givenPmtk = Helper::getPacketName(data[0].mid(4).toInt()-100);
    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle("Success");
    msgBox->setText("Given "+ givenPmtk + " returned : Release Name "+ data[1] + " BuildID : " + data[2] +" ProductModel : " + data[3] );
    msgBox->show();

}

/**
 *  EPO data valid day check
**/
void PMTKSentence::process707(QList<QString> data)
{
    QString  packet = Helper::getPacketName(data[0].mid(4).toInt());
    QString givenPmtk = Helper::getPacketName(data[0].mid(4).toInt()-100);
    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowTitle("Success");
    msgBox->setText("Given "+ givenPmtk + " returned : Total number of EPO stored "+ data[1] +"\n"+ " FWN : " + data[2] +" FTOW : " + data[3]+"\n"+ " LWN : " + data[4] +" LTOW : " + data[5]+"\n"+ " FCWN : " + data[6] +" FCTOW : " + data[7]+"\n"+ " LCWN : " + data[8] +" LCTOW : " + data[9] );
    msgBox->show();

}
