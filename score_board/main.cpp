/* GPL preample */

#include <QApplication>
#include "sboard.h"
#include "udp_ctl.h"

int main(int ac, char **av)
{
    QApplication a(ac,av);
    sboard *win = new sboard();
    a.setActiveWindow(win);

    // starting the UDP control interface.
    qsrand(time((0)));
    quint16 port = 10000 + (qrand() % 2000);
    udpserver *server = new udpserver(port,win);
    server->requestTitle();
    a.connect(win,SIGNAL(needTitle()), server, SLOT(requestTitle()));
    win->show();
    return a.exec();
}
