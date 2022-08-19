#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_tetris);
    ui->graphicsView->scale(1,-1);
    ui->graphicsView->resize(m_tetris.sceneSize());
    ui->graphicsView2->setScene(m_tetris.nextScene());
    ui->graphicsView->grabKeyboard();
    ui->graphicsView2->scale(1,-1);

//    conButt=false;

    this->setFixedSize(460,419);

    connect(&m_tetris,SIGNAL(scoreChange(int)),this,SLOT(changeScore(int)));
    connect(&m_tetris,SIGNAL(speedChange(int)),this,SLOT(changeSpeed(int)));
    connect(ui->newGameButton,SIGNAL(clicked()),this,SLOT(startGame()));
    connect(ui->pauseButton,SIGNAL(clicked()),&m_tetris,SLOT(pauseGame()));
    connect(&m_tetris,SIGNAL(statusChange(int)),this,SLOT(changeStatus(int)));
    connect(ui->stopGameButton,SIGNAL(clicked()),this,SLOT(stopGame()));
    connect(ui->aboutButton,SIGNAL(clicked()),this,SLOT(showAbout()));
    connect(ui->aboutQtButton,SIGNAL(clicked()),this,SLOT(showAboutQt()));


    changeStatus(m_tetris.status());
//    m_tetris.startGame(2);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeScore(int score)
{
    ui->scoreLabel->setText(QString("Score: ")+QString::number(score));
}

void Dialog::changeSpeed(int speed)
{
    ui->levelLabel->setText(QString("Level: ")+QString::number(speed));
}

void Dialog::changeStatus(int status)
{
    switch(status)
    {
    case 0:
        ui->pauseButton->setText("Pause");
        ui->pauseButton->setDisabled(true);
        ui->newGameButton->setEnabled(true);
        ui->stopGameButton->setDisabled(true);
        break;
    case 1:
        ui->pauseButton->setText("Pause");
        ui->pauseButton->setEnabled(true);
        ui->newGameButton->setDisabled(true);
        ui->stopGameButton->setEnabled(true);
        break;
    case 2:
        ui->pauseButton->setText("Resume");
        ui->pauseButton->setEnabled(true);
        ui->newGameButton->setEnabled(true);
        ui->stopGameButton->setEnabled(true);
        break;
    }
}

void Dialog::startGame()
{
    m_tetris.startGame();
}

void Dialog::stopGame()
{
    m_tetris.pauseGame();
    if(QMessageBox::question(this,"Waring","Stop? Are you sure about that?")==QMessageBox::Yes)
    {
        if(QMessageBox::question(this,"Waring","Really?")==QMessageBox::Yes)
        {
            if(QMessageBox::question(this,"Waring","You will lose the game?")==QMessageBox::Yes)
            {
                if(QMessageBox::question(this,"Waring","Ok, stop it now?")==QMessageBox::Yes)
                {
                    m_tetris.stopGame();
                }
                else
                {
                    m_tetris.resumeGame();
                }
            }
            else
            {
                m_tetris.resumeGame();
            }
        }
        else
        {
            m_tetris.resumeGame();
        }
    }
    else
    {
        m_tetris.resumeGame();
    }
}

void Dialog::showAbout()
{
    m_tetris.pauseGame();

    QMessageBox::about(this,"About",
    "Simple Tetris By PhamNamKhanh<br>"
    "Facebook: <a href='https://facebook.com/AlgoriSoBad'>facebook.com/AlgoriSoBad</a><br>"
    "Email: <a>pnkill3327scratch@gmail.com</a>"
                       );

    m_tetris.resumeGame();
//    setFocusId=startTimer(50);

    ui->graphicsView->setFocus();
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
}

void Dialog::showAboutQt()
{
    m_tetris.pauseGame();
    QMessageBox::aboutQt(this,"About Qt");
    m_tetris.resumeGame();
}

void Dialog::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==setFocusId)
    {
        ui->graphicsView->activateWindow();
    }
}

