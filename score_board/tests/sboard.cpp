#include "tsboard.h"
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
}

void
sboard_test::testTimer()
{
    this->reset_time();
    int min = this->timeMin->intValue ();
    if (6 != min)
        throw (new Assert("min isn't 6 after reset!"));
}
