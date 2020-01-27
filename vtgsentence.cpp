#include "vtgsentence.h"

VTGSentence::VTGSentence(QObject *parent) : QObject(parent)
{

}

VTGSentence::VTGSentence(QString sentenceIdentifier, QString trackDegree, QString trackReference, QString trackDegreeMagnetic, QString trackDegreeMagRef, QString speedInKnots, QString speedForKnots, QString speedInKm, QString speedForKm, QString status)
{
    setSentenceIdentifier(sentenceIdentifier);
    setTrackDegree(trackDegree);
    setTrackReference(trackReference);
    setTrackDegreeMagnetic(trackDegreeMagnetic);
    setTrackDegreeMagRef(trackDegreeMagRef);
    setSpeedInKnots(speedInKnots);
    setSpeedForKnots(speedForKnots);
    setSpeedInKm(speedInKm);
    setSpeedForKm(speedForKm);
    setStatus(status);
}

QString VTGSentence::getSentenceIdentifier() const
{
    return sentenceIdentifier;
}

void VTGSentence::setSentenceIdentifier(const QString &value)
{
    sentenceIdentifier = value;
}

double VTGSentence::getTrackDegree() const
{
    return trackDegree;
}

void VTGSentence::setTrackDegree(QString &value)
{
    trackDegree = value.toDouble();
}

QString VTGSentence::getTrackReference() const
{
    return trackReference;
}

void VTGSentence::setTrackReference(const QString &value)
{
    trackReference = value;
}

double VTGSentence::getTrackDegreeMagnetic() const
{
    return trackDegreeMagnetic;
}

void VTGSentence::setTrackDegreeMagnetic(QString &value)
{
    trackDegreeMagnetic = value.toDouble();
}

QString VTGSentence::getTrackDegreeMagRef() const
{
    return trackDegreeMagRef;
}

void VTGSentence::setTrackDegreeMagRef(const QString &value)
{
    trackDegreeMagRef = value;
}

double VTGSentence::getSpeedInKnots() const
{
    return speedInKnots;
}

void VTGSentence::setSpeedInKnots(QString &value)
{
    speedInKnots = value.toDouble();
}

QString VTGSentence::getSpeedForKnots() const
{
    return speedForKnots;
}

void VTGSentence::setSpeedForKnots(const QString &value)
{
    speedForKnots = value;
}

double VTGSentence::getSpeedInKm() const
{
    return speedInKm;
}

void VTGSentence::setSpeedInKm(QString &value)
{
    speedInKm = value.toDouble();
}

QString VTGSentence::getSpeedForKm() const
{
    return speedForKm;
}

void VTGSentence::setSpeedForKm(const QString &value)
{
    speedForKm = value;
}

QString VTGSentence::getStatus() const
{
    return status;
}

void VTGSentence::setStatus(const QString &value)
{
    status = value;
}
