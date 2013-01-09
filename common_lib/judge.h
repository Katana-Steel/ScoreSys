#ifndef JUDGE_H
#define JUDGE_H

#include <QObject>

class Judge : public QObject
{
    Q_OBJECT
    quint64 id;
public:
    explicit Judge(QObject *parent = 0);
    
signals:
    void exec(const QString&);
    
public slots:
    
};

#endif // JUDGE_H
