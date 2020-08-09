#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/inotify.h>

#define PATHFILE "/root/projects/ETC/data.txt"

int main()
{
    void *addr = NULL;
    struct stat mmapstat = {0};
    int fp1, fp2 = 0;
    fd_set readfds;
    int ret = -1;
    char data[100] = {0x00};

    while (1)
    {
        fp2 = open(PATHFILE, O_RDONLY | O_CREAT);
        if (fp2 == -1)
        {
            printf("open file error:%d \n", errno);
            break;
        }
        if (stat(PATHFILE, &mmapstat) == -1)
        {
            printf("don't exist file: %d \n", errno);
        }
        else if (mmapstat.st_size != 0)
        {
            addr = mmap(NULL, 20, PROT_READ, MAP_PRIVATE, fp2, 0);
            if (addr == MAP_FAILED)
            {
                printf("mmap error: %d \n", errno);
                break;
            }
            memcpy(data, addr, mmapstat.st_size);
            printf("data from client1: %s \n", data);
        }

        fp1 = inotify_init();
        int g = inotify_add_watch(fp1, PATHFILE, IN_MODIFY);
        if (g == -1)
        {
            int h = errno;
            printf("watch error:%s \n", errno);
        }
        FD_ZERO(&readfds);
        FD_SET(fp1, &readfds);
        printf("Wait data from client1! \n");
        ret = select(fp1 + 1, &readfds, NULL, NULL, NULL);
        if (ret == -1)
        {
            printf("select error:%d \n", errno);
            break;
        }
        //seek();
        //char h;
        //read(fp2, h, 1);
        stat(PATHFILE, &mmapstat);
        //if (addr == NULL)
        //{
            addr = mmap(NULL, 20, PROT_READ, MAP_PRIVATE, fp2, 0);
            if (addr == MAP_FAILED)
            {
                printf("mmap error: %d \n", errno);
                break;
            }
            memcpy(data, addr, mmapstat.st_size);
            printf("data from client1: %s \n", data);
        //}
        
        //memcpy(data, addr, mmapstat.st_size);
        //printf("data from client1: %s \n", data);
        munmap(addr, mmapstat.st_size);
        close(fp2);
    }

    return 0;
}
