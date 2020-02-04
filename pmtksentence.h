#ifndef PMTKSENTENCE_H
#define PMTKSENTENCE_H

#include <helper.h>
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
        Acknowledgement=1,
        SystemMessage = 10,
        TextMessage = 11,
        HotStart = 101,
        WarmStart=102,
        ColdStart =103,
        FullColdStart = 104,
        ClearEpo = 127,
        StandbyMode = 161,
        Locus_Query_Status = 183,
        Locus_Erase_Flash = 184,
        Locus_Stop_Logger = 185,
        Locus_Log_Now = 186,
        Locus_Config=187,
        SetPosFix = 220,
        Set_AL_DeeCfg = 223,
        SetPeriodicMode = 225,
        SetDataPort = 250,
        Set_Nmea_BaudRate= 251,
        Set_Sync_PPS_Nmea = 255,
        Set_GLP_Mode = 262,
        Set_Nmea_ReportInterval = 263,
        Set_Nmea_ReportCondition = 264,
        Set_PPS_ConfigCmd =285,
        Set_AIC_Cmd = 286,
        SetOutputDebug = 299,
        API_Set_FixCtl = 300,
        API_Set_SBAS_Enabled=313,
        APISetNmeaOutput=314,
        API_Set_PPS=326,
        API_Set_GNSS_SearchMode=353,
        API_Query_GNSS_SearchMode =355,
        API_Set_HDOP_Threshold=356,
        API_Get_HDOP_Threshold=357,
        API_Set_Static_NavThd=386,
        APIQFixCTL= 400,
        API_Q_SBAS_Enabled=413,
        API_QNmea_Output=414,
        DT_FixCtl=500,
        DT_SBAS_Enabled=513,
        DT_Nmea_Output=514,
        Q_Release =605,
        Q_EPO_Info=607,
        Q_LocusData=622,
        DT_Release=705,
        DT_UTC=740,
        DT_Pos=741
    };
    Q_ENUM(PacketType)
signals:

public slots:

private:
    QList<QString> sentence;
    QWidget *window;

    void process(QList<QString> pmtkSentence);
    void process001(QString packetName,QString status);
    void process010(QString packetName,QString systemTextMessage);
    void process011(QString packetName,QString textMessage);
    void process500(QList<QString> data);
    void process513(QString packetName,QString textMessage);
    void process514(QList<QString> data);
    void process705(QList<QString> data);
    void process707(QList<QString>data);

};

#endif // PMTKSENTENCE_H
