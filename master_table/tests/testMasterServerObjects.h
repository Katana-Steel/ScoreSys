#ifndef TESTMASTERSERVEROBJECTS_H
#define TESTMASTERSERVEROBJECTS_H

#include <QObject>
#include <QTextStream>

class MasterServer;

class testRequestTitle : public QObject
{
    Q_OBJECT
public:
    testRequestTitle();
private:
    quint16 myPort;
public slots:
    void start();
    void rqCallback(const QString &title, const QString &, quint16 port);
signals:
    void finished(QObject*);
};

class testMS : public QObject
{
    Q_OBJECT
public:
    testMS(QTextStream &_o);
private:
    QTextStream out;
    MasterServer *master;
    testRequestTitle *trqt;
private slots:
    void destroyCases(QObject* obj);
};

#endif // TESTMASTERSERVEROBJECTS_H
