//
//  main.c
//  SocketServerDemo
//
//  Created by 广东省深圳市 on 2017/4/21.
//  Copyright © 2017年 Ace. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include "uxerror.h"

#define TCPPort 1234 //TCP端口号

int main(int argc, const char * argv[]) {
   
    //listenfd connfd用于本地监听连接状态
    int listenfd, connfd;
    
    //服务端和连接的客户端ipv4地址
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
    
    //地址字节长度
    unsigned int addressLen;
    addressLen = sizeof(clientaddr);
    
    //创建buff
    char buff[MAXLINE];
    
    //用于获取本地时间
    time_t ticks;
    
    //创建监听socket AF_INET:IPv4 网络协议的套接字类型
    //SOCK_STREAM表示使用TCP协议连接
    if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        err_sys("socket create error");
        return 0;
    }
   
    //初始化地址
    bzero(&servaddr, sizeof(servaddr));
    
    //AF_INET: IPv4 网络协议的套接字类型
    servaddr.sin_family = AF_INET;
    
    //INADDR_ANY表示对客户端IP地址不做限制
    //htonl函数将一个32位数从主机字节顺序转换成网络字节顺序
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //设置监听端口号 htons函数:主机字节顺序转变成网络字节顺序
    servaddr.sin_port = htons(TCPPort);
    
    //将socket与主机地址与端口号绑定
    if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1) {
        err_sys("socket bind error");
        return 0;
    }
    
    //设置服务器的缓冲区队列以接收客户端的连接请求 这里缓冲区队列设置为1024
    listen(listenfd, 1024);
    

    while (1) {
        //接受客户端连接请求并将客户端的网络地址信息保存到clientaddr
        //TCP连接在客户端被服务端接受后，连接建立，即可以通信
        if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &addressLen))==-1){
            err_sys("accepet error\n");
            return 0;
        }
        
        //输出已经连接客户端IP和端口号
        printf("connect successful!\n");
        printf("the client ip is %s,port is %d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
        

        //生成本地时间字符串
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n",ctime(&ticks));
    
        //向客户端发送本地时间
        write(connfd, buff, strlen(buff));
        
        //断开本次TCP连接
        close(connfd);
    }
    return 0;

}
