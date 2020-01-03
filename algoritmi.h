#ifndef ALGORITMI_H
#define ALGORITMI_H

#include <QObject>
#include <QVector>
#include <QStack>
#include <QDebug>
class Algoritmi
{

public:
    Algoritmi(int tstart[2],int tend[2],int tred,int tkolona, QVector<int> tprepreke);  //konstruktor
    QVector<int> DFS(int start,int end);
    QVector<int> getNeighbors(int n);
    QVector<int> BFS(int start, int end);
    QVector<int> Astar(int start,int end);
    QVector<int> Dijkstra(int start,int end);
    QVector<int> BFS2(int start, int end);
private:

int red=0,kolona=0;                     //promenljiva koja cuva velicinu reda i kolone
int start[2]={-1,-1},end[2]={-1,-1};    //koordinate starta i cilja
QVector<int> prepreke;                  //vektor koji cuva pozicije prepreka oblika 100*red + kolona
bool outOfBounds(int x);                 //provera da li je polje u matrici
QVector<int> visited;
};

#endif // ALGORITMI_H
