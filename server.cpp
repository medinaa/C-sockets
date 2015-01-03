#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <set>
#include <string>
#include <arpa/inet.h>


int main(int argc, char** argv)
{
    int port = atoi(argv[1]);
    int sd;  //our master socket

    struct sockaddr_in addr;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    bind(sd, (struct sockaddr*) &addr, sizeof(addr));
    listen(sd, 5);

    while(1)
    {
        struct sockaddr_in client;
        int slavesocket; //goes inside the iterative server
        int alen = sizeof(client);
        slavesocket = accept(sd, (struct sockaddr*) &client, (socklen_t*) &alen);

        int n;
        unsigned char newChar = 'x';
        unsigned char lastChar = 'x';
        char curr_string[1024];
        int length = 0;

                
        while((n = read(slavesocket, &newChar, sizeof(newChar))))
        {
            if (newChar == '\n' && lastChar == '\r')
            {
                curr_string[length++] = newChar;
                curr_string[length] = '\0';
                printf("curr_string is %s \n", curr_string);
                write(slavesocket, curr_string, strlen(curr_string));
                break;
            }
            curr_string[length++] = newChar;
            lastChar = newChar;
        }
        close (slavesocket);
    }
    return 0;
}
