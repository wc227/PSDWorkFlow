#ifndef _GRAND_DOG_DEF_H
#define _GRAND_DOG_DEF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//  #include "include/MemsInc.h"

#include <vector>
#include <string>
using namespace std;

//用户使用狗的类型
#define   LOCAL_GROUNDDOG     0   //本地狗
#define   TIMELIMIT_GROUNDDOG   1   //时限狗
#define   MEMORY_GROUNDDOG    2   //内存狗

//用户使用狗的范围
#define   DOG_USAGE_OUT     0   //外部使用
#define   DOG_USAGE_PARCAL    1   //并行计算使用
#define   DOG_USAGE_INTERNAL    2   //内部使用

//验证返回值
#define   UNKNOWN_ERROR     -1    //未知的错误
#define   VALIDATE_SUCCEED    0   //验证成功
#define   NOT_FIND_SOFTDOG    1   //未找到软件狗
#define   MODULE_NOT_WARRANT    1   //软件的使用没有得到授权
#define   SOFTDOG_TYPE_ERROR    1   //用户使用的狗的类型错误
#define   Read_DOGINFO_ERROE    2   //读软件狗信息错误
#define   VALIDATE_FAILED     3   //验证失败
#define   MODIFY_LOCAL_DATE   4   //用户修改了本机时间
#define   VALIDATE_USERID_FALIED  5   //验证用户信息失败


#define   USER_NAEM_LENTH   9
#define   FILE_REQUEST_LENTH  DOGMODULE_SIZE*80+DOGDATASEC_SIZE
#define   FILE_TIME_AREA    DOGTIMELIMIT_SIZE+DOGDATASEC_SIZE
#define   FILE_USER_AREA    DOGUSER_SIZE+DOGDATASEC_SIZE

#define   FILE_SECRET_FILE_LENTH  1024*5

typedef vector<DOGUSER> veDogUser; 
typedef vector<DOGUSER>::iterator veDogUserPos;
typedef vector<DOGMODULE> veDogModule; 
typedef vector<DOGMODULE>::iterator veDogModulePos;
typedef vector<DOGTIMELIMIT> veDogTimeLimit; 
typedef vector<DOGTIMELIMIT>::iterator veDogTimeLimitPos;
typedef vector<EXEINFO> veExeInfo; 
typedef vector<EXEINFO>::iterator veExeInfoPos;

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef HUINT
#define HUINT unsigned short
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef WORD
#define WORD unsigned short
#endif
#define MHSTATUS ULONG


#define INSTALL_ONLY_USB_DOG_DRVIER         1
#define INSTALL_ONLY_PARALLEL_DOG_DRVIER    2
#define INSTALL_ALL_DOG_DRVIER              3

#define UNINSTALL_ONLY_USB_DOG_DRVIER         1
#define UNINSTALL_ONLY_PARALLEL_DOG_DRVIER    2
#define UNINSTALL_ALL_DOG_DRVIER              3

typedef int (PASCAL *CHECKVERSION) (BOOL bShowMessageBox, int* piUsbVerStatus, int* piParVerStatus);
typedef int (PASCAL *INSTALL)(int iFlag);
typedef int (PASCAL *UNINSTALL)(int iFlag);

#endif // _GRAND_DOG_DEF_H

