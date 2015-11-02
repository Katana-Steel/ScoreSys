#include "tsboard.h"
#include "tkarate.h"
#include "tests.h"
#include <iostream>

using namespace std;

sboard_test::sboard_test()
 : sboard(0)
{
}

void
sboard_test::test()
{
  cout << "initated unit test of sboard" << endl;
  this->testTimer();
  cout << "timer tests done, pass" << endl;
  this->testScores();
  cout << "scoring tests done, pass" << endl;
}

void
sboard_test::validateTimer (int min,int sec, int usec)
{
    int val = this->timeMin->intValue ();
    if (min != val)
        throw (new Assert("min isn't 6 after reset!"));
    val = this->timeSec->intValue ();
    if (sec != val)
        throw (new Assert("sec isn't 0 after reset!"));
    val = this->timeProcentSec->intValue ();
    if (usec != val)
        throw (new Assert("hundreds of a sec isn't 0 after reset!"));

}

void
sboard_test::testTimer()
{
    this->reset_time();
    this->validateTimer();
    // a test out of the norm.
    this->reset_time(4,67,127);
    this->validateTimer(4,67,127);
}

void
sboard_test::testScores()
{
  this->set_score_ui(QString("karate"));
  if(!this->scores) {
    throw(new Assert("couldn't set the central scoring ui"));
  }
}

