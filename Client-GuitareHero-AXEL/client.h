#ifndef CLIENT_H
#define CLIENT_H


#include "qtcpsocket.h"
class Client
{
public:
    Client();
    int getScoreJoueur() const;
        void setScoreJoueur(int newScoreJoueur);
        const QString &getPseudo() const;
        void setPseudo(const QString &newPseudo);
        void setSockClient(QTcpSocket *newSockClient);
        QTcpSocket *getSockClient() const;

    private:
        int scoreJoueur;
        QString pseudo;
        QTcpSocket *sockClient;

        int timer  = 1000 ;
};

#endif // CLIENT_H
