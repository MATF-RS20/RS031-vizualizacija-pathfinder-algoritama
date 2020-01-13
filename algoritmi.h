#ifndef ALGORITMI_H
#define ALGORITMI_H

#include <QObject>
#include <QVector>
#include <QStack>
#include <QDebug>
#include <QTimer>
#include <qrightclickbutton.h>
class Algoritmi: public QObject
{
    Q_OBJECT
public:
    Algoritmi(int tstart[2],int tend[2],int tred,int tkolona, QVector<int> tprepreke,QRightClickButton *button[20][35]);  //konstruktor
    virtual ~Algoritmi(){}
    QVector<int> DFS(int start,int end);
    QVector<int> getNeighbors(int n);
    QVector<int> BFS(int start, int end);
    QVector<int> Astar(int start,int end);
    QVector<int> Dijkstra(int start,int end);
    QTimer *korak;

private:
int red=0,kolona=0;                     //promenljiva koja cuva velicinu reda i kolone
int start[2]={-1,-1},end[2]={-1,-1};    //koordinate starta i cilja
QVector<int> prepreke;                  //vektor koji cuva pozicije prepreka oblika 100*red + kolona
bool outOfBounds(int x);                 //provera da li je polje u matrici
QVector<int> visited;
QVector<QVector<int>> redovi;          //Vektor koji prica do kog je reda stigao algoritam
int br_reda=0;
void Paint(int i,int j,QColor boja);    //oboji dugme
QRightClickButton *button[20][35];      //niz koji cuva buttone u obliku matrice

private slots:
    void Animiraj();                    //Animacija pojedinacnog koraka
};

#endif // ALGORITMI_H
