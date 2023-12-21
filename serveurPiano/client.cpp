#include "client.h"

Client::Client()
{

}

float Client::getScoreJoueur() const
{
    return scoreJoueur;
}

void Client::setScoreJoueur(float newScoreJoueur)
{
    scoreJoueur = newScoreJoueur;
}

void Client::setPseudo(const QString &newPseudo)
{
    pseudo = newPseudo;
}

void Client::setSockClient(QTcpSocket *newSockClient)
{
    sockClient = newSockClient;
}

QTcpSocket *Client::getSockClient() const
{
    return sockClient;
}

bool Client::getPret() const
{
    return pret;
}

void Client::setPret(bool newPret)
{
    pret = newPret;
}

int Client::getCombo() const
{
    return combo;
}

void Client::setCombo(int newCombo)
{
    combo = newCombo;
}

const QString &Client::getPseudo() const
{
    return pseudo;
}
