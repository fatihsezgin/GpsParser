#include "ggasentence.h"
#include <QDebug>

GGASentence::GGASentence(QObject *parent) : QObject(parent)
{

}

GGASentence::GGASentence(QString sentenceIdentifier, QString fixTime, QString latitude, QString latDirection, QString longitude, QString longDirection, QString fixedQuality, QString numberSatallites, QString horizontalDilution, QString altitude, QString heightOfGeoid)
{
    setSentId(sentenceIdentifier);
    setfixTime(fixTime);
    setLatitude(latitude);
    setLatitudeDirection(latDirection);
    setLongitude(longitude);
    setLongitudeDirection(longDirection);
    setFixQuality(fixedQuality);
    setNumberStallites(numberSatallites);
    setHorizontalDilution(horizontalDilution);
    setAltitude(altitude);
    setHeightOfGeoid(heightOfGeoid);

}

QString GGASentence::getSentId() const
{
    return this->sentenceIdentifier;
}

void GGASentence::setSentId(const QString &sentenceIdentifier)
{
    this->sentenceIdentifier = sentenceIdentifier;
}

QTime GGASentence::getfixTime() const
{
    return this->fixTime;
}

void GGASentence::setfixTime(QString &fixedDate)
{
    this->fixTime = Helper::getTime(fixedDate);

}

double GGASentence::getLatitude() const
{
    return this->latitude;
}

void GGASentence::setLatitude(QString &latitude )
{
    this->latitude =latitude.toDouble();
}

double GGASentence::getLongitude() const
{
    return this->longitude;
}

void GGASentence::setLongitude( QString &longitude)
{
    this->longitude = longitude.toDouble();
}

int GGASentence::getFixQuality() const
{
    return this->fixQuality;
}

void GGASentence::setFixQuality(const QString &fixQuality)
{
    this->fixQuality = fixQuality.toInt();
}

int GGASentence::getNumberSatallites() const
{
    return this->numberSatallites;
}

void GGASentence::setNumberStallites(const QString &numberSatallites)
{
    this->numberSatallites = numberSatallites.toInt();
}

double GGASentence::getHorizontalDilution() const
{
    return this->horizontalDilution;
}

void GGASentence::setHorizontalDilution(const QString &horizontalDilution)
{
    this->horizontalDilution = horizontalDilution.toDouble();
}

double GGASentence::getAltitude() const
{
    return this->altitude;
}

void GGASentence::setAltitude(const QString &altitude)
{
    this->altitude = altitude.toDouble();
}

double GGASentence::getHeightOfGeoid() const
{
    return this->heightOfGeoid;
}

void GGASentence::setHeightOfGeoid(const QString &heightOfGeoid)
{
    this->heightOfGeoid = heightOfGeoid.toDouble();
}

QString GGASentence::toString()
{
    return (this->sentenceIdentifier +" "+this->getfixTime().toString() + " "+  QString::number(this->getLatitude()) +" " +this->getLatitudeDirection()+" " + QString::number(this->getLongitude())+" " + this->getLongitudeDirection()+" " + QString::number(this->getFixQuality())+" " + QString::number(this->getNumberSatallites())+" " + QString::number(this->getHorizontalDilution())+" " + QString::number(this->getAltitude())+" " + QString::number(this->getHeightOfGeoid())+"\n");
}

QString GGASentence::getLatitudeDirection() const
{
    return latitudeDirection;
}

void GGASentence::setLatitudeDirection(const QString &value)
{
    latitudeDirection = value;
}

QString GGASentence::getLongitudeDirection() const
{
    return longitudeDirection;
}

void GGASentence::setLongitudeDirection(const QString &value)
{
    longitudeDirection = value;
}

