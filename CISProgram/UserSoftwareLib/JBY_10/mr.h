/***************************************************************************

****************************************************************************/

/*防止重复引用 */
#ifndef MR_H
#define MR_H

#include "system.h"

/*将外部包含和内部包含分开*/
#ifdef _MR_H_
    #define MR_EXT_PARA
	#define MR_EXT_FUNC
	#define _INITMR(d) =d
#else
	#ifdef __cplusplus
		#define MR_EXT_PARA  EXTERN_C
		#define MR_EXT_FUNC  extern
	#else
		#define MR_EXT_PARA  extern
		#define MR_EXT_FUNC  extern		
	#endif
	#define _INITMR(d)
#endif

//---------------------------------------------------------------------
//全局常量定义
//---------------------------------------------------------------------
#define MAX_COUNT 100
#define MAX_MP_COUNT 500
#define MAX_FALLMP_COUNT (MAX_MP_COUNT/2)


enum
{
	CHAO_XIANG_0,
	CHAO_XIANG_1,
	CHAO_XIANG_2,
	CHAO_XIANG_3
};
//---------------------------------------------------------------------
//全局类型定义
//---------------------------------------------------------------------
typedef struct// ValuePosInfor
{
	u8 val;
	u16 startPos;
	u16 endPos;
	u16 pos;
	u16 oldPos;
	u8 maxSzVal;
	u8 minVal;
	u16 minPos;
}ValuePosInfor;

//---------------------------------------------------------------------
//全局类型定义
//---------------------------------------------------------------------
// typedef struct 
// {
// 	u8 noteType;		//币值
// 	u8 headMrBanBie;	//套别和版别
// 	u8 ctmNum;			//磁条码根数
// 	u8 bccSum;
// }NJCTB_INFO_T;


typedef struct 
{
	u8 noteType;	//币值
	u8 banBie;		//版别
	u8 ctmNum;		//磁条码根数
//	u8 bccSum;
}NJCTB_INFO_T;

typedef enum
{
	WID_100 = 0,
	WID_20 = 1,
	WID_5 = 2,
	WID_ARTI = 3
}NOTEWIDTH_T;



enum
{
	RMB_100_05,
	RMB_100_15,
	RMB_50,
	RMB_20,
	RMB_10,
	RMB_5,
	RMB_1,
	RMB_ARTI,
};
// enum
// {
// 	BAN_BIE_99_MR = 0,
// 	BAN_BIE_05_MR = 1,
// 	BAN_BIE_05_2_MR = 2,
// //	BAN_BIE_ARTI = 3,
// };

enum
{
	BAN_BIE_99_MR = 0,
	BAN_BIE_05_MR = 1,
	BAN_BIE_15_MR,
	BAN_BIE_05_2_MR,
//	BAN_BIE_ARTI = 3,
};


enum
{
	INDEX_LEFT_GZH_MR = 0,
	INDEX_RIGHT_GZH_MR,
	INDEX_LEFT_HEAD_MR,
	INDEX_RIGHT_HEAD_MR,
	MR_NUM,
};


 enum
 {
	AQX_ERROR_LEN = 1,
	AQX_WAVE_NUM_ERR = 2,
	AQX_CODE_ERR,

	CXYM_LESS = 1,

	GZH_LESS = 1,
	PINYIN_LESS = 2,
 };


//---------------------------------------------------------------------
#define IR_DATA_MAX_LEN 900//650
// MR_EXT_PARA u8 irDataA[2][IR_DATA_MAX_LEN]; 
MR_EXT_PARA u16 lengthDataLen;
MR_EXT_PARA u8 lengthData[REAL_IR_NUM+1][IR_DATA_MAX_LEN]; 
MR_EXT_PARA u8 lengthIdleOriginValue[REAL_IR_NUM];
 
#define MG_DATA_MAX_LEN 850
// MR_EXT_PARA u8 mgDataA[2][10]; 
MR_EXT_PARA u8 mgData[2][MG_DATA_MAX_LEN]; 
MR_EXT_PARA u16 mgDataLen;

//MR_EXT_PARA u8 uvDataA[2][UV_DATA_MAX_LEN]; 
//MR_EXT_PARA u16 uvDataLenA;

//MR_EXT_PARA u8 uvDataErr[4][UV_DATA_MAX_LEN]; 
//MR_EXT_PARA u8 mgDataErr[3][MG_DATA_MAX_LEN]; 
//MR_EXT_PARA u8 mtDataErr[MT_DATA_MAX_LEN]; 
//MR_EXT_PARA u8 uvDataLenErr,mgDataLenErr;
//MR_EXT_PARA u8 uvDataErrUsed,mgDataErrUsed,mtDataErrUsed;
#define UV_DATA_MAX_LEN 900
MR_EXT_PARA u8 uvData[UV_DATA_MAX_LEN]; 
MR_EXT_PARA u16 uvDataLen;


#define COLOR_DATA_MAX_LEN 300
MR_EXT_PARA u8 colorData[12][COLOR_DATA_MAX_LEN]; 
MR_EXT_PARA u16 colorDataLen;

MR_EXT_PARA u8 errorCode;

MR_EXT_PARA u8 currentNoteType;

enum
{
	COLLABRATION_OFF,
	COLLABRATION_COLOR,
	COLLABRATION_80G_BZ,
	COLLABRATION_40G_BZ,
};
MR_EXT_PARA u8 gb_inCollabration;
MR_EXT_PARA u8 collabrationNoteNum;
#define COLLABRATION_FINSH_POINT_NUM 5
MR_EXT_PARA u32 collabrationSum[REAL_IR_NUM];
MR_EXT_PARA u8 collabrationNum[REAL_IR_NUM];
MR_EXT_PARA u16 collabrationValue[REAL_IR_NUM];
MR_EXT_PARA u16 collabrationMax[REAL_IR_NUM];
MR_EXT_PARA u16 collabrationMin[REAL_IR_NUM];

typedef struct
{
	u16 pos;
	u16 val;
}MG_WAVE;

// #define MAX_AQX_WAVE_NUM 30
// MR_EXT_PARA MG_WAVE aqxMaxWave[MAX_AQX_WAVE_NUM];
// MR_EXT_PARA u8 aqxMaxWaveNum;
// MR_EXT_PARA MG_WAVE aqxMinWave[MAX_AQX_WAVE_NUM];
// MR_EXT_PARA u8 aqxMinWaveNum;
//MR_EXT_PARA u8 chanelMgThres[7];

/*公开的过程/函数*/
#ifdef __cplusplus
extern "C"
{
#endif
	//---------------------------------------------------------------------
	//函数介绍
	//---------------------------------------------------------------------
	//MR_EXT_FUNC void mr_JudgeNoteType(u8 *info);
	//MR_EXT_FUNC void mr_JudgeUsdNoteType(u8 *info);
	MR_EXT_FUNC void mr_JudgeRmbNoteType(u8 noteWidth);
	MR_EXT_FUNC u16 GetAqxCodeInMp(u16 pos);
	MR_EXT_FUNC void length_collabrationCompute(void);
	//MR_EXT_FUNC void uv_JudgeNote(void);
#ifdef __cplusplus
}
#endif

#endif
