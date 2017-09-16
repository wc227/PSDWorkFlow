//2012010015
// 利用实时数据库缓冲多个记录数据，实现多个进程间批量数据的访问
// 对于WAMS应用，必须要包括PSDStructs.h
#if !defined(___PSDDB_PSDSTRUCTS_INCLUDES_H__)
#define ___PSDDB_PSDSTRUCTS_INCLUDES_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////
//通信命令定义，与结构体有关PSDCOMBLOCK
//For WAMS
#define  COM_WAMS_CMD       21      //命令帧，可以查询配置帧或数据帧
#define  COM_WAMS_CFG       22      //配置帧
#define  COM_WAMS_DATA      23      //数据帧
#define  COM_WAMS_STATUS    24      //状态帧
#define  COM_WAMS_INFO      25      //信息帧

//For WAMS  标志为定义
#define  SUPPORT_MULTILAYER_CONTROL   1     //支持多层控制

#define  EVT_WAMSAPP_DATAA_POS    200         //缓冲区A已写入记录个数
#define  EVT_WAMSAPP_DATAB_POS    201         //缓冲区B已写入记录个数
#define  EVT_WAMSAPP_READ_POS     202         //业务读指向的缓冲区，可能值为0,enumA=1，enumB=2,否则错误
#define  EVT_WAMSAPP_READOVER_POS     232     //业务读[完]指向的缓冲区，可能值为 0，>0 读完,为防止读写锁在一个段内，需要将读完标记远离计数器

#define  EVT_WAMSAPP_CFG_CHANGE_POS   217     //WAMS配置内容改变标识
#define  EVT_WAMSAPP_DATA_CHANGE_POS  218    //WAMS数据内容改变标识
#define  EVT_WAMSAPP_COM_RESET_POS    219      //通信复位并准备就绪

//数据表定义
//配置环境变量内容
#define  BDB_WAMS_ENV      "BWENV"

//当前配置表(只有一张表，只有一个记录)
#define  BDB_WAMS_CFG      "BWCFG"
//当前实时数据表 (只有一张表，存在多个记录,通过A/B缓冲循环)
#define  BDB_WAMS_DATA_A      "BWDATAA"
#define  BDB_WAMS_DATA_B      "BWDATAB"

//PMU实时数据表（存在多张表，表的数量按PMU数量建立,一个表有多个记录）
#define  BDB_WAMS_PMU    "BWPMU"

//取指定标号为x的表名称
#define  MPMU(x)     BWPMU##x

//命令帧结构
typedef struct tagCmdFrame
{
 WORD   Sync;  //同步字 AA40
 DWORD  FrameSize;//报文字节长度，16位无符号整型数，从Sync到Chk字段全长
 DWORD  SOC;  //世界秒
 WORD   QueryType; //命令类型, 1 配置 2数据 3 状态
 WORD   Interval;  //定时回复时间间隔，毫秒单位（需要为断面间隔的整数倍）。为0时本字段无效
 WORD   Chk;  //校验字
} WAMSCMDFRAME, far* PWAMSCMDFRAME;

#define  COM_WAMSAPP_NO    6  //Wams通信应用缓冲区内容
#endif