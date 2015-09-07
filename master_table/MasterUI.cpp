#include  <QtGui>
#include "MasterUI.h"
#include "MasterServer.h"
#include "board.h"

MainMasterUi::MainMasterUi(QWidget *parent)
  : QMainWindow (parent)
{ 
  setupUi(this);
  this->server =  new MasterServer();
}

void
MainMasterUi::addNewBoard()
{
}
