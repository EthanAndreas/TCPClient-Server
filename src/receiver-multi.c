#include "../include/set.h"

int main(void) {

    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr[MAXCLIENT];
    char buffer[MAXLINE];
    char *init_connection = "Connection established\n";
    int i;

    // create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // the highest descriptor when connection is established
    int master_fd;
    // descriptor for a new connection
    int new_fd;

    // mutli-client securing
    int opt = 1;
    SCHK(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                    sizeof(opt)));

    // init servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(SERV_PORT);
    ICHK(inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr));

    // display
    printf("Listener on port %d \n", SERV_PORT);

    // assign an address to the socket
    socklen_t addrlen = (socklen_t)sizeof(servaddr);
    CHK(bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)));

    // pass to a passive socket
    CHK(listen(socket_fd, MAXCLIENT));

    // create the connexion between the client and the server
    int connect_fd[MAXCLIENT];
    // empty connection at the beginning
    for (i = 0; i < MAXCLIENT; i++)
        connect_fd[i] = 0;

    fd_set read_fds;

    for (;;) {

        FD_ZERO(&read_fds);
        FD_SET(socket_fd, &read_fds);
        master_fd = socket_fd;

        for (i = 0; i < MAXCLIENT; i++) {

            // if there is a valid socket descriptor then add to read list
            if (connect_fd[i] > 0)
                FD_SET(connect_fd[i], &read_fds);

            // we need the highest file descriptor number for select
            if (connect_fd[i] > master_fd)
                master_fd = connect_fd[i];
        }

        // wait for an activity on one of the sockets
        SCHK(select(master_fd + 1, &read_fds, NULL, NULL, NULL));

        // new connection when the master socket received something
        if (FD_ISSET(socket_fd, &read_fds)) {

            CHK(new_fd = accept(socket_fd, (struct sockaddr *)&servaddr,
                                &addrlen));

            printf("New connection\n"
                   "    socket : %d\n"
                   "    ip : %s\n"
                   "    port : %d\n",
                   new_fd, SERV_IP, SERV_PORT);

            // notify the new connection to the client
            send(new_fd, init_connection, strlen(init_connection), 0);

            // add new socket to array of sockets
            for (i = 0; i < MAXCLIENT; i++) {

                // if position is empty
                if (connect_fd[i] == 0) {

                    connect_fd[i] = new_fd;
                    break;
                }
            }

            // if we receive an information, print it
            CHK(recv(connect_fd[i], buffer, MAXLINE, 0));
            printf("%s", buffer);

            // if we receive from the keyboard, send it
            if (FD_ISSET(0, &read_fds)) {
                // send the package to the server
                fgets(buffer, MAXLINE, stdin);
                send(connect_fd[i], "success sending", MAXLINE, 0);
            }
        }

        // if (strcmp(buffer, "exit") >= 0) {
        // break;
        // }
    }

    // close the connecction
    for (i = 0; i < MAXCLIENT; i++) {
        if (connect_fd[i] != 0)
            CHK(close(connect_fd[i]));
    }

    CHK(close(socket_fd));

    return 0;
}
