#include  <QtGui>
#include "MasterUI.h"
#include "MasterServer.h"
#include "board.h"
#include "BoardListItem.h"

MainMasterUi::MainMasterUi(QWidget *parent)
  : QMainWindow (parent),boards (),curBoard(0)
{ 
  setupUi(this);
  this->server =  new MasterServer(true, this);
  connect(
    this->autoMode, SIGNAL(toggled(bool)),
    this->server, SLOT(setAutoMode(bool))
  );
  connect(
    this->server, SIGNAL(newBoardReady(const QString &, quint16)),
    this, SLOT(addNewBoard(const QString &, quint16 ))
  );
  connect(
    this->server, SIGNAL(updateBoardName(const QString &, const QString &, quint16)),
    this, SLOT(updateBoard(const QString &,const QString &, quint16 ))
  );
  connect(
    this->scoreboardList, SIGNAL(itemClicked(QListWidgetItem*)), 
    this, SLOT(BoardSelected(QListWidgetItem*))
  );
}

void
MainMasterUi::BoardSelected(QListWidgetItem *lwi)
{

    BoardListItem *brd = dynamic_cast<BoardListItem*>(lwi);
    if (brd) {
      if (this->curBoard) {
        disconnect(this->sb_title,SIGNAL(textChanged(const QString&)),0,0);
      }
      this->sb_title->setText(brd->getBoard()->getName());
      this->sb_type->setCurrentIndex(0);
      this->curBoard = brd->getBoard();
      connect(
        this->sb_title, SIGNAL(textChanged(const QString&)), 
        this->curBoard, SLOT(setName(const QString&))
      );
      connect(
        this->sb_title, SIGNAL(textChanged(const QString&)), 
        this->curBoard, SLOT(updateBoard())
      );
    }
}

void 
MainMasterUi::addNewBoard(const QString &ip, quint16 port)
{ 
  Board *brd = new Board  (ip,port,this);
  brd->setName(ip + ":" + QString::number(port) + " - Default");
  brd->setType("karate");
  this->boards.append (brd);
  BoardListItem *lwi = new BoardListItem(brd);
  this->scoreboardList->addItem(lwi);
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
