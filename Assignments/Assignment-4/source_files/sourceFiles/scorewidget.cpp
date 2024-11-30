
#include "scorewidget.h"
#include <minegridlayout.h>

ScoreWidget::ScoreWidget() : QHBoxLayout() { //constructor

    createUnits();

    QObject::connect(retryButton,SIGNAL(clicked()),this,SLOT(retryButton_clicked())); //connect retryButton's clicked signal to retry_clicked function
    QObject::connect(hintButton,SIGNAL(clicked()),this,SLOT(hintButton_clicked())); //connect hintButtons's clicked signal to hint_clicked function
}


void ScoreWidget::updateScore(){ // function to update score

    score_point++; //increment the score
    QString new_score=QString::number(score_point);
    QString new_text="Score: "+new_score+"      " ; //initialize the text of the QLineEdit widget

    score->setText(new_text);
    if(score_point==N*M-K){ //game won condition
        emit game_won();
    }
}

void ScoreWidget::zeroScore(){
    score_point=0;
    QString new_score=QString::number(score_point);
    QString new_text="Score: "+new_score+"      " ; //initialize the text of the QLineEdit widget

    score->setText(new_text);
}

void ScoreWidget::createUnits(){ //function for initializing necessary variables

    score=new QLabel("Score: 0       ");
    retryButton=new QPushButton("Restart");
    hintButton=new QPushButton("Hint");

    this->addWidget(score);
    this->addWidget(retryButton);
    this->addWidget(hintButton);

}

void ScoreWidget::retryButton_clicked(){
    emit retry_clicked();
}

void ScoreWidget::hintButton_clicked(){
    emit hint_clicked();
}

