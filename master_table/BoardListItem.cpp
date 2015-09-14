/*  GPL preample. */ 

#include "board.h"
#include "BoardListItem.h"

BoardListItem::BoardListItem  (Board * brd, QListWidget *parent )
  : QListWidgetItem(parent),_board  (brd)
{ 
  setText(this->board->getName());
  connect(this->board,SIGNAL(boardChanged()), this, SLOT(updateBoardName()));
} 

void
BoardListItem::updateBoardName()
{ 
   setText (board->getName());
}