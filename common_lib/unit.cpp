#include "unit.h"
#include "board.h"
#include "judge.h"
#include <QtCore>

Unit::Unit(QObject *parent)
    : QObject(parent)
{

}

void Unit::addScoreBoard(quint64 id)
{
    Board *brd = new Board(id);
    boards.append(brd);
    connect(table, SIGNAL(exec(const QString&)),brd,SLOT(execCommand(const QString&)));
}
