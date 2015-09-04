/* GPL preample */
#include <QtGui>
#include <QtSql>
#include "sboard.h"
#include "karate.h"
#include "football.h"
#include "udp_ctl.h"

sboard::sboard(QWidget *parent)
    : QWidget(parent),port(8888)
{
    setupUi(this);
    /* the default scoreboard is for karate
       but the abstraction with scoreBase means in the future
       we could have more types of scoring systems */
    scores = 0;
    timer = new QTimer(this);
    disp = new QTimer(this);
    disp->setInterval(15000);
    timer->setInterval(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(update_count()));
    connect(disp,SIGNAL(timeout()),this,SLOT(update_display()));
}

sboard::~sboard()
{
    if(disp->isActive()) disp->stop();
    if(timer->isActive()) timer->stop();
    delete disp;
    delete timer;
}

scoreBase*
sboard::get_score_ui  ()
{
  return this->scores;
}

void
sboard::mouseReleaseEvent(QMouseEvent*)
{
    if(this->isVisible())
        this->close();
}

void
sboard::show()
{
    timeMin->display(6);
    timeSec->display(0);
    timeProcentSec->display(0);
    disp->start();
    return QWidget::show();
}

void
sboard::update_count()
{
    if(!disp->isActive())
        timer->stop();
    int min = timeMin->intValue();
    int sec = timeSec->intValue();
    int hun = timeProcentSec->intValue();
    if (hun == 0) {
        if(sec == 0) {
            if(min == 0) {
                timer->stop();
                return;
            }
            else
                min--;
            sec = 59;
        }
        else
            sec--;
        hun = 99;
    }
    else
        hun--;

    timeMin->display(min);
    timeSec->display(sec);
    timeProcentSec->display(hun);
}

void
sboard::update_display()
{
/*    if(!timer->isActive()) {
        timeMin->display(6);
        timeSec->display(0);
        timeProcentSec->display(0);
        timer->start();
    } */
    if(table.isEmpty())
        emit needTitle();
}

void
sboard::stop_time()
{
    timer->stop();
}

void
sboard::start_time()
{
    timer->start();
}

void
sboard::reset_time(int min, int sec,int pro)
{
    bool act = timer->isActive();
    if(act) timer->stop();
    timeMin->display(min);
    timeSec->display(sec);
    timeProcentSec->display(pro);
    if(act) timer->start();
}

void
sboard::set_title(const QString &str)
{
    table = str;
    btitle->setText(str);
}

void
sboard::set_score_ui (const QString &str)
{
    scoreBase *newui=0;
    if (str.toLower() == QString ("karate")){
      newui = new Karate(this);
    }
    if (str.toLower() == QString ("football")){
      newui = new Football(this);
    }

    if (newui != 0) {
      if (scores != 0) {
        this->TheBoard->removeWidget (scores);
        delete scores;
      }
      scores = newui;
      this->TheBoard->addWidget(scores);
    }
}
