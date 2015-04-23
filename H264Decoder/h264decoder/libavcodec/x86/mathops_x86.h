/*
 * simple math operations
 * Copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at> et al
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_X86_MATHOPS_H
#define AVCODEC_X86_MATHOPS_H

#include "config.h"
#include "libavutil/common.h"

////#if ARCH_X86_32
////
////#define MULL MULL
////__declspec(naked) static av_always_inline av_const int MULL(int a, int b, unsigned shift)
////{
////    __asm {
////        mov    ecx,DWORD PTR [esp+0xc]
////        mov    eax,DWORD PTR [esp+0x4]
////        imul   DWORD PTR [esp+0x8]    
////        shrd   eax,edx,cl             
////            ret                           
////
////    }
////}
////
////#define MULH MULH
////__declspec(naked) static av_always_inline av_const int MULH(int a, int b)
////{
////    __asm {
////        mov    eax,DWORD PTR [esp+0x4] 
////        imul   DWORD PTR [esp+0x8]     
////        mov    eax,edx                 
////            ret                            
////
////    }
////}
////
////#define MUL64 MUL64
////__declspec(naked) static av_always_inline av_const int64_t MUL64(int a, int b)
////{
////    __asm {
////        mov    eax,DWORD PTR [esp+0x4] 
////        imul   DWORD PTR [esp+0x8]     
////        ret                            
////
////    }
////}
////
////#endif /* ARCH_X86_32 */

#if HAVE_CMOV
/* median of 3 */
#define mid_pred mid_pred
static inline av_const int mid_pred(int a, int b, int c)
{
    int i=b;
    __asm__ volatile(
        "cmp    %2, %1 \n\t"
        "cmovg  %1, %0 \n\t"
        "cmovg  %2, %1 \n\t"
        "cmp    %3, %1 \n\t"
        "cmovl  %3, %1 \n\t"
        "cmp    %1, %0 \n\t"
        "cmovg  %1, %0 \n\t"
        :"+&r"(i), "+&r"(a)
        :"r"(b), "r"(c)
    );
    return i;
}
#endif

#if HAVE_CMOV
#define COPY3_IF_LT(x, y, a, b, c, d)\
__asm__ volatile(\
    "cmpl  %0, %3       \n\t"\
    "cmovl %3, %0       \n\t"\
    "cmovl %4, %1       \n\t"\
    "cmovl %5, %2       \n\t"\
    : "+&r" (x), "+&r" (a), "+r" (c)\
    : "r" (y), "r" (b), "r" (d)\
);
#endif

// avoid +32 for shift optimization (gcc should do that ...)
#define NEG_SSR32 NEG_SSR32
__declspec(naked) static inline  int32_t NEG_SSR32( int32_t a, int8_t s)
{
    __asm {
        movzx  ecx,BYTE PTR [esp+0x8]  
        mov    eax,DWORD PTR [esp+0x4] 
        neg    ecx                     
            sar    eax,cl                  
            ret                            

    }
}

#define NEG_USR32 NEG_USR32
__declspec(naked) static inline uint32_t NEG_USR32(uint32_t a, int8_t s)
{
    __asm {
        movzx  ecx,BYTE PTR [esp+0x8] 
        mov    eax,DWORD PTR [esp+0x4]
        neg    ecx                    
            shr    eax,cl                 
            ret                           

    }
}

#endif /* AVCODEC_X86_MATHOPS_H */
