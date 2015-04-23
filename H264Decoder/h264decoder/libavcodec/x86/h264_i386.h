/*
 * H.26L/H.264/AVC/JVT/14496-10/... encoder/decoder
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
 * H.264 / AVC / MPEG4 part10 codec.
 * non-MMX i386-specific optimizations for H.264
 * @author Michael Niedermayer <michaelni@gmx.at>
 */

#ifndef AVCODEC_X86_H264_I386_H
#define AVCODEC_X86_H264_I386_H

#include <stddef.h>

#include "libavcodec/cabac.h"
#include "cabac_x86.h"

//FIXME use some macros to avoid duplicating get_cabac (cannot be done yet
//as that would make optimization work hard)
#if HAVE_7REGS && !defined(BROKEN_RELOCATIONS)
int decode_significance_x86(CABACContext *c, int max_coeff,
                                   uint8_t *significant_coeff_ctx_base,
                                   int *index, x86_reg last_off);


int decode_significance_8x8_x86(CABACContext *c,
                                       uint8_t *significant_coeff_ctx_base,
                                       int *index, uint8_t *last_coeff_ctx_base, const uint8_t *sig_off);

#endif /* HAVE_7REGS && !defined(BROKEN_RELOCATIONS) */

#endif /* AVCODEC_X86_H264_I386_H */
