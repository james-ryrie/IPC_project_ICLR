Simple UDP p2p connection between a mock simulator and an adaptor that will be available as part of Ricardo-Backend-Apps
Included is also a dummy client file that can be used for testing with the simulator file.
the .hpp file contains definitions for the type packets that should be send and recieved from the simulator

To run the project:
make clean && make -j
./udp_simulator_client
then (if testing internally)
./udp_ITL_client
Where the output indicates a success
