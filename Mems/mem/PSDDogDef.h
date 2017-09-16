#ifndef  _DOGDEFINE_H_BYSONGDW_20110819
#define _DOGDEFINE_H_BYSONGDW_20110819

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
//以下结构用于管理数据节信息内容
typedef struct tagDogDataSec
{
 unsigned char    Type; //保存数据节意义,例如用户数据类型、功能类型、时间数据类型（）
 unsigned char    Res;  //备用字捉
 unsigned short   Size; //本数据节块数多少
} DOGDATASEC, far* PDOGDATASEC;

#define  DOGDATASEC_SIZE       sizeof(DOGDATASEC)

#define  DAT_TYPE_USER        1  //描述用户信息的节类型编号
#define  DAT_TYPE_MODULE      2  //描述模块配置的节类型编号
#define  DAT_TYPE_TIME        3  //描述时间信息的节类型编号
#define  DAT_TYPE_EXEINFO     4  //密件中的Exe信息内容
#define  DAT_TYPE_DOGUPDATETIME  5  //狗最新写入的时间内容

//////////////////////////////////////////////////////////////////////////
//以下信息用于管理用户信息内容
#define   USER_LEN   20
typedef struct  tagDogUser
{
 char           ID[USER_LEN / 2];    //用户ID信息
 char           Name[USER_LEN*2];  //用户名称
 char           UserCode[3];       //用户代码
 unsigned char  Class;             //用户类型(0 外部使用，1 平行计算使用，2 内部使用)
 // char   Alias[USER_LEN];        //用户别名
 // char   Class[USER_LEN];        //用户类型
 unsigned char  DogType;         //用户使用狗的类型
}DOGUSER, far* PDOGUSER;

#define   DOGUSER_SIZE   sizeof(DOGUSER)   //整个狗用户大小

#define    USER_CLASS_NULL         0    //缺省用户类型

//////////////////////////////////////////////////////////////////////////
//以下信息用于管理模块及功能信息
typedef struct  tagDogModule
{
 unsigned short   ModuleNumber;  //模块编号
 unsigned char    Function;      //功能号
 // char             Key[USER_LEN / 2];  //模块关键字
 unsigned short   Flag;           //Bit 0 - 1:Enable /0:disable
 unsigned long    WarrantTime;    //授权时间
 unsigned short   Days;           //有效天数
 // unsigned long    ValidTerm;      //有效期限
}DOGMODULE, far* PDOGMODULE;

#define   DOGMODULE_SIZE   sizeof(DOGMODULE)   //整个结构体大小

//////////////////////////////////////////////////////////////////////////
//以下文件管理时间信息
typedef struct tagDogTimeLimit
{
 unsigned long    WarrantTime;   //网络狗授权时间
 unsigned long    LastDownTime;  //最新当机时间
 unsigned short   ValidDays;     //有效天数
}DOGTIMELIMIT, far* PDOGTIMELIMIT;

#define  DOGTIMELIMIT_SIZE  sizeof(DOGTIMELIMIT)  //结构块大小

//////////////////////////////////////////////////////////////////////////
//以下为密件管理文件
typedef struct  tagExeInfo
{
 unsigned short   CodeNumber;               //执行代码编号
 char             PureFileName[USER_LEN*4];  //模块关键字
 char             Suffix[USER_LEN];          //后缀体名称
 unsigned long    IsseTime;                  //记录发布时间内容
 unsigned long    Flag;                      //Bit 0 - 1:Enable /0:disable
 unsigned long    FreeTimeTerm;              //免费升级的期限
}EXEINFO, far* PEXEINFO;

#define   EXEINFO_SIZE   sizeof(EXEINFO)   //整个结构体大小

//////////////////////////////////////////////////////////////////////////
//狗数据更新时间内容
typedef struct tagDogUpdateTime
{
 unsigned long    LastTime;          //最近一次更新时间
 unsigned short   Flag;              //数据标记，目前备用
 unsigned short   NetUserLimit;      //最多支持用户数 2012-07-23 WeiShiQuan add
  unsigned long  datumTime;		       //基准时间，用于验证狗的有效期。2012-08-07 add
} DOGUPDATETIME, * PDOGUPDATETIME;

#define  DOGUPDATETIME_SIZE   sizeof(DOGUPDATETIME)


//////////////////////////////////////////////////////////////////////////
//提取值内容
#define  DOGSIZE(Size,Type) \
 if(Type==DAT_TYPE_USER) Size=sizeof(DOGUSER);  \
 else if(Type==DAT_TYPE_MODULE) Size=sizeof(DOGMODULE);  \
 else if(Type==DAT_TYPE_TIME) Size=sizeof(DOGTIMELIMIT);  \
 else if(Type==DAT_TYPE_EXEINFO) Size=sizeof(EXEINFO);   \
 else if(Type==DAT_TYPE_DOGUPDATETIME) Size=sizeof(DOGUPDATETIME); 

#endif
