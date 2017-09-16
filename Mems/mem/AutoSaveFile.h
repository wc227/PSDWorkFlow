#ifndef AUTO_SAVE_TO_FILE_20110612
#define  AUTO_SAVE_TO_FILE_20110612

#ifndef S_OVERLAY    
#define S_OVERLAY    0
#define S_APPEND     1 
#endif
 
class MEMS_API CAutoSaveFile 
{
public:
  CAutoSaveFile();
  ~CAutoSaveFile();
protected:
  bool   m_bOpenStatus; //文件打开状态
  HANDLE  m_hFile;   //文件句柄
public:
  bool  IsOpen(){return m_bOpenStatus;}
public:
   virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags,int* pError = NULL);
	 virtual void Close();
//////////////////////////////////////////////////////////////////////////
//public:
public:
   BOOL Open(UINT uFlag = OPEN_ALWAYS);  //是否永远打开，直到人工关闭它
	 unsigned long Read(void* lpBuf, unsigned long nCount);
   //写缓冲区数据到日志文件中去，可能会导致文件变化，是本类中需要被调用的函数
	 void Write(const void* lpBuf, unsigned long nCount);

   long  GetLength();  //获取文件长度
   long  GetPosition(); //得到当前的存盘位置
   bool CanOpen(const char* pchFileName,UINT uStyles=OF_EXIST|OF_WRITE);
//////////////////////////////////////////////////////////////////////////
//文件名称管理
protected:
  long  m_lTotalOpenCount;    // 总的打开文件次数
  int   m_nOneFileMaxLength;       //201106012  单文件最大长度
  int   m_nOverlayMode ;    //数据存盘时的模式，覆盖式或追加模式
  int   m_nSameFileIndex;               //2006-10-18 同文件名当前索引
  int   m_nSameFileMaxCount;       //201106012  同类文件最大数量
  char  m_chFileName[MAX_PATH];     //2006-10-18

  bool  m_bSaveEnable;             //201106012  控制是否能够保存内容
  float m_fSaveRatio;                  //记录保存的比例
public:
	int SameFileMaxCount() const { return m_nSameFileMaxCount; }
	void SameFileMaxCount(int val) { m_nSameFileMaxCount = val; }

	int OneFileMaxLength() const { return m_nOneFileMaxLength; }
	void OneFileMaxLength(int val) { m_nOneFileMaxLength = val; }

	int OverlayMode() const { return m_nOverlayMode; }
	void OverlayMode(int val) { m_nOverlayMode = val; }

	int SameFileIndex() const { return m_nSameFileIndex; }
	void SameFileIndex(int val) { m_nSameFileIndex = val; }

	const char* FileName() { return m_chFileName; }
	void FileName(const char* val);

	bool SaveEnable() const { return m_bSaveEnable; }
	void SaveEnable(bool val) { m_bSaveEnable = val; }

	float SaveRatio() const { return m_fSaveRatio; }
	void SaveRatio(float val) { m_fSaveRatio = val; }
};
#endif
