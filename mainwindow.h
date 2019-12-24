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
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    int red=0,kolona=0;                     //promenljiva koja cuva velicinu reda i kolone
    int start[2]={-1,-1},end[2]={-1,-1};    //koordinate starta i cilja
    void SetStart(int i,int j);             //postavljanje starta u obliku (red,kolona)
    void SetEnd(int i,int j);               //postavljanje cilja u obliku (red,kolona)

private slots:
   // void NumChanged();
   // void StartPressed();
    void ButtonPressed();
    void Matrica();                         //pocetna alokacija matrice red=20, kolona=35
    void RedSet();                          //postavljanje redova na novi broj
    void KolonaSet();                       //postavljanje kolona na novi broj
    void Iscrtaj();                         //iscrtavanje grid mreze nakon promene
};
#endif // MAINWINDOW_H
