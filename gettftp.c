
//
// Created by Evmurzaev Deni on 11/12/2023.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include <fcntl.h>
#define BUFSIZE 512
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int main ( int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <server> <port> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char server[20], file[20], mode[]="octet";
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

    int en = getaddrinfo(server, argv[2], &hints, &res);
    if (en == -1) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    char RRQ[BUFSIZE];
    memset(RRQ, 0, BUFSIZE);
    RRQ[1] = 1;
    strcpy(RRQ + 2, argv[3]);
    size_t padding = strlen(RRQ+2);
    strcpy(RRQ + 2 + padding + 1, mode);
    size_t padding2 = strlen(RRQ + 3 + padding);

    if (sendto(sock, RRQ, padding + padding2 + 4, 0, res->ai_addr, res->ai_addrlen) == -1) {
        perror("send RRQ");
        exit(EXIT_FAILURE);
    }
    int n_bytes = BUFSIZE;

    while(n_bytes == BUFSIZE) {

        // First reception
        if ((n_bytes = recvfrom(sock, RRQ, BUFSIZE, 0, res->ai_addr, &res->ai_addrlen)) == -1) {
            perror("receive DATA");
            exit(EXIT_FAILURE);
        }
        printf("Heading : ");
        for (int i = 0; i < 4; i++) {
            printf("%x", RRQ[i]);
        }
        printf("\nFile content: ");
        for (int i = 4; i < n_bytes; i++) {
            printf("%d", RRQ[i]);
        }
        printf("\n");

        // Sending ACK
        RRQ[1] = 4;
        printf("Sending ACK : ");
        for (int i = 0; i < 4; i++) {
            printf("%d", RRQ[i]);
        }
        printf("\n");
    }


    if (sendto(sock, RRQ, 4, 0, res->ai_addr, res->ai_addrlen) == -1) {
        perror("Send ACK");
        exit(EXIT_FAILURE);
    }
    printf("ACK send\n");


    close(sock);
    freeaddrinfo(res);

    exit(EXIT_SUCCESS);



}
