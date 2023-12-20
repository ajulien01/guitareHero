#ifndef SERVEUR_H
#define SERVEUR_H

#include <QWidget>
#include <QAbstractSocket>
#include <QTcpServer>
#include "client.h"

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

    void recupererPseudo();
    int getIndexClient(QTcpSocket *client);
private:
    Ui::Serveur *ui;
    QList<Client *> listeClients;
    QTcpServer *socketEcoute;

};
#endif // SERVEUR_H
