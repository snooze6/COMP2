//
// Created by arman on 30/10/2016.
//

#include "logger.h"

void log(const char* format, ... ) {
    va_list args;
    va_start( args, format );
    printf(format, args);
    va_end( args );
}
