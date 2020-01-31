#ifndef VTGSENTENCE_H
#define VTGSENTENCE_H

#include <QObject>

class VTGSentence : public QObject
{
    Q_OBJECT
public:
    explicit VTGSentence(QObject *parent = nullptr);

    VTGSentence (QString sentenceIdentifier, QString trackDegree,
                     QString trackReference, QString trackDegreeMagnetic,QString trackDegreeMagRef,
                     QString speedInKnots,QString speedForKnots,
                     QString speedInKm, QString speedForKm,
                     QString status);

    QString getSentenceIdentifier() const;
    void setSentenceIdentifier(const QString &value);

    double getTrackDegree() const;
    void setTrackDegree(QString &value);

    QString getTrackReference() const;
    void setTrackReference(const QString &value);

    double getTrackDegreeMagnetic() const;
    void setTrackDegreeMagnetic(QString &value);

    QString getTrackDegreeMagRef() const;
    void setTrackDegreeMagRef(const QString &value);

    double getSpeedInKnots() const;
    void setSpeedInKnots(QString  &value);

    QString getSpeedForKnots() const;
    void setSpeedForKnots(const QString &value);

    double getSpeedInKm() const;
    void setSpeedInKm(QString &value);

    QString getSpeedForKm() const;
    void setSpeedForKm(const QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

    QString toString();

signals:

public slots:

private:
    QString sentenceIdentifier;
    double trackDegree;
    QString trackReference;
    double trackDegreeMagnetic;
    QString trackDegreeMagRef;//TrackDegreeMagneticReference
    double speedInKnots;
    QString speedForKnots;
    double speedInKm;
    QString speedForKm;
    QString status;


};

#endif // VTGSENTENCE_H
