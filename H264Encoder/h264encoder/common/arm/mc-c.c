/*****************************************************************************
 * mc-c.c: arm motion compensation
 *****************************************************************************
 * Copyright (C) 2009-2012 x264 project
 *
 * Authors: David Conrad <lessen42@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@x264.com.
 *****************************************************************************/
#include <arm_neon.h>
#include "common/common.h"
#include "mc.h"

void x264_prefetch_ref_arm( uint8_t *, intptr_t, int );
void x264_prefetch_fenc_arm( uint8_t *, intptr_t, uint8_t *, intptr_t, int );

void *x264_memcpy_aligned_neon( void *dst, const void *src, size_t n );
void x264_memzero_aligned_neon( void *dst, size_t n );

void x264_pixel_avg_16x16_neon( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_pixel_avg_16x8_neon ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_pixel_avg_8x16_neon ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_pixel_avg_8x8_neon  ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_pixel_avg_8x4_neon  ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_pixel_avg_4x8_neon  ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_pixel_avg_4x4_neon  ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_pixel_avg_4x2_neon  ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, intptr_t, int );

void x264_pixel_avg2_w4_neon ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, int );
void x264_pixel_avg2_w8_neon ( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, int );
void x264_pixel_avg2_w16_neon( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, int );
void x264_pixel_avg2_w20_neon( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, int );

#define MC_WEIGHT(func)\
void x264_mc_weight_w20##func##_neon( uint8_t *, intptr_t, uint8_t *, intptr_t, const x264_weight_t *, int );\
void x264_mc_weight_w16##func##_neon( uint8_t *, intptr_t, uint8_t *, intptr_t, const x264_weight_t *, int );\
void x264_mc_weight_w8##func##_neon ( uint8_t *, intptr_t, uint8_t *, intptr_t, const x264_weight_t *, int );\
void x264_mc_weight_w4##func##_neon ( uint8_t *, intptr_t, uint8_t *, intptr_t, const x264_weight_t *, int );\
\
static void (* const x264_mc##func##_wtab_neon[6])( uint8_t *, intptr_t, uint8_t *, intptr_t, const x264_weight_t *, int ) =\
{\
    x264_mc_weight_w4##func##_neon,\
    x264_mc_weight_w4##func##_neon,\
    x264_mc_weight_w8##func##_neon,\
    x264_mc_weight_w16##func##_neon,\
    x264_mc_weight_w16##func##_neon,\
    x264_mc_weight_w20##func##_neon,\
};

MC_WEIGHT()
MC_WEIGHT(_nodenom)
MC_WEIGHT(_offsetadd)
MC_WEIGHT(_offsetsub)

void x264_mc_copy_w4_neon ( uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_mc_copy_w8_neon ( uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_mc_copy_w16_neon( uint8_t *, intptr_t, uint8_t *, intptr_t, int );
void x264_mc_copy_w16_aligned_neon( uint8_t *, intptr_t, uint8_t *, intptr_t, int );

void x264_mc_chroma_neon( uint8_t *, intptr_t, uint8_t *, intptr_t, int, int, int, int );
void x264_frame_init_lowres_core_neon( uint8_t *, uint8_t *, uint8_t *, uint8_t *, uint8_t *, intptr_t, intptr_t, int, int );

void x264_hpel_filter_v_neon( uint8_t *, uint8_t *, int16_t *, intptr_t, int );
void x264_hpel_filter_c_neon( uint8_t *, int16_t *, int );
void x264_hpel_filter_h_neon( uint8_t *, uint8_t *, int );

#if !HIGH_BIT_DEPTH
// added by sensong 201305
static void load_deinterleave_chroma_fenc_neon( pixel *dst, pixel *src, intptr_t i_src, int height )
{
    pixel *dstu = dst;
    pixel *dstv = dst+FENC_STRIDE/2;
    uint8x8x2_t vecUV;

    for( int y=0; y<height; y++, dstu+=FENC_STRIDE, dstv+=FENC_STRIDE, src+=i_src )
    {
        vecUV = vld2_u8(src);
        vst1_u8(dstu,vecUV.val[0]);
        vst1_u8(dstv,vecUV.val[1]);
        
    }
}

static void load_deinterleave_chroma_fdec_neon( pixel *dst, pixel *src, intptr_t i_src, int height )
{
    pixel *dstu = dst;
    pixel *dstv = dst+FDEC_STRIDE/2;
    uint8x8x2_t vecUV;
    
    for( int y=0; y<height; y++, dstu+=FDEC_STRIDE, dstv+=FDEC_STRIDE, src+=i_src )
    {
        vecUV = vld2_u8(src);
        vst1_u8(dstu,vecUV.val[0]);
        vst1_u8(dstv,vecUV.val[1]);
        
    }
}


static void store_interleave_chroma_neon( pixel *dst, intptr_t i_dst, pixel *srcu, pixel *srcv, int height )
{
    uint8x8x2_t vec_UV;
    
    for( int y=0; y<height; y++, dst+=i_dst, srcu+=FDEC_STRIDE, srcv+=FDEC_STRIDE )
    {
        vec_UV.val[0] = vld1_u8(srcu);
        vec_UV.val[1] = vld1_u8(srcv);
        
        vst2_u8(dst,vec_UV);
    }
}

static void x264_weight_cache_neon( x264_t *h, x264_weight_t *w )
{
    if( w->i_scale == 1<<w->i_denom )
    {
        if( w->i_offset < 0 )
        {
            w->weightfn = x264_mc_offsetsub_wtab_neon;
            w->cachea[0] = -w->i_offset;
        }
        else
        {
            w->weightfn = x264_mc_offsetadd_wtab_neon;
            w->cachea[0] = w->i_offset;
        }
    }
    else if( !w->i_denom )
        w->weightfn = x264_mc_nodenom_wtab_neon;
    else
        w->weightfn = x264_mc_wtab_neon;
}

static void (* const x264_pixel_avg_wtab_neon[6])( uint8_t *, intptr_t, uint8_t *, intptr_t, uint8_t *, int ) =
{
    NULL,
    x264_pixel_avg2_w4_neon,
    x264_pixel_avg2_w8_neon,
    x264_pixel_avg2_w16_neon,   // no slower than w12, so no point in a separate function
    x264_pixel_avg2_w16_neon,
    x264_pixel_avg2_w20_neon,
};

static void (* const x264_mc_copy_wtab_neon[5])( uint8_t *, intptr_t, uint8_t *, intptr_t, int ) =
{
    NULL,
    x264_mc_copy_w4_neon,
    x264_mc_copy_w8_neon,
    NULL,
    x264_mc_copy_w16_neon,
};

static const uint8_t hpel_ref0[16] = {0,1,1,1,0,1,1,1,2,3,3,3,0,1,1,1};
static const uint8_t hpel_ref1[16] = {0,0,0,0,2,2,3,2,2,2,3,2,2,2,3,2};

static void mc_luma_neon( uint8_t *dst,    intptr_t i_dst_stride,
                          uint8_t *src[4], intptr_t i_src_stride,
                          int mvx, int mvy,
                          int i_width, int i_height, const x264_weight_t *weight )
{
    int qpel_idx = ((mvy&3)<<2) + (mvx&3);
    intptr_t offset = (mvy>>2)*i_src_stride + (mvx>>2);
    uint8_t *src1 = src[hpel_ref0[qpel_idx]] + offset;
    if ( (mvy&3) == 3 )             // explict if() to force conditional add
        src1 += i_src_stride;

    if( qpel_idx & 5 ) /* qpel interpolation needed */
    {
        uint8_t *src2 = src[hpel_ref1[qpel_idx]] + offset + ((mvx&3) == 3);
        x264_pixel_avg_wtab_neon[i_width>>2](
                dst, i_dst_stride, src1, i_src_stride,
                src2, i_height );
        if( weight->weightfn )
            weight->weightfn[i_width>>2]( dst, i_dst_stride, dst, i_dst_stride, weight, i_height );
    }
    else if( weight->weightfn )
        weight->weightfn[i_width>>2]( dst, i_dst_stride, src1, i_src_stride, weight, i_height );
    else
        x264_mc_copy_wtab_neon[i_width>>2]( dst, i_dst_stride, src1, i_src_stride, i_height );
}

static uint8_t *get_ref_neon( uint8_t *dst,   intptr_t *i_dst_stride,
                              uint8_t *src[4], intptr_t i_src_stride,
                              int mvx, int mvy,
                              int i_width, int i_height, const x264_weight_t *weight )
{
    int qpel_idx = ((mvy&3)<<2) + (mvx&3);
    intptr_t offset = (mvy>>2)*i_src_stride + (mvx>>2);
    uint8_t *src1 = src[hpel_ref0[qpel_idx]] + offset;
    if ( (mvy&3) == 3 )             // explict if() to force conditional add
        src1 += i_src_stride;

    if( qpel_idx & 5 ) /* qpel interpolation needed */
    {
        uint8_t *src2 = src[hpel_ref1[qpel_idx]] + offset + ((mvx&3) == 3);
        x264_pixel_avg_wtab_neon[i_width>>2](
                dst, *i_dst_stride, src1, i_src_stride,
                src2, i_height );
        if( weight->weightfn )
            weight->weightfn[i_width>>2]( dst, *i_dst_stride, dst, *i_dst_stride, weight, i_height );
        return dst;
    }
    else if( weight->weightfn )
    {
        weight->weightfn[i_width>>2]( dst, *i_dst_stride, src1, i_src_stride, weight, i_height );
        return dst;
    }
    else
    {
        *i_dst_stride = i_src_stride;
        return src1;
    }
}

static void hpel_filter_neon( uint8_t *dsth, uint8_t *dstv, uint8_t *dstc, uint8_t *src,
                              intptr_t stride, int width, int height, int16_t *buf )
{
    intptr_t realign = (intptr_t)src & 15;
    src -= realign;
    dstv -= realign;
    dstc -= realign;
    dsth -= realign;
    width += realign;
    while( height-- )
    {
        x264_hpel_filter_v_neon( dstv, src, buf+8, stride, width );
        x264_hpel_filter_c_neon( dstc, buf+8, width );
        x264_hpel_filter_h_neon( dsth, src, width );
        dsth += stride;
        dstv += stride;
        dstc += stride;
        src  += stride;
    }
}


void x264_plane_copy_core_16x_neon( pixel *dst, intptr_t i_dst, pixel *src, intptr_t i_src, int w, int h )
{
	  asm volatile(
	  "    sub         %1,%1,%4                    \n\t"
	  "    sub         %3,%3,%4                    \n\t"
	  "1:                                          \n\t"
	  "    sub         r12,%4,#63                  \n\t"
      "2:                                          \n\t"
	  "    pld         [%2,#128]                   \n\t"
	  "    vld1.8      {d0,d1,d2,d3},[%2]!         \n\t"
	  "    vld1.8      {d4,d5,d6,d7},[%2]!         \n\t"
	  "    vst1.8      {d0,d1,d2,d3},[%0,:128]!    \n\t"
	  "    vst1.8      {d4,d5,d6,d7},[%0,:128]!    \n\t"
	  "    subs        r12,r12,#64                 \n\t"
	  "    bgt         2b                          \n\t"
	  "    adds        r12,r12,#63                 \n\t"
	  "    ble         4f                          \n\t"
	  "3:                                          \n\t"
	  "    vld1.8      {d0,d1},[%2]!               \n\t"
	  "    vst1.8      {d0,d1},[%0,:128]!          \n\t"
	  "    subs        r12,r12,#16                 \n\t"
	  "    bgt         3b                          \n\t"
	  "4:                                          \n\t"
	  "    add         %0,%0,%1                    \n\t"
	  "    add         %2,%2,%3                    \n\t"
	  "    subs        %5,%5,#1                    \n\t"
	  "    bgt         1b                          \n\t"

   :"+r"(dst),"+r"(i_dst),"+r"(src),"+r"(i_src),"+r"(w),"+r"(h)
   ::"r12","q0","q1","q2","q3","memory"
   );
}

void x264_plane_copy_interleave_core_8x_neon( pixel *dst,  intptr_t i_dst,
                                               pixel *srcu, intptr_t i_srcu,
                                               pixel *srcv, intptr_t i_srcv, int w, int h )
{
	  asm volatile(
	  "    sub         %1,%1,%6,lsl #1           \n\t"
	  "    sub         %3,%3,%6                  \n\t"
	  "    sub         %5,%5,%6                  \n\t"

	  "1:                                        \n\t"
	  "    sub         r12,%6,#31                \n\t"
	  "2:                                        \n\t"
	  "    pld         [%2,#128]                 \n\t"
	  "    pld         [%4,#128]                 \n\t"

	  "    vld1.8      {Q0},[%2]!                \n\t"
	  "    vld1.8      {Q1},[%4]!                \n\t"
	  "    vld1.8      {Q2},[%2]!                \n\t"
	  "    vld1.8      {Q3},[%4]!                \n\t"

	  "    vst2.8      {Q0,Q1},[%0,:128]!        \n\t"
	  "    vst2.8      {Q2,Q3},[%0,:128]!        \n\t"
	  "    subs        r12,r12,#32               \n\t"
	  "    bgt         2b                        \n\t"
	  "    adds        r12,r12,#31               \n\t"
	  "    ble         4f                        \n\t"

	  "3:                                        \n\t"
	  "    vld1.8      {d0},[%2]!                \n\t"
	  "    vld1.8      {d1},[%4]!                \n\t"
	  "    vst2.8      {d0,d1},[%0,:128]!        \n\t"
	  "    subs        r12,r12,#8                \n\t"
	  "    bgt         3b                        \n\t"
	  "4:                                        \n\t"
	  "    add         %0,%0,%1                  \n\t"
	  "    add         %2,%2,%3                  \n\t"
	  "    add         %4,%4,%5                  \n\t"
	  "    subs        %7,%7,#1                  \n\t"
	  "    bgt         1b                        \n\t"

   //    0          1           2           3           4           5         6       7
   :"+r"(dst),"+r"(i_dst),"+r"(srcu),"+r"(i_srcu),"+r"(srcv),"+r"(i_srcv),"+r"(w),"+r"(h)
   ::"r12","q0","q1","q2","q3","memory"
   );
}


static void x264_plane_copy_neon( pixel *dst, intptr_t i_dst, pixel *src, intptr_t i_src, int w, int h )
{
    int c_w = 16/sizeof(pixel) - 1;
    
    if( w < 256 ) 
    { // tiny resolutions don't want non-temporal hints. dunno the exact threshold.
        x264_plane_copy_c( dst, i_dst, src, i_src, w, h );
    }
    else if( !(w&c_w) ) 
    {
        x264_plane_copy_core_16x_neon( dst, i_dst, src, i_src, w, h );
    }
    else if( i_src > 0 ) 
    {
        // have to use plain memcpy on the last line (in memory order) to avoid overreading src
        x264_plane_copy_core_16x_neon( dst, i_dst, src, i_src, (w+c_w)&~c_w, h-1 );
        memcpy( dst+i_dst*(h-1), src+i_src*(h-1), w*sizeof(pixel) );
    }
    else
    {
        memcpy( dst, src, w*sizeof(pixel) );
        x264_plane_copy_core_16x_neon( dst+i_dst, i_dst, src+i_src, i_src, (w+c_w)&~c_w, h-1 );
    }
}






static void x264_plane_copy_interleave_neon( pixel *dst,  intptr_t i_dst,
                                              pixel *srcu, intptr_t i_srcu,
                                              pixel *srcv, intptr_t i_srcv, int w, int h )
{
    if( !(w&15) ) 
    {
        x264_plane_copy_interleave_core_8x_neon( dst, i_dst, srcu, i_srcu, srcv, i_srcv, w, h );
    }
    else if( w < 16 || (i_srcu ^ i_srcv) ) 
    {
        x264_plane_copy_interleave_c( dst, i_dst, srcu, i_srcu, srcv, i_srcv, w, h );
    }
    else if( i_srcu > 0 ) 
    {
        x264_plane_copy_interleave_core_8x_neon( dst, i_dst, srcu, i_srcu, srcv, i_srcv, (w+15)&~15, h-1 );
        x264_plane_copy_interleave_c( dst+i_dst*(h-1), 0, srcu+i_srcu*(h-1), 0, srcv+i_srcv*(h-1), 0, w, 1 );
    }
    else 
    {
        x264_plane_copy_interleave_c( dst, 0, srcu, 0, srcv, 0, w, 1 );
        x264_plane_copy_interleave_core_8x_neon( dst+i_dst, i_dst, srcu+i_srcu, i_srcu, srcv+i_srcv, i_srcv, (w+15)&~15, h-1 );
    }
}









#endif // !HIGH_BIT_DEPTH

void x264_mc_init_arm( int cpu, x264_mc_functions_t *pf )
{
    if( !(cpu&X264_CPU_ARMV6) )
        return;

#if !HIGH_BIT_DEPTH
    pf->prefetch_fenc_420 = x264_prefetch_fenc_arm;
    pf->prefetch_fenc_422 = x264_prefetch_fenc_arm; /* FIXME */
    pf->prefetch_ref  = x264_prefetch_ref_arm;
#endif // !HIGH_BIT_DEPTH

    if( !(cpu&X264_CPU_NEON) )
        return;

#if !HIGH_BIT_DEPTH
    // added by sensong 201305 start
    pf->store_interleave_chroma = store_interleave_chroma_neon;//pass
    pf->load_deinterleave_chroma_fdec = load_deinterleave_chroma_fdec_neon;//pass
    pf->load_deinterleave_chroma_fenc = load_deinterleave_chroma_fenc_neon;//pass
	// end
	
    pf->copy_16x16_unaligned = x264_mc_copy_w16_neon;
    pf->copy[PIXEL_16x16] = x264_mc_copy_w16_aligned_neon;
    pf->copy[PIXEL_8x8]   = x264_mc_copy_w8_neon;
    pf->copy[PIXEL_4x4]   = x264_mc_copy_w4_neon;

    pf->avg[PIXEL_16x16] = x264_pixel_avg_16x16_neon;
    pf->avg[PIXEL_16x8]  = x264_pixel_avg_16x8_neon;
    pf->avg[PIXEL_8x16]  = x264_pixel_avg_8x16_neon;
    pf->avg[PIXEL_8x8]   = x264_pixel_avg_8x8_neon;
    pf->avg[PIXEL_8x4]   = x264_pixel_avg_8x4_neon;
    pf->avg[PIXEL_4x8]   = x264_pixel_avg_4x8_neon;
    pf->avg[PIXEL_4x4]   = x264_pixel_avg_4x4_neon;
    pf->avg[PIXEL_4x2]   = x264_pixel_avg_4x2_neon;

    pf->weight    = x264_mc_wtab_neon;
    pf->offsetadd = x264_mc_offsetadd_wtab_neon;
    pf->offsetsub = x264_mc_offsetsub_wtab_neon;
    pf->weight_cache = x264_weight_cache_neon;

    pf->mc_chroma = x264_mc_chroma_neon;
    pf->mc_luma = mc_luma_neon;
    pf->get_ref = get_ref_neon;
    pf->hpel_filter = hpel_filter_neon;
    pf->frame_init_lowres_core = x264_frame_init_lowres_core_neon;
    
    //added by sensong 201404
    pf->plane_copy            = x264_plane_copy_neon;
    pf->plane_copy_interleave = x264_plane_copy_interleave_neon;
    //
    
    
#endif // !HIGH_BIT_DEPTH

// Apple's gcc stupidly cannot align stack variables, and ALIGNED_ARRAY can't work on structs
//#ifndef SYS_MACOSX
#if (!defined(SYS_MACOSX) && !defined(TARGET_OS_IPHONE))
    pf->memcpy_aligned  = x264_memcpy_aligned_neon;
#endif
    pf->memzero_aligned = x264_memzero_aligned_neon;
}
