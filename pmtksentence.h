#ifndef PMTKSENTENCE_H
#define PMTKSENTENCE_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>

class PMTKSentence : public QObject
{
    Q_OBJECT
public:
    explicit PMTKSentence(QObject *parent = nullptr);
    PMTKSentence(QList<QString> sentence ,QWidget *parent);
    enum PacketType{
        TestPacket = 0,
        Ack =1,
        SystemMessage = 10,
        TextMessage = 11,
        HotStart = 101,
        WarmStart=102,
        ColdStart =103,
        FullColdStart = 104,
        ClearEpo = 127,
        StandbyMode = 161,
        LocusQueryStatus = 183,
        LocusEraseFlash = 184,
        LocusStopLogger = 185,
        LocusLogNow = 186,
        LocusConfig=187,
        SetPosFix = 220,
        SetALDeeCfg = 223,
        SetPeriodicMode = 225,
        SetDataPort = 250,
        SetNmeaBaudRate= 251,
        SetSyncPPSNmea = 255,
        SetGLPMode = 262,
        SetNmeaReportInterval = 263,
        SetNmeaReportCondition = 264,
        SetPPSConfigCmd =285,
        SetAICCmd = 286,
        SetOutputDebug = 299,
        APISetFixCtl = 300,
        APISetSBASEnabled=313,
        APISetNmeaOutput=314,
        APISetPPS=326,
        APISetGNSSSearchMode=353,
        APIQueryGnssSearchMode =355,
        APISetHDOPThreshold=356,
        APIGetHDOPThreshold=357,
        APISetStaticNavThd=386,
        APIQFixCTL= 400,
        APIQSBASEnabled=413,
        APIQNmeaOutput=414,
        DTFixCtl=500,
        DTSBASEnabled=513,
        DTNmeaOutput=514,
        QRelease =605,
        QEPOInfo=607,
        QLocusData=622,
        DTRelease=705,
        DTUTC=740,
        DTPos=741
    };
    Q_ENUM(PacketType)
signals:

public slots:

private:
    QList<QString> sentence;
    QWidget *window;

    void process(QList<QString> pmtkSentence);
};

#endif // PMTKSENTENCE_H
