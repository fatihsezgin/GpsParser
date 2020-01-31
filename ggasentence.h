#ifndef GGASENTENCE_H
#define GGASENTENCE_H

#include <QObject>
#include <QTime>
#include <helper.h>

class GGASentence : public QObject
{
    Q_OBJECT
public:
    explicit GGASentence(QObject *parent = nullptr);
     GGASentence(QString sentenceIdentifier,
                 QString fixTime,
                 QString latitude,
                 QString latDirection,
                 QString longitude,
                 QString longDirection,
                 QString  fixedQuality,
                 QString numberSatallites,
                 QString horizontalDilution,
                 QString altitude,
                 QString heightOfGeoid);


    QString getSentId() const;
    void setSentId(const QString &sentenceIdentifier);

    QTime getfixTime() const;
    void setfixTime( QString &fixTime);

    double getLatitude() const;
    void setLatitude(QString &latitude);

    QString getLatitudeDirection() const;
    void setLatitudeDirection(const QString &value);

    double getLongitude() const;
    void setLongitude( QString &longitude);

    QString getLongitudeDirection() const;
    void setLongitudeDirection(const QString &value);

    int getFixQuality() const;
    void setFixQuality(const QString &fixQuality);

    int getNumberSatallites() const;
    void setNumberStallites(const QString &numberSatallites);

    double getHorizontalDilution() const;
    void setHorizontalDilution(const QString &horizontalDilution);

    double getAltitude() const;
    void setAltitude(const QString &altitude);

    double getHeightOfGeoid() const;
    void setHeightOfGeoid(const QString &heightOfGeoid);

    QString toString();

signals:

public slots:


private:
    QString sentenceIdentifier;
    QTime fixTime;
    double latitude;
    QString latitudeDirection;
    double longitude;
    QString longitudeDirection;
    int fixQuality;
    int numberSatallites;
    double horizontalDilution;
    double altitude;
    double heightOfGeoid;

};

#endif // GGASENTENCE_H
