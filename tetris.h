#ifndef TETRIS_H
#define TETRIS_H

#include <QGraphicsScene>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>
#include <QMap>
#include <QSet>
#include "matrix.h"
#include "tetromino.h"
#include "direction.h"

class Tetris : public QGraphicsScene
{
    Q_OBJECT
public:
    Tetris(QObject *parent=0);
    ~Tetris();
    QSize sceneSize();
private:
    QRect m_rect;
private:
    class Tetro : public Tetromino , public XY{};

signals:
    void scoreChange(int score);
    void speedChange(int speed);
    void gameStart();
    void gameStop();
    void gamePause();
    void statusChange(int status);
public slots:
    void setSpeed(int speed){
        m_speed=speed;
        emit speedChange(speed);
    }
    void startGame(int speed=2);
    void stopGame(bool pause=false);
    void pauseGame(){
        if(status()==0) return;
        if(status()==2)
        {
            resumeGame();
        }
        else stopGame(true);
    }
    void resumeGame(){
        if(status()==0) return;
        setStatus(1);
    }
    void tetroRotate(){
        if(status()!=1) return;
        rotate();
    }
    void tetroMoveLeft(){
        if(status()!=1) return;
        tetroMove(Direction::LEFT);
    }
    void tetroMoveRight(){
        if(status()!=1) return;
        tetroMove(Direction::RIGHT);
    }
    void tetroFalling(){
        if(status()!=1) return;
        tetroMove(Direction::DOWN);
        addScore(3);
    }
private:
    void setStatus(int status){this->m_status=status;emit statusChange(this->m_status);}
    void tetroMove(Direction::Type dir=Direction::DOWN);
public:
    int status();
private:
    int m_status;

private:
    void addItems();
    Tetro m_tetro;
    void rotate();
    Tetromino m_nextTetro;
    QGraphicsScene *m_nextScene;
public:
    QGraphicsScene *nextScene()
    {
        return m_nextScene;
    }
private:
    QRandomGenerator rand;
    void generatorTetro(bool isStart=false);
    Matrix matrix;
    QPoint m_size;
    int placeTetro();
    void falling(int index);

    int m_score;
    bool isTetris;
    int score();
    void setScore(int score);
    void addScore(int score);

    int m_speed;
    int id_speed;
public:
    int speed();
protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    QMap<int,int> m_keyPress;
    QSet<int> m_keyAutoRe;
    void keyPress(int id);
};

#endif // TETRIS_H
