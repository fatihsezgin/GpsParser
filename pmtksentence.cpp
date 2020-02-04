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


void PMTKSentence::process(QList<QString> packetType)
{
    QMessageBox* msgBox = new QMessageBox(this->window);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons(QMessageBox::Ok);
    if(packetType[0].contains("001")){
        QString status = packetType[2];
        if(status.compare("0")== 0){
            msgBox->setWindowTitle("Error");
            msgBox->setText("Invalid Command/Packet");
            msgBox->show();
        }else if(status.compare("1")== 0){
            QString packet = QMetaEnum::fromType<PMTKSentence::PacketType>().valueToKey(packetType[1].toInt());
            msgBox->setWindowTitle("Error");
            msgBox->setText(packet +" is Unsporrted");
            msgBox->show();
        }else if(status.compare("2")== 0){
            QString packet = QMetaEnum::fromType<PMTKSentence::PacketType>().valueToKey(packetType[1].toInt());
            msgBox->setWindowTitle("Error");
            msgBox->setText(packet + "is valid but action failed");
            msgBox->show();
        }else if(status.compare("3")== 0){
            QString packet = QMetaEnum::fromType<PMTKSentence::PacketType>().valueToKey(packetType[1].toInt());
            msgBox->setWindowTitle("Success");
            msgBox->setText(packet + "is delivered, and action is succeded.");
            msgBox->show();
        }else{
            return;
        }
        QCoreApplication::processEvents();
    }
}
