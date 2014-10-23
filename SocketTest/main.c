//
//  main.c
//  SocketTest
//
//  Created by laukevin on 14-10-23.
//  Copyright (c) 2014年 laukevin. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argci, const char * argvi[]) {
    // insert code here...
    //printf("Hello, World!\n");
    //return 0;

        int sockfd;
        char buffer[1024];
        struct sockaddr_in server_addr;
        int portnumber, nbytes;
        if (inet_aton("180.97.33.108", &server_addr.sin_addr) == 0) {
            fprintf(stderr, "the hostip is not right!");
            exit(1);
        }
        portnumber = atoi("80");
        // 创建套接字
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            fprintf(stderr, "Socket Error:%s\n\a", strerror(errno));
            exit(1);
        }
        // 填充服务器的地址信息
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(portnumber);
        // 向服务器发起连接
        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            fprintf(stderr, "Connect Error:%s\n\a", strerror(errno));
            exit(1);
        }
    char p[]="GET / HTTP/1.1\r\n\r\n";
    int c;
    send(sockfd,p,strlen(p),0);
        // 连接成功后，从服务器接收信息
        if ((nbytes = read(sockfd, buffer, 1024)) == -1) {
            fprintf(stderr, "Read Error:%s\n", strerror(errno));
            exit(1);
        }   
        buffer[nbytes] = '\0';   
        printf("I have received:%s\n", buffer);   
        close(sockfd);   
        exit(0);


}
