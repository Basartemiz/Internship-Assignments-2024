#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

//global variables
int snake[30][2]; 
int matrix[15][15];
int bait[2];
char direction='w';
int snake_length=1;
char input='0';

//functions to be used 
void create_bait();
void get_input();
int bait_eaten();
void createSnake();
void updateSnake();
int check_bait();
void handleSignal(int signal);
void clean();
void print_matrix();

struct termios terminal_settings; //original terminal settings

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

void clean(){
    printf("\033[H\033[J"); // ANSI escape codes to clear the terminal
}


void get_input(){
   if(kbhit()){
        input=getchar();
        tcflush(STDIN_FILENO,TCIFLUSH); //flush all the old inputs 
        printf("You pressed: %c\n", input);
       
    }
}



//must update snakes information 
//must create new bait with random function
int bait_eaten(){
    snake[snake_length][0]=bait[0]; snake[snake_length][1]=bait[1]; //copy the values of the bait to the snake array
    create_bait(); //create a new bait
    snake_length++;

}
//creatates snake given snakes information
void createSnake(){

    for(int i=0;i<snake_length;i++){
        int* pos=snake[i];
        int y=*pos; int x= *(pos+1);
        matrix[y][x]='#';

    }
    int y = snake[snake_length - 1][0];
    int x = snake[snake_length - 1][1];
    matrix[y][x]='O';
}

//update snakes information if the next position is feasible
void updateSnake(){
    int add_y=0;
    int add_x=0;
        switch(direction){
            case 'w':
                add_y=-1;
                add_x=0;
                break;
            case 'd':
                add_y=0;
                add_x=1;
                break;
            case 'a':
                add_y=0;
                add_x=-1;
                break;
            case 's':
                add_y=1;
                add_x=0;
                break;
        }
    int *snake_head=snake[snake_length-1];
    int y_head=*snake_head; int x_head=*(snake_head+1);
    int y_new=y_head+add_y; int x_new=x_head+add_x;  //calculated new positions

    if(x_new<15 && x_new>=0 && y_new <15 &&y_new>=0){ //iff positions are feasible
        for(int i=0;i<snake_length;i++){
            int * pos=snake[i];
            if(y_new==*pos && x_new==*(pos+1)){
                return;  //not feasible since this is the snake's position
            }
        }

        if(check_bait()){ //if bait is eaten
            bait_eaten();
        }
        else{ //if the bait is not eaten and pos is feasible

        //if it comes to here then the next position is feasible
       for (int i = 0; i < snake_length - 1; i++) {
            snake[i][0] = snake[i + 1][0];
            snake[i][1] = snake[i + 1][1];
        }
       
        snake[snake_length-1][0]=y_new; snake[snake_length-1][1]=x_new; //add the new position
        }
    }
    else{ return; }
}

//this function checks if the bait is eaten
int check_bait() {
    int y_s = snake[snake_length - 1][0]; // Snake head's y-coordinate
    int x_s = snake[snake_length - 1][1]; // Snake head's x-coordinate

    if (x_s == bait[1] && y_s == bait[0]) { // Compare head position with bait
        return 1; // Bait is eaten
    }
    return 0; // Bait is not eaten
}

//creates a bait with a random seed
void create_bait(){
    // Seed the random number generator with the current time
    srand(time(NULL));
    
    // Generate a random integer between 1 and 15
    int y = (rand() % 15); //random x
    
    int x = (rand() % 15); //random y
    
    for (int i=0;i<snake_length-1;i++){
        int * pos=snake[i];
        if(y==*pos && x==*(pos+1)){
            return create_bait(); 
        }
    }
    bait[0]=y; bait[1]=x; //update bait

    return ;
}
//prints the matrix
void print_matrix() {
    // Clear the terminal
    printf("\033[H\033[J"); // ANSI escape codes to clear the terminal

    // Print the matrix
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            printf("%c ", matrix[y][x]);
        }
        printf("\n");
    }
}


int main(){

    signal(SIGINT, handleSignal);  // Handle Ctrl+C
    signal(SIGTERM, handleSignal); // Handle kill -TERM

    enableRawMode();

    //start the snake
    snake[0][0]=7; //snake_y 7
    snake[0][1]=7; //snake_x=10;

    //create bait
    create_bait();

    int i=0;
    while(1){ //main loop
        i++;
    
        get_input(); //collects input

        //create the matrix
        for(int y=0;y<15;y++){
            for(int x=0;x<15;x++){
                matrix[y][x]='.';
            }
        }
        //process input
        if(input=='w'){
            direction='w';
        }
        else if(input=='d'){
            direction='d';
        }
        else if(input=='a'){
            direction='a';
        }
        else if(input=='s'){
            direction='s';
        }

        if(input=='q'){
            clean();
            exit(0);
        }

        updateSnake();
        createSnake();

        matrix[bait[0]][bait[1]] = 'X'; // Place bait on the grid
        print_matrix();
        usleep(250000); //sleep for .. microseconds



        
    }
}



