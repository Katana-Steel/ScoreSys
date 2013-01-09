/* GPL preamble */
#include "error.h"
#include "testSQLdb.h"
#include "SQLdb.h"
#include <QtCore>
#include <QtSql>
#include <QtNetwork>

static void testReadSQLfile();
static void testLargeCompetitorInsert(); // Made this in to a two part test
                                         // First checking if the data in the database is right
                                         // Next seeing if the data rows count is correct too
static QStringList* generateCompetitors(int);
static void testCreateBoard();

static SQLdb *db;

void
testSQLdb(QTextStream &out)
{
  out << "entering SQL testing." << endl;
  db = new SQLdb(":memory:");
  testReadSQLfile();
  testLargeCompetitorInsert();
  testCreateBoard();
  delete db;
//  THROW_E("Object is not implemented yet") ;
}

void
testReadSQLfile()
{
    db->readSQLFile("db_create.sql");
    int tableCount = db->tableCount();
    if(tableCount < 2) {
        delete db;
        THROW_E("Didn't read the SQL file, right");
    }
}

static void
testLargeCompetitorInsert()
{
    int genNum = 6;
    QStringList *list = generateCompetitors(genNum);

    db->addCompetitors(list);
    delete list;

    QSqlDatabase *primeDb = new QSqlDatabase(QSqlDatabase::database("master"));
    QSqlQuery que = primeDb->exec("select name,cats from competitor");
    que.first();
    QString res = que.value(0).toString();
    que.finish();
    if( res != QString("Jack in the Box")) {
        delete primeDb;
        delete db;
        THROW_E(QString("insert failed expected: 'Jack in the Box' got '%1'").arg(res));
    }
    delete primeDb;

    // rowCount test
    int competitors = db->rowCount("competitor");
    if(competitors != genNum) {
        delete db;
        THROW_E(QString("expected: %1 got %2").arg(genNum).arg(competitors));
    }
}

static QStringList *generateCompetitors(int number)
{
    QStringList *ret = new QStringList();
    for(int i=0;i<number;i++)
    {
        ret->append("Jack in the Box:135");
    }
    return ret;
}

static void
testCreateBoard()
{

}
