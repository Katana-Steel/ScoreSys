#include  <QtGui>
#include "MasterUI.h"
#include "MasterServer.h"
#include "board.h"

MainMasterUi::MainMasterUi(QWidget *parent)
  : QMainWindow (parent),boards ()
{ 
  setupUi(this);
  this->server =  new MasterServer();
}

void 
MainMasterUi::addNewBoard(const QString &ip, quint16 port)
{ 
  Board *brd = new Board  (ip,port,this);
  this->boards.append (brd);
}

void
MainMasterUi::updateBoard (const QString &title, const QString & ip, quint16 port)
{
  if ( this->boards.isEmpty ())
    addNewBoard  (ip,port);
  Board *brd = this->boards.at(0);
  brd->execCommand  ("SetUi '"+title+"' karate\n");
}