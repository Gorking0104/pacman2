#ifndef MAP_H
#define MAP_H

#include "data.h"



class map
{
    public:
        map();

        char init_map[LEVEL_HEIGHT][LEVEL_WIDTH];
        void initmap();

        void drawmap(QPainter& painter);
        void drawobject(QPainter &painter,int dir,bool scare);
        void show(QPainter& painter,int x,int y,int dir,bool scare);
        void scary(QPainter& painter,int x,int y);
        bool empty();

        void pacmove(int dir,int x,int y);
        bool canmove(int x,int y);

        bool moving;
        int newx;
        int newy;


};


#endif // MAP_H
