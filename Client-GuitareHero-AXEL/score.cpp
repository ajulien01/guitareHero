#include "score.h"
#include "ui_score.h"
#include "guitarehero_client.h"
#include "client.h"

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

void score::affichernom(QList <QString> PseudoJoueur)
{
/*
ui->labelNom1->setText(PseudoJoueur.at(0));
ui->labelNom2->setText(PseudoJoueur.at(1));
ui->labelNom3->setText(PseudoJoueur.at(2));
ui->labelNom4->setText(PseudoJoueur.at(3));
*/
}
