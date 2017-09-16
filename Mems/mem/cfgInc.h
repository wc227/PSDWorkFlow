#ifndef CFGINC_BYSDW
#define   CFGINC_BYSDW       201103027

#if _cplusplus
extern "C" {
#endif
 //工作过程：
 //  开发者根据应用需要，决定一个配置存储区，存储区内是一个通用的线性空间，
 //  由开发者，根据应用的定义决定访问的位置及长度，例如，在线性空间的第5个
 //  字节，连续存4个字节IP地址，则在操作时，将lOffset指向5，lLen指向6可以在
 //  不同的应用间实现应用配置交互

  //////////////////////////////////////////////////////////////////////////
  //基于位置模式的配置内容
  MEMS_API  long WriteCfg(void* pData, long lLen, long lOffset = 0, int* pnError = NULL);
  //读取配置文件内容
  MEMS_API  long ReadCfg(void* pData, long lLen, long lOffset = 0, int* pnError = NULL);
  //存配置文件
  MEMS_API  long SaveCfg(const char* pchName,int * pnError=NULL);

#if _cplusplus
}
#endif

#endif
