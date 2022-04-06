#ifndef ARTICLE_H
#define ARTICLE_H
#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlQueryModel>


class Article
{
public:
    Article();
   Article(QString,int,QString);
   Article(int,QString,int,QString);

       bool ajouter();
       bool archiver();
       bool desArchiver(int);
       bool ajouterHistorique(QString);
      QSqlQueryModel * Afficher();
      QSqlQueryModel * AfficherArchive();
      QSqlQueryModel * historique();
      QSqlQueryModel * triNom();
      QSqlQueryModel * triPrix();
      QSqlQueryModel * triType();
       bool supprimer(int );
    QSqlQueryModel * cherch_art(QString);
       bool modifier(int , QString  );



   private:

       int id;
       int prix;


         QString nom;
         QString type;



};

#endif // ARTICLE_H
