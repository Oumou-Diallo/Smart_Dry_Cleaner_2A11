#ifndef STATISTIQUE_H
#define STATISTIQUE_H
#include <qcustomplot.h>
#include <QSqlQuery>
#include "equipement.h"

class statistique
{
public:
    statistique();
    void stat(QCustomPlot*);
};

#endif // STATISTIQUE_H
