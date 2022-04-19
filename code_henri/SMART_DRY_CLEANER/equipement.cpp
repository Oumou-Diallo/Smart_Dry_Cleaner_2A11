#include "equipement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QSqlDatabase>
#include <QDate>

#include <fstream>

using std::cout; using std::ofstream;
using std::endl; using std::string;
using std::fstream;

using namespace std;


equipement::equipement()
{
    id_eq=0;
    etat=" ";
    type_eq=" ";
    qte_eq=0;
}

equipement::equipement(int i,QString e,QString t,int q)
{
    this->id_eq = i;
    this->etat = e;
    this->type_eq = t;
    this->qte_eq = q;
}

int equipement::get_id_eq()
{    return id_eq;}

QString equipement::get_etat()
{   return etat; }

QString equipement::get_type()
{ return type_eq; }

int equipement::get_qte_eq()
{ return qte_eq; }

void equipement::set_id_eq(int i)
{ this->id_eq = i; }

void equipement::set_etat(QString e)
{ this->etat = e; }

void equipement::set_type_eq(QString t)
{ this->type_eq = t; }

void equipement::set_qte_eq(int q)
{ this->qte_eq = q; }

bool equipement::ajouter()
{
   /* QSqlQuery query;
    QString id_string= QString::number(id_eq);
    QString id_string2= QString::number(qte_eq);
         query.prepare("INSERT INTO EQUIPEMENT (ID_EQ, ETAT, TYPE_EQ , QTE_EQ) "
                       " values (:id_equipement,:etat,:type_equipement,:quantite_equipemnt");
         query.bindValue(":id_equipement", id_string);
         query.bindValue(":etat", etat);
         query.bindValue(":type_equipement", type_eq);
         query.bindValue(":quantite_equipemnt", id_string2);
         return query.exec();*/

    QSqlQuery query;
        QString id_string= QString::number(id_eq);
             query.prepare("INSERT INTO EQUIPEMENT (ID_EQ, ETAT, TYPE_EQ , QTE_EQ) "
                           " VALUES (:id_string,:etat,:type_eq,:qte_eq)");
             query.bindValue(0, id_string);
             query.bindValue(1, etat);
             query.bindValue(2, type_eq);
             query.bindValue(3, qte_eq);
             return query.exec();
}

bool equipement::modifier()
{
    QSqlQuery query;
    QString id_string= QString::number(id_eq);
    QString id_string2= QString::number(qte_eq);
         query.prepare("UPDATE EQUIPEMENT SET  ETAT=:ETAT, TYPE_EQ=:TYPE_EQ, QTE_EQ=:QTE_EQ WHERE ID_EQ=:ID_EQ");
         query.bindValue(":ID_EQ", id_string);
         query.bindValue(":QTE_EQ", id_string2);
         query.bindValue(":TYPE_EQ", type_eq);
         query.bindValue(":ETAT", etat);
         return query.exec();
}

bool equipement::supprimer(int id)
{
    QSqlQuery query;
         query.prepare("Delete from EQUIPEMENT where ID_EQ=:id_equipement");
         query.bindValue(":id_equipement", id);
         return query.exec();
}

QSqlQueryModel* equipement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM EQUIPEMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
    return model;


}

QSqlQueryModel* equipement::triParEtat(QString etat)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QString requete="SELECT * FROM EQUIPEMENT where ETAT=";
     requete+="'";
    requete+=etat;
    requete+="'";
          model->setQuery(requete);
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_eq"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("type_eq"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte_eq"));
    return model;

}
QSqlQueryModel* equipement::triParType(int type)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QString requete;
    switch (type) {
    case 1://cas uniquement savon lessive
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='savons lessive'";
        break;
    case 2://cas uniquement eau de javel
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='eau de javel'";
        break;
    case 3://cas uniquement machine a laver
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='machine a lave'";
        break;
    case 4://cas uniquement machine a repasser
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='machine a repasse'";
        break;

        //savon lessive
    case 5://cas savon lessive et eau de javel
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='savons lessive' or TYPE_EQ='eau de javel'";
        break;
    case 6:// cas savon lessive et machine a lave
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='savons lessive' or TYPE_EQ='machine a lave'";
        break;
    case 7://cas savon lessive et machine a repasser
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='savons lessive' or TYPE_EQ='machine a repasse'";
        break;

        //eaux de javel
    case 8://cas eau de javel et machine a lave
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='eau de javel' or TYPE_EQ='machine a lave'";
        break;
    case 9://cas eau de javel et machine a repasser
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='eau de javel' or TYPE_EQ='machine a repasse'";
        break;

        //machine a lave
    case 10://cas machine a lave et machine a repasser
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='machine a lave' or TYPE_EQ='machine a repasse'";
        break;

        //cas triples
    case 11://cas machine a lave et machine a repasser et eau de javel
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='machine a lave' or TYPE_EQ='machine a repasse' or TYPE_EQ='eau de javel'";
        break;
    case 12://cas savon lessive,eau de javel et machine a lave
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='savon lessive' or TYPE_EQ='eau de javel' or TYPE_EQ='machine a lave'";
        break;
    case 13://cas savon lessive,eau de javel et machine a repasser
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='savon lessive' or TYPE_EQ='eau de javel' or TYPE_EQ='machine a repasse'";
        break;
    case 14://cas savon lessive,machine a lave et machine a repasser
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='savon lessive' or TYPE_EQ='machine a lave' or TYPE_EQ='machine a repasse'";
        break;
    case 15://cas savon lessive,machine a lave et eau de javel
        requete="SELECT * FROM EQUIPEMENT where TYPE_EQ='savon lessive' or TYPE_EQ='machine a lave' or TYPE_EQ='eau de javel'";
        break;

    }
    /*QString requete="SELECT * FROM EQUIPEMENT where TYPE_EQ=";
     requete+="'";
    requete+=type_eq;
    requete+="'";*/
          model->setQuery(requete);
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_eq"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("type_eq"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte_eq"));
    return model;

}

QSqlQueryModel* equipement::statistique()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM EQUIPEMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_eq"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("type_eq"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte_eq"));
    return model;

}



QSqlQueryModel* equipement::rechercher(QString id_eq)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QString requete=("SELECT * FROM EQUIPEMENT where ID_EQ=");
         requete+="'";
        requete+=id_eq;
        requete+="";
          model->setQuery(requete);
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
    return model;
}


/*bool equipement::historique(std::string id,QString action)
{
    QString nomFichier("historique.txt");
    ofstream outfile(nomFichier.toStdString(),ios::app);
    QDate date;
    QString dateStr=date.currentDate().toString();



    if(action=="ajout")
    {
        outfile<<"-Ajout de l'equipement: "+id+" Date: "+dateStr.toStdString()+"\n";
    }
    else if(action=="modification")
    {
        outfile<<"-Modification de l'equipement: "+id+" Date: "+dateStr.toStdString()+"\n";
    }
    else if(action=="supression")
    {
        outfile<<"-Supression de l'equipement: "+id+" Date: "+dateStr.toStdString()+"\n";
    }
}
*/




