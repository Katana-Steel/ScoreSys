/* GPL preample */
#ifndef __scoring_sys_football_h
#define __scoring_sys_football_h
#include "scoreBase.h"
#include "ui_football.h"

class Football : public scoreBase, private Ui_Football
{
    Q_OBJECT
    QStringList timeouts;
public:
    Football (QWidget *parent=0);
    void setRightPlayer ( QList<QString> pldata );
    void setLeftPlayer ( QList<QString> pldata );
};

#endif
