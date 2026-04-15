#include <stdio.h>
#include <string.h>

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

    // combine password + message
    char data[200];
    sprintf(data, "%s#%s", pass, msg);

    // copy header
    for(i = 0; i < 54; i++)
    {
        ch = fgetc(fp1);
        fputc(ch, fp2);
    }

    // encode data
    char c;
    int j = 0;

    while(data[j] != '\0')
    {
        char m = data[j];

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

    printf("Message encoded\n");

    // copy remaining image
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

    char entered_pass[20];

    printf("Enter password: ");
    scanf("%s", entered_pass);

    // skip header
    for(i = 0; i < 54; i++)
    {
        fgetc(fp);
    }

    char data[200];
    int k = 0;

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

        data[k++] = c;
    }

    data[k] = '\0';

    char *p = strtok(data, "#");
    char *m = strtok(NULL, "#");

    if(p != NULL && m != NULL && strcmp(p, entered_pass) == 0)
    {
        printf("Message: %s\n", m);
    }
    else
    {
        printf("Wrong password\n");
    }

    fclose(fp);
}