#include "article.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>

Article::Article()
{
    id_art="0";
    nom_art="";
        prix_art="0";
        type_art="";
}

Article::Article( QString nom_art, QString prix_art, QString type_art)
{
    this->nom_art=nom_art;
    this->prix_art=prix_art;
    this->type_art=type_art;
}

Article::Article(QString id_art, QString nom_art, QString prix_art, QString type_art)
{
    this->id_art=id_art;
    this->nom_art=nom_art;
    this->prix_art=prix_art;
    this->type_art=type_art;
}


QSqlQueryModel* Article::tri_identifiant()
{


    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM articles order by id_art ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
return model;

}


QSqlQueryModel* Article::tri_nom()
{


    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM articles order by nom_art ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
return model;

}


QSqlQueryModel* Article::tri_prix()
{


    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM articles order by prix_art ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
return model;

}


QSqlQueryModel* Article::tri_type()
{


    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM articles order by type_art ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
return model;

}
bool Article::chercher(QString id_art)
{
   QSqlQuery *query = new QSqlQuery;
   query->prepare("select id_art from articles where id_art='"+id_art+"'");
   if (query->exec())
   {

       while(query->next()){
                  auto chk = query->value(0).toString();
                  if(chk == id_art) return true;
               }

   }
   return false;

}

bool Article::modifier_art(){

    QSqlQuery query;

         query.prepare("UPDATE ARTICLES SET  NOM_ART=:NOM_ART, PRIX_ART=:PRIX_ART, TYPE_ART=:TYPE_ART WHERE ID_ART=:ID_ART");
         query.bindValue(":ID_ART", id_art);
         query.bindValue(":NOM_ART", nom_art);
         query.bindValue(":PRIX_ART", prix_art);
         query.bindValue(":TYPE_ART", type_art);

         return query.exec();
}

bool Article::supprimer(QString id_art)
{

                QSqlQuery query;

                query.prepare("Delete from Articles where id_art=:id_art");
                query.bindValue(0,id_art);
                return query.exec();

}
QSqlQueryModel * Article::Afficher()
{

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from Articles");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    return model;

}
bool Article::ajouter()
{

    QSqlQuery query;

           query.prepare("INSERT INTO Articles (id_art,NOM_art, PRIX_art,TYPE_art) "
                               "VALUES (:id_art,:nom_art, :prix_art, :type_art)");
           query.bindValue(":id_art", id_art);
           query.bindValue(":nom_art", nom_art);
           query.bindValue(":prix_art", prix_art);
           query.bindValue(":type_art", type_art);
   return query.exec();
}


QSqlQueryModel *Article::cherch(QString nom){


    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select  * from articles where id_art LIKE '%"+nom+"%' OR nom_art LIKE '%"+nom+"%' OR prix_art LIKE '%"+nom+"%' OR type_art LIKE '%"+nom+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
return model;


}
