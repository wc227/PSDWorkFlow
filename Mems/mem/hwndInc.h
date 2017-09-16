#ifndef  HWNDINC_INCLUDE_BYSDW   
#define  HWNDINC_INCLUDE_BYSDW        201103027
#ifndef __cplusplus
extern "C"
{
#endif

//201103027 
//////////////////////////////////////////////////////////////////////////
//功能：对存在窗口的进程，建立消息中断传输机制，通过在共享
//内存中注册相关窗口，可以在注册的窗口间通过发送约定的消息进行
//通信，可以实现非窗口进程向窗口进程发送消息操作；消息的内容由
//具体程序另外约定

//////////////////////////////////////////////////////////////////////////
//过程：先要将接受消息的窗口，按应用的需要进行固定的编号，在同一个系统中
//窗口编号要保持唯一性，可以通过判断应用mems.dll的应用程序数量进行
//分配，发送给对方消息时，实际上是指定对方的编号发送，这样就将对
//动态窗口操作转换为对编号的操作
 //////////////////////////////////////////////////////////////////////////
 //消息控制

 //对窗口广播共享数据已经改变
 MEMS_API  void BroadcastVarietyMsg(UINT uMsg, WPARAM wPara, LPARAM lPara = 0,
  HWND hExceptHWND = NULL);
 //将窗口注册到指定名称的共享内存中
 //  MEMS_API  int  RegisterHWND(HWND hWnd);
  MEMS_API  int RegisterHWND(HWND hWnd, int nPara = -1);
  //释放窗口，释放窗口后，将不在接受外来进程发送的消息
 //取消指定窗口在指定名称的共享内存中注册信息
 MEMS_API  int UnregisterHWND(HWND hWnd);   
 //窗口绑定
 //指定窗口对应的固定标示（将动态窗口转换可以控制的编号）     //2006-12-19
 MEMS_API  int SetHWNDPara(HWND hWnd, int nPara);
 //点对点通信，按指定的条件标示通知消息       //2006-12-19
 MEMS_API  int PtoPMsg(int nPara, UINT uMsg, WPARAM wPara, LPARAM lPara = 0);



#ifndef __cplusplus
}
#endif

#endif