#include <QtGui>
#include "tsboard.h"
#include "tkarate.h"
#include "tests.h"
#include <iostream>

int main (int p1, char **p2)
{
  int exitCode = 0;
  QApplication a(p1,p2);
  sboard_test *t = new sboard_test();
  Karate_test *k = new Karate_test(t);
  t->show ();
  try {
    t->test ();
    k->test ();
    std::cout << "All tests pass" << std::endl;
  }
  catch (Assert *a) {
    exitCode =  1;
    std::cout << a->msg << std::endl;
  }
  delete t;
  return exitCode;
}
