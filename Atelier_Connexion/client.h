#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQueryModel>


class Client
{
public:
    Client();
    Client(int,QString,QString,int,QString,int);
    int getid_cl();
    QString getnom();
    QString getprenoml();
    int gettel();
    int getnbrart();
    QString getservice();

    void setid_cl(int);
    void setnbrart(int);
    void setnom(QString);
    void setprenom(QString);
    void settel(int);
    void setservice(QString);
    bool chercher(int);
    bool ajouter();
    bool ModifierClient();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(QString);
    bool supprimer(int);
    QSqlQueryModel* TriCASC();
    QSqlQueryModel* TriCDESC();
    QSqlQueryModel* TriDASC();
    QSqlQueryModel* TriDDESC();
    QSqlQueryModel* TriEASC();
    QSqlQueryModel* TriEDESC();
    QSqlQueryModel *cherch(QString);
    QSqlQueryModel* tri_identifiant();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_service();

private:
    int id_cl,nbr_art;
    QString nom,prenom;
    int tel;
   QString service;
};

#endif // CLIENT_H
