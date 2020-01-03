#include "algoritmi.h"
#include "mainwindow.h"

#include <QQueue>


Algoritmi::Algoritmi(int tstart[2],int tend[2],int tred,int tkolona, QVector<int> tprepreke)
    : red(tred),kolona(tkolona),prepreke(tprepreke) {
    start[0]=tstart[0];
    start[1]=tstart[1];
    end[0]=tend[0];
    end[1]=tend[1];
}



bool Algoritmi::outOfBounds(int x){
    int i=x/100;
    int j=x%100;

    if(i>=0 && i<red && j<kolona && j>=0) {
        return true;
    }
    else {
        return false;
    }
}

QVector<int> Algoritmi::getNeighbors(int n){
    QVector<int> *susedi= new QVector<int>();

    int i=n/100;
    int j=n%100;
    int indeks;

    //desno
    if(outOfBounds((i)*100+(j+1))){
         indeks=prepreke.indexOf((i)*100+(j+1));
        if(indeks==-1) {
            susedi->push_back((i)*100+(j+1));
        }
    }
    //dole-desno
    if(outOfBounds((i+1)*100+(j+1))){
        indeks=prepreke.indexOf((i+1)*100+(j+1));
        if(indeks==-1) {
            susedi->push_back((i+1)*100+(j+1));
        }
    }
    //gore-desno
    if(outOfBounds((i-1)*100+(j+1))){
        indeks=prepreke.indexOf((i-1)*100+(j+1));
        if(indeks==-1) {
            susedi->push_back((i-1)*100+(j+1));
        }
    }
    //dole
    if(outOfBounds((i+1)*100+(j))){
        indeks=prepreke.indexOf((i+1)*100+(j));
        if(indeks==-1) {
            susedi->push_back((i+1)*100+(j));
        }
    }


    //gore
    if(outOfBounds((i-1)*100+(j))){
        indeks=prepreke.indexOf((i-1)*100+(j));
        if(indeks==-1) {
            susedi->push_back((i-1)*100+(j));
        }
    }


    //levo
    if(outOfBounds((i)*100+(j-1))){
        indeks=prepreke.indexOf((i)*100+(j-1));
        if(indeks==-1) {
            susedi->push_back((i)*100+(j-1));
        }
    }

    //gore-levo
    //indeks=prepreke.indexOf((i-1)*100+(j-1));
    if(outOfBounds(n-101)){
        indeks=prepreke.indexOf(n-101);
        if(indeks==-1){
            susedi->push_back(n-101);
        }
    }

    //dole-levo
    if(outOfBounds((i+1)*100+(j-1))){
        indeks=prepreke.indexOf((i+1)*100+(j-1));
        if(indeks==-1) {
            susedi->push_back((i+1)*100+(j-1));
        }
    }
    return *susedi;
}

QVector<int> Algoritmi::DFS(int start, int end){
    QStack<int> *path = new QStack<int>();

    // Inicijalizacija skupa oznacenih cvorova
    // na prazan skup
    QVector<int> visited;

    // Na stek path i u skup posecenih cvorova stavi samo polazni cvor;
    visited.push_back(start);
    path->push(start);

    // Dok na steku path ima elemenata
    while (!path->isEmpty()) {
        // Uzmi cvor n sa vrha steka path;
        int n = path->top();

        // Ako je cvor n ciljni cvor
        if (n == end){
            // izvesti o uspehu i vrati put konstruisan na osnovu sadrzaja steka path
            qDebug()<<"Nadjen put:";
            //print('Pronadjen je put: {}'.format(path))
            return *path;
        }

        // Indikator da li cvor n ima neobidjenih suseda
        bool has_unvisited = false;

        // Ako n IMA potomaka koji nisu poseceni
        for (int m:getNeighbors(n)){
            if (visited.indexOf(m)==-1) {
                //(m not in visited)
                // Izaberi prvog takvog potomka m
                // i dodaj ga na vrh steka path i u skup posecenih cvorova
                path->push(m);
                visited.push_back(m);
                has_unvisited = true;
                break;
            }
        }
        // Inace izbaci n sa steka path
        if (!has_unvisited)
            path->pop();
    }

    // ako je petlja zavrsena put nije pronadjen,
    // izvesti da trazeni put ne postoji.
    qDebug()<<"Trazeni put ne postoji";
    QVector<int> nista;
    return nista;
}

QVector<int> Algoritmi::BFS(int start, int end){

    QStack<int> *path = new QStack<int>();

    // Pomocni red
    QQueue<int> queue =  QQueue<int>();

    // Inicijalizacija skupa oznacenih cvorova
    // na prazan skup
    QVector<int> visited;

    // Mapa direktnih predaka cvorova nadjenih prilikom obilaska grafa
    QVector<int> parent;

    // Dodajemo pocetni cvor u listu
    queue.push_back(start);
    parent.push_back(start);
    visited.push_back(start);

    // Sve dok red putanja nije prazna
    while(!queue.empty()) {

        // Skidamo pocetni cvor sa pocetka reda
        int n = queue.front();
        queue.pop_front();

        // Ako je n krajnji cvor
        if(n==end) {
            while (parent[n] != n) {
                path->push_back(n);
                int i = parent.indexOf(n);
                n = parent[i];
            }
            path->push_back(start);
            return *path;
        }

        for(int m : getNeighbors(n)){
            if(parent.indexOf(m)==-1){
                parent[m]=n;
                visited.push_back(m);
                queue.enqueue(m);
            }
        }


    }
    // ako je petlja zavrsena put nije pronadjen,
    // izvesti da trazeni put ne postoji.
    qDebug()<<"Trazeni put ne postoji";
    QVector<int> nista;
    return nista;
}

QVector<int> Algoritmi::Astar(int start,int end){
    QVector<int> *path = new QVector<int>();
    path->push_back(start);
    path->push_back(end);
    return *path;
}

QVector<int> Algoritmi::Dijkstra(int start,int end){
    QVector<int> *path = new QVector<int>();
    path->push_back(start);
    path->push_back(end);
    return *path;

}
