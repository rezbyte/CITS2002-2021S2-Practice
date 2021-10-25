#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Usage
// $ texteditor text.txt
// The file text.txt is created and opened
// Each inputted line from stdin is added to the file
// Unless the the line is !q in which the program exits

#define BUFFERSIZE 500
void createFile(const char inFileName[])
{
    FILE* fp = fopen(inFileName,"w");
    if (fp == NULL)
    {
        perror("Text Editor");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFFERSIZE];
    bool isQuit = false;
    while (!isQuit)
    {
        fgets(buffer,BUFFERSIZE,stdin);
        if (buffer[0] != '!' && buffer[1] != 'q')
        {
           fputs(buffer,fp);
        } else
        {
           
           isQuit = true;
        }
    } 
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Too few arguments!\n");
        exit(EXIT_FAILURE);
    } else if (argc > 2)
    {
        printf("Too many arguments!\n");
        exit(EXIT_FAILURE);
    }

    createFile(argv[1]);
    
    return EXIT_SUCCESS;
}
