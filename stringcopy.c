#include <string.h>
#include <stdio.h>

/*  Get the last index of a null terminated string 
    Parameters: inString
    Returns: an integer with the last index */
int getLengthOfString(char* inString) {
    int length = 0;
    while (inString[length] != '\0')
    {
        length++;
    }
    return length;
}

/*  Duplicates a string
    Parameters: inString
    Returns: the base address of a clone of inString */
char* copyString(char* inString) {
    int length = getLengthOfString(inString);
    char buffer[length];
    for (int i = 0; i < length; i++)
    {
        buffer[i] = inString[i];
    }
    char* newString = buffer;
    return newString;
}

int main(int argc, char const *argv[])
{
    char* oldString = "Hello";
    printf("Value of oldString: %s\n",oldString);
    
    char* newString;
    newString = copyString(oldString);
    printf("Value of newString: %s\n", newString);

    return 0;
}
