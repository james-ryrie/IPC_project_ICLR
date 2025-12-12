#include "udp_p2p.hpp"
#include <stdio.h>

void send_data_packet(int open_socket_fd, struct ITL_to_simulator_data_packet* data_packet) {
        send(open_socket_fd, data_packet, sizeof(*data_packet), 0);
}
void await_data_packet(int open_socket_fd) {
        struct simulator_to_ITL_data_packet recieve_buffer;
        /* This operation waits untill some information is recieved in the socket */
        recv(open_socket_fd, &recieve_buffer, sizeof(recieve_buffer), 0);
        printf("%d\n",recieve_buffer.magic_code);
}


int main() {
        int open_socket_fd = open_socket(9001);
        if(open_socket_fd < 0) return -1;

        int suc = establish_connection(open_socket_fd, 9000);
        if(suc < 0){
                close(open_socket_fd);
                return -1;
        }

        struct ITL_to_simulator_data_packet dp;
        dp.magic_code = MAGIC;
        send_data_packet(open_socket_fd, &dp);
        close(open_socket_fd);
}

        
