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
    int red=0,kolona=0;
    int start[2]={-1,-1},end[2]={-1,-1};
    void Redraw();
    void SetStart(int i,int j);
    void SetEnd(int i,int j);

private slots:
   // void NumChanged();
   // void StartPressed();
    void ButtonPressed();
    void Matrica();
    void RedSet();
    void KolonaSet();
    void Iscrtaj();
};
#endif // MAINWINDOW_H
