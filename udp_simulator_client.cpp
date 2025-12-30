#include "udp_p2p.hpp"
#include <stdio.h>
#include <stdlib.h>




void send_data_packet(struct simOutPacket * simoutpacket, int open_socket_fd) {


        send(open_socket_fd, simoutpacket, sizeof(*simoutpacket), 0);
}

void await_data_packet(struct simInPacket * siminpacket, int open_socket_fd) {
        /* This operation waits untill some information is recieved in the socket */


        printf("Awaiting response:\n");
        recv(open_socket_fd, siminpacket, sizeof(*siminpacket), 0);
        printf("%x\n",siminpacket->version);
        printf("above should be 0x0010\n");
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

        //Sends a dummy response for test purposes
        simOutPacket * outbound_packet= new simOutPacket();
        outbound_packet->version = VERSION;
        send_data_packet(outbound_packet, open_socket_fd);

        struct simInPacket * inbound_packet = (struct simInPacket *) calloc(1, sizeof(struct simInPacket));
        await_data_packet(inbound_packet, open_socket_fd);
        printf("Second packet recieved\n");

        while (1) {
                printf("Awaiting data packet:\n");
                await_data_packet(inbound_packet, open_socket_fd);
                send_data_packet(outbound_packet, open_socket_fd);
        }


        free(inbound_packet);
        
        close(open_socket_fd);
}
