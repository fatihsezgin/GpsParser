#ifndef GSVDETAIL_H
#define GSVDETAIL_H

#include <QObject>

class GSVDetail : public QObject
{
    Q_OBJECT
public:
    explicit GSVDetail(QObject *parent = nullptr);

    GSVDetail(QString SvPrnNumber, QString elevationDegree,QString azimuthDegree,QString SNR);

    int getSvPrnNumber();
    void setSvPrnNumber(QString &value);

    int getElevationDegree() ;
    void setElevationDegree(QString &value);

    double getAzimuthDegree() ;
    void setAzimuthDegree(QString &value);

    int getSNR();
    void setSNR(QString &value);

signals:

public slots:

private:
    int svPrnNumber;
    int elevationDegree;
    double azimuthDegree;
    int SNR;

};

#endif // GSVDETAIL_H
