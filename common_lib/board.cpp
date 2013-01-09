#include "board.h"
#include <QtNetwork>

Board::Board(quint64 /*id*/, QObject *parent) :
    QObject(parent)
{
//    QSqlDatabase db = QSqlDatabase::database(¨master¨);
    board = new QUdpSocket(this);
    QHostAddress addr;
    addr.setAddress("192.168.1.69");
    quint16 port = 10500;
    board->connectToHost(addr, port, QUdpSocket::WriteOnly);

}

void Board::execCommand(const QString &exec)
{
    board->write(exec.toLatin1());
}
