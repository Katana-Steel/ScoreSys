/* GPL preample */
#include <QtGui>
#include "karate.h"


Karate::Karate(QWidget *parent)
  : scoreBase(parent)
{
    setupUi(this);
}

void
Karate::setRightPlayer(QList<QString> pldata)
{
  nameAka->setText (pldata.at (0));
}

void
Karate::setLeftPlayer(QList<QString> pldata)
{
  nameAo->setText (pldata.at (0));
}
