#ifndef SECTIONINC_BYSDW
#define   SECTIONINC_BYSDW       201103027

#if _cplusplus
extern "C" {
#endif
  //////////////////////////////////////////////////////////////////////////
  //全局节配置方式管理
//工作原理：
//   系统配置中存在多节需要共享管理，每个节有固定的内容，其内容有长度、意义编号、控制字来描述
//   每个描述字为long型，原理上还是一个线性区域，实现空间的按节的动态管理，与cfg方式，按偏移
//   方式管理，区域是具有一定的灵活性，需要说明的是，初始节配置的空间大小，最后面的修改会有影响
//   如果修改后的空间超过初始空间，将不能被有效保存在共享区域中，如果存在配置修改，其配置内容
//   最好不要用变长字符串内容
  #define   MGetSectionMeaning(p)  (*(long*)((char*)(p)))  //取节意义
  #define   MGetSectionExt(p)      (*(long*)((char*)(p)+1*sizeof(long))) 
  #define   MGetSectionData(p)     ((char*)((char*)(p)+2*sizeof(long))) 

//20110403 写节内容，pData中不要含有节编号和控制字内容
  MEMS_API  long WriteSectionCfg(IN void* pData,IN long lLen, long lSecMeaning, long lExtData, int* pnError = NULL);
//20110403 读节内容，读出的pData中不要含有节编号和控制字内容
  MEMS_API  long ReadSectionCfg(OUT void* pData,IN long lLen, long lSecMeaning, long lExtData, int* pnError = NULL);
//20110403  删节内容，删除节之后，共享内存空间会自动回收
  MEMS_API  long DeleteSectionCfg(long lSecMeaning, long lExtData = -1);
//20110403  按序号遍历节配置内容，指导返回为NULL,返回的指针包括节编号和节控制字，
//          lIndex,输入为索引，输出为节长度(包括节编号和控制字）
  MEMS_API  void* GetSection(IN OUT long& lIndex);  //得到nIndex配置,并返回节内容(包括长度，节意义和扩展数，数据)
//20110403  获取配置区中存在的节数目
  MEMS_API  long GetSectionCount();         //得到总的配置节数
//20110403 找指定意义的节数据内容，如果lExeData为-1，将不考虑控制字条件，返回为存在的节的数据内容，不包括节编号和控制字
//         lPureSectionLen,指向返回的节配置长度
  MEMS_API  void* FindSection(OUT long& lPureSectionLen, long lSecMeaning, long lExtData);         //得到总的配置节数
  //  MEMS_API  long SaveSectionCfg(char* pchName);

#if _cplusplus
}
#endif

#endif
