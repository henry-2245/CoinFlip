#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>
#include "chooselevel.h"
#include "mypushbutton.h"
ChooseLevel::ChooseLevel(QWidget *parent) : QMainWindow(parent)
{
    //size
    this->setFixedSize(320,600);

    //icon
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //title
    this->setWindowTitle("Level");

    //create menu bar
    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    //create Option Button
    QMenu *startMenu = bar->addMenu("Option");

    //quit under option
    QAction *quit = startMenu->addAction(("Quit"));

    //click to quit
    connect(quit,&QAction::triggered,[=](){
        this->close();
    });

    //choose stage sound
    QSound *stageSound = new QSound(":/res/TapButtonSound.wav",this);
    //back button sound
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //back button
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //clicked back
    connect(backBtn,&MyPushButton::clicked,[=](){
        //start sound(back)
        backSound->play();
        //delay time
        QTimer::singleShot(300,this,[=](){
            emit this->changeScene();
        });
    });

    //button for choossing stage
    for(int i = 0; i < 20; i++){
        MyPushButton *stageBtn = new MyPushButton(":/res/LevelIcon.png");
        stageBtn->setParent(this);
        stageBtn->move(28 + (i%4) * 70, 150 +  (i/4) * 80); //space between each button(both top and side way)

        connect(stageBtn,&MyPushButton::clicked,[=](){
            //play sound
            stageSound->play();

            QString str = QString("Stage %1").arg(i+1);
            qDebug() << str;


            this->hide();
            play = new PlayScene(i+1);
            //set pos for window
            play->setGeometry(this->geometry());
            play->show();



            connect(play,&PlayScene::changeScene,[=](){
               this->setGeometry(play->geometry());
               this->show();
               delete play;
               play = NULL;

            });
        });

        //using label for text
        QLabel *label = new QLabel;
        label->setParent(this);
        label->setStyleSheet("QLabel {color : white;}");
        label->setFixedSize(stageBtn->width(), stageBtn->height());
        label->setText(QString::number(i+1));
        label->move(28 + (i%4) * 70, 150 +  (i/4) * 80);
        //align the text with the circle pic
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //allowing click pass through the label
        label->setAttribute((Qt::WA_TransparentForMouseEvents));

    }
}

//load background
void ChooseLevel::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pic;
    pic.load(":/res/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pic);

    //load stage text
    pic.load(":/res/stagebg.png");
    painter.drawPixmap((this->width() - pic.width())*0.5,50,pic.width(),pic.height(),pic);


}
