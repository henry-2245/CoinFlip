#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressImg ){
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pic;
    bool ret = pic.load(normalImg);
    if(!ret){
        qDebug() << "Image fail to load";
        return;
    }

    //set picture size
    this->setFixedSize(pic.width(),pic.height());

    //set border using css
    this->setStyleSheet("QPushButton{border:0px;}");

    //set icon
    this->setIcon(pic);

    //set icon size
    this->setIconSize(QSize(pic.width(),pic.height()));


}

void MyPushButton::scene1(){

    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //time between scene
    animation->setDuration(200);

    //starting point
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //ending point
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height())); //go down 10 pixel

    //set path
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //start animation
    animation->start();
}

void MyPushButton::scene2(){

    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //time between scene
    animation->setDuration(200);

    //starting point
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //ending point
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //set path
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //start animation
    animation->start();
}

//mouse push switch image
void MyPushButton::mousePressEvent(QMouseEvent *e){
    if(this->pressImgPath != ""){
        QPixmap pic;
        bool ret = pic.load(this->pressImgPath);
        if(!ret){
            qDebug() << "Image fail to load";
            return;
        }

        //set picture size
        this->setFixedSize(pic.width(),pic.height());

        //set border using css
        this->setStyleSheet("QPushButton{border:0px;}");

        //set icon
        this->setIcon(pic);

        //set icon size
        this->setIconSize(QSize(pic.width(),pic.height()));

    }

    return QPushButton::mousePressEvent(e);
}

//mouse release switch back image
void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImgPath != ""){
        QPixmap pic;
        bool ret = pic.load(this->normalImgPath);
        if(!ret){
            qDebug() << "Image fail to load";
            return;
        }

        //set picture size
        this->setFixedSize(pic.width(),pic.height());

        //set border using css
        this->setStyleSheet("QPushButton{border:0px;}");

        //set icon
        this->setIcon(pic);

        //set icon size
        this->setIconSize(QSize(pic.width(),pic.height()));

    }

    return QPushButton::mouseReleaseEvent(e);
}
