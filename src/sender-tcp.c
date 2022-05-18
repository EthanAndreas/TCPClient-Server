#include "../include/set.h"

int main(void) {

    struct sockaddr_in servaddr;
    char buffer[MAXLINE];

    // create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // init servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    ICHK(inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr));

    // create the connection between the client and the server
    CHK(connect(socket_fd, (struct sockaddr *)&servaddr,
                sizeof(servaddr)));

    fd_set read_fds;
    FD_ZERO(&read_fds);

    buffer[0] = '\0';
    while (strcmp(buffer, "exit") != 0) {

        FD_SET(socket_fd, &read_fds);
        FD_SET(0, &read_fds);
        // choose the file descriptor (the client)
        select(socket_fd + 1, &read_fds, NULL, NULL, NULL);

        // if we receive an information, receive it
        if (FD_ISSET(socket_fd, &read_fds)) {
            CHK(recv(socket_fd, buffer, MAXLINE, 0));
            printf("%s", buffer);
        }

        // if we receive from the keyboard, send it
        if (FD_ISSET(0, &read_fds)) {
            // send the package to the server
            fgets(buffer, MAXLINE, stdin);
            send(socket_fd, buffer, MAXLINE, 0);
        }
    }

    // close
    close(socket_fd);

    return 0;
}