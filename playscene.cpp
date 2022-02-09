#include "playscene.h"
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>



PlayScene::PlayScene(int stageNum){
    QString str = QString("Stage %1").arg(stageNum);
    qDebug() << str;
    this->stageIndex = stageNum;

    this->setFixedSize(320,600);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("CoinFlip");

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

    //sounds(back,flip,win)
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);



    //back button
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //clicked back
    connect(backBtn,&MyPushButton::clicked,[=](){
        //play back sound
        backSound->play();
        //delay time
        QTimer::singleShot(300,this,[=](){
            emit this->changeScene();
        });
    });

    //show stages
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(20);
    QString tex = QString("Level %1").arg(this->stageIndex);
    //put font inside label
    label->setFont(font);
    label->setStyleSheet("QLabel {color : white;}");
    label->setText(tex);
    label->setGeometry(25, this->height() - 50,120,50);

    //reset the data for each stage
    dataConfig config;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->gameArray[i][j] = config.mData[this->stageIndex][i][j];
        }
    }

    //display win image
    QLabel *winImg = new QLabel;
    QPixmap wpic;
    wpic.load(":/res/LevelCompletedDialogBg.png");
    winImg->setGeometry(0,0,wpic.width(),wpic.height());
    winImg->setPixmap(wpic);
    winImg->setParent(this);
    winImg->move(this->width() - wpic.width()*0.5, -wpic.height());



    //display coin background
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            QPixmap pic = QPixmap(":/res/BoardNode.png");
            QLabel *label1 = new QLabel;
            label1->setGeometry(0,0,pic.width(),pic.height());
            label1->setPixmap(pic);
            label1->setParent(this);
            label1->move(57+ i*50,200+j*50);


            //create coin
            QString str;
            if(this->gameArray[i][j] == 1){
                str = ":/res/Coin0001.png";
            }
            else{
                str = ":/res/Coin0008.png";
            }

            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+ i*50,204+j*50);

            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];//1 front 2 back

            //Put coin in the array
            coinBtn[i][j] = coin;


            //click to flip
            connect(coin,&MyCoin::clicked,[=](){
                //play sound
                flipSound->play();

                //locked all the button first
                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        this->coinBtn[i][j]->isWin = true;
                    }
                }


                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                //flip area coin(right)
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX + 1 <=3){
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }
                    //flip left
                    if(coin->posX - 1 >= 0){
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }
                    //flip top
                    if(coin->posY + 1 <= 3){
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                    }
                    //flip bottom
                    if(coin->posY -1 >= 0){
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                    }
                    //after flipped unlock all the coin
                    for(int i =0; i < 4; i++){
                        for(int j = 0; j < 4;j++){
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    //chcek if all coin were flip(win)
                    this->isWin = true;
                    for(int i = 0; i < 4; i ++){
                        for(int j = 0; j < 4; j++){
                            if(coinBtn[i][j]->flag == false){
                                this->isWin = false;
                                break;
                            } //if any hasn't flip still playing
                        }
                    }
                    if(this->isWin == true){
                        winSound->play();
                        qDebug() << "you won!";
                        for(int i = 0; i < 4; i ++){
                            for(int j = 0; j < 4; j++){
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        //bring the win img down
                        QPropertyAnimation *wanimation = new QPropertyAnimation(winImg,"geometry");

                        //set time between drop
                        wanimation->setDuration(1000);
                        //start pos
                        wanimation->setStartValue(QRect(winImg->x(),winImg->y()+130,winImg->width(),winImg->height()));
                        //ending pos
                        wanimation->setEndValue(QRect(winImg->x()-150,winImg->y()+130,winImg->width(),winImg->height()));
                        //pos
                        wanimation->setEasingCurve(QEasingCurve::OutBounce);
                        //start ani
                        wanimation->start();
                    }
                });

            });
        }
    }


}


void PlayScene::paintEvent(QPaintEvent *){
    //create background
    QPainter painter(this);
    QPixmap pic;
    pic.load(":/res/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pic);

    //Title


}
