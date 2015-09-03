/* GPL preample */
#include <QtGui>
#include "karate.h"

Karate::Karate(QWidget *parent)
  : scoreBase(parent),penalties()
{
    setupUi(this);
    this->penalties << " " << "CHUKOKU" << "KEIKOKU" << "HANSOKU-CHUI" << "HANSOKU" << "SHIKKAKU";
}

void
Karate::setRightPlayer(QList<QString> pldata)
{
  nameAka->setText (pldata.at (0));
  scoreAka->display (pldata.at(1).split(':').at(1));

  try {
    aka_cat1->setText  ("Cat1: " + this->penalties.at(pldata.at (2).split(':').at(1).toInt()));
    aka_cat2->setText  ("Cat2: " + this->penalties.at(pldata.at (3).split(':').at(1).toInt()));
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
  scoreAo->display(pldata.at (1).split(':').at(1));

  try {
    ao_cat1->setText  ("Cat1: " + this->penalties.at(pldata.at (2).split(':').at(1).toInt()));
    ao_cat2->setText  ("Cat2: " + this->penalties.at(pldata.at (3).split(':').at(1).toInt()));
  }
  catch (...)
  {
    //done
  }
}
