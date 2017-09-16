#ifndef  PROCESSINC_INCLUDE_BYSDW   
#define  PROCESSINC_INCLUDE_BYSDW   20070306
#include <time.h>

//#ifdef _SDWMEMS_
//#define MEMS_API __declspec(dllexport)
//#else
//#define MEMS_API __declspec(dllimport)
//#endif

#ifndef __cplusplus
extern "C" {
#endif
 
//////////////////////////////////////////////////////////////////////////
//进程内容管理

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define  SFLAG_HIDE 	     0x1

#define  SFLAG_CONSOLE	   0x10
#define  SFLAG_WINEXE 	   0x20
#define  SFLAG_CONSOLETOW  0x40
#define  SFLAG_MULTICONSOLETOW  0x80

#define  SFLAG_WRITEPIPE	 0x100
#define  SFLAG_READPIPE 	 0x200

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#ifndef PROCESS_STRUCTURE
#define PROCESS_STRUCTURE    20061206

#define  PS_NOMEANING        0  //space
#define  PS_STOP        1  //stop
#define  PS_HANG        2  
#define  PS_RUNNING     3

#define  PSINDEX_HPID           0   

#define  PSINDEX_FILENAME       1 
#define  PSINDEX_COMMANDLINE    2
#define  PSINDEX_INIDIR         3
#define  PSINDEX_COMMENT        4
#define  PSINDEX_PRIORITY       5
#define  PSINDEX_MEMORYNO       6
#define  PSINDEX_STATUS         7
#define  PSINDEX_FLAG           8
#define  PSINDEX_TAG            9           //2006-7-30  PMU 's tag

#define  PSINDEX_CMDLEN                 (2*MAX_PATH)
#define  PSINDEX_FILENAMELEN            (MAX_PATH)
#define  PSINDEX_INIDIRLEN              (MAX_PATH)
#define  PSINDEX_COMMENTLEN             (MAX_PATH)
#define  PSINDEX_TAGLEN                 (100)     //2006-7-30

typedef struct tagProcess
{
  char    chFileName[PSINDEX_FILENAMELEN];

  char    chCommandLine[PSINDEX_CMDLEN];
  char    chIniDir[PSINDEX_INIDIRLEN];
  char    chComment[PSINDEX_COMMENTLEN];
  char    chTag[PSINDEX_TAGLEN];     //2006-7-30

  int     nFlag;
  int     nPriority;
  int     nHPid;
  int     nShareMemoryNo;
  int     nStatus;
  time_t  tmAccess;
} PROCESS,far* PPROCESS;
#endif

//////////////////////////////////////////////////////////////////////////
//得到指定索引位置上的进程信息
//pProcess  进程信息返回内容指针
//nIndex    内存中进程项的索引
//返回 :  <=0  无效
//          >0 有效的进程信息
MEMS_API  int  GetProcessInfo(PPROCESS pProcess,int nIndex); 

//////////////////////////////////////////////////////////////////////////
//更新进程信息项内容，如果进程信息没有在内存中登记，就建立新的登记项直到能
//管理的最大进程项内容
//pProcess  进程信息返回内容指针
//返回 :  >0  更新成功
//          <=0 无效更新
MEMS_API  int  UpdateProcessInfo(PPROCESS pProcess,int nCond=0);

//////////////////////////////////////////////////////////////////////////
//删除指定进程编号为nHPid的进程信息,清除nHPid的值内容
//nHPid  :  手动进程编号
//return : >0   发现了进程信息，并清除掉
//         <=0  没有发现进程信息
MEMS_API  int  ClearProcessInfo(int nHPid);

//////////////////////////////////////////////////////////////////////////
//得到内存中进程项内容
//返回 :  在内存中存放的进程项内容
MEMS_API  int  GetProcessCount();     //get the count of process

//////////////////////////////////////////////////////////////////////////
//发现指定编号的进程是否在内存中
//nHPid 进程手工编号
//返回 :  <0  无效
//        >=0 有效的进程索引位置
MEMS_API  int  FindProcessItem(int nHPid);

//////////////////////////////////////////////////////////////////////////
//启动指定编号的进程
//nHPid 进程手工编号
//返回 :  <=0  启动失败
//        >0 启动成功
MEMS_API  int  StartProcess(int nHPid,int nFlag = 0,const char* lpParam = NULL,char* pchLog=NULL);

//////////////////////////////////////////////////////////////////////////
//指定编号的进程是否在运行
//nHPid 进程手工编号
//返回 :  <=0  不存在或没有启动
//        >0 在 运行中
MEMS_API  int  IsProcessActive(int nHPid,int* pnStatus=NULL);

//////////////////////////////////////////////////////////////////////////
//停止指定编号的进程
//nHPid 进程手工编号
//返回 :  <=0  停止失败
//        >0 启动成功
MEMS_API  int  StopProcess(int nHPid);


#ifndef __cplusplus
}
#endif

#endif