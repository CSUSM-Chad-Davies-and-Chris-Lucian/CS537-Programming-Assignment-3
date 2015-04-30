// Names: Chris Lucian && Chad Davies
// Class: CS 537
// Date: 4/28/2015
// Assignment: 3

#include "rdt.h"
#include <errno.h>

bool test_mode;

void enable_test_mode()
{
   test_mode = true;
}

// Create udp socket for rdt connection
int rdt_socket(int address_family, int type, int protocol)
{
  int socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socketDescriptor == -1)
    {
        printf("RDT Socket Could not be created.\n");
    }
  return socketDescriptor;
}

// Bind UDP socket for RDT connection.
int rdt_bind(int socket_descriptor,const struct sockaddr *local_address,socklen_t address_length)
{
  int bindSuccess = bind(socket_descriptor , local_address, address_length);
  if(bindSuccess == -1)
    {
        printf("RDT Socket could not be bound.\n");
    }
  return bindSuccess;
}

// Get number of packets for a buffer length.
int get_num_packets(int buffer_length)
{
  printf("Get Packets Buffer Length %d\n", buffer_length);

  int num_packets = buffer_length / PACKET_DATA_SIZE;
  if(buffer_length % PACKET_DATA_SIZE != 0)
  {
    num_packets++;
  }
  printf("RDT Num Packets %d\n", num_packets);
  return num_packets;
}

// User UDP to receive a buffer and insert it into packets.
packet* recv_buffer_to_packets(int num_packets, int socket_descriptor,char *buffer, int buffer_length, int flags, struct sockaddr *from_address, int *address_length)
{
  //Create array of packets
  packet* packets = new packet[num_packets];

  //Load data into packets
  for(int i = 0; i < num_packets; i++)
  {
    // Use UDP to populate the buffer.
    char local_buffer[PACKET_SIZE];
    int recieveLength = recvfrom(socket_descriptor, &local_buffer, PACKET_SIZE, flags, from_address, (socklen_t*)address_length);
    printf("RDT Received Length %d\n",recieveLength);

    if (recieveLength == -1)
    {
      printf("RDT Received Failed.\n");
      return 0;
    }

    // Convert buffer into packet struct.
    memcpy(&packets[i], local_buffer, PACKET_SIZE);

     //printf("RDT Received Packed Data %s\n\n\n", packets[i].data);

  }

  return packets;

}

// Copy packets into a buffer.
void copy_packets_to_buffer(packet* packets, char* buffer, int num_packets, int buffer_length)
{
  //transfer the packet data into the buffer
  for(int i = 0; i < num_packets; i++)
  {
    for(int d = 0; d < PACKET_DATA_SIZE; d++)
    {
      int data_index = i * PACKET_DATA_SIZE + d;
      if(data_index < buffer_length)
      {
        buffer[data_index] = packets[i].data[d];
      }
    }
  }

  // Null terminate end of message.
  buffer[buffer_length] = '\0';
    //printf("RDT Received Message %s\n\n\n", buffer);
}

// Calls all the functions needed to receive packets over RDT.
int rdt_recv(int socket_descriptor,char *buffer, int buffer_length, int flags, struct sockaddr *from_address, int *address_length)
{
    //Get number of packets to receive
    int num_packets = get_num_packets(buffer_length);

    // Receive packets.
    packet* packets = recv_buffer_to_packets(num_packets, socket_descriptor, buffer, buffer_length, flags, from_address, address_length);

    // Check for error.
    if (packets == 0)
    {
      return -1;
    }

    // Get buffer contents from packets.
    copy_packets_to_buffer(packets, buffer, num_packets, buffer_length);

  return buffer_length;
}

// Copy buffer contents into packets.
packet* copy_buffer_to_packets(int num_packets, char *buffer, int buffer_length)
{
  //Create array of packets to send
  packet* packets = new packet[num_packets];

  //Fill packet array with data
  for(int i = 0; i < num_packets; i++)
  {
    for(int d = 0; d < PACKET_DATA_SIZE; d++)
    {
      int data_index = i * PACKET_DATA_SIZE + d;
      if(data_index < buffer_length)
      {
        packets[i].data[d] = buffer[data_index];
      }
      else
      {
        packets[i].data[d] = '\0';
      }
    }
  }
  return packets;
}

// User UDP to send packets across the network.
void send_packets(int socket_descriptor,char *buffer,int buffer_length,int flags,struct sockaddr * destination_address,int address_length, int num_packets, packet* packets)
{
  //Send packets
  for(int i = 0; i < num_packets; i++)
  {
    int errno;
    int sendToSuccess = sendto(socket_descriptor, &packets[i], PACKET_SIZE, flags, destination_address, address_length);
    if (sendToSuccess == -1)
    {
        printf("RDT Couldn't be sent.\n");
    }
  }
}

// Calls all the functions to send a buffer across RDT.
int rdt_sendto(int socket_descriptor,char *buffer,int buffer_length,int flags,struct sockaddr * destination_address,int address_length)
{
  //Get Number of packets to send
  int num_packets = get_num_packets(buffer_length);

  // Copy the buffer contents into packets.
  packet* packets = copy_buffer_to_packets(num_packets, buffer, buffer_length);

  // Send the packets.
  send_packets(socket_descriptor, buffer, buffer_length, flags, destination_address, address_length, num_packets, packets);

  return buffer_length;
}

// Close the RDT connection.
int rdt_close(int fildes)
{
  printf("RDT close\n");
  return close(fildes);
}
