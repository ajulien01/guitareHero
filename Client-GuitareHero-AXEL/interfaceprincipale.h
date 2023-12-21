#ifndef INTERFACEPRINCIPALE_H
#define INTERFACEPRINCIPALE_H

#include <QWidget>
#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class InterfacePrincipale; }
QT_END_NAMESPACE

class InterfacePrincipale : public QWidget
{
    Q_OBJECT

private slots:
    void timerJeux();
    void timerVitesseDescente();
public:
     InterfacePrincipale(bool start = false ,QWidget *parent = nullptr);
    ~InterfacePrincipale();
    void keyPressEvent(QKeyEvent* event);
    void genererObjet();
    const QList<int> &getListePositionsObjets() const;
    void setListePositionsObjets(const QList<int> &newListePositionsObjets);

    bool getStart() const;
    void setStart(bool newStart);

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
    QTimer timer ;


    void actionTimer(); //
    void deplacerFormesVersLeBas();

    void verifierCoordonneesCarres();
    void verifierCoordonneesCercle();
    void verifierCoordonneesTriangle();
    void verifierCoordonneesLosange();
    int genererValeurAleatoire();
    int posCourante;
    bool start;


};

#endif // INTERFACEPRINCIPALE_H
