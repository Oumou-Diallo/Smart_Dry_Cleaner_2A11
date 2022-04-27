 #ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "depense.h"
#include <QtDebug>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintPreviewDialog>
#include <QMainWindow>
#include <QMainWindow>
#include <QDialog>
#include <QSpinBox>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include "equipement.h"
#include "statistique.h"
#include "statistiques.h"
#include "article.h"
#include "client.h"
#include "arduino.h"
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPainter>
#include <QSqlQuery>
#include <QDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    double num1=0,num2=0,resultat=0;
    double getlineEditNum();
    void writeResult(double tempresult);
public:
    //statistique:::





    QComboBox * cbox;
    QPushButton * qButton;
    QSpinBox * sBox;
    QTextEdit * tEdit;
    QHBoxLayout * Hlay;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void Alert(int nb,QString nomProduit);
     int getselectedclient();

private slots:



    void writetofile();

    void NumPressed();

    void MathButtonPressed();

    void EqualButton();

    void ChangeNumberSign();

    void Clear();

    void on_pb_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();



    void on_pushButton_plus_clicked();
    bool ajouter_historic_depense();
    QSqlQueryModel*  historic_ajouter_equipement();
    QSqlQueryModel* historic_modifier();
    QSqlQueryModel* historic_ajouter();
    QSqlQueryModel* historic_supprimer(int);
    void on_pushButton_moins_clicked();

    void on_pushButton_fois_clicked();

    void on_pushButton_diviser_clicked();

    void on_actionNouveau_triggered();

    void on_actionOuvrir_triggered();

    void on_actionSortir_triggered();

    void on_actionImprimer_triggered();

    void on_tri_date_clicked();

    void on_tri_identifiant_clicked();

    void on_tri_type_clicked();
    void Write_modifier(QString,int,QString,QString,QString);
    void Read_modifier(QString);
    void Write_ajouter(QString,int,QString,QString,QString);
    void Read_ajouter(QString);
    void Write_supprimer(QString,int,QString,QString,QString);
    void Read_supprimer(QString);






    void on_pushButton_ajouter_eq_clicked();

    void on_pushButton_modifier_eq_clicked();

    void on_pushButton_supprimer_eq_clicked();

    void on_radioButton_qte_eq_aff_clicked();

    void on_tri_id_eq_aff_clicked();

    void on_tri_type_eq_aff_clicked();

    void on_tri_etat_aff_clicked();

    void on_tri_qte_eq_aff_clicked();


    void on_lineEdit_rechercher_textEdited(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_ajouter_article_clicked();
    void refresh();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_modifier_article_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_excel_equipement_clicked();

    void on_pushButton_excel_depense_clicked();

    void on_radioButton_type_art_clicked();

    void on_radioButton_id_art_clicked();

    void on_radioButton_nom_art_clicked();

    void on_radioButton_prix_art_clicked();

    void on_lineEdit_rechercher_article_textEdited(const QString &arg1);



    void on_commandLinkButton_clicked();

    void on_pushButton_ajouter_client_clicked();

    void on_pushButton_supprimer_client_clicked();

    void on_pushButton_7_clicked();



    void on_lineEdit_textEdited(const QString &arg1);

    void on_radioButton_clicked();

    void on_tri_nom_cl_clicked();

    void on_tri_id_cl_clicked();

    void on_tri_service_cl_clicked();

    void on_pushButton_imprimer_client_clicked();

    void on_pushButton_statistique_client_clicked();

    void on_pushButton_excel_client_clicked();

    void on_pushButton_pdf_client_clicked();

    void on_pushButton_pdf_depense_clicked();


    
    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_hist_client_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    /*void on_OUVRIR_clicked();
    void update_label();
    void on_FERMER_clicked();*/

public:
    void on_spinBox_valueChanged(int arg1);

    void Alert();

private:
    QByteArray data;
    //Arduino A;
    int Seuil;
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    Ui::MainWindow *ui;
    Depense D,Dm;
    Article Ar;
    equipement E1;
    statistique S;
    statistiques SS;
    Client C;
};

#endif // MAINWINDOW_H
