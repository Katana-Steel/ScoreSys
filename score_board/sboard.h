/* GPL Preample here */
#ifndef __scoring_sys_sboard_h
#define __scoring_sys_sboard_h

#include "ui_sboard.h"
#include <QWidget>

class udpserver;

class sboard : public QWidget, private Ui_Dialog
{
    Q_OBJECT
public:
    sboard(QWidget *parent=0);
    ~sboard();
public slots:
    void show();
    void update_display();
    void update_count();
    void stop_time();
    void start_time();
    void reset_time(int min=6, int sec=0,int pro=0);
    void set_title(const QString &str);
    void set_aka_name(const QString &name);
    void set_ao_name(const QString &name);
    void set_aka_points(int);
    void set_ao_points(int);
    void aka_penalty(int,int);
    void ao_penalty(int,int);
private:
    QTimer *timer;
    QTimer *disp;
    QString table;
    quint16 port;

    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void needTitle();
};


#endif
