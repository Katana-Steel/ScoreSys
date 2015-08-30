
#include <QtSql>
#include <QtCore>
#include "SQLdb.h"
#include "error.h"

SQLdb::SQLdb(QString dbfile, QObject *parent)
    : QObject(parent),connectionName("master")
{
    if (QSqlDatabase::contains(connectionName)) {
        db = new QSqlDatabase(QSqlDatabase::database(connectionName));
        if(db->databaseName() != dbfile) {
            delete db;
            QSqlDatabase::removeDatabase(connectionName);
            createConnection(dbfile);
        }
    } else {
        createConnection(dbfile);
    }
}

SQLdb::~SQLdb()
{
    db->close();
    delete db;
    QSqlDatabase::removeDatabase(connectionName);
}

void
SQLdb::createConnection(QString dbfile)
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", connectionName));
    db->setDatabaseName(dbfile);
    db->open();
}

void
SQLdb::readSQLFile(QString sqlFile)
{
    if(db->isValid()) {
        db->transaction();
        QFile *file = new QFile(sqlFile);
        file->open(QFile::ReadOnly);
        QTextStream sql(file);
        QSqlQuery dbQuery = db->exec();
        for(QString queryString = sql.readLine(); !queryString.isNull();queryString = sql.readLine()) {
            if(queryString.isEmpty()) continue;
            dbQuery.exec(queryString);
        }
        dbQuery.clear();
        db->commit();
    }
}

int
SQLdb::tableCount()
{
    return db->tables().size();
}

void
SQLdb::addCompetitors(QStringList *competitors)
{
    if(db->isValid()) {
        db->transaction();
        QSqlQuery dbQuery = db->exec();
        dbQuery.prepare("insert into `competitor` (name, cats) values(:name, :cats)");
        QStringList names;
        QStringList cats;
        foreach(QString comp, *competitors)
        {
            QStringList competSplit = comp.split(":");
            names << competSplit.at(0);
            cats << competSplit.at(1);
        }
        dbQuery.bindValue("name", names);
        dbQuery.bindValue("cats", cats);
        dbQuery.execBatch();
        db->commit();
    }
}

int
SQLdb::rowCount(const QString &tableName)
{
    QString query = "select * from " + tableName;
    QSqlQuery dbQuery = db->exec();
    bool success = dbQuery.exec(query);
    int ret = 0;
    if(success) {
        success = dbQuery.first();
        if(success) {
            ret = 1;
            dbQuery.first();
            while(dbQuery.next())
                ret++;
        }
    }
    dbQuery.finish();
    return ret;
}

void
SQLdb::setTableName(QString name, QString IPv4, quint16 port)
{
    emit tableNameChanged(name,IPv4,port);
}
