#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "constantHeader.h"
#include "Prompt.h"

int main() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

    return 0;
}

