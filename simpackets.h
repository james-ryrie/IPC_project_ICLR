
#include <cstdint>

struct __attribute__((packed)) simOutPacket {
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

struct __attribute__((packed)) simInPacket{
        uint16_t version;
        double dt;
        uint64_t frame;
        double actuators[32];
};
