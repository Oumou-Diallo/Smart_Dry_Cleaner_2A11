#include "equipement.h"
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

bool equipement::ajouter_eq()
{
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


bool equipement::ajouter_historic_equipement()
{
/*
    QSqlQuery query;
    QString id_string=QString::number(id_eq);
    QString option_dep="Ajouter";
            query.prepare("INSERT INTO historique_equipement(id_eq,etat,prix_eq,type_eq,date_eq,option_eq)"
    "VALUES (:id_eq,:etat,:prix_eq, :type_eq,:date_dep, :option_dep)");
    query.bindValue(0,id_string);
    //query.bindValue(1,_etat);
    query.bindValue(2,montant_dep);
    query.bindValue(3,QDate::currentDate());
    query.bindValue(4,option_dep);
    return query.exec();*/


}
/*bool equipement::modifier_historic_depense(int,QString,QString)
{

    QSqlQuery query;
    QString id_string=QString::number(id);
    QString option_dep="Modifier";
            query.prepare("INSERT INTO historique_depense(id_dep,type_dep,montant_dep,date_dep,option_dep)"
    "VALUES (:id, :type, :montant, :date, :option_dep)");
    query.bindValue(0,id_string);
    query.bindValue(1,type);
    query.bindValue(2,montant);
    query.bindValue(3,QDate::currentDate());
    query.bindValue(4,option_dep);
    return query.exec();




}
*/
QSqlQueryModel* equipement::afficher_eq()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM EQUIPEMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantite"));
    return model;


}

bool equipement::modifier_eq()
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


bool equipement::chercher(QString id)
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select id_eq from EQUIPEMENT where id_eq='"+id+"'");
    if (query->exec())
    {

        while(query->next()){
                   auto chk = query->value(0).toString();
                   if(chk == id)
                       return true;
                }

    }
    return false;

}

bool equipement::supprimer_eq(int id_eq)
{
    QSqlQuery query;
         query.prepare("Delete from EQUIPEMENT where ID_EQ=:id_eq");
         query.bindValue(":id_eq", id_eq);
         return query.exec();
}


QSqlQueryModel *equipement::cherch_identifiant(int id_eq)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString id_string= QString::number(id_eq);
        model->setQuery("select  * from equipement where id_eq LIKE '%"+id_string+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
return model;
}


QSqlQueryModel *equipement::cherch_type(QString nom)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select  * from equipement where type_eq LIKE '%"+nom+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
return model;
}


QSqlQueryModel *equipement::cherch_etat(QString nom)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select  * from equipement where etat LIKE '%"+nom+"%' OR type_eq LIKE '%"+nom+"%' OR id_eq LIKE '%"+nom+"%' OR qte_eq LIKE '%"+nom+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantite"));
return model;
}


QSqlQueryModel* equipement::tri_identifiant()
{
    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM equipement order by id_eq ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantite"));
return model;
}



QSqlQueryModel* equipement::tri_etat()
{
    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM equipement order by etat ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantite"));
return model;
}

QSqlQueryModel* equipement::tri_type_eq()
{
    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM equipement order by type_eq ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantite"));
return model;
}


QSqlQueryModel* equipement::tri_qte_eq()
{
    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM equipement order by qte_eq ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantite"));
return model;
}

QSqlQueryModel* equipement::rechercher(QString nom)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString id_string= QString::number(id_eq);
            model->setQuery("select  * from equipement where '" +nom+"' LIKE '%"+id_string+"%' OR  '" +nom+"' LIKE '%"+type_eq+"%' OR '" +nom+"' LIKE '%"+qte_eq+"%' OR '" +nom+"' LIKE '%"+etat+"%'");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantite"));

    return model;
}

