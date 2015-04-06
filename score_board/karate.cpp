/* GPL preample */
#include <QtGui>
#include "karate.h"


Karate::Karate(QWidget *parent)
  : scoreBase(parent)
{
    setupUi(this);
}

void
Karate::setRightPlayer(QList<QString> /* pldata */)
{
}

void
Karate::setLeftPlayer(QList<QString> /* pldata */)
{
}
