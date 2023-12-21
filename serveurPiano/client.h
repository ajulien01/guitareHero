#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>

class Client
{
public:
    Client();
    float getScoreJoueur() const;
    void setScoreJoueur(float newScoreJoueur);
    const QString &getPseudo() const;
    void setPseudo(const QString &newPseudo);
    void setSockClient(QTcpSocket *newSockClient);
    QTcpSocket *getSockClient() const;
    bool getPret() const;
    void setPret(bool newPret);

    int getCombo() const;
    void setCombo(int newCombo);

private:
    float scoreJoueur=0;
    QString pseudo;
    QTcpSocket *sockClient;
    bool pret=false;
    int combo;
    int vitesse = 1000;//vitesse par defaut pour le timer 1 sec

};

#endif // CLIENT_H
