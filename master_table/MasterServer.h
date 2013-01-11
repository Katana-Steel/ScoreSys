#ifndef MASTERSERVER_H
#define MASTERSERVER_H

#include <QObject>

class QUdpSocket;

class MasterServer : public QObject
{
    Q_OBJECT
    QUdpSocket *masterSocket;
    bool autoMode;
    quint32 counts;
public:
    MasterServer(bool mode=true,QObject *parent = 0);
    
signals:
    void updateBoardName(const QString &name, const QString &IPv4, quint16 port);

private:
    void process(const QString &IPv4, QByteArray msg);
public slots:
    void incomming();
  //  void pushTableName(QString name, QString IPv4, quint16 port);
};

#endif // MASTERSERVER_H
