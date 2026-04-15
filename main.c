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
    int ch, i;

    fp1 = fopen("input.bmp", "rb");
    fp2 = fopen("output.bmp", "wb");

    if(fp1 == NULL || fp2 == NULL)
    {
        printf("File error\n");
        return;
    }

    char msg[100], pass[20];

    printf("Enter password: ");
    scanf("%s", pass);

    printf("Enter message: ");
    scanf(" %[^\n]", msg);

    // copy header
    for(i = 0; i < 54; i++)
    {
        ch = fgetc(fp1);
        fputc(ch, fp2);
    }

    // encode message
    char c;
    int j = 0;

    while(msg[j] != '\0')
    {
        char m = msg[j];

        for(i = 7; i >= 0; i--)
        {
            c = fgetc(fp1);

            c = c & 254;

            if((m >> i) & 1)
                c = c | 1;

            fputc(c, fp2);
        }

        j++;
    }

    // encode end character
    char m = '\0';

    for(i = 7; i >= 0; i--)
    {
        c = fgetc(fp1);

        c = c & 254;

        if((m >> i) & 1)
            c = c | 1;

        fputc(c, fp2);
    }

    printf("Message encoded successfully\n");

    // copy rest of image
    while((ch = fgetc(fp1)) != EOF)
    {
        fputc(ch, fp2);
    }

    fclose(fp1);
    fclose(fp2);
}

void decode()
{
    FILE *fp;
    int ch, i;
    char c;

    fp = fopen("output.bmp", "rb");

    if(fp == NULL)
    {
        printf("File error\n");
        return;
    }

    // skip header
    for(i = 0; i < 54; i++)
    {
        fgetc(fp);
    }

    printf("Decoded message: ");

    while(1)
    {
        c = 0;

        for(i = 7; i >= 0; i--)
        {
            ch = fgetc(fp);

            if(ch & 1)
                c = c | (1 << i);
        }

        if(c == '\0')
            break;

        printf("%c", c);
    }

    printf("\n");

    fclose(fp);
}