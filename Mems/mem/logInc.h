#ifndef LOGINC_BYSDW
#define   LOGINC_BYSDW       201103027

#if _cplusplus
extern "C" {
#endif
  //////////////////////////////////////////////////////////////////////////
  //全局日志管理
  //写一条日志，pLog空间必须小于或等于MAX_PATH
  MEMS_API long LogWrite(char* pLog, int* pnError = NULL); //
  //读缓冲区长度，pLog空间长度必须大于或等于MAX_PATH
  MEMS_API long LogRead(char* pLog, int* pnError = NULL);
 //读取历史缓冲区中内容，可以按最大或最小方式读取
  MEMS_API long LogHistory( char* pLog, int nMaxLen,int* pnError = NULL );

  //保存日志内容,后面为属性内容
  MEMS_API long LogSaveHistory(char* pchName, float* pnRatio = NULL,int* pnMaxFiles=NULL,int* pnMaxBytes=NULL,int*pnMode=NULL);
  //结束日志保存
  MEMS_API long LogSaveHistoryEnable(bool bEnable =true);
#if _cplusplus
}
#endif

#endif
