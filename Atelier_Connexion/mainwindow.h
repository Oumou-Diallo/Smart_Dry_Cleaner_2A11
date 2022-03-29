#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "depense.h"
#include <QtDebug>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintPreviewDialog>
#include <QMainWindow>

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pb_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_calculer_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_moins_clicked();

    void on_pushButton_fois_clicked();

    void on_pushButton_diviser_clicked();

    void on_actionNouveau_triggered();

    void on_actionOuvrir_triggered();

    void on_actionSortir_triggered();

    void on_actionImprimer_triggered();

private:
    Ui::MainWindow *ui;
    Depense D,Dm;
};

#endif // MAINWINDOW_H
