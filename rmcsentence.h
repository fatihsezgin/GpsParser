#ifndef RMCSENTENCE_H
#define RMCSENTENCE_H

#include <QObject>
#include <QTime>
#include <helper.h>

class RMCSentence : public QObject
{
    Q_OBJECT
public:
    explicit RMCSentence(QObject *parent = nullptr);

    RMCSentence(QString sentenceIdentigier,
                QString fixTime,
                QString status,
                QString latitude,
                QString latitudeDirection,
                QString longitude,
                QString longitudeDirection,
                QString speedOverGround,
                QString courseOverGround,
                QString date,
                QString magneticVariation,
                QString magneticVarIndicator,
                QString modeIndicator);

    QString getSentenceIdentifier() const;
    void setSentenceIdentifier(const QString &value);

    QTime getFixTime() const;
    void setFixTime(QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

    double getLatitude() const;
    void setLatitude( QString &latitude);

    QString getLatitudeDirection() const;
    void setLatitudeDirection(const QString &value);

    double getLongitude() const;
    void setLongitude( QString &longitude);

    QString getLongitudeDirection() const;
    void setLongitudeDirection(const QString &value);

    double getSpeedOverGround() const;
    void setSpeedOverGround(const QString &value);

    double getCourseOverGround() const;
    void setCourseOverGround(const QString &value);

    QDate getDate() const;
    void setDate(const QString &value);

    double getMagneticVariation() const;
    void setMagneticVariation(QString &value);

    QString getMagneticVarIndicator() const;
    void setMagneticVarIndicator(const QString &value);

    QString toString();

    QString getModeIndicator() const;
    void setModeIndicator(const QString &value);

signals:

public slots:

private:
    QString sentenceIdentifier;
    QTime fixTime;
    QString status;
    double latitude;
    QString latitudeDirection;
    double longitude;
    QString longitudeDirection;
    double speedOverGround;
    double courseOverGround;
    QDate date;
    double magneticVariation;
    QString magneticVarIndicator;
    QString modeIndicator; // in some gps devices does not contains this variable !!! (unclear)
};

#endif // RMCSENTENCE_H
