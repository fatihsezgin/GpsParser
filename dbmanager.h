#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QDir>
#include <QDebug>
#include <ggasentence.h>
#include <rmcsentence.h>
class DbManager
{
public:
    DbManager();

    bool isOpen() const;
    void createTable() ;
    bool open();
    bool openTransaction();
    bool commit();


    bool insertGPSDatum();
    void insertGGA(GGASentence *gga);
    bool insertRMC(RMCSentence *rmc);

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
