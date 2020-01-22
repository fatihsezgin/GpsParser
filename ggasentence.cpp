#include "ggasentence.h"
#include <QDebug>

GGASentence::GGASentence(QObject *parent) : QObject(parent)
{

}

GGASentence::GGASentence(QString sentenceIdentifier, QString fixedDate, QString latitude, QString latDirection, QString longitude, QString longDirection, QString fixedQuality, QString numberSatallites, QString horizontalDilution, QString altitude, QString heightOfGeoid)
{
    setSentId(sentenceIdentifier);
    setFixedDate(fixedDate);
    setLatitude(latitude,latDirection);
    setLongitude(longitude,longDirection);
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

QString GGASentence::getFixedDate() const
{
    return this->fixDate;
}

void GGASentence::setFixedDate(const QString &fixedDate)
{
    //qDebug() << fixedDate;
    QTime time = QTime::fromString(fixedDate,"HHmmss.z");
    this->fixDate = time.toString("HHmmss");
    //qDebug() << time.toString("HHmmss");

}

QString GGASentence::getLatitude() const
{
    return this->latitude;
}

void GGASentence::setLatitude(QString &latitude ,  QString &latDirection)
{
    latitude.append(" " + latDirection);
    this->latitude = latitude;
}

QString GGASentence::getLongitude() const
{
    return this->longitude;
}

void GGASentence::setLongitude( QString &longitude,  QString &longDirection)
{
    longitude.append(" "+ longDirection);
    this->longitude = longitude;
}

QString GGASentence::getFixQuality() const
{
    return this->fixQuality;
}

void GGASentence::setFixQuality(const QString &fixQuality)
{
    this->fixQuality = fixQuality;
}

QString GGASentence::getNumberSatallites() const
{
    return this->numberSatallites;
}

void GGASentence::setNumberStallites(const QString &numberSatallites)
{
    this->numberSatallites = numberSatallites;
}

QString GGASentence::getHorizontalDilution() const
{
    return this->horizontalDilution;
}

void GGASentence::setHorizontalDilution(const QString &horizontalDilution)
{
    this->horizontalDilution = horizontalDilution;
}

QString GGASentence::getAltitude() const
{
    return this->altitude;
}

void GGASentence::setAltitude(const QString &altitude)
{
    this->altitude = altitude;
}

QString GGASentence::getHeightOfGeoid() const
{
    return this->heightOfGeoid;
}

void GGASentence::setHeightOfGeoid(const QString &heightOfGeoid)
{
    this->heightOfGeoid = heightOfGeoid;
}

