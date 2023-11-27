#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "constantHeader.h"
int main() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
    return 0;
}

