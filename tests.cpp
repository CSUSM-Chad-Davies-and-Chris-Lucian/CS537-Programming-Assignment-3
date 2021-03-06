// Names: Chris Lucian && Chad Davies
// Class: CS 537
// Date: 4/28/2015
// Assignment: 3

#include <cstdlib>
#include <stdio.h>
#ifndef STRING_H
#define STRING_H
#include <string>
#endif
#include <unistd.h>
#include <iostream>
#include "rdt.h"
#include "test_data.h"

using namespace std;

//Runs the client and server with a given port and testmode
void run_tests_with_test_mode(string port1, string test_mode)
{
  // kill all clients and servers before executing a test
  system("echo \e[92mKilling Old Processes:\e[0m");
  system("ps | grep server | awk '{print $1}' | xargs kill");
  system("ps | grep client | awk '{print $1}' | xargs kill");

  printf("\n\n\n");

  // construct the server command and start the test
  printf("\nTESTS: Starting Server App\n");
  string command = "./server " + port1 + " " + test_mode + " &";
  system(command.c_str());

  // Create the client to send the server data.
  printf("\nTESTS: Starting Client App %d\n",index);
  string command2 = "./client localhost " + port1 + " " + test_mode + " &";
  system(command2.c_str());

  printf("\n\n\n");

}

//Tests the checksum to validate the value
void test_checksum(char* buffer, uint16_t expected)
{
  if(get_checksum(buffer) == expected)
  {
    printf("\e[92mChecksum Successful!\e[0m\n");
  }
  else
  {
    printf("\e[91mNot Checksum Successful!\e[0m\n");
  }
}

//Tests the checksum validator value
void test_checksum_is_valid(char* buffer, uint16_t cksum, bool expected)
{
  if(checksum_is_valid(buffer, cksum) == expected)
  {
    printf("\e[92mChecksum is Valid Successful!\e[0m\n");
  }
  else
  {
    printf("\e[91mNot Checksum is Not Valid Successful!\e[0m\n");
  }
}

// this program automates the testing of the two applications with a single
// argument of a port
int main(int argc, char *argv[]) {
    string port1;
    port1 = argv[1];

    //Test checksums
    test_checksum("pick", 65113);
    test_checksum("lol", 65209);

    //Test checksum validator
    test_checksum_is_valid("lol", 11245, false);
    test_checksum_is_valid("lol", 65209, true);

    printf("\n\n\n");

    //Test each test mode
    run_tests_with_test_mode(port1, get_none_testmode());
    printf("\n\n\n");
    sleep(1);
    run_tests_with_test_mode(port1, get_invalid_sequence_testmode());
    printf("\n\n\n");
    sleep(1);
    run_tests_with_test_mode(port1, get_checksum_testmode());
    printf("\n\n\n");
    sleep(1);
    run_tests_with_test_mode(port1, get_timeout_testmode());
    printf("\n\n\n");
    sleep(1);
    return 0;
}
