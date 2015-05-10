// Names: Chris Lucian && Chad Davies
// Class: CS 537
// Date: 4/28/2015
// Assignment: 3

#include "test_data.h"

//Get the message string accessable anywhere in the code
std::string get_message_string()
{
  static std::string word("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi hendrerit erat a nunc facilisis varius. Sed lectus mi, egestas eget auctor eu, elementum eget justo. Mauris lacinia viverra mi, at pretium ante iaculis bibendum. Interdum et malesuada fames ac ante ipsum primis in faucibus. Vestibulum condimentum lobortis justo id varius. Mauris quis mi lorem. Interdum et malesuada fames ac ante ipsum primis in faucibus. Vivamus sed sagittis diam. Aenean elementum elementum massa at sagittis. Suspendisse euismod magna ut pulvinar tempor. Morbi ultricies enim eros, non feugiat neque sollicitudin sed. Mauris nec viverra neque.Nulla facilisi. Quisque pharetra pellentesque tristique. Phasellus et lectus ac lacus elementum lacinia ac ut nisi. Vivamus ornare purus vulputate, aliquam risus nec, facilisis metus. Donec eu elit et diam dignissim placerat euismod a lorem. Nullam sed neque consectetur, tristique tellus ac, molestie ex. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur semper hendrerit ligula, nec convallis est nullam.");
  return word;
}

//Get the checksum test mode
std::string get_checksum_testmode()
{
  static std::string word("CheckSum");
  return word;
}

//Get the time out test mdoe
std::string get_timeout_testmode()
{
  static std::string word("TimeOut");
  return word;
}

//Get the None value test mode
std::string get_none_testmode()
{
  static std::string word("None");
  return word;
}
