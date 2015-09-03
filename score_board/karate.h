/* GPL preample */
#ifndef __scoring_sys_karate_h
#define __scoring_sys_karate_h
#include "scoreBase.h"
#include "ui_karate.h"

class Karate : public scoreBase, private Ui_Karate
{
    Q_OBJECT
    QStringList penalties;
public:
    Karate  (QWidget *parent=0);
    void setRightPlayer ( QList<QString> pldata );
    void setLeftPlayer ( QList<QString> pldata );
};

#endif
