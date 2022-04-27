#ifndef DUMESSENGERSOCKET_H
#define DUMESSENGERSOCKET_H
#include <QTcpSocket>

class DuMessengerSocket : public QTcpSocket
{

    Q_OBJECT
public:
    DuMessengerSocket(qintptr handle, QObject*parent=nullptr);


signals:
void DuStateChanged(DuMessengerSocket * , int);
void DuReadyRead(DuMessengerSocket*);

};

#endif // DUMESSENGERSOCKET_H
