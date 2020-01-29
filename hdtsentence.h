#ifndef HDTSENTENCE_H
#define HDTSENTENCE_H

#include <QObject>

class HDTSentence : public QObject
{
    Q_OBJECT
public:
    explicit HDTSentence(QObject *parent = nullptr);

    HDTSentence (QString sentenceIdentifier, QString degree , QString relative);

    QString getSentenceIdentifier() const;
    void setSentenceIdentifier(const QString &value);

    double getDegree() const;
    void setDegree(QString &value);

    QString getRelative() const;
    void setRelative(const QString &value);

signals:

public slots:

private:
    QString sentenceIdentifier;
    double degree;
    QString relative;
};

#endif // HDTSENTENCE_H
