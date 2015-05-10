// Names: Chris Lucian && Chad Davies
// Class: CS 537
// Date: 4/28/2015
// Assignment: 3

#ifndef STRING_H
#define STRING_H
#include <string>
#endif


#ifdef __cplusplus
extern "C" {
#endif

//Get the message string accessable anywhere in the code
std::string get_message_string();

//Get the checksum test mode
std::string get_checksum_testmode();

//Get the timeout test mode
std::string get_timeout_testmode();

//Get the none testmode
std::string get_none_testmode();


#ifdef __cplusplus
}
#endif
