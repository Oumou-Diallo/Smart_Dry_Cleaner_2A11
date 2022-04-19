#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include <iostream>



class equipement
{
private:
    int id_eq;
    QString etat;
    QString type_eq;
    int qte_eq;

public:
    equipement();
    equipement(int,QString,QString,int);

    int get_id_eq();
    QString get_etat();
    QString get_type();
    int get_qte_eq();


    void set_id_eq(int);
    void set_etat(QString);
    void set_type_eq(QString);
    void set_qte_eq(int);

    bool ajouter_eq();
    QSqlQueryModel* afficher_eq();
    bool supprimer_eq(int);
    bool modifier_eq();

    QSqlQueryModel *cherch_identifiant(int);
    QSqlQueryModel *cherch_type(QString);
    QSqlQueryModel *cherch_etat(QString);
    QSqlQueryModel* tri_identifiant();
    QSqlQueryModel* tri_type_eq();
    QSqlQueryModel* tri_qte_eq();
    QSqlQueryModel* tri_etat();

    QSqlQueryModel* rechercher(QString);

};

#endif // EQUIPEMENT_H
