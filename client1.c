#include <stdio.h>
#include <errno.h>
#include <string.h>

#define PATHFILE "/root/projects/ETC/data.txt"
int main()
{
    char code[100] = {0x00}; //data input from user
    FILE *fp = NULL;         //pointer to wite file
    int sizeData = 0;

    while (1)
    {
        printf("Please enter code data:");
        gets(code);
        fp = fopen(PATHFILE, "w");
        if (fp == NULL)
        {
            printf("open file error:%d \n", errno);
        }
        sizeData = fwrite(code, 1, strlen(code), fp);
        int g = strlen(code);
        if (sizeData < strlen(code))
        {
            printf("write file error: %d \n", errno);
            fclose(fp);
            break;
        }
        fclose(fp);
    }

    return 0;
}
