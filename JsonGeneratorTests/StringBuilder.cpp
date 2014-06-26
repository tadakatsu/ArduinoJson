/*
 * Arduino JSON library
 * Benoit Blanchon 2014 - MIT License
 */

#include "StringBuilder.h"


void StringBuilder::append(const char* s)
{
    char* tail = buffer + length;

    strncpy(tail, s, capacity - length);

    length += strlen(tail);
}

void StringBuilder::appendEscaped(const char* s)
{
    if (length > capacity - 3) return;

    buffer[length++] = '"';

    // keep one slot for the end quote
    capacity--;

    while (*s && length<capacity)
    {
        switch (*s)
        {
        case '"':
            append("\\\"");
            break;

        case '\\':
            append("\\\\");
            break;


        default:
            buffer[length++] = *s;
            break;
        }

        s++;
    }

    buffer[length++] = '"';
    buffer[length] = 0;

    // restore the original capacity
    capacity++;
}

void StringBuilder::appendFormatted(const char* format, ...)
{
    char* tail = buffer + length;

    va_list args;
    va_start(args, format);
    vsnprintf(tail, capacity - length, format, args);
    va_end(args);

    length += strlen(tail);
}