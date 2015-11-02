/*  GPL preample */
#include <QtGui>
#include "football.h"

Football ::Football (QWidget *parent)
  : scoreBase(parent),timeouts()
{
    setupUi(this);
}

void
Football::setRightPlayer(const QList<QString> &pldata)
{
  QString Away = pldata.at(0);
  QString Score = pldata.at(1).split(':').at(1);
  this->away_team->setText(Away);
  this->away_score->display(Score);
}

void
Football::setLeftPlayer(const QList<QString> &pldata)
{
  QString Home = pldata.at(0);
  QString Score = pldata.at(1).split(':').at(1);
  this->home_team->setText(Home);
  this->home_score->display(Score);
}
