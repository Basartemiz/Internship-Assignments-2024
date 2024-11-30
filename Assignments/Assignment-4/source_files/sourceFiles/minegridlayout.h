#ifndef MINEGRIDLAYOUT_H
#define MINEGRIDLAYOUT_H

#include <QGridLayout>
#include <QString>
#include <minepushbutton.h>
#include <scorewidget.h>
#include <QSignalMapper>

#define N 15
#define M 15

#define K 10 //mine count


class MineGridLayout : public QGridLayout
{
    Q_OBJECT

public:
    MineGridLayout(ScoreWidget*); //constructor

private slots:
    void finish(int mod); // game ends
    void giveHint();//gives an hint
    void revealEmptyCells(int,int); //reveals empty cells recursively
    void restart(); //restart the game

private:
    void showPopUp(QString);
    void createMines();
    void calculateAroundMines(); //calculates the mines around a given mine
    void makeConnections(); // make necessary connections
    bool checkCell(int,int); //check if an uncertain cell has a mine or if an certain cell has mine for certain (e.g 2 with 2 uncertain)

    //variables
    MinePushButton *mines [N][M] ;
    ScoreWidget *scoreWidget;
    int score_point=0;
    QSignalMapper *finish_mapper;
    QSignalMapper *empty_mapper;

};

#endif // MINEGRIDLAYOUT_H
