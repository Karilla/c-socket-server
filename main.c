#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>>

int main()
{
    int listener; 
    int connfd;
    char sendBuff[1025];  
    int clientCounter = 0;
    printf("Server started...\n");

    struct sockaddr_in serv_address;

    listener = socket(AF_INET,SOCK_STREAM,0);

    printf("Socket Created...\n");

    memset(&serv_address,'0',sizeof(serv_address));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_address.sin_port = htons(5000);

    bind(listener,(struct sockaddr_in*)&serv_address,sizeof(serv_address));

    printf("Server Ready...\n");

    if(listen(listener, 10) == -1)
    {
      printf("Failed to listen\n");
      return -1;
    }      

    printf("Server listening on %d\n",serv_address.sin_addr.s_addr);

    while(1)
    {      
        clientCounter++;
        connfd = accept(listener, (struct sockaddr*)NULL ,NULL); // accept awaiting request
        snprintf(sendBuff, 1025, "Client number %d\n", clientCounter); // puts string into buffer

        strcpy(sendBuff, sendBuff);
        write(connfd, sendBuff, strlen(sendBuff));
    
    
        close(connfd);    
        sleep(1);
    } 

    return 0;
}