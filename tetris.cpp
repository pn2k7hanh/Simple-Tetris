#include "tetris.h"

Tetris::Tetris(QObject *parent) : QGraphicsScene(parent)
{
    m_nextScene = new QGraphicsScene(this);
    m_nextScene->addItem(&m_nextTetro);
    setScore(0);
    m_size=QPoint(10,20);
    matrix.setPos(QPoint(0,1));
    addItems();
//    generatorTetro(true);
    matrix.setupMatrix(m_size);
    m_rect=QRect(QPoint(0,0),m_size*20);
    this->setSceneRect(QRectF(m_rect));
    setSpeed(2);

    setStatus(0);
}

Tetris::~Tetris()
{
    m_nextScene->removeItem(&m_nextTetro);
    delete m_nextScene;
}

QSize Tetris::sceneSize()
{
    return QSize(m_rect.width(),m_rect.height());
}

void Tetris::startGame(int speed)
{
    if(status()!=0) stopGame();
    setStatus(1);
    setScore(0);
    isTetris=false;
    rand.seed(time(0));
    matrix.setupMatrix(m_size);
    generatorTetro(true);
    generatorTetro();

    setSpeed(speed);
    id_speed=startTimer(1000/m_speed);
    emit gameStart();
}

void Tetris::stopGame(bool pause)
{
    if(pause)
    {
        setStatus(2);
        emit gamePause();
    }
    else
    {
        setStatus(0);
        killTimer(id_speed);
        emit gameStart();
    }
}

void Tetris::tetroMove(Direction::Type dir)
{
    if(status()!=1) return;
    bool falling=true;

    // Check if the tetromino can't move
    for(int i=0;i<4;i++)
    {
        QPoint nextPoint=m_tetro.XY::xy()+m_tetro.pointAt(i)+Direction::Move[dir];
        if(0<=nextPoint.x()&&nextPoint.x()<10&&
                0<=nextPoint.y())
        {
            // Check if the tetromino torch the block
            if(nextPoint.y()<20)
            {
                if(!matrix.blockAt(nextPoint).isEmpty())
                {
                    falling=false;
                    break;
                }
            }
        }
        else
        {
            falling=false;
            break;
        }
    }

    if(falling)
    {
        m_tetro.addXY(Direction::Move[dir]);
        m_tetro.setPos(matrix.xy()+m_tetro.XY::xy()*20);
    }
    else
    {
        if(dir==Direction::DOWN)
        {
            int sc=placeTetro();
            if(sc!=4)
            {
                addScore(100*sc);
                isTetris=false;
            }
            else
            {
                if(!isTetris) addScore(800);
                else addScore(1200);
                isTetris=true;
            }
        }
    }
}

int Tetris::status()
{
    return this->m_status;
}

void Tetris::addItems()
{
    addItem(&m_tetro);
    addItem(&matrix);
}

void Tetris::rotate()
{
    m_tetro.rotate(0);
    bool kt=true;
    for(int i=0;i<4;i++)
    {
        QPoint point=m_tetro.pointAt(i)+m_tetro.XY::xy();
        if(0<=point.x()&&point.x()<10&&
                0<=point.y())
        {
            if(point.y()<20)
            {
                if(!matrix.blockAt(point).isEmpty())
                {
                    kt=false;
                    break;
                }
            }
        }
        else
        {
            kt=false;
            break;
        }
    }
    if(!kt) m_tetro.rotate(2);
}

void Tetris::generatorTetro(bool isStart)
{
    if(!isStart)
    {
        m_tetro.setTetro(m_nextTetro);
        m_tetro.XY::setXY((10-m_tetro.size().x())/2,19);
        m_tetro.setPos(matrix.xy()+m_tetro.XY::xy()*20);
    }
    m_nextTetro.setType(Tetromino::Type(rand.bounded(0,6)),rand.bounded(0,3));
    m_nextScene->setSceneRect(m_nextTetro.boundingRect());
    m_nextTetro.setPos(m_nextTetro.size()/-2);
}

int Tetris::placeTetro()
{
    for(int i=0;i<4;i++)
    {
        QPoint point=m_tetro.XY::xy()+m_tetro.pointAt(i);
        if(point.y()<20)
        {
            matrix.blockAt(point).setBlock(m_tetro.blockAt(i));
        }
        else
        {
            stopGame();
        }
    }
    int sc=0;
    for(int j=0;j<m_size.y();j++)
    {
        int d=0;
        for(int i=0;i<m_size.x();i++)
        {
            if(!matrix.blockAt(i,j).isEmpty())
            {
                d++;
            }
        }
        if(d==m_size.x())
        {
            falling(j);
            sc++;
            j--;
        }
    }
    generatorTetro();
    return sc;
}

void Tetris::falling(int index)
{
    for(int j=index;j<m_size.y();j++)
    {
        for(int i=0;i<m_size.x();i++)
        {
            if(j<m_size.y()-1)
            {
                matrix.blockAt(i,j).setBlock(matrix.blockAt(i,j+1));
            }
            else
            {
                matrix.blockAt(i,j).setEmpty(true);
            }
        }
    }
}

int Tetris::score()
{
    return m_score;
}

void Tetris::setScore(int score)
{
    if(score>=0) m_score=score;
    emit scoreChange(m_score);
}

void Tetris::addScore(int score)
{
    setScore(this->score()+score);
}

int Tetris::speed()
{
    return m_speed;
}


void Tetris::timerEvent(QTimerEvent *event)
{
    if(status()!=1) return;
    if(event->timerId()==id_speed)
    {
        tetroMove(Direction::DOWN);
    }
    else
    {
//        for(int i=0;i<m_keyPress.size();i++)
//        {

//        }
        for(QMap<int,int>::iterator i=m_keyPress.begin();i!=m_keyPress.end();i++)
        {
            if(event->timerId()==i.value())
            {
//                keyPress(i.key());
                if(!m_keyAutoRe.contains(i.key()))
                {
                    m_keyAutoRe.insert(i.key());
                    killTimer(i.value());
                    i.value()=startTimer(40);
                }
                else
                {
                    keyPress(i.key());
                }

            }
        }
    }
    update();
}

void Tetris::keyPressEvent(QKeyEvent *event)
{
    if(status()!=1) return;
    if(!event->isAutoRepeat())
    {
        int t=startTimer(200);
        m_keyPress[event->key()]=t;
        keyPress(event->key());
        if(event->key()==Qt::Key_Down) killTimer(id_speed);
    }
    update();
}

void Tetris::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
       killTimer(m_keyPress[event->key()]);
       m_keyPress.remove(event->key());
       m_keyAutoRe.remove(event->key());
       if(event->key()==Qt::Key_Down) id_speed=startTimer(1000/m_speed);
    }
    update();
}

void Tetris::keyPress(int id)
{
    switch(id)
    {
    case Qt::Key_Up:
        tetroRotate();
        break;
    case Qt::Key_Left:
        tetroMoveLeft();
        break;
    case Qt::Key_Right:
        tetroMoveRight();
        break;
    case Qt::Key_Down:
        tetroFalling();
        break;
    }
}
