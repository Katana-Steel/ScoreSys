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

  foreach (QString data, pldata) {
    int pen;
    if(data.startsWith("cat1:")) {
      pen = data.split(':').at(1).toInt();
      if ( pen >= 0 && pen < this->penalties.size() ) {
        aka_cat1->setText  ("Cat1: " + this->penalties.at(pen));
      }
    }
    if(data.startsWith("cat2:")) {
      pen = data.split(':').at(1).toInt();
      if ( pen >= 0 && pen < this->penalties.size() ) {
        aka_cat2->setText  ("Cat2: " + this->penalties.at(pen));
      }
    }
  }
}

void
Karate::setLeftPlayer(QList<QString> pldata)
{
  nameAo->setText (pldata.at (0));
  scoreAo->display(pldata.at (1).split(':').at(1));

  foreach (QString data, pldata) {
    int pen;
    if(data.startsWith("cat1:")) {
      pen = data.split(':').at(1).toInt();
      if ( pen >= 0 && pen < this->penalties.size() ) {
        ao_cat1->setText  ("Cat1: " + this->penalties.at(pen));
      }
    }
    if(data.startsWith("cat2:")) {
      pen = data.split(':').at(1).toInt();
      if ( pen >= 0 && pen < this->penalties.size() ) {
        ao_cat2->setText  ("Cat2: " + this->penalties.at(pen));
      }
    }
  }
}
