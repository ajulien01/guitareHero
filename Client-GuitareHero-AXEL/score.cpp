#include "score.h"
#include "ui_score.h"

score::score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::score)
{
    ui->setupUi(this);
}

score::~score()
{
    delete ui;
}

const QList<QString> &score::getPseudoJoueur() const
{
    return pseudoJoueur;
}

void score::setPseudoJoueur(const QList<QString> &newPseudoJoueur)
{
    pseudoJoueur = newPseudoJoueur;
}

const QList<int> &score::getScoreJoueur() const
{
    return scoreJoueur;
}

void score::setScoreJoueur(const QList<int> &newScoreJoueur)
{
    scoreJoueur = newScoreJoueur;
}

int score::getNbDeJoueur() const
{
    return nbDeJoueur;
}

void score::setNbDeJoueur(int newNbDeJoueur)
{
    nbDeJoueur = newNbDeJoueur;
}

void score::affichernom(QList<QString> PseudoJoueur, int nombreDeJoueurs)
{
    if (nombreDeJoueurs >= 1)
    {
        ui->labelNom1->setText(PseudoJoueur.at(0));
    }

    if (nombreDeJoueurs >= 2)
    {
        ui->labelNom1->setText(PseudoJoueur.at(0));
        ui->labelNom2->setText(PseudoJoueur.at(1));
    }

    if (nombreDeJoueurs >= 3)
    {
        ui->labelNom1->setText(PseudoJoueur.at(0));
        ui->labelNom2->setText(PseudoJoueur.at(1));
        ui->labelNom3->setText(PseudoJoueur.at(2));
    }

    if (nombreDeJoueurs >= 4)
    {
        ui->labelNom1->setText(PseudoJoueur.at(0));
        ui->labelNom2->setText(PseudoJoueur.at(1));
        ui->labelNom3->setText(PseudoJoueur.at(2));
        ui->labelNom4->setText(PseudoJoueur.at(3));
    }
}

void score::afficherScore(QList<int> ScoreJoueur, int nombreDeJoueurs)
{
    if (nombreDeJoueurs >= 1)
    {
        ui->lcdNumberScoreJ1->display(ScoreJoueur.at(0));
    }

    if (nombreDeJoueurs >= 2)
    {
        ui->lcdNumberScoreJ1->display(ScoreJoueur.at(0));
        ui->lcdNumberScoreJ2->display(ScoreJoueur.at(1));

    }

    if (nombreDeJoueurs >= 3)
    {
        ui->lcdNumberScoreJ1->display(ScoreJoueur.at(0));
        ui->lcdNumberScoreJ2->display(ScoreJoueur.at(1));
        ui->lcdNumberScoreJ3->display(ScoreJoueur.at(2));
    }

    if (nombreDeJoueurs >= 4)
    {
        ui->lcdNumberScoreJ1->display(ScoreJoueur.at(0));
        ui->lcdNumberScoreJ2->display(ScoreJoueur.at(1));
        ui->lcdNumberScoreJ3->display(ScoreJoueur.at(2));
        ui->lcdNumberScoreJ4->display(ScoreJoueur.at(3));
    }

}

void score::afficherVaiqueur(QList<QString> PseudoJoueur, QList<int> ScoreJoueur, int nombreDeJoueurs)
{
int meilleurScore ;
int numeroDuVainqueur = 0 ;
meilleurScore = ScoreJoueur.at(0);
for(int i= 1 ; i<nombreDeJoueurs; i++){
    if(meilleurScore<ScoreJoueur.at(i)){
        meilleurScore = ScoreJoueur.at(i);
        numeroDuVainqueur = i ;
    }
}
ui->labelNomVainqueur->setText(PseudoJoueur.at(numeroDuVainqueur));

}

void score::on_pushButton_clicked()
{
    afficherScore(scoreJoueur,nbDeJoueur);
    afficherVaiqueur(pseudoJoueur,scoreJoueur,nbDeJoueur);
    affichernom(pseudoJoueur,nbDeJoueur);
}

