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

void DbManager::prepareQuery(bool gga, bool rmc, bool gll,bool gns,bool gsa,bool gsv,bool hdt,bool vtg,bool zda)
{
    QString ids = "";
    QString selectQuery = "";

    if(gga){
        ids.append("GGAID");
        selectQuery.append("(select seq from sqlite_sequence where name='GGASentence')");
    } if(rmc){
        ids.append("RMCID");
         selectQuery.append("(select seq from sqlite_sequence where name='RMCSentence')");
    } if(gll){
        ids.append("GLLID");
         selectQuery.append("(select seq from sqlite_sequence where name='GLLSentence')");
    }if(gns){
        ids.append("GNSID");
         selectQuery.append("(select seq from sqlite_sequence where name='GNSSentence')");
    }if(gsa){
        ids.append("GSAID");
         selectQuery.append("(select seq from sqlite_sequence where name='GSASentence')");
    }if(gsv){
        ids.append("GSVID");
         selectQuery.append("(select seq from sqlite_sequence where name='GSVSentence')");
    }if(hdt){
        ids.append("HDTID");
         selectQuery.append("(select seq from sqlite_sequence where name='HDTSentence')");
    }if(vtg){
        ids.append("VTGID");
         selectQuery.append("(select seq from sqlite_sequence where name='VTGSentence')");
    }if(zda){
        ids.append("ZDAID");
         selectQuery.append("(select seq from sqlite_sequence where name='ZDASentence')");
    }

    for(int i = 5 ; i < ids.size();i+=6){
            ids.insert(i,",");
        }
    for(int i = 58 ; i < selectQuery.size();i+=59){
            selectQuery.insert(i,",");
        }
        QString query = "";
        query.append("insert into GPSDatum (" );
        query.append(ids + ") values ("+selectQuery+");");

        qDebug() << "insert GpsDatum"<<   insertGPSDatum(query);

}

    bool DbManager::insertGPSDatum(QString &queryString)
    {
        QSqlQuery query(db);
        return query.exec(queryString);
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

    bool DbManager::insertGLL(GLLSentence *gll)
    {
        QSqlQuery query(db);
        query.prepare("insert into GLLSentence(LATITUDE, LATDIR, LONGITUDE, LONGDIR, FIXTIME,STATUS) VALUES (:a,:b,:c,:d,:e,:f);");
        query.bindValue(":a",gll->getLatitude());
        query.bindValue(":b",gll->getLatitudeDirection());
        query.bindValue(":c",gll->getLongitude());
        query.bindValue(":d",gll->getLongitudeDirection());
        query.bindValue(":e",gll->getFixTime());
        query.bindValue(":f",gll->getStatus());

        return  query.exec();
    }

    bool DbManager::insertVTG(VTGSentence *vtg)
    {
        QSqlQuery query(db);
        query.prepare("insert into VTGSentence(TRACKDEGREE,TRACKREF, TRACKDEGREEMAG, TRACKDMAGREF, SPEEDINKNOTS,SPEEDINKM,STATUS) VALUES (:a,:b,:c,:d,:e,:f,:g);");
        query.bindValue(":a",vtg->getTrackDegree());
        query.bindValue(":b",vtg->getTrackReference());
        query.bindValue(":c",vtg->getTrackDegreeMagnetic());
        query.bindValue(":d",vtg->getTrackDegreeMagRef());
        query.bindValue(":e",vtg->getSpeedInKnots());
        query.bindValue(":f",vtg->getSpeedInKm());
        query.bindValue(":g",vtg->getStatus());
        return  query.exec();
    }

    bool DbManager::insertZDA(ZDASentence *zda)
    {
        QSqlQuery query(db);
        query.prepare("insert into ZDASentence(UTCTIME,DATE, LOCALZONEHOURS, LOCALZONEMINUTES) VALUES (:a,:b,:c,:d);");
        query.bindValue(":a",zda->getUtcTime().toString());
        query.bindValue(":b",zda->getDate().toString());
        query.bindValue(":c",zda->getLocalZoneHours());
        query.bindValue(":d",zda->getLocalZoneMinutes());
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
