#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QTime>
#include <QMetaEnum>
#include <pmtksentence.h>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);

signals:

public slots:
    static QTime getTime(QString &time);
    static int calculateCheckSum(const char* s);
    static QString getPacketName(int packetValue);
};

#endif // HELPER_H
