#ifndef __scoring_sys_master_table_ui_h 
#define __scoring_sys_master_table_ui_h 1
#include <QList>
#include "ui_MasterUI.h"


class MasterServer;
class Board;

class MainMasterUi : public QMainWindow, private Ui::MainWindow
{
   Q_OBJECT 
   MasterServer *server;
   QList<Board*> boards;
public:
    MainMasterUi(QWidget *parent=0);
private slots:
   void addNewBoard();
};



#endif
