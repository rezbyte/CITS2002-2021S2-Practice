#include <stdio.h>

int Ackermann(int m, int n)
{
    if (m)
    {
        if (n)
        {
            return Ackermann(m-1, Ackermann(m,n-1));
        } else {
            return Ackermann(m-1,1);
        }
    }
    return n+1;
}

int main(int argc, char const *argv[])
{
    printf("Ackermann(3,2) is %i\n",Ackermann(3,2));
    return 0;
}
