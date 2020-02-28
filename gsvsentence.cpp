#include "gsvsentence.h"

GSVSentence::GSVSentence(QObject *parent) : QObject(parent)
{

}

GSVSentence::GSVSentence(QString sentenceIdentifier, QString totalMessageNum, QString messageNumber, QString totalSvs,QList<GSVDetail*> svlist)
{
    setSentenceIdentifier(sentenceIdentifier);
    setTotalMessageNum(totalMessageNum);
    setMessageNumber(messageNumber);
    setTotalNumberSatallites(totalSvs);
    setSvlist(svlist);
}

GSVSentence::GSVSentence(QList<QString> satalliteList)
{

}


QString GSVSentence::toString()
{
    QString satalliteListInString;
    for(int i = 0 ; i< this->getSvlist().size(); i++){
           satalliteListInString.append(QString::number(this->getSvlist().at(i)->getSvPrnNumber()) + " " +QString::number(this->getSvlist().at(i)->getElevationDegree()) + " " + QString::number(this->getSvlist().at(i)->getAzimuthDegree()) + " "+QString::number(this->getSvlist().at(i)->getSNR()) + " ");
    }

    return QString(this->getSentenceIdentifier() + " " + QString::number(this->getTotalMessageNum()) + " " + QString::number(this->getMessageNumber()) + "  " +  satalliteListInString + "\n");

}

QString GSVSentence::getSentenceIdentifier()
{
    return sentenceIdentifier;
}

void GSVSentence::setSentenceIdentifier( QString &value)
{
    sentenceIdentifier = value;
}

int GSVSentence::getMessageNumber()
{
    return messageNumber;
}

void GSVSentence::setMessageNumber(QString &value)
{
    messageNumber = value.toInt();
}

int GSVSentence::getTotalNumberSatallites()
{
    return totalNumberSatallites;
}

void GSVSentence::setTotalNumberSatallites(QString &value)
{
    totalNumberSatallites = value.toInt();
}


QList<GSVDetail*> GSVSentence::getSvlist()
{
    return svlist;
}

void GSVSentence::setSvlist( QList<GSVDetail*> &list)
{
    svlist = list;
}


int GSVSentence::getTotalMessageNum() const
{
    return totalMessageNum;
}

void GSVSentence::setTotalMessageNum(QString &value)
{
    totalMessageNum = value.toInt();
}
