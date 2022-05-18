#include "../include/set.h"

int main(void) {

    int sockfd, n;
    struct sockaddr_in servaddr;

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // init servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr);

    // create the connection between the client and the server
    CHK(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)));

    // send the package to the server
    send(sockfd, "exit", 4, 0);

    // close
    close(sockfd);

    return 0;
}