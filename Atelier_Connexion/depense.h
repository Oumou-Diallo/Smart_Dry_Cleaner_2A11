#ifndef DEPENSE_H
#define DEPENSE_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Depense
{
public:
    Depense();
    Depense(int,QString,QString,QDate);
    Depense(QString,QString);
    int getid_dep();
    QString gettype_dep();
    QString getmontant_dep();
    QDate getdate_dep();
    double get_total();
    void setid_dep(int);
    void settype_dep(QString);
    void setmontant_dep(QString);
    void setdate_dep(QDate);
    void set_total(double);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* historic_ajouter(int);
    QSqlQueryModel* tri_date();
    QSqlQueryModel* tri_type();
    QSqlQueryModel* tri_identifiant();
    QSqlQueryModel* afficher_historique();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* afficher_calculer();
    bool supprimer(int);
    QSqlQuery recuperer(int);
    bool modifier(int,QString,QString,QDateTime);
    bool chercher(int);
    bool chercher_c(QString);
    double calculer(QString);
    QSqlQueryModel * rechercher(int);
private :
    int id_dep;
    QString type_dep;
    QString montant_dep;
    QDate date_dep;
    double number;

};

#endif // DEPENSE_H
