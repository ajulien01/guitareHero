#include "serveur.h"
#include "ui_serveur.h"

Serveur::Serveur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Serveur)
{
    ui->setupUi(this);
    socketEcoute = new QTcpServer();
    connect(socketEcoute, &QTcpServer::newConnection,this,&Serveur::onQTcpSocket_newConnection);

}

Serveur::~Serveur()
{
    delete ui;
    delete socketEcoute;
}

void Serveur::onQTcpSocket_connected()
{
    ui->textEditMessage->append("Il y a une connexion");
}

void Serveur::onQTcpSocket_disconnected()
{
    // récupérer la socket du client se déconnectant
    QTcpSocket *client=qobject_cast<QTcpSocket *>(sender());
    // récupérer l'index de ce client dans la liste
    int index= getIndexClient(client);
    // supprimer le client de la liste
    if (index!=-1)
    {
        listeClients.removeAt(index);
    }
    // afficher un message avec l'ip et le port du client deconnecté
    ui->textEditMessage->append("Deconnexion" + client->peerAddress().toString() + " " + client->peerPort());
}

void Serveur::onQTcpSocket_readyRead()
{
    quint16 taille=0;
    QChar commande;
    QString pseudo;
    int indexClient;


    QTcpSocket *client=qobject_cast<QTcpSocket *>(sender ());

    if(client->bytesAvailable() >= (quint64)sizeof(taille))
    {
        QDataStream in(client);
        in >> taille;
        if(client->bytesAvailable() >= (quint64)sizeof(taille))
        {
            in >> commande;
            switch(commande.toLatin1())
            {
            //pseudo
            case 'P':
                in >> pseudo;
                listeClients.at(indexClient)->setPseudo(pseudo);
                break;
            //touche piano
            case 'A':

                break;
            case 'Z':
                break;
            case 'E':
                break;
            case 'R':
                break;
            }
        }
    }
}

void Serveur::onQTcpSocket_newConnection()
{
    // récupération de la socket de communication du client
    QTcpSocket *client=socketEcoute->nextPendingConnection();

    // connection signal/slot pour la socket
    connect(client,&QTcpSocket::connected,this,&Serveur::onQTcpSocket_connected);
    connect(client,&QTcpSocket::disconnected,this,&Serveur::onQTcpSocket_disconnected);
    connect(client,&QTcpSocket::readyRead,this,&Serveur::onQTcpSocket_readyRead);
    connect(client,&QTcpSocket::errorOccurred,this,&Serveur::onQTcpSocket_errorOccured);
    // création et ajout du client dans la liste des clients
    Client *nouveauClient=new Client();
    nouveauClient->setSockClient(client);
    listeClients.append(nouveauClient);
    ui->textEditMessage->append("nouvelle connexion");
}

void Serveur::onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditMessage->append(socketEcoute->errorString());
}


void Serveur::on_pushButtonLancerServeur_clicked()
{
    if (socketEcoute->listen(QHostAddress::Any, ui->spinBoxPortEcoute->value())) {
        ui->textEditMessage->append( "Le serveur est en écoute sur le port "+ui->spinBoxPortEcoute->text());
    } else {
        ui->textEditMessage->append("Impossible de démarrer le serveur.");
    }
}

void Serveur::getPseudoClient()
{

}

int Serveur::getIndexClient(QTcpSocket *client)
{
    foreach(Client *clientCourant, listeClients)
    {
        if (clientCourant->getSockClient() == client)
        {
            int index = listeClients.indexOf(clientCourant);
            return index;
        }
        else
        {
            int index = -1;
            return index;
        }
    }
}

