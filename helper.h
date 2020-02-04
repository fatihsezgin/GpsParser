#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QTime>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);

signals:

public slots:
    static QTime getTime(QString &time);
    static int calculateCheckSum(const char* s);
};

#endif // HELPER_H
