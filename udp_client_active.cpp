#include "udp_p2p.hpp"


int main() {
        int open_socket_fd = open_socket(9001);
        if(open_socket_fd < 0) return -1;

        int suc = establish_connection(open_socket_fd, 9000);
        if(suc < 0){
                close(open_socket_fd);
                return -1;
        }

        const char * message = "Hello other client!\n";
        send_message(open_socket_fd, message);
        close(open_socket_fd);
}

        
