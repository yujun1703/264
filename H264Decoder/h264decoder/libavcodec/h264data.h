/*
 * H26L/H264/AVC/JVT/14496-10/... encoder/decoder
 * Copyright (c) 2003 Michael Niedermayer <michaelni@gmx.at>
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

/**
 * @file
 * @brief
 *     H264 / AVC / MPEG4 part10 codec data table
 * @author Michael Niedermayer <michaelni@gmx.at>
 */

#ifndef AVCODEC_H264DATA_H
#define AVCODEC_H264DATA_H

//#include <stdint.h>
#include "commontypes.h"
#include "libavutil/rational.h"
#include "mpegvideo.h"
#include "h264.h"

extern const uint8_t zigzag_scan[16];
extern const uint8_t field_scan[16];
extern const uint8_t chroma_dc_scan[4];
extern const uint8_t chroma422_dc_scan[8];

// zigzag_scan8x8_cavlc[i] = zigzag_scan8x8[(i/4) + 16*(i%4)]
extern const uint8_t zigzag_scan8x8_cavlc[64];

extern const uint8_t field_scan8x8[64];
extern const uint8_t field_scan8x8_cavlc[64];

typedef struct IMbInfo{
    uint16_t type;
    uint8_t pred_mode;
    uint8_t cbp;
} IMbInfo;

extern const IMbInfo i_mb_type_info[26];

typedef struct PMbInfo{
    uint16_t type;
    uint8_t partition_count;
} PMbInfo;

extern const PMbInfo p_mb_type_info[5];
extern const PMbInfo p_sub_mb_type_info[4];
extern const PMbInfo b_mb_type_info[23];
extern const PMbInfo b_sub_mb_type_info[13];





#endif /* AVCODEC_H264DATA_H */
