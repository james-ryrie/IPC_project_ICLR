#include "udp_p2p.hpp"
#include <string.h>
#include <stdio.h>

int open_socket(int port) {

        sockaddr_in server_address;
        memset(&server_address, 0, sizeof(server_address));

        int open_socket_fd = socket(AF_INET,SOCK_DGRAM,0);
        if(open_socket_fd<0) return -1;

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        /* We accept only addresses making requests from 127.0.0.1 which is localhost */
        inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

        int err_code = bind(open_socket_fd, (sockaddr *) &server_address, sizeof(server_address));
        if (err_code < 0) return -1;
       
        return open_socket_fd;
}

int establish_connection(int open_socket_fd, int client_port) {


        sockaddr_in client_address{};
        client_address.sin_family = AF_INET;
        client_address.sin_port = htons(client_port);
        inet_pton(AF_INET, "127.0.0.1", &client_address.sin_addr);

        int suc = connect(open_socket_fd, (sockaddr *) &client_address, sizeof(client_address)); 
        if(suc < 0) {
                close(open_socket_fd);
                return 1;
        }


        return 0;
}
void send_message(int open_socket_fd, const char * message) {
        send(open_socket_fd, message, strlen(message), 0);
}
void await_message(int open_socket_fd) {
        char recieve_buffer[1024];
        /* This operation waits untill some information is recieved in the socket */
        ssize_t message_length = recv(open_socket_fd, &recieve_buffer, sizeof(recieve_buffer), 0);
        recieve_buffer[message_length] = 0;
        printf("%s\n",recieve_buffer);
}

