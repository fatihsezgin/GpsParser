#include "dbmanager.h"


DbManager::DbManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::currentPath()+"/NMEASentencesdeneme.db");

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

bool DbManager::createTable()
{
    QSqlQuery query(db);
    return query.exec("CREATE TABLE GGASentence(GGAID INTEGER constraint GGASentence_pk primary key autoincrement,FIXTIME TEXT,LATITUDE NUMERIC,LATDIR TEXT,LONGITUDE NUMERIC,LONGDIR TEXT,FIXEDQUALITY INTEGER,SATALLITENUMBER INTEGER,HORIZONTALDILUTION NUMERIC,ALTITUDE NUMERIC,HEIGHTOFGEOID NUMERIC);") &&  query.exec("CREATE TABLE GLLSentence(GLLID INTEGER constraint GLLSentence_pk primary key autoincrement,LATITUDE NUMERIC,LATDIR TEXT,LONGITUDE NUMERIC,LONGDIR TEXT,FIXTIME TEXT,STATUS TEXT);")
     && query.exec("CREATE TABLE GNSSentence(GNSID INTEGER constraint GNSSentence_pk primary key autoincrement,FIXTIME TEXT,LATITUDE NUMERIC,LATDIR TEXT,LONGITUDE NUMERIC,LONGDIR TEXT,MODEINDUCATOR TEXT,NUMOFSATALLITES int,HDOP NUMERIC,ORTHOMETRICHEIGHT NUMERIC,GEOIDALSEPARATION NUMERIC,AGEOFDIFFERANTIALDATA NUMERIC default 0,REFERENCESTATIONID int);")
     && query.exec("CREATE TABLE GSASataList(LISTID INTEGER constraint GSASateList_pk primary key autoincrement,SATA1 int,SATA2 int,SATA3 int,SATA4 int,SATA5 int,SATA6 int,SATA7 int,SATA8 int,SATA9 int,SATA10 int,SATA11 int,SATA12 int);")
     && query.exec("CREATE TABLE GSASentence(GSAID INTEGER constraint GSASentence_pk primary key autoincrement,MODE TEXT,FIX int,PDOP NUMERIC,HDOP NUMERIC,VDOP NUMERIC,LISTID INTEGER constraint GSASentence_GSASataList_LISTID_fk references GSASataList);")
     &&  query.exec("CREATE TABLE GSVDetail(DETAILID INTEGER constraint MessageDeneme_pk primary key autoincrement,PRNNO int,ELEVATION int,AZIMUTH int,SNR int);")
    && query.exec("CREATE TABLE GSVMessage(GSVMESSAGEID INTEGER constraint GSVSentence_pk primary key autoincrement,TOTALMSGNO int,CURRENTMSGNO int,TOTALSVNO int,GSVDETAIL1 INTEGER references GSVDetail,GSVDETAIL2 INTEGER references GSVDetail,GSVDETAIL3 INTEGER references GSVDetail,GSVDETAIL4 INTEGER references GSVDetail)")
    && query.exec("create table GSVSentence(GSVID INTEGER constraint GSVTotalSentences_pk primary key autoincrement, SENTENCE1ID INTEGER references GSVMessage,SENTENCE2ID INTEGER references GSVMessage,SENTENCE3ID INTEGER references GSVMessage, SENTENCE4ID INTEGER references GSVMessage);")
    && query.exec("CREATE TABLE HDTSentence(HDTID INTEGER constraint HDTSentence_pk	primary key autoincrement,HEADINGDEGREE NUMERIC,RELATIVE TEXT);")
    && query.exec("CREATE TABLE RMCSentence(RMCID INTEGER constraint RMCSentence_pk primary key autoincrement,FIXTIME TEXT,STATUS TEXT,LATITUDE NUMERIC,LATDIR TEXT,LONGITUDE NUMERIC,LONGDIR TEXT,SPEEDGROUND NUMERIC,COURSEGROUND NUMERIC,FIXDATE TEXT,MAGNETICVARIATION NUMERIC,MAGNETICVARIND TEXT,MODEINDUCATOR TEXT);")
    && query.exec("CREATE TABLE VTGSentence(VTGID INTEGER constraint VTGSentence_pk primary key autoincrement,TRACKDEGREE NUMERIC,TRACKREF TEXT,TRACKDEGREEMAG NUMERIC,TRACKDMAGREF TEXT,SPEEDINKNOTS NUMERIC,SPEEDINKM NUMERIC,STATUS int);")
    && query.exec("CREATE TABLE ZDASentence(ZDAID INTEGER constraint ZDASentence_pk primary key autoincrement,UTCTIME TEXT,DATE TEXT,LOCALZONEHOURS int,LOCALZONEMINUTES int);")
    && query.exec("create table GpsDatum(DATAID INTEGER constraint GpsDatum_pk primary key autoincrement,GGAID  int references GGASentence,RMCID  int references RMCSentence,GLLID  int references GLLSentence,VTGID  int references VTGSentence,ZDAID  int references ZDASentence,GNSID  int references GNSSentence,HDTID  int references HDTSentence,GSAID  int references GSASentence,GSVID  int references GSVSentence, DateTime date);");
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
    QStringList idsList;
    QStringList selectQueryList;

    if(gga){
        idsList.append("GGAID");
        selectQueryList.append("(select seq from sqlite_sequence where name='GGASentence')");
    } if(rmc){
        idsList.append("RMCID");
        selectQueryList.append("(select seq from sqlite_sequence where name='RMCSentence')");
    } if(gll){
        idsList.append("GLLID");
        selectQueryList.append("(select seq from sqlite_sequence where name='GLLSentence')");
    }if(gns){
        idsList.append("GNSID");
        selectQueryList.append("(select seq from sqlite_sequence where name='GNSSentence')");
    }if(gsa){
        idsList.append("GSAID");
        selectQueryList.append("(select seq from sqlite_sequence where name='GSASentence')");
    }if(gsv){
        idsList.append("GSVID");
        selectQueryList.append("(select seq from sqlite_sequence where name='GSVSentence')");
    }if(hdt){
        idsList.append("HDTID");
        selectQueryList.append("(select seq from sqlite_sequence where name='HDTSentence')");
    }if(vtg){
        idsList.append("VTGID");
        selectQueryList.append("(select seq from sqlite_sequence where name='VTGSentence')");
    }if(zda){
        idsList.append("ZDAID");
        selectQueryList.append("(select seq from sqlite_sequence where name='ZDASentence')");
    }

    QString ids = idsList.join(",");
    QString selectQuery = selectQueryList.join(",");

    QString query = "";
    query.append("insert into GPSDatum (DateTime," );
    query.append(ids + ") values (datetime('now'),"+selectQuery+");");

    qDebug() << query;

    qDebug() << "insert GpsDatum"<<   insertGPSDatum(query);

}

bool DbManager::insertGPSDatum(QString &queryString)
{
    QSqlQuery query(db);
    return query.exec(queryString);
}

bool DbManager::insertGGA(GGASentence *gga)
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
    return  query.exec();

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

    //qDebug() << zda->getUtcTime() << zda->getDate() << zda->getLocalZoneHours() << zda->getLocalZoneHours()

    return  query.exec();

}

bool DbManager::insertGNS(GNSSentence *gns)
{
    QSqlQuery query(db);
    query.prepare("insert into GNSSentence(FIXTIME, LATITUDE, LATDIR, LONGITUDE, LONGDIR, MODEINDUCATOR, NUMOFSATALLITES, HDOP, ORTHOMETRICHEIGHT, GEOIDALSEPARATION, AGEOFDIFFERANTIALDATA, REFERENCESTATIONID) values(:a,:b,:c,:d,:e,:f,:g,:h,:k,:l,:m,:n);");
    query.bindValue(":a",gns->getFixTime());
    query.bindValue(":b",gns->getLatitude());
    query.bindValue(":c",gns->getLatitudeDirection());
    query.bindValue(":d",gns->getLongitude());
    query.bindValue(":e",gns->getLongitudeDirection());
    query.bindValue(":f",gns->getMode());
    query.bindValue(":g",gns->getNumberOfStallites());
    query.bindValue(":h",gns->getHDOP());
    query.bindValue(":k",gns->getOrthometricHeight());
    query.bindValue(":l",gns->getGeoidalSeparation());
    query.bindValue(":m",gns->getAgeOfDifferentialData());
    query.bindValue(":n",gns->getReferenceStationId());
    return  query.exec();
}

bool DbManager::insertHDT(HDTSentence *hdt)
{
    QSqlQuery query(db);
    query.prepare("insert into HDTSentence(HEADINGDEGREE,RELATIVE) VALUES (:a,:b);");
    query.bindValue(":a",hdt->getDegree());
    query.bindValue(":b",hdt->getRelative());
    return  query.exec();
}

bool DbManager::insertGSA(GSASentence *gsa)
{
    QSqlQuery query(db);
    query.prepare("insert into GSASataList (SATA1, SATA2, SATA3, SATA4, SATA5, SATA6, SATA7, SATA8, SATA9, SATA10, SATA11, SATA12) values (:a,:b,:c,:d,:e,:f,:g,:h,:k,:l,:m,:n);");
    query.bindValue(":a",gsa->getIds()[0]);
    query.bindValue(":b",gsa->getIds()[1]);
    query.bindValue(":c",gsa->getIds()[2]);
    query.bindValue(":d",gsa->getIds()[3]);
    query.bindValue(":e",gsa->getIds()[4]);
    query.bindValue(":f",gsa->getIds()[5]);
    query.bindValue(":g",gsa->getIds()[6]);
    query.bindValue(":h",gsa->getIds()[7]);
    query.bindValue(":k",gsa->getIds()[8]);
    query.bindValue(":l",gsa->getIds()[9]);
    query.bindValue(":m",gsa->getIds()[10]);
    query.bindValue(":n",gsa->getIds()[11]);

    bool a = query.exec();

    QSqlQuery q (db);
    q.prepare("insert into GSASentence (MODE,FIX,PDOP,HDOP,VDOP,LISTID) values (:a,:b,:c,:d,:e,(select seq from sqlite_sequence where name ='GSASataList'));");
    q.bindValue(":a", gsa->getMode());
    q.bindValue(":b",gsa->getFix());
    q.bindValue(":c",gsa->getPDOP());
    q.bindValue(":d",gsa->getHDOP());
    q.bindValue(":e",gsa->getVDOP());

    bool b = q.exec();
    return  (a && b);
}

bool DbManager::insertGSV(GSVSentence *gsv)
{
    QSqlQuery query(db);
    for(int i = 0 ; i< gsv->getSvlist().size(); i++){
        query.prepare("insert into GSVDetail(PRNNO,ELEVATION,AZIMUTH,SNR) values (:a,:b,:c,:d);");
        query.bindValue(":a",gsv->getSvlist().at(i)->getSvPrnNumber());
        query.bindValue(":b",gsv->getSvlist().at(i)->getElevationDegree());
        query.bindValue(":c",gsv->getSvlist().at(i)->getAzimuthDegree());
        query.bindValue(":d",gsv->getSvlist().at(i)->getSNR());
        query.exec();
    }
    int i = query.lastInsertId().toInt() - gsv->getSvlist().size(); // to get ıds that have been inserted into messages table to do inserting to GSVSentence

    QSqlQuery q (db);
    q.prepare( "insert into GSVMessage(TOTALMSGNO,CURRENTMSGNO,TOTALSVNO,GSVDETAIL1,GSVDETAIL2,GSVDETAIL3,GSVDETAIL4) values (:a,:b,:c,:d,:e,:f,:g)");
    q.bindValue(":a",gsv->getTotalMessageNum());
    q.bindValue(":b",gsv->getMessageNumber());
    q.bindValue(":c",gsv->getTotalNumberSatallites());
    q.bindValue(":d",i);
    q.bindValue(":e",i+1);
    q.bindValue(":f",i+2);
    q.bindValue(":g",i+3);

    return q.exec() ;

}

bool DbManager::insertTotalGSV(int totalMessageNumber)
{

    if(totalMessageNumber > 0 ){
        int lastinsertedid;
        QSqlQuery query (db);
        query.exec("select seq from sqlite_sequence where name='GSVMessage';");
        while(query.next()){
            lastinsertedid = query.value(0).toInt();
        }
        int beginindex = lastinsertedid - totalMessageNumber; // beginindex is the index that will be start inserting from.

        QString queryString = "";
        QStringList rows;
        QStringList values;

        // rows that will be inserting
        for(int i = 1; i <= totalMessageNumber ; i++){
            rows.append("SENTENCE"+QString::number(i)+"ID");
        }
        QString queryrows = rows.join(",");

        for (int i = beginindex; i < beginindex+totalMessageNumber ;i++ ){
            values.append(QString::number(i));
        }
        QString queryvalue = values.join(",");

        queryString.append("insert into GSVSentence("+queryrows+") values("+queryvalue+");");
        QSqlQuery q(db);
        qDebug() << "quuueryyyyyyyy" << queryString;
        return q.exec(queryString);
    }
    return false;

}



QList<QString> DbManager::getGGAById(QString ggaid)
{
    QList<QString>  gga;
    QSqlQuery query (db);

    query.exec("select * from GGASentence where GGAID="+ggaid);
    if(query.next()){
        for(int i = 0 ; i < 11 ; i++){ // since there are 10 colums in tge GGASentence
            gga << query.value(i).toString();
        }
    }
    for( QString a : gga){
        qDebug() << a;
    }

    return gga;

}

QList<QString> DbManager::getRMCById(QString rmcid)
{
    QList<QString>  rmc;
    QSqlQuery query (db);

    query.exec("select * from RMCSentence where RMCID="+rmcid);

    if(query.next()){
        for(int i = 0 ; i < 13 ; i++){ // since there are 11 colums in tge GGASentence
            rmc << query.value(i).toString();
        }
    }
    for( QString a : rmc){
        qDebug() << a;
    }
    return rmc;
}

QList<QString> DbManager::getGLLById(QString gllid)
{
    QList<QString>  rmc;
    QSqlQuery query (db);

    query.exec("select * from RMCSentence where RMCID="+gllid);
    query.record().count();
    if(query.next()){
        for(int i = 0 ; i < 13 ; i++){ // since there are 11 colums in tge GGASentence
            rmc << query.value(i).toString();
        }
    }
    for( QString a : rmc){
        qDebug() << a;
    }
    return rmc;
}

/** @param SentenceType is the identificator for NMEA type
 * @param sentenceId for the get all records that is related with that id.
**/

QList<QString> DbManager::getSentenceInfo(QString sentenceType, QString sentenceID)
{
    QList<QString> list;

    if(sentenceType.compare("GSA")==0){
        list = getSentenceInfoGSA(sentenceID);
        return list;
    }else if(sentenceType.compare("GSV") ==0){
        list = getSentenceInfoGSV(sentenceID);
        return list;
    }

    QSqlQuery query(db);

    query.exec("select * from " + sentenceType+"Sentence where " + sentenceType+"ID ="+ sentenceID);

    if(query.next()){
        for(int i =0 ; i <query.record().count(); i++ )
            list << query.value(i).toString();
    }

    for( QString a : list){
        qDebug() << a;
    }
    return list;
}

QList<QString> DbManager::getSentenceInfoGSA(QString sentenceID)
{
    QList<QString> list;
    QSqlQuery query(db);
    query.exec("Select * from GSASentence inner join GSASataList on GSASentence.LISTID = GSASataList.LISTID where GSAID ="+sentenceID);

    if(query.next()){
        for(int i =0 ; i <query.record().count(); i++ )
            list << query.value(i).toString();
    }
    for( QString a : list){
        qDebug() << a;
    }
    return list;
}

QList<QString> DbManager::getSentenceInfoGSV(QString sentenceID)
{
    QList<QString> sentenceList;//to store the records that is returned from GSVSentence table;
    QList<QString> messageList;//to store the records that is returned from GSVMessage table;
    QList<QString> detailList;
    QSqlQuery query(db);
    qDebug() << query.exec("Select * from GSVSentence where GSVID =" + sentenceID+";");

    if(query.next()){
        for(int i = 0 ; i < query.record().count();i++)
            sentenceList << query.value(i).toString();
    }

    QSqlQuery q(db);

    for(int i = 1 ; i < sentenceList.size();i++){
        q.exec("Select * from GSVMessage where GSVMESSAGEID =" + sentenceList.at(i) +";");
        if(q.next()){
            for(int i = 0 ; i < q.record().count();i++)
                messageList << q.value(i).toString();
        }
    }

    qDebug() << messageList.join(",");

    int i = 4;
    int j = 0;
    while(i < messageList.size()){
        while( j < 4){
            QSqlQuery query(db);
            query.exec("Select * from GSVDetail where DETAILID ="+ messageList.at(i)+";");
            if(query.next()){
                for(int i = 0 ; i < query.record().count() ; i++){
                    detailList << query.value(i).toString();
                }
            }
            i++;
            j++;
        }
        j=0;
        i+=4;
    }

    QString a = detailList.join(",");
    qDebug() << a;

    return detailList;

}

QSqlDatabase DbManager::getDb() const
{
    return db;
}
