/*
 * MMX optimized DSP utils
 * Copyright (c) 2007  Aurelien Jacobs <aurel@gnuage.org>
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

#ifndef AVCODEC_X86_DSPUTIL_MMX_H
#define AVCODEC_X86_DSPUTIL_MMX_H

//#include <stdint.h>
#include "commontypes.h"
#include "libavcodec/dsputil.h"
#include "libavutil/x86_cpu.h"

typedef struct { uint64_t a, b; } xmm_reg;

DECLARE_ALIGNED(8,  extern const uint64_t, ff_bone);// = 0x0101010101010101ULL;
DECLARE_ALIGNED(8,  extern const uint64_t, ff_wtwo) ;// = 0x0002000200020002ULL;

//DECLARE_ALIGNED(16, extern const uint64_t, ff_pdw_80000000)[2] ;// = {0x8000000080000000ULL, 0x8000000080000000ULL};

DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_1  ) ;// = {0x0001000100010001ULL, 0x0001000100010001ULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_2  ) ;// = {0x0002000200020002ULL, 0x0002000200020002ULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_3  ) ;// = {0x0003000300030003ULL, 0x0003000300030003ULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_4  ) ;// = {0x0004000400040004ULL, 0x0004000400040004ULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_5  ) ;// = {0x0005000500050005ULL, 0x0005000500050005ULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_8  ) ;// = {0x0008000800080008ULL, 0x0008000800080008ULL};
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_9  ) ;// = {0x0009000900090009ULL, 0x0009000900090009ULL};
DECLARE_ALIGNED(8,  extern const uint64_t, ff_pw_15 ) ;// = 0x000F000F000F000FULL;
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_16 ) ;// = {0x0010001000100010ULL, 0x0010001000100010ULL};
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_17 ) ;// = {0x0011001100110011ULL, 0x0011001100110011ULL};
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_18 ) ;// = {0x0012001200120012ULL, 0x0012001200120012ULL};
DECLARE_ALIGNED(8,  extern const uint64_t, ff_pw_20 ) ;// = 0x0014001400140014ULL;
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_27 ) ;// = {0x001B001B001B001BULL, 0x001B001B001B001BULL};
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_28 ) ;// = {0x001C001C001C001CULL, 0x001C001C001C001CULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_32 ) ;// = {0x0020002000200020ULL, 0x0020002000200020ULL};
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pw_42 ) ;// = 0x002A002A002A002AULL;
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pw_53 ) ;// = 0x0035003500350035ULL;
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_63 ) ;// = {0x003F003F003F003FULL, 0x003F003F003F003FULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_64 ) ;// = {0x0040004000400040ULL, 0x0040004000400040ULL};
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pw_96 ) ;// = 0x0060006000600060ULL;
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pw_128) ;// = 0x0080008000800080ULL;
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pw_255) ;// = 0x00ff00ff00ff00ffULL;
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_512) ;// = {0x0200020002000200ULL, 0x0200020002000200ULL};
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pw_1019);// = {0x03FB03FB03FB03FBULL, 0x03FB03FB03FB03FBULL};

DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pb_0  ) ;// = {0x0000000000000000ULL, 0x0000000000000000ULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pb_1  ) ;// = {0x0101010101010101ULL, 0x0101010101010101ULL};
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pb_3  ) ;// = {0x0303030303030303ULL, 0x0303030303030303ULL};
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pb_4  ) ;// = {0x0404040404040404ULL, 0x0404040404040404ULL};
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pb_7  ) ;// = 0x0707070707070707ULL;
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pb_1F ) ;// = 0x1F1F1F1F1F1F1F1FULL;
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pb_3F ) ;// = 0x3F3F3F3F3F3F3F3FULL;
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pb_80 ) ;// = {0x8080808080808080ULL, 0x8080808080808080ULL};
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pb_81 ) ;// = 0x8181818181818181ULL;
DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pb_A1 ) ;// = {0xA1A1A1A1A1A1A1A1ULL, 0xA1A1A1A1A1A1A1A1ULL};
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pb_F8 ) ;// = {0xF8F8F8F8F8F8F8F8ULL, 0xF8F8F8F8F8F8F8F8ULL};
//DECLARE_ALIGNED(8,  extern const uint64_t, ff_pb_FC ) ;// = 0xFCFCFCFCFCFCFCFCULL;
//DECLARE_ALIGNED(16, extern const xmm_reg,  ff_pb_FE ) ;// = {0xFEFEFEFEFEFEFEFEULL, 0xFEFEFEFEFEFEFEFEULL};

//DECLARE_ALIGNED(16, extern const double, ff_pd_1)[2] ;// = { 1.0, 1.0 };
//DECLARE_ALIGNED(16, extern const double, ff_pd_2)[2] ;// = { 2.0, 2.0 };

DECLARE_ALIGNED(8, extern const uint64_t, ff_pb_3_1);
DECLARE_ALIGNED(16, extern unsigned char, scan8_mem[16*3]);

DECLARE_ALIGNED(16, extern short, pw_pixel_max[8]);

#if 0

extern const uint64_t ff_bone;
extern const uint64_t ff_wtwo;

extern const uint64_t ff_pdw_80000000[2];

extern const xmm_reg  ff_pw_3;
extern const xmm_reg  ff_pw_4;
extern const xmm_reg  ff_pw_5;
extern const xmm_reg  ff_pw_8;
extern const uint64_t ff_pw_15;
extern const xmm_reg  ff_pw_16;
extern const xmm_reg  ff_pw_18;
extern const uint64_t ff_pw_20;
extern const xmm_reg  ff_pw_27;
extern const xmm_reg  ff_pw_28;
extern const xmm_reg  ff_pw_32;
extern const uint64_t ff_pw_42;
extern const uint64_t ff_pw_53;
extern const xmm_reg  ff_pw_63;
extern const xmm_reg  ff_pw_64;
extern const uint64_t ff_pw_96;
extern const uint64_t ff_pw_128;
extern const uint64_t ff_pw_255;

extern const xmm_reg  ff_pb_1;
extern const xmm_reg  ff_pb_3;
extern const uint64_t ff_pb_7;
extern const uint64_t ff_pb_1F;
extern const uint64_t ff_pb_3F;
extern const uint64_t ff_pb_81;
extern const xmm_reg  ff_pb_A1;
extern const xmm_reg  ff_pb_F8;
extern const uint64_t ff_pb_FC;
extern const xmm_reg  ff_pb_FE;

extern const double ff_pd_1[2];
extern const double ff_pd_2[2];
#endif

//#define LOAD4(stride,in,a,b,c,d)\
//    "movq 0*"#stride"+"#in", "#a"\n\t"\
//    "movq 1*"#stride"+"#in", "#b"\n\t"\
//    "movq 2*"#stride"+"#in", "#c"\n\t"\
//    "movq 3*"#stride"+"#in", "#d"\n\t"
//
//#define STORE4(stride,out,a,b,c,d)\
//    "movq "#a", 0*"#stride"+"#out"\n\t"\
//    "movq "#b", 1*"#stride"+"#out"\n\t"\
//    "movq "#c", 2*"#stride"+"#out"\n\t"\
//    "movq "#d", 3*"#stride"+"#out"\n\t"
//
///* in/out: mma=mma+mmb, mmb=mmb-mma */
//#define SUMSUB_BA( a, b ) \
//    "paddw "#b", "#a" \n\t"\
//    "paddw "#b", "#b" \n\t"\
//    "psubw "#a", "#b" \n\t"
//
//#define SBUTTERFLY(a,b,t,n,m)\
//    "mov" #m " " #a ", " #t "         \n\t" /* abcd */\
//    "punpckl" #n " " #b ", " #a "     \n\t" /* aebf */\
//    "punpckh" #n " " #b ", " #t "     \n\t" /* cgdh */\
//
//#define TRANSPOSE4(a,b,c,d,t)\
//    SBUTTERFLY(a,b,t,wd,q) /* a=aebf t=cgdh */\
//    SBUTTERFLY(c,d,b,wd,q) /* c=imjn b=kolp */\
//    SBUTTERFLY(a,c,d,dq,q) /* a=aeim d=bfjn */\
//    SBUTTERFLY(t,b,c,dq,q) /* t=cgko c=dhlp */

//static inline void transpose4x4(uint8_t *dst, uint8_t *src, x86_reg dst_stride, x86_reg src_stride){
//    //__asm__ volatile( //FIXME could save 1 instruction if done as 8x4 ...
//    //    "movd  (%1), %%mm0              \n\t"
//    //    "add   %3, %1                   \n\t"
//    //    "movd  (%1), %%mm1              \n\t"
//    //    "movd  (%1,%3,1), %%mm2         \n\t"
//    //    "movd  (%1,%3,2), %%mm3         \n\t"
//    //    "punpcklbw %%mm1, %%mm0         \n\t"
//    //    "punpcklbw %%mm3, %%mm2         \n\t"
//    //    "movq %%mm0, %%mm1              \n\t"
//    //    "punpcklwd %%mm2, %%mm0         \n\t"
//    //    "punpckhwd %%mm2, %%mm1         \n\t"
//    //    "movd  %%mm0, (%0)              \n\t"
//    //    "add   %2, %0                   \n\t"
//    //    "punpckhdq %%mm0, %%mm0         \n\t"
//    //    "movd  %%mm0, (%0)              \n\t"
//    //    "movd  %%mm1, (%0,%2,1)         \n\t"
//    //    "punpckhdq %%mm1, %%mm1         \n\t"
//    //    "movd  %%mm1, (%0,%2,2)         \n\t"
//
//    //    :  "+&r" (dst),
//    //       "+&r" (src)
//    //    :  "r" (dst_stride),
//    //       "r" (src_stride)
//    //    :  "memory"
//    //);
//}
//
// e,f,g,h can be memory
// out: a,d,t,c
//#define TRANSPOSE8x4(a,b,c,d,e,f,g,h,t)\
//    "punpcklbw " #e ", " #a " \n\t" /* a0 e0 a1 e1 a2 e2 a3 e3 */\
//    "punpcklbw " #f ", " #b " \n\t" /* b0 f0 b1 f1 b2 f2 b3 f3 */\
//    "punpcklbw " #g ", " #c " \n\t" /* c0 g0 c1 g1 c2 g2 d3 g3 */\
//    "punpcklbw " #h ", " #d " \n\t" /* d0 h0 d1 h1 d2 h2 d3 h3 */\
//    SBUTTERFLY(a, b, t, bw, q)   /* a= a0 b0 e0 f0 a1 b1 e1 f1 */\
//                                 /* t= a2 b2 e2 f2 a3 b3 e3 f3 */\
//    SBUTTERFLY(c, d, b, bw, q)   /* c= c0 d0 g0 h0 c1 d1 g1 h1 */\
//                                 /* b= c2 d2 g2 h2 c3 d3 g3 h3 */\
//    SBUTTERFLY(a, c, d, wd, q)   /* a= a0 b0 c0 d0 e0 f0 g0 h0 */\
//                                 /* d= a1 b1 c1 d1 e1 f1 g1 h1 */\
//    SBUTTERFLY(t, b, c, wd, q)   /* t= a2 b2 c2 d2 e2 f2 g2 h2 */\
//                                 /* c= a3 b3 c3 d3 e3 f3 g3 h3 */

////////#if ARCH_X86_64
////////// permutes 01234567 -> 05736421
////////#define TRANSPOSE8(a,b,c,d,e,f,g,h,t)\
////////    SBUTTERFLY(a,b,%%xmm8,wd,dqa)\
////////    SBUTTERFLY(c,d,b,wd,dqa)\
////////    SBUTTERFLY(e,f,d,wd,dqa)\
////////    SBUTTERFLY(g,h,f,wd,dqa)\
////////    SBUTTERFLY(a,c,h,dq,dqa)\
////////    SBUTTERFLY(%%xmm8,b,c,dq,dqa)\
////////    SBUTTERFLY(e,g,b,dq,dqa)\
////////    SBUTTERFLY(d,f,g,dq,dqa)\
////////    SBUTTERFLY(a,e,f,qdq,dqa)\
////////    SBUTTERFLY(%%xmm8,d,e,qdq,dqa)\
////////    SBUTTERFLY(h,b,d,qdq,dqa)\
////////    SBUTTERFLY(c,g,b,qdq,dqa)\
////////    "movdqa %%xmm8, "#g"              \n\t"
////////#else
////////#define TRANSPOSE8(a,b,c,d,e,f,g,h,t)\
////////    "movdqa "#h", "#t"                \n\t"\
////////    SBUTTERFLY(a,b,h,wd,dqa)\
////////    "movdqa "#h", 16"#t"              \n\t"\
////////    "movdqa "#t", "#h"                \n\t"\
////////    SBUTTERFLY(c,d,b,wd,dqa)\
////////    SBUTTERFLY(e,f,d,wd,dqa)\
////////    SBUTTERFLY(g,h,f,wd,dqa)\
////////    SBUTTERFLY(a,c,h,dq,dqa)\
////////    "movdqa "#h", "#t"                \n\t"\
////////    "movdqa 16"#t", "#h"              \n\t"\
////////    SBUTTERFLY(h,b,c,dq,dqa)\
////////    SBUTTERFLY(e,g,b,dq,dqa)\
////////    SBUTTERFLY(d,f,g,dq,dqa)\
////////    SBUTTERFLY(a,e,f,qdq,dqa)\
////////    SBUTTERFLY(h,d,e,qdq,dqa)\
////////    "movdqa "#h", 16"#t"              \n\t"\
////////    "movdqa "#t", "#h"                \n\t"\
////////    SBUTTERFLY(h,b,d,qdq,dqa)\
////////    SBUTTERFLY(c,g,b,qdq,dqa)\
////////    "movdqa 16"#t", "#g"              \n\t"
////////#endif

//#define MOVQ_WONE(regd) \
//    __asm__ volatile ( \
//    "pcmpeqd %%" #regd ", %%" #regd " \n\t" \
//    "psrlw $15, %%" #regd ::)

//void ff_dsputilenc_init_mmx(DSPContext* c, AVCodecContext *avctx);
//void ff_dsputil_init_pix_mmx(DSPContext* c, AVCodecContext *avctx);

//////void ff_add_pixels_clamped_mmx(const DCTELEM *block, uint8_t *pixels, int line_size);
//////void ff_put_pixels_clamped_mmx(const DCTELEM *block, uint8_t *pixels, int line_size);
//////void ff_put_signed_pixels_clamped_mmx(const DCTELEM *block, uint8_t *pixels, int line_size);

//void ff_put_cavs_qpel8_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride);
//void ff_avg_cavs_qpel8_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride);
//void ff_put_cavs_qpel16_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride);
//void ff_avg_cavs_qpel16_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride);

//void ff_put_vc1_mspel_mc00_mmx(uint8_t *dst, const uint8_t *src, int stride, int rnd);
//void ff_avg_vc1_mspel_mc00_mmx2(uint8_t *dst, const uint8_t *src, int stride, int rnd);

//void ff_mmx_idct(DCTELEM *block);
//void ff_mmxext_idct(DCTELEM *block);


//void ff_deinterlace_line_mmx(uint8_t *dst,
//                             const uint8_t *lum_m4, const uint8_t *lum_m3,
//                             const uint8_t *lum_m2, const uint8_t *lum_m1,
//                             const uint8_t *lum,
//                             int size);

//void ff_deinterlace_line_inplace_mmx(const uint8_t *lum_m4,
//                                     const uint8_t *lum_m3,
//                                     const uint8_t *lum_m2,
//                                     const uint8_t *lum_m1,
//                                     const uint8_t *lum, int size);

#endif /* AVCODEC_X86_DSPUTIL_MMX_H */
