#ifndef __COMMON_LIB_BOARD_H
#define __COMMON_LIB_BOARD_H

#include <QObject>
#include <QUdpSocket>

class Board : public QObject
{
    Q_OBJECT

    QString name;
    QUdpSocket *board;
    QString type;
public:
    explicit Board(
     const QString &ipAddr, 
     quint16 udpPort ,
     QObject *parent = 0);
    const QString& getName();

    bool myAddr (const QString &ip, quint16 port);
    const QString& getType();
    
signals:
    void boardChanged();

public slots:
    void execCommand(const QString&);
    void updateBoard ( );
    void setName(const QString &str);
    void setType (const QString &str);
};

#endif // BOARD_H
