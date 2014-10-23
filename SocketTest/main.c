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


/*
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
        printf("I have received:\n%s\n", buffer);
        close(sockfd);   
        exit(0);


}
*/
/*
int main(int argc, char *argv[])
{
    int client_sockfd;
    int len;
    struct sockaddr_in remote_addr; //服务器端网络地址结构体
    char buf[BUFSIZ];  //数据传送的缓冲区
    memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零
    remote_addr.sin_family=AF_INET; //设置为IP通信
    remote_addr.sin_addr.s_addr=inet_addr("180.97.33.108");//服务器IP地址
    remote_addr.sin_port=htons(80); //服务器端口号
    
    
    if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        return 1;
    }
    
    
    if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
    {
        perror("connect");
        return 1;
    }
    printf("connected to server\n");
    len=recv(client_sockfd,buf,BUFSIZ,0);//接收服务器端信息
    buf[len]='\0';
    printf("%s",buf); //打印服务器端信息
    
    
    while(1)
    {
        printf("Enter string to send:");
        scanf("%s",buf);
        if(!strcmp(buf,"quit"))
           break;
           len=send(client_sockfd,buf,strlen(buf),0);
           len=recv(client_sockfd,buf,BUFSIZ,0);
           buf[len]='\0';
           printf("received:%s\n",buf);
           }
           close(client_sockfd);//关闭套接字
           return 0;
           }


*/


//
//  main.m
//  server
//
//  Created by mac on 13-4-15.
//  Copyright (c) 2013年 mac. All rights reserved.
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
int CreateClinetSocket()
{
    int ClinetSocket = 0;
    ClinetSocket = socket(AF_INET, SOCK_STREAM, 0);
    return ClinetSocket;
}
int ConnectionToServer(int client_socket,const char * server_ip,unsigned short port)
{
    struct sockaddr_in sAddr={0};
    sAddr.sin_len=sizeof(sAddr);
    sAddr.sin_family=AF_INET;
    inet_aton(server_ip, &sAddr.sin_addr);
    sAddr.sin_port=htons(port);
    if (connect(client_socket, (struct sockaddr *)&sAddr, sizeof(sAddr))==0) {
        return client_socket;
    }
    return 0;
}
//client
void Message(int socket)
{
    char send_Message[1024]="0";
    char recv_Message[1024]={0};
    while (1) {
        recv(socket, recv_Message, sizeof(recv_Message), 0);
        printf("<-----%s",recv_Message);
        printf("----->");
        fgets(send_Message, sizeof(send_Message), stdin);
        send(socket,send_Message,strlen(send_Message)+1,0);
    }
}
int main(int argc, const char * argv[])
{
    const char * server_ip="127.0.0.1";
    short server_port=9897;
    if (argc>1) {
        server_ip = argv[1];
    }
    if (argc>2) {
        server_port=(short)atoi(argv[2]);
    }
    
    int client_socket= CreateClinetSocket();
    if (ConnectionToServer(client_socket,server_ip, server_port)==0) {
        printf("Connect to server error\n");
        return 0;
    }
    printf("Connect to server ok\n");
    Message(client_socket);
    
    return 0;
}
