/*  GPL preample */
#include  <Qt/QWidget>
#include  <Qt/QList>

class scoreBase
  : public QWidget
{
public:
  /** void setRightPlayer  ();
   param QList<QString>
     first  element will be the display name
     second element will be the player's current score 
  */
  virtual void setRightPlayer (QList <QString> pldata) = 0;
  /** void setLeftPlayer  ();
   param QList<QString>
     first  element will be the display name
     second element will be the player's current score 
  */
  virtual void setLeftPlayer (QList <QString> pldata) = 0;
}; 