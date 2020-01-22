#include "rmcsentence.h"

RMCSentence::RMCSentence(QObject *parent) : QObject(parent)
{

}

RMCSentence::RMCSentence(QString sentenceIdentifier,QString fixDate,QString status,QString latitude,QString latitudeDirection,QString longitude,QString longitudeDirection,QString speedOverGround,QString courseOverGround,QString date,QString magneticVariation, QString magneticVarIndicator, QString modeIndicator){
    setSentenceIdentifier(sentenceIdentifier);
    setFixDate(fixDate);
    setStatus(status);
    setLatitude(latitude,latitudeDirection);
    setLongitude(longitude,longitudeDirection);
    setSpeedOverGround(speedOverGround);
    setCourseOverGround(courseOverGround);
    setDate(date);
    setMagneticVariation(magneticVariation,magneticVarIndicator);
    setModeIndicator(modeIndicator);
}

QString RMCSentence::getSentenceIdentifier() const
{
    return this->sentenceIdentifier;
}

void RMCSentence::setSentenceIdentifier(const QString &value)
{
    sentenceIdentifier = value;
}

QString RMCSentence::getFixDate() const
{
    return this->fixDate;
}

void RMCSentence::setFixDate(const QString &value)
{
    QTime time = QTime::fromString(value,"HHmmss.z");
    this->fixDate = time.toString("HHmmss");
}

QString RMCSentence::getStatus() const
{
    return status;
}

void RMCSentence::setStatus(const QString &value)
{
    status = value;
}

QString RMCSentence::getLatitude() const
{
    return latitude;
}

void RMCSentence::setLatitude( QString &latitude , QString &latitudeDirection )
{
    latitude.append(" " + latitudeDirection);
    this->latitude = latitude;
}



QString RMCSentence::getLongitude() const
{
    return longitude;
}

void RMCSentence::setLongitude(QString &longitude,QString &longitudeDirection)
{
    longitude.append(" "+ longitudeDirection);
    this->longitude = longitude;
}

QString RMCSentence::getSpeedOverGround() const
{
    return speedOverGround;
}

void RMCSentence::setSpeedOverGround(const QString &value)
{
    speedOverGround = value;
}

QString RMCSentence::getCourseOverGround() const
{
    return courseOverGround;
}

void RMCSentence::setCourseOverGround(const QString &value)
{
    courseOverGround = value;
}

QString RMCSentence::getDate() const
{
    return date;
}

void RMCSentence::setDate(const QString &value)
{
    date = value;
}

QString RMCSentence::getMagneticVariation() const
{
    return magneticVariation;
}

void RMCSentence::setMagneticVariation(QString &magneticVariation, QString &magneticVarIndicator)
{
    if(!magneticVariation.isNull() && !magneticVarIndicator.isNull() ){
            magneticVariation.append(" " + magneticVarIndicator);
            this->magneticVariation = magneticVariation;
    }
}

QString RMCSentence::getModeIndicator() const
{
    return modeIndicator;
}

void RMCSentence::setModeIndicator(const QString &value)
{
    modeIndicator = value;
}


