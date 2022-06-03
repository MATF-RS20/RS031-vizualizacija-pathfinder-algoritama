#include "headers/algoritmi.h"
#include "headers/mainwindow.h"
#include <QQueue>

Algoritmi::Algoritmi(int tstart[2],int tend[2],int tred,int tkolona, QVector<int> tprepreke, QRightClickButton *butto[20][35], bool diag)
    : red(tred),kolona(tkolona),prepreke(tprepreke),diagonalno(diag) {
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

Algoritmi::~Algoritmi(){
    delete **button;
    delete korak;
}

bool Algoritmi::outOfBounds(int x){
    int i=x/36;
    int j=x%36;
    if(i==0 && j==0)return true;
    if(i>=0 && i<red && j<kolona && j>=0) {
        return true;
    }
    else {
        return false;
    }
}

QVector<int> Algoritmi::getNeighbors(int n){
    QVector<int> *susedi= new QVector<int>();

    int i=n/36;
    int j=n%36;
    int indeks;

    //desno
    if(outOfBounds((i)*36+(j+1))){
         indeks=prepreke.indexOf((i)*36+(j+1));
        if(indeks==-1) {
            susedi->push_back((i)*36+(j+1));
        }
    }
    //dole-desno
    if(outOfBounds((i+1)*36+(j+1))){
        indeks=prepreke.indexOf((i+1)*36+(j+1));
        if(indeks==-1) {
            susedi->push_back((i+1)*36+(j+1));
        }
    }
    //gore-desno
    if(outOfBounds((i-1)*36+(j+1))){
        indeks=prepreke.indexOf((i-1)*36+(j+1));
        if(indeks==-1) {
            susedi->push_back((i-1)*36+(j+1));
        }
    }
    //dole
    if(outOfBounds((i+1)*36+(j))){
        indeks=prepreke.indexOf((i+1)*36+(j));
        if(indeks==-1) {
            susedi->push_back((i+1)*36+(j));
        }
    }


    //gore
    if(outOfBounds((i-1)*36+(j))){
        indeks=prepreke.indexOf((i-1)*36+(j));
        if(indeks==-1) {
            susedi->push_back((i-1)*36+(j));
        }
    }


    //levo
    if(outOfBounds((i)*36+(j-1))){
        indeks=prepreke.indexOf((i)*36+(j-1));
        if(indeks==-1) {
            susedi->push_back((i)*36+(j-1));
        }
    }

    //gore-levo
    //indeks=prepreke.indexOf((i-1)*36+(j-1));
    if(outOfBounds((i-1)*36+(j-1))){
        indeks=prepreke.indexOf((i-1)*36+(j-1));
        if(indeks==-1){
            susedi->push_back((i-1)*36+(j-1));
        }
    }

    //dole-levo
    if(outOfBounds((i+1)*36+(j-1))){
        indeks=prepreke.indexOf((i+1)*36+(j-1));
        if(indeks==-1) {
            susedi->push_back((i+1)*36+(j-1));
        }
    }
    return *susedi;
}

QVector<int> Algoritmi::DFS(int start, int end){
    QStack<int> *path = new QStack<int>();
    visited=QVector<int>(21*36,1);
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
        QVector<int> komsije;
        if(diagonalno) komsije=getNeighbors(n);
        else komsije=getNeighbors2(n);
        // Ako n IMA potomaka koji nisu poseceni
        for (int m:komsije){
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
    visited=QVector<int>(21*36,0);
    // Pomocni red
    QQueue<int> queue =  QQueue<int>();

    // Mapa direktnih predaka cvorova nadjenih prilikom obilaska grafa
    QVector<int> parent = QVector<int>(21*36,0);

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
        QVector<int> komsije;
        if(diagonalno) komsije=getNeighbors(n);
        else komsije=getNeighbors2(n);

        for(int m : komsije){
            if(visited[m]==0){
                parent[m]=n;
                visited[m]=1;
                queue.enqueue(m);
                krk.push_back(m);
            }
        }
    if(!krk.isEmpty()){redovi.push_back(krk);korak->start(20);}
    }
    // ako je petlja zavrsena put nije pronadjen,
    // izvesti da trazeni put ne postoji.

    qDebug()<<"Trazeni put ne postoji";
    QVector<int> *nista=new QVector<int>();
    return *nista;
}

QVector<int> Algoritmi::Dijkstra(int start, int end){

    return Astar(start,end,0);
}

QVector<int> Algoritmi::Astar(int start,int end,int tipHeuristike){
            // Zatvorena lista je inicijalno prazna, a otvorena lista sadrzi samo polazni cvor
            QVector<int> open_list;
            open_list.push_back(start);
            QVector<int> closed_list ;

            //ako nije dozvoljeno diagonalno heuristika je manhattan
            if(diagonalno==false && tipHeuristike==1) tipHeuristike=2;

            // g sadrzi tekuce udaljenosti od polaznog cvora (start) do ostalih cvorova, ukoliko se cvor ne nalazi
            // u mapi, podrazumevana vrednost udaljenosti je beskonacno
            QVector<int> g(21*36,999);

            // Udaljenost polaznog cvora od samog sebe je 0
            g[start] = 0;

            // Mapa parents cuva roditelje cvorova
            QVector<int> parent(21*36,999);
            parent[start] = start;
            int n = 0;
            // Izvrsavaj dok god ima elemenata u otvorenoj listi
            while (!open_list.isEmpty()) {

                QVector<int> krk;
                n=-1;
                for(int v:open_list)
                {if (n == -1 or g[v] + Heuristika(v,tipHeuristike) < g[n] +  Heuristika(n,tipHeuristike))
                        n = v;}

                if (n == -1){
                    qDebug()<<"Trazeni put ne postoji";
                    return QVector<int>(0);}

                // Ako je n ciljni cvor, izvesti o uspehu i vrati resenje konstruisuci put
                // od polaznog do ciljnog cvora (iduci unazad — od ciljnog cvora).

                    QVector<int> path;

                    // do-while petlja ne postoji u Python-u
                if(n==end) {
                    while (parent[n] != n) {
                        path.push_back(n);
                        n = parent[n];
                    }
                    path.push_back(start);
                    return path;
                }


                // Za svaki cvor m koji je direktno dostupan izn𝑛 uradi sledece:
                QVector<int> komsije;
                if(diagonalno) komsije=getNeighbors(n);
                else komsije=getNeighbors2(n);

                for (int m:komsije){

                    // Ako m nije ni u otvorenoj ni u zatvorenoj listi, dodaj ga u otvorenu listu
                    // i oznaci n kao njegovog roditelja.
                    //if (m not in open_list and m not in closed_list)
                    int opn,cls;
                    opn=open_list.indexOf(m);
                    cls=closed_list.indexOf(m);
                    if (opn==-1 && cls==-1){
                        open_list.push_back(m);
                        parent[m] = n;
                        g[m] = g[n] + 1;

                                                    }

                    // Inace, proveri da li je put od polaznog cvora do cvora m preko
                    // cvora n bolji (kraci ili jeftiniji) od postojeceg puta do m
                    // (trenutna vrednost g(m)). Ako jeste, promeni informaciju o roditelju
                    // cvora m na cvor n i azuriraj vrednosti g(m), a ako je
                    // m bio u zatvorenoj listi, prebaci ga u otvorenu.
                    else{
                        if (g[m] > g[n] + 1)
                            {g[m] = g[n] + 1;
                            parent[m] = n;

                            if (cls!=-1){
                                closed_list.remove(cls);
                                open_list.push_back(m);}
                             }
                    }

            }
                // Izbaci n iz otvorene liste i dodaj ga u zatvorenu listu
                open_list.remove(open_list.indexOf(n));
                closed_list.push_back(n);
                //animiraj
                if(n!=start)krk.push_back(n);
                if(!krk.isEmpty()){redovi.push_back(krk);korak->start(20);}
            }
            //  Obavesti da trazeni put ne postoji (otvorena lista je prazna i uspeh nije prijavljen).
            qDebug()<<"Trazeni put ne postoji";
            return QVector<int>(0);


}

void Algoritmi::Animiraj()
{   if(!redovi.isEmpty()){
    while(!redovi[0].isEmpty()){
         int i=redovi[0].first()/36;
         int j=redovi[0].first()%36;
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

int Algoritmi::Heuristika(int x,int tip){
    if(tip==0)return 0;

    else if (tip==1){
    int a = abs(x/36 - end[0]);
    int b = abs(x%36 - end[1]);
    return a>b? a:b;}

    else {
        return HeuristikaManhattan(x);
    }
}

QVector<int> Algoritmi::getNeighbors2(int n){
    QVector<int> *susedi= new QVector<int>();

    int i=n/36;
    int j=n%36;
    int indeks;

    //desno
    if(outOfBounds((i)*36+(j+1))){
         indeks=prepreke.indexOf((i)*36+(j+1));
        if(indeks==-1) {
            susedi->push_back((i)*36+(j+1));
        }
    }

    //dole
    if(outOfBounds((i+1)*36+(j))){
        indeks=prepreke.indexOf((i+1)*36+(j));
        if(indeks==-1) {
            susedi->push_back((i+1)*36+(j));
        }
    }


    //gore
    if(outOfBounds((i-1)*36+(j))){
        indeks=prepreke.indexOf((i-1)*36+(j));
        if(indeks==-1) {
            susedi->push_back((i-1)*36+(j));
        }
    }


    //levo
    if(outOfBounds((i)*36+(j-1))){
        indeks=prepreke.indexOf((i)*36+(j-1));
        if(indeks==-1) {
            susedi->push_back((i)*36+(j-1));
        }
    }
    return *susedi;
}

int Algoritmi::HeuristikaManhattan(int x){
    int a = abs(x/36 - end[0]);
    int b = abs(x%36 - end[1]);
    return a+b;
}
