#include "minegridlayout.h"
#include <QMessageBox>
#include <random>



MineGridLayout::MineGridLayout(ScoreWidget *scoreWidget):QGridLayout() {  //constructor

    this->setHorizontalSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(0); //remove distances between objects

    createMines();
    calculateAroundMines();
    this->scoreWidget=scoreWidget;
    makeConnections();





}

void MineGridLayout::finish(int mod){   //finish slot
    if(mod==0){
        showPopUp("You lose!");
    }
    else{
        showPopUp("You win!");
    }
}

void MineGridLayout::giveHint(){    //hint slot
    //find the clicked cells
    for(int y=0;y<N;y++)  {
        for(int x=0;x<M;x++){
            if(mines[y][x]->button_clicked) { //if the button is clicked

                int certain_mines=0; //certain_mines count
                int uncertain_cells=0;// uncertain cell count

                //check the surroinding cells
                for(int y_plus=-1;y_plus<2;y_plus++){
                    for(int x_plus=-1;x_plus<2;x_plus++){
                        if(x_plus==0 && y_plus==0){
                            continue;
                        }
                        if(x+x_plus>=0 && x+x_plus<M && y+y_plus>=0 && y+y_plus<N){
                            if(mines[y+y_plus][x+x_plus]->button_clicked==false){ //uncertain cell
                                if(checkCell(y+y_plus,x+x_plus)){ // if there is a mine in a surroinding cell
                                    certain_mines++;
                                }
                                uncertain_cells++;
                            }
                        }

                    }
                }

                if(uncertain_cells>certain_mines && certain_mines==mines[y][x]->minesAround){ // there is a cell we can open (e.g. 4 uncertain cell with 2 certain mine with the mine count 2)
                    //give hint to the first uncertain cell
                    for(int y_plus=-1;y_plus<2;y_plus++){
                        for(int x_plus=-1;x_plus<2;x_plus++){
                            if(x_plus==0 && y_plus==0){
                                continue;
                            }
                            if(x+x_plus>=0 && x+x_plus<M && y+y_plus>=0 && y+y_plus<N){

                                if(mines[y+y_plus][x+x_plus]->button_clicked==false){ //check if the cell is not opened alredy

                                    if(checkCell(y+y_plus,x+x_plus)==false){ // uncertain cell is found
                                    mines[y+y_plus][x+x_plus]->hintMode(); //activate the hint mode
                                    return; //return after giving the hint
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

void MineGridLayout::showPopUp(QString name){   // a function to throw popUps

    QMessageBox *popUp=new QMessageBox();

    popUp->setText(name); //set the name of the popUp
    popUp->setIcon(QMessageBox::NoIcon); //remove the icon

    QPushButton *okButton=popUp->addButton("OK",QMessageBox::NoRole); //adding the "OK" button

    popUp->exec();

    if(popUp->clickedButton()==okButton){

        //reveal all the mines
        for(int y=0;y<N;y++)  {
            for(int x=0;x<M;x++){
                if(mines[y][x]->mine){
                    mines[y][x]->openCell(); //reveal the mines
                }
                mines[y][x]->button_clicked=true; //make the button unclickable
            }
        }

    }
}

void MineGridLayout::restart(){   // a function to restart the game

    //delete the mines
    for(int y=0;y<N;y++)  {
        for(int x=0;x<M;x++){
            this->removeWidget(mines[y][x]); //remove the button from the widget
            delete(mines[y][x]);
        }
    }


    scoreWidget->zeroScore(); //zero the score
    scoreWidget->disconnect(); //disconnect all the signals before connecting them again in makeConnections

    //create cells and mines
    createMines(); //creating the mines again
    calculateAroundMines(); //calculating the surrounding mines
    makeConnections();
}

void MineGridLayout::createMines(){    //creates Cells with the right amount of  mines
    for(int y=0;y<N;y++)  {
        for(int x=0;x<M;x++){
            mines[y][x]=new MinePushButton(false,y,x);
            this->addWidget(mines[y][x],y,x);

        }
    }
    int mine_laid=0;
    int x=0;int y =0;

    // create a random generator
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> getRandom(0, M*N);

    while(mine_laid<K){ //laying random mine
        int random_number=getRandom(gen)%5;
        qDebug()<<random_number;
        if(random_number==1 && mines[y][x]->mine==false){
            mines[y][x]->mine=true; //put the mine
            mine_laid++;
        }
        x+=getRandom(gen);
        y+=getRandom(gen);
        x=x%M;
        y=y%N;

    }


}

void MineGridLayout::calculateAroundMines(){   // a function for calculating the mine count
    for(int y=0;y<N;y++){
        for(int x=0;x<M;x++) {
            int mine_count=0;

            //calculate the mine count
            for(int y_plus=-1;y_plus<2;y_plus++){
                for(int x_plus=-1;x_plus<2;x_plus++){
                    if(x_plus==0 && y_plus==0){
                        continue;
                    }
                    if(x+x_plus>=0 && x+x_plus<M && y+y_plus>=0 && y+y_plus<N){
                        if(mines[y+y_plus][x+x_plus]->mine){
                            mine_count++;
                        }
                    }
                }
            }

            mines[y][x]->setMinesAround(mine_count);


        }
    }
}

void MineGridLayout::revealEmptyCells(int x, int y){ // recursively reveal empty cells
    for(int y_plus=-1;y_plus<2;y_plus++){
        for(int x_plus=-1;x_plus<2;x_plus++){
            if(x_plus==0 && y_plus==0){
                continue;
            }
            if(x+x_plus>=0 && x+x_plus<M && y+y_plus>=0 && y+y_plus<N){
                if(mines[y+y_plus][x+x_plus]->mine==false ){
                    mines[y+y_plus][x+x_plus]->openCell();
                }
            }
        }
    }
}

void MineGridLayout::makeConnections(){


    //connect buttons
    for(int y=0;y<N;y++){
        for(int x=0;x<M;x++) {
            QObject::connect(mines[y][x],&MinePushButton::clickedMine,this,[this](){
                finish(0);
            }); //connect the clickedMine signal
            QObject::connect(mines[y][x],&MinePushButton::clickedEmpty,this,[y,x, this](){
                revealEmptyCells(x,y);
            }); //connect the clickedMine signal

            QObject::connect(mines[y][x],&MinePushButton::incrementScore,this,[this](){
                (scoreWidget->updateScore()); //update the score
            });

        }
    }

    //connect the signals of the scoreWidget
    QObject::connect(scoreWidget,SIGNAL(retry_clicked()),this,SLOT(restart())); //restart condition
    QObject::connect(scoreWidget,SIGNAL(hint_clicked()),this,SLOT(giveHint())); //give hint condition
    QObject::connect(scoreWidget,&ScoreWidget::game_won,this,[this](){ //game win condition
        finish(1);
    });

}

bool MineGridLayout::checkCell(int y, int x){
    //handle the unclicked case, this should return true if one of the surroinding cells have certainly mines
    if(mines[y][x]->button_clicked==false){
        //check the surroinding cells
        for(int y_plus=-1;y_plus<2;y_plus++){
            for(int x_plus=-1;x_plus<2;x_plus++){
                if(x_plus==0 && y_plus==0){
                    continue;
                }
                if(x+x_plus>=0 && x+x_plus<M && y+y_plus>=0 && y+y_plus<N){
                    if(mines[y+y_plus][x+x_plus]->button_clicked){ //check the uncertain cells
                        if(checkCell(y+y_plus,x+x_plus)){
                            return true; // return true if surroinding cells have certainly mines
                        }
                    }
                }
            }
        }
        return false; // returns false if there is no surroinding cell that has mines for sure
    }

    //handle the clicked case , this case should return true if in the surrounding cells ,the number of uncertain cells is equal to the mine count
    else{
        int uncertainCell=0;
        for(int y_plus=-1;y_plus<2;y_plus++){
            for(int x_plus=-1;x_plus<2;x_plus++){
                if(x_plus==0 && y_plus==0){
                    continue;
                }
                if(x+x_plus>=0 && x+x_plus<M && y+y_plus>=0 && y+y_plus<N){
                    if(mines[y+y_plus][x+x_plus]->button_clicked==false){ //check the uncertain cells
                        uncertainCell++;
                    }
                }
            }

        }
        return uncertainCell==mines[y][x]->minesAround; //return true if the equality holds
    }


}
