#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void refresh();
    ~MainWindow();

private slots:

    void on_ajouter_article_clicked();

    void on_supprimer_article_clicked();

    void on_modif_article_clicked();

    void on_pushButton_clicked();

    void on_pushButton_triPrix_clicked();

    void on_pushButton_triType_clicked();

    void on_lineEdit_rech_textChanged(const QString &arg1);

    void on_excel_clicked();

    void on_archiver_clicked();

    void on_pushButton_reactiver_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
