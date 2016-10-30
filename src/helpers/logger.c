#include "logger.h"

/**
 * Printf reimplementation to work as a logger
 * @param format
 */
void log(const char* format, ... ) {
    va_list args;
    va_start( args, format );
    printf(format, args);
    va_end( args );
}
