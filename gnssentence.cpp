#include "gnssentence.h"

GNSSentence::GNSSentence(QObject *parent) : QObject(parent)
{

}

GNSSentence::GNSSentence(QString sentenceIdentifier, QString fixTime, QString latitude, QString latitudeDirection, QString longitude, QString longitudeDirection, QString mode, QString noOfSatallites, QString HDOP, QString orthometricHeight, QString geoidalSeperation, QString referenceStationId)
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
    setReferenceStationId(referenceStationId);

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

void GNSSentence::setFixTime(const QString &value)
{
    QTime time = QTime::fromString(value, "HHmmss.z");
    fixTime = time;
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
