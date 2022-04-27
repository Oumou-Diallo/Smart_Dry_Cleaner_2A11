#ifndef DUMESSENGERSERVER_H
#define DUMESSENGERSERVER_H
#include <QTcpServer>
class DuMessengerSocket;
class DuMessengerServer : public QTcpServer
{
public:
    DuMessengerServer(QObject * parent = nullptr);
protected:
    void incomingConnection(qintptr handle);

private:
    QList<DuMessengerSocket *>mSockets;
};

#endif // DUMESSENGERSERVER_H
