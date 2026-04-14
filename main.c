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
    FILE *fp1, *fp2;
    int ch;   // MUST be int
    int i;

    fp1 = fopen("input.bmp", "rb");
    fp2 = fopen("output.bmp", "wb");

    if(fp1 == NULL || fp2 == NULL)
    {
        printf("File error\n");
        return;
    }

    // copy header
    for(i = 0; i < 54; i++)
    {
        ch = fgetc(fp1);
        fputc(ch, fp2);
    }

    // copy remaining data
    while( (ch = fgetc(fp1)) != EOF )
    {
        fputc(ch, fp2);
    }

    printf("Image copied successfully\n");

    fclose(fp1);
    fclose(fp2);
}

void decode()
{
    printf("Decoding part will be added soon...\n");
}

