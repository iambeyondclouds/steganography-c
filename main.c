#include <stdio.h>

void encode();
void decode();

int main()
{
    int ch;

    printf("\nSteganography Program\n");
    printf("1. Encode\n");
    printf("2. Decode\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);

    if(ch == 1)
    {
        printf("You selected Encode option\n");
        encode();
    }
    else if(ch == 2)
    {
        printf("You selected Decode option\n");
        decode();
    }
    else
    {
        printf("Wrong choice entered\n");
    }

    return 0;
}

    void encode()
{
    FILE *fp;

    fp = fopen("input.bmp", "rb");

    if(fp == NULL)
    {
        printf("File not found\n");
    }
    else
    {
        printf("File found successfully\n");
    }
}


void decode()
{
    printf("Decoding part will be added soon...\n");
}

