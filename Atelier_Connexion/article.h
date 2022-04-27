#ifndef ARTICLE_H
#define ARTICLE_H
#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlQueryModel>


class Article
{
public:
    Article();


       Article(QString,QString,QString);
       Article(QString,QString,QString,QString);

           QSqlQueryModel * Afficher();
           bool ajouter();
           bool supprimer(QString);
           bool modifier_art();
           bool chercher(QString);
           QSqlQueryModel* tri_identifiant();
           QSqlQueryModel* tri_nom();
           QSqlQueryModel* tri_prix();
           QSqlQueryModel* tri_type();
           QSqlQueryModel *cherch(QString);

private:


       QString id_art;
       QString prix_art;


         QString nom_art;
         QString type_art;
};


#endif // ARTICLE_H
