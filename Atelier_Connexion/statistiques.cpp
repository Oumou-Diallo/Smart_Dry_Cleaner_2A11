#include "statistiques.h"

statistiques::statistiques()
{

}

void statistiques::stat(QCustomPlot *customPlot)
{
    QSqlQuery query,query1;
    // set dark background gradient:
    QLinearGradient gradient(255, 255, 255, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->clearPlottables();
    customPlot->clearGraphs();
    customPlot->replot();

    customPlot->setBackground(QBrush(gradient));


    QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    fossil->setAntialiased(false);

    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("statistique du nombre d'articles des clients");
    fossil->setPen(QPen(QColor(200, 200, 50).lighter(170)));
    fossil->setBrush(QColor(200, 200, 50));

    QVector<double> ticks;
    QVector<QString> labels;
   /* query.prepare("SELECT COUNT(DISTINCT cin) FROM gs_personnel where age between 15 and 25");
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }*/
    query.prepare("SELECT COUNT(nbr_art) FROM client where service like '%'Detachage'%'");
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
    }

    query.prepare("SELECT COUNT(nbr_art) FROM client where service like '%'Nettoyage a sec'%'");
    query.exec();
    int deux;
    while(query.next())
    {
       deux=query.value(0).toInt();
    }
    query.prepare("SELECT COUNT(nbr_art) FROM client where service '%'Nettoyage a l'eau'%' ");
    query.exec();
    int trois;
    while(query.next())
    {
        trois=query.value(0).toInt();
    }

    query.prepare("SELECT COUNT(nbr_art) FROM client where service like '%'Repassage'%' ");
    query.exec();
    int quatre;
    while(query.next())
    {
        quatre=query.value(0).toInt();
    }

/*void Produit::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select QUANTITE from produit");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}*/



    ticks << 1 << 2 << 3 << 4;
    labels <<"Detachage"<< "Nettoyage a sec" << "Nettoyage a l'eau"<< "Repassage";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setLabel("Service");
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 8);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(255, 20, 0), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 20);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Nombre D'Articles ");
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    /*QVector<double> fossilData, nuclearData, regenData;
    fossilData  << un << deux << trois << quatre << cinq;
   // nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2<< 0.25*11.2;
    fossil->setData(ticks, fossilData);
  //  nuclear->setData(ticks, nuclearData);
 //   regen->setData(ticks, regenData);*/


   QVector<double> PlaceData;
              QSqlQuery q1("select nbr_art from client");
              while (q1.next()) {
                            int  nbr_fautee = q1.value(0).toInt();
                            PlaceData<< nbr_fautee;
                              }
              fossil->setData(ticks, PlaceData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = QFont();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}
