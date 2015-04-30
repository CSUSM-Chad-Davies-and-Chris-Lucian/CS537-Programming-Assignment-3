// Names: Chris Lucian && Chad Davies
// Class: CS 537
// Date: 4/28/2015
// Assignment: 3

#include <stdio.h>
#include <string.h>
#include "rdt.h"
#include <string>
#include <iostream>
#include <fstream>
#include "test_data.h"

using namespace std;

// A simple test server meant to receive a file from the client.
int main(int argc, char *argv[]) {

    string message_string = get_message_string();

    // Test buffer lengths.
    int bufferLength = 1050;
    // int bufferLength = 36;
    // Server and client addresses.
    struct sockaddr_in serverAddress, clientAddress;
    int sizeClientAddress = sizeof(clientAddress);
    char buffer[bufferLength];

    // Validate the correct number of arguments have been passed to the server
    if (argc < 3) {
        fprintf(stderr,"Usage: %s <port> <test_mode>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    char* test_mode = argv[2];
    printf("SERVER test_mode: \e[93m%s\e[0m\n", test_mode);

    // Initialize server socket information.
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    // Create the RDT socket.
    printf("SERVER beforesocket\n");
    int socketDescriptor = rdt_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Bind to the RDT socket to receive data from the client.
    printf("SERVER beforebindsocket\n");
    rdt_bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(clientAddress));

    // Receive data of buffer length from the client using RDT.
    printf("SERVER beforerecieve\n");
    rdt_recv(socketDescriptor, buffer, bufferLength, 0, (struct sockaddr *) &clientAddress, &sizeClientAddress);
    //printf("SERVER Recieved %s\n" , buffer );

    string result_message_string(buffer);
    if(message_string.compare(result_message_string) == 0)
    {
        printf("SERVER \e[92mCompare Successful!\e[0m\n");
    }
    else
    {
        printf("SERVER \e[91mCompare NOT Successful!\e[0m\n");
    }

    printf("SERVER afterrecieve\n");

    // Close the RDT socket.
    rdt_close(socketDescriptor);
    return 0;
}
