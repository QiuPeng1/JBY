#ifndef MENU_H
#define MENU_H

#include "system.h"
#include "disp.h"

enum
{
	FONT_8 = 8,
	FONT_16 = 16,	//字体以高度为度量点
	FONT_24 = 24,
	FONT_32 = 32,
	FONT_48 = 48,
};

enum
{
	TOP_BAR_X = 0,
	TOP_BAR_Y = 0,
	TOP_BAR_H = 32,
	TOP_BAR_W = SCREEN_WIDTH,
	
	BOTTOM_BAR_X = 0,	
	BOTTOM_BAR_H = 32,
	BOTTOM_BAR_Y = SCREEN_HEIGHT-BOTTOM_BAR_H,
	BOTTOM_BAR_W = SCREEN_WIDTH,
	
	MID_BAR_X = 0,
	MID_BAR_Y = TOP_BAR_Y+TOP_BAR_H,
	MID_BAR_H = BOTTOM_BAR_Y-MID_BAR_Y,
	MID_BAR_W = SCREEN_WIDTH,	

	BAR_LINE_H = 2,
	
	INFO_BAR_X = 0,
	INFO_BAR_H = 24,
	//INFO_BAR_Y = BOTTOM_BAR_Y-INFO_BAR_H-1,
	INFO_BAR_Y = TOP_BAR_Y+TOP_BAR_H+BAR_LINE_H,
	INFO_BAR_W = 480,
	
	TOP_BAR_DISP_GAP = 4,
	
	//模式
	MODE_ICON_X = TOP_BAR_DISP_GAP,
	MODE_ICON_W = 100,//32*3
	MODE_ICON_H = 40,
	MODE_ICON_Y = (TOP_BAR_H-MODE_ICON_H)/2,
	
	MODE_STR_FONT = FONT_32,
	MODE_STR_H = 32,
	MODE_STR_W = (MODE_STR_H*3),//3个汉字 6个英文字
	MODE_STR_X = MODE_ICON_X+(MODE_ICON_W-MODE_STR_W)/2,
	MODE_STR_Y = MODE_ICON_Y+(MODE_ICON_H-MODE_STR_H)/2,
	
	MODE_CHINESE_STR_FONT = FONT_32,
	MODE_CHINESE_STR_H = 32,
	MODE_CHINESE_STR_W = (MODE_CHINESE_STR_H*3),//3个汉字 6个英文字
	MODE_CHINESE_STR_X = MODE_ICON_X+(MODE_ICON_W-MODE_CHINESE_STR_W)/2,
	MODE_CHINESE_STR_Y = MODE_ICON_Y+(MODE_ICON_H-MODE_CHINESE_STR_H)/2,
	
	//币种
	CURRENCY_ICON_X = 4,
	CURRENCY_ICON_W = 50,//24*3 英文3*12
	CURRENCY_ICON_H = 28,
	CURRENCY_ICON_Y = (TOP_BAR_H-CURRENCY_ICON_H)/2,	
	
	CURRENCY_FONT = FONT_24,
	CURRENCY_H = 24,
	CURRENCY_W = (CURRENCY_H/2*3),//英文3*16
	CURRENCY_X = CURRENCY_ICON_X+(CURRENCY_ICON_W-CURRENCY_W)/2,
	CURRENCY_Y = CURRENCY_ICON_Y+(CURRENCY_ICON_H-CURRENCY_H)/2,
	
	CURRENCY_CHINESE_FONT = FONT_32,
	CURRENCY_CHINESE_H = 32,
	CURRENCY_CHINESE_W = (CURRENCY_CHINESE_H*3),//英文3*16
	CURRENCY_CHINESE_X = CURRENCY_ICON_X+(CURRENCY_ICON_W-CURRENCY_CHINESE_W)/2,
	CURRENCY_CHINESE_Y = CURRENCY_ICON_Y+(CURRENCY_ICON_H-CURRENCY_CHINESE_H)/2,
	
	//累加
	ADD_ICON_X = SCREEN_WIDTH - 44*4-TOP_BAR_DISP_GAP*4,//CURRENCY_X + CURRENCY_W + TOP_BAR_DISP_GAP,
	ADD_ICON_W = 44,
	ADD_ICON_H = 44,
	ADD_ICON_Y = (TOP_BAR_H-ADD_ICON_H)/2,
	
	ADD_STR_FONT = FONT_24,
	ADD_STR_H = 24,
	ADD_STR_W = (ADD_STR_H/2*3),
	ADD_STR_X = ADD_ICON_X+(ADD_ICON_W-ADD_STR_W)/2,
	ADD_STR_Y = ADD_ICON_Y+(ADD_ICON_H-ADD_STR_H)/2,
	
	ADD_CHINESE_STR_FONT = FONT_16,
	ADD_CHINESE_STR_H = 16,
	ADD_CHINESE_STR_W = (ADD_CHINESE_STR_H*2),
	ADD_CHINESE_STR_X = ADD_ICON_X+(ADD_ICON_W-ADD_CHINESE_STR_W)/2,
	ADD_CHINESE_STR_Y = ADD_ICON_Y+(ADD_ICON_H-ADD_CHINESE_STR_H)/2,
	
	FACE_ICON_X = ADD_ICON_X + ADD_ICON_W + TOP_BAR_DISP_GAP,
	FACE_ICON_W = 44,
	FACE_ICON_H = 44,
	FACE_ICON_Y = (TOP_BAR_H-FACE_ICON_H)/2,	
	//面向 方向
	FACE_STR_FONT = FONT_16,
	FACE_STR_H = 16,
	FACE_STR_W = (FACE_STR_H/2*4),
	FACE_STR_X = FACE_ICON_X+(FACE_ICON_W-FACE_STR_W)/2,
	FACE_STR_Y = FACE_ICON_Y+ (FACE_ICON_H-2*FACE_STR_H)/2,
	
	FACE_CHINESE_STR_FONT = FONT_16,
	FACE_CHINESE_STR_H = 16,
	FACE_CHINESE_STR_W = (FACE_STR_H*2),
	FACE_CHINESE_STR_X = FACE_ICON_X+(FACE_ICON_W-FACE_CHINESE_STR_W)/2,
	FACE_CHINESE_STR_Y = FACE_ICON_Y+ (FACE_ICON_H-2*FACE_CHINESE_STR_H)/2,

	ORI_STR_FONT = FONT_16,
	ORI_STR_H = 16,
	ORI_STR_W = (ORI_STR_H/2*4),
	ORI_STR_X = FACE_STR_X,
	ORI_STR_Y = FACE_STR_Y+FACE_STR_H,
	
	ORI_CHINESE_STR_FONT = FONT_16,
	ORI_CHINESE_STR_H = 16,
	ORI_CHINESE_STR_W = (ORI_CHINESE_STR_H*2),
	ORI_CHINESE_STR_X = FACE_CHINESE_STR_X,
	ORI_CHINESE_STR_Y = FACE_CHINESE_STR_Y+FACE_CHINESE_STR_H,
		
	AUTO_ICON_X = FACE_ICON_X + FACE_ICON_W + TOP_BAR_DISP_GAP,
	AUTO_ICON_W = 44,
	AUTO_ICON_H = 44,
	AUTO_ICON_Y = (TOP_BAR_H-AUTO_ICON_H)/2,
	//手动
	AUTO_STR_FONT = FONT_16,
	AUTO_STR_H = 16,
	AUTO_STR_W = (AUTO_STR_H/2*4),
	AUTO_STR_X = AUTO_ICON_X+(AUTO_ICON_W-AUTO_STR_W)/2,
	AUTO_STR_Y = AUTO_ICON_Y+(ADD_ICON_H-AUTO_STR_H)/2,
	
	AUTO_CHINESE_STR_FONT = FONT_16,
	AUTO_CHINESE_STR_H = 16,
	AUTO_CHINESE_STR_W = (AUTO_CHINESE_STR_H*2),
	AUTO_CHINESE_STR_X = AUTO_ICON_X+(AUTO_ICON_W-AUTO_CHINESE_STR_W)/2,
	AUTO_CHINESE_STR_Y = AUTO_ICON_Y+(ADD_ICON_H-AUTO_CHINESE_STR_H)/2,
	
	//速度
	SPEED_ICON_X = AUTO_ICON_X + AUTO_ICON_W + TOP_BAR_DISP_GAP,
	SPEED_ICON_W = 44,
	SPEED_ICON_H = 44,
	SPEED_ICON_Y = (TOP_BAR_H-SPEED_ICON_H)/2,
	
	SPEED_STR_FONT = FONT_16,
	SPEED_STR_H = 16,
	SPEED_STR_W = (SPEED_STR_H*4/2),
	SPEED_STR_X = SPEED_ICON_X+(SPEED_ICON_W-SPEED_STR_W)/2,
	SPEED_STR_Y = SPEED_ICON_Y+ (SPEED_ICON_H-2*SPEED_STR_H)/2,
	
	SPEED_CHINESE_STR_FONT = FONT_16,
	SPEED_CHINESE_STR_H = 16,
	SPEED_CHINESE_STR_W = (SPEED_CHINESE_STR_H*2),
	SPEED_CHINESE_STR_X = SPEED_ICON_X+(SPEED_ICON_W-SPEED_CHINESE_STR_W)/2,
	SPEED_CHINESE_STR_Y = SPEED_ICON_Y+ (SPEED_ICON_H-2*SPEED_CHINESE_STR_H)/2,
	//4个字符用4个
	
	SPEED_VALUE_X = SPEED_STR_X,
	SPEED_VALUE_FONT = FONT_16,
	SPEED_VALUE_H = 16,
	SPEED_VALUE_Y = SPEED_STR_Y+SPEED_STR_H,
	SPEED_VALUE_W = (SPEED_STR_H*4/2),//SPEED
	
	//时间
	
	//预置数
	
	BATCH_STR_X = 0,
	BATCH_STR_FONT = FONT_32,
	BATCH_STR_H = 32,
	BATCH_STR_Y = BOTTOM_BAR_Y + (BOTTOM_BAR_H -BATCH_STR_H)/2,
	BATCH_STR_W = (BATCH_STR_H*4/2),//BATCH: 预置
	BATCH_VALUE_W = (BATCH_STR_H*4/2),//9999
	
	TEMP_INFO_X = 0,
	TEMP_INFO_FONT = FONT_32,
	TEMP_INFO_H = 32,
	TEMP_INFO_Y = BOTTOM_BAR_Y + (BOTTOM_BAR_H -BATCH_STR_H)/2,	
	
	DATE_STR_FONT = FONT_24,
	DATE_STR_H = 24,
	DATE_STR_Y = BOTTOM_BAR_Y + (BOTTOM_BAR_H -DATE_STR_H*2)/2+DATE_STR_H,
	DATE_STR_W = (DATE_STR_H*10/2),
	DATE_STR_X = SCREEN_WIDTH - DATE_STR_W - 4,

	TIME_STR_FONT = FONT_24,
	TIME_STR_H = 24,
	TIME_STR_Y = BOTTOM_BAR_Y + (BOTTOM_BAR_H -TIME_STR_H*2)/2,
	TIME_STR_W = (TIME_STR_H*8/2),
	TIME_STR_X = DATE_STR_X+TIME_STR_H/2,
	
	BOTTOM_BAR_DISP_GAP = 4,
	
	UDISK_PIC_H = 40,
	UDISK_PIC_W = 40,
	UDISK_PIC_Y = BOTTOM_BAR_Y + (BOTTOM_BAR_H -UDISK_PIC_H)/2,
	UDISK_PIC_X = DATE_STR_X - UDISK_PIC_W - BOTTOM_BAR_DISP_GAP,	
	
	NET_PIC_H = 40,
	NET_PIC_W = 40,
	NET_PIC_Y = BOTTOM_BAR_Y + (BOTTOM_BAR_H -NET_PIC_H)/2,
	NET_PIC_X = UDISK_PIC_X - NET_PIC_W - BOTTOM_BAR_DISP_GAP,	
	
	PRINT_PIC_H = 40,
	PRINT_PIC_W = 32,
	PRINT_PIC_Y = BOTTOM_BAR_Y + (BOTTOM_BAR_H -PRINT_PIC_H)/2,
	PRINT_PIC_X = NET_PIC_X - PRINT_PIC_W - BOTTOM_BAR_DISP_GAP,	
	
	MENU_PIC_H = 40,
	MENU_PIC_W = 28,
	MENU_PIC_Y = BOTTOM_BAR_Y + (BOTTOM_BAR_H -MENU_PIC_H)/2,
	MENU_PIC_X = PRINT_PIC_X - MENU_PIC_W - BOTTOM_BAR_DISP_GAP,	

	//面额
	DENO_STR_FONT = FONT_24,
	DENO_STR_H = 24,
	DENO_CHAR_W = DENO_STR_H/2,
	DENO_STR_W = DENO_CHAR_W*5,
	DENO_STR_X = SCREEN_WIDTH - 16 - DENO_STR_W,
	DENO_STR_Y = 34 + 26,
	
	DENO_NUM_BITS = 5,
	DENO_NUM_STR_FONT = FONT_24,
	DENO_NUM_STR_H = 24,
	DENO_NUM_CHAR_W = DENO_NUM_STR_H/2,
	DENO_NUM_STR_W = DENO_NUM_CHAR_W*5,
	DENO_NUM_X = SCREEN_WIDTH - 16 - DENO_STR_W,
	DENO_NUM_Y = DENO_STR_Y,
	DENO_NUM_TITLE_X = SCREEN_WIDTH - 16 - 7*DENO_CHAR_W - 5*DENO_CHAR_W,
	
	//张数
	DOWN_NOTE_NUM_BITS = 4,
	NOTENUM_FONT = FONT_24,
	NOTENUM_CHAR_W = 12,
	NOTENUM_STR_W = NOTENUM_CHAR_W*DOWN_NOTE_NUM_BITS,
	NOTENUM_H = 24,
	NOTENUM_X = SCREEN_WIDTH - 16 - NOTENUM_STR_W,
	NOTENUM_Y = DENO_STR_Y+40,
	NOTENUM_TITLE_X = DENO_NUM_TITLE_X,
	
	//总金额
	DOWN_NOTE_SUM_BITS = 7,
	NOTESUM_FONT = FONT_24,
	NOTESUM_H = 24,
	NOTESUM_CHAR_W = NOTESUM_H/2,
	NOTESUM_STR_W = NOTESUM_CHAR_W*DOWN_NOTE_SUM_BITS,
	NOTESUM_X = SCREEN_WIDTH - 16 - NOTESUM_STR_W,
	NOTESUM_Y = NOTENUM_Y + 40,
	NOTESUM_TITLE_X = DENO_NUM_TITLE_X,
	
	DETAIL_NOTE_CHART_X = 16,
	DETAIL_NOTE_CHART_Y = 34+2,
	DETAIL_NOTE_CHART_FONT = FONT_16,
	DETAIL_NOTE_CHART_H = 16,
	DETAIL_NOTE_CHART_ONE_ROW_H = 20,
	DETAIL_NOTE_CHART_ONE_COL_W = 8*5+2,
	DETAIL_NOTE_CHART_ROW_NUM = 8,
	DETAIL_NOTE_CHART_COL_NUM = 3,
	
	DETAIL_NOTE_DENO_BITS = 5,
	DETAIL_NOTE_DENO_FONT = FONT_16,
	DETAIL_NOTE_DENO_H = 16,
	DETAIL_NOTE_DENO_CHAR_W = DETAIL_NOTE_DENO_H/2,
	DETAIL_NOTE_DENO_STR_W = DETAIL_NOTE_DENO_CHAR_W*DETAIL_NOTE_DENO_CHAR_W,
	DETAIL_NOTE_DENO_X = SCREEN_WIDTH - 16 - NOTESUM_STR_W,
	DETAIL_NOTE_DENO_Y = NOTENUM_Y + 40,
	
	DETAIL_NOTE_NUM_BITS = 5,
	DETAIL_NOTE_NUM_FONT = FONT_16,
	DETAIL_NOTE_NUM_H = 16,
	DETAIL_NOTE_NUM_CHAR_W = DETAIL_NOTE_NUM_H/2,
	DETAIL_NOTE_NUM_STR_W = DETAIL_NOTE_NUM_CHAR_W*DETAIL_NOTE_NUM_CHAR_W,
	DETAIL_NOTE_NUM_X = SCREEN_WIDTH - 16 - NOTESUM_STR_W,
	DETAIL_NOTE_NUM_Y = NOTENUM_Y + 40,
	
	REJECT_STR_FONT = FONT_24,
	REJECT_STR_H = 24,
	REJECT_CHAR_W = REJECT_STR_H/2,
	REJECT_STR_W = REJECT_CHAR_W*5,
	REJECT_STR_X = 8,
	REJECT_STR_Y = NOTENUM_Y,
	
	REJECT_NUM_STR_FONT = FONT_24,
	REJECT_NUM_STR_H = 24,
	REJECT_NUM_CHAR_W = REJECT_NUM_STR_H/2,
	REJECT_NUM_STR_W = REJECT_NUM_CHAR_W*5,
	REJECT_NUM_X = REJECT_STR_X + REJECT_STR_W,
	REJECT_NUM_Y = REJECT_STR_Y,
	

	
	GZH_STR_FONT = FONT_24,
	GZH_STR_H = 24,
	GZH_CHAR_W = GZH_STR_H/2,
	GZH_STR_W = GZH_CHAR_W*12,
	GZH_STR_X = 8,
	GZH_STR_Y = SCREEN_HEIGHT - BOTTOM_BAR_H - GZH_STR_H - BAR_LINE_H,
	
	DSP_ADJUST_RECT_W = 280,
	DSP_ADJUST_RECT_H = 48,
	DSP_ADJUST_RECT_X = ((SCREEN_WIDTH - DSP_ADJUST_RECT_W)/2),
	DSP_ADJUST_RECT_Y = (BOTTOM_BAR_Y - DSP_ADJUST_RECT_H*2 - 20),
	DSP_ADJUST_CHINESE_STR_X = (DSP_ADJUST_RECT_X + (DSP_ADJUST_RECT_W-32*6)/2),
	DSP_ADJUST_ENGLISH_STR_X =  (DSP_ADJUST_RECT_X + (DSP_ADJUST_RECT_W-16*13)/2),
	DSP_ADJUST_STR_Y  = DSP_ADJUST_RECT_Y + (DSP_ADJUST_RECT_H - 32)/2,
	
	DSP_ADJUST_RECT2_W = 280,
	DSP_ADJUST_RECT2_H = 48,
	DSP_ADJUST_RECT2_X = ((SCREEN_WIDTH - DSP_ADJUST_RECT2_W)/2),
	DSP_ADJUST_RECT2_Y = (BOTTOM_BAR_Y - DSP_ADJUST_RECT2_H - 10),
	DSP_ADJUST2_CHINESE_STR_X = (DSP_ADJUST_RECT2_X + (DSP_ADJUST_RECT2_W-32*6)/2),
	DSP_ADJUST2_ENGLISH_STR_X =  (DSP_ADJUST_RECT2_X + (DSP_ADJUST_RECT2_W-16*13)/2),
	DSP_ADJUST2_STR_Y  = DSP_ADJUST_RECT2_Y + (DSP_ADJUST_RECT2_H - 32)/2,

	LINE1_Y = 0,
	LINE2_Y = 66,
	LINE3_Y = 86,
	LINE4_Y = 260,
	LINE5_Y = 319,
	BAR1_MIDLINE_Y = (LINE2_Y-LINE1_Y)/2,
	
	BAR1_X1 = 136,
	BAR1_X2 = 300,
	BAR3_X1 = 85,
//	BAR4_X1 = 240,
	BAR4_X1 = 218,
	
	WORKMODE_X = BAR1_X1+2,
	WORKMODE_Y = 3,
	

	
// 	BATCH_NUM_X = BAR1_X2+2 + 32*2+8,
// 	BATCH_NUM_Y = 0,
// 	BATCH_NUM_X = 6*8,
// 	BATCH_NUM_Y = 320-16,
	
	PAPERDEAL_STR_X = 1,
	PAPERDEAL_STR_Y = LINE3_Y+1,

	MANUAL_STR_X = 1,
	MANUAL_STR_Y = LINE3_Y+1+64,
	
	FITNESS_STR_X = 1,
	FITNESS_STR_Y = LINE3_Y+1+96,
	
	
	REJECT_ZHANG_X = BAR1_X2+2+48+32,
	REJECT_ZHANG_Y = BAR1_MIDLINE_Y + 8,
	
// 	CURRENCY_X = 479-8*6-2,
// 	CURRENCY_ENGLISH_X = 479-8*6-2,
// 	CURRENCY_Y = 0,
	
// 	SPEED_STR_X = 479-8*6-2,
// 	SPEED_STR_Y = 16,


	
	CF_STR_X = 475-26-20,
	CF_STR_Y = BAR1_MIDLINE_Y + 8,		
	
	CF_COLOR_X = 475-26,
	CF_COLOR_Y = BAR1_MIDLINE_Y + 3,	
	


	
	NOTENUM_ZHANG_X = 475-32,
	NOTENUM_ZHANG_Y = 245 - 32,		
	
	NOTESUM_YUAN_X = 475-48,
	NOTESUM_YUAN_Y = LINE4_Y + 16,	
};

#define MAX_ITEM_STR_NUM 18

u8 * const CURRENCY_TITLE_STR_ENGLISH = \
"40|\
CNY|USD|EUR|JPY|GBP|HKD|AUD|CAD|\
SGD|KRW|TWD|RUB|GHC|UAH|NGN|ALL|\
MKD|MOP|CHF|SEK|KZT|TRY|INR|VND|\
MYR|BRL|TJS|CNY|BGN|MAD|LYD|LAK|\
ZAR|ZWD|   |   |   |   |   |   |\
";
u8 * const CURRENCY_MENU_TITLE_STR_ENGLISH = "SELECT CURRENCY";

u8 * const CURRENCY_TITLE_STR_CHINESE = \
"40|\
人民币| 美元 | 欧元 | 日元 | 英镑 | 港币 | 澳币 | 加币 |\
SGD|KRW|TWD|RUB|GHC|UAH|NGN|ALL|\
MKD|MOP|CHF|SEK|KZT|TRY|INR|VND|\
MYR|BRL|TJS|CNY|BGN|MAD|LYD|LAK|\
ZAR|ZWD|   |   |   |   |   |   |\
";

#endif
