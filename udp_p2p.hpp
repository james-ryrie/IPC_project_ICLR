#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#define VERSION 0x0010
#define PORT 10550

struct __attribute__((packed)) simulator_to_ITL_data_packet {
        uint16_t version;
        double timestamp;
        uint64_t frame;
        double gyroscope[3];
        double accelerometer[3];
        double barometer;
        double gps_pos[3];
        double gps_vel[3];
        double gps_pdop;
        double pressures[8];
        double temperatures[8];
        double battery;
};

struct __attribute__((packed)) ITL_to_simulator_data_packet {
        uint16_t version;
        double dt;
        uint64_t frame;
        double actuators[32];
};

int open_socket(int port);

int establish_connection(int open_socket_fd, int client_port);

