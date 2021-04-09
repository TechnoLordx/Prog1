#include "areciboiablak.h"

AreciboAblak::AreciboAblak(int szelesseg, int magassag, std::string uzenet, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Arecibo");

    this->magassag = magassag;
    this->szelesseg = szelesseg;
    this->uzenet = uzenet;

    cellaSzelesseg = 12;
    cellaMagassag = 12;

    setFixedSize(QSize(szelesseg*cellaSzelesseg, magassag*cellaMagassag));

}

void AreciboAblak::paintEvent(QPaintEvent*) {
    QPainter qpainter(this);

    for(int i=0; i<magassag; ++i) {
        for(int j=0; j<szelesseg; ++j) {

            if(uzenet.at(i*szelesseg+j) == '1')
                qpainter.fillRect(j*cellaSzelesseg, i*cellaMagassag,
                                  cellaSzelesseg, cellaMagassag, Qt::black);
            else
                qpainter.fillRect(j*cellaSzelesseg, i*cellaMagassag,
                                  cellaSzelesseg, cellaMagassag, Qt::white);

            qpainter.setPen(QPen(Qt::gray, 1));
            qpainter.drawRect(j*cellaSzelesseg, i*cellaMagassag,
                              cellaSzelesseg, cellaMagassag);
        }
    }

    qpainter.end();
}

AreciboAblak::~AreciboAblak()
{
}
