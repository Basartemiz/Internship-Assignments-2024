#include "minepushbutton.h"
#include <QPixmap>
#include <QIcon>
MinePushButton::MinePushButton(bool mine,int y,int x) : QPushButton() { //constructor
    this->mine=mine;
    this->x=x;
    this->y=y;
    this->setStyleSheet("QPushButton {"
                        " border :0px;"
                        "padding: 0px;"
                        "margin: 0px; "
                        "}");


    buttonSize.setWidth(button_size);buttonSize.setHeight(button_size) ;//set the begginning size
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setButtonIcon(":/images/empty.png"); //set Icon to be empty

}


void MinePushButton::setMinesAround(int mineCount){//function for assigning the count of the mines surronding the block
    this->minesAround=mineCount;
}

void MinePushButton::openCell(){ //default openCell method
    if(mine){
        setBackgroundImage(-1);        //this line get's called from the grid_layout so it is not a losing condition
        return;
    }
    openCell(minesAround);
}

void MinePushButton::hintMode(){ // the buttons turns into the hint mode
    if(backgroundImage==":images/hint.png"){ //hint button pressed twice
        openCell();
        return;
    }
    setButtonIcon(":images/hint.png");

}

void MinePushButton::mousePressEvent(QMouseEvent * click){   // a function to restart the game

    if(button_clicked){
        return; //return if button is clicked
    }
    if(click->button()==Qt::LeftButton){ //left click

        if(mine){
            openCell(-1);
        }
        else{
            openCell(minesAround);
        }
        button_clicked=true;
    }

    else if(click->button()==Qt::RightButton){ //right button
        if(flag){ //there is flag
            openCell(-3);
            flag=false;
        }
        else{ // there is no flag
            flag=true; // set flag to true
            openCell(-2);
        }
    }
}

void MinePushButton::setBackgroundImage(int image){    // a function to restart the game

    switch(image){

    case(-1): //mine clicked
        setButtonIcon(":/images/mine.png");
        break;
    case(-2): //right clicked without a flag
        setButtonIcon(":/images/flag.png");
        break;
    case(-3): //right clicked with a flag
        setButtonIcon(":/images/empty.png");
        break;
    default:
        QString style_string=QString(":/images/%1.png").arg(image);
        setButtonIcon(style_string);
        break;
    }
        this->setIconSize(buttonSize);
}

void MinePushButton::openCell(int backGroundImage){ //base function for opening a cell
    if(button_clicked){
        return; //return if the button is already clicked
    }

    switch(backGroundImage){
    case(0): //empty cell
        button_clicked=true; // set button_clicked to true , because the cell has already opened
        emit clickedEmpty();
        setBackgroundImage(backGroundImage);
        emit incrementScore(); //right clicked a cell with no mine
        break;

    case(-1): //mine clicked
        emit clickedMine();
        setBackgroundImage(-1);
        break;
    case(-2): //right clicked with no flag
        setBackgroundImage(-2);
        break;

    case(-3): //right clicked with a flag
        setBackgroundImage(-3);
        break;

    default:
        button_clicked=true; // set button_clicked to true , because the cell has already opened
        setBackgroundImage(backGroundImage);
        emit incrementScore(); //right clicked a cell with no mine
        break;
    }


}

void MinePushButton::setButtonIcon(QString image){

    backgroundImage=image;
    QPixmap pixmap(image);
    QPixmap scaledPixmap = pixmap.scaled(buttonSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    this->setIcon(QIcon(scaledPixmap));
    this->setFixedSize(buttonSize);
    this->setIconSize(buttonSize);  // set the size of the pixmap


}


