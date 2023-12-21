#ifndef GUITAREHERO_CLIENT_H
#define GUITAREHERO_CLIENT_H

#include "client.h"
#define TAILLE 20

#include <QWidget>
#include <QTcpSocket>
#include <interfaceprincipale.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GuitareHero_Client; }
QT_END_NAMESPACE

class GuitareHero_Client : public QWidget
{
    Q_OBJECT

public:
    GuitareHero_Client(QWidget *parent = nullptr);
    ~GuitareHero_Client();
    void EnvoyerPseudo();
    void EnvoyerEtat(bool pret);

private slots:
    void on_pushButtonConnexion_clicked();
    void onQTcpSocket_connected();
    void onQTcpSocket_disconnected();
    void onQTcpSocket_readyRead();
    void onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError);

    void on_pushButtonPret_clicked();

    void handleKeyPressed(int score);

private:
    Ui::GuitareHero_Client *ui;
    QTcpSocket *socketClient;
    QList <Client> joueur;
    QString pseudo;
    QString etat;
    InterfacePrincipale * jeux;
};
#endif // GUITAREHERO_CLIENT_H
