#ifndef __USER_TM1616_H__
#define __USER_TM1616_H__
#include "user_includes.h"

#define SEG_NUM 29
//----------------------------------------------
typedef struct { 
	u8	LEDW_TOLA;
	u8  :8;
	
	u8	LEDW_TOLB;
	u8  :8;
	
	u8	LEDW_TOLC;
	u8  :8;
	
	u8	LEDW_TOLE;
	u8  :8;
	
	u8	LEDW_TOLF;
	u8  :8;
	
	u8	LEDW_TOLD;
	u8  LEDW_JSA;
	
	u8  :8;
	u8	LEDW_JSB;
	
	u8  :8;
	u8	LEDW_JSC;

}_LEDW1629;
//--------------------------------------------------------------------
//----------------------------------------------
typedef struct { 
	u8	LEDW9_TOLA;
    u8	LEDW9_JSA;
	u8	LEDW9_TOLB;
    u8  LEDW9_JSB;
	u8	LEDW9_TOLC;
    u8	LEDW9_JSC;
	u8	LEDW9_TOLD;
	u8	LEDW9_JSD;
	u8	LEDW9_TOLE;
    u8  LEDW9_BJ;
}_LEDW91629;
extern _LEDW91629 g_LEDW91629;
//--------------------------------------------------------------------

void TM1616_Config(void);
void Disp_3NumW(u8*);
void Disp_TotalW(void);
void Disp_TotalW9(void);
void Fill_3NumW(void);
void Fill_TotalW(void);
void Disp_Static(void);
void Fill_Static(void);
#endif


