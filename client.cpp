// Names: Chris Lucian && Chad Davies
// Class: CS 537
// Date: 4/28/2015
// Assignment: 3

#include <stdio.h>
#include <string.h>
#include "rdt.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>
#include "test_data.h"

using namespace std;

int main(int argc, char *argv[]) {

    struct sockaddr_in serverAddress;

    // Test files.
    // string message_string = "Hello Wolds I am here to be awesome.";
    string message_string = get_message_string();
    //Argument Validation
    if (argc < 4) {
       fprintf(stderr,"usage %s <hostname> <port> <test_mode>\n", argv[0]);
       exit(0);
    }

    //Assign the arguments to well-named variables
    string ipAddress = argv[1];
    int port = atoi(argv[2]);
    char* test_mode = argv[3];
    set_rdt_test_mode(test_mode);
    printf("CLIENT test_mode: \e[94m%s\e[0m\n", test_mode);


    // Setup server address.
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // Establish RDT socket.
    printf("CLIENT beforesocket\n");
    int socketDescriptor = rdt_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Get server address length.
    printf("CLIENT beforesend\n");
    int serverAddressLength = sizeof(serverAddress);

    // User RTD 1.0 to send the message.
    //printf("CLIENT Sending string length %d\n", strlen(message_string.c_str()));
    rdt_sendto(socketDescriptor, const_cast<char*>(message_string.c_str()), strlen(message_string.c_str()), 0,(struct sockaddr *) &serverAddress, serverAddressLength);
    printf("CLIENT sendto done\n");

    rdt_close(socketDescriptor);
    return 0;
}
