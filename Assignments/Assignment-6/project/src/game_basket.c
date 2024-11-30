#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>



//functions
void createBasket(); //prints basket
void createObject(); //creates object in the matrix , update the y value
int checkCollision(); //check collision if the basket has touched the falling object
void initializeObject(); //initialize the object when object[y]<0
void updateBasket(); //updates basket with respect to the direction
void print_matrix(); //creates the matrix which everything resides
void clean(); //cleans the terminal

//variables
int basket[3][2]; 
int matrix[15][20];
int object[2];
char direction='w';
int score=0;
int basket_length=3;

//input handling functions and variables and signal handling 
struct termios terminal_settings; //original terminal settings
char input='0';

void enableRawMode() { //function to enable raw mode on terminal to take real time input
    struct termios modf; //original terminal settings
    tcgetattr(STDIN_FILENO,&terminal_settings);
    modf=terminal_settings; //copy the settings in order to modify them
    modf.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &modf); //apply the changes 

}

void disableRawMode(){
    tcsetattr(STDIN_FILENO,TCSANOW ,&terminal_settings); 
}

//function to check if a key is pressed
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Save the old terminal attributes
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set stdin to non-blocking
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    // Restore terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin); // Put character back into the input buffer
        return 1; // Key was pressed
    }

    return 0; // No key was pressed
}
void handleSignal(int signal) {
   
    clean();
    
    exit(0); // Exit the program
}




void get_input(){
   if(kbhit()){
        input=getchar();
        tcflush(STDIN_FILENO,TCIFLUSH); //flush all the old inputs 
    }
}



void createBasket(){
     for(int i=0;i<basket_length;i++){
        int* pos=basket[i];
        int y=*pos; int x= *(pos+1);
        matrix[y][x]='-';

    }
}

void createObject(){
    object[0]+=1;  //y+1
    matrix[object[0]][object[1]]='O'; // create the object
}

int checkCollision(){
    for(int i=0;i<basket_length;i++){
        if(basket[i][0]==object[0] && basket[i][1]==object[1]){
            return 1;
        }
    }
    return 0;
}


void initializeObject(){

    srand(time(NULL));
    
    int x = (rand() % 20); //random x
    
    
    object[0]=0; object[1]=x; //update object
}

void updateBasket(){

    if(direction=='a'){ //go to left
        int new_x=basket[0][1]-1;
        if(new_x>=0){ //new position is feasible
            //update the basket
            for(int i=0;i<basket_length;i++){
                basket[i][1]-=1; //decrease x
            }
            
    }
    }
    else if(direction=='d'){ //go to right
        int new_x=basket[2][1]+1;
        if(new_x<20){ //new position is feasible
            for(int i=0;i<basket_length;i++){
                
                basket[i][1]+=1; //increase x
            }
            
        }
    }
    
}



void print_matrix() {
    // Clear the terminal
    printf("\033[H\033[J"); // ANSI escape codes to clear the terminal

    // Print the matrix
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 20; x++) {
            printf("%c ", matrix[y][x]);
        }
        printf("\n");
    }
}

void clean(){
    printf("\033[H\033[J"); // ANSI escape codes to clear the terminal
}

int main(){
    enableRawMode();

    signal(SIGINT, handleSignal);  // Handle Ctrl+C
    signal(SIGTERM, handleSignal); // Handle kill -TERM

    //initalize basket
    basket[0][0]=14; basket[0][1]=9;
    basket[1][0]=14; basket[1][1]=10;
    basket[2][0]=14; basket[2][1]=11;


    while(1){
    get_input();
    
    //game logic

        //process input
        if(input=='a'){
            direction='a';
        }
        else if(input=='d'){
            direction='d';
        }
        else if(input=='q'){
            clean();
            exit(0);
        }

        //create the matrix
        for(int y=0;y<15;y++){
            for(int x=0;x<20;x++){
                matrix[y][x]='.';
            }
        }
        if(object[0]==14){ //object is at the ground
            if(checkCollision()){ //if there is a collision
                score++;
                initializeObject();
            }
            else{
                score=0; //restore the score
            }
        }
        else if(object[0]>14){ //object is out of range 
            initializeObject();
        }
        updateBasket();
        createBasket();
        createObject();

        //printMatrix
        print_matrix();
        printf("Current score %d\n",score); //print the current score
        


    
    usleep(100000);
    }
    disableRawMode(); //return the normal terminal settings
}
