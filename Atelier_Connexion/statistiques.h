#ifndef STATISTIQUES_H
#define STATISTIQUES_H
#include <qcustomplot.h>
#include <QSqlQuery>
#include "client.h"

class statistiques
{
public:
    statistiques();

    void stat(QCustomPlot*);
};

#endif // STATISTIQUES_H
