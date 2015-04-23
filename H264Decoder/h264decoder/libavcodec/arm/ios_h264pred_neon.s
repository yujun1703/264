
//
//  Created by landyji on 20140605.
//  Copyright (c) 2013å¹?com.tencent.avteam. All rights reserved.
//

.macro function name
.global _\name
.align 2
_\name:
.endm

.text
function ff_pred16x16_dc_neon
sub	r2, r0, r1
vld1.8	{d0, d1}, [r2:128]
sub	r2, r0, #0x1
vld1.8	{d2[0]}, [r2], r1
vld1.8	{d2[1]}, [r2], r1
vld1.8	{d2[2]}, [r2], r1
vld1.8	{d2[3]}, [r2], r1
vld1.8	{d2[4]}, [r2], r1
vld1.8	{d2[5]}, [r2], r1
vld1.8	{d2[6]}, [r2], r1
vld1.8	{d2[7]}, [r2], r1
vld1.8	{d3[0]}, [r2], r1
vld1.8	{d3[1]}, [r2], r1
vld1.8	{d3[2]}, [r2], r1
vld1.8	{d3[3]}, [r2], r1
vld1.8	{d3[4]}, [r2], r1
vld1.8	{d3[5]}, [r2], r1
vld1.8	{d3[6]}, [r2], r1
vld1.8	{d3[7]}, [r2], r1
vaddl.u8	q0, d0, d1
vaddl.u8	    q1, d2, d3
vadd.i16	q0, q0, q1
vadd.i16	d0, d0, d1
vpadd.i16	d0, d0, d0
vpadd.i16	d0, d0, d0
vrshrn.i16	d0, q0, #0x5
vdup.8	q0, d0[0]
L_pred16x16_dc_end:
mov.w	r3, #0x8
6:
vst1.8	{d0, d1}, [r0:128], r1
vst1.8	{d0, d1}, [r0:128], r1
subs	r3, #0x1
bne	6b
bx	lr


function ff_pred16x16_vert_neon
sub.w	r0, r0, r1
vld1.8	{d0, d1}, [r0:128], r1
mov.w	r3, #0x8
1:
vst1.8	{d0, d1}, [r0:128], r1
vst1.8	{d0, d1}, [r0:128], r1
subs	r3, #0x1
bne	1b
bx	lr


function ff_pred16x16_left_dc_neon
sub.w	r2, r0, #0x1
vld1.8	{d0[0]}, [r2], r1
vld1.8	{d0[1]}, [r2], r1
vld1.8	{d0[2]}, [r2], r1
vld1.8	{d0[3]}, [r2], r1
vld1.8	{d0[4]}, [r2], r1
vld1.8	{d0[5]}, [r2], r1
vld1.8	{d0[6]}, [r2], r1
vld1.8	{d0[7]}, [r2], r1
vld1.8	{d1[0]}, [r2], r1
vld1.8	{d1[1]}, [r2], r1
vld1.8	{d1[2]}, [r2], r1
vld1.8	{d1[3]}, [r2], r1
vld1.8	{d1[4]}, [r2], r1
vld1.8	{d1[5]}, [r2], r1
vld1.8	{d1[6]}, [r2], r1
vld1.8	{d1[7]}, [r2], r1
vaddl.u8	q0, d0, d1
vadd.i16	d0, d0, d1
vpadd.i16	d0, d0, d0
vpadd.i16	d0, d0, d0
vrshrn.i16	d0, q0, #0x4
vdup.8	q0, d0[0]
b L_pred16x16_dc_end


function ff_pred16x16_128_dc_neon
vmov.i8	q0, #0x80
b	L_pred16x16_dc_end


function ff_pred16x16_top_dc_neon
sub.w	r2, r0, r1
vld1.8	{d0, d1}, [r2:128]
vaddl.u8	q0, d0, d1
vadd.i16	d0, d0, d1
vpadd.i16	d0, d0, d0
vpadd.i16	d0, d0, d0
vrshrn.i16	d0, q0, #0x4
vdup.8	q0, d0[0]
b	L_pred16x16_dc_end



function ff_pred16x16_hor_neon
sub.w	r2, r0, #0x1
mov.w	r3, #0x10
1:
vld1.8	{d0[], d1[]}, [r2], r1
vst1.8	{d0, d1}, [r0:128], r1
subs	r3, #0x1
bne	1b
bx	lr

function ff_pred8x8_vert_neon
sub.w	r0, r0, r1
vld1.8	{d0}, [r0:64], r1
mov.w	r3, #0x4
1:
vst1.8	{d0}, [r0:64], r1
vst1.8	{d0}, [r0:64], r1
subs	r3, #0x1
bne	1b
bx	lr


function ff_pred8x8_hor_neon
sub.w	r2, r0, #0x1
mov.w	r3, #0x8
1:
vld1.8	{d0[]}, [r2], r1
vst1.8	{d0}, [r0:64], r1 
subs	r3, #0x1
bne	1b
bx	lr



function ff_pred8x8_128_dc_neon
vmov.i8	q0, #0x80
b	L_pred8x8_dc_end

function ff_pred8x8_top_dc_neon
sub.w	r2, r0, r1
vld1.8	{d0}, [r2:64]
vpaddl.u8	d0, d0
vpadd.i16	d0, d0, d0
vrshrn.i16	d0, q0, #0x2
vdup.8	d1, d0[1]
vdup.8	d0, d0[0]
vtrn.32	d0, d1
b	L_pred8x8_dc_end
nop

function ff_pred8x8_left_dc_neon
sub.w	r2, r0, #0x1
vld1.8	{d0[0]}, [r2], r1
vld1.8	{d0[1]}, [r2], r1
vld1.8	{d0[2]}, [r2], r1
vld1.8	{d0[3]}, [r2], r1
vld1.8	{d0[4]}, [r2], r1
vld1.8	{d0[5]}, [r2], r1
vld1.8	{d0[6]}, [r2], r1
vld1.8	{d0[7]}, [r2], r1
vpaddl.u8	d0, d0
vpadd.i16	d0, d0, d0
vrshrn.i16	d0, q0, #0x2
vdup.8	d1, d0[1]
vdup.8	d0, d0[0]
b	L_pred8x8_dc_end


function ff_pred8x8_dc_neon
sub.w	r2, r0, r1
vld1.8	{d0}, [r2:64]
sub.w	r2, r0, #0x1
vld1.8	{d1[0]}, [r2], r1
vld1.8	{d1[1]}, [r2], r1
vld1.8	{d1[2]}, [r2], r1
vld1.8	{d1[3]}, [r2], r1
vld1.8	{d1[4]}, [r2], r1
vld1.8	{d1[5]}, [r2], r1
vld1.8	{d1[6]}, [r2], r1
vld1.8	{d1[7]}, [r2], r1
vtrn.32	d0, d1
vpaddl.u8	q0, q0
vpadd.i16	d0, d0, d1
vpadd.i16	d1, d0, d0
vrshrn.i16	d2, q0, #0x3
vrshrn.i16	d3, q0, #0x2
vdup.8	d0, d2[4]
vdup.8	d1, d3[3]
vdup.8	d4, d3[2]
vdup.8	d5, d2[5]
vtrn.32	q0, q2
L_pred8x8_dc_end:
mov.w	r3, #0x4
add.w	r2, r0, r1, lsl #2
6:
vst1.8	{d0}, [r0:64], r1
vst1.8	{d1}, [r2:64], r1
subs	r3, #0x1
bne	6b
bx	lr


function ff_pred8x8_l0t_dc_neon
sub.w	r2, r0, r1
vld1.8	{d0}, [r2:64]
sub.w	r2, r0, #0x1
vld1.8	{d1[0]}, [r2], r1
vld1.8	{d1[1]}, [r2], r1
vld1.8	{d1[2]}, [r2], r1
vld1.8	{d1[3]}, [r2], r1
vtrn.32	d0, d1
vpaddl.u8	q0, q0
vpadd.i16	d0, d0, d1
vpadd.i16	d1, d0, d0
vrshrn.i16	d2, q0, #0x3
vrshrn.i16	d3, q0, #0x2
vdup.8	d0, d2[4]
vdup.8	d1, d3[0]
vdup.8	q2, d3[2]
vtrn.32	q0, q2
b	L_pred8x8_dc_end


function ff_pred8x8_0lt_dc_neon
sub.w	r2, r0, r1
vld1.8	{d0}, [r2:64]
add.w	r2, r0, r1, lsl #2
sub.w	r2, r2, #0x1
vld1.8	{d1[4]}, [r2], r1
vld1.8	{d1[5]}, [r2], r1
vld1.8	{d1[6]}, [r2], r1
vld1.8	{d1[7]}, [r2], r1
vtrn.32	d0, d1
vpaddl.u8	q0, q0
vpadd.i16	d0, d0, d1
vpadd.i16	d1, d0, d0
vrshrn.i16	d3, q0, #0x2
vrshrn.i16	d2, q0, #0x3
vdup.8	d0, d3[0]
vdup.8	d1, d3[3]
vdup.8	d4, d3[2]
vdup.8	d5, d2[5]
vtrn.32	q0, q2
b	L_pred8x8_dc_end


function ff_pred8x8_0l0_dc_neon
add.w	r2, r0, r1, lsl #2
sub.w	r2, r2, #0x1
vld1.8	{d1[0]}, [r2], r1
vld1.8	{d1[1]}, [r2], r1
vld1.8	{d1[2]}, [r2], r1
vld1.8	{d1[3]}, [r2], r1
vpaddl.u8	d2, d1
vpadd.i16	d2, d2, d2
vrshrn.i16	d1, q1, #0x2
vmov.i8	d0, #0x80
vdup.8	d1, d1[0]
b	L_pred8x8_dc_end


function ff_pred8x8_l00_dc_neon
sub.w	r2, r0, #0x1
vld1.8	{d0[0]}, [r2], r1
vld1.8	{d0[1]}, [r2], r1
vld1.8	{d0[2]}, [r2], r1
vld1.8	{d0[3]}, [r2], r1
vpaddl.u8	d0, d0
vpadd.i16	d0, d0, d0
vrshrn.i16	d0, q0, #0x2
vmov.i8	d1, #0x80
vdup.8	d0, d0[0]
b	L_pred8x8_dc_end

function ff_pred16x16_plane_neon
sub.w	r3, r0, r1                                               
add.w	r2, r3, #0x8                                             
sub.w	r3, r3, #0x1                                             
vld1.8	{d0}, [r3]                                             
vld1.8	{d2}, [r2:64], r1                                      
vld1.8	{d1[0]}, [r3], r1                                      
vld1.8	{d1[1]}, [r3], r1                                      
vld1.8	{d1[2]}, [r3], r1                                      
vld1.8	{d1[3]}, [r3], r1                                      
vld1.8	{d1[4]}, [r3], r1                                      
vld1.8	{d1[5]}, [r3], r1                                      
vld1.8	{d1[6]}, [r3], r1                                      
vld1.8	{d1[7]}, [r3], r1                                      
add	r3, r1                                                     
vld1.8	{d3[0]}, [r3], r1                                      
vld1.8	{d3[1]}, [r3], r1                                      
vld1.8	{d3[2]}, [r3], r1                                      
vld1.8	{d3[3]}, [r3], r1                                      
vld1.8	{d3[4]}, [r3], r1                                      
vld1.8	{d3[5]}, [r3], r1                                      
vld1.8	{d3[6]}, [r3], r1                                      
vld1.8	{d3[7]}, [r3], r1                                      
vrev64.8	q0, q0                                               
vaddl.u8	q8, d2, d3                                           
vsubl.u8	q2, d2, d0                                           
vsubl.u8	q3, d3, d1                                           
adr	        r3, p16weight

vld1.8	{d0, d1}, [r3:128]                                     
vmul.i16	q2, q2, q0                                           
vmul.i16	q3, q3, q0                                           
vadd.i16	d4, d4, d5                                           
vadd.i16	d5, d6, d7                                           
vpadd.i16	d4, d4, d5                                           
vpadd.i16	d4, d4, d4                                           
vshll.s16	q3, d4, #0x2                                         
vaddw.s16	q2, q3, d4                                           
vrshrn.i32	d4, q2, #0x6                                       
mov.w	r3, #0x0                                                 
vtrn.16	d4, d5                                                 
vadd.i16	d2, d4, d5                                           
vshl.i16	d3, d2, #0x3                                         
vrev64.16	d16, d17                                             
vsub.i16	d3, d3, d2                                           
vadd.i16	d16, d16, d0                                         
vshl.i16	d2, d16, #0x4                                        
vsub.i16	d2, d2, d3                                           
vshl.i16	d3, d4, #0x4                                         
vext.16	q0, q0, q0, #0x7                                       
vsub.i16	d6, d5, d3                                           
vmov.16	d0[0], r3                                              
vmul.i16	q0, q0, d4[0]                                        
vdup.16	q1, d2[0]                                              
vdup.16	q2, d4[0]                                              
vdup.16	q3, d6[0]                                              
vshl.i16	q2, q2, #0x3                                         
vadd.i16	q1, q1, q0                                           
vadd.i16	q3, q3, q2                                           
mov.w	r3, #0x10                                                
1:                                                             
vqshrun.s16	d0, q1, #0x5                                       
vadd.i16	q1, q1, q2                                           
vqshrun.s16	d1, q1, #0x5                                       
vadd.i16	q1, q1, q3                                           
vst1.8	{d0, d1}, [r0:128], r1                                 
subs	r3, #0x1                                                 
bne	1b                                                         
bx	lr

function ff_pred8x8_plane_neon
sub.w	r3, r0, r1                                
add.w	r2, r3, #0x4                              
sub.w	r3, r3, #0x1                              
vld1.32	{d0[0]}, [r3]                           
vld1.32	{d2[0]}, [r2:32], r1
vld1.8	{d0[4]}, [r3], r1                       
vld1.8	{d0[5]}, [r3], r1                       
vld1.8	{d0[6]}, [r3], r1                       
vld1.8	{d0[7]}, [r3], r1                       
add	r3, r1                                      
vld1.8	{d3[0]}, [r3], r1                       
vld1.8	{d3[1]}, [r3], r1                       
vld1.8	{d3[2]}, [r3], r1                       
vld1.8	{d3[3]}, [r3], r1                       
vaddl.u8	q8, d2, d3                            
vrev32.8	d0, d0                                
vtrn.32	d2, d3                                  
vsubl.u8	q2, d2, d0                            
adr	        r3, p16weight
vld1.16	{d0, d1}, [r3:128]                      
vmul.i16	d4, d4, d0                            
vmul.i16	d5, d5, d0                            
vpadd.i16	d4, d4, d5                            
vpaddl.s16	d4, d4                              
vshl.i32	d5, d4, #0x4                          
vadd.i32	d4, d4, d5                            
vrshrn.i32	d4, q2, #0x5                        
mov.w	r3, #0x0                                  
vtrn.16	d4, d5                                  
vadd.i16	d2, d4, d5                            
vshl.i16	d3, d2, #0x2                          
vrev64.16	d16, d16                              
vsub.i16	d3, d3, d2                            
vadd.i16	d16, d16, d0                          
vshl.i16	d2, d16, #0x4                         
vsub.i16	d2, d2, d3                            
vshl.i16	d3, d4, #0x3                          
vext.16	q0, q0, q0, #0x7                        
vsub.i16	d6, d5, d3                            
vmov.16	d0[0], r3                               
vmul.i16	q0, q0, d4[0]                         
vdup.16	q1, d2[0]                               
vdup.16	q2, d4[0]                               
vdup.16	q3, d6[0]                               
vshl.i16	q2, q2, #0x3                          
vadd.i16	q1, q1, q0                            
vadd.i16	q3, q3, q2                            
mov.w	r3, #0x8                                  
1:                                              
vqshrun.s16	d0, q1, #0x5                        
vadd.i16	q1, q1, q3                            
vst1.8	{d0}, [r0:64], r1                       
subs	r3, #0x1                                  
bne	1b                                          
bx	lr

.align 4
p16weight: .short 1,2,3,4,5,6,7,8

