
//
// Created by Evmurzaev Deni on 11/12/2023.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include <fcntl.h>
#define BUFSIZE 256
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int main ( int argc, char *argv[]) {
    char server[20], file[20];
    strcpy(server, argv[1]);
    strcpy(file, argv[3]);

    printf("Server : %s\n", server);
    printf("File : %s\n", file);

    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;

    int en = getaddrinfo(server, "1069", &hints, &res);
    if (en == -1) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

}
