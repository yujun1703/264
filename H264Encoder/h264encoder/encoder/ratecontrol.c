/*****************************************************************************
* ratecontrol.c: ratecontrol
*****************************************************************************
* Copyright (C) 2005-2012 x264 project
*
* Authors: Loren Merritt <lorenm@u.washington.edu>
*          Michael Niedermayer <michaelni@gmx.at>
*          Gabriel Bouvigne <gabriel.bouvigne@joost.com>
*          Jason Garrett-Glaser <darkshikari@gmail.com>
*          M錸s Rullg錼d <mru@mru.ath.cx>
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
#define  _CRT_SECURE_NO_WARNINGS

#define _ISOC99_SOURCE
#undef NDEBUG // always check asserts, the speed effect is far too small to disable them
#include <math.h>
#include <float.h>
#include <sys/time.h>

#include "common/common.h"
#include "ratecontrol.h"
#include "me.h"
#include "set.h"

#ifndef WIN32
#define FALSE 0
#define TRUE 1
#define BOOL int
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

#endif
//fred
#define PREDICTOR_TYPE_SUM  5
// mdou
#define SHOW_QP 0
#define RC_MODEL_HISTORY 21
#define RC_MODEL_HISTORY_SP	7
static const float THETA = 1.3636F;
static const float OMEGA = 0.9F;
static const float MINVALUE = 4.0F;
static const float MAXVALUE = 2.0F;
static const float MINVALUE_SP = 2.0F;
static const float MAXVALUE_SP = 10.0F;
void rc_init_seq(x264_t *h);
int updateQP_P( x264_t *h );
int updateQP_SP( x264_t *h );
void updateRCModel_P (x264_t *h);
void updateRCModel_SP (x264_t *h);
void rc_init_GOP(x264_t *h, int np);
void rc_init_GF(x264_t *h, int np);
typedef struct
{
	int pict_type;
	int frame_type;
	int kept_as_ref;
	double qscale;
	int mv_bits;
	int tex_bits;
	int misc_bits;
	uint64_t expected_bits; /*total expected bits up to the current frame (current one excluded)*/
	double expected_vbv;
	double new_qscale;
	int new_qp;
	int i_count;
	int p_count;
	int s_count;
	float blurred_complexity;
	char direct_mode;
	int16_t weight[3][2];
	int16_t i_weight_denom[2];
	int refcount[16];
	int refs;
	int64_t i_duration;
	int64_t i_cpb_duration;
} ratecontrol_entry_t;

typedef struct
{
	float coeff;
	float count;
	float decay;
	float offset;
} predictor_t;

struct x264_ratecontrol_t
{
	//fred drop frame
// 	int buffer_over_bits;//size of buffer filling
	int drop_count;//num of droped frames
// 	int last_pred_qp;
	int drop_count_GOP;  // mdou
	
#if RC_MAD
	int	header_bits;  // header bits
	int header_bits_P;
	int text_bits; // texture bits
	int header_bits_BU;  // header bits in BU
	int text_bit_BU; // texture bits in BU
	int header_bits_MB;  // header bits in MB
	int text_bits_MB;  // texture bits in MB
	int num_GOP;  // 1, 2, 3, ...
	int64_t sum_MAD_BU;// MAD of BasicUnit
	int BU_left;  // number of BU left
	int BU_coded;
	int BU_total;  // number of BU in frame
	int MBs_in_BU;  // num of MB in one BasicUnit
	int init_qp_GOP; // changed every GOP
	int ave_qp_lastGOP; // average QP of P frame in last GOP
	int ave_qp_I_Frame; // average QP of last I frame
	int ave_qp_lastGOP_P;
	int ave_qp_lastGOP_SP;
	int frame_qp; // calculated before everage frame
	int m_Qc;  // QP
	int *MAD_MB;
	double target_buffer;
	int64_t curr_buffer; 
	int64_t bits_remain;  // bits left
	double GAMMAP; // parameter              
	double BETAP;
	double MADPictureC1; // param
	double MADPictureC2;
	double PMADPictureC1;
	double PMADPictureC2;
	double PPictureMAD [RC_MODEL_HISTORY];
	double PictureMAD  [RC_MODEL_HISTORY];
	double ReferenceMAD[RC_MODEL_HISTORY];
	double m_rgQp      [RC_MODEL_HISTORY];
	double m_rgRp      [RC_MODEL_HISTORY];
	double Pm_rgQp     [RC_MODEL_HISTORY];
	double Pm_rgRp     [RC_MODEL_HISTORY];
	// SP
	double MADPictureC1_SP; // param
	double MADPictureC2_SP;
	double PMADPictureC1_SP;
	double PMADPictureC2_SP;
	double PPictureMAD_SP [RC_MODEL_HISTORY_SP];
	double PictureMAD_SP  [RC_MODEL_HISTORY_SP];
	double ReferenceMAD_SP[RC_MODEL_HISTORY_SP];
	double m_rgQp_SP      [RC_MODEL_HISTORY_SP];
	double m_rgRp_SP      [RC_MODEL_HISTORY_SP];
	double Pm_rgQp_SP     [RC_MODEL_HISTORY_SP];
	double Pm_rgRp_SP     [RC_MODEL_HISTORY_SP];
	// P parameter
	double m_X1;
	double m_X2;
	double Pm_X1;
	double Pm_X2;
	int    Pm_Qp;
	int    MADm_windowSize;
	int    m_windowSize;
	// SP parameter
	double m_X1_SP;
	double m_X2_SP;
	double Pm_X1_SP;
	double Pm_X2_SP;
	int    Pm_Qp_SP;
	int    MADm_windowSize_SP;
	int    m_windowSize_SP;
	int    PAveHeaderBits1_SP;
	int    PAveHeaderBits2_SP;
	int    PAveHeaderBits3_SP;
	// end
	int    sum_qp_frame; // sum qp of one frame
	int    ave_qp_frame; // average qp of one frame
	int	   ave_qp_frame_SP; // SP
	int	   ave_qp_frame_P;
	int    ave_qp_frame_first;
	int    PAveHeaderBits1;
	int    PAveHeaderBits2;
	int    PAveHeaderBits3;
	
	int    frame_coded;    // include drop frame
	int	   frame_coded_P; // PwithSP or PnoSP
	int    frame_coded_SP; // SP
	int    sum_qp_GOP; // sum of qp(P frame) in GOP, reset before a new GOP
	int	   sum_qp_GOP_P;
	int    sum_qp_GOP_SP;
	int    coded_Pframe_inGOP; // P frame coded in GOP, include drop frame
	int	   num_P_lastGOP;
	int	   num_SP_lastGOP;
	int    num_P_left;  // number of P frame, include SP and P
	int	   num_SP_left;	
	int	   num_P_before;  // before current frame, after SP or GF
	int    num_P_in_GOP;   // P include SP
	int	   num_SP_in_GOP;  // SP
	int    max_first;
	double    ratio_sp;
	double pred_MAD_BU; // MAD of BU (pred)
	double pred_sum_MAD_BU; // rc->CurrentBUMAD*rc->CurrentBUMAD up to now
	double prev_frame_MAD_BU;
	int    max_delta_qp_BU;  // max delta QP between BU
	int	   max_delta_qp_BU_check;  // if drop frame, max delta qp + 1
	int    qp_last_Pframe; // for clip
	int    QPLastGOP;
	double *BUPFMAD;  // pre
	double *BUCFMAD;  // current
	double *BUPFMAD_SP; // last SP
	int   overdue_GOP;  // over, target_bits<0
// 	int   overdue_first_frame;   
	int    Xp;
	int    target_bits;  // target bit
	int    target_bits_frame;  // target bit of current frame
	
	int    upper_bound1, upper_bound2, lower_bound; // clip
	int	   last_bits_P;
	int	   last_bits_SP;
	double delta_target_frame;

	double bitrate_SP;
	double bitrate_frame;
	double bit_GOP;
	temporal_levle_idc curr_level_last;

#endif

	/* constants */
	int b_abr;
	int b_2pass;
	int b_vbv;
	int b_vbv_min_rate;
	double fps;
	double bitrate;
	double rate_tolerance;
	double qcompress;
	int nmb;                    /* number of macroblocks in a frame */
	int qp_constant[3];

	/* current frame */
	ratecontrol_entry_t *rce;
	int qp;                     /* qp for current frame */
	float qpm;                  /* qp for current macroblock: precise float for AQ */
	float qpa_rc;               /* average of macroblocks' qp before aq */
	float qpa_rc_prev;
	int   qpa_aq;               /* average of macroblocks' qp after aq */
	int   qpa_aq_prev;
	float qp_novbv;             /* QP for the current frame if 1-pass VBV was disabled. */

	/* VBV stuff */
	double buffer_size;
	int64_t buffer_fill_final;
	double buffer_fill;         /* planned buffer, if all in-progress frames hit their bit budget */
	double buffer_rate;         /* # of bits added to buffer_fill after each frame */
	double vbv_max_rate;        /* # of bits added to buffer_fill per second */
	predictor_t *pred;          /* predict frame size from satd */
	int single_frame_vbv;
	double rate_factor_max_increment; /* Don't allow RF above (CRF + this value). */

	/* ABR stuff */
	int    last_satd;
	double last_rceq;
	double cplxr_sum;           /* sum of bits*qscale/rceq */
	double expected_bits_sum;   /* sum of qscale2bits after rceq, ratefactor, and overflow, only includes finished frames */
	int64_t filler_bits_sum;    /* sum in bits of finished frames' filler data */
	double wanted_bits_window;  /* target bitrate * window */
	double cbr_decay;
	double short_term_cplxsum;
	double short_term_cplxcount;
	double rate_factor_constant;
	double ip_offset;
	double pb_offset;

	/* 2pass stuff */
	FILE *p_stat_file_out;
	char *psz_stat_file_tmpname;
	FILE *p_mbtree_stat_file_out;
	char *psz_mbtree_stat_file_tmpname;
	char *psz_mbtree_stat_file_name;
	FILE *p_mbtree_stat_file_in;

	int num_entries;            /* number of ratecontrol_entry_ts */
	ratecontrol_entry_t *entry; /* FIXME: copy needed data and free this once init is done */
	double last_qscale;
	double last_qscale_for[3];  /* last qscale for a specific pict type, used for max_diff & ipb factor stuff */
	int last_non_b_pict_type;
	double accum_p_qp;          /* for determining I-frame quant */
	double accum_p_norm;
	double last_accum_p_norm;
	double lmin[3];             /* min qscale by frame type */
	double lmax[3];
	double lstep;               /* max change (multiply) in qscale per frame */
	uint16_t *qp_buffer[2];     /* Global buffers for converting MB-tree quantizer data. */
	int qpbuf_pos;              /* In order to handle pyramid reordering, QP buffer acts as a stack.
								* This value is the current position (0 or 1). */

	/* MBRC stuff */
	float frame_size_estimated; /* Access to this variable must be atomic: double is
								* not atomic on all arches we care about */
	double frame_size_maximum;  /* Maximum frame size due to MinCR */
	double frame_size_planned;
	double slice_size_planned;
	predictor_t (*row_pred)[2];
	predictor_t row_preds[3][2];
	predictor_t *pred_b_from_p; /* predict B-frame size from P-frame satd */
	int bframes;                /* # consecutive B-frames before this P-frame */
	int bframe_bits;            /* total cost of those frames */

	int i_zones;
	x264_zone_t *zones;
	x264_zone_t *prev_zone;

	/* hrd stuff */
	int initial_cpb_removal_delay;
	int initial_cpb_removal_delay_offset;
	double nrt_first_access_unit; /* nominal removal time */
	double previous_cpb_final_arrival_time;
	uint64_t hrd_multiply_denom;

    int i_time_interval;
    int i_timestamp;
};

static int x264_GetTickCount()
{
#ifdef WIN32
    return GetTickCount();
#else
    int unCurrentTime;
   // int	gettimeofday(struct timeval * __restrict, void * __restrict);

    struct timeval Current;
    
  //  if(gettimeofday(&Current, NULL) != 0)
    if(gettimeofday(&Current,NULL)!=0)
    {
        unCurrentTime = 0;
    }
    else
    {
        unCurrentTime = Current.tv_sec * 1000  + Current.tv_usec/1000;
    }
    return unCurrentTime;
#endif
}

void x264_nal_start( x264_t *h, int i_type, int i_ref_idc );
int x264_nal_end( x264_t *h );
int x264_encoder_encapsulate_nals( x264_t *h, int start );


static int parse_zones( x264_t *h );
static int init_pass2(x264_t *);
static float rate_estimate_qscale( x264_t *h );
static int update_vbv( x264_t *h, int bits );
static void update_vbv_plan( x264_t *h, int overhead );
static float predict_size( predictor_t *p, float q, float var );
static void update_predictor( predictor_t *p, float q, float var, float bits );

#define CMP_OPT_FIRST_PASS( opt, param_val )\
{\
	if( ( p = strstr( opts, opt "=" ) ) && sscanf( p, opt "=%d" , &i ) && param_val != i )\
{\
	x264_log( h, X264_LOG_ERROR, "different " opt " setting than first pass (%d vs %d)\n", param_val, i );\
	return -1;\
}\
}
/*
//fred 0[p]  1[b]  2[i]  3[sp]  4[psp] 5[gf]
static inline int predictor_id( x264_t* h )
{
	int id;

// 	if ( tp_lvl_2 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
// 		id = (int)SLICE_TYPE_I + 3;
// 	else if ( tp_lvl_1 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
//         id = (int)SLICE_TYPE_P;
//     else if ( tp_lvl_0 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
//         id = (int)SLICE_TYPE_P;
//     else
// 		id = h->sh.i_type;
	if ( tp_lvl_2 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
		id = (int)SLICE_TYPE_I + 3;
	else if ( tp_lvl_1 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
		id = (int)SLICE_TYPE_P;
	else if ( tp_lvl_0 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
		id = (int)SLICE_TYPE_P;
	else
		id = h->sh.i_type;

	return id;
}
*/
/* Terminology:
* qp = h.264's quantizer
* qscale = linearized quantizer = Lagrange multiplier
*/
static inline float qp2qscale( float qp )
{
	return 0.85f * powf( 2.0f, ( qp - 12.0f ) / 6.0f );
}
static inline float qscale2qp( float qscale )
{
	return 12.0f + 6.0f * log2f( qscale/0.85f );
}
/* Texture bitrate is not quite inversely proportional to qscale,
* probably due the the changing number of SKIP blocks.
* MV bits level off at about qp<=12, because the lambda used
* for motion estimation is constant there. */
static inline double qscale2bits( ratecontrol_entry_t *rce, double qscale )
{
	if( qscale<0.1 )
		qscale = 0.1;
	return (rce->tex_bits + .1) * pow( rce->qscale / qscale, 1.1 )
		+ rce->mv_bits * pow( X264_MAX(rce->qscale, 1) / X264_MAX(qscale, 1), 0.5 )
		+ rce->misc_bits;
}

static ALWAYS_INLINE uint32_t ac_energy_var( uint64_t sum_ssd, int shift, x264_frame_t *frame, int i, int b_store )
{
	uint32_t sum = (uint32_t)sum_ssd;
	uint32_t ssd = (uint32_t)(sum_ssd >> 32);
	if( b_store )
	{
		frame->i_pixel_sum[i] += sum;
		frame->i_pixel_ssd[i] += ssd;
	}
	return (uint32_t)(ssd - ((uint64_t)sum * sum >> shift));
}

static ALWAYS_INLINE uint32_t ac_energy_plane( x264_t *h, int mb_x, int mb_y, x264_frame_t *frame, int i, int b_chroma, int b_field, int b_store )
{
	int height = b_chroma ? 16>>CHROMA_V_SHIFT : 16;
	int stride = frame->i_stride[i];
	int offset = b_field
		? 16 * mb_x + height * (mb_y&~1) * stride + (mb_y&1) * stride
		: 16 * mb_x + height * mb_y * stride;
	stride <<= b_field;
	if( b_chroma )
	{
		ALIGNED_ARRAY_16( pixel, pix,[FENC_STRIDE*16] );
		int chromapix = h->luma2chroma_pixel[PIXEL_16x16];
		int shift = 7 - CHROMA_V_SHIFT;

		h->mc.load_deinterleave_chroma_fenc( pix, frame->plane[1] + offset, stride, height );
		return ac_energy_var( h->pixf.var[chromapix]( pix,               FENC_STRIDE ), shift, frame, 1, b_store )
			+ ac_energy_var( h->pixf.var[chromapix]( pix+FENC_STRIDE/2, FENC_STRIDE ), shift, frame, 2, b_store );
	}
	else
		return ac_energy_var( h->pixf.var[PIXEL_16x16]( frame->plane[i] + offset, stride ), 8, frame, i, b_store );
}

// Find the total AC energy of the block in all planes.
static NOINLINE uint32_t x264_ac_energy_mb( x264_t *h, int mb_x, int mb_y, x264_frame_t *frame )
{
	/* This function contains annoying hacks because GCC has a habit of reordering emms
	* and putting it after floating point ops.  As a result, we put the emms at the end of the
	* function and make sure that its always called before the float math.  Noinline makes
	* sure no reordering goes on. */
	uint32_t var;
	x264_prefetch_fenc( h, frame, mb_x, mb_y );
	if( h->mb.b_adaptive_mbaff )
	{
		/* We don't know the super-MB mode we're going to pick yet, so
		* simply try both and pick the lower of the two. */
		uint32_t var_interlaced, var_progressive;
		var_interlaced   = ac_energy_plane( h, mb_x, mb_y, frame, 0, 0, 1, 1 );
		var_progressive  = ac_energy_plane( h, mb_x, mb_y, frame, 0, 0, 0, 0 );
		if( CHROMA444 )
		{
			var_interlaced  += ac_energy_plane( h, mb_x, mb_y, frame, 1, 0, 1, 1 );
			var_progressive += ac_energy_plane( h, mb_x, mb_y, frame, 1, 0, 0, 0 );
			var_interlaced  += ac_energy_plane( h, mb_x, mb_y, frame, 2, 0, 1, 1 );
			var_progressive += ac_energy_plane( h, mb_x, mb_y, frame, 2, 0, 0, 0 );
		}
		else
		{
			var_interlaced  += ac_energy_plane( h, mb_x, mb_y, frame, 1, 1, 1, 1 );
			var_progressive += ac_energy_plane( h, mb_x, mb_y, frame, 1, 1, 0, 0 );
		}
		var = X264_MIN( var_interlaced, var_progressive );
	}
	else
	{
		var  = ac_energy_plane( h, mb_x, mb_y, frame, 0, 0, PARAM_INTERLACED, 1 );
		if( CHROMA444 )
		{
			var += ac_energy_plane( h, mb_x, mb_y, frame, 1, 0, PARAM_INTERLACED, 1 );
			var += ac_energy_plane( h, mb_x, mb_y, frame, 2, 0, PARAM_INTERLACED, 1 );
		}
		else
			var += ac_energy_plane( h, mb_x, mb_y, frame, 1, 1, PARAM_INTERLACED, 1 );
	}
	x264_emms();
	return var;
}

void x264_adaptive_quant_frame( x264_t *h, x264_frame_t *frame, float *quant_offsets )
{
	/* constants chosen to result in approximately the same overall bitrate as without AQ.
	* FIXME: while they're written in 5 significant digits, they're only tuned to 2. */
	float strength;
	float avg_adj = 0.f;
	/* Initialize frame stats */
	for( int i = 0; i < 3; i++ )
	{
		frame->i_pixel_sum[i] = 0;
		frame->i_pixel_ssd[i] = 0;
	}

	/* Degenerate cases */
	if( h->param.rc.i_aq_mode == X264_AQ_NONE || h->param.rc.f_aq_strength == 0 )
	{
		/* Need to init it anyways for MB tree */
		if( h->param.rc.i_aq_mode && h->param.rc.f_aq_strength == 0 )
		{
			if( quant_offsets )
			{
				for( int mb_xy = 0; mb_xy < h->mb.i_mb_count; mb_xy++ )
					frame->f_qp_offset[mb_xy] = frame->f_qp_offset_aq[mb_xy] = quant_offsets[mb_xy];
				if( h->frames.b_have_lowres )
					for( int mb_xy = 0; mb_xy < h->mb.i_mb_count; mb_xy++ )
						frame->i_inv_qscale_factor[mb_xy] = x264_exp2fix8( frame->f_qp_offset[mb_xy] );
			}
			else
			{
				memset( frame->f_qp_offset, 0, h->mb.i_mb_count * sizeof(float) );
				memset( frame->f_qp_offset_aq, 0, h->mb.i_mb_count * sizeof(float) );
				if( h->frames.b_have_lowres )
					for( int mb_xy = 0; mb_xy < h->mb.i_mb_count; mb_xy++ )
						frame->i_inv_qscale_factor[mb_xy] = 256;
			}
		}
		/* Need variance data for weighted prediction */
		if( h->param.analyse.i_weighted_pred )
		{
			for( int mb_y = 0; mb_y < h->mb.i_mb_height; mb_y++ )
				for( int mb_x = 0; mb_x < h->mb.i_mb_width; mb_x++ )
					x264_ac_energy_mb( h, mb_x, mb_y, frame );
		}
		else
			return;
	}
	/* Actual adaptive quantization */
	else
	{
		if( h->param.rc.i_aq_mode == X264_AQ_AUTOVARIANCE )
		{
			float bit_depth_correction = powf(1 << (BIT_DEPTH-8), 0.5f);
			float avg_adj_pow2 = 0.f;
			for( int mb_y = 0; mb_y < h->mb.i_mb_height; mb_y++ )
				for( int mb_x = 0; mb_x < h->mb.i_mb_width; mb_x++ )
				{
					uint32_t energy = x264_ac_energy_mb( h, mb_x, mb_y, frame );
					float qp_adj = powf( energy + 1.0f, 0.125f );
					frame->f_qp_offset[mb_x + mb_y*h->mb.i_mb_stride] = qp_adj;
					avg_adj += qp_adj;
					avg_adj_pow2 += qp_adj * qp_adj;
				}
				avg_adj /= h->mb.i_mb_count;
				avg_adj_pow2 /= h->mb.i_mb_count;
				strength = h->param.rc.f_aq_strength * avg_adj / bit_depth_correction;
				avg_adj = avg_adj - 0.5f * (avg_adj_pow2 - (14.f * bit_depth_correction)) / avg_adj;
		}
		else
			strength = h->param.rc.f_aq_strength * 1.0397f;

		for( int mb_y = 0; mb_y < h->mb.i_mb_height; mb_y++ )
			for( int mb_x = 0; mb_x < h->mb.i_mb_width; mb_x++ )
			{
				float qp_adj;
				int mb_xy = mb_x + mb_y*h->mb.i_mb_stride;
				if( h->param.rc.i_aq_mode == X264_AQ_AUTOVARIANCE )
				{
					qp_adj = frame->f_qp_offset[mb_xy];
					qp_adj = strength * (qp_adj - avg_adj);
				}
				else
				{
					uint32_t energy = x264_ac_energy_mb( h, mb_x, mb_y, frame );
					qp_adj = strength * (x264_log2( X264_MAX(energy, 1) ) - (14.427f + 2*(BIT_DEPTH-8)));
				}
				if( quant_offsets )
					qp_adj += quant_offsets[mb_xy];
				frame->f_qp_offset[mb_xy] =
					frame->f_qp_offset_aq[mb_xy] = qp_adj;
				if( h->frames.b_have_lowres )
					frame->i_inv_qscale_factor[mb_xy] = x264_exp2fix8(qp_adj);
			}
	}

	/* Remove mean from SSD calculation */
	for( int i = 0; i < 3; i++ )
	{
		uint64_t ssd = frame->i_pixel_ssd[i];
		uint64_t sum = frame->i_pixel_sum[i];
		int width  = 16*h->mb.i_mb_width  >> (i && CHROMA_H_SHIFT);
		int height = 16*h->mb.i_mb_height >> (i && CHROMA_V_SHIFT);
		frame->i_pixel_ssd[i] = ssd - (sum * sum + width * height / 2) / (width * height);
	}
}

int x264_macroblock_tree_read( x264_t *h, x264_frame_t *frame, float *quant_offsets )
{
	x264_ratecontrol_t *rc = h->rc;
	uint8_t i_type_actual = rc->entry[frame->i_frame].pict_type;

	if( rc->entry[frame->i_frame].kept_as_ref )
	{
		uint8_t i_type;
		if( rc->qpbuf_pos < 0 )
		{
			do
			{
				rc->qpbuf_pos++;

				if( !fread( &i_type, 1, 1, rc->p_mbtree_stat_file_in ) )
					goto fail;
				if( fread( rc->qp_buffer[rc->qpbuf_pos], sizeof(uint16_t), h->mb.i_mb_count, rc->p_mbtree_stat_file_in ) != h->mb.i_mb_count )
					goto fail;

				if( i_type != i_type_actual && rc->qpbuf_pos == 1 )
				{
					x264_log( h, X264_LOG_ERROR, "MB-tree frametype %d doesn't match actual frametype %d.\n", i_type, i_type_actual );
					return -1;
				}
			} while( i_type != i_type_actual );
		}

		for( int i = 0; i < h->mb.i_mb_count; i++ )
		{
			frame->f_qp_offset[i] = ((float)(int16_t)endian_fix16( rc->qp_buffer[rc->qpbuf_pos][i] )) * (1/256.0f);
			if( h->frames.b_have_lowres )
				frame->i_inv_qscale_factor[i] = x264_exp2fix8(frame->f_qp_offset[i]);
		}
		rc->qpbuf_pos--;
	}
	else
		x264_stack_align( x264_adaptive_quant_frame, h, frame, quant_offsets );
	return 0;
fail:
	x264_log( h, X264_LOG_ERROR, "Incomplete MB-tree stats file.\n" );
	return -1;
}
#if 0
int x264_reference_build_list_optimal( x264_t *h )
{
	ratecontrol_entry_t *rce = h->rc->rce;
	x264_frame_t *frames[16];
	x264_weight_t weights[16][3];
	int refcount[16];

	if( rce->refs != h->i_ref[0] )
		return -1;

	memcpy( frames, h->fref[0], sizeof(frames) );
	memcpy( refcount, rce->refcount, sizeof(refcount) );
	memcpy( weights, h->fenc->weight, sizeof(weights) );
	memset( &h->fenc->weight[1][0], 0, sizeof(x264_weight_t[15][3]) );

	/* For now don't reorder ref 0; it seems to lower quality
	in most cases due to skips. */
	for( int ref = 1; ref < h->i_ref[0]; ref++ )
	{
		int max = -1;
		int bestref = 1;

		for( int i = 1; i < h->i_ref[0]; i++ )
			/* Favor lower POC as a tiebreaker. */
			COPY2_IF_GT( max, refcount[i], bestref, i );

		/* FIXME: If there are duplicates from frames other than ref0 then it is possible
		* that the optimal ordering doesnt place every duplicate. */

		refcount[bestref] = -1;
		h->fref[0][ref] = frames[bestref];
		memcpy( h->fenc->weight[ref], weights[bestref], sizeof(weights[bestref]) );
	}

	return 0;
}
#endif

static char *x264_strcat_filename( char *input, char *suffix )
{
	char *output = (char *)x264_malloc( strlen( input ) + strlen( suffix ) + 1 );
	if( !output )
		return NULL;
	strcpy( output, input );
	strcat( output, suffix );
	return output;
}

void x264_ratecontrol_init_reconfigurable( x264_t *h, int b_init )
{
	x264_ratecontrol_t *rc = h->rc;
	uint32_t i_time_scale;
	if( !b_init && rc->b_2pass )
		return;

	//fred for drop
	rc->drop_count = 0;
	// mdou
	rc->drop_count_GOP = 0;

	// added by timlong
	//rc->wanted_bits_window = 1.0 * rc->bitrate / rc->fps;
	//rc->last_non_b_pict_type = SLICE_TYPE_I;
	h->sps->vui.i_num_units_in_tick = h->param.i_timebase_num;
	i_time_scale = h->sps->vui.i_time_scale;
	h->sps->vui.i_time_scale = h->param.i_timebase_den * 2;
	h->i_prev_duration = ((uint64_t)h->param.i_fps_den * h->sps->vui.i_time_scale) / ((uint64_t)h->param.i_fps_num * h->sps->vui.i_num_units_in_tick);

	/* FIXME: use integers */
	if( h->param.i_fps_num > 0 && h->param.i_fps_den > 0 )
		rc->fps = (float) h->param.i_fps_num / h->param.i_fps_den;
	else
		rc->fps = 25.0;

	// end
#if RC_MAD
	if (b_init && h->param.rc.use_MAD)
	{
		rc_init_seq(h);
	}
#endif

	if( h->param.rc.i_rc_method == X264_RC_CRF )
	{
		/* Arbitrary rescaling to make CRF somewhat similar to QP.
		* Try to compensate for MB-tree's effects as well. */
		double base_cplx = h->mb.i_mb_count * (h->param.i_bframe ? 120 : 80);
		double mbtree_offset = h->param.rc.b_mb_tree ? (1.0-h->param.rc.f_qcompress)*13.5 : 0;
		rc->rate_factor_constant = pow( base_cplx, 1 - rc->qcompress )
			/ qp2qscale( h->param.rc.f_rf_constant + (float)mbtree_offset + QP_BD_OFFSET );
	}

	if( h->param.rc.i_vbv_max_bitrate > 0 && h->param.rc.i_vbv_buffer_size > 0 )
	{
		/* We don't support changing the ABR bitrate right now,
		so if the stream starts as CBR, keep it CBR. */
		if( rc->b_vbv_min_rate )
			h->param.rc.i_vbv_max_bitrate = h->param.rc.i_bitrate;

		if( h->param.rc.i_vbv_buffer_size < (int)(h->param.rc.i_vbv_max_bitrate / rc->fps) )
		{
			h->param.rc.i_vbv_buffer_size = (int)(h->param.rc.i_vbv_max_bitrate / rc->fps);
			x264_log( h, X264_LOG_WARNING, "VBV buffer size cannot be smaller than one frame, using %d kbit\n",
				h->param.rc.i_vbv_buffer_size );
		}

		int vbv_buffer_size = h->param.rc.i_vbv_buffer_size * 1000;
		int vbv_max_bitrate = h->param.rc.i_vbv_max_bitrate * 1000;

		/* Init HRD */
		if( h->param.i_nal_hrd && b_init )
		{
			h->sps->vui.hrd.i_cpb_cnt = 1;
			h->sps->vui.hrd.b_cbr_hrd = h->param.i_nal_hrd == X264_NAL_HRD_CBR;
			h->sps->vui.hrd.i_time_offset_length = 0;

#define BR_SHIFT  6
#define CPB_SHIFT 4

			int bitrate = 1000*h->param.rc.i_vbv_max_bitrate;
			int bufsize = 1000*h->param.rc.i_vbv_buffer_size;

			// normalize HRD size and rate to the value / scale notation
			h->sps->vui.hrd.i_bit_rate_scale = x264_clip3( x264_ctz( bitrate ) - BR_SHIFT, 0, 15 );
			h->sps->vui.hrd.i_bit_rate_value = bitrate >> ( h->sps->vui.hrd.i_bit_rate_scale + BR_SHIFT );
			h->sps->vui.hrd.i_bit_rate_unscaled = h->sps->vui.hrd.i_bit_rate_value << ( h->sps->vui.hrd.i_bit_rate_scale + BR_SHIFT );
			h->sps->vui.hrd.i_cpb_size_scale = x264_clip3( x264_ctz( bufsize ) - CPB_SHIFT, 0, 15 );
			h->sps->vui.hrd.i_cpb_size_value = bufsize >> ( h->sps->vui.hrd.i_cpb_size_scale + CPB_SHIFT );
			h->sps->vui.hrd.i_cpb_size_unscaled = h->sps->vui.hrd.i_cpb_size_value << ( h->sps->vui.hrd.i_cpb_size_scale + CPB_SHIFT );

#undef CPB_SHIFT
#undef BR_SHIFT

			// arbitrary
#define MAX_DURATION 0.5

			int max_cpb_output_delay = (int)X264_MIN( h->param.i_keyint_max * MAX_DURATION * h->sps->vui.i_time_scale / h->sps->vui.i_num_units_in_tick, INT_MAX );
			int max_dpb_output_delay = (int)(h->sps->vui.i_max_dec_frame_buffering * MAX_DURATION * h->sps->vui.i_time_scale / h->sps->vui.i_num_units_in_tick);
			int max_delay = (int)(90000.0 * (double)h->sps->vui.hrd.i_cpb_size_unscaled / h->sps->vui.hrd.i_bit_rate_unscaled + 0.5);

			h->sps->vui.hrd.i_initial_cpb_removal_delay_length = 2 + x264_clip3( 32 - x264_clz( max_delay ), 4, 22 );
			h->sps->vui.hrd.i_cpb_removal_delay_length = x264_clip3( 32 - x264_clz( max_cpb_output_delay ), 4, 31 );
			h->sps->vui.hrd.i_dpb_output_delay_length  = x264_clip3( 32 - x264_clz( max_dpb_output_delay ), 4, 31 );

#undef MAX_DURATION

			vbv_buffer_size = h->sps->vui.hrd.i_cpb_size_unscaled;
			vbv_max_bitrate = h->sps->vui.hrd.i_bit_rate_unscaled;
		}
		else if( h->param.i_nal_hrd && !b_init )
		{
			x264_log( h, X264_LOG_WARNING, "VBV parameters cannot be changed when NAL HRD is in use\n" );
			return;
		}
		h->sps->vui.hrd.i_bit_rate_unscaled = vbv_max_bitrate;
		h->sps->vui.hrd.i_cpb_size_unscaled = vbv_buffer_size;

		if( rc->b_vbv_min_rate )
			rc->bitrate = h->param.rc.i_bitrate * 1000.;
		rc->buffer_rate = vbv_max_bitrate / rc->fps;
		rc->vbv_max_rate = vbv_max_bitrate;
		rc->buffer_size = vbv_buffer_size;
		rc->single_frame_vbv = rc->buffer_rate * 1.1 > rc->buffer_size;
		rc->cbr_decay = 1.0 - rc->buffer_rate / rc->buffer_size * 0.5 * X264_MAX(0, 1.5 - rc->buffer_rate * rc->fps / rc->bitrate);

		if( h->param.rc.i_rc_method == X264_RC_CRF && h->param.rc.f_rf_constant_max )
		{
			rc->rate_factor_max_increment = h->param.rc.f_rf_constant_max - h->param.rc.f_rf_constant;
			if( rc->rate_factor_max_increment <= 0 )
			{
				x264_log( h, X264_LOG_WARNING, "CRF max must be greater than CRF\n" );
				rc->rate_factor_max_increment = 0;
			}
		}

		if( b_init )
		{
			if( h->param.rc.f_vbv_buffer_init > 1. )
				h->param.rc.f_vbv_buffer_init = (float)x264_clip3f( h->param.rc.f_vbv_buffer_init / h->param.rc.i_vbv_buffer_size, 0, 1 );
			h->param.rc.f_vbv_buffer_init = (float)x264_clip3f( X264_MAX( h->param.rc.f_vbv_buffer_init, rc->buffer_rate / rc->buffer_size ), 0, 1);
			rc->buffer_fill_final = (int64_t)(rc->buffer_size * h->param.rc.f_vbv_buffer_init * h->sps->vui.i_time_scale);
			rc->b_vbv = 1;
			rc->b_vbv_min_rate = !rc->b_2pass
				&& h->param.rc.i_rc_method == X264_RC_ABR
				&& h->param.rc.i_vbv_max_bitrate <= h->param.rc.i_bitrate;

// 			rc->buffer_over_bits = 0;//fred            
		}
		else
		{
			rc->buffer_fill_final = rc->buffer_fill_final*h->sps->vui.i_time_scale/i_time_scale;
		}
	}
}


// timlong added param: bInit   
int x264_ratecontrol_new( x264_t *h, int bInit)
{
	x264_ratecontrol_t *rc;

	x264_emms();

	// mod by timlong
	if(bInit)
	{
		CHECKED_MALLOCZERO(x264_ratecontrol_t *, h->rc, h->param.i_threads * sizeof(x264_ratecontrol_t) );
	}

	rc = h->rc;
#if RC_MAD
	h->param.rc.use_MAD = 1;
	if ((h->param.intra_period == 0) ||(h->param.rc.b_mb_tree) || (h->param.rc.i_lookahead) 
		||(h->mb.b_adaptive_mbaff) ||(SLICE_MBAFF) ||(MB_INTERLACED) || (PARAM_INTERLACED) || (rc->b_2pass)||(h->param.analyse.intra &X264_ANALYSE_I8x8) 
        ||(BIT_DEPTH!=8) )
	{
		h->param.rc.use_MAD = 0;
	}
#endif

	rc->b_abr = h->param.rc.i_rc_method != X264_RC_CQP && !h->param.rc.b_stat_read;
	rc->b_2pass = h->param.rc.i_rc_method == X264_RC_ABR && h->param.rc.b_stat_read;

	/* FIXME: use integers */
	if( h->param.i_fps_num > 0 && h->param.i_fps_den > 0 )
		rc->fps = (float) h->param.i_fps_num / h->param.i_fps_den;
	else
		rc->fps = 25.0;

	if( h->param.rc.b_mb_tree )
	{
		h->param.rc.f_pb_factor = 1;
		rc->qcompress = 1;
	}
	else
		rc->qcompress = h->param.rc.f_qcompress;

	rc->bitrate = h->param.rc.i_bitrate * 1000.;
	rc->rate_tolerance = h->param.rc.f_rate_tolerance;
	rc->nmb = h->mb.i_mb_count;
	rc->last_non_b_pict_type = -1;
	rc->cbr_decay = 1.0;

	if( h->param.rc.i_rc_method == X264_RC_CRF && h->param.rc.b_stat_read )
	{
		x264_log( h, X264_LOG_ERROR, "constant rate-factor is incompatible with 2pass.\n" );
		return -1;
	}

	x264_ratecontrol_init_reconfigurable( h, 1 );

	if( h->param.i_nal_hrd )
	{
		uint64_t denom = (uint64_t)h->sps->vui.hrd.i_bit_rate_unscaled * h->sps->vui.i_time_scale;
		uint64_t num = 180000;
		x264_reduce_fraction64( &num, &denom );
		rc->hrd_multiply_denom = 180000 / num;

		double bits_required = log2( (double)(180000) / rc->hrd_multiply_denom )
			+ log2((double)( h->sps->vui.i_time_scale ))
			+ log2((double)( h->sps->vui.hrd.i_cpb_size_unscaled ));
		if( bits_required >= 63 )
		{
			x264_log( h, X264_LOG_ERROR, "HRD with very large timescale and bufsize not supported\n" );
			return -1;
		}
	}

	if( rc->rate_tolerance < 0.01 )
	{
		x264_log( h, X264_LOG_WARNING, "bitrate tolerance too small, using .01\n" );
		rc->rate_tolerance = 0.01;
	}

	h->mb.b_variable_qp = rc->b_vbv || h->param.rc.i_aq_mode;

	if( rc->b_abr )
	{
		/* FIXME ABR_INIT_QP is actually used only in CRF */
#define ABR_INIT_QP (( h->param.rc.i_rc_method == X264_RC_CRF ? h->param.rc.f_rf_constant : 24 ) + QP_BD_OFFSET)
		rc->accum_p_norm = .01;
		rc->accum_p_qp = ABR_INIT_QP * rc->accum_p_norm;
		/* estimated ratio that produces a reasonable QP for the first I-frame */
		rc->cplxr_sum = .01 * pow( 7.0e5, rc->qcompress ) * pow( h->mb.i_mb_count, 0.5 );
		rc->wanted_bits_window = 1.0 * rc->bitrate / rc->fps;
		rc->last_non_b_pict_type = SLICE_TYPE_I;
	}

	rc->ip_offset = 6.0 * log2f( h->param.rc.f_ip_factor );
	rc->pb_offset = 6.0 * log2f( h->param.rc.f_pb_factor );
	rc->qp_constant[SLICE_TYPE_P] = h->param.rc.i_qp_constant;
	rc->qp_constant[SLICE_TYPE_I] = (int)x264_clip3( h->param.rc.i_qp_constant - rc->ip_offset + 0.5, 0, QP_MAX );
	rc->qp_constant[SLICE_TYPE_B] = (int)x264_clip3( h->param.rc.i_qp_constant + rc->pb_offset + 0.5, 0, QP_MAX );
	h->mb.ip_offset = (int)(rc->ip_offset + 0.5);

	rc->lstep = pow( 2, h->param.rc.i_qp_step / 6.0 );
	rc->last_qscale = qp2qscale( 26 );
	int num_preds = h->param.b_sliced_threads * h->param.i_threads + 1;

	// mod by timlong
	if( bInit )
	{
#if RC_MAD
			rc->prev_frame_MAD_BU = 1.0;
			rc->pred_MAD_BU = 1.0;
			rc->target_bits = 0;
			rc->lower_bound = 0;
			rc->upper_bound1 = INT_MAX;
			rc->upper_bound2 = INT_MAX;
			
			rc->ave_qp_frame   = 0;
			rc->ave_qp_frame_P   = 0;
			rc->ave_qp_frame_SP = 0;
			rc->m_Qc          = 0;
			rc->ave_qp_lastGOP    = 0;
			
			CHECKED_MALLOC(int *, rc->MAD_MB, sizeof(int)*h->mb.i_mb_width*h->mb.i_mb_height);
			CHECKED_MALLOC(double*, rc->BUPFMAD,sizeof(double)*h->mb.i_mb_height);
			// init
			memset(rc->BUPFMAD,0,sizeof(double)*h->mb.i_mb_height);
			CHECKED_MALLOC(double*, rc->BUCFMAD,sizeof(double)*h->mb.i_mb_height);
			CHECKED_MALLOC(double*, rc->BUPFMAD_SP,sizeof(double)*h->mb.i_mb_height);
			memset(rc->BUPFMAD_SP,0,sizeof(double)*h->mb.i_mb_height);
#endif
		CHECKED_MALLOC(predictor_t *, rc->pred, PREDICTOR_TYPE_SUM * sizeof(predictor_t) * num_preds );
		CHECKED_MALLOC(predictor_t *, rc->pred_b_from_p, sizeof(predictor_t) );

    	for( int i = 0; i < 3; i++ )//0[p]  1[b]  2[i]  3[sp]  4[psp] 5[gf]
    	{
    		rc->last_qscale_for[i    ] = qp2qscale( ABR_INIT_QP );
//     		rc->last_qscale_for[i + 3] = qp2qscale( ABR_INIT_QP );
    		rc->lmin[i] = qp2qscale( h->param.rc.i_qp_min );
        rc->lmax[i] = qp2qscale( h->param.rc.i_qp_max );
        for( int j = 0; j < num_preds; j++ )
        {
            rc->pred[i+j*PREDICTOR_TYPE_SUM].coeff= 2.0;
            rc->pred[i+j*PREDICTOR_TYPE_SUM].count= 1.0;
            rc->pred[i+j*PREDICTOR_TYPE_SUM].decay= 0.5;
            rc->pred[i+j*PREDICTOR_TYPE_SUM].offset= 0.0;
        }
		for( int j = 0; j < 2; j++ )
		{
			rc->row_preds[i][j].coeff= .25;
			rc->row_preds[i][j].count= 1.0;
			rc->row_preds[i][j].decay= 0.5;
			rc->row_preds[i][j].offset= 0.0;
		}
	}
	*rc->pred_b_from_p = rc->pred[0];

// 	//fred for gf :0[p]  1[b]  2[i]  3[sp]  4[psp] 5[gf]
//     	for( int j = 0; j < num_preds; j++ )
//     	{
//     		rc->pred[ 5 + j*PREDICTOR_TYPE_SUM ].coeff= 8.0;
//     		rc->pred[ 5 + j*PREDICTOR_TYPE_SUM ].count= 1.0;
//     		rc->pred[ 5 + j*PREDICTOR_TYPE_SUM ].decay= 0.5;
//     		rc->pred[ 5 + j*PREDICTOR_TYPE_SUM ].offset= 0.0;
//     	}
    }

	//fred comment no use
#if 0 

	if( parse_zones( h ) < 0 )
	{
		x264_log( h, X264_LOG_ERROR, "failed to parse zones\n" );
		return -1;
	}

	/* Load stat file and init 2pass algo */
	if( h->param.rc.b_stat_read )
	{
		char *p, *stats_in, *stats_buf;

		/* read 1st pass stats */
		assert( h->param.rc.psz_stat_in );
		stats_buf = stats_in = x264_slurp_file( h->param.rc.psz_stat_in );
		if( !stats_buf )
		{
			x264_log( h, X264_LOG_ERROR, "ratecontrol_init: can't open stats file\n" );
			return -1;
		}
		if( h->param.rc.b_mb_tree )
		{
			char *mbtree_stats_in = x264_strcat_filename( h->param.rc.psz_stat_in, ".mbtree" );
			if( !mbtree_stats_in )
				return -1;
			rc->p_mbtree_stat_file_in = fopen( mbtree_stats_in, "rb" );
			x264_free( mbtree_stats_in );
			if( !rc->p_mbtree_stat_file_in )
			{
				x264_log( h, X264_LOG_ERROR, "ratecontrol_init: can't open mbtree stats file\n" );
				return -1;
			}
		}

		/* check whether 1st pass options were compatible with current options */
		if( strncmp( stats_buf, "#options:", 9 ) )
		{
			x264_log( h, X264_LOG_ERROR, "options list in stats file not valid\n" );
			return -1;
		}

		float res_factor, res_factor_bits;
		{
			int i, j;
			uint32_t k, l;
			char *opts = stats_buf;
			stats_in = strchr( stats_buf, '\n' );
			if( !stats_in )
				return -1;
			*stats_in = '\0';
			stats_in++;
			if( sscanf( opts, "#options: %dx%d", &i, &j ) != 2 )
			{
				x264_log( h, X264_LOG_ERROR, "resolution specified in stats file not valid\n" );
				return -1;
			}
			else if( h->param.rc.b_mb_tree && (i != h->param.i_width || j != h->param.i_height)  )
			{
				x264_log( h, X264_LOG_ERROR, "MB-tree doesn't support different resolution than 1st pass (%dx%d vs %dx%d)\n",
					h->param.i_width, h->param.i_height, i, j );
				return -1;
			}
			res_factor = (float)h->param.i_width * h->param.i_height / (i*j);
			/* Change in bits relative to resolution isn't quite linear on typical sources,
			* so we'll at least try to roughly approximate this effect. */
			res_factor_bits = powf( res_factor, 0.7 );

			if( ( p = strstr( opts, "timebase=" ) ) && sscanf( p, "timebase=%u/%u", &k, &l ) != 2 )
			{
				x264_log( h, X264_LOG_ERROR, "timebase specified in stats file not valid\n" );
				return -1;
			}
			if( k != h->param.i_timebase_num || l != h->param.i_timebase_den )
			{
				x264_log( h, X264_LOG_ERROR, "timebase mismatch with 1st pass (%u/%u vs %u/%u)\n",
					h->param.i_timebase_num, h->param.i_timebase_den, k, l );
				return -1;
			}

			CMP_OPT_FIRST_PASS( "bitdepth", BIT_DEPTH );
			CMP_OPT_FIRST_PASS( "weightp", X264_MAX( 0, h->param.analyse.i_weighted_pred ) );
			CMP_OPT_FIRST_PASS( "bframes", h->param.i_bframe );
			CMP_OPT_FIRST_PASS( "b_pyramid", h->param.i_bframe_pyramid );
			CMP_OPT_FIRST_PASS( "intra_refresh", h->param.b_intra_refresh );
			CMP_OPT_FIRST_PASS( "open_gop", h->param.b_open_gop );
			CMP_OPT_FIRST_PASS( "bluray_compat", h->param.b_bluray_compat );

			if( (p = strstr( opts, "interlaced=" )) )
			{
				char *current = h->param.b_interlaced ? h->param.b_tff ? "tff" : "bff" : h->param.b_fake_interlaced ? "fake" : "0";
				char buf[5];
				sscanf( p, "interlaced=%4s", buf );
				if( strcmp( current, buf ) )
				{
					x264_log( h, X264_LOG_ERROR, "different interlaced setting than first pass (%s vs %s)\n", current, buf );
					return -1;
				}
			}

			if( (p = strstr( opts, "keyint=" )) )
			{
				p += 7;
				char buf[13] = "infinite ";
				if( h->param.i_keyint_max != X264_KEYINT_MAX_INFINITE )
					sprintf( buf, "%d ", h->param.i_keyint_max );
				if( strncmp( p, buf, strlen(buf) ) )
				{
					x264_log( h, X264_LOG_ERROR, "different keyint setting than first pass (%.*s vs %.*s)\n",
						strlen(buf)-1, buf, strcspn(p, " "), p );
					return -1;
				}
			}

			if( strstr( opts, "qp=0" ) && h->param.rc.i_rc_method == X264_RC_ABR )
				x264_log( h, X264_LOG_WARNING, "1st pass was lossless, bitrate prediction will be inaccurate\n" );

			if( !strstr( opts, "direct=3" ) && h->param.analyse.i_direct_mv_pred == X264_DIRECT_PRED_AUTO )
			{
				x264_log( h, X264_LOG_WARNING, "direct=auto not used on the first pass\n" );
				h->mb.b_direct_auto_write = 1;
			}

			if( ( p = strstr( opts, "b_adapt=" ) ) && sscanf( p, "b_adapt=%d", &i ) && i >= X264_B_ADAPT_NONE && i <= X264_B_ADAPT_TRELLIS )
				h->param.i_bframe_adaptive = i;
			else if( h->param.i_bframe )
			{
				x264_log( h, X264_LOG_ERROR, "b_adapt method specified in stats file not valid\n" );
				return -1;
			}

			if( (h->param.rc.b_mb_tree || h->param.rc.i_vbv_buffer_size) && ( p = strstr( opts, "rc_lookahead=" ) ) && sscanf( p, "rc_lookahead=%d", &i ) )
				h->param.rc.i_lookahead = i;
		}

		/* find number of pics */
		p = stats_in;
		int num_entries;
		for( num_entries = -1; p; num_entries++ )
			p = strchr( p + 1, ';' );
		if( !num_entries )
		{
			x264_log( h, X264_LOG_ERROR, "empty stats file\n" );
			return -1;
		}
		rc->num_entries = num_entries;

		if( h->param.i_frame_total < rc->num_entries && h->param.i_frame_total > 0 )
		{
			x264_log( h, X264_LOG_WARNING, "2nd pass has fewer frames than 1st pass (%d vs %d)\n",
				h->param.i_frame_total, rc->num_entries );
		}
		if( h->param.i_frame_total > rc->num_entries )
		{
			x264_log( h, X264_LOG_ERROR, "2nd pass has more frames than 1st pass (%d vs %d)\n",
				h->param.i_frame_total, rc->num_entries );
			return -1;
		}

		// mod by timlong
		if(bInit)
		{
			CHECKED_MALLOCZERO(ratecontrol_entry_t *, rc->entry, rc->num_entries * sizeof(ratecontrol_entry_t) );
		}
		else
		{
			memset(rc->entry, 0, rc->num_entries * sizeof(ratecontrol_entry_t));
		}

		/* init all to skipped p frames */
		for( int i = 0; i < rc->num_entries; i++ )
		{
			ratecontrol_entry_t *rce = &rc->entry[i];
			rce->pict_type = SLICE_TYPE_P;
			rce->qscale = rce->new_qscale = qp2qscale( 20 );
			rce->misc_bits = rc->nmb + 10;
			rce->new_qp = 0;
		}

		/* read stats */
		p = stats_in;
		for( int i = 0; i < rc->num_entries; i++ )
		{
			ratecontrol_entry_t *rce;
			int frame_number;
			char pict_type;
			int e;
			char *next;
			float qp;
			int ref;

			next= strchr(p, ';');
			if( next )
				*next++ = 0; //sscanf is unbelievably slow on long strings
			e = sscanf( p, " in:%d ", &frame_number );

			if( frame_number < 0 || frame_number >= rc->num_entries )
			{
				x264_log( h, X264_LOG_ERROR, "bad frame number (%d) at stats line %d\n", frame_number, i );
				return -1;
			}
			rce = &rc->entry[frame_number];
			rce->direct_mode = 0;

			e += sscanf( p, " in:%*d out:%*d type:%c dur:%lld cpbdur:%lld q:%f tex:%d mv:%d misc:%d imb:%d pmb:%d smb:%d d:%c",
				&pict_type, &rce->i_duration, &rce->i_cpb_duration, &qp, &rce->tex_bits,
				&rce->mv_bits, &rce->misc_bits, &rce->i_count, &rce->p_count,
				&rce->s_count, &rce->direct_mode );
			rce->tex_bits  *= res_factor_bits;
			rce->mv_bits   *= res_factor_bits;
			rce->misc_bits *= res_factor_bits;
			rce->i_count   *= res_factor;
			rce->p_count   *= res_factor;
			rce->s_count   *= res_factor;

			p = strstr( p, "ref:" );
			if( !p )
				goto parse_error;
			p += 4;
			for( ref = 0; ref < 16; ref++ )
			{
				if( sscanf( p, " %d", &rce->refcount[ref] ) != 1 )
					break;
				p = strchr( p+1, ' ' );
				if( !p )
					goto parse_error;
			}
			rce->refs = ref;

			/* find weights */
			rce->i_weight_denom[0] = rce->i_weight_denom[1] = -1;
			char *w = strchr( p, 'w' );
			if( w )
			{
				int count = sscanf( w, "w:%hd,%hd,%hd,%hd,%hd,%hd,%hd,%hd",
					&rce->i_weight_denom[0], &rce->weight[0][0], &rce->weight[0][1],
					&rce->i_weight_denom[1], &rce->weight[1][0], &rce->weight[1][1],
					&rce->weight[2][0], &rce->weight[2][1] );
				if( count == 3 )
					rce->i_weight_denom[1] = -1;
				else if ( count != 8 )
					rce->i_weight_denom[0] = rce->i_weight_denom[1] = -1;
			}

			if( pict_type != 'b' )
				rce->kept_as_ref = 1;
			switch( pict_type )
			{
			case 'I':
				rce->frame_type = X264_TYPE_IDR;
				rce->pict_type  = SLICE_TYPE_I;
				break;
			case 'i':
				rce->frame_type = X264_TYPE_I;
				rce->pict_type  = SLICE_TYPE_I;
				break;
			case 'P':
				rce->frame_type = X264_TYPE_P;
				rce->pict_type  = SLICE_TYPE_P;
				break;
			case 'B':
				rce->frame_type = X264_TYPE_BREF;
				rce->pict_type  = SLICE_TYPE_B;
				break;
			case 'b':
				rce->frame_type = X264_TYPE_B;
				rce->pict_type  = SLICE_TYPE_B;
				break;
			default:  e = -1; break;
			}
			if( e < 12 )
			{
parse_error:
				x264_log( h, X264_LOG_ERROR, "statistics are damaged at line %d, parser out=%d\n", i, e );
				return -1;
			}
			rce->qscale = qp2qscale( qp );
			p = next;
		}

		x264_free( stats_buf );

		if( h->param.rc.i_rc_method == X264_RC_ABR )
		{
			if( init_pass2( h ) < 0 )
				return -1;
		} /* else we're using constant quant, so no need to run the bitrate allocation */
	}

	/* Open output file */
	/* If input and output files are the same, output to a temp file
	* and move it to the real name only when it's complete */
	if( h->param.rc.b_stat_write )
	{
		char *p;
		rc->psz_stat_file_tmpname = x264_strcat_filename( h->param.rc.psz_stat_out, ".temp" );
		if( !rc->psz_stat_file_tmpname )
			return -1;

		rc->p_stat_file_out = fopen( rc->psz_stat_file_tmpname, "wb" );
		if( rc->p_stat_file_out == NULL )
		{
			x264_log( h, X264_LOG_ERROR, "ratecontrol_init: can't open stats file\n" );
			return -1;
		}

		p = x264_param2string( &h->param, 1 );
		if( p )
			fprintf( rc->p_stat_file_out, "#options: %s\n", p );
		x264_free( p );
		if( h->param.rc.b_mb_tree && !h->param.rc.b_stat_read )
		{
			rc->psz_mbtree_stat_file_tmpname = x264_strcat_filename( h->param.rc.psz_stat_out, ".mbtree.temp" );
			rc->psz_mbtree_stat_file_name = x264_strcat_filename( h->param.rc.psz_stat_out, ".mbtree" );
			if( !rc->psz_mbtree_stat_file_tmpname || !rc->psz_mbtree_stat_file_name )
				return -1;

			rc->p_mbtree_stat_file_out = fopen( rc->psz_mbtree_stat_file_tmpname, "wb" );
			if( rc->p_mbtree_stat_file_out == NULL )
			{
				x264_log( h, X264_LOG_ERROR, "ratecontrol_init: can't open mbtree stats file\n" );
				return -1;
			}
		}
	}

	if( h->param.rc.b_mb_tree && (h->param.rc.b_stat_read || h->param.rc.b_stat_write) )
	{
		// mod by timlong
		if(bInit)
		{
			CHECKED_MALLOC(uint16_t *, rc->qp_buffer[0], h->mb.i_mb_count * sizeof(uint16_t) );
		}

		if( h->param.i_bframe_pyramid && h->param.rc.b_stat_read )
		{
			if(bInit)
			{
				CHECKED_MALLOC(uint16_t *, rc->qp_buffer[1], h->mb.i_mb_count * sizeof(uint16_t) );
			}
		}

		rc->qpbuf_pos = -1;
	}

#endif

	for( int i = 0; i<h->param.i_threads; i++ )
	{
		h->thread[i]->rc = rc+i;
		if( i )
		{
			rc[i] = rc[0];
			h->thread[i]->param = h->param;
			h->thread[i]->mb.b_variable_qp = h->mb.b_variable_qp;
			h->thread[i]->mb.ip_offset = h->mb.ip_offset;
		}
	}

	return 0;
fail:
	return -1;
}
//fred comment no use
#if 0

static int parse_zone( x264_t *h, x264_zone_t *z, char *p )
{
	int len = 0;
	char *tok, UNUSED *saveptr=NULL;
	z->param = NULL;
	z->f_bitrate_factor = 1;
	if( 3 <= sscanf(p, "%d,%d,q=%d%n", &z->i_start, &z->i_end, &z->i_qp, &len) )
		z->b_force_qp = 1;
	else if( 3 <= sscanf(p, "%d,%d,b=%f%n", &z->i_start, &z->i_end, &z->f_bitrate_factor, &len) )
		z->b_force_qp = 0;
	else if( 2 <= sscanf(p, "%d,%d%n", &z->i_start, &z->i_end, &len) )
		z->b_force_qp = 0;
	else
	{
		x264_log( h, X264_LOG_ERROR, "invalid zone: \"%s\"\n", p );
		return -1;
	}
	p += len;
	if( !*p )
		return 0;
	CHECKED_MALLOC(x264_param_t *, z->param, sizeof(x264_param_t) );
	memcpy( z->param, &h->param, sizeof(x264_param_t) );
	z->param->param_free = x264_free;
	while( (tok = strtok_r( p, ",", &saveptr )) )
	{
		char *val = strchr( tok, '=' );
		if( val )
		{
			*val = '\0';
			val++;
		}
		if( x264_param_parse( z->param, tok, val ) )
		{
			x264_log( h, X264_LOG_ERROR, "invalid zone param: %s = %s\n", tok, val );
			return -1;
		}
		p = NULL;
	}
	return 0;
fail:
	return -1;
}

static int parse_zones( x264_t *h )
{
	x264_ratecontrol_t *rc = h->rc;
	if( h->param.rc.psz_zones && !h->param.rc.i_zones )
	{
		char *psz_zones, *p;
		CHECKED_MALLOC(char *, psz_zones, strlen( h->param.rc.psz_zones )+1 );
		strcpy( psz_zones, h->param.rc.psz_zones );
		h->param.rc.i_zones = 1;
		for( p = psz_zones; *p; p++ )
			h->param.rc.i_zones += (*p == '/');
		CHECKED_MALLOC(x264_zone_t *, h->param.rc.zones, h->param.rc.i_zones * sizeof(x264_zone_t) );
		p = psz_zones;
		for( int i = 0; i < h->param.rc.i_zones; i++ )
		{
			int i_tok = strcspn( p, "/" );
			p[i_tok] = 0;
			if( parse_zone( h, &h->param.rc.zones[i], p ) )
				return -1;
			p += i_tok + 1;
		}
		x264_free( psz_zones );
	}

	if( h->param.rc.i_zones > 0 )
	{
		for( int i = 0; i < h->param.rc.i_zones; i++ )
		{
			x264_zone_t z = h->param.rc.zones[i];
			if( z.i_start < 0 || z.i_start > z.i_end )
			{
				x264_log( h, X264_LOG_ERROR, "invalid zone: start=%d end=%d\n",
					z.i_start, z.i_end );
				return -1;
			}
			else if( !z.b_force_qp && z.f_bitrate_factor <= 0 )
			{
				x264_log( h, X264_LOG_ERROR, "invalid zone: bitrate_factor=%f\n",
					z.f_bitrate_factor );
				return -1;
			}
		}

		rc->i_zones = h->param.rc.i_zones + 1;
		CHECKED_MALLOC(x264_zone_t *, rc->zones, rc->i_zones * sizeof(x264_zone_t) );
		memcpy( rc->zones+1, h->param.rc.zones, (rc->i_zones-1) * sizeof(x264_zone_t) );

		// default zone to fall back to if none of the others match
		rc->zones[0].i_start = 0;
		rc->zones[0].i_end = INT_MAX;
		rc->zones[0].b_force_qp = 0;
		rc->zones[0].f_bitrate_factor = 1;
		CHECKED_MALLOC(x264_param_t *, rc->zones[0].param, sizeof(x264_param_t) );
		memcpy( rc->zones[0].param, &h->param, sizeof(x264_param_t) );
		for( int i = 1; i < rc->i_zones; i++ )
		{
			if( !rc->zones[i].param )
				rc->zones[i].param = rc->zones[0].param;
		}
	}

	return 0;
fail:
	return -1;
}
#endif

static x264_zone_t *get_zone( x264_t *h, int frame_num )
{
	for( int i = h->rc->i_zones - 1; i >= 0; i-- )
	{
		x264_zone_t *z = &h->rc->zones[i];
		if( frame_num >= z->i_start && frame_num <= z->i_end )
			return z;
	}
	return NULL;
}

void x264_ratecontrol_summary( x264_t *h )
{
	x264_ratecontrol_t *rc = h->rc;
	if( rc->b_abr && h->param.rc.i_rc_method == X264_RC_ABR && rc->cbr_decay > .9999 )
	{
		double base_cplx = h->mb.i_mb_count * (h->param.i_bframe ? 120 : 80);
		double mbtree_offset = h->param.rc.b_mb_tree ? (1.0-h->param.rc.f_qcompress)*13.5 : 0;
		x264_log( h, X264_LOG_INFO, "final ratefactor: %.2f\n",
			qscale2qp( pow( base_cplx, 1 - rc->qcompress )
			* rc->cplxr_sum / rc->wanted_bits_window ) - mbtree_offset - QP_BD_OFFSET );
	}
}

void x264_ratecontrol_delete( x264_t *h )
{
	x264_ratecontrol_t *rc = h->rc;
	int b_regular_file;

	if( rc->p_stat_file_out )
	{
		b_regular_file = x264_is_regular_file( rc->p_stat_file_out );
		fclose( rc->p_stat_file_out );
		if( h->i_frame >= rc->num_entries && b_regular_file )
			if( rename( rc->psz_stat_file_tmpname, h->param.rc.psz_stat_out ) != 0 )
			{
				x264_log( h, X264_LOG_ERROR, "failed to rename \"%s\" to \"%s\"\n",
					rc->psz_stat_file_tmpname, h->param.rc.psz_stat_out );
			}
			x264_free( rc->psz_stat_file_tmpname );
	}
	if( rc->p_mbtree_stat_file_out )
	{
		b_regular_file = x264_is_regular_file( rc->p_mbtree_stat_file_out );
		fclose( rc->p_mbtree_stat_file_out );
		if( h->i_frame >= rc->num_entries && b_regular_file )
			if( rename( rc->psz_mbtree_stat_file_tmpname, rc->psz_mbtree_stat_file_name ) != 0 )
			{
				x264_log( h, X264_LOG_ERROR, "failed to rename \"%s\" to \"%s\"\n",
					rc->psz_mbtree_stat_file_tmpname, rc->psz_mbtree_stat_file_name );
			}
			x264_free( rc->psz_mbtree_stat_file_tmpname );
			x264_free( rc->psz_mbtree_stat_file_name );
	}
	if( rc->p_mbtree_stat_file_in )
		fclose( rc->p_mbtree_stat_file_in );
#if RC_MAD
		x264_free(rc->MAD_MB);
		x264_free(rc->BUCFMAD);
		x264_free(rc->BUPFMAD);
		x264_free(rc->BUPFMAD_SP);
#endif
	x264_free( rc->pred );
	x264_free( rc->pred_b_from_p );
	x264_free( rc->entry );
	x264_free( rc->qp_buffer[0] );
	x264_free( rc->qp_buffer[1] );
	if( rc->zones )
	{
		x264_free( rc->zones[0].param );
		for( int i = 1; i < rc->i_zones; i++ )
			if( rc->zones[i].param != rc->zones[0].param && rc->zones[i].param->param_free )
				rc->zones[i].param->param_free( rc->zones[i].param );
		x264_free( rc->zones );
	}
	x264_free( rc );
}

static void accum_p_qp_update( x264_t *h, float qp )
{
	x264_ratecontrol_t *rc = h->rc;
	rc->accum_p_qp   *= .95;
	rc->accum_p_norm *= .95;
	rc->accum_p_norm += 1;
	if( h->sh.i_type == SLICE_TYPE_I )
		rc->accum_p_qp += qp + rc->ip_offset;
	else
		rc->accum_p_qp += qp;
}

/* Before encoding a frame, choose a QP for it */
void x264_ratecontrol_start( x264_t *h, int i_force_qp, int overhead )
{
	x264_ratecontrol_t *rc = h->rc;
	ratecontrol_entry_t *rce = NULL;
	x264_zone_t *zone = get_zone( h, h->fenc->i_frame );
	float q;

	x264_emms();
	rc->qpa_rc = 0;
	rc->qpa_rc_prev = 0;
	rc->qpa_aq = 0;
	rc->qpa_aq_prev = 0;

#if RC_MAD
	if (h->param.rc.use_MAD)
	{
		// rc_init_pict
		int tmp_T;

		{
			if (h->param.gf_period)
			{
				if (h->sh.i_type == SLICE_TYPE_I)
				{
					rc_init_GOP(h, h->param.gf_period- 1);
				}
				else if (h->fenc->curr_level == tp_lvl_2) // GF
				{
					rc_init_GF(h, h->param.gf_period - 1);
				}
			}
			else
			{
				if (h->sh.i_type == SLICE_TYPE_I)
				{
					rc_init_GOP(h, h->param.intra_period - 1);
				}
			}
			
			if (( h->sh.i_type == SLICE_TYPE_P  ) &&(h->fenc->curr_level != tp_lvl_2))  // SP, PwithSP, PnoSP
			{
				if((rc->frame_coded_P + rc->frame_coded_SP)>0)// not first P slice
				{
					if ((h->param.sp_period)&&(rc->num_P_before ==0))  // last is SP
					{
						memcpy((void *)rc->BUPFMAD_SP,(void *)rc->BUCFMAD, rc->BU_total * sizeof(double));
					}
					else  // last is P 
					{
						memcpy((void *)rc->BUPFMAD,(void *)rc->BUCFMAD, rc->BU_total * sizeof(double));
					}
					
				}// BUPFMAD  pre MAD
				if ((h->param.rc.use_drop_frame)&&(rc->drop_count_GOP))
				{
					rc->max_delta_qp_BU_check = rc->max_delta_qp_BU +1;
				}
				else
					rc->max_delta_qp_BU_check = rc->max_delta_qp_BU;

				// compute target buffer
				if(rc->num_GOP==1) // first GOP
				{
					if(rc->coded_Pframe_inGOP==1)  // first P
					{
						rc->target_buffer = (double) rc->curr_buffer;  // GF overflow
						rc->delta_target_frame = ((double)rc->curr_buffer)/(rc->num_P_in_GOP - 1);  // GF overflow, divide into each P and SP frame
						rc->target_buffer -= rc->delta_target_frame;
					}
					else if(rc->coded_Pframe_inGOP>1)
						rc->target_buffer -= rc->delta_target_frame;
				}
				else if(rc->num_GOP>1)
				{
					if(rc->coded_Pframe_inGOP==0)
					{
						rc->target_buffer = (double) rc->curr_buffer;
						rc->delta_target_frame = ((double)rc->curr_buffer) / rc->num_P_in_GOP;
						rc->target_buffer -= rc->delta_target_frame;
					}
					else if(rc->coded_Pframe_inGOP>0)
						rc->target_buffer -= rc->delta_target_frame;
				}
			}

			// Compute the target bit for each frame 
			if(( h->sh.i_type == SLICE_TYPE_P  )&&(h->fenc->curr_level != tp_lvl_2))  // SP, PwithSP, PnoSP
			{
				if(((rc->num_GOP == 1)&&((rc->frame_coded_P + rc->frame_coded_SP)>0))|| (rc->num_GOP > 1))  // not first P in seq
				{
					// target bit
					rc->target_bits = (int) (floor(  rc->bits_remain / (rc->num_P_left -rc->num_SP_left + rc->num_SP_left*rc->ratio_sp ) + 0.5));

					// target buffer
					if (h->fenc->curr_level == tp_lvl_1)// not for Pwith SP or PnoSP
					{
						rc->target_bits = (int)(rc->ratio_sp*rc->target_bits);
						tmp_T  = max(0, (int) (floor(rc->bitrate_SP  - rc->GAMMAP * (rc->curr_buffer-rc->target_buffer) + 0.5))); // 0.5
					}
					else
						tmp_T  = max(0, (int) (floor(rc->bitrate_frame  - rc->GAMMAP * (rc->curr_buffer-rc->target_buffer) + 0.5))); // 0.5
					
					rc->target_bits = (int) (floor(rc->BETAP * (rc->target_bits - tmp_T) + tmp_T + 0.5)); // average  0.5
				}
				if (h->fenc->curr_level == tp_lvl_1)
					rc->target_bits_frame = rc->target_bits = x264_clip3(rc->target_bits, min(rc->lower_bound + rc->bitrate_SP, rc->bitrate_SP), rc->upper_bound2);
				else
					rc->target_bits_frame = rc->target_bits = x264_clip3(rc->target_bits, min(rc->lower_bound + rc->bitrate_frame, rc->bitrate_frame), rc->upper_bound2);
			}
		}
		// init
		{
			rc->header_bits  = 0;
			rc->text_bits = 0;

			rc->sum_qp_frame = 0;  // init before a new frame
			rc->header_bits_BU  = 0;
			rc->text_bit_BU = 0;
			rc->sum_MAD_BU = 0;
			rc->BU_left = rc->BU_total;
		}

		// calculate QP for frame
		if (h->fenc->curr_level == tp_lvl_2)  // GF or IDR
		{
			rc->sum_qp_frame = rc->frame_qp = rc->m_Qc = rc->init_qp_GOP;		
			rc->BU_coded = 0;
		}
		else if (h->fenc->curr_level == tp_lvl_1)  // SP
		{
			rc->Pm_Qp--;
			rc->frame_qp = updateQP_SP(h);
		}
		else // Pwith SP or PnoSP
		{
			rc->frame_qp = updateQP_P(h);
		}
		rc->frame_qp = x264_clip3( rc->frame_qp, h->param.rc.i_qp_min, h->param.rc.i_qp_max);
		rc->qpm = rc->frame_qp;
		return;
	}
#endif
	if( zone && (!rc->prev_zone || zone->param != rc->prev_zone->param) )
		x264_encoder_reconfig( h, zone->param );
	rc->prev_zone = zone;
	if (h->fenc->curr_level == tp_lvl_2)// GF or IDR
	{
#if SHOW_QP
		FILE* fp_bit = fopen("x264_bit.txt","a+");
		fprintf(fp_bit,"%d\t",rc->drop_count_GOP);
		fclose(fp_bit);
#endif
	rc->drop_count_GOP = 0;
	}
	if( h->param.rc.b_stat_read )
	{
		int frame = h->fenc->i_frame;
		assert( frame >= 0 && frame < rc->num_entries );
		rce = h->rc->rce = &h->rc->entry[frame];

		if( h->sh.i_type == SLICE_TYPE_B
			&& h->param.analyse.i_direct_mv_pred == X264_DIRECT_PRED_AUTO )
		{
			h->sh.b_direct_spatial_mv_pred = ( rce->direct_mode == 's' );
			h->mb.b_direct_auto_read = ( rce->direct_mode == 's' || rce->direct_mode == 't' );
		}
	}

	if( rc->b_vbv )
	{
		memset( h->fdec->i_row_bits, 0, h->mb.i_mb_height * sizeof(int) );
		memset( h->fdec->f_row_qp, 0, h->mb.i_mb_height * sizeof(float) );
		memset( h->fdec->f_row_qscale, 0, h->mb.i_mb_height * sizeof(float) );
		rc->row_pred = &rc->row_preds[h->sh.i_type];
		rc->buffer_rate = h->fenc->i_cpb_duration * rc->vbv_max_rate * h->sps->vui.i_num_units_in_tick / h->sps->vui.i_time_scale;
		update_vbv_plan( h, overhead );

		const x264_level_t *l = x264_levels;
		while( l->level_idc != 0 && l->level_idc != h->param.i_level_idc )
			l++;

		int mincr = l->mincr;

		if( h->param.b_bluray_compat )
			mincr = 4;

		/* Profiles above High don't require minCR, so just set the maximum to a large value. */
		if( h->sps->i_profile_idc > PROFILE_HIGH )
			rc->frame_size_maximum = 1e9;
		else
		{
			/* The spec has a bizarre special case for the first frame. */
			if( h->i_frame == 0 )
			{
				//384 * ( Max( PicSizeInMbs, fR * MaxMBPS ) + MaxMBPS * ( tr( 0 ) - tr,n( 0 ) ) ) / MinCR
				double fr = 1. / 172;
				int pic_size_in_mbs = h->mb.i_mb_width * h->mb.i_mb_height;
				rc->frame_size_maximum = 384 * BIT_DEPTH * X264_MAX( pic_size_in_mbs, fr*l->mbps ) / mincr;
			}
			else
			{
				//384 * MaxMBPS * ( tr( n ) - tr( n - 1 ) ) / MinCR
				rc->frame_size_maximum = 384 * BIT_DEPTH * ((double)h->fenc->i_cpb_duration * h->sps->vui.i_num_units_in_tick / h->sps->vui.i_time_scale) * l->mbps / mincr;
			}
		}
	}

	if( h->sh.i_type != SLICE_TYPE_B )
		rc->bframes = h->fenc->i_bframes;

	if( rc->b_abr )
	{
		q = qscale2qp( rate_estimate_qscale( h ) );
	}
	else if( rc->b_2pass )
	{
		rce->new_qscale = rate_estimate_qscale( h );
		q = qscale2qp( (float)rce->new_qscale );
	}
	else /* CQP */
	{
		if( h->sh.i_type == SLICE_TYPE_B && h->fdec->b_kept_as_ref )
			q = (float)(( rc->qp_constant[ SLICE_TYPE_B ] + rc->qp_constant[ SLICE_TYPE_P ] ) / 2);
		else
			q = (float)rc->qp_constant[ h->sh.i_type ];

		if( zone )
		{
			if( zone->b_force_qp )
				q += zone->i_qp - rc->qp_constant[SLICE_TYPE_P];
			else
				q -= 6*log2f( zone->f_bitrate_factor );
		}
	}

	if( i_force_qp != X264_QP_AUTO )
		q = i_force_qp - 1.0f;

	q = (float)x264_clip3f( q, h->param.rc.i_qp_min, h->param.rc.i_qp_max );

	
	rc->qp = x264_clip3( (int)(q + 0.5f), 0, QP_MAX );
	h->fdec->f_qp_avg_rc = q;
	h->fdec->f_qp_avg_aq = q;
	rc->qpm = q;
	if( rce )
		rce->new_qp = rc->qp;

	accum_p_qp_update( h, rc->qpm );

	if( h->sh.i_type != SLICE_TYPE_B )
		rc->last_non_b_pict_type = h->sh.i_type;
}

static float predict_row_size( x264_t *h, int y, float qscale )
{
	/* average between two predictors:
	* absolute SATD, and scaled bit cost of the colocated row in the previous frame */
	x264_ratecontrol_t *rc = h->rc;
	float pred_s = predict_size( rc->row_pred[0], qscale, h->fdec->i_row_satd[y] );
	if (h->sh.i_type == SLICE_TYPE_P && h->fenc->curr_level == tp_lvl_2)
	{
		return pred_s;
	}
	else if( h->sh.i_type == SLICE_TYPE_I || qscale >= h->fref[0][0]->f_row_qscale[y] )
	{
		if( h->sh.i_type == SLICE_TYPE_P
			&& h->fref[0][0]->i_type == h->fdec->i_type
			&& h->fref[0][0]->f_row_qscale[y] > 0
			&& h->fref[0][0]->i_row_satd[y] > 0
			&& (abs(h->fref[0][0]->i_row_satd[y] - h->fdec->i_row_satd[y]) < h->fdec->i_row_satd[y]/2))
		{
			float pred_t = h->fref[0][0]->i_row_bits[y] * h->fdec->i_row_satd[y] / h->fref[0][0]->i_row_satd[y]
			* h->fref[0][0]->f_row_qscale[y] / qscale;
			return (pred_s + pred_t) * 0.5f;
		}
		return pred_s;
	}
	/* Our QP is lower than the reference! */
	else
	{
		float pred_intra = predict_size( rc->row_pred[1], qscale, h->fdec->i_row_satds[0][0][y] );
		/* Sum: better to overestimate than underestimate by using only one of the two predictors. */
		return pred_intra + pred_s;
	}
}

static int row_bits_so_far( x264_t *h, int y )
{
	int bits = 0;
	for( int i = h->i_threadslice_start; i <= y; i++ )
		bits += h->fdec->i_row_bits[i];
	return bits;
}

static float predict_row_size_sum( x264_t *h, int y, float qp )
{
	float qscale = qp2qscale( qp );
	float bits = row_bits_so_far( h, y );
	for( int i = y+1; i < h->i_threadslice_end; i++ )
		bits += predict_row_size( h, i, qscale );
	return bits;
}

/* TODO:
*  eliminate all use of qp in row ratecontrol: make it entirely qscale-based.
*  make this function stop being needlessly O(N^2)
*  update more often than once per row? */
int x264_ratecontrol_mb( x264_t *h, int bits )
{
	x264_ratecontrol_t *rc = h->rc;
	const int y = h->mb.i_mb_y;

	h->fdec->i_row_bits[y] += bits;
	//rc->qpa_aq += h->mb.i_qp;
	x264_emms();
	rc->qpa_rc += rc->qpm;
	rc->qpa_aq += h->mb.i_qp;

#if RC_MAD
	if (h->param.rc.use_MAD)
	{
		rc->MAD_MB[h->mb.i_mb_x] = h->mb.pic.diffy;
		rc->sum_MAD_BU += rc->MAD_MB[h->mb.i_mb_x]; 
		// update after encode one MB

		rc->header_bits_MB = bits - h->stat.frame.i_tex_bits_mb;
		rc->text_bits_MB = h->stat.frame.i_tex_bits_mb;

		rc->text_bits += rc->text_bits_MB;  // frame texture bits
		rc->header_bits  += rc->header_bits_MB;
		
		rc->header_bits_BU  += rc->header_bits_MB; // BU texture bits
		rc->text_bit_BU += rc->text_bits_MB;
	}
#endif
	if( h->mb.i_mb_x != h->mb.i_mb_width - 1 )
		return 0;

    if (h->param.em_rc_mode == em_mode_dsktop)
        return 0;
    
// 	x264_emms();
// 	rc->qpa_rc += rc->qpm * h->mb.i_mb_width;
// 	rc->qpa_aq += h->mb.i_qp * h->mb.i_mb_width;

	if( !rc->b_vbv )
		return 0;
#if RC_MAD
	if (h->param.rc.use_MAD)  // each BU end
	{
		if (h->mb.i_mb_y != h->mb.i_mb_height - 1)
		{// end of BU

			if ( h->fenc->curr_level == tp_lvl_2 )  // I frame or GF(P)
			{
				float coded_bits, target_bits;
				rc->BU_coded ++;
				coded_bits = rc->text_bits + rc->header_bits;
				target_bits = rc->bitrate/(rc->max_first+rc->fps)*rc->max_first*rc->BU_coded/rc->BU_total;
// 				if (h->fenc->i_type == X264_TYPE_I || h->fenc->i_type == X264_TYPE_IDR)
// 				{
// 					target_bits = rc->bitrate/(rc->max_first+rc->fps)*rc->max_first*rc->BU_coded/rc->BU_total;
// 				}
// 				else
// 				{
// 					target_bits = 0.5*rc->bitrate/(rc->max_first+rc->fps)*rc->max_first*rc->BU_coded/rc->BU_total;
// 				}
				if (coded_bits > target_bits )
				{
// 					rc->overdue_first_frame = 1;
					rc->qpm = rc->qpm + coded_bits/target_bits;
					rc->qpm = min(h->param.rc.i_qp_max, rc->qpm);
				}
// 				else if (rc->overdue_first_frame == 0)
// 				{
// 					rc->qpm = rc->frame_qp;
// 				}
				else
				{
					rc->qpm = rc->qpm--;
					rc->qpm = max(rc->frame_qp-1, rc->qpm);
					rc->qpm = max(h->param.rc.i_qp_min, rc->qpm);
				}
				rc->sum_qp_frame += rc->qpm;
			}
			else // PwithSP, PnoSP, SP
			{   
				if (h->fenc->curr_level == tp_lvl_1)  // SP
				{
					updateRCModel_SP(h);
					rc->qpm = updateQP_SP(h);
				}
				else // PwithSP, PnoSP
				{
					updateRCModel_P(h);
					rc->qpm = updateQP_P(h);
				}

				rc->qpm = x264_clip3(rc->qpm, h->param.rc.i_qp_min, h->param.rc.i_qp_max);
			}
		}
		return 0;
	}
#endif

	float qscale = qp2qscale( rc->qpm );
	h->fdec->f_row_qp[y] = rc->qpm;
	h->fdec->f_row_qscale[y] = qscale;

	update_predictor( rc->row_pred[0], qscale, h->fdec->i_row_satd[y], h->fdec->i_row_bits[y] );
	if( h->sh.i_type == SLICE_TYPE_P && rc->qpm < h->fref[0][0]->f_row_qp[y] )
		update_predictor( rc->row_pred[1], qscale, h->fdec->i_row_satds[0][0][y], h->fdec->i_row_bits[y] );

	/* update ratecontrol per-mbpair in MBAFF */
	if( SLICE_MBAFF && !(y&1) )
		return 0;

	/* FIXME: We don't currently support the case where there's a slice
	* boundary in between. */
	int can_reencode_row = h->sh.i_first_mb <= ((h->mb.i_mb_y - SLICE_MBAFF) * h->mb.i_mb_stride);

	/* tweak quality based on difference from predicted size */
	float prev_row_qp = h->fdec->f_row_qp[y];
	float qp_absolute_max = h->param.rc.i_qp_max;
	if( rc->rate_factor_max_increment )
		qp_absolute_max = X264_MIN( qp_absolute_max, rc->qp_novbv + rc->rate_factor_max_increment );
	float qp_max = X264_MIN( prev_row_qp + h->param.rc.i_qp_step, qp_absolute_max );
	float qp_min = X264_MAX( prev_row_qp - h->param.rc.i_qp_step, h->param.rc.i_qp_min );
	float step_size = 0.5f;
	float buffer_left_planned = rc->buffer_fill - rc->frame_size_planned;
	float slice_size_planned = h->param.b_sliced_threads ? rc->slice_size_planned : rc->frame_size_planned;
	float max_frame_error = X264_MAX( 0.05f, 1.0f / h->mb.i_mb_height );
	float size_of_other_slices = 0;
	if( h->param.b_sliced_threads )
	{
		float size_of_other_slices_planned = 0;
		for( int i = 0; i < h->param.i_threads; i++ )
		{
			if( h != h->thread[i] )
			{
				size_of_other_slices += h->thread[i]->rc->frame_size_estimated;
				size_of_other_slices_planned += h->thread[i]->rc->slice_size_planned;
			}
		}
		float weight = rc->slice_size_planned / rc->frame_size_planned;
		size_of_other_slices = (size_of_other_slices - size_of_other_slices_planned) * weight + size_of_other_slices_planned;
	}

	if( y < h->i_threadslice_end-1 )
	{
		/* B-frames shouldn't use lower QP than their reference frames. */
		if( h->sh.i_type == SLICE_TYPE_B )
		{
			qp_min = X264_MAX( qp_min, X264_MAX( h->fref[0][0]->f_row_qp[y+1], h->fref[1][0]->f_row_qp[y+1] ) );
			rc->qpm = X264_MAX( rc->qpm, qp_min );
		}

		/* More threads means we have to be more cautious in letting ratecontrol use up extra bits. */
		float rc_tol = buffer_left_planned / h->param.i_threads * rc->rate_tolerance;
		float b1 = predict_row_size_sum( h, y, rc->qpm ) + size_of_other_slices;

		/* Don't increase the row QPs until a sufficent amount of the bits of the frame have been processed, in case a flat */
		/* area at the top of the frame was measured inaccurately. */
		//int row_bits_total_now = row_bits_so_far( h, y );
		if( row_bits_so_far( h, y ) < 0.05f * slice_size_planned )
			qp_max = qp_absolute_max = prev_row_qp;

		if( h->sh.i_type != SLICE_TYPE_I )
			rc_tol *= 0.5f;

		if( !rc->b_vbv_min_rate )
			qp_min = X264_MAX( qp_min, rc->qp_novbv );

		while( rc->qpm < qp_max
			&& ((b1 > rc->frame_size_planned + rc_tol) ||
			(rc->buffer_fill - b1 < buffer_left_planned * 0.5f) ||
			(b1 > rc->frame_size_planned  && rc->qpm < rc->qp_novbv )) )//fred 1107
		{
			rc->qpm += step_size;
			b1 = predict_row_size_sum( h, y, rc->qpm ) + size_of_other_slices;
		}

		while( rc->qpm > qp_min
// 			&& (rc->qpm > h->fdec->f_row_qp[0] || rc->single_frame_vbv)
			&& ((b1 < rc->frame_size_planned * 0.8f && rc->qpm <= prev_row_qp)
			|| b1 < (rc->buffer_fill - rc->buffer_size + rc->buffer_rate) * 1.1f) )
		{
			rc->qpm -= step_size;
			b1 = predict_row_size_sum( h, y, rc->qpm ) + size_of_other_slices;
		}

		/* avoid VBV underflow or MinCR violation */
		while( (rc->qpm < qp_absolute_max)
			&& ((rc->buffer_fill - b1 < rc->buffer_rate * max_frame_error) ||
			(rc->frame_size_maximum - b1 < rc->frame_size_maximum * max_frame_error)))
		{
			rc->qpm += step_size;
			b1 = predict_row_size_sum( h, y, rc->qpm ) + size_of_other_slices;
		}

		h->rc->frame_size_estimated = b1 - size_of_other_slices;

		/* If the current row was large enough to cause a large QP jump, try re-encoding it. */
		if( rc->qpm > qp_max && prev_row_qp < qp_max && can_reencode_row )
		{
			/* Bump QP to halfway in between... close enough. */
			rc->qpm = x264_clip3f( (prev_row_qp + rc->qpm)*0.5f, prev_row_qp + 1.0f, qp_max );
			rc->qpa_rc = rc->qpa_rc_prev;
			rc->qpa_aq = rc->qpa_aq_prev;
			h->fdec->i_row_bits[y] = h->fdec->i_row_bits[y-SLICE_MBAFF] = 0;
			return -1;
		}
	}
	else
	{
		h->rc->frame_size_estimated = predict_row_size_sum( h, y, rc->qpm );

		/* Last-ditch attempt: if the last row of the frame underflowed the VBV,
		* try again. */
		if( (h->rc->frame_size_estimated + size_of_other_slices) > (rc->buffer_fill - rc->buffer_rate * max_frame_error) &&
			rc->qpm < qp_max && can_reencode_row )
		{
			rc->qpm = qp_max;
			rc->qpa_rc = rc->qpa_rc_prev;
			rc->qpa_aq = rc->qpa_aq_prev;
			h->fdec->i_row_bits[y] = h->fdec->i_row_bits[y-SLICE_MBAFF] = 0;
			return -1;
		}
	}

	rc->qpa_rc_prev = rc->qpa_rc;
	rc->qpa_aq_prev = rc->qpa_aq;

	return 0;
}



int x264_ratecontrol_qp( x264_t *h )
{
	x264_emms();    
	return x264_clip3( h->rc->qpm + 0.5f, h->param.rc.i_qp_min, h->param.rc.i_qp_max );
}

int x264_ratecontrol_mb_qp( x264_t *h )
{
	x264_emms();
	float qp = h->rc->qpm;
	if( h->param.rc.i_aq_mode )
	{
		/* MB-tree currently doesn't adjust quantizers in unreferenced frames. */
		float qp_offset = h->fdec->b_kept_as_ref ? h->fenc->f_qp_offset[h->mb.i_mb_xy] : h->fenc->f_qp_offset_aq[h->mb.i_mb_xy];
		/* Scale AQ's effect towards zero in emergency mode. */
		if( qp > QP_MAX_SPEC )
			qp_offset *= (QP_MAX - qp) / (QP_MAX - QP_MAX_SPEC);
		qp += qp_offset;
	}
	return x264_clip3( qp + 0.5f, h->param.rc.i_qp_min, h->param.rc.i_qp_max );
}

/* In 2pass, force the same frame types as in the 1st pass */
int x264_ratecontrol_slice_type( x264_t *h, int frame_num )
{
#if 0
	x264_ratecontrol_t *rc = h->rc;
	if( h->param.rc.b_stat_read )
	{
		if( frame_num >= rc->num_entries )
		{
			/* We could try to initialize everything required for ABR and
			* adaptive B-frames, but that would be complicated.
			* So just calculate the average QP used so far. */
			h->param.rc.i_qp_constant = (h->stat.i_frame_count[SLICE_TYPE_P] == 0) ? 24 + QP_BD_OFFSET
				: 1 + h->stat.f_frame_qp[SLICE_TYPE_P] / h->stat.i_frame_count[SLICE_TYPE_P];
			rc->qp_constant[SLICE_TYPE_P] = x264_clip3( h->param.rc.i_qp_constant, 0, QP_MAX );
			rc->qp_constant[SLICE_TYPE_I] = x264_clip3( (int)( qscale2qp( qp2qscale( h->param.rc.i_qp_constant ) / fabs( h->param.rc.f_ip_factor )) + 0.5 ), 0, QP_MAX );
			rc->qp_constant[SLICE_TYPE_B] = x264_clip3( (int)( qscale2qp( qp2qscale( h->param.rc.i_qp_constant ) * fabs( h->param.rc.f_pb_factor )) + 0.5 ), 0, QP_MAX );

			x264_log( h, X264_LOG_ERROR, "2nd pass has more frames than 1st pass (%d)\n", rc->num_entries );
			x264_log( h, X264_LOG_ERROR, "continuing anyway, at constant QP=%d\n", h->param.rc.i_qp_constant );
			if( h->param.i_bframe_adaptive )
				x264_log( h, X264_LOG_ERROR, "disabling adaptive B-frames\n" );

			for( int i = 0; i < h->param.i_threads; i++ )
			{
				h->thread[i]->rc->b_abr = 0;
				h->thread[i]->rc->b_2pass = 0;
				h->thread[i]->param.rc.i_rc_method = X264_RC_CQP;
				h->thread[i]->param.rc.b_stat_read = 0;
				h->thread[i]->param.i_bframe_adaptive = 0;
				h->thread[i]->param.i_scenecut_threshold = 0;
				h->thread[i]->param.rc.b_mb_tree = 0;
				if( h->thread[i]->param.i_bframe > 1 )
					h->thread[i]->param.i_bframe = 1;
			}
			return X264_TYPE_AUTO;
		}
		return rc->entry[frame_num].frame_type;
	}
	else
#endif
		return X264_TYPE_AUTO;
}

void x264_ratecontrol_set_weights( x264_t *h, x264_frame_t *frm )
{
	ratecontrol_entry_t *rce = &h->rc->entry[frm->i_frame];
	if( h->param.analyse.i_weighted_pred <= 0 )
		return;

	if( rce->i_weight_denom[0] >= 0 )
		SET_WEIGHT( frm->weight[0][0], 1, rce->weight[0][0], rce->i_weight_denom[0], rce->weight[0][1] );

	if( rce->i_weight_denom[1] >= 0 )
	{
		SET_WEIGHT( frm->weight[0][1], 1, rce->weight[1][0], rce->i_weight_denom[1], rce->weight[1][1] );
		SET_WEIGHT( frm->weight[0][2], 1, rce->weight[2][0], rce->i_weight_denom[1], rce->weight[2][1] );
	}
}

/* After encoding one frame, save stats and update ratecontrol state */
int x264_ratecontrol_end( x264_t *h, int bits, int *filler )
{
	x264_ratecontrol_t *rc = h->rc;
	const int *mbs = h->stat.frame.i_mb_count;
#if SHOW_QP
	FILE* fp_qp;
#endif
	x264_emms();
#if RC_MAD
	if (h->param.rc.use_MAD)
	{
		rc->curr_level_last = h->fenc->curr_level;
		if (( SLICE_TYPE_P == h->sh.i_type ) &&(h->fenc->curr_level != tp_lvl_2))  // P & not GF
		{
			double Avem_Qc = (double)rc->sum_qp_frame / (double)rc->BU_total;  // updata Xp after one frame
			int Complexity = ((int)floor(bits * Avem_Qc + 0.5)); // bit 
			rc->Xp = Complexity;
			rc->num_P_left--;  // include SP
			rc->frame_coded++;
			rc->coded_Pframe_inGOP++;
			rc->qp_last_Pframe = Avem_Qc;

			if (h->fenc->curr_level == tp_lvl_1)
			{  // SP
				rc->num_P_before = 0;
				rc->num_SP_lastGOP ++;
				rc->Pm_Qp ++;
				rc->frame_coded_SP++;
				rc->num_SP_left --;  // SP
				rc->last_bits_SP = bits;
			}
			else
			{// PwithSP or PnoSP
				rc->num_P_lastGOP ++;
				rc->num_P_before ++;
				rc->frame_coded_P++;
				rc->last_bits_P = bits;
				rc->header_bits_P = rc->header_bits;
			}
		}
		
		int delta_bits;
		rc->bit_GOP += bits;
		if (h->param.sp_period)  // 这里再简化一下
		{
			if (h->fenc->curr_level == tp_lvl_2 || h->fenc->curr_level == tp_lvl_1) // GF, IDR, SP
			{
				delta_bits = bits -(int)floor(rc->bitrate_SP + 0.5F) ;
			}
			else  // Pwith SP or PnoSP
			{
				delta_bits = bits -(int)floor(rc->bitrate_frame + 0.5F) ;
			}
		}
		else  // no sp
		{
			delta_bits = (bits - (int)floor(rc->bitrate_frame + 0.5F) );
		}
		if ( (rc->num_GOP == 1)&& h->fenc->curr_level == tp_lvl_2)
		{
			rc->ave_qp_frame_first =(int)((double)rc->sum_qp_frame/(double) rc->BU_total+0.5);
		}
		
		rc->bits_remain -= bits;        // remaining bits in GOP
		rc->curr_buffer += delta_bits;  // overflow

		// update the lower bound and the upper bound 
		rc->lower_bound  -= (int) delta_bits;
		rc->upper_bound1 -= (int) delta_bits;
		rc->upper_bound2  = (int)(OMEGA * rc->upper_bound1);

		if( SLICE_TYPE_P == h->sh.i_type)
		{
			if (h->fenc->curr_level == tp_lvl_1)
			{
				updateRCModel_SP(h);
			}
			else if (h->fenc->curr_level != tp_lvl_2)  // not GF or SP, is PwithSP or PnoSP
			{
				updateRCModel_P(h);
			}
		}

		h->fdec->f_qp_avg_rc = rc->qpa_rc /= h->mb.i_mb_count;
		h->fdec->f_qp_avg_aq = (float)rc->qpa_aq / h->mb.i_mb_count;

		if( SLICE_TYPE_I == h->sh.i_type)
		{
			rc->ave_qp_I_Frame = h->fdec->f_qp_avg_aq;
		}
#if SHOW_QP
		fp_qp = fopen("x264_QP.txt","a+");
		fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
		fclose(fp_qp);

		if (h->sh.i_type == SLICE_TYPE_I)
		{
			fp_qp = fopen("x264_QP_I.txt","a+");
			fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
			fclose(fp_qp);
		}
		else if (tp_lvl_2 == h->fenc->curr_level)// GF
		{
			fp_qp = fopen("x264_QP_GF.txt","a+");
			fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
			fclose(fp_qp);
		}
		else if (tp_lvl_1 == h->fenc->curr_level)// SP
		{
			fp_qp = fopen("x264_QP_SP.txt","a+");
			fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
			fclose(fp_qp);
		}
		else // PwithSP or PnoSP
		{
			fp_qp = fopen("x264_QP_P.txt","a+");
			fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
			fclose(fp_qp);
		}
#endif
		return 0;
	}
#endif
	h->stat.frame.i_mb_count_skip = mbs[P_SKIP] + mbs[B_SKIP];
	h->stat.frame.i_mb_count_i = mbs[I_16x16] + mbs[I_8x8] + mbs[I_4x4];
	h->stat.frame.i_mb_count_p = mbs[P_L0] + mbs[P_8x8];
	for( int i = B_DIRECT; i < B_8x8; i++ )
		h->stat.frame.i_mb_count_p += mbs[i];

	h->fdec->f_qp_avg_rc = rc->qpa_rc /= h->mb.i_mb_count;
	h->fdec->f_qp_avg_aq = (float)rc->qpa_aq / h->mb.i_mb_count;
#if SHOW_QP
	fp_qp = fopen("x264_QP.txt","a+");
	fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
	fclose(fp_qp);
	if (h->sh.i_type == SLICE_TYPE_I)
	{
		fp_qp = fopen("x264_QP_I.txt","a+");
		fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
		fclose(fp_qp);
	}
	else if (tp_lvl_2 == h->fenc->curr_level)// GF
	{
		fp_qp = fopen("x264_QP_GF.txt","a+");
		fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
		fclose(fp_qp);
	}
	else if (tp_lvl_1 == h->fenc->curr_level)// SP
	{
		fp_qp = fopen("x264_QP_SP.txt","a+");
		fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
		fclose(fp_qp);
	}
	else // PwithSP or PnoSP
	{
		fp_qp = fopen("x264_QP_P.txt","a+");
		fprintf(fp_qp,"%.2f\t%.2f\n",h->fdec->f_qp_avg_rc,h->fdec->f_qp_avg_aq);
		fclose(fp_qp);
	}

#endif

#if 0

	if( h->param.rc.b_stat_write )
	{
		char c_type = h->sh.i_type==SLICE_TYPE_I ? (h->fenc->i_poc==0 ? 'I' : 'i')
			: h->sh.i_type==SLICE_TYPE_P ? 'P'
			: h->fenc->b_kept_as_ref ? 'B' : 'b';
		int dir_frame = h->stat.frame.i_direct_score[1] - h->stat.frame.i_direct_score[0];
		int dir_avg = h->stat.i_direct_score[1] - h->stat.i_direct_score[0];
		char c_direct = h->mb.b_direct_auto_write ?
			( dir_frame>0 ? 's' : dir_frame<0 ? 't' :
			dir_avg>0 ? 's' : dir_avg<0 ? 't' : '-' )
			: '-';
		if( fprintf( rc->p_stat_file_out,
			"in:%d out:%d type:%c dur:%lld cpbdur:%lld q:%.2f tex:%d mv:%d misc:%d imb:%d pmb:%d smb:%d d:%c ref:",
			h->fenc->i_frame, h->i_frame,
			c_type, h->fenc->i_duration,
			h->fenc->i_cpb_duration, rc->qpa_rc,
			h->stat.frame.i_tex_bits,
			h->stat.frame.i_mv_bits,
			h->stat.frame.i_misc_bits,
			h->stat.frame.i_mb_count_i,
			h->stat.frame.i_mb_count_p,
			h->stat.frame.i_mb_count_skip,
			c_direct) < 0 )
			goto fail;

		/* Only write information for reference reordering once. */
		int use_old_stats = h->param.rc.b_stat_read && rc->rce->refs > 1;
		for( int i = 0; i < (use_old_stats ? rc->rce->refs : h->i_ref[0]); i++ )
		{
			int refcount = use_old_stats         ? rc->rce->refcount[i]
			: PARAM_INTERLACED      ? h->stat.frame.i_mb_count_ref[0][i*2]
			+ h->stat.frame.i_mb_count_ref[0][i*2+1]
			:                         h->stat.frame.i_mb_count_ref[0][i];
			if( fprintf( rc->p_stat_file_out, "%d ", refcount ) < 0 )
				goto fail;
		}

		if( h->param.analyse.i_weighted_pred >= X264_WEIGHTP_SIMPLE && h->sh.weight[0][0].weightfn )
		{
			if( fprintf( rc->p_stat_file_out, "w:%d,%d,%d",
				h->sh.weight[0][0].i_denom, h->sh.weight[0][0].i_scale, h->sh.weight[0][0].i_offset ) < 0 )
				goto fail;
			if( h->sh.weight[0][1].weightfn || h->sh.weight[0][2].weightfn )
			{
				if( fprintf( rc->p_stat_file_out, ",%d,%d,%d,%d,%d ",
					h->sh.weight[0][1].i_denom, h->sh.weight[0][1].i_scale, h->sh.weight[0][1].i_offset,
					h->sh.weight[0][2].i_scale, h->sh.weight[0][2].i_offset ) < 0 )
					goto fail;
			}
			else if( fprintf( rc->p_stat_file_out, " " ) < 0 )
				goto fail;
		}

		if( fprintf( rc->p_stat_file_out, ";\n") < 0 )
			goto fail;

		/* Don't re-write the data in multi-pass mode. */
		if( h->param.rc.b_mb_tree && h->fenc->b_kept_as_ref && !h->param.rc.b_stat_read )
		{
			uint8_t i_type = h->sh.i_type;
			/* Values are stored as big-endian FIX8.8 */
			for( int i = 0; i < h->mb.i_mb_count; i++ )
				rc->qp_buffer[0][i] = endian_fix16( h->fenc->f_qp_offset[i]*256.0 );
			if( fwrite( &i_type, 1, 1, rc->p_mbtree_stat_file_out ) < 1 )
				goto fail;
			if( fwrite( rc->qp_buffer[0], sizeof(uint16_t), h->mb.i_mb_count, rc->p_mbtree_stat_file_out ) < h->mb.i_mb_count )
				goto fail;
		}
	}
#endif

	if( rc->b_abr )
	{
		if( h->sh.i_type != SLICE_TYPE_B )
			rc->cplxr_sum += bits * qp2qscale( rc->qpa_rc ) / rc->last_rceq;
		else
		{
			/* Depends on the fact that B-frame's QP is an offset from the following P-frame's.
			* Not perfectly accurate with B-refs, but good enough. */
			rc->cplxr_sum += bits * qp2qscale( rc->qpa_rc ) / (rc->last_rceq * fabs( h->param.rc.f_pb_factor ));
		}
		rc->cplxr_sum *= rc->cbr_decay;
		rc->wanted_bits_window += h->fenc->f_duration * rc->bitrate;
		rc->wanted_bits_window *= rc->cbr_decay;
	}

	//fred comment no use
#if 0

	if( rc->b_2pass )
		rc->expected_bits_sum += qscale2bits( rc->rce, qp2qscale( rc->rce->new_qp ) );

	if( h->mb.b_variable_qp )
	{
		if( h->sh.i_type == SLICE_TYPE_B )
		{
			rc->bframe_bits += bits;
			if( h->fenc->b_last_minigop_bframe )
			{
				update_predictor( rc->pred_b_from_p, qp2qscale( rc->qpa_rc ),
					h->fref[1][h->i_ref[1]-1]->i_satd, rc->bframe_bits / rc->bframes );
				rc->bframe_bits = 0;
			}
		}
	}
#endif

	*filler = update_vbv( h, bits );
	rc->filler_bits_sum += *filler * 8;

	//fred comment no use
#if 0
	if( h->sps->vui.b_nal_hrd_parameters_present )
	{
		if( h->fenc->i_frame == 0 )
		{
			// access unit initialises the HRD
			h->fenc->hrd_timing.cpb_initial_arrival_time = 0;
			rc->initial_cpb_removal_delay = h->initial_cpb_removal_delay;
			rc->initial_cpb_removal_delay_offset = h->initial_cpb_removal_delay_offset;
			h->fenc->hrd_timing.cpb_removal_time = rc->nrt_first_access_unit = (double)rc->initial_cpb_removal_delay / 90000;
		}
		else
		{
			h->fenc->hrd_timing.cpb_removal_time = rc->nrt_first_access_unit + (double)(h->fenc->i_cpb_delay - h->i_cpb_delay_pir_offset) *
				h->sps->vui.i_num_units_in_tick / h->sps->vui.i_time_scale;

			double cpb_earliest_arrival_time = h->fenc->hrd_timing.cpb_removal_time - (double)rc->initial_cpb_removal_delay / 90000;
			if( h->fenc->b_keyframe )
			{
				rc->nrt_first_access_unit = h->fenc->hrd_timing.cpb_removal_time;
				rc->initial_cpb_removal_delay = h->initial_cpb_removal_delay;
				rc->initial_cpb_removal_delay_offset = h->initial_cpb_removal_delay_offset;
			}
			else
				cpb_earliest_arrival_time -= (double)rc->initial_cpb_removal_delay_offset / 90000;

			if( h->sps->vui.hrd.b_cbr_hrd )
				h->fenc->hrd_timing.cpb_initial_arrival_time = rc->previous_cpb_final_arrival_time;
			else
				h->fenc->hrd_timing.cpb_initial_arrival_time = X264_MAX( rc->previous_cpb_final_arrival_time, cpb_earliest_arrival_time );
		}
		int filler_bits = *filler ? X264_MAX( (FILLER_OVERHEAD - h->param.b_annexb), *filler )*8 : 0;
		// Equation C-6
		h->fenc->hrd_timing.cpb_final_arrival_time = rc->previous_cpb_final_arrival_time = h->fenc->hrd_timing.cpb_initial_arrival_time +
			(double)(bits + filler_bits) / h->sps->vui.hrd.i_bit_rate_unscaled;

		h->fenc->hrd_timing.dpb_output_time = (double)h->fenc->i_dpb_output_delay * h->sps->vui.i_num_units_in_tick / h->sps->vui.i_time_scale +
			h->fenc->hrd_timing.cpb_removal_time;
	}
#endif

	return 0;
fail:
	x264_log( h, X264_LOG_ERROR, "ratecontrol_end: stats file could not be written to\n" );
	return -1;
}

/****************************************************************************
* 2 pass functions
***************************************************************************/

/**
* modify the bitrate curve from pass1 for one frame
*/
static double get_qscale(x264_t *h, ratecontrol_entry_t *rce, double rate_factor, int frame_num)
{
	x264_ratecontrol_t *rcc= h->rc;
	x264_zone_t *zone = get_zone( h, frame_num );
	double q;
	if( h->param.rc.b_mb_tree )
	{
		double timescale = (double)h->sps->vui.i_num_units_in_tick / h->sps->vui.i_time_scale;
		q = pow( BASE_FRAME_DURATION / CLIP_DURATION(rce->i_duration * timescale), (double)(1 - h->param.rc.f_qcompress) );
	}
	else
	{   
		q = pow((double)( rce->blurred_complexity), 1 - rcc->qcompress );
		//q = rcc->bitrate/rcc->fps;
	}

	// avoid NaN's in the rc_eq
	if( !isfinite(q) || rce->tex_bits + rce->mv_bits == 0 )
        q = rcc->last_qscale_for[ rce->pict_type ];
		//q = rcc->last_qscale_for[rce->pict_type];
	else
	{
		rcc->last_rceq = q;
		q /= rate_factor;
		rcc->last_qscale = q;
	}

	if( zone )
	{
		if( zone->b_force_qp )
			q = qp2qscale( zone->i_qp );
		else
			q /= zone->f_bitrate_factor;
	}

	return q;
}

//fred comment no use
#if 0
static double get_diff_limited_q(x264_t *h, ratecontrol_entry_t *rce, double q, int frame_num)
{
	x264_ratecontrol_t *rcc = h->rc;
	const int pict_type = rce->pict_type;
	x264_zone_t *zone = get_zone( h, frame_num );

	// force I/B quants as a function of P quants
	const double last_p_q    = rcc->last_qscale_for[SLICE_TYPE_P];
	const double last_non_b_q= rcc->last_qscale_for[rcc->last_non_b_pict_type];
	if( pict_type == SLICE_TYPE_I )
	{
		double iq = q;
		double pq = qp2qscale( rcc->accum_p_qp / rcc->accum_p_norm );
		double ip_factor = fabs( h->param.rc.f_ip_factor );
		/* don't apply ip_factor if the following frame is also I */
		if( rcc->accum_p_norm <= 0 )
			q = iq;
		else if( h->param.rc.f_ip_factor < 0 )
			q = iq / ip_factor;
		else if( rcc->accum_p_norm >= 1 )
			q = pq / ip_factor;
		else
			q = rcc->accum_p_norm * pq / ip_factor + (1 - rcc->accum_p_norm) * iq;
	}
	else if( pict_type == SLICE_TYPE_B )
	{
		if( h->param.rc.f_pb_factor > 0 )
			q = last_non_b_q;
		if( !rce->kept_as_ref )
			q *= fabs( h->param.rc.f_pb_factor );
	}
	else if( pict_type == SLICE_TYPE_P
		&& rcc->last_non_b_pict_type == SLICE_TYPE_P
		&& rce->tex_bits == 0 )
	{
		q = last_p_q;
	}

	/* last qscale / qdiff stuff */
	if( rcc->last_non_b_pict_type == pict_type &&
		(pict_type!=SLICE_TYPE_I || rcc->last_accum_p_norm < 1) )
	{
		double last_q = rcc->last_qscale_for[pict_type];
		double max_qscale = last_q * rcc->lstep;
		double min_qscale = last_q / rcc->lstep;

		if     ( q > max_qscale ) q = max_qscale;
		else if( q < min_qscale ) q = min_qscale;
	}

	rcc->last_qscale_for[pict_type] = q;
	if( pict_type != SLICE_TYPE_B )
		rcc->last_non_b_pict_type = pict_type;
	if( pict_type == SLICE_TYPE_I )
	{
		rcc->last_accum_p_norm = rcc->accum_p_norm;
		rcc->accum_p_norm = 0;
		rcc->accum_p_qp = 0;
	}
	if( pict_type == SLICE_TYPE_P )
	{
		float mask = 1 - pow( (float)rce->i_count / rcc->nmb, 2 );
		rcc->accum_p_qp   = mask * (qscale2qp( q ) + rcc->accum_p_qp);
		rcc->accum_p_norm = mask * (1 + rcc->accum_p_norm);
	}

	if( zone )
	{
		if( zone->b_force_qp )
			q = qp2qscale( zone->i_qp );
		else
			q /= zone->f_bitrate_factor;
	}

	return q;
}
#endif

static float predict_size( predictor_t *p, float q, float var )
{
	return (p->coeff*var + p->offset) / (q*p->count);
}

//fred
static float get_qscale_from_predsize( predictor_t *p, float pred_size, float var )
{
	return ( p->coeff * var + p->offset ) / ( pred_size * p->count );
}

static void update_predictor( predictor_t *p, float q, float var, float bits )
{
	float range = 1.5;
	if( var < 10 )
		return;
	float old_coeff = p->coeff / p->count;
	float new_coeff = bits*q / var;
	float new_coeff_clipped = x264_clip3f( new_coeff, old_coeff/range, old_coeff*range );
	float new_offset = bits*q - new_coeff_clipped * var;
	if( new_offset >= 0 )
		new_coeff = new_coeff_clipped;
	else
		new_offset = 0;
	p->count  *= p->decay;
	p->coeff  *= p->decay;
	p->offset *= p->decay;
	p->count  ++;
	p->coeff  += new_coeff;
	p->offset += new_offset;
}

// update VBV after encoding a frame
static int update_vbv( x264_t *h, int bits )
{
	int filler = 0;
	int bitrate = h->sps->vui.hrd.i_bit_rate_unscaled;
	x264_ratecontrol_t *rcc = h->rc;
	x264_ratecontrol_t *rct = h->thread[0]->rc;
	uint64_t buffer_size = (uint64_t)h->sps->vui.hrd.i_cpb_size_unscaled * h->sps->vui.i_time_scale;

	if( rcc->last_satd >= h->mb.i_mb_count )
		update_predictor( &rct->pred[h->sh.i_type], qp2qscale( rcc->qpa_rc ), rcc->last_satd, bits );


	if( !rcc->b_vbv )
	{
		return filler;
	}

	rct->buffer_fill_final -= (uint64_t)bits * h->sps->vui.i_time_scale;

	if( rct->buffer_fill_final < 0 )
	{
		x264_log( h, X264_LOG_WARNING, "VBV underflow (frame %d, %.0f bits)\n", h->i_frame, (double)rct->buffer_fill_final / h->sps->vui.i_time_scale );
		if (h->param.rc.use_drop_frame)
		{
			rct->buffer_fill_final += (uint64_t)bits * h->sps->vui.i_time_scale;
			rct->buffer_fill_final += (uint64_t)bitrate * h->sps->vui.i_num_units_in_tick * h->fenc->i_cpb_duration;
			h->param.rc.b_drop_frame = 1;
			return 0;
		}
	}
	h->param.rc.b_drop_frame = 0;

    if (h->param.em_rc_mode != em_mode_dsktop)
    {
        rct->buffer_fill_final = X264_MAX( rct->buffer_fill_final, 0 );
        rct->buffer_fill_final += (uint64_t)bitrate * h->sps->vui.i_num_units_in_tick * h->fenc->i_cpb_duration;
    }
    

	if( h->sps->vui.hrd.b_cbr_hrd && rct->buffer_fill_final > buffer_size )
	{
		int64_t scale = (int64_t)h->sps->vui.i_time_scale * 8;
		filler = (rct->buffer_fill_final - buffer_size + scale - 1) / scale;
		bits = X264_MAX( (FILLER_OVERHEAD - h->param.b_annexb), filler ) * 8;
		rct->buffer_fill_final -= (uint64_t)bits * h->sps->vui.i_time_scale;
	}
	else
	{
		rct->buffer_fill_final = X264_MIN( rct->buffer_fill_final, buffer_size );
	}

	

// 	int send_bits = (1.0*bitrate * h->sps->vui.i_num_units_in_tick * h->fenc->i_cpb_duration)/h->sps->vui.i_time_scale;

// 	rcc->buffer_over_bits += bits - send_bits;

	//rcc->buffer_over_bits = X264_MAX(rcc->buffer_over_bits, 0);

	return filler;
}

//fred comment no use
#if 0
void x264_hrd_fullness( x264_t *h )
{
	x264_ratecontrol_t *rct = h->thread[0]->rc;
	uint64_t denom = (uint64_t)h->sps->vui.hrd.i_bit_rate_unscaled * h->sps->vui.i_time_scale / rct->hrd_multiply_denom;
	uint64_t cpb_state = rct->buffer_fill_final;
	uint64_t cpb_size = (uint64_t)h->sps->vui.hrd.i_cpb_size_unscaled * h->sps->vui.i_time_scale;
	uint64_t multiply_factor = 180000 / rct->hrd_multiply_denom;

	if( rct->buffer_fill_final < 0 || rct->buffer_fill_final > cpb_size )
	{
		x264_log( h, X264_LOG_WARNING, "CPB %s: %.0lf bits in a %.0lf-bit buffer\n",
			rct->buffer_fill_final < 0 ? "underflow" : "overflow", (float)rct->buffer_fill_final/denom, (float)cpb_size/denom );
	}

	h->initial_cpb_removal_delay = (multiply_factor * cpb_state + denom) / (2*denom);
	h->initial_cpb_removal_delay_offset = (multiply_factor * cpb_size + denom) / (2*denom) - h->initial_cpb_removal_delay;
}
#endif

// provisionally update VBV according to the planned size of all frames currently in progress
static void update_vbv_plan( x264_t *h, int overhead )
{
	x264_ratecontrol_t *rcc = h->rc;
    x264_ratecontrol_t *rct = h->thread[0]->rc;

    if (h->param.em_rc_mode == em_mode_dsktop)
    {
        int cur_time = x264_GetTickCount();
        rct->buffer_fill_final = X264_MAX( rct->buffer_fill_final, 0 );

        if (cur_time <= 0)
        {
            rct->buffer_fill_final = X264_MAX( rct->buffer_fill_final, 0 );
            rct->buffer_fill_final += (uint64_t)rcc->bitrate * h->sps->vui.i_num_units_in_tick * h->fenc->i_cpb_duration;
        }
        else
        {
            if (rcc->i_timestamp == 0)
            {
                x264_ratecontrol_reset_buffer(h);
            }
            else
            {
                rcc->i_time_interval = cur_time - rcc->i_timestamp;
                if (rcc->i_time_interval > 100000)
                {
                    x264_ratecontrol_reset_buffer(h);
                }
                else
                {
                    rct->buffer_fill_final += (uint64_t)(h->rc->i_time_interval *rcc->bitrate * h->sps->vui.i_time_scale / 1000);
                }
            }
            rcc->i_timestamp = cur_time;
            rct->buffer_fill_final = X264_MIN(rct->buffer_fill_final, (int64_t)(rcc->buffer_size * h->sps->vui.i_time_scale));
        }
    }
    
	rcc->buffer_fill = h->thread[0]->rc->buffer_fill_final / h->sps->vui.i_time_scale;
	if( h->i_thread_frames > 1 )
	{
		int j = h->rc - h->thread[0]->rc;
		for( int i = 1; i < h->i_thread_frames; i++ )
		{
			x264_t *t = h->thread[ (j+i)%h->i_thread_frames ];
			double bits = t->rc->frame_size_planned;
			if( !t->b_thread_active )
				continue;
			bits = X264_MAX(bits, t->rc->frame_size_estimated);
			rcc->buffer_fill -= bits;
			rcc->buffer_fill = X264_MAX( rcc->buffer_fill, 0 );
			rcc->buffer_fill += t->rc->buffer_rate;
			rcc->buffer_fill = X264_MIN( rcc->buffer_fill, rcc->buffer_size );
		}
	}

// 	//fred
// 	if ( em_mode_normal == h->param.mode && tp_lvl_2 == h->fenc->curr_level )
//     {   
//         rcc->buffer_fill *= 1.1;
//     }

	rcc->buffer_fill = X264_MIN( rcc->buffer_fill, rcc->buffer_size );
	rcc->buffer_fill -= overhead;
}

// apply VBV constraints and clip qscale to between lmin and lmax
static double clip_qscale( x264_t *h, int pict_type, double q )
{
	x264_ratecontrol_t *rcc = h->rc;
	double lmin = rcc->lmin[pict_type];
	double lmax = rcc->lmax[pict_type];
	if( rcc->rate_factor_max_increment )
		lmax = X264_MIN( lmax, qp2qscale( (double)rcc->qp_novbv + rcc->rate_factor_max_increment ) );
	double q0 = q;

	/* B-frames are not directly subject to VBV,
	* since they are controlled by the P-frames' QPs. */

	if( rcc->b_vbv && rcc->last_satd > 0 )
	{
#if 0
		/* Lookahead VBV: raise the quantizer as necessary such that no frames in
		* the lookahead overflow and such that the buffer is in a reasonable state
		* by the end of the lookahead. */
		if( h->param.rc.i_lookahead )
		{
			int terminate = 0;

			/* Avoid an infinite loop. */
			for( int iterations = 0; iterations < 1000 && terminate != 3; iterations++ )
			{
				double frame_q[3];
				double cur_bits = predict_size( &rcc->pred[ predictor_id( h ) ], q, rcc->last_satd );
				double buffer_fill_cur = rcc->buffer_fill - cur_bits;
				double target_fill;
				double total_duration = 0;
				frame_q[0] = h->sh.i_type == SLICE_TYPE_I ? q * h->param.rc.f_ip_factor : q;
				frame_q[1] = frame_q[0] * h->param.rc.f_pb_factor;
				frame_q[2] = frame_q[0] / h->param.rc.f_ip_factor;

				/* Loop over the planned future frames. */
				for( int j = 0; buffer_fill_cur >= 0 && buffer_fill_cur <= rcc->buffer_size; j++ )
				{
					total_duration += h->fenc->f_planned_cpb_duration[j];
					buffer_fill_cur += rcc->vbv_max_rate * h->fenc->f_planned_cpb_duration[j];
					int i_type = h->fenc->i_planned_type[j];
					int i_satd = h->fenc->i_planned_satd[j];
					if( i_type == X264_TYPE_AUTO )
						break;
					i_type = IS_X264_TYPE_I( i_type ) ? SLICE_TYPE_I : IS_X264_TYPE_B( i_type ) ? SLICE_TYPE_B : SLICE_TYPE_P;
					cur_bits = predict_size( &rcc->pred[i_type], frame_q[i_type], i_satd );
					buffer_fill_cur -= cur_bits;
				}
				/* Try to get to get the buffer at least 50% filled, but don't set an impossible goal. */
				target_fill = X264_MIN( rcc->buffer_fill + total_duration * rcc->vbv_max_rate * 0.5, rcc->buffer_size * 0.5 );
				if( buffer_fill_cur < target_fill )
				{
					q *= 1.01;
					terminate |= 1;
					continue;
				}
				/* Try to get the buffer no more than 80% filled, but don't set an impossible goal. */
				target_fill = x264_clip3f( rcc->buffer_fill - total_duration * rcc->vbv_max_rate * 0.5, rcc->buffer_size * 0.8, rcc->buffer_size );
				if( rcc->b_vbv_min_rate && buffer_fill_cur > target_fill )
				{
					q /= 1.01;
					terminate |= 2;
					continue;
				}
				break;
			}
		}
		/* Fallback to old purely-reactive algorithm: no lookahead. */
		else
#endif
		{
			if( ( (pict_type == SLICE_TYPE_P && h->fenc->curr_level != tp_lvl_2) ||
				( pict_type == SLICE_TYPE_I && rcc->last_non_b_pict_type == SLICE_TYPE_I ) ) &&
				rcc->buffer_fill/rcc->buffer_size < 0.8 )
			{
				q /= x264_clip3f( 1.25*rcc->buffer_fill/rcc->buffer_size, 0.5, 1.0 );
			}

            /* Now a hard threshold to make sure the frame fits in VBV.
             * This one is mostly for I-frames. */
            double bits = predict_size( &rcc->pred[h->sh.i_type], q, rcc->last_satd );
            double qf = 1.0;
            /* For small VBVs, allow the frame to use up the entire VBV. */
            double max_fill_factor = h->param.rc.i_vbv_buffer_size >= 5*h->param.rc.i_vbv_max_bitrate / rcc->fps ? 2 : 1;
            /* For single-frame VBVs, request that the frame use up the entire VBV. */
            double min_fill_factor = rcc->single_frame_vbv ? 1 : 2;

            if( bits > rcc->buffer_fill/max_fill_factor )
                qf = x264_clip3f( rcc->buffer_fill/(max_fill_factor*bits), 0.2, 1.0 );
            q /= qf;
            bits *= qf;
            if( bits < rcc->buffer_rate/min_fill_factor )
                q *= bits*min_fill_factor/rcc->buffer_rate;
            q = X264_MAX( q0, q );
		}

		/* Apply MinCR restrictions */
		double bits = predict_size( &rcc->pred[h->sh.i_type], q, rcc->last_satd );
		if( bits > rcc->frame_size_maximum )
			q *= bits / rcc->frame_size_maximum;
		bits = predict_size( &rcc->pred[h->sh.i_type], q, rcc->last_satd );

		/* Check B-frame complexity, and use up any bits that would
		* overflow before the next P-frame. */
		if( h->sh.i_type == SLICE_TYPE_P && !rcc->single_frame_vbv )
		{
			int nb = rcc->bframes;
			double pbbits = bits;
			double bbits = predict_size( rcc->pred_b_from_p, q * h->param.rc.f_pb_factor, rcc->last_satd );
			double space;
			double bframe_cpb_duration = 0;
			double minigop_cpb_duration;
			for( int i = 0; i < nb; i++ )
				bframe_cpb_duration += h->fenc->f_planned_cpb_duration[1+i];

			if( bbits * nb > bframe_cpb_duration * rcc->vbv_max_rate )
				nb = 0;
			pbbits += nb * bbits;

			minigop_cpb_duration = bframe_cpb_duration + h->fenc->f_planned_cpb_duration[0];
			space = rcc->buffer_fill + minigop_cpb_duration*rcc->vbv_max_rate - rcc->buffer_size;
			if( pbbits < space )
			{
				q *= X264_MAX( pbbits / space, bits / (0.5 * rcc->buffer_size) );
			}
			q = X264_MAX( q0/2, q );
		}

		if( !rcc->b_vbv_min_rate )
			q = X264_MAX( q0, q );
	}

	if( lmin==lmax )
		return lmin;
	else if( rcc->b_2pass )
	{
		double min2 = log( lmin );
		double max2 = log( lmax );
		q = (log(q) - min2)/(max2-min2) - 0.5;
		q = 1.0/(1.0 + exp( -4*q ));
		q = q*(max2-min2) + min2;
		return exp( q );
	}
	else
		return x264_clip3f( q, lmin, lmax );
}
#if 0
int try_filler_data( x264_t* h, int* p_frame_size )
{
	if ( h->rc->buffer_over_bits < 0 )
	{
		int over_byte_count = (0 - h->rc->buffer_over_bits)/8;

		if ( over_byte_count > 50*( FILLER_OVERHEAD - h->param.b_annexb ) )
		{
			over_byte_count -= 50*( FILLER_OVERHEAD - h->param.b_annexb );

			x264_nal_start( h, NAL_FILLER, NAL_PRIORITY_DISPOSABLE );
			x264_filler_write( h, &h->out.bs, over_byte_count );
			if( x264_nal_end( h ) )
				return -1;

			int total_size = x264_encoder_encapsulate_nals( h, h->out.i_nal-1 );
			if( total_size < 0 )
				return -1;

			*p_frame_size += total_size;
		}
	}

	return 0;
}
#endif
/*
//fred
void feed_back( x264_t* h, float* p_fator, x264_ratecontrol_t *rcc )
{
	float factor = *p_fator;
	float fps = 1.0*h->param.i_fps_num/h->param.i_fps_den;
	int   gop_pos = h->i_frame%((int)fps);

    // 0 1 2 in gop, no feed back
	if ( gop_pos <= 2 ) return;

	float rator = 1.0f;

    //last three
	if ( fps - gop_pos < 3 )  rator = 0.5;


	float over_rate = rcc->buffer_over_bits/rcc->bitrate;

	if ( over_rate >= 0.15*rator )
	{
		if ( tp_lvl_1 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			factor = 1.25;
		else if ( tp_lvl_0 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			factor = 1.3;
		else
			factor = 1.15;

		rcc->buffer_fill *= 0.8;
	}
	else if ( over_rate >= 0.10*rator )
	{
		if ( tp_lvl_1 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			factor = 1.18;
		else if ( tp_lvl_0 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			factor = 1.2;
		else
			factor = 1.15;		
	}

	*p_fator = factor;    
}

//fred
void feed_back2( x264_t* h, int* p_fator, x264_ratecontrol_t *rcc )
{
	int factor = 0;
	float fps = 1.0*h->param.i_fps_num/h->param.i_fps_den;
	int   gop_pos = h->i_frame%((int)fps);

    // 0 1 2 in gop, no feed back,
    int pos = (fps <= 6)? 1 : 2;
	if ( gop_pos <= pos ) return;

	float rator = 1.0f;

    //last three
	if ( fps - gop_pos < 2 )
		rator = 0.9;
	else if ( fps - gop_pos < 3 )
		rator = 0.9;

	float over_rate = rcc->buffer_over_bits/rcc->bitrate;

	if ( over_rate >= 0.15*rator )
	{
		if ( tp_lvl_1 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			factor = 3;
		else if ( tp_lvl_0 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			factor = 4;
		else
			factor = 3;

		rcc->buffer_fill *= 0.8;
	}
	else if ( over_rate >= 0.10*rator )
	{
		if ( tp_lvl_1 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			factor = 1;
		else if ( tp_lvl_0 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			factor = 2;
		else
			factor = 1;
	}

	*p_fator = factor;
}


//fred for desktop mode
static int rc_feedback( x264_t *h, float* p_qscale, int b_try )
{
	float qscale = *p_qscale;
	x264_ratecontrol_t *rcc;
	x264_ratecontrol_t tmp_rcc;
    float factor_feedback = 1.0f;

	if ( 1 == b_try )
	{
		memcpy(&tmp_rcc, h->rc, sizeof(x264_ratecontrol_t));
		rcc = &tmp_rcc;
	}
	else
    {   
		rcc = h->rc;
    }
    
	//if idr or gf, modify qp
	float scalor_on_qp = 1.0;

	if ( tp_lvl_2 == h->fenc->curr_level )
	{
		if ( SLICE_TYPE_I == h->sh.i_type )
            scalor_on_qp = 54/64.0;
		else if ( SLICE_TYPE_P == h->sh.i_type )
		{
			scalor_on_qp = 54/64.0;

			if ( em_mode_dsktop == h->param.mode )
				scalor_on_qp = 60/64.0;
		}
	}
	else 
	{
		if ( tp_lvl_1 == h->fenc->curr_level &&  SLICE_TYPE_P == h->sh.i_type )
		{
			scalor_on_qp = 58/64.0;
            
			if ( em_mode_dsktop == h->param.mode )
				scalor_on_qp = 63/64.0;
		}

        if ( em_mode_normal == h->param.mode )
        {
            feed_back( h, &factor_feedback, rcc );
        }
	}

    scalor_on_qp *=  factor_feedback;

	qscale = qp2qscale( qscale2qp( qscale ) * scalor_on_qp );
	rcc->frame_size_planned = predict_size( &rcc->pred[h->sh.i_type], qscale, rcc->last_satd );    
	rcc->frame_size_planned = X264_MIN( rcc->frame_size_planned, X264_MIN(1300*8*64*0.7, rcc->bitrate*0.5) );

	*p_qscale = qscale;

    return rcc->frame_size_planned;
}

static int rc_adjust_qprator( x264_t *h )
	{
	float qp_offset = 0;

	if ( tp_lvl_2 == h->fenc->curr_level )
	{// idr or gf
		if (SLICE_TYPE_I == h->sh.i_type)
	{
			qp_offset = 2;  // I SLICE: (1)ip_offset; (2)rc_adjust_qprator;
		}
		else if ( SLICE_TYPE_P == h->sh.i_type )
		{
			qp_offset = 3;
		}
			if ( em_mode_dsktop == h->param.mode )
		{
			qp_offset--;
		}
	}
	else 
	{
		if ( tp_lvl_1 == h->fenc->curr_level &&  SLICE_TYPE_P == h->sh.i_type )
		{
			qp_offset = 1;//h->mb.ip_offset/4;
			//qp_offset = max(1,qp_offset);
		}
	}

	return qp_offset;

}

static int rc_feedback2( x264_t *h, float* p_qscale, int b_try )
{
	float qscale = *p_qscale;
	x264_ratecontrol_t *rcc;
	x264_ratecontrol_t tmp_rcc;
    int factor_feedback = 0;
	int qp_offset = 0;

	if ( 1 == b_try )
        {
		memcpy(&tmp_rcc, h->rc, sizeof(x264_ratecontrol_t));
		rcc = &tmp_rcc;
        }
	else
    {   
		rcc = h->rc;
	}

	//if idr or gf, modify qp	
	qp_offset = rc_adjust_qprator( h );

	if ( tp_lvl_2 != h->fenc->curr_level )
	{
		feed_back2( h, &factor_feedback, rcc );
	}

	float psp_qp = qscale2qp( qscale ) - qp_offset +  factor_feedback;

    //if prev is sp, curr is psp && qp <= prev_qp && qp <= 40
    //0[p]  1[b]  2[i]  3[sp]  4[psp] 5[gf]
    //float prev_sp_qp = qscale2qp( rcc->last_qscale_for[ SLICE_TYPE_P + 3 ] );
    if (   tp_lvl_0 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type         
        && psp_qp <= rcc->last_pred_qp
        && psp_qp <= 40 )
    {
        psp_qp += 2;
    }
    
	qscale = qp2qscale( psp_qp );
	rcc->frame_size_planned = predict_size( &rcc->pred[h->sh.i_type], qscale, rcc->last_satd );    
	rcc->frame_size_planned = X264_MIN( rcc->frame_size_planned, X264_MIN(1300*8*64*0.7, rcc->bitrate*0.5) );

	*p_qscale = qscale;

    return rcc->frame_size_planned;
}
*/


// update qscale for 1 frame based on actual bits used so far
static float rate_estimate_qscale( x264_t *h )
{
	float qscale;
	x264_ratecontrol_t *rcc = h->rc;
	//ratecontrol_entry_t UNINIT(rce);
	ratecontrol_entry_t rce;
	int pict_type = h->sh.i_type;
	int64_t total_bits = 8*(h->stat.i_frame_size[SLICE_TYPE_I]
	+ h->stat.i_frame_size[SLICE_TYPE_P]
	+ h->stat.i_frame_size[SLICE_TYPE_B])
		- rcc->filler_bits_sum;

	memset(&rce, 0, sizeof(rce));

	//fred commit no use code
#if 0
	if( rcc->b_2pass )
	{
		rce = *rcc->rce;
		if( pict_type != rce.pict_type )
		{
			x264_log( h, X264_LOG_ERROR, "slice=%c but 2pass stats say %c\n",
				slice_type_to_char[pict_type], slice_type_to_char[rce.pict_type] );
		}
	}

	if( pict_type == SLICE_TYPE_B )
	{
		/* B-frames don't have independent ratecontrol, but rather get the
		* average QP of the two adjacent P-frames + an offset */

		int i0 = IS_X264_TYPE_I(h->fref_nearest[0]->i_type);
		int i1 = IS_X264_TYPE_I(h->fref_nearest[1]->i_type);
		int dt0 = abs(h->fenc->i_poc - h->fref_nearest[0]->i_poc);
		int dt1 = abs(h->fenc->i_poc - h->fref_nearest[1]->i_poc);
		float q0 = h->fref_nearest[0]->f_qp_avg_rc;
		float q1 = h->fref_nearest[1]->f_qp_avg_rc;

		if( h->fref_nearest[0]->i_type == X264_TYPE_BREF )
			q0 -= rcc->pb_offset/2;
		if( h->fref_nearest[1]->i_type == X264_TYPE_BREF )
			q1 -= rcc->pb_offset/2;

		if( i0 && i1 )
			q = (q0 + q1) / 2 + rcc->ip_offset;
		else if( i0 )
			q = q1;
		else if( i1 )
			q = q0;
		else
			q = (q0*dt1 + q1*dt0) / (dt0 + dt1);

		if( h->fenc->b_kept_as_ref )
			q += rcc->pb_offset/2;
		else
			q += rcc->pb_offset;

		if( rcc->b_2pass && rcc->b_vbv )
			rcc->frame_size_planned = qscale2bits( &rce, qp2qscale( q ) );
		else
			rcc->frame_size_planned = predict_size( rcc->pred_b_from_p, qp2qscale( q ), h->fref[1][h->i_ref[1]-1]->i_satd );
		/* Limit planned size by MinCR */
		if( rcc->b_vbv )
			rcc->frame_size_planned = X264_MIN( rcc->frame_size_planned, rcc->frame_size_maximum );
		h->rc->frame_size_estimated = rcc->frame_size_planned;

		/* For row SATDs */
		if( rcc->b_vbv )
			rcc->last_satd = x264_rc_analyse_slice( h );

		rcc->qp_novbv = q;

		return qp2qscale( q );
	}
	else 
#endif
	{
		double abr_buffer = 2 * rcc->rate_tolerance * rcc->bitrate;
#if 0
		if( rcc->b_2pass )
		{
			double lmin = rcc->lmin[pict_type];
			double lmax = rcc->lmax[pict_type];
			int64_t diff;
			int64_t predicted_bits = total_bits;

			if( rcc->b_vbv )
			{
				if( h->i_thread_frames > 1 )
				{
					int j = h->rc - h->thread[0]->rc;
					for( int i = 1; i < h->i_thread_frames; i++ )
					{
						x264_t *t = h->thread[ (j+i)%h->i_thread_frames ];
						double bits = t->rc->frame_size_planned;
						if( !t->b_thread_active )
							continue;
						bits = X264_MAX(bits, t->rc->frame_size_estimated);
						predicted_bits += (int64_t)bits;
					}
				}
			}
			else
			{
				if( h->i_frame < h->i_thread_frames )
					predicted_bits += (int64_t)h->i_frame * rcc->bitrate / rcc->fps;
				else
					predicted_bits += (int64_t)(h->i_thread_frames - 1) * rcc->bitrate / rcc->fps;
			}

			/* Adjust ABR buffer based on distance to the end of the video. */
			if( rcc->num_entries > h->i_frame )
			{
				double final_bits = rcc->entry[rcc->num_entries-1].expected_bits;
				double video_pos = rce.expected_bits / final_bits;
				double scale_factor = sqrt( (1 - video_pos) * rcc->num_entries );
				abr_buffer *= 0.5 * X264_MAX( scale_factor, 0.5 );
			}

			diff = predicted_bits - (int64_t)rce.expected_bits;
			q = rce.new_qscale;
			q /= x264_clip3f((double)(abr_buffer - diff) / abr_buffer, .5, 2);
			if( ((h->i_frame + 1 - h->i_thread_frames) >= rcc->fps) &&
				(rcc->expected_bits_sum > 0))
			{
				/* Adjust quant based on the difference between
				* achieved and expected bitrate so far */
				double cur_time = (double)h->i_frame / rcc->num_entries;
				double w = x264_clip3f( cur_time*100, 0.0, 1.0 );
				q *= pow( (double)total_bits / rcc->expected_bits_sum, w );
			}
			if( rcc->b_vbv )
			{
				/* Do not overflow vbv */
				double expected_size = qscale2bits( &rce, q );
				double expected_vbv = rcc->buffer_fill + rcc->buffer_rate - expected_size;
				double expected_fullness = rce.expected_vbv / rcc->buffer_size;
				double qmax = q*(2 - expected_fullness);
				double size_constraint = 1 + expected_fullness;
				qmax = X264_MAX( qmax, rce.new_qscale );
				if( expected_fullness < .05 )
					qmax = lmax;
				qmax = X264_MIN(qmax, lmax);
				while( ((expected_vbv < rce.expected_vbv/size_constraint) && (q < qmax)) ||
					((expected_vbv < 0) && (q < lmax)))
				{
					q *= 1.05;
					expected_size = qscale2bits(&rce, q);
					expected_vbv = rcc->buffer_fill + rcc->buffer_rate - expected_size;
				}
				rcc->last_satd = x264_rc_analyse_slice( h );
			}
			q = x264_clip3f( q, lmin, lmax );
		}
		else /* 1pass ABR */
#endif
		{
			/* Calculate the quantizer which would have produced the desired
			* average bitrate if it had been applied to all frames so far.
			* Then modulate that quant based on the current frame's complexity
			* relative to the average complexity so far (using the 2pass RCEQ).
			* Then bias the quant up or down if total size so far was far from
			* the target.
			* Result: Depending on the value of rate_tolerance, there is a
			* tradeoff between quality and bitrate precision. But at large
			* tolerances, the bit distribution approaches that of 2pass. */

			double wanted_bits, overflow = 1;

			rcc->last_satd = x264_rc_analyse_slice( h );
			rcc->short_term_cplxsum *= 0.5;
			rcc->short_term_cplxcount *= 0.5;
			rcc->short_term_cplxsum += rcc->last_satd / (CLIP_DURATION(h->fenc->f_duration) / BASE_FRAME_DURATION);
			rcc->short_term_cplxcount ++;

			rce.tex_bits = rcc->last_satd;
			rce.blurred_complexity = rcc->short_term_cplxsum / rcc->short_term_cplxcount;
			rce.mv_bits = 0;
			rce.p_count = rcc->nmb;
			rce.i_count = 0;
			rce.s_count = 0;
			rce.qscale = 1;
			rce.pict_type = pict_type;
			rce.i_duration = h->fenc->i_duration;

			if( h->param.rc.i_rc_method == X264_RC_CRF )
			{
				qscale = get_qscale( h, &rce, rcc->rate_factor_constant, h->fenc->i_frame );
			}
			else
			{
				qscale = get_qscale( h, &rce, rcc->wanted_bits_window / rcc->cplxr_sum, h->fenc->i_frame );

				/* ABR code can potentially be counterproductive in CBR, so just don't bother.
				* Don't run it if the frame complexity is zero either. */
				if( !rcc->b_vbv_min_rate && rcc->last_satd )
				{
					// FIXME is it simpler to keep track of wanted_bits in ratecontrol_end?
					int i_frame_done = h->i_frame + 1 - h->i_thread_frames;
					double time_done = i_frame_done / rcc->fps;

					if( h->param.b_vfr_input && i_frame_done > 0 )
					{
						time_done = ((double)(h->fenc->i_reordered_pts - h->i_reordered_pts_delay))
							* h->param.i_timebase_num / h->param.i_timebase_den;
					}

					wanted_bits = time_done * rcc->bitrate;
					if( wanted_bits > 0 )
					{
						abr_buffer *= X264_MAX( 1, sqrt( time_done ) );
						overflow = x264_clip3f( 1.0 + (total_bits - wanted_bits) / abr_buffer, .5, 2 );
						qscale *= overflow;
					}
				}
			}

			if( SLICE_TYPE_I == pict_type && h->param.i_keyint_max > 1				
				&& SLICE_TYPE_I != rcc->last_non_b_pict_type )/* should test _next_ pict type, but that isn't decided yet */
			{
				qscale = qp2qscale( rcc->accum_p_qp / rcc->accum_p_norm );
				qscale /= fabs( h->param.rc.f_ip_factor );
			}
			else if ( tp_lvl_2 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
			{
				qscale = qp2qscale( rcc->accum_p_qp / rcc->accum_p_norm );
				qscale /= fabs( h->param.rc.f_ip_factor );
			}
			else if( h->i_frame > 0 )
			{
				if( h->param.rc.i_rc_method != X264_RC_CRF )
				{
					/* Asymmetric clipping, because symmetric would prevent
					* overflow control in areas of rapidly oscillating complexity */
					double lmin = rcc->last_qscale_for[ pict_type ] / rcc->lstep;
					double lmax = rcc->last_qscale_for[ pict_type ] * rcc->lstep;
					if( overflow > 1.1 && h->i_frame > 3 )
						lmax *= rcc->lstep;
					else if( overflow < 0.9 )
						lmin /= rcc->lstep;

					qscale = x264_clip3f(qscale, lmin, lmax);
				}
			}
			else if( h->param.rc.i_rc_method == X264_RC_CRF && rcc->qcompress != 1 )
			{
				qscale = qp2qscale( ABR_INIT_QP ) / fabs( h->param.rc.f_ip_factor );
			}

			//fred q maybe modified
			rcc->qp_novbv = qscale2qp( qscale );

			//FIXME use get_diff_limited_q() ?
			qscale = clip_qscale( h, pict_type, qscale );
		}		

		if( rcc->b_2pass && rcc->b_vbv )
		{
			rcc->frame_size_planned = qscale2bits(&rce, qscale);
		}
		else
		{
// 			rc_feedback2( h, &qscale, 0 );
// 
// 			rcc->qp_novbv = qscale2qp( qscale );

			rcc->frame_size_planned = predict_size( &rcc->pred[h->sh.i_type], qscale, rcc->last_satd );

		}

		if (tp_lvl_2 == h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type)
		{
			rcc->frame_size_planned = rcc->buffer_fill*0.9;
		}

		rcc->last_qscale_for[pict_type] = rcc->last_qscale = qscale;
#if 0
		if ( tp_lvl_2 != h->fenc->curr_level && SLICE_TYPE_P == h->sh.i_type )
		{
			rcc->last_qscale_for[ predictor_id( h ) ] = qscale;
			//rcc->last_qscale = q;
		}
#endif
        
		if( !(rcc->b_2pass && !rcc->b_vbv) && h->fenc->i_frame == 0 )
		{
			float t = qscale * fabs( h->param.rc.f_ip_factor );

			rcc->last_qscale_for[SLICE_TYPE_P    ] = t;
// 			rcc->last_qscale_for[SLICE_TYPE_P + 3] = t; 
// 			rcc->last_qscale_for[SLICE_TYPE_P + 4] = t;
// 			rcc->last_qscale_for[SLICE_TYPE_P + 5] = t;
		}

		/* Always use up the whole VBV in this case. */
		if( rcc->single_frame_vbv )
			rcc->frame_size_planned = rcc->buffer_rate;

		/* Limit planned size by MinCR */
		if( rcc->b_vbv )
			rcc->frame_size_planned = X264_MIN( rcc->frame_size_planned, rcc->frame_size_maximum );        

		h->rc->frame_size_estimated = rcc->frame_size_planned;		

		return qscale;
	}
}
//fred : calc predicted size of current frame
double rc_get_frame_tar_size( x264_t *h)
{
	float qscale;
	x264_ratecontrol_t tmp_rcc;
	ratecontrol_entry_t rce;
	int pict_type = h->sh.i_type;
	int64_t total_bits = 0;
    double planed_size;    

	memcpy(&tmp_rcc, h->rc, sizeof(x264_ratecontrol_t));
	memset(&rce, 0, sizeof(rce));

    update_vbv_plan( h, 0 );

	const x264_level_t *l = x264_levels;
	while( l->level_idc != 0 && l->level_idc != h->param.i_level_idc )
		l++;

	int mincr = l->mincr;

	if( h->param.b_bluray_compat )
		mincr = 4;

	/* Profiles above High don't require minCR, so just set the maximum to a large value. */
	if( h->sps->i_profile_idc > PROFILE_HIGH )
		h->rc->frame_size_maximum = 1e9;
	else
	{
		/* The spec has a bizarre special case for the first frame. */
		if( h->i_frame == 0 )
		{
			//384 * ( Max( PicSizeInMbs, fR * MaxMBPS ) + MaxMBPS * ( tr( 0 ) - tr,n( 0 ) ) ) / MinCR
			double fr = 1. / 172;
			int pic_size_in_mbs = h->mb.i_mb_width * h->mb.i_mb_height;
			h->rc->frame_size_maximum = 384 * BIT_DEPTH * X264_MAX( pic_size_in_mbs, fr*l->mbps ) / mincr;
		}
		else
		{
			//384 * MaxMBPS * ( tr( n ) - tr( n - 1 ) ) / MinCR
			h->rc->frame_size_maximum = 384 * BIT_DEPTH * ((double)h->fenc->i_cpb_duration * h->sps->vui.i_num_units_in_tick / h->sps->vui.i_time_scale) * l->mbps / mincr;
		}
	}

	total_bits = 8*(h->stat.i_frame_size[SLICE_TYPE_I]
	+ h->stat.i_frame_size[SLICE_TYPE_P]
	+ h->stat.i_frame_size[SLICE_TYPE_B])
		- h->rc->filler_bits_sum;

	double abr_buffer = 2 * h->rc->rate_tolerance * h->rc->bitrate;    

	double wanted_bits, overflow = 1;

	h->rc->last_satd = x264_rc_analyse_slice( h );
	h->rc->short_term_cplxsum *= 0.5;
	h->rc->short_term_cplxcount *= 0.5;
	h->rc->short_term_cplxsum += h->rc->last_satd / (CLIP_DURATION(h->fenc->f_duration) / BASE_FRAME_DURATION);
	h->rc->short_term_cplxcount ++;

	rce.tex_bits = h->rc->last_satd;
	rce.blurred_complexity = h->rc->short_term_cplxsum / h->rc->short_term_cplxcount;
	rce.mv_bits = 0;
	rce.p_count = h->rc->nmb;
	rce.i_count = 0;
	rce.s_count = 0;
	rce.qscale = 1;
	rce.pict_type = pict_type;
	rce.i_duration = h->fenc->i_duration;

	if( h->param.rc.i_rc_method == X264_RC_CRF )
	{
		qscale = get_qscale( h, &rce, h->rc->rate_factor_constant, h->fenc->i_frame );
	}
	else
	{
		qscale = get_qscale( h, &rce, h->rc->wanted_bits_window / h->rc->cplxr_sum, h->fenc->i_frame );

		//* ABR code can potentially be counterproductive in CBR, so just don't bother.
		//* Don't run it if the frame complexity is zero either. */
		if( !h->rc->b_vbv_min_rate && h->rc->last_satd )
		{
			// FIXME is it simpler to keep track of wanted_bits in ratecontrol_end?
			int i_frame_done = h->i_frame + 1 - h->i_thread_frames;
			double time_done = i_frame_done / h->rc->fps;
			if( h->param.b_vfr_input && i_frame_done > 0 )
				time_done = ((double)(h->fenc->i_reordered_pts - h->i_reordered_pts_delay)) * h->param.i_timebase_num / h->param.i_timebase_den;
			wanted_bits = time_done * h->rc->bitrate;
			if( wanted_bits > 0 )
			{
				abr_buffer *= X264_MAX( 1, sqrt( time_done ) );
				overflow = x264_clip3f( 1.0 + (total_bits - wanted_bits) / abr_buffer, .5, 2 );
				qscale *= overflow;
			}
		}
	}

	if ( ( SLICE_TYPE_P == pict_type && tp_lvl_2 == h->fenc->curr_level )
		|| ( pict_type == SLICE_TYPE_I && h->param.i_keyint_max > 1 
		&& h->rc->last_non_b_pict_type != SLICE_TYPE_I ) )
	{
		qscale = qp2qscale( h->rc->accum_p_qp / h->rc->accum_p_norm );
		qscale /= fabs( h->param.rc.f_ip_factor );
	}
	else if( h->i_frame > 0 )
	{
		if( h->param.rc.i_rc_method != X264_RC_CRF )
		{
			/* Asymmetric clipping, because symmetric would prevent
			* overflow control in areas of rapidly oscillating complexity */
			double lmin = h->rc->last_qscale_for[pict_type] / h->rc->lstep;
			double lmax = h->rc->last_qscale_for[pict_type] * h->rc->lstep;
			if( overflow > 1.1 && h->i_frame > 3 )
				lmax *= h->rc->lstep;
			else if( overflow < 0.9 )
				lmin /= h->rc->lstep;

			qscale = x264_clip3f(qscale, lmin, lmax);
		}
	}
	else if( h->param.rc.i_rc_method == X264_RC_CRF && h->rc->qcompress != 1 )
	{
		qscale = qp2qscale( ABR_INIT_QP ) / fabs( h->param.rc.f_ip_factor );
	}
    
	qscale = clip_qscale( h, pict_type, qscale );	

// 	planed_size = rc_feedback2( h, &qscale, 1 );
	planed_size = predict_size( &h->rc->pred[h->sh.i_type], qscale, h->rc->last_satd );

// 	h->rc->qp_novbv = qscale2qp( qscale );

    //fred test
	LOG_M("%04d\t%05.2f\t%02d\t%.2f\t", h->rc->last_satd/1000, planed_size/1000,  
		X264_MIN(51, *p_pred_qp), h->rc->buffer_fill/h->rc->buffer_size);

	memcpy(h->rc, &tmp_rcc, sizeof(x264_ratecontrol_t));

    return planed_size;
}
/*
int drop_frame( x264_t *h, int pred_qp, int pos_in_gop )
{
    int ret, delta_qp;
    x264_ratecontrol_t* rc = h->rc;
    
    if (  0 == h->param.rc.max_drop_num
       || tp_lvl_2 == h->fenc->curr_level
       || rc->drop_count >= h->param.rc.max_drop_num
       || h->param.rc.drop_start_pos > pos_in_gop )
	{
		ret = 0;
		goto exit;
	}

    delta_qp = pred_qp - rc->last_pred_qp;

    int thresh_max_qp_with_bufover, thresh_delta_qp, thresh_pred_qp;

    if ( em_mode_normal == h->param.mode )
    {
		thresh_max_qp_with_bufover = 42 ;
		thresh_delta_qp = 8;
        thresh_pred_qp = 40;
    }
    else//must be deskshare mode
    {
        thresh_max_qp_with_bufover = 5;
        thresh_delta_qp = 5;
        thresh_pred_qp = 40;
    }

    if ( ( buf_over_with_frm > h->param.rc.vbv_drop_thr && pred_qp > thresh_max_qp_with_bufover ) 
        || (pred_qp - rc->last_pred_qp > thresh_delta_qp && pred_qp >= thresh_pred_qp ))
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    
exit:
    return ret;
    
}*/


//fred
int try_drop_frame( x264_t *h )
{
	int b_drop = 0, send_bits;
	x264_ratecontrol_t *rc = h->rc;
	x264_ratecontrol_t *rct = h->thread[0]->rc;
	int bitrate = h->sps->vui.hrd.i_bit_rate_unscaled;    
	uint64_t buffer_size = (uint64_t)h->sps->vui.hrd.i_cpb_size_unscaled * h->sps->vui.i_time_scale;
	double pred_curent_size = 0;
	double buffer_fill = h->thread[0]->rc->buffer_fill_final;

    if( X264_RC_CQP == h->param.rc.i_rc_method || !rc->b_vbv ) return 0;

	x264_emms();

//     if ( em_mode_normal == h->param.mode && 0 == gop_pos )
//         rc->buffer_over_bits = 0;

	h->sh.i_type = h->fenc->i_type == X264_TYPE_P ? SLICE_TYPE_P : SLICE_TYPE_I;
	pred_curent_size = rc_get_frame_tar_size( h );	
	pred_curent_size = (uint64_t)pred_curent_size * h->sps->vui.i_time_scale;

// 	pred_buffer_over = rc->buffer_over_bits + pred_curent_size ;    

// 	LOG_M("%.2f\t%.2f\t", 1.0*rc->buffer_over_bits/send_bits, 1.0*pred_buffer_over/send_bits );

// 	if ( em_mode_normal == h->param.mode )
// 		b_drop = drop_frame( h, 1.0*rc->buffer_over_bits/send_bits, pred_qp, gop_pos );
// 	else
// 		b_drop = drop_frame( h, 1.0*pred_buffer_over/send_bits,     pred_qp, gop_pos );

    //update pred qp 
//     rc->last_pred_qp = pred_qp;

	if (buffer_fill < pred_curent_size || buffer_fill < buffer_size*0.1)
	{
// 		b_drop = 1;
	}

	if ( 1 == b_drop )
	{
		rct->drop_count++;
		rct->drop_count_GOP++;

		rct->buffer_fill_final += (uint64_t)bitrate * h->sps->vui.i_num_units_in_tick * h->fenc->i_cpb_duration;
		rct->buffer_fill_final = X264_MIN( rct->buffer_fill_final, buffer_size );

// 		rc->buffer_over_bits -= send_bits;
		//rc->buffer_over_bits = X264_MAX(rc->buffer_over_bits, 0);

		x264_frame_push_unused( h, h->fenc );
	}
	else
	{
		rct->drop_count = 0;
	}    

	return b_drop;
}

#if RC_MAD
// mdou 
int try_drop_frame_MAD( x264_t *h)
{
	x264_ratecontrol_t *rc = h->rc;
	int b_skipframe = 0;
	if ((rc->drop_count >= h->param.rc.max_drop_num)||( h->fenc->curr_level == tp_lvl_2) /*|| (rc->num_P_left==1)//*/
		|| (rc->bits_remain>0) && (((rc->num_P_left>(rc->num_P_in_GOP*0.3))&&(rc->coded_Pframe_inGOP<=5))
		||((rc->ave_qp_frame<(h->param.rc.i_qp_max-1))&&(rc->ave_qp_frame<=45)&&( rc->curr_level_last != tp_lvl_1)) || ((rc->ave_qp_frame<h->param.rc.i_qp_max)&&(h->fdec->f_qp_avg_aq<(h->param.rc.i_qp_max-1))&&(h->fdec->f_qp_avg_aq<=45)&&( rc->curr_level_last != tp_lvl_1))
	    ||((rc->ave_qp_frame<(h->param.rc.i_qp_max-5))&&(rc->ave_qp_frame<=40)&&( rc->curr_level_last == tp_lvl_1)) || ((rc->ave_qp_frame<h->param.rc.i_qp_max-5)&&(h->fdec->f_qp_avg_aq<(h->param.rc.i_qp_max-5))&&(h->fdec->f_qp_avg_aq<=40)&&( rc->curr_level_last == tp_lvl_1))
		||((rc->ave_qp_frame<(h->param.rc.i_qp_max-3))&&(rc->num_P_in_GOP<=2))))
	{   // not drop frame  h->fdec->f_qp_avg_aq
		rc->drop_count = 0;  // clear
		return 0;
	}
	if ( ((h->param.sp_period == 0) &&( ((double)rc->bits_remain/rc->num_P_left) < rc->header_bits )) 
		|| (h->param.sp_period &&( (double)rc->bits_remain/(rc->num_P_left - rc->num_SP_left + rc->num_SP_left * rc->ratio_sp)< rc->header_bits_P)))
	{  // drop frame
		rc->drop_count++; // drop num (continue)
		rc->drop_count_GOP++;
		rc->num_P_left--;
		rc->frame_coded++;// include drop frame
		rc->coded_Pframe_inGOP++;
		int delta_bits;
		if (rc->num_P_left)
		{
			if (h->param.sp_period)
			{
				rc->num_SP_left = (rc->num_P_left + rc->num_P_before)/h->param.sp_period;
				rc->num_SP_in_GOP = (h->param.gf_period - 1-rc->drop_count_GOP)/h->param.sp_period + 1;
				// reset bitrate_frame, bitrate_SP
				rc->bitrate_frame = rc->bitrate / (h->param.gf_period - rc->drop_count_GOP + (rc->ratio_sp - 1)*rc->num_SP_in_GOP);
				rc->bitrate_SP = rc->bitrate_frame * rc->ratio_sp;
				delta_bits = rc->curr_buffer - (rc->bit_GOP - ((rc->num_SP_lastGOP + 1) * rc->bitrate_SP + rc->num_P_lastGOP * rc->bitrate_frame));
				rc->curr_buffer = rc->bit_GOP - ((rc->num_SP_lastGOP + 1) * rc->bitrate_SP + rc->num_P_lastGOP * rc->bitrate_frame);
				rc->delta_target_frame = rc->delta_target_frame * (rc->num_P_left + 1)/rc->num_P_left;

				rc->lower_bound  -= delta_bits;
				rc->upper_bound1 -= delta_bits;
				rc->upper_bound2  = (OMEGA * rc->upper_bound1);
			}
			else
			{
				delta_bits =  -rc->bitrate_frame ;
				rc->curr_buffer += delta_bits;  
				rc->delta_target_frame = rc->curr_buffer/rc->num_P_left;

				rc->lower_bound  -= delta_bits;
				rc->upper_bound1 -= delta_bits;
				rc->upper_bound2  = (OMEGA * rc->upper_bound1);
			}
		}
		//else // end of GOP
		rc->target_buffer = rc->curr_buffer - rc->delta_target_frame;

		x264_frame_push_unused( h, h->fenc );
		return 1;
	}
	else
	{
		rc->drop_count = 0;
		return 0;
	} 
	
}
#endif
static void x264_threads_normalize_predictors( x264_t *h )
{
	double totalsize = 0;
	for( int i = 0; i < h->param.i_threads; i++ )
		totalsize += h->thread[i]->rc->slice_size_planned;
	double factor = h->rc->frame_size_planned / totalsize;
	for( int i = 0; i < h->param.i_threads; i++ )
		h->thread[i]->rc->slice_size_planned *= factor;
}

void x264_threads_distribute_ratecontrol( x264_t *h )
{
	int row;
	x264_ratecontrol_t *rc = h->rc;

	/* Initialize row predictors */
	if( h->i_frame == 0 )
		for( int i = 0; i < h->param.i_threads; i++ )
		{
			x264_ratecontrol_t *t = h->thread[i]->rc;
			memcpy( t->row_preds, rc->row_preds, sizeof(rc->row_preds) );
		}

		for( int i = 0; i < h->param.i_threads; i++ )
		{
			x264_t *t = h->thread[i];
			memcpy( t->rc, rc, offsetof(x264_ratecontrol_t, row_pred) );
			t->rc->row_pred = &t->rc->row_preds[h->sh.i_type];
			/* Calculate the planned slice size. */
			if( rc->b_vbv && rc->frame_size_planned )
			{
				int size = 0;
				for( row = t->i_threadslice_start; row < t->i_threadslice_end; row++ )
					size += h->fdec->i_row_satd[row];
				t->rc->slice_size_planned = predict_size( &rc->pred[h->sh.i_type + (i+1) * PREDICTOR_TYPE_SUM ], rc->qpm, size );
			}
			else
				t->rc->slice_size_planned = 0;
		}
		if( rc->b_vbv && rc->frame_size_planned )
		{
			x264_threads_normalize_predictors( h );

			if( rc->single_frame_vbv )
			{
				/* Compensate for our max frame error threshold: give more bits (proportionally) to smaller slices. */
				for( int i = 0; i < h->param.i_threads; i++ )
				{
					x264_t *t = h->thread[i];
					float max_frame_error = X264_MAX( 0.05, 1.0 / (t->i_threadslice_end - t->i_threadslice_start) );
					t->rc->slice_size_planned += 2 * max_frame_error * rc->frame_size_planned;
				}
				x264_threads_normalize_predictors( h );
			}

			for( int i = 0; i < h->param.i_threads; i++ )
				h->thread[i]->rc->frame_size_estimated = h->thread[i]->rc->slice_size_planned;
		}
}

void x264_threads_merge_ratecontrol( x264_t *h )
{
	x264_ratecontrol_t *rc = h->rc;
	x264_emms();

	for( int i = 0; i < h->param.i_threads; i++ )
	{
		x264_t *t = h->thread[i];
		x264_ratecontrol_t *rct = h->thread[i]->rc;
		if( h->param.rc.i_vbv_buffer_size )
		{
			int size = 0;
			for( int row = t->i_threadslice_start; row < t->i_threadslice_end; row++ )
				size += h->fdec->i_row_satd[row];
			int bits = t->stat.frame.i_mv_bits + t->stat.frame.i_tex_bits + t->stat.frame.i_misc_bits;
			int mb_count = (t->i_threadslice_end - t->i_threadslice_start) * h->mb.i_mb_width;
			update_predictor( &rc->pred[h->sh.i_type+(i+1)*PREDICTOR_TYPE_SUM ], qp2qscale( rct->qpa_rc/mb_count ), size, bits );
		}
		if( !i )
			continue;
		rc->qpa_rc += rct->qpa_rc;
		rc->qpa_aq += rct->qpa_aq;
	}
}

void x264_thread_sync_ratecontrol( x264_t *cur, x264_t *prev, x264_t *next )
{
	if( cur != prev )
	{
#define COPY(var) memcpy(&cur->rc->var, &prev->rc->var, sizeof(cur->rc->var))
		/* these vars are updated in x264_ratecontrol_start()
		* so copy them from the context that most recently started (prev)
		* to the context that's about to start (cur). */
		COPY(accum_p_qp);
		COPY(accum_p_norm);
		COPY(last_satd);
		COPY(last_rceq);
		COPY(last_qscale_for);
		COPY(last_non_b_pict_type);
		COPY(short_term_cplxsum);
		COPY(short_term_cplxcount);
		COPY(bframes);
		COPY(prev_zone);
		COPY(qpbuf_pos);
		/* these vars can be updated by x264_ratecontrol_init_reconfigurable */
		COPY(bitrate);
		COPY(buffer_size);
		COPY(buffer_rate);
		COPY(vbv_max_rate);
		COPY(single_frame_vbv);
		COPY(cbr_decay);
		COPY(rate_factor_constant);
		COPY(rate_factor_max_increment);
#undef COPY
	}
	if( cur != next )
	{
#define COPY(var) next->rc->var = cur->rc->var
		/* these vars are updated in x264_ratecontrol_end()
		* so copy them from the context that most recently ended (cur)
		* to the context that's about to end (next) */
		COPY(cplxr_sum);
		COPY(expected_bits_sum);
		COPY(filler_bits_sum);
		COPY(wanted_bits_window);
		COPY(bframe_bits);
		COPY(initial_cpb_removal_delay);
		COPY(initial_cpb_removal_delay_offset);
		COPY(nrt_first_access_unit);
		COPY(previous_cpb_final_arrival_time);
#undef COPY
	}
	//FIXME row_preds[] (not strictly necessary, but would improve prediction)
	/* the rest of the variables are either constant or thread-local */
}

//fred no use code
#if 0

static int find_underflow( x264_t *h, double *fills, int *t0, int *t1, int over )
{
	/* find an interval ending on an overflow or underflow (depending on whether
	* we're adding or removing bits), and starting on the earliest frame that
	* can influence the buffer fill of that end frame. */
	x264_ratecontrol_t *rcc = h->rc;
	const double buffer_min = (over ? .1 : .1) * rcc->buffer_size;
	const double buffer_max = .9 * rcc->buffer_size;
	double fill = fills[*t0-1];
	double parity = over ? 1. : -1.;
	int start = -1, end = -1;
	for( int i = *t0; i < rcc->num_entries; i++ )
	{
		fill += (rcc->entry[i].i_cpb_duration * rcc->vbv_max_rate * h->sps->vui.i_num_units_in_tick / h->sps->vui.i_time_scale -
			qscale2bits( &rcc->entry[i], rcc->entry[i].new_qscale )) * parity;
		fill = x264_clip3f(fill, 0, rcc->buffer_size);
		fills[i] = fill;
		if( fill <= buffer_min || i == 0 )
		{
			if( end >= 0 )
				break;
			start = i;
		}
		else if( fill >= buffer_max && start >= 0 )
			end = i;
	}
	*t0 = start;
	*t1 = end;
	return start >= 0 && end >= 0;
}

static int fix_underflow( x264_t *h, int t0, int t1, double adjustment, double qscale_min, double qscale_max)
{
	x264_ratecontrol_t *rcc = h->rc;
	double qscale_orig, qscale_new;
	int adjusted = 0;
	if( t0 > 0 )
		t0++;
	for( int i = t0; i <= t1; i++ )
	{
		qscale_orig = rcc->entry[i].new_qscale;
		qscale_orig = x264_clip3f( qscale_orig, qscale_min, qscale_max );
		qscale_new  = qscale_orig * adjustment;
		qscale_new  = x264_clip3f( qscale_new, qscale_min, qscale_max );
		rcc->entry[i].new_qscale = qscale_new;
		adjusted = adjusted || (qscale_new != qscale_orig);
	}
	return adjusted;
}

static double count_expected_bits( x264_t *h )
{
	x264_ratecontrol_t *rcc = h->rc;
	double expected_bits = 0;
	for( int i = 0; i < rcc->num_entries; i++ )
	{
		ratecontrol_entry_t *rce = &rcc->entry[i];
		rce->expected_bits = expected_bits;
		expected_bits += qscale2bits( rce, rce->new_qscale );
	}
	return expected_bits;
}

static int vbv_pass2( x264_t *h, double all_available_bits )
{
	/* for each interval of buffer_full .. underflow, uniformly increase the qp of all
	* frames in the interval until either buffer is full at some intermediate frame or the
	* last frame in the interval no longer underflows.  Recompute intervals and repeat.
	* Then do the converse to put bits back into overflow areas until target size is met */

	x264_ratecontrol_t *rcc = h->rc;
	double *fills;
	double expected_bits = 0;
	double adjustment;
	double prev_bits = 0;
	int t0, t1;
	double qscale_min = qp2qscale( h->param.rc.i_qp_min );
	double qscale_max = qp2qscale( h->param.rc.i_qp_max );
	int iterations = 0;
	int adj_min, adj_max;
	CHECKED_MALLOC( double *,fills, (rcc->num_entries+1)*sizeof(double) );

	fills++;

	/* adjust overall stream size */
	do
	{
		iterations++;
		prev_bits = expected_bits;

		if( expected_bits )
		{   /* not first iteration */
			adjustment = X264_MAX(X264_MIN(expected_bits / all_available_bits, 0.999), 0.9);
			fills[-1] = rcc->buffer_size * h->param.rc.f_vbv_buffer_init;
			t0 = 0;
			/* fix overflows */
			adj_min = 1;
			while(adj_min && find_underflow( h, fills, &t0, &t1, 1 ))
			{
				adj_min = fix_underflow( h, t0, t1, adjustment, qscale_min, qscale_max );
				t0 = t1;
			}
		}

		fills[-1] = rcc->buffer_size * (1. - h->param.rc.f_vbv_buffer_init);
		t0 = 0;
		/* fix underflows -- should be done after overflow, as we'd better undersize target than underflowing VBV */
		adj_max = 1;
		while( adj_max && find_underflow( h, fills, &t0, &t1, 0 ) )
			adj_max = fix_underflow( h, t0, t1, 1.001, qscale_min, qscale_max );

		expected_bits = count_expected_bits( h );
	} while( (expected_bits < .995*all_available_bits) && ((int64_t)(expected_bits+.5) > (int64_t)(prev_bits+.5)) );

	if( !adj_max )
		x264_log( h, X264_LOG_WARNING, "vbv-maxrate issue, qpmax or vbv-maxrate too low\n");

	/* store expected vbv filling values for tracking when encoding */
	for( int i = 0; i < rcc->num_entries; i++ )
		rcc->entry[i].expected_vbv = rcc->buffer_size - fills[i];

	x264_free( fills-1 );
	return 0;
fail:
	return -1;
}

static int init_pass2( x264_t *h )
{
	x264_ratecontrol_t *rcc = h->rc;
	uint64_t all_const_bits = 0;
	double timescale = (double)h->sps->vui.i_num_units_in_tick / h->sps->vui.i_time_scale;
	double duration = 0;
	for( int i = 0; i < rcc->num_entries; i++ )
		duration += rcc->entry[i].i_duration;
	duration *= timescale;
	uint64_t all_available_bits = h->param.rc.i_bitrate * 1000. * duration;
	double rate_factor, step_mult;
	double qblur = h->param.rc.f_qblur;
	double cplxblur = h->param.rc.f_complexity_blur;
	const int filter_size = (int)(qblur*4) | 1;
	double expected_bits;
	double *qscale, *blurred_qscale;
	double base_cplx = h->mb.i_mb_count * (h->param.i_bframe ? 120 : 80);

	/* find total/average complexity & const_bits */
	for( int i = 0; i < rcc->num_entries; i++ )
	{
		ratecontrol_entry_t *rce = &rcc->entry[i];
		all_const_bits += rce->misc_bits;
	}

	if( all_available_bits < all_const_bits)
	{
		x264_log( h, X264_LOG_ERROR, "requested bitrate is too low. estimated minimum is %d kbps\n",
			(int)(all_const_bits * rcc->fps / (rcc->num_entries * 1000.)) );
		return -1;
	}

	/* Blur complexities, to reduce local fluctuation of QP.
	* We don't blur the QPs directly, because then one very simple frame
	* could drag down the QP of a nearby complex frame and give it more
	* bits than intended. */
	for( int i = 0; i < rcc->num_entries; i++ )
	{
		ratecontrol_entry_t *rce = &rcc->entry[i];
		double weight_sum = 0;
		double cplx_sum = 0;
		double weight = 1.0;
		double gaussian_weight;
		/* weighted average of cplx of future frames */
		for( int j = 1; j < cplxblur*2 && j < rcc->num_entries-i; j++ )
		{
			ratecontrol_entry_t *rcj = &rcc->entry[i+j];
			double frame_duration = CLIP_DURATION(rcj->i_duration * timescale) / BASE_FRAME_DURATION;
			weight *= 1 - pow( (float)rcj->i_count / rcc->nmb, 2 );
			if( weight < .0001 )
				break;
			gaussian_weight = weight * exp( -j*j/200.0 );
			weight_sum += gaussian_weight;
			cplx_sum += gaussian_weight * (qscale2bits( rcj, 1 ) - rcj->misc_bits) / frame_duration;
		}
		/* weighted average of cplx of past frames */
		weight = 1.0;
		for( int j = 0; j <= cplxblur*2 && j <= i; j++ )
		{
			ratecontrol_entry_t *rcj = &rcc->entry[i-j];
			double frame_duration = CLIP_DURATION(rcj->i_duration * timescale) / BASE_FRAME_DURATION;
			gaussian_weight = weight * exp( -j*j/200.0 );
			weight_sum += gaussian_weight;
			cplx_sum += gaussian_weight * (qscale2bits( rcj, 1 ) - rcj->misc_bits) / frame_duration;
			weight *= 1 - pow( (float)rcj->i_count / rcc->nmb, 2 );
			if( weight < .0001 )
				break;
		}
		rce->blurred_complexity = cplx_sum / weight_sum;
	}

	CHECKED_MALLOC(double *, qscale, sizeof(double)*rcc->num_entries );
	if( filter_size > 1 )
		CHECKED_MALLOC(double *, blurred_qscale, sizeof(double)*rcc->num_entries );
	else
		blurred_qscale = qscale;

	/* Search for a factor which, when multiplied by the RCEQ values from
	* each frame, adds up to the desired total size.
	* There is no exact closed-form solution because of VBV constraints and
	* because qscale2bits is not invertible, but we can start with the simple
	* approximation of scaling the 1st pass by the ratio of bitrates.
	* The search range is probably overkill, but speed doesn't matter here. */

	expected_bits = 1;
	for( int i = 0; i < rcc->num_entries; i++ )
	{
		double q = get_qscale(h, &rcc->entry[i], 1.0, i);
		expected_bits += qscale2bits(&rcc->entry[i], q);
		rcc->last_qscale_for[rcc->entry[i].pict_type] = q;
	}
	step_mult = all_available_bits / expected_bits;

	rate_factor = 0;
	for( double step = 1E4 * step_mult; step > 1E-7 * step_mult; step *= 0.5)
	{
		expected_bits = 0;
		rate_factor += step;

		rcc->last_non_b_pict_type = -1;
		rcc->last_accum_p_norm = 1;
		rcc->accum_p_norm = 0;

		rcc->last_qscale_for[0] =
			rcc->last_qscale_for[1] =
			rcc->last_qscale_for[2] = pow( base_cplx, 1 - rcc->qcompress ) / rate_factor;

		/* find qscale */
		for( int i = 0; i < rcc->num_entries; i++ )
		{
			qscale[i] = get_qscale( h, &rcc->entry[i], rate_factor, -1 );
			rcc->last_qscale_for[rcc->entry[i].pict_type] = qscale[i];
		}

		/* fixed I/B qscale relative to P */
		for( int i = rcc->num_entries-1; i >= 0; i-- )
		{
			qscale[i] = get_diff_limited_q( h, &rcc->entry[i], qscale[i], i );
			assert(qscale[i] >= 0);
		}

		/* smooth curve */
		if( filter_size > 1 )
		{
			assert( filter_size%2 == 1 );
			for( int i = 0; i < rcc->num_entries; i++ )
			{
				ratecontrol_entry_t *rce = &rcc->entry[i];
				double q = 0.0, sum = 0.0;

				for( int j = 0; j < filter_size; j++ )
				{
					int idx = i+j-filter_size/2;
					double d = idx-i;
					double coeff = qblur==0 ? 1.0 : exp( -d*d/(qblur*qblur) );
					if( idx < 0 || idx >= rcc->num_entries )
						continue;
					if( rce->pict_type != rcc->entry[idx].pict_type )
						continue;
					q += qscale[idx] * coeff;
					sum += coeff;
				}
				blurred_qscale[i] = q/sum;
			}
		}

		/* find expected bits */
		for( int i = 0; i < rcc->num_entries; i++ )
		{
			ratecontrol_entry_t *rce = &rcc->entry[i];
			rce->new_qscale = clip_qscale( h, rce->pict_type, blurred_qscale[i] );
			assert(rce->new_qscale >= 0);
			expected_bits += qscale2bits( rce, rce->new_qscale );
		}

		if( expected_bits > all_available_bits )
			rate_factor -= step;
	}

	x264_free( qscale );
	if( filter_size > 1 )
		x264_free( blurred_qscale );

	if( rcc->b_vbv )
		if( vbv_pass2( h, all_available_bits ) )
			return -1;
	expected_bits = count_expected_bits( h );

	if( fabs( expected_bits/all_available_bits - 1.0 ) > 0.01 )
	{
		double avgq = 0;
		for( int i = 0; i < rcc->num_entries; i++ )
			avgq += rcc->entry[i].new_qscale;
		avgq = qscale2qp( avgq / rcc->num_entries );

		if( expected_bits > all_available_bits || !rcc->b_vbv )
			x264_log( h, X264_LOG_WARNING, "Error: 2pass curve failed to converge\n" );
		x264_log( h, X264_LOG_WARNING, "target: %.2f kbit/s, expected: %.2f kbit/s, avg QP: %.4f\n",
			(float)h->param.rc.i_bitrate,
			expected_bits * rcc->fps / (rcc->num_entries * 1000.),
			avgq );
		if( expected_bits < all_available_bits && avgq < h->param.rc.i_qp_min + 2 )
		{
			if( h->param.rc.i_qp_min > 0 )
				x264_log( h, X264_LOG_WARNING, "try reducing target bitrate or reducing qp_min (currently %d)\n", h->param.rc.i_qp_min );
			else
				x264_log( h, X264_LOG_WARNING, "try reducing target bitrate\n" );
		}
		else if( expected_bits > all_available_bits && avgq > h->param.rc.i_qp_max - 2 )
		{
			if( h->param.rc.i_qp_max < QP_MAX )
				x264_log( h, X264_LOG_WARNING, "try increasing target bitrate or increasing qp_max (currently %d)\n", h->param.rc.i_qp_max );
			else
				x264_log( h, X264_LOG_WARNING, "try increasing target bitrate\n");
		}
		else if( !(rcc->b_2pass && rcc->b_vbv) )
			x264_log( h, X264_LOG_WARNING, "internal error\n" );
	}

	return 0;
fail:
	return -1;
}
#endif
#if RC_MAD
int update_qp_negative_target_P( x264_t *h ,int m_Qp)  // target bits < 0
{
	x264_ratecontrol_t *rc = h->rc;
	int PAverageQP;

	if(rc->overdue_GOP==1)
		rc->m_Qc=m_Qp+2;
	else
		rc->m_Qc=m_Qp+rc->max_delta_qp_BU;//2

	rc->m_Qc = min(rc->m_Qc, h->param.rc.i_qp_max );  // clipping
// 	rc->m_Qc = min(rc->m_Qc, rc->ave_qp_frame + 6);

	rc->sum_qp_frame +=rc->m_Qc;  
	rc->BU_left--;
	if(rc->BU_left==0)
	{  // all BU coded
		PAverageQP=(int)((double)rc->sum_qp_frame/(double)rc->BU_total+0.5);  
		if (rc->coded_Pframe_inGOP == (h->param.intra_period - 2))
			rc->qp_last_Pframe = PAverageQP;

		rc->sum_qp_GOP +=PAverageQP;
		rc->sum_qp_GOP_P += PAverageQP;
		rc->ave_qp_frame = rc->ave_qp_frame_P =PAverageQP;
		rc->PAveHeaderBits3=rc->PAveHeaderBits2;

	}
	
	rc->Pm_Qp=rc->m_Qc;

	return rc->m_Qc;
}

int update_qp_negative_target_SP( x264_t *h ,int m_Qp)  // target bits < 0
{
	x264_ratecontrol_t *rc = h->rc;
	int PAverageQP;

	if(rc->overdue_GOP==1)
		rc->m_Qc=m_Qp+2;
	else
		rc->m_Qc=m_Qp+rc->max_delta_qp_BU;//2

	rc->m_Qc = min(rc->m_Qc, h->param.rc.i_qp_max );  // clipping
	rc->m_Qc = min(rc->m_Qc, rc->ave_qp_frame + 6);

	rc->sum_qp_frame +=rc->m_Qc;  
	rc->BU_left--;
	if(rc->BU_left==0)
	{  // all BU coded
		PAverageQP=(int)((double)rc->sum_qp_frame/(double)rc->BU_total+0.5);  
		if (rc->coded_Pframe_inGOP == (h->param.intra_period - 2))
			rc->qp_last_Pframe = PAverageQP;

		rc->sum_qp_GOP +=PAverageQP;
		rc->sum_qp_GOP_SP += PAverageQP;

		rc->ave_qp_frame = rc->ave_qp_frame_SP = PAverageQP;
		rc->PAveHeaderBits3_SP=rc->PAveHeaderBits2_SP;
	}
	rc->Pm_Qp=rc->m_Qc;

	return rc->m_Qc;
}

int update_qp_first_P(  x264_t *h )
{ // first P slice in seq
	x264_ratecontrol_t *rc = h->rc;
	// first P Slice
	rc->m_Qc=rc->ave_qp_frame_first;  
	rc->header_bits_BU=0;
	rc->text_bit_BU=0;
	rc->BU_left--;
	if(rc->BU_left==0)// last BU
	{
		rc->sum_qp_GOP +=rc->m_Qc;
		rc->sum_qp_GOP_P += rc->m_Qc;
		rc->ave_qp_frame = rc->ave_qp_frame_P = rc->m_Qc;
		rc->PAveHeaderBits3=rc->PAveHeaderBits2;
	}
	rc->Pm_Qp=rc->m_Qc;
	rc->sum_qp_frame +=rc->m_Qc;  // for average P QP
	return rc->m_Qc;
}
int update_qp_first_SP(  x264_t *h )
{ // first SP slice in seq
	x264_ratecontrol_t *rc = h->rc;
	// first P Slice
	rc->m_Qc=rc->ave_qp_frame-1;
	rc->header_bits_BU=0;
	rc->text_bit_BU=0;
	rc->BU_left--;
	if(rc->BU_left==0)// last BU
	{
		rc->sum_qp_GOP +=rc->m_Qc;
		rc->sum_qp_GOP_SP += rc->m_Qc;
		rc->ave_qp_frame = rc->ave_qp_frame_SP = rc->m_Qc;
		rc->PAveHeaderBits3_SP=rc->PAveHeaderBits2_SP;
	}
	rc->Pm_Qp=rc->m_Qc;
	rc->sum_qp_frame +=rc->m_Qc;  // for average P QP
	return rc->m_Qc;
}

int update_qp_first_BU_P( x264_t *h )
{ // first BU in P frame
	x264_ratecontrol_t *rc = h->rc;

	if (rc->target_bits<=0) 
	{ // target bits < 0
		if (h->param.rc.use_drop_frame && rc->drop_count_GOP)
		{
			rc->m_Qc = rc->ave_qp_frame + 3;  // last frame qp  (SP or P)
		}
		else
		rc->m_Qc = rc->ave_qp_frame + 2; // max increase 2
		if(rc->m_Qc > (h->param.rc.i_qp_max ))
			rc->m_Qc = h->param.rc.i_qp_max;
		if (rc->target_bits<=0)
			rc->overdue_GOP=1;
	}
	else // mdou test update QP for first BU
	{
		double m_Qstep = qp2qscale(rc->ave_qp_frame_P); // last P
		m_Qstep=m_Qstep*rc->last_bits_P/rc->target_bits;
		rc->m_Qc = (int)(qscale2qp(m_Qstep));
		rc->m_Qc = x264_clip3(rc->m_Qc,rc->ave_qp_frame-2,rc->ave_qp_frame+2);  // last frame QP (SP or P)
		rc->m_Qc = x264_clip3(rc->m_Qc,h->param.rc.i_qp_min,h->param.rc.i_qp_max);
	}
	
	rc->sum_qp_frame +=rc->m_Qc;
	rc->BU_left--;
	rc->Pm_Qp = rc->m_Qc;

	return rc->m_Qc;
}


int update_qp_first_BU_SP( x264_t *h )
{ // first BU in P frame
	x264_ratecontrol_t *rc = h->rc;

	if (rc->target_bits<=0) 
	{ // target bits < 0
		if (h->param.rc.use_drop_frame && rc->drop_count_GOP)
		{
			rc->m_Qc = rc->ave_qp_frame + 2;
		}
		else
			rc->m_Qc = rc->ave_qp_frame + 1; // max increase 2
		
		if(rc->m_Qc > (h->param.rc.i_qp_max ))
			rc->m_Qc = h->param.rc.i_qp_max;
		if (rc->target_bits<=0)
			rc->overdue_GOP=1;
	}
	else if ((rc->ave_qp_frame_P>rc->ave_qp_frame_SP)&&(rc->last_bits_P>rc->last_bits_SP))
	{
		rc->m_Qc = rc->ave_qp_frame;
	}
	else // update QP for first BU
	{
		double m_Qstep = qp2qscale(rc->ave_qp_frame_SP);
		m_Qstep=m_Qstep*rc->last_bits_SP/rc->target_bits;
		rc->m_Qc = (int)(qscale2qp(m_Qstep));
		rc->m_Qc = x264_clip3(rc->m_Qc,rc->ave_qp_frame-3,rc->ave_qp_frame+2);
		rc->m_Qc = x264_clip3(rc->m_Qc,h->param.rc.i_qp_min,h->param.rc.i_qp_max);
	}

	rc->sum_qp_frame +=rc->m_Qc;
	rc->BU_left--;
	rc->Pm_Qp = rc->m_Qc;
	
	return rc->m_Qc;
}

void update_qp_P( x264_t *h, int m_Qp )
{
	double dtmp, m_Qstep;
	x264_ratecontrol_t *rc = h->rc;
	int m_Bits;
// 	int i_qp_min = max(max(m_Qp-rc->max_delta_qp_BU_check,rc->ave_qp_frame-6),h->param.rc.i_qp_min);
// 	int i_qp_max = min(min(m_Qp+rc->max_delta_qp_BU_check,rc->ave_qp_frame+6),h->param.rc.i_qp_max);
	int i_qp_min = max(m_Qp-rc->max_delta_qp_BU_check,h->param.rc.i_qp_min);
	int i_qp_max = min(m_Qp+rc->max_delta_qp_BU_check,h->param.rc.i_qp_max);
	// target bits of BU
	m_Bits = (int)(rc->bitrate*MAXVALUE/(rc->fps*rc->BU_total));// max
	if (rc->pred_sum_MAD_BU)
	{// test 10_4
		m_Bits =(int)(rc->target_bits * rc->pred_MAD_BU * rc->pred_MAD_BU / rc->pred_sum_MAD_BU);// not zero
	}
	
	// target bits of texture
	m_Bits -=rc->PAveHeaderBits2;
	i_qp_min = (m_Bits<0)?(m_Qp+rc->max_delta_qp_BU_check):i_qp_min; // 
	// mdou test RC

	m_Bits=max(m_Bits,(int)(rc->bitrate/(MINVALUE*rc->fps*rc->BU_total)));
	m_Bits=min(m_Bits,(int)(rc->bitrate*MAXVALUE/(rc->fps*rc->BU_total)));
	//m_Bits=min(m_Bits,(int)(rc->bitrate/(rc->fps*rc->BU_total)));

	dtmp = rc->pred_MAD_BU * rc->pred_MAD_BU * rc->m_X1 * rc->m_X1 \
		+ 4 * rc->m_X2 * rc->pred_MAD_BU * m_Bits;
	if ( rc->pred_MAD_BU ==0 )  // mdou test RC
	{// MAD = 0
		int ave_before = (rc->target_bits_frame - rc->target_bits)/(rc->BU_total - rc->BU_left);
		int ave_after = rc->target_bits/rc->BU_left;
		double m_Qstep = qp2qscale(m_Qp);
		m_Qstep=m_Qstep*ave_before/ave_after;
		rc->m_Qc = (int)(qscale2qp(m_Qstep));
		
		rc->m_Qc = max(rc->m_Qc, i_qp_min);
		rc->m_Qc = min(rc->m_Qc, i_qp_max);

		return;
	}
	else if ((rc->m_X2 == 0.0) || (dtmp < 0) || ((sqrt (dtmp) - rc->m_X1 * rc->pred_MAD_BU) <= 0.0))  // fall back 1st order mode
		m_Qstep = (float)(rc->m_X1 * rc->pred_MAD_BU / (double) m_Bits);  // ??MAD??QP
	else // 2nd order mode
		m_Qstep = (float) ((2 * rc->m_X2 * rc->pred_MAD_BU) / (sqrt (dtmp) - rc->m_X1 * rc->pred_MAD_BU));

	rc->m_Qc = (int)(qscale2qp(m_Qstep));
	rc->m_Qc = max(rc->m_Qc, i_qp_min);
	rc->m_Qc = min(rc->m_Qc, i_qp_max);
}

void update_qp_SP( x264_t *h, int m_Qp )
{
	double dtmp, m_Qstep;
	x264_ratecontrol_t *rc = h->rc;
	int m_Bits;
// 	int i_qp_min = max(max(m_Qp-rc->max_delta_qp_BU_check,rc->ave_qp_frame-6),h->param.rc.i_qp_min);
// 	int i_qp_max = min(min(m_Qp+rc->max_delta_qp_BU_check,rc->ave_qp_frame+6),h->param.rc.i_qp_max);
	int i_qp_min = max(m_Qp-rc->max_delta_qp_BU_check,h->param.rc.i_qp_min);
	int i_qp_max = min(m_Qp+rc->max_delta_qp_BU_check,h->param.rc.i_qp_max);
	// target bits of BU
	m_Bits = (int)(rc->bitrate*MAXVALUE_SP/(rc->fps*rc->BU_total));// max
	if (rc->pred_sum_MAD_BU)
	{// test 10_4
		m_Bits =(int)(rc->target_bits * rc->pred_MAD_BU * rc->pred_MAD_BU / rc->pred_sum_MAD_BU);// not zero
	}

	// target bits of texture
	m_Bits -=rc->PAveHeaderBits2_SP;
	i_qp_min = (m_Bits<0)?(m_Qp+rc->max_delta_qp_BU_check):i_qp_min; 

	m_Bits=max(m_Bits,(int)(rc->bitrate/(MINVALUE_SP*rc->fps*rc->BU_total)));
	m_Bits=min(m_Bits,(int)(rc->bitrate*MAXVALUE_SP/(rc->fps*rc->BU_total)));

	dtmp = rc->pred_MAD_BU * rc->pred_MAD_BU * rc->m_X1_SP * rc->m_X1_SP \
		+ 4 * rc->m_X2_SP * rc->pred_MAD_BU * m_Bits;
	
	if ( rc->pred_MAD_BU ==0 )  // mdou test RC
	{// MAD = 0
		int ave_before = (rc->target_bits_frame - rc->target_bits)/(rc->BU_total - rc->BU_left);
		int ave_after = rc->target_bits/rc->BU_left;
		double m_Qstep = qp2qscale(m_Qp);
		m_Qstep=m_Qstep*ave_before/ave_after;
		rc->m_Qc = (int)(qscale2qp(m_Qstep));

		rc->m_Qc = max(rc->m_Qc, i_qp_min);
		rc->m_Qc = min(rc->m_Qc, i_qp_max);
		return;
	}
	else if ((rc->m_X2_SP == 0.0) || (dtmp < 0) || ((sqrt (dtmp) - rc->m_X1_SP * rc->pred_MAD_BU) <= 0.0))  // fall back 1st order mode
		m_Qstep = (float)(rc->m_X1_SP * rc->pred_MAD_BU / (double) m_Bits);  
	else // 2nd order mode
		m_Qstep = (float) ((2 * rc->m_X2_SP * rc->pred_MAD_BU) / (sqrt (dtmp) - rc->m_X1_SP * rc->pred_MAD_BU));

	rc->m_Qc = (int)(qscale2qp(m_Qstep));
	rc->m_Qc = max(rc->m_Qc, i_qp_min);
	rc->m_Qc = min(rc->m_Qc, i_qp_max);
}

void predictCurrPicMAD_P( x264_t *h  )
{
	int i;
	double BUMAD;
	x264_ratecontrol_t *rc = h->rc;
	rc->pred_MAD_BU=rc->MADPictureC1*rc->BUPFMAD[rc->BU_total-rc->BU_left]+rc->MADPictureC2;
	rc->pred_sum_MAD_BU=0;
	for(i=rc->BU_total-1; i>=(rc->BU_total-rc->BU_left);i--)
	{
		BUMAD=rc->MADPictureC1*rc->BUPFMAD[i]+rc->MADPictureC2;
		rc->pred_sum_MAD_BU +=BUMAD*BUMAD;
	}

}
void predictCurrPicMAD_SP( x264_t *h  )
{
	int i;
	double BUMAD;
	x264_ratecontrol_t *rc = h->rc;
	
	rc->pred_MAD_BU=rc->MADPictureC1_SP*rc->BUPFMAD_SP[rc->BU_total-rc->BU_left]+rc->MADPictureC2_SP;
	rc->pred_sum_MAD_BU=0;
	for(i=rc->BU_total-1; i>=(rc->BU_total-rc->BU_left);i--)
	{
		BUMAD=rc->MADPictureC1_SP*rc->BUPFMAD_SP[i]+rc->MADPictureC2_SP;
		rc->pred_sum_MAD_BU +=BUMAD*BUMAD;
	}

}
int updateQP_P( x264_t *h )
{
	x264_ratecontrol_t *rc = h->rc;
	int m_Bits;
	int SumofBasicUnit;
	int m_Qp;

	if( (rc->num_GOP == 1) && (rc->coded_Pframe_inGOP == 0) )
	{// first P frame in sequence
		return update_qp_first_P( h);
	}
	else
	{
		rc->m_X1=rc->Pm_X1;
		rc->m_X2=rc->Pm_X2;
		rc->MADPictureC1=rc->PMADPictureC1;
		rc->MADPictureC2=rc->PMADPictureC2;

		m_Qp=rc->Pm_Qp;// last QP

		SumofBasicUnit=rc->BU_total;  // total BasicUnit
        
		if(rc->BU_left==SumofBasicUnit)// first BU
			return update_qp_first_BU_P( h );
		else
		{
			//compute the number of remaining bits
			rc->target_bits -= (rc->header_bits_BU + rc->text_bit_BU);  // last BU bits
			rc->header_bits_BU  = 0;
			rc->text_bit_BU = 0;
			if(rc->target_bits<0)  // target bit < 0, QP+2
				return update_qp_negative_target_P( h, m_Qp);
			else
			{// ok
				//predict the MAD of current picture
				predictCurrPicMAD_P( h );

				//compute the total number of bits for the current basic unit
				update_qp_P(h, m_Qp );

				rc->sum_qp_frame +=rc->m_Qc;  // average
				rc->Pm_Qp=rc->m_Qc;
				rc->BU_left--;
				if( rc->BU_left == 0 && h->sh.i_type == SLICE_TYPE_P ) // last BU of P frame  // not GF
				{
					int ave_qp =(int)((double)rc->sum_qp_frame/(double) rc->BU_total+0.5);  // last
					if (rc->coded_Pframe_inGOP == (h->param.intra_period - 2)) // idr_gop
						rc->qp_last_Pframe = ave_qp;

					rc->sum_qp_GOP +=ave_qp;
					rc->sum_qp_GOP_P +=ave_qp;
					rc->ave_qp_frame = rc->ave_qp_frame_P =ave_qp;
					rc->PAveHeaderBits3=rc->PAveHeaderBits2;
				}
				return rc->m_Qc;
			}
		}
	}
}

int updateQP_SP( x264_t *h )
{
	x264_ratecontrol_t *rc = h->rc;
	int m_Bits;
	int SumofBasicUnit;
	int m_Qp;


	// not first P in seq
	rc->m_X1_SP=rc->Pm_X1_SP;
	rc->m_X2_SP=rc->Pm_X2_SP;
	rc->MADPictureC1_SP=rc->PMADPictureC1_SP;
	rc->MADPictureC2_SP=rc->PMADPictureC2_SP;

	m_Qp=rc->Pm_Qp;// last QP

	SumofBasicUnit=rc->BU_total;  // total BasicUnit
    if ((rc->num_GOP == 1) && (rc->frame_coded_SP == 0))
	{// first SP frame in sequence
		return update_qp_first_SP( h);
	}
	else
	{
		if(rc->BU_left==SumofBasicUnit)// first BU
			return update_qp_first_BU_SP( h );
		else
		{
			//compute the number of remaining bits
			rc->target_bits -= (rc->header_bits_BU + rc->text_bit_BU);
			rc->header_bits_BU  = 0;
			rc->text_bit_BU = 0;
			if(rc->target_bits<0)  // target bit < 0, QP+2
				return update_qp_negative_target_SP( h, m_Qp);
			else
			{
				//predict the MAD of current picture
				predictCurrPicMAD_SP( h );

				//compute the total number of bits for the current basic unit
				update_qp_SP(h, m_Qp );

				rc->sum_qp_frame +=rc->m_Qc;  // average
				rc->Pm_Qp=rc->m_Qc;
				rc->BU_left--;
				if( rc->BU_left == 0 && h->sh.i_type == SLICE_TYPE_P ) // last BU of P frame  // not GF
				{
					int ave_qp =(int)((double)rc->sum_qp_frame/(double) rc->BU_total+0.5);  // last
					if (rc->coded_Pframe_inGOP == (h->param.intra_period - 2)) // idr_gop
						rc->qp_last_Pframe = ave_qp; // just for last GOP

					rc->sum_qp_GOP +=ave_qp;
					rc->sum_qp_GOP_SP +=ave_qp;
					rc->ave_qp_frame = rc->ave_qp_frame_SP = ave_qp;
					rc->PAveHeaderBits3_SP=rc->PAveHeaderBits2_SP;
				}
				
				return rc->m_Qc;
			}
		}
	}
	
}

// mdou RC MAD BU
// each BU
void update_RC_model_P (x264_t *h, int n_windowSize, BOOL *m_rgRejected)
{
	int n_realSize = n_windowSize;
	int i;
	double oneSampleQ = 0;
	double a00 = 0.0, a01 = 0.0, a10 = 0.0, a11 = 0.0, b0 = 0.0, b1 = 0.0;
	double MatrixValue;
	x264_ratecontrol_t *rc = h->rc;
	BOOL estimateX2 = FALSE;

	for (i = 0; i < n_windowSize; i++)
	{// find the number of samples which are not rejected
		if (m_rgRejected[i])
			n_realSize--;
	}

	// default RD model estimation results
	rc->m_X1 = rc->m_X2 = 0.0;

	for (i = 0; i < n_windowSize; i++)
	{
		if (!m_rgRejected[i])
			oneSampleQ = rc->m_rgQp[i];
	}
	for (i = 0; i < n_windowSize; i++)
	{// if all non-rejected Q are the same, take 1st order model
		if ((rc->m_rgQp[i] != oneSampleQ) && !m_rgRejected[i])
			estimateX2 = TRUE;
		if (!m_rgRejected[i])
			rc->m_X1 += (rc->m_rgQp[i] * rc->m_rgRp[i]) / n_realSize;
	}

	// take 2nd order model to estimate X1 and X2
	if ((n_realSize >= 1) && estimateX2)
	{
		for (i = 0; i < n_windowSize; i++)
		{
			if (!m_rgRejected[i])
			{
				a00  = a00 + 1.0;
				a01 += 1.0 / rc->m_rgQp[i];
				a10  = a01;
				a11 += 1.0 / (rc->m_rgQp[i] * rc->m_rgQp[i]);
				b0  += rc->m_rgQp[i] * rc->m_rgRp[i];
				b1  += rc->m_rgRp[i];
			}
		}
		// solve the equation of AX = B
		MatrixValue=a00*a11-a01*a10;
		if(fabs(MatrixValue) > 0.00001)
		{
			rc->m_X1 = (b0 * a11 - b1 * a01) / MatrixValue;
			rc->m_X2 = (b1 * a00 - b0 * a10) / MatrixValue;
		}
		else
		{
			rc->m_X1 = b0 / a00;
			rc->m_X2 = 0.0;
		}
	}
	rc->Pm_X1 = rc->m_X1;
	rc->Pm_X2 = rc->m_X2;
}

void update_RC_model_SP (x264_t *h, int n_windowSize, BOOL *m_rgRejected)
{
	int n_realSize = n_windowSize;
	int i;
	double oneSampleQ = 0;
	double a00 = 0.0, a01 = 0.0, a10 = 0.0, a11 = 0.0, b0 = 0.0, b1 = 0.0;
	double MatrixValue;
	x264_ratecontrol_t *rc = h->rc;
	BOOL estimateX2 = FALSE;

	for (i = 0; i < n_windowSize; i++)
	{// find the number of samples which are not rejected
		if (m_rgRejected[i])
			n_realSize--;
	}

	// default RD model estimation results
	rc->m_X1_SP = rc->m_X2_SP = 0.0;

	for (i = 0; i < n_windowSize; i++)
	{
		if (!m_rgRejected[i])
			oneSampleQ = rc->m_rgQp_SP[i];
	}
	for (i = 0; i < n_windowSize; i++)
	{// if all non-rejected Q are the same, take 1st order model
		if ((rc->m_rgQp_SP[i] != oneSampleQ) && !m_rgRejected[i])
			estimateX2 = TRUE;
		if (!m_rgRejected[i])
			rc->m_X1_SP += (rc->m_rgQp_SP[i] * rc->m_rgRp_SP[i]) / n_realSize;
	}

	// take 2nd order model to estimate X1 and X2
	if ((n_realSize >= 1) && estimateX2)
	{
		for (i = 0; i < n_windowSize; i++)
		{
			if (!m_rgRejected[i])
			{
				a00  = a00 + 1.0;
				a01 += 1.0 / rc->m_rgQp_SP[i];
				a10  = a01;
				a11 += 1.0 / (rc->m_rgQp_SP[i] * rc->m_rgQp_SP[i]);
				b0  += rc->m_rgQp_SP[i] * rc->m_rgRp_SP[i];
				b1  += rc->m_rgRp_SP[i];
			}
		}
		// solve the equation of AX = B
		MatrixValue=a00*a11-a01*a10;
		if(fabs(MatrixValue) > 0.00001)
		{
			rc->m_X1_SP = (b0 * a11 - b1 * a01) / MatrixValue;
			rc->m_X2_SP = (b1 * a00 - b0 * a10) / MatrixValue;
		}
		else
		{
			rc->m_X1_SP = b0 / a00;
			rc->m_X2_SP = 0.0;
		}
	}
	
	rc->Pm_X1_SP = rc->m_X1_SP;
	rc->Pm_X2_SP = rc->m_X2_SP;
}

// each BU
void update_MAD_param_P (x264_t *h, int n_windowSize, BOOL *PictureRejected)
{ 
	int    n_realSize = n_windowSize;
	int    i;
	double oneSampleQ = 0.0;
	double a00 = 0.0, a01 = 0.0, a10 = 0.0, a11 = 0.0, b0 = 0.0, b1 = 0.0;
	double MatrixValue;
	x264_ratecontrol_t *rc = h->rc;
	BOOL estimateX2 = FALSE;

	for (i = 0; i < n_windowSize; i++)
	{// find the number of samples which are not rejected
		if (PictureRejected[i])
			n_realSize--;
	}

	// default MAD model estimation results
	rc->MADPictureC1 = rc->MADPictureC2 = 0.0;

	for (i = 0; i < n_windowSize; i++)
	{
		if (!PictureRejected[i])
			oneSampleQ = rc->PictureMAD[i];
	}

	for (i = 0; i < n_windowSize; i++)
	{// if all non-rejected MAD are the same, take 1st order model
		if ((rc->PictureMAD[i] != oneSampleQ) && !PictureRejected[i])
			estimateX2 = TRUE;
		//if (!PictureRejected[i])  // mdou
		if ((!PictureRejected[i])&&(rc->ReferenceMAD[i]*n_realSize))
			rc->MADPictureC1 += rc->PictureMAD[i] / (rc->ReferenceMAD[i]*n_realSize);//

	}

	// take 2nd order model to estimate X1 and X2
	if ((n_realSize >= 1) && estimateX2)
	{
		for (i = 0; i < n_windowSize; i++)
		{
			if (!PictureRejected[i])
			{
				a00  = a00 + 1.0;
				a01 += rc->ReferenceMAD[i];
				a10  = a01;
				a11 += rc->ReferenceMAD[i] * rc->ReferenceMAD[i];
				b0  += rc->PictureMAD[i];
				b1  += rc->PictureMAD[i]   * rc->ReferenceMAD[i];
			}
		}
		// solve the equation of AX = B
		MatrixValue = a00 * a11 - a01 * a10;
		if(fabs(MatrixValue) > 0.000001)
		{
			rc->MADPictureC2 = (b0 * a11 - b1 * a01) / MatrixValue;
			rc->MADPictureC1 = (b1 * a00 - b0 * a10) / MatrixValue;
		}
		// mdou test
		else if (a01)
		{
			rc->MADPictureC1 = b0/a01;
			rc->MADPictureC2 = 0.0;
		}
		else
		{
			rc->MADPictureC1 = b0/ 0.000001;
			rc->MADPictureC2 = 0.0;
		}
	}
	if( SLICE_TYPE_P == h->sh.i_type )
	{
		rc->PMADPictureC1 = rc->MADPictureC1;
		rc->PMADPictureC2 = rc->MADPictureC2;
	}
}

void update_MAD_param_SP (x264_t *h, int n_windowSize, BOOL *PictureRejected)
{ 
	int    n_realSize = n_windowSize;
	int    i;
	double oneSampleQ = 0.0;
	double a00 = 0.0, a01 = 0.0, a10 = 0.0, a11 = 0.0, b0 = 0.0, b1 = 0.0;
	double MatrixValue;
	x264_ratecontrol_t *rc = h->rc;
	BOOL estimateX2 = FALSE;

	for (i = 0; i < n_windowSize; i++)
	{// find the number of samples which are not rejected
		if (PictureRejected[i])
			n_realSize--;
	}

	// default MAD model estimation results
	rc->MADPictureC1_SP = rc->MADPictureC2_SP = 0.0;

	for (i = 0; i < n_windowSize; i++)
	{
		if (!PictureRejected[i])
			oneSampleQ = rc->PictureMAD_SP[i];
	}

	for (i = 0; i < n_windowSize; i++)
	{// if all non-rejected MAD are the same, take 1st order model
		if ((rc->PictureMAD_SP[i] != oneSampleQ) && !PictureRejected[i])
			estimateX2 = TRUE;
		//if (!PictureRejected[i])  // mdou
		if ((!PictureRejected[i])&&(rc->ReferenceMAD_SP[i]*n_realSize))
			rc->MADPictureC1_SP += rc->PictureMAD_SP[i] / (rc->ReferenceMAD_SP[i]*n_realSize);//

	}

	// take 2nd order model to estimate X1 and X2
	if ((n_realSize >= 1) && estimateX2)
	{
		for (i = 0; i < n_windowSize; i++)
		{
			if (!PictureRejected[i])
			{
				a00  = a00 + 1.0;
				a01 += rc->ReferenceMAD_SP[i];
				a10  = a01;
				a11 += rc->ReferenceMAD_SP[i] * rc->ReferenceMAD_SP[i];
				b0  += rc->PictureMAD_SP[i];
				b1  += rc->PictureMAD_SP[i]   * rc->ReferenceMAD_SP[i];
			}
		}
		// solve the equation of AX = B
		MatrixValue = a00 * a11 - a01 * a10;
		if(fabs(MatrixValue) > 0.000001)
		{
			rc->MADPictureC2_SP = (b0 * a11 - b1 * a01) / MatrixValue;
			rc->MADPictureC1_SP = (b1 * a00 - b0 * a10) / MatrixValue;
		}
		// mdou test
		else if (a01)
		{
			rc->MADPictureC1_SP = b0/a01;
			rc->MADPictureC2_SP = 0.0;
		}
		else
		{
			rc->MADPictureC1_SP = b0/ 0.000001;
			rc->MADPictureC2_SP = 0.0;
		}
	}
	if( SLICE_TYPE_P == h->sh.i_type )
	{
		rc->PMADPictureC1_SP = rc->MADPictureC1_SP;
		rc->PMADPictureC2_SP = rc->MADPictureC2_SP;
	}
}

void update_MAD_model_P (x264_t *h)
{// after each BU (except first P)
	int    n_windowSize;
	int    i;
	double std = 0.0, threshold;
	x264_ratecontrol_t *rc = h->rc;
	int    m_Nc;
	BOOL PictureRejected[RC_MODEL_HISTORY];
	double  error          [RC_MODEL_HISTORY];

	if(rc->frame_coded_P>0)
	{
		// basic unit layer rate control
		m_Nc=rc->frame_coded_P*rc->BU_total+rc->BU_coded;

		for (i = (RC_MODEL_HISTORY-2); i > 0; i--)
		{// update the history
			rc->PPictureMAD[i]  = rc->PPictureMAD[i - 1];
			rc->PictureMAD[i]   = rc->PPictureMAD[i];
			rc->ReferenceMAD[i] = rc->ReferenceMAD[i-1];
		}
		rc->PPictureMAD[0] = rc->pred_MAD_BU;
		rc->PictureMAD[0]  = rc->PPictureMAD[0];

		rc->ReferenceMAD[0]=rc->BUPFMAD[rc->BU_total-1-rc->BU_left];

		rc->MADPictureC1 = rc->PMADPictureC1;
		rc->MADPictureC2 = rc->PMADPictureC2;

		/*compute the size of window*/
		n_windowSize = (rc->pred_MAD_BU > rc->prev_frame_MAD_BU)
			? (int) ((float)(RC_MODEL_HISTORY-1) * rc->prev_frame_MAD_BU / rc->pred_MAD_BU)
			: (int) ((float)(RC_MODEL_HISTORY-1) * rc->pred_MAD_BU / rc->prev_frame_MAD_BU);
		n_windowSize = x264_clip3(n_windowSize,1, (m_Nc-1));
		n_windowSize=min(n_windowSize, min(20, rc->MADm_windowSize + 1));

		/*update the previous window size*/
		rc->MADm_windowSize=n_windowSize;

		for (i = 0; i < (RC_MODEL_HISTORY-1); i++)
		{
			PictureRejected[i] = FALSE;
		}

		//update the MAD for the previous frame
		if( SLICE_TYPE_P == h->sh.i_type   )
			rc->prev_frame_MAD_BU=rc->pred_MAD_BU;

		// initial MAD model estimator
		update_MAD_param_P(h, n_windowSize, PictureRejected);

		// remove outlier
		for (i = 0; i < n_windowSize; i++)
		{
			error[i] = rc->MADPictureC1 * rc->ReferenceMAD[i] + rc->MADPictureC2 - rc->PictureMAD[i];
			std += (error[i] * error[i]);
		}

		threshold = (n_windowSize == 2) ? 0 : sqrt (std / n_windowSize);
		for (i = 0; i < n_windowSize; i++)
		{
			if (fabs(error[i]) > threshold)
				PictureRejected[i] = TRUE;
		}
		// always include the last data point
		PictureRejected[0] = FALSE;

		// second MAD model estimator
		update_MAD_param_P (h, n_windowSize, PictureRejected);
	}
}


void update_MAD_model_SP (x264_t *h)
{// after each BU (except first SP)
	int    n_windowSize;
	int    i;
	double std = 0.0, threshold;
	x264_ratecontrol_t *rc = h->rc;
	int    m_Nc;
	BOOL PictureRejected[RC_MODEL_HISTORY_SP];
	double  error          [RC_MODEL_HISTORY_SP];

	if(rc->frame_coded_SP>0)
	{
		// basic unit layer rate control
		m_Nc=rc->frame_coded_SP*rc->BU_total+rc->BU_coded;

		for (i = (RC_MODEL_HISTORY_SP-2); i > 0; i--)
		{// update the history
			rc->PPictureMAD_SP[i]  = rc->PPictureMAD_SP[i - 1];
			rc->PictureMAD_SP[i]   = rc->PPictureMAD_SP[i];
			rc->ReferenceMAD_SP[i] = rc->ReferenceMAD_SP[i-1];
		}
		rc->PPictureMAD_SP[0] = rc->pred_MAD_BU;
		rc->PictureMAD_SP[0]  = rc->PPictureMAD_SP[0];

		rc->ReferenceMAD_SP[0]=rc->BUPFMAD_SP[rc->BU_total-1-rc->BU_left];

		rc->MADPictureC1_SP = rc->PMADPictureC1_SP;
		rc->MADPictureC2_SP = rc->PMADPictureC2_SP;

		/*compute the size of window*/
		n_windowSize = (rc->pred_MAD_BU > rc->prev_frame_MAD_BU)
			? (int) ((float)(RC_MODEL_HISTORY_SP-1) * rc->prev_frame_MAD_BU / rc->pred_MAD_BU)
			: (int) ((float)(RC_MODEL_HISTORY_SP-1) * rc->pred_MAD_BU / rc->prev_frame_MAD_BU);
		n_windowSize = x264_clip3(n_windowSize,1, (m_Nc-1));
		n_windowSize=min(n_windowSize, min(20, rc->MADm_windowSize_SP + 1));

		/*update the previous window size*/
		rc->MADm_windowSize_SP=n_windowSize;

		for (i = 0; i < (RC_MODEL_HISTORY_SP-1); i++)
		{
			PictureRejected[i] = FALSE;
		}

		rc->prev_frame_MAD_BU=rc->pred_MAD_BU;

		// initial MAD model estimator
		update_MAD_param_SP (h, n_windowSize, PictureRejected);

		// remove outlier
		for (i = 0; i < n_windowSize; i++)
		{
			error[i] = rc->MADPictureC1_SP * rc->ReferenceMAD_SP[i] + rc->MADPictureC2_SP - rc->PictureMAD_SP[i];
			std += (error[i] * error[i]);
		}

		threshold = (n_windowSize == 2) ? 0 : sqrt (std / n_windowSize);
		for (i = 0; i < n_windowSize; i++)
		{
			if (fabs(error[i]) > threshold)
				PictureRejected[i] = TRUE;
		}
		// always include the last data point
		PictureRejected[0] = FALSE;

		// second MAD model estimator
		update_MAD_param_SP (h, n_windowSize, PictureRejected);
	}
}


void updateRCModel_P (x264_t *h)
{// after a BU
	int n_windowSize;
	int i;
	double std = 0.0, threshold;
	x264_ratecontrol_t *rc = h->rc;
	int m_Nc = rc->frame_coded_P;
	BOOL MADModelFlag = FALSE;
	BOOL m_rgRejected[RC_MODEL_HISTORY];
	double  error       [RC_MODEL_HISTORY];

	{
		rc->pred_MAD_BU = (double) ((rc->sum_MAD_BU >> 8)/rc->MBs_in_BU);
		// sum_MAD_BU: total MAD of MB in last BU
		rc->sum_MAD_BU=0; // reset

		// predict header bit
		rc->BU_coded=rc->BU_total-rc->BU_left;  // num of BU, encoded
		if(rc->BU_coded > 0)
		{
			rc->PAveHeaderBits1=(int)((double)(rc->PAveHeaderBits1*(rc->BU_coded-1)+
				rc->header_bits_BU)/rc->BU_coded+0.5);
			if(rc->PAveHeaderBits3 == 0)
				rc->PAveHeaderBits2 = rc->PAveHeaderBits1;
			else
			{
				rc->PAveHeaderBits2 = (int)((double)(rc->PAveHeaderBits1 * rc->BU_coded+
					rc->PAveHeaderBits3 * rc->BU_left)/rc->BU_total+0.5);
			}
		}

		// update the MAD
		rc->BUCFMAD[rc->BU_total-1-rc->BU_left]=rc->pred_MAD_BU; // average MB MAD of last BU

		if(rc->BU_left != 0)  // not last BU
			m_Nc = rc->frame_coded_P * rc->BU_total + rc->BU_coded;
		else
			m_Nc = (rc->frame_coded_P-1) * rc->BU_total + rc->BU_coded;

		if(m_Nc > 1)
			MADModelFlag=TRUE;

		for (i = (RC_MODEL_HISTORY-2); i > 0; i--)  
		{// update the history
			rc->Pm_rgQp[i] = rc->Pm_rgQp[i - 1];
			rc->m_rgQp[i]  = rc->Pm_rgQp[i];
			rc->Pm_rgRp[i] = rc->Pm_rgRp[i - 1];
			rc->m_rgRp[i]  = rc->Pm_rgRp[i];
		}
		
		rc->Pm_rgQp[0] = qp2qscale(rc->m_Qc); // qp step of last BU

		rc->Pm_rgRp[0] = rc->text_bit_BU*1.0/rc->pred_MAD_BU;  // text bits/ prediction MAD of BU

		rc->m_rgQp[0] = rc->Pm_rgQp[0];  // last BU, maybe last frame
		rc->m_rgRp[0] = rc->Pm_rgRp[0];
		rc->m_X1 = rc->Pm_X1;
		rc->m_X2 = rc->Pm_X2;

		// update size of window
		n_windowSize = (rc->pred_MAD_BU > rc->prev_frame_MAD_BU)
			? (int)(rc->prev_frame_MAD_BU/rc->pred_MAD_BU * (RC_MODEL_HISTORY-1) )  // RC_MODEL_HISTORY = 21
			: (int)(rc->pred_MAD_BU/rc->prev_frame_MAD_BU *(RC_MODEL_HISTORY-1));
		
		n_windowSize=x264_clip3(n_windowSize,1, m_Nc);
		n_windowSize=min(n_windowSize,rc->m_windowSize+1); // increase 1
		n_windowSize=min(n_windowSize,(RC_MODEL_HISTORY-1));  
		// update
		rc->m_windowSize=n_windowSize;

		for (i = 0; i < (RC_MODEL_HISTORY-1); i++)
		{
			m_rgRejected[i] = FALSE;
		}

		// initial RC model
		update_RC_model_P (h, n_windowSize, m_rgRejected); 

		n_windowSize = rc->m_windowSize;

		for (i = 0; i < (int) n_windowSize; i++)
		{
			error[i] = rc->m_X1 / rc->m_rgQp[i] + rc->m_X2 / (rc->m_rgQp[i] * rc->m_rgQp[i]) - rc->m_rgRp[i];
			std += error[i] * error[i];
		}
		threshold = (n_windowSize == 2) ? 0 : sqrt (std / n_windowSize);
		for (i = 0; i < (int) n_windowSize; i++)
		{
			if (fabs(error[i]) > threshold)
				m_rgRejected[i] = TRUE;
		}
		m_rgRejected[0] = FALSE;

		// second RC model
		update_RC_model_P (h, n_windowSize, m_rgRejected);

		if( MADModelFlag )
			update_MAD_model_P(h);  // not first P frame
		else if( SLICE_TYPE_P == h->sh.i_type )
			rc->PPictureMAD[0] = rc->pred_MAD_BU;
	}
}


void updateRCModel_SP (x264_t *h)
{// after a BU
	int n_windowSize;
	int i;
	double std = 0.0, threshold;
	x264_ratecontrol_t *rc = h->rc;
	int m_Nc = rc->frame_coded_SP;
	BOOL MADModelFlag = FALSE;
	BOOL m_rgRejected[RC_MODEL_HISTORY_SP];
	double  error       [RC_MODEL_HISTORY_SP];

	{
		rc->pred_MAD_BU = (double) ((rc->sum_MAD_BU >> 8)/rc->MBs_in_BU);
		// sum_MAD_BU: total MAD of MB in last BU
		rc->sum_MAD_BU=0; // reset

		// predict header bit
		rc->BU_coded=rc->BU_total-rc->BU_left;  // num of BU, encoded
		if(rc->BU_coded > 0)
		{
			rc->PAveHeaderBits1_SP=(int)((double)(rc->PAveHeaderBits1_SP*(rc->BU_coded-1)+
				rc->header_bits_BU)/rc->BU_coded+0.5);
			if(rc->PAveHeaderBits3_SP == 0)
				rc->PAveHeaderBits2_SP = rc->PAveHeaderBits1_SP;
			else
			{
				rc->PAveHeaderBits2_SP = (int)((double)(rc->PAveHeaderBits1_SP * rc->BU_coded+
					rc->PAveHeaderBits3_SP * rc->BU_left)/rc->BU_total+0.5);
			}
		}

		// update the MAD
		rc->BUCFMAD[rc->BU_total-1-rc->BU_left]=rc->pred_MAD_BU; // average MB MAD of last BU

		if(rc->BU_left != 0)  // not last BU
			m_Nc = rc->frame_coded_SP * rc->BU_total + rc->BU_coded;
		else
			m_Nc = (rc->frame_coded_SP-1) * rc->BU_total + rc->BU_coded;

		if(m_Nc > 1)
			MADModelFlag=TRUE;

		for (i = (RC_MODEL_HISTORY_SP-2); i > 0; i--)  
		{// update the history
			rc->Pm_rgQp_SP[i] = rc->Pm_rgQp_SP[i - 1];
			rc->m_rgQp_SP[i]  = rc->Pm_rgQp_SP[i];
			rc->Pm_rgRp_SP[i] = rc->Pm_rgRp_SP[i - 1];
			rc->m_rgRp_SP[i]  = rc->Pm_rgRp_SP[i];
		}

		rc->Pm_rgQp_SP[0] = qp2qscale(rc->m_Qc); // qp step of last BU

		rc->Pm_rgRp_SP[0] = rc->text_bit_BU*1.0/rc->pred_MAD_BU;  // text bits/ prediction MAD of BU

		rc->m_rgQp_SP[0] = rc->Pm_rgQp_SP[0];  // last BU, maybe last frame
		rc->m_rgRp_SP[0] = rc->Pm_rgRp_SP[0];
		rc->m_X1_SP = rc->Pm_X1_SP;
		rc->m_X2_SP = rc->Pm_X2_SP;

		// update size of window
		n_windowSize = (rc->pred_MAD_BU > rc->prev_frame_MAD_BU)
			? (int)(rc->prev_frame_MAD_BU/rc->pred_MAD_BU * (RC_MODEL_HISTORY_SP-1) )  
			: (int)(rc->pred_MAD_BU/rc->prev_frame_MAD_BU *(RC_MODEL_HISTORY_SP-1));

		n_windowSize=x264_clip3(n_windowSize,1, m_Nc);
		n_windowSize=min(n_windowSize,rc->m_windowSize_SP+1); // increase 1
		n_windowSize=min(n_windowSize,(RC_MODEL_HISTORY_SP-1));  
		// update
		rc->m_windowSize_SP=n_windowSize;

		for (i = 0; i < (RC_MODEL_HISTORY_SP-1); i++)
		{
			m_rgRejected[i] = FALSE;
		}

		// initial RC model
		update_RC_model_SP (h, n_windowSize, m_rgRejected); 
		
		n_windowSize = rc->m_windowSize_SP;

		for (i = 0; i < (int) n_windowSize; i++)
		{
			error[i] = rc->m_X1_SP / rc->m_rgQp_SP[i] + rc->m_X2_SP / (rc->m_rgQp_SP[i] * rc->m_rgQp_SP[i]) - rc->m_rgRp_SP[i];
			std += error[i] * error[i];
		}
		threshold = (n_windowSize == 2) ? 0 : sqrt (std / n_windowSize);
		for (i = 0; i < (int) n_windowSize; i++)
		{
			if (fabs(error[i]) > threshold)
				m_rgRejected[i] = TRUE;
		}
		m_rgRejected[0] = FALSE;

		// second RC model
		update_RC_model_SP (h, n_windowSize, m_rgRejected);

		if( MADModelFlag )
			update_MAD_model_SP(h);  // not first P frame
		else if( SLICE_TYPE_P == h->sh.i_type )
			rc->PPictureMAD_SP[0] = rc->pred_MAD_BU;
		
	}
}
void rc_store_slice_header_bits( x264_t *h, int len )
{// frame ?
	h->rc->header_bits =len;
}//*/
void rc_init_seq(x264_t *h)
{
	double L0,L1,L2,L3,L4,bpp;
	int qp, i;
	x264_ratecontrol_t *rc = h->rc;

	rc->Xp=0;

	rc->MBs_in_BU = h->mb.i_mb_width;
	rc->BU_total = h->mb.i_mb_height;
	rc->ratio_sp = 3;
	rc->num_SP_left = 0;
// 	rc->overdue_first_frame = 0;
	rc->max_first = rc->fps*0.5;//max(30,rc->fps);

	rc->curr_buffer = 0;
	rc->frame_coded = 0;
	rc->frame_coded_P = 0;
	rc->frame_coded_SP = 0;
	rc->num_GOP  = 0;
	rc->last_bits_P = 0;

	rc->bits_remain = 0;
	rc->GAMMAP=0.5;
	rc->BETAP=0.5;

	rc->m_windowSize = rc->m_windowSize_SP = 0;
	rc->MADm_windowSize = rc->MADm_windowSize_SP = 0;
	

	rc->Pm_X1 = rc->Pm_X1_SP = rc->bitrate * 1.0;
	rc->Pm_X2 = rc->Pm_X2_SP = 0.0;
	rc->PMADPictureC1 = rc->PMADPictureC1_SP = 1.0;
	rc->PMADPictureC2 = rc->PMADPictureC2_SP = 0.0;

	// init for each window
	for(i=0;i<RC_MODEL_HISTORY;i++)
	{
		rc->Pm_rgQp[i] = 0;
		rc->Pm_rgRp[i] = 0.0;
		rc->PPictureMAD[i] = 0.0;
	}
	for(i=0;i<RC_MODEL_HISTORY_SP;i++)
	{
		rc->Pm_rgQp_SP[i] = 0;
		rc->Pm_rgRp_SP[i] = 0.0;
		rc->PPictureMAD_SP[i] = 0.0;
	}
	rc->PAveHeaderBits1 = rc->PAveHeaderBits1_SP = 0;
	rc->PAveHeaderBits3 = rc->PAveHeaderBits3_SP = 0;
	rc->max_delta_qp_BU = rc->max_delta_qp_BU_check = 2;//(rc->BU_total>=9 ? 1 : 2);

	// init QP
	{
		bpp = 1.0*rc->bitrate /(rc->fps*h->param.i_width*h->param.i_height);

		if (rc->fps>=50)
		{
			if (h->param.i_width <= 176)
			{
				L0 = 0.008;	L1 = 0.04;		L2 = 0.12;		L3 = 0.27;		L4 = 0.5;
			}
			else if (h->param.i_width <= 352)
			{ 
				L0 = 0.015;		L1 = 0.08;		L2 = 0.15;		L3 = 0.55;		L4 = 1.0;
			}
			else if (h->param.i_width <= 640)
			{
				L0 = 0.015;		L1 = 0.08;		L2 = 0.15;		L3 = 0.55;		L4 = 1.0;
			}
			else 
			{
				L0 = 0.01;		L1 = 0.5;		L2 = 0.15;		L3 = 0.4;		L4 = 0.7;
			}
		}
		else
		{
			if (h->param.i_width <= 176)
			{
				L0 = 0.01;	L1 = 0.05;		L2 = 0.15;		L3 = 0.35;		L4 = 0.6;
			}
			else if (h->param.i_width <= 352)
			{ 
				L0 = 0.02;		L1 = 0.1;		L2 = 0.3;		L3 = 0.7;		L4 = 1.2;
			}
			else if (h->param.i_width <= 640)
			{
				L0 = 0.02;		L1 = 0.1;		L2 = 0.3;		L3 = 0.7;		L4 = 1.2;
			}
			else 
			{
				L0 = 0.02;		L1 = 0.1;		L2 = 0.3;		L3 = 0.7;		L4 = 1.2;
			}
		}
		
		if (bpp<= L0)
			qp = 38;
		else if (bpp<= L1)
			qp = 35;
		else if(bpp<=L2)
			qp = 30;
		else if(bpp<=L3)
			qp = 25;
		else if(bpp<=L4)
			qp = 20;
		else
			qp = 15;
		rc->init_qp_GOP =  qp;
	}
}

void rc_init_GOP(x264_t *h, int np)
{

	int GOPDquant;
	x264_ratecontrol_t *rc = h->rc;
	int64_t AllocatedBits;

	// init bound
	rc->lower_bound  = (int)(rc->bits_remain );
	rc->upper_bound1 = (int)(rc->bits_remain + (rc->bitrate * 2.048));
	rc->upper_bound2  = (OMEGA * rc->upper_bound1);
		

	rc->num_P_left = np;
	AllocatedBits = (int64_t) floor((1 + np ) * rc->bitrate / rc->fps + 0.5);
	rc->bits_remain += AllocatedBits;

	rc->overdue_GOP=0;
#if SHOW_QP
	{
		FILE* fp_bit = fopen("x264_bit.txt","a+");
		fprintf(fp_bit,"%d\t",rc->drop_count_GOP);
		fclose(fp_bit);
	}
#endif
	rc->num_P_in_GOP=np;
	rc->bit_GOP = 0;

	if (h->param.sp_period)  // use sp
	{
		rc->num_SP_left = np/h->param.sp_period;
		rc->num_SP_in_GOP = np/h->param.sp_period+1;
		rc->bitrate_frame = rc->bitrate/rc->fps*(np+1)/(np + 1 + (rc->ratio_sp-1)*rc->num_SP_in_GOP);
		rc->bitrate_SP = rc->bitrate_frame*rc->ratio_sp;
	}
	else
	{
		rc->bitrate_frame = rc->bitrate/rc->fps;
	}
	rc->num_GOP++;
	if(rc->num_GOP==1)
	{
		rc->QPLastGOP   = rc->init_qp_GOP;
		rc->ave_qp_frame   = rc->init_qp_GOP;
		rc->m_Qc          = rc->ave_qp_frame;
		rc->ave_qp_lastGOP    = rc->ave_qp_frame;
	}
	else
	{
		// average QP of P frames in the previous GOP
		rc->ave_qp_lastGOP=(int)(1.0 * (rc->sum_qp_GOP +51*rc->drop_count_GOP) / rc->coded_Pframe_inGOP+0.5);
		rc->ave_qp_lastGOP = min( rc->ave_qp_lastGOP, h->param.rc.i_qp_max);

		// mdou test
// 		GOPDquant=(int)((1.0*(np+1)/15.0)*1.5 + 0.5);
// 		if(GOPDquant>6)
// 			GOPDquant=6;
// 
// 		rc->ave_qp_lastGOP -= GOPDquant;// I frame

		if (rc->ave_qp_lastGOP > (rc->qp_last_Pframe - 2))
			rc->ave_qp_lastGOP--;

		// mdou test
		if (rc->drop_count_GOP>rc->coded_Pframe_inGOP*0.3)
		{
			rc->ave_qp_lastGOP = x264_clip3(rc->ave_qp_lastGOP, rc->QPLastGOP - 2, rc->QPLastGOP + 8);
			rc->ave_qp_lastGOP = (rc->ave_qp_lastGOP, rc->ave_qp_frame-GOPDquant, rc->ave_qp_frame +3);  
		}
		else if (rc->drop_count_GOP>rc->coded_Pframe_inGOP*0.1)
		{
			rc->ave_qp_lastGOP = x264_clip3(rc->ave_qp_lastGOP, rc->QPLastGOP - 4, rc->QPLastGOP + 5);
		}
// 		else
// 		{
// 			rc->ave_qp_lastGOP = x264_clip3(rc->ave_qp_lastGOP, rc->QPLastGOP - 4, rc->QPLastGOP + 3);
// 		}
		rc->ave_qp_lastGOP = x264_clip3(rc->ave_qp_lastGOP, h->param.rc.i_qp_min,  h->param.rc.i_qp_max);

// 		rc->init_qp_GOP = rc->ave_qp_lastGOP;
		rc->init_qp_GOP = rc->ave_qp_I_Frame;
		rc->Pm_Qp       = rc->ave_qp_I_Frame;
		rc->ave_qp_frame = rc->ave_qp_I_Frame;
		rc->QPLastGOP   = rc->init_qp_GOP;
		if (rc->num_SP_lastGOP)
		{
			double ave_qp_lastGOP_P = (1.0 * (rc->sum_qp_GOP_P) / rc->num_P_lastGOP);
			double ave_qp_lastGOP_SP = (1.0 * (rc->sum_qp_GOP_SP) / rc->num_SP_lastGOP);
			if (ave_qp_lastGOP_P - ave_qp_lastGOP_SP>2)
			{
				rc->ratio_sp *= 0.8;
			}
			else if (ave_qp_lastGOP_P - ave_qp_lastGOP_SP<=1)
			{
				rc->ratio_sp *= 1.2;
			}
			rc->ratio_sp = x264_clip3f(rc->ratio_sp, 1.5, 15);
		}
	}

	rc->sum_qp_GOP=0;
	rc->sum_qp_GOP_P = 0;
	rc->sum_qp_GOP_SP = 0;
	rc->coded_Pframe_inGOP=0;
	rc->drop_count_GOP = 0;
	rc->num_P_before = 0;
	rc->num_P_lastGOP = 0;
	rc->num_SP_lastGOP = 0;
}

void rc_init_GF(x264_t *h, int np)
{

	int GOPDquant;
	x264_ratecontrol_t *rc = h->rc;
	int64_t AllocatedBits;

	// init bound
	rc->lower_bound  = (int)(rc->bits_remain);
	rc->upper_bound1 = (int)(rc->bits_remain + (rc->bitrate * 2.048));
	rc->upper_bound2  = (OMEGA * rc->upper_bound1);
	

	AllocatedBits = (int64_t) floor((1 + np ) * rc->bitrate / rc->fps + 0.5);
	rc->bits_remain += AllocatedBits;
	rc->num_P_left = np;

	rc->overdue_GOP=0;
#if SHOW_QP
	{
		FILE* fp_bit = fopen("x264_bit.txt","a+");
		fprintf(fp_bit,"%d\t",rc->drop_count_GOP);
		fclose(fp_bit);
	}
#endif
	rc->num_P_in_GOP=np;
	rc->bit_GOP = 0;
	
	if (h->param.sp_period)  // use sp
	{
		rc->num_SP_left = np/h->param.sp_period;
		rc->num_SP_in_GOP = np/h->param.sp_period+1;
		rc->bitrate_frame = rc->bitrate/rc->fps*(np+1)/(np + 1 + (rc->ratio_sp-1)*rc->num_SP_in_GOP);
		rc->bitrate_SP = rc->bitrate_frame*rc->ratio_sp;
	}
	else
	{
		rc->bitrate_frame = rc->bitrate/rc->fps;
	}
	rc->num_GOP++;
	// not first GOP; first GOP is start with IDR frame
	{
		// average QP of P frames in the previous GOP
		rc->ave_qp_lastGOP=(int)(1.0 * (rc->sum_qp_GOP +51*rc->drop_count_GOP) / rc->coded_Pframe_inGOP+0.5);
		rc->ave_qp_lastGOP = min( rc->ave_qp_lastGOP, h->param.rc.i_qp_max);
		

		// mdou test
// 		GOPDquant=(int)((1.0*(np+1)/15.0)*1.5 + 0.5);
// 		if(GOPDquant>6)
// 			GOPDquant=6;
// 
// 		rc->ave_qp_lastGOP -= GOPDquant;// I frame

		if (rc->ave_qp_lastGOP > (rc->qp_last_Pframe - 2))
			rc->ave_qp_lastGOP--;

		// mdou test
		if (rc->drop_count_GOP>rc->coded_Pframe_inGOP*0.3)
		{
			rc->ave_qp_lastGOP = x264_clip3(rc->ave_qp_lastGOP, rc->QPLastGOP - 2, rc->QPLastGOP + 8);
			rc->ave_qp_lastGOP = (rc->ave_qp_lastGOP, rc->ave_qp_frame-GOPDquant, rc->ave_qp_frame +3);  
		}
		else if (rc->drop_count_GOP>rc->coded_Pframe_inGOP*0.1)
		{
			rc->ave_qp_lastGOP = x264_clip3(rc->ave_qp_lastGOP, rc->QPLastGOP - 4, rc->QPLastGOP + 5);
		}
// 		else
// 		{
// 			rc->ave_qp_lastGOP = x264_clip3(rc->ave_qp_lastGOP, rc->QPLastGOP - 4, rc->QPLastGOP + 3);
// 		}
		rc->ave_qp_lastGOP = x264_clip3(rc->ave_qp_lastGOP, h->param.rc.i_qp_min,  h->param.rc.i_qp_max);

		rc->init_qp_GOP = rc->ave_qp_lastGOP;
		rc->Pm_Qp = rc->ave_qp_lastGOP;		
		rc->ave_qp_frame = rc->ave_qp_lastGOP;
		rc->QPLastGOP   = rc->init_qp_GOP;

		if (rc->num_SP_lastGOP)
		{
			double ave_qp_lastGOP_P = (1.0 * (rc->sum_qp_GOP_P) / rc->num_P_lastGOP);
			double ave_qp_lastGOP_SP = (1.0 * (rc->sum_qp_GOP_SP) / rc->num_SP_lastGOP);
			if (ave_qp_lastGOP_P - ave_qp_lastGOP_SP>2)
			{
				rc->ratio_sp *= 0.8;
			}
			else if (ave_qp_lastGOP_P - ave_qp_lastGOP_SP<=1)
			{
				rc->ratio_sp *= 1.2;
			}
			rc->ratio_sp = x264_clip3f(rc->ratio_sp, 1.5, 15);
		}
		
		
	}

	rc->sum_qp_GOP=0;
	rc->sum_qp_GOP_P = 0;
	rc->sum_qp_GOP_SP = 0;
	rc->coded_Pframe_inGOP=0;
	rc->drop_count_GOP = 0;
	rc->num_P_before = 0;
	rc->num_P_lastGOP = 0;
	rc->num_SP_lastGOP = 0;
}

#endif

void x264_ratecontrol_reset_gop( x264_t *h )
{
#if RC_MAD
	x264_ratecontrol_t *rc = h->rc;

	if (h->param.sp_period)  // use sp
	{
		rc->bits_remain -= (rc->num_P_left - rc->num_SP_left) * rc->bitrate_frame + rc->num_SP_left * rc->bitrate_SP;
	}
	else
	{
		rc->bits_remain -= rc->num_P_left * rc->bitrate_frame;
	}
#endif
}

void x264_ratecontrol_reset_buffer(x264_t *h)
{
	x264_ratecontrol_t *rc = h->rc;
	x264_ratecontrol_t *rct = h->thread[0]->rc;

	rct->buffer_fill_final = (int64_t)(rc->buffer_size * h->sps->vui.i_time_scale);

}

void x264_ratecontrol_set_delaytime(x264_t *h, int sec)
{
    x264_ratecontrol_t *rc = h->rc;
    int vbv_buffer_size;
    
    h->param.rc.i_vbv_buffer_size = h->param.rc.i_bitrate * sec;
    vbv_buffer_size = h->param.rc.i_vbv_buffer_size * 1000;
    h->sps->vui.hrd.i_cpb_size_unscaled = vbv_buffer_size;

    h->thread[0]->rc->buffer_fill_final += (vbv_buffer_size - rc->buffer_size)*h->sps->vui.i_time_scale;
    rc->buffer_size = vbv_buffer_size;
}
