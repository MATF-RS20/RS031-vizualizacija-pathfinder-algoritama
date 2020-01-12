#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QSize>
#include <qrightclickbutton.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QRightClickButton *button[20][35];      //niz koji cuva buttone u obliku matrice
    int red=0,kolona=0;                     //promenljiva koja cuva velicinu reda i kolone
    int start[2]={-1,-1},end[2]={-1,-1};    //koordinate starta i cilja
    QVector<int> prepreke;                  //vektor koji cuva pozicije prepreka oblika 100*red + kolona
    void SetStart(int i,int j);             //postavljanje starta u obliku (red,kolona)
    void SetEnd(int i,int j);               //postavljanje cilja u obliku (red,kolona)
    void SetPrepreka(int i,int j);          //postavljanje prepreke u obliku(red,kolona)
    void ShowPath(QVector<int> put);        //ofarbaj put
    QVector<int> path;                      //put prethodnog algoritma
    void Paint(int i,int j,QColor boja);    //oboji dugme(red,kolona) u boju

private slots:
   // void NumChanged();
    void StartPressed();                    //pokretanje algoritma
    void ButtonPressed();                   //funkcija za crtanje po grid mrezi na osnovu cekiranog radiobuttona
    void Matrica();                         //pocetna alokacija matrice red=20, kolona=35
    void RedSet();                          //postavljanje redova na novi broj
    void KolonaSet();                       //postavljanje kolona na novi broj
    void Iscrtaj();                         //iscrtavanje grid mreze nakon promene
    void Clear();                           //vrati na pocetno
    void onRightClicked();                  //ako se button pritisne desnim klikom onda clear taj button
    void onMiddleClicked();                 //promeni odabir za iscrtavanje klikom na tockic
};
#endif // MAINWINDOW_H
