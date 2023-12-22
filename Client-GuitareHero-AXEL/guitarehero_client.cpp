#include "guitarehero_client.h"
#include "ui_guitarehero_client.h"
#include <QGridLayout>
#include <QBuffer>
#include <QDataStream>
#include <QApplication>

GuitareHero_Client::GuitareHero_Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuitareHero_Client)
{
    ui->setupUi(this);
    socketClient = new QTcpSocket(this);
    connect(socketClient, &QTcpSocket::connected, this, &::GuitareHero_Client::onQTcpSocket_connected);
    connect(socketClient, &QTcpSocket::disconnected, this, &::GuitareHero_Client::onQTcpSocket_disconnected);
    connect(socketClient, &QTcpSocket::readyRead, this, &::GuitareHero_Client::onQTcpSocket_readyRead);
    connect(socketClient, &QTcpSocket::errorOccurred, this, &::GuitareHero_Client::onQTcpSocket_errorOccured);
    bidon=new QWidget();
    bidon->setGeometry(0,0,600,600);
    bidon->show();
    jeux = new InterfacePrincipale(false,bidon);
    jeux->show();
    connect(jeux, &InterfacePrincipale::keyPressed, this, &GuitareHero_Client::handleKeyPressed);
    resultat = new score();

    connect(jeux, &InterfacePrincipale::finDePartie, this ,&GuitareHero_Client::finDePartie);



}

GuitareHero_Client::~GuitareHero_Client()
{
    delete ui;
}

void GuitareHero_Client::EnvoyerPseudo()
{
    pseudo = ui->lineEditPseudo->text();
    //qDebug() << "pseudo send";

    quint16 taille=0;
    QBuffer tampon;
    QChar commande('P');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<pseudo;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    // envoi du QByteArray du tampon via la socket
    socketClient->write(tampon.buffer());
}

void GuitareHero_Client::EnvoyerEtat(bool pret)
{
    qDebug() << "etat send";

    quint16 taille=0;
    QBuffer tampon;
    QChar commande('Q');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<pret;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    // envoi du QByteArray du tampon via la socket
    socketClient->write(tampon.buffer());
}


void GuitareHero_Client::on_pushButtonConnexion_clicked()
{
    if(ui->pushButtonConnexion->text()=="Connexion"){
        socketClient->connectToHost(ui->lineEditAdresseServeur->text(),ui->spinBoxPortServeur->value());
    }else{
        socketClient->disconnectFromHost();
    }
}

void GuitareHero_Client::onQTcpSocket_connected()
{
  //  qDebug()<<"connexion";
    EnvoyerPseudo();
}

void GuitareHero_Client::onQTcpSocket_disconnected()
{
    qDebug()<<"deconnexion";
}

void GuitareHero_Client::onQTcpSocket_readyRead()
{
    quint16 taille=0;
    QChar commande;
    QList <QString> PseudoJoueur ;
    QList <bool> etatJoueur;
    bool start ;
    int nombreDeJoueurs ;
    QList <int> coordonnees ;
    int combo ;
    float multiplicateurVitesse ;
    int musique ;
    QList <int> scoreJoueurs;

    if (socketClient->bytesAvailable() >= (qint64)sizeof(taille))
    {
        // Lecture de la taille de la trame
        QDataStream in(socketClient);
        in >> taille;
        // Le reste de la trame est disponible
        if (socketClient->bytesAvailable() >= (qint64)taille)
        {
            in>>commande;
            switch (commande.toLatin1()) {
            // envoyer les places pour le vol ref
            case 'P':
                in>>PseudoJoueur>>nombreDeJoueurs;
             //   qDebug() << nombreDeJoueurs ;
                if (nombreDeJoueurs == 1 ){
                    ui->lineEditJoueur1->setText(PseudoJoueur.at(0));
                }
                if (nombreDeJoueurs == 2 ){
                    ui->lineEditJoueur1->setText(PseudoJoueur.at(0));
                    ui->lineEditJoueur2->setText(PseudoJoueur.at(1));
                }

                if (nombreDeJoueurs == 3 ){
                    ui->lineEditJoueur1->setText(PseudoJoueur.at(0));
                    ui->lineEditJoueur2->setText(PseudoJoueur.at(1));
                    ui->lineEditJoueur3->setText(PseudoJoueur.at(2));
                }

                if (nombreDeJoueurs == 4 ){
                    ui->lineEditJoueur1->setText(PseudoJoueur.at(0));
                    ui->lineEditJoueur2->setText(PseudoJoueur.at(1));
                    ui->lineEditJoueur3->setText(PseudoJoueur.at(2));
                    ui->lineEditJoueur4->setText(PseudoJoueur.at(3));
                }

                break ;

            case 'Q':
                in>>coordonnees>>etatJoueur>>nombreDeJoueurs >> start;
                jeux->setListePositionsObjets(coordonnees);
               // qDebug() << nombreDeJoueurs ;
                if (nombreDeJoueurs == 1 ){
                    if(etatJoueur.at(0) == true){
                        ui->lineEditJoueur1->setStyleSheet("background-color: rgb(132, 227, 132);");
                    }
                    else{
                        ui->lineEditJoueur1->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }
                }
                if (nombreDeJoueurs == 2){

                    if(etatJoueur.at(0) == true){
                        ui->lineEditJoueur1->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur1->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }

                    if(etatJoueur.at(1) == true){
                        ui->lineEditJoueur2->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur2->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }
                }
                if (nombreDeJoueurs == 3 ){
                    if(etatJoueur.at(0) == true){
                        ui->lineEditJoueur1->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur1->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }

                    if(etatJoueur.at(1) == true){
                        ui->lineEditJoueur2->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur2->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }

                    if(etatJoueur.at(2) == true){
                        ui->lineEditJoueur3->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur3->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }
                }
                if (nombreDeJoueurs == 4 ){
                    if(etatJoueur.at(0) == true){
                        ui->lineEditJoueur1->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur1->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }

                    if(etatJoueur.at(1) == true){
                        ui->lineEditJoueur2->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur2->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }

                    if(etatJoueur.at(2) == true){
                        ui->lineEditJoueur3->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur3->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }

                    if(etatJoueur.at(3) == true){
                        ui->lineEditJoueur4->setStyleSheet("background-color: rgb(135, 227, 132);");
                    }else{
                        ui->lineEditJoueur4->setStyleSheet("background-color: rgb(227, 132, 132);");
                    }
                }
                if (start == true && jeux->getListePositionsObjets().size()>1){
                    this->hide();
                    jeux->show();
                    jeux->setStart(true);
                }
                break;


            case 'C' :
                in >> coordonnees ;

                //  qDebug() << coordonnees;
                jeux->setListePositionsObjets(coordonnees);

                break ;

            case 'V':
                in >> combo >>multiplicateurVitesse ;

                break ;
            case 'M':
                in>>musique;

                break ;
            case 'S' :
                in >> scoreJoueurs >> nombreDeJoueurs;
          //      qDebug() << "nb joueur:" << nombreDeJoueurs;
                qDebug() << "score case : " << scoreJoueurs.at(0);
                    jeux->setScore(scoreJoueurs);
                    jeux->setNbDeJoueurs(nombreDeJoueurs);
                break;

            case 'F' :
                in >> nombreDeJoueurs >> PseudoJoueur >> scoreJoueurs ;
                bidon->hide();
                resultat->show();

                resultat->setPseudoJoueur(PseudoJoueur);
                resultat->setNbDeJoueur(nombreDeJoueurs);
                resultat->setScoreJoueur(scoreJoueurs);
                break ;
            }
        }
    }
}


void GuitareHero_Client::onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError)
{
    qDebug()<<socketClient->errorString();
}


void GuitareHero_Client::on_pushButtonPret_clicked()
{
    if(ui->pushButtonPret->text()=="Pas Prêt"){
        ui->pushButtonPret->setText("Prêt");
        EnvoyerEtat(true);
    }
    else{
        ui->pushButtonPret->setText("Pas Prêt");
        EnvoyerEtat(false);
    }
}

void GuitareHero_Client::handleKeyPressed(int score)
{
   // qDebug() << "score send";

    quint16 taille=0;
    QBuffer tampon;
    QChar commande('S');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<score;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    // envoi du QByteArray du tampon via la socket
    socketClient->write(tampon.buffer());
}

void GuitareHero_Client::finDePartie(bool info)
{
    // qDebug() << "info send";

     quint16 taille=0;
     QBuffer tampon;
     QChar commande('F');
     tampon.open(QIODevice::WriteOnly);
     // association du tampon au flux de sortie
     QDataStream out(&tampon);
     // construction de la trame
     out<<taille<<commande<<info;
     // calcul de la taille de la trame
     taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
     // placement sur la premiere position du flux pour pouvoir modifier la taille
     tampon.seek(0);
     //modification de la trame avec la taille reel de la trame
     out<<taille;
     // envoi du QByteArray du tampon via la socket
     socketClient->write(tampon.buffer());
}

