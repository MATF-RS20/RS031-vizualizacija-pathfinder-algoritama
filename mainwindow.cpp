#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

QPushButton *button[20][35];     //niz koji cuva buttone u obliku matrice
QSize velicina(20,20);          //podrazumevana velicina
//platno size WxH = 700x400
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSpinBox *redBox=MainWindow::findChild<QSpinBox*>("red");
    QSpinBox *kolonaBox=MainWindow::findChild<QSpinBox*>("kolona");
    red=redBox->value();
    kolona=kolonaBox->value();
    Matrica();
    connect(redBox,SIGNAL(valueChanged(int)),this,SLOT(RedSet()));
    connect(kolonaBox,SIGNAL(valueChanged(int)),this,SLOT(KolonaSet()));
    Iscrtaj();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Matrica(){
    int i,j;


    for(i=0;i<red;i++)
    {
    for(j=0;j<kolona;j++)
    {
                    button[i][j] = new QPushButton("",this);
                    button[i][j]->resize(velicina);
                    button[i][j]->move(30+velicina.rwidth()*j,20+velicina.rheight()*i);
                    button[i][j]->show();
                    connect(button[i][j],SIGNAL(released()),
                            this,SLOT(ButtonPressed()));
            }
        }


}


void MainWindow::ButtonPressed(){

}

void MainWindow::RedSet(){
    QSpinBox *redBox=(QSpinBox *) sender();
    red=redBox->value();
    Iscrtaj();
    qDebug() << red;

}


void MainWindow::KolonaSet(){
    QSpinBox *kolonaBox=(QSpinBox *) sender();
    kolona=kolonaBox->value();
    Iscrtaj();
    qDebug() << kolona;
}

void MainWindow::Iscrtaj(){
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

    SetStart(red/2,kolona/4);
    SetEnd(red/2,3*kolona/4);
}



void MainWindow::SetStart(int i, int j){


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
