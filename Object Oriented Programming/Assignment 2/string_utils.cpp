#include "string_utils.h"

int calculateLen(char *arr)
{
    int c = 0;
    while (arr[c] != '\0')
        c++;

    return c;
}

void copyString(char *destination, int destAllocSize, char *source)
// we have to know the amount of allocated memory here, else the program throws
{
    if (destAllocSize <= 0)
    {
        return; // maybe an error?
    }

    int sourceLen = calculateLen(source);
    destination[destAllocSize - 1] = '\0';
    for (int i = 0; i < destAllocSize - 1; ++i)
        destination[i] = source[i];
}