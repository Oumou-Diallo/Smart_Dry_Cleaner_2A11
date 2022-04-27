#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Client::Client()
{
    id_cl=0;
    nom="";
    prenom="";
    tel=0;
    service="";
    nbr_art=0;


}
bool Client::chercher(int)
{

    QString id_string=QString::number(id_cl);
    QSqlQuery *query = new QSqlQuery;
   query->prepare("select id_cl from Client where id_cl='"+id_string+"'");
   if (query->exec())
   {

       while(query->next()){
                  auto chk = query->value(0).toString();
                  if(chk == id_string) return true;
               }

   }
   return false;


}
Client::Client(int id_cl,QString nom,QString prenom,int tel,QString service,int nbr_art){
    this->id_cl=id_cl ; this->nom=nom ; this->prenom=prenom ; this->tel=tel ; this->service=service ;
    this->nbr_art=nbr_art ;
}
int Client::getid_cl(){return id_cl;}
int Client::getnbrart(){return nbr_art;}
QString Client::getnom(){return nom;}
QString Client::getprenoml(){return prenom;}
int Client::gettel(){return tel;}
QString Client::getservice(){return service;}

void Client::setid_cl(int id_cl){this->id_cl=id_cl ;}
void Client::setnbrart(int nbr_art){this->nbr_art=nbr_art ;}
void Client::setnom(QString nom){this->nom=nom ;}
void Client::setprenom(QString prenom){this->prenom=prenom ;}
void Client::settel(int tel){this->tel=tel ;}
void Client::setservice(QString service){this->service=service ;}
bool Client::ajouter(){

    QSqlQuery query;
    QString id_string= QString::number(id_cl);
    QString tel_string= QString::number(tel);

         query.prepare("INSERT INTO Client (id_cl, nom, prenom, tel, service,nbr_art) "
                       "VALUES (:id_cl, :nom, :prenom, :tel, :service,:nbr_art)");
         query.bindValue(":id_cl", id_string);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":tel", tel_string);
         query.bindValue(":service", service);
         query.bindValue(":nbr_art", nbr_art);

         return query.exec();
}
bool Client::supprimer(int id_cl){
    QSqlQuery query;
        QString res=QString::number(id_cl);
         query.prepare("DELETE FROM Client WHERE id_cl=:id_cl ");
         query.bindValue(":id_cl",res);
         return query.exec();
}



QSqlQueryModel *Client::cherch(QString nom)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select  * from client where id_cl LIKE '%"+nom+"%' OR tel LIKE '%"+nom+"%'  OR service LIKE '%"+nom+"%' OR nom LIKE '%"+nom+"%' OR prenom LIKE '%"+nom+"%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Service"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre D'Articles"));
return model;
}

QSqlQueryModel* Client::tri_identifiant()
{

    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM client order by id_cl ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Service"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre D'Articles"));

return model;


}

QSqlQueryModel* Client::tri_nom()
{

    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM client order by nom ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Service"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre D'Articles"));

return model;


}


QSqlQueryModel* Client::tri_service()
{

    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT * FROM client order by service ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Service"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre D'Articles"));
return model;


}

QSqlQueryModel* Client::afficher(){
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM Client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Service"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre D'Articles"));


    return model;
}
bool Client::ModifierClient()
{
       QSqlQuery query;
       QString id_string=QString::number(id_cl);
       QString tel_string= QString::number(tel);


       query.prepare(" UPDATE Client set id_cl = :id_cl ,nom = :nom,prenom = :prenom,tel = :tel,service = :service ,nbr_art=:nbr_art WHERE  id_cl = :id_cl");
                          query.bindValue(":id_cl", id_string);
                          query.bindValue(":nom", nom);
                          query.bindValue(":prenom", prenom);
                          query.bindValue(":tel", tel_string);
                          query.bindValue(":service", service);
                          query.bindValue(":nbr_art", nbr_art);

                         return query.exec();




}
QSqlQueryModel * Client::rechercher(QString a)
{

    QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("select * from Client where id_cl like'%"+a+"%' OR tel like '%"+a+"%' OR prenom like '%"+a+"%' OR nom like '%"+a+"%'OR service like '%"+a+"%' ");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Service"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre D'Articles"));

        return model;



     }
QSqlQueryModel* Client::TriCASC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT* FROM Client ORDER BY nom ASC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("service"));
  return  model;
}
QSqlQueryModel* Client::TriCDESC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT* FROM Client ORDER BY nom DESC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("service"));
  return  model;
}
QSqlQueryModel* Client::TriDASC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT* FROM Client ORDER BY prenom ASC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("service"));
  return  model;
}
QSqlQueryModel* Client::TriDDESC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT* FROM Client ORDER BY prenom DESC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("service"));
  return  model;
}
QSqlQueryModel* Client::TriEASC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT* FROM Client ORDER BY service ASC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("service"));
  return  model;
}
QSqlQueryModel* Client::TriEDESC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT* FROM Client ORDER BY service DESC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("service"));
  return  model;
}

