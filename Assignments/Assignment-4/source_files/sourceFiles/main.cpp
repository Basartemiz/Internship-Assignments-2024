
#include <QApplication>
#include <QWidget>
#include <scorewidget.h>
#include <QVBoxLayout>
#include <minegridlayout.h>

#define space 100 //pre-defined space variable for giving enough space for items in the main container

int main(int argc, char *argv[]){

    QApplication app(argc,argv); //create the app variable


    QWidget * mainWidget=new QWidget(); //create the main widget


    QVBoxLayout * container=new QVBoxLayout(mainWidget); // create the main container


    ScoreWidget * scoreWidget=new ScoreWidget(); // creating the first element of the container

    MineGridLayout *mineLayout=new MineGridLayout(scoreWidget); // create the mines
    mineLayout->setAlignment(Qt::AlignCenter);

    QWidget *mineLayoutContainer=new QWidget(); //container for the mineLayout
    //mineLayoutContainer->setFixedSize(300,300);

    mineLayoutContainer->setLayout(mineLayout);

    container->addLayout(scoreWidget); // adding elements to container

    container->addWidget(mineLayoutContainer);

    qDebug()<<mainWidget->size();


    //mainWidget->setFixedSize(M*button_size+space,N*button_size+space); //set fixed size of the mainWidget

    mainWidget->setFixedSize(mainWidget->sizeHint());

    mainWidget->show(); //show the main layout

    app.exec();
}
