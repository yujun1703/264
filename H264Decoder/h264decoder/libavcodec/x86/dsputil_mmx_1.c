#include "x86_opt.h"
#include "dsputil_mmx.h"


//#define NAKED __declspec(naked)

NAKED void put_no_rnd_pixels8_x2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                           
			mov    DWORD PTR [esp],esi               
			mov    ecx,DWORD PTR [esp+0x18]          
		mov    DWORD PTR [esp+0x4],edi           
			mov    esi,DWORD PTR [esp+0x10]          
		mov    edi,DWORD PTR [esp+0xc]           
		pcmpeqd mm6,mm6                          
			paddb  mm6,mm6                           
			mov    edx,DWORD PTR [esp+0x14]          
		lea    eax,[edx+edx*1]                   
		nop                                      
			
put_no_rnd_pixels8_x2_mmx_28:            
		movq   mm0,QWORD PTR [esi]               
		movq   mm1,QWORD PTR [esi+0x1]           
		movq   mm2,QWORD PTR [esi+edx*1]         
		movq   mm3,QWORD PTR [esi+edx*1+0x1]     
		movq   mm4,mm0                           
			movq   mm5,mm2                           
			pand   mm4,mm1                           
			pand   mm5,mm3                           
			pxor   mm1,mm0                           
			pxor   mm3,mm2                           
			pand   mm1,mm6                           
			pand   mm3,mm6                           
			psrlq  mm1,0x1                           
			psrlq  mm3,0x1                           
			paddb  mm4,mm1                           
			paddb  mm5,mm3                           
			movq   QWORD PTR [edi],mm4               
			movq   QWORD PTR [edi+edx*1],mm5         
			add    esi,eax                           
			add    edi,eax                           
			movq   mm0,QWORD PTR [esi]               
		movq   mm1,QWORD PTR [esi+0x1]           
		movq   mm2,QWORD PTR [esi+edx*1]         
		movq   mm3,QWORD PTR [esi+edx*1+0x1]     
		movq   mm4,mm0                           
			movq   mm5,mm2                           
			pand   mm4,mm1                           
			pand   mm5,mm3                           
			pxor   mm1,mm0                           
			pxor   mm3,mm2                           
			pand   mm1,mm6                           
			pand   mm3,mm6                           
			psrlq  mm1,0x1                           
			psrlq  mm3,0x1                           
			paddb  mm4,mm1                           
			paddb  mm5,mm3                           
			movq   QWORD PTR [edi],mm4               
			movq   QWORD PTR [edi+edx*1],mm5         
			add    esi,eax                           
			add    edi,eax                           
			sub    ecx,0x4                           
			jne    put_no_rnd_pixels8_x2_mmx_28      
			mov    esi,DWORD PTR [esp]               
		mov    edi,DWORD PTR [esp+0x4]           
		add    esp,0x8                           
			ret                                      

	}
}


void av_unused put_no_rnd_pixels8_l2_mmx(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)// 2
{
	
}

NAKED  void put_no_rnd_pixels16_x2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 3
{
	__asm {
		sub    esp,0x8                               
			mov    DWORD PTR [esp],esi                   
			mov    ecx,DWORD PTR [esp+0x18]              
		mov    DWORD PTR [esp+0x4],edi               
			mov    esi,DWORD PTR [esp+0x10]              
		mov    edi,DWORD PTR [esp+0xc]               
		pcmpeqd mm6,mm6                              
			paddb  mm6,mm6                               
			mov    edx,DWORD PTR [esp+0x14]              
		lea    eax,[edx+edx*1]                       
		nop                                          
			
put_no_rnd_pixels16_x2_mmx_e8:               
		movq   mm0,QWORD PTR [esi]                   
		movq   mm1,QWORD PTR [esi+0x1]               
		movq   mm2,QWORD PTR [esi+edx*1]             
		movq   mm3,QWORD PTR [esi+edx*1+0x1]         
		movq   mm4,mm0                               
			movq   mm5,mm2                               
			pand   mm4,mm1                               
			pand   mm5,mm3                               
			pxor   mm1,mm0                               
			pxor   mm3,mm2                               
			pand   mm1,mm6                               
			pand   mm3,mm6                               
			psrlq  mm1,0x1                               
			psrlq  mm3,0x1                               
			paddb  mm4,mm1                               
			paddb  mm5,mm3                               
			movq   QWORD PTR [edi],mm4                   
			movq   QWORD PTR [edi+edx*1],mm5             
			movq   mm0,QWORD PTR [esi+0x8]               
		movq   mm1,QWORD PTR [esi+0x9]               
		movq   mm2,QWORD PTR [esi+edx*1+0x8]         
		movq   mm3,QWORD PTR [esi+edx*1+0x9]         
		movq   mm4,mm0                               
			movq   mm5,mm2                               
			pand   mm4,mm1                               
			pand   mm5,mm3                               
			pxor   mm1,mm0                               
			pxor   mm3,mm2                               
			pand   mm1,mm6                               
			pand   mm3,mm6                               
			psrlq  mm1,0x1                               
			psrlq  mm3,0x1                               
			paddb  mm4,mm1                               
			paddb  mm5,mm3                               
			movq   QWORD PTR [edi+0x8],mm4               
			movq   QWORD PTR [edi+edx*1+0x8],mm5         
			add    esi,eax                               
			add    edi,eax                               
			movq   mm0,QWORD PTR [esi]                   
		movq   mm1,QWORD PTR [esi+0x1]               
		movq   mm2,QWORD PTR [esi+edx*1]             
		movq   mm3,QWORD PTR [esi+edx*1+0x1]         
		movq   mm4,mm0                               
			movq   mm5,mm2                               
			pand   mm4,mm1                               
			pand   mm5,mm3                               
			pxor   mm1,mm0                               
			pxor   mm3,mm2                               
			pand   mm1,mm6                               
			pand   mm3,mm6                               
			psrlq  mm1,0x1                               
			psrlq  mm3,0x1                               
			paddb  mm4,mm1                               
			paddb  mm5,mm3                               
			movq   QWORD PTR [edi],mm4                   
			movq   QWORD PTR [edi+edx*1],mm5             
			movq   mm0,QWORD PTR [esi+0x8]               
		movq   mm1,QWORD PTR [esi+0x9]               
		movq   mm2,QWORD PTR [esi+edx*1+0x8]         
		movq   mm3,QWORD PTR [esi+edx*1+0x9]         
		movq   mm4,mm0                               
			movq   mm5,mm2                               
			pand   mm4,mm1                               
			pand   mm5,mm3                               
			pxor   mm1,mm0                               
			pxor   mm3,mm2                               
			pand   mm1,mm6                               
			pand   mm3,mm6                               
			psrlq  mm1,0x1                               
			psrlq  mm3,0x1                               
			paddb  mm4,mm1                               
			paddb  mm5,mm3                               
			movq   QWORD PTR [edi+0x8],mm4               
			movq   QWORD PTR [edi+edx*1+0x8],mm5         
			add    esi,eax                               
			add    edi,eax                               
			sub    ecx,0x4                               
			jne    put_no_rnd_pixels16_x2_mmx_e8         
			mov    esi,DWORD PTR [esp]                   
		mov    edi,DWORD PTR [esp+0x4]               
		add    esp,0x8                               
			ret
	}	
}

void av_unused put_no_rnd_pixels16_l2_mmx(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)// 4
{
	
}

NAKED  void put_no_rnd_pixels8_y2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 5
{
	__asm {
		sub    esp,0x8                       
			mov    DWORD PTR [esp],esi           
			mov    ecx,DWORD PTR [esp+0x18]      
		mov    DWORD PTR [esp+0x4],edi       
			mov    esi,DWORD PTR [esp+0x10]      
		mov    edi,DWORD PTR [esp+0xc]       
		pcmpeqd mm6,mm6                      
			paddb  mm6,mm6                       
			mov    edx,DWORD PTR [esp+0x14]      
		lea    eax,[edx+edx*1]               
		movq   mm0,QWORD PTR [esi]           
		xchg   ax,ax                         
put_no_rnd_pixels8_y2_mmx_228:       
		movq   mm1,QWORD PTR [esi+edx*1]     
		movq   mm2,QWORD PTR [esi+eax*1]     
		movq   mm4,mm1                       
			movq   mm5,mm2                       
			pand   mm4,mm0                       
			pand   mm5,mm1                       
			pxor   mm0,mm1                       
			pxor   mm1,mm2                       
			pand   mm0,mm6                       
			pand   mm1,mm6                       
			psrlq  mm0,0x1                       
			psrlq  mm1,0x1                       
			paddb  mm4,mm0                       
			paddb  mm5,mm1                       
			movq   QWORD PTR [edi],mm4           
			movq   QWORD PTR [edi+edx*1],mm5     
			add    esi,eax                       
			add    edi,eax                       
			movq   mm1,QWORD PTR [esi+edx*1]     
		movq   mm0,QWORD PTR [esi+eax*1]     
		movq   mm4,mm1                       
			movq   mm5,mm0                       
			pand   mm4,mm2                       
			pand   mm5,mm1                       
			pxor   mm2,mm1                       
			pxor   mm1,mm0                       
			pand   mm2,mm6                       
			pand   mm1,mm6                       
			psrlq  mm2,0x1                       
			psrlq  mm1,0x1                       
			paddb  mm4,mm2                       
			paddb  mm5,mm1                       
			movq   QWORD PTR [edi],mm4           
			movq   QWORD PTR [edi+edx*1],mm5     
			add    esi,eax                       
			add    edi,eax                       
			sub    ecx,0x4                       
			jne    put_no_rnd_pixels8_y2_mmx_228 
			mov    esi,DWORD PTR [esp]           
		mov    edi,DWORD PTR [esp+0x4]       
		add    esp,0x8                       
			ret                                  

	}
}

NAKED  void put_no_rnd_pixels8_xy2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 6
{
	__asm {
		sub    esp,0x8                           
			mov    DWORD PTR [esp],esi               
			mov    edx,DWORD PTR [esp+0x18]          
		mov    DWORD PTR [esp+0x4],edi           
			mov    esi,DWORD PTR [esp+0x10]          
		pxor   mm7,mm7                           
			pcmpeqd mm6,mm6                          
			psrlw  mm6,0xf                           
			mov    ecx,DWORD PTR [esp+0x14]          
		mov    edi,DWORD PTR [esp+0xc]           
		movq   mm0,QWORD PTR [esi]               
		movq   mm4,QWORD PTR [esi+0x1]           
		movq   mm1,mm0                           
			movq   mm5,mm4                           
			punpcklbw mm0,mm7                        
			punpcklbw mm4,mm7                        
			punpckhbw mm1,mm7                        
			punpckhbw mm5,mm7                        
			paddusw mm4,mm0                          
			paddusw mm5,mm1                          
			xor    eax,eax                           
			add    esi,ecx                           
			nop                                      
put_no_rnd_pixels8_xy2_mmx_2f8:          
		movq   mm0,QWORD PTR [esi+eax*1]         
		movq   mm2,QWORD PTR [esi+eax*1+0x1]     
		movq   mm1,mm0                           
			movq   mm3,mm2                           
			punpcklbw mm0,mm7                        
			punpcklbw mm2,mm7                        
			punpckhbw mm1,mm7                        
			punpckhbw mm3,mm7                        
			paddusw mm0,mm2                          
			paddusw mm1,mm3                          
			paddusw mm4,mm6                          
			paddusw mm5,mm6                          
			paddusw mm4,mm0                          
			paddusw mm5,mm1                          
			psrlw  mm4,0x2                           
			psrlw  mm5,0x2                           
			packuswb mm4,mm5                         
			movq   QWORD PTR [edi+eax*1],mm4         
			add    eax,ecx                           
			movq   mm2,QWORD PTR [esi+eax*1]         
		movq   mm4,QWORD PTR [esi+eax*1+0x1]     
		movq   mm3,mm2                           
			movq   mm5,mm4                           
			punpcklbw mm2,mm7                        
			punpcklbw mm4,mm7                        
			punpckhbw mm3,mm7                        
			punpckhbw mm5,mm7                        
			paddusw mm4,mm2                          
			paddusw mm5,mm3                          
			paddusw mm0,mm6                          
			paddusw mm1,mm6                          
			paddusw mm0,mm4                          
			paddusw mm1,mm5                          
			psrlw  mm0,0x2                           
			psrlw  mm1,0x2                           
			packuswb mm0,mm1                         
			movq   QWORD PTR [edi+eax*1],mm0         
			add    eax,ecx                           
			sub    edx,0x2                           
			jne    put_no_rnd_pixels8_xy2_mmx_2f8    
			mov    esi,DWORD PTR [esp]               
		mov    edi,DWORD PTR [esp+0x4]           
		add    esp,0x8                           
			ret
	}
}

// avg_pixels
void av_unused avg_no_rnd_pixels4_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 7
{

}

// in case more speed is needed - unroling would certainly help
NAKED  void avg_no_rnd_pixels8_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 8
{
	__asm {
		push   esi                         
			push   ebx                         
			mov    ecx,DWORD PTR [esp+0xc]     
		mov    esi,DWORD PTR [esp+0x10]    
		mov    ebx,DWORD PTR [esp+0x14]    
		mov    edx,DWORD PTR [esp+0x18]    
		pcmpeqd mm6,mm6                    
			paddb  mm6,mm6                     
			xor    eax,eax                     
			lea    esi,[esi+0x0]               
no_rnd_pixels8_mmx_3b0:            
		movq   mm0,QWORD PTR [ecx+eax*1]   
		movq   mm1,QWORD PTR [esi+eax*1]   
		movq   mm2,mm0                     
			por    mm2,mm1                     
			pxor   mm1,mm0                     
			pand   mm1,mm6                     
			psrlq  mm1,0x1                     
			psubb  mm2,mm1                     
			movq   QWORD PTR [ecx+eax*1],mm2   
			add    eax,ebx                     
			sub    edx,0x1                     
			jne    no_rnd_pixels8_mmx_3b0      
			pop    ebx                         
			pop    esi                         
			ret                                

	}
}

NAKED  void avg_no_rnd_pixels16_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 9
{
	__asm {
		push   esi                             
			push   ebx                             
			mov    ecx,DWORD PTR [esp+0xc]         
		mov    esi,DWORD PTR [esp+0x10]        
		mov    ebx,DWORD PTR [esp+0x14]        
		mov    edx,DWORD PTR [esp+0x18]        
		pcmpeqd mm6,mm6                        
			paddb  mm6,mm6                         
			xor    eax,eax                         
			lea    esi,[esi+0x0]                   
avg_no_rnd_pixels16_mmx_400:           
		movq   mm0,QWORD PTR [ecx+eax*1]       
		movq   mm1,QWORD PTR [esi+eax*1]       
		movq   mm2,mm0                         
			por    mm2,mm1                         
			pxor   mm1,mm0                         
			pand   mm1,mm6                         
			psrlq  mm1,0x1                         
			psubb  mm2,mm1                         
			movq   QWORD PTR [ecx+eax*1],mm2       
			movq   mm0,QWORD PTR [ecx+eax*1+0x8]   
		movq   mm1,QWORD PTR [esi+eax*1+0x8]   
		movq   mm2,mm0                         
			por    mm2,mm1                         
			pxor   mm1,mm0                         
			pand   mm1,mm6                         
			psrlq  mm1,0x1                         
			psubb  mm2,mm1                         
			movq   QWORD PTR [ecx+eax*1+0x8],mm2   
			add    eax,ebx                         
			sub    edx,0x1                         
			jne    avg_no_rnd_pixels16_mmx_400     
			pop    ebx                             
			pop    esi                             
			ret                                    

	}
}

NAKED  void avg_no_rnd_pixels8_x2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 10
{
	__asm {
		push   esi                            
			push   ebx                            
			mov    ecx,DWORD PTR [esp+0xc]        
		mov    esi,DWORD PTR [esp+0x10]       
		mov    ebx,DWORD PTR [esp+0x14]       
		mov    edx,DWORD PTR [esp+0x18]       
		pcmpeqd mm6,mm6                       
			paddb  mm6,mm6                        
			xor    eax,eax                        
			lea    esi,[esi+0x0]                  
avg_no_rnd_pixels8_x2_mmx_470:        
		movq   mm0,QWORD PTR [esi+eax*1]      
		movq   mm1,QWORD PTR [esi+eax*1+0x1]  
		movq   mm3,QWORD PTR [ecx+eax*1]      
		movq   mm2,mm0                        
			pand   mm2,mm1                        
			pxor   mm1,mm0                        
			pand   mm1,mm6                        
			psrlq  mm1,0x1                        
			paddb  mm2,mm1                        
			movq   mm0,mm3                        
			por    mm0,mm2                        
			pxor   mm2,mm3                        
			pand   mm2,mm6                        
			psrlq  mm2,0x1                        
			psubb  mm0,mm2                        
			movq   QWORD PTR [ecx+eax*1],mm0      
			add    eax,ebx                        
			sub    edx,0x1                        
			jne    avg_no_rnd_pixels8_x2_mmx_470  
			pop    ebx                            
			pop    esi                            
			ret                                   

	}
}

av_unused void avg_no_rnd_pixels8_l2_mmx(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)// 11
{

}

NAKED  void avg_no_rnd_pixels16_x2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 12
{
	__asm {
		push   esi                                
			push   ebx                                
			mov    ecx,DWORD PTR [esp+0xc]            
		mov    esi,DWORD PTR [esp+0x10]           
		mov    ebx,DWORD PTR [esp+0x14]           
		mov    edx,DWORD PTR [esp+0x18]           
		pcmpeqd mm6,mm6                           
			paddb  mm6,mm6                            
			xor    eax,eax                            
			lea    esi,[esi+0x0]                      
avg_no_rnd_pixels16_x2_mmx_4e0:           
		movq   mm0,QWORD PTR [esi+eax*1]          
		movq   mm1,QWORD PTR [esi+eax*1+0x1]      
		movq   mm3,QWORD PTR [ecx+eax*1]          
		movq   mm2,mm0                            
			pand   mm2,mm1                            
			pxor   mm1,mm0                            
			pand   mm1,mm6                            
			psrlq  mm1,0x1                            
			paddb  mm2,mm1                            
			movq   mm0,mm3                            
			por    mm0,mm2                            
			pxor   mm2,mm3                            
			pand   mm2,mm6                            
			psrlq  mm2,0x1                            
			psubb  mm0,mm2                            
			movq   QWORD PTR [ecx+eax*1],mm0          
			movq   mm0,QWORD PTR [esi+eax*1+0x8]      
		movq   mm1,QWORD PTR [esi+eax*1+0x9]      
		movq   mm3,QWORD PTR [ecx+eax*1+0x8]      
		movq   mm2,mm0                            
			pand   mm2,mm1                            
			pxor   mm1,mm0                            
			pand   mm1,mm6                            
			psrlq  mm1,0x1                            
			paddb  mm2,mm1                            
			movq   mm0,mm3                            
			por    mm0,mm2                            
			pxor   mm2,mm3                            
			pand   mm2,mm6                            
			psrlq  mm2,0x1                            
			psubb  mm0,mm2                            
			movq   QWORD PTR [ecx+eax*1+0x8],mm0      
			add    eax,ebx                            
			sub    edx,0x1                            
			jne    avg_no_rnd_pixels16_x2_mmx_4e0     
			pop    ebx                                
			pop    esi                                
			ret                                       

	}
}

av_unused void avg_no_rnd_pixels16_l2_mmx(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)//13
{

}

NAKED  void avg_no_rnd_pixels8_y2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)//14
{
	__asm {
		sub    esp,0x8                       
			mov    DWORD PTR [esp],esi           
			mov    ecx,DWORD PTR [esp+0x18]      
		mov    DWORD PTR [esp+0x4],edi       
			mov    esi,DWORD PTR [esp+0x10]      
		mov    edi,DWORD PTR [esp+0xc]       
		pcmpeqd mm6,mm6                      
			paddb  mm6,mm6                       
			mov    edx,DWORD PTR [esp+0x14]      
		lea    eax,[edx+edx*1]               
		movq   mm0,QWORD PTR [esi]           
		xchg   ax,ax                         
avg_no_rnd_pixels8_y2_mmx_588:       
		movq   mm1,QWORD PTR [esi+edx*1]     
		movq   mm2,QWORD PTR [esi+eax*1]     
		movq   mm4,mm1                       
			movq   mm5,mm2                       
			pand   mm4,mm0                       
			pand   mm5,mm1                       
			pxor   mm0,mm1                       
			pxor   mm1,mm2                       
			pand   mm0,mm6                       
			pand   mm1,mm6                       
			psrlq  mm0,0x1                       
			psrlq  mm1,0x1                       
			paddb  mm4,mm0                       
			paddb  mm5,mm1                       
			movq   mm3,QWORD PTR [edi]           
		movq   mm0,mm3                       
			por    mm0,mm4                       
			pxor   mm4,mm3                       
			pand   mm4,mm6                       
			psrlq  mm4,0x1                       
			psubb  mm0,mm4                       
			movq   mm3,QWORD PTR [edi+edx*1]     
		movq   mm1,mm3                       
			por    mm1,mm5                       
			pxor   mm5,mm3                       
			pand   mm5,mm6                       
			psrlq  mm5,0x1                       
			psubb  mm1,mm5                       
			movq   QWORD PTR [edi],mm0           
			movq   QWORD PTR [edi+edx*1],mm1     
			add    esi,eax                       
			add    edi,eax                       
			movq   mm1,QWORD PTR [esi+edx*1]     
		movq   mm0,QWORD PTR [esi+eax*1]     
		movq   mm4,mm1                       
			movq   mm5,mm0                       
			pand   mm4,mm2                       
			pand   mm5,mm1                       
			pxor   mm2,mm1                       
			pxor   mm1,mm0                       
			pand   mm2,mm6                       
			pand   mm1,mm6                       
			psrlq  mm2,0x1                       
			psrlq  mm1,0x1                       
			paddb  mm4,mm2                       
			paddb  mm5,mm1                       
			movq   mm3,QWORD PTR [edi]           
		movq   mm2,mm3                       
			por    mm2,mm4                       
			pxor   mm4,mm3                       
			pand   mm4,mm6                       
			psrlq  mm4,0x1                       
			psubb  mm2,mm4                       
			movq   mm3,QWORD PTR [edi+edx*1]     
		movq   mm1,mm3                       
			por    mm1,mm5                       
			pxor   mm5,mm3                       
			pand   mm5,mm6                       
			psrlq  mm5,0x1                       
			psubb  mm1,mm5                       
			movq   QWORD PTR [edi],mm2           
			movq   QWORD PTR [edi+edx*1],mm1     
			add    esi,eax                       
			add    edi,eax                       
			sub    ecx,0x4                       
			jne    avg_no_rnd_pixels8_y2_mmx_588 
			mov    esi,DWORD PTR [esp]           
		mov    edi,DWORD PTR [esp+0x4]       
		add    esp,0x8                       
			ret                                  

	}
}

// this routine is 'slightly' suboptimal but mostly unused
NAKED  void avg_no_rnd_pixels8_xy2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)// 15
{
	__asm {
		sub    esp,0x8                         
			mov    DWORD PTR [esp],esi             
			mov    edx,DWORD PTR [esp+0x18]        
		mov    DWORD PTR [esp+0x4],edi         
			mov    esi,DWORD PTR [esp+0x10]        
		pxor   mm7,mm7                         
			pcmpeqd mm6,mm6                        
			psrlw  mm6,0xf                         
			mov    ecx,DWORD PTR [esp+0x14]        
		mov    edi,DWORD PTR [esp+0xc]         
		movq   mm0,QWORD PTR [esi]             
		movq   mm4,QWORD PTR [esi+0x1]         
		movq   mm1,mm0                         
			movq   mm5,mm4                         
			punpcklbw mm0,mm7                      
			punpcklbw mm4,mm7                      
			punpckhbw mm1,mm7                      
			punpckhbw mm5,mm7                      
			paddusw mm4,mm0                        
			paddusw mm5,mm1                        
			xor    eax,eax                         
			add    esi,ecx                         
			nop                                    
avg_no_rnd_pixels8_xy2_mmx_a38:        
		movq   mm0,QWORD PTR [esi+eax*1]       
		movq   mm2,QWORD PTR [esi+eax*1+0x1]   
		movq   mm1,mm0                         
			movq   mm3,mm2                         
			punpcklbw mm0,mm7                      
			punpcklbw mm2,mm7                      
			punpckhbw mm1,mm7                      
			punpckhbw mm3,mm7                      
			paddusw mm0,mm2                        
			paddusw mm1,mm3                        
			paddusw mm4,mm6                        
			paddusw mm5,mm6                        
			paddusw mm4,mm0                        
			paddusw mm5,mm1                        
			psrlw  mm4,0x2                         
			psrlw  mm5,0x2                         
			movq   mm3,QWORD PTR [edi+eax*1]       
		packuswb mm4,mm5                       
			pcmpeqd mm2,mm2                        
			paddb  mm2,mm2                         
			movq   mm5,mm3                         
			por    mm5,mm4                         
			pxor   mm4,mm3                         
			pand   mm4,mm2                         
			psrlq  mm4,0x1                         
			psubb  mm5,mm4                         
			movq   QWORD PTR [edi+eax*1],mm5       
			add    eax,ecx                         
			movq   mm2,QWORD PTR [esi+eax*1]       
		movq   mm4,QWORD PTR [esi+eax*1+0x1]   
		movq   mm3,mm2                         
			movq   mm5,mm4                         
			punpcklbw mm2,mm7                      
			punpcklbw mm4,mm7                      
			punpckhbw mm3,mm7                      
			punpckhbw mm5,mm7                      
			paddusw mm4,mm2                        
			paddusw mm5,mm3                        
			paddusw mm0,mm6                        
			paddusw mm1,mm6                        
			paddusw mm0,mm4                        
			paddusw mm1,mm5                        
			psrlw  mm0,0x2                         
			psrlw  mm1,0x2                         
			movq   mm3,QWORD PTR [edi+eax*1]       
		packuswb mm0,mm1                       
			pcmpeqd mm2,mm2                        
			paddb  mm2,mm2                         
			movq   mm1,mm3                         
			por    mm1,mm0                         
			pxor   mm0,mm3                         
			pand   mm0,mm2                         
			psrlq  mm0,0x1                         
			psubb  mm1,mm0                         
			movq   QWORD PTR [edi+eax*1],mm1       
			add    eax,ecx                         
			sub    edx,0x2                         
			jne    avg_no_rnd_pixels8_xy2_mmx_a38  
			mov    esi,DWORD PTR [esp]             
		mov    edi,DWORD PTR [esp+0x4]         
		add    esp,0x8                         
			ret                                    

	}
}

//FIXME optimize
void put_no_rnd_pixels16_y2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	put_no_rnd_pixels8_y2_mmx(block  , pixels  , line_size, h);
	put_no_rnd_pixels8_y2_mmx(block+8, pixels+8, line_size, h);
}

void put_no_rnd_pixels16_xy2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	put_no_rnd_pixels8_xy2_mmx(block  , pixels  , line_size, h);
	put_no_rnd_pixels8_xy2_mmx(block+8, pixels+8, line_size, h);
}

////void avg_no_rnd_pixels16_y2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)
////{
////	avg_no_rnd_pixels8_y2_mmx(block  , pixels  , line_size, h);
////	avg_no_rnd_pixels8_y2_mmx(block+8, pixels+8, line_size, h);
////}

////void avg_no_rnd_pixels16_xy2_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h)
////{
////	avg_no_rnd_pixels8_xy2_mmx(block  , pixels  , line_size, h);
////	avg_no_rnd_pixels8_xy2_mmx(block+8, pixels+8, line_size, h);
////}





















