#ifndef __USER_COMMON_H__
#define __USER_COMMON_H__
#include "user_includes.h"
//---------------------------------------------------------------------------
//----------------------------------------------------------------------------
typedef struct {
	u16* Param;
	u16 max;
	u16 min;
}_KeySetSensitivity;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#define  CODE_FIRST  0
#define  CODE_NEXT   1
#define  NOTES_NONE  0
//--------------------------------------------------------------------
void SwitchDecSensitivity(void);
void SwitchAddSensitivity(void);
void CheckOld(void);
void IF_ERR_SEROR(void);
//-----------------------------------------------------------------
//-----------------小电机停转---------------------------
void stbj(void);
//---------------------------------------------------------
void WidthAnaly(void);
/***************幅面计算****************************/
void ScopeAnalysis(void);

#endif

