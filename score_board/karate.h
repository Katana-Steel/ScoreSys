/* GPL preample */
#include "scoreBase.h"

class Karate : public scoreBase 
{
    Q_OBJECT 
public:
    Karate  (QWidget *parent);
    void setRightPlayer ( QList<QString> pldata );
    void setLeftPlayer ( QList<QString> pldata );
};