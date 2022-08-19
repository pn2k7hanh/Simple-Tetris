#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTimerEvent>
#include "tetris.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
namespace Settings { class Setting; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void changeScore(int score);
    void changeSpeed(int speed);
    void changeStatus(int status);
    void startGame();
    void stopGame();
    void showAbout();
    void showAboutQt();
private:
    Ui::Dialog *ui;
    Settings::Setting *setting;
    Tetris m_tetris;
//    QGraphicsScene m_nextTetro;

    int setFocusId;
protected:
    void timerEvent(QTimerEvent *event) override;    
};
#endif // DIALOG_H






















