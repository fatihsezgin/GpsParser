#ifndef RMCSENTENCE_H
#define RMCSENTENCE_H

#include <QObject>
#include <QTime>

class RMCSentence : public QObject
{
    Q_OBJECT
public:
    explicit RMCSentence(QObject *parent = nullptr);

    RMCSentence(QString sentenceIdentigier,
                QString fixDate,
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

    QString getFixDate() const;
    void setFixDate(const QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

    QString getLatitude() const;
    void setLatitude( QString &latitude , QString &latitudeDirection );

    QString getLongitude() const;
    void setLongitude( QString &longitude,QString &longitudeDirection );

    QString getSpeedOverGround() const;
    void setSpeedOverGround(const QString &value);

    QString getCourseOverGround() const;
    void setCourseOverGround(const QString &value);

    QString getDate() const;
    void setDate(const QString &value);

    QString getMagneticVariation() const;
    void setMagneticVariation( QString &magneticVariation, QString &magneticVarIndicator);

    QString getModeIndicator() const;
    void setModeIndicator(const QString &value);

signals:

public slots:

private:
    QString sentenceIdentifier;
    QString fixDate;
    QString status;
    QString latitude;
    QString latitudeDirection;
    QString longitude;
    QString longitudeDirection;
    QString speedOverGround;
    QString courseOverGround;
    QString date;
    QString magneticVariation;
    QString magneticVarIndicator;
    QString modeIndicator;
};

#endif // RMCSENTENCE_H
