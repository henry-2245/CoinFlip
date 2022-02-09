#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);


    //Set Window Size
    setFixedSize(320,600);

    //set Window Icon
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //Game Name
    setWindowTitle("CoinFlip");

    //Quit Button
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //sound for start button
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);

    //startSound->setLoops(-1);//unlimited loops
    //startSound->play();


    //Start Button
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    //choose stages
    chooseStage = new ChooseLevel;

    //get signal from back
    connect(chooseStage,&ChooseLevel::changeScene,this,[=](){
        this->setGeometry(chooseStage->geometry());
        chooseStage->hide(); //hide chooseStage
        this->show(); //reshow the main scene
    });

    connect(startBtn, &MyPushButton::clicked,[=](){

        //start sound
        startSound->play();

        //animation
        startBtn->scene1();
        startBtn->scene2();


        //delay
        QTimer::singleShot(300,this,[=](){
            //set position
            chooseStage->setGeometry(this->geometry());

            //make main scene dissapear
            this->hide();
            //go to level scene
            chooseStage->show();


        });

    });

}

void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pic;
    pic.load(":/res/1.png");
    //Stretch the image to fit the screen
    painter.drawPixmap(0,0,this->width(),this->height(),pic);

}

MainScene::~MainScene()
{
    delete ui;
}

