#ifndef MINEPUSHBUTTON_H
#define MINEPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QString>

#define button_size 40 //size parameters of the button

class MinePushButton:public QPushButton
{
    Q_OBJECT

public:
    MinePushButton(bool,int,int);

    void setMinesAround(int); //function for setting the the number of mines around
    void openCell(); //default openCell function
    void hintMode(); //activate the hintMode

    //variables
    bool mine;
    int x;int y; //coordinates
    bool button_clicked=false;//variable to indicate if the button is clicked
    int minesAround;

signals:
    void clickedMine(); // signal for clicking a mine signals the finish function
    void clickedEmpty(); // signal for clicking an empty cell , signals the revealEmptyCells function
    void incrementScore(); //signal for incrementing the score when a cell is opened

private:
    void mousePressEvent(QMouseEvent*) override;
    void setBackgroundImage(int); //sets the bacground image according to the number
    void openCell(int); //base function for opening a cell
    void setButtonIcon(QString); //function for setting the Icon
    //void resizeEvent(QResizeEvent*) override; //for handling the resize event

    //variables
    QSize buttonSize;
    QString backgroundImage;


    bool flag=false;
};

#endif // MINEPUSHBUTTON_H
