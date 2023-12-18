#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFSIZE 516

int main(int argc, char *argv[]) {

    char server[20], file[20], mode[]="octet";
    strcpy(server, argv[1]);
    strcpy(file, argv[2]);

    printf("Host : %s\n", server);
    printf("File : %s\n", file);

    char file_content[BUFSIZE- 4];
    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo)); // Initialize at 0
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

    // WRQ request
    char WRQ[BUFSIZE];
    memset(WRQ, 0, BUFSIZE);
    WRQ[1] = 2; // writing mode
    strcpy(WRQ + 2, argv[3]);
    size_t padding = strlen(WRQ+2);
    strcpy(WRQ + 2 + padding + 1, mode);
    size_t padding2 = strlen(WRQ + 3 + padding);
    int n_bytes = sendto(sock, WRQ, padding + padding2 + 4, 0, res->ai_addr, res->ai_addrlen);
    if ((n_bytes)  == -1) {
        perror("send WRQ");
        exit(EXIT_FAILURE);
    }
    printf("WRQ sent : OK\n");
    // Opening and reading of the file in argument
    int fd = open(argv[3], O_RDONLY);
    if (fd == -1) {
        perror("Open file");
        exit(EXIT_FAILURE);
    }

    if ((n_bytes = read(fd, file_content, BUFSIZE - 4)) == -1) {
        perror("read file");
        exit(EXIT_FAILURE);
    }

    // Data packet creation
    memset(WRQ, 0, BUFSIZE);
    WRQ[1] = 3;
    WRQ[3] = 0;
    strcpy(WRQ + 4, file_content);
    padding = strlen(WRQ + 4);

    // send DATA
    if (sendto(sock, WRQ, padding + 4, 0, res->ai_addr, res->ai_addrlen) == -1) {
        perror("Send DATA");
        exit(EXIT_FAILURE);
    }

    printf("DATA PACKET SEND : ");
    for (int i = 0; i < 4; i++) {
        printf("%x", WRQ[i]);
    }
    for (int i = 4; i < padding + 4; i++) {
        printf("%c", WRQ[i]);
    }
    printf("\n");

    // Reception ACK
    if (recvfrom(sock, WRQ, 4, 0, res->ai_addr, &res->ai_addrlen) == -1) {
        perror("Receive ACK");
        exit(EXIT_FAILURE);
    }

    printf("ACK serveur : ");
    for (int i = 0; i < 4; i++) {
        printf("%x", WRQ[i]);
    }
    printf("\n");

    exit(EXIT_SUCCESS);

}

