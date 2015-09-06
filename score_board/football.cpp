/*  GPL preample */
#include <QtGui>
#include "football.h"

Football ::Football (QWidget *parent)
  : scoreBase(parent),timeouts()
{
    setupUi(this);
}

void
Football::setRightPlayer(QList<QString> pldata)
{
}

void
Football::setLeftPlayer(QList<QString> pldata)
{
}