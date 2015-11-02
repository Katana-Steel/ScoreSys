#include "karate.h"

class QWidget;

class Karate_test: public Karate
{
  void penalty_tests();
  void score_tests();
  void name_tests();
public:
  Karate_test(QWidget *parent=0);
  void test();
};
