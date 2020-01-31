#include "hdtsentence.h"

HDTSentence::HDTSentence(QObject *parent) : QObject(parent)
{

}

HDTSentence::HDTSentence(QString sentenceIdentifier, QString degree, QString relative)
{
    setSentenceIdentifier(sentenceIdentifier);
    setDegree(degree);
    setRelative(relative);
}

QString HDTSentence::getSentenceIdentifier() const
{
    return sentenceIdentifier;
}

void HDTSentence::setSentenceIdentifier(const QString &value)
{
    sentenceIdentifier = value;
}

double HDTSentence::getDegree() const
{
    return degree;
}

void HDTSentence::setDegree(QString &value)
{
    degree = value.toDouble();
}

QString HDTSentence::getRelative() const
{
    return relative;
}

void HDTSentence::setRelative(const QString &value)
{
    relative = value;
}

QString HDTSentence::toString()
{
    return QString(this->getSentenceIdentifier() + " " + QString::number(this->getDegree()) + " " + this->getRelative()+ "\n");
}
