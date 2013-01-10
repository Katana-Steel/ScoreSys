#ifndef MASTERSERVER_H
#define MASTERSERVER_H

#include <QObject>

class MasterServer : public QObject
{
    Q_OBJECT
public:
    explicit MasterServer(QObject *parent = 0);
    
signals:
    void updateBoardName(QString name, QString IPv4, quint16 port);

public slots:
  //  void pushTableName(QString name, QString IPv4, quint16 port);
};

#endif // MASTERSERVER_H
