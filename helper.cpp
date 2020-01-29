#include "helper.h"

Helper::Helper(QObject *parent) : QObject(parent)
{

}

QTime Helper::getTime(QString &time)
{
    QString trimmedTime = time.split(".").at(0);
    QTime result = QTime::fromString(trimmedTime,"HHmmss");
    return result;
}
