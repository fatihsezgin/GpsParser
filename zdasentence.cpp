#include "zdasentence.h"

ZDASentence::ZDASentence(QObject *parent) : QObject(parent)
{

}

ZDASentence::ZDASentence(QString sentenceIdentifier, QString utcTime, QString day, QString month, QString year, QString localZoneHours, QString localZoneMinutes)
{
    setSentenceIdentifier(sentenceIdentifier);
    setUtcTime(utcTime);
    setDate(day.toInt(),month.toInt(),year.toInt());
    setLocalZoneHours(localZoneHours.toInt());
    setLocalZoneMinutes(localZoneMinutes.toInt());
}

QString ZDASentence::toString()
{
    return QString(this->getSentenceIdentifier() + " " + this->getUtcTime().toString() + " "+ this->getDate().toString() + " "+ QString::number(this->getLocalZoneHours())+ " "+ QString::number(this->getLocalZoneMinutes())+ "\n");
}

QString ZDASentence::getSentenceIdentifier() const
{
    return sentenceIdentifier;
}

void ZDASentence::setSentenceIdentifier(const QString &value)
{
    sentenceIdentifier = value;
}

QTime ZDASentence::getUtcTime() const
{
    return utcTime;
}

void ZDASentence::setUtcTime( QString &value)
{

    this->utcTime = Helper::getTime(value);
}

QDate ZDASentence::getDate() const
{
    return date;
}

void ZDASentence::setDate(int day, int month, int year)
{
    QDate date(year,month,day);
    this->date = date;
}

int ZDASentence::getLocalZoneHours() const
{
    return localZoneHours;
}

void ZDASentence::setLocalZoneHours(int value)
{
    localZoneHours = value;
}

int ZDASentence::getLocalZoneMinutes() const
{
    return localZoneMinutes;
}

void ZDASentence::setLocalZoneMinutes(int value)
{
    localZoneMinutes = value;
}


