#include "algoritmi.h"
#include "mainwindow.h"
Algoritmi::Algoritmi(int tstart[2],int tend[2],int tred,int tkolona, QVector<int> tprepreke):
    red(tred),kolona(tkolona),prepreke(tprepreke)
{
start[0]=tstart[0];
start[1]=tstart[1];
end[0]=tend[0];
end[1]=tend[1];
}

QVector<int> Algoritmi::getNeighbors(int n){
    QVector<int> *susedi= new QVector<int>();

    int i=n/100;
    int j=n%100;
    int indeks;

    //gore-levo
    //indeks=prepreke.indexOf((i-1)*100+(j-1));
    if(outOfBounds(n-101)){
    indeks=prepreke.indexOf(n-101);
    if(indeks==-1)susedi->push_back(n-101);}

    //gore
    if(outOfBounds((i-1)*100+(j))){
    indeks=prepreke.indexOf((i-1)*100+(j));
    if(indeks==-1)susedi->push_back((i-1)*100+(j));}

    //gore-desno
    if(outOfBounds((i-1)*100+(j+1))){
    indeks=prepreke.indexOf((i-1)*100+(j+1));
    if(indeks==-1)susedi->push_back((i-1)*100+(j+1));}

    //desno
    if(outOfBounds((i)*100+(j+1))){
    indeks=prepreke.indexOf((i)*100+(j+1));
    if(indeks==-1)susedi->push_back((i)*100+(j+1));}

    //dole-desno
    if(outOfBounds((i+1)*100+(j+1))){
    indeks=prepreke.indexOf((i+1)*100+(j+1));
    if(indeks==-1)susedi->push_back((i+1)*100+(j+1));}

    //dole
    if(outOfBounds((i+1)*100+(j))){
    indeks=prepreke.indexOf((i+1)*100+(j));
    if(indeks==-1)susedi->push_back((i+1)*100+(j));}

    //dole-levo
    if(outOfBounds((i+1)*100+(j-1))){
    indeks=prepreke.indexOf((i+1)*100+(j-1));
    if(indeks==-1)susedi->push_back((i+1)*100+(j-1));}

    //levo
       if(outOfBounds((i)*100+(j-1))){
    indeks=prepreke.indexOf((i)*100+(j-1));
    if(indeks==-1)susedi->push_back((i)*100+(j-1));}
    return *susedi;
}

QVector<int> Algoritmi::DFS(int start, int end){
    QStack<int> path;

// Inicijalizacija skupa oznacenih cvorova
        // na prazan skup
        QVector<int> visited;

        // Na stek path i u skup posecenih cvorova stavi samo polazni cvor;
        visited.push_back(start);
        path.push(start);

        // Dok na steku path ima elemenata
        while (!path.isEmpty())
        {

            // Uzmi cvor n sa vrha steka path;
            int n = path.top();

            // Ako je cvor n ciljni cvor
            if (n == end){
                // izvesti o uspehu i vrati put konstruisan na osnovu sadrzaja steka path
                qDebug()<<"Nadjen put:";
                //print('Pronadjen je put: {}'.format(path))
                return path;}

            // Indikator da li cvor n ima neobidjenih suseda
            bool has_unvisited = false;

            // Ako n IMA potomaka koji nisu poseceni
            for (int m:getNeighbors(n)){
                if (visited.indexOf(m)==-1)//(m not in visited)
                    // Izaberi prvog takvog potomka m
                    // i dodaj ga na vrh steka path i u skup posecenih cvorova
                {path.push(m);
                    visited.push_back(m);
                    has_unvisited = true;
                    break;}
                }
            // Inace izbaci n sa steka path
            if (!has_unvisited)
                path.pop();
        }

        // ako je petlja zavrsena put nije pronadjen,
        // izvesti da trazeni put ne postoji.
        qDebug()<<"Trazeni put ne postoji";
        QVector<int> nista;
        return nista;
}

bool Algoritmi::outOfBounds(int x){
    int i=x/100;
    int j=x%100;

    if(i>=0 && i<red && j<kolona && j>=0)
    return true;
    else return false;
}

QVector<int> Algoritmi::BFS(int start, int end){

}

QVector<int> Algoritmi::Astar(int start,int end){

}

QVector<int> Algoritmi::Dijkstra(int start,int end){

}
