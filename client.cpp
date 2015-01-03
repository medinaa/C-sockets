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


/* client program */


int main(int argc, char** argv)
{
    if (argc < 4) { printf("incorrect usage \n"); return 0; }
   
    char* host = strdup(argv[1]); //grab the host name
    int port = atoi(argv[2]); //grab the port number

    int sd;
    sd = socket(PF_INET, SOCK_STREAM, 0);  //create the scoket

    struct sockaddr_in addr;        
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &addr.sin_addr);
    connect(sd, (struct sockaddr *) &addr, sizeof(addr));

    
    char* stringtoSend = (char*) calloc(100, sizeof(char)); //grab the string to send
    int i;
    for (i = 0; i < strlen(argv[3]); i++)
    {
        stringtoSend[i] = argv[3][i];
    }
    stringtoSend[i++] = '\r';
    stringtoSend[i++] = '\n';
    stringtoSend[i] = '\0';
    printf("string to send -%s- \n", stringtoSend);
    write(sd, stringtoSend, strlen(stringtoSend));

    int n;
    char readBuff[1024];
    while((n = read(sd, readBuff, sizeof(readBuff)-1))>0)
    {
        //printf("readbuff is %s \n", readBuff);
    }
    printf("readbuff is %s \n", readBuff);
    return 0;
}
