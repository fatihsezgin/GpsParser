#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QDir>
#include <QDebug>
#include <ggasentence.h>
#include <rmcsentence.h>
#include <gllsentence.h>
#include <vtgsentence.h>
#include <zdasentence.h>
class DbManager
{
public:
    DbManager();

    bool isOpen() const;
    void createTable() ;
    bool open();
    bool openTransaction();
    bool commit();

    void prepareQuery(bool gga, bool rmc, bool gll,bool gns,bool gsa,bool gsv,bool hdt,bool vtg,bool zda);

    bool insertGPSDatum(QString &queryString);
    void insertGGA(GGASentence *gga);
    bool insertRMC(RMCSentence *rmc);
    bool insertGLL(GLLSentence *gll);
    bool insertVTG(VTGSentence *vtg);
    bool insertZDA(ZDASentence *zda);

    /*GGASentence *getGga() const;
    void setGga(GGASentence *value);

    RMCSentence *getRmc() const;
    void setRmc(RMCSentence *value);*/

private:
    QSqlDatabase db;

    /*GGASentence *gga;
    RMCSentence *rmc;*/

};

#endif // DBMANAGER_H
