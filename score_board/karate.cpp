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
  scoreAka->display (pldata.at (1));
  try {
    aka_cat1->setText  (pldata.at (2));
    aka_cat2->setText  (pldata.at (3));
  }
  catch (...)
  {
    //done
  }
}

void
Karate::setLeftPlayer(QList<QString> pldata)
{
  nameAo->setText (pldata.at (0));
  scoreAo->display(pldata.at (1));
  try {
    ao_cat1->setText  (pldata.at (2));
    ao_cat2->setText  (pldata.at (3));
  }
  catch (...)
  {
    //done
  }
}