#include "passgenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PassGenerator w;
    w.show();

    return a.exec();
}
