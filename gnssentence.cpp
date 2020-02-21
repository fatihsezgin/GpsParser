#include "gnssentence.h"

GNSSentence::GNSSentence(QObject *parent) : QObject(parent)
{

}

GNSSentence::GNSSentence(QString sentenceIdentifier, QString fixTime, QString latitude, QString latitudeDirection, QString longitude, QString longitudeDirection, QString mode, QString noOfSatallites, QString HDOP, QString orthometricHeight, QString geoidalSeperation,QString ageofDifferentialData, QString referenceStationId)
{
    setSentenceIdentifier(sentenceIdentifier);
    setFixTime(fixTime);
    setLatitude(latitude);
    setLatitudeDirection(latitudeDirection);
    setLongitude(longitude);
    setLongitudeDirection(longitudeDirection);
    setMode(mode);
    setNumberOfStallites(noOfSatallites);
    setHDOP(HDOP);
    setOrthometricHeight(orthometricHeight);
    setGeoidalSeparation(geoidalSeperation);
    setAgeOfDifferentialData(ageofDifferentialData);
    setReferenceStationId(referenceStationId);

}


QString GNSSentence::toString()
{
    return QString(this->getSentenceIdentifier() + " " + this->getFixTime().toString() + " " + QString::number(this->getLatitude()) + " " + this->getLatitudeDirection() + " " + QString::number(this->getLongitude())+ " " + this->getLongitudeDirection() + " " + this->getMode() + " " + QString::number(this->getNumberOfStallites()) + " " +QString::number( this->getHDOP())+ " " +QString::number(this->getOrthometricHeight()) + " " +QString::number(this->getGeoidalSeparation())+ " " +QString::number(this->getAgeOfDifferentialData())+ " " +QString::number(this->getReferenceStationId())+"\n") ;
}


QString GNSSentence::getSentenceIdentifier() const
{
    return sentenceIdentifier;
}

void GNSSentence::setSentenceIdentifier(const QString &value)
{
    sentenceIdentifier = value;
}

QTime GNSSentence::getFixTime() const
{
    return fixTime;
}

void GNSSentence::setFixTime(QString &value)
{

    this->fixTime = Helper::getTime(value);
}

double GNSSentence::getLatitude() const
{
    return latitute;
}

void GNSSentence::setLatitude(QString  &value)
{
    latitute = value.toDouble();
}

QString GNSSentence::getLatitudeDirection() const
{
    return latituteDirection;
}

void GNSSentence::setLatitudeDirection(const QString &value)
{
    latituteDirection = value;
}

double GNSSentence::getLongitude() const
{
    return longitude;
}

void GNSSentence::setLongitude(QString &value)
{
    longitude = value.toDouble();
}

QString GNSSentence::getLongitudeDirection() const
{
    return longitudeDirection;
}

void GNSSentence::setLongitudeDirection(const QString &value)
{
    longitudeDirection = value;
}

QString GNSSentence::getMode() const
{
    return mode;
}

void GNSSentence::setMode(const QString &value)
{
    mode = value;
}

int GNSSentence::getNumberOfStallites() const
{
    return numberOfStallites;
}

void GNSSentence::setNumberOfStallites(QString &value)
{
    numberOfStallites = value.toInt();
}

double GNSSentence::getHDOP() const
{
    return HDOP;
}

void GNSSentence::setHDOP(QString &value)
{
    HDOP = value.toInt();
}

double GNSSentence::getOrthometricHeight() const
{
    return orthometricHeight;
}

void GNSSentence::setOrthometricHeight(QString &value)
{
    orthometricHeight = value.toDouble();
}

double GNSSentence::getGeoidalSeparation() const
{
    return geoidalSeparation;
}

void GNSSentence::setGeoidalSeparation(QString &value)
{
    geoidalSeparation = value.toDouble();
}

double GNSSentence::getAgeOfDifferentialData() const
{
    return ageOfDifferentialData;
}

void GNSSentence::setAgeOfDifferentialData(QString &value)
{
    ageOfDifferentialData = value.toDouble();
}

int GNSSentence::getReferenceStationId() const
{
    return referenceStationID;
}

void GNSSentence::setReferenceStationId(QString &value)
{
    referenceStationID = value.toInt();
}

