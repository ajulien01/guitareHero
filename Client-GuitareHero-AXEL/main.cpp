#include "guitarehero_client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuitareHero_Client w;
    w.show();
    return a.exec();
}
