#ifndef GSVSENTENCE_H
#define GSVSENTENCE_H

#include <QObject>
#include <QList>
#include <gsvdetail.h>

class GSVSentence : public QObject
{
    Q_OBJECT
public:
    explicit GSVSentence(QObject *parent = nullptr);

    GSVSentence(QString sentenceIdentifier, QString totalMessageNum, QString messageNumber, QString totalSvs,QString satallitePrnNumber, QString elevationDegree, QString azimuthDegree, QString SNR , QList<GSVDetail*> svlist);

    QString getSentenceIdentifier() ;
    void setSentenceIdentifier( QString &value);

    int getTotalMessageNum() const;
    void setTotalMessageNum(QString &value);

    int getMessageNumber() ;
    void setMessageNumber(QString &value);

    int getTotalNumberSatallites() ;
    void setTotalNumberSatallites(QString &value);

    int getSatallitePrnNumber() ;
    void setSatallitePrnNumber(QString &value);

    int getElevationDegree() ;
    void setElevationDegree(QString &value);

    double getAzimuthDegree() ;
    void setAzimuthDegree(QString &value);

    int getSNR() ;
    void setSNR(QString &value);

    QList<GSVDetail*> getSvlist() ;
    void setSvlist(  QList<GSVDetail*> &value);

    QString toString();

private:
    QString sentenceIdentifier;
    int totalMessageNum;
    int messageNumber;
    int totalNumberSatallites;
    int satallitePrnNumber;
    int elevationDegree;
    double azimuthDegree;
    int SNR;
    QList<GSVDetail*> svlist;

};

#endif // GSVSENTENCE_H
