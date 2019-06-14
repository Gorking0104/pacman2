#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data.h"
#include "map.h"
#include "pacman.h"

#include <iostream>
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        QTextStream cout;

        class map loadmap;
        class pacman player;
        class pacman ghosts[4];
        class pacman pellets[4];


        void MainLoop();

    public:
        void start();
        void delay();
        void ended();
        void power();
        bool samepos(int i);
        bool delayyyy;
        bool playing;
        bool over;
        void text(QPainter &painter);
        int scaretime=0;
        int path[10000][2];
        int pos=0;

        int scarestate=0;
        int ghostA=0,ghostB=0,ghostC=0,ghostD=0;
        char tmp='x';

        void check();

    public slots:
        void showTime();
        void lives();
        void ghostlives();

    private:
        Ui::MainWindow *ui;

        QTimer *timer;
        QTimer *ghoststimer;
        QLCDNumber *myLCDNumber;
        QTime *time;
        QLabel *showmode;


    protected:
        void paintEvent(QPaintEvent *);
        void keyPressEvent(QKeyEvent *event);


};

#endif // MAINWINDOW_H
