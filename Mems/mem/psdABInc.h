#ifndef PSDABINC_BYSDW
#define   PSDABINC_BYSDW       201103027

#include "PSDStructs.h"  //支持通讯结构内容
#include "PSDDogDef.h"

#if _cplusplus
extern "C"
{
 #endif

 //PSD AB buffer model
 //////////////////////////////////////////////////////
 //复位PSD业务层操作写入的缓冲区
 MEMS_API  void   PSDCOMReset(int nAppNo = 0); 

 //将PSD业务层上的内容写入到发送缓冲区，共通信层读取
 MEMS_API  long   PSDWrite(int nAppNo, void* pData, long lLen, int* pnError = NULL); 
 //将读取由通信层发送到缓冲区的内容
 MEMS_API  long   PSDRead(int nAppNo, void* pData, long lLen, int* pnError = NULL); 

 //从PSD业务层中观察最新的内容
 MEMS_API  long   PSDPeek(int nAppNo, OUT void* pData, IN long lLen, OUT int* pnError = NULL);  
 //判断PSD业务层上是否要处理的数据已经填满数据区
 MEMS_API  bool   PSDIsFull(int nAppNo);  
 //判断PSD业务层上是否无任何数据内容
 MEMS_API  bool   PSDIsEmpty(int nAppNo);  
 //判断PSD业务层上是否有要处理的数据
 MEMS_API  bool   PSDExist(int nAppNo);  

 //将通信层收到的信息缓存到PSD业务层
 MEMS_API  long   COMWrite(int nAppNo, void* pData, long lLen, int* pnError = NULL); 
 //通信层读取最新要发送内容
 MEMS_API  long   COMRead(int nAppNo, OUT void* pData, IN long lLen, OUT int* pnError = NULL);  
  //2012010029  通信层读取业务层数据(可以指定帧长度偏移位置)
 MEMS_API  long   COMReadA(int nAppNo, OUT void* pData, IN long lLen,int nLenPos=sizeof(unsigned short), OUT int* pnError = NULL);  
 
 //从通讯层中观察最新要发送内容
 MEMS_API  long   COMPeek(int nAppNo, OUT void* pData, IN long lLen, OUT int* pnError = NULL);  
 //判断通讯层上是否要处理的数据已经填满数据区
 MEMS_API  bool   COMIsFull(int nAppNo);  
 //判断通讯层上是否无任何数据内容
 MEMS_API  bool   COMIsEmpty(int nAppNo);  
 //判断通讯层上是否有要处理的数据
 MEMS_API  bool   COMExist(int nAppNo);  

 //复位业务和通讯区的数据和状态
 MEMS_API  bool   PSDCOMClear(int nAppNo, int nWho = -1);  
 //201107024 业务层重启控制标记
 MEMS_API  int    AppReset(int nAppNo, bool bReset = true);

 ////////////////////////////////////////////////////////////////
 //调试输出信息内容
 #define   PSDDUMP_UP      1
 #define   PSDDUMP_DOWN    2

 MEMS_API  long   PSDDump(int nAppNo, int nWho, OUT char* pOut, IN int nMaxLen = MAX_PATH);
 MEMS_API  long   PSDDump2(char* pOut, IN int nMaxLen = MAX_PATH);
 //保存通讯写入内容,后面为属性内容
 MEMS_API long    PSDComLog(const char* pchName, float* pnRatio = NULL, int* pnMaxFiles = NULL, int* pnMaxBytes = NULL, int* pnMode = NULL);
 //使能通讯写入进行日志记录
 MEMS_API long    PSDComLogEnable(bool bEnable = true);

 //////////////////////////////////////////////////////////////////////////
 //增加对配置文件的处理
 //存储区内的IP地址定义
 //设置当前机器工作配置，如果没有配置，指向通讯程序自己启动目录
 MEMS_API  int    PSDSetWorkPath(char* pchPath, int nMaxLen = MAX_PATH);
 //取缺省的当前机器工作配置，如果没有配置，指向通讯程序自己启动目录
 MEMS_API  int    PSDWorkPath(char* pchPath, int nMaxLen = MAX_PATH);

 //设置本机IP地址，一般由通讯层来完成
 MEMS_API  void   PSDSetMyIP(long lIP);
 //获取本机IP地址
 MEMS_API   long  PSDMyIP();
 //获取管理机地址     //2011010024
 MEMS_API   long  PSDServerIP();
 //设置管理机地址     //2011010024
 MEMS_API   void  PSDServerIP(long lServerIP);

 //////////////////////////////////////////////////////////////////////////
 //当前机器管理的最大的机器IP数量，用于遍历时的最大值
 MEMS_API  int    PSDMaxIPCount(); 
 //当前存在的IP配置数量
 MEMS_API  int    PSDIPCount();
 //找一个为空的配置位置,返回索引,<0 表明没有空闲位置保存地址了
 MEMS_API  int    PSDSearchSpaceIPPos();
 //判断指定位置上的记录是否有效
 MEMS_API  bool   PSDIsIPPosValid(int nIndex = 0);
 //删除已经不在的地址删除，并将其它地址进行整理
 MEMS_API int     PSDIPTrim();
 //清空全部IP配置内容，重新进行配置
 MEMS_API int     PSDIPZero();

 // 根据IP地址寻找它，<0 为没有找到
 MEMS_API  int    PSDFindIPPos(unsigned long ulIP, PPSDCOMCFG pIPCfg = NULL);
 // 对指定的IP地址，给出工作任务记数器变化内容，以方便动态分配任务,返回记数前数据     //2011010013
 MEMS_API  int    PSDTaskIncrement(unsigned long ulIP, int nJumpCount=1); 

 //指定当前配置中，一个地址为管理服务节点
 MEMS_API bool    PSDSetSingleServer(unsigned long ulIP, PPSDCOMCFG pServer = NULL, bool bAutoAdd = true);

 //取指定的配置是否存在有效的配置,在地址表中不存放自己
 MEMS_API  bool   PSDGetComCfg(PSDCOMCFG& cfgItem, int nIndex = 0);

 //设置通讯位置上的值内容，可以先得到，然后改造它，尤其对于标志位内容
 //  除非是要复位它
 MEMS_API  bool   PSDSetComCfg(PSDCOMCFG& cfgItem, int nIndex = 0); 
 // 增加一个通信配置内容
 MEMS_API  bool   PSDAddComCfg(PSDCOMCFG& cfgItem, bool bOnlyZeroIP = false); 
//201208029 获取线上的IP地址列表
 MEMS_API  int   PSDOnLineIPList(unsigned long* plIPList,int nMaxIPCount); 

 //////////////////////////////////////////////////////////////////////////
 //201107024 对通信层重启控制内容
 //返回当前重启次数，when bReset is true重启一次对记数器加1 
 MEMS_API  int    ComReset(bool bReset = false); 
 //心跳一次，bBeat is true 对心跳次数+1
 MEMS_API  int    ComHeartBeat(bool bBeat = false);

 //////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////
 //201108022 增加对内存狗的支持
 //狗数据区清除掉
 MEMS_API  void   DogReset(); 
 //狗数据指定
 MEMS_API  int    DogDataMacro(void* pData, int nLen, int* pnError = NULL);
 //取指定节数据偏移地址 
 MEMS_API  int    DogSectionOffset(int nSecType, int nIndex = 0);

 //在内存中提取指定模块信息内容
 MEMS_API  int    DogGetSection(int nSecType, OUT void* pData, IN OUT int* pDataLen);
 
 //在指定缓冲区中提取指定节的数据内容
 MEMS_API  int    DogGetSectionExt(int nSecType, OUT void* pData, IN OUT int* pDataLen,IN void* pSrc,int nMaxLen);

 //取用户数量
 MEMS_API  int    DogUserCount();
 //取指定位置用户信息（按规定的格式）
 MEMS_API  bool   DogGetUserInfo(PDOGUSER pUser, int nIndex);
 //设置指定位置用户信息（按规定的格式）
 MEMS_API  bool   DogSetUserInfo(int nIndex, PDOGUSER pUser);
 //取模块功能信息
 MEMS_API  int    DogModuleCount();
 //取模块指定信息
 MEMS_API  bool   DogGetModuleInfo(PDOGMODULE pModule, int nIndex);
 //设置指定模块信息
 MEMS_API  bool   DogSetModuleInfo(int nIndex, PDOGMODULE pModule);

 //取狗写入时间内容
 MEMS_API  bool   DogGetDogLastTime(PDOGUPDATETIME pDogTime);
 //设置指定模块信息
 MEMS_API  bool   DogSetDogLastTime(PDOGUPDATETIME pDogTime);

 //////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////
 //20110902 增加应用程序内关键变化通知机制（通过共享内容实现）
 // 应用变化可以应用根据需求增加，不用更新库变化，库提供1-254个变化控制
 // 可以用于顺序控制
 #define   APP_PSDCLOUD_NO             1  //通信程序变化， //通信层，机器数目改变记数器
 #define   APP_PSDDOG_ALREADY          2  //看狗信息发送是否已存在发送（目前是EndServer/PSDCloud两种）

 #define   APP_MAC_ONLINE              3       //201208030  存在机器上线
 #define   APP_MAC_OFFLINE             4       //201208030 存在机器下线了

 MEMS_API   int   PSDAPPChange(int nAppNo = APP_PSDCLOUD_NO, int nCountOffset = 0); //offset =1 为增加一个,-1为减少一个,0为获取当前的值
 //应用标志控制内容，与应用程序变化共享1-254变化控制，但一个位置可以由sizeof(int)*8个标志位
 MEMS_API   bool   PSDAPPSetFlag(int nAppNo,bool bStatus=false,int nFlagPos=0); 
 //读指定位置的标志（一个应用位置最多只能有32个标志应用）
 MEMS_API   bool   PSDAPPGetFlag(int nAppNo,int nFlagPos=0);

 #if _cplusplus
}
#endif

#endif
