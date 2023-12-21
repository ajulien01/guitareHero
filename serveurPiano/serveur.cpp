#include "serveur.h"
#include "ui_serveur.h"
#include <QBuffer>
#include <QTextStream>
#include <QRandomGenerator>
#include <QTimer>

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
    nbJoueur--;
    ui->textEditMessage->append("Deconnexion" + client->peerAddress().toString() + " " + client->peerPort());
}

void Serveur::onQTcpSocket_readyRead()
{
    quint16 taille=0;
    QChar commande;
    QString pseudo;
    int score;
    bool pret;
    QString chaine;

    QTcpSocket *client=qobject_cast<QTcpSocket *>(sender ());
    int indexClient =getIndexClient(client);

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
                in >> pseudo ;
                listeClients.at(indexClient)->setPseudo(pseudo);
                ui->textEditMessage->append(pseudo+"vient de se connecter");
                envoyerPseudo();
                break;

            case 'S':
                //score
                in >> score;
                //calcul du nouveau score
                score = calculerScore(score,indexClient);
                //ajout du nouveau score dans liste client
                listeClients.at(indexClient)->setScoreJoueur(score);
                QTextStream(&chaine)<<"score "<<listeClients.at(indexClient)->getPseudo()<<":"<<score;
                ui->textEditMessage->append(chaine);
                break;
            case 'Q':
                //pret ou pas
                in >> pret;
                //joueur liste pret
                listeClients.at(indexClient)->setPret(pret);
                envoyerPret();
                QTextStream(&chaine)<<listeClients.at(indexClient)->getPseudo() << ":" << listeClients.at(indexClient)->getPret();
                ui->textEditMessage->append(chaine);

            // case envoie des coordonnees au clients
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
    nbJoueur++;
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

float Serveur::calculerScore(float newScore, int indexClient)
{
    float scoreJoueur = listeClients.at(indexClient)->getScoreJoueur();
    if(newScore > 0)
    {
        scoreJoueur += newScore;
        //combo
        if(scoreJoueur >= 10 && scoreJoueur < 50)
        {
            //reduire timer de 10%
            //envoyer combo x2
            envoyerComboVitesse(2,0.10);
        }

        if(scoreJoueur >= 50 && scoreJoueur <100)
        {
            //reduire timer de 20%
            //envoyer combo x4
            envoyerComboVitesse(4,0.20);
        }

        if(scoreJoueur == 100)
        {
            //reduire timer de 30%
            //envoyer combo x6
            envoyerComboVitesse(6,0.30);
        }
    }
    else if(newScore == 0)
    {
        if(scoreJoueur > 0)
            scoreJoueur --;

        //remettre timer initiale et combo à 0
        if(scoreJoueur < 30)
            envoyerComboVitesse(0,1);
    }

    return newScore;
}

void Serveur::envoyerComboVitesse(int combo, float multiplicateurTimer)
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('V');
    //envoie combo et vitesse

    // construction de la trame à envoyer au client;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<combo<<multiplicateurTimer;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    foreach(Client *client, listeClients)
    {

        client->getSockClient()->write(tampon.buffer());
    }
}


void Serveur::envoyerScore()
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('S');
    //envoie score

    QList<float> scoreJoueurs;

    //construire la liste des pret pas pret
    foreach(Client *client, listeClients)
    {
        scoreJoueurs.append(client->getScoreJoueur());
    }
    // envoyer à tous les clients
    // construction de la trame à envoyer au client;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<scoreJoueurs<<nbJoueur;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    foreach(Client *client, listeClients)
    {

        client->getSockClient()->write(tampon.buffer());
    }
}

void Serveur::envoyerPseudo()
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('P');

    // generation de liste des pseudos

    QList <QString> pseudoClients;

    //construire la liste des pseudos
    foreach(Client *client, listeClients)
    {
        pseudoClients.append(client->getPseudo());

    }
    // envoyer à tous les clients
    // construction de la trame à envoyer au client    qDebug() << "reserver";
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<pseudoClients<<nbJoueur;
    qDebug() << "envoyer pseudo :" << nbJoueur;

    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    foreach(Client *client, listeClients)
    {

        client->getSockClient()->write(tampon.buffer());
    }

}

void Serveur::envoyerPret()
{
    quint16 taille=0;
    QBuffer tampon;
    int nbPret=0;
    bool start=false;
    //envoie pret pas pret

    QList<bool> clientsPret;

    //construire la liste des pret pas pret
    foreach(Client *client, listeClients)
    {
        clientsPret.append(client->getPret());
        if(client->getPret()==true)
            nbPret++;
    }

    if(nbPret == nbJoueur && nbJoueur>=1)
    {
        start=true;
       // envoyerCoordonnees();
    }

    QList<int> coordonnees;

    for(int i= 0 ; i < NBPOINT; i++)
    {
        coordonnees.append(generValeurAleatoire());
    }

    QChar commande('Q');

    // envoyer à tous les clients
    // construction de la trame à envoyer au client;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<coordonnees<<clientsPret<<nbJoueur<<start;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    foreach(Client *client, listeClients)
    {

        client->getSockClient()->write(tampon.buffer());
    }
}



int Serveur::getIndexClient(QTcpSocket *client)
{
    int index = -1;
    foreach(Client *clientCourant, listeClients)
    {
        if (clientCourant->getSockClient() == client)
        {
            index = listeClients.indexOf(clientCourant);
        }
    }
    return index;
}

int Serveur::choixMusique()
{
    int valeurAleatoire = QRandomGenerator::global()->bounded(1, 3);
    return valeurAleatoire;
}

void Serveur::envoyerMusique()
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('M');
    int musique;
    //envoie titre musique

    musique = choixMusique();

    // envoyer à tous les clients
    // construction de la trame à envoyer au client;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<musique;
    qDebug() << "musique:" << musique;

    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    foreach(Client *client, listeClients)
    {

        client->getSockClient()->write(tampon.buffer());
    }

}

int Serveur::generValeurAleatoire()
{
    int valeurAleatoire = QRandomGenerator::global()->bounded(1, 5);
    //qDebug() << "Valeur aléatoire : " << valeurAleatoire;//debug
    return valeurAleatoire;
}

void Serveur::envoyerCoordonnees()
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('C');
    qDebug() << "envoi de coordonnee";
    QList<int> coordonnees;
    for(int i= 0 ; i < NBPOINT; i++)
    {
        coordonnees.append(generValeurAleatoire());
    }

    // envoyer à tous les clients
    // construction de la trame à envoyer au client;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<coordonnees;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    foreach(Client *client, listeClients)
    {

        client->getSockClient()->write(tampon.buffer());
    }
}



