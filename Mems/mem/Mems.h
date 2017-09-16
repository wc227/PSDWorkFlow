// ***************************************************************
//  Mems   version:  1.0    date: 04/28/2007
//  -------------------------------------------------------------
//  Author: Song Dunwen  宋墩文(China)
//  Function: 
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// Log:
//201103031  修改使之适应PSD通讯要求
//2007-4-28  
// +  添加根据关键字查找指定节内容
// ***************************************************************

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MEMS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MEMS_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//no  use library
// winspool.lib  comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
#ifndef MEMS_H
#define MEMS_H
//////////////////////////////////////////////////////////////////////////
//共享内存操作
#ifndef __cplusplus
extern "C"
{
  #endif

  //////////////////////////////////////////////////////////////////////////
  #define  MAX_PROCESS_COUNT           30     //可以管理的进程数，多个进程，可以观察到系统运行的进程数量(PSDEdit要最少达到30个)
  #define  MAX_WINDOWS_COUNT           10    //窗口间通信消息用

  //	#define  MAX_CFG_LEN                 1090   //线性配置长度定义，其内容有具体业务定义
  //	#define  MAX_CFG_LEN                 (5*1024)   //线性配置长度定义，其内容有具体业务定义      //201108019 扩展2K，当PSD用时，需要建立1K左右的内存狗

  //	#define  MAX_SECTIONCFG_LEN          (64*1024)
  #define  MAX_SECTIONCFG_LEN          (3*1024)   //按节方式存放的数据
	//	#define  MAX_SECTIONCFG_LEN          (5*1024)   //按节方式存放的数据      

  #define  MAX_APP_COUNT               20  //支持最大业务数量
//20110402 对于需要应用共享内存的应用而言，必须在应用之前调用ShareMemoryBuild
  //	MEMS_API long ShareMemoryBuild(const char* pchName=NULL);
 MEMS_API long ShareMemoryBuild();

//20110402 一般不用调用ShareMemoryRelease()，进程退出时，动态链接库会自动释放自己
//         开辟的共享内存库，如果还有进程使用共享数据区，将不释放共享内存内容，尤其
//         在应用共享内存控制进程执行时,更是不用调用ShareMemoryRelease(..),否则将导
//         致程序一般性保护错误。
  MEMS_API void ShareMemoryRelease();

  //////////////////////////////////////////////////////////////////////////
  //应用共享数据管理
  //////////////////////////////////////////////////////////////////////////
  //common test interface
  MEMS_API int Test();
  MEMS_API int DllDump(char* pData, int nLen);

  #ifndef __cplusplus
}
#endif

#endif
