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

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();

    //metiers
    QSqlQueryModel* statistique();
    QSqlQueryModel* triParEtat(QString etat);
    QSqlQueryModel* triParType(int type_);

    QSqlQueryModel* rechercher(QString id_eq );
    bool historique(std::string id,QString action);

};

// public ::



// Private slots :

//Private :


#endif // EQUIPEMENT_H
