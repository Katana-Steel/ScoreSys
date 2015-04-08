/* GPL preample */

#ifndef __scoring_sys_udp_ctl_h
#define __scoring_sys_udp_ctl_h

#include <QObject>

class sboard;
class QUdpSocket;

class udpserver : public QObject
{
    Q_OBJECT
public:
    udpserver(quint16 port, sboard *parent);
    ~udpserver();
private:
    QUdpSocket *sock;
    sboard *timer;
    quint16 my_port;

    void checkdata(QByteArray qba);
    void timerOps (QList<QByteArray> ops);
    void uiOps (QList<QByteArray> ops);
    void playerOps (QByteArray ops);
private slots:
    void udp_data();
public slots:
    void requestTitle();
};

#endif
