/* GPL preample */

#include <QtGui>
#include <QtNetwork>
#include "udp_ctl.h"
#include "sboard.h"
#include "scoreBase.h"

udpserver::udpserver(quint16 port, sboard *parent)
    : QObject(parent)
{
    my_port = port;
    timer = parent;
    sock = new QUdpSocket(this);
    sock->bind(port,QUdpSocket::DontShareAddress|QUdpSocket::ReuseAddressHint);

    connect(sock, SIGNAL(readyRead()), this, SLOT(udp_data()));
    connect(timer, SIGNAL(needTitle()), this, SLOT(requestTitle()));
}

udpserver::~udpserver()
{
    delete sock;
}

void
udpserver::checkdata (QByteArray qba)
{
    QList<QByteArray> ops;
    int i = qba.indexOf(" ")+1;
    if(qba.startsWith("timer ")) {
      ops = qba.split(' ');
      timerOps (ops);
    }
    if(qba.startsWith("SetUi ")) {
        ops = QList<QByteArray>();
        int j = qba.indexOf("'",i+2);
        ops.append(qba.mid(i,j-i));
        ops.append(qba.mid(j+2).split(' '));
        uiOps (ops);
    }
    if(qba.startsWith("player ")) {
      playerOps(qba.mid(i));
    }
}

void
udpserver::timerOps ( QList<QByteArray> ops)
{
  if (ops.count() > 2) {
    QList<QByteArray> t = ops.at(2).split(':');
    if (t.count () > 2)
      timer->reset_time(t.at(0).toInt(), t.at(1).toInt(), t.at(2).toInt());
  }
  if (ops.at(1) == "start")
    timer->start_time();
  if (ops.at(1) == "stop")
    timer->stop_time();

}

void
udpserver::uiOps (QList<QByteArray> ops)
{
  timer->set_title(ops.first().replace ('\'',QString("")));
  ops.removeFirst();
  if (!ops.isEmpty()) {
    timer->set_score_ui(ops.first());
  }
}

void
udpserver::playerOps ( QByteArray ops)
{
  scoreBase *scores = timer->get_score_ui();
  if (scores == 0)
    return;
  char pl = ops.at(0);

  QList<QString> update = QList<QString>();
  int i = ops.indexOf ("'")+1;
  int j = ops.indexOf ("'",i)-1;
  QString n = QString(ops.mid(i,j-i));
  update.append(n);
  foreach( QString part, ops.mid (j+2).split(' ')) {
    update.append(part);
  }
  if (pl == 'r')
    scores->setRightPlayer(update);
  if (pl == 'l')
    scores->setLeftPlayer(update);
}

void
udpserver::udp_data()
{
    while (sock->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(sock->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         sock->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);

         foreach(QByteArray data, datagram.split('\n')) {
           checkdata(data);
         }
         datagram.clear();
     }
}

void
udpserver::requestTitle()
{
    QByteArray datagram = "needUi " + QByteArray::number((uint)my_port);
    sock->writeDatagram(datagram,QHostAddress::Broadcast,9500);
}