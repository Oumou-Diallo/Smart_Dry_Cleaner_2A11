#include "gestionequipement.h"
#include "ui_gestionequipement.h"
#include "equipement.h"
#include <qmessagebox.h>
#include <QSqlTableModel>
#include <QSqlDatabase>





/*void gestionEquipement::notification()
{
    QSqlQuery query;
  QString requete="SELECT ID_EQ,QTE_EQ FROM EQUIPEMENT WHERE QTE_EQ<3";
  QString message="les equipements avec les IDENTIDIANTS suivant seront bientot en rupture\n";

  int nombre=0;
  QMessageBox msgBox;

  query.prepare(requete);
  if(query.exec())
  {
      while (query.next())
      {
          message+=query.value(0).toString()+", qte:"+query.value(1).toString()+"\n";
          nombre++;
      }
  }

  if(nombre>0)
  {
      msgBox.setText(message);
      msgBox.exec();
  }



}
*/








gestionEquipement::gestionEquipement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestionEquipement)
{
    ui->setupUi(this);
    ui->tableView_afficher->setModel(E.afficher());
     ui->table_historic_ajouter->setModel(historic_ajouter());
     ui->table_historic_modifier->setModel(historic_modfication());
    //ui->tableView_statistique->setModel(E.afficher());
    ui->comboBox_5->setModel(E.afficher());
    //this->notification();

    int ret=A.connect_arduino();
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

gestionEquipement::~gestionEquipement()
{
    delete ui;
}











void gestionEquipement::on_pushButton_ajouter_clicked()//appuies sur le boutton ajouter
{
    QString id_s=ui->lineEdit_id_eqA->text();
    bool id_ok=true;
    int qte_s=ui->spinBox->text().toInt();
    bool qte_ok=true;
    QString etat_s=ui->comboBox->currentText();
    bool etat_ok=true;
    QString type_s=ui->comboBox_2->currentText();
    bool type_ok=true;


    ui->label_9->setText("");
    ui->label_13->setText("");
    ui->label_12->setText("");
    ui->label_14->setText("");

    for (int i=0;i<id_s.length();i++) {
        if(id_s[i]!="0" && id_s[i]!="1" && id_s[i]!="2" && id_s[i]!="3" && id_s[i]!="4" && id_s[i]!="5" && id_s[i]!="6" && id_s[i]!="7" && id_s[i]!="8" && id_s[i]!="9" )
        {
            id_ok=false;
            break;
        }
    }

    if(id_s.length()==0)
        id_ok=false;
    if(etat_s.length()==0)
        etat_ok=false;
    if(qte_s<=0)
        qte_ok=false;
    if(type_s.length()==0)
        type_ok=false;


    if(!id_ok)
    {
        ui->label_9->setText("invalide");
    }
    else if(!etat_ok)
        ui->label_13->setText("invalide");
    else if(!type_ok)
         ui->label_14->setText("invalide");
    else if(!qte_ok)
         ui->label_12->setText("invalide");
    else
    {
        int id= ui->lineEdit_id_eqA->text().toInt();
    QString et= ui->comboBox->currentText();
    QString ty= ui->comboBox_2->currentText();;
    int qte= ui->spinBox->text().toInt();
    equipement E(id,et,ty,qte);

    bool test =E.ajouter();
    QMessageBox msgBox;

    if(test)
       {
           msgBox.setText("Ajout avec succes.");
           ui->tableView_afficher->setModel(E.afficher());
           //this->notification();
           ui->table_historic_ajouter->setModel(historic_ajouter());
       }
    else
          msgBox.setText("Echec d'ajout");
    msgBox.exec();
    //this->notification();
    //E.historique(ui->lineEdit_id_eqA->text().toStdString(),"ajout");
    if(test)
        Alert(qte,ui->lineEdit_id_eqA->text());
    }
}

void gestionEquipement::on_pushButton_modifier_clicked()//click sur le boutton modifier
{
    QString id_p= ui->comboBox_5->currentText();
    bool id_ok=true;
    QString etat_p= ui->comboBox_3->currentText();
    bool etat_ok=true;
    QString type_p= ui->comboBox_4->currentText();
    bool type_ok=true;
    int qte_p= ui->spinBox_2->text().toInt();
    bool qte_ok=true;

    ui->label_15->setText("");
    ui->label_16->setText("");
    ui->label_17->setText("");
    ui->label_18->setText("");

    for (int i=0;i<id_p.length();i++) {
        if(id_p[i]!="0" && id_p[i]!="1" && id_p[i]!="2" && id_p[i]!="3" && id_p[i]!="4" && id_p[i]!="5" && id_p[i]!="6" && id_p[i]!="7" && id_p[i]!="8" && id_p[i]!="9" )
        {
            id_ok=false;
            break;
        }
    }

    if(id_p.length()==0)
        id_ok=false;
    if(etat_p.length()==0)
        etat_ok=false;
    if(qte_p<=0)
        qte_ok=false;
    if(type_p.length()==0)
        type_ok=false;

    if(!id_ok)
    {
        ui->label_15->setText("invalide");
    }
    else if(!etat_ok)
        ui->label_16->setText("invalide");
    else if(!type_ok)
         ui->label_17->setText("invalide");
    else if(!qte_ok)
         ui->label_18->setText("invalide");
    else
    {
        int id_p= ui->comboBox_5->currentText().toInt();
        QString et_p= ui->comboBox_3->currentText();
        QString ty_p= ui->comboBox_4->currentText();
        int qte= ui->spinBox_2->text().toInt();
        equipement E(id_p,et_p,ty_p,qte);

        bool test =E.modifier();
        QMessageBox msgBox;

        if(test)
           {
               msgBox.setText("modification avec succes.");
               ui->tableView_afficher->setModel(E.afficher());
               ui->table_historic_modifier->setModel(historic_modfication());
           }
        else
              msgBox.setText("Echec de la modification");
        msgBox.exec();

        //E.historique(ui->lineEdit_id_eqA->text().toStdString(),"modification");
    }

   // this->notification();


}


void gestionEquipement::on_pushButton_supprimer_clicked()
{
    equipement E1; E1.set_id_eq(ui->lineEdit_RS->text().toInt());
    bool test = E1.supprimer(E1.get_id_eq());
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Suppression avec succes.");
    ui->tableView_afficher->setModel(E.afficher());

    }
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();

    //E.historique(ui->lineEdit_id_eqA->text().toStdString(),"supression");
}

void gestionEquipement::on_checkBox_stateChanged(int arg1)//si case nouveau est coché
{
   if(ui->checkBox->isChecked() && !ui->checkBox_3->isChecked())
       ui->tableView_afficher->setModel(E.triParEtat("nouveau"));
   else {
       ui->tableView_afficher->setModel(E.afficher());
   }
}

void gestionEquipement::on_checkBox_3_stateChanged(int arg1)//si case utilisé est coché
{
    if(!ui->checkBox->isChecked() && ui->checkBox_3->isChecked())
        ui->tableView_afficher->setModel(E.triParEtat("utilise"));
    else {
        ui->tableView_afficher->setModel(E.afficher());
    }
}

void gestionEquipement::on_checkBox_2_stateChanged(int arg1)
{
    bool sl=ui->checkBox_2->isChecked();
    bool ej=ui->checkBox_4->isChecked();
    bool ml=ui->checkBox_5->isChecked();
    bool mr=ui->checkBox_6->isChecked();

    if(sl && !ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(1));
    else if(!sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(2));
    else if(!sl && !ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(3));
    else if(!sl && !ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(4));
    else if(sl && !ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(7));
    else if(sl && !ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(6));
    else if(sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(5));
    else if(!sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(8));
    else if(!sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(9));
    else if(!sl && !ej && ml && mr)
        ui->tableView_afficher->setModel(E.triParType(10));
    else if(sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(11));
    else if(sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(12));
    else if(sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(13));
    else if(sl && !ej && ml && mr)
        ui->tableView_afficher->setModel(E.triParType(14));
    else if(sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(15));
    else
        ui->tableView_afficher->setModel(E.afficher());
}

void gestionEquipement::on_checkBox_4_stateChanged(int arg1)
{
    bool sl=ui->checkBox_2->isChecked();
    bool ej=ui->checkBox_4->isChecked();
    bool ml=ui->checkBox_5->isChecked();
    bool mr=ui->checkBox_6->isChecked();

    if(sl && !ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(1));
    else if(!sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(2));
    else if(!sl && !ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(3));
    else if(!sl && !ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(4));
    else if(sl && !ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(7));
    else if(sl && !ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(6));
    else if(sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(5));
    else if(!sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(8));
    else if(!sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(9));
    else if(!sl && !ej && ml && mr)
        ui->tableView_afficher->setModel(E.triParType(10));
    else if(sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(11));
    else if(sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(12));
    else if(sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(13));
    else if(sl && !ej && ml && mr)
        ui->tableView_afficher->setModel(E.triParType(14));
    else if(sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(15));
    else
        ui->tableView_afficher->setModel(E.afficher());

}

void gestionEquipement::on_checkBox_5_stateChanged(int arg1)
{
    bool sl=ui->checkBox_2->isChecked();
    bool ej=ui->checkBox_4->isChecked();
    bool ml=ui->checkBox_5->isChecked();
    bool mr=ui->checkBox_6->isChecked();

    if(sl && !ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(1));
    else if(!sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(2));
    else if(!sl && !ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(3));
    else if(!sl && !ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(4));
    else if(sl && !ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(7));
    else if(sl && !ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(6));
    else if(sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(5));
    else if(!sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(8));
    else if(!sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(9));
    else if(!sl && !ej && ml && mr)
        ui->tableView_afficher->setModel(E.triParType(10));
    else if(sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(11));
    else if(sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(12));
    else if(sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(13));
    else if(sl && !ej && ml && mr)
        ui->tableView_afficher->setModel(E.triParType(14));
    else if(sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(15));
    else
        ui->tableView_afficher->setModel(E.afficher());
}

void gestionEquipement::on_checkBox_6_stateChanged(int arg1)
{
    bool sl=ui->checkBox_2->isChecked();
    bool ej=ui->checkBox_4->isChecked();
    bool ml=ui->checkBox_5->isChecked();
    bool mr=ui->checkBox_6->isChecked();

    if(sl && !ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(1));
    else if(!sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(2));
    else if(!sl && !ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(3));
    else if(!sl && !ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(4));
    else if(sl && !ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(7));
    else if(sl && !ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(6));
    else if(sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(5));
    else if(!sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(8));
    else if(!sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(9));
    else if(!sl && !ej && ml && mr)
        ui->tableView_afficher->setModel(E.triParType(10));
    else if(sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(11));
    else if(sl && ej && !ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(12));
    else if(sl && ej && !ml && mr)
        ui->tableView_afficher->setModel(E.triParType(13));
    else if(sl && !ej && ml && mr)
        ui->tableView_afficher->setModel(E.triParType(14));
    else if(sl && ej && ml && !mr)
        ui->tableView_afficher->setModel(E.triParType(15));
    else
        ui->tableView_afficher->setModel(E.afficher());
}

void gestionEquipement::on_lineEdit_RS_editingFinished()//edition du champs supprimer
{
   int id=ui->lineEdit_RS->text().toInt();
   //ui->tableView_afficher->setModel(E.rechercher(id));
   //ui->tableView_afficher->setModel(E.triParType(15));
}

void gestionEquipement::on_lineEdit_RS_textEdited(const QString &arg1)
{
    QString id=ui->lineEdit_RS->text();
    if(id.length()<1)
       ui->tableView_afficher->setModel(E.afficher());
    else
    ui->tableView_afficher->setModel(E.rechercher(id));

}

void gestionEquipement::on_Statistique_clicked()
{

       // ui->Gestion->setCurrentIndex(3);

            S.stat(ui->widget_stat);

}


void gestionEquipement::on_lineEdit_textEdited(const QString &arg1)
{
    
    QString id=ui->lineEdit->text();
    if(id.length()<1)
       ui->tableView_afficher->setModel(E.afficher());
    else
    ui->tableView_afficher->setModel(E.rechercher(id));

}

void gestionEquipement::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")
        ui->state->setText("Accepter"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher Accepter

    else if (data=="0")

        ui->state->setText("Refuser");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher Refuser
}


void gestionEquipement::on_OUVRIR_clicked()
{
    A.write_to_arduino("1");
}

void gestionEquipement::on_FERMER_clicked()
{
    A.write_to_arduino("0");
}



QSqlQueryModel* gestionEquipement::historic_ajouter()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT sysdate,id_eq,etat,type_eq,qte_eq FROM equipement ORDER BY SYSDATE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Effectué le"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantité"));
    return model;
}

QSqlQueryModel* gestionEquipement::historic_modfication()
{
    QSqlQueryModel* model= new QSqlQueryModel();
   // QString id_string=QString::number(id_eq);
    model->setQuery("SELECT sysdate,id_eq,etat,type_eq,qte_eq FROM equipement ORDER BY SYSDATE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Effectué le"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantité"));
    return model;
}

void gestionEquipement::Alert(int nb,QString nomProduit){
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















