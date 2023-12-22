#ifndef SCORE_H
#define SCORE_H

#include <QWidget>

namespace Ui {
class score;
}

class score : public QWidget
{
    Q_OBJECT

public:
    explicit score(QWidget *parent = nullptr);
    ~score();

    const QList<QString> &getPseudoJoueur() const;

    void setPseudoJoueur(const QList<QString> &newPseudoJoueur);

    const QList<int> &getScoreJoueur() const;
    void setScoreJoueur(const QList<int> &newScoreJoueur);

    int getNbDeJoueur() const;
    void setNbDeJoueur(int newNbDeJoueur);

private slots:
    void on_pushButton_clicked();

private:
    Ui::score *ui;
    QList <QString> pseudoJoueur;
    QList <int> scoreJoueur ;
    int nbDeJoueur ;

    void affichernom(QList<QString> PseudoJoueur, int nombreDeJoueurs);
    void afficherScore(QList<int> ScoreJoueur, int nombreDeJoueurs);
    void afficherVaiqueur(QList<QString> PseudoJoueur, QList<int> ScoreJoueur, int nombreDeJoueurs);

};

#endif // SCORE_H
