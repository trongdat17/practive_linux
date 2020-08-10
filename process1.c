#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;
#define PATHFILE "/root/projects/ETC/process2"
#define FILE1 "LogCollector"
#define FILE2 "CCU"
int main()
{
    char szExecFile[200] = "";
    int iPid = -1;
    int iRet = -1;
    sprintf(szExecFile, "%s", PATHFILE);
    iPid = fork();
    if (iPid == -1) // Error
    {
        printf("Create chill process error \n");
    }
    else if (iPid == 0) // Child Process
    {
        // Child Process
        //const char *args[] = "bui trong dat";
        int g = 1060;

        char data[100] ;
        string sspace = " ";
        string sFile1 = FILE1;
        string sFile2 = FILE2;
        memset(data,0x00,100);
        sprintf(data,"%d",g);
        const char *argument1 = "arg1";
        const char *argument2 = "arg2";
        //sprintf(data,"%d%s%s%s%s", g, sspace.c_str(), sFile1.c_str(), sspace.c_str(), sFile2.c_str());
        printf("%s \n",data);
        iRet = execl(szExecFile,
                     data,
                     sFile1.c_str(),
                     sFile2.c_str(),
                     NULL);

        // If the above system call returns, it means something wrong happens
    }
    else // Current Process
    {
        printf("parent process has created chil process:%d \n", iPid);
    }
    return 0;
}