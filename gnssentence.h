#ifndef GNSSENTENCE_H
#define GNSSENTENCE_H

#include <QObject>

class GNSSentence : public QObject
{
    Q_OBJECT
public:
    explicit GNSSentence(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GNSSENTENCE_H
