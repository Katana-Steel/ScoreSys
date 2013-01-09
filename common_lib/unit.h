#ifndef __COMMON_LIB_Unit
#define __COMMON_LIB_Unit 1

#include <QObject>
#include <QVector>

class Board;
class Judge;

class Unit : public QObject
{
    Q_OBJECT
    Judge *table;
    QVector<Board*> boards;
public:
    Unit(QObject *parent=0);

public slots:
    void addScoreBoard(quint64);
};

#endif
