#include "gsasentence.h"

GSASentence::GSASentence(QObject *parent) : QObject(parent)
{

}

GSASentence::GSASentence(QString sentenceIdentifier, QString mode, QString fix, QList<int> ids, QString PDOP, QString HDOP, QString VDOP)
{
    setSentenceIdentifier(sentenceIdentifier);
    setMode(mode);
    setFix(fix);
    setIds(ids);
    setPDOP(PDOP);
    setHDOP(HDOP);
    setVDOP(VDOP);
}

QString GSASentence::toString()
{
    QString idListInString;
    for(int a : this->getIds()){
        idListInString.append(QString::number(a)+ " ");
    }
    qDebug() << idListInString;
    return QString(this->getSentenceIdentifier() + " " + this->getMode() + " " + QString::number(this->getFix()) + " "+  idListInString+ "  " + QString::number(this->getPDOP()) +" " + QString::number(this->getHDOP()) + " " + QString::number(this->getVDOP())+ "\n" );
}

QString GSASentence::getSentenceIdentifier() const
{
    return sentenceIdentifier;
}

void GSASentence::setSentenceIdentifier(const QString &value)
{
    sentenceIdentifier = value;
}

QString GSASentence::getMode() const
{
    return mode;
}

void GSASentence::setMode(const QString &value)
{
    mode = value;
}

int GSASentence::getFix() const
{
    return fix;
}

void GSASentence::setFix(QString &value)
{
    fix = value.toInt();
}

QList<int> GSASentence::getIds() const
{
    return ids;
}

void GSASentence::setIds(const QList<int> &value)
{
    ids = value;
}

double GSASentence::getPDOP() const
{
    return PDOP;
}

void GSASentence::setPDOP(QString &value)
{
    PDOP = value.toDouble();
}

double GSASentence::getHDOP() const
{
    return HDOP;
}

void GSASentence::setHDOP(QString &value)
{
    HDOP = value.toDouble();
}

double GSASentence::getVDOP() const
{
    return VDOP;
}

void GSASentence::setVDOP(QString &value)
{
    VDOP = value.toDouble();
}


