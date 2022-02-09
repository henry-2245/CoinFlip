#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //Display image idle, and display when pressing down the button
    MyPushButton (QString normalImg, QString pressImg = "" );

    //remembering path for both idle and pressing down
    QString normalImgPath;
    QString pressImgPath;


    //animation
    void scene1(); //down
    void scene2(); //up

    //press and release
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
