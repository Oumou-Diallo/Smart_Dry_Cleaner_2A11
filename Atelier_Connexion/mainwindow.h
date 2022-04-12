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
    QComboBox * cbox;
    QPushButton * qButton;
    QSpinBox * sBox;
    QTextEdit * tEdit;
    QHBoxLayout * Hlay;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

    void on_pushButton_calculer_clicked();

    void on_pushButton_plus_clicked();
    QSqlQueryModel* historic_modifier(int);
    QSqlQueryModel* historic_ajouter(int);
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
    void on_actionTout_Selectionner_triggered();

private:
    Ui::MainWindow *ui;
    Depense D,Dm;
};

#endif // MAINWINDOW_H
