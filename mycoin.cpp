#include "mycoin.h"
#include <QDebug>

MyCoin::MyCoin(QString btnImg){
    QPixmap pic;
    bool ret = pic.load(btnImg);
    if(!ret){
        QString str = QString("Picture %1 load failed").arg(btnImg);
        qDebug() << "load fail";
        return;
    }

    this->setFixedSize(pic.width(),pic.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pic);
    this->setIconSize(QSize(pic.width(),pic.height()));

    //timer
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //signal for flipping the coin
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pic;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        pic.load(str);

        this->setFixedSize(pic.width(),pic.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pic);
        this->setIconSize(QSize(pic.width(),pic.height()));
        //after flipped reset min
        if(this->min > this->max){
            this->min = 1;
            animation = false;
            timer1->stop();
        }
    });


    //signal for flipping the coin
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pic;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        pic.load(str);

        this->setFixedSize(pic.width(),pic.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pic);
        this->setIconSize(QSize(pic.width(),pic.height()));
        //after flipped reset max
        if(this->max < this->min){
            this->max = 8;
            animation = false;
            timer2->stop();
        }
    });
}



void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->animation || this->isWin ){
        return;
    }
    else{
        QPushButton::mousePressEvent(e);
    }
}


//change the sign of coin is flipped or not flipped
void MyCoin::changeFlag(){
    //if is not flipped yet flip the coin
    if(this->flag){
        timer1->start(30);
        animation = true; //start animation
        this->flag = false;


    }
    else{
        timer2->start(30);
        this->flag = true;
    }
}
