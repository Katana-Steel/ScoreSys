
void#include "board.h"
#include <QtNetwork>

Board::Board(const QString & ipAddr, quint16 udpPort , QObject *parent) :
    QObject(parent)
{
    board = new QUdpSocket(this);
    QHostAddress addr;
    addr.setAddress(ipAddr);
    board->connectToHost(addr, udpPort, QUdpSocket::WriteOnly);

}

void 
Board::execCommand(const QString &exec)
{
    board->write(exec.toLatin1());
}

void
Board::setName(const QString &str)
{
  this->name = str;
}

QString& 
Board::getName() const
{
  return this->name;
}

bool 
Board::myAddr (const QString &ip, quint16 port)
{
  bool ret = false; 
  if ( this->board->peerAddress().toString() == ip )
    if ( this->board->peerPort() == port)
      ret = true;
  return ret;
} 

QString& 
Board::getType() const
{ 
  return this->type;
} 

void
Board::updateBoard ( ) 
{ 
  this->execCommand  ("SetUi '" +this->name +"' "+ this->type);
} 