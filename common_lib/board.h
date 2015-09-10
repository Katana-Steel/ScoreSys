#ifndef __COMMON_LIB_BOARD_H
#define __COMMON_LIB_BOARD_H

#include <QObject>
#include <QUdpSocket>

class Board : public QObject
{
    Q_OBJECT
    quint64 id;
    QString name;
    QUdpSocket *board;
public:
    explicit Board(
     const QString &ipAddr, 
     quint16 udpPort ,
     QObject *parent = 0);
    void setName(const QString &str);
    const QString& getName();
    
signals:
    
public slots:
    void execCommand(const QString&);
    
};

#endif // BOARD_H
