#include "dbmanager.h"


DbManager::DbManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::currentPath()+"/NMEASentences.db");

   if(!db.open()){
        qDebug() << "error";
    }else{
        qDebug() << "Database connection ok";
    }
}

bool DbManager::isOpen() const
{
    return db.isOpen();
}

void DbManager::createTable()
{

   QString insert =
           "insert into RMCSentence (FIXTIME, STATUS, LATITUDE, LATDIR) values (:a,:b, :c,:d);"
           "insert into GGASentence (FIXTIME, LATITUDE, LATDIR) values (:e,:f,:g);"
           "insert into GpsDatum (GGAID,RMCID) values ((select seq from sqlite_sequence where name='GGASentence'), (select seq from sqlite_sequence where name='RMCSentence'));";
          // "commit transaction ;";

   qDebug() << db.isOpen();

    db.transaction();
    qDebug() << "transaction status : "  << db.transaction();

    //qDebug() << "rmc query " <<insertRMC();

    qDebug() << "comit" <<db.commit();

}

bool DbManager::open()
{
    if(!db.isOpen()){
        db.open();
    }
    return db.open();
}

bool DbManager::openTransaction()
{
    return db.transaction();
}

bool DbManager::commit()
{
    return db.commit();
}

bool DbManager::insertGPSDatum()
{
    QSqlQuery query(db);
    return query.exec("insert into GpsDatum (GGAID,RMCID) values ((select seq from sqlite_sequence where name='GGASentence'), (select seq from sqlite_sequence where name='RMCSentence'));");
}

void DbManager::insertGGA(GGASentence *gga)
{
        QSqlQuery query(db);
        query.prepare("insert into GGASentence(FIXTIME,LATITUDE,LATDIR,LONGITUDE,LONGDIR,FIXEDQUALITY,SATALLITENUMBER,HORIZONTALDILUTION,ALTITUDE,HEIGHTOFGEOID) values (:a,:b,:c,:d,:e,:f,:g,:h,:k,:l) ");
        query.bindValue(":a",gga->getfixTime());
        query.bindValue(":b",gga->getLatitude());
        query.bindValue(":c",gga->getLatitudeDirection());
        query.bindValue(":d",gga->getLongitude());
        query.bindValue(":e",gga->getLongitudeDirection());
        query.bindValue(":f",gga->getFixQuality());
        query.bindValue(":g",gga->getNumberSatallites());
        query.bindValue(":h",gga->getHorizontalDilution());
        query.bindValue(":k",gga->getAltitude());
        query.bindValue(":l",gga->getHeightOfGeoid());
        qDebug() << "insertGGA"<< query.exec();
}

bool DbManager::insertRMC(RMCSentence *rmc)
{
    QSqlQuery query(db);
    query.prepare("insert into RMCSentence(FIXTIME,STATUS,LATITUDE,LATDIR,LONGITUDE,LONGDIR,SPEEDGROUND,COURSEGROUND,FIXDATE,MAGNETICVARIATION,MAGNETICVARIND,MODEINDUCATOR) values (:a,:b,:c,:d,:e,:f,:g,:h,:k,:l,:m,:n)");
    query.bindValue(":a",rmc->getFixTime());
    query.bindValue(":b",rmc->getStatus());
    query.bindValue(":c",rmc->getLatitude());
    query.bindValue(":d",rmc->getLatitudeDirection());
    query.bindValue(":e",rmc->getLongitude());
    query.bindValue(":f",rmc->getLongitudeDirection());
    query.bindValue(":g",rmc->getSpeedOverGround());
    query.bindValue(":h",rmc->getCourseOverGround());
    query.bindValue(":k",rmc->getDate());
    query.bindValue(":l",rmc->getMagneticVariation());
    query.bindValue(":m",rmc->getMagneticVarIndicator());
    query.bindValue(":n",rmc->getModeIndicator());
    return  query.exec();
}

/*GGASentence *DbManager::getGga() const
{
    return gga;
}

void DbManager::setGga(GGASentence *value)
{
    gga = value;
}

RMCSentence *DbManager::getRmc() const
{
    return rmc;
}

void DbManager::setRmc(RMCSentence *value)
{
    rmc = value;
}*/
