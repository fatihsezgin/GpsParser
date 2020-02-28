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

    GSVSentence(QString sentenceIdentifier, QString totalMessageNum, QString messageNumber, QString totalSvs,QList<GSVDetail*> svlist);

    GSVSentence(QList<QString> satalliteList);

    QString getSentenceIdentifier() ;
    void setSentenceIdentifier( QString &value);

    int getTotalMessageNum() const;
    void setTotalMessageNum(QString &value);

    int getMessageNumber() ;
    void setMessageNumber(QString &value);

    int getTotalNumberSatallites() ;
    void setTotalNumberSatallites(QString &value);

    QList<GSVDetail*> getSvlist() ;
    void setSvlist(  QList<GSVDetail*> &value);

    QString toString();

private:
    QString sentenceIdentifier;
    int totalMessageNum;
    int messageNumber;
    int totalNumberSatallites;
    QList<GSVDetail*> svlist;

};

#endif // GSVSENTENCE_H
