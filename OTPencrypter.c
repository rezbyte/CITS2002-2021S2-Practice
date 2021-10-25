#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

/* Usage
$ ./OTPencrypter encrypt text.txt key.otp
$ ./OTPencrypter decrypt text.txt key.otp
$ ./OTPencrypter generate 500 key.otp

    Details:
    .otp is a binary format containing (pseudo) randomly generated offsets
    The standard block size is an 8-bit unsigned integer
*/

#define BLOCKTYPE uint8_t

int getLength(FILE* inFP)
{
    int currentPosition = ftell(inFP);
    fseek(inFP, 0L, SEEK_END);
    int size = ftell(inFP);
    fseek(inFP, 0L, currentPosition);
    return size;
}

int getLengthFromName(const char* inFileName)
{
    FILE* fp;
    fp = fopen(inFileName,"rb");
    int size = getLength(fp);
    fclose(fp);
    return size;
}

void randomizeArray (BLOCKTYPE inArray[], int inLength)
{
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < inLength; i++)
    {
        inArray[i] = (BLOCKTYPE) rand();
    }
}

void makeOTPFile(const char inFileName[],int inLength)
{
    BLOCKTYPE randomNumbers[inLength];

    FILE* fp;
    fp = fopen(inFileName,"wb");
    if (fp == NULL)
    {
        perror("generate");
    }
    
    randomizeArray(randomNumbers,inLength);

    fwrite(randomNumbers,inLength,sizeof(BLOCKTYPE),fp);
    fclose(fp);
}

void loadOTP(BLOCKTYPE destinationArray[], const char inOTPName[])
{
    FILE* fp;
    fp = fopen(inOTPName,"rb");
    if (fp == NULL)
    {
        perror("Failed to load key");
    }

    fread(destinationArray,sizeof(BLOCKTYPE),getLength(fp),fp);
    
    fclose(fp);
}

void encryptFile(const char inFileName[], const char inOTPName[])
{
    BLOCKTYPE key[getLengthFromName(inOTPName)];
    loadOTP(key,inOTPName);

    FILE* fp;
    fp = fopen(inFileName,"r+");
    if (fp == NULL)
    {
        perror("encrypt");
    }

    int size = getLength(fp);
    char buffer[size];
    fread(buffer, sizeof(BLOCKTYPE), size, fp);
    rewind(fp);

    for (int i = 0; i < size; i++)
    {
        buffer[i] = buffer[i] + key[i];
    }
    fwrite(buffer,sizeof(BLOCKTYPE),size,fp);
    fclose(fp);
}

void decryptFile(const char inFileName[], const char inOTPName[])
{
    BLOCKTYPE key[getLengthFromName(inOTPName)];
    loadOTP(key,inOTPName);

    FILE* fp;
    fp = fopen(inFileName,"r+");
    if (fp == NULL)
    {
        perror("encrypt");
    }

    int size = getLength(fp);
    char buffer[size];
    fread(buffer, sizeof(BLOCKTYPE), size, fp);
    rewind(fp);

    for (int i = 0; i < size; i++)
    {
        buffer[i] = buffer[i] - key[i];
    }
    
    fwrite(buffer,sizeof(BLOCKTYPE),size,fp);
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        printf("Too few arguments!\n");
        exit(EXIT_FAILURE);
    } else if (argc > 4)
    {
        printf("Too many arguments!\n");
        exit(EXIT_FAILURE);
    }
    
    switch (argv[1][0]) // We can tell the command from only the first letters: e, d & g
    {
        case 'e':
            encryptFile(argv[2],argv[3]);
            break;
        case 'd':
            decryptFile(argv[2],argv[3]);
            break;
        case 'g':
            if (atoi(argv[2]) <= 0)
            {
                printf("Invalid size!\n");
                exit(EXIT_FAILURE);
            }
            makeOTPFile(argv[3],atoi(argv[2]));
            break;
        default:
            printf("Unrecognised command!\n");
            exit(EXIT_FAILURE);
            break;
    }
    
    return EXIT_SUCCESS;
}
