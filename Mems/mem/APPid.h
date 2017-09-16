#ifndef APPID_INCLUDE
#define APPID_INCLUDE       201103031
//以下为应用程序ID标示，在利用共享内存通讯时，需要
//采用以下统一的ID标识，如果标示有变化，与之相对应
//的应用，将需要重新进行编译和链接
#define    PSD_EDIT_APP          1   // PSDEdit主要应用程序
#define    PSD_PFREPORT_1        2   //第一类潮流统计报表
#define    PSD_SWREPORT_1        3   //第一类稳定统计报表

//////////////////////////////////////////////////////////////////////////
//定义消息参数内容
//wParam  内容
#define    PSDSHARE_WPARAM_UPDATE    1  //更新命令内容

//////////////////////////////////////////////////////////////////////////
//lParam  内容
#define    PSDSHARE_LPARAM_RELOADBSE    1  //重新加载文件
#define    PSDSHARE_LPARAM_NOTEXISTBSE  2  //加载文件失败

//定义消息响应函数内容
#if !defined(EXPORT_MESSAGENOTICE)
#define  DECLARE_MSGNO() \
public: \
  static UINT RegMsgNo; \
public: \
   LRESULT   MsgInShareMemory(WPARAM wParam,LPARAM lParam); \
   LRESULT   PostRegisterMessage(WPARAM wParam,LPARAM lParam=0); \


#define  IMPLEMENT_MSGNO(CLASS)  \
 UINT  CLASS::RegMsgNo    = ::RegisterWindowMessage("PSDSHARE_MSG"); \
 \
 LRESULT  CLASS::PostRegisterMessage(WPARAM wParam,LPARAM lParam) \
 { \
  PostMessage(RegMsgNo,wParam,lParam); \
  return 1L; \
 }\

#else

#define       DECLARE_MSGNO() 
#define       IMPLEMENT_MSGNO()
#endif


#endif