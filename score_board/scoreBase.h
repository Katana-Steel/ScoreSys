/*  GPL preample */
#ifndef __scoring_sys_score_base_h 
#define __scoring_sys_score_base_h 1

#include  <QWidget>
#include  <QList>

class scoreBase
  : public QWidget
{
public:
  scoreBase(QWidget *parent=0) : QWidget(parent) {};
  /** void setRightPlayer  ();
   param QList<QString>
     first  element will be the display name
     second element will be the player's current score
  */
  virtual void setRightPlayer (const QList <QString> &pldata) = 0;
  /** void setLeftPlayer  ();
   param QList<QString>
     first  element will be the display name
     second element will be the player's current score
  */
  virtual void setLeftPlayer (const QList <QString> &pldata) = 0;
};

#endif 
