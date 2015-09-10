#include "board.h"
#include <QtNetwork>

Board::Board(const QString & ipAddr, quint16 udpPort , QObject *parent) :
    QObject(parent)
{
    board = new QUdpSocket(this);
    QHostAddress addr;
    addr.setAddress(ipAddr);
    board->connectToHost(addr, udpPort, QUdpSocket::WriteOnly);

}

void Board::execCommand(const QString &exec)
{
    board->write(exec.toLatin1());
}

void
Board::setName(const QString &str)
{
  this->name = str;
}
const QString & 
Board::getName()
{
  return this->name;
}
