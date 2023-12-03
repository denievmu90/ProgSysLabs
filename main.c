#include <stdio.h>
#include <unistd.h>
#include <string.h>
//#include <wait.h>
#include <stdlib.h>
#include "constantHeader.h"
#define BUFSIZE 128


int main() {
    char console_buffer[BUFSIZE];
    int son_exec_status;
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
    while (1) {
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
        int byte_read = read(STDIN_FILENO, console_buffer, BUFSIZE);
        console_buffer[byte_read - 1] = '\0';
        //if the process is the child then we are able to write in the terminal
        if (fork() == 0) {
            execlp(console_buffer, console_buffer, NULL);
            exit(EXIT_SUCCESS);
        } else{
            wait(&son_exec_status);
        }
            if (strcmp(console_buffer, "exit") == 0) {
                // If we type "exit" , the code will display a bye bye message and exit the program
                const char exit_message[] = "Bye bye...";
                write(STDOUT_FILENO, exit_message, sizeof(exit_message));
                break;
            }

            ssize_t console_buffer_length = read(STDIN_FILENO, console_buffer, sizeof(console_buffer));
            if (console_buffer_length == 0) {
                // If the command is <ctrl>+d, display a bye bye message and exit the program
                const char exit_message[] = "Bye bye...";
                write(STDOUT_FILENO, exit_message, sizeof(exit_message));
                break;
            }

        }


        return 0;
    }

