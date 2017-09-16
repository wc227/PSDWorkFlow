#ifndef __SDWMEMSINC_H_20061216
#define __SDWMEMSINC_H_20061216
//2007-3-3
//	 添加编译变量控制

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//201103027  增加输入输出控制标记符号

#ifdef _SDWMEMS_
#define MEMS_API __declspec(dllexport)
#else
#define MEMS_API __declspec(dllimport)
#endif

#pragma  pack(1)
#include "Mems.h" //must place in the first position
#include "AutoSaveFile.h"       //201106013  新的自动存盘控制

#if !defined(SDWMEMS_EXCLUDE_PROCESS)
#include "processInc.h"
#endif

#if !defined(SDWMEMS_EXCLUDE_LOG)
#include "logInc.h"
#endif

#if !defined(SDWMEMS_EXCLUDE_HWND)
#include "hwndInc.h"
#endif

#if !defined(SDWMEMS_EXCLUDE_CFG)
#include "cfgInc.h"
#endif

#if !defined(SDWMEMS_EXCLUDE_SECTION)
#include "sectionInc.h"
#endif

#if !defined(SDWMEMS_EXCLUDE_PSD)
#include "psdABInc.h"
#endif

#if !defined(SDWMEMS_EXCLUDE_EVENT)      //2011012017 增加事件管理内容
#include "psdEvtInc.h"
#endif

#pragma  pack()


//*
#if defined _AFXDLL && !defined _SDWMEM_STATIC_
	//------------------------------------------
	// MFC shared DLL
	//------------------------------------------
	#ifdef _DEBUG
			#pragma comment(lib,"MemsD.lib") 
			#pragma message("Automatically linking with MemsD.dll")
	#else
			#pragma comment(lib,"Mems.lib") 
			#pragma message("Automatically _AFXDLL linking with Mems.dll") 
	#endif
#elif defined _SDWMEM_STATIC_
	//---------------------------------------------
	// MFC shared DLL
	//---------------------------------------------
	#ifdef _DEBUG
			#pragma comment(lib,"MemsD.lib") 
			#pragma message("Automatically linking with MemsD.lib") 
	#else
			#pragma comment(lib,"Mems.lib") 
			#pragma message("Automatically _STATIC_ linking with Mems.lib") 
	#endif
#else
	//--------------------------------------------------
	// MFC static library,
	//--------------------------------------------------
	#ifdef _DEBUG
			#pragma comment(lib,"MemsD.lib") 
			#pragma message("Automatically linking with MemsD.lib") 
	#else
			#pragma comment(lib,"Mems.lib") 
			#pragma message("Automatically static linking with Mems.lib") 
	#endif
#endif 
//*/
#endif
