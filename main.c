#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <stdlib.h>
#include "constantHeader.h"
#define BUFSIZE 128


int main() {
    char console_buffer[BUFSIZE];
    int son_exec_status;
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));



    while(1){
        write(STDOUT_FILENO,PROMPT, strlen(PROMPT));
        int byte_read=read(STDIN_FILENO,console_buffer,BUFSIZE);
        console_buffer[byte_read-1]= '\0';
        if (fork()==0){
            execlp(console_buffer,console_buffer,NULL);
            exit(EXIT_SUCCESS);
        }
        else{
            wait(&son_exec_status);
        }
    }


    return 0;
}

