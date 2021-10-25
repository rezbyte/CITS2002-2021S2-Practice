#include <stdlib.h>
#include <stdio.h>

void insertionSort(int* inArray, int length) 
{
    int i, j, key;
    for (i = 1; i < length; i++)
    {
        key = inArray[i];
        for (j = i-1; j >= 0 && inArray[j] > key; j--)
        {
           inArray[j+1] = inArray[j];
        }
        inArray[j+1] = key;
    }
}

// Returning a pointer is a bad idea; This resulted in the array being popped off the stack when it is accessed
// int* copyArray (char const** inArray, int size)
// {
//     int buffer[size];
//     for (int i = 0; i < size; i++)
//     {
//         buffer[i] = atoi(inArray[i+1]);
//     }
//     int* output = buffer; // Using a pointer results in being deallocated, when it is popped from the stack
//     return output;
// }

// Passing by pointer avoids the result being deallocated
// An alternative is to make buffer[] static and return it
void copyArray (int destination[],char const** inArray, int size)
{
    for (int i = 0; i < size; i++)
    {
        destination[i] = atoi(inArray[i+1]); 
    }
}

void printArray (char* inText,int* inArray, int size)
{
    printf("%s",inText);
    for (int i = 0; i < size; i++)
    {
        printf("%i ",inArray[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    if (argc < 2) 
    {
        printf("Too few arguments!\n");
        return EXIT_FAILURE;
    }

    int inArray[argc-1];
    copyArray(inArray,argv,argc-1);
    // int* inArray = copyArray(argv,argc-1);
    printArray("Unsorted: ",inArray,argc-1); // This call pops the array off the execution stack (When using old copyArray with pointer return)

    // inArray = copyArray(argv,argc-1); // Need to remake the array
    insertionSort(inArray,argc-1);
    printArray("Sorted: ",inArray,argc-1);
    
    return EXIT_SUCCESS;
}
