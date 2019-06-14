#include "map.h"

map::map()
{

}

void map::drawmap(QPainter &painter)
{
    painter.setPen(QPen(Qt::black,0));
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(50,50,(LEVEL_WIDTH-1)*block,(LEVEL_HEIGHT-1)*block);
    int x,y;
    for (x=0;x<LEVEL_WIDTH;x++)
    {
        for(y=0;y<LEVEL_HEIGHT;y++)
        {
            if(init_map[y][x]=='1')
            {
                painter.setPen(QPen(Qt::blue,0));
                painter.setBrush(QBrush(Qt::blue));
                painter.drawRect(50+x*block,50+y*block,block,block);
            }
        }
    }

}

void map::drawobject(QPainter &painter,int dir,bool scare)
{
    int x,y;
    for (x=0;x<LEVEL_WIDTH;x++)
    {
        for(y=0;y<LEVEL_HEIGHT;y++)
        {
            show(painter,x,y,dir,scare);
        }
    }
}

void map::initmap()
{
    char init[LEVEL_HEIGHT][LEVEL_WIDTH]=
    {
        "1111111111111x1111111111111",
        "100000000000000000000000001",
        "101111011111010111110111101",
        "121xx101xxx10101xxx101xx121",
        "101111011111010111110111101",
        "1000000000000P0000000000001",
        "101111010111111111010111101",
        "101xx10101xxxxxxx10101xx101",
        "101111010111111111010111101",
        "100000010000010000010000001",
        "101111011111010111110111101",
        "101xx10100000A00000101xx101",
        "10111101B111101111D10111101",
        "1000000100000C0000010000001",
        "111101111011111110111101111",
        "x0000000001xxxxx1000000000x",
        "111111010011111110010111111",
        "1xxxx10110000000001101xxxx1",
        "111111010001111100010111111",
        "100000000100000001000000001",
        "101111011111010111110111101",
        "101xx101xxx10101xxx101xx101",
        "101111011111010111110111101",
        "120001000000010000000100021",
        "111101011011111110110101111",
        "1xx10101101xxxxx10110101xx1",
        "111101011011111110110101111",
        "100000011000010000110000001",
        "101111111111010111111111101",
        "100000000000000000000000001",
        "1111111111111x1111111111111"
    };
    int i,j;
    for(i=0;i<LEVEL_HEIGHT;i++)
    {
        for(j=0;j<LEVEL_WIDTH;j++)
        {
            init_map[i][j]=init[i][j];
        }
    }
}

void map::show(QPainter& painter,int x,int y,int dir,bool scare)
{
    switch(init_map[y][x])
    {
        case '1':
            painter.setPen(QPen(Qt::blue,0));
            painter.setBrush(QBrush(Qt::blue));
            painter.drawRect(50+x*block,50+y*block,block,block);
            break;
        case '2':
            painter.setPen(QPen(Qt::magenta,0));
            painter.setBrush(QBrush(Qt::magenta));
            painter.drawEllipse(50+x*block+6,50+y*block+6,power,power);
            break;
        case '3':
            painter.setPen(QPen(Qt::darkGray,0));
            painter.setBrush(QBrush(Qt::darkGray));
            painter.drawRect(50+x*block,50+y*block,block*3,block-15);
            break;
        case '0':
            painter.setPen(QPen(Qt::white,0));
            painter.setBrush(QBrush(Qt::white));
            painter.drawEllipse(50+x*block+12,50+y*block+12,bean,bean);
            break;
        case 'A':
            if(scare)
            {
                painter.setPen(QPen(Qt::lightGray,1));
                painter.setBrush(QBrush(Qt::lightGray));
            }
            else
            {
                painter.setPen(QPen(Qt::red,1));
                painter.setBrush(QBrush(Qt::red));
            }
            painter.drawRect(50+x*block+5,50+y*block+5,ghost,ghost);
            break;
        case 'B':
            if(scare)
            {
                painter.setPen(QPen(Qt::lightGray,1));
                painter.setBrush(QBrush(Qt::lightGray));
            }
            else
            {
                painter.setPen(QPen(Qt::cyan,1));
                painter.setBrush(QBrush(Qt::cyan));
            }
            painter.drawRect(50+x*block+5,50+y*block+5,ghost,ghost);
            break;
        case 'C':
            if(scare)
            {
                painter.setPen(QPen(Qt::lightGray,1));
                painter.setBrush(QBrush(Qt::lightGray));
            }
            else
            {
                painter.setPen(QPen(QColor(255,128,0),1));
                painter.setBrush(QBrush(QColor(255,128,0)));
            }
            painter.drawRect(50+x*block+5,50+y*block+5,ghost,ghost);
            break;
        case 'D':
            if(scare)
            {
                painter.setPen(QPen(Qt::lightGray,1));
                painter.setBrush(QBrush(Qt::lightGray));
            }
            else
            {
                painter.setPen(QPen(Qt::green,1));
                painter.setBrush(QBrush(Qt::green));
            }
            painter.drawRect(50+x*block+5,50+y*block+5,ghost,ghost);
            break;
        case 'P':
            painter.setPen(QPen(Qt::yellow,0));
            painter.setBrush(QBrush(Qt::yellow));
            if(dir==1)
                painter.drawPie(50+x*block+5,50+y*block+5,pacman,pacman,135*16,270*16);
            if(dir==2)
                painter.drawPie(50+x*block+5,50+y*block+5,pacman,pacman,315*16,270*16);
            if(dir==3)
                painter.drawPie(50+x*block+5,50+y*block+5,pacman,pacman,215*16,270*16);
            if(dir==4)
                painter.drawPie(50+x*block+5,50+y*block+5,pacman,pacman,45*16,270*16);
            break;
        case 'x':
            painter.setPen(QPen(Qt::black,0));
            painter.setBrush(QBrush(Qt::black));
            painter.drawRect(50+x*block,50+y*block,block,block);
            break;
        case '4' :
            painter.setPen(QPen(Qt::black,0));
            painter.setBrush(QBrush(Qt::black));
            painter.drawEllipse(50+x*block+12,50+y*block+12,bean,bean);
            break;
        case 'E' :
            painter.setPen(QPen(Qt::yellow,0));
            painter.setBrush(QBrush(Qt::yellow));
            painter.drawPie(50+x*block+5,50+y*block+5,pacman,pacman,45*16,270*16);
            break;
    }
}

void map::scary(QPainter& painter,int x,int y)
{
    switch(init_map[y][x])
    {
        case '1':
            painter.setPen(QPen(Qt::blue,0));
            painter.setBrush(QBrush(Qt::blue));
            painter.drawRect(50+x*block,50+y*block,block,block);
            break;
        case '2':
            painter.setPen(QPen(Qt::magenta,0));
            painter.setBrush(QBrush(Qt::magenta));
            painter.drawEllipse(50+x*block+6,50+y*block+6,power,power);
            break;
        case '3':
            painter.setPen(QPen(Qt::darkGray,0));
            painter.setBrush(QBrush(Qt::darkGray));
            painter.drawRect(50+x*block,50+y*block,block*3,block-15);
            break;
        case '0':
            painter.setPen(QPen(Qt::white,0));
            painter.setBrush(QBrush(Qt::white));
            painter.drawEllipse(50+x*block+12,50+y*block+12,bean,bean);
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            painter.setPen(QPen(Qt::green,1));
            painter.setBrush(QBrush(Qt::green));
            painter.drawRect(50+x*block+5,50+y*block+5,ghost,ghost);
            break;
        case 'P':
            painter.setPen(QPen(QColor(41,41,255),0));
            painter.setBrush(QBrush(QColor(41,41,255)));
            painter.drawPie(50+x*block+5,50+y*block+5,pacman,pacman,45*16,270*16);
//            painter.drawRect(50+x*block,50+y*block,pacman,pacman);
            break;
        case ' ':
            painter.setPen(QPen(Qt::black,0));
            painter.setBrush(QBrush(Qt::black));
            painter.drawRect(50+x*block,50+y*block,block,block);
            break;
    }
}

bool map::empty()
{
    int x,y;
    for (x=0;x<LEVEL_WIDTH;x++)
    {
        for(y=0;y<LEVEL_HEIGHT;y++)
        {
            if(init_map[y][x]=='0')
                return false;
            if(init_map[y][x]=='2')
                return false;
        }
    }
    return true;
}

void map::pacmove(int dir,int x,int y)
{
    switch(dir)
    {
        case 1:
            newx=x;
            if(x==13 && y==0)
                newy=LEVEL_HEIGHT-2;
            else
                newy=y-1;
            break;
        case 2:
            newx=x;
            if(x==13 && y==(LEVEL_HEIGHT-2))
                newy=0;
            else
                newy=y+1;
            break;
        case 3:
            newy=y;
            if(y==15 && x==0)
                newx=26;
            else
                newx=x-1;
            break;
        case 4:
            newy=y;
            if(y==15 && x==26)
                newx=0;
            else
                newx=x+1;
            break;
    }
    if(canmove(newx,newy))
    {
        x=newx;
        y=newy;
    }
}

bool map::canmove(int x,int y)
{
    if(x==(LEVEL_WIDTH)-1 || x==0)
        if(y!=15)
            return false;
    if(y==0 || y==(LEVEL_HEIGHT-1))
        if(x!=13)
            return false;
    switch(init_map[y][x])
    {
        case '1':
        case '3':
        case 'X':
            return false;
        default:
            return true;
    }
}



