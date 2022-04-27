#include "depense.h"
#include <QObject>
#include <QSqlQuery>
#include <QString>
#include <QtDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSqlError>

Depense::Depense()
{
id_dep=0;
type_dep=" ";
montant_dep="0";
date_dep =  QDate(2000, 7, 6);
}

Depense::Depense(int id_dep,QString type_dep,QString montant_dep,QDate date_dep)
{
    this->id_dep=id_dep;
    this->type_dep=type_dep;
    this->montant_dep=montant_dep;
    this->date_dep=date_dep;
  }


Depense::Depense(QString type_dep,QString montant_dep)
{

    this->type_dep=type_dep;
    this->montant_dep=montant_dep;
  }

    int Depense::getid_dep(){return id_dep;}
    QString Depense::gettype_dep(){return type_dep;}
    QString Depense::getmontant_dep(){return montant_dep;}
    QDate Depense::getdate_dep(){return date_dep;}
    void Depense::setid_dep(int id_dep){this->id_dep=id_dep;}
    void Depense::settype_dep(QString type_dep){this->type_dep=type_dep;}
    void Depense::setmontant_dep(QString montant_dep){this->montant_dep=montant_dep;}
    void Depense::setdate_dep(QDate date_dep){this->date_dep=date_dep;}
    bool Depense::ajouter()
    {
        QSqlQuery query;
        QString id_string=QString::number(id_dep);

                query.prepare("INSERT INTO dépense(id_dep,type_dep,montant_dep,date_dep)"
        "VALUES (:id_dep, :type_dep, :montant_dep, :date_dep)");
        query.bindValue(0,id_string);
        query.bindValue(1,type_dep);
        query.bindValue(2,montant_dep);
         query.bindValue(3,date_dep);
        return query.exec();


    }

    bool Depense::ajouter_historic_depense()
    {
        QSqlQuery query;
        QString id_string=QString::number(id_dep);
        QString option_dep="Ajouter";
                query.prepare("INSERT INTO historique_depense(id_dep,type_dep,montant_dep,date_dep,option_dep)"
        "VALUES (:id_dep, :type_dep, :montant_dep, :date_dep, :option_dep)");
        query.bindValue(0,id_string);
        query.bindValue(1,type_dep);
        query.bindValue(2,montant_dep);
        query.bindValue(3,QDate::currentDate());
        query.bindValue(4,option_dep);
        return query.exec();


    }

    bool Depense::modifier_historic_depense(int id,QString type,QString montant)
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


    bool Depense::supprimer_historic_depense(int id_dep)
    {


        QSqlQuery query,select;
        QString id_string=QString::number(id_dep);
        QString option_dep="Supprimer";
                select.prepare("SELECT id_dep, type_dep, montant_dep,date_dep FROM dépense where id_dep LIKE '"+id_string+"' ");

                 select.exec();

                QString idt=select.value(0).toString();
                QString typet=select.value(1).toString();
                QString montantt=select.value(2).toString();
               QDate datet=select.value(3).toDate();

                query.prepare("INSERT INTO historique_depense(id_dep,type_dep,montant_dep,date_dep,option_dep)"
        "VALUES (:idt, :typet, :montantt, :datet, :option_dep)");
        query.bindValue(0,idt);
        query.bindValue(1,typet);
        query.bindValue(2,montantt);
        query.bindValue(3,QDate::currentDate());
        query.bindValue(4,option_dep);
        return query.exec();

    }

    QSqlQueryModel * Depense::rechercher(int id_dep)
    {
        QString id_string=QString::number(id_dep);
        QSqlQueryModel * model=new QSqlQueryModel();
            model->setQuery("select * from dépense where id_dep like'%"+id_string+"%' ");

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_dep"));

            return model;

         }

    bool Depense::chercher(int id_dep)
     {
         QString id_string=QString::number(id_dep);
         QSqlQuery *query = new QSqlQuery;
        query->prepare("select id_dep from Dépense where id_dep='"+id_string+"'");
        if (query->exec())
        {

            while(query->next()){
                       auto chk = query->value(0).toString();
                       if(chk == id_string) return true;
                    }

        }
        return false;
     }


    bool Depense::chercher_c(QString type_dep)
     {

         QSqlQuery *query = new QSqlQuery;
        query->prepare("select type_dep from Dépense where type_dep=:type_dep");

        if (query->exec())
        {

            while(query->next()){
                       auto chk = query->value(1).toString();
                       if(chk == type_dep) return true;
                    }

        }
        return false;
     }



QSqlQueryModel* Depense::afficher()
{
    QSqlQueryModel* model= new QSqlQueryModel();

    model->setQuery("SELECT id_dep, type_dep, montant_dep, date_dep FROM dépense");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    return model;
}


QSqlQueryModel* Depense::tri_date()
{
    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT id_dep, type_dep, montant_dep, date_dep FROM dépense order by date_dep ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Montant"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
return model;}
QSqlQueryModel* Depense::tri_type()
{
    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT id_dep, type_dep, montant_dep, date_dep FROM dépense order by type_dep ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Montant"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
return model;
}

QSqlQueryModel* Depense::tri_identifiant()
{
    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT id_dep, type_dep, montant_dep, date_dep FROM dépense order by id_dep ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Montant"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
return model;
}

QSqlQueryModel* Depense::afficher_historique()
{
    QSqlQueryModel* model= new QSqlQueryModel();

    model->setQuery("SELECT id_dep, type_dep, montant_dep, date_dep FROM dépense ORDER BY date_dep DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    return model;
}

QSqlQueryModel* Depense::afficher_id()
{
    QSqlQueryModel* model= new QSqlQueryModel();

    model->setQuery("SELECT id_dep FROM dépense ORDER BY date_dep DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    return model;
}

QSqlQueryModel* Depense::afficher_calculer()
{


    QSqlQueryModel* model= new QSqlQueryModel();

    model->setQuery("SELECT montant_dep, date_dep FROM dépense where ");
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total des montants"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    return model;


}


bool Depense::supprimer(int id_dep)
{

                QSqlQuery query;

                query.prepare("Delete from dépense where id_dep=:id_dep");
                query.bindValue(0,id_dep);
                return query.exec();

}

QSqlQuery Depense::recuperer(int id_dep)
{

                QSqlQuery query;
                QString id_string=QString::number(id_dep);
                query.prepare("Select id_dep,type_dep,montant_dep,date_dep from dépense where id_dep=:id_string");
                query.bindValue(0,id_string);
                query.bindValue(1,type_dep);
                query.bindValue(2,montant_dep);
                query.bindValue(3,date_dep);
                return query;

}


