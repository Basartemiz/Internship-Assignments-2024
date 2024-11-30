#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>



//functions
void createChar();  //creates a ASCII charachter that we should use 
void clean(); //cleans the terminal and if necessary the terminal
//variables
int minimum_time=0;
char currentChar='0';

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


void clean(){
    printf("\033[H\033[J"); // ANSI escape codes to clear the terminal
}
void createChar(){
    int random_offset = rand() % 26;

    currentChar = 'a' + random_offset;
    if (currentChar=='q'){ //cannot be q
       return createChar();
    }
}







int main(){
    enableRawMode();

    signal(SIGINT, handleSignal);  // Handle Ctrl+C
    signal(SIGTERM, handleSignal); // Handle kill -TERM

    //initlialize char
    createChar();
    int time=0;
    int current_minimum=0;
    while(1){
    get_input();
    
    //game logic
        if(input=='q'){
            clean();
            exit(0);
        }
        //process input
        if(input==currentChar){ //input detected
            if(time<minimum_time || minimum_time==0){
                minimum_time=time;
            }
            current_minimum=time; //set the current minimum
            time=0; //restore time
            
            createChar();
        }
       
    printf("\033[H\033[J"); // ANSI escape codes to clear the terminal
    printf("Please click '%c' as soon as possible ! \n\n\n",currentChar);
    printf("all time  minimum time : %d miliseconds \n\n",minimum_time);
    printf("current  minimum time : %d miliseconds \n",current_minimum);

    time++;
    usleep(1000); //microseconds 
    }
    disableRawMode(); //return the normal terminal settings
}
