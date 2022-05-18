#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 1024
#define SERV_PORT 8888
#define SERV_IP "127.0.0.1"

#define BLU "\e[30m"
#define NC "\e[0m"

#define CHK(op)            \
    do {                   \
        if ((op) == -1)    \
            alert(1, #op); \
    } while (0)

#define ICHK(op)                     \
    do {                             \
        if ((op) == -1 || (op) == 0) \
            alert(1, #op);           \
    } while (0)

#define NCHK(op)           \
    do {                   \
        if ((op) == NULL)  \
            alert(1, #op); \
    } while (0)

#define TCHK(op)                \
    do {                        \
        if ((errno = (op)) > 0) \
            alert(1, #op);      \
    } while (0)

noreturn void alert(int syserr, const char *msg, ...) {
    va_list ap;

    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);

    if (syserr == 1)
        perror("");

    exit(EXIT_FAILURE);
}