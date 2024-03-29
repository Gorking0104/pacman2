#ifndef PACMAN_H
#define PACMAN_H

#include "data.h"
#include "map.h"

class Mainwindow;

class pacman
{
    public:
        pacman();

        int score;
        int x,y;
        int newx,newy;
        int timeafterstart;

        int oldx,oldy;
        int oldx2,oldy2;

        int lives;
        bool moving;
        int direction;
        int nextdirection;
        int lastdirection;
        char index;
        char tmp;
        int path[10000][2];

        class map mapping;
        bool scared=false;
        bool start=false;
        char map[LEVEL_HEIGHT][LEVEL_WIDTH];

        Mainwindow *window;

    public:
//        Pacman(Game *const g);
        void ghostAmove(int dir,int x,int y,int px,int py);
        void ghostBmove(int dir,int x,int y,int px,int py);
        void ghostCmove(int dir);
        void ghostDmove(int dir,int x,int y,int px,int py);
        bool canghost(int x,int y);
        bool canghost2(int dir,int newx,int newy,int x,int y);
        int newdirection(int x,int y,int z);
        int newdirection2(int x,int y,int z);
        int opdir(int x);
        bool change(int dir);
        bool change2(int dir);
};

#endif // PACMAN_H
