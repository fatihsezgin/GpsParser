#ifndef GSASENTENCE_H
#define GSASENTENCE_H

#include <QObject>

class GSASentence : public QObject
{
    Q_OBJECT
public:
    explicit GSASentence(QObject *parent = nullptr);

    GSASentence(QString sentenceIdentifier, QString mode, QString fix , QList<int> ids, QString PDOP, QString HDOP, QString VDOP);

    QString getSentenceIdentifier() const;
    void setSentenceIdentifier(const QString &value);

    QString getMode() const;
    void setMode(const QString &value);

    int getFix() const;
    void setFix(QString &value);

    QList<int> getIds() const;
    void setIds(const QList<int> &value);

    double getPDOP() const;
    void setPDOP(QString &value);

    double getHDOP() const;
    void setHDOP(QString &value);

    double getVDOP() const;
    void setVDOP(QString &value);

signals:

public slots:

private:
    QString sentenceIdentifier;
    QString mode;
    int fix;
    QList<int> ids;
    double PDOP;//diluton of precision
    double HDOP;//horizontal dilution of precision
    double VDOP;//vertical dilution of precision


};

#endif // GSASENTENCE_H
