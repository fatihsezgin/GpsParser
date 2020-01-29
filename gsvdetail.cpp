#include "gsvdetail.h"

GSVDetail::GSVDetail(QObject *parent) : QObject(parent)
{

}

GSVDetail::GSVDetail(QString SvPrnNumber, QString elevationDegree, QString azimuthDegree, QString SNR)
{
    setSvPrnNumber(SvPrnNumber);
    setElevationDegree(elevationDegree);
    setAzimuthDegree(azimuthDegree);
    setSNR(SNR);

}

int GSVDetail::getSvPrnNumber()
{
    return svPrnNumber;
}

void GSVDetail::setSvPrnNumber(QString &value)
{
    svPrnNumber = value.toInt();
}

int GSVDetail::getElevationDegree()
{
    return elevationDegree;
}

void GSVDetail::setElevationDegree(QString &value)
{
    elevationDegree = value.toInt();
}

double GSVDetail::getAzimuthDegree()
{
    return azimuthDegree;
}

void GSVDetail::setAzimuthDegree(QString &value)
{
    azimuthDegree = value.toDouble();
}

int GSVDetail::getSNR()
{
    return SNR;
}

void GSVDetail::setSNR(QString &value)
{
    SNR = value.toInt();
}
