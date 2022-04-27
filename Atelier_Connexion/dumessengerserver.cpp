#include "dumessengerserver.h"
#include "dumessengersocket.h"
#include <QDebug>
#include <QTextStream>

DuMessengerServer::DuMessengerServer(QObject * parent)
    : QTcpServer(parent)
{

}


void DuMessengerServer::incomingConnection(qintptr handle)
{
    auto socket = new DuMessengerSocket(handle,this);
    mSockets << socket;

    connect(socket, &DuMessengerSocket::DuReadyRead, [&](DuMessengerSocket * S){
      QTextStream T(S);
      auto text = T.readAll();

      for(auto i : mSockets){
          QTextStream K(i);
          K<<text;


      }

    });

    /*connect(socket, &DuMessengerSocket::DuStateChanged,
            [&](DuMessengerSocket *S, int ST)
            )
    {
        if(ST)


    }*/

}
