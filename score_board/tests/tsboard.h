#include "sboard.h"

class sboard_test : public sboard 
{
  void testTimer();
  void validateTimer(int m=6,int s=0,int u=0);
public:
  sboard_test ();
  void test ();
};
