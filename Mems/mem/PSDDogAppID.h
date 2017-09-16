#ifndef _PSDDOGAPP_ID_BYSDW
#define _PSDDOGAPP_ID_BYSDW

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//定义宏狗的APP，ID定义是唯一的
#define PSD_PFNTG_ID     1    //潮流计算
#define PSD_SWNTG_ID     2    //稳定计算
#define PSD_SCCPG_ID     3    //短路电路计算
#define PSD_CLIQUE_ID    4    //地理接线图
#define PSD_SSAPG_ID     5    //小扰动计算

//基本环境及典型功能
#define PSD_EDITG_ID     10  //总集成环境
#define PSD_PFREPORTG_ID  11  //潮流统计分析报表
#define PSD_SWBATG_ID     12  //单机暂态稳定批处理
#define PSD_SSAPAG_ID     13  //小干扰自动分析

//暂态稳定密切相关的应用
#define PSD_SECTIONG_ID   20  //断面输电极限
#define PSD_TASG_ID       21  //暂态稳定辅助决策
#define PSD_SSC_I         22  //安全稳定控制程序应用1

//与长过程密切相关的应用
#define PSD_FDS_ID        30   //长过程计算程序
#define PSD_FDS_I         31   //长过程计算功能程序
#endif
