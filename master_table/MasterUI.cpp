#include  <QtGui>
#include "MasterUI.h"
#include "MasterServer.h"
#include "board.h"

MainMasterUi::MainMasterUi(QWidget *parent)
  : QMainWindow (parent),boards ()
{ 
  setupUi(this);
  this->server =  new MasterServer(true, this);
  connect(this->server, SIGNAL(newBoardReady(const QString &, quint16)),this,SLOT(addNewBoard(const QString &, quint16 )));
  connect(this->server, SIGNAL(updateBoardName(const QString &, const QString &, quint16)),this,SLOT(updateBoard(const QString &,const QString &, quint16 )));
}

void 
MainMasterUi::addNewBoard(const QString &ip, quint16 port)
{ 
  Board *brd = new Board  (ip,port,this);
  brd->setName(ip + ":" + QString::number(port) + " - Default");
  this->boards.append (brd);
  QListWidgetItem *lwi = new QListWidgetItem(brd->getName());
  this->listView->addItem(lwi);
}

void
MainMasterUi::updateBoard (const QString &title, const QString & ip, quint16 port)
{
  if ( this->boards.isEmpty ())
    addNewBoard  (ip,port);
  Board *brd = this->boards.last();
  if (!brd->getName().contains(ip)) {
    addNewBoard(ip,port);
    brd = this->boards.last();
  }
  brd->execCommand  ("SetUi '"+title+"' karate\n");
}
