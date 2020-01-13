#include "algoritmi.h"
#include "mainwindow.h"
#include <QQueue>

Algoritmi::Algoritmi(int tstart[2],int tend[2],int tred,int tkolona, QVector<int> tprepreke, QRightClickButton *butto[20][35])
    : red(tred),kolona(tkolona),prepreke(tprepreke) {
    start[0]=tstart[0];
    start[1]=tstart[1];
    end[0]=tend[0];
    end[1]=tend[1];
    //povezi timer za animaciju
    korak= new QTimer();
    connect(korak,SIGNAL(timeout()),this,SLOT(Animiraj()));

    for(int i=0;i<20;i++)
    {
    for(int j=0;j<35;j++)
    {
                    button[i][j] = butto[i][j];
            }
        }

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
    visited=QVector<int>(2036,1);
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

                //deo za animaciju
                QVector<int> krk;
                krk.push_back(m);
                redovi.push_back(krk);
                korak->start(50);

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
    QVector<int> *nista=new QVector<int>();
    return *nista;
}

QVector<int> Algoritmi::BFS(int start, int end){

    QStack<int> *path = new QStack<int>();
    visited=QVector<int>(2036,0);
    // Pomocni red
    QQueue<int> queue =  QQueue<int>();

    // Mapa direktnih predaka cvorova nadjenih prilikom obilaska grafa
    QVector<int> parent = QVector<int>(2036,0);

    // Dodajemo pocetni cvor u listu
    queue.push_back(start);
    parent[start]=start;
    visited[start]=1;

    // Sve dok red putanja nije prazna
    while(!queue.empty()) {

        QVector<int> krk;
        // Skidamo pocetni cvor sa pocetka reda
        int n = queue.front();
        queue.pop_front();

        // Ako je n krajnji cvor
        if(n==end) {
            while (parent[n] != n) {
                path->push_back(n);
                n = parent[n];
            }
            path->push_back(start);
            return *path;
        }
        // Ako nije dodaj neposecene susede u red
        // i postavi n kao roditelja
        for(int m : getNeighbors(n)){
            if(visited[m]==0){
                parent[m]=n;
                visited[m]=1;
                queue.enqueue(m);
                krk.push_back(m);
            }
        }
    if(!krk.isEmpty()){redovi.push_back(krk);korak->start(50);}
    }
    // ako je petlja zavrsena put nije pronadjen,
    // izvesti da trazeni put ne postoji.

    qDebug()<<"Trazeni put ne postoji";
    QVector<int> *nista=new QVector<int>();
    return *nista;
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

void Algoritmi::Animiraj()
{   if(!redovi.isEmpty()){
    while(!redovi[0].isEmpty()){
         int i=redovi[0].first()/100;
         int j=redovi[0].first()%100;
         if(i==end[0] && j==end[1]){redovi.clear();redovi.push_back(QVector<int>(0));break;}
        Paint(i,j,Qt::yellow);
        redovi[0].pop_front();
     }
    redovi.pop_front();
}
else{
        korak->stop();
    }
}

void Algoritmi::Paint(int i,int j,QColor boja){
    QPalette pal = button[i][j]->palette();
    pal.setColor(QPalette::Button, boja);
    button[i][j]->setAutoFillBackground(true);
    button[i][j]->setPalette(pal);
    button[i][j]->update();
}
