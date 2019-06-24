#ifndef __UNION_H__
#define __UNION_H__
#include "user_includes.h"

//---------------------------------------------
#define IN_LEFT			((ADCConvertedValue[ValIRLeft]*330/4096)<g_Sensitivity.IRCntVol)
#define IN_RIGHT		((ADCConvertedValue[ValIRRight]*330/4096)<g_Sensitivity.IRCntVol)

#define OUT_LEFT		((ADCConvertedValue[ValIRLeft]*330/4096)>g_Sensitivity.IRCntVol)
#define OUT_RIGHT		((ADCConvertedValue[ValIRRight]*330/4096)>g_Sensitivity.IRCntVol)
//---------------------------------------------

extern u8 UsartDmaSendBuff[320];

void YesResetRun(void);
void MultipleDeal(void);
void DealBill(void);
#endif
