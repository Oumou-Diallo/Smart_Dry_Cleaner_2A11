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
#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QPrintDialog>
#include <QDate>
#include <QDateEdit>
#include <QDateTime>
#include <iostream>
#include <cstdlib>
#include <QCursor>
#include <qtextcursor.h>

double calcval = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    cbox=new QComboBox;
    qButton = new QPushButton;
    sBox = new QSpinBox;
    tEdit = new QTextEdit;
    Hlay = new QHBoxLayout;

    ui->setupUi(this);
    ui->Display->setText(QString::number(calcval));
    QPushButton * numbuttons[10];
    for(int i = 0; i < 10; ++i){

        QString butName = "button_" + QString::number(i);
        numbuttons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numbuttons[i], SIGNAL(released()), this, SLOT(NumPressed()));

    }

    connect(ui->addition, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->soustraction, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->division, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->multiplication, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->egal, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->change_signe, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->clear, SIGNAL(released()), this, SLOT(Clear()));


    ui->lineEdit_ia->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_is->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_ma->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    ui->lineEdit_im->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_mm->setValidator(new QDoubleValidator(-999.0,999.0,2,this));



    ui->t_depense->setModel(D.afficher_id());

   ui->table_depense->setModel(D.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writetofile()
{

    QString fname = "D:\\Qt\\Qt5.";


}

QSqlQueryModel* MainWindow::historic_ajouter(int id_dep)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString id_string=QString::number(id_dep);
    model->setQuery("SELECT sysdate,id_dep,type_dep,montant_dep,date_dep FROM dépense ORDER BY SYSDATE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Effectué le"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    return model;
}

QSqlQueryModel* MainWindow::historic_modifier(int id)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString id_string=QString::number(id);
    model->setQuery("SELECT sysdate,id_dep,type_dep,montant_dep,date_dep FROM dépense ORDER BY SYSDATE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Effectué le"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    return model;
}


void MainWindow::NumPressed()
{

    QPushButton * button=(QPushButton *)sender();
    QString butval= button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble()==0)||(displayVal.toDouble()==0.0))
    {
       ui ->Display->setText(butval);
    }
    else
    {

        QString newVal = displayVal + butval;
        double dbNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dbNewVal, 'g', 16));

    }

}

void MainWindow::Clear()
{

       ui->Display->clear();
       ui->Display->clear();

}

void MainWindow::MathButtonPressed()
{

    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcval = displayVal.toDouble();
    QPushButton * button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive)==0)
    {
        divTrigger = true;

    }

    else
        if(QString::compare(butVal, "x", Qt::CaseInsensitive)==0)
     {
         multTrigger = true;

    }


        else
            if(QString::compare(butVal, "+", Qt::CaseInsensitive)==0)
         {
             addTrigger = true;

        }


            else
                if(QString::compare(butVal, "-", Qt::CaseInsensitive)==0)
             {
                 subTrigger = true;

            }
    ui->Display->setText("");
}

void MainWindow::EqualButton()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dbDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcval + dbDisplayVal;
        }
        else
            if(subTrigger){
                solution = calcval - dbDisplayVal;
            }
        else
        if(multTrigger){
            solution = calcval * dbDisplayVal;
        }
        else
            if(divTrigger){
                solution = calcval / dbDisplayVal;
            }

    }
    ui->Display->setText(QString::number(solution));
}

void MainWindow::ChangeNumberSign()
{

QString displayVal = ui->Display->text();
QRegExp reg("[-]?[0-9.]*");
if(reg.exactMatch(displayVal)){

    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = -1 * dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign));


}



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
    ui->t_depense->setModel(D.afficher_id());
    ui->table_ha->setModel(historic_ajouter(id_dep));

    }
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
   QSqlQuery q=D1.recuperer(ui->lineEdit_is->text().toInt());

   QString mfilename = "C:/Users/HP/Downloads/Atelier_Connexion_oumou/Atelier_Connexion/build-Atelier_Connexion-Desktop_Qt_5_9_9_MinGW_32bit-Debug/historique.txt";
   QString date_dep=q.value(3).toString();
  // QString type_dep=q.value(1);
  // QString montant_dep=q.value(2);
  // int id_dep=ui->lineEdit_is->text().toInt();
  // Write_supprimer(mfilename,id_dep,type_dep,montant_dep,date_dep);

  // Read_supprimer(mfilename);
    //ui->table_hs->setModel(historic_supprimer(ui->lineEdit_is->text().toInt()));
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

QSqlQueryModel* MainWindow::historic_supprimer(int id)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString id_string=QString::number(id);
    model->setQuery("SELECT sysdate,id_dep FROM dépense");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Effectué le"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    return model;
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
           ui->table_hm->setModel(historic_modifier(ui->lineEdit_im->text().toInt()));

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

void MainWindow::Write_modifier(QString Filename,int id, QString type, QString montant, QString dated)
{

QFile mFile(Filename);
if(!mFile.open(QFile::WriteOnly| QFile::Text))
{
    qDebug() <<"ne peut pas ouvrir le fichier pour l'écriture";
    return;

}

QTextStream out(&mFile);

out <<"Modifier::     " <<"Identifiant     "<<"Type                 "<<"Montant     "<<"Date     " ;
out <<"\n" ;
out <<"                    " <<id          <<"             "  <<type   <<"     "    <<montant     <<"           "<<dated;
out <<"\n" ;
out <<"                    " <<id          <<"             "  <<type   <<"     "    <<montant     <<"           "<<dated;

mFile.flush();
mFile.close();

}

void MainWindow::Read_modifier(QString Filename)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::ReadOnly| QFile::Text))
    {
        qDebug() <<"ne peut pas ouvrir le fichier pour la lecture";
        return;

    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    qDebug() <<mText;

    mFile.close();
}


void MainWindow::Write_ajouter(QString Filename,int id, QString type, QString montant, QString dated)
{

QFile mFile(Filename);
if(!mFile.open(QFile::WriteOnly| QFile::Text))
{
    qDebug() <<"ne peut pas ouvrir le fichier pour l'écriture";
    return;

}

QTextStream out(&mFile);

out <<"Ajouter::     " <<"Identifiant     "<<"Type                 "<<"Montant     "<<"Date     " ;
out <<"\n" ;
out <<"                    " <<id          <<"             "  <<type   <<"     "    <<montant     <<"           "<<dated;
mFile.flush();
mFile.close();
}

void MainWindow::Read_ajouter(QString Filename)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::ReadOnly| QFile::Text))
    {
        qDebug() <<"ne peut pas ouvrir le fichier pour la lecture";
        return;

    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    qDebug() <<mText;

    mFile.close();
}

void MainWindow::Write_supprimer(QString Filename,int id, QString type, QString montant, QString dated)
{

QFile mFile(Filename);
if(!mFile.open(QFile::WriteOnly| QFile::Text))
{
    qDebug() <<"ne peut pas ouvrir le fichier pour l'écriture";
    return;

}

QTextStream out(&mFile);


out <<"supprimer:     " <<"Identifiant     "<<"Type                 "<<"Montant     "<<"Date     " ;
out <<"\n" ;
out <<"                    " <<id          <<"             "  <<type   <<"     "    <<montant     <<"           "<<dated;
mFile.flush();

mFile.close();
}

void MainWindow::Read_supprimer(QString Filename)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::ReadOnly| QFile::Text))
    {
        qDebug() <<"ne peut pas ouvrir le fichier pour la lecture";
        return;

    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    qDebug() <<mText;

    mFile.close();
}


double MainWindow :: getlineEditNum()
{

    //num1=ui->lineEdit_num1->text().toDouble();
   // num2=ui->lineEdit_num2->text().toDouble();

}

void MainWindow :: writeResult(double tempresult)
{

      //ui->lineEdit_result->setText(QString :: number(tempresult));
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

   /* QPrinter printer;

        QPrintDialog *dialog = new QPrintDialog(&printer, this);
        dialog->setWindowTitle(tr("Print Document"));
        if (ui->Cursor().hasSelection())
            dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
        if (dialog->exec() != QDialog::Accepted)
            return;*/

}

void MainWindow::on_tri_date_clicked()
{
    if(ui->tri_date->isChecked())
    {

   ui->table_depense->setModel(D.tri_date());


    }


}

void MainWindow::on_tri_identifiant_clicked()
{
    if(ui->tri_identifiant->isChecked())
    {

   ui->table_depense->setModel(D.tri_identifiant());


    }

}

void MainWindow::on_tri_type_clicked()
{
    if(ui->tri_type->isChecked())
    {

   ui->table_depense->setModel(D.tri_type());


    }
}
