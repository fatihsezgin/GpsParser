#ifndef GNSSENTENCE_H
#define GNSSENTENCE_H

#include <QObject>
#include <QTime>
#include <helper.h>

class GNSSentence : public QObject
{
    Q_OBJECT
public:
    explicit GNSSentence(QObject *parent = nullptr);

    GNSSentence(QString sentenceIdentifier,
                QString fixTime,
                QString latitude,
                QString latitudeDirection,
                QString longitude,
                QString longitudeDirection,
                QString mode,
                QString noOfSatallites,
                QString HDOP,
                QString orthometricHeight,
                QString geoidalSeperation,
                QString referenceStationId);

    QString getSentenceIdentifier() const;
    void setSentenceIdentifier(const QString &value);

    QTime getFixTime() const;
    void setFixTime( QString &value);

    double getLatitude() const;
    void setLatitude(QString &value);

    QString getLatitudeDirection() const;
    void setLatitudeDirection(const QString &value);

    double getLongitude() const;
    void setLongitude( QString &longitude);

    QString getLongitudeDirection() const;
    void setLongitudeDirection(const QString &value);

    QString getMode() const;
    void setMode(const QString &value);

    int getNumberOfStallites() const;
    void setNumberOfStallites(QString &value);

    double getHDOP() const;
    void setHDOP(QString &value);

    double getOrthometricHeight() const;
    void setOrthometricHeight(QString &value);

    double getGeoidalSeparation() const;
    void setGeoidalSeparation(QString &value);

    double getAgeOfDifferentialData() const;
    void setAgeOfDifferentialData(QString &value);

    int getReferenceStationId() const;
    void setReferenceStationId(QString &value);

signals:

public slots:

private:
    QString sentenceIdentifier;
    QTime fixTime;
    double latitute;
    QString latituteDirection;
    double longitude;
    QString longitudeDirection;
    QString mode;
    int numberOfStallites;
    double HDOP;
    double orthometricHeight;
    double geoidalSeparation;
    double ageOfDifferentialData;
    int referenceStationID;


};

#endif // GNSSENTENCE_H
