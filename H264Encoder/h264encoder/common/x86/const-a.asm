;*****************************************************************************
;* const-a.asm: x86 global constants
;*****************************************************************************
;* Copyright (C) 2010-2012 x264 project
;*
;* Authors: Loren Merritt <lorenm@u.washington.edu>
;*          Jason Garrett-Glaser <darkshikari@gmail.com>
;*
;* This program is free software; you can redistribute it and/or modify
;* it under the terms of the GNU General Public License as published by
;* the Free Software Foundation; either version 2 of the License, or
;* (at your option) any later version.
;*
;* This program is distributed in the hope that it will be useful,
;* but WITHOUT ANY WARRANTY; without even the implied warranty of
;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;* GNU General Public License for more details.
;*
;* You should have received a copy of the GNU General Public License
;* along with this program; if not, write to the Free Software
;* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
;*
;* This program is also available under a commercial proprietary license.
;* For more information, contact us at licensing@x264.com.
;*****************************************************************************

%include "x86inc.asm"

SECTION_RODATA

const pb_01,       times  8 db 0,1
const pb_0,        times 16 db 0
const pb_a1,       times 16 db 0xa1
const pb_1,        times 16 db 1
const pb_3,        times 16 db 3
const hsub_mul,    times  8 db 1, -1
const pb_shuf8x8c, db 0,0,0,0,2,2,2,2,4,4,4,4,6,6,6,6

const pw_1,        times 8 dw 1
const pw_2,        times 8 dw 2
const pw_m2,       times 8 dw -2
const pw_4,        times 8 dw 4
const pw_8,        times 8 dw 8
const pw_16,       times 8 dw 16
const pw_32,       times 8 dw 32
const pw_64,       times 8 dw 64
const pw_32_0,     times 4 dw 32,
                   times 4 dw 0
const pw_8000,     times 8 dw 0x8000
const pw_3fff,     times 8 dw 0x3fff
const pw_pixel_max,times 8 dw ((1 << BIT_DEPTH)-1)
const pw_ppppmmmm, dw 1,1,1,1,-1,-1,-1,-1
const pw_ppmmppmm, dw 1,1,-1,-1,1,1,-1,-1
const pw_pmpmpmpm, dw 1,-1,1,-1,1,-1,1,-1
const pw_pmmpzzzz, dw 1,-1,-1,1,0,0,0,0

const pd_1,        times 4 dd 1
const pd_32,       times 4 dd 32
const pd_1024,     times 4 dd 1024
const pd_ffff,     times 4 dd 0xffff
const pw_00ff,     times 8 dw 0x00ff
const pw_ff00,     times 8 dw 0xff00

const sw_64,       dd 64

const cabac_range_lps, db  2,   2,   2,   2,   6,   7,   8,   9,   6,   7,   9,  10,   6,   8,   9,  11,
	 db  7,   8,  10,  11,   7,   9,  10,  12,   7,   9,  11,  12,   8,   9,  11,  13,
	 db  8,  10,  12,  14,   9,  11,  12,  14,   9,  11,  13,  15,  10,  12,  14,  16,
     db  10,  12,  15,  17,  11,  13,  15,  18,  11,  14,  16,  19,  12,  14,  17,  20,
     db 12,  15,  18,  21,  13,  16,  19,  22,  14,  17,  20,  23,  14,  18,  21,  24,
     db 15,  19,  22,  25,  16,  20,  23,  27,  17,  21,  25,  28,  18,  22,  26,  30,
     db 19,  23,  27,  31,  20,  24,  29,  33,  21,  26,  30,  35,  22,  27,  32,  37,
     db 23,  28,  33,  39,  24,  30,  35,  41,  26,  31,  37,  43,  27,  33,  39,  45,
     db 29,  35,  41,  48,  30,  37,  43,  50,  32,  39,  46,  53,  33,  41,  48,  56,
     db 35,  43,  51,  59,  37,  45,  54,  62,  39,  48,  56,  65,  41,  50,  59,  69,
     db 43,  53,  63,  72,  46,  56,  66,  76,  48,  59,  69,  80,  51,  62,  73,  85,
     db 53,  65,  77,  89,  56,  69,  81,  94,  59,  72,  86,  99,  62,  76,  90, 104,
     db 66,  80,  95, 110,  69,  85, 100, 116,  73,  89, 105, 122,  77,  94, 111, 128,
     db 81,  99, 117, 135,  85, 104, 123, 142,  90, 110, 130, 150,  95, 116, 137, 158,
     db 100, 122, 144, 166, 105, 128, 152, 175, 111, 135, 160, 185, 116, 142, 169, 195,
     db 123, 150, 178, 205, 128, 158, 187, 216, 128, 167, 197, 227, 128, 176, 208, 240

const cabac_transition, db      0,   0,   1,   1,   2,  50,  51,   3,   2,  50,  51,   3,   4,  52,  53,   5,
	db      6,  52,  53,   7,   8,  52,  53,   9,  10,  54,  55,  11,  12,  54,  55,  13,
	db     14,  54,  55,  15,  16,  56,  57,  17,  18,  56,  57,  19,  20,  56,  57,  21,
    db     22,  58,  59,  23,  24,  58,  59,  25,  26,  60,  61,  27,  28,  60,  61,  29,
    db     30,  60,  61,  31,  32,  62,  63,  33,  34,  62,  63,  35,  36,  64,  65,  37,
    db     38,  66,  67,  39,  40,  66,  67,  41,  42,  66,  67,  43,  44,  68,  69,  45,
     db     46,  68,  69,  47,  48,  70,  71,  49,  50,  72,  73,  51,  52,  72,  73,  53,
     db     54,  74,  75,  55,  56,  74,  75,  57,  58,  76,  77,  59,  60,  78,  79,  61,
     db     62,  78,  79,  63,  64,  80,  81,  65,  66,  82,  83,  67,  68,  82,  83,  69,
     db     70,  84,  85,  71,  72,  84,  85,  73,  74,  88,  89,  75,  76,  88,  89,  77,
     db     78,  90,  91,  79,  80,  90,  91,  81,  82,  94,  95,  83,  84,  94,  95,  85,
     db     86,  96,  97,  87,  88,  96,  97,  89,  90, 100, 101,  91,  92, 100, 101,  93,
     db     94, 102, 103,  95,  96, 104, 105,  97,  98, 104, 105,  99, 100, 108, 109, 101,
    db     102, 108, 109, 103, 104, 110, 111, 105, 106, 112, 113, 107, 108, 114, 115, 109,
    db     110, 116, 117, 111, 112, 118, 119, 113, 114, 118, 119, 115, 116, 122, 123, 117,
    db     118, 122, 123, 119, 120, 124, 125, 121, 122, 126, 127, 123, 124, 127, 126, 125


const cabac_renorm_shift, db 6,5,4,4,3,3,3,3,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

const decimate_table4, db 3,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0

const decimate_table8, db 3,3,3,3,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

