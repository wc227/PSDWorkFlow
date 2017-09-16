#ifndef  PSD_EVT_HEADER
#define PSD_EVT_HEADER
//2011012017 数据事件记录器地址定义表

//////////////////////////////////////////////////////////////////////////
//文件地址改变事件定义，可以在已定义基础上增加
// 最大数据范围为[1-255]
#define   PSDEVT_FILE_NULL   0  //Reserve 保留地址

#define   PSDEVT_FILE_WAMS_RAW      10  //Wams 输入文件
#define   PSDEVT_FILE_WAMS_TOEMS    11  //到EMS整合
#define   PSDEVT_FILE_WAMS_TOLINE   12  //到线路辨识
#define   PSDEVT_FILE_WAMS_TOPRONY    13  //到Prony分析
#define   PSDEVT_FILE_WAMS_TOSEARCH   14  //到振荡源搜索

#define   PSDEVT_FILE_WAMS_LINE   17  //线路辨识结果
#define   PSDEVT_FILE_WAMS_PRONY    18  //Prony分析结果
#define   PSDEVT_FILE_WAMS_SEARCH   19  //振荡源搜索结果


//////////////////////////////////////////////////////////////////////////
//应用程序运行事件定义
// 最大程序编号范围为[1-255]
#define   PSDEVT_TASK_NULL         0

#define   PSDEVT_TASK_WAMS_FILTER      1    //wams 数据拆解器

//////////////////////////////////////////////////////////////////////////
//应用程序运行错误计数器
// 最大程序编号范围为[1-255]
#define   PSDEVT_ERR_NULL         0

#define   PSDEVT_ERR_WFILTER      1        //wams 数据拆解器连续错误事件

#endif
