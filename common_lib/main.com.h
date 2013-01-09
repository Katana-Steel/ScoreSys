/* GPL preample */
#ifndef __common_main_h
#define __common_main_h 1

#include <QObject>

class common_config : public QObject
{
    Q_OBJECT
public:
    common_config(QObject *parent);
};

#endif
