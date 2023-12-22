#ifndef INTERFACEPRINCIPALE_H
#define INTERFACEPRINCIPALE_H

#include <QWidget>
#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class InterfacePrincipale; }
QT_END_NAMESPACE

class InterfacePrincipale : public QWidget
{
    Q_OBJECT

private slots:
    void timerJeux();
    void timerVitesseDescente();
    void stopTimer();
public:
     InterfacePrincipale(bool start = false ,QWidget *parent = nullptr);
    ~InterfacePrincipale();
    void keyPressEvent(QKeyEvent* event);
    void genererObjet();
    const QList<int> &getListePositionsObjets() const;
    void setListePositionsObjets(const QList<int> &newListePositionsObjets);

    bool getStart() const;
    void setStart(bool newStart);

    const QList<int> &getScore() const;

    void setScore(const QList<int> &newScore);

    int getNbDeJoueurs() const;

    void setNbDeJoueurs(int newNbDeJoueurs);
    //son
    void toucheSound();
    void colisionSound();
    void musiqueSound();
private:
    Ui::InterfacePrincipale *ui;
    QGraphicsScene *maScene;
    QGraphicsView *maVue;
    QGraphicsRectItem* carre;
    QGraphicsEllipseItem* cercle;
    QGraphicsPolygonItem* triangle;
    QGraphicsPolygonItem *losange;
    QList<QGraphicsItem*> objetsGeneres;
    QList<int> listePositionsObjets;
    QList<int> score;
    int nbDeJoueurs ;
    QTimer timer ;
    void initialiserScore();


    void actionTimer(); //
    void deplacerFormesVersLeBas();

    int  verifierCoordonneesCarres();
    int verifierCoordonneesCercle();
    int verifierCoordonneesTriangle();
    int verifierCoordonneesLosange();
    int genererValeurAleatoire();
    int posCourante;
    bool start;
    //son
    QMediaPlayer touche;
    QAudioOutput sortieAudioTouche;
    QMediaPlayer colision;
    QAudioOutput sortieAudioColision;
    QMediaPlayer musique;
    QAudioOutput musiquefond;
signals:
        void keyPressed(int score);
        void finDePartie(bool timeout);


};

#endif // INTERFACEPRINCIPALE_H
