#ifndef __USERTYPE_H__
#define __USERTYPE_H__

typedef  unsigned char uchar;
typedef  unsigned int uint;

typedef unsigned char u8;
typedef unsigned char U8;
typedef char s8;
typedef char S8;
typedef unsigned char uint8;


typedef unsigned int u16;
typedef unsigned int uint16;
typedef unsigned int U16;
typedef int s16;
typedef int S16;

typedef unsigned long u32;
typedef unsigned long uint32;
typedef unsigned long U32;
typedef long s32;
typedef long S32;

typedef bit BOOLEAN;

#define TRUE (1==1)
#define FALSE (!TRUE)
#define true TRUE
#define false FALSE
#define equal ==
#define and &&
#define or ||
#define band &
#define bor |
#define ArrayLen(x) (sizeof(x)/sizeof(x[0]))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define RowNum(x) (sizeof(x)/sizeof(x[0]))
#define ColNum(x) (sizeof(x[0]))
#define nop() _nop_()
#define HighByte(x) ((u8)(x>>8))
#define LowByte(x) ((u8)(x))


#endif
