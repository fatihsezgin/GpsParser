#ifndef GLLSENTENCE_H
#define GLLSENTENCE_H

#include <QObject>
#include <QTime>
#include <helper.h>

class GLLSentence : public QObject
{
    Q_OBJECT
public:
    explicit GLLSentence(QObject *parent = nullptr);

    GLLSentence(QString sentenceIdentifer, QString latitude, QString latDirection, QString longitude, QString longDirection, QString fixTime, QString status);

    QString getSentenceIdentifier() const;
    void setSentenceIdentifier(const QString &value);

    double getLatitude() const;
    void setLatitude(QString &value);

    QString getLatitudeDirection() const;
    void setLatitudeDirection(const QString &value);

    double getLongitude() const;
    void setLongitude(QString &value);

    QString getLongitudeDirection() const;
    void setLongitudeDirection(const QString &value);

    QTime getFixTime() const;
    void setFixTime( QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

signals:

public slots:

private:
    QString sentenceIdentifier;
    double latitude;
    QString latitudeDirection;
    double longitude;
    QString longitudeDirection;
    QTime fixTime;
    QString status;
};

#endif // GLLSENTENCE_H
