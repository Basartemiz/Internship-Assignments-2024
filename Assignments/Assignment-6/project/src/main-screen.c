#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>


//functions
void get_games(); //function to get games
void printMenu(); //prints the main menu
void clean(); //cleans the terminal and dynamically allocated variables 

//variables
char game_list[3][20] ; //store games with prefix
char game_list_base[3][20] ; //store games base name
int start_exit=0; //if it is 0 automatically it is on start
int* selected_game; //index of the selected game , we must allocate on the heap


//functions and variables for input handling and signal handling
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
    }
    else{
        input=' '; //if input is not pressed set it to null
    }
    
}


void clean(){
     free(selected_game);
     printf("\033[H\033[J"); // Clear the terminal
}


void get_games(){
    DIR *dir; //directory pointer

    struct dirent *directory_entry; //directory entry pointer

    dir=opendir("."); //open the current directory
    int game_count=0;
    while ((directory_entry = readdir(dir)) != NULL) { //get entries
        if(strncmp(directory_entry->d_name,"game_",5)==0){
            snprintf(game_list[game_count], 20, "./%s", directory_entry->d_name);
            strcpy(game_list_base[game_count], directory_entry->d_name); //copy the name of the game
            game_count++;
        }
    }

    closedir(dir); //close the directory
}

void printMenu(){
    printf("\033[H\033[J"); // Clear the terminal
    printf("===        Welcome to the Console !        ===\n");
    printf("===        use w/s to switch               ===\n");
    printf("===        use a/d to start or exit        ===\n\n\n");

    for(int i=0;i< 3;i++){
        if(i==*selected_game){
            if(start_exit==0){
                printf("[START]     {%s}     EXIT\n",game_list_base[*selected_game]);
            }
            else{
                printf("START     {%s}    [EXIT]\n",game_list_base[*selected_game]);
            }
        }
    }

}
int main(){
    enableRawMode();

    signal(SIGINT, handleSignal);  // Handle Ctrl+C
    signal(SIGTERM, handleSignal); // Handle kill -TERM
    
    get_games(); //get the games

    //allocate selected game
    selected_game=(int*)malloc(sizeof(int));
    
    //main loop
    while(1){
    get_input();
    
    //process input
    
    if (input == 'w') {
            *selected_game = (*selected_game - 1 + 3) % 3; //increase the selected game
        } else if (input == 's') {
            *selected_game = (*selected_game - 1 + 3) % 3; //decrease the selected game
        } else if (input == '\n') { // Enter key pressed
           if(start_exit==0){ //if it is in the start mode
                system(game_list[*selected_game]); // Use system to launch the game
           }
           else{ //it is in the exit mode
                clean();
                exit(0);
           }
        }
        else if(input=='a'){
            start_exit=0; //set start 
        }
        else if(input=='d'){ //s
             start_exit=1; //set exit
        }
        else if (input == 'q') {
            clean();
            exit(0);
            
        }
        
    printMenu();
    
    usleep(10000);
    }
    disableRawMode();
}
