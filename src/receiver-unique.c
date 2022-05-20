#include "../include/set.h"

int main(void) {

    struct sockaddr_in servaddr, clientaddr;
    char buffer[MAXLINE];
    char *init_connection = "Connection established\n";

    // create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // init servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    ICHK(inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr));

    // display
    printf("Listener on port %d \n", SERV_PORT);

    // assign an address to the socket
    CHK(bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)));

    // pass to a passive socket
    CHK(listen(socket_fd, 5));

    // create the connexion between the client and the server
    // on fera un tableau de client avec accept dans la boucle qui parcout
    // tout avec un for
    int connect_fd;
    socklen_t addrlen = sizeof(clientaddr);
    CHK(connect_fd =
            accept(socket_fd, (struct sockaddr *)&clientaddr, &addrlen));

    // display
    printf("New connection\n"
           "    socket : %d\n"
           "    ip : %s\n"
           "    port : %d\n",
           connect_fd, SERV_IP, SERV_PORT);

    // notify the new connection to the client
    send(connect_fd, init_connection, strlen(init_connection), 0);

    fd_set read_fds;
    FD_ZERO(&read_fds);

    for (;;) {

        FD_SET(connect_fd, &read_fds);
        FD_SET(0, &read_fds);
        // choose the file descriptor (the client)
        select(connect_fd + 1, &read_fds, NULL, NULL, NULL);

        // if we receive an information, receive it
        if (FD_ISSET(connect_fd, &read_fds)) {
            CHK(recv(connect_fd, buffer, MAXLINE, 0));
            printf("%s", buffer);
        }

        // if we receive from the keyboard, send it
        if (FD_ISSET(0, &read_fds)) {
            // send the package to the server
            fgets(buffer, MAXLINE, stdin);
            send(connect_fd, buffer, MAXLINE, 0);
        }

        if (strcmp(buffer, "exit") >= 0) {
            break;
        }
    }

    // close
    CHK(close(connect_fd));
    CHK(close(socket_fd));

    return 0;
}