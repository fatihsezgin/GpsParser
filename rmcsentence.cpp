#include "rmcsentence.h"

RMCSentence::RMCSentence(QObject *parent) : QObject(parent)
{

}

RMCSentence::RMCSentence(QString sentenceIdentifier,QString fixDate,QString status,QString latitude,QString latitudeDirection,QString longitude,QString longitudeDirection,QString speedOverGround,QString courseOverGround,QString date,QString magneticVariation, QString magneticVarIndicator, QString modeIndicator){
    setSentenceIdentifier(sentenceIdentifier);
    setFixDate(fixDate);
    setStatus(status);
    setLatitude(latitude);
    setLatitudeDirection(latitudeDirection);
    setLongitude(longitude);
    setLongitudeDirection(longitudeDirection);
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

QTime RMCSentence::getFixDate() const
{
    return this->fixDate;
}

void RMCSentence::setFixDate(const QString &value)
{
    QTime time = QTime::fromString(value,"HHmmss.z");
    this->fixDate = time;
}

QString RMCSentence::getStatus() const
{
    return status;
}

void RMCSentence::setStatus(const QString &value)
{
    status = value;
}

double RMCSentence::getLatitude() const
{
    return latitude;
}

void RMCSentence::setLatitude( QString &latitude )
{
    this->latitude = latitude.toDouble();
}

double RMCSentence::getLongitude() const
{
    return longitude;
}

void RMCSentence::setLongitude(QString &longitude)
{
    this->longitude = longitude.toDouble();
}

double RMCSentence::getSpeedOverGround() const
{
    return speedOverGround;
}

void RMCSentence::setSpeedOverGround(const QString &value)
{
    speedOverGround = value.toDouble();
}

double RMCSentence::getCourseOverGround() const
{
    return courseOverGround;
}

void RMCSentence::setCourseOverGround(const QString &value)
{
    courseOverGround = value.toDouble();
}

QDate RMCSentence::getDate() const
{
    return date;
}

void RMCSentence::setDate(const QString &value)
{
    QDate newDate = QDate::fromString(value,"ddMMyy");
    date = newDate;
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

QString RMCSentence::getLatitudeDirection() const
{
    return latitudeDirection;
}

void RMCSentence::setLatitudeDirection(const QString &value)
{
    latitudeDirection = value;
}

QString RMCSentence::getLongitudeDirection() const
{
    return longitudeDirection;
}

void RMCSentence::setLongitudeDirection(const QString &value)
{
    longitudeDirection = value;
}


