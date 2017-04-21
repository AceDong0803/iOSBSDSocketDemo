//
//  uxerror.h
//  unix头文件
//
//  Created by 广东省深圳市 on 2017/4/14.
//  Copyright © 2017年 Ace. All rights reserved.
//

#ifndef uxerror_h
#define uxerror_h

#define MAXLINE 4096

void err_ret(const char *fmt,...);
void err_sys(const char *fmt,...);
void err_dump(const char *fmt,...);
void err_msg(const char *fmt,...);
void err_quit(const char *fmt,...);

#endif /* uxerror_h */
