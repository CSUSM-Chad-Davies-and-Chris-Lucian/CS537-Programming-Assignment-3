// Names: Chris Lucian && Chad Davies
// Class: CS 537
// Date: 4/28/2015
// Assignment: 3

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>

using namespace std;

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

// this program automates the testing of the two applications with a single
// argument of a port
int main(int argc, char *argv[]) {
    string port1;
    port1 = argv[1];

    run_tests_with_test_mode(port1, "CheckSum");
    printf("\n\n\n");
    sleep(1);
    //run_tests_with_test_mode(port1, "TimeOut");
    //printf("\n\n\n");
    //sleep(1);
    //run_tests_with_test_mode(port1, "None");
    //printf("\n\n\n");
    //sleep(1);
    return 0;
}
