
/****************************************************************************
 *
 *   Copyright (C) 2015 Mark Charlebois. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file attack_example.cpp
 * Example for Linux
 *
 * @author Anton Hristozov
 */

#include "attack_example.h"
#include <px4_platform_common/time.h>
#include <unistd.h>
#include <stdio.h>
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
  while(1){
     printf("sneaky() function called.Code flow successfully changed.\n");
     sleep(1);
  }
}

void regular(void){
  printf("regular() function called\n");
}


int read_tcp(int s_sockfd, char * b){
    return read(s_sockfd, b, 26);
}


 typedef void (*myfunc)(void);

int serversocket(void){
  myfunc fp;
  char buffer[10];


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
     printf("Read %d bytes from socket\n",len);
     if(len == 0){
        break;
     }

     for(unsigned int i=0;i<len;i++){
        printf("0x%02X ",buffer[i]);
     }
     printf("\n");
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
  return 0;
}

px4::AppState AttackExample::appState;


int AttackExample::main()
{
	appState.setRunning(true);

	while (!appState.exitRequested()) {
      serversocket();
      AttackExample::appState.requestExit();
      break;
	}

	return 0;
}
