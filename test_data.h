#ifndef STRING_H
#define STRING_H
#include <string>
#endif


#ifdef __cplusplus
extern "C" {
#endif

std::string get_message_string();

std::string get_checksum_testmode();


std::string get_timeout_testmode();


std::string get_none_testmode();


#ifdef __cplusplus
}
#endif
