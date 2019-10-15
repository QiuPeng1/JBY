#ifndef __USERTYPE_H__
#define __USERTYPE_H__

typedef  unsigned char uchar;
typedef  unsigned int uint;

typedef unsigned char u8;
typedef unsigned char U8;
typedef char s8;
typedef char S8;
typedef unsigned char uint8;


typedef unsigned short u16;
typedef unsigned short uint16;
typedef unsigned short U16;
typedef short s16;
typedef short S16;

typedef unsigned int u32;
typedef unsigned int uint32;
typedef unsigned int U32;
typedef int s32;
typedef int S32;
typedef int I32;

#define ArrayLen(x) (sizeof(x)/sizeof(x[0]))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define RowNum(x) (sizeof(x)/sizeof(x[0]))
#define ColNum(x) (sizeof(x[0]))
#define HighByte(x) ((u8)(x>>8))
#define LowByte(x) ((u8)(x))
#define BIN_DATA(a,b,c,d,e,f,g,h) (a<<7 | b<<6 | c<<5 | d<<4 | e<<3 | f<<2 | g<<1 | h<<0)

#define HUAN_HANG_STR "\r\n"
//#define code const

#endif
