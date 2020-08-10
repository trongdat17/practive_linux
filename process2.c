#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
using namespace std;
// int main() {
//     printf("Process children %d has created \n", getpid());
//     return 0;
// }
int main(int argc, char const *argv[])
{
    int input = atoi(argv[0]);
    string para1 = string(argv[1]);
    string para2 = string(argv[2]);
    printf("%d \n",argc);
    printf("child:%d \n",input);
    printf("%s \n",para1.c_str());
    printf("%s \n",para2.c_str());
    return 0;
}
