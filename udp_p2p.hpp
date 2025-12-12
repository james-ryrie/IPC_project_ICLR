#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAGIC 0x4h23
#define PORT 10550

struct data_packet {
        int magic_code;
        void * data_blob;
};



int open_socket(int port);

int establish_connection(int open_socket_fd, int client_port);

void send_message(int open_socket_fd, const char * message);

void await_message(int open_socket_fd);
