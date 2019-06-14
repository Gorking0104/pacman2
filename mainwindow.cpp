#include "mainwindow.h"
#include "ui_mainwindow.h"
//QTextStream cout(stdout, QIODevice::WriteOnly);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("PPPPPPPPPPPPPPPACman"));
    this->setFixedSize(1200,950);
    this->move(400,20);
    loadmap.initmap();

    int i;
    loadmap.moving=false;
    player.score=0;
    ghosts[0].direction=4;
    ghosts[1].direction=1;
    ghosts[2].direction=1;
    ghosts[3].direction=1;

    for(i=0;i<4;i++)
    {
        ghosts[i].moving=false;
        ghosts[i].scared=false;
        ghosts[i].tmp='0';
        ghosts[i].nextdirection=ghosts[i].direction;
    }
    delayyyy=false;
    playing=false;
    over=false;
    scaretime=0;
    player.scared=false;
    player.nextdirection=4;
    player.direction=4;
    tmp='x';

//    myTimer = new QTimer(this);
//    myLCDNumber = new QLCDNumber(this);
//    myLCDNumber->setGeometry(100+LEVEL_WIDTH*block,110,200,40); //設定位置大小
//    myLCDNumber->setDigitCount(8);          //設定位數
//    myTimer->start(1000);                   //以1000毫秒為周期起動定時器
//    showTime();
//    connect(myTimer,SIGNAL(timeout()),this,SLOT(showTime()));

//    showmode=new QLabel(this);
//    showmode->setGeometry(100+LEVEL_WIDTH*block,500,200,40);
//    showmode->setFont(QFont("標楷體",16));
//    showmode->setText(tr(""));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    loadmap.drawmap(painter);
//    if(playing)
    loadmap.drawobject(painter,player.direction,player.scared);
    text(painter);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
            playing=true;
            over=false;
            player.nextdirection=1;
            lives();
            break;
        case Qt::Key_Down:
            playing=true;
            over=false;
            player.nextdirection=2;
            lives();
            break;
        case Qt::Key_Left:
            playing=true;
            over=false;
            player.nextdirection=3;
            lives();
            break;
        case Qt::Key_Right:
            playing=true;
            over=false;
            player.nextdirection=4;
            lives();
            break;
        case Qt::Key_Space:
            if(!playing)
            {
                start();
                playing=true;
                over=false;
            }
            else
            {
//                ended();
//                start();
            }
            break;
        default:
            break;
    }
}

void MainWindow::text(QPainter &painter)
{
    QPen pen(Qt::white);
    painter.setPen(pen);
    QBrush brush(Qt::yellow);
    painter.setBrush(brush);
    QRect rect2(50,12*block+150,(LEVEL_WIDTH-1)*block,150);
    QRect rect3(100+LEVEL_WIDTH*block,170,200,40);
    QRect rect4(50,12*block,(LEVEL_WIDTH-1)*block,150);
    QRect rect5(100+LEVEL_WIDTH*block,220,200,40);
    if(!playing)
    {
        if(over)
        {
            painter.setFont(QFont("標楷體",80));
            painter.setPen(QColor(255,250,0));
            painter.drawText(rect4,"GAME OVER",QTextOption(Qt::AlignCenter));
            painter.drawText(rect2,Qt::AlignCenter,"SCORE:"+QString::number(player.score));
        }
        else
        {
            painter.setFont(QFont("標楷體",80));
            painter.setPen(QColor(255,250,0));
            painter.drawText(rect4,Qt::AlignCenter,"PRESS SPACE" );
            painter.drawText(rect2,Qt::AlignCenter,"TO START" );
            painter.setFont(QFont("標楷體",16));
            painter.setPen(Qt::black);
            painter.drawText(rect3,Qt::AlignCenter,"SCORE:"/*+QString::number(player.score)*/);
            painter.drawText(rect5,Qt::AlignCenter,QString::number(player.score));
        }
    }
    else
    {
        painter.setFont(QFont("標楷體",16));
        painter.setPen(Qt::black);
        painter.drawText(rect3,Qt::AlignCenter,"SCORE : "/*+QString::number(player.score)*/);
        painter.drawText(rect5,Qt::AlignCenter,QString::number(player.score));
    }
}

void MainWindow::start()
{
    over=false;
    playing=true;
    int x,y,i;
    for(x=0;x<LEVEL_HEIGHT;x++)
    {
        for(y=0;y<LEVEL_WIDTH;y++)
        {
            switch(loadmap.init_map[y][x])
            {
                case 'A':
                    ghosts[0].x=x;
                    ghosts[0].y=y;
                    break;
                case 'B':
                    ghosts[1].x=x;
                    ghosts[1].y=y;
                    break;
                case 'C':
                    ghosts[2].x=x;
                    ghosts[2].y=y;
                    break;
                case 'D':
                    ghosts[3].x=x;
                    ghosts[3].y=y;
                    break;
                case 'P':
                    player.x=x;
                    player.y=y;
                    player.oldx=x;
                    player.oldy=y;
                    player.oldx2=x;
                    player.oldy2=y;
                    path[pos][0]=x;
                    path[pos][1]=y;
                    pos++;
                    break;
            }
            for(i=0;i<4;i++)
            {
                ghosts[i].map[x][y]=loadmap.init_map[x][y];
            }
        }
    }
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(lives()));
    timer->start(300);

//    ghoststimer = new QTimer(this);
//    connect(ghoststimer,SIGNAL(timeout()),this,SLOT(ghostslives()));
//    ghoststimer->start(550);

    update();
    delayyyy=true;
//    for(x=0;x<LEVEL_HEIGHT;x++)
//    {
//        for(y=0;y<LEVEL_WIDTH;y++)
//        {
//            qDebug()<<ghosts[1].map[y][x]<<loadmap.init_map[y][x];
//        }
//    }

    player.nextdirection=4;
    player.direction=4;
    lives();
    this->setFocus();
}

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(2);
    while( QTime::currentTime() < dieTime ){}
    delayyyy=false;
}

void MainWindow::showTime()
{
//    QTime time = QTime::currentTime();
//    QString text=time.toString("hh:mm:ss"); //設定顯示時間格式
//    myLCDNumber->display(text);
}

void MainWindow::lives()
{
    if(player.direction!=player.nextdirection)
    {
        loadmap.pacmove(player.nextdirection,player.x,player.y);
        if(loadmap.canmove(loadmap.newx,loadmap.newy))
        {
            if(loadmap.init_map[loadmap.newy][loadmap.newx]=='0')
                player.score+=10;
            if(loadmap.init_map[loadmap.newy][loadmap.newx]=='2')
                player.scared=true;
            loadmap.init_map[player.y][player.x]='x';
            player.oldx2=player.oldx;
            player.oldx=player.x;
            player.oldy2=player.oldy;
            player.oldy=player.y;
            player.x=loadmap.newx;
            player.y=loadmap.newy;
            loadmap.init_map[player.y][player.x]='P';
            player.direction=player.nextdirection;
        }
        else
            player.nextdirection=player.direction;
    }
    else
    {
        loadmap.pacmove(player.direction,player.x,player.y);
        if(loadmap.canmove(loadmap.newx,loadmap.newy))
        {
            if(loadmap.init_map[loadmap.newy][loadmap.newx]=='0')
                player.score+=10;
            if(loadmap.init_map[loadmap.newy][loadmap.newx]=='2')
                player.scared=true;
            loadmap.init_map[player.y][player.x]=' ';
            player.oldx2=player.oldx;
            player.oldx=player.x;
            player.oldy2=player.oldy;
            player.oldy=player.y;
            player.x=loadmap.newx;
            player.y=loadmap.newy;
            loadmap.init_map[player.y][player.x]='P';
        }
    }
    power();
    ghostlives();
    if(player.scared)
        scaretime++;
    if(scaretime==20)
    {
        scaretime=0;
        player.scared=false;
    }

//    int i;
//    if(player.scared)
//    {
//        for(i=0;i<4;i++)
//            ghosts[i].scared=true;
//        scarestate+=1;
//        if(scarestate==1)
//            ghoststimer->setInterval(80);
//        if(scarestate==100)
//        {
//            ghost->whiteb=true;
//            ghost1->whiteb=true;
//            ghost2->whiteb=true;
//            ghost3->whiteb=true;
//        }
//        if(scarestate==150)
//        {
//            player.scared=false;
//            scarestate=0;
//            ghoststimer->setInterval(45);
//            ghost->whiteb=false;
//            ghost1->whiteb=false;
//            ghost2->whiteb=false;
//            ghost3->whiteb=false;
//        }
//    }
//    else
//    {
//        for(i=0;i<4;i++)
//            ghosts[i].scared=false;
//    }
//        ball->setpoints(ballpoints);
//        powerball->setpoints(Powerballpoints);
//        pac_map->setballpoints(ballpoints);
//        pac_map->setpowerballpoints(Powerballpoints);
//        pac_map->fillpacpoints(pacx,pacy);
//        pacman->advance();
//        ghost->advance();
//        ghost1->advance();
//        ghost2->advance();
//        ghost3->advance();

    check();
    this->setFocus();
    if(delayyyy)
        delay();
    update();
}

void MainWindow::ghostlives()
{
    int i;

//    player.show();
    if(playing)
    {

//        if(ghosts[1].scared)
//        {
//            if(ghostA==10)
//            {
//                ghostA=0;
//                ghosts[1].scared=false;
//            }
//            else
//                ghostA++;
//        }
//        else
//        {
            ghosts[0].ghostAmove(ghosts[0].direction,ghosts[0].x,ghosts[0].y,player.x,player.y);
//            if(ghosts[0].tmp!='0' || ghosts[0].tmp!='x')
//                ghosts[0].tmp=' ';
            loadmap.init_map[ghosts[0].y][ghosts[0].x]=ghosts[0].tmp;
            ghosts[0].x=ghosts[0].newx;
            ghosts[0].y=ghosts[0].newy;
            ghosts[0].tmp=loadmap.init_map[ghosts[0].y][ghosts[0].x];
            loadmap.init_map[ghosts[0].y][ghosts[0].x]='A';
            ghosts[0].direction=ghosts[0].nextdirection;
//        }
        update();

        ghosts[1].ghostBmove(ghosts[1].direction,ghosts[1].x,ghosts[1].y,player.oldx2,player.oldy2);
//        if(ghosts[1].tmp!='0' || ghosts[1].tmp!='x')
//            ghosts[1].tmp=' ';
        loadmap.init_map[ghosts[1].y][ghosts[1].x]=ghosts[1].tmp;
        ghosts[1].x=ghosts[1].newx;
        ghosts[1].y=ghosts[1].newy;
        ghosts[1].tmp=loadmap.init_map[ghosts[1].y][ghosts[1].x];
        loadmap.init_map[ghosts[1].y][ghosts[1].x]='B';
        ghosts[1].direction=ghosts[1].nextdirection;
        update();

        for(i=0;i<pos;i++)
        {
            if(ghosts[2].x==path[pos][0] && ghosts[2].y==path[pos][1])
            {
//                if(ghosts[2].tmp!='0' || ghosts[2].tmp!='x')
//                    ghosts[2].tmp=' ';
                loadmap.init_map[ghosts[2].y][ghosts[2].x]=ghosts[2].tmp;
                ghosts[2].newx=path[pos+1][0];
                ghosts[2].newy=path[pos+1][1];
                ghosts[2].x=ghosts[2].newx;
                ghosts[2].y=ghosts[2].newy;
                ghosts[2].tmp=loadmap.init_map[ghosts[2].y][ghosts[2].x];
                loadmap.init_map[ghosts[2].y][ghosts[2].x]='C';
                ghosts[2].direction=0;
                qDebug()<<"smae";
            }
            else
            {
                ghosts[2].ghostCmove(ghosts[2].direction);
//                if(ghosts[2].tmp!='0' || ghosts[2].tmp!='x')
//                    ghosts[2].tmp=' ';
                loadmap.init_map[ghosts[2].y][ghosts[2].x]=ghosts[2].tmp;
                ghosts[2].x=ghosts[2].newx;
                ghosts[2].y=ghosts[2].newy;
                ghosts[2].tmp=loadmap.init_map[ghosts[2].y][ghosts[2].x];
                loadmap.init_map[ghosts[2].y][ghosts[2].x]='C';
                ghosts[2].direction=ghosts[2].nextdirection;
            }
        }
        update();
    }

    if(delayyyy)
        delay();
    update();
}

void MainWindow::ended()
{
    over=true;
    playing=false;
}

bool MainWindow::samepos(int i)
{
    if(player.x==ghosts[i].x && player.y==ghosts[i].y)
        return true;
    if(player.newx==ghosts[i].x && player.newy==ghosts[i].y)
        return true;
    if(player.x==ghosts[i].newx && player.y==ghosts[i].newy)
        return true;
    return false;
}

void MainWindow::power()
{
    int i;
    if(loadmap.empty())
    {
        qDebug()<<"123";
        timer->stop();
        ended();
    }
    if(samepos(0)||samepos(1)||samepos(2)||samepos(3))
    {
        if(player.scared)
        {
            for(i=0;i<4;i++)
            {
                samepos(i);
                player.score+=100;
                ghosts[i].scared=true;
//                if(i==0)
//                {
//                    ghosts[i].x=13;
//                    ghosts[i].y=11;
//                }
//                else
//                {
//                    ghosts[i].x=13;
//                    ghosts[i].y=15;
//                }
            }
        }
        else
        {
            delay();
            timer->stop();
            ended();
        }
    }
}

void MainWindow::check()
{
    int i,j;
    for(i=0;i<LEVEL_HEIGHT;i++)
    {
        for(j=0;j<LEVEL_WIDTH;j++)
        {
            if(loadmap.init_map[i][j]=='P')
                if(i!=player.y || j!=player.x)
                    loadmap.init_map[i][j]='x';
            if(loadmap.init_map[i][j]=='A')
                if(i!=ghosts[0].y || j!=ghosts[0].x)
                    loadmap.init_map[i][j]='0';
            if(loadmap.init_map[i][j]=='B')
                if(i!=ghosts[1].y || j!=ghosts[1].x)
                    loadmap.init_map[i][j]='0';
            if(loadmap.init_map[i][j]=='C')
                if(i!=ghosts[2].y || j!=ghosts[2].x)
                    loadmap.init_map[i][j]='0';
            if(loadmap.init_map[i][j]=='D')
                if(i!=ghosts[3].y || j!=ghosts[3].x)
                    loadmap.init_map[i][j]='0';
        }
    }
}
