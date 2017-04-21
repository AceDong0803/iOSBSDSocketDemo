//
//  main.c
//  SocketClientDemo
//
//  Created by 广东省深圳市 on 2017/4/21.
//  Copyright © 2017年 Ace. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "uxerror.h"

#define TCPPort 1234  //TCP端口号

int main(int argc, const char * argv[]) {
    
    //sockfd用于本地监听连接状态  n接受数据监听
    int sockfd,n;
    
    //创建接收buf
    char recvline[MAXLINE + 1];
    
    //服务端ipv4地址
    struct sockaddr_in servaddr;
    
    //创建socket AF_INET:IPv4 网络协议的套接字类型
    //SOCK_STREAM表示使用TCP协议连接
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        err_sys("socket error");
    }
    
    //初始化地址
    bzero(&servaddr, sizeof(servaddr));
    
    //AF_INET: IPv4 网络协议的套接字类型
    servaddr.sin_family = AF_INET;
    
    //设置连接服务器端口号:htons函数:主机字节顺序转变成网络字节顺序
    servaddr.sin_port = htons(TCPPort);
    
    //inet_pton 转化ipv4地址
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        err_quit("inet_pton error for %s","");
    }
    
    //客户端向特定网络地址的服务器发送连接请求，连接成功返回0，失败返回 -1
    //connect调用会阻塞当前线程，直到服务器返回
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0) {
        err_sys("connet error");
    }
    
    //接受服务端数据并输出
    while ((n = (int)read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs error");
        }
    }
    if (n < 0) {
        err_sys("read error");
    }
    return 0;
}
