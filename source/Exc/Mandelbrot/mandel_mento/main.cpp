// main.cpp


#include <QApplication>
#include "frakablak.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    FrakAblak w1;
    w1.show();

    return a.exec();
}
