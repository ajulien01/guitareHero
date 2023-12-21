#include "client.h"

Client::Client()
{

}

int Client::getScoreJoueur() const
{
    return scoreJoueur;
}

const QString &Client::getPseudo() const
{
    return pseudo;
}

void Client::setScoreJoueur(int newScoreJoueur)
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

int Client::getVitesse() const
{
    return vitesse;
}

void Client::setVitesse(int newVitesse)
{
    vitesse = newVitesse;
}
