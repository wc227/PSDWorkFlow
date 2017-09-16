/********************************************************************
	created:	2011/04/25
	created:	25:4:2011   14:29
	filename: 	D:\Work\Project\Lib\ComEmbed\PSDFiles\PSDStructs.h
	file path:	D:\Work\Project\Lib\ComEmbed\PSDFiles
	file base:	PSDStructs
	file ext:	h
	author:		Song Dunwen
	
	purpose:	
    Log:  
//201106013 将通信帧上的宏，用编译变量来控制
//201104025 定义通讯配置结构内容
//201104025 当采用文件组进行传送时，考虑到有效性，目前只支持同一个目录下
//          多个文件的传送，命令的格式描述如下：
//           源目录\v目标机目录\v主传输文件名\v辅助文件名1\v辅助文件名2\v...
//          目标机目录可以为空，当为空时，由业务层设置缺省目录，然后添加
//          源机器IP地址构成，通讯层负责将通讯命令改造为完整的命令
*********************************************************************/

#if !defined(___PSDCE_PSDSTRUCTS_INCLUDES_H__)
#define ___PSDCE_PSDSTRUCTS_INCLUDES_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//////////////////////////////////////////////////////////////////////////
//根据PSD通讯协议定义内容
typedef  struct tagPSDCOMBLOCK
{
  unsigned char  Head;  //版本
  unsigned char  AppNo; //业务编号 Hi:4为源地址编号,Lo:4为目标地址编号
  unsigned char  ComCmd; //
  unsigned char  TaskCmd;     //201308031 为实现事件与固定命令的兼容（规定任务号80以下为内部执行体控制,80以后为事件号控制执行体内容）
                              //由事件代替固定内部编号命令，将更具有通用性
  
  unsigned long  Flag; //通讯属性
                       //B0-0主动(发起)/1被动(响应)
                       //B1-1:需要回答,0:不要回答
                       //B2-1:通讯完成
                       //B3-1:任务完成
                       //B4-1  转发命令状态
                       //B5-1  组播控制标记
                       //B6-1  本地代理执行命令标记
                       //B7-1   判断传输同名文件(文件全名称相同，字节数量相同，不同仍要覆盖)
                       //B8-1   对于恢复命令进行标识，表明本命令为恢复命令

                       //B12-B15 协同缓冲区     //201308026 如果该值在原始命令中存在，在进行命令配对时，要转发对应的命令到该缓冲区(0无效，1到7)
  unsigned long  SourceIP;     //命令发起IP地址b31-25.b24-16.b15-9.b8-0
  unsigned long  DestIP;       //命令目的IP地址b31-25.b24-16.b15-9.b8-0
  unsigned long  FrameTime;  //建立时刻-包序号

  unsigned short FrameNo;   //流水号
  unsigned short FrameLen;  //数据长度（包括整个数据区长度）
  unsigned short DataCRC16; //纯数据CRC
  unsigned char  ComCmdResult;       //通讯命令执行结果
  unsigned char  TaskCmdResult;      //任务执行结果
  unsigned long  LocalFrameTime;     //201108015  当前机器上帧获取时间
  unsigned long  SourceIPBak;        //201108023  当实现转发时，需要将上上级发出的内容进行缓冲
  unsigned char* pData;     //块数据内容
} PSDCOMBLOCK, far* PPSDCOMBLOCK;

//////////////////////////////////////////////////////////////////////////
//帧固定结构长度
#define  COM_FRAMEHEAD_SIZE     (sizeof(PSDCOMBLOCK)-sizeof(unsigned char*))
//201109016  读取时减少读取长度
#define  COM_FRAME_LENPOS       (4*sizeof(char)+4*sizeof(long)+sizeof(short))

//////////////////////////////////////////////////////////////////////////
//业务缓冲编号
#define  MSrcAppNo(cAppNo)      ((cAppNo>>4)&0xF)
#define  MDesAppNo(cAppNo)      ((cAppNo)&0xF)
#define  MMakeSrcDes(Src,Des)   (((Src)<<4)|((Des)&0xF))

#define  MExSrcDes(cAppNo)  \
 char s1 = MSrcAppNo(cAppNo);  \
 char d1 = MDesAppNo(cAppNo);  \
 cAppNo = MMakeSrcDes(d1,s1); 

//////////////////////////////////////////////////////////////////////////
//通讯命令
#define  COM_COM_COMMAND               1
#define  COM_COM_SHORTMESSAGE          2
//	#define  COM_COM_SINGLEFILE            3
#define  COM_COM_GROUPFILE             4
#define  COM_COM_PATH                  5

#define  COM_COM_ANSWER                6  //一个回答命令

#define  COM_COM_BROADCAST             7  //广播
#define  COM_COM_GROUPCAST             8  //组播

#define  COM_COM_LICENSECAST           9  //广播license
#define  COM_JOIN_GROUP                10 //加入组
#define  COM_DISMISS_GROUP             11 //解散组
#define  COM_DISMISS_ALL               12 //解散全部组      //20120103
#define  COM_COM_RESPONSE              13       //20120509  ????

#define  COM_COM_EVTGROUP                    14 //事件通信命令,事件之间用\v间隔     //2013012016
#define  COM_COM_EVTMSG                      15 //消息及事件混合值，中间用\v间隔  例如 evt\b1:2\vmsg\b短路电流计算事件
#define  COM_COM_PUREEVT                     16 //纯事件组内容

//	#define  COM_COM_MASK                        0x80   //20140108  增加通信任务掩码，当掩码存在时，命令只通过消息传送
//对通讯命令的提示
#ifndef EXCLUDE_COMMACRO
#define  MComCmd(strOut,ComPtr)  \
 switch(ComPtr->ComCmd)  \
 {  \
  case COM_COM_COMMAND:{ strOut+=":命令";}break;  \
  case COM_COM_SHORTMESSAGE:{ strOut+=":短消息";}break;  \
  case COM_COM_GROUPFILE:{ strOut+=":组文件";}break;  \
  case COM_COM_PATH:{ strOut+=":目录";}break;  \
  case COM_COM_ANSWER:{ strOut+=":应答";}break;  \
  case COM_JOIN_GROUP:{ strOut+=":建通信组";}break;  \
  case COM_DISMISS_GROUP:{ strOut+=":拆单通信组";}break;  \
  case COM_DISMISS_ALL:{ strOut+=":拆通信组";}break;  \
  case COM_COM_EVTGROUP:{ strOut+=":文件事件";}break;  \
  case COM_COM_EVTMSG:{ strOut+=":事件&消息";}break;  \
  case COM_COM_PUREEVT:{ strOut+=":纯事件";}break;  \
  default:  {  strOut+=":未定义";  }break   ;     \
 } 

#else
#define  MComCmd(strOut,ComPtr)  
#endif 

//通讯命令执行结果
#define  COM_RESULT_SUCCESS            1  //按设计完成
#define  COM_RESULT_WARNING            2  //有一定程度的告警，但完成了，例如重传等
#define  COM_RESULT_ERROR              3  //通讯不能正确执行

#ifndef EXCLUDE_COMMACRO
#define  MComCmdResult(strOut,ComPtr)  \
 switch(ComPtr->ComCmdResult)  \
 {  \
  case COM_RESULT_SUCCESS:{ strOut+=":通讯完成";}break;  \
  case COM_RESULT_WARNING:{ strOut+=":***通讯警告";}break;  \
  case COM_RESULT_ERROR:{ strOut+=":****通讯错误";}break;  \
  default:  \
  {  \
  }break   ;     \
 }  
#else
#define  MComCmdResult(strOut,ComPtr)  
#endif 

//////////////////////////////////////////////////////////////////////////
//任务或业务命令（每一种计算类型，预留5个命令号）
#define  COM_TASK_PFNT                 1  //潮流计
#define  COM_TASK_PFRESULT             2  //潮流结果分析

#define  COM_TASK_SWNT                 6  //稳定计
#define  COM_TASK_SWRESULT             7  //稳定结果分析


#define  COM_TASK_FDS                  10  //长过程计
#define  COM_TASK_FDSRESULT            11 //长过程结果分

#define  COM_TASK_SSAP                  15  //小扰动
#define  COM_TASK_SSAPRESULT            16 //小扰动分析


#define  COM_TASK_SCCP                  20  //短路电流
#define  COM_TASK_SCCPRESULT            21 //短路电流分析

#define  COM_TASK_BATSWNT               30  //综合执行暂态稳定批处理     //201107010
#define  COM_TASK_SWNTFLTONCE           31            //201205018  单一故障集的暂态稳定计算内容

#ifndef EXCLUDE_COMMACRO
//20140104  下面的命令为缺省的方式，实际上内部编号可以自定义类型

#define  MComTask(strOut,ComPtr)  \
 switch(ComPtr->TaskCmd)  \
 {  \
  case COM_TASK_PFNT:{ strOut+=":潮流计算";}break;  \
  case COM_TASK_SWNT:{ strOut+=":稳定计算";}break;  \
  case COM_TASK_PFRESULT:{ strOut+=":潮流结果";}break;  \
  case COM_TASK_SWRESULT:{ strOut+=":稳定结果";}break;  \
  case COM_TASK_FDS:{ strOut+=":全过程计算";}break;  \
  case COM_TASK_FDSRESULT:{ strOut+=":全过程结果";}break;  \
  case COM_TASK_SCCP:{ strOut+=":短路电流";}break;  \
  case COM_TASK_SCCPRESULT:{ strOut+=":短路电流结果";}break;  \
  case COM_TASK_BATSWNT:{ strOut+=":稳定批处理";}break;  \
  case COM_TASK_SWNTFLTONCE:{ strOut+=":稳定批处理-带判断";}break;  \
  case 29:{ strOut+=":批处理协调";}break;  \
  default:  {  strOut+=":未定义";  }break   ;     \
 } 

#else
#define  MComTask(strOut,ComPtr)  
#endif 

//#ifndef EXCLUDE_COMMACRO
//#define  MComFlag(strOut,ComPtr)  \
// if(ComPtr->Flag&0x1)  strOut+=":响应命令";\
// else  strOut+=":发起命令";\
// if(ComPtr->Flag&0x2)  strOut+=":需要回答";\
// else  strOut+=":无需回答";\
// if(ComPtr->Flag&0x4)  strOut+=":通讯完成";\
// if(ComPtr->Flag&0x8)  strOut+=":任务完成";
//
//
//#else
//#define  MComFlag(strOut,ComPtr)  
//#endif 

//////////////////////////////////////////////////////////////////////////
#define  COM_TASK_SUCCESS                1   //当需要产生计算结果时，如果全部结果存在，则表示成功
#define  COM_TASK_WARNING                2   //当需要产生计算结果，如果部分结果存在，则表示成功
#define  COM_TASK_ERROR                  3   //任务不能正确执行

#define  COM_TASK_WARNINGFILE            21  //有文件回传，但所要求的文件不完整
#define  COM_TASK_ERRORFILE              31  //有文件回传，但一个文件也没有

#ifndef EXCLUDE_COMMACRO
#define  MComTaskResult(strOut,ComPtr)  \
 switch(ComPtr->TaskCmdResult)  \
 {  \
  case COM_TASK_SUCCESS:{ strOut+=":业务完成";}break;  \
  case COM_TASK_WARNING:{ strOut+=":***业务警告";}break;  \
  case COM_TASK_ERROR:{ strOut+=":****业务错误";}break;  \
  case COM_TASK_WARNINGFILE:{ strOut+=":***结果文件不完整";}break;  \
  case COM_TASK_ERRORFILE:{ strOut+=":****结果文件没有生成";}break;  \
  default:  {  strOut+=":未定义";  }break   ;     \
 }  
#else
#define  MComTaskResult(strOut,ComPtr)  
#endif 

//////////////////////////////////////////////////////////////////////////
//通讯块属性字
#define  COM_FLAG_ANSWERSIDE            0x1   //响应侧命令
#define  COM_FLAG_NEEDANSWER            0x2   //需要应答
#define  COM_FLAG_COMFINISH             0x4   //通讯完成
#define  COM_FLAG_TASKFINISH            0x8   //任务完成
#define  COM_FLAG_TRANSMIT              0x10  //转发命令状态     //201107016
#define  COM_FLAG_GROUPCAST             0x20  //201201018 增加组播控制标志
#define  COM_FLAG_LOCALAGENT            0x40  //20120509  在本地实现代理机制
#define  COM_FLAG_JUDGESAMENAME         0x80  //201205029 判断传输同名文件(文件全名称相同，字节数量相同，不同仍要覆盖)
#define  COM_FLAG_IAMRESOTRECMD         0x100       //20130502  对于恢复命令进行标识，表明本命令为恢复命令
#define  COM_FLAG_SHOWONCE              0x200           //2013012028 当判断失陪命令，又不想每次都显示报警时用
                                                            //当命令帧完成后，如果存在该标记，需要向管理者发送命令完成信息
#define  COM_FLAG_COOPERATION           0xF000      //201308026  增加不同进程间的协同命令

#define  COM_FLAG_RESREQUIRE             0x10000        //20140104 当管理者将资源派遣给客户后，在原始命令帧上添加该标记
#define  COM_FLAG_RESANSWER              0x20000        //20140104 当管理者接受到资源请求后，回复命令表示，可以成功也可以不成功
#define  COM_FLAG_RESSERVER              0x40000        //20140104 当服务对象完成资源请求的命令后，在标志位上打上该标记



#define SET_FLAGCOOPERATION(x)     ((x&0xF)<<12)         //201308026  将1-15的缓冲地址变换到相应位置
#define GET_FLAGCOOPERATION(x)     ((x&0xF000)>>12)     //201308026  取协同缓冲区地址内容

#ifndef EXCLUDE_COMMACRO
#define  MComFlag(strOut,ComPtr)  \
if(ComPtr->Flag&COM_FLAG_ANSWERSIDE) strOut+=_T(":响应侧");\
if(ComPtr->Flag&COM_FLAG_NEEDANSWER) strOut+=_T(":需要应答");\
if(ComPtr->Flag&COM_FLAG_COMFINISH) strOut+=_T(":通讯结束");\
if(ComPtr->Flag&COM_FLAG_TASKFINISH) strOut+=_T(":任务结束");\
if(ComPtr->Flag&COM_FLAG_TRANSMIT) strOut+=_T(":转发令");\
if(ComPtr->Flag&COM_FLAG_GROUPCAST) strOut+=_T(":组播");\
if(ComPtr->Flag&COM_FLAG_LOCALAGENT) strOut+=_T(":本地代理");\
if(ComPtr->Flag&COM_FLAG_JUDGESAMENAME) strOut+=_T(":判断同名");\
if(ComPtr->Flag&COM_FLAG_IAMRESOTRECMD) strOut+=_T(":我被恢复");\
if(ComPtr->Flag&COM_FLAG_COOPERATION) strOut+=_T(":存在协同作业");\
if(ComPtr->Flag&COM_FLAG_SHOWONCE) strOut+=_T(":帧信息已显示");\
if(ComPtr->Flag&COM_FLAG_RESREQUIRE) strOut+=_T(":资源请求");\
if(ComPtr->Flag&COM_FLAG_RESANSWER) strOut+=_T(":资源回应");\
if(ComPtr->Flag&COM_FLAG_RESSERVER) strOut+=_T(":资源服务");\


#else
#define  MComFlag(strOut,ComPtr)  
#endif 



//////////////////////////////////////////////////////////////////////////
//IP 地址,long 与ip地址整数转换
#define  MTOIP(x1,x2,x3,x4)     (((x1)<<24)|((x2)<<16)|((x3)<<8)|(x4))
#define  MIP1(x)                (((x)>>24)&0xFF)
#define  MIP2(x)                (((x)>>16)&0xFF)
#define  MIP3(x)                (((x)>>8)&0xFF)
#define  MIP4(x)                ((x)&0xFF)

//////////////////////////////////////////////////////////////////////////
//通讯帧构成的任务ID宏
#define MFrameID(strOut,ComPtr) \
  strOut.Format(_T("%d\v%d\v%d\v%d"),ComPtr->AppNo,ComPtr->FrameTime,ComPtr->FrameNo,ComPtr->DestIP)

#define MFrameIDNoIP(strOut,ComPtr) \
  strOut.Format(_T("%d\v%d\v%d\v%d"),ComPtr->AppNo,ComPtr->FrameTime,ComPtr->FrameNo,ComPtr->Flag&0xF000)

#define MFrameIDExt(strOut,mAppNo,mFrameTime,mFrameNo,mDestIP) \
  strOut.Format(_T("%d\v%d\v%d\v%d"),mAppNo,mFrameTime,mFrameNo,mDestIP)


//////////////////////////////////////////////////////////////////////////
//Dump Com Command
#define  COMTRACE1(strOut,ComPtr) \
        MComCmd(strOut,ComPtr) \
        MComTask(strOut,ComPtr) \
        MComFlag(strOut,ComPtr) \
        MComCmdResult(strOut,ComPtr) \
        MComTaskResult(strOut,ComPtr) \

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//当前机器缺省的工作目录，当接收文件时，以此目录为基础目录按IP地址建接收
//文件目录，通过配置设置，如果配置不存在，就在程序目录下，建立Temp作为缺省
//工作情况
typedef struct tagPSDCOMWORKPATH
{
 unsigned long  IP;     //IP地址
 unsigned long  ServerIP;  //保存管理IP节点内容     //2011010024
 unsigned char  Path[MAX_PATH];      //2011010024 管理临时文件目录内容
}PSDCOMWORKPATH,far* PPSDCOMWORKPATH;
///
#define  COM_WORKPATH_SIZE     sizeof(PSDCOMWORKPATH)

/////////////////////////////////////////////////////////////////////////
//通讯机器工作状态配置内容，由Flag指向IP地址所描述机器的工作状态
//只有那些在线的机器，才可能作为共享资源
typedef struct tagPSDCOMCFG
{
 unsigned long  IP;     //IP地址
 unsigned long  Flag;   //B0  1-在线 0-下线，默认为在线
                        //B1  1-通讯中，默认为空闲
                        //B2  0-允许共享，1-关闭共享, 默认不关闭(表示协作工作模式)
                        //B3  1-唯一Server IP 标记，为非对等工作模式时指定
                        //B4  1-接受内存狗信息，0-不接受狗信息，可以通过接受与不接受狗信息来统计内部计算节点或客户信息，来进行       //201101007
 unsigned int   Count;  //通讯次数
}PSDCOMCFG,far* PPSDCOMCFG;
///
#define COM_CFG_SIZE   sizeof(PSDCOMCFG)
///
#define COMCFG_FLAG_ONLINE       0x1
#define COMCFG_FLAG_BUSY         0x2
#define COMCFG_FLAG_CLOSESHARE   0x4
#define COMCFG_FLAG_ONLYSERVER   0x8  
///
#define  CFG_IPCFG_MAXCOUNT       (50)   //在中间层上，可以支持的最大IP地址支持数量     //201208030

#define MEnable(cfgFlag,bitValue)   ((cfgFlag)|=(bitValue))
#define MDisable(cfgFlag,bitValue)   ((cfgFlag)&=~(bitValue))
#define MIsFalse(cfgFlag,bitValue)    ((cfgFlag)&(bitValue)?false:true)
#define MIsTrue(cfgFlag,bitValue)    ((cfgFlag)&(bitValue)?true:false)
#endif