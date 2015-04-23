//
//  Created by landyji on 20140605.
//  Copyright (c) 2013年 com.tencent.avteam. All rights reserved.
//

.macro function name
.global _\name
.align 2
_\name:
.endm

.text
function ff_put_h264_qpel16_mc00_neon
mov.w	r3, #0x10
1:
vld1.8	{d0, d1}, [r1], r2
vld1.8	{d2, d3}, [r1], r2
vld1.8	{d4, d5}, [r1], r2
pld	[r1, r2, lsl #2]
vld1.8	{d6, d7}, [r1], r2
pld	[r1]
pld	[r1, r2]
pld	[r1, r2, lsl #1]
subs	r3, #0x4
vst1.64	{d0, d1}, [r0:128], r2
vst1.64	{d2, d3}, [r0:128], r2
vst1.64	{d4, d5}, [r0:128], r2
vst1.64	{d6, d7}, [r0:128], r2
bne	1b
bx	lr


function ff_put_h264_qpel8_mc00_neon  
mov.w	r3, #0x8                        
1:                                    
vld1.8	{d0}, [r1], r2                
vld1.8	{d1}, [r1], r2                
vld1.8	{d2}, [r1], r2                
pld	[r1, r2, lsl #2]                  
vld1.8	{d3}, [r1], r2                
pld	[r1]                              
pld	[r1, r2]                          
pld	[r1, r2, lsl #1]                  
subs	r3, #0x4                        
vst1.8	{d0}, [r0:64], r2             
vst1.8	{d1}, [r0:64], r2             
vst1.8	{d2}, [r0:64], r2             
vst1.8	{d3}, [r0:64], r2             
bne	1b                                
bx	lr



put_h264_qpel16_h_lowpass_neon_packed:
mov	r4, lr
mov.w	r12, #0x10
mov.w	r3, #0x8
bl	put_h264_qpel8_h_lowpass_neon
sub.w	r1, r1, r2, lsl #4
add.w	r1, r1, #0x8
mov.w	r12, #0x10
mov	lr, r4
b	put_h264_qpel8_h_lowpass_neon
nop
put_h264_qpel16_h_lowpass_neon:
push	{lr}
mov.w	r12, #0x10
bl	put_h264_qpel8_h_lowpass_neon
sub.w	r0, r0, r3, lsl #4
sub.w	r1, r1, r2, lsl #4
add.w	r0, r0, #0x8
add.w	r1, r1, #0x8
mov.w	r12, #0x10
ldr	lr, [sp], #4
nop
put_h264_qpel8_h_lowpass_neon:
vld1.8	{d0, d1}, [r1], r2
vld1.8	{d16, d17}, [r1], r2
subs.w	r12, r12, #0x2
vext.16	d2, d0, d1, #0x1
vext.8	d3, d0, d1, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d0, d1, #0x1
vext.32	d5, d0, d1, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d0, d1, #0x5
vaddl.u8	q0, d0, d30
vext.16	d18, d16, d17, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d16, d17, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d16, d17, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d16, d17, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d16, d17, #0x5
vaddl.u8	q8, d16, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d0, q0, #0x5
vqrshrun.s16	d16, q8, #0x5
vst1.8	{d0}, [r0:64], r3
vst1.8	{d16}, [r0:64], r3
bne	put_h264_qpel8_h_lowpass_neon
bx	lr
avg_h264_qpel16_h_lowpass_neon:
push	{lr}
mov.w	r12, #0x10
bl	avg_h264_qpel8_h_lowpass_neon
sub.w	r0, r0, r3, lsl #4
sub.w	r1, r1, r2, lsl #4
add.w	r0, r0, #0x8
add.w	r1, r1, #0x8
mov.w	r12, #0x10
ldr	lr, [sp], #4
nop
avg_h264_qpel8_h_lowpass_neon:
vld1.8	{d0, d1}, [r1], r2
vld1.8	{d16, d17}, [r1], r2
subs.w	r12, r12, #0x2
vext.16	d2, d0, d1, #0x1
vext.8	d3, d0, d1, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d0, d1, #0x1
vext.32	d5, d0, d1, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d0, d1, #0x5
vaddl.u8	q0, d0, d30
vext.16	d18, d16, d17, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d16, d17, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d16, d17, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d16, d17, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d16, d17, #0x5
vaddl.u8	q8, d16, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d0, q0, #0x5
vqrshrun.s16	d16, q8, #0x5
vld1.8	{d2}, [r0:64], r3
vrhadd.u8	d0, d0, d2
vld1.8	{d3}, [r0:64]
vrhadd.u8	d16, d16, d3
sub.w	r0, r0, r3
vst1.8	{d0}, [r0:64], r3
vst1.8	{d16}, [r0:64], r3
bne	avg_h264_qpel8_h_lowpass_neon
bx	lr
put_h264_qpel16_h_lowpass_l2_neon:
push	{lr}
mov.w	r12, #0x10
bl	put_h264_qpel8_h_lowpass_l2_neon
sub.w	r0, r0, r2, lsl #4
sub.w	r1, r1, r2, lsl #4
sub.w	r3, r3, r2, lsl #4
add.w	r0, r0, #0x8
add.w	r1, r1, #0x8
add.w	r3, r3, #0x8
mov.w	r12, #0x10
ldr	lr, [sp], #4
nop
put_h264_qpel8_h_lowpass_l2_neon:
vld1.8	{d0, d1}, [r1], r2
vld1.8	{d16, d17}, [r1], r2
vld1.8	{d28}, [r3], r2
vld1.8	{d29}, [r3], r2
subs.w	r12, r12, #0x2
vext.16	d2, d0, d1, #0x1
vext.8	d3, d0, d1, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d0, d1, #0x1
vext.32	d5, d0, d1, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d0, d1, #0x5
vaddl.u8	q0, d0, d30
vext.16	d18, d16, d17, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d16, d17, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d16, d17, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d16, d17, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d16, d17, #0x5
vaddl.u8	q8, d16, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d0, q0, #0x5
vqrshrun.s16	d1, q8, #0x5
vrhadd.u8	q0, q0, q14
vst1.8	{d0}, [r0:64], r2
vst1.8	{d1}, [r0:64], r2
bne	put_h264_qpel8_h_lowpass_l2_neon
bx	lr
avg_h264_qpel16_h_lowpass_l2_neon:
push	{lr}
mov.w	r12, #0x10
bl	avg_h264_qpel8_h_lowpass_l2_neon
sub.w	r0, r0, r2, lsl #4
sub.w	r1, r1, r2, lsl #4
sub.w	r3, r3, r2, lsl #4
add.w	r0, r0, #0x8
add.w	r1, r1, #0x8
add.w	r3, r3, #0x8
mov.w	r12, #0x10
ldr	lr, [sp], #4
nop
avg_h264_qpel8_h_lowpass_l2_neon:
vld1.8	{d0, d1}, [r1], r2
vld1.8	{d16, d17}, [r1], r2
vld1.8	{d28}, [r3], r2
vld1.8	{d29}, [r3], r2
subs.w	r12, r12, #0x2
vext.16	d2, d0, d1, #0x1
vext.8	d3, d0, d1, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d0, d1, #0x1
vext.32	d5, d0, d1, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d0, d1, #0x5
vaddl.u8	q0, d0, d30
vext.16	d18, d16, d17, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d16, d17, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d16, d17, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d16, d17, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d16, d17, #0x5
vaddl.u8	q8, d16, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d0, q0, #0x5
vqrshrun.s16	d1, q8, #0x5
vrhadd.u8	q0, q0, q14
vld1.8	{d2}, [r0:64], r2
vrhadd.u8	d0, d0, d2
vld1.8	{d3}, [r0:64]
vrhadd.u8	d1, d1, d3
sub.w	r0, r0, r2
vst1.8	{d0}, [r0:64], r2
vst1.8	{d1}, [r0:64], r2
bne	avg_h264_qpel8_h_lowpass_l2_neon
bx	lr
put_h264_qpel16_v_lowpass_neon_packed:
mov	r4, lr
mov.w	r2, #0x8
bl	put_h264_qpel8_v_lowpass_neon
sub.w	r1, r1, r3, lsl #2
bl	put_h264_qpel8_v_lowpass_neon
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
bl	put_h264_qpel8_v_lowpass_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r4
b	put_h264_qpel8_v_lowpass_neon
nop
put_h264_qpel16_v_lowpass_neon:
mov	r4, lr
bl	put_h264_qpel8_v_lowpass_neon
sub.w	r1, r1, r3, lsl #2
bl	put_h264_qpel8_v_lowpass_neon
sub.w	r0, r0, r2, lsl #4
add.w	r0, r0, #0x8
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
bl	put_h264_qpel8_v_lowpass_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r4
put_h264_qpel8_v_lowpass_neon:
vld1.8	{d8}, [r1], r3
vld1.8	{d10}, [r1], r3
vld1.8	{d12}, [r1], r3
vld1.8	{d14}, [r1], r3
vld1.8	{d22}, [r1], r3
vld1.8	{d24}, [r1], r3
vld1.8	{d26}, [r1], r3
vld1.8	{d28}, [r1], r3
vld1.8	{d9}, [r1], r3
vld1.8	{d11}, [r1], r3
vld1.8	{d13}, [r1], r3
vld1.8	{d15}, [r1], r3
vld1.8	{d23}, [r1]
vtrn.32	q4, q11
vtrn.32	q5, q12
vtrn.32	q6, q13
vtrn.32	q7, q14
vtrn.16	q4, q6
vtrn.16	q5, q7
vtrn.16	q11, q13
vtrn.16	q12, q14
vtrn.8	q4, q5
vtrn.8	q6, q7
vtrn.8	q11, q12
vtrn.8	q13, q14
vext.16	d2, d8, d9, #0x1
vext.8	d3, d8, d9, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d8, d9, #0x1
vext.32	d5, d8, d9, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d8, d9, #0x5
vaddl.u8	q0, d8, d30
vext.16	d18, d10, d11, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d10, d11, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d10, d11, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d10, d11, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d10, d11, #0x5
vaddl.u8	q8, d10, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d8, q0, #0x5
vqrshrun.s16	d10, q8, #0x5
vext.16	d2, d12, d13, #0x1
vext.8	d3, d12, d13, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d12, d13, #0x1
vext.32	d5, d12, d13, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d12, d13, #0x5
vaddl.u8	q0, d12, d30
vext.16	d18, d14, d15, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d14, d15, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d14, d15, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d14, d15, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d14, d15, #0x5
vaddl.u8	q8, d14, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d12, q0, #0x5
vqrshrun.s16	d14, q8, #0x5
vext.16	d2, d22, d23, #0x1
vext.8	d3, d22, d23, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d22, d23, #0x1
vext.32	d5, d22, d23, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d22, d23, #0x5
vaddl.u8	q0, d22, d30
vext.16	d18, d24, d25, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d24, d25, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d24, d25, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d24, d25, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d24, d25, #0x5
vaddl.u8	q8, d24, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d22, q0, #0x5
vqrshrun.s16	d24, q8, #0x5
vext.16	d2, d26, d27, #0x1
vext.8	d3, d26, d27, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d26, d27, #0x1
vext.32	d5, d26, d27, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d26, d27, #0x5
vaddl.u8	q0, d26, d30
vext.16	d18, d28, d29, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d28, d29, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d28, d29, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d28, d29, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d28, d29, #0x5
vaddl.u8	q8, d28, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d26, q0, #0x5
vqrshrun.s16	d28, q8, #0x5
vtrn.32	d8, d22
vtrn.32	d10, d24
vtrn.32	d12, d26
vtrn.32	d14, d28
vtrn.16	d8, d12
vtrn.16	d10, d14
vtrn.16	d22, d26
vtrn.16	d24, d28
vtrn.8	d8, d10
vtrn.8	d12, d14
vtrn.8	d22, d24
vtrn.8	d26, d28
vst1.8	{d8}, [r0:64], r2
vst1.8	{d10}, [r0:64], r2
vst1.8	{d12}, [r0:64], r2
vst1.8	{d14}, [r0:64], r2
vst1.8	{d22}, [r0:64], r2
vst1.8	{d24}, [r0:64], r2
vst1.8	{d26}, [r0:64], r2
vst1.8	{d28}, [r0:64], r2
bx	lr
nop
avg_h264_qpel16_v_lowpass_neon:
mov	r4, lr
bl	avg_h264_qpel8_v_lowpass_neon
sub.w	r1, r1, r3, lsl #2
bl	avg_h264_qpel8_v_lowpass_neon
sub.w	r0, r0, r2, lsl #4
add.w	r0, r0, #0x8
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
bl	avg_h264_qpel8_v_lowpass_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r4
avg_h264_qpel8_v_lowpass_neon:
vld1.8	{d8}, [r1], r3
vld1.8	{d10}, [r1], r3
vld1.8	{d12}, [r1], r3
vld1.8	{d14}, [r1], r3
vld1.8	{d22}, [r1], r3
vld1.8	{d24}, [r1], r3
vld1.8	{d26}, [r1], r3
vld1.8	{d28}, [r1], r3
vld1.8	{d9}, [r1], r3
vld1.8	{d11}, [r1], r3
vld1.8	{d13}, [r1], r3
vld1.8	{d15}, [r1], r3
vld1.8	{d23}, [r1]
vtrn.32	q4, q11
vtrn.32	q5, q12
vtrn.32	q6, q13
vtrn.32	q7, q14
vtrn.16	q4, q6
vtrn.16	q5, q7
vtrn.16	q11, q13
vtrn.16	q12, q14
vtrn.8	q4, q5
vtrn.8	q6, q7
vtrn.8	q11, q12
vtrn.8	q13, q14
vext.16	d2, d8, d9, #0x1
vext.8	d3, d8, d9, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d8, d9, #0x1
vext.32	d5, d8, d9, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d8, d9, #0x5
vaddl.u8	q0, d8, d30
vext.16	d18, d10, d11, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d10, d11, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d10, d11, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d10, d11, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d10, d11, #0x5
vaddl.u8	q8, d10, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d8, q0, #0x5
vqrshrun.s16	d10, q8, #0x5
vext.16	d2, d12, d13, #0x1
vext.8	d3, d12, d13, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d12, d13, #0x1
vext.32	d5, d12, d13, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d12, d13, #0x5
vaddl.u8	q0, d12, d30
vext.16	d18, d14, d15, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d14, d15, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d14, d15, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d14, d15, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d14, d15, #0x5
vaddl.u8	q8, d14, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d12, q0, #0x5
vqrshrun.s16	d14, q8, #0x5
vext.16	d2, d22, d23, #0x1
vext.8	d3, d22, d23, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d22, d23, #0x1
vext.32	d5, d22, d23, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d22, d23, #0x5
vaddl.u8	q0, d22, d30
vext.16	d18, d24, d25, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d24, d25, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d24, d25, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d24, d25, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d24, d25, #0x5
vaddl.u8	q8, d24, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d22, q0, #0x5
vqrshrun.s16	d24, q8, #0x5
vext.16	d2, d26, d27, #0x1
vext.8	d3, d26, d27, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d26, d27, #0x1
vext.32	d5, d26, d27, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d26, d27, #0x5
vaddl.u8	q0, d26, d30
vext.16	d18, d28, d29, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d28, d29, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d28, d29, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d28, d29, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d28, d29, #0x5
vaddl.u8	q8, d28, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d26, q0, #0x5
vqrshrun.s16	d28, q8, #0x5
vtrn.32	d8, d22
vtrn.32	d10, d24
vtrn.32	d12, d26
vtrn.32	d14, d28
vtrn.16	d8, d12
vtrn.16	d10, d14
vtrn.16	d22, d26
vtrn.16	d24, d28
vtrn.8	d8, d10
vtrn.8	d12, d14
vtrn.8	d22, d24
vtrn.8	d26, d28
vld1.8	{d9}, [r0:64], r2
vrhadd.u8	d8, d8, d9
vld1.8	{d11}, [r0:64], r2
vrhadd.u8	d10, d10, d11
vld1.8	{d13}, [r0:64], r2
vrhadd.u8	d12, d12, d13
vld1.8	{d15}, [r0:64], r2
vrhadd.u8	d14, d14, d15
vld1.8	{d23}, [r0:64], r2
vrhadd.u8	d22, d22, d23
vld1.8	{d25}, [r0:64], r2
vrhadd.u8	d24, d24, d25
vld1.8	{d27}, [r0:64], r2
vrhadd.u8	d26, d26, d27
vld1.8	{d29}, [r0:64], r2
vrhadd.u8	d28, d28, d29
sub.w	r0, r0, r2, lsl #3
vst1.8	{d8}, [r0:64], r2
vst1.8	{d10}, [r0:64], r2
vst1.8	{d12}, [r0:64], r2
vst1.8	{d14}, [r0:64], r2
vst1.8	{d22}, [r0:64], r2
vst1.8	{d24}, [r0:64], r2
vst1.8	{d26}, [r0:64], r2
vst1.8	{d28}, [r0:64], r2
bx	lr
nop
put_h264_qpel16_v_lowpass_l2_neon:
mov	r4, lr
bl	put_h264_qpel8_v_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #2
bl	put_h264_qpel8_v_lowpass_l2_neon
sub.w	r0, r0, r3, lsl #4
sub.w	r12, r12, r2, lsl #4
add.w	r0, r0, #0x8
add.w	r12, r12, #0x8
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
bl	put_h264_qpel8_v_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r4
put_h264_qpel8_v_lowpass_l2_neon:
vld1.8	{d8}, [r1], r3
vld1.8	{d10}, [r1], r3
vld1.8	{d12}, [r1], r3
vld1.8	{d14}, [r1], r3
vld1.8	{d22}, [r1], r3
vld1.8	{d24}, [r1], r3
vld1.8	{d26}, [r1], r3
vld1.8	{d28}, [r1], r3
vld1.8	{d9}, [r1], r3
vld1.8	{d11}, [r1], r3
vld1.8	{d13}, [r1], r3
vld1.8	{d15}, [r1], r3
vld1.8	{d23}, [r1]
vtrn.32	q4, q11
vtrn.32	q5, q12
vtrn.32	q6, q13
vtrn.32	q7, q14
vtrn.16	q4, q6
vtrn.16	q5, q7
vtrn.16	q11, q13
vtrn.16	q12, q14
vtrn.8	q4, q5
vtrn.8	q6, q7
vtrn.8	q11, q12
vtrn.8	q13, q14
vext.16	d2, d8, d9, #0x1
vext.8	d3, d8, d9, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d8, d9, #0x1
vext.32	d5, d8, d9, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d8, d9, #0x5
vaddl.u8	q0, d8, d30
vext.16	d18, d10, d11, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d10, d11, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d10, d11, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d10, d11, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d10, d11, #0x5
vaddl.u8	q8, d10, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d8, q0, #0x5
vqrshrun.s16	d9, q8, #0x5
vext.16	d2, d12, d13, #0x1
vext.8	d3, d12, d13, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d12, d13, #0x1
vext.32	d5, d12, d13, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d12, d13, #0x5
vaddl.u8	q0, d12, d30
vext.16	d18, d14, d15, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d14, d15, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d14, d15, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d14, d15, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d14, d15, #0x5
vaddl.u8	q8, d14, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d12, q0, #0x5
vqrshrun.s16	d13, q8, #0x5
vext.16	d2, d22, d23, #0x1
vext.8	d3, d22, d23, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d22, d23, #0x1
vext.32	d5, d22, d23, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d22, d23, #0x5
vaddl.u8	q0, d22, d30
vext.16	d18, d24, d25, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d24, d25, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d24, d25, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d24, d25, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d24, d25, #0x5
vaddl.u8	q8, d24, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d22, q0, #0x5
vqrshrun.s16	d23, q8, #0x5
vext.16	d2, d26, d27, #0x1
vext.8	d3, d26, d27, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d26, d27, #0x1
vext.32	d5, d26, d27, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d26, d27, #0x5
vaddl.u8	q0, d26, d30
vext.16	d18, d28, d29, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d28, d29, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d28, d29, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d28, d29, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d28, d29, #0x5
vaddl.u8	q8, d28, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d26, q0, #0x5
vqrshrun.s16	d27, q8, #0x5
vtrn.32	d8, d22
vtrn.32	d9, d23
vtrn.32	d12, d26
vtrn.32	d13, d27
vtrn.16	d8, d12
vtrn.16	d9, d13
vtrn.16	d22, d26
vtrn.16	d23, d27
vtrn.8	d8, d9
vtrn.8	d12, d13
vtrn.8	d22, d23
vtrn.8	d26, d27
vld1.8	{d0}, [r12], r2
vld1.8	{d1}, [r12], r2
vld1.8	{d2}, [r12], r2
vld1.8	{d3}, [r12], r2
vld1.8	{d4}, [r12], r2
vrhadd.u8	q0, q0, q4
vld1.8	{d5}, [r12], r2
vrhadd.u8	q1, q1, q6
vld1.8	{d10}, [r12], r2
vrhadd.u8	q2, q2, q11
vld1.8	{d11}, [r12], r2
vrhadd.u8	q5, q5, q13
vst1.8	{d0}, [r0:64], r3
vst1.8	{d1}, [r0:64], r3
vst1.8	{d2}, [r0:64], r3
vst1.8	{d3}, [r0:64], r3
vst1.8	{d4}, [r0:64], r3
vst1.8	{d5}, [r0:64], r3
vst1.8	{d10}, [r0:64], r3
vst1.8	{d11}, [r0:64], r3
bx	lr
nop
avg_h264_qpel16_v_lowpass_l2_neon:
mov	r4, lr
bl	avg_h264_qpel8_v_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #2
bl	avg_h264_qpel8_v_lowpass_l2_neon
sub.w	r0, r0, r3, lsl #4
sub.w	r12, r12, r2, lsl #4
add.w	r0, r0, #0x8
add.w	r12, r12, #0x8
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
bl	avg_h264_qpel8_v_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r4
avg_h264_qpel8_v_lowpass_l2_neon:
vld1.8	{d8}, [r1], r3
vld1.8	{d10}, [r1], r3
vld1.8	{d12}, [r1], r3
vld1.8	{d14}, [r1], r3
vld1.8	{d22}, [r1], r3
vld1.8	{d24}, [r1], r3
vld1.8	{d26}, [r1], r3
vld1.8	{d28}, [r1], r3
vld1.8	{d9}, [r1], r3
vld1.8	{d11}, [r1], r3
vld1.8	{d13}, [r1], r3
vld1.8	{d15}, [r1], r3
vld1.8	{d23}, [r1]
vtrn.32	q4, q11
vtrn.32	q5, q12
vtrn.32	q6, q13
vtrn.32	q7, q14
vtrn.16	q4, q6
vtrn.16	q5, q7
vtrn.16	q11, q13
vtrn.16	q12, q14
vtrn.8	q4, q5
vtrn.8	q6, q7
vtrn.8	q11, q12
vtrn.8	q13, q14
vext.16	d2, d8, d9, #0x1
vext.8	d3, d8, d9, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d8, d9, #0x1
vext.32	d5, d8, d9, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d8, d9, #0x5
vaddl.u8	q0, d8, d30
vext.16	d18, d10, d11, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d10, d11, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d10, d11, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d10, d11, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d10, d11, #0x5
vaddl.u8	q8, d10, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d8, q0, #0x5
vqrshrun.s16	d9, q8, #0x5
vext.16	d2, d12, d13, #0x1
vext.8	d3, d12, d13, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d12, d13, #0x1
vext.32	d5, d12, d13, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d12, d13, #0x5
vaddl.u8	q0, d12, d30
vext.16	d18, d14, d15, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d14, d15, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d14, d15, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d14, d15, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d14, d15, #0x5
vaddl.u8	q8, d14, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d12, q0, #0x5
vqrshrun.s16	d13, q8, #0x5
vext.16	d2, d22, d23, #0x1
vext.8	d3, d22, d23, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d22, d23, #0x1
vext.32	d5, d22, d23, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d22, d23, #0x5
vaddl.u8	q0, d22, d30
vext.16	d18, d24, d25, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d24, d25, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d24, d25, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d24, d25, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d24, d25, #0x5
vaddl.u8	q8, d24, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d22, q0, #0x5
vqrshrun.s16	d23, q8, #0x5
vext.16	d2, d26, d27, #0x1
vext.8	d3, d26, d27, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d26, d27, #0x1
vext.32	d5, d26, d27, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d26, d27, #0x5
vaddl.u8	q0, d26, d30
vext.16	d18, d28, d29, #0x1
vmla.i16	q0, q1, d6[1]
vext.8	d19, d28, d29, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d28, d29, #0x1
vmls.i16	q0, q2, d6[0]
vext.32	d21, d28, d29, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d28, d29, #0x5
vaddl.u8	q8, d28, d31
vmla.i16	q8, q9, d6[1]
vmls.i16	q8, q10, d6[0]
vqrshrun.s16	d26, q0, #0x5
vqrshrun.s16	d27, q8, #0x5
vtrn.32	d8, d22
vtrn.32	d9, d23
vtrn.32	d12, d26
vtrn.32	d13, d27
vtrn.16	d8, d12
vtrn.16	d9, d13
vtrn.16	d22, d26
vtrn.16	d23, d27
vtrn.8	d8, d9
vtrn.8	d12, d13
vtrn.8	d22, d23
vtrn.8	d26, d27
vld1.8	{d0}, [r12], r2
vld1.8	{d1}, [r12], r2
vld1.8	{d2}, [r12], r2
vld1.8	{d3}, [r12], r2
vld1.8	{d4}, [r12], r2
vrhadd.u8	q0, q0, q4
vld1.8	{d5}, [r12], r2
vrhadd.u8	q1, q1, q6
vld1.8	{d10}, [r12], r2
vrhadd.u8	q2, q2, q11
vld1.8	{d11}, [r12], r2
vrhadd.u8	q5, q5, q13
vld1.8	{d16}, [r0:64], r3
vrhadd.u8	d0, d0, d16
vld1.8	{d17}, [r0:64], r3
vrhadd.u8	d1, d1, d17
vld1.8	{d16}, [r0:64], r3
vrhadd.u8	d2, d2, d16
vld1.8	{d17}, [r0:64], r3
vrhadd.u8	d3, d3, d17
vld1.8	{d16}, [r0:64], r3
vrhadd.u8	d4, d4, d16
vld1.8	{d17}, [r0:64], r3
vrhadd.u8	d5, d5, d17
vld1.8	{d16}, [r0:64], r3
vrhadd.u8	d10, d10, d16
vld1.8	{d17}, [r0:64], r3
vrhadd.u8	d11, d11, d17
sub.w	r0, r0, r3, lsl #3
vst1.8	{d0}, [r0:64], r3
vst1.8	{d1}, [r0:64], r3
vst1.8	{d2}, [r0:64], r3
vst1.8	{d3}, [r0:64], r3
vst1.8	{d4}, [r0:64], r3
vst1.8	{d5}, [r0:64], r3
vst1.8	{d10}, [r0:64], r3
vst1.8	{d11}, [r0:64], r3
bx	lr
nop
put_h264_qpel8_hv_lowpass_neon_top:
movw	r12, #0x5
movt	r12, #0x14
vmov.32	d6[0], r12
mov.w	r12, #0xc
1:
vld1.8	{d0, d1}, [r1], r3
vld1.8	{d16, d17}, [r1], r3
subs.w	r12, r12, #0x2
vext.16	d2, d0, d1, #0x1
vext.8	d3, d0, d1, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d0, d1, #0x1
vext.32	d5, d0, d1, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d0, d1, #0x5
vaddl.u8	q11, d0, d30
vext.16	d18, d16, d17, #0x1
vmla.i16	q11, q1, d6[1]
vext.8	d19, d16, d17, #0x3
vaddl.u8	q9, d18, d19
vext.8	d20, d16, d17, #0x1
vmls.i16	q11, q2, d6[0]
vext.32	d21, d16, d17, #0x1
vaddl.u8	q10, d20, d21
vext.8	d31, d16, d17, #0x5
vaddl.u8	q12, d16, d31
vmla.i16	q12, q9, d6[1]
vmls.i16	q12, q10, d6[0]
vst1.8	{d22, d23, d24, d25}, [r4:128]!
bne	1b
vld1.8	{d0, d1}, [r1]
vext.16	d2, d0, d1, #0x1
vext.8	d3, d0, d1, #0x3
vaddl.u8	q1, d2, d3
vext.8	d4, d0, d1, #0x1
vext.32	d5, d0, d1, #0x1
vaddl.u8	q2, d4, d5
vext.8	d30, d0, d1, #0x5
vaddl.u8	q12, d0, d30
vmla.i16	q12, q1, d6[1]
vmls.i16	q12, q2, d6[0]
mvn	r12, #0xf
add	r4, r12
vld1.8	{d30, d31}, [r4:128], r12
vld1.8	{d20, d21}, [r4:128], r12
vld1.8	{d18, d19}, [r4:128], r12
vld1.8	{d16, d17}, [r4:128], r12
vld1.8	{d14, d15}, [r4:128], r12
vld1.8	{d12, d13}, [r4:128], r12
vld1.8	{d10, d11}, [r4:128], r12
vld1.8	{d8, d9}, [r4:128], r12
vld1.8	{d6, d7}, [r4:128], r12
vld1.8	{d4, d5}, [r4:128], r12
vld1.8	{d2, d3}, [r4:128], r12
vld1.8	{d0, d1}, [r4:128]
vswp	d1, d8
vswp	d3, d10
vswp	d5, d12
vswp	d7, d14
vtrn.32	q0, q2
vtrn.32	q1, q3
vtrn.32	q4, q6
vtrn.32	q5, q7
vtrn.16	q0, q1
vtrn.16	q2, q3
vtrn.16	q4, q5
vtrn.16	q6, q7
vswp	d17, d24
vswp	d19, d26
vswp	d21, d28
vswp	d31, d22
vtrn.32	q8, q10
vtrn.32	q9, q15
vtrn.32	q12, q14
vtrn.32	q13, q11
vtrn.16	q8, q9
vtrn.16	q10, q15
vtrn.16	q12, q13
vtrn.16	q14, q11
vst1.8	{d30, d31}, [r4:128]!
vst1.8	{d6, d7}, [r4:128]!
vst1.8	{d20, d21}, [r4:128]!
vst1.8	{d4, d5}, [r4:128]!
vst1.8	{d18, d19}, [r4:128]!
vst1.8	{d2, d3}, [r4:128]!
vst1.8	{d16, d17}, [r4:128]!
vst1.8	{d0, d1}, [r4:128]
vext.32	q1, q4, q12, #0x1
vext.16	q0, q4, q12, #0x3
vaddl.s16	q9, d2, d0
vext.16	q2, q4, q12, #0x1
vaddl.s16	q1, d3, d1
vext.64	q3, q4, q12, #0x1
vaddl.s16	q10, d4, d6
vext.16	q12, q4, q12, #0x5
vaddl.s16	q2, d5, d7
vaddl.s16	q0, d9, d25
vaddl.s16	q8, d8, d24
vshl.i32	q3, q9, #0x4
vshl.i32	q9, q9, #0x2
vshl.i32	q15, q10, #0x2
vadd.i32	q9, q9, q3
vadd.i32	q10, q10, q15
vshl.i32	q3, q1, #0x4
vshl.i32	q1, q1, #0x2
vshl.i32	q15, q2, #0x2
vadd.i32	q1, q1, q3
vadd.i32	q2, q2, q15
vadd.i32	q9, q9, q8
vsub.i32	q9, q9, q10
vadd.i32	q1, q1, q0
vsub.i32	q1, q1, q2
vrshrn.i32	d18, q9, #0xa
vrshrn.i32	d19, q1, #0xa
vqmovun.s16	d8, q9
vext.32	q1, q5, q13, #0x1
vext.16	q0, q5, q13, #0x3
vaddl.s16	q9, d2, d0
vext.16	q2, q5, q13, #0x1
vaddl.s16	q1, d3, d1
vext.64	q3, q5, q13, #0x1
vaddl.s16	q10, d4, d6
vext.16	q13, q5, q13, #0x5
vaddl.s16	q2, d5, d7
vaddl.s16	q0, d11, d27
vaddl.s16	q8, d10, d26
vshl.i32	q3, q9, #0x4
vshl.i32	q9, q9, #0x2
vshl.i32	q15, q10, #0x2
vadd.i32	q9, q9, q3
vadd.i32	q10, q10, q15
vshl.i32	q3, q1, #0x4
vshl.i32	q1, q1, #0x2
vshl.i32	q15, q2, #0x2
vadd.i32	q1, q1, q3
vadd.i32	q2, q2, q15
vadd.i32	q9, q9, q8
vsub.i32	q9, q9, q10
vadd.i32	q1, q1, q0
vsub.i32	q1, q1, q2
vrshrn.i32	d18, q9, #0xa
vrshrn.i32	d19, q1, #0xa
vqmovun.s16	d9, q9
vext.32	q1, q6, q14, #0x1
vext.16	q0, q6, q14, #0x3
vaddl.s16	q9, d2, d0
vext.16	q2, q6, q14, #0x1
vaddl.s16	q1, d3, d1
vext.64	q3, q6, q14, #0x1
vaddl.s16	q10, d4, d6
vext.16	q14, q6, q14, #0x5
vaddl.s16	q2, d5, d7
vaddl.s16	q0, d13, d29
vaddl.s16	q8, d12, d28
vshl.i32	q3, q9, #0x4
vshl.i32	q9, q9, #0x2
vshl.i32	q15, q10, #0x2
vadd.i32	q9, q9, q3
vadd.i32	q10, q10, q15
vshl.i32	q3, q1, #0x4
vshl.i32	q1, q1, #0x2
vshl.i32	q15, q2, #0x2
vadd.i32	q1, q1, q3
vadd.i32	q2, q2, q15
vadd.i32	q9, q9, q8
vsub.i32	q9, q9, q10
vadd.i32	q1, q1, q0
vsub.i32	q1, q1, q2
vrshrn.i32	d18, q9, #0xa
vrshrn.i32	d19, q1, #0xa
vqmovun.s16	d10, q9
vext.32	q1, q7, q11, #0x1
vext.16	q0, q7, q11, #0x3
vaddl.s16	q9, d2, d0
vext.16	q2, q7, q11, #0x1
vaddl.s16	q1, d3, d1
vext.64	q3, q7, q11, #0x1
vaddl.s16	q10, d4, d6
vext.16	q11, q7, q11, #0x5
vaddl.s16	q2, d5, d7
vaddl.s16	q0, d15, d23
vaddl.s16	q8, d14, d22
vshl.i32	q3, q9, #0x4
vshl.i32	q9, q9, #0x2
vshl.i32	q15, q10, #0x2
vadd.i32	q9, q9, q3
vadd.i32	q10, q10, q15
vshl.i32	q3, q1, #0x4
vshl.i32	q1, q1, #0x2
vshl.i32	q15, q2, #0x2
vadd.i32	q1, q1, q3
vadd.i32	q2, q2, q15
vadd.i32	q9, q9, q8
vsub.i32	q9, q9, q10
vadd.i32	q1, q1, q0
vsub.i32	q1, q1, q2
vrshrn.i32	d18, q9, #0xa
vrshrn.i32	d19, q1, #0xa
vqmovun.s16	d11, q9
vld1.8	{d16, d17}, [r4:128], r12
vld1.8	{d30, d31}, [r4:128], r12
vext.32	q1, q8, q15, #0x1
vext.16	q0, q8, q15, #0x3
vaddl.s16	q9, d2, d0
vext.16	q2, q8, q15, #0x1
vaddl.s16	q1, d3, d1
vext.64	q3, q8, q15, #0x1
vaddl.s16	q10, d4, d6
vext.16	q15, q8, q15, #0x5
vaddl.s16	q2, d5, d7
vaddl.s16	q0, d17, d31
vaddl.s16	q8, d16, d30
vshl.i32	q3, q9, #0x4
vshl.i32	q9, q9, #0x2
vshl.i32	q15, q10, #0x2
vadd.i32	q9, q9, q3
vadd.i32	q10, q10, q15
vshl.i32	q3, q1, #0x4
vshl.i32	q1, q1, #0x2
vshl.i32	q15, q2, #0x2
vadd.i32	q1, q1, q3
vadd.i32	q2, q2, q15
vadd.i32	q9, q9, q8
vsub.i32	q9, q9, q10
vadd.i32	q1, q1, q0
vsub.i32	q1, q1, q2
vrshrn.i32	d18, q9, #0xa
vrshrn.i32	d19, q1, #0xa
vqmovun.s16	d12, q9
vld1.8	{d16, d17}, [r4:128], r12
vld1.8	{d30, d31}, [r4:128], r12
vext.32	q1, q8, q15, #0x1
vext.16	q0, q8, q15, #0x3
vaddl.s16	q9, d2, d0
vext.16	q2, q8, q15, #0x1
vaddl.s16	q1, d3, d1
vext.64	q3, q8, q15, #0x1
vaddl.s16	q10, d4, d6
vext.16	q15, q8, q15, #0x5
vaddl.s16	q2, d5, d7
vaddl.s16	q0, d17, d31
vaddl.s16	q8, d16, d30
vshl.i32	q3, q9, #0x4
vshl.i32	q9, q9, #0x2
vshl.i32	q15, q10, #0x2
vadd.i32	q9, q9, q3
vadd.i32	q10, q10, q15
vshl.i32	q3, q1, #0x4
vshl.i32	q1, q1, #0x2
vshl.i32	q15, q2, #0x2
vadd.i32	q1, q1, q3
vadd.i32	q2, q2, q15
vadd.i32	q9, q9, q8
vsub.i32	q9, q9, q10
vadd.i32	q1, q1, q0
vsub.i32	q1, q1, q2
vrshrn.i32	d18, q9, #0xa
vrshrn.i32	d19, q1, #0xa
vqmovun.s16	d13, q9
vld1.8	{d16, d17}, [r4:128], r12
vld1.8	{d30, d31}, [r4:128], r12
vext.32	q1, q8, q15, #0x1
vext.16	q0, q8, q15, #0x3
vaddl.s16	q9, d2, d0
vext.16	q2, q8, q15, #0x1
vaddl.s16	q1, d3, d1
vext.64	q3, q8, q15, #0x1
vaddl.s16	q10, d4, d6
vext.16	q15, q8, q15, #0x5
vaddl.s16	q2, d5, d7
vaddl.s16	q0, d17, d31
vaddl.s16	q8, d16, d30
vshl.i32	q3, q9, #0x4
vshl.i32	q9, q9, #0x2
vshl.i32	q15, q10, #0x2
vadd.i32	q9, q9, q3
vadd.i32	q10, q10, q15
vshl.i32	q3, q1, #0x4
vshl.i32	q1, q1, #0x2
vshl.i32	q15, q2, #0x2
vadd.i32	q1, q1, q3
vadd.i32	q2, q2, q15
vadd.i32	q9, q9, q8
vsub.i32	q9, q9, q10
vadd.i32	q1, q1, q0
vsub.i32	q1, q1, q2
vrshrn.i32	d18, q9, #0xa
vrshrn.i32	d19, q1, #0xa
vqmovun.s16	d14, q9
vld1.8	{d16, d17}, [r4:128], r12
vld1.8	{d30, d31}, [r4:128]
vext.32	q1, q8, q15, #0x1
vext.16	q0, q8, q15, #0x3
vaddl.s16	q9, d2, d0
vext.16	q2, q8, q15, #0x1
vaddl.s16	q1, d3, d1
vext.64	q3, q8, q15, #0x1
vaddl.s16	q10, d4, d6
vext.16	q15, q8, q15, #0x5
vaddl.s16	q2, d5, d7
vaddl.s16	q0, d17, d31
vaddl.s16	q8, d16, d30
vshl.i32	q3, q9, #0x4
vshl.i32	q9, q9, #0x2
vshl.i32	q15, q10, #0x2
vadd.i32	q9, q9, q3
vadd.i32	q10, q10, q15
vshl.i32	q3, q1, #0x4
vshl.i32	q1, q1, #0x2
vshl.i32	q15, q2, #0x2
vadd.i32	q1, q1, q3
vadd.i32	q2, q2, q15
vadd.i32	q9, q9, q8
vsub.i32	q9, q9, q10
vadd.i32	q1, q1, q0
vsub.i32	q1, q1, q2
vrshrn.i32	d18, q9, #0xa
vrshrn.i32	d19, q1, #0xa
vqmovun.s16	d15, q9
vtrn.32	d12, d8
vtrn.32	d13, d9
vtrn.32	d14, d10
vtrn.32	d15, d11
vtrn.16	d12, d14
vtrn.16	d13, d15
vtrn.16	d8, d10
vtrn.16	d9, d11
vtrn.8	d12, d13
vtrn.8	d14, d15
vtrn.8	d8, d9
vtrn.8	d10, d11
bx	lr
nop
put_h264_qpel8_hv_lowpass_neon:
mov	r10, lr
bl	put_h264_qpel8_hv_lowpass_neon_top
vst1.8	{d12}, [r0:64], r2
vst1.8	{d13}, [r0:64], r2
vst1.8	{d14}, [r0:64], r2
vst1.8	{d15}, [r0:64], r2
vst1.8	{d8}, [r0:64], r2
vst1.8	{d9}, [r0:64], r2
vst1.8	{d10}, [r0:64], r2
vst1.8	{d11}, [r0:64], r2
mov	lr, r10
bx	lr
nop
avg_h264_qpel8_hv_lowpass_neon:
mov	r10, lr
bl	put_h264_qpel8_hv_lowpass_neon_top
vld1.8	{d0}, [r0:64], r2
vrhadd.u8	d12, d12, d0
vld1.8	{d1}, [r0:64], r2
vrhadd.u8	d13, d13, d1
vld1.8	{d2}, [r0:64], r2
vrhadd.u8	d14, d14, d2
vld1.8	{d3}, [r0:64], r2
vrhadd.u8	d15, d15, d3
vld1.8	{d4}, [r0:64], r2
vrhadd.u8	d8, d8, d4
vld1.8	{d5}, [r0:64], r2
vrhadd.u8	d9, d9, d5
vld1.8	{d6}, [r0:64], r2
vrhadd.u8	d10, d10, d6
vld1.8	{d7}, [r0:64], r2
vrhadd.u8	d11, d11, d7
sub.w	r0, r0, r2, lsl #3
vst1.8	{d12}, [r0:64], r2
vst1.8	{d13}, [r0:64], r2
vst1.8	{d14}, [r0:64], r2
vst1.8	{d15}, [r0:64], r2
vst1.8	{d8}, [r0:64], r2
vst1.8	{d9}, [r0:64], r2
vst1.8	{d10}, [r0:64], r2
vst1.8	{d11}, [r0:64], r2
mov	lr, r10
bx	lr
nop
put_h264_qpel8_hv_lowpass_l2_neon:
mov	r10, lr
bl	put_h264_qpel8_hv_lowpass_neon_top
vld1.8	{d0, d1}, [r2:128]!
vld1.8	{d2, d3}, [r2:128]!
vrhadd.u8	q0, q0, q6
vld1.8	{d4, d5}, [r2:128]!
vrhadd.u8	q1, q1, q7
vld1.8	{d6, d7}, [r2:128]!
vrhadd.u8	q2, q2, q4
vrhadd.u8	q3, q3, q5
vst1.8	{d0}, [r0:64], r3
vst1.8	{d1}, [r0:64], r3
vst1.8	{d2}, [r0:64], r3
vst1.8	{d3}, [r0:64], r3
vst1.8	{d4}, [r0:64], r3
vst1.8	{d5}, [r0:64], r3
vst1.8	{d6}, [r0:64], r3
vst1.8	{d7}, [r0:64], r3
mov	lr, r10
bx	lr
nop
avg_h264_qpel8_hv_lowpass_l2_neon:
mov	r10, lr
bl	put_h264_qpel8_hv_lowpass_neon_top
vld1.8	{d0, d1}, [r2:128]!
vld1.8	{d2, d3}, [r2:128]!
vrhadd.u8	q0, q0, q6
vld1.8	{d4, d5}, [r2:128]!
vrhadd.u8	q1, q1, q7
vld1.8	{d6, d7}, [r2:128]!
vrhadd.u8	q2, q2, q4
vrhadd.u8	q3, q3, q5
vld1.8	{d16}, [r0:64], r3
vrhadd.u8	d0, d0, d16
vld1.8	{d17}, [r0:64], r3
vrhadd.u8	d1, d1, d17
vld1.8	{d18}, [r0:64], r3
vrhadd.u8	d2, d2, d18
vld1.8	{d19}, [r0:64], r3
vrhadd.u8	d3, d3, d19
vld1.8	{d20}, [r0:64], r3
vrhadd.u8	d4, d4, d20
vld1.8	{d21}, [r0:64], r3
vrhadd.u8	d5, d5, d21
vld1.8	{d22}, [r0:64], r3
vrhadd.u8	d6, d6, d22
vld1.8	{d23}, [r0:64], r3
vrhadd.u8	d7, d7, d23
sub.w	r0, r0, r3, lsl #3
vst1.8	{d0}, [r0:64], r3
vst1.8	{d1}, [r0:64], r3
vst1.8	{d2}, [r0:64], r3
vst1.8	{d3}, [r0:64], r3
vst1.8	{d4}, [r0:64], r3
vst1.8	{d5}, [r0:64], r3
vst1.8	{d6}, [r0:64], r3
vst1.8	{d7}, [r0:64], r3
mov	lr, r10
bx	lr
nop
put_h264_qpel16_hv_lowpass_neon:
mov	r9, lr
bl	put_h264_qpel8_hv_lowpass_neon
sub.w	r1, r1, r3, lsl #2
bl	put_h264_qpel8_hv_lowpass_neon
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
sub.w	r0, r0, r2, lsl #4
add.w	r0, r0, #0x8
bl	put_h264_qpel8_hv_lowpass_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r9
b	put_h264_qpel8_hv_lowpass_neon
nop
put_h264_qpel16_hv_lowpass_l2_neon:
mov	r9, lr
sub.w	r2, r4, #0x100
bl	put_h264_qpel8_hv_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #2
bl	put_h264_qpel8_hv_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
sub.w	r0, r0, r3, lsl #4
add.w	r0, r0, #0x8
bl	put_h264_qpel8_hv_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r9
b	put_h264_qpel8_hv_lowpass_l2_neon
nop
avg_h264_qpel16_hv_lowpass_neon:
mov	r9, lr
bl	avg_h264_qpel8_hv_lowpass_neon
sub.w	r1, r1, r3, lsl #2
bl	avg_h264_qpel8_hv_lowpass_neon
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
sub.w	r0, r0, r2, lsl #4
add.w	r0, r0, #0x8
bl	avg_h264_qpel8_hv_lowpass_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r9
b	avg_h264_qpel8_hv_lowpass_neon
nop
avg_h264_qpel16_hv_lowpass_l2_neon:
mov	r9, lr
sub.w	r2, r4, #0x100
bl	avg_h264_qpel8_hv_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #2
bl	avg_h264_qpel8_hv_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #4
sub.w	r1, r1, r3, lsl #2
add.w	r1, r1, #0x8
sub.w	r0, r0, r3, lsl #4
add.w	r0, r0, #0x8
bl	avg_h264_qpel8_hv_lowpass_l2_neon
sub.w	r1, r1, r3, lsl #2
mov	lr, r9
b	avg_h264_qpel8_hv_lowpass_l2_neon
nop
function ff_put_h264_qpel8_mc10_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r3, r1
sub.w	r1, r1, #0x2
mov.w	r12, #0x8
b.w	put_h264_qpel8_h_lowpass_l2_neon
nop
function ff_put_h264_qpel8_mc20_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
sub.w	r1, r1, #0x2
mov	r3, r2
mov.w	r12, #0x8
b.w	put_h264_qpel8_h_lowpass_neon
nop
function ff_put_h264_qpel8_mc30_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
add.w	r3, r1, #0x1
sub.w	r1, r1, #0x2
mov.w	r12, #0x8
b.w	put_h264_qpel8_h_lowpass_l2_neon

function ff_put_h264_qpel8_mc01_neon
push	{lr}
mov	r12, r1
put_h264_qpel8_mc01:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r3, r2
sub.w	r1, r1, r2, lsl #1
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_v_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
pop	{pc}

function ff_put_h264_qpel8_mc11_neon
push.w	{r0, r1, r11, lr}
put_h264_qpel8_mc11:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x40
mov	r0, sp
sub.w	r1, r1, #0x2
mov.w	r3, #0x8
mov.w	r12, #0x8
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_h_lowpass_neon
ldrd	r0, r1, [r11], #8
mov	r3, r2
add.w	r12, sp, #0x40
sub.w	r1, r1, r2, lsl #1
mov.w	r2, #0x8
bl	put_h264_qpel8_v_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r11, pc}

function ff_put_h264_qpel8_mc21_neon
push.w	{r0, r1, r4, r10, r11, lr}
put_h264_qpel8_mc21:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x100
sub.w	r1, r1, #0x2
mov.w	r3, #0x8
mov	r0, sp
mov.w	r12, #0x8
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_h_lowpass_neon
mov	r4, r0
ldrd	r0, r1, [r11], #8
sub.w	r1, r1, r2, lsl #1
sub.w	r1, r1, #0x2
mov	r3, r2
sub.w	r2, r4, #0x40
bl	put_h264_qpel8_hv_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r10, r11, pc}
nop

function ff_put_h264_qpel8_mc31_neon
add.w	r1, r1, #0x1
push.w	{r0, r1, r11, lr}
sub.w	r1, r1, #0x1
b	put_h264_qpel8_mc11
nop

function ff_put_h264_qpel8_mc02_neon
push	{lr}
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
sub.w	r1, r1, r2, lsl #1
mov	r3, r2
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_v_lowpass_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
pop	{pc}
nop

function ff_put_h264_qpel8_mc12_neon
push.w	{r0, r1, r4, r10, r11, lr}
put_h264_qpel8_mc12:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x100
sub.w	r1, r1, r2, lsl #1
mov	r3, r2
mov.w	r2, #0x8
mov	r0, sp
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_v_lowpass_neon
mov	r4, r0
ldrd	r0, r1, [r11], #8
sub.w	r1, r1, r3, lsl #1
sub.w	r1, r1, #0x2
sub.w	r2, r4, #0x40
bl	put_h264_qpel8_hv_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r10, r11, pc}
nop

function ff_put_h264_qpel8_mc22_neon
push.w	{r4, r10, r11, lr}
mov	r11, sp
bic	r4, r11, #0xf
mov	sp, r4
sub.w	r1, r1, r2, lsl #1
sub.w	r1, r1, #0x2
mov	r3, r2
sub	sp, #0xc0
mov	r4, sp
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_hv_lowpass_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r10, r11, pc}

function ff_put_h264_qpel8_mc32_neon
push.w	{r0, r1, r4, r10, r11, lr}
add.w	r1, r1, #0x1
b	put_h264_qpel8_mc12
nop
function ff_put_h264_qpel8_mc03_neon
push	{lr}
add.w	r12, r1, r2
b	put_h264_qpel8_mc01

function ff_put_h264_qpel8_mc13_neon
push.w	{r0, r1, r11, lr}
add	r1, r2
b	put_h264_qpel8_mc11
function ff_put_h264_qpel8_mc23_neon
push.w	{r0, r1, r4, r10, r11, lr}
add	r1, r2
b	put_h264_qpel8_mc21
function ff_put_h264_qpel8_mc33_neon
add.w	r1, r1, #0x1
push.w	{r0, r1, r11, lr}
add	r1, r2
sub.w	r1, r1, #0x1
b	put_h264_qpel8_mc11

function ff_avg_h264_qpel8_mc10_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r3, r1
sub.w	r1, r1, #0x2
mov.w	r12, #0x8
b.w	avg_h264_qpel8_h_lowpass_l2_neon
nop

function ff_avg_h264_qpel8_mc20_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
sub.w	r1, r1, #0x2
mov	r3, r2
mov.w	r12, #0x8
b.w	avg_h264_qpel8_h_lowpass_neon
nop

function ff_avg_h264_qpel8_mc30_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
add.w	r3, r1, #0x1
sub.w	r1, r1, #0x2
mov.w	r12, #0x8
b.w	avg_h264_qpel8_h_lowpass_l2_neon
function ff_avg_h264_qpel8_mc01_neon
push	{lr}
mov	r12, r1
avg_h264_qpel8_mc01:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r3, r2
sub.w	r1, r1, r2, lsl #1
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	avg_h264_qpel8_v_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
pop	{pc}

function ff_avg_h264_qpel8_mc11_neon
push.w	{r0, r1, r11, lr}
avg_h264_qpel8_mc11:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x40
mov	r0, sp
sub.w	r1, r1, #0x2
mov.w	r3, #0x8
mov.w	r12, #0x8
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_h_lowpass_neon
ldrd	r0, r1, [r11], #8
mov	r3, r2
add.w	r12, sp, #0x40
sub.w	r1, r1, r2, lsl #1
mov.w	r2, #0x8
bl	avg_h264_qpel8_v_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r11, pc}
function ff_avg_h264_qpel8_mc21_neon
push.w	{r0, r1, r4, r10, r11, lr}
avg_h264_qpel8_mc21:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x100
sub.w	r1, r1, #0x2
mov.w	r3, #0x8
mov	r0, sp
mov.w	r12, #0x8
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_h_lowpass_neon
mov	r4, r0
ldrd	r0, r1, [r11], #8
sub.w	r1, r1, r2, lsl #1
sub.w	r1, r1, #0x2
mov	r3, r2
sub.w	r2, r4, #0x40
bl	avg_h264_qpel8_hv_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r10, r11, pc}
nop
function ff_avg_h264_qpel8_mc31_neon
add.w	r1, r1, #0x1
push.w	{r0, r1, r11, lr}
sub.w	r1, r1, #0x1
b	avg_h264_qpel8_mc11
nop
ff_avg_h264_qpel8_mc02_neon:
push	{lr}
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
sub.w	r1, r1, r2, lsl #1
mov	r3, r2
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	avg_h264_qpel8_v_lowpass_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
pop	{pc}
nop
ff_avg_h264_qpel8_mc12_neon:
push.w	{r0, r1, r4, r10, r11, lr}
avg_h264_qpel8_mc12:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x100
sub.w	r1, r1, r2, lsl #1
mov	r3, r2
mov.w	r2, #0x8
mov	r0, sp
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel8_v_lowpass_neon
mov	r4, r0
ldrd	r0, r1, [r11], #8
sub.w	r1, r1, r3, lsl #1
sub.w	r1, r1, #0x2
sub.w	r2, r4, #0x40
bl	avg_h264_qpel8_hv_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r10, r11, pc}
nop
ff_avg_h264_qpel8_mc22_neon:
push.w	{r4, r10, r11, lr}
mov	r11, sp
bic	r4, r11, #0xf
mov	sp, r4
sub.w	r1, r1, r2, lsl #1
sub.w	r1, r1, #0x2
mov	r3, r2
sub	sp, #0xc0
mov	r4, sp
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	avg_h264_qpel8_hv_lowpass_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r10, r11, pc}
ff_avg_h264_qpel8_mc32_neon:
push.w	{r0, r1, r4, r10, r11, lr}
add.w	r1, r1, #0x1
b	avg_h264_qpel8_mc12
nop
ff_avg_h264_qpel8_mc03_neon:
push	{lr}
add.w	r12, r1, r2
b	avg_h264_qpel8_mc01
ff_avg_h264_qpel8_mc13_neon:
push.w	{r0, r1, r11, lr}
add	r1, r2
b	avg_h264_qpel8_mc11
function ff_avg_h264_qpel8_mc23_neon
push.w	{r0, r1, r4, r10, r11, lr}
add	r1, r2
b	avg_h264_qpel8_mc21

function ff_avg_h264_qpel8_mc33_neon
add.w	r1, r1, #0x1
push.w	{r0, r1, r11, lr}
add	r1, r2
sub.w	r1, r1, #0x1
b	avg_h264_qpel8_mc11

function ff_put_h264_qpel16_mc10_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r3, r1
sub.w	r1, r1, #0x2
b.w	put_h264_qpel16_h_lowpass_l2_neon
nop

function ff_put_h264_qpel16_mc20_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
sub.w	r1, r1, #0x2
mov	r3, r2
b.w	put_h264_qpel16_h_lowpass_neon
nop

function ff_put_h264_qpel16_mc30_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
add.w	r3, r1, #0x1
sub.w	r1, r1, #0x2
b.w	put_h264_qpel16_h_lowpass_l2_neon

function ff_put_h264_qpel16_mc01_neon
push	{r4, lr}
mov	r12, r1
put_h264_qpel16_mc01:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r3, r2
sub.w	r1, r1, r2, lsl #1
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_v_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
pop	{r4, pc}

function ff_put_h264_qpel16_mc11_neon
push.w	{r0, r1, r4, r11, lr}
put_h264_qpel16_mc11:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x100
mov	r0, sp
sub.w	r1, r1, #0x2
mov.w	r3, #0x10
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_h_lowpass_neon
ldrd	r0, r1, [r11], #8
mov	r3, r2
add.w	r12, sp, #0x40
sub.w	r1, r1, r2, lsl #1
mov.w	r2, #0x10
bl	put_h264_qpel16_v_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r11, pc}

function ff_put_h264_qpel16_mc21_neon
push.w	{r0, r1, r4, r5, r9, r10, r11, lr}
put_h264_qpel16_mc21:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x1c0
sub.w	r1, r1, #0x2
mov	r0, sp
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_h_lowpass_neon_packed
mov	r4, r0
ldrd	r0, r1, [r11], #8
sub.w	r1, r1, r2, lsl #1
sub.w	r1, r1, #0x2
mov	r3, r2
bl	put_h264_qpel16_hv_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r5, r9, r10, r11, pc}
nop
function ff_put_h264_qpel16_mc31_neon
add.w	r1, r1, #0x1
push.w	{r0, r1, r4, r11, lr}
sub.w	r1, r1, #0x1
b	put_h264_qpel16_mc11
nop

function ff_put_h264_qpel16_mc02_neon
push	{r4, lr}
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
sub.w	r1, r1, r2, lsl #1
mov	r3, r2
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_v_lowpass_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
pop	{r4, pc}
nop

function ff_put_h264_qpel16_mc12_neon
push.w	{r0, r1, r4, r5, r9, r10, r11, lr}
put_h264_qpel16_mc12:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x1c0
sub.w	r1, r1, r2, lsl #1
mov	r0, sp
mov	r3, r2
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_v_lowpass_neon_packed
mov	r4, r0
ldrd	r0, r1, [r11], #8
sub.w	r1, r1, r3, lsl #1
sub.w	r1, r1, #0x2
mov	r2, r3
bl	put_h264_qpel16_hv_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r5, r9, r10, r11, pc}

function ff_put_h264_qpel16_mc22_neon
push.w	{r4, r9, r10, r11, lr}
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r4, r11, #0xf
mov	sp, r4
sub.w	r1, r1, r2, lsl #1
sub.w	r1, r1, #0x2
mov	r3, r2
sub	sp, #0xc0
mov	r4, sp
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_hv_lowpass_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r9, r10, r11, pc}

function ff_put_h264_qpel16_mc32_neon
push.w	{r0, r1, r4, r5, r9, r10, r11, lr}
add.w	r1, r1, #0x1
b	put_h264_qpel16_mc12
nop
function ff_put_h264_qpel16_mc03_neon
push	{r4, lr}
add.w	r12, r1, r2
b	put_h264_qpel16_mc01

function ff_put_h264_qpel16_mc13_neon
push.w	{r0, r1, r4, r11, lr}
add	r1, r2
b	put_h264_qpel16_mc11

function ff_put_h264_qpel16_mc23_neon
push.w	{r0, r1, r4, r5, r9, r10, r11, lr}
add	r1, r2
b	put_h264_qpel16_mc21

function ff_put_h264_qpel16_mc33_neon
add.w	r1, r1, #0x1
push.w	{r0, r1, r4, r11, lr}
add	r1, r2
sub.w	r1, r1, #0x1
b	put_h264_qpel16_mc11

function ff_avg_h264_qpel16_mc10_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r3, r1
sub.w	r1, r1, #0x2
b.w	avg_h264_qpel16_h_lowpass_l2_neon
nop
ff_avg_h264_qpel16_mc20_neon:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
sub.w	r1, r1, #0x2
mov	r3, r2
b.w	avg_h264_qpel16_h_lowpass_neon
nop

function ff_avg_h264_qpel16_mc30_neon
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
add.w	r3, r1, #0x1
sub.w	r1, r1, #0x2
b.w	avg_h264_qpel16_h_lowpass_l2_neon
ff_avg_h264_qpel16_mc01_neon:
push	{r4, lr}
mov	r12, r1
avg_h264_qpel16_mc01:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r3, r2
sub.w	r1, r1, r2, lsl #1
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	avg_h264_qpel16_v_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
pop	{r4, pc}

function ff_avg_h264_qpel16_mc11_neon
push.w	{r0, r1, r4, r11, lr}
avg_h264_qpel16_mc11:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x100
mov	r0, sp
sub.w	r1, r1, #0x2
mov.w	r3, #0x10
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_h_lowpass_neon
ldrd	r0, r1, [r11], #8
mov	r3, r2
add.w	r12, sp, #0x40
sub.w	r1, r1, r2, lsl #1
mov.w	r2, #0x10
bl	avg_h264_qpel16_v_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r11, pc}

function ff_avg_h264_qpel16_mc21_neon
push.w	{r0, r1, r4, r5, r9, r10, r11, lr}
avg_h264_qpel16_mc21:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x1c0
sub.w	r1, r1, #0x2
mov	r0, sp
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_h_lowpass_neon_packed
mov	r4, r0
ldrd	r0, r1, [r11], #8
sub.w	r1, r1, r2, lsl #1
sub.w	r1, r1, #0x2
mov	r3, r2
bl	avg_h264_qpel16_hv_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r5, r9, r10, r11, pc}
nop
ff_avg_h264_qpel16_mc31_neon:
add.w	r1, r1, #0x1
push.w	{r0, r1, r4, r11, lr}
sub.w	r1, r1, #0x1
b	avg_h264_qpel16_mc11
nop
ff_avg_h264_qpel16_mc02_neon:
push	{r4, lr}
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
sub.w	r1, r1, r2, lsl #1
mov	r3, r2
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	avg_h264_qpel16_v_lowpass_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
pop	{r4, pc}
nop

function ff_avg_h264_qpel16_mc12_neon
push.w	{r0, r1, r4, r5, r9, r10, r11, lr}
avg_h264_qpel16_mc12:
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r0, r11, #0xf
mov	sp, r0
sub	sp, #0x1c0
sub.w	r1, r1, r2, lsl #1
mov	r0, sp
mov	r3, r2
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	put_h264_qpel16_v_lowpass_neon_packed
mov	r4, r0
ldrd	r0, r1, [r11], #8
sub.w	r1, r1, r3, lsl #1
sub.w	r1, r1, #0x2
mov	r2, r3
bl	avg_h264_qpel16_hv_lowpass_l2_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r5, r9, r10, r11, pc}
ff_avg_h264_qpel16_mc22_neon:
push.w	{r4, r9, r10, r11, lr}
movw	r3, #0x5
movt	r3, #0x14
vmov.32	d6[0], r3
mov	r11, sp
bic	r4, r11, #0xf
mov	sp, r4
sub.w	r1, r1, r2, lsl #1
sub.w	r1, r1, #0x2
mov	r3, r2
sub	sp, #0xc0
mov	r4, sp
vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
bl	avg_h264_qpel16_hv_lowpass_neon
vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
mov	sp, r11
pop.w	{r4, r9, r10, r11, pc}

function ff_avg_h264_qpel16_mc32_neon
push.w	{r0, r1, r4, r5, r9, r10, r11, lr}
add.w	r1, r1, #0x1
b	avg_h264_qpel16_mc12
nop
ff_avg_h264_qpel16_mc03_neon:
push	{r4, lr}
add.w	r12, r1, r2
b	avg_h264_qpel16_mc01
ff_avg_h264_qpel16_mc13_neon:
push.w	{r0, r1, r4, r11, lr}
add	r1, r2
b	avg_h264_qpel16_mc11

function ff_avg_h264_qpel16_mc23_neon
push.w	{r0, r1, r4, r5, r9, r10, r11, lr}
add	r1, r2
b	avg_h264_qpel16_mc21
ff_avg_h264_qpel16_mc33_neon:
add.w	r1, r1, #0x1
push.w	{r0, r1, r4, r11, lr}
add	r1, r2
sub.w	r1, r1, #0x1
b	avg_h264_qpel16_mc11