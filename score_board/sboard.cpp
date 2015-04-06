/* GPL preample */
#include <QtGui>
#include <QtSql>
#include "sboard.h"
#include "karate.h"
#include "udp_ctl.h"

sboard::sboard(QWidget *parent)
    : QWidget(parent),port(8888)
{
    setupUi(this);
    /* the default scoreboard is for karate
       but the abstraction with scoreBase means in the future
       we could have more types of scoring systems */
    scores = new Karate(this);
    this->TheBoard->addWidget(scores);
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
sboard::set_aka_name(const QString &str)
{
//    nameAka->setText(str);
}

void
sboard::set_ao_name(const QString &str)
{
//    nameAo->setText(str);
}

void
sboard::set_aka_points(int points)
{
/*    if(!timer->isActive() && points != 0) return;
    scoreAka->display(points); */
}

void
sboard::set_ao_points(int points)
{
/*    if(!timer->isActive() && points != 0) return;
    scoreAo->display(points); */
}

void
sboard::aka_penalty(int cat,int lvl)
{
/*
    QString pen;
    for(int i=0;i<lvl;i++)
        pen.append("X ");

    switch(cat)
    {
    case 1:
        aka_cat1->setText(QString("Cat. 1 ").append(pen));
        break;
    case 2:
        aka_cat2->setText(QString("Cat. 2 ") + pen);
        break;
    }
*/
}

void
sboard::ao_penalty(int cat,int lvl)
{
/*
    QString pen;
    for(int i=0;i<lvl;i++)
        pen.append("X ");

    switch(cat)
    {
    case 1:
        ao_cat1->setText(QString("Cat. 1 ") + pen);
        break;
    case 2:
        ao_cat2->setText(QString("Cat. 2 ") + pen);
        break;
    }
*/
}
