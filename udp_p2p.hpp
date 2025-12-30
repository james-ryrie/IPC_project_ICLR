#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include "simpackets.h"

#define VERSION 0x0010
#define PORT 10550

int open_socket(int port);

int establish_connection(int open_socket_fd, int client_port);

