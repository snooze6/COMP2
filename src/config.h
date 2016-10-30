//
// Created by Snooze on 24/10/2016.
//

#ifndef P1_COMP_CONFIG_H
#define P1_COMP_CONFIG_H

#include "external/model/hash.h"
#include "helpers/logger.h"
#include <stdbool.h>

#define ETAG "[+] -"
#define VTAG "[-] -"
#define WTAG "[*] -"


#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

hashtable_t *hashtable;
extern char * onechar[];
extern int sizeonechar;
extern char * operators[];
extern int sizeoperators;
extern bool config_verbose;
extern int config_errors;

#endif //P1_COMP_CONFIG_H
