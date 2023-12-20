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

private:
    float scoreJoueur;
    QString pseudo;
    QTcpSocket *sockClient;
    bool pret=false;

};

#endif // CLIENT_H
