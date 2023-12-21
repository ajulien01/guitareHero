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

private:
    Ui::score *ui;
    void affichernom(QList <QString> PseudoJoueur);
};

#endif // SCORE_H
