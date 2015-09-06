#ifndef __scoring_sys_master_table_ui_h 
#define __scoring_sys_master_table_ui_h 1
#include "ui_MasterUI.h"

class MainMasterUi : public QMainWindow, private Ui::MainWindow
{
   Q_OBJECT 
public:
    MainMasterUi(QWidget *parent=0);
};



#endif