#include <QtGui>
#include "tsboard.h"

int main (int p1, char **p2)
{
  QApplication a = QApplication(p1,p2);
  sboard_test *t = new sboard_test();
  t->show ();
  t->test ();
  delete t;
  return 0;
}