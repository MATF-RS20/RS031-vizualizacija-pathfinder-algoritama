#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMouseEvent>
#include "qrightclickbutton.h"
#include <algorithm>
#include "algoritmi.h"

static QSize velicina(20,20);          //podrazumevana velicina
//platno size WxH = 700x400
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //pocetna inicijalizacija programa

    //dohvati vrednosti iz spinboxova za red i kolonu i iscrtaj grid mrezu
    QSpinBox *redBox=MainWindow::findChild<QSpinBox*>("red");
    QSpinBox *kolonaBox=MainWindow::findChild<QSpinBox*>("kolona");
    red=redBox->value();
    kolona=kolonaBox->value();
    //nacrtaj maksimalan broj dugmica na grid mrezi
    Matrica();

    //omoguci promenu grid mreze pri promeni vrednosti spinboxova
    connect(redBox,SIGNAL(valueChanged(int)),this,SLOT(RedSet()));
    connect(kolonaBox,SIGNAL(valueChanged(int)),this,SLOT(KolonaSet()));

    //zavrsi iscrtavanje(postavi pocetno i krajnje polje)
    Iscrtaj();

    //povezi button clear
    QPushButton *clear = MainWindow::findChild<QPushButton*>("btnClear");
    connect(clear,SIGNAL(released()),
            this,SLOT(Clear()));

    //povezi start button
    QPushButton *start=MainWindow::findChild<QPushButton*>("btnStart");
    connect(start,SIGNAL(released()),
            this,SLOT(StartPressed()));

    //povezi timer za animaciju
    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Animiraj()));

    //povezivanje timera za softclear
    softcleartimer= new QTimer(this);
    softcleartimer->setSingleShot(true);
    connect(softcleartimer,SIGNAL(timeout()),this,SLOT(PromeniSoftClear()));

    QRadioButton *pocetni= MainWindow::findChild<QRadioButton*>("rPocetni");
    QPalette pal = pocetni->palette();
    pal.setColor(QPalette::Button, Qt::green);
    pocetni->setAutoFillBackground(false);
    pocetni->setPalette(pal);
    pocetni->update();
    connect(pocetni,SIGNAL(clicked()),this,SLOT(RadioClicked()));

    QRadioButton *krajnji= MainWindow::findChild<QRadioButton*>("rKrajnji");
    pal = krajnji->palette();
    pal.setColor(QPalette::Button, Qt::red);
    krajnji->setAutoFillBackground(false);
    krajnji->setPalette(pal);
    krajnji->update();
    connect(krajnji,SIGNAL(clicked()),this,SLOT(RadioClicked()));

    QRadioButton *prepreka= MainWindow::findChild<QRadioButton*>("rPrepreka");
    connect(prepreka,SIGNAL(clicked()),this,SLOT(RadioClicked()));
    Popup *tut;
    tut=new Popup(this);
    tut->move(200,124);
    tut->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::Matrica(){

    //napravi grid mrezu velicine (Red x Kolona)
    //sa pocetkom u tacki 30,20
    int i,j;
    for(i=0;i<red;i++)
    {
    for(j=0;j<kolona;j++)
    {
                    button[i][j] = new QRightClickButton(this);
                    button[i][j]->resize(velicina);
                    button[i][j]->move(30+velicina.rwidth()*j,20+velicina.rheight()*i);
                    button[i][j]->show();
                    connect(button[i][j],SIGNAL(released()),
                            this,SLOT(ButtonPressed()));
                    connect(button[i][j], SIGNAL(rightClicked()), this, SLOT(onRightClicked()));
                    connect(button[i][j], SIGNAL(middleClicked()), this, SLOT(onMiddleClicked()));
            }
        }


}


void MainWindow::ButtonPressed(){
    //funkcija iscrtavanja na osnovu cekiranog radiobuttona
    //i koordinata pritisnutog polja
    QRadioButton *pocetni= MainWindow::findChild<QRadioButton*>("rPocetni");
    QRadioButton *krajnji= MainWindow::findChild<QRadioButton*>("rKrajnji");

    QPushButton *trenutni= qobject_cast<QPushButton*>(sender());
    QPoint x;
    x=trenutni->pos();
    int velicinaDugmeta=(700/kolona) < (400/red) ? (700/kolona): (400/red);

    if(pocetni->isChecked())    SetStart((x.ry()-20)/velicinaDugmeta,(x.rx()-30)/velicinaDugmeta);
    else if (krajnji->isChecked()) SetEnd((x.ry()-20)/velicinaDugmeta,(x.rx()-30)/velicinaDugmeta);
    else SetPrepreka((x.ry()-20)/velicinaDugmeta,(x.rx()-30)/velicinaDugmeta);


}

void MainWindow::RedSet(){
    //funkcija za promenu broja redova
    QSpinBox *redBox=qobject_cast<QSpinBox*>(sender());
    red=redBox->value();
    Iscrtaj();
    Clear();
    //qDebug() <<"red"<< red;

}


void MainWindow::KolonaSet(){
    //funkcija za promenu broja kolona
    QSpinBox *kolonaBox=qobject_cast<QSpinBox*>(sender());
    kolona=kolonaBox->value();
    Iscrtaj();
    Clear();
    //qDebug() << kolona;
}



void MainWindow::Iscrtaj(){

    //funkcija koja vrsi crtanje tako sto
    //namesta da svaki button(polje) bude hidden
    //i nakon toga proverava da li treba povecati velicinu
    //polja (ukoliko se broj redova ili kolona smanjio)
    //kako bi mreza zauzimala istu velicinu na ekranu
    int i,j;

    for(i=0;i<20;i++)
    {for(j=0;j<35;j++){
          button[i][j]->hide();
            }}




    for(i=0;i<red;i++)
    {for(j=0;j<kolona;j++){

        int manji=(700/kolona) < (400/red) ? (700/kolona): (400/red);
        QSize newVelicina(manji,manji);
        button[i][j]->resize(newVelicina);
        button[i][j]->move(30+newVelicina.rwidth()*j,20+newVelicina.rheight()*i);
        button[i][j]->show();
    }}
    //namesta default start i end ako ne postoje
    //ili ako su postavljeni na red/kolonu koja ne postoji
    //qDebug()<<"start "<<start[0]<<" "<<start[1];
     if(start[0]==-1)SetStart(red/2,kolona/4);
     if(start[0]>=red-1)SetStart(red-1,start[1]);
     if(start[1]>=kolona-1)SetStart(start[0],kolona-1);

     if(end[0]==-1) SetEnd(red/2,3*kolona/4);
     if(end[0]>=red-1)SetEnd(red-1,end[1]);
     if(end[1]>=kolona-1)SetEnd(end[0],kolona-1);
}



void MainWindow::SetStart(int i, int j){
    //funkcija koja omogucava namestanje starta
    //tako sto brise prethodni start i stavlja novi

    if(start[0]>=0 && start[1]>=0){
        QPalette tmp = this->style()->standardPalette();
        button[start[0]][start[1]]->setPalette(tmp);
        button[start[0]][start[1]]->update();
    }

    //provera da li se postavlja preko cilja ili prepreke

    if(end[0]==i && end[1]==j){
        end[0]=-1; end[1]=-1;
    }

    int indeks=prepreke.indexOf(i*36+j);
    if(indeks!=-1){
        prepreke.remove(indeks);
    }

    Paint(i,j,Qt::green);

    start[0]=i;
    start[1]=j;
    PromeniSoftClear();
}

void MainWindow::SetEnd(int i, int j){
    //funkcija koja omogucava namestanje cilja
    //tako sto brise prethodni cilj i stavlja novi

    if(end[0]>=0 && end[1]>=0){
        QPalette tmp = this->style()->standardPalette();
        button[end[0]][end[1]]->setPalette(tmp);
        button[end[0]][end[1]]->update();
    }

    //provera da li se postavlja preko starta ili prepreke

    if(i==start[0] && j==start[1])
    {start[0]=-1; start[1]=-1;}

    int indeks=prepreke.indexOf(i*36+j);
    if(indeks!=-1){
        prepreke.remove(indeks);
    }

    Paint(i,j,Qt::red);
    end[0]=i;
    end[1]=j;
    PromeniSoftClear();
}

void MainWindow::SetPrepreka(int i, int j){
    //postavljanje prepreke na grid mrezi

    //provera da li se prepreka postavlja na start ili cilj
    //ako se postavlja treba se obrisati start i cilj
    if(start[0]==i && start[1]==j){
        start[0]=-1; start[1]=-1;
    }
    if(end[0]==i && end[1]==j){
        end[0]=-1; end[1]=-1;
    }
    //provera da li se prepreka postavlja na path
    int indeks=path.indexOf(i*36+j);
    if(indeks!=-1)path.remove(indeks);

    Paint(i,j,Qt::black);
    //globalni vektor prepreka oblika(36*red + kolona)
    prepreke.push_back(36*i+j);
    PromeniSoftClear();
}

void MainWindow::Clear(){
    if(softclear){
        SoftClear();
        //omoguciti fullclear ako je dva puta pritsnuto dugme clear u roku
        //od 5 sekundi
        softclear=false;
        softcleartimer->start(5000);
    }
    else{
 // qDebug()<<prepreke;
    timer->stop();
    if(objekat!=nullptr)objekat->korak->stop();

    //cisti boje prepreka na grid mrezi
    /*
    for(auto a: prepreke){
        QPalette tmp = this->style()->standardPalette();
        button[a/36][a%36]->setPalette(tmp);
        button[a/36][a%36]->update();
    }*/


    //cisti globalni vektor prepreka i vrsi ponovno iscrtavanje
    prepreke.clear();

    //cisti trenutni path
   /* for(auto a: path){
        QPalette tmp = this->style()->standardPalette();
        button[a/36][a%36]->setPalette(tmp);
        button[a/36][a%36]->update();
    } */
    path.clear();

    QPalette tmp = this->style()->standardPalette();
    for(int i=0;i<20;i++)
    {
    for(int j=0;j<35;j++)
    {
        button[i][j]->setPalette(tmp);
        button[i][j]->update();
            }
        }

    //vrati start i end na default
    SetStart(red/2,kolona/4);
    SetEnd(red/2,3*kolona/4);
    Iscrtaj();
    PromeniSoftClear();
 // qDebug()<<prepreke;
}}

void MainWindow::onRightClicked()
{
    QPushButton *trenutni= qobject_cast<QRightClickButton*>(sender());
    QPoint x;
    x=trenutni->pos();
    int velicinaDugmeta=(700/kolona) < (400/red) ? (700/kolona): (400/red);
    int i=(x.ry()-20)/velicinaDugmeta;
    int j=(x.rx()-30)/velicinaDugmeta;

    //provera da li je polje prepreka
    // ako jeste ukloni ga iz vektora prepreka
    int indeks=prepreke.indexOf(i*36+j);
    if(indeks!=-1){
        prepreke.remove(indeks);
    }

    //provera da li je pocetno polje
    //i obrisati ga ako jeste
    if(i==start[0] && j==start[1])
    {start[0]=-1; start[1]=-1;}

    //provera da li je polje cilj
    //i obrisati ga ako jeste
    if(i==end[0] && j==end[1])
    {end[0]=-1; end[1]=-1;}

    QPalette tmp = this->style()->standardPalette();
    button[i][j]->setPalette(tmp);
    button[i][j]->update();
    PromeniSoftClear();

}


void MainWindow::StartPressed(){
    //sakupi sve podatke
    std::sort(prepreke.begin(),prepreke.end());
    QComboBox *alg= MainWindow::findChild<QComboBox*>("selectBox");


    qDebug() << "Pritisnut start, algoritam: "<<alg->currentText();
    qDebug()<<"Start: "<<start[0]<<" "<<start[1];
    qDebug()<<"Cilj: "<<end[0]<<" "<<end[1];
    qDebug()<<"Prepreke: ";
    for(auto i:prepreke)
    qDebug()<<i/36<<" "<<i%36;


    if(start[0]==-1 || start[1]==-1){
        QMessageBox::information(
            this,
            tr(""),
            tr("Molim vas odaberite pocetno polje") );
        return;
    }
    if(end[0]==-1 ||end[1]==-1 ){
        QMessageBox::information(
            this,
            tr(""),
            tr("Molim vas odaberite krajnje polje") );
        return;
    }
    //soft ciscenje
    SoftClear();
    PromeniSoftClear();
    //postavi indikator
    pronadjen_put=false;

    //provera da li je dozvoljeno diagonalno kretanje
    QCheckBox *dg=MainWindow::findChild<QCheckBox*>("checkDiagonalno");
    if(dg->isChecked()) allowDiagonal=true;
    else allowDiagonal=false;

    //proveri koji je algoritam i pozovi ga
    objekat=new Algoritmi(start, end, red,  kolona, prepreke, button,allowDiagonal);
    if(alg->currentIndex()==0){

        path=objekat->DFS(start[0]*36+start[1],end[0]*36+end[1]);
        //ShowPath(path);
        put=path;
        timer->start(200);
        if(!put.isEmpty()){
            pronadjen_put=true;
            put.pop_front();
            put.pop_back();
            std::reverse(put.begin(), put.end());
            }
        qDebug()<<path;

    }

    if(alg->currentIndex()==1){

       path=objekat->BFS(start[0]*36+start[1],end[0]*36+end[1]);
       //ShowPath(path);
       put=path;
       //prikazi animiran put
       timer->start(200);
       if(!put.isEmpty()){
            pronadjen_put=true;
            put.pop_front();
            put.pop_back();
            }
       qDebug()<<path;
    }
    if(alg->currentIndex()==2){

       path=objekat->Dijkstra(start[0]*36+start[1],end[0]*36+end[1]);
       //ShowPath(path);
       put=path;
       //prikazi animiran put
       timer->start(200);
       if(!put.isEmpty()){
            pronadjen_put=true;
            put.pop_front();
            put.pop_back();
            }
       qDebug()<<path;
    }

    if(alg->currentIndex()==3){

       path=objekat->Astar(start[0]*36+start[1],end[0]*36+end[1],1);
       //ShowPath(path);
       put=path;
       //prikazi animiran put
       timer->start(200);
       if(!put.isEmpty()){
            pronadjen_put=true;
            put.pop_front();
            put.pop_back();

            }
       qDebug()<<path;
    }
}

void MainWindow::ShowPath(QVector<int> put){
    for(int x=1;x<put.size()-1;x++){
        int i=put[x]/36;
        int j=put[x]%36;
        Paint(i,j,Qt::yellow);
    }
}

void MainWindow::Paint(int i,int j,QColor boja){
    QPalette pal = button[i][j]->palette();
    pal.setColor(QPalette::Button, boja);
    button[i][j]->setAutoFillBackground(true);
    button[i][j]->setPalette(pal);
    button[i][j]->update();
}

void MainWindow::Animiraj()
{
    if(!objekat->korak->isActive()){
     if(!put.isEmpty()){
          int i=put.last()/36;
          int j=put.last()%36;
          Paint(i,j,Qt::blue);
         put.pop_back();
      }
    else{
         if(!pronadjen_put){
             QMessageBox::information(
                 this,
                 tr(""),
                 tr("Put ne postoji.") );
         }
         timer->stop();

     }
    }

}

void MainWindow::onMiddleClicked(){
    QRadioButton *pocetni= MainWindow::findChild<QRadioButton*>("rPocetni");
    QRadioButton *krajnji= MainWindow::findChild<QRadioButton*>("rKrajnji");
    QRadioButton *prepreka= MainWindow::findChild<QRadioButton*>("rPrepreka");

    if(pocetni->isChecked()){
        pocetni->setChecked(false);
        pocetni->setAutoFillBackground(false);
        pocetni->update();
        krajnji->setChecked(true);
        krajnji->setAutoFillBackground(true);
        krajnji->update();
    }
    else if(krajnji->isChecked()){
        krajnji->setChecked(false);
        krajnji->setAutoFillBackground(false);
        krajnji->update();
        prepreka->setChecked(true);
    }
    else {
        prepreka->setChecked(false);
        pocetni->setChecked(true);
        pocetni->setAutoFillBackground(true);
        pocetni->update();
    }

}

void MainWindow::SoftClear(){
    timer->stop();
    if(objekat!=nullptr)objekat->korak->stop();
    path.clear();

    QPalette tmp = this->style()->standardPalette();
    for(int i=0;i<20;i++)
    {
    for(int j=0;j<35;j++)
    {
        button[i][j]->setPalette(tmp);
        button[i][j]->update();
            }
        }
    SetStart(start[0],start[1]);
    SetEnd(end[0],end[1]);
    for(auto x: prepreke){
        Paint(x/36,x%36,Qt::black);
    }

}

void MainWindow::PromeniSoftClear(){
    softclear=true;
}

void MainWindow::RadioClicked(){
    QRadioButton *pocetni= MainWindow::findChild<QRadioButton*>("rPocetni");
    QRadioButton *krajnji= MainWindow::findChild<QRadioButton*>("rKrajnji");

    QRadioButton *tmp= qobject_cast<QRadioButton*>(sender());
    if(tmp->text()=="pocetni"){
        krajnji->setAutoFillBackground(false);
        pocetni->setAutoFillBackground(true);
    }

    else if (tmp->text()=="krajnji"){
        krajnji->setAutoFillBackground(true);
        pocetni->setAutoFillBackground(false);
    }
    else{
        krajnji->setAutoFillBackground(false);
        pocetni->setAutoFillBackground(false);
    }
}
