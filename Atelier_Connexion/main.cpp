#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QTranslator>
#include <QInputDialog>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;
    QTranslator guide;
    QStringList langage;
    langage <<"Francais" <<"Anglais" <<"Chinois"<<"Portuguais";
    QString lang =QInputDialog::getItem(NULL,"Langue",
                                        "Langue",langage);

    if(lang== "Chinois")
    {

       t.load(":/chineese.qm");
       guide.load("C:\Qt\Qt5.9.9\5.9.9\mingw53_32\translations/qt_zh_CN.qm");

    }else if(lang == "Anglais")
    {

         t.load(":/english.qm");
         guide.load("C:\Qt\Qt5.9.9\5.9.9\mingw53_32\translations/qtbase_en.qm");
    }

    else if(lang == "Portuguais")
        {

             t.load(":/portuguese.qm");
             //guide.load("C:\Qt\Qt5.9.9\5.9.9\mingw53_32\translations/qtbase_en.qm");
        }

    if(lang != "Francais")
    {


        a.installTranslator(&t);
        a.installTranslator(&guide);

    }


    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {
        w.show();
        QMessageBox::critical(nullptr, QObject::tr("la base de donnée est ouverte"),
                    QObject::tr("connexion réussie.\n"
                                "Cliquez Cancel pour quitter."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("la base de donnée est non ouverte"),
                    QObject::tr("connexion échouée.\n"
                                "Cliquez Cancel pour quitter."), QMessageBox::Cancel);



    return a.exec();
}
