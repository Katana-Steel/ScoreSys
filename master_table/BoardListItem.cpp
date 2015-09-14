/*  GPL preample. */ 

#include "board.h"
#include "BoardListItem.h"

BoardListItem::BoardListItem  (Board * brd, QListWidget *parent )
  : QListWidgetItem(parent),_board  (brd)
{ 
  setText(_board->getName());
  connect(_board,SIGNAL(boardChanged()), this, SLOT(updateBoardName()));
} 

void
BoardListItem::updateBoardName()
{ 
   setText (_board->getName());
}
