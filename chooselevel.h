#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevel(QWidget *parent = nullptr);


    void paintEvent(QPaintEvent *);

    PlayScene *play  = NULL;
signals:
    //signal to main scene when clicked back
    void changeScene();

};

#endif // CHOOSELEVEL_H
