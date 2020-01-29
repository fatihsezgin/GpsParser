#include "gsvsentence.h"

GSVSentence::GSVSentence(QObject *parent) : QObject(parent)
{

}

GSVSentence::GSVSentence(QString sentenceIdentifier, QString totalMessageNum, QString messageNumber, QString totalSvs, QString satallitePrnNumber, QString elevationDegree, QString azimuthDegree, QString SNR, QList<GSVDetail*> svlist)
{
    setSentenceIdentifier(sentenceIdentifier);
    setTotalMessageNum(totalMessageNum);
    setMessageNumber(messageNumber);
    setTotalNumberSatallites(totalSvs);
    setSatallitePrnNumber(satallitePrnNumber);
    setElevationDegree(elevationDegree);
    setAzimuthDegree(azimuthDegree);
    setSNR(SNR);
    setSvlist(svlist);
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

int GSVSentence::getSatallitePrnNumber()
{
    return satallitePrnNumber;
}

void GSVSentence::setSatallitePrnNumber(QString &value)
{
    satallitePrnNumber = value.toInt();
}

int GSVSentence::getElevationDegree()
{
    return elevationDegree;
}

void GSVSentence::setElevationDegree(QString &value)
{
    elevationDegree = value.toInt();
}

double GSVSentence::getAzimuthDegree()
{
    return azimuthDegree;
}

void GSVSentence::setAzimuthDegree(QString &value)
{
    azimuthDegree = value.toDouble();
}

int GSVSentence::getSNR()
{
    return SNR;
}

void GSVSentence::setSNR(QString &value)
{
    SNR = value.toInt();
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
