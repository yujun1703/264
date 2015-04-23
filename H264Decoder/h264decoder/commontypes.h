#ifndef _COMMO_N_TYPES__ 
#define _COMMO_N_TYPES__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <math.h>

#define snprintf _snprintf
#define __WORDSIZE	32

#if !defined __cplusplus || defined __STDC_CONSTANT_MACROS

/* Signed.  */
#define INT8_C(c)	c
#define INT16_C(c)	c
#define INT32_C(c)	c
#if __WORDSIZE == 64
#define INT64_C(c)	c ## L
#else
#define INT64_C(c)	c ## LL
#endif

/* Unsigned.  */
#define UINT8_C(c)	c
#define UINT16_C(c)	c
#define UINT32_C(c)	c ## U
#if __WORDSIZE == 64
#define UINT64_C(c)	c ## UL
#else
#define UINT64_C(c)	c ## ULL
#endif

/* Maximal type.  */
#if __WORDSIZE == 64
#define INTMAX_C(c)	c ## L
#define UINTMAX_C(c)	c ## UL
#else
#define INTMAX_C(c)	c ## LL
#define UINTMAX_C(c)	c ## ULL
#endif

#endif	/* C++ && constant macros */

#define inline __inline
//#define av_always_inline __inline
#define av_noinline
#define av_pure
#define av_const
#define av_cold
#define attribute_deprecated
#define av_unused

//c99 keyword
#define restrict
#if defined (_WIN32)
typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef signed __int64      int64_t;
typedef unsigned __int64    uint64_t;
#else if (TARGET_OS_IPHONE && TARGET_OS_MAC)
#include <stdint.h>
//typedef int64_t             int64_t;
//typedef uint64_t            uint64_t;
#endif

#define HAVE_AV_CONFIG_H

#endif