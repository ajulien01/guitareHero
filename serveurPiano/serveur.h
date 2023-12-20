#ifndef SERVEUR_H
#define SERVEUR_H

#include <QWidget>
#include <QAbstractSocket>
#include <QTcpServer>
#include "client.h"
#define NBPOINT 2000

QT_BEGIN_NAMESPACE
namespace Ui { class Serveur; }
QT_END_NAMESPACE

class Serveur : public QWidget
{
    Q_OBJECT

public:
    Serveur(QWidget *parent = nullptr);
    ~Serveur();
private slots:
    void onQTcpSocket_connected();
    void onQTcpSocket_disconnected();
    void onQTcpSocket_readyRead();
    void onQTcpSocket_newConnection();
    void onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError);

    void on_pushButtonLancerServeur_clicked();
    float calculerScore(float newScore,int indexClient);
    void envoyerScore();
    void envoyerPseudo();
    void envoyerPret();
    int getIndexClient(QTcpSocket *client);
    int choixMusique();
    void envoyerMusique();
    //generateur de coordonnées
    int generValeurAleatoire();
    void envoyerCoordonnees();
    double vitesseJeux();

private:
    Ui::Serveur *ui;
    QList<Client *> listeClients;
    QTcpServer *socketEcoute;
    int nbJoueur=0;
    QTimer* timer;
    QList<int> valeurAleatoire;
};
#endif // SERVEUR_H
