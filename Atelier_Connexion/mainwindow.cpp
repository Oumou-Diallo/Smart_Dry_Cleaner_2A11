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
#include <QSqlDatabase>
#include"QPainter"
#include <QTextDocument>
#include <QFileDialog>
#include <QTextStream>
#include "equipement.h"
#include "article.h"
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPropertyAnimation>
#include "client.h"
#include <iostream>
#include "statistiques.h"
#include "historique.h"

using namespace std;



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


    ui->lineEdit_id_cl_aj->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_tel_cl->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_ia->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_is->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_id_eq_aj->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_suppression->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_id_art_sup->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_id_art_aj->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_supprimer_client->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_tel_cl_m->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_naj->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_nbr_art_cl_m->setValidator(new QIntValidator(0,9999999,this));



    ui->lineEdit_ma->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    ui->lineEdit_mm->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    ui->lineEdit_qte_eq_m->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    ui->lineEdit_qte_eq_aj->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    ui->lineEdit_prix_art_modifier->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    ui->lineEdit_prix_art_aj->setValidator(new QDoubleValidator(-999.0,999.0,2,this));
    QValidator *validator_String=new QRegExpValidator(QRegExp("[A-Za-z]+"),this);
    ui->lineEdit_nom_cl_aj->setValidator(validator_String);
    ui->lineEdit_prenom_cl_aj->setValidator(validator_String);
    ui->lineEdit_nom_art_aj->setValidator(validator_String);
    ui->lineEdit_nom_cl_m->setValidator(validator_String);
    ui->lineEdit_prenom_cl_m->setValidator(validator_String);





   ui->table_depense->setModel(D.afficher());
   ui->comboBox_id_dep_m->setModel(D.afficher());
   ui->table_eq_aff->setModel(E1.afficher_eq());
   ui->comboBox_id_eq_m->setModel(E1.afficher_eq());
   ui->comboBox_id_cl_m->setModel(C.afficher());
   ui->comboBox_id_art_modifier->setModel(Ar.Afficher());
   ui->table_article->setModel(Ar.Afficher());
   ui->table_client->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writetofile()
{

    QString fname = "D:\\Qt\\Qt5.";


}
 bool MainWindow::ajouter_historic_depense()
 {
     return true;


 }
QSqlQueryModel* MainWindow::historic_ajouter()
{
    QSqlQueryModel* model= new QSqlQueryModel();

    model->setQuery("SELECT id_dep,type_dep,montant_dep,date_dep,option_dep FROM historique_depense ORDER BY date_dep");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Effectué le"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Option"));
    return model;
}

QSqlQueryModel* MainWindow::historic_modifier()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT sysdate,id_dep,type_dep,montant_dep,date_dep,option_dep FROM historique_depense ORDER BY SYSDATE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Effectué le"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Option"));
    return model;
}


QSqlQueryModel* MainWindow::historic_ajouter_equipement()
{
    QSqlQueryModel* model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM historique_equipement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Effectué le"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Option"));
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
   bool test_historic_dep=D.ajouter_historic_depense();
   QMessageBox msgbox;

   if(test){
   msgbox.setText("ajout réussi");
   msgbox.exec();
   ui->table_depense->setModel(D.afficher());
    ui->comboBox_id_dep_m->setModel(D.afficher());


    }
   else{
   msgbox.setText("echec de l'ajout");
   msgbox.exec();}
      QString id_string=QString::number(id_dep);
   QString textajouter;
   historique h;
   QSqlQuery qry;
   qry.prepare("select * from APPAREILS");
   textajouter="L'ajout d'une depense a la base de donnees d'identifiant = "+QString(id_string)+", de type = "+QString(type_dep)+", de montant = "+QString(montant_dep)+" a ete effectue avec succes";
   h.write3(textajouter);

}

void MainWindow::on_pushButton_supprimer_clicked()
{
     QMediaPlayer * player ;


    player = new QMediaPlayer;
    // ...
    player->setMedia(QUrl::fromLocalFile("/Users/HP/Downloads/Atelier_Connexion_oumou/Atelier_Connexion/Atelier_Connexion/20220425_215601.mp3"));
    player->setVolume(50);
    player->play();
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
   QString id_string=QString::number(D1.getid_dep());

   if(t)
   {

       bool test=D1.supprimer(D1.getid_dep());
       ui->comboBox_id_dep_m->setModel(D1.afficher());
       if(test==true){
       msgbox.setText("suppression réussie");
       msgbox.exec();
       ui->table_depense->setModel(D1.afficher());
        }
       else {
       msgbox.setText("echec de la suppression");
       msgbox.exec();
       }
}

   else
    {msgbox.setText("identifiant n'existe pas");
       msgbox.exec();}

   QString textajouter;
   historique h;
   QSqlQuery qry;
   qry.prepare("select * from APPAREILS");
   textajouter="La suppression d'une depense a la base de donnees d'identifiant = "+QString(id_string)+" a ete effectue avec succes";
   h.write3(textajouter);

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


void MainWindow::Alert(int nb,QString nomProduit){
    QSqlQueryModel* model =new QSqlQueryModel();
    Seuil=5;
    QString S=QString::number(Seuil);
    /*model->setQuery("SELECT * FROM equipement WHERE quantite < "+S);
    if (model->rowCount() == 1){
    QString produitNom =model->data(ui->tableView_afficher->model()->index(0,3)).toString();*/

    notifyIcon->show();
    if(nb<Seuil)
        notifyIcon->showMessage("alerte produits ","le produit "+nomProduit+" presque epuisé ",QSystemTrayIcon::Information,15000);

    /*} else if (model->rowCount() > 1) {
    notifyIcon->show();
    notifyIcon->showMessage("alerte produits ","vous avez beaucoup de produits presque epuisés ",QSystemTrayIcon::Information,15000);
    }*/
    }




void MainWindow::on_pushButton_modifier_clicked()
{    Depense D;
     QString type_dep;
     int id_dep= ui->comboBox_id_dep_m->currentText().toInt();
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
       bool t=D.chercher(ui->comboBox_id_dep_m->currentText().toInt());

       if(t)
       {

          query.prepare("Update dépense set type_dep=:type_dep, montant_dep=:montant_dep , date_dep=:date_dep where id_dep=:id_string");
          query.bindValue(":id_string",id_string);
          query.bindValue(":type_dep",type_dep);
          query.bindValue(":montant_dep",montant_dep);
          query.bindValue(":date_dep",date_dep);
          query.exec();

           ui->table_depense->setModel(D.afficher());
           bool test_historic_dep=D.modifier_historic_depense(id_dep,type_dep,montant_dep);
            if(query.exec())
            {
                QMessageBox::information(nullptr, QObject::tr("Message"),
                            QObject::tr("Modification effectuée avec succes.\n"
                                        "Cliquer sur Annuler pour quitter."), QMessageBox::Cancel);
            }
            else
             {

                QMessageBox::critical(nullptr, QObject::tr("Message"),
                            QObject::tr("Modification non effectuée.\n"
                                        "Cliquer sur Annuler pour quitter."), QMessageBox::Cancel);

            }




    }

       else
        {msgbox.setText("identifiant n'existe pas");
           msgbox.exec();}

        QString textajouter;
        historique h;
        QSqlQuery qry;
        qry.prepare("select * from APPAREILS");
        textajouter="La modification d'une depense a la base de donnees d'identifiant = "+QString(id_string)+" , de type= "+QString(type_dep)+", de montant "+montant_dep+" a ete effectue avec succes";
        h.write3(textajouter);



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
    QString strStream;
            QTextStream out(&strStream);

                                 const int rowCount = ui->table_depense->model()->rowCount();
                                 const int columnCount = ui->table_depense->model()->columnCount();
                                 QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                                 out <<"<html>\n"
                                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     << "<title>ERP - CONTRAT<title>\n "
                                     << "</head>\n"
                                     "<body bgcolor=#FA8072 link=#C0C0C0>\n"
                                     "<h1 style=\"text-align: center;\"><strong> ******LISTE DES DEPENSES ******"+TT+" </strong></h1>"
                                     "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                       "</br> </br>";
                                 // headers
                                 out << "<thead><tr bgcolor=#d6e5ff>";
                                 for (int column = 0; column < columnCount; column++)
                                     if (!ui->table_depense->isColumnHidden(column))
                                         out << QString("<th>%1</th>").arg(ui->table_depense->model()->headerData(column, Qt::Horizontal).toString());
                                 out << "</tr></thead>\n";

                                 // data table
                                 for (int row = 0; row < rowCount; row++) {
                                     out << "<tr>";
                                     for (int column = 0; column < columnCount; column++) {
                                         if (!ui->table_depense->isColumnHidden(column)) {
                                             QString data =ui->table_depense->model()->data(ui->table_depense->model()->index(row, column)).toString().simplified();
                                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                         }
                                     }
                                     out << "</tr>\n";
                                 }
                                 out <<  "</table>\n"
                                     "</body>\n"
                                     "</html>\n";

                                 QTextDocument *document = new QTextDocument();
                                 document->setHtml(strStream);

                                 QPrinter printer;

                                 QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                                 if (dialog->exec() == QDialog::Accepted) {
                                     document->print(&printer);
                                 }

                                 delete document;



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

void MainWindow::on_pushButton_ajouter_eq_clicked()
{
    QString id_eq=ui->lineEdit_id_eq_aj->text();
    bool id_ok=true;
    int qte_eq=ui->lineEdit_qte_eq_aj->text().toInt();
    bool qte_ok=true;
    QString etat=ui->comboBox_etat->currentText();
    bool etat_ok=true;
    QString type_eq=ui->comboBox_type_eq->currentText();
    bool type_ok=true;


    ui->label_ii->setText("");
    ui->label_qi->setText("");

    for (int i=0;i<id_eq.length();i++) {
        if(id_eq[i]!="0" && id_eq[i]!="1" && id_eq[i]!="2" && id_eq[i]!="3" && id_eq[i]!="4" && id_eq[i]!="5" && id_eq[i]!="6" && id_eq[i]!="7" && id_eq[i]!="8" && id_eq[i]!="9" )
        {
            id_ok=false;
            break;
        }
    }

    if(id_eq.length()==0)
        id_ok=false;
    if(etat.length()==0)
        etat_ok=false;
    if(qte_eq<=0)
        qte_ok=false;
    if(type_eq.length()==0)
        type_ok=false;


    if(!id_ok)
    {
        ui->label_ii->setText("invalide");
    }

    else if(!qte_ok)
         ui->label_qi->setText("invalide");
    else
    {
    int id= ui->lineEdit_id_eq_aj->text().toInt();
    QString et= ui->comboBox_etat->currentText();
    QString ty= ui->comboBox_type_eq->currentText();;
    int qte= ui->lineEdit_qte_eq_aj->text().toInt();
    equipement E(id,et,ty,qte);

    bool test =E.ajouter_eq();
    QMessageBox msgBox;

    if(test)
       {
           msgBox.setText("Ajout avec succes.");
           ui->table_eq_aff->setModel(E.afficher_eq());
           ui->comboBox_id_eq_m->setModel(E.afficher_eq());
           //this->notification();
          // ui->table_historic_ajouter->setModel(historic_ajouter());
           Alert(qte,ui->lineEdit_id_eq_aj->text());
       }
    else
          msgBox.setText("Echec d'ajout");
    msgBox.exec();
    //this->notification();
    //E.historique(ui->lineEdit_id_eqA->text().toStdString(),"ajout");
    }


    QString textajouter;
    historique h;
    QSqlQuery qry;
    qry.prepare("select * from APPAREILS");
    textajouter="L'ajout de l'equipement a la base de donnees d'identifiant = "+QString(id_eq)+", d'etat = "+QString(etat)+", de type = "+QString(type_eq)+" et de quantite="+QString(qte_eq)+"  a ete effectue avec succes";
    h.write2(textajouter);

}

void MainWindow::on_pushButton_modifier_eq_clicked()
{

    int qte_p= ui->lineEdit_qte_eq_m->text().toInt();
    bool qte_ok=true;


    ui->label_qim->setText("");



    if(qte_p<=0)
        qte_ok=false;

      else if(!qte_ok)
         ui->label_qim->setText("invalide");
    else
    {
        int id_p= ui->comboBox_id_eq_m->currentText().toInt();
        QString et_p= ui->comboBox_etat_m->currentText();
        QString ty_p= ui->comboBox_type_eq_m->currentText();
        int qte= ui->lineEdit_qte_eq_m->text().toInt();
        equipement E(id_p,et_p,ty_p,qte);

        bool test =E.modifier_eq();
        QMessageBox msgBox;

        if(test)
           {
               msgBox.setText("modification avec succes.");
               ui->table_eq_aff->setModel(E.afficher_eq());
               //ui->table_historic_modifier->setModel(historic_modfication());
           }
        else
              msgBox.setText("Echec de la modification");
        msgBox.exec();

        //E.historique(ui->lineEdit_id_eqA->text().toStdString(),"modification");
    }
    QString id_string=QString::number(ui->comboBox_id_eq_m->currentText().toInt());
    QString et_p= ui->comboBox_etat_m->currentText();
    QString ty_p= ui->comboBox_type_eq_m->currentText();
    int qte= ui->lineEdit_qte_eq_m->text().toInt();
     QString qte_string=QString::number(qte);
    QString textajouter;
    historique h;
    QSqlQuery qry;
    qry.prepare("select * from APPAREILS");
    textajouter="La modification de l'equipement a la base de donnees d'identifiant = "+QString(id_string)+", d'etat = "+QString(et_p)+", de type = "+QString(ty_p)+" et de quantite="+QString(qte_string)+"  a ete effectue avec succes";
    h.write2(textajouter);

}

void MainWindow::on_pushButton_supprimer_eq_clicked()
{
    equipement Em;
    Em.set_id_eq(ui->lineEdit_suppression->text().toInt());

    QMessageBox msgBox;
    bool t=Em.chercher(ui->lineEdit_suppression->text());
    if(t)
    {
         bool test = Em.supprimer_eq(Em.get_id_eq());
    if(test)
    {
        msgBox.setText("Suppression avec succes.");
         msgBox.exec();
    ui->table_eq_aff->setModel(Em.afficher_eq());
    ui->comboBox_id_eq_m->setModel(Em.afficher_eq());

    }
    else{
        msgBox.setText("Echec de suppression");
    msgBox.exec();

    }

}

    else
                 {
                    msgBox.setText("identifiant n'existe pas");
                    msgBox.exec();
             }

    int id_eq=Em.get_id_eq();
    QString id_string=QString::number(id_eq);
    QString textajouter;
    historique h;
    QSqlQuery qry;
    qry.prepare("select * from APPAREILS");
    textajouter="La suppression de l'equipement a la base de donnees d'identifiant = "+QString(id_string)+"  a ete effectue avec succes";
    h.write2(textajouter);



}

void MainWindow::on_radioButton_qte_eq_aff_clicked()
{
    if(ui->tri_qte_eq_aff->isChecked())
    {

   ui->table_eq_aff->setModel(E1.tri_qte_eq());


    }
}

void MainWindow::on_tri_id_eq_aff_clicked()
{
    if(ui->tri_id_eq_aff->isChecked())
    {

   ui->table_eq_aff->setModel(E1.tri_identifiant());


    }
}

void MainWindow::on_tri_type_eq_aff_clicked()
{
    if(ui->tri_type_eq_aff->isChecked())
    {

   ui->table_eq_aff->setModel(E1.tri_type_eq());


    }
}

void MainWindow::on_tri_etat_aff_clicked()
{
    if(ui->tri_etat_aff->isChecked())
    {

   ui->table_eq_aff->setModel(E1.tri_etat());


    }
}

void MainWindow::on_tri_qte_eq_aff_clicked()
{
    if(ui->tri_qte_eq_aff->isChecked())
    {

   ui->table_eq_aff->setModel(E1.tri_qte_eq());


    }
}



void MainWindow::on_lineEdit_rechercher_textEdited(const QString &arg1)
{
    equipement E;

    ui->table_eq_aff->setModel(E.cherch_etat(arg1));

}


void MainWindow::on_pushButton_2_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

                                 const int rowCount = ui->table_depense->model()->rowCount();
                                 const int columnCount = ui->table_depense->model()->columnCount();
                                 QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                                 out <<"<html>\n"
                                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     << "<title>ERP - CONTRAT<title>\n "
                                     << "</head>\n"
                                     "<body bgcolor=#FA8072 link=#C0C0C0>\n"
                                     "<h1 style=\"text-align: center;\"><strong> ******LISTE DES DEPENSES ******"+TT+" </strong></h1>"
                                     "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                       "</br> </br>";
                                 // headers
                                 out << "<thead><tr bgcolor=#d6e5ff>";
                                 for (int column = 0; column < columnCount; column++)
                                     if (!ui->table_depense->isColumnHidden(column))
                                         out << QString("<th>%1</th>").arg(ui->table_depense->model()->headerData(column, Qt::Horizontal).toString());
                                 out << "</tr></thead>\n";

                                 // data table
                                 for (int row = 0; row < rowCount; row++) {
                                     out << "<tr>";
                                     for (int column = 0; column < columnCount; column++) {
                                         if (!ui->table_depense->isColumnHidden(column)) {
                                             QString data =ui->table_depense->model()->data(ui->table_depense->model()->index(row, column)).toString().simplified();
                                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                         }
                                     }
                                     out << "</tr>\n";
                                 }
                                 out <<  "</table>\n"
                                     "</body>\n"
                                     "</html>\n";

                                 QTextDocument *document = new QTextDocument();
                                 document->setHtml(strStream);

                                 QPrinter printer;

                                 QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                                 if (dialog->exec() == QDialog::Accepted) {
                                     document->print(&printer);
                                 }

                                 delete document;



}

void MainWindow::on_pushButton_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

                                 const int rowCount = ui->table_eq_aff->model()->rowCount();
                                 const int columnCount = ui->table_eq_aff->model()->columnCount();
                                 QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                                 out <<"<html>\n"
                                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     << "<title>ERP - CONTRAT<title>\n "
                                     << "</head>\n"
                                     "<body bgcolor=#FA8072 link=#C0C0C0>\n"
                                     "<h1 style=\"text-align: center;\"><strong> ******LISTE DES EQUIPEMENTS ******"+TT+" </strong></h1>"
                                     "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                       "</br> </br>";
                                 // headers
                                 out << "<thead><tr bgcolor=#d6e5ff>";
                                 for (int column = 0; column < columnCount; column++)
                                     if (!ui->table_eq_aff->isColumnHidden(column))
                                         out << QString("<th>%1</th>").arg(ui->table_eq_aff->model()->headerData(column, Qt::Horizontal).toString());
                                 out << "</tr></thead>\n";

                                 // data table
                                 for (int row = 0; row < rowCount; row++) {
                                     out << "<tr>";
                                     for (int column = 0; column < columnCount; column++) {
                                         if (!ui->table_eq_aff->isColumnHidden(column)) {
                                             QString data =ui->table_eq_aff->model()->data(ui->table_eq_aff->model()->index(row, column)).toString().simplified();
                                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                         }
                                     }
                                     out << "</tr>\n";
                                 }
                                 out <<  "</table>\n"
                                     "</body>\n"
                                     "</html>\n";

                                 QTextDocument *document = new QTextDocument();
                                 document->setHtml(strStream);

                                 QPrinter printer;

                                 QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                                 if (dialog->exec() == QDialog::Accepted) {
                                     document->print(&printer);
                                 }

                                 delete document;



}

void MainWindow::on_pushButton_3_clicked()
{
     S.stat(ui->widget_statistique);
}

void MainWindow::Alert(){
    QSqlQueryModel* model =new QSqlQueryModel();
    QString S=QString::number(Seuil);
    model->setQuery("SELECT * FROM Equipement WHERE QTE_EQ < "+S);
    if (model->rowCount() == 1){
        QString produitNom =model->data(ui->table_eq_aff->model()->index(0,2)).toString();

        notifyIcon->show();
        notifyIcon->showMessage("alerte equipement ","l'equipement "+produitNom+" presque epuisé ",QSystemTrayIcon::Information,15000);

    } else if (model->rowCount() > 1) {
        notifyIcon->show();
        notifyIcon->showMessage("alerte equipement ","les equipements sont presque expirés ",QSystemTrayIcon::Information,15000);
    }

}
void MainWindow::on_spinBox_valueChanged(int arg1)
{

    Seuil = arg1;
    Alert();

}

void MainWindow::refresh()
{
    ui->table_article->setModel(Ar.Afficher());
   // ui->tableView_historique->setModel(Ar.historique());
  //ui->tableView_archive->setModel(Ar.AfficherArchive());
}

void MainWindow::on_pushButton_ajouter_article_clicked()
{   QString id_art= ui->lineEdit_id_art_aj->text();
    QString prix_art = ui->lineEdit_prix_art_aj->text();
       QString nom_art = ui->lineEdit_nom_art_aj->text();
       //QString type = ui->type->text();
       QString type_art = ui->comboBox_type_art_aj->currentText();

       Article A(id_art,nom_art,prix_art,type_art);
       bool ok = A.ajouter();
       if(ok)
       {
           //Ar.ajouterHistorique("ajout article");
           refresh();
           QMessageBox::information(nullptr, QObject::tr("success"),
                       QObject::tr("article ajouté.\n"
                                   "Cliquer Annuler pour quitter."), QMessageBox::Cancel);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("fail"),
                       QObject::tr("article non ajouté.\n"
                                   "Cliquer Annuler pour quitter."), QMessageBox::Cancel);

       QString textajouter;
       historique h;
       QSqlQuery qry;
       qry.prepare("select * from APPAREILS");
       textajouter="La modification d'un article a la base de donnees d'identifiant = "+QString(id_art)+" , de type= "+QString(type_art)+", de montant = "+prix_art+" et de nom = "+nom_art+"a ete effectue avec succes";
       h.write(textajouter);
}

void MainWindow::on_pushButton_4_clicked()
{  Article A;
    QString id_art = ui->lineEdit_id_art_sup->text();

         bool t=A.chercher(ui->lineEdit_id_art_sup->text());
         QMessageBox msgBox;
         if(t){
         bool ok = A.supprimer(id_art);
         refresh();
         if(ok)
        {


            //Ar.ajouterHistorique("suppression article");

            QMessageBox::information(nullptr, QObject::tr("Réussi"),
                        QObject::tr("article supprimé.\n"
                                    "Cliquer Annuler pour sortir."), QMessageBox::Cancel);

    }
        else{
            QMessageBox::critical(nullptr, QObject::tr("Echoué"),
                        QObject::tr("article non supprimé.\n"
                                    "Cliquer Annuler pour sortir."), QMessageBox::Cancel);
}

 }        else
             {
                msgBox.setText("identifiant n'existe pas");
                msgBox.exec();
         }

         QString textajouter;
         historique h;
         QSqlQuery qry;
         qry.prepare("select * from APPAREILS");
         textajouter="La suppression d'un article a la base de donnees d'identifiant = "+QString(id_art)+"  a ete effectue avec succes";
         h.write(textajouter);

}

void MainWindow::on_pushButton_5_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

                                 const int rowCount = ui->table_article->model()->rowCount();
                                 const int columnCount = ui->table_article->model()->columnCount();
                                 QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                                 out <<"<html>\n"
                                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     << "<title>ERP - CONTRAT<title>\n "
                                     << "</head>\n"
                                     "<body bgcolor=#FA8072 link=#C0C0C0>\n"
                                     "<h1 style=\"text-align: center;\"><strong> ******LISTE DES ARTICLES ******"+TT+" </strong></h1>"
                                     "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                       "</br> </br>";
                                 // headers
                                 out << "<thead><tr bgcolor=#d6e5ff>";
                                 for (int column = 0; column < columnCount; column++)
                                     if (!ui->table_article->isColumnHidden(column))
                                         out << QString("<th>%1</th>").arg(ui->table_article->model()->headerData(column, Qt::Horizontal).toString());
                                 out << "</tr></thead>\n";

                                 // data table
                                 for (int row = 0; row < rowCount; row++) {
                                     out << "<tr>";
                                     for (int column = 0; column < columnCount; column++) {
                                         if (!ui->table_article->isColumnHidden(column)) {
                                             QString data =ui->table_article->model()->data(ui->table_article->model()->index(row, column)).toString().simplified();
                                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                         }
                                     }
                                     out << "</tr>\n";
                                 }
                                 out <<  "</table>\n"
                                     "</body>\n"
                                     "</html>\n";

                                 QTextDocument *document = new QTextDocument();
                                 document->setHtml(strStream);

                                 QPrinter printer;

                                 QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                                 if (dialog->exec() == QDialog::Accepted) {
                                     document->print(&printer);
                                 }

                                 delete document;
}

void MainWindow::on_pushButton_modifier_article_clicked()
{
    QString nom_art = ui->lineEdit_nom_art_modifier->text();
    QString prix_art = ui->lineEdit_prix_art_modifier->text();


            QString id_art= ui->comboBox_id_art_modifier->currentText();
            QString type_art= ui->comboBox_type_art_modifier->currentText();

            Article A(id_art,nom_art,prix_art,type_art);

            bool test =A.modifier_art();
            QMessageBox msgBox;

            if(test)
               {
                   msgBox.setText("modification avec succes.");
                   ui->table_article->setModel(A.Afficher());
                   //ui->table_historic_modifier->setModel(historic_modfication());
                    msgBox.exec();
               }
            else
                 { msgBox.setText("Echec de la modification");
            msgBox.exec();

            //E.historique(ui->lineEdit_id_eqA->text().toStdString(),"modification");
        }


            QString textajouter;
            historique h;
            QSqlQuery qry;
            qry.prepare("select * from APPAREILS");
            textajouter="La modification d'un article a la base de donnees d'identifiant = "+QString(id_art)+" , de type= "+QString(type_art)+", de montant "+prix_art+" et de nom = "+nom_art+"a ete effectue avec succes";
            h.write(textajouter);

}

void MainWindow::on_pushButton_excel_clicked()
{
    QTableView *table;
           table = ui->table_article;

           QString filters("CSV files (*.csv);;All files (*.*)");
           QString defaultFilter("CSV files (*.csv)");
           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                              filters, &defaultFilter);
           QFile file(fileName);

           QAbstractItemModel *model =  table->model();
           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
               QTextStream data(&file);
               QStringList strList;
               for (int i = 0; i < model->columnCount(); i++) {
                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") << "\n";
               for (int i = 0; i < model->rowCount(); i++) {
                   strList.clear();
                   for (int j = 0; j < model->columnCount(); j++) {

                       if (model->data(model->index(i, j)).toString().length() > 0)
                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") + "\n";
               }
               file.close();
               QMessageBox::information(this,"Exporter Sur Excel","Exporter Sur Excel Avec Succes ");
           }
}

void MainWindow::on_pushButton_excel_equipement_clicked()
{
    QTableView *table;
           table = ui->table_eq_aff;

           QString filters("CSV files (*.csv);;All files (*.*)");
           QString defaultFilter("CSV files (*.csv)");
           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                              filters, &defaultFilter);
           QFile file(fileName);

           QAbstractItemModel *model =  table->model();
           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
               QTextStream data(&file);
               QStringList strList;
               for (int i = 0; i < model->columnCount(); i++) {
                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") << "\n";
               for (int i = 0; i < model->rowCount(); i++) {
                   strList.clear();
                   for (int j = 0; j < model->columnCount(); j++) {

                       if (model->data(model->index(i, j)).toString().length() > 0)
                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") + "\n";
               }
               file.close();
               QMessageBox::information(this,"Exporter Sur Excel","Exporter Sur Excel Avec Succées ");
           }
}

void MainWindow::on_pushButton_excel_depense_clicked()
{
    QTableView *table;
           table = ui->table_depense;

           QString filters("CSV files (*.csv);;All files (*.*)");
           QString defaultFilter("CSV files (*.csv)");
           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                              filters, &defaultFilter);
           QFile file(fileName);

           QAbstractItemModel *model =  table->model();
           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
               QTextStream data(&file);
               QStringList strList;
               for (int i = 0; i < model->columnCount(); i++) {
                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") << "\n";
               for (int i = 0; i < model->rowCount(); i++) {
                   strList.clear();
                   for (int j = 0; j < model->columnCount(); j++) {

                       if (model->data(model->index(i, j)).toString().length() > 0)
                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") + "\n";
               }
               file.close();
               QMessageBox::information(this,"Exporter Sur Excel","Exporter Sur Excel Avec Succes ");
           }
}

void MainWindow::on_radioButton_type_art_clicked()
{
    if(ui->radioButton_type_art->isChecked())
    {

   ui->table_article->setModel(Ar.tri_type());


    }
}

void MainWindow::on_radioButton_id_art_clicked()
{
    if(ui->radioButton_id_art->isChecked())
    {

   ui->table_article->setModel(Ar.tri_identifiant());


    }
}

void MainWindow::on_radioButton_nom_art_clicked()
{
    if(ui->radioButton_nom_art->isChecked())
    {

   ui->table_article->setModel(Ar.tri_nom());


    }
}

void MainWindow::on_radioButton_prix_art_clicked()
{
    if(ui->radioButton_prix_art->isChecked())
    {

   ui->table_article->setModel(Ar.tri_prix());


    }
}

void MainWindow::on_lineEdit_rechercher_article_textEdited(const QString &arg1)
{
   Article Ar;

    ui->table_article->setModel(Ar.cherch(arg1));

}



void MainWindow::on_commandLinkButton_clicked()
{

}

void MainWindow::on_pushButton_ajouter_client_clicked()
{
    int id_cl=ui->lineEdit_id_cl_aj->text().toInt();
    QString nom=ui->lineEdit_nom_cl_aj->text();
    QString prenom=ui->lineEdit_prenom_cl_aj->text();
    int tel=ui->lineEdit_tel_cl->text().toInt();
    int nbr_art=ui->lineEdit_naj->text().toInt();
    QString service=ui->comboBox_service_cl_aj->currentText();
    Client C(id_cl,nom,prenom,tel,service,nbr_art);
    bool test=C.ajouter();
    if(test){
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Cliquer sur Annuler pour quitter."), QMessageBox::Cancel);
        ui->table_client->setModel(C.afficher());
    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué.\n"
                                "Cliquer sur Annuler pour quitter."), QMessageBox::Cancel);}
    QString textajouter;
    historique h;
    QSqlQuery qry;
    qry.prepare("select * from APPAREILS");
    textajouter="L'ajout d'un client a la base de donnees de nom = "+QString(nom)+" a ete effectue avec succees";
    h.write1(textajouter);
}

void MainWindow::on_pushButton_supprimer_client_clicked()
{
    Client C1;
   C1.setid_cl(ui->lineEdit_supprimer_client->text().toInt());

   QMessageBox msgbox;
   bool t=C1.chercher(ui->lineEdit_supprimer_client->text().toInt());

   if(t)
   {

       bool test=C1.supprimer(C1.getid_cl());
       ui->comboBox_id_cl_m->setModel(C1.afficher());
       if(test==true){
       msgbox.setText("suppression réussie");
       msgbox.exec();
       ui->table_client->setModel(C1.afficher());
        }
       else {
       msgbox.setText("echec de la suppression");
       msgbox.exec();
       }
}

   else
    {msgbox.setText("identifiant n'existe pas");
       msgbox.exec();}

   QString textajouter;
   historique h;
   QSqlQuery qry;
   qry.prepare("select * from APPAREILS");
   textajouter="La suppression d'un client a la base de donnees de Nom = "+QString(C.getnom())+" a ete effectue avec succees";
   h.write1(textajouter);


}

void MainWindow::on_pushButton_7_clicked()
{
    int id_cl=ui->comboBox_id_cl_m->currentText().toInt();
    QString nom=ui->lineEdit_nom_cl_m->text();
    QString prenom=ui->lineEdit_prenom_cl_m->text();
    int tel=ui->lineEdit_tel_cl_m->text().toInt();
    int nbr_art=ui->lineEdit_nbr_art_cl_m->text().toInt();
    QString service=ui->comboBox_service_cl_m->currentText();
    Client C(id_cl,nom,prenom,tel,service,nbr_art);
    bool test=C.ModifierClient();
    if(test){
        QMessageBox::information(nullptr, QObject::tr("Message"),
                    QObject::tr("Modification effectuée.\n"
                                "Cliquer sur Annuler pour quitter."), QMessageBox::Cancel);
        ui->table_client->setModel(C.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Message"),
                    QObject::tr("Modification non effectué.\n"
                                "Cliquer sur Annuler pour quitter."), QMessageBox::Cancel);
    QString textajouter;
    historique h;
    QSqlQuery qry;
    qry.prepare("select * from APPAREILS");
    textajouter="La modification d'un client a la base de donnees du nom = "+QString(C.getnom())+" a ete effectue avec succes";
    h.write1(textajouter);
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
   Client C1;

    ui->table_client->setModel(C1.cherch(arg1));

}

void MainWindow::on_radioButton_clicked()
{
    if(ui->tri_service_cl->isChecked())
    {

   ui->table_client->setModel(C.tri_service());


    }
}

void MainWindow::on_tri_nom_cl_clicked()
{
    if(ui->tri_nom_cl->isChecked())
    {

   ui->table_client->setModel(C.tri_nom());


    }
}

void MainWindow::on_tri_id_cl_clicked()
{
    if(ui->tri_id_cl->isChecked())
    {

   ui->table_client->setModel(C.tri_identifiant());


    }
}

void MainWindow::on_tri_service_cl_clicked()
{

    if(ui->tri_service_cl->isChecked())
    {

   ui->table_client->setModel(C.tri_service());


    }
}





void MainWindow::on_pushButton_imprimer_client_clicked()
{

    QString strStream;
            QTextStream out(&strStream);

                                 const int rowCount = ui->table_client->model()->rowCount();
                                 const int columnCount = ui->table_client->model()->columnCount();
                                 QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                                 out <<"<html>\n"
                                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     << "<title>ERP - CONTRAT<title>\n "
                                     << "</head>\n"
                                     "<body bgcolor=#FA8072 link=#C0C0C0>\n"
                                     "<h1 style=\"text-align: center;\"><strong> ******LISTE DES CLIENTS ******"+TT+" </strong></h1>"
                                     "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                       "</br> </br>";
                                 // headers
                                 out << "<thead><tr bgcolor=#d6e5ff>";
                                 for (int column = 0; column < columnCount; column++)
                                     if (!ui->table_client->isColumnHidden(column))
                                         out << QString("<th>%1</th>").arg(ui->table_client->model()->headerData(column, Qt::Horizontal).toString());
                                 out << "</tr></thead>\n";

                                 // data table
                                 for (int row = 0; row < rowCount; row++) {
                                     out << "<tr>";
                                     for (int column = 0; column < columnCount; column++) {
                                         if (!ui->table_client->isColumnHidden(column)) {
                                             QString data =ui->table_client->model()->data(ui->table_client->model()->index(row, column)).toString().simplified();
                                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                         }
                                     }
                                     out << "</tr>\n";
                                 }
                                 out <<  "</table>\n"
                                     "</body>\n"
                                     "</html>\n";

                                 QTextDocument *document = new QTextDocument();
                                 document->setHtml(strStream);

                                 QPrinter printer;

                                 QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                                 if (dialog->exec() == QDialog::Accepted) {
                                     document->print(&printer);
                                 }

                                 delete document;



}

void MainWindow::on_pushButton_statistique_client_clicked()
{
    SS.stat(ui->widget_statistique);
}

void MainWindow::on_pushButton_excel_client_clicked()
{
    QTableView *table;
           table = ui->table_client;

           QString filters("CSV files (*.csv);;All files (*.*)");
           QString defaultFilter("CSV files (*.csv)");
           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                              filters, &defaultFilter);
           QFile file(fileName);

           QAbstractItemModel *model =  table->model();
           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
               QTextStream data(&file);
               QStringList strList;
               for (int i = 0; i < model->columnCount(); i++) {
                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") << "\n";
               for (int i = 0; i < model->rowCount(); i++) {
                   strList.clear();
                   for (int j = 0; j < model->columnCount(); j++) {

                       if (model->data(model->index(i, j)).toString().length() > 0)
                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") + "\n";
               }
               file.close();
               QMessageBox::information(this,"Exporter Sur Excel","Exporter Sur Excel Avec Succes ");
           }
}

void MainWindow::on_pushButton_pdf_client_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString());
        str.append("<table border=1><tr>") ;
        str.append("<td>"+QString("Identifiant")+"</td>") ;
        str.append("<td>"+QString("Nom")+"</td>") ;
        str.append("<td>"+QString("Prenom")+"</td>") ;
        str.append("<td>"+QString("Telephone")+"</td>") ;
        str.append("<td>"+QString("Service")+"</td>") ;
        str.append("<td>"+QString("Nombre d'articles")+"</td>") ;
        QSqlQuery* query=new QSqlQuery();
        query->exec("SELECT * FROM Client");
        //query.prepare("INSERT INTO CHAMBRES (NOMDEPARTEMENT,TYPEC,ETATC,ELEMENTSMANQUANTS,NUMCHAMBRE,NUMETAGE,NBLITS)"
                      //"VALUES (:NomDepartement, :TypeC, :EtatC, :ElementsManquants, :NumChambre, :NumEtage, :NbLits)");
        while(query->next())
        {
        str.append("<tr><td>");
        str.append(query->value(0).toString()) ;
        str.append("</td><td>") ;
        str.append(query->value(1).toString());
        str.append("</td><td>") ;
        str.append(query->value(2).toString());
        str.append("</td><td>") ;
        str.append(query->value(3).toString());
        str.append("</td><td>") ;
        str.append(query->value(4).toString());
        str.append("</td><td>") ;
        str.append(query->value(5).toString());

        }
        str.append("</table></center></body></html>") ;

        QPrinter printer ;
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4) ;

        QString path=QFileDialog::getSaveFileName(NULL,"Convertir a PDF","C:/Users/Downloads","PDF(*.pdf)");

        if (path.isEmpty()) return ;
        printer.setOutputFileName(path) ;
        QTextDocument doc;
        doc.setHtml(str) ;
        doc.print(&printer);
        QMessageBox::information(nullptr,QObject::tr("Creation PDF"),QObject::tr("PDF crée .\n"
                                                                                           "Cliquer sur Annuler pour quitter ."),QMessageBox::Cancel);

}


void MainWindow::on_pushButton_pdf_depense_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString());
        str.append("<table border=1><tr>") ;
        str.append("<td>"+QString("Identifiant")+"</td>") ;
        str.append("<td>"+QString("Type")+"</td>") ;
        str.append("<td>"+QString("Montant")+"</td>") ;
        str.append("<td>"+QString("Date")+"</td>") ;
        QSqlQuery* query=new QSqlQuery();
        query->exec("SELECT * FROM dépense");
        //query.prepare("INSERT INTO CHAMBRES (NOMDEPARTEMENT,TYPEC,ETATC,ELEMENTSMANQUANTS,NUMCHAMBRE,NUMETAGE,NBLITS)"
                      //"VALUES (:NomDepartement, :TypeC, :EtatC, :ElementsManquants, :NumChambre, :NumEtage, :NbLits)");
        while(query->next())
        {
        str.append("<tr><td>");
        str.append(query->value(0).toString()) ;
        str.append("</td><td>") ;
        str.append(query->value(1).toString());
        str.append("</td><td>") ;
        str.append(query->value(2).toString());
        str.append("</td><td>") ;
        str.append(query->value(3).toString());
        }
        str.append("</table></center></body></html>") ;

        QPrinter printer ;
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4) ;

        QString path=QFileDialog::getSaveFileName(NULL,"Convertir a PDF","C:/Users/Downloads","PDF(*.pdf)");

        if (path.isEmpty()) return ;
        printer.setOutputFileName(path) ;
        QTextDocument doc;
        doc.setHtml(str) ;
        doc.print(&printer);
        QMessageBox::information(nullptr,QObject::tr("Creation PDF"),QObject::tr("PDF crée .\n"
                                                                                           "Cliquer sur Annuler pour quitter ."),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_11_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString());
        str.append("<table border=1><tr>") ;
        str.append("<td>"+QString("Identifiant")+"</td>") ;
        str.append("<td>"+QString("Etat")+"</td>") ;
        str.append("<td>"+QString("Type")+"</td>") ;
        str.append("<td>"+QString("Quantite")+"</td>") ;
        QSqlQuery* query=new QSqlQuery();
        query->exec("SELECT * FROM equipement");
        //query.prepare("INSERT INTO CHAMBRES (NOMDEPARTEMENT,TYPEC,ETATC,ELEMENTSMANQUANTS,NUMCHAMBRE,NUMETAGE,NBLITS)"
                      //"VALUES (:NomDepartement, :TypeC, :EtatC, :ElementsManquants, :NumChambre, :NumEtage, :NbLits)");
        while(query->next())
        {
        str.append("<tr><td>");
        str.append(query->value(0).toString()) ;
        str.append("</td><td>") ;
        str.append(query->value(1).toString());
        str.append("</td><td>") ;
        str.append(query->value(2).toString());
        str.append("</td><td>") ;
        str.append(query->value(3).toString());

        }
        str.append("</table></center></body></html>") ;

        QPrinter printer ;
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4) ;

        QString path=QFileDialog::getSaveFileName(NULL,"Convertir a PDF","C:/Users/Downloads","PDF(*.pdf)");

        if (path.isEmpty()) return ;
        printer.setOutputFileName(path) ;
        QTextDocument doc;
        doc.setHtml(str) ;
        doc.print(&printer);
        QMessageBox::information(nullptr,QObject::tr("Creation PDF"),QObject::tr("PDF crée .\n"
                                                                                           "Cliquer sur Annuler pour quitter ."),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_12_clicked()
{
    QString str;
        str.append("<html><head></head><body><center>"+QString());
        str.append("<table border=1><tr>") ;
        str.append("<td>"+QString("Identifiant")+"</td>") ;
        str.append("<td>"+QString("Nom")+"</td>") ;
        str.append("<td>"+QString("Prix")+"</td>") ;
        str.append("<td>"+QString("Type")+"</td>") ;
        QSqlQuery* query=new QSqlQuery();
        query->exec("SELECT * FROM articles");
        //query.prepare("INSERT INTO CHAMBRES (NOMDEPARTEMENT,TYPEC,ETATC,ELEMENTSMANQUANTS,NUMCHAMBRE,NUMETAGE,NBLITS)"
                      //"VALUES (:NomDepartement, :TypeC, :EtatC, :ElementsManquants, :NumChambre, :NumEtage, :NbLits)");
        while(query->next())
        {
        str.append("<tr><td>");
        str.append(query->value(0).toString()) ;
        str.append("</td><td>") ;
        str.append(query->value(1).toString());
        str.append("</td><td>") ;
        str.append(query->value(2).toString());
        str.append("</td><td>") ;
        str.append(query->value(3).toString());

        }
        str.append("</table></center></body></html>") ;

        QPrinter printer ;
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4) ;

        QString path=QFileDialog::getSaveFileName(NULL,"Convertir a PDF","C:/Users/Downloads","PDF(*.pdf)");

        if (path.isEmpty()) return ;
        printer.setOutputFileName(path) ;
        QTextDocument doc;
        doc.setHtml(str) ;
        doc.print(&printer);
        QMessageBox::information(nullptr,QObject::tr("Creation PDF"),QObject::tr("PDF crée .\n"
                                                                                           "Cliquer sur Annuler pour quitter ."),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_hist_client_clicked()
{
    ui->table_client->hide();
    historique h;
    ui->textEdit_client->show();
    ui->textEdit_client->setPlainText(h.read1());
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->table_article->hide();
    historique h;
    ui->textEdit_client->show();
    ui->textEdit_client->setPlainText(h.read());
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->table_eq_aff->hide();
    historique h;
    ui->textEdit_client->show();
    ui->textEdit_client->setPlainText(h.read2());
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->table_depense->hide();
    historique h;
    ui->textEdit_client->show();
    ui->textEdit_client->setPlainText(h.read3());
}
/*
void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")
        ui->state->setText("Accepter"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->state->setText("Refuser");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}



void MainWindow::on_OUVRIR_clicked()
{
    A.write_to_arduino("1");
}

void MainWindow::on_FERMER_clicked()
{
    A.write_to_arduino("0");
}
*/
