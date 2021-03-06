#include "gllsentence.h"

GLLSentence::GLLSentence(QObject *parent) : QObject(parent)
{

}

GLLSentence::GLLSentence(QString sentenceIdentifer, QString latitude, QString latDirection, QString longitude, QString longDirection, QString fixTime, QString status)
{
    setSentenceIdentifier(sentenceIdentifer);
    setLatitude(latitude);
    setLatitudeDirection(latDirection);
    setLongitude(longitude);
    setLongitudeDirection(longDirection);
    setFixTime(fixTime);
    setStatus(status);
}

QString GLLSentence::toString()
{
    return QString(this->getSentenceIdentifier()+ " " + QString::number(this->getLatitude()) + " "+ this->getLatitudeDirection() + " "+ QString::number(this->getLongitude()) + " "+this->getLongitudeDirection() + " "+ this->fixTime.toString() + " "+ this->getStatus()+ "\n");
}

QString GLLSentence::getSentenceIdentifier() const
{
    return sentenceIdentifier;
}

void GLLSentence::setSentenceIdentifier(const QString &value)
{
    sentenceIdentifier = value;
}

double GLLSentence::getLatitude() const
{

    return latitude;
}

void GLLSentence::setLatitude(QString &value)
{
    latitude = value.toDouble();
}

QString GLLSentence::getLatitudeDirection() const
{
    return latitudeDirection;
}

void GLLSentence::setLatitudeDirection(const QString &value)
{
    latitudeDirection = value;
}

double GLLSentence::getLongitude() const
{
    return longitude;
}

void GLLSentence::setLongitude(QString &value)
{
    longitude = value.toDouble();
}

QString GLLSentence::getLongitudeDirection() const
{
    return longitudeDirection;
}

void GLLSentence::setLongitudeDirection(const QString &value)
{
    longitudeDirection = value;
}

QTime GLLSentence::getFixTime() const
{
    return fixTime;
}

void GLLSentence::setFixTime( QString &value)
{
    this->fixTime = Helper::getTime(value);
}

QString GLLSentence::getStatus() const
{
    return status;
}

void GLLSentence::setStatus(const QString &value)
{
    status = value;
}


