#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "depense.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include <QFontDialog>
#include <QSqlError>
#include <QDebug>
#include <QDoubleValidator>
#include <QSqlTableModel>
#include <QPrinter>
#include <QPrintDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ia->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_is->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_ma->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    ui->lineEdit_im->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_mm->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    ui->table_depense->setModel(D.afficher());
    ui->table_historique->setModel(D.afficher_historique());
    ui->t_depense->setModel(D.afficher_id());

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pb_ajouter_clicked()
{


    QString type_dep;


    int id_dep=ui->lineEdit_ia->text().toInt();
 if(ui->radioButton_sa->isChecked())
 {

  type_dep="Salaire";


 }

 if(ui->radioButton_ia->isChecked())
 {

  type_dep="Impot";


 }
 if(ui->radioButton_feta->isChecked())
 {

   type_dep="Frais d'entretien";


 }

 if(ui->radioButton_ra->isChecked())
 {

   type_dep="Remboursement";


 }

 if(ui->radioButton_feqa->isChecked())
 {

  type_dep="Frais d'equipement";


 }


   QString montant_dep=ui->lineEdit_ma->text();
   QDate date_dep=ui->dateEdit_a->date();
   Depense D(id_dep,type_dep,montant_dep,date_dep);
   bool test=D.ajouter();
   QMessageBox msgbox;

   if(test){
   msgbox.setText("ajout réussi");
   msgbox.exec();
   ui->table_depense->setModel(D.afficher());
    ui->t_depense->setModel(D.afficher_id());}
   else{
   msgbox.setText("echec de l'ajout");
   msgbox.exec();}

}

void MainWindow::on_pushButton_supprimer_clicked()
{


   Depense D1;
   D1.setid_dep(ui->lineEdit_is->text().toInt());

   QMessageBox msgbox;
   bool t=D1.chercher(ui->lineEdit_is->text().toInt());
   if(t)
   {bool test=D1.supprimer(D1.getid_dep());
       if(test==true){
       msgbox.setText("suppression réussie");
       msgbox.exec();
       ui->table_depense->setModel(D1.afficher());
        ui->t_depense->setModel(D.afficher_id());}
       else {
       msgbox.setText("echec de la suppression");
       msgbox.exec();
       }
}

   else
    {msgbox.setText("identifiant n'existe pas");
       msgbox.exec();}



}

void MainWindow::on_pushButton_modifier_clicked()
{    Depense D;
     QString type_dep;
     ui->t_depense->setModel(D.afficher_id());
     int id_dep=ui->lineEdit_im->text().toInt();
     if(ui->radioButton_sm->isChecked())
      {

       type_dep="Salaire";


      }

      if(ui->radioButton_im->isChecked())
      {

       type_dep="Impot";


      }
      if(ui->radioButton_fetm->isChecked())
      {

        type_dep="Frais d'entretien";


      }

      if(ui->radioButton_rm->isChecked())
      {

        type_dep="Remboursement";


      }

      if(ui->radioButton_feqm->isChecked())
      {

       type_dep="Frais d'equipement";


      }
/*

       qDebug()<<"pushButton_modifier";
            QSqlTableModel *model = new QSqlTableModel(this);
            model->setTable("id_dep");
            model->select();
            ui->table_depense->setModel(model);
            ui->table_depense->resizeColumnsToContents();
            ui->table_depense->setModel(D.afficher());

*/
      QString montant_dep=ui->lineEdit_mm->text();
      QDate date_dep=ui->dateEdit_m->date();
      QMessageBox msgbox;
      QSqlQuery query;
      QString id_string=QString::number(id_dep);
       bool t=D.chercher(ui->lineEdit_im->text().toInt());
       if(t)
       {  query.prepare("Update dépense set type_dep=:type_dep, montant_dep=:montant_dep , date_dep=:date_dep where id_dep=:id_string");
          query.bindValue(":id_string",id_string);
          query.bindValue(":type_dep",type_dep);
          query.bindValue(":montant_dep",montant_dep);
          query.bindValue(":date_dep",date_dep);
          query.exec();
           ui->table_depense->setModel(D.afficher());


            if(query.exec())
            {
                QMessageBox::critical(this,tr("Editer"),tr("Modifié"));
            }
            else
             {

              QMessageBox::critical(this,tr("erreur::"),query.lastError().text());

            }


    }

       else
        {msgbox.setText("identifiant n'existe pas");
           msgbox.exec();}


}

//void MainWindow::on_pushButton_calculer_clicked()

//{
  /*  double nombre;


    Depense D1;
   // D1.setdate_dep(ui->dateEdit_c->date());

    QMessageBox msgbox;
    QString type_dep;
    if(ui->radioButton_sc->isChecked())
     {

      type_dep="Salaire";


     }

     if(ui->radioButton_ic->isChecked())
     {

      type_dep="Impot";


     }
     if(ui->radioButton_fetc->isChecked())
     {

       type_dep="Frais d'entretien";


     }

     if(ui->radioButton_rc->isChecked())
     {

       type_dep="Remboursement";


     }

     if(ui->radioButton_feqc->isChecked())
     {

      type_dep="Frais d'equipement";


     }

    //bool t=D1.chercher_c(type_dep);
    //if(t)
   // {


       QLineEdit lineEdit_c;
       lineEdit_c->setText(D1.calculer(type_dep));
   */
//}

    //else
    /* {  msgbox.setText("Il n'y a aucune dépense correspondante à ce");
        msgbox.exec();}
*/


//}


double MainWindow :: getlineEditNum()
{

    num1=ui->lineEdit_num1->text().toDouble();
    num2=ui->lineEdit_num2->text().toDouble();

}

void MainWindow :: writeResult(double tempresult)
{

      ui->lineEdit_result->setText(QString :: number(tempresult));
      resultat=0;
}

void MainWindow::on_pushButton_plus_clicked()
{    getlineEditNum();
     resultat=num1+num2;
     writeResult(resultat);

}

void MainWindow::on_pushButton_moins_clicked()
{   getlineEditNum();
    resultat=num1-num2;
    writeResult(resultat);
}

void MainWindow::on_pushButton_fois_clicked()
{   getlineEditNum();
    resultat=num1*num2;
    writeResult(resultat);
}

void MainWindow::on_pushButton_diviser_clicked()
{   getlineEditNum();
    resultat=num1/num2;
    writeResult(resultat);
}



void MainWindow::on_actionNouveau_triggered()
{

    QMessageBox::information(this, "Titre", "Nouveau");



}

void MainWindow::on_actionOuvrir_triggered()
{
    QMessageBox::information(this, "Titre", "Ouvrir");

}

void MainWindow::on_actionSortir_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionImprimer_triggered()
{
     QPrinter printer;
     printer.setPrinterName("desierd printer name");
     QPrintDialog dialog(&printer,this);
     if(dialog.exec() == QDialog::Rejected) return;
     ui->textEdit->print(&printer);
}
