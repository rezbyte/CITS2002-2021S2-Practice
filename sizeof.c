# include <stdio.h>

#define PRINTSIZE(x) printf("%lu\n", sizeof(x));

int main () {
    PRINTSIZE(int);
    PRINTSIZE(char);
    PRINTSIZE(float);
}