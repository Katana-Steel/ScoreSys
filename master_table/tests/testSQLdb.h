/* GPL preamble */

#include <QTextStream>


// general database tests, eg. creation, inserts and general tests of the db object
void testSQLdb(QTextStream &out);

// interactions with the tests database for other test modules( read-only )
QStringList getDataFromTestDb(const QString &table, const QString &where=QString(),const QString &limit=QString());

// at the end of all test call this to clear up the database from memory.
void destroyTestDb(void);
