#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SRV_PORT 1080
#define SA struct sockaddr

void sneaky(void);
void regular(void);
int read_tcp(int s_sockfd, char * b);

void sneaky(void){
     printf("sneaky() function called. Code flow successfully changed.\n");
}

void regular(void){
  printf("regular() function called\n");
}


int read_tcp(int s_sockfd, char * b){
    return read(s_sockfd, b, 26);
}

static void (*fp)(void);
static char buffer[10];

int serversocket(void){
  int server_sockfd,connfd;
  unsigned int len;
  struct sockaddr_in servaddr,cli;

  // socket create and verification
  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sockfd == -1) {
        printf("socket creation failed...\n");
        return -1;
  }
  else{
     printf("Server Socket created..\n");
  }
  bzero((char *)&servaddr, sizeof(servaddr));

  // assign IP and port
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SRV_PORT);

  // Binding newly created socket to given IP and verification
  if ((bind(server_sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
      printf("socket bind failed...\n");
      return -1;
  }
  else{
      printf("Socket successfully bound..\n");
  }
  // Now server is ready to listen
  if ((listen(server_sockfd, 5)) != 0) {
     printf("Listen failed...\n");
     return -1;
  }
  else{
     printf("Server listening..\n");
  }
  len = sizeof(cli);
  // Accept the data packet from client
  connfd = accept(server_sockfd, (SA*)&cli, &len);
  if (connfd < 0) {
     printf("server acccept failed...\n");
     return -1;
  }
  else{
     printf("server acccept the client...\n");
  }

  fp = sneaky;

  printf("sneaky function addr: %p\n",fp);

  fp = regular;

  printf("regular function addr: %p\n",fp);

  while(1){
     len = read_tcp(connfd,buffer);
     if(len == 0){
        break;
     }

     if(fp){
        printf("calling function pointer at address : %p\n",fp);
        fp();
        printf("function addr: %p\n",fp);
     }
     else{
        printf("function pointer is set to NULL \n");
     }
  }
  close(server_sockfd);
  close(connfd);
  printf("Exiting ...\n");
  return 0;
}
