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
    explicit Board(quint64 id,QObject *parent = 0);
    
signals:
    
public slots:
    void execCommand(const QString&);
    
};

#endif // BOARD_H
