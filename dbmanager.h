#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QList>
#include <QDebug>
#include <ggasentence.h>
#include <rmcsentence.h>
#include <gllsentence.h>
#include <vtgsentence.h>
#include <zdasentence.h>
#include <gnssentence.h>
#include <hdtsentence.h>
#include <gsasentence.h>
#include <gsvdetail.h>
#include <gsvsentence.h>
class DbManager
{
public:
    DbManager();

    bool isOpen() const;
    bool createTable() ;
    bool open();
    bool openTransaction();
    bool commit();

    void prepareQuery(bool gga, bool rmc, bool gll,bool gns,bool gsa,bool gsv,bool hdt,bool vtg,bool zda);

    bool insertGPSDatum(QString &queryString);
    bool insertGGA(GGASentence *gga);
    bool insertRMC(RMCSentence *rmc);
    bool insertGLL(GLLSentence *gll);
    bool insertVTG(VTGSentence *vtg);
    bool insertZDA(ZDASentence *zda);
    bool insertGNS(GNSSentence *gns);
    bool insertHDT(HDTSentence *hdt);
    bool insertGSA(GSASentence *gsa);
    bool insertGSV(GSVSentence *gsv);
    bool insertTotalGSV(int totalMessageNumber);

    QList<QString> getGGAById(QString ggaid);
    QList<QString> getRMCById(QString rmcid);
    QList<QString> getGLLById(QString gllid);

    QList<QString> getSentenceInfo(QString tableName,QString sentenceID);
    QList<QString> getSentenceInfoGSA(QString sentenceID);
    QList<QString> getSentenceInfoGSV(QString sentenceID);

    /*GGASentence *getGga() const;
    void setGga(GGASentence *value);

    RMCSentence *getRmc() const;
    void setRmc(RMCSentence *value);*/

    QSqlDatabase getDb() const;

private:
    QSqlDatabase db;

    /*GGASentence *gga;
    RMCSentence *rmc;*/

};

#endif // DBMANAGER_H
