/*******************************************************

*******************************************************/

/*防止重复引用 */
#ifndef _DISP_H_
#define _DISP_H_

/*包含文件 */
#include "system.h"
#include "disp.h"

u8 CurrentFont;
u16 CurrentBackColor;
u16 CurrentPenColor;
u8 LastFont;
char TFTStr[300] = {0};
char TFTTmpStr[300] = {0};

extern void uart_SendDataToUart1(u8 * pData,u16 len);
#endif
