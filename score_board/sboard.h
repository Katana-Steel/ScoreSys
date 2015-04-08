/* GPL Preample here */
#ifndef __scoring_sys_sboard_h
#define __scoring_sys_sboard_h

#include "ui_sboard.h"
#include <QWidget>

class udpserver;
class scoreBase;

class sboard : public QWidget, private Ui_Dialog
{
    Q_OBJECT
public:
    sboard(QWidget *parent=0);
    ~sboard();
    scoreBase* get_score_ui();
public slots:
    void show();
    void update_display();
    void update_count();
    void stop_time();
    void start_time();
    void reset_time(int min=6, int sec=0,int pro=0);
    void set_title(const QString &str);
    void set_score_ui(const QString &req_ui);
private:
    QTimer *timer;
    QTimer *disp;
    QString table;
    quint16 port;
    scoreBase *scores;

    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void needTitle();
};


#endif
