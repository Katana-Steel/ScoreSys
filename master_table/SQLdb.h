
#include <QSqlDatabase>
#include <QObject>

class QSqlDatabase;

class SQLdb : public QObject
{
    Q_OBJECT
public:
    SQLdb(QString dbfile, QObject *parent=0);
    ~SQLdb();

    void readSQLFile(QString file);
    int tableCount();
    int rowCount(const QString &tableName);
    void addCompetitors(QStringList *competitors);
public slots:
    void setTableName(QString name, QString IPv4, quint16 port);
private:
    void createConnection(QString dbfile);
    QString connectionName;
    QSqlDatabase *db;
signals:
    void tableNameChanged(QString name, QString IPv4, quint16 port);
};
