#include "interfaceprincipale.h"
#include "ui_interfaceprincipale.h"

#include <QRandomGenerator>

InterfacePrincipale::InterfacePrincipale(bool start , QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InterfacePrincipale)
{


    ui->setupUi(this);

    // Créer une scène de 600x600 pixels
    maScene = new QGraphicsScene();
    maVue = new QGraphicsView(this);
    maScene->setSceneRect(0, 0, 400, 600); // Définir la taille de la scène à 600x600 pixels

    //Dégradé
    QLinearGradient gradient(-15, 120, maVue->width(), maVue->height());
    gradient.setColorAt(1, QColor(255, 230, 230));
    gradient.setColorAt(0, QColor(200, 240, 255));
    maVue->setBackgroundBrush(QBrush(gradient));
    maVue->setScene(maScene);

    // Créer les lignes blanches
    int nombreLignes = 3;
    int distanceEntreLignes = 400 / (nombreLignes+1);
    for (int i = 1; i <= nombreLignes; ++i) {
        QGraphicsLineItem *ligne = new QGraphicsLineItem(i * distanceEntreLignes, 0, i * distanceEntreLignes, maVue->sceneRect().height());
        QPen pen(Qt::white);
        pen.setWidth(2);
        ligne->setPen(pen);
        maScene->addItem(ligne);
    }

    //ligne du bas
    int distanceDuBas = 100;
    QGraphicsLineItem *ligne = new QGraphicsLineItem(0, maVue->sceneRect().height() - distanceDuBas, maVue->sceneRect().width(), maVue->sceneRect().height() - distanceDuBas);
    QPen pen(Qt::white);
    pen.setWidth(2);
    ligne->setPen(pen);
    maScene->addItem(ligne);

    // Carré base
    int tailleCote = 50;
    QGraphicsRectItem *carre1 = new QGraphicsRectItem(25, maVue->sceneRect().height() - 75, tailleCote, tailleCote);
    carre1->setBrush(Qt::blue);
    maScene->addItem(carre1);

    // Cercle base
    QGraphicsEllipseItem *cercle2 = new QGraphicsEllipseItem(125, maVue->sceneRect().height() - 75, tailleCote, tailleCote);
    cercle2->setBrush(Qt::red);
    maScene->addItem(cercle2);

    // Triangle base
    QPolygonF trianglePolygon;
    trianglePolygon << QPointF(250, maVue->sceneRect().height() - 75)
                    << QPointF(275, maVue->sceneRect().height() - 25)
                    << QPointF(225, maVue->sceneRect().height() - 25);
    QGraphicsPolygonItem *triangle3 = new QGraphicsPolygonItem(trianglePolygon);
    triangle3->setBrush(Qt::green);
    maScene->addItem(triangle3);

    // Losange base
    QPolygonF losangePolygon;
    losangePolygon << QPointF(325, 550)
                   << QPointF(350, 575)
                   << QPointF(375, 550)
                   << QPointF(350, 525);

    QGraphicsPolygonItem *losange4 = new QGraphicsPolygonItem(losangePolygon);
    losange4->setBrush(Qt::yellow);
    maScene->addItem(losange4);

    maVue->setScene(maScene);
    maVue->show();
    posCourante=0;
    //son
    //son touche
    touche.setAudioOutput(&sortieAudioTouche);
    touche.setSource(QUrl("qrc:/sounds/ping.mp3")); //origine du fichier son
    sortieAudioTouche.setVolume(100);

    //son colision
    colision.setAudioOutput(&sortieAudioColision);
    colision.setSource(QUrl("qrc:/sounds/punch.mp3")); //origine du fichier son
    sortieAudioColision.setVolume(1);

    //son musique
    musique.setAudioOutput(&musiquefond);
    musique.setSource(QUrl("qrc:/sounds/lastchristmas.mp3")); //origine du fichier son
    musiquefond.setVolume(100);

    musique.play();
}

InterfacePrincipale::~InterfacePrincipale()
{
    delete ui;
}

int CarreZ = 50;
int CercleZ = 150;
int TriangleZ = 250;
int LosangeZ = 350;

void InterfacePrincipale::genererObjet()
{
    if (posCourante<listePositionsObjets.size())
    {
        int valeurAleatoire=listePositionsObjets.at(posCourante++); //= genererValeurAleatoire();
        QPoint center;

        if (valeurAleatoire == 1) {
            // Carré
            int tailleCote = 50;
            center = QPoint(static_cast<int>(CarreZ), -50);
            carre = new QGraphicsRectItem(center.x() - tailleCote/2, center.y() - tailleCote/2, tailleCote, tailleCote);
            carre->setBrush(Qt::blue);
            maScene->addItem(carre);
            objetsGeneres.append(carre);
        }
        if (valeurAleatoire == 2) {
            // Cercle
            int rayon = 25;
            center = QPoint(CercleZ, -50);
            cercle = new QGraphicsEllipseItem(center.x() - rayon, center.y() - rayon, rayon*2, rayon*2);
            cercle->setBrush(Qt::red);
            maScene->addItem(cercle);
            objetsGeneres.append(cercle);
        }
        if (valeurAleatoire == 3) {
            // Triangle
            center = QPoint(TriangleZ, -50);
            QPolygonF trianglePolygon;
            trianglePolygon << QPoint(center.x(), center.y() - 25)
                            << QPoint(center.x() + 25, center.y() + 25)
                            << QPoint(center.x() - 25, center.y() + 25);
            triangle = new QGraphicsPolygonItem(trianglePolygon);
            triangle->setBrush(Qt::green);
            maScene->addItem(triangle);
            objetsGeneres.append(triangle);
            triangle->setData(0, "Triangle"); //id triangle
        }
        if (valeurAleatoire == 4) {
            // Losange
            int tailleCote = 50;
            center = QPoint(LosangeZ, -50);
            QPolygonF losangePolygon;
            losangePolygon << QPoint(center.x(), center.y() - tailleCote/2)
                           << QPoint(center.x() + tailleCote/2, center.y())
                           << QPoint(center.x(), center.y() + tailleCote/2)
                           << QPoint(center.x() - tailleCote/2, center.y());
            losange = new QGraphicsPolygonItem(losangePolygon);
            losange->setBrush(Qt::yellow);
            maScene->addItem(losange);
            objetsGeneres.append(losange);
            losange->setData(0, "Losange");//id losange
        }

        maVue->setScene(maScene);
        maVue->show();
    }

}

const QList<int> &InterfacePrincipale::getListePositionsObjets() const
{
    return listePositionsObjets;
}

void InterfacePrincipale::setListePositionsObjets(const QList<int> &newListePositionsObjets)
{
    listePositionsObjets = newListePositionsObjets;
}

int InterfacePrincipale::verifierCoordonneesCarres()
{
    int point = 0 ;
    foreach (QGraphicsItem* item, objetsGeneres) {
        carre = dynamic_cast<QGraphicsRectItem*>(item);
        if (carre) {
            int positionX = carre->pos().x();
            int positionY = carre->pos().y();
            qDebug() << "Coordonnées du carré : (" << positionX << ", " << positionY << ")";
            if (positionY >= 595 && positionY <= 615) {
                qDebug() << "La coordonnée x du carré est entre 540 et 560.";
                maScene->removeItem(carre);
                // envoyer 1 avec signals
                point = 1 ;
                colisionSound();
            } else {
                qDebug() << "La coordonnée x du carré n'est pas entre 540 et 560.";
                toucheSound();
            }
        }
    }
    return point ;
}
int InterfacePrincipale::verifierCoordonneesCercle()
{
    int point = 0 ;
    foreach (QGraphicsItem* item, objetsGeneres) {
        cercle = dynamic_cast<QGraphicsEllipseItem*>(item);
        if (cercle) {
            int positionX = cercle->pos().x();
            int positionY = cercle->pos().y();
            qDebug() << "Coordonnées du cercle : (" << positionX << ", " << positionY << ")";
            if (positionY >= 595 && positionY <= 615) {
                qDebug() << "La coordonnée x du cercle est entre 540 et 560.";
                maScene->removeItem(cercle);
                // envoyer 1 avec signals
                colisionSound();
                point = 1 ;
            } else {
                qDebug() << "La coordonnée x du cercle n'est pas entre 540 et 560.";
                toucheSound();
            }
        }
    }
    return point ;
}
int InterfacePrincipale::verifierCoordonneesTriangle()
{
    int point = 0 ;
    foreach (QGraphicsItem* item, objetsGeneres) {
        triangle = dynamic_cast<QGraphicsPolygonItem*>(item);
        if (triangle && triangle->data(0) == "Triangle") {
            int positionX = triangle->pos().x();
            int positionY = triangle->pos().y();
            qDebug() << "Coordonnées du triangle : (" << positionX << ", " << positionY << ")";
            if (positionY >= 595 && positionY <= 615) {
                qDebug() << "La coordonnée x du triangle est entre 540 et 560.";
                maScene->removeItem(triangle);
                // envoyer 1 avec signals
                point = 1 ;
                colisionSound();
            } else {
                qDebug() << "La coordonnée x du triangle n'est pas entre 540 et 560.";
                toucheSound();
            }
        }
    }
    return point ;
}
int InterfacePrincipale::verifierCoordonneesLosange()
{
    int point = 0 ;
    foreach (QGraphicsItem* item, objetsGeneres) {
        losange = dynamic_cast<QGraphicsPolygonItem*>(item);
        if (losange && losange->data(0) == "Losange") {
            int positionX = losange->pos().x();
            int positionY = losange->pos().y();
            qDebug() << "Coordonnées du losange : (" << positionX << ", " << positionY << ")";
            if (positionY >= 595 && positionY <= 615) {
                qDebug() << "La coordonnée x du losange est entre 540 et 560.";
                maScene->removeItem(losange);
                // envoyer 1 avec signals
                point = 1 ;
                colisionSound();
            } else {
                qDebug() << "La coordonnée x du losange n'est pas entre 540 et 560.";
                toucheSound();
            }
        }
    }
    return point ;
}

void InterfacePrincipale::deplacerFormesVersLeBas()
{
    // Parcourir les objets générés et les déplacer d'un pixel vers le bas
    foreach (QGraphicsItem* item, objetsGeneres) {
        item->moveBy(0, 1);
        int positionY = item->pos().y();
        if(positionY>700){
            qDebug() << "Coordonnées du carré dépassé : (" << positionY << ")";
            item->hide();
            item->setPos(10,10);
            maScene->removeItem(item);
        }
    }

}

void InterfacePrincipale::keyPressEvent(QKeyEvent* event)
{
    int point = 0 ;
    switch (event->key()) {
    case Qt::Key_A:
        point = verifierCoordonneesCarres();
        break;
    case Qt::Key_Z:
        point = verifierCoordonneesCercle();
        break;
    case Qt::Key_E:
        point = verifierCoordonneesTriangle();
        break;
    case Qt::Key_R:
        point = verifierCoordonneesLosange();
        break;
        // Ajoutez d'autres cas pour les autres touches si nécessaire
    default:
        // Traitez les autres touches ici si nécessaire
        break;
    }

    emit keyPressed(point);
    initialiserScore();
}





int InterfacePrincipale::genererValeurAleatoire()//a enlever
{
    int valeurAleatoire = QRandomGenerator::global()->bounded(1, 5);
    qDebug() << "Valeur aléatoire : " << valeurAleatoire;//debug
    return valeurAleatoire;
}

bool InterfacePrincipale::getStart() const
{
    return start;
}

void InterfacePrincipale::setStart(bool newStart)
{
    start = newStart;
    if (start)
    {
        timerVitesseDescente();
        timerJeux();
    }
    else
    {
        timer.stop();
    }
}

const QList<int> &InterfacePrincipale::getScore() const
{
    return score;
}

void InterfacePrincipale::setScore(const QList<int> &newScore)
{
    score = newScore;
}

int InterfacePrincipale::getNbDeJoueurs() const
{
    return nbDeJoueurs;
}

void InterfacePrincipale::setNbDeJoueurs(int newNbDeJoueurs)
{
    nbDeJoueurs = newNbDeJoueurs;
    qDebug () << "Set nb joueur : " << nbDeJoueurs;
}

void InterfacePrincipale::toucheSound()
{
    touche.play();
}

void InterfacePrincipale::musiqueSound()
{
    musique.play();
}

void InterfacePrincipale::colisionSound()
{
    colision.play();
}

void InterfacePrincipale::initialiserScore()
{
    switch (nbDeJoueurs){

    case 1:
        ui->lcdNumberScoreJ1->display(score.at(0));
        break;
    case 2:
        ui->lcdNumberScoreJ1->display(score.at(0));
        ui->lcdNumberScoreJ2->display(score.at(1));
        break;
    case 3:
        ui->lcdNumberScoreJ1->display(score.at(0));
        ui->lcdNumberScoreJ2->display(score.at(1));
        ui->lcdNumberScoreJ3->display(score.at(2));
        break;
    case 4:
        ui->lcdNumberScoreJ1->display(score.at(0));
        ui->lcdNumberScoreJ2->display(score.at(1));
        ui->lcdNumberScoreJ3->display(score.at(2));
        ui->lcdNumberScoreJ4->display(score.at(3));

        break;
    }
}

void InterfacePrincipale::timerJeux()//a enlever
{
    // Crée un minuteur avec une durée de 1 seconde
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,&QTimer::timeout,this,&InterfacePrincipale::genererObjet);

    timer->start();
}

void InterfacePrincipale::timerVitesseDescente()//a enlever
{
    // Crée un minuteur avec une durée de 1 seconde
    QTimer* timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, &QTimer::timeout, this, &InterfacePrincipale::deplacerFormesVersLeBas);

    timer->start();
}
