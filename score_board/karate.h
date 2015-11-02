/* GPL preample */
#ifndef __scoring_sys_karate_h
#define __scoring_sys_karate_h
#include "scoreBase.h"
#include "ui_karate.h"

class Karate : public scoreBase, private Ui_Karate
{
    Q_OBJECT
public:
    Karate  (QWidget *parent=0);
    void setRightPlayer ( const QList<QString> &pldata );
    void setLeftPlayer ( const QList<QString> &pldata );

private:
    QStringList penalties;
};

#endif
