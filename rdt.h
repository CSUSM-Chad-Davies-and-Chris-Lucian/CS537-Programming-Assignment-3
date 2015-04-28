// Names: Chris Lucian && Chad Davies
// Class: CS 537
// Date: 4/28/2015
// Assignment: 3

// Guard against linking errors.
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <unistd.h>

// Size of the data inside a packet.
const int PACKET_DATA_SIZE = 500;
// Size of a packet.
const int PACKET_SIZE = 512;

// Common struct used to define a packet.
struct packet {
  uint16_t cksum; /* Ack and Data */
  uint16_t len; /* Ack and Data */
  uint32_t ackno; /* Ack and Data */
  uint32_t seqno; /* Data only */
  char data[PACKET_DATA_SIZE]; /* Data only; Not always 500 bytes, can be less */
};
typedef struct packet packet_t;

//The rdt_socket() function is used to create an end point for communications.
int rdt_socket(int address_family, int type, int protocol);

//The rdt_bind() function is used to associate a local address with a socket
int rdt_bind(int socket_descriptor,const struct sockaddr *local_address,socklen_t address_length);

//The rdt_recv() function is used to receive data through an unconnected socket.
int rdt_recv(int socket_descriptor,char *buffer, int buffer_length, int flags, struct sockaddr *from_address, int *address_length);

//The rdt_send() function is used to send data through a connected or unconnected socket
int rdt_sendto(int socket_descriptor,char *buffer,int buffer_length,int flags,struct sockaddr *destination_address,int address_length);

//The rdt_close() function closes a descriptor, fildes
int rdt_close(int fildes);
#ifdef __cplusplus
}
#endif
