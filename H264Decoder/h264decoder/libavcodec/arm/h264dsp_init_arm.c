/*
 * Copyright (c) 2010 Mans Rullgard <mans@mansr.com>
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

#include <stdint.h>

#include "libavcodec/dsputil.h"
#include "libavcodec/h264dsp.h"

void ff_h264_v_loop_filter_luma_neon(uint8_t *pix, int stride, int alpha,
                                     int beta, int8_t *tc0);
void ff_h264_h_loop_filter_luma_neon(uint8_t *pix, int stride, int alpha,
                                     int beta, int8_t *tc0);
void ff_h264_v_loop_filter_chroma_neon(uint8_t *pix, int stride, int alpha,
                                       int beta, int8_t *tc0);
void ff_h264_h_loop_filter_chroma_neon(uint8_t *pix, int stride, int alpha,
                                       int beta, int8_t *tc0);

void ff_weight_h264_pixels_16_neon(uint8_t *dst, int stride, int height,
                                   int log2_den, int weight, int offset);
void ff_weight_h264_pixels_8_neon(uint8_t *dst, int stride, int height,
                                  int log2_den, int weight, int offset);
void ff_weight_h264_pixels_4_neon(uint8_t *dst, int stride, int height,
                                  int log2_den, int weight, int offset);

void ff_biweight_h264_pixels_16_neon(uint8_t *dst, uint8_t *src, int stride,
                                     int height, int log2_den, int weightd,
                                     int weights, int offset);
void ff_biweight_h264_pixels_8_neon(uint8_t *dst, uint8_t *src, int stride,
                                    int height, int log2_den, int weightd,
                                    int weights, int offset);
void ff_biweight_h264_pixels_4_neon(uint8_t *dst, uint8_t *src, int stride,
                                    int height, int log2_den, int weightd,
                                    int weights, int offset);

extern void ff_h264_idct_add_neon(uint8_t *dst, DCTELEM *block, int stride);
extern void ff_h264_idct_dc_add_neon(uint8_t *dst, DCTELEM *block, int stride);
extern void ff_h264_idct8_add_neon(uint8_t *dst, DCTELEM *block, int stride);
extern void ff_h264_idct8_dc_add_neon(uint8_t *dst, DCTELEM *block, int stride);
extern const uint8_t scan8[16*3+3];
#define dctcoef int16_t
#define pixel  uint8_t
void ff_h264_idct_add16_neon(uint8_t *dst, const int *block_offset,
                             DCTELEM *block, int stride,
                             const uint8_t nnzc[15*8])
{
    int i;
    for(i=0; i<16; i++){
        int nnz = nnzc[ scan8[i] ];
        if(nnz){
            if(nnz==1 && ((dctcoef*)block)[i*16]) ff_h264_idct_dc_add_neon(dst + block_offset[i], block + i*16*sizeof(pixel), stride);
            else                                  ff_h264_idct_add_neon   (dst + block_offset[i], block + i*16*sizeof(pixel), stride);
        }
    }
}
void ff_h264_idct_add16intra_neon(uint8_t *dst, const int *block_offset,
                                  DCTELEM *block, int stride,
                                  const uint8_t nnzc[15*8])
{
    int i;
    for(i=0; i<16; i++){
        if(nnzc[ scan8[i] ])             ff_h264_idct_add_neon   (dst + block_offset[i], block + i*16*sizeof(pixel), stride);
        else if(((dctcoef*)block)[i*16]) ff_h264_idct_dc_add_neon(dst + block_offset[i], block + i*16*sizeof(pixel), stride);
    }
}
void ff_h264_idct_add8_neon(uint8_t **dest, const int *block_offset,
                            DCTELEM *block, int stride,
                            const uint8_t nnzc[15*8])
{
    int i, j;
    for(j=1; j<3; j++){
        for(i=j*16; i<j*16+4; i++){
            if(nnzc[ scan8[i] ])
                ff_h264_idct_add_neon   (dest[j-1] + block_offset[i], block + i*16*sizeof(pixel), stride);
            else if(((dctcoef*)block)[i*16])
                ff_h264_idct_dc_add_neon(dest[j-1] + block_offset[i], block + i*16*sizeof(pixel), stride);
        }
    }
}
void ff_h264_idct8_add4_neon(uint8_t *dst, const int *block_offset,
                             DCTELEM *block, int stride,
                             const uint8_t nnzc[15*8])
{
    int i;
    for(i=0; i<16; i+=4){
        int nnz = nnzc[ scan8[i] ];
        if(nnz){
            if(nnz==1 && ((dctcoef*)block)[i*16]) ff_h264_idct8_dc_add_neon(dst + block_offset[i], block + i*16*sizeof(pixel), stride);
            else                                  ff_h264_idct8_add_neon   (dst + block_offset[i], block + i*16*sizeof(pixel), stride);
        }
    }
}

static void deblock_v_luma_intra_neon( uint8_t *pix, int stride, int alpha, int beta )
{
    asm volatile(
                 "sub           %0,%0,%1,lsl #2  \n" //pix = pix -4*stride;
                 
                 "vld1.8        d0,[%0],%1      \n" //d0 p3
                 "vld1.8        d1,[%0],%1      \n" //d1 p2
                 "vld1.8        d2,[%0],%1      \n" //d2 p1
                 "vld1.8        d3,[%0],%1      \n" //d3 p0
                 "vld1.8        d4,[%0],%1      \n" //d4 q0
                 "vld1.8        d5,[%0],%1      \n" //d5 q1
                 "vld1.8        d6,[%0],%1      \n" //d6 q2
                 "vld1.8        d7,[%0],%1      \n" //d7 q3
                 
                 "vaddl.u8      q4,d3,d4        \n" // q4: A p0+q0
                 "vaddl.u8      q5,d1,d2        \n" // q5: B p2+p1
                 "vaddl.u8      q6,d0,d1        \n" // q6: C p3+p2
                 "vaddl.u8      q7,d5,d6        \n" // q7: D q1+q2
                 "vdup.u8      d31,%2           \n" //d31 alpha
                 "vaddl.u8      q8,d6,d7        \n" // q8: E q2+q3
                 "vaddl.u8      q9,d2,d5        \n" // q9: F p1+q1
                 "vaddl.u8     q10,d2,d3        \n" //q10: G p1+p0
                 "vaddl.u8     q11,d4,d5        \n" //q11: H q0+q1
                 
                 "vdup.u8     d30, %3           \n" //d30 beta
                 "vadd.u16     q5, q5, q4       \n" // q5:A+B
                 "vadd.u16     q7, q7, q4       \n" // q7:A+D
                 "vadd.u16    q10,q10, q9       \n" //q10:G+F
                 "vshr.u8     d29,d31,2         \n" // d29: (alpha>>2)
                 "vadd.u16    q11,q11, q9       \n" //q11:H+F
                 "vadd.u16     q4, q4, q9       \n" // q4:A+F
                 "vadd.u16     q6, q6, q6       \n" // q6:2C
                 "vadd.u16     q8, q8, q8       \n" // q8:2E
                 "vmov.u8     d28,#2            \n" // d28:2
                 
                 "vadd.u16     q9, q4, q5       \n" // q9:A+B+A+F
                 "vadd.u16     q6, q6, q5       \n" // q6:A+B+2C
                 "vadd.u16     q8, q8, q7       \n" // q8:A+D+2E
                 "vadd.u16     q4, q4, q7       \n" // q4:A+F+A+D
                 "vadd.u8     d29,d29,d28       \n" //
                 
                 "vrshrn.u16    d10, q5,#2       \n" //d10:p1'   ( p2 + p1 + p0 + q0 + 2 ) >> 2
                 "vrshrn.u16    d12, q6,#3       \n" //d12:p2'   ( 2*p3 + 3*p2 + p1 + p0 + q0 + 4 ) >> 3
                 "vrshrn.u16    d14, q7,#2       \n" //d14:q1'   ( p0 + q0 + q1 + q2 + 2 ) >> 2
                 "vrshrn.u16    d16, q8,#3       \n" //d16:q2'   ( 2*q3 + 3*q2 + q1 + q0 + p0 + 4 ) >> 3;
                 "vrshrn.u16    d18, q9,#3       \n" //d18:p0_T  ( p1 + 2*p0 + 2*q0 + 2*q1 + q2 + 4 ) >> 3;
                 "vrshrn.u16    d20,q10,#2       \n" //d20:p0_F  ( 2*p1 + p0 + q1 + 2 ) >> 2;
                 "vrshrn.u16    d22,q11,#2       \n" //d22:q0_F  ( 2*q1 + q0 + p1 + 2 ) >> 2;
                 "vrshrn.u16     d8, q4,#3       \n" // d8:q0_T  ( p1 + 2*p0 + 2*q0 + 2*q1 + q2 + 4 ) >> 3
                 
                 "vabd.u8      d11,d3,d4        \n"//d11:abs(p0-q0)
                 "vabd.u8      d17,d1,d3        \n"//d17:abs(p2-p0)
                 "vabd.u8      d19,d6,d4        \n"//d19:abs(q2-q0)
                 "vabd.u8      d13,d2,d3        \n"//d13:abs(p1-p0)
                 "vabd.u8      d15,d5,d4        \n"//d15:abs(q1-q0)
                 "sub           %0,%0,%1,lsl #3 \n" //pix = pix -4*stride;
                 
                 
                 "vclt.u8      d28,d11,d29      \n"//d28:abs(p0-q0)<((alpha>>2)+2)  cond1
                 "vclt.u8      d17,d17,d30      \n"//d17:abs(p2-p0)<beta            cond2
                 "vclt.u8      d19,d19,d30      \n"//d19:abs(q2-q0)<beta            cond3
                 
                 "add          r12,%0,#8        \n"//r12->pix+8
                 
                 
                 "vclt.u8      d11,d11,d31      \n"//d11:abs(p0-q0)<alpha
                 "vclt.u8      d13,d13,d30      \n"//d13:abs(p1-p0)<beta
                 "vclt.u8      d15,d15,d30      \n"//d15:abs(q1-q0)<beta
                 "add          %0,%0,%1         \n"//%0-> pix-3*stride
                 
                 "vand.u8      d17,d17,d28      \n"//d17:cond1&&cond2
                 "vand.u8      d11,d11,d13      \n"
                 "vand.u8      d19,d19,d28      \n"//d19:cond1&&cond3
                 "vand.u8      d11,d11,d15      \n"//d11:cond0
                 
                 
                 "vbit.u8      d20,d18,d17      \n" // if(cond1&&cond2) {B+2A+F;}else {G+F}
                 "vbit.u8      d22, d8,d19      \n" // if(cond1&&cond3) {F+2A+D;}else {H+F}
                 
                 "vand.u8      d17,d17,d11      \n" // cond0 && cond1 && cond2
                 "vand.u8      d19,d19,d11      \n" // cond0 && cond1 && cond3
                 
                 "vbit.u8      d3,d20,d11       \n" //p0
                 "vbit.u8      d4,d22,d11       \n" //q0
                 "vbit.u8      d2,d10,d17       \n" //p1
                 "vbit.u8      d1,d12,d17       \n" //p2
                 "vbit.u8      d5,d14,d19       \n" //q1
                 "vbit.u8      d6,d16,d19       \n" //q2
                 
                 "vst1.8        d1,[%0],%1      \n" //d1 p2
                 "vst1.8        d2,[%0],%1      \n" //d2 p1
                 "vst1.8        d3,[%0],%1      \n" //d3 p0
                 "vst1.8        d4,[%0],%1      \n" //d4 q0
                 "vst1.8        d5,[%0],%1      \n" //d5 q1
                 "vst1.8        d6,[%0],%1      \n" //d6 q2
                 
                 
                 // Next 8 bytes
                 
                 "vld1.8        d0,[r12],%1      \n" //d0 p3
                 "vld1.8        d1,[r12],%1      \n" //d1 p2
                 "vld1.8        d2,[r12],%1      \n" //d2 p1
                 "vld1.8        d3,[r12],%1      \n" //d3 p0
                 "vld1.8        d4,[r12],%1      \n" //d4 q0
                 "vld1.8        d5,[r12],%1      \n" //d5 q1
                 "vld1.8        d6,[r12],%1      \n" //d6 q2
                 "vld1.8        d7,[r12],%1      \n" //d7 q3
                 
                 "vaddl.u8      q4,d3,d4        \n" // q4: A p0+q0
                 "vaddl.u8      q5,d1,d2        \n" // q5: B p2+p1
                 "vaddl.u8      q6,d0,d1        \n" // q6: C p3+p2
                 "vaddl.u8      q7,d5,d6        \n" // q7: D q1+q2
                 
                 "vaddl.u8      q8,d6,d7        \n" // q8: E q2+q3
                 "vaddl.u8      q9,d2,d5        \n" // q9: F p1+q1
                 "vaddl.u8     q10,d2,d3        \n" //q10: G p1+p0
                 "vaddl.u8     q11,d4,d5        \n" //q11: H q0+q1
                 
                 
                 "vadd.u16     q5, q5, q4       \n" // q5:A+B
                 "vadd.u16     q7, q7, q4       \n" // q7:A+D
                 "vadd.u16    q10,q10, q9       \n" //q10:G+F
                 
                 "vadd.u16    q11,q11, q9       \n" //q11:H+F
                 "vadd.u16     q4, q4, q9       \n" // q4:A+F
                 "vadd.u16     q6, q6, q6       \n" // q6:2C
                 "vadd.u16     q8, q8, q8       \n" // q8:2E
                 
                 
                 "vadd.u16     q9, q4, q5       \n" // q9:A+B+A+F
                 "vadd.u16     q6, q6, q5       \n" // q6:A+B+2C
                 "vadd.u16     q8, q8, q7       \n" // q8:A+D+2E
                 "vadd.u16     q4, q4, q7       \n" // q4:A+F+A+D
                 
                 
                 "vrshrn.u16    d10, q5,#2       \n" //d10:p1'   ( p2 + p1 + p0 + q0 + 2 ) >> 2
                 "vrshrn.u16    d12, q6,#3       \n" //d12:p2'   ( 2*p3 + 3*p2 + p1 + p0 + q0 + 4 ) >> 3
                 "vrshrn.u16    d14, q7,#2       \n" //d14:q1'   ( p0 + q0 + q1 + q2 + 2 ) >> 2
                 "vrshrn.u16    d16, q8,#3       \n" //d16:q2'   ( 2*q3 + 3*q2 + q1 + q0 + p0 + 4 ) >> 3;
                 "vrshrn.u16    d18, q9,#3       \n" //d18:p0_T  ( p1 + 2*p0 + 2*q0 + 2*q1 + q2 + 4 ) >> 3;
                 "vrshrn.u16    d20,q10,#2       \n" //d20:p0_F  ( 2*p1 + p0 + q1 + 2 ) >> 2;
                 "vrshrn.u16    d22,q11,#2       \n" //d22:q0_F  ( 2*q1 + q0 + p1 + 2 ) >> 2;
                 "vrshrn.u16     d8, q4,#3       \n" // d8:q0_T  ( p1 + 2*p0 + 2*q0 + 2*q1 + q2 + 4 ) >> 3
                 
                 "vabd.u8      d11, d3,d4        \n"//d11:abs(p0-q0)
                 "vabd.u8      d17, d1,d3        \n"//d17:abs(p2-p0)
                 "vabd.u8      d19, d6,d4        \n"//d19:abs(q2-q0)
                 "vabd.u8      d13, d2,d3        \n"//d13:abs(p1-p0)
                 "vabd.u8      d15, d5,d4        \n"//d15:abs(q1-q0)
                 "sub          r12,r12,%1,lsl #3 \n" //pix = pix -4*stride;
                 
                 
                 "vclt.u8      d28,d11,d29      \n"//d28:abs(p0-q0)<((alpha>>2)+2)  cond1
                 "vclt.u8      d17,d17,d30      \n"//d17:abs(p2-p0)<beta            cond2
                 "vclt.u8      d19,d19,d30      \n"//d19:abs(q2-q0)<beta            cond3
                 
                 
                 
                 
                 "vclt.u8      d11,d11,d31      \n"//d11:abs(p0-q0)<alpha
                 "vclt.u8      d13,d13,d30      \n"//d13:abs(p1-p0)<beta
                 "vclt.u8      d15,d15,d30      \n"//d15:abs(q1-q0)<beta
                 "add          r12,r12,%1       \n"//%0-> pix-3*stride
                 
                 "vand.u8      d17,d17,d28      \n"//d17:cond1&&cond2
                 "vand.u8      d11,d11,d13      \n"
                 "vand.u8      d19,d19,d28      \n"//d19:cond1&&cond3
                 "vand.u8      d11,d11,d15      \n"//d11:cond0
                 
                 
                 "vbit.u8      d20,d18,d17      \n" // if(cond1&&cond2) {B+2A+F;}else {G+F}
                 "vbit.u8      d22, d8,d19      \n" // if(cond1&&cond3) {F+2A+D;}else {H+F}
                 
                 "vand.u8      d17,d17,d11      \n" // cond0 && cond1 && cond2
                 "vand.u8      d19,d19,d11      \n" // cond0 && cond1 && cond3
                 
                 "vbit.u8      d3,d20,d11       \n" //p0
                 "vbit.u8      d4,d22,d11       \n" //q0
                 "vbit.u8      d2,d10,d17       \n" //p1
                 "vbit.u8      d1,d12,d17       \n" //p2
                 "vbit.u8      d5,d14,d19       \n" //q1
                 "vbit.u8      d6,d16,d19       \n" //q2
                 
                 "vst1.8        d1,[r12],%1      \n" //d1 p2
                 "vst1.8        d2,[r12],%1      \n" //d2 p1
                 "vst1.8        d3,[r12],%1      \n" //d3 p0
                 "vst1.8        d4,[r12],%1      \n" //d4 q0
                 "vst1.8        d5,[r12],%1      \n" //d5 q1
                 "vst1.8        d6,[r12],%1      \n" //d6 q2
                 
                 
                 :"+r"(pix),"+r"(stride),"+r"(alpha),"+r"(beta)::"r12","q0","q1","q2","q3","q4","q5","q6","q7","q8","q9","q10","q11","q12","q13","q14","q15","memory");
}

static void deblock_h_luma_intra_neon( uint8_t *pix, int stride, int alpha, int beta )
{
    asm volatile(
                 "sub           %0,%0,#4  \n" //pix = pix -4
                 
                 
                 "vld1.8        d0,[%0],%1      \n" //d0 line p3
                 "vld1.8        d1,[%0],%1      \n" //d1 line p2
                 "vld1.8        d2,[%0],%1      \n" //d2 line p1
                 "vld1.8        d3,[%0],%1      \n" //d3 line p0
                 "vld1.8        d4,[%0],%1      \n" //d4 line q0
                 "vld1.8        d5,[%0],%1      \n" //d5 line q1
                 "vld1.8        d6,[%0],%1      \n" //d6 line q2
                 "vld1.8        d7,[%0],%1      \n" //d7 line q3
                 
                 
                 "vtrn.u8 d0,d1                 \n" // d0 high< 16,06,14,04,12,02,10,00>low
                 // d1 high< 17,07,15,05,13,03,11,01>low
                 "vtrn.u8 d2,d3                 \n" // d2 high< 36,26,34,24,32,22,30,20>low
                 // d3 high< 37,27,35,25,33,23,31,21>low
                 "vtrn.u8 d4,d5                 \n" // d4 high< 56,46,54,44,52,42,50,40>low
                 // d5 high< 57,47,55,45,53,43,51,41>low
                 "vtrn.u8 d6,d7                 \n" // d6 high< 76,66,74,64,72,62,70,60>low
                 // d7 high< 77,67,75,65,73,63,71,61>low
                 
                 //-------------------------------------------------------------------------------
                 "vtrn.u16 q0,q1                \n" // q0 high< 35,25,15,05,31,21,11,01,34,24,14,04,30,20,10,00>low
                 // q1 high< 37,27,17,07,33,23,13,03,36,26,16,06,32,22,12,02>low
                 
                 "vtrn.u16 q2,q3                \n" // q2 high< 75,65,55,45,71,61,51,41,74,64,54,44,70,60,50,40>low
                 // q3 high< 77,67,57,47,73,63,53,53,76,66,56,46,72,62,52,42>low
                 //-------------------------------------------------------------------------------
                 "vtrn.u32 q0,q2                \n" // q0 high< 71,61,51,41,31,21,11,01,70,60,50,40,30,20,10,00>low
                 // q2 high< 75,65,55,45,35,25,15,05,74,64,54,44,34,24,14,04>low
                 "vtrn.u32 q1,q3                \n" // q1 high< 73,63,53,53,33,23,13,03,72,62,52,42,32,22,12,02>low
                 // q3 high< 77,67,57,47,37,27,17,07,76,66,56,46,36,26,16,06>low
                 
                 "vaddl.u8      q4,d3,d4        \n" // q4: A p0+q0
                 "vaddl.u8      q5,d1,d2        \n" // q5: B p2+p1
                 "vaddl.u8      q6,d0,d1        \n" // q6: C p3+p2
                 "vaddl.u8      q7,d5,d6        \n" // q7: D q1+q2
                 "vdup.u8      d31,%2           \n" //d31 alpha
                 "vaddl.u8      q8,d6,d7        \n" // q8: E q2+q3
                 "vaddl.u8      q9,d2,d5        \n" // q9: F p1+q1
                 "vaddl.u8     q10,d2,d3        \n" //q10: G p1+p0
                 "vaddl.u8     q11,d4,d5        \n" //q11: H q0+q1
                 
                 "vdup.u8     d30, %3           \n" //d30 beta
                 "vadd.u16     q5, q5, q4       \n" // q5:A+B
                 "vadd.u16     q7, q7, q4       \n" // q7:A+D
                 "vadd.u16    q10,q10, q9       \n" //q10:G+F
                 "vshr.u8     d29,d31,2         \n" // d29: (alpha>>2)
                 "vadd.u16    q11,q11, q9       \n" //q11:H+F
                 "vadd.u16     q4, q4, q9       \n" // q4:A+F
                 "vadd.u16     q6, q6, q6       \n" // q6:2C
                 "vadd.u16     q8, q8, q8       \n" // q8:2E
                 "vmov.u8     d28,#2            \n" // d28:2
                 
                 "vadd.u16     q9, q4, q5       \n" // q9:A+B+A+F
                 "vadd.u16     q6, q6, q5       \n" // q6:A+B+2C
                 "vadd.u16     q8, q8, q7       \n" // q8:A+D+2E
                 "vadd.u16     q4, q4, q7       \n" // q4:A+F+A+D
                 "vadd.u8     d29,d29,d28       \n" //
                 
                 "vrshrn.u16    d10, q5,#2       \n" //d10:p1'   ( p2 + p1 + p0 + q0 + 2 ) >> 2
                 "vrshrn.u16    d12, q6,#3       \n" //d12:p2'   ( 2*p3 + 3*p2 + p1 + p0 + q0 + 4 ) >> 3
                 "vrshrn.u16    d14, q7,#2       \n" //d14:q1'   ( p0 + q0 + q1 + q2 + 2 ) >> 2
                 "vrshrn.u16    d16, q8,#3       \n" //d16:q2'   ( 2*q3 + 3*q2 + q1 + q0 + p0 + 4 ) >> 3;
                 "vrshrn.u16    d18, q9,#3       \n" //d18:p0_T  ( p1 + 2*p0 + 2*q0 + 2*q1 + q2 + 4 ) >> 3;
                 "vrshrn.u16    d20,q10,#2       \n" //d20:p0_F  ( 2*p1 + p0 + q1 + 2 ) >> 2;
                 "vrshrn.u16    d22,q11,#2       \n" //d22:q0_F  ( 2*q1 + q0 + p1 + 2 ) >> 2;
                 "vrshrn.u16     d8, q4,#3       \n" // d8:q0_T  ( p1 + 2*p0 + 2*q0 + 2*q1 + q2 + 4 ) >> 3
                 
                 "vabd.u8      d11,d3,d4        \n"//d11:abs(p0-q0)
                 "vabd.u8      d17,d1,d3        \n"//d17:abs(p2-p0)
                 "vabd.u8      d19,d6,d4        \n"//d19:abs(q2-q0)
                 "vabd.u8      d13,d2,d3        \n"//d13:abs(p1-p0)
                 "vabd.u8      d15,d5,d4        \n"//d15:abs(q1-q0)
                 "sub           %0,%0,%1,lsl #3 \n" //pix = pix -4;
                 
                 
                 "vclt.u8      d28,d11,d29      \n"//d28:abs(p0-q0)<((alpha>>2)+2)  cond1
                 "vclt.u8      d17,d17,d30      \n"//d17:abs(p2-p0)<beta            cond2
                 "vclt.u8      d19,d19,d30      \n"//d19:abs(q2-q0)<beta            cond3
                 
                 
                 "vclt.u8      d11,d11,d31      \n"//d11:abs(p0-q0)<alpha
                 "vclt.u8      d13,d13,d30      \n"//d13:abs(p1-p0)<beta
                 "vclt.u8      d15,d15,d30      \n"//d15:abs(q1-q0)<beta
                 
                 
                 "vand.u8      d17,d17,d28      \n"//d17:cond1&&cond2
                 "vand.u8      d11,d11,d13      \n"
                 "vand.u8      d19,d19,d28      \n"//d19:cond1&&cond3
                 "vand.u8      d11,d11,d15      \n"//d11:cond0
                 
                 
                 "vbit.u8      d20,d18,d17      \n" // if(cond1&&cond2) {B+2A+F;}else {G+F}
                 "vbit.u8      d22, d8,d19      \n" // if(cond1&&cond3) {F+2A+D;}else {H+F}
                 
                 "vand.u8      d17,d17,d11      \n" // cond0 && cond1 && cond2
                 "vand.u8      d19,d19,d11      \n" // cond0 && cond1 && cond3
                 
                 "vbit.u8      d3,d20,d11       \n" //p0
                 "vbit.u8      d4,d22,d11       \n" //q0
                 "vbit.u8      d2,d10,d17       \n" //p1
                 "vbit.u8      d1,d12,d17       \n" //p2
                 "vbit.u8      d5,d14,d19       \n" //q1
                 "vbit.u8      d6,d16,d19       \n" //q2
                 
                 "vtrn.u8 d0,d1                 \n"
                 "vtrn.u8 d2,d3                 \n"
                 "vtrn.u8 d4,d5                 \n"
                 "vtrn.u8 d6,d7                 \n"
                 "vtrn.u16 q0,q1                \n"
                 "vtrn.u16 q2,q3                \n"
                 "vtrn.u32 q0,q2                \n"
                 "vtrn.u32 q1,q3                \n"
                 
                 "vst1.8        d0,[%0],%1      \n" //d0 line p3
                 "vst1.8        d1,[%0],%1      \n" //d1 line p2
                 "vst1.8        d2,[%0],%1      \n" //d2 line p1
                 "vst1.8        d3,[%0],%1      \n" //d3 line p0
                 "vst1.8        d4,[%0],%1      \n" //d4 line q0
                 "vst1.8        d5,[%0],%1      \n" //d5 line q1
                 "vst1.8        d6,[%0],%1      \n" //d6 line q2
                 "vst1.8        d7,[%0],%1      \n" //d7 line q3
                 
                 
                 // Next 8 bytes
                 "vld1.8        d0,[%0],%1      \n" //d0 line p3
                 "vld1.8        d1,[%0],%1      \n" //d1 line p2
                 "vld1.8        d2,[%0],%1      \n" //d2 line p1
                 "vld1.8        d3,[%0],%1      \n" //d3 line p0
                 "vld1.8        d4,[%0],%1      \n" //d4 line q0
                 "vld1.8        d5,[%0],%1      \n" //d5 line q1
                 "vld1.8        d6,[%0],%1      \n" //d6 line q2
                 "vld1.8        d7,[%0],%1      \n" //d7 line q3
                 
                 
                 "vtrn.u8 d0,d1                 \n" // d0 high< 16,06,14,04,12,02,10,00>low
                 // d1 high< 17,07,15,05,13,03,11,01>low
                 "vtrn.u8 d2,d3                 \n" // d2 high< 36,26,34,24,32,22,30,20>low
                 // d3 high< 37,27,35,25,33,23,31,21>low
                 "vtrn.u8 d4,d5                 \n" // d4 high< 56,46,54,44,52,42,50,40>low
                 // d5 high< 57,47,55,45,53,43,51,41>low
                 "vtrn.u8 d6,d7                 \n" // d6 high< 76,66,74,64,72,62,70,60>low
                 // d7 high< 77,67,75,65,73,63,71,61>low
                 
                 //-------------------------------------------------------------------------------
                 "vtrn.u16 q0,q1                \n" // q0 high< 35,25,15,05,31,21,11,01,34,24,14,04,30,20,10,00>low
                 // q1 high< 37,27,17,07,33,23,13,03,36,26,16,06,32,22,12,02>low
                 
                 "vtrn.u16 q2,q3                \n" // q2 high< 75,65,55,45,71,61,51,41,74,64,54,44,70,60,50,40>low
                 // q3 high< 77,67,57,47,73,63,53,53,76,66,56,46,72,62,52,42>low
                 //-------------------------------------------------------------------------------
                 "vtrn.u32 q0,q2                \n" // q0 high< 71,61,51,41,31,21,11,01,70,60,50,40,30,20,10,00>low
                 // q2 high< 75,65,55,45,35,25,15,05,74,64,54,44,34,24,14,04>low
                 "vtrn.u32 q1,q3                \n" // q1 high< 73,63,53,53,33,23,13,03,72,62,52,42,32,22,12,02>low
                 // q3 high< 77,67,57,47,37,27,17,07,76,66,56,46,36,26,16,06>low
                 
                 "vaddl.u8      q4,d3,d4        \n" // q4: A p0+q0
                 "vaddl.u8      q5,d1,d2        \n" // q5: B p2+p1
                 "vaddl.u8      q6,d0,d1        \n" // q6: C p3+p2
                 "vaddl.u8      q7,d5,d6        \n" // q7: D q1+q2
                 
                 "vaddl.u8      q8,d6,d7        \n" // q8: E q2+q3
                 "vaddl.u8      q9,d2,d5        \n" // q9: F p1+q1
                 "vaddl.u8     q10,d2,d3        \n" //q10: G p1+p0
                 "vaddl.u8     q11,d4,d5        \n" //q11: H q0+q1
                 
                 
                 "vadd.u16     q5, q5, q4       \n" // q5:A+B
                 "vadd.u16     q7, q7, q4       \n" // q7:A+D
                 "vadd.u16    q10,q10, q9       \n" //q10:G+F
                 
                 "vadd.u16    q11,q11, q9       \n" //q11:H+F
                 "vadd.u16     q4, q4, q9       \n" // q4:A+F
                 "vadd.u16     q6, q6, q6       \n" // q6:2C
                 "vadd.u16     q8, q8, q8       \n" // q8:2E
                 
                 
                 "vadd.u16     q9, q4, q5       \n" // q9:A+B+A+F
                 "vadd.u16     q6, q6, q5       \n" // q6:A+B+2C
                 "vadd.u16     q8, q8, q7       \n" // q8:A+D+2E
                 "vadd.u16     q4, q4, q7       \n" // q4:A+F+A+D
                 
                 
                 "vrshrn.u16    d10, q5,#2       \n" //d10:p1'   ( p2 + p1 + p0 + q0 + 2 ) >> 2
                 "vrshrn.u16    d12, q6,#3       \n" //d12:p2'   ( 2*p3 + 3*p2 + p1 + p0 + q0 + 4 ) >> 3
                 "vrshrn.u16    d14, q7,#2       \n" //d14:q1'   ( p0 + q0 + q1 + q2 + 2 ) >> 2
                 "vrshrn.u16    d16, q8,#3       \n" //d16:q2'   ( 2*q3 + 3*q2 + q1 + q0 + p0 + 4 ) >> 3;
                 "vrshrn.u16    d18, q9,#3       \n" //d18:p0_T  ( p1 + 2*p0 + 2*q0 + 2*q1 + q2 + 4 ) >> 3;
                 "vrshrn.u16    d20,q10,#2       \n" //d20:p0_F  ( 2*p1 + p0 + q1 + 2 ) >> 2;
                 "vrshrn.u16    d22,q11,#2       \n" //d22:q0_F  ( 2*q1 + q0 + p1 + 2 ) >> 2;
                 "vrshrn.u16     d8, q4,#3       \n" // d8:q0_T  ( p1 + 2*p0 + 2*q0 + 2*q1 + q2 + 4 ) >> 3
                 
                 "vabd.u8      d11,d3,d4        \n"//d11:abs(p0-q0)
                 "vabd.u8      d17,d1,d3        \n"//d17:abs(p2-p0)
                 "vabd.u8      d19,d6,d4        \n"//d19:abs(q2-q0)
                 "vabd.u8      d13,d2,d3        \n"//d13:abs(p1-p0)
                 "vabd.u8      d15,d5,d4        \n"//d15:abs(q1-q0)
                 
                 "vclt.u8      d28,d11,d29      \n"//d28:abs(p0-q0)<((alpha>>2)+2)  cond1
                 "vclt.u8      d17,d17,d30      \n"//d17:abs(p2-p0)<beta            cond2
                 "vclt.u8      d19,d19,d30      \n"//d19:abs(q2-q0)<beta            cond3
                 
                 
                 "vclt.u8      d11,d11,d31      \n"//d11:abs(p0-q0)<alpha
                 "vclt.u8      d13,d13,d30      \n"//d13:abs(p1-p0)<beta
                 "vclt.u8      d15,d15,d30      \n"//d15:abs(q1-q0)<beta
                 
                 
                 "vand.u8      d17,d17,d28      \n"//d17:cond1&&cond2
                 "vand.u8      d11,d11,d13      \n"
                 "vand.u8      d19,d19,d28      \n"//d19:cond1&&cond3
                 "vand.u8      d11,d11,d15      \n"//d11:cond0
                 
                 
                 "vbit.u8      d20,d18,d17      \n" // if(cond1&&cond2) {B+2A+F;}else {G+F}
                 "vbit.u8      d22, d8,d19      \n" // if(cond1&&cond3) {F+2A+D;}else {H+F}
                 
                 "vand.u8      d17,d17,d11      \n" // cond0 && cond1 && cond2
                 "vand.u8      d19,d19,d11      \n" // cond0 && cond1 && cond3
                 
                 "vbit.u8      d3,d20,d11       \n" //p0
                 "vbit.u8      d4,d22,d11       \n" //q0
                 "vbit.u8      d2,d10,d17       \n" //p1
                 "vbit.u8      d1,d12,d17       \n" //p2
                 "vbit.u8      d5,d14,d19       \n" //q1
                 "vbit.u8      d6,d16,d19       \n" //q2
                 
                 "sub           %0,%0,%1,lsl #3 \n" //pix = pix -4;
                 
                 "vtrn.u8 d0,d1                 \n"
                 "vtrn.u8 d2,d3                 \n"
                 "vtrn.u8 d4,d5                 \n"
                 "vtrn.u8 d6,d7                 \n"
                 "vtrn.u16 q0,q1                \n"
                 "vtrn.u16 q2,q3                \n"
                 "vtrn.u32 q0,q2                \n"
                 "vtrn.u32 q1,q3                \n"
                 
                 "vst1.8        d0,[%0],%1      \n" //d0 line p3
                 "vst1.8        d1,[%0],%1      \n" //d1 line p2
                 "vst1.8        d2,[%0],%1      \n" //d2 line p1
                 "vst1.8        d3,[%0],%1      \n" //d3 line p0
                 "vst1.8        d4,[%0],%1      \n" //d4 line q0
                 "vst1.8        d5,[%0],%1      \n" //d5 line q1
                 "vst1.8        d6,[%0],%1      \n" //d6 line q2
                 "vst1.8        d7,[%0],%1      \n" //d7 line q3
                 
                 :"+r"(pix),"+r"(stride),"+r"(alpha),"+r"(beta)::"q0","q1","q2","q3","q4","q5","q6","q7","q8","q9","q10","q11","q12","q13","q14","q15","memory");
}

static void deblock_v_chroma_intra_neon( uint8_t *pix, int stride, int alpha, int beta )
{
    asm volatile(
                 "sub           %0,%0,%1,lsl #1 \n" //pix = pix -2*stride;
                 "vld1.8        {q0},[%0],%1      \n" //q0 A1
                 "vld1.8        {q1},[%0],%1      \n" //q1 A0
                 "vld1.8        {q2},[%0],%1      \n" //q2 B0
                 "vld1.8        {q3},[%0]         \n" //q3 B1
                 
                 "vabd.u8       q4,q1,q2        \n" //q4 abs(A0-B0)
                 "vaddl.u8      q8,d0,d6        \n" //q8 (A1+B1) low
                 "vdup.u8       q15,%2          \n" //q15 alpha
                 "vaddl.u8      q9,d1,d7        \n" //q9 (A1+B1) high
                 
                 "vabd.u8       q5,q0,q1        \n" //q5 abs(A1-A0)
                 "vaddl.u8     q10,d0,d2        \n" //q10 (A1+A0) low
                 "vdup.u8       q14,%3          \n" //q14 beta
                 "vaddl.u8     q11,d1,d3        \n" //q11 (A1+A0) high
                 
                 "vabd.u8       q6,q3,q2        \n" //q6 abs(B1-B0)
                 "vaddl.u8     q12,d6,d4        \n" //q12 (B1 + B0) low
                 "vaddl.u8     q13,d7,d5        \n" //q13 (B1 + B0) high
                 "vclt.u8      q4,q4,q15        \n" //abs(A0-B0)<alpha
                 "vclt.u8      q5,q5,q14        \n" //abs(A1-A0)<beta
                 "vclt.u8      q6,q6,q14        \n" //abs(B1-B0)<beta
                 "vadd.u16     q10,q10,q8       \n" //2*A1+A0+B1
                 "vadd.u16     q11,q11,q9       \n"
                 "vand.u8      q4,q4,q5         \n" // q4 :abs(A0-B0)&&abs(A1-A0)
                 "vadd.u16     q12,q12,q8       \n" //2*B1+B0+A1
                 "vadd.u16     q13,q13,q9       \n"
                 "vand.u8      q4,q4,q6         \n" // q4 :abs(A0-B0)&&abs(A1-A0)&&abs(B1-B0)
                 "vrshrn.u16    d16,q10,#2       \n" //(2*p1+p0+q1+2)>>2 p0'
                 "vrshrn.u16    d17,q11,#2       \n"
                 "vrshrn.u16    d18,q12,#2       \n" //(2*q1+q0+p1+2)>>2 q0'
                 "vrshrn.u16    d19,q13,#2       \n"
                 "sub          %0,%0,%1,lsl #1  \n" // pix =pix-stride
                 "vbit.u8      q1,q8,q4         \n"
                 "vbit.u8      q2,q9,q4         \n"
                 
                 "vst1.8        {q1},[%0],%1      \n" //d0 high<B01,B00,A00,A01>low
                 "vst1.8        {q2},[%0]         \n" //d2 high<B11,B10,A10,A11>low
                 
                 :"+r"(pix),"+r"(stride),"+r"(alpha),"+r"(beta)::"q0","q1","q2","q3","q4","q5","q6","q7","q8","q9","q10","q11","q12","q13","q14","q15","memory");
}

static void deblock_h_chroma_intra_neon( uint8_t *pix, int stride, int alpha, int beta )
{
    asm volatile(
                 "sub           %0,%0, #4       \n" //pix = pix -4;
                 "vld1.8        d0,[%0],%1      \n" //d0 high<B01,B00,A00,A01>low
                 "vld1.8        d2,[%0],%1      \n" //d2 high<B11,B10,A10,A11>low
                 "vld1.8        d4,[%0],%1      \n" //d4 high<B21,B20,A20,A21>low
                 "vld1.8        d6,[%0],%1      \n" //d6 high<B31,B30,A30,A31>low
                 "vld1.8        d1,[%0],%1      \n" //d1 high<B41,B40,A40,A41>low
                 "vld1.8        d3,[%0],%1      \n" //d3 high<B51,B50,A50,A51>low
                 "vld1.8        d5,[%0],%1      \n" //d5 high<B61,B60,A60,A61>low
                 "vld1.8        d7,[%0],%1      \n" //d7 high<B71,B70,A70,A71>low
                 
                 "vtrn.u16      q0,q1           \n" //q0 high<B50,B40,A51,A41,B10,B00,A11,A01>low
                 //q1 high<B51,B41,A50,A40,B11,B01,A10,A00>low
                 "vtrn.u16      q2,q3           \n" //q2 high<B70,B60,A71,A61,B30,B20,A31,A21>low
                 //q3 high<B71,B61,A70,A60,B31,B21,A30,A20>low
                 
                 "vtrn.u32      q0,q2           \n" //q0 high<A71,A61,A51,A41,A31,A21,A11,A01>low  A1
                 //q2 high<B70,B60,B50,B40,B30,B20,B10,B00>low  B0
                 "vtrn.u32      q1,q3           \n" //q1 high<A70,A60,A50,A40,A30,A20,A10,A00>low  A0
                 //q3 high<B71,B61,B51,B41,B31,B21,B11,B01>low  B1
                 
                 "vabd.u8       q4,q1,q2        \n" //q4 abs(A0-B0)
                 "vaddl.u8      q8,d0,d6        \n" //q8 (A1+B1) low
                 "vdup.u8       q14,%3          \n" //q14 beta
                 "vaddl.u8      q9,d1,d7        \n" //q9 (A1+B1) high
                 
                 "vabd.u8       q5,q0,q1        \n" //q5 abs(A1-A0)
                 "vaddl.u8     q10,d0,d2        \n" //q10 (A1+A0) low
                 "vdup.u8       q15,%2          \n" //q15 alpha
                 "vaddl.u8     q11,d1,d3        \n" //q11 (A1+A0) high
                 
                 "vabd.u8       q6,q3,q2        \n" //q6 abs(B1-B0)
                 "vaddl.u8     q12,d6,d4        \n" //q12 (B1 + B0) low
                 "vaddl.u8     q13,d7,d5        \n" //q13 (B1 + B0) high
                 "vclt.u8      q4,q4,q15        \n" //abs(A0-B0)<alpha
                 "vclt.u8      q5,q5,q14        \n" //abs(A1-A0)<beta
                 "vclt.u8      q6,q6,q14        \n" //abs(B1-B0)<beta
                 "vadd.u16     q10,q10,q8       \n" //2*A1+A0+B1
                 "vadd.u16     q11,q11,q9       \n"
                 "vand.u8      q4,q4,q5         \n" // q4 :abs(A0-B0)&&abs(A1-A0)
                 "vadd.u16     q12,q12,q8       \n" //2*B1+B0+A1
                 "vadd.u16     q13,q13,q9       \n"
                 "vand.u8      q4,q4,q6         \n" // q4 :abs(A0-B0)&&abs(A1-A0)&&abs(B1-B0)
                 "vrshrn.u16    d16,q10,#2       \n" //(2*A1+A0+B1+2)>>2 A0'
                 "vrshrn.u16    d17,q11,#2       \n"
                 "vrshrn.u16    d18,q12,#2       \n" //(2*B1+B0+A1+2)>>2 B0'
                 "vrshrn.u16    d19,q13,#2       \n"
                 "sub          %0,%0,%1,lsl #3  \n"
                 "vbit.u8      q1,q8,q4         \n"
                 "vbit.u8      q2,q9,q4         \n"
                 
                 "vtrn.u32     q0,q2            \n"
                 "vtrn.u32     q1,q3            \n"
                 "vtrn.u16     q0,q1            \n"
                 "vtrn.u16     q2,q3            \n"
                 
                 "vst1.8        d0,[%0],%1      \n" //d0 high<B01,B00,A00,A01>low
                 "vst1.8        d2,[%0],%1      \n" //d2 high<B11,B10,A10,A11>low
                 "vst1.8        d4,[%0],%1      \n" //d4 high<B21,B20,A20,A21>low
                 "vst1.8        d6,[%0],%1      \n" //d6 high<B31,B30,A30,A31>low
                 "vst1.8        d1,[%0],%1      \n" //d1 high<B41,B40,A40,A41>low
                 "vst1.8        d3,[%0],%1      \n" //d3 high<B51,B50,A50,A51>low
                 "vst1.8        d5,[%0],%1      \n" //d5 high<B61,B60,A60,A61>low
                 "vst1.8        d7,[%0]         \n" //d7 high<B71,B70,A70,A71>low
                 
                 :"+r"(pix),"+r"(stride),"+r"(alpha),"+r"(beta)::"q0","q1","q2","q3","q4","q5","q6","q7","q8","q9","q10","q11","q12","q13","q14","q15","memory");
    
}




static void ff_h264dsp_init_neon(H264DSPContext *c, const int bit_depth, const int chroma_format_idc)
{
    if (bit_depth == 8) {
    c->h264_v_loop_filter_luma   = ff_h264_v_loop_filter_luma_neon;
    c->h264_h_loop_filter_luma   = ff_h264_h_loop_filter_luma_neon;
    if(chroma_format_idc == 1){
    c->h264_v_loop_filter_chroma = ff_h264_v_loop_filter_chroma_neon;
    c->h264_h_loop_filter_chroma = ff_h264_h_loop_filter_chroma_neon;
    }

    c->h264_h_loop_filter_luma_intra = deblock_h_luma_intra_neon;
    c->h264_v_loop_filter_luma_intra = deblock_v_luma_intra_neon;
    c->h264_v_loop_filter_chroma_intra = deblock_v_chroma_intra_neon;
    c->h264_h_loop_filter_chroma_intra = deblock_h_chroma_intra_neon;
        
    c->weight_h264_pixels_tab[0] = ff_weight_h264_pixels_16_neon;
    c->weight_h264_pixels_tab[1] = ff_weight_h264_pixels_8_neon;
    c->weight_h264_pixels_tab[2] = ff_weight_h264_pixels_4_neon;

    c->biweight_h264_pixels_tab[0] = ff_biweight_h264_pixels_16_neon;
    c->biweight_h264_pixels_tab[1] = ff_biweight_h264_pixels_8_neon;
    c->biweight_h264_pixels_tab[2] = ff_biweight_h264_pixels_4_neon;

    c->h264_idct_add        = ff_h264_idct_add_neon;
    c->h264_idct_dc_add     = ff_h264_idct_dc_add_neon;
    c->h264_idct_add16      = ff_h264_idct_add16_neon;
    c->h264_idct_add16intra = ff_h264_idct_add16intra_neon;
    if (chroma_format_idc == 1)
        c->h264_idct_add8   = ff_h264_idct_add8_neon;
    c->h264_idct8_add       = ff_h264_idct8_add_neon;
    c->h264_idct8_dc_add    = ff_h264_idct8_dc_add_neon;
    c->h264_idct8_add4      = ff_h264_idct8_add4_neon;
    }
}

void ff_h264dsp_init_arm(H264DSPContext *c, const int bit_depth, const int chroma_format_idc)
{
    int flag = av_get_cpu_flags();
    if (flag & AV_CPU_NEON) ff_h264dsp_init_neon(c, bit_depth, chroma_format_idc);
}
