#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMouseEvent>
#include "qrightclickbutton.h"
#include <algorithm>

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
}

MainWindow::~MainWindow()
{
    delete ui;
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
    qDebug() <<"red"<< red;

}


void MainWindow::KolonaSet(){
    //funkcija za promenu broja kolona
    QSpinBox *kolonaBox=qobject_cast<QSpinBox*>(sender());
    kolona=kolonaBox->value();
    Iscrtaj();
    qDebug() << kolona;
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
    qDebug()<<"start "<<start[0]<<" "<<start[1];
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



    QPalette pal = button[i][j]->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    button[i][j]->setAutoFillBackground(true);
    button[i][j]->setPalette(pal);
    button[i][j]->update();

    start[0]=i;
    start[1]=j;
}

void MainWindow::SetEnd(int i, int j){
    //funkcija koja omogucava namestanje cilja
    //tako sto brise prethodni cilj i stavlja novi

    if(end[0]>=0 && end[1]>=0){
        QPalette tmp = this->style()->standardPalette();
        button[end[0]][end[1]]->setPalette(tmp);
        button[end[0]][end[1]]->update();
    }

    QPalette pal = button[i][j]->palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    button[i][j]->setAutoFillBackground(true);
    button[i][j]->setPalette(pal);
    button[i][j]->update();
    end[0]=i;
    end[1]=j;
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


    QPalette pal = button[i][j]->palette();
    pal.setColor(QPalette::Button, QColor(Qt::black));
    button[i][j]->setAutoFillBackground(true);
    button[i][j]->setPalette(pal);
    button[i][j]->update();
    //globalni vektor prepreka oblika(100*red + kolona)
    prepreke.push_back(100*i+j);
    //qDebug()<<"Start: "<<start[0]<<" "<<start[1]<<"\t Cilj: "<<end[0]<<" "<<end[1];
}

void MainWindow::Clear(){

 // qDebug()<<prepreke;
    //cisti boje prepreka na grid mrezi
    for(auto a: prepreke){
        QPalette tmp = this->style()->standardPalette();
        button[a/100][a%100]->setPalette(tmp);
        button[a/100][a%100]->update();
    }
    //cisti globalni vektor prepreka i vrsi ponovno iscrtavanje
    prepreke.clear();

    //vrati start i end na default
    SetStart(red/2,kolona/4);
    SetEnd(red/2,3*kolona/4);
    Iscrtaj();
 // qDebug()<<prepreke;
}

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
    int indeks=prepreke.indexOf(i*100+j);
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

}


void MainWindow::StartPressed(){
    //sakupi sve podatke
    std::sort(prepreke.begin(),prepreke.end());
    qDebug() << "Pritisnut start";
    qDebug()<<"Prepreke"<<prepreke;
    //proveri koji je algoritam i pozovi ga
}
