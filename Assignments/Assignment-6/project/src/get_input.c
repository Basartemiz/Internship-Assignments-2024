#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

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
   
    
    exit(0); // Exit the program
}




void get_input(){
   if(kbhit()){
        input=getchar();
        tcflush(STDIN_FILENO,TCIFLUSH); //flush all the old inputs 
        printf("You pressed: %c\n", input);
       
    }
}

int main(){
    enableRawMode();
    while(1){
    get_input();
    printf("input :%c",input);
    
    usleep(1000000);
    }
    disableRawMode();
}
