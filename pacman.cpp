#include "pacman.h"

pacman::pacman()
{

}

int pacman::iswall(int x, int y)
{
    if(mapping.init_map[y][x]=='1')
        return 1;
    else
        return 0;

}

void pacman::setdirection(int dir)
{
    direction=dir;
}

void pacman::ghostAmove(int dir,int x,int y,int px,int py)
{
    if(y<=py)
    {
        if(x<=px)
        {
//            qDebug()<<"A";
            if(dir==1)
                nextdirection=newdirection(4,3,1);
            if(dir==2)
                nextdirection=newdirection(2,4,3);
            if(dir==3)
                nextdirection=newdirection(2,3,1);
            if(dir==4)
                nextdirection=newdirection(4,2,1);
        }
        if(x>px)
        {
//            qDebug()<<"B";
            if(dir==1)
                nextdirection=newdirection(3,1,4);
            if(dir==2)
                nextdirection=newdirection(2,3,4);
            if(dir==3)
                nextdirection=newdirection(3,2,1);
            if(dir==4)
                nextdirection=newdirection(2,1,4);
        }
    }
    else if(y>py)
    {
        if(x<=px)
        {
//            qDebug()<<"C";
            if(dir==1)
                nextdirection=newdirection(1,4,3);
            if(dir==2)
                nextdirection=newdirection(4,3,2);
            if(dir==3)
                nextdirection=newdirection(1,3,2);
            if(dir==4)
                nextdirection=newdirection(4,1,2);
        }
        if(x>px)
        {
//            qDebug()<<"D";
            if(dir==1)
                nextdirection=newdirection(1,3,4);
            if(dir==2)
                nextdirection=newdirection(3,4,2);
            if(dir==3)
                nextdirection=newdirection(3,1,2);
            if(dir==4)
                nextdirection=newdirection(1,4,2);
        }
    }
//    qDebug()<<dir<<nextdirection;
}

void pacman::ghostBmove(int dir,int x,int y,int px,int py)
{
//    qDebug()<<px<<py;
    if(y<=py)
    {
        if(x<=px)
        {
//            qDebug()<<"A";
            if(dir==1)
                nextdirection=newdirection(4,3,1);
            if(dir==2)
                nextdirection=newdirection(2,4,3);
            if(dir==3)
                nextdirection=newdirection(2,3,1);
            if(dir==4)
                nextdirection=newdirection(4,2,1);
        }
        if(x>px)
        {
//            qDebug()<<"B";
            if(dir==1)
                nextdirection=newdirection(3,1,4);
            if(dir==2)
                nextdirection=newdirection(2,3,4);
            if(dir==3)
                nextdirection=newdirection(3,2,1);
            if(dir==4)
                nextdirection=newdirection(2,1,4);
        }
    }
    else if(y>py)
    {
        if(x<=px)
        {
//            qDebug()<<"C";
            if(dir==1)
                nextdirection=newdirection(1,4,3);
            if(dir==2)
                nextdirection=newdirection(4,3,2);
            if(dir==3)
                nextdirection=newdirection(1,3,2);
            if(dir==4)
                nextdirection=newdirection(4,1,2);
        }
        if(x>px)
        {
//            qDebug()<<"D";
            if(dir==1)
                nextdirection=newdirection(1,3,4);
            if(dir==2)
                nextdirection=newdirection(3,4,2);
            if(dir==3)
                nextdirection=newdirection(3,1,2);
            if(dir==4)
                nextdirection=newdirection(1,4,2);
        }
    }
    qDebug()<<"dir"<<dir<<"next"<<nextdirection;
}

void pacman::ghostCmove(int dir)
{
    int tmp,i;
    for(i=0;i<100;i++)
    {
        tmp=rand()%4+1;
        if(dir==0)
        {
            nextdirection=dir;
//            qDebug()<<"dir"<<dir<<"next"<<nextdirection;
            break;
        }
        if(tmp!=opdir(dir))
        {
            if(change2(tmp))
            {
                nextdirection=tmp;
//                qDebug()<<"dir"<<dir<<"next"<<nextdirection;
                break;
            }
        }
    }
}

void pacman::ghostDmove(int dir,int x,int y,int px,int py)
{

}

bool pacman::canghost(int x,int y)
{
    if(x==(LEVEL_WIDTH)-1 || x==0)
        if(y!=15)
            return false;
    if(y==0 || y==(LEVEL_HEIGHT-1))
        if(x!=13)
            return false;
    switch(map[y][x])
    {
        case '1':
        case '3':
        case 'X':
            return false;
        default:
            return true;
    }
}

bool pacman::canghost2(int dir,int newx,int newy,int x,int y)
{
    if(newx==(LEVEL_WIDTH-1) || newx==0)
        if(newy!=15)
            return false;
    if(newy==0 || newy==(LEVEL_HEIGHT-1))
        if(newx!=13)
            return false;
//    if(y==13)
//    {
//        if(x==12 || x==13 || x==14 )
//        {
//            switch(map[newy][newx])
//            {
//                case '1':
//                    return false;
//                default:
//                    return true;
//            }
//        }
//    }
//    else
//    {
        switch(map[newy][newx])
        {
            case '1':
            case '3':
            case 'X':
                return false;
            default:
                return true;
        }
//    }
}

bool pacman::change(int dir)
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
    if(canghost(newx,newy))
        return true;
    else
        return false;
}

bool pacman::change2(int dir)
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
    qDebug()<<dir<<"pos"<<x<<y<<"new"<<newx<<newy;
    if(canghost2(dir,newx,newy,x,y))
        return true;
    else
        return false;
}

void pacman::show()
{
//    int x,y;
//    for(x=0;x<LEVEL_HEIGHT;x++)
//    {
//        for(y=0;y<LEVEL_WIDTH;y++)
//        {
//            qDebug()<<map[y][x];
//        }
//    }
}

bool pacman::intersection(int x,int y)
{
    int x1,x2,x3,x4,y1,y2,y3,y4,way=0;
    x1=x-1;
    y1=y;
    x2=x;
    y2=y+1;
    x3=x+1;
    y3=y;
    x4=x;
    y4=y-1;
    if(canghost(x1,y1))
        way++;
    if(canghost(x2,y2))
        way++;
    if(canghost(x3,y3))
        way++;
    if(canghost(x4,y4))
        way++;
    if(way==1)
        return true;
    return
        false;
}

int pacman::opdir(int x)
{
    if(x==1)
        return 2;
    if(x==2)
        return 1;
    if(x==3)
        return 4;
    if(x==4)
        return 3;
}

int pacman::newdirection(int x,int y,int z)
{
    if(change(x))
        return x;
    else if(change(y))
        return y;
    else if(change(z))
        return z;
}

int pacman::newdirection2(int x,int y,int z)
{
    if(change2(x))
        return x;
    else if(change2(y))
        return y;
    else if(change2(z))
        return z;
}
