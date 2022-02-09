#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //import gold coin or silver coin
    MyCoin(QString btnImg);

    //for coin flipping
    int posX;
    int posY;
    bool flag; //flipped or not flipped

    //change the sign of flag
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 8;

    //animation
    bool animation = false;

    //clicked and released
    void mousePressEvent(QMouseEvent *e);

    //check win
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
