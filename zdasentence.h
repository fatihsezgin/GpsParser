#ifndef ZDASENTENCE_H
#define ZDASENTENCE_H

#include <QObject>
#include <QTime>
#include <QDate>
class ZDASentence : public QObject
{
    Q_OBJECT
public:
    explicit ZDASentence(QObject *parent = nullptr);

    ZDASentence(QString sentenceIdentifier, QString utcTime,QString day, QString month, QString year, QString localZoneHours, QString localZoneMinutes);

    QString getSentenceIdentifier() const;
    void setSentenceIdentifier(const QString &value);

    QTime getUtcTime() const;
    void setUtcTime(const QString &value);

    QDate getDate() const;
    void setDate(int day, int month, int year);

    int getLocalZoneHours() const;
    void setLocalZoneHours(int value);

    int getLocalZoneMinutes() const;
    void setLocalZoneMinutes(int value);

signals:

public slots:

private:
    QString sentenceIdentifier;
    QTime utcTime;
    QDate date;
    int localZoneHours;
    int localZoneMinutes;
};

#endif // ZDASENTENCE_H
