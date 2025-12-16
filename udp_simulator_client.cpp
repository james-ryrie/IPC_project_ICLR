#include "udp_p2p.hpp"
#include <stdio.h>
#include <stdlib.h>

void send_data_packet(int open_socket_fd) {
        struct simulator_to_ITL_data_packet data_packet = {};
        data_packet.version = VERSION;
        printf("%x\n",data_packet.version);
        send(open_socket_fd, &data_packet, sizeof(data_packet), 0);
}
void await_data_packet(int open_socket_fd) {
        struct ITL_to_simulator_data_packet * recieve_buffer = (struct ITL_to_simulator_data_packet *) malloc (sizeof(struct ITL_to_simulator_data_packet));
        /* This operation waits untill some information is recieved in the socket */
        recv(open_socket_fd, recieve_buffer, sizeof(*recieve_buffer), 0);
        printf("%x\n",recieve_buffer->version);
        printf("above should be 0x0010\n");
        free(recieve_buffer);
}

void await_debug_data_packet(int open_socket_fd) {
        char buffer[1024];
        int n = recv(open_socket_fd, &buffer, sizeof(buffer), 0);
        buffer[n] = 0;
        printf(buffer); 
        printf("\n");
}
        

int main(){
        int open_socket_fd = open_socket(10550);
        if(open_socket_fd < 0) return -1;

        int suc = establish_connection(open_socket_fd, 10551);
        if(suc < 0){
                close(open_socket_fd);
                return -1;
        }

        //await_data_packet(open_socket_fd);
        await_debug_data_packet(open_socket_fd);
        printf("First packet recieved\n");

        //Sends a dummy response for test purposes
        printf("Sending response!\n");
        send_data_packet(open_socket_fd);
        printf("Sent data packet to adapter\n");

        await_data_packet(open_socket_fd);
        printf("Second packet recieved\n");
        
        close(open_socket_fd);
}
