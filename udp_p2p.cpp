#include "udp_p2p.hpp"
#include <string.h>

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
