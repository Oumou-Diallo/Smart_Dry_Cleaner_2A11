#ifndef GESTIONEQUIPEMENT_H
#define GESTIONEQUIPEMENT_H

#include <equipement.h>
#include <QMainWindow>
#include <QSqlDatabase>
#include "statistique.h"
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class gestionEquipement; }
QT_END_NAMESPACE

class gestionEquipement : public QMainWindow
{
    Q_OBJECT

public:
    gestionEquipement(QWidget *parent = nullptr);
    ~gestionEquipement();
    void notification();
     void Alert(int nb,QString nomProduit);

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_lineEdit_RS_editingFinished();

    void on_lineEdit_RS_textEdited(const QString &arg1);

    void on_Statistique_clicked();

    QSqlQueryModel* historic_modfication();
    QSqlQueryModel* historic_ajouter();


    void on_lineEdit_textEdited(const QString &arg1);

    //void on_tab_classement_activated(const QModelIndex &index);

    void update_label();

    void on_OUVRIR_clicked();

    void on_FERMER_clicked();

    //void on_state_windowIconTextChanged(const QString &iconText);

    //void on_input_push_clicked();
    //void on_spinBox_valueChanged(int arg1);


private:
    Ui::gestionEquipement *ui;
    equipement E;
    statistique S;
    QByteArray data; // variable contenant les données reçues
    Arduino A;
    int Seuil;
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

};
#endif // GESTIONEQUIPEMENT_H
