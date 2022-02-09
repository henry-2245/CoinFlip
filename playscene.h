#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <mycoin.h>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int stageNum);

    int stageIndex;

    //paint event
    void paintEvent(QPaintEvent *);

    int gameArray[4][4]; //change the data

    MyCoin *coinBtn[4][4];

    //detect win
    bool isWin;

signals:
    void changeScene();

};

#endif // PLAYSCENE_H
