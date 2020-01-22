#ifndef GGASENTENCE_H
#define GGASENTENCE_H

#include <QObject>
#include <QDateTime>

class GGASentence : public QObject
{
    Q_OBJECT
public:
    explicit GGASentence(QObject *parent = nullptr);
     GGASentence(QString sentenceIdentifier,
                 QString fixedDate,
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

    QString getFixedDate() const;
    void setFixedDate(const QString &fixedDate);

    QString getLatitude() const;
    void setLatitude(QString &latitude,  QString &latDirection);

    QString getLongitude() const;
    void setLongitude( QString &longitude,  QString &longDirection);

    QString getFixQuality() const;
    void setFixQuality(const QString &fixQuality);

    QString getNumberSatallites() const;
    void setNumberStallites(const QString &numberSatallites);

    QString getHorizontalDilution() const;
    void setHorizontalDilution(const QString &horizontalDilution);

    QString getAltitude() const;
    void setAltitude(const QString &altitude);

    QString getHeightOfGeoid() const;
    void setHeightOfGeoid(const QString &heightOfGeoid);



signals:

public slots:


private:
    QString sentenceIdentifier;
    QString fixDate;
    QString latitude;
    QString longitude;
    QString fixQuality;
    QString numberSatallites;
    QString horizontalDilution;
    QString altitude;
    QString heightOfGeoid;

};

#endif // GGASENTENCE_H
