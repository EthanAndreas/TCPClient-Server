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

    // create the connexion between the client and the server
    int connect_fd;
    CHK(connect_fd = accept(socket_fd, (struct sockaddr *)&servaddr,
                            sizeof(servaddr)));

    // assign an address to the socket
    CHK(bind(connect_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)));

    // pass to a passive socket
    CHK(listen(connect_fd, 5));

    fd_set read_fds;
    FD_ZERO(&read_fds);

    buffer[0] = '\0';
    while (strcmp(buffer, "exit\n") != 0) {

        FD_SET(connect_fd, &read_fds);
        FD_SET(0, &read_fds);
        // choose the file descriptor (the client)
        select(connect_fd + 1, &read_fds, NULL, NULL, NULL);

        // recv
        if (FD_ISSET(connect_fd, &read_fds)) {
            CHK(recv(connect_fd, buffer, MAXLINE, 0));
            printf("%s", buffer);
        }
    }

    // close
    CHK(close(socket_fd));

    return 0;
}
