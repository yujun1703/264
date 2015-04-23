/*
from h264_i386.h
*/

#include <stddef.h>
#include "libavcodec/cabac.h"
#include "cabac_x86.h"

extern const uint8_t ff_h264_norm_shift[512];
extern uint8_t ff_h264_mlps_state[4*64];
extern uint8_t ff_h264_lps_range[4*2*64];  ///< rangeTabLPS
extern const uint8_t last_coeff_flag_offset_8x8[63];

#define NAKED __declspec(naked)

#if HAVE_7REGS && !defined(BROKEN_RELOCATIONS)

int __declspec(naked) decode_significance_x86(CABACContext *c, int max_coeff,
							uint8_t *significant_coeff_ctx_base,
							int *index, x86_reg last_off)
{
	__asm {
	sub    esp,0x28                             
	mov    edx,DWORD PTR [esp+0x34]             
	mov    ecx,DWORD PTR [esp+0x30]             
	mov    eax,DWORD PTR [esp+0x2c]             
	mov    DWORD PTR [esp+0x20],edi             
	mov    DWORD PTR [esp+0x18],ebx             
	mov    edi,edx                              
	lea    ecx,[edx+ecx*1-0x1]                  
	mov    DWORD PTR [esp+0x14],ecx             
	mov    ecx,edx                              
	neg    ecx                                  
	mov    DWORD PTR [esp+0x10],ecx             
	mov    ecx,0x4                              
	sub    ecx,DWORD PTR [esp+0x38]             
	mov    DWORD PTR [esp+0x1c],esi             
	mov    DWORD PTR [esp+0x24],ebp             
	mov    DWORD PTR [esp+0xc],ecx              
	mov    esi,DWORD PTR [eax]                  
	mov    ebx,DWORD PTR [eax+0x4]              
decode_significance_x86_323:                 
	movzx  ebp,BYTE PTR [edi]                   
	mov    edx,ebx                              
	and    ebx,0xc0                             
	movzx  ebx,BYTE PTR [ff_h264_lps_range+ebp+ebx*2+0x0]         
                                             
	sub    edx,ebx                              
	mov    ecx,edx                              
	shl    edx,0x11                             
	sub    edx,esi                              
	sar    edx,0x1f                             
	sub    ebx,ecx                              
	and    ebx,edx                              
	add    ebx,ecx                              
	shl    ecx,0x11                             
	and    ecx,edx                              
	sub    esi,ecx                              
	xor    ebp,edx                              
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+ebx+0x0]               
	shl    ebx,cl                               
	movzx  edx,BYTE PTR [ff_h264_mlps_state+ebp+0x80]              
	shl    esi,cl                               
	mov    BYTE PTR [edi],dl                    
	test   si,si                                
	jne    decode_significance_x86_397          
	mov    ecx,DWORD PTR [eax+0x10]             
	add    DWORD PTR [eax+0x10],0x2             
	movzx  edx,WORD PTR [ecx]                   
	lea    ecx,[esi-0x1]                        
	xor    ecx,esi                              
	shr    ecx,0xf                              
	bswap  edx                                  
	shr    edx,0xf                              
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+ecx+0x0]               
	sub    edx,0xffff                           
	neg    ecx                                  
	add    ecx,0x7                              
	shl    edx,cl                               
	add    esi,edx                              
decode_significance_x86_397:                 
	test   ebp,0x1                              
	je     decode_significance_x86_438          
	add    edi,DWORD PTR [esp+0x3c]             
	movzx  ebp,BYTE PTR [edi]                   
	mov    edx,ebx                              
	and    ebx,0xc0                             
	movzx  ebx,BYTE PTR [ff_h264_lps_range+ebp+ebx*2+0x0]         
                                             
	sub    edx,ebx                              
	mov    ecx,edx                              
	shl    edx,0x11                             
	sub    edx,esi                              
	sar    edx,0x1f                             
	sub    ebx,ecx                              
	and    ebx,edx                              
	add    ebx,ecx                              
	shl    ecx,0x11                             
	and    ecx,edx                              
	sub    esi,ecx                              
	xor    ebp,edx                              
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+ebx+0x0]               
	shl    ebx,cl                               
	movzx  edx,BYTE PTR [ff_h264_mlps_state+ebp+0x80]              
	shl    esi,cl                               
	mov    BYTE PTR [edi],dl                    
	test   si,si                                
	jne    decode_significance_x86_41b          
	mov    ecx,DWORD PTR [eax+0x10]             
	add    DWORD PTR [eax+0x10],0x2             
	movzx  edx,WORD PTR [ecx]                   
	lea    ecx,[esi-0x1]                        
	xor    ecx,esi                              
	shr    ecx,0xf                              
	bswap  edx                                  
	shr    edx,0xf                              
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+ecx+0x0]               
	sub    edx,0xffff                           
	neg    ecx                                  
	add    ecx,0x7                              
	shl    edx,cl                               
	add    esi,edx                              
decode_significance_x86_41b:                 
	sub    edi,DWORD PTR [esp+0x3c]             
	mov    edx,DWORD PTR [esp+0x38]             
	mov    ecx,DWORD PTR [esp+0x10]             
	add    ecx,edi                              
	mov    DWORD PTR [edx],ecx                  
	test   ebp,0x1                              
	jne    decode_significance_x86_451          
	add    DWORD PTR [esp+0x38],0x4             
decode_significance_x86_438:                 
	add    edi,0x1                              
	cmp    edi,DWORD PTR [esp+0x14]             
	jb     decode_significance_x86_323          
	mov    edx,DWORD PTR [esp+0x38]             
	mov    ecx,DWORD PTR [esp+0x10]             
	add    ecx,edi                              
	mov    DWORD PTR [edx],ecx                  
decode_significance_x86_451:                 
	add    edx,DWORD PTR [esp+0xc]              
	shr    edx,0x2                              
	mov    DWORD PTR [eax],esi                  
	mov    DWORD PTR [eax+0x4],ebx              
	mov    eax,edx                              
	mov    ebx,DWORD PTR [esp+0x18]             
	mov    esi,DWORD PTR [esp+0x1c]             
	mov    edi,DWORD PTR [esp+0x20]             
	mov    ebp,DWORD PTR [esp+0x24]             
	add    esp,0x28                             
	ret
	}
}


int __declspec(naked) decode_significance_8x8_x86(CABACContext *c,
									   uint8_t *significant_coeff_ctx_base,
									   int *index, uint8_t *last_coeff_ctx_base, const uint8_t *sig_off)
{
	__asm {
	sub    esp,0x30                                     
	mov    edx,0x4                                      
	mov    eax,DWORD PTR [esp+0x34]                     
	sub    edx,DWORD PTR [esp+0x3c]                     
	mov    DWORD PTR [esp+0x28],edi                     
	mov    DWORD PTR [esp+0x20],ebx                     
	mov    DWORD PTR [esp+0x24],esi                     
	mov    DWORD PTR [esp+0x2c],ebp                     
	mov    DWORD PTR [esp+0x1c],edx                     
	mov    DWORD PTR [esp+0x18],0x0                     
                                                     
	mov    edx,DWORD PTR [eax+0x4]                      
	mov    ebx,DWORD PTR [eax]                          
	mov    DWORD PTR [esp+0xc],edx                      
	mov    edi,edx                                      
	mov    ebp,DWORD PTR [esp+0x18]                     
decode_significance_8x8_x86_4bb:                     
	mov    edx,DWORD PTR [esp+0x44]                     
	movzx  ebp,BYTE PTR [edx+ebp*1]                     
	add    ebp,DWORD PTR [esp+0x38]                     
	movzx  esi,BYTE PTR [ebp+0x0]                       
	mov    edx,edi                                      
	and    edi,0xc0                                     
	movzx  edi,BYTE PTR [ff_h264_lps_range+esi+edi*2+0x0]                 
                                                     
	sub    edx,edi                                      
	mov    ecx,edx                                      
	shl    edx,0x11                                     
	sub    edx,ebx                                      
	sar    edx,0x1f                                     
	sub    edi,ecx                                      
	and    edi,edx                                      
	add    edi,ecx                                      
	shl    ecx,0x11                                     
	and    ecx,edx                                      
	sub    ebx,ecx                                      
	xor    esi,edx                                      
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+edi+0x0]                       
	shl    edi,cl                                       
	movzx  edx,BYTE PTR [ff_h264_mlps_state+esi+0x80]                      
	shl    ebx,cl                                       
	mov    BYTE PTR [ebp+0x0],dl                        
	test   bx,bx                                        
	jne    decode_significance_8x8_x86_53d              
	mov    ecx,DWORD PTR [eax+0x10]                     
	add    DWORD PTR [eax+0x10],0x2                     
	movzx  edx,WORD PTR [ecx]                           
	lea    ecx,[ebx-0x1]                                
	xor    ecx,ebx                                      
	shr    ecx,0xf                                      
	bswap  edx                                          
	shr    edx,0xf                                      
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+ecx+0x0]                       
	sub    edx,0xffff                                   
	neg    ecx                                          
	add    ecx,0x7                                      
	shl    edx,cl                                       
	add    ebx,edx                                      
decode_significance_8x8_x86_53d:                     
	mov    ebp,DWORD PTR [esp+0x18]                     
	test   esi,0x1                                      
	je     decode_significance_8x8_x86_5e5              
	movzx  ebp,BYTE PTR [last_coeff_flag_offset_8x8+ebp+0x0]                       
	add    ebp,DWORD PTR [esp+0x40]                     
	movzx  esi,BYTE PTR [ebp+0x0]                       
	mov    edx,edi                                      
	and    edi,0xc0                                     
	movzx  edi,BYTE PTR [ff_h264_lps_range+esi+edi*2+0x0]                 
                                                     
	sub    edx,edi                                      
	mov    ecx,edx                                      
	shl    edx,0x11                                     
	sub    edx,ebx                                      
	sar    edx,0x1f                                     
	sub    edi,ecx                                      
	and    edi,edx                                      
	add    edi,ecx                                      
	shl    ecx,0x11                                     
	and    ecx,edx                                      
	sub    ebx,ecx                                      
	xor    esi,edx                                      
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+edi+0x0]                       
	shl    edi,cl                                       
	movzx  edx,BYTE PTR [ff_h264_mlps_state+esi+0x80]                      
	shl    ebx,cl                                       
	mov    BYTE PTR [ebp+0x0],dl                        
	test   bx,bx                                        
	jne    decode_significance_8x8_x86_5ce              
	mov    ecx,DWORD PTR [eax+0x10]                     
	add    DWORD PTR [eax+0x10],0x2                     
	movzx  edx,WORD PTR [ecx]                           
	lea    ecx,[ebx-0x1]                                
	xor    ecx,ebx                                      
	shr    ecx,0xf                                      
	bswap  edx                                          
	shr    edx,0xf                                      
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+ecx+0x0]                       
	sub    edx,0xffff                                   
	neg    ecx                                          
	add    ecx,0x7                                      
	shl    edx,cl                                       
	add    ebx,edx                                      
decode_significance_8x8_x86_5ce:                     
	mov    edx,DWORD PTR [esp+0x3c]                     
	mov    ebp,DWORD PTR [esp+0x18]                     
	mov    DWORD PTR [edx],ebp                          
	test   esi,0x1                                      
	jne    decode_significance_8x8_x86_5fb              
	add    DWORD PTR [esp+0x3c],0x4                     
decode_significance_8x8_x86_5e5:                     
	add    ebp,0x1                                      
	mov    DWORD PTR [esp+0x18],ebp                     
	cmp    ebp,0x3f                                     
	jb     decode_significance_8x8_x86_4bb              
	mov    edx,DWORD PTR [esp+0x3c]                     
	mov    DWORD PTR [edx],ebp                          
decode_significance_8x8_x86_5fb:                     
	add    edx,DWORD PTR [esp+0x1c]                     
	shr    edx,0x2                                      
	mov    DWORD PTR [eax],ebx                          
	mov    DWORD PTR [eax+0x4],edi                      
	mov    eax,edx                                      
	mov    ebx,DWORD PTR [esp+0x20]                     
	mov    esi,DWORD PTR [esp+0x24]                     
	mov    edi,DWORD PTR [esp+0x28]                     
	mov    ebp,DWORD PTR [esp+0x2c]                     
	add    esp,0x30                                     
	ret       
	}
}
#endif