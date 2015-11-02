#include "tkarate.h"
#include "tests.h"
#include <QList>
#include <iostream>

using namespace::std;

Karate_test::Karate_test(QWidget *parent)
  : Karate(parent)
{
}

void
Karate_test::penalty_tests()
{
  QString pen = this->aka_cat1->text().split(' ').at(1);
  if (pen != this->penalties.at(1))
    throw (new Assert("Didn't set Red contestant's Category 1 penalty"));
  pen = this->aka_cat2->text().split(' ').at(1);
  if (pen != this->penalties.at(2))
    throw (new Assert("Didn't set Red contestant's Category 2 penalty"));
  pen = this->ao_cat1->text().split(' ').at(1);
  if (pen != this->penalties.at(1))
    throw (new Assert("Didn't set Blue contestant's Category 1 penalty"));
  pen = this->ao_cat2->text().split(' ').at(1);
  if (pen != this->penalties.at(2))
    throw (new Assert("Didn't set Blue contestant's Category 2 penalty"));
  cout << "penalty tests passed" << endl;
}

void
Karate_test::score_tests()
{
  if(this->scoreAka->intValue() != 3)
    throw (new Assert("Didn't set Red contestant's score to 3"));
  if(this->scoreAo->intValue() != 3)
    throw (new Assert("Didn't set Blue contestant's score to 3"));
  cout << "scoring tests passed" << endl;
}

void
Karate_test::name_tests()
{
  if(this->nameAka->text() != QString("Piere"))
    throw (new Assert("The name wasn't set for Red contestant"));
  if(this->nameAo->text() != QString("Piere"))
    throw (new Assert("The name wasn't set for Blue contestant"));
  cout << "name tests passed" << endl;
}

void
Karate_test::test()
{
  cout << "running Karate score board unit tests" << endl;
  QList<QString> pdata;
  pdata.append(QString::fromUtf8("Piere"));
  pdata.append(QString::fromUtf8("pt:3 cat1:1 cat2:2").split(' '));
  this->setRightPlayer(pdata);
  this->setLeftPlayer(pdata);
  this->penalty_tests();
  this->score_tests();
  this->name_tests();
}
