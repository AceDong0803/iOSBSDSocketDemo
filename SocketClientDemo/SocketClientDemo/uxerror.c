

//
//  uxerror.c
//  unix头文件
//
//  Created by 广东省深圳市 on 2017/4/14.
//  Copyright © 2017年 Ace. All rights reserved.
//

#include "uxerror.h"
#include <stdarg.h>
#include <syslog.h>
#include <sys/errno.h>
#include <stdio.h>



int daemon_proc = 1;

static void err_doit(int,int,const char *,va_list);

void err_ret(const char *fmt,...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}


void err_sys(const char *fmt,...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}


void err_dump(const char *fmt,...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    abort();
    exit(1);
}


void err_msg(const char *fmt,...){
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(0, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}


void err_quit(const char *fmt,...){
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    return;
}


static void err_doit(int errnoflag, int level, const char *fmt,va_list ap){
    int errno_save,n;
    char buf[MAXLINE +1];
    errno_save = errno;
    
#ifdef HAVE_VSNPRINTF
    vsnprintf(buf,MAXLINE,fmt,ap);
#else
    vsprintf(buf, fmt, ap);
#endif
    
    n = (int)strlen(buf);
    if (errnoflag) {
        snprintf(buf + n, MAXLINE - n, ":%s",strerror(errno_save));
    }
    strcat(buf, "\n");
    
    if (daemon_proc) {
        syslog(level, "%s", buf);
    }else{
        fflush(stdout);
        fputc(buf, stderr);
        fflush(stderr);
    }
    
}
