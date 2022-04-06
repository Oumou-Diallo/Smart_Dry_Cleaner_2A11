#include "article.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
Article::Article()
{
id=0;
nom="";
    prix=0;
    type="";
}

Article::Article( QString nom, int prix, QString type)
{
    this->nom=nom;
    this->prix=prix;
    this->type=type;
}

Article::Article(int id, QString nom, int prix, QString type)
{
    this->id=id;
    this->nom=nom;
    this->prix=prix;
    this->type=type;
}



bool Article::ajouter()
{
    QSqlQuery query;

        query.prepare("INSERT INTO Articles (NOM, PRIX,TYPE) "
                            "VALUES (:nom, :prix, :type)");
        query.bindValue(":nom", nom);
        query.bindValue(":prix", prix);
        query.bindValue(":type", type);
return query.exec();
}

bool Article::archiver()
{
    QSqlQuery query;

        query.prepare("INSERT INTO Articles_archives (NOM, PRIX,TYPE) "
                            "VALUES (:nom, :prix, :type)");
        query.bindValue(":nom", nom);
        query.bindValue(":prix", prix);
        query.bindValue(":type", type);
return query.exec();
}

bool Article::ajouterHistorique(QString op)
{
    QSqlQuery query;

        query.prepare("INSERT INTO HISTORIQUE (NOM, DATE_OP) "
                            "VALUES (:nom, :date)");
        query.bindValue(":nom", op);
        query.bindValue(":date", QDateTime::currentDateTime());
return query.exec();
}

bool Article::supprimer(int num)
{
    QSqlQuery query;
    query.prepare("Delete from ARTICLES where ID = :num ");
    query.bindValue(":num", num);
return    query.exec();
}

bool Article::desArchiver(int num)
{
    QSqlQuery query;
    query.prepare("Delete from ARTICLES_archives where ID = :num ");
    query.bindValue(":num", num);
return    query.exec();
}

QSqlQueryModel * Article::Afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from Articles");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
return model;
}

QSqlQueryModel * Article::AfficherArchive()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from Articles_archives");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
return model;
}

QSqlQueryModel * Article::historique()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from HISTORIQUE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
return model;
}

QSqlQueryModel * Article::triNom()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from Articles ORDER BY NOM");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
return model;
}

QSqlQueryModel * Article::triPrix()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from Articles ORDER BY PRIX");
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
return model;
}

QSqlQueryModel * Article::triType()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from Articles ORDER BY TYPE");
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
return model;
}

QSqlQueryModel *Article::cherch_art(QString nom)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select  * from Articles where NOM LIKE '%"+nom+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
return model;
}
bool Article::modifier(int id ,QString nom)
{
    QSqlQuery query ;
    query.prepare("update Articles set nom=:nom  where id= :id");
    query.bindValue(":nom", nom);
    query.bindValue(":id", id);
return query.exec();
}



