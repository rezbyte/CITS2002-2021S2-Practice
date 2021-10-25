#include <stdio.h>
#include <string.h>

void encrypt(char* inString) {
    for (int charIndex = 0; charIndex < strlen(inString); charIndex++) {
        inString[charIndex] += 3;
    }
}

void decrypt(char* inString) {
    for (int charIndex = 0; charIndex < strlen(inString); charIndex++) {
        inString[charIndex] -= 3;
    }
}

int main(int argc, char* argv[]) {
    // Ensure there are two arguments
    if (argc < 3) {
        printf("Too few arguments!\n");
        return 1;
    }
    if (argc > 3) {
        printf("Too many arguments!\n");
        return 1; 
    }

    // Parse command
    if (strcmp(argv[1],"encrypt") == 0) {
        encrypt(argv[2]);
    } else if (strcmp(argv[1],"decrypt") == 0) {
        decrypt(argv[2]);
    } else {
        printf("Unknown command: %s\n", argv[1]);
        return 1;
    }
    
    printf("%s\n",argv[2]);
    return 0;
}