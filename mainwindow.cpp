#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "article.h"
#include <QMessageBox>
#include"QtPrintSupport/QPrinter"
#include"QPainter"
#include <QPrintDialog>
#include <QTextDocument>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
Article Ar;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    ui->tableView_article->setModel(Ar.Afficher());
    ui->tableView_historique->setModel(Ar.historique());
    ui->tableView_archive->setModel(Ar.AfficherArchive());
}


void MainWindow::on_ajouter_article_clicked()
{
    int prix = ui->prix->text().toInt();
    QString nom = ui->nom->text();
    //QString type = ui->type->text();
    QString type = ui->comboBox->currentText();

    Article A(nom,prix,type);
    bool ok = A.ajouter();
    if(ok)
    {
        Ar.ajouterHistorique("ajout article");
        refresh();
        QMessageBox::information(nullptr, QObject::tr("success"),
                    QObject::tr("article ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("article non ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_supprimer_article_clicked()
{
    int id = ui->id_article->text().toInt();
    bool ok = Ar.supprimer(id);
    if(ok)
    {
        Ar.ajouterHistorique("suppression article");
        refresh();
        QMessageBox::information(nullptr, QObject::tr("success"),
                    QObject::tr("article supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("article non supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_modif_article_clicked()
{
    int id = ui->id_article->text().toInt();
    QString nom = ui->nom_2->text();
    bool ok = Ar.modifier(id,nom);
    if(ok)
    {
        Ar.ajouterHistorique("modification article");
        refresh();
        QMessageBox::information(nullptr, QObject::tr("success"),
                    QObject::tr("article modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("article non modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableView_article->setModel(Ar.triNom());
}

void MainWindow::on_pushButton_triPrix_clicked()
{
    ui->tableView_article->setModel(Ar.triPrix());

}

void MainWindow::on_pushButton_triType_clicked()
{
    ui->tableView_article->setModel(Ar.triType());
}

void MainWindow::on_lineEdit_rech_textChanged(const QString &arg1)
{
    ui->tableView_article->setModel(Ar.cherch_art(arg1));
}

void MainWindow::on_excel_clicked()
{
    QTableView *table;
       table = ui->tableView_article;

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
           QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
       }
}

void MainWindow::on_archiver_clicked()
{
    int id = ui->id_article->text().toInt();
    QSqlQueryModel * model= new QSqlQueryModel();
    QString idS = QString::number(id);
        model->setQuery("select * from Articles WHERE ID = "+idS);
   Article A(model->data(model->index(0,1)).toString(),model->data(model->index(0,2)).toInt(),model->data(model->index(0,3)).toString());
    bool ok = Ar.supprimer(id);
    bool ok1 = A.archiver();
    if(ok && ok1)
    {
        Ar.ajouterHistorique("article archive");
        refresh();
        QMessageBox::information(nullptr, QObject::tr("success"),
                    QObject::tr("article archive.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("article non archive.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_reactiver_clicked()
{
    int id = ui->lineEdit_arch->text().toInt();
    QSqlQueryModel * model= new QSqlQueryModel();
    QString idS = QString::number(id);
        model->setQuery("select * from Articles_archives WHERE ID = "+idS);
   Article A(model->data(model->index(0,1)).toString(),model->data(model->index(0,2)).toInt(),model->data(model->index(0,3)).toString());
    bool ok = Ar.desArchiver(id);
    bool ok1 = A.ajouter();
    if(ok && ok1)
    {
        Ar.ajouterHistorique("article active");
        refresh();
        QMessageBox::information(nullptr, QObject::tr("success"),
                    QObject::tr("article active.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("article non active.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
