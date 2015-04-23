#include "..\dsputil.h"
#include "dsputil_mmx.h"

typedef unsigned char uint8_t;
typedef char int8_t;
typedef short int16_t;

//extern const xmm_reg ff_pw_16;
//extern const xmm_reg ff_pw_5;

void __declspec(naked) put_pixels4_l2_3dnow(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                    
	mov    DWORD PTR [esp],ebx        
	mov    edx,DWORD PTR [esp+0x10]   
	mov    DWORD PTR [esp+0x4],esi    
	mov    eax,DWORD PTR [esp+0x14]   
	mov    DWORD PTR [esp+0x8],edi    
	mov    ecx,DWORD PTR [esp+0x18]   
	mov    ebx,DWORD PTR [esp+0x24]   
	mov    esi,DWORD PTR [esp+0x20]   
	mov    edi,DWORD PTR [esp+0x1c]   
	test   ebx,0x1                    
	je     put_pixels4_l2_3dnowFlag   
	movd   mm0,DWORD PTR [eax]        
	movd   mm1,DWORD PTR [ecx]        
	add    eax,esi                    
	add    ecx,0x4                    
	pavgusb mm0,mm1                   
	movd   DWORD PTR [edx],mm0        
	add    edx,edi                    
	dec    ebx                        
put_pixels4_l2_3dnowFlag:          
	movd   mm0,DWORD PTR [eax]        
	add    eax,esi                    
	movd   mm1,DWORD PTR [eax]        
	movd   mm2,DWORD PTR [ecx]        
	movd   mm3,DWORD PTR [ecx+0x4]    
	add    eax,esi                    
	pavgusb mm0,mm2                   
	pavgusb mm1,mm3                   
	movd   DWORD PTR [edx],mm0        
	add    edx,edi                    
	movd   DWORD PTR [edx],mm1        
	add    edx,edi                    
	movd   mm0,DWORD PTR [eax]        
	add    eax,esi                    
	movd   mm1,DWORD PTR [eax]        
	movd   mm2,DWORD PTR [ecx+0x8]    
	movd   mm3,DWORD PTR [ecx+0xc]    
	add    eax,esi                    
	pavgusb mm0,mm2                   
	pavgusb mm1,mm3                   
	movd   DWORD PTR [edx],mm0        
	add    edx,edi                    
	movd   DWORD PTR [edx],mm1        
	add    edx,edi                    
	add    ecx,0x10                   
	sub    ebx,0x4                    
	jne    put_pixels4_l2_3dnowFlag   
	mov    ebx,DWORD PTR [esp]        
	mov    esi,DWORD PTR [esp+0x4]    
	mov    edi,DWORD PTR [esp+0x8]    
	add    esp,0xc                    
	ret
	}
}
void __declspec(naked) put_pixels8_l2_3dnow(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                   
	mov    DWORD PTR [esp],ebx       
	mov    edx,DWORD PTR [esp+0x10]  
	mov    DWORD PTR [esp+0x4],esi   
	mov    eax,DWORD PTR [esp+0x14]  
	mov    DWORD PTR [esp+0x8],edi   
	mov    ecx,DWORD PTR [esp+0x18]  
	mov    ebx,DWORD PTR [esp+0x24]  
	mov    esi,DWORD PTR [esp+0x20]  
	mov    edi,DWORD PTR [esp+0x1c]  
	test   ebx,0x1                   
	je     put_pixels8_l2_3dnowflag  
	movq   mm0,QWORD PTR [eax]       
	movq   mm1,QWORD PTR [ecx]       
	add    eax,esi                   
	add    ecx,0x8                   
	pavgusb mm0,mm1                  
	movq   QWORD PTR [edx],mm0       
	add    edx,edi                   
	dec    ebx                       
put_pixels8_l2_3dnowflag:         
	movq   mm0,QWORD PTR [eax]       
	add    eax,esi                   
	movq   mm1,QWORD PTR [eax]       
	add    eax,esi                   
	pavgusb mm0,QWORD PTR [ecx]      
	pavgusb mm1,QWORD PTR [ecx+0x8]  
	movq   QWORD PTR [edx],mm0       
	add    edx,edi                   
	movq   QWORD PTR [edx],mm1       
	add    edx,edi                   
	movq   mm0,QWORD PTR [eax]       
	add    eax,esi                   
	movq   mm1,QWORD PTR [eax]       
	add    eax,esi                   
	pavgusb mm0,QWORD PTR [ecx+0x10] 
	pavgusb mm1,QWORD PTR [ecx+0x18] 
	movq   QWORD PTR [edx],mm0       
	add    edx,edi                   
	movq   QWORD PTR [edx],mm1       
	add    edx,edi                   
	add    ecx,0x20                  
	sub    ebx,0x4                   
	jne    put_pixels8_l2_3dnowflag  
	mov    ebx,DWORD PTR [esp]       
	mov    esi,DWORD PTR [esp+0x4]   
	mov    edi,DWORD PTR [esp+0x8]   
	add    esp,0xc                   
	ret
	}
}

void __declspec(naked) put_pixels16_l2_3dnow(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                      
	mov    DWORD PTR [esp],ebx          
	mov    edx,DWORD PTR [esp+0x10]     
	mov    DWORD PTR [esp+0x4],esi      
	mov    eax,DWORD PTR [esp+0x14]     
	mov    DWORD PTR [esp+0x8],edi      
	mov    ecx,DWORD PTR [esp+0x18]     
	mov    ebx,DWORD PTR [esp+0x24]     
	mov    esi,DWORD PTR [esp+0x20]     
	mov    edi,DWORD PTR [esp+0x1c]     
	test   ebx,0x1                      
	je     put_pixels16_l2_3dnowflag    
	movq   mm0,QWORD PTR [eax]          
	movq   mm1,QWORD PTR [eax+0x8]      
	pavgusb mm0,QWORD PTR [ecx]         
	pavgusb mm1,QWORD PTR [ecx+0x8]     
	add    eax,esi                      
	add    ecx,0x10                     
	movq   QWORD PTR [edx],mm0          
	movq   QWORD PTR [edx+0x8],mm1      
	add    edx,edi                      
	dec    ebx                          
put_pixels16_l2_3dnowflag:           
	movq   mm0,QWORD PTR [eax]          
	movq   mm1,QWORD PTR [eax+0x8]      
	add    eax,esi                      
	pavgusb mm0,QWORD PTR [ecx]         
	pavgusb mm1,QWORD PTR [ecx+0x8]     
	movq   QWORD PTR [edx],mm0          
	movq   QWORD PTR [edx+0x8],mm1      
	add    edx,edi                      
	movq   mm0,QWORD PTR [eax]          
	movq   mm1,QWORD PTR [eax+0x8]      
	add    eax,esi                      
	pavgusb mm0,QWORD PTR [ecx+0x10]    
	pavgusb mm1,QWORD PTR [ecx+0x18]    
	movq   QWORD PTR [edx],mm0          
	movq   QWORD PTR [edx+0x8],mm1      
	add    edx,edi                      
	add    ecx,0x20                     
	sub    ebx,0x2                      
	jne    put_pixels16_l2_3dnowflag    
	mov    ebx,DWORD PTR [esp]          
	mov    esi,DWORD PTR [esp+0x4]      
	mov    edi,DWORD PTR [esp+0x8]      
	add    esp,0xc                      
	ret
	}
}
void __declspec(naked) put_pixels4_l2_mmx2(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                                
	mov    DWORD PTR [esp],ebx                    
	mov    edx,DWORD PTR [esp+0x10]               
	mov    DWORD PTR [esp+0x4],esi                
	mov    eax,DWORD PTR [esp+0x14]               
	mov    DWORD PTR [esp+0x8],edi                
	mov    ecx,DWORD PTR [esp+0x18]               
	mov    ebx,DWORD PTR [esp+0x24]               
	mov    esi,DWORD PTR [esp+0x20]               
	mov    edi,DWORD PTR [esp+0x1c]               
	test   ebx,0x1                                
	je     put_pixels4_l2_mmx2flag                
	movd   mm0,DWORD PTR [eax]                    
	movd   mm1,DWORD PTR [ecx]                    
	add    eax,esi                                
	add    ecx,0x4                                
	pavgb  mm0,mm1                                
	movd   DWORD PTR [edx],mm0                    
	add    edx,edi                                
	dec    ebx                                    
put_pixels4_l2_mmx2flag:                       
	movd   mm0,DWORD PTR [eax]                    
	add    eax,esi                                
	movd   mm1,DWORD PTR [eax]                    
	movd   mm2,DWORD PTR [ecx]                    
	movd   mm3,DWORD PTR [ecx+0x4]                
	add    eax,esi                                
	pavgb  mm0,mm2                                
	pavgb  mm1,mm3                                
	movd   DWORD PTR [edx],mm0                    
	add    edx,edi                                
	movd   DWORD PTR [edx],mm1                    
	add    edx,edi                                
	movd   mm0,DWORD PTR [eax]                    
	add    eax,esi                                
	movd   mm1,DWORD PTR [eax]                    
	movd   mm2,DWORD PTR [ecx+0x8]                
	movd   mm3,DWORD PTR [ecx+0xc]                
	add    eax,esi                                
	pavgb  mm0,mm2                                
	pavgb  mm1,mm3                                
	movd   DWORD PTR [edx],mm0                    
	add    edx,edi                                
	movd   DWORD PTR [edx],mm1                    
	add    edx,edi                                
	add    ecx,0x10                               
	sub    ebx,0x4                                
	jne    put_pixels4_l2_mmx2flag                
	mov    ebx,DWORD PTR [esp]                    
	mov    esi,DWORD PTR [esp+0x4]                
	mov    edi,DWORD PTR [esp+0x8]                
	add    esp,0xc                                
	ret                                           
	}
}
void __declspec(naked) put_pixels8_l2_mmx2(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
 	sub    esp,0xc                     
 	mov    DWORD PTR [esp],ebx         
 	mov    edx,DWORD PTR [esp+0x10]    
 	mov    DWORD PTR [esp+0x4],esi     
 	mov    eax,DWORD PTR [esp+0x14]    
 	mov    DWORD PTR [esp+0x8],edi     
 	mov    ecx,DWORD PTR [esp+0x18]    
 	mov    ebx,DWORD PTR [esp+0x24]    
 	mov    esi,DWORD PTR [esp+0x20]    
 	mov    edi,DWORD PTR [esp+0x1c]    
 	test   ebx,0x1                     
 	je     put_pixels8_l2_mmx2flag     
 	movq   mm0,QWORD PTR [eax]         
 	movq   mm1,QWORD PTR [ecx]         
 	add    eax,esi                     
 	add    ecx,0x8                     
 	pavgb  mm0,mm1                     
 	movq   QWORD PTR [edx],mm0         
 	add    edx,edi                     
 	dec    ebx                         
 put_pixels8_l2_mmx2flag:            
 	movq   mm0,QWORD PTR [eax]         
 	add    eax,esi                     
 	movq   mm1,QWORD PTR [eax]         
 	add    eax,esi                     
 	pavgb  mm0,QWORD PTR [ecx]         
 	pavgb  mm1,QWORD PTR [ecx+0x8]     
 	movq   QWORD PTR [edx],mm0         
 	add    edx,edi                     
 	movq   QWORD PTR [edx],mm1         
 	add    edx,edi                     
 	movq   mm0,QWORD PTR [eax]         
 	add    eax,esi                     
 	movq   mm1,QWORD PTR [eax]         
 	add    eax,esi                     
 	pavgb  mm0,QWORD PTR [ecx+0x10]    
 	pavgb  mm1,QWORD PTR [ecx+0x18]    
 	movq   QWORD PTR [edx],mm0         
 	add    edx,edi                     
 	movq   QWORD PTR [edx],mm1         
 	add    edx,edi                     
 	add    ecx,0x20                    
 	sub    ebx,0x4                     
 	jne    put_pixels8_l2_mmx2flag     
 	mov    ebx,DWORD PTR [esp]         
 	mov    esi,DWORD PTR [esp+0x4]     
 	mov    edi,DWORD PTR [esp+0x8]     
 	add    esp,0xc                     
 	ret                                
	}
}
void __declspec(naked) put_pixels16_l2_mmx2(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                  
	mov    DWORD PTR [esp],ebx      
	mov    edx,DWORD PTR [esp+0x10] 
	mov    DWORD PTR [esp+0x4],esi  
	mov    eax,DWORD PTR [esp+0x14] 
	mov    DWORD PTR [esp+0x8],edi  
	mov    ecx,DWORD PTR [esp+0x18] 
	mov    ebx,DWORD PTR [esp+0x24] 
	mov    esi,DWORD PTR [esp+0x20] 
	mov    edi,DWORD PTR [esp+0x1c] 
	test   ebx,0x1                  
	je     put_pixels16_l2_mmx2flag 
	movq   mm0,QWORD PTR [eax]      
	movq   mm1,QWORD PTR [eax+0x8]  
	pavgb  mm0,QWORD PTR [ecx]      
	pavgb  mm1,QWORD PTR [ecx+0x8]  
	add    eax,esi                  
	add    ecx,0x10                 
	movq   QWORD PTR [edx],mm0      
	movq   QWORD PTR [edx+0x8],mm1  
	add    edx,edi                  
	dec    ebx                      
put_pixels16_l2_mmx2flag:        
	movq   mm0,QWORD PTR [eax]      
	movq   mm1,QWORD PTR [eax+0x8]  
	add    eax,esi                  
	pavgb  mm0,QWORD PTR [ecx]      
	pavgb  mm1,QWORD PTR [ecx+0x8]  
	movq   QWORD PTR [edx],mm0      
	movq   QWORD PTR [edx+0x8],mm1  
	add    edx,edi                  
	movq   mm0,QWORD PTR [eax]      
	movq   mm1,QWORD PTR [eax+0x8]  
	add    eax,esi                  
	pavgb  mm0,QWORD PTR [ecx+0x10] 
	pavgb  mm1,QWORD PTR [ecx+0x18] 
	movq   QWORD PTR [edx],mm0      
	movq   QWORD PTR [edx+0x8],mm1  
	add    edx,edi                  
	add    ecx,0x20                 
	sub    ebx,0x2                  
	jne    put_pixels16_l2_mmx2flag 
	mov    ebx,DWORD PTR [esp]      
	mov    esi,DWORD PTR [esp+0x4]  
	mov    edi,DWORD PTR [esp+0x8]  
	add    esp,0xc                  
	ret                             
	}
}
void __declspec(naked) put_h264_qpel4_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                        
 	mov    DWORD PTR [esp],ebx            
 	mov    edx,DWORD PTR [esp+0x10]       
 	mov    DWORD PTR [esp+0x4],esi        
 	mov    ecx,DWORD PTR [esp+0xc]        
 	mov    esi,0x4                        
 	mov    ebx,DWORD PTR [esp+0x14]       
 	lea    eax,[ebx+ebx*1]                
 	
put_h264_qpel4_mc00_3dnowLoop:
 	movd   mm0,DWORD PTR [edx]            
 	movd   mm1,DWORD PTR [edx+ebx*1]      
 	movd   DWORD PTR [ecx],mm0            
 	movd   DWORD PTR [ecx+ebx*1],mm1      
 	add    edx,eax                        
 	add    ecx,eax                        
 	movd   mm0,DWORD PTR [edx]            
 	movd   mm1,DWORD PTR [edx+ebx*1]      
 	movd   DWORD PTR [ecx],mm0            
 	movd   DWORD PTR [ecx+ebx*1],mm1      
 	add    edx,eax                        
 	add    ecx,eax                        
 	sub    esi,0x4                        
 	jne    put_h264_qpel4_mc00_3dnowLoop          
 	mov    ebx,DWORD PTR [esp]            
 	mov    esi,DWORD PTR [esp+0x4]        
 	add    esp,0x8                        
 	ret
	}
}
void __declspec(naked) put_h264_qpel8_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
			sub    esp,0x8                       
	mov    DWORD PTR [esp],ebx           
	mov    edx,DWORD PTR [esp+0x10]      
	mov    DWORD PTR [esp+0x4],esi       
	mov    ecx,DWORD PTR [esp+0xc]       
	mov    esi,0x8                       
	mov    ebx,DWORD PTR [esp+0x14]      
	lea    eax,[ebx+ebx*1]               
                         
put_h264_qpel8_mc00_3dnowloop:       
	movq   mm0,QWORD PTR [edx]           
	movq   mm1,QWORD PTR [edx+ebx*1]     
	movq   QWORD PTR [ecx],mm0           
	movq   QWORD PTR [ecx+ebx*1],mm1     
	add    edx,eax                       
	add    ecx,eax                       
	movq   mm0,QWORD PTR [edx]           
	movq   mm1,QWORD PTR [edx+ebx*1]     
	movq   QWORD PTR [ecx],mm0           
	movq   QWORD PTR [ecx+ebx*1],mm1     
	add    edx,eax                       
	add    ecx,eax                       
	sub    esi,0x4                       
	jne    put_h264_qpel8_mc00_3dnowloop 
	mov    ebx,DWORD PTR [esp]           
	mov    esi,DWORD PTR [esp+0x4]       
	add    esp,0x8                       
	ret
	}
}
void __declspec(naked) put_h264_qpel16_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                               
	mov    DWORD PTR [esp],ebx                   
	mov    edx,DWORD PTR [esp+0x10]              
	mov    DWORD PTR [esp+0x4],esi               
	mov    ecx,DWORD PTR [esp+0xc]               
	mov    esi,0x10                              
	mov    ebx,DWORD PTR [esp+0x14]              
	lea    eax,[ebx+ebx*1]                       
	xchg   ax,ax                                 
put_h264_qpel16_mc00_3dnowloop:              
	movq   mm0,QWORD PTR [edx]                   
	movq   mm4,QWORD PTR [edx+0x8]               
	movq   mm1,QWORD PTR [edx+ebx*1]             
	movq   mm5,QWORD PTR [edx+ebx*1+0x8]         
	movq   QWORD PTR [ecx],mm0                   
	movq   QWORD PTR [ecx+0x8],mm4               
	movq   QWORD PTR [ecx+ebx*1],mm1             
	movq   QWORD PTR [ecx+ebx*1+0x8],mm5         
	add    edx,eax                               
	add    ecx,eax                               
	movq   mm0,QWORD PTR [edx]                   
	movq   mm4,QWORD PTR [edx+0x8]               
	movq   mm1,QWORD PTR [edx+ebx*1]             
	movq   mm5,QWORD PTR [edx+ebx*1+0x8]         
	movq   QWORD PTR [ecx],mm0                   
	movq   QWORD PTR [ecx+0x8],mm4               
	movq   QWORD PTR [ecx+ebx*1],mm1             
	movq   QWORD PTR [ecx+ebx*1+0x8],mm5         
	add    edx,eax                               
	add    ecx,eax                               
	sub    esi,0x4                               
	jne    put_h264_qpel16_mc00_3dnowloop        
	mov    ebx,DWORD PTR [esp]                   
	mov    esi,DWORD PTR [esp+0x4]               
	add    esp,0x8                               
	ret
	}
}
void __declspec(naked) put_h264_qpel4_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                       
	mov    DWORD PTR [esp],ebx           
	mov    edx,DWORD PTR [esp+0x10]      
	mov    DWORD PTR [esp+0x4],esi       
	mov    ecx,DWORD PTR [esp+0xc]       
	mov    esi,0x4                       
	mov    ebx,DWORD PTR [esp+0x14]      
	lea    eax,[ebx+ebx*1]               
	xchg   ax,ax                         
put_h264_qpel4_mc00_mmx2loop:        
	movd   mm0,DWORD PTR [edx]           
	movd   mm1,DWORD PTR [edx+ebx*1]     
	movd   DWORD PTR [ecx],mm0           
	movd   DWORD PTR [ecx+ebx*1],mm1     
	add    edx,eax                       
	add    ecx,eax                       
	movd   mm0,DWORD PTR [edx]           
	movd   mm1,DWORD PTR [edx+ebx*1]     
	movd   DWORD PTR [ecx],mm0           
	movd   DWORD PTR [ecx+ebx*1],mm1     
	add    edx,eax                       
	add    ecx,eax                       
	sub    esi,0x4                       
	jne    put_h264_qpel4_mc00_mmx2loop  
	mov    ebx,DWORD PTR [esp]           
	mov    esi,DWORD PTR [esp+0x4]       
	add    esp,0x8                       
	ret                                  

	}
}
void __declspec(naked) put_h264_qpel8_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                      
	mov    DWORD PTR [esp],ebx          
	mov    edx,DWORD PTR [esp+0x10]     
	mov    DWORD PTR [esp+0x4],esi      
	mov    ecx,DWORD PTR [esp+0xc]      
	mov    esi,0x8                      
	mov    ebx,DWORD PTR [esp+0x14]     
	lea    eax,[ebx+ebx*1]              
                                     
put_h264_qpel8_mc00_mmx2loop:       
	movq   mm0,QWORD PTR [edx]          
	movq   mm1,QWORD PTR [edx+ebx*1]    
	movq   QWORD PTR [ecx],mm0          
	movq   QWORD PTR [ecx+ebx*1],mm1    
	add    edx,eax                      
	add    ecx,eax                      
	movq   mm0,QWORD PTR [edx]          
	movq   mm1,QWORD PTR [edx+ebx*1]    
	movq   QWORD PTR [ecx],mm0          
	movq   QWORD PTR [ecx+ebx*1],mm1    
	add    edx,eax                      
	add    ecx,eax                      
	sub    esi,0x4                      
	jne    put_h264_qpel8_mc00_mmx2loop 
	mov    ebx,DWORD PTR [esp]          
	mov    esi,DWORD PTR [esp+0x4]      
	add    esp,0x8                      
	ret
	}
}
void __declspec(naked) put_h264_qpel16_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                       
	mov    DWORD PTR [esp],ebx           
	mov    edx,DWORD PTR [esp+0x10]      
	mov    DWORD PTR [esp+0x4],esi       
	mov    ecx,DWORD PTR [esp+0xc]       
	mov    esi,0x10                      
	mov    ebx,DWORD PTR [esp+0x14]      
	lea    eax,[ebx+ebx*1]               
put_h264_qpel16_mc00_mmx2loop:           
	movq   mm0,QWORD PTR [edx]           
	movq   mm4,QWORD PTR [edx+0x8]       
	movq   mm1,QWORD PTR [edx+ebx*1]     
	movq   mm5,QWORD PTR [edx+ebx*1+0x8] 
	movq   QWORD PTR [ecx],mm0           
	movq   QWORD PTR [ecx+0x8],mm4       
	movq   QWORD PTR [ecx+ebx*1],mm1     
	movq   QWORD PTR [ecx+ebx*1+0x8],mm5 
	add    edx,eax                       
	add    ecx,eax                       
	movq   mm0,QWORD PTR [edx]           
	movq   mm4,QWORD PTR [edx+0x8]       
	movq   mm1,QWORD PTR [edx+ebx*1]     
	movq   mm5,QWORD PTR [edx+ebx*1+0x8] 
	movq   QWORD PTR [ecx],mm0           
	movq   QWORD PTR [ecx+0x8],mm4       
	movq   QWORD PTR [ecx+ebx*1],mm1     
	movq   QWORD PTR [ecx+ebx*1+0x8],mm5 
	add    edx,eax                       
	add    ecx,eax                       
	sub    esi,0x4                       
	jne    put_h264_qpel16_mc00_mmx2loop     
	mov    ebx,DWORD PTR [esp]           
	mov    esi,DWORD PTR [esp+0x4]       
	add    esp,0x8                       
	ret
	}
}
void __declspec(naked) put_h264_qpel16_mc00_sse2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
		sub    esp,0x8                      
		mov    eax,DWORD PTR [esp+0x14]     
		mov    DWORD PTR [esp],ebx          
		mov    edx,DWORD PTR [esp+0x10]     
		mov    DWORD PTR [esp+0x4],esi      
		mov    ecx,DWORD PTR [esp+0xc]      
		mov    esi,0x10                     
		lea    ebx,[eax+eax*2]              
put_h264_qpel16_mc00_sse2loop:      
		movdqu xmm0,XMMWORD PTR [edx]       
		movdqu xmm1,XMMWORD PTR [edx+eax*1] 
		movdqu xmm2,XMMWORD PTR [edx+eax*2] 
		movdqu xmm3,XMMWORD PTR [edx+ebx*1] 
		lea    edx,[edx+eax*4]              
		movdqa XMMWORD PTR [ecx],xmm0       
		movdqa XMMWORD PTR [ecx+eax*1],xmm1 
		movdqa XMMWORD PTR [ecx+eax*2],xmm2 
		movdqa XMMWORD PTR [ecx+ebx*1],xmm3 
		sub    esi,0x4                      
		lea    ecx,[ecx+eax*4]              
		jne    put_h264_qpel16_mc00_sse2loop
		mov    ebx,DWORD PTR [esp]          
		mov    esi,DWORD PTR [esp+0x4]      
		add    esp,0x8                      
		ret
	}
}
void __declspec(naked) put_h264_qpel4_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                            
	mov    DWORD PTR [esp],ebx                
	mov    ecx,DWORD PTR [esp+0xc]            
	mov    ebx,0x4                            
	mov    DWORD PTR [esp+0x4],esi            
	mov    eax,DWORD PTR [esp+0x10]           
	mov    edx,DWORD PTR [esp+0x18]           
	mov    esi,DWORD PTR [esp+0x14]           
	pxor   mm7,mm7                            
	movq   mm4,QWORD PTR [ff_pw_5]            
	movq   mm5,QWORD PTR [ff_pw_16]           
put_h264_qpel4_h_lowpass_3dnowflag:        
	movd   mm1,DWORD PTR [eax-0x1]            
	movd   mm2,DWORD PTR [eax]                
	movd   mm3,DWORD PTR [eax+0x1]            
	movd   mm0,DWORD PTR [eax+0x2]            
	punpcklbw mm1,mm7                         
	punpcklbw mm2,mm7                         
	punpcklbw mm3,mm7                         
	punpcklbw mm0,mm7                         
	paddw  mm1,mm0                            
	paddw  mm2,mm3                            
	movd   mm0,DWORD PTR [eax-0x2]            
	movd   mm3,DWORD PTR [eax+0x3]            
	punpcklbw mm0,mm7                         
	punpcklbw mm3,mm7                         
	paddw  mm0,mm3                            
	psllw  mm2,0x2                            
	psubw  mm2,mm1                            
	pmullw mm2,mm4                            
	paddw  mm0,mm5                            
	paddw  mm0,mm2                            
	psraw  mm0,0x5                            
	packuswb mm0,mm0                          
	movd   DWORD PTR [ecx],mm0                
	add    eax,edx                            
	add    ecx,esi                            
	dec    ebx                                
	jne    put_h264_qpel4_h_lowpass_3dnowflag 
	mov    ebx,DWORD PTR [esp]                
	mov    esi,DWORD PTR [esp+0x4]            
	add    esp,0x8                            
	ret                                       
	}
}
void __declspec(naked) put_h264_qpel4_h_lowpass_l2_3dnow(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0x8                              
	mov    DWORD PTR [esp],esi                  
	mov    ecx,DWORD PTR [esp+0xc]              
	mov    DWORD PTR [esp+0x4],edi              
	mov    eax,DWORD PTR [esp+0x10]             
	mov    edx,DWORD PTR [esp+0x14]             
	mov    esi,DWORD PTR [esp+0x18]             
	mov    edi,DWORD PTR [esp+0x1c]             
	pxor   mm7,mm7                              
	movq   mm4,QWORD PTR [ff_pw_5]                 
	movq   mm5,QWORD PTR [ff_pw_16]                
	movd   mm1,DWORD PTR [eax-0x1]              
	movd   mm2,DWORD PTR [eax]                  
	movd   mm3,DWORD PTR [eax+0x1]              
	movd   mm0,DWORD PTR [eax+0x2]              
	punpcklbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpcklbw mm3,mm7                           
	punpcklbw mm0,mm7                           
	paddw  mm1,mm0                              
	paddw  mm2,mm3                              
	movd   mm0,DWORD PTR [eax-0x2]              
	movd   mm3,DWORD PTR [eax+0x3]              
	punpcklbw mm0,mm7                           
	punpcklbw mm3,mm7                           
	paddw  mm0,mm3                              
	psllw  mm2,0x2                              
	psubw  mm2,mm1                              
	pmullw mm2,mm4                              
	paddw  mm0,mm5                              
	paddw  mm0,mm2                              
	movd   mm3,DWORD PTR [edx]                  
	psraw  mm0,0x5                              
	packuswb mm0,mm0                            
	pavgusb mm0,mm3                             
	movd   DWORD PTR [ecx],mm0                  
	add    eax,esi                              
	add    ecx,esi                              
	add    edx,edi                              
	movd   mm1,DWORD PTR [eax-0x1]              
	movd   mm2,DWORD PTR [eax]                  
	movd   mm3,DWORD PTR [eax+0x1]              
	movd   mm0,DWORD PTR [eax+0x2]              
	punpcklbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpcklbw mm3,mm7                           
	punpcklbw mm0,mm7                           
	paddw  mm1,mm0                              
	paddw  mm2,mm3                              
	movd   mm0,DWORD PTR [eax-0x2]              
	movd   mm3,DWORD PTR [eax+0x3]              
	punpcklbw mm0,mm7                           
	punpcklbw mm3,mm7                           
	paddw  mm0,mm3                              
	psllw  mm2,0x2                              
	psubw  mm2,mm1                              
	pmullw mm2,mm4                              
	paddw  mm0,mm5                              
	paddw  mm0,mm2                              
	movd   mm3,DWORD PTR [edx]                  
	psraw  mm0,0x5                              
	packuswb mm0,mm0                            
	pavgusb mm0,mm3                             
	movd   DWORD PTR [ecx],mm0                  
	add    eax,esi                              
	add    ecx,esi                              
	add    edx,edi                              
	movd   mm1,DWORD PTR [eax-0x1]              
	movd   mm2,DWORD PTR [eax]                  
	movd   mm3,DWORD PTR [eax+0x1]              
	movd   mm0,DWORD PTR [eax+0x2]              
	punpcklbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpcklbw mm3,mm7                           
	punpcklbw mm0,mm7                           
	paddw  mm1,mm0                              
	paddw  mm2,mm3                              
	movd   mm0,DWORD PTR [eax-0x2]              
	movd   mm3,DWORD PTR [eax+0x3]              
	punpcklbw mm0,mm7                           
	punpcklbw mm3,mm7                           
	paddw  mm0,mm3                              
	psllw  mm2,0x2                              
	psubw  mm2,mm1                              
	pmullw mm2,mm4                              
	paddw  mm0,mm5                              
	paddw  mm0,mm2                              
	movd   mm3,DWORD PTR [edx]                  
	psraw  mm0,0x5                              
	packuswb mm0,mm0                            
	pavgusb mm0,mm3                             
	movd   DWORD PTR [ecx],mm0                  
	add    eax,esi                              
	add    ecx,esi                              
	add    edx,edi                              
	movd   mm1,DWORD PTR [eax-0x1]              
	movd   mm2,DWORD PTR [eax]                  
	movd   mm3,DWORD PTR [eax+0x1]              
	movd   mm0,DWORD PTR [eax+0x2]              
	punpcklbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpcklbw mm3,mm7                           
	punpcklbw mm0,mm7                           
	paddw  mm1,mm0                              
	paddw  mm2,mm3                              
	movd   mm0,DWORD PTR [eax-0x2]              
	movd   mm3,DWORD PTR [eax+0x3]              
	punpcklbw mm0,mm7                           
	punpcklbw mm3,mm7                           
	paddw  mm0,mm3                              
	psllw  mm2,0x2                              
	psubw  mm2,mm1                              
	pmullw mm2,mm4                              
	paddw  mm0,mm5                              
	paddw  mm0,mm2                              
	movd   mm3,DWORD PTR [edx]                  
	psraw  mm0,0x5                              
	packuswb mm0,mm0                            
	pavgusb mm0,mm3                             
	movd   DWORD PTR [ecx],mm0                  
	add    eax,esi                              
	add    ecx,esi                              
	add    edx,edi                              
	mov    esi,DWORD PTR [esp]                  
	mov    edi,DWORD PTR [esp+0x4]              
	add    esp,0x8                              
	ret                                         
   }
}
void __declspec(naked) put_h264_qpel4_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                   
	mov    DWORD PTR [esp],esi       
	mov    esi,DWORD PTR [esp+0x18]  
	mov    DWORD PTR [esp+0x4],edi   
	mov    ecx,DWORD PTR [esp+0xc]   
	mov    edi,DWORD PTR [esp+0x14]  
	lea    eax,[esi+esi*1]           
	neg    eax                       
	add    eax,DWORD PTR [esp+0x10]  
	pxor   mm7,mm7                   
	movd   mm0,DWORD PTR [eax]       
	add    eax,esi                   
	movd   mm1,DWORD PTR [eax]       
	add    eax,esi                   
	movd   mm2,DWORD PTR [eax]       
	add    eax,esi                   
	movd   mm3,DWORD PTR [eax]       
	add    eax,esi                   
	movd   mm4,DWORD PTR [eax]       
	add    eax,esi                   
	punpcklbw mm0,mm7                
	punpcklbw mm1,mm7                
	punpcklbw mm2,mm7                
	punpcklbw mm3,mm7                
	punpcklbw mm4,mm7                
	movq   mm6,mm2                   
	movd   mm5,DWORD PTR [eax]       
	paddw  mm6,mm3                   
	psllw  mm6,0x2                   
	psubw  mm6,mm1                   
	psubw  mm6,mm4                   
	punpcklbw mm5,mm7                
	pmullw mm6,QWORD PTR [ff_pw_5]      
	paddw  mm0,QWORD PTR [ff_pw_16]      
	add    eax,esi                   
	paddw  mm0,mm5                   
	paddw  mm6,mm0                   
	psraw  mm6,0x5                   
	packuswb mm6,mm6                 
	movd   DWORD PTR [ecx],mm6       
	add    ecx,edi                   
	movq   mm6,mm3                   
	movd   mm0,DWORD PTR [eax]       
	paddw  mm6,mm4                   
	psllw  mm6,0x2                   
	psubw  mm6,mm2                   
	psubw  mm6,mm5                   
	punpcklbw mm0,mm7                
	pmullw mm6,QWORD PTR [ff_pw_5]      
	paddw  mm1,QWORD PTR [ff_pw_16]      
	add    eax,esi                   
	paddw  mm1,mm0                   
	paddw  mm6,mm1                   
	psraw  mm6,0x5                   
	packuswb mm6,mm6                 
	movd   DWORD PTR [ecx],mm6       
	add    ecx,edi                   
	movq   mm6,mm4                   
	movd   mm1,DWORD PTR [eax]       
	paddw  mm6,mm5                   
	psllw  mm6,0x2                   
	psubw  mm6,mm3                   
	psubw  mm6,mm0                   
	punpcklbw mm1,mm7                
	pmullw mm6,QWORD PTR [ff_pw_5]      
	paddw  mm2,QWORD PTR [ff_pw_16]      
	add    eax,esi                   
	paddw  mm2,mm1                   
	paddw  mm6,mm2                   
	psraw  mm6,0x5                   
	packuswb mm6,mm6                 
	movd   DWORD PTR [ecx],mm6       
	add    ecx,edi                   
	movq   mm6,mm5                   
	movd   mm2,DWORD PTR [eax]       
	paddw  mm6,mm0                   
	psllw  mm6,0x2                   
	psubw  mm6,mm4                   
	psubw  mm6,mm1                   
	punpcklbw mm2,mm7                
	pmullw mm6,QWORD PTR [ff_pw_5]      
	paddw  mm3,QWORD PTR [ff_pw_16]      
	add    eax,esi                   
	paddw  mm3,mm2                   
	paddw  mm6,mm3                   
	psraw  mm6,0x5                   
	packuswb mm6,mm6                 
	movd   DWORD PTR [ecx],mm6       
	add    ecx,edi                   
	mov    esi,DWORD PTR [esp]       
	mov    edi,DWORD PTR [esp+0x4]   
	add    esp,0x8                   
	ret                              
	}
}
void __declspec(naked) put_h264_qpel4_hv_lowpass_3dnow(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	__asm{
			sub    esp,0xc                                                                          
	mov    DWORD PTR [esp+0x4],esi                                                          
	mov    esi,DWORD PTR [esp+0x24]                                                         
	mov    edx,DWORD PTR [esp+0x14]                                                         
	mov    DWORD PTR [esp],ebx                                                              
	mov    DWORD PTR [esp+0x8],edi                                                          
	mov    edi,DWORD PTR [esp+0x10]                                                         
	mov    eax,esi                                                                          
	lea    ebx,[esi+esi*8]                                                                  
	not    eax                                                                              
	neg    ebx                                                                              
	add    eax,eax                                                                          
	add    ebx,0x4                                                                          
	mov    ecx,edx                                                                          
	add    eax,DWORD PTR [esp+0x18]                                                         
	pxor   mm7,mm7                                                                          
	movd   mm0,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm1,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm2,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm3,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm4,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	punpcklbw mm0,mm7                                                                       
	punpcklbw mm1,mm7                                                                       
	punpcklbw mm2,mm7                                                                       
	punpcklbw mm3,mm7                                                                       
	punpcklbw mm4,mm7                                                                       
	movq   mm6,mm2                                                                          
	movd   mm5,DWORD PTR [eax]                                                              
	paddw  mm6,mm3                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm0,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm1                                                                          
	psubw  mm6,mm4                                                                          
	punpcklbw mm5,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm0,mm5                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm0                                                                          
	movq   QWORD PTR [ecx],mm6                                                              
	movq   mm6,mm3                                                                          
	movd   mm0,DWORD PTR [eax]                                                              
	paddw  mm6,mm4                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm1,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm2                                                                          
	psubw  mm6,mm5                                                                          
	punpcklbw mm0,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm1,mm0                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm1                                                                          
	movq   QWORD PTR [ecx+0x18],mm6                                                         
	movq   mm6,mm4                                                                          
	movd   mm1,DWORD PTR [eax]                                                              
	paddw  mm6,mm5                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm2,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm3                                                                          
	psubw  mm6,mm0                                                                          
	punpcklbw mm1,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm2,mm1                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm2                                                                          
	movq   QWORD PTR [ecx+0x30],mm6                                                         
	movq   mm6,mm5                                                                          
	movd   mm2,DWORD PTR [eax]                                                              
	paddw  mm6,mm0                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm3,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm4                                                                          
	psubw  mm6,mm1                                                                          
	punpcklbw mm2,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm3,mm2                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm3                                                                          
	movq   QWORD PTR [ecx+0x48],mm6                                                         
	lea    ecx,[edx+0x8]                                                                    
	add    eax,ebx                                                                          
	pxor   mm7,mm7                                                                          
	movd   mm0,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm1,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm2,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm3,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm4,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	punpcklbw mm0,mm7                                                                       
	punpcklbw mm1,mm7                                                                       
	punpcklbw mm2,mm7                                                                       
	punpcklbw mm3,mm7                                                                       
	punpcklbw mm4,mm7                                                                       
	movq   mm6,mm2                                                                          
	movd   mm5,DWORD PTR [eax]                                                              
	paddw  mm6,mm3                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm0,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm1                                                                          
	psubw  mm6,mm4                                                                          
	punpcklbw mm5,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm0,mm5                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm0                                                                          
	movq   QWORD PTR [ecx],mm6                                                              
	movq   mm6,mm3                                                                          
	movd   mm0,DWORD PTR [eax]                                                              
	paddw  mm6,mm4                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm1,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm2                                                                          
	psubw  mm6,mm5                                                                          
	punpcklbw mm0,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm1,mm0                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm1                                                                          
	movq   QWORD PTR [ecx+0x18],mm6                                                         
	movq   mm6,mm4                                                                          
	movd   mm1,DWORD PTR [eax]                                                              
	paddw  mm6,mm5                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm2,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm3                                                                          
	psubw  mm6,mm0                                                                          
	punpcklbw mm1,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm2,mm1                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm2                                                                          
	movq   QWORD PTR [ecx+0x30],mm6                                                         
	movq   mm6,mm5                                                                          
	movd   mm2,DWORD PTR [eax]                                                              
	paddw  mm6,mm0                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm3,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm4                                                                          
	psubw  mm6,mm1                                                                          
	punpcklbw mm2,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm3,mm2                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm3                                                                          
	movq   QWORD PTR [ecx+0x48],mm6                                                         
	add    eax,ebx                                                                          
	lea    ecx,[edx+0x10]                                                                   
	pxor   mm7,mm7                                                                          
	movd   mm0,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm1,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm2,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm3,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	movd   mm4,DWORD PTR [eax]                                                              
	add    eax,esi                                                                          
	punpcklbw mm0,mm7                                                                       
	punpcklbw mm1,mm7                                                                       
	punpcklbw mm2,mm7                                                                       
	punpcklbw mm3,mm7                                                                       
	punpcklbw mm4,mm7                                                                       
	movq   mm6,mm2                                                                          
	movd   mm5,DWORD PTR [eax]                                                              
	paddw  mm6,mm3                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm0,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm1                                                                          
	psubw  mm6,mm4                                                                          
	punpcklbw mm5,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm0,mm5                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm0                                                                          
	movq   QWORD PTR [ecx],mm6                                                              
	movq   mm6,mm3                                                                          
	movd   mm0,DWORD PTR [eax]                                                              
	paddw  mm6,mm4                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm1,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm2                                                                          
	psubw  mm6,mm5                                                                          
	punpcklbw mm0,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm1,mm0                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm1                                                                          
	movq   QWORD PTR [ecx+0x18],mm6                                                         
	movq   mm6,mm4                                                                          
	movd   mm1,DWORD PTR [eax]                                                              
	paddw  mm6,mm5                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm2,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm3                                                                          
	psubw  mm6,mm0                                                                          
	punpcklbw mm1,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm2,mm1                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm2                                                                          
	movq   QWORD PTR [ecx+0x30],mm6                                                         
	movq   mm6,mm5                                                                          
	movd   mm2,DWORD PTR [eax]                                                              
	paddw  mm6,mm0                                                                          
	psllw  mm6,0x2                                                                          
	paddw  mm3,QWORD PTR [ff_pw_16]                                                             
	psubw  mm6,mm4                                                                          
	psubw  mm6,mm1                                                                          
	punpcklbw mm2,mm7                                                                       
	pmullw mm6,QWORD PTR [ff_pw_5]                                                             
	paddw  mm3,mm2                                                                          
	add    eax,esi                                                                          
	paddw  mm6,mm3                                                                          
	movq   QWORD PTR [ecx+0x48],mm6                                                         
	mov    eax,edx                                                                          
	mov    esi,DWORD PTR [esp+0x1c]                                                         
	mov    ecx,edi                                                                          
	mov    edx,0x4                                                                          
put_h264_qpel4_hv_lowpass_3dnowflag:                                                     
	movq   mm0,QWORD PTR [eax]                                                              
	paddw  mm0,QWORD PTR [eax+0xa]                                                          
	movq   mm1,QWORD PTR [eax+0x2]                                                          
	paddw  mm1,QWORD PTR [eax+0x8]                                                          
	movq   mm2,QWORD PTR [eax+0x4]                                                          
	paddw  mm2,QWORD PTR [eax+0x6]                                                          
	psubw  mm0,mm1                                                                          
	psraw  mm0,0x2                                                                          
	psubw  mm0,mm1                                                                          
	paddsw mm0,mm2                                                                          
	psraw  mm0,0x2                                                                          
	paddw  mm0,mm2                                                                          
	psraw  mm0,0x6                                                                          
	packuswb mm0,mm0                                                                        
	movd   DWORD PTR [ecx],mm0                                                              
	add    eax,0x18                                                                         
	add    ecx,esi                                                                          
	dec    edx                                                                              
	jne    put_h264_qpel4_hv_lowpass_3dnowflag                                              
	mov    ebx,DWORD PTR [esp]                                                              
	mov    esi,DWORD PTR [esp+0x4]                                                          
	mov    edi,DWORD PTR [esp+0x8]                                                          
	add    esp,0xc                                                                          
	ret                                                                                     
	}
}
void __declspec(naked) put_h264_qpel8_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{	
	sub    esp,0x8                           
	mov    DWORD PTR [esp],ebx               
	mov    ecx,DWORD PTR [esp+0xc]           
	mov    ebx,0x8                           
	mov    DWORD PTR [esp+0x4],esi           
	mov    eax,DWORD PTR [esp+0x10]          
	mov    edx,DWORD PTR [esp+0x18]          
	mov    esi,DWORD PTR [esp+0x14]          
	pxor   mm7,mm7                           
	movq   mm6,QWORD PTR [ff_pw_5]              
put_h264_qpel8_h_lowpass_3dnowflag:       
	movq   mm0,QWORD PTR [eax]               
	movq   mm2,QWORD PTR [eax+0x1]           
	movq   mm1,mm0                           
	movq   mm3,mm2                           
	punpcklbw mm0,mm7                        
	punpckhbw mm1,mm7                        
	punpcklbw mm2,mm7                        
	punpckhbw mm3,mm7                        
	paddw  mm0,mm2                           
	paddw  mm1,mm3                           
	psllw  mm0,0x2                           
	psllw  mm1,0x2                           
	movq   mm2,QWORD PTR [eax-0x1]           
	movq   mm4,QWORD PTR [eax+0x2]           
	movq   mm3,mm2                           
	movq   mm5,mm4                           
	punpcklbw mm2,mm7                        
	punpckhbw mm3,mm7                        
	punpcklbw mm4,mm7                        
	punpckhbw mm5,mm7                        
	paddw  mm2,mm4                           
	paddw  mm5,mm3                           
	psubw  mm0,mm2                           
	psubw  mm1,mm5                           
	pmullw mm0,mm6                           
	pmullw mm1,mm6                           
	movd   mm2,DWORD PTR [eax-0x2]           
	movd   mm5,DWORD PTR [eax+0x7]           
	punpcklbw mm2,mm7                        
	punpcklbw mm5,mm7                        
	paddw  mm2,mm3                           
	paddw  mm4,mm5                           
	movq   mm5,QWORD PTR [ff_pw_16]              
	paddw  mm2,mm5                           
	paddw  mm4,mm5                           
	paddw  mm0,mm2                           
	paddw  mm1,mm4                           
	psraw  mm0,0x5                           
	psraw  mm1,0x5                           
	packuswb mm0,mm1                         
	movq   QWORD PTR [ecx],mm0               
	add    eax,edx                           
	add    ecx,esi                           
	dec    ebx                               
	jne    put_h264_qpel8_h_lowpass_3dnowflag
	mov    ebx,DWORD PTR [esp]               
	mov    esi,DWORD PTR [esp+0x4]           
	add    esp,0x8                           
	ret
	}
}
void put_h264_qpel16_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	put_h264_qpel8_h_lowpass_3dnow(dst , src , dstStride, srcStride);
	put_h264_qpel8_h_lowpass_3dnow(dst+8, src+8, dstStride, srcStride);
	src += 8*srcStride;
	dst += 8*dstStride;
	put_h264_qpel8_h_lowpass_3dnow(dst , src , dstStride, srcStride);
	put_h264_qpel8_h_lowpass_3dnow(dst+8, src+8, dstStride, srcStride);
}
void __declspec(naked) put_h264_qpel8_h_lowpass_l2_3dnow(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0xc                              
	mov    DWORD PTR [esp],ebx                  
	mov    ecx,DWORD PTR [esp+0x10]             
	mov    ebx,0x8                              
	mov    DWORD PTR [esp+0x4],esi              
	mov    eax,DWORD PTR [esp+0x14]             
	mov    DWORD PTR [esp+0x8],edi              
	mov    edx,DWORD PTR [esp+0x18]             
	mov    edi,DWORD PTR [esp+0x20]             
	mov    esi,DWORD PTR [esp+0x1c]             
	pxor   mm7,mm7                              
	movq   mm6,QWORD PTR [ff_pw_5]
put_h264_qpel8_h_lowpass_l2_3dnowflag:       
	movq   mm0,QWORD PTR [eax]                  
	movq   mm2,QWORD PTR [eax+0x1]              
	movq   mm1,mm0                              
	movq   mm3,mm2                              
	punpcklbw mm0,mm7                           
	punpckhbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpckhbw mm3,mm7                           
	paddw  mm0,mm2                              
	paddw  mm1,mm3                              
	psllw  mm0,0x2                              
	psllw  mm1,0x2                              
	movq   mm2,QWORD PTR [eax-0x1]              
	movq   mm4,QWORD PTR [eax+0x2]              
	movq   mm3,mm2                              
	movq   mm5,mm4                              
	punpcklbw mm2,mm7                           
	punpckhbw mm3,mm7                           
	punpcklbw mm4,mm7                           
	punpckhbw mm5,mm7                           
	paddw  mm2,mm4                              
	paddw  mm5,mm3                              
	psubw  mm0,mm2                              
	psubw  mm1,mm5                              
	pmullw mm0,mm6                              
	pmullw mm1,mm6                              
	movd   mm2,DWORD PTR [eax-0x2]              
	movd   mm5,DWORD PTR [eax+0x7]              
	punpcklbw mm2,mm7                           
	punpcklbw mm5,mm7                           
	paddw  mm2,mm3                              
	paddw  mm4,mm5                              
	movq   mm5,QWORD PTR [ff_pw_16]
	paddw  mm2,mm5                              
	paddw  mm4,mm5                              
	paddw  mm0,mm2                              
	paddw  mm1,mm4                              
	psraw  mm0,0x5                              
	psraw  mm1,0x5                              
	movq   mm4,QWORD PTR [edx]                  
	packuswb mm0,mm1                            
	pavgusb mm0,mm4                             
	movq   QWORD PTR [ecx],mm0                  
	add    eax,esi                              
	add    ecx,esi                              
	add    edx,edi                              
	dec    ebx                                  
	jg     put_h264_qpel8_h_lowpass_l2_3dnowflag
	mov    ebx,DWORD PTR [esp]                  
	mov    esi,DWORD PTR [esp+0x4]              
	mov    edi,DWORD PTR [esp+0x8]              
	add    esp,0xc                              
	ret                                         
	}
}
void __declspec(naked) put_h264_qpel8or16_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
	__asm{
	sub    esp,0x10                                           
	mov    edx,0xfffffffb                                     
	mov    DWORD PTR [esp],ebx                                
	mov    ebx,DWORD PTR [esp+0x24]                           
	mov    DWORD PTR [esp+0x4],esi                            
	mov    esi,DWORD PTR [esp+0x20]                           
	mov    DWORD PTR [esp+0x8],edi                            
	mov    edi,DWORD PTR [esp+0x1c]                           
	mov    DWORD PTR [esp+0xc],ebp                            
	mov    ecx,DWORD PTR [esp+0x14]                           
	sub    edx,ebx                                            
	mov    ebp,ebx                                            
	lea    eax,[esi+esi*1]                                    
	neg    eax                                                
	imul   edx,esi                                            
	add    eax,DWORD PTR [esp+0x18]                           
	imul   ebp,edi                                            
	pxor   mm7,mm7                                            
	movd   mm0,DWORD PTR [eax]                                
	add    eax,esi                                            
	movd   mm1,DWORD PTR [eax]                                
	add    eax,esi                                            
	movd   mm2,DWORD PTR [eax]                                
	add    eax,esi                                            
	movd   mm3,DWORD PTR [eax]                                
	add    eax,esi                                            
	movd   mm4,DWORD PTR [eax]                                
	add    eax,esi                                            
	punpcklbw mm0,mm7                                         
	punpcklbw mm1,mm7                                         
	punpcklbw mm2,mm7                                         
	punpcklbw mm3,mm7                                         
	punpcklbw mm4,mm7                                         
	movq   mm6,mm2                                            
	movd   mm5,DWORD PTR [eax]                                
	paddw  mm6,mm3                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm1                                            
	psubw  mm6,mm4                                            
	punpcklbw mm5,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm0,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm0,mm5                                            
	paddw  mm6,mm0                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm3                                            
	movd   mm0,DWORD PTR [eax]                                
	paddw  mm6,mm4                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm2                                            
	psubw  mm6,mm5                                            
	punpcklbw mm0,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm1,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm1,mm0                                            
	paddw  mm6,mm1                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm4                                            
	movd   mm1,DWORD PTR [eax]                                
	paddw  mm6,mm5                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm3                                            
	psubw  mm6,mm0                                            
	punpcklbw mm1,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm2,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm2,mm1                                            
	paddw  mm6,mm2                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm5                                            
	movd   mm2,DWORD PTR [eax]                                
	paddw  mm6,mm0                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm4                                            
	psubw  mm6,mm1                                            
	punpcklbw mm2,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm3,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm3,mm2                                            
	paddw  mm6,mm3                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm0                                            
	movd   mm3,DWORD PTR [eax]                                
	paddw  mm6,mm1                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm5                                            
	psubw  mm6,mm2                                            
	punpcklbw mm3,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm4,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm4,mm3                                            
	paddw  mm6,mm4                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm1                                            
	movd   mm4,DWORD PTR [eax]                                
	paddw  mm6,mm2                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm0                                            
	psubw  mm6,mm3                                            
	punpcklbw mm4,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm5,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm5,mm4                                            
	paddw  mm6,mm5                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm2                                            
	movd   mm5,DWORD PTR [eax]                                
	paddw  mm6,mm3                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm1                                            
	psubw  mm6,mm4                                            
	punpcklbw mm5,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm0,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm0,mm5                                            
	paddw  mm6,mm0                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm3                                            
	movd   mm0,DWORD PTR [eax]                                
	paddw  mm6,mm4                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm2                                            
	psubw  mm6,mm5                                            
	punpcklbw mm0,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm1,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm1,mm0                                            
	paddw  mm6,mm1                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	cmp    ebx,0x10                                           
	jne    put_h264_qpel8or16_v_lowpass_3dnow_3f47e           
	movq   mm6,mm4                                            
	movd   mm1,DWORD PTR [eax]                                
	paddw  mm6,mm5                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm3                                            
	psubw  mm6,mm0                                            
	punpcklbw mm1,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm2,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm2,mm1                                            
	paddw  mm6,mm2                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm5                                            
	movd   mm2,DWORD PTR [eax]                                
	paddw  mm6,mm0                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm4                                            
	psubw  mm6,mm1                                            
	punpcklbw mm2,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm3,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm3,mm2                                            
	paddw  mm6,mm3                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm0                                            
	movd   mm3,DWORD PTR [eax]                                
	paddw  mm6,mm1                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm5                                            
	psubw  mm6,mm2                                            
	punpcklbw mm3,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm4,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm4,mm3                                            
	paddw  mm6,mm4                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm1                                            
	movd   mm4,DWORD PTR [eax]                                
	paddw  mm6,mm2                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm0                                            
	psubw  mm6,mm3                                            
	punpcklbw mm4,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm5,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm5,mm4                                            
	paddw  mm6,mm5                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm2                                            
	movd   mm5,DWORD PTR [eax]                                
	paddw  mm6,mm3                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm1                                            
	psubw  mm6,mm4                                            
	punpcklbw mm5,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm0,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm0,mm5                                            
	paddw  mm6,mm0                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm3                                            
	movd   mm0,DWORD PTR [eax]                                
	paddw  mm6,mm4                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm2                                            
	psubw  mm6,mm5                                            
	punpcklbw mm0,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm1,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm1,mm0                                            
	paddw  mm6,mm1                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm4                                            
	movd   mm1,DWORD PTR [eax]                                
	paddw  mm6,mm5                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm3                                            
	psubw  mm6,mm0                                            
	punpcklbw mm1,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm2,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm2,mm1                                            
	paddw  mm6,mm2                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm5                                            
	movd   mm2,DWORD PTR [eax]                                
	paddw  mm6,mm0                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm4                                            
	psubw  mm6,mm1                                            
	punpcklbw mm2,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm3,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm3,mm2                                            
	paddw  mm6,mm3                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
put_h264_qpel8or16_v_lowpass_3dnow_3f47e:                 
	sub    ecx,ebp                                            
	lea    eax,[eax+edx*1+0x4]                                
	add    ecx,0x4                                            
	pxor   mm7,mm7                                            
	movd   mm0,DWORD PTR [eax]                                
	add    eax,esi                                            
	movd   mm1,DWORD PTR [eax]                                
	add    eax,esi                                            
	movd   mm2,DWORD PTR [eax]                                
	add    eax,esi                                            
	movd   mm3,DWORD PTR [eax]                                
	add    eax,esi                                            
	movd   mm4,DWORD PTR [eax]                                
	add    eax,esi                                            
	punpcklbw mm0,mm7                                         
	punpcklbw mm1,mm7                                         
	punpcklbw mm2,mm7                                         
	punpcklbw mm3,mm7                                         
	punpcklbw mm4,mm7                                         
	movq   mm6,mm2                                            
	movd   mm5,DWORD PTR [eax]                                
	paddw  mm6,mm3                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm1                                            
	psubw  mm6,mm4                                            
	punpcklbw mm5,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm0,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm0,mm5                                            
	paddw  mm6,mm0                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm3                                            
	movd   mm0,DWORD PTR [eax]                                
	paddw  mm6,mm4                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm2                                            
	psubw  mm6,mm5                                            
	punpcklbw mm0,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm1,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm1,mm0                                            
	paddw  mm6,mm1                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm4                                            
	movd   mm1,DWORD PTR [eax]                                
	paddw  mm6,mm5                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm3                                            
	psubw  mm6,mm0                                            
	punpcklbw mm1,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm2,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm2,mm1                                            
	paddw  mm6,mm2                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm5                                            
	movd   mm2,DWORD PTR [eax]                                
	paddw  mm6,mm0                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm4                                            
	psubw  mm6,mm1                                            
	punpcklbw mm2,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm3,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm3,mm2                                            
	paddw  mm6,mm3                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm0                                            
	movd   mm3,DWORD PTR [eax]                                
	paddw  mm6,mm1                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm5                                            
	psubw  mm6,mm2                                            
	punpcklbw mm3,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm4,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm4,mm3                                            
	paddw  mm6,mm4                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm1                                            
	movd   mm4,DWORD PTR [eax]                                
	paddw  mm6,mm2                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm0                                            
	psubw  mm6,mm3                                            
	punpcklbw mm4,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm5,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm5,mm4                                            
	paddw  mm6,mm5                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm2                                            
	movd   mm5,DWORD PTR [eax]                                
	paddw  mm6,mm3                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm1                                            
	psubw  mm6,mm4                                            
	punpcklbw mm5,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm0,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm0,mm5                                            
	paddw  mm6,mm0                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm3                                            
	movd   mm0,DWORD PTR [eax]                                
	paddw  mm6,mm4                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm2                                            
	psubw  mm6,mm5                                            
	punpcklbw mm0,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm1,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm1,mm0                                            
	paddw  mm6,mm1                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	cmp    ebx,0x10                                           
	jne    put_h264_qpel8or16_v_lowpass_3dnow_3f83b           
	movq   mm6,mm4                                            
	movd   mm1,DWORD PTR [eax]                                
	paddw  mm6,mm5                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm3                                            
	psubw  mm6,mm0                                            
	punpcklbw mm1,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm2,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm2,mm1                                            
	paddw  mm6,mm2                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm5                                            
	movd   mm2,DWORD PTR [eax]                                
	paddw  mm6,mm0                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm4                                            
	psubw  mm6,mm1                                            
	punpcklbw mm2,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm3,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm3,mm2                                            
	paddw  mm6,mm3                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm0                                            
	movd   mm3,DWORD PTR [eax]                                
	paddw  mm6,mm1                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm5                                            
	psubw  mm6,mm2                                            
	punpcklbw mm3,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm4,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm4,mm3                                            
	paddw  mm6,mm4                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm1                                            
	movd   mm4,DWORD PTR [eax]                                
	paddw  mm6,mm2                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm0                                            
	psubw  mm6,mm3                                            
	punpcklbw mm4,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm5,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm5,mm4                                            
	paddw  mm6,mm5                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm2                                            
	movd   mm5,DWORD PTR [eax]                                
	paddw  mm6,mm3                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm1                                            
	psubw  mm6,mm4                                            
	punpcklbw mm5,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm0,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm0,mm5                                            
	paddw  mm6,mm0                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm3                                            
	movd   mm0,DWORD PTR [eax]                                
	paddw  mm6,mm4                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm2                                            
	psubw  mm6,mm5                                            
	punpcklbw mm0,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm1,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm1,mm0                                            
	paddw  mm6,mm1                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm4                                            
	movd   mm1,DWORD PTR [eax]                                
	paddw  mm6,mm5                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm3                                            
	psubw  mm6,mm0                                            
	punpcklbw mm1,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm2,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm2,mm1                                            
	paddw  mm6,mm2                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
	movq   mm6,mm5                                            
	movd   mm2,DWORD PTR [eax]                                
	paddw  mm6,mm0                                            
	psllw  mm6,0x2                                            
	psubw  mm6,mm4                                            
	psubw  mm6,mm1                                            
	punpcklbw mm2,mm7                                         
	pmullw mm6,QWORD PTR [ff_pw_5]                               
	paddw  mm3,QWORD PTR [ff_pw_16]                               
	add    eax,esi                                            
	paddw  mm3,mm2                                            
	paddw  mm6,mm3                                            
	psraw  mm6,0x5                                            
	packuswb mm6,mm6                                          
	movd   DWORD PTR [ecx],mm6                                
	add    ecx,edi                                            
put_h264_qpel8or16_v_lowpass_3dnow_3f83b:                  
	mov    ebx,DWORD PTR [esp]                                
	mov    esi,DWORD PTR [esp+0x4]                            
	mov    edi,DWORD PTR [esp+0x8]                            
	mov    ebp,DWORD PTR [esp+0xc]                            
	add    esp,0x10                                           
	ret                                                       
	}
}
void put_h264_qpel8_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	put_h264_qpel8or16_v_lowpass_3dnow(dst , src , dstStride, srcStride, 8);
}
void put_h264_qpel16_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	put_h264_qpel8or16_v_lowpass_3dnow(dst , src , dstStride, srcStride, 16);
	put_h264_qpel8or16_v_lowpass_3dnow(dst+8, src+8, dstStride, srcStride, 16);
}
void put_h264_qpel16_h_lowpass_l2_3dnow(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{ 
	put_h264_qpel8_h_lowpass_l2_3dnow(dst , src , src2 , dstStride, src2Stride);
	put_h264_qpel8_h_lowpass_l2_3dnow(dst+8, src+8, src2+8, dstStride, src2Stride);
	src += 8*dstStride;
	dst += 8*dstStride;
	src2 += 8*src2Stride;
	put_h264_qpel8_h_lowpass_l2_3dnow(dst , src , src2 , dstStride, src2Stride);
	put_h264_qpel8_h_lowpass_l2_3dnow(dst+8, src+8, src2+8, dstStride, src2Stride);
}
void __declspec(naked) put_h264_qpel8or16_hv_lowpass_3dnow(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride, int size)
{
	__asm{
	push   ebp                                                     
	push   edi                                                     
	push   esi                                                     
	push   ebx                                                     
	sub    esp,0x8                                                 
	mov    edi,DWORD PTR [esp+0x34]                                
	mov    ebp,DWORD PTR [esp+0x20]                                
	mov    esi,DWORD PTR [esp+0x30]                                
	lea    ebx,[edi+0x8]                                           
	sar    ebx,0x2                                                 
	test   ebx,ebx                                                 
	je     put_h264_qpel8or16_hv_lowpass_3dnow_41d96               
	mov    eax,DWORD PTR [esp+0x24]                                
	mov    edx,esi                                                 
	mov    ecx,ebp                                                 
	not    edx                                                     
	mov    DWORD PTR [esp+0x4],ebp                                 
	lea    eax,[eax+edx*2]                                         
	mov    edx,0xfffffffb                                          
	sub    edx,edi                                                 
	imul   edx,esi                                                 
	add    edx,0x4                                                 
	mov    DWORD PTR [esp],edx                                     
	mov    ebp,DWORD PTR [esp]                                     
	xor    edx,edx                                                 
	nop                                                            
put_h264_qpel8or16_hv_lowpass_3dnow_41a28:                      
	pxor   mm7,mm7                                                 
	movd   mm0,DWORD PTR [eax]                                     
	add    eax,esi                                                 
	movd   mm1,DWORD PTR [eax]                                     
	add    eax,esi                                                 
	movd   mm2,DWORD PTR [eax]                                     
	add    eax,esi                                                 
	movd   mm3,DWORD PTR [eax]                                     
	add    eax,esi                                                 
	movd   mm4,DWORD PTR [eax]                                     
	add    eax,esi                                                 
	punpcklbw mm0,mm7                                              
	punpcklbw mm1,mm7                                              
	punpcklbw mm2,mm7                                              
	punpcklbw mm3,mm7                                              
	punpcklbw mm4,mm7                                              
	movq   mm6,mm2                                                 
	movd   mm5,DWORD PTR [eax]                                     
	paddw  mm6,mm3                                                 
	psllw  mm6,0x2                                                 
	paddw  mm0,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm1                                                 
	psubw  mm6,mm4                                                 
	punpcklbw mm5,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm0,mm5                                                 
	add    eax,esi                                                 
	paddw  mm6,mm0                                                 
	movq   QWORD PTR [ecx],mm6                                     
	movq   mm6,mm3                                                 
	movd   mm0,DWORD PTR [eax]                                     
	paddw  mm6,mm4                                                 
	psllw  mm6,0x2                                                 
	paddw  mm1,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm2                                                 
	psubw  mm6,mm5                                                 
	punpcklbw mm0,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm1,mm0                                                 
	add    eax,esi                                                 
	paddw  mm6,mm1                                                 
	movq   QWORD PTR [ecx+0x30],mm6                                
	movq   mm6,mm4                                                 
	movd   mm1,DWORD PTR [eax]                                     
	paddw  mm6,mm5                                                 
	psllw  mm6,0x2                                                 
	paddw  mm2,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm3                                                 
	psubw  mm6,mm0                                                 
	punpcklbw mm1,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm2,mm1                                                 
	add    eax,esi                                                 
	paddw  mm6,mm2                                                 
	movq   QWORD PTR [ecx+0x60],mm6                                
	movq   mm6,mm5                                                 
	movd   mm2,DWORD PTR [eax]                                     
	paddw  mm6,mm0                                                 
	psllw  mm6,0x2                                                 
	paddw  mm3,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm4                                                 
	psubw  mm6,mm1                                                 
	punpcklbw mm2,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm3,mm2                                                 
	add    eax,esi                                                 
	paddw  mm6,mm3                                                 
	movq   QWORD PTR [ecx+0x90],mm6                                
	movq   mm6,mm0                                                 
	movd   mm3,DWORD PTR [eax]                                     
	paddw  mm6,mm1                                                 
	psllw  mm6,0x2                                                 
	paddw  mm4,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm5                                                 
	psubw  mm6,mm2                                                 
	punpcklbw mm3,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm4,mm3                                                 
	add    eax,esi                                                 
	paddw  mm6,mm4                                                 
	movq   QWORD PTR [ecx+0xc0],mm6                                
	movq   mm6,mm1                                                 
	movd   mm4,DWORD PTR [eax]                                     
	paddw  mm6,mm2                                                 
	psllw  mm6,0x2                                                 
	paddw  mm5,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm0                                                 
	psubw  mm6,mm3                                                 
	punpcklbw mm4,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm5,mm4                                                 
	add    eax,esi                                                 
	paddw  mm6,mm5                                                 
	movq   QWORD PTR [ecx+0xf0],mm6                                
	movq   mm6,mm2                                                 
	movd   mm5,DWORD PTR [eax]                                     
	paddw  mm6,mm3                                                 
	psllw  mm6,0x2                                                 
	paddw  mm0,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm1                                                 
	psubw  mm6,mm4                                                 
	punpcklbw mm5,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm0,mm5                                                 
	add    eax,esi                                                 
	paddw  mm6,mm0                                                 
	movq   QWORD PTR [ecx+0x120],mm6                               
	movq   mm6,mm3                                                 
	movd   mm0,DWORD PTR [eax]                                     
	paddw  mm6,mm4                                                 
	psllw  mm6,0x2                                                 
	paddw  mm1,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm2                                                 
	psubw  mm6,mm5                                                 
	punpcklbw mm0,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm1,mm0                                                 
	add    eax,esi                                                 
	paddw  mm6,mm1                                                 
	movq   QWORD PTR [ecx+0x150],mm6                               
	cmp    edi,0x10                                                
	jne    put_h264_qpel8or16_hv_lowpass_3dnow_41d82               
	movq   mm6,mm4                                                 
	movd   mm1,DWORD PTR [eax]                                     
	paddw  mm6,mm5                                                 
	psllw  mm6,0x2                                                 
	paddw  mm2,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm3                                                 
	psubw  mm6,mm0                                                 
	punpcklbw mm1,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm2,mm1                                                 
	add    eax,esi                                                 
	paddw  mm6,mm2                                                 
	movq   QWORD PTR [ecx+0x180],mm6                               
	movq   mm6,mm5                                                 
	movd   mm2,DWORD PTR [eax]                                     
	paddw  mm6,mm0                                                 
	psllw  mm6,0x2                                                 
	paddw  mm3,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm4                                                 
	psubw  mm6,mm1                                                 
	punpcklbw mm2,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm3,mm2                                                 
	add    eax,esi                                                 
	paddw  mm6,mm3                                                 
	movq   QWORD PTR [ecx+0x1b0],mm6                               
	movq   mm6,mm0                                                 
	movd   mm3,DWORD PTR [eax]                                     
	paddw  mm6,mm1                                                 
	psllw  mm6,0x2                                                 
	paddw  mm4,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm5                                                 
	psubw  mm6,mm2                                                 
	punpcklbw mm3,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm4,mm3                                                 
	add    eax,esi                                                 
	paddw  mm6,mm4                                                 
	movq   QWORD PTR [ecx+0x1e0],mm6                               
	movq   mm6,mm1                                                 
	movd   mm4,DWORD PTR [eax]                                     
	paddw  mm6,mm2                                                 
	psllw  mm6,0x2                                                 
	paddw  mm5,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm0                                                 
	psubw  mm6,mm3                                                 
	punpcklbw mm4,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm5,mm4                                                 
	add    eax,esi                                                 
	paddw  mm6,mm5                                                 
	movq   QWORD PTR [ecx+0x210],mm6                               
	movq   mm6,mm2                                                 
	movd   mm5,DWORD PTR [eax]                                     
	paddw  mm6,mm3                                                 
	psllw  mm6,0x2                                                 
	paddw  mm0,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm1                                                 
	psubw  mm6,mm4                                                 
	punpcklbw mm5,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm0,mm5                                                 
	add    eax,esi                                                 
	paddw  mm6,mm0                                                 
	movq   QWORD PTR [ecx+0x240],mm6                               
	movq   mm6,mm3                                                 
	movd   mm0,DWORD PTR [eax]                                     
	paddw  mm6,mm4                                                 
	psllw  mm6,0x2                                                 
	paddw  mm1,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm2                                                 
	psubw  mm6,mm5                                                 
	punpcklbw mm0,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm1,mm0                                                 
	add    eax,esi                                                 
	paddw  mm6,mm1                                                 
	movq   QWORD PTR [ecx+0x270],mm6                               
	movq   mm6,mm4                                                 
	movd   mm1,DWORD PTR [eax]                                     
	paddw  mm6,mm5                                                 
	psllw  mm6,0x2                                                 
	paddw  mm2,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm3                                                 
	psubw  mm6,mm0                                                 
	punpcklbw mm1,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm2,mm1                                                 
	add    eax,esi                                                 
	paddw  mm6,mm2                                                 
	movq   QWORD PTR [ecx+0x2a0],mm6                               
	movq   mm6,mm5                                                 
	movd   mm2,DWORD PTR [eax]                                     
	paddw  mm6,mm0                                                 
	psllw  mm6,0x2                                                 
	paddw  mm3,QWORD PTR [ff_pw_16]                                    
	psubw  mm6,mm4                                                 
	psubw  mm6,mm1                                                 
	punpcklbw mm2,mm7                                              
	pmullw mm6,QWORD PTR [ff_pw_5]                                    
	paddw  mm3,mm2                                                 
	add    eax,esi                                                 
	paddw  mm6,mm3                                                 
	movq   QWORD PTR [ecx+0x2d0],mm6                               
put_h264_qpel8or16_hv_lowpass_3dnow_41d82:	                     
	add    edx,0x1                                                 
	add    ecx,0x8                                                 
	add    eax,ebp                                                 
	cmp    edx,ebx                                                 
	jne    put_h264_qpel8or16_hv_lowpass_3dnow_41a28               
	mov    ebp,DWORD PTR [esp+0x4]                                 
put_h264_qpel8or16_hv_lowpass_3dnow_41d96:                      
	lea    eax,[edi+edi*2]                                         
	mov    ecx,DWORD PTR [esp+0x1c]                                
	mov    edx,0x8                                                 
	neg    eax                                                     
	mov    esi,DWORD PTR [esp+0x28]                                
	mov    ebx,edi                                                 
	add    eax,0x1                                                 
	shl    eax,0x4                                                 
	mov    DWORD PTR [esp],eax                                     
	mov    eax,DWORD PTR [esp+0x28]                                
	sar    ebx,0x4                                                 
	imul   eax,edi                                                 
	sub    edx,eax                                                 
	mov    eax,ebp                                                 
	mov    ebp,edx                                                 
	nop                                                            
	lea    esi,[esi+0x0]                                     
put_h264_qpel8or16_hv_lowpass_3dnow_41dc8:                      
	mov    edx,edi                                                 
put_h264_qpel8or16_hv_lowpass_3dnow_41dca:                      
	movq   mm0,QWORD PTR [eax]                                     
	movq   mm3,QWORD PTR [eax+0x8]                                 
	movq   mm1,QWORD PTR [eax+0x2]                                 
	movq   mm4,QWORD PTR [eax+0xa]                                 
	paddw  mm0,mm4                                                 
	paddw  mm1,mm3                                                 
	paddw  mm3,QWORD PTR [eax+0x12]                                
	paddw  mm4,QWORD PTR [eax+0x10]                                
	movq   mm2,QWORD PTR [eax+0x4]                                 
	movq   mm5,QWORD PTR [eax+0xc]                                 
	paddw  mm2,QWORD PTR [eax+0x6]                                 
	paddw  mm5,QWORD PTR [eax+0xe]                                 
	psubw  mm0,mm1                                                 
	psubw  mm3,mm4                                                 
	psraw  mm0,0x2                                                 
	psraw  mm3,0x2                                                 
	psubw  mm0,mm1                                                 
	psubw  mm3,mm4                                                 
	paddsw mm0,mm2                                                 
	paddsw mm3,mm5                                                 
	psraw  mm0,0x2                                                 
	psraw  mm3,0x2                                                 
	paddw  mm0,mm2                                                 
	paddw  mm3,mm5                                                 
	psraw  mm0,0x6                                                 
	psraw  mm3,0x6                                                 
	packuswb mm0,mm3                                               
	movq   QWORD PTR [ecx],mm0                                     
	add    eax,0x30                                                
	add    ecx,esi                                                 
	dec    edx                                                     
	jne    put_h264_qpel8or16_hv_lowpass_3dnow_41dca               
	sub    ebx,0x1                                                 
	add    ecx,ebp                                                 
	add    eax,DWORD PTR [esp]                                     
	cmp    ebx,0xffffffff                                          
	jne    put_h264_qpel8or16_hv_lowpass_3dnow_41dc8               
	add    esp,0x8                                                 
	pop    ebx                                                     
	pop    esi                                                     
	pop    edi                                                     
	pop    ebp                                                     
	ret                                                            
 }
}
void put_h264_qpel8_hv_lowpass_3dnow(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	put_h264_qpel8or16_hv_lowpass_3dnow(dst , tmp , src , dstStride, tmpStride, srcStride, 8);
}
void put_h264_qpel16_hv_lowpass_3dnow(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	put_h264_qpel8or16_hv_lowpass_3dnow(dst , tmp , src , dstStride, tmpStride, srcStride, 16);
}
void __declspec(naked) put_pixels4_l2_shift5_3dnow(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
	__asm{
	sub    esp,0x8                     
	mov    DWORD PTR [esp],esi         
	mov    edx,DWORD PTR [esp+0xc]     
	mov    DWORD PTR [esp+0x4],edi     
	mov    ecx,DWORD PTR [esp+0x10]    
	mov    eax,DWORD PTR [esp+0x14]    
	mov    esi,DWORD PTR [esp+0x1c]    
	mov    edi,DWORD PTR [esp+0x18]    
	movq   mm0,QWORD PTR [ecx]         
	movq   mm1,QWORD PTR [ecx+0x18]    
	psraw  mm0,0x5                     
	psraw  mm1,0x5                     
	packuswb mm0,mm0                   
	packuswb mm1,mm1                   
	pavgusb mm0,QWORD PTR [eax]        
	pavgusb mm1,QWORD PTR [eax+esi*1]  
	movd   DWORD PTR [edx],mm0         
	movd   DWORD PTR [edx+edi*1],mm1   
	lea    eax,[eax+esi*2]             
	lea    edx,[edx+edi*2]             
	movq   mm0,QWORD PTR [ecx+0x30]    
	movq   mm1,QWORD PTR [ecx+0x48]    
	psraw  mm0,0x5                     
	psraw  mm1,0x5                     
	packuswb mm0,mm0                   
	packuswb mm1,mm1                   
	pavgusb mm0,QWORD PTR [eax]        
	pavgusb mm1,QWORD PTR [eax+esi*1]  
	movd   DWORD PTR [edx],mm0         
	movd   DWORD PTR [edx+edi*1],mm1   
	mov    esi,DWORD PTR [esp]         
	mov    edi,DWORD PTR [esp+0x4]     
	add    esp,0x8                     
	ret                                
	}
}
void __declspec(naked) put_pixels8_l2_shift5_3dnow(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
	__asm{
 	sub    esp,0x14                        
 	mov    DWORD PTR [esp+0xc],edi         
 	mov    edi,DWORD PTR [esp+0x24]        
 	mov    DWORD PTR [esp+0x8],esi         
 	mov    esi,DWORD PTR [esp+0x28]        
 	mov    DWORD PTR [esp+0x4],ebx         
 	mov    edx,DWORD PTR [esp+0x18]        
 	mov    ecx,DWORD PTR [esp+0x1c]        
 	lea    eax,[edi+edi*1]                 
 	mov    ebx,DWORD PTR [esp+0x2c]        
 	mov    DWORD PTR [esp],eax             
 	mov    eax,DWORD PTR [esp+0x20]        
 	mov    DWORD PTR [esp+0x10],ebp        
 	lea    ebp,[esi+esi*1]                 
 	lea    esi,[esi+0x0]             
 put_pixels8_l2_shift5_3dnowflag:        
 	movq   mm0,QWORD PTR [ecx]             
 	movq   mm1,QWORD PTR [ecx+0x8]         
 	movq   mm2,QWORD PTR [ecx+0x30]        
 	movq   mm3,QWORD PTR [ecx+0x38]        
 	psraw  mm0,0x5                         
 	psraw  mm1,0x5                         
 	psraw  mm2,0x5                         
 	psraw  mm3,0x5                         
 	packuswb mm0,mm1                       
 	packuswb mm2,mm3                       
 	pavgusb mm0,QWORD PTR [eax]            
 	pavgusb mm2,QWORD PTR [eax+esi*1]      
 	movq   QWORD PTR [edx],mm0             
 	movq   QWORD PTR [edx+edi*1],mm2       
 	add    eax,ebp                         
 	add    ecx,0x60                        
 	add    edx,DWORD PTR [esp]             
 	sub    ebx,0x2                         
 	jne    put_pixels8_l2_shift5_3dnowflag 
 	mov    ebx,DWORD PTR [esp+0x4]         
 	mov    esi,DWORD PTR [esp+0x8]         
 	mov    edi,DWORD PTR [esp+0xc]         
 	mov    ebp,DWORD PTR [esp+0x10]        
 	add    esp,0x14                        
 	ret                                    
	}
}

void __declspec(naked) put_h264_qpel4_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                          
	mov    DWORD PTR [esp],ebx              
	mov    ecx,DWORD PTR [esp+0xc]          
	mov    ebx,0x4                          
	mov    DWORD PTR [esp+0x4],esi          
	mov    eax,DWORD PTR [esp+0x10]         
	mov    edx,DWORD PTR [esp+0x18]         
	mov    esi,DWORD PTR [esp+0x14]         
	pxor   mm7,mm7                          
	movq   mm4,QWORD PTR [ff_pw_5]            
	movq   mm5,QWORD PTR [ff_pw_16]            
put_h264_qpel4_h_lowpass_mmx2flag:       
	movd   mm1,DWORD PTR [eax-0x1]          
	movd   mm2,DWORD PTR [eax]              
	movd   mm3,DWORD PTR [eax+0x1]          
	movd   mm0,DWORD PTR [eax+0x2]          
	punpcklbw mm1,mm7                       
	punpcklbw mm2,mm7                       
	punpcklbw mm3,mm7                       
	punpcklbw mm0,mm7                       
	paddw  mm1,mm0                          
	paddw  mm2,mm3                          
	movd   mm0,DWORD PTR [eax-0x2]          
	movd   mm3,DWORD PTR [eax+0x3]          
	punpcklbw mm0,mm7                       
	punpcklbw mm3,mm7                       
	paddw  mm0,mm3                          
	psllw  mm2,0x2                          
	psubw  mm2,mm1                          
	pmullw mm2,mm4                          
	paddw  mm0,mm5                          
	paddw  mm0,mm2                          
	psraw  mm0,0x5                          
	packuswb mm0,mm0                        
	movd   DWORD PTR [ecx],mm0              
	add    eax,edx                          
	add    ecx,esi                          
	dec    ebx                              
	jne    put_h264_qpel4_h_lowpass_mmx2flag
	mov    ebx,DWORD PTR [esp]              
	mov    esi,DWORD PTR [esp+0x4]          
	add    esp,0x8                          
	ret
	}
}
void __declspec(naked) put_h264_qpel4_h_lowpass_l2_mmx2(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
		sub    esp,0x8                      
	mov    DWORD PTR [esp],esi          
	mov    ecx,DWORD PTR [esp+0xc]      
	mov    DWORD PTR [esp+0x4],edi      
	mov    eax,DWORD PTR [esp+0x10]     
	mov    edx,DWORD PTR [esp+0x14]     
	mov    esi,DWORD PTR [esp+0x18]     
	mov    edi,DWORD PTR [esp+0x1c]     
	pxor   mm7,mm7                      
	movq   mm4,QWORD PTR [ff_pw_5]
	movq   mm5,QWORD PTR [ff_pw_16]
	movd   mm1,DWORD PTR [eax-0x1]      
	movd   mm2,DWORD PTR [eax]          
	movd   mm3,DWORD PTR [eax+0x1]      
	movd   mm0,DWORD PTR [eax+0x2]      
	punpcklbw mm1,mm7                   
	punpcklbw mm2,mm7                   
	punpcklbw mm3,mm7                   
	punpcklbw mm0,mm7                   
	paddw  mm1,mm0                      
	paddw  mm2,mm3                      
	movd   mm0,DWORD PTR [eax-0x2]      
	movd   mm3,DWORD PTR [eax+0x3]      
	punpcklbw mm0,mm7                   
	punpcklbw mm3,mm7                   
	paddw  mm0,mm3                      
	psllw  mm2,0x2                      
	psubw  mm2,mm1                      
	pmullw mm2,mm4                      
	paddw  mm0,mm5                      
	paddw  mm0,mm2                      
	movd   mm3,DWORD PTR [edx]          
	psraw  mm0,0x5                      
	packuswb mm0,mm0                    
	pavgb  mm0,mm3                      
	movd   DWORD PTR [ecx],mm0          
	add    eax,esi                      
	add    ecx,esi                      
	add    edx,edi                      
	movd   mm1,DWORD PTR [eax-0x1]      
	movd   mm2,DWORD PTR [eax]          
	movd   mm3,DWORD PTR [eax+0x1]      
	movd   mm0,DWORD PTR [eax+0x2]      
	punpcklbw mm1,mm7                   
	punpcklbw mm2,mm7                   
	punpcklbw mm3,mm7                   
	punpcklbw mm0,mm7                   
	paddw  mm1,mm0                      
	paddw  mm2,mm3                      
	movd   mm0,DWORD PTR [eax-0x2]      
	movd   mm3,DWORD PTR [eax+0x3]      
	punpcklbw mm0,mm7                   
	punpcklbw mm3,mm7                   
	paddw  mm0,mm3                      
	psllw  mm2,0x2                      
	psubw  mm2,mm1                      
	pmullw mm2,mm4                      
	paddw  mm0,mm5                      
	paddw  mm0,mm2                      
	movd   mm3,DWORD PTR [edx]          
	psraw  mm0,0x5                      
	packuswb mm0,mm0                    
	pavgb  mm0,mm3                      
	movd   DWORD PTR [ecx],mm0          
	add    eax,esi                      
	add    ecx,esi                      
	add    edx,edi                      
	movd   mm1,DWORD PTR [eax-0x1]      
	movd   mm2,DWORD PTR [eax]          
	movd   mm3,DWORD PTR [eax+0x1]      
	movd   mm0,DWORD PTR [eax+0x2]      
	punpcklbw mm1,mm7                   
	punpcklbw mm2,mm7                   
	punpcklbw mm3,mm7                   
	punpcklbw mm0,mm7                   
	paddw  mm1,mm0                      
	paddw  mm2,mm3                      
	movd   mm0,DWORD PTR [eax-0x2]      
	movd   mm3,DWORD PTR [eax+0x3]      
	punpcklbw mm0,mm7                   
	punpcklbw mm3,mm7                   
	paddw  mm0,mm3                      
	psllw  mm2,0x2                      
	psubw  mm2,mm1                      
	pmullw mm2,mm4                      
	paddw  mm0,mm5                      
	paddw  mm0,mm2                      
	movd   mm3,DWORD PTR [edx]          
	psraw  mm0,0x5                      
	packuswb mm0,mm0                    
	pavgb  mm0,mm3                      
	movd   DWORD PTR [ecx],mm0          
	add    eax,esi                      
	add    ecx,esi                      
	add    edx,edi                      
	movd   mm1,DWORD PTR [eax-0x1]      
	movd   mm2,DWORD PTR [eax]          
	movd   mm3,DWORD PTR [eax+0x1]      
	movd   mm0,DWORD PTR [eax+0x2]      
	punpcklbw mm1,mm7                   
	punpcklbw mm2,mm7                   
	punpcklbw mm3,mm7                   
	punpcklbw mm0,mm7                   
	paddw  mm1,mm0                      
	paddw  mm2,mm3                      
	movd   mm0,DWORD PTR [eax-0x2]      
	movd   mm3,DWORD PTR [eax+0x3]      
	punpcklbw mm0,mm7                   
	punpcklbw mm3,mm7                   
	paddw  mm0,mm3                      
	psllw  mm2,0x2                      
	psubw  mm2,mm1                      
	pmullw mm2,mm4                      
	paddw  mm0,mm5                      
	paddw  mm0,mm2                      
	movd   mm3,DWORD PTR [edx]          
	psraw  mm0,0x5                      
	packuswb mm0,mm0                    
	pavgb  mm0,mm3                      
	movd   DWORD PTR [ecx],mm0          
	add    eax,esi                      
	add    ecx,esi                      
	add    edx,edi                      
	mov    esi,DWORD PTR [esp]          
	mov    edi,DWORD PTR [esp+0x4]      
	add    esp,0x8                      
	ret
	}
}
void __declspec(naked) put_h264_qpel4_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                           
	mov    DWORD PTR [esp],esi               
	mov    esi,DWORD PTR [esp+0x18]          
	mov    DWORD PTR [esp+0x4],edi           
	mov    ecx,DWORD PTR [esp+0xc]           
	mov    edi,DWORD PTR [esp+0x14]          
	lea    eax,[esi+esi*1]                   
	neg    eax                               
	add    eax,DWORD PTR [esp+0x10]          
	pxor   mm7,mm7                           
	movd   mm0,DWORD PTR [eax]               
	add    eax,esi                           
	movd   mm1,DWORD PTR [eax]               
	add    eax,esi                           
	movd   mm2,DWORD PTR [eax]               
	add    eax,esi                           
	movd   mm3,DWORD PTR [eax]               
	add    eax,esi                           
	movd   mm4,DWORD PTR [eax]               
	add    eax,esi                           
	punpcklbw mm0,mm7                        
	punpcklbw mm1,mm7                        
	punpcklbw mm2,mm7                        
	punpcklbw mm3,mm7                        
	punpcklbw mm4,mm7                        
	movq   mm6,mm2                           
	movd   mm5,DWORD PTR [eax]               
	paddw  mm6,mm3                           
	psllw  mm6,0x2                           
	psubw  mm6,mm1                           
	psubw  mm6,mm4                           
	punpcklbw mm5,mm7                        
	pmullw mm6,QWORD PTR [ff_pw_5]              
	paddw  mm0,QWORD PTR [ff_pw_16]              
	add    eax,esi                           
	paddw  mm0,mm5                           
	paddw  mm6,mm0                           
	psraw  mm6,0x5                           
	packuswb mm6,mm6                         
	movd   DWORD PTR [ecx],mm6               
	add    ecx,edi                           
	movq   mm6,mm3                           
	movd   mm0,DWORD PTR [eax]               
	paddw  mm6,mm4                           
	psllw  mm6,0x2                           
	psubw  mm6,mm2                           
	psubw  mm6,mm5                           
	punpcklbw mm0,mm7                        
	pmullw mm6,QWORD PTR [ff_pw_5]              
	paddw  mm1,QWORD PTR [ff_pw_16]              
	add    eax,esi                           
	paddw  mm1,mm0                           
	paddw  mm6,mm1                           
	psraw  mm6,0x5                           
	packuswb mm6,mm6                         
	movd   DWORD PTR [ecx],mm6               
	add    ecx,edi                           
	movq   mm6,mm4                           
	movd   mm1,DWORD PTR [eax]               
	paddw  mm6,mm5                           
	psllw  mm6,0x2                           
	psubw  mm6,mm3                           
	psubw  mm6,mm0                           
	punpcklbw mm1,mm7                        
	pmullw mm6,QWORD PTR [ff_pw_5]              
	paddw  mm2,QWORD PTR [ff_pw_16]              
	add    eax,esi                           
	paddw  mm2,mm1                           
	paddw  mm6,mm2                           
	psraw  mm6,0x5                           
	packuswb mm6,mm6                         
	movd   DWORD PTR [ecx],mm6               
	add    ecx,edi                           
	movq   mm6,mm5                           
	movd   mm2,DWORD PTR [eax]               
	paddw  mm6,mm0                           
	psllw  mm6,0x2                           
	psubw  mm6,mm4                           
	psubw  mm6,mm1                           
	punpcklbw mm2,mm7                        
	pmullw mm6,QWORD PTR [ff_pw_5]              
	paddw  mm3,QWORD PTR [ff_pw_16]              
	add    eax,esi                           
	paddw  mm3,mm2                           
	paddw  mm6,mm3                           
	psraw  mm6,0x5                           
	packuswb mm6,mm6                         
	movd   DWORD PTR [ecx],mm6               
	add    ecx,edi                           
	mov    esi,DWORD PTR [esp]               
	mov    edi,DWORD PTR [esp+0x4]           
	add    esp,0x8                           
	ret                                      
	}
}
void __declspec(naked) put_h264_qpel4_hv_lowpass_mmx2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	__asm{
	sub    esp,0xc                                 
	mov    DWORD PTR [esp+0x4],esi                 
	mov    esi,DWORD PTR [esp+0x24]                
	mov    edx,DWORD PTR [esp+0x14]                
	mov    DWORD PTR [esp],ebx                     
	mov    DWORD PTR [esp+0x8],edi                 
	mov    edi,DWORD PTR [esp+0x10]                
	mov    eax,esi                                 
	lea    ebx,[esi+esi*8]                         
	not    eax                                     
	neg    ebx                                     
	add    eax,eax                                 
	add    ebx,0x4                                 
	mov    ecx,edx                                 
	add    eax,DWORD PTR [esp+0x18]                
	pxor   mm7,mm7                                 
	movd   mm0,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm1,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm2,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm3,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm4,DWORD PTR [eax]                     
	add    eax,esi                                 
	punpcklbw mm0,mm7                              
	punpcklbw mm1,mm7                              
	punpcklbw mm2,mm7                              
	punpcklbw mm3,mm7                              
	punpcklbw mm4,mm7                              
	movq   mm6,mm2                                 
	movd   mm5,DWORD PTR [eax]                     
	paddw  mm6,mm3                                 
	psllw  mm6,0x2                                 
	paddw  mm0,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm1                                 
	psubw  mm6,mm4                                 
	punpcklbw mm5,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm0,mm5                                 
	add    eax,esi                                 
	paddw  mm6,mm0                                 
	movq   QWORD PTR [ecx],mm6                     
	movq   mm6,mm3                                 
	movd   mm0,DWORD PTR [eax]                     
	paddw  mm6,mm4                                 
	psllw  mm6,0x2                                 
	paddw  mm1,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm2                                 
	psubw  mm6,mm5                                 
	punpcklbw mm0,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm1,mm0                                 
	add    eax,esi                                 
	paddw  mm6,mm1                                 
	movq   QWORD PTR [ecx+0x18],mm6                
	movq   mm6,mm4                                 
	movd   mm1,DWORD PTR [eax]                     
	paddw  mm6,mm5                                 
	psllw  mm6,0x2                                 
	paddw  mm2,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm3                                 
	psubw  mm6,mm0                                 
	punpcklbw mm1,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm2,mm1                                 
	add    eax,esi                                 
	paddw  mm6,mm2                                 
	movq   QWORD PTR [ecx+0x30],mm6                
	movq   mm6,mm5                                 
	movd   mm2,DWORD PTR [eax]                     
	paddw  mm6,mm0                                 
	psllw  mm6,0x2                                 
	paddw  mm3,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm4                                 
	psubw  mm6,mm1                                 
	punpcklbw mm2,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm3,mm2                                 
	add    eax,esi                                 
	paddw  mm6,mm3                                 
	movq   QWORD PTR [ecx+0x48],mm6                
	lea    ecx,[edx+0x8]                           
	add    eax,ebx                                 
	pxor   mm7,mm7                                 
	movd   mm0,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm1,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm2,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm3,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm4,DWORD PTR [eax]                     
	add    eax,esi                                 
	punpcklbw mm0,mm7                              
	punpcklbw mm1,mm7                              
	punpcklbw mm2,mm7                              
	punpcklbw mm3,mm7                              
	punpcklbw mm4,mm7                              
	movq   mm6,mm2                                 
	movd   mm5,DWORD PTR [eax]                     
	paddw  mm6,mm3                                 
	psllw  mm6,0x2                                 
	paddw  mm0,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm1                                 
	psubw  mm6,mm4                                 
	punpcklbw mm5,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm0,mm5                                 
	add    eax,esi                                 
	paddw  mm6,mm0                                 
	movq   QWORD PTR [ecx],mm6                     
	movq   mm6,mm3                                 
	movd   mm0,DWORD PTR [eax]                     
	paddw  mm6,mm4                                 
	psllw  mm6,0x2                                 
	paddw  mm1,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm2                                 
	psubw  mm6,mm5                                 
	punpcklbw mm0,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm1,mm0                                 
	add    eax,esi                                 
	paddw  mm6,mm1                                 
	movq   QWORD PTR [ecx+0x18],mm6                
	movq   mm6,mm4                                 
	movd   mm1,DWORD PTR [eax]                     
	paddw  mm6,mm5                                 
	psllw  mm6,0x2                                 
	paddw  mm2,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm3                                 
	psubw  mm6,mm0                                 
	punpcklbw mm1,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm2,mm1                                 
	add    eax,esi                                 
	paddw  mm6,mm2                                 
	movq   QWORD PTR [ecx+0x30],mm6                
	movq   mm6,mm5                                 
	movd   mm2,DWORD PTR [eax]                     
	paddw  mm6,mm0                                 
	psllw  mm6,0x2                                 
	paddw  mm3,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm4                                 
	psubw  mm6,mm1                                 
	punpcklbw mm2,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm3,mm2                                 
	add    eax,esi                                 
	paddw  mm6,mm3                                 
	movq   QWORD PTR [ecx+0x48],mm6                
	add    eax,ebx                                 
	lea    ecx,[edx+0x10]                          
	pxor   mm7,mm7                                 
	movd   mm0,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm1,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm2,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm3,DWORD PTR [eax]                     
	add    eax,esi                                 
	movd   mm4,DWORD PTR [eax]                     
	add    eax,esi                                 
	punpcklbw mm0,mm7                              
	punpcklbw mm1,mm7                              
	punpcklbw mm2,mm7                              
	punpcklbw mm3,mm7                              
	punpcklbw mm4,mm7                              
	movq   mm6,mm2                                 
	movd   mm5,DWORD PTR [eax]                     
	paddw  mm6,mm3                                 
	psllw  mm6,0x2                                 
	paddw  mm0,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm1                                 
	psubw  mm6,mm4                                 
	punpcklbw mm5,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm0,mm5                                 
	add    eax,esi                                 
	paddw  mm6,mm0                                 
	movq   QWORD PTR [ecx],mm6                     
	movq   mm6,mm3                                 
	movd   mm0,DWORD PTR [eax]                     
	paddw  mm6,mm4                                 
	psllw  mm6,0x2                                 
	paddw  mm1,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm2                                 
	psubw  mm6,mm5                                 
	punpcklbw mm0,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm1,mm0                                 
	add    eax,esi                                 
	paddw  mm6,mm1                                 
	movq   QWORD PTR [ecx+0x18],mm6                
	movq   mm6,mm4                                 
	movd   mm1,DWORD PTR [eax]                     
	paddw  mm6,mm5                                 
	psllw  mm6,0x2                                 
	paddw  mm2,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm3                                 
	psubw  mm6,mm0                                 
	punpcklbw mm1,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm2,mm1                                 
	add    eax,esi                                 
	paddw  mm6,mm2                                 
	movq   QWORD PTR [ecx+0x30],mm6                
	movq   mm6,mm5                                 
	movd   mm2,DWORD PTR [eax]                     
	paddw  mm6,mm0                                 
	psllw  mm6,0x2                                 
	paddw  mm3,QWORD PTR [ff_pw_16]                    
	psubw  mm6,mm4                                 
	psubw  mm6,mm1                                 
	punpcklbw mm2,mm7                              
	pmullw mm6,QWORD PTR [ff_pw_5]                    
	paddw  mm3,mm2                                 
	add    eax,esi                                 
	paddw  mm6,mm3                                 
	movq   QWORD PTR [ecx+0x48],mm6                
	mov    eax,edx                                 
	mov    esi,DWORD PTR [esp+0x1c]                
	mov    ecx,edi                                 
	mov    edx,0x4                                 
put_h264_qpel4_hv_lowpass_mmx2loop:             
	movq   mm0,QWORD PTR [eax]                     
	paddw  mm0,QWORD PTR [eax+0xa]                 
	movq   mm1,QWORD PTR [eax+0x2]                 
	paddw  mm1,QWORD PTR [eax+0x8]                 
	movq   mm2,QWORD PTR [eax+0x4]                 
	paddw  mm2,QWORD PTR [eax+0x6]                 
	psubw  mm0,mm1                                 
	psraw  mm0,0x2                                 
	psubw  mm0,mm1                                 
	paddsw mm0,mm2                                 
	psraw  mm0,0x2                                 
	paddw  mm0,mm2                                 
	psraw  mm0,0x6                                 
	packuswb mm0,mm0                               
	movd   DWORD PTR [ecx],mm0                     
	add    eax,0x18                                
	add    ecx,esi                                 
	dec    edx                                     
	jne    put_h264_qpel4_hv_lowpass_mmx2loop      
	mov    ebx,DWORD PTR [esp]                     
	mov    esi,DWORD PTR [esp+0x4]                 
	mov    edi,DWORD PTR [esp+0x8]                 
	add    esp,0xc                                 
	ret                                            
	}
}
void __declspec(naked) put_h264_qpel8_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                            
	mov    DWORD PTR [esp],ebx                
	mov    ecx,DWORD PTR [esp+0xc]            
	mov    ebx,0x8                            
	mov    DWORD PTR [esp+0x4],esi            
	mov    eax,DWORD PTR [esp+0x10]           
	mov    edx,DWORD PTR [esp+0x18]           
	mov    esi,DWORD PTR [esp+0x14]           
	pxor   mm7,mm7                            
	movq   mm6,QWORD PTR [ff_pw_5]               
put_h264_qpel8_h_lowpass_mmx2loop:         
	movq   mm0,QWORD PTR [eax]                
	movq   mm2,QWORD PTR [eax+0x1]            
	movq   mm1,mm0                            
	movq   mm3,mm2                            
	punpcklbw mm0,mm7                         
	punpckhbw mm1,mm7                         
	punpcklbw mm2,mm7                         
	punpckhbw mm3,mm7                         
	paddw  mm0,mm2                            
	paddw  mm1,mm3                            
	psllw  mm0,0x2                            
	psllw  mm1,0x2                            
	movq   mm2,QWORD PTR [eax-0x1]            
	movq   mm4,QWORD PTR [eax+0x2]            
	movq   mm3,mm2                            
	movq   mm5,mm4                            
	punpcklbw mm2,mm7                         
	punpckhbw mm3,mm7                         
	punpcklbw mm4,mm7                         
	punpckhbw mm5,mm7                         
	paddw  mm2,mm4                            
	paddw  mm5,mm3                            
	psubw  mm0,mm2                            
	psubw  mm1,mm5                            
	pmullw mm0,mm6                            
	pmullw mm1,mm6                            
	movd   mm2,DWORD PTR [eax-0x2]            
	movd   mm5,DWORD PTR [eax+0x7]            
	punpcklbw mm2,mm7                         
	punpcklbw mm5,mm7                         
	paddw  mm2,mm3                            
	paddw  mm4,mm5                            
	movq   mm5,QWORD PTR [ff_pw_16]               
	paddw  mm2,mm5                            
	paddw  mm4,mm5                            
	paddw  mm0,mm2                            
	paddw  mm1,mm4                            
	psraw  mm0,0x5                            
	psraw  mm1,0x5                            
	packuswb mm0,mm1                          
	movq   QWORD PTR [ecx],mm0                
	add    eax,edx                            
	add    ecx,esi                            
	dec    ebx                                
	jne    put_h264_qpel8_h_lowpass_mmx2loop  
	mov    ebx,DWORD PTR [esp]                
	mov    esi,DWORD PTR [esp+0x4]            
	add    esp,0x8                            
	ret                                       
	}
}

void put_h264_qpel16_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	put_h264_qpel8_h_lowpass_mmx2(dst , src , dstStride, srcStride); 
	put_h264_qpel8_h_lowpass_mmx2(dst+8, src+8, dstStride, srcStride);
	src += 8*srcStride;
	dst += 8*dstStride; 
	put_h264_qpel8_h_lowpass_mmx2(dst , src , dstStride, srcStride); 
	put_h264_qpel8_h_lowpass_mmx2(dst+8, src+8, dstStride, srcStride);
 }
void __declspec(naked) put_h264_qpel8_h_lowpass_l2_mmx2(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0xc                                
	mov    DWORD PTR [esp],ebx                    
	mov    ecx,DWORD PTR [esp+0x10]               
	mov    ebx,0x8                                
	mov    DWORD PTR [esp+0x4],esi                
	mov    eax,DWORD PTR [esp+0x14]               
	mov    DWORD PTR [esp+0x8],edi                
	mov    edx,DWORD PTR [esp+0x18]               
	mov    edi,DWORD PTR [esp+0x20]               
	mov    esi,DWORD PTR [esp+0x1c]               
	pxor   mm7,mm7                                
	movq   mm6,QWORD PTR [ff_pw_5]                   
put_h264_qpel8_h_lowpass_l2_mmx2loop:           
	movq   mm0,QWORD PTR [eax]                    
	movq   mm2,QWORD PTR [eax+0x1]                
	movq   mm1,mm0                                
	movq   mm3,mm2                                
	punpcklbw mm0,mm7                             
	punpckhbw mm1,mm7                             
	punpcklbw mm2,mm7                             
	punpckhbw mm3,mm7                             
	paddw  mm0,mm2                                
	paddw  mm1,mm3                                
	psllw  mm0,0x2                                
	psllw  mm1,0x2                                
	movq   mm2,QWORD PTR [eax-0x1]                
	movq   mm4,QWORD PTR [eax+0x2]                
	movq   mm3,mm2                                
	movq   mm5,mm4                                
	punpcklbw mm2,mm7                             
	punpckhbw mm3,mm7                             
	punpcklbw mm4,mm7                             
	punpckhbw mm5,mm7                             
	paddw  mm2,mm4                                
	paddw  mm5,mm3                                
	psubw  mm0,mm2                                
	psubw  mm1,mm5                                
	pmullw mm0,mm6                                
	pmullw mm1,mm6                                
	movd   mm2,DWORD PTR [eax-0x2]                
	movd   mm5,DWORD PTR [eax+0x7]                
	punpcklbw mm2,mm7                             
	punpcklbw mm5,mm7                             
	paddw  mm2,mm3                                
	paddw  mm4,mm5                                
	movq   mm5,QWORD PTR [ff_pw_16]
	paddw  mm2,mm5                                
	paddw  mm4,mm5                                
	paddw  mm0,mm2                                
	paddw  mm1,mm4                                
	psraw  mm0,0x5                                
	psraw  mm1,0x5                                
	movq   mm4,QWORD PTR [edx]                    
	packuswb mm0,mm1                              
	pavgb  mm0,mm4                                
	movq   QWORD PTR [ecx],mm0                    
	add    eax,esi                                
	add    ecx,esi                                
	add    edx,edi                                
	dec    ebx                                    
	jg     put_h264_qpel8_h_lowpass_l2_mmx2loop   
	mov    ebx,DWORD PTR [esp]                    
	mov    esi,DWORD PTR [esp+0x4]                
	mov    edi,DWORD PTR [esp+0x8]                
	add    esp,0xc                                
	ret                                           
	}
}
void put_h264_qpel16_h_lowpass_l2_mmx2(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{ 
	put_h264_qpel8_h_lowpass_l2_mmx2(dst , src , src2 , dstStride, src2Stride); 
	put_h264_qpel8_h_lowpass_l2_mmx2(dst+8, src+8, src2+8, dstStride, src2Stride); 
	src += 8*dstStride; 
	dst += 8*dstStride; 
	src2 += 8*src2Stride;
	put_h264_qpel8_h_lowpass_l2_mmx2(dst , src , src2 , dstStride, src2Stride); 
	put_h264_qpel8_h_lowpass_l2_mmx2(dst+8, src+8, src2+8, dstStride, src2Stride);
}
void __declspec(naked) put_h264_qpel8or16_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
	__asm{
	sub    esp,0x10                                                     
	mov    edx,0xfffffffb                                               
	mov    DWORD PTR [esp],ebx                                          
	mov    ebx,DWORD PTR [esp+0x24]                                     
	mov    DWORD PTR [esp+0x4],esi                                      
	mov    esi,DWORD PTR [esp+0x20]                                     
	mov    DWORD PTR [esp+0x8],edi                                      
	mov    edi,DWORD PTR [esp+0x1c]                                     
	mov    DWORD PTR [esp+0xc],ebp                                      
	mov    ecx,DWORD PTR [esp+0x14]                                     
	sub    edx,ebx                                                      
	mov    ebp,ebx                                                      
	lea    eax,[esi+esi*1]                                              
	neg    eax                                                          
	imul   edx,esi                                                      
	add    eax,DWORD PTR [esp+0x18]                                     
	imul   ebp,edi                                                      
	pxor   mm7,mm7                                                      
	movd   mm0,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm1,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm2,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm3,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm4,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	punpcklbw mm0,mm7                                                   
	punpcklbw mm1,mm7                                                   
	punpcklbw mm2,mm7                                                   
	punpcklbw mm3,mm7                                                   
	punpcklbw mm4,mm7                                                   
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm4,mm3                                                      
	paddw  mm6,mm4                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm5,mm4                                                      
	paddw  mm6,mm5                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	cmp    ebx,0x10                                                     
	jne    put_h264_qpel8or16_v_lowpass_mmx2_4695e                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm4,mm3                                                      
	paddw  mm6,mm4                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm5,mm4                                                      
	paddw  mm6,mm5                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
put_h264_qpel8or16_v_lowpass_mmx2_4695e:                             
	sub    ecx,ebp                                                      
	lea    eax,[eax+edx*1+0x4]                                          
	add    ecx,0x4                                                      
	pxor   mm7,mm7                                                      
	movd   mm0,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm1,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm2,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm3,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm4,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	punpcklbw mm0,mm7                                                   
	punpcklbw mm1,mm7                                                   
	punpcklbw mm2,mm7                                                   
	punpcklbw mm3,mm7                                                   
	punpcklbw mm4,mm7                                                   
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm4,mm3                                                      
	paddw  mm6,mm4                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm5,mm4                                                      
	paddw  mm6,mm5                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	cmp    ebx,0x10                                                     
	jne    put_h264_qpel8or16_v_lowpass_mmx2_46d1b                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm4,mm3                                                      
	paddw  mm6,mm4                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm5,mm4                                                      
	paddw  mm6,mm5                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
put_h264_qpel8or16_v_lowpass_mmx2_46d1b:                             
	mov    ebx,DWORD PTR [esp]                                          
	mov    esi,DWORD PTR [esp+0x4]                                      
	mov    edi,DWORD PTR [esp+0x8]                                      
	mov    ebp,DWORD PTR [esp+0xc]                                      
	add    esp,0x10                                                     
	ret
	}
}
void put_h264_qpel8_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	put_h264_qpel8or16_v_lowpass_mmx2(dst , src , dstStride, srcStride, 8);
}
void put_h264_qpel16_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	put_h264_qpel8or16_v_lowpass_mmx2(dst , src , dstStride, srcStride, 16); 
	put_h264_qpel8or16_v_lowpass_mmx2(dst+8, src+8, dstStride, srcStride, 16);
}

void __declspec(naked) put_h264_qpel8or16_hv_lowpass_mmx2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride, int size)
{
	__asm{	
	push   ebp                                                         
	push   edi                                                         
	push   esi                                                         
	push   ebx                                                         
	sub    esp,0x8                                                     
	mov    edi,DWORD PTR [esp+0x34]                                    
	mov    ebp,DWORD PTR [esp+0x20]                                    
	mov    esi,DWORD PTR [esp+0x30]                                    
	lea    ebx,[edi+0x8]                                               
	sar    ebx,0x2                                                     
	test   ebx,ebx                                                     
	je     put_h264_qpel8or16_hv_lowpass_mmx2_49276                    
	mov    eax,DWORD PTR [esp+0x24]                                    
	mov    edx,esi                                                     
	mov    ecx,ebp                                                     
	not    edx                                                         
	mov    DWORD PTR [esp+0x4],ebp                                     
	lea    eax,[eax+edx*2]                                             
	mov    edx,0xfffffffb                                              
	sub    edx,edi                                                     
	imul   edx,esi                                                     
	add    edx,0x4                                                     
	mov    DWORD PTR [esp],edx                                         
	mov    ebp,DWORD PTR [esp]                                         
	xor    edx,edx                                                     
	nop                                                                
put_h264_qpel8or16_hv_lowpass_mmx2_48f08:                           
	pxor   mm7,mm7                                                     
	movd   mm0,DWORD PTR [eax]                                         
	add    eax,esi                                                     
	movd   mm1,DWORD PTR [eax]                                         
	add    eax,esi                                                     
	movd   mm2,DWORD PTR [eax]                                         
	add    eax,esi                                                     
	movd   mm3,DWORD PTR [eax]                                         
	add    eax,esi                                                     
	movd   mm4,DWORD PTR [eax]                                         
	add    eax,esi                                                     
	punpcklbw mm0,mm7                                                  
	punpcklbw mm1,mm7                                                  
	punpcklbw mm2,mm7                                                  
	punpcklbw mm3,mm7                                                  
	punpcklbw mm4,mm7                                                  
	movq   mm6,mm2                                                     
	movd   mm5,DWORD PTR [eax]                                         
	paddw  mm6,mm3                                                     
	psllw  mm6,0x2                                                     
	paddw  mm0,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm1                                                     
	psubw  mm6,mm4                                                     
	punpcklbw mm5,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm0,mm5                                                     
	add    eax,esi                                                     
	paddw  mm6,mm0                                                     
	movq   QWORD PTR [ecx],mm6                                         
	movq   mm6,mm3                                                     
	movd   mm0,DWORD PTR [eax]                                         
	paddw  mm6,mm4                                                     
	psllw  mm6,0x2                                                     
	paddw  mm1,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm2                                                     
	psubw  mm6,mm5                                                     
	punpcklbw mm0,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm1,mm0                                                     
	add    eax,esi                                                     
	paddw  mm6,mm1                                                     
	movq   QWORD PTR [ecx+0x30],mm6                                    
	movq   mm6,mm4                                                     
	movd   mm1,DWORD PTR [eax]                                         
	paddw  mm6,mm5                                                     
	psllw  mm6,0x2                                                     
	paddw  mm2,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm3                                                     
	psubw  mm6,mm0                                                     
	punpcklbw mm1,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm2,mm1                                                     
	add    eax,esi                                                     
	paddw  mm6,mm2                                                     
	movq   QWORD PTR [ecx+0x60],mm6                                    
	movq   mm6,mm5                                                     
	movd   mm2,DWORD PTR [eax]                                         
	paddw  mm6,mm0                                                     
	psllw  mm6,0x2                                                     
	paddw  mm3,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm4                                                     
	psubw  mm6,mm1                                                     
	punpcklbw mm2,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm3,mm2                                                     
	add    eax,esi                                                     
	paddw  mm6,mm3                                                     
	movq   QWORD PTR [ecx+0x90],mm6                                    
	movq   mm6,mm0                                                     
	movd   mm3,DWORD PTR [eax]                                         
	paddw  mm6,mm1                                                     
	psllw  mm6,0x2                                                     
	paddw  mm4,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm5                                                     
	psubw  mm6,mm2                                                     
	punpcklbw mm3,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm4,mm3                                                     
	add    eax,esi                                                     
	paddw  mm6,mm4                                                     
	movq   QWORD PTR [ecx+0xc0],mm6                                    
	movq   mm6,mm1                                                     
	movd   mm4,DWORD PTR [eax]                                         
	paddw  mm6,mm2                                                     
	psllw  mm6,0x2                                                     
	paddw  mm5,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm0                                                     
	psubw  mm6,mm3                                                     
	punpcklbw mm4,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm5,mm4                                                     
	add    eax,esi                                                     
	paddw  mm6,mm5                                                     
	movq   QWORD PTR [ecx+0xf0],mm6                                    
	movq   mm6,mm2                                                     
	movd   mm5,DWORD PTR [eax]                                         
	paddw  mm6,mm3                                                     
	psllw  mm6,0x2                                                     
	paddw  mm0,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm1                                                     
	psubw  mm6,mm4                                                     
	punpcklbw mm5,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm0,mm5                                                     
	add    eax,esi                                                     
	paddw  mm6,mm0                                                     
	movq   QWORD PTR [ecx+0x120],mm6                                   
	movq   mm6,mm3                                                     
	movd   mm0,DWORD PTR [eax]                                         
	paddw  mm6,mm4                                                     
	psllw  mm6,0x2                                                     
	paddw  mm1,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm2                                                     
	psubw  mm6,mm5                                                     
	punpcklbw mm0,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm1,mm0                                                     
	add    eax,esi                                                     
	paddw  mm6,mm1                                                     
	movq   QWORD PTR [ecx+0x150],mm6                                   
	cmp    edi,0x10                                                    
	jne    put_h264_qpel8or16_hv_lowpass_mmx2_49262                    
	movq   mm6,mm4                                                     
	movd   mm1,DWORD PTR [eax]                                         
	paddw  mm6,mm5                                                     
	psllw  mm6,0x2                                                     
	paddw  mm2,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm3                                                     
	psubw  mm6,mm0                                                     
	punpcklbw mm1,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm2,mm1                                                     
	add    eax,esi                                                     
	paddw  mm6,mm2                                                     
	movq   QWORD PTR [ecx+0x180],mm6                                   
	movq   mm6,mm5                                                     
	movd   mm2,DWORD PTR [eax]                                         
	paddw  mm6,mm0                                                     
	psllw  mm6,0x2                                                     
	paddw  mm3,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm4                                                     
	psubw  mm6,mm1                                                     
	punpcklbw mm2,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm3,mm2                                                     
	add    eax,esi                                                     
	paddw  mm6,mm3                                                     
	movq   QWORD PTR [ecx+0x1b0],mm6                                   
	movq   mm6,mm0                                                     
	movd   mm3,DWORD PTR [eax]                                         
	paddw  mm6,mm1                                                     
	psllw  mm6,0x2                                                     
	paddw  mm4,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm5                                                     
	psubw  mm6,mm2                                                     
	punpcklbw mm3,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm4,mm3                                                     
	add    eax,esi                                                     
	paddw  mm6,mm4                                                     
	movq   QWORD PTR [ecx+0x1e0],mm6                                   
	movq   mm6,mm1                                                     
	movd   mm4,DWORD PTR [eax]                                         
	paddw  mm6,mm2                                                     
	psllw  mm6,0x2                                                     
	paddw  mm5,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm0                                                     
	psubw  mm6,mm3                                                     
	punpcklbw mm4,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm5,mm4                                                     
	add    eax,esi                                                     
	paddw  mm6,mm5                                                     
	movq   QWORD PTR [ecx+0x210],mm6                                   
	movq   mm6,mm2                                                     
	movd   mm5,DWORD PTR [eax]                                         
	paddw  mm6,mm3                                                     
	psllw  mm6,0x2                                                     
	paddw  mm0,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm1                                                     
	psubw  mm6,mm4                                                     
	punpcklbw mm5,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm0,mm5                                                     
	add    eax,esi                                                     
	paddw  mm6,mm0                                                     
	movq   QWORD PTR [ecx+0x240],mm6                                   
	movq   mm6,mm3                                                     
	movd   mm0,DWORD PTR [eax]                                         
	paddw  mm6,mm4                                                     
	psllw  mm6,0x2                                                     
	paddw  mm1,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm2                                                     
	psubw  mm6,mm5                                                     
	punpcklbw mm0,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm1,mm0                                                     
	add    eax,esi                                                     
	paddw  mm6,mm1                                                     
	movq   QWORD PTR [ecx+0x270],mm6                                   
	movq   mm6,mm4                                                     
	movd   mm1,DWORD PTR [eax]                                         
	paddw  mm6,mm5                                                     
	psllw  mm6,0x2                                                     
	paddw  mm2,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm3                                                     
	psubw  mm6,mm0                                                     
	punpcklbw mm1,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm2,mm1                                                     
	add    eax,esi                                                     
	paddw  mm6,mm2                                                     
	movq   QWORD PTR [ecx+0x2a0],mm6                                   
	movq   mm6,mm5                                                     
	movd   mm2,DWORD PTR [eax]                                         
	paddw  mm6,mm0                                                     
	psllw  mm6,0x2                                                     
	paddw  mm3,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm4                                                     
	psubw  mm6,mm1                                                     
	punpcklbw mm2,mm7                                                  
	pmullw mm6,QWORD PTR [ff_pw_5]                                        
	paddw  mm3,mm2                                                     
	add    eax,esi                                                     
	paddw  mm6,mm3                                                     
	movq   QWORD PTR [ecx+0x2d0],mm6                                   
put_h264_qpel8or16_hv_lowpass_mmx2_49262:                           
	add    edx,0x1                                                     
	add    ecx,0x8                                                     
	add    eax,ebp                                                     
	cmp    edx,ebx                                                     
	jne    put_h264_qpel8or16_hv_lowpass_mmx2_48f08                    
	mov    ebp,DWORD PTR [esp+0x4]                                     
put_h264_qpel8or16_hv_lowpass_mmx2_49276:                           
	lea    eax,[edi+edi*2]                                             
	mov    ecx,DWORD PTR [esp+0x1c]                                    
	mov    edx,0x8                                                     
	neg    eax                                                         
	mov    esi,DWORD PTR [esp+0x28]                                    
	mov    ebx,edi                                                     
	add    eax,0x1                                                     
	shl    eax,0x4                                                     
	mov    DWORD PTR [esp],eax                                         
	mov    eax,DWORD PTR [esp+0x28]                                    
	sar    ebx,0x4                                                     
	imul   eax,edi                                                     
	sub    edx,eax                                                     
	mov    eax,ebp                                                     
	mov    ebp,edx                                                     
	nop                                                                
	lea    esi,[esi+0x0]                                         
put_h264_qpel8or16_hv_lowpass_mmx2_492a8:                           
	mov    edx,edi                                                     
put_h264_qpel8or16_hv_lowpass_mmx2_492aa:                           
	movq   mm0,QWORD PTR [eax]                                         
	movq   mm3,QWORD PTR [eax+0x8]                                     
	movq   mm1,QWORD PTR [eax+0x2]                                     
	movq   mm4,QWORD PTR [eax+0xa]                                     
	paddw  mm0,mm4                                                     
	paddw  mm1,mm3                                                     
	paddw  mm3,QWORD PTR [eax+0x12]                                    
	paddw  mm4,QWORD PTR [eax+0x10]                                    
	movq   mm2,QWORD PTR [eax+0x4]                                     
	movq   mm5,QWORD PTR [eax+0xc]                                     
	paddw  mm2,QWORD PTR [eax+0x6]                                     
	paddw  mm5,QWORD PTR [eax+0xe]                                     
	psubw  mm0,mm1                                                     
	psubw  mm3,mm4                                                     
	psraw  mm0,0x2                                                     
	psraw  mm3,0x2                                                     
	psubw  mm0,mm1                                                     
	psubw  mm3,mm4                                                     
	paddsw mm0,mm2                                                     
	paddsw mm3,mm5                                                     
	psraw  mm0,0x2                                                     
	psraw  mm3,0x2                                                     
	paddw  mm0,mm2                                                     
	paddw  mm3,mm5                                                     
	psraw  mm0,0x6                                                     
	psraw  mm3,0x6                                                     
	packuswb mm0,mm3                                                   
	movq   QWORD PTR [ecx],mm0                                         
	add    eax,0x30                                                    
	add    ecx,esi                                                     
	dec    edx                                                         
	jne    put_h264_qpel8or16_hv_lowpass_mmx2_492aa                    
	sub    ebx,0x1                                                     
	add    ecx,ebp                                                     
	add    eax,DWORD PTR [esp]                                         
	cmp    ebx,0xffffffff                                              
	jne    put_h264_qpel8or16_hv_lowpass_mmx2_492a8                    
	add    esp,0x8                                                     
	pop    ebx                                                         
	pop    esi                                                         
	pop    edi                                                         
	pop    ebp                                                         
	ret                                                    
	}
}

void put_h264_qpel8_hv_lowpass_mmx2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	put_h264_qpel8or16_hv_lowpass_mmx2(dst , tmp , src , dstStride, tmpStride, srcStride, 8);
}
void put_h264_qpel16_hv_lowpass_mmx2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	put_h264_qpel8or16_hv_lowpass_mmx2(dst , tmp , src , dstStride, tmpStride, srcStride, 16);
}
void __declspec(naked) put_pixels4_l2_shift5_mmx2(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
	__asm{
 	sub    esp,0x8                   
 	mov    DWORD PTR [esp],esi       
 	mov    edx,DWORD PTR [esp+0xc]   
 	mov    DWORD PTR [esp+0x4],edi   
 	mov    ecx,DWORD PTR [esp+0x10]  
 	mov    eax,DWORD PTR [esp+0x14]  
 	mov    esi,DWORD PTR [esp+0x1c]  
 	mov    edi,DWORD PTR [esp+0x18]  
 	movq   mm0,QWORD PTR [ecx]       
 	movq   mm1,QWORD PTR [ecx+0x18]  
 	psraw  mm0,0x5                   
 	psraw  mm1,0x5                   
 	packuswb mm0,mm0                 
 	packuswb mm1,mm1                 
 	pavgb  mm0,QWORD PTR [eax]       
 	pavgb  mm1,QWORD PTR [eax+esi*1] 
 	movd   DWORD PTR [edx],mm0       
 	movd   DWORD PTR [edx+edi*1],mm1 
 	lea    eax,[eax+esi*2]           
 	lea    edx,[edx+edi*2]           
 	movq   mm0,QWORD PTR [ecx+0x30]  
 	movq   mm1,QWORD PTR [ecx+0x48]  
 	psraw  mm0,0x5                   
 	psraw  mm1,0x5                   
 	packuswb mm0,mm0                 
 	packuswb mm1,mm1                 
 	pavgb  mm0,QWORD PTR [eax]       
 	pavgb  mm1,QWORD PTR [eax+esi*1] 
 	movd   DWORD PTR [edx],mm0       
 	movd   DWORD PTR [edx+edi*1],mm1 
 	mov    esi,DWORD PTR [esp]       
 	mov    edi,DWORD PTR [esp+0x4]   
 	add    esp,0x8                   
 	ret                              
	}
}
void __declspec(naked) put_pixels8_l2_shift5_mmx2(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
	__asm{	
	sub    esp,0x14                       
	mov    DWORD PTR [esp+0xc],edi        
	mov    edi,DWORD PTR [esp+0x24]       
	mov    DWORD PTR [esp+0x8],esi        
	mov    esi,DWORD PTR [esp+0x28]       
	mov    DWORD PTR [esp+0x4],ebx        
	mov    edx,DWORD PTR [esp+0x18]       
	mov    ecx,DWORD PTR [esp+0x1c]       
	lea    eax,[edi+edi*1]                
	mov    ebx,DWORD PTR [esp+0x2c]       
	mov    DWORD PTR [esp],eax            
	mov    eax,DWORD PTR [esp+0x20]       
	mov    DWORD PTR [esp+0x10],ebp       
	lea    ebp,[esi+esi*1]                
	lea    esi,[esi+0x0]            
put_pixels8_l2_shift5_mmx2flag:        
	movq   mm0,QWORD PTR [ecx]            
	movq   mm1,QWORD PTR [ecx+0x8]        
	movq   mm2,QWORD PTR [ecx+0x30]       
	movq   mm3,QWORD PTR [ecx+0x38]       
	psraw  mm0,0x5                        
	psraw  mm1,0x5                        
	psraw  mm2,0x5                        
	psraw  mm3,0x5                        
	packuswb mm0,mm1                      
	packuswb mm2,mm3                      
	pavgb  mm0,QWORD PTR [eax]            
	pavgb  mm2,QWORD PTR [eax+esi*1]      
	movq   QWORD PTR [edx],mm0            
	movq   QWORD PTR [edx+edi*1],mm2      
	add    eax,ebp                        
	add    ecx,0x60                       
	add    edx,DWORD PTR [esp]            
	sub    ebx,0x2                        
	jne    put_pixels8_l2_shift5_mmx2flag 
	mov    ebx,DWORD PTR [esp+0x4]        
	mov    esi,DWORD PTR [esp+0x8]        
	mov    edi,DWORD PTR [esp+0xc]        
	mov    ebp,DWORD PTR [esp+0x10]       
	add    esp,0x14                       
	ret                                   
	}
}
void __declspec(naked) put_h264_qpel8or16_v_lowpass_sse2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
	__asm{
	sub    esp,0x8                                  
	mov    DWORD PTR [esp],esi                      
	mov    esi,DWORD PTR [esp+0x18]                 
	mov    DWORD PTR [esp+0x4],edi                  
	mov    ecx,DWORD PTR [esp+0xc]                  
	mov    edi,DWORD PTR [esp+0x14]                 
	lea    eax,[esi+esi*1]                          
	neg    eax                                      
	add    eax,DWORD PTR [esp+0x10]                 
	pxor   xmm7,xmm7                                
	movq   xmm0,QWORD PTR [eax]                     
	add    eax,esi                                  
	movq   xmm1,QWORD PTR [eax]                     
	add    eax,esi                                  
	movq   xmm2,QWORD PTR [eax]                     
	add    eax,esi                                  
	movq   xmm3,QWORD PTR [eax]                     
	add    eax,esi                                  
	movq   xmm4,QWORD PTR [eax]                     
	add    eax,esi                                  
	punpcklbw xmm0,xmm7                             
	punpcklbw xmm1,xmm7                             
	punpcklbw xmm2,xmm7                             
	punpcklbw xmm3,xmm7                             
	punpcklbw xmm4,xmm7                             
	movdqa xmm6,xmm2                                
	movq   xmm5,QWORD PTR [eax]                     
	paddw  xmm6,xmm3                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm1                                
	psubw  xmm6,xmm4                                
	punpcklbw xmm5,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm0,xmm5                                
	paddw  xmm6,xmm0                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm3                                
	movq   xmm0,QWORD PTR [eax]                     
	paddw  xmm6,xmm4                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm2                                
	psubw  xmm6,xmm5                                
	punpcklbw xmm0,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm1,xmm0                                
	paddw  xmm6,xmm1                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm4                                
	movq   xmm1,QWORD PTR [eax]                     
	paddw  xmm6,xmm5                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm3                                
	psubw  xmm6,xmm0                                
	punpcklbw xmm1,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm2,xmm1                                
	paddw  xmm6,xmm2                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm5                                
	movq   xmm2,QWORD PTR [eax]                     
	paddw  xmm6,xmm0                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm4                                
	psubw  xmm6,xmm1                                
	punpcklbw xmm2,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm3,xmm2                                
	paddw  xmm6,xmm3                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm0                                
	movq   xmm3,QWORD PTR [eax]                     
	paddw  xmm6,xmm1                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm5                                
	psubw  xmm6,xmm2                                
	punpcklbw xmm3,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm4,xmm3                                
	paddw  xmm6,xmm4                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm1                                
	movq   xmm4,QWORD PTR [eax]                     
	paddw  xmm6,xmm2                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm0                                
	psubw  xmm6,xmm3                                
	punpcklbw xmm4,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm5,xmm4                                
	paddw  xmm6,xmm5                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm2                                
	movq   xmm5,QWORD PTR [eax]                     
	paddw  xmm6,xmm3                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm1                                
	psubw  xmm6,xmm4                                
	punpcklbw xmm5,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm0,xmm5                                
	paddw  xmm6,xmm0                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm3                                
	movq   xmm0,QWORD PTR [eax]                     
	paddw  xmm6,xmm4                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm2                                
	psubw  xmm6,xmm5                                
	punpcklbw xmm0,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm1,xmm0                                
	paddw  xmm6,xmm1                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	cmp    DWORD PTR [esp+0x1c],0x10                
	jne    put_h264_qpel8or16_v_lowpass_sse2End     
	movdqa xmm6,xmm4                                
	movq   xmm1,QWORD PTR [eax]                     
	paddw  xmm6,xmm5                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm3                                
	psubw  xmm6,xmm0                                
	punpcklbw xmm1,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm2,xmm1                                
	paddw  xmm6,xmm2                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm5                                
	movq   xmm2,QWORD PTR [eax]                     
	paddw  xmm6,xmm0                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm4                                
	psubw  xmm6,xmm1                                
	punpcklbw xmm2,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm3,xmm2                                
	paddw  xmm6,xmm3                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm0                                
	movq   xmm3,QWORD PTR [eax]                     
	paddw  xmm6,xmm1                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm5                                
	psubw  xmm6,xmm2                                
	punpcklbw xmm3,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm4,xmm3                                
	paddw  xmm6,xmm4                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm1                                
	movq   xmm4,QWORD PTR [eax]                     
	paddw  xmm6,xmm2                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm0                                
	psubw  xmm6,xmm3                                
	punpcklbw xmm4,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm5,xmm4                                
	paddw  xmm6,xmm5                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm2                                
	movq   xmm5,QWORD PTR [eax]                     
	paddw  xmm6,xmm3                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm1                                
	psubw  xmm6,xmm4                                
	punpcklbw xmm5,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm0,xmm5                                
	paddw  xmm6,xmm0                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm3                                
	movq   xmm0,QWORD PTR [eax]                     
	paddw  xmm6,xmm4                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm2                                
	psubw  xmm6,xmm5                                
	punpcklbw xmm0,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm1,xmm0                                
	paddw  xmm6,xmm1                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm4                                
	movq   xmm1,QWORD PTR [eax]                     
	paddw  xmm6,xmm5                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm3                                
	psubw  xmm6,xmm0                                
	punpcklbw xmm1,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm2,xmm1                                
	paddw  xmm6,xmm2                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
	movdqa xmm6,xmm5                                
	movq   xmm2,QWORD PTR [eax]                     
	paddw  xmm6,xmm0                                
	psllw  xmm6,0x2                                 
	psubw  xmm6,xmm4                                
	psubw  xmm6,xmm1                                
	punpcklbw xmm2,xmm7                             
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                  
                                                 
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                  
                                                 
	add    eax,esi                                  
	paddw  xmm3,xmm2                                
	paddw  xmm6,xmm3                                
	psraw  xmm6,0x5                                 
	packuswb xmm6,xmm6                              
	movq   QWORD PTR [ecx],xmm6                     
	add    ecx,edi                                  
put_h264_qpel8or16_v_lowpass_sse2End:            
	mov    esi,DWORD PTR [esp]                      
	mov    edi,DWORD PTR [esp+0x4]                  
	add    esp,0x8                                  
	ret
	}
}
void put_h264_qpel8_v_lowpass_sse2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	put_h264_qpel8or16_v_lowpass_sse2(dst , src , dstStride, srcStride, 8);
}
void put_h264_qpel16_v_lowpass_sse2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	put_h264_qpel8or16_v_lowpass_sse2(dst , src , dstStride, srcStride, 16); 
	put_h264_qpel8or16_v_lowpass_sse2(dst+8, src+8, dstStride, srcStride, 16);
}
void __declspec(naked) put_h264_qpel8or16_hv_lowpass_sse2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride, int size)
{
	__asm{
	push   ebp                                                     
	push   edi                                                     
	push   esi                                                     
	push   ebx                                                     
	sub    esp,0x8                                                 
	mov    edi,DWORD PTR [esp+0x34]                                
	mov    ebp,DWORD PTR [esp+0x20]                                
	mov    esi,DWORD PTR [esp+0x30]                                
	lea    ebx,[edi+0x8]                                           
	sar    ebx,0x3                                                 
	test   ebx,ebx                                                 
	je     put_h264_qpel8or16_hv_lowpass_sse2_4fdc1                
	mov    eax,DWORD PTR [esp+0x24]                                
	mov    edx,esi                                                 
	mov    ecx,ebp                                                 
	not    edx                                                     
	mov    DWORD PTR [esp+0x4],ebp                                 
	lea    eax,[eax+edx*2]                                         
	mov    edx,0xfffffffb                                          
	sub    edx,edi                                                 
	imul   edx,esi                                                 
	add    edx,0x8                                                 
	mov    DWORD PTR [esp],edx                                     
	mov    ebp,DWORD PTR [esp]                                     
	xor    edx,edx                                                 
	nop                                                            
put_h264_qpel8or16_hv_lowpass_sse2_4f988:                       
	pxor   xmm7,xmm7                                               
	movq   xmm0,QWORD PTR [eax]                                    
	add    eax,esi                                                 
	movq   xmm1,QWORD PTR [eax]                                    
	add    eax,esi                                                 
	movq   xmm2,QWORD PTR [eax]                                    
	add    eax,esi                                                 
	movq   xmm3,QWORD PTR [eax]                                    
	add    eax,esi                                                 
	movq   xmm4,QWORD PTR [eax]                                    
	add    eax,esi                                                 
	punpcklbw xmm0,xmm7                                            
	punpcklbw xmm1,xmm7                                            
	punpcklbw xmm2,xmm7                                            
	punpcklbw xmm3,xmm7                                            
	punpcklbw xmm4,xmm7                                            
	movdqa xmm6,xmm2                                               
	movq   xmm5,QWORD PTR [eax]                                    
	paddw  xmm6,xmm3                                               
	psllw  xmm6,0x2                                                
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm1                                               
	psubw  xmm6,xmm4                                               
	punpcklbw xmm5,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm0,xmm5                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm0                                               
	movdqa XMMWORD PTR [ecx],xmm6                                  
	movdqa xmm6,xmm3                                               
	movq   xmm0,QWORD PTR [eax]                                    
	paddw  xmm6,xmm4                                               
	psllw  xmm6,0x2                                                
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm2                                               
	psubw  xmm6,xmm5                                               
	punpcklbw xmm0,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm1,xmm0                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm1                                               
	movdqa XMMWORD PTR [ecx+0x30],xmm6                             
	movdqa xmm6,xmm4                                               
	movq   xmm1,QWORD PTR [eax]                                    
	paddw  xmm6,xmm5                                               
	psllw  xmm6,0x2                                                
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm3                                               
	psubw  xmm6,xmm0                                               
	punpcklbw xmm1,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm2,xmm1                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm2                                               
	movdqa XMMWORD PTR [ecx+0x60],xmm6                             
	movdqa xmm6,xmm5                                               
	movq   xmm2,QWORD PTR [eax]                                    
	paddw  xmm6,xmm0                                               
	psllw  xmm6,0x2                                                
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm4                                               
	psubw  xmm6,xmm1                                               
	punpcklbw xmm2,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm3,xmm2                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm3                                               
	movdqa XMMWORD PTR [ecx+0x90],xmm6                             
                                                                
	movdqa xmm6,xmm0                                               
	movq   xmm3,QWORD PTR [eax]                                    
	paddw  xmm6,xmm1                                               
	psllw  xmm6,0x2                                                
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm5                                               
	psubw  xmm6,xmm2                                               
	punpcklbw xmm3,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm4,xmm3                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm4                                               
	movdqa XMMWORD PTR [ecx+0xc0],xmm6                             
                                                                
	movdqa xmm6,xmm1                                               
	movq   xmm4,QWORD PTR [eax]                                    
	paddw  xmm6,xmm2                                               
	psllw  xmm6,0x2                                                
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm0                                               
	psubw  xmm6,xmm3                                               
	punpcklbw xmm4,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm5,xmm4                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm5                                               
	movdqa XMMWORD PTR [ecx+0xf0],xmm6                             
                                                                
	movdqa xmm6,xmm2                                               
	movq   xmm5,QWORD PTR [eax]                                    
	paddw  xmm6,xmm3                                               
	psllw  xmm6,0x2                                                
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm1                                               
	psubw  xmm6,xmm4                                               
	punpcklbw xmm5,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm0,xmm5                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm0                                               
	movdqa XMMWORD PTR [ecx+0x120],xmm6                            
                                                                
	movdqa xmm6,xmm3                                               
	movq   xmm0,QWORD PTR [eax]                                    
	paddw  xmm6,xmm4                                               
	psllw  xmm6,0x2                                                
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm2                                               
	psubw  xmm6,xmm5                                               
	punpcklbw xmm0,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm1,xmm0                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm1                                               
	movdqa XMMWORD PTR [ecx+0x150],xmm6                            
                                                                
	cmp    edi,0x10                                                
	jne    put_h264_qpel8or16_hv_lowpass_sse2_4fdad                
	movdqa xmm6,xmm4                                               
	movq   xmm1,QWORD PTR [eax]                                    
	paddw  xmm6,xmm5                                               
	psllw  xmm6,0x2                                                
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm3                                               
	psubw  xmm6,xmm0                                               
	punpcklbw xmm1,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm2,xmm1                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm2                                               
	movdqa XMMWORD PTR [ecx+0x180],xmm6                            
                                                                
	movdqa xmm6,xmm5                                               
	movq   xmm2,QWORD PTR [eax]                                    
	paddw  xmm6,xmm0                                               
	psllw  xmm6,0x2                                                
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm4                                               
	psubw  xmm6,xmm1                                               
	punpcklbw xmm2,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm3,xmm2                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm3                                               
	movdqa XMMWORD PTR [ecx+0x1b0],xmm6                            
                                                                
	movdqa xmm6,xmm0                                               
	movq   xmm3,QWORD PTR [eax]                                    
	paddw  xmm6,xmm1                                               
	psllw  xmm6,0x2                                                
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm5                                               
	psubw  xmm6,xmm2                                               
	punpcklbw xmm3,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm4,xmm3                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm4                                               
	movdqa XMMWORD PTR [ecx+0x1e0],xmm6                            
                                                                
	movdqa xmm6,xmm1                                               
	movq   xmm4,QWORD PTR [eax]                                    
	paddw  xmm6,xmm2                                               
	psllw  xmm6,0x2                                                
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm0                                               
	psubw  xmm6,xmm3                                               
	punpcklbw xmm4,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm5,xmm4                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm5                                               
	movdqa XMMWORD PTR [ecx+0x210],xmm6                            
                                                                
	movdqa xmm6,xmm2                                               
	movq   xmm5,QWORD PTR [eax]                                    
	paddw  xmm6,xmm3                                               
	psllw  xmm6,0x2                                                
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm1                                               
	psubw  xmm6,xmm4                                               
	punpcklbw xmm5,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm0,xmm5                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm0                                               
	movdqa XMMWORD PTR [ecx+0x240],xmm6                            
                                                                
	movdqa xmm6,xmm3                                               
	movq   xmm0,QWORD PTR [eax]                                    
	paddw  xmm6,xmm4                                               
	psllw  xmm6,0x2                                                
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm2                                               
	psubw  xmm6,xmm5                                               
	punpcklbw xmm0,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm1,xmm0                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm1                                               
	movdqa XMMWORD PTR [ecx+0x270],xmm6                            
                                                                
	movdqa xmm6,xmm4                                               
	movq   xmm1,QWORD PTR [eax]                                    
	paddw  xmm6,xmm5                                               
	psllw  xmm6,0x2                                                
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm3                                               
	psubw  xmm6,xmm0                                               
	punpcklbw xmm1,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm2,xmm1                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm2                                               
	movdqa XMMWORD PTR [ecx+0x2a0],xmm6                            
                                                                
	movdqa xmm6,xmm5                                               
	movq   xmm2,QWORD PTR [eax]                                    
	paddw  xmm6,xmm0                                               
	psllw  xmm6,0x2                                                
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                 
                                                                
	psubw  xmm6,xmm4                                               
	psubw  xmm6,xmm1                                               
	punpcklbw xmm2,xmm7                                            
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                 
                                                                
	paddw  xmm3,xmm2                                               
	add    eax,esi                                                 
	paddw  xmm6,xmm3                                               
	movdqa XMMWORD PTR [ecx+0x2d0],xmm6                            
                                                                
put_h264_qpel8or16_hv_lowpass_sse2_4fdad:                       
	add    edx,0x1                                                 
	add    ecx,0x10                                                
	add    eax,ebp                                                 
	cmp    edx,ebx                                                 
	jne    put_h264_qpel8or16_hv_lowpass_sse2_4f988                
	mov    ebp,DWORD PTR [esp+0x4]                                 
put_h264_qpel8or16_hv_lowpass_sse2_4fdc1:                       
	lea    eax,[edi+edi*2]                                         
	mov    ecx,DWORD PTR [esp+0x1c]                                
	mov    edx,0x8                                                 
	neg    eax                                                     
	mov    esi,DWORD PTR [esp+0x28]                                
	mov    ebx,edi                                                 
	add    eax,0x1                                                 
	shl    eax,0x4                                                 
	mov    DWORD PTR [esp],eax                                     
	mov    eax,DWORD PTR [esp+0x28]                                
	sar    ebx,0x4                                                 
	imul   eax,edi                                                 
	sub    edx,eax                                                 
	mov    eax,ebp                                                 
	mov    ebp,edx                                                 
	xchg   ax,ax                                                   
put_h264_qpel8or16_hv_lowpass_sse2_4fdf0:                       
	mov    edx,edi                                                 
put_h264_qpel8or16_hv_lowpass_sse2_4fdf2:                       
	movq   mm0,QWORD PTR [eax]                                     
	movq   mm3,QWORD PTR [eax+0x8]                                 
	movq   mm1,QWORD PTR [eax+0x2]                                 
	movq   mm4,QWORD PTR [eax+0xa]                                 
	paddw  mm0,mm4                                                 
	paddw  mm1,mm3                                                 
	paddw  mm3,QWORD PTR [eax+0x12]                                
	paddw  mm4,QWORD PTR [eax+0x10]                                
	movq   mm2,QWORD PTR [eax+0x4]                                 
	movq   mm5,QWORD PTR [eax+0xc]                                 
	paddw  mm2,QWORD PTR [eax+0x6]                                 
	paddw  mm5,QWORD PTR [eax+0xe]                                 
	psubw  mm0,mm1                                                 
	psubw  mm3,mm4                                                 
	psraw  mm0,0x2                                                 
	psraw  mm3,0x2                                                 
	psubw  mm0,mm1                                                 
	psubw  mm3,mm4                                                 
	paddsw mm0,mm2                                                 
	paddsw mm3,mm5                                                 
	psraw  mm0,0x2                                                 
	psraw  mm3,0x2                                                 
	paddw  mm0,mm2                                                 
	paddw  mm3,mm5                                                 
	psraw  mm0,0x6                                                 
	psraw  mm3,0x6                                                 
	packuswb mm0,mm3                                               
	movq   QWORD PTR [ecx],mm0                                     
	add    eax,0x30                                                
	add    ecx,esi                                                 
	dec    edx                                                     
	jne    put_h264_qpel8or16_hv_lowpass_sse2_4fdf2                
	sub    ebx,0x1                                                 
	add    ecx,ebp                                                 
	add    eax,DWORD PTR [esp]                                     
	cmp    ebx,0xffffffff                                          
	jne    put_h264_qpel8or16_hv_lowpass_sse2_4fdf0                
	add    esp,0x8                                                 
	pop    ebx                                                     
	pop    esi                                                     
	pop    edi                                                     
	pop    ebp                                                     
	ret
	}
}
void put_h264_qpel8_hv_lowpass_sse2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	put_h264_qpel8or16_hv_lowpass_sse2(dst, tmp, src, dstStride, tmpStride, srcStride, 8);
}
void put_h264_qpel16_hv_lowpass_sse2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	put_h264_qpel8or16_hv_lowpass_sse2(dst, tmp, src, dstStride, tmpStride, srcStride, 16);
}
void __declspec(naked) put_h264_qpel8_h_lowpass_l2_ssse3(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0xc                                            
	mov    DWORD PTR [esp],ebx                                
	mov    ecx,DWORD PTR [esp+0x10]                           
	mov    ebx,0x8                                            
	mov    DWORD PTR [esp+0x4],esi                            
	mov    eax,DWORD PTR [esp+0x14]                           
	mov    DWORD PTR [esp+0x8],edi                            
	mov    edx,DWORD PTR [esp+0x18]                           
	mov    edi,DWORD PTR [esp+0x20]                           
	mov    esi,DWORD PTR [esp+0x1c]                           
	pxor   xmm7,xmm7                                          
	movdqa xmm6,XMMWORD PTR [ff_pw_5]                           
                                                           
put_h264_qpel8_h_lowpass_l2_ssse3flag:										
	lddqu  xmm1,[eax-0x2]                                     
	movdqa xmm0,xmm1                                          
	punpckhbw xmm1,xmm7                                       
	punpcklbw xmm0,xmm7                                       
	movdqa xmm2,xmm1                                          
	movdqa xmm3,xmm1                                          
	movdqa xmm4,xmm1                                          
	movdqa xmm5,xmm1                                          
	palignr xmm4,xmm0,0x2                                     
	palignr xmm3,xmm0,0x4                                     
	palignr xmm2,xmm0,0x6                                     
	palignr xmm1,xmm0,0x8                                     
	palignr xmm5,xmm0,0xa                                     
	paddw  xmm0,xmm5                                          
	paddw  xmm2,xmm3                                          
	paddw  xmm1,xmm4                                          
	psllw  xmm2,0x2                                           
	movq   xmm3,QWORD PTR [edx]                               
	psubw  xmm2,xmm1                                          
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                            
                                                           
	pmullw xmm2,xmm6                                          
	paddw  xmm2,xmm0                                          
	psraw  xmm2,0x5                                           
	packuswb xmm2,xmm2                                        
	pavgb  xmm2,xmm3                                          
	movq   QWORD PTR [ecx],xmm2                               
	add    eax,esi                                            
	add    ecx,esi                                            
	add    edx,edi                                            
	dec    ebx                                                
	jg     put_h264_qpel8_h_lowpass_l2_ssse3flag            
	mov    ebx,DWORD PTR [esp]                                
	mov    esi,DWORD PTR [esp+0x4]                            
	mov    edi,DWORD PTR [esp+0x8]                            
	add    esp,0xc                                            
	ret                                                     
	}
}
void put_h264_qpel16_h_lowpass_l2_ssse3(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{ 
	put_h264_qpel8_h_lowpass_l2_ssse3(dst , src , src2 , dstStride, src2Stride); 
	put_h264_qpel8_h_lowpass_l2_ssse3(dst+8, src+8, src2+8, dstStride, src2Stride);
	src += 8*dstStride;
	dst += 8*dstStride; 
	src2 += 8*src2Stride; 
	put_h264_qpel8_h_lowpass_l2_ssse3(dst , src , src2 , dstStride, src2Stride); 
	put_h264_qpel8_h_lowpass_l2_ssse3(dst+8, src+8, src2+8, dstStride, src2Stride);
}
void __declspec(naked) put_h264_qpel8_h_lowpass_ssse3(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                              
	mov    edx,0x8                              
	mov    DWORD PTR [esp],esi                  
	mov    ecx,DWORD PTR [esp+0xc]              
	mov    DWORD PTR [esp+0x4],edi              
	mov    eax,DWORD PTR [esp+0x10]             
	mov    edi,DWORD PTR [esp+0x18]             
	mov    esi,DWORD PTR [esp+0x14]             
	pxor   xmm7,xmm7                            
	movdqa xmm6,XMMWORD PTR [ff_pw_5]           
                                             
put_h264_qpel8_h_lowpass_ssse3flag:        
	lddqu  xmm1,[eax-0x2]                       
	movdqa xmm0,xmm1                            
	punpckhbw xmm1,xmm7                         
	punpcklbw xmm0,xmm7                         
	movdqa xmm2,xmm1                            
	movdqa xmm3,xmm1                            
	movdqa xmm4,xmm1                            
	movdqa xmm5,xmm1                            
	palignr xmm4,xmm0,0x2                       
	palignr xmm3,xmm0,0x4                       
	palignr xmm2,xmm0,0x6                       
	palignr xmm1,xmm0,0x8                       
	palignr xmm5,xmm0,0xa                       
	paddw  xmm0,xmm5                            
	paddw  xmm2,xmm3                            
	paddw  xmm1,xmm4                            
	psllw  xmm2,0x2                             
	psubw  xmm2,xmm1                            
	paddw  xmm0,XMMWORD PTR [ff_pw_16]       
                                             
	pmullw xmm2,xmm6                            
	paddw  xmm2,xmm0                            
	psraw  xmm2,0x5                             
	packuswb xmm2,xmm2                          
	movq   QWORD PTR [ecx],xmm2                 
	add    eax,edi                              
	add    ecx,esi                              
	dec    edx                                  
	jne    put_h264_qpel8_h_lowpass_ssse3flag
	mov    esi,DWORD PTR [esp]                  
	mov    edi,DWORD PTR [esp+0x4]              
	add    esp,0x8                              
	ret
	}
}
void __declspec(naked) put_h264_qpel8or16_hv_lowpass_ssse3(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride, int size)
{
	__asm{
	push   ebp                                                          
	push   edi                                                          
	push   esi                                                          
	push   ebx                                                          
	mov    edi,DWORD PTR [esp+0x2c]                                     
	mov    esi,DWORD PTR [esp+0x28]                                     
	lea    ebx,[edi+0x8]                                                
	sar    ebx,0x3                                                      
	test   ebx,ebx                                                      
	je     put_h264_qpel8or16_hv_lowpass_ssse3_5192d                    
	mov    ebp,0xfffffffb                                               
	mov    eax,DWORD PTR [esp+0x1c]                                     
	mov    edx,esi                                                      
	sub    ebp,edi                                                      
	mov    ecx,DWORD PTR [esp+0x18]                                     
	not    edx                                                          
	imul   ebp,esi                                                      
	lea    eax,[eax+edx*2]                                              
	xor    edx,edx                                                      
	add    ebp,0x8                                                      
put_h264_qpel8or16_hv_lowpass_ssse3_514f8:                           
	pxor   xmm7,xmm7                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm1,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm2,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm3,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm4,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	punpcklbw xmm0,xmm7                                                 
	punpcklbw xmm1,xmm7                                                 
	punpcklbw xmm2,xmm7                                                 
	punpcklbw xmm3,xmm7                                                 
	punpcklbw xmm4,xmm7                                                 
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx],xmm6                                       
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x30],xmm6                                  
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x60],xmm6                                  
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x90],xmm6                                  
                                                                     
	movdqa xmm6,xmm0                                                    
	movq   xmm3,QWORD PTR [eax]                                         
	paddw  xmm6,xmm1                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm5                                                    
	psubw  xmm6,xmm2                                                    
	punpcklbw xmm3,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm4,xmm3                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm4                                                    
	movdqa XMMWORD PTR [ecx+0xc0],xmm6                                  
                                                                     
	movdqa xmm6,xmm1                                                    
	movq   xmm4,QWORD PTR [eax]                                         
	paddw  xmm6,xmm2                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm0                                                    
	psubw  xmm6,xmm3                                                    
	punpcklbw xmm4,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm5,xmm4                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm5                                                    
	movdqa XMMWORD PTR [ecx+0xf0],xmm6                                  
                                                                     
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx+0x120],xmm6                                 
                                                                     
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x150],xmm6                                 
                                                                     
	cmp    edi,0x10                                                     
	jne    put_h264_qpel8or16_hv_lowpass_ssse3_5191d                    
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x180],xmm6                                 
                                                                     
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x1b0],xmm6                                 
                                                                     
	movdqa xmm6,xmm0                                                    
	movq   xmm3,QWORD PTR [eax]                                         
	paddw  xmm6,xmm1                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm5                                                    
	psubw  xmm6,xmm2                                                    
	punpcklbw xmm3,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm4,xmm3                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm4                                                    
	movdqa XMMWORD PTR [ecx+0x1e0],xmm6                                 
                                                                     
	movdqa xmm6,xmm1                                                    
	movq   xmm4,QWORD PTR [eax]                                         
	paddw  xmm6,xmm2                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm0                                                    
	psubw  xmm6,xmm3                                                    
	punpcklbw xmm4,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm5,xmm4                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm5                                                    
	movdqa XMMWORD PTR [ecx+0x210],xmm6                                 
                                                                     
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx+0x240],xmm6                                 
                                                                     
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x270],xmm6                                 
                                                                     
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x2a0],xmm6                                 
                                                                     
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x2d0],xmm6                                 
                                                                     
put_h264_qpel8or16_hv_lowpass_ssse3_5191d:                           
	add    edx,0x1                                                      
	add    ecx,0x10                                                     
	add    eax,ebp                                                      
	cmp    edx,ebx                                                      
	jne    put_h264_qpel8or16_hv_lowpass_ssse3_514f8                    
put_h264_qpel8or16_hv_lowpass_ssse3_5192d:                            
	cmp    edi,0x10                                                     
	je     put_h264_qpel8or16_hv_lowpass_ssse3_519c0                    
	mov    eax,DWORD PTR [esp+0x18]                                     
	mov    ecx,DWORD PTR [esp+0x14]                                     
	mov    esi,DWORD PTR [esp+0x20]                                     
put_h264_qpel8or16_hv_lowpass_ssse3_51942:                           
	movdqa xmm1,XMMWORD PTR [eax+0x10]                                  
	movdqa xmm0,XMMWORD PTR [eax]                                       
	movdqa xmm2,xmm1                                                    
	movdqa xmm3,xmm1                                                    
	movdqa xmm4,xmm1                                                    
	movdqa xmm5,xmm1                                                    
	palignr xmm5,xmm0,0xa                                               
	palignr xmm4,xmm0,0x8                                               
	palignr xmm3,xmm0,0x6                                               
	palignr xmm2,xmm0,0x4                                               
	palignr xmm1,xmm0,0x2                                               
	paddw  xmm0,xmm5                                                    
	paddw  xmm1,xmm4                                                    
	paddw  xmm2,xmm3                                                    
	psubw  xmm0,xmm1                                                    
	psraw  xmm0,0x2                                                     
	psubw  xmm0,xmm1                                                    
	paddw  xmm0,xmm2                                                    
	psraw  xmm0,0x2                                                     
	paddw  xmm0,xmm2                                                    
	psraw  xmm0,0x6                                                     
	packuswb xmm0,xmm0                                                  
	movq   QWORD PTR [ecx],xmm0                                         
	add    eax,0x30                                                     
	add    ecx,esi                                                      
	dec    edi                                                          
	jne    put_h264_qpel8or16_hv_lowpass_ssse3_51942                    
	pop    ebx                                                          
	pop    esi                                                          
	pop    edi                                                          
	pop    ebp                                                          
	ret                                                                 
	lea    esi,[esi+0x0]                                          
put_h264_qpel8or16_hv_lowpass_ssse3_519c0:                           
	mov    eax,DWORD PTR [esp+0x18]                                     
	mov    edx,0x10                                                     
	mov    ecx,DWORD PTR [esp+0x14]                                     
	mov    esi,DWORD PTR [esp+0x20]                                     
put_h264_qpel8or16_hv_lowpass_ssse3_519d1:                           
	movdqa xmm4,XMMWORD PTR [eax+0x20]                                  
	movdqa xmm5,XMMWORD PTR [eax+0x10]                                  
	movdqa xmm7,XMMWORD PTR [eax]                                       
	movdqa xmm3,xmm4                                                    
	movdqa xmm2,xmm4                                                    
	movdqa xmm1,xmm4                                                    
	movdqa xmm0,xmm4                                                    
	palignr xmm0,xmm5,0xa                                               
	palignr xmm1,xmm5,0x8                                               
	palignr xmm2,xmm5,0x6                                               
	palignr xmm3,xmm5,0x4                                               
	palignr xmm4,xmm5,0x2                                               
	paddw  xmm0,xmm5                                                    
	paddw  xmm1,xmm4                                                    
	paddw  xmm2,xmm3                                                    
	movdqa xmm6,xmm5                                                    
	movdqa xmm4,xmm5                                                    
	movdqa xmm3,xmm5                                                    
	palignr xmm4,xmm7,0x8                                               
	palignr xmm6,xmm7,0x2                                               
	palignr xmm3,xmm7,0xa                                               
	paddw  xmm4,xmm6                                                    
	movdqa xmm6,xmm5                                                    
	palignr xmm5,xmm7,0x6                                               
	palignr xmm6,xmm7,0x4                                               
	paddw  xmm3,xmm7                                                    
	paddw  xmm5,xmm6                                                    
	psubw  xmm0,xmm1                                                    
	psubw  xmm3,xmm4                                                    
	psraw  xmm0,0x2                                                     
	psraw  xmm3,0x2                                                     
	psubw  xmm0,xmm1                                                    
	psubw  xmm3,xmm4                                                    
	paddw  xmm0,xmm2                                                    
	paddw  xmm3,xmm5                                                    
	psraw  xmm0,0x2                                                     
	psraw  xmm3,0x2                                                     
	paddw  xmm0,xmm2                                                    
	paddw  xmm3,xmm5                                                    
	psraw  xmm0,0x6                                                     
	psraw  xmm3,0x6                                                     
	packuswb xmm3,xmm0                                                  
	movdqa XMMWORD PTR [ecx],xmm3                                       
	add    eax,0x30                                                     
	add    ecx,esi                                                      
	dec    edx                                                          
	jne    put_h264_qpel8or16_hv_lowpass_ssse3_519d1                    
	pop    ebx                                                          
	pop    esi                                                          
	pop    edi                                                          
	pop    ebp                                                          
	ret                                                                 
	}
}
void put_h264_qpel8_hv_lowpass_ssse3(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
    put_h264_qpel8or16_hv_lowpass_ssse3(dst, tmp, src, dstStride, tmpStride, srcStride, 8);
}
void put_h264_qpel16_hv_lowpass_ssse3(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
    put_h264_qpel8or16_hv_lowpass_ssse3(dst, tmp, src, dstStride, tmpStride, srcStride, 16);
}


void put_h264_qpel16_h_lowpass_ssse3(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	put_h264_qpel8_h_lowpass_ssse3(dst , src , dstStride, srcStride);
	put_h264_qpel8_h_lowpass_ssse3(dst+8, src+8, dstStride, srcStride);
	src += 8*srcStride;
	dst += 8*dstStride;
	put_h264_qpel8_h_lowpass_ssse3(dst , src , dstStride, srcStride);
	put_h264_qpel8_h_lowpass_ssse3(dst+8, src+8, dstStride, srcStride);
}
#define put_pixels8_l2_sse2 put_pixels8_l2_mmx2
#define put_pixels16_l2_sse2 put_pixels16_l2_mmx2
#define put_pixels8_l2_ssse3 put_pixels8_l2_mmx2
#define put_pixels16_l2_ssse3 put_pixels16_l2_mmx2


#define put_pixels8_l2_shift5_sse2 put_pixels8_l2_shift5_mmx2
#define put_pixels16_l2_shift5_sse2 put_pixels16_l2_shift5_mmx2
#define put_pixels8_l2_shift5_ssse3 put_pixels8_l2_shift5_mmx2
#define put_pixels16_l2_shift5_ssse3 put_pixels16_l2_shift5_mmx2



#define put_h264_qpel8_h_lowpass_l2_sse2 put_h264_qpel8_h_lowpass_l2_mmx2
#define put_h264_qpel16_h_lowpass_l2_sse2 put_h264_qpel16_h_lowpass_l2_mmx2
#define put_h264_qpel8_v_lowpass_ssse3 put_h264_qpel8_v_lowpass_sse2
#define put_h264_qpel16_v_lowpass_ssse3 put_h264_qpel16_v_lowpass_sse2
#define put_h264_qpel8or16_hv2_lowpass_sse2 put_h264_qpel8or16_hv2_lowpass_mmx2



void put_pixels16_l2_shift5_mmx2(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
    put_pixels8_l2_shift5_mmx2(dst  , src16  , src8  , dstStride, src8Stride, h);
    put_pixels8_l2_shift5_mmx2(dst+8, src16+8, src8+8, dstStride, src8Stride, h);
}
void put_pixels16_l2_shift5_3dnow(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
    put_pixels8_l2_shift5_3dnow(dst  , src16  , src8  , dstStride, src8Stride, h);
    put_pixels8_l2_shift5_3dnow(dst+8, src16+8, src8+8, dstStride, src8Stride, h);
}

//#define H264_MC(OPNAME, SIZE, MMX, ALIGN) \
//H264_MC_V(OPNAME, SIZE, MMX, ALIGN)\
//H264_MC_H(OPNAME, SIZE, MMX, ALIGN)\
//H264_MC_HV(OPNAME, SIZE, MMX, ALIGN)\


#define put_h264_qpel8_mc00_sse2 put_h264_qpel8_mc00_mmx2


//////#define H264_MC_H(OPNAME, SIZE, MMX, ALIGN) \
//////static void OPNAME ## h264_qpel ## SIZE ## _mc10_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_l2_ ## MMX(dst, src, src, stride, stride);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc20_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_ ## MMX(dst, src, stride, stride);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc30_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_l2_ ## MMX(dst, src, src+1, stride, stride);\
//////}\
//////
//////#define H264_MC_V(OPNAME, SIZE, MMX, ALIGN) \
//////static void OPNAME ## h264_qpel ## SIZE ## _mc01_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*SIZE];\
//////    put_h264_qpel ## SIZE ## _v_lowpass_ ## MMX(temp, src, SIZE, stride);\
//////    OPNAME ## pixels ## SIZE ## _l2_ ## MMX(dst, src, temp, stride, stride, SIZE);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc02_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    OPNAME ## h264_qpel ## SIZE ## _v_lowpass_ ## MMX(dst, src, stride, stride);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc03_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*SIZE];\
//////    put_h264_qpel ## SIZE ## _v_lowpass_ ## MMX(temp, src, SIZE, stride);\
//////    OPNAME ## pixels ## SIZE ## _l2_ ## MMX(dst, src+stride, temp, stride, stride, SIZE);\
//////}\
//////
//////#define H264_MC_HV(OPNAME, SIZE, MMX, ALIGN) \
//////static void OPNAME ## h264_qpel ## SIZE ## _mc11_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*SIZE];\
//////    put_h264_qpel ## SIZE ## _v_lowpass_ ## MMX(temp, src, SIZE, stride);\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_l2_ ## MMX(dst, src, temp, stride, SIZE);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc31_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*SIZE];\
//////    put_h264_qpel ## SIZE ## _v_lowpass_ ## MMX(temp, src+1, SIZE, stride);\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_l2_ ## MMX(dst, src, temp, stride, SIZE);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc13_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*SIZE];\
//////    put_h264_qpel ## SIZE ## _v_lowpass_ ## MMX(temp, src, SIZE, stride);\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_l2_ ## MMX(dst, src+stride, temp, stride, SIZE);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc33_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*SIZE];\
//////    put_h264_qpel ## SIZE ## _v_lowpass_ ## MMX(temp, src+1, SIZE, stride);\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_l2_ ## MMX(dst, src+stride, temp, stride, SIZE);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc22_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint16_t, temp)[SIZE*(SIZE<8?12:24)];\
//////    OPNAME ## h264_qpel ## SIZE ## _hv_lowpass_ ## MMX(dst, temp, src, stride, SIZE, stride);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc21_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*(SIZE<8?12:24)*2 + SIZE*SIZE];\
//////    uint8_t * const halfHV= temp;\
//////    int16_t * const halfV= (int16_t*)(temp + SIZE*SIZE);\
//////    assert(((int)temp & 7) == 0);\
//////    put_h264_qpel ## SIZE ## _hv_lowpass_ ## MMX(halfHV, halfV, src, SIZE, SIZE, stride);\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_l2_ ## MMX(dst, src, halfHV, stride, SIZE);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc23_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*(SIZE<8?12:24)*2 + SIZE*SIZE];\
//////    uint8_t * const halfHV= temp;\
//////    int16_t * const halfV= (int16_t*)(temp + SIZE*SIZE);\
//////    assert(((int)temp & 7) == 0);\
//////    put_h264_qpel ## SIZE ## _hv_lowpass_ ## MMX(halfHV, halfV, src, SIZE, SIZE, stride);\
//////    OPNAME ## h264_qpel ## SIZE ## _h_lowpass_l2_ ## MMX(dst, src+stride, halfHV, stride, SIZE);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc12_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*(SIZE<8?12:24)*2 + SIZE*SIZE];\
//////    uint8_t * const halfHV= temp;\
//////    int16_t * const halfV= (int16_t*)(temp + SIZE*SIZE);\
//////    assert(((int)temp & 7) == 0);\
//////    put_h264_qpel ## SIZE ## _hv_lowpass_ ## MMX(halfHV, halfV, src, SIZE, SIZE, stride);\
//////    OPNAME ## pixels ## SIZE ## _l2_shift5_ ## MMX(dst, halfV+2, halfHV, stride, SIZE, SIZE);\
//////}\
//////\
//////static void OPNAME ## h264_qpel ## SIZE ## _mc32_ ## MMX(uint8_t *dst, uint8_t *src, int stride){\
//////    DECLARE_ALIGNED(ALIGN, uint8_t, temp)[SIZE*(SIZE<8?12:24)*2 + SIZE*SIZE];\
//////    uint8_t * const halfHV= temp;\
//////    int16_t * const halfV= (int16_t*)(temp + SIZE*SIZE);\
//////    assert(((int)temp & 7) == 0);\
//////    put_h264_qpel ## SIZE ## _hv_lowpass_ ## MMX(halfHV, halfV, src, SIZE, SIZE, stride);\
//////    OPNAME ## pixels ## SIZE ## _l2_shift5_ ## MMX(dst, halfV+3, halfHV, stride, SIZE, SIZE);\
//////}\
//////
//////#define H264_MC_4816(MMX)\
//////H264_MC(put_, 4, MMX, 8)\
//////H264_MC(put_, 8, MMX, 8)\
//////H264_MC(put_, 16,MMX, 8)\
//////H264_MC(avg_, 4, MMX, 8)\
//////H264_MC(avg_, 8, MMX, 8)\
//////H264_MC(avg_, 16,MMX, 8)\
//////
//////#define H264_MC_816(QPEL, XMM)\
//////QPEL(put_, 8, XMM, 16)\
//////QPEL(put_, 16,XMM, 16)\
//////QPEL(avg_, 8, XMM, 16)\
//////QPEL(avg_, 16,XMM, 16)\


#if 0

H264_MC_4816(3dnow)
H264_MC_4816(mmx2)
H264_MC_816(H264_MC_V, sse2)
H264_MC_816(H264_MC_HV, sse2)
H264_MC_816(H264_MC_H, ssse3)
H264_MC_816(H264_MC_HV, ssse3)

#else

 void put_h264_qpel4_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src, 4, stride); 
     put_pixels4_l2_3dnow(dst, src, temp, stride, stride, 4);
 }
 void put_h264_qpel4_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     put_h264_qpel4_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_h264_qpel4_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src, 4, stride); 
     put_pixels4_l2_3dnow(dst, src+stride, temp, stride, stride, 4);
 }
 void put_h264_qpel4_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     put_h264_qpel4_h_lowpass_l2_3dnow(dst, src, src, stride, stride);
 }
 void put_h264_qpel4_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     put_h264_qpel4_h_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_h264_qpel4_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     put_h264_qpel4_h_lowpass_l2_3dnow(dst, src, src+1, stride, stride);
 }
 void put_h264_qpel4_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_3dnow(dst, src, temp, stride, 4);
 }
 void put_h264_qpel4_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src+1, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_3dnow(dst, src, temp, stride, 4);
 }
 void put_h264_qpel4_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4];
     put_h264_qpel4_v_lowpass_3dnow(temp, src, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 4);
 }
 void put_h264_qpel4_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src+1, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 4);
 }
 void put_h264_qpel4_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint16_t, temp)[4*(4<8?12:24)]; 
     put_h264_qpel4_hv_lowpass_3dnow(dst, temp, src, stride, 4, stride);
 }
 void put_h264_qpel4_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4];
     uint8_t * const halfHV= temp;
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_3dnow(halfHV, halfV, src, 4, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_3dnow(dst, src, halfHV, stride, 4);
 }
 void put_h264_qpel4_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4];
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_3dnow(halfHV, halfV, src, 4, 4, stride);
     put_h264_qpel4_h_lowpass_l2_3dnow(dst, src+stride, halfHV, stride, 4);
 }
 void put_h264_qpel4_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_3dnow(halfHV, halfV, src, 4, 4, stride); 
     put_pixels4_l2_shift5_3dnow(dst, halfV+2, halfHV, stride, 4, 4);
 }
 void put_h264_qpel4_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_3dnow(halfHV, halfV, src, 4, 4, stride); 
     put_pixels4_l2_shift5_3dnow(dst, halfV+3, halfHV, stride, 4, 4);
 }
 void put_h264_qpel8_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8];
     put_h264_qpel8_v_lowpass_3dnow(temp, src, 8, stride);
     put_pixels8_l2_3dnow(dst, src, temp, stride, stride, 8);
 }
 void put_h264_qpel8_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     put_h264_qpel8_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_h264_qpel8_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src, 8, stride); 
     put_pixels8_l2_3dnow(dst, src+stride, temp, stride, stride, 8);
 }
 void put_h264_qpel8_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
     put_h264_qpel8_h_lowpass_l2_3dnow(dst, src, src, stride, stride);
 }
 void put_h264_qpel8_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel8_h_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_h264_qpel8_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel8_h_lowpass_l2_3dnow(dst, src, src+1, stride, stride);
 }
 void put_h264_qpel8_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_3dnow(dst, src, temp, stride, 8);
 }
 void put_h264_qpel8_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src+1, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_3dnow(dst, src, temp, stride, 8);
 }
 void put_h264_qpel8_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 8);
 }
 void put_h264_qpel8_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src+1, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 8);
 }
 void put_h264_qpel8_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint16_t, temp)[8*(8<8?12:24)]; 
     put_h264_qpel8_hv_lowpass_3dnow(dst, temp, src, stride, 8, stride);
 }
 void put_h264_qpel8_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel8_hv_lowpass_3dnow(halfHV, halfV, src, 8, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_3dnow(dst, src, halfHV, stride, 8);
 }
 void put_h264_qpel8_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel8_hv_lowpass_3dnow(halfHV, halfV, src, 8, 8, stride);
     put_h264_qpel8_h_lowpass_l2_3dnow(dst, src+stride, halfHV, stride, 8);
 }
 void put_h264_qpel8_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
     uint8_t * const halfHV= temp;
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel8_hv_lowpass_3dnow(halfHV, halfV, src, 8, 8, stride);
     put_pixels8_l2_shift5_3dnow(dst, halfV+2, halfHV, stride, 8, 8);
 }
 void put_h264_qpel8_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel8_hv_lowpass_3dnow(halfHV, halfV, src, 8, 8, stride);
     put_pixels8_l2_shift5_3dnow(dst, halfV+3, halfHV, stride, 8, 8);
 }
 void put_h264_qpel16_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src, 16, stride); 
     put_pixels16_l2_3dnow(dst, src, temp, stride, stride, 16);
 }
 void put_h264_qpel16_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel16_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_h264_qpel16_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src, 16, stride); 
     put_pixels16_l2_3dnow(dst, src+stride, temp, stride, stride, 16);
 }
 void put_h264_qpel16_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel16_h_lowpass_l2_3dnow(dst, src, src, stride, stride);
 }
 void put_h264_qpel16_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel16_h_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_h264_qpel16_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel16_h_lowpass_l2_3dnow(dst, src, src+1, stride, stride);
 }
 void put_h264_qpel16_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src, 16, stride);
     put_h264_qpel16_h_lowpass_l2_3dnow(dst, src, temp, stride, 16);
 }
 void put_h264_qpel16_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src+1, 16, stride); 
     put_h264_qpel16_h_lowpass_l2_3dnow(dst, src, temp, stride, 16);
 }
 void put_h264_qpel16_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src, 16, stride); 
     put_h264_qpel16_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 16);
 }
 void put_h264_qpel16_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src+1, 16, stride); 
     put_h264_qpel16_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 16);
 }
 void put_h264_qpel16_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint16_t, temp)[16*(16<8?12:24)]; 
     put_h264_qpel16_hv_lowpass_3dnow(dst, temp, src, stride, 16, stride);
 }
 void put_h264_qpel16_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 16*16); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel16_hv_lowpass_3dnow(halfHV, halfV, src, 16, 16, stride); 
     put_h264_qpel16_h_lowpass_l2_3dnow(dst, src, halfHV, stride, 16);
 }
 void put_h264_qpel16_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 16*16); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel16_hv_lowpass_3dnow(halfHV, halfV, src, 16, 16, stride);
     put_h264_qpel16_h_lowpass_l2_3dnow(dst, src+stride, halfHV, stride, 16);
 }
 void put_h264_qpel16_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 16*16); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel16_hv_lowpass_3dnow(halfHV, halfV, src, 16, 16, stride); 
     put_pixels16_l2_shift5_3dnow(dst, halfV+2, halfHV, stride, 16, 16);
 }
 void put_h264_qpel16_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 16*16); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel16_hv_lowpass_3dnow(halfHV, halfV, src, 16, 16, stride);
     put_pixels16_l2_shift5_3dnow(dst, halfV+3, halfHV, stride, 16, 16);
 }
 
 void put_h264_qpel4_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4];
     put_h264_qpel4_v_lowpass_mmx2(temp, src, 4, stride); 
     put_pixels4_l2_mmx2(dst, src, temp, stride, stride, 4);
 }
 void put_h264_qpel4_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel4_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_h264_qpel4_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_mmx2(temp, src, 4, stride); 
     put_pixels4_l2_mmx2(dst, src+stride, temp, stride, stride, 4);
 }
 void put_h264_qpel4_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel4_h_lowpass_l2_mmx2(dst, src, src, stride, stride);
 }
 void put_h264_qpel4_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel4_h_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_h264_qpel4_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel4_h_lowpass_l2_mmx2(dst, src, src+1, stride, stride);
 }
 void put_h264_qpel4_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_mmx2(temp, src, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_mmx2(dst, src, temp, stride, 4);
 }
 void put_h264_qpel4_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_mmx2(temp, src+1, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_mmx2(dst, src, temp, stride, 4);
 }
 void put_h264_qpel4_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_mmx2(temp, src, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 4);
 }
 void put_h264_qpel4_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_mmx2(temp, src+1, 4, stride); 
     put_h264_qpel4_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 4);
 }
 void put_h264_qpel4_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint16_t, temp)[4*(4<8?12:24)];
     put_h264_qpel4_hv_lowpass_mmx2(dst, temp, src, stride, 4, stride);
 }
 void put_h264_qpel4_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp;
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_mmx2(halfHV, halfV, src, 4, 4, stride);
     put_h264_qpel4_h_lowpass_l2_mmx2(dst, src, halfHV, stride, 4);
 }
 void put_h264_qpel4_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4);
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_mmx2(halfHV, halfV, src, 4, 4, stride);
     put_h264_qpel4_h_lowpass_l2_mmx2(dst, src+stride, halfHV, stride, 4);
 }
 void put_h264_qpel4_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0);
     put_h264_qpel4_hv_lowpass_mmx2(halfHV, halfV, src, 4, 4, stride); 
     put_pixels4_l2_shift5_mmx2(dst, halfV+2, halfHV, stride, 4, 4);
 }
 void put_h264_qpel4_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4);
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_mmx2(halfHV, halfV, src, 4, 4, stride);
     put_pixels4_l2_shift5_mmx2(dst, halfV+3, halfHV, stride, 4, 4);
 }
 void put_h264_qpel8_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_mmx2(temp, src, 8, stride); 
     put_pixels8_l2_mmx2(dst, src, temp, stride, stride, 8);
 }
 void put_h264_qpel8_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel8_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_h264_qpel8_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_mmx2(temp, src, 8, stride); 
     put_pixels8_l2_mmx2(dst, src+stride, temp, stride, stride, 8);
 }
 void put_h264_qpel8_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
     put_h264_qpel8_h_lowpass_l2_mmx2(dst, src, src, stride, stride);
 }
 void put_h264_qpel8_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel8_h_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_h264_qpel8_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     put_h264_qpel8_h_lowpass_l2_mmx2(dst, src, src+1, stride, stride);
 }
 void put_h264_qpel8_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_mmx2(temp, src, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_mmx2(dst, src, temp, stride, 8);
 }
 void put_h264_qpel8_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_mmx2(temp, src+1, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_mmx2(dst, src, temp, stride, 8);
 }
 void put_h264_qpel8_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_mmx2(temp, src, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 8);
 }
 void put_h264_qpel8_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_mmx2(temp, src+1, 8, stride); 
     put_h264_qpel8_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 8);
 }
 void put_h264_qpel8_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint16_t, temp)[8*(8<8?12:24)]; 
     put_h264_qpel8_hv_lowpass_mmx2(dst, temp, src, stride, 8, stride);
 }
 void put_h264_qpel8_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel8_hv_lowpass_mmx2(halfHV, halfV, src, 8, 8, stride);
     put_h264_qpel8_h_lowpass_l2_mmx2(dst, src, halfHV, stride, 8);
 }
 void put_h264_qpel8_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
    DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
    uint8_t * const halfHV= temp; 
    int16_t * const halfV= (int16_t*)(temp + 8*8); 
    assert(((int)temp & 7) == 0);
    put_h264_qpel8_hv_lowpass_mmx2(halfHV, halfV, src, 8, 8, stride);
    put_h264_qpel8_h_lowpass_l2_mmx2(dst, src+stride, halfHV, stride, 8);
}
 void put_h264_qpel8_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_mmx2(halfHV, halfV, src, 8, 8, stride);
	 put_pixels8_l2_shift5_mmx2(dst, halfV+2, halfHV, stride, 8, 8);
 }
 void put_h264_qpel8_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_mmx2(halfHV, halfV, src, 8, 8, stride);
	 put_pixels8_l2_shift5_mmx2(dst, halfV+3, halfHV, stride, 8, 8);
 }
 void put_h264_qpel16_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src, 16, stride);
	 put_pixels16_l2_mmx2(dst, src, temp, stride, stride, 16);
 }
 void put_h264_qpel16_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_h264_qpel16_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_h264_qpel16_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_mmx2(temp, src, 16, stride); 
	 put_pixels16_l2_mmx2(dst, src+stride, temp, stride, stride, 16);
 }
 void put_h264_qpel16_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel16_h_lowpass_l2_mmx2(dst, src, src, stride, stride);
 }
 void put_h264_qpel16_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_h264_qpel16_h_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_h264_qpel16_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_h264_qpel16_h_lowpass_l2_mmx2(dst, src, src+1, stride, stride);
 }
 void put_h264_qpel16_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_mmx2(temp, src, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_mmx2(dst, src, temp, stride, 16);
 }
 void put_h264_qpel16_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src+1, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_mmx2(dst, src, temp, stride, 16);
 }
 void put_h264_qpel16_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 16);
 }
 void put_h264_qpel16_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src+1, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 16);
 }
 void put_h264_qpel16_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint16_t, temp)[16*(16<8?12:24)];
	 put_h264_qpel16_hv_lowpass_mmx2(dst, temp, src, stride, 16, stride);
 }
 void put_h264_qpel16_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_mmx2(halfHV, halfV, src, 16, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_mmx2(dst, src, halfHV, stride, 16);
 }
 void put_h264_qpel16_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_mmx2(halfHV, halfV, src, 16, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_mmx2(dst, src+stride, halfHV, stride, 16);
 }
 void put_h264_qpel16_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel16_hv_lowpass_mmx2(halfHV, halfV, src, 16, 16, stride); 
	 put_pixels16_l2_shift5_mmx2(dst, halfV+2, halfHV, stride, 16, 16);
 }
 void put_h264_qpel16_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_mmx2(halfHV, halfV, src, 16, 16, stride); 
	 put_pixels16_l2_shift5_mmx2(dst, halfV+3, halfHV, stride, 16, 16);
 }
 
 void put_h264_qpel8_mc01_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_sse2(temp, src, 8, stride);
	 put_pixels8_l2_sse2(dst, src, temp, stride, stride, 8);
 }
 void put_h264_qpel8_mc02_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel8_v_lowpass_sse2(dst, src, stride, stride);
 }
 void put_h264_qpel8_mc03_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_sse2(temp, src, 8, stride); 
	 put_pixels8_l2_sse2(dst, src+stride, temp, stride, stride, 8);
 }
 void put_h264_qpel16_mc01_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_sse2(temp, src, 16, stride); 
	 put_pixels16_l2_sse2(dst, src, temp, stride, stride, 16);
 }
 void put_h264_qpel16_mc02_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel16_v_lowpass_sse2(dst, src, stride, stride);
 }
 void put_h264_qpel16_mc03_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_sse2(temp, src, 16, stride);
	 put_pixels16_l2_sse2(dst, src+stride, temp, stride, stride, 16);
 }
 
 void put_h264_qpel8_mc11_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_sse2(temp, src, 8, stride); 
	 put_h264_qpel8_h_lowpass_l2_sse2(dst, src, temp, stride, 8);
 }
 void put_h264_qpel8_mc31_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_sse2(temp, src+1, 8, stride);
	 put_h264_qpel8_h_lowpass_l2_sse2(dst, src, temp, stride, 8);
 }
 void put_h264_qpel8_mc13_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_sse2(temp, src, 8, stride);
	 put_h264_qpel8_h_lowpass_l2_sse2(dst, src+stride, temp, stride, 8);
 }
 void put_h264_qpel8_mc33_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_sse2(temp, src+1, 8, stride);
	 put_h264_qpel8_h_lowpass_l2_sse2(dst, src+stride, temp, stride, 8);
 }
 void put_h264_qpel8_mc22_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint16_t, temp)[8*(8<8?12:24)];
	 put_h264_qpel8_hv_lowpass_sse2(dst, temp, src, stride, 8, stride);
 }
 void put_h264_qpel8_mc21_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_sse2(halfHV, halfV, src, 8, 8, stride);
	 put_h264_qpel8_h_lowpass_l2_sse2(dst, src, halfHV, stride, 8);
 }
 void put_h264_qpel8_mc23_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_sse2(halfHV, halfV, src, 8, 8, stride);
	 put_h264_qpel8_h_lowpass_l2_sse2(dst, src+stride, halfHV, stride, 8);
 }
 void put_h264_qpel8_mc12_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_sse2(halfHV, halfV, src, 8, 8, stride); 
	 put_pixels8_l2_shift5_sse2(dst, halfV+2, halfHV, stride, 8, 8);
 }
 void put_h264_qpel8_mc32_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_sse2(halfHV, halfV, src, 8, 8, stride);
	 put_pixels8_l2_shift5_sse2(dst, halfV+3, halfHV, stride, 8, 8);
 }
 void put_h264_qpel16_mc11_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_sse2(temp, src, 16, stride); 
	 put_h264_qpel16_h_lowpass_l2_sse2(dst, src, temp, stride, 16);
 }
 void put_h264_qpel16_mc31_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_sse2(temp, src+1, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_sse2(dst, src, temp, stride, 16);
 }
 void put_h264_qpel16_mc13_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_sse2(temp, src, 16, stride); 
	 put_h264_qpel16_h_lowpass_l2_sse2(dst, src+stride, temp, stride, 16);
 }
 void put_h264_qpel16_mc33_sse2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_sse2(temp, src+1, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_sse2(dst, src+stride, temp, stride, 16);
 }
 void put_h264_qpel16_mc22_sse2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint16_t, temp)[16*(16<8?12:24)]; 
	 put_h264_qpel16_hv_lowpass_sse2(dst, temp, src, stride, 16, stride);
 }
 void put_h264_qpel16_mc21_sse2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel16_hv_lowpass_sse2(halfHV, halfV, src, 16, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_sse2(dst, src, halfHV, stride, 16);
 }
 void put_h264_qpel16_mc23_sse2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel16_hv_lowpass_sse2(halfHV, halfV, src, 16, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_sse2(dst, src+stride, halfHV, stride, 16);
 }
 void put_h264_qpel16_mc12_sse2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel16_hv_lowpass_sse2(halfHV, halfV, src, 16, 16, stride);
	 put_pixels16_l2_shift5_sse2(dst, halfV+2, halfHV, stride, 16, 16);
 }
 void put_h264_qpel16_mc32_sse2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_sse2(halfHV, halfV, src, 16, 16, stride);
	 put_pixels16_l2_shift5_sse2(dst, halfV+3, halfHV, stride, 16, 16);
 }
 
 void put_h264_qpel8_mc10_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel8_h_lowpass_l2_ssse3(dst, src, src, stride, stride);
 }
 void put_h264_qpel8_mc20_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel8_h_lowpass_ssse3(dst, src, stride, stride);
 }
 void put_h264_qpel8_mc30_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel8_h_lowpass_l2_ssse3(dst, src, src+1, stride, stride);
 }
 void put_h264_qpel16_mc10_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel16_h_lowpass_l2_ssse3(dst, src, src, stride, stride);
 }
 void put_h264_qpel16_mc20_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel16_h_lowpass_ssse3(dst, src, stride, stride);
 }
 void put_h264_qpel16_mc30_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_h264_qpel16_h_lowpass_l2_ssse3(dst, src, src+1, stride, stride);
 }
 
 void put_h264_qpel8_mc11_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_ssse3(temp, src, 8, stride); 
	 put_h264_qpel8_h_lowpass_l2_ssse3(dst, src, temp, stride, 8);
 }
 void put_h264_qpel8_mc31_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_ssse3(temp, src+1, 8, stride); 
	 put_h264_qpel8_h_lowpass_l2_ssse3(dst, src, temp, stride, 8);
 }
 void put_h264_qpel8_mc13_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_ssse3(temp, src, 8, stride); 
	 put_h264_qpel8_h_lowpass_l2_ssse3(dst, src+stride, temp, stride, 8);
 }
 void put_h264_qpel8_mc33_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_ssse3(temp, src+1, 8, stride); 
	 put_h264_qpel8_h_lowpass_l2_ssse3(dst, src+stride, temp, stride, 8);
 }
 void put_h264_qpel8_mc22_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint16_t, temp)[8*(8<8?12:24)]; 
	 put_h264_qpel8_hv_lowpass_ssse3(dst, temp, src, stride, 8, stride);
 }
 void put_h264_qpel8_mc21_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_ssse3(halfHV, halfV, src, 8, 8, stride); 
	 put_h264_qpel8_h_lowpass_l2_ssse3(dst, src, halfHV, stride, 8);
 }
 void put_h264_qpel8_mc23_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_ssse3(halfHV, halfV, src, 8, 8, stride);
	 put_h264_qpel8_h_lowpass_l2_ssse3(dst, src+stride, halfHV, stride, 8);
 }
 void put_h264_qpel8_mc12_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_ssse3(halfHV, halfV, src, 8, 8, stride); 
	 put_pixels8_l2_shift5_ssse3(dst, halfV+2, halfHV, stride, 8, 8);
 }
 void put_h264_qpel8_mc32_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_ssse3(halfHV, halfV, src, 8, 8, stride);
	 put_pixels8_l2_shift5_ssse3(dst, halfV+3, halfHV, stride, 8, 8);
 }
 void put_h264_qpel16_mc11_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_ssse3(temp, src, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_ssse3(dst, src, temp, stride, 16);
 }
 void put_h264_qpel16_mc31_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_ssse3(temp, src+1, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_ssse3(dst, src, temp, stride, 16);
 }
 void put_h264_qpel16_mc13_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_ssse3(temp, src, 16, stride); 
	 put_h264_qpel16_h_lowpass_l2_ssse3(dst, src+stride, temp, stride, 16);
 }
 void put_h264_qpel16_mc33_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_ssse3(temp, src+1, 16, stride); 
	 put_h264_qpel16_h_lowpass_l2_ssse3(dst, src+stride, temp, stride, 16);
 }
 void put_h264_qpel16_mc22_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint16_t, temp)[16*(16<8?12:24)];
	 put_h264_qpel16_hv_lowpass_ssse3(dst, temp, src, stride, 16, stride);
 }
 void put_h264_qpel16_mc21_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 16*16); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_ssse3(halfHV, halfV, src, 16, 16, stride); 
	 put_h264_qpel16_h_lowpass_l2_ssse3(dst, src, halfHV, stride, 16);
 }
 void put_h264_qpel16_mc23_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel16_hv_lowpass_ssse3(halfHV, halfV, src, 16, 16, stride);
	 put_h264_qpel16_h_lowpass_l2_ssse3(dst, src+stride, halfHV, stride, 16);
 }
 void put_h264_qpel16_mc12_ssse3(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_ssse3(halfHV, halfV, src, 16, 16, stride); 
	 put_pixels16_l2_shift5_ssse3(dst, halfV+2, halfHV, stride, 16, 16);
 }
 void put_h264_qpel16_mc32_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_ssse3(halfHV, halfV, src, 16, 16, stride); 
	 put_pixels16_l2_shift5_ssse3(dst, halfV+3, halfHV, stride, 16, 16);
 }
 
 #endif

#if 0
// for useless code!
void __declspec(naked) avg_h264_qpel4_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                     
	mov    eax,DWORD PTR [esp+0x14]    
	mov    DWORD PTR [esp],esi         
	mov    esi,DWORD PTR [esp+0x10]    
	mov    DWORD PTR [esp+0x4],edi     
	mov    edi,DWORD PTR [esp+0xc]     
	lea    edx,[eax+eax*2]             
	movd   mm0,DWORD PTR [edi]         
	movd   mm1,DWORD PTR [edi+eax*1]   
	movd   mm2,DWORD PTR [edi+eax*2]   
	movd   mm3,DWORD PTR [edi+edx*1]   
	pavgusb mm0,QWORD PTR [esi]        
	pavgusb mm1,QWORD PTR [esi+eax*1]  
	pavgusb mm2,QWORD PTR [esi+eax*2]  
	pavgusb mm3,QWORD PTR [esi+edx*1]  
	movd   DWORD PTR [edi],mm0         
	movd   DWORD PTR [edi+eax*1],mm1   
	movd   DWORD PTR [edi+eax*2],mm2   
	movd   DWORD PTR [edi+edx*1],mm3   
	mov    esi,DWORD PTR [esp]         
	mov    edi,DWORD PTR [esp+0x4]     
	add    esp,0x8                     
	ret
	}
}
void __declspec(naked) avg_h264_qpel8_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                       
	mov    ecx,0x8                       
	mov    DWORD PTR [esp],esi           
	mov    edx,DWORD PTR [esp+0x14]      
	mov    DWORD PTR [esp+0x4],edi       
	mov    esi,DWORD PTR [esp+0x10]      
	mov    edi,DWORD PTR [esp+0xc]       
	lea    eax,[edx+edx*1]               
avg_h264_qpel8_mc00_3dnowloop:       
	movq   mm0,QWORD PTR [edi]           
	movq   mm1,QWORD PTR [edi+edx*1]     
	pavgusb mm0,QWORD PTR [esi]          
	pavgusb mm1,QWORD PTR [esi+edx*1]    
	movq   QWORD PTR [edi],mm0           
	movq   QWORD PTR [edi+edx*1],mm1     
	add    esi,eax                       
	add    edi,eax                       
	movq   mm0,QWORD PTR [edi]           
	movq   mm1,QWORD PTR [edi+edx*1]     
	pavgusb mm0,QWORD PTR [esi]          
	pavgusb mm1,QWORD PTR [esi+edx*1]    
	add    esi,eax                       
	movq   QWORD PTR [edi],mm0           
	movq   QWORD PTR [edi+edx*1],mm1     
	add    edi,eax                       
	sub    ecx,0x4                       
	jne    avg_h264_qpel8_mc00_3dnowloop 
	mov    esi,DWORD PTR [esp]           
	mov    edi,DWORD PTR [esp+0x4]       
	add    esp,0x8                       
	ret
	}
}
void __declspec(naked) avg_h264_qpel16_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x10                                  
	mov    edx,0x10                                  
	mov    DWORD PTR [esp+0xc],ebp                   
	mov    ecx,DWORD PTR [esp+0x18]                  
	mov    ebp,DWORD PTR [esp+0x14]                  
	mov    DWORD PTR [esp],ebx                       
	mov    ebx,DWORD PTR [esp+0x1c]                  
	mov    DWORD PTR [esp+0x4],esi                   
	mov    DWORD PTR [esp+0x8],edi                   
	mov    esi,ecx                                   
	mov    edi,ebp                                   
	lea    eax,[ebx+ebx*1]                           
avg_h264_qpel16_mc00_3dnow_4821a:                
	movq   mm0,QWORD PTR [edi]                       
	movq   mm1,QWORD PTR [edi+ebx*1]                 
	pavgusb mm0,QWORD PTR [esi]                      
	pavgusb mm1,QWORD PTR [esi+ebx*1]                
	movq   QWORD PTR [edi],mm0                       
	movq   QWORD PTR [edi+ebx*1],mm1                 
	add    esi,eax                                   
	add    edi,eax                                   
	movq   mm0,QWORD PTR [edi]                       
	movq   mm1,QWORD PTR [edi+ebx*1]                 
	pavgusb mm0,QWORD PTR [esi]                      
	pavgusb mm1,QWORD PTR [esi+ebx*1]                
	add    esi,eax                                   
	movq   QWORD PTR [edi],mm0                       
	movq   QWORD PTR [edi+ebx*1],mm1                 
	add    edi,eax                                   
	sub    edx,0x4                                   
	jne    avg_h264_qpel16_mc00_3dnow_4821a          
	mov    edx,0x10                                  
	lea    esi,[ecx+0x8]                             
	lea    edi,[ebp+0x8]                             
	lea    eax,[ebx+ebx*1]                           
avg_h264_qpel16_mc00_3dnow_48263:                
	movq   mm0,QWORD PTR [edi]                       
	movq   mm1,QWORD PTR [edi+ebx*1]                 
	pavgusb mm0,QWORD PTR [esi]                      
	pavgusb mm1,QWORD PTR [esi+ebx*1]                
	movq   QWORD PTR [edi],mm0                       
	movq   QWORD PTR [edi+ebx*1],mm1                 
	add    esi,eax                                   
	add    edi,eax                                   
	movq   mm0,QWORD PTR [edi]                       
	movq   mm1,QWORD PTR [edi+ebx*1]                 
	pavgusb mm0,QWORD PTR [esi]                      
	pavgusb mm1,QWORD PTR [esi+ebx*1]                
	add    esi,eax                                   
	movq   QWORD PTR [edi],mm0                       
	movq   QWORD PTR [edi+ebx*1],mm1                 
	add    edi,eax                                   
	sub    edx,0x4                                   
	jne    avg_h264_qpel16_mc00_3dnow_48263          
	mov    ebx,DWORD PTR [esp]                       
	mov    esi,DWORD PTR [esp+0x4]                   
	mov    edi,DWORD PTR [esp+0x8]                   
	mov    ebp,DWORD PTR [esp+0xc]                   
	add    esp,0x10                                  
	ret
	}
}

void __declspec(naked) avg_h264_qpel4_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                   
	mov    eax,DWORD PTR [esp+0x14]  
	mov    DWORD PTR [esp],esi       
	mov    esi,DWORD PTR [esp+0x10]  
	mov    DWORD PTR [esp+0x4],edi   
	mov    edi,DWORD PTR [esp+0xc]   
	lea    edx,[eax+eax*2]           
	movd   mm0,DWORD PTR [edi]       
	movd   mm1,DWORD PTR [edi+eax*1] 
	movd   mm2,DWORD PTR [edi+eax*2] 
	movd   mm3,DWORD PTR [edi+edx*1] 
	pavgb  mm0,QWORD PTR [esi]       
	pavgb  mm1,QWORD PTR [esi+eax*1] 
	pavgb  mm2,QWORD PTR [esi+eax*2] 
	pavgb  mm3,QWORD PTR [esi+edx*1] 
	movd   DWORD PTR [edi],mm0       
	movd   DWORD PTR [edi+eax*1],mm1 
	movd   DWORD PTR [edi+eax*2],mm2 
	movd   DWORD PTR [edi+edx*1],mm3 
	mov    esi,DWORD PTR [esp]       
	mov    edi,DWORD PTR [esp+0x4]   
	add    esp,0x8                   
	ret
	}
}
void __declspec(naked) avg_h264_qpel8_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
			sub    esp,0x8                        
	mov    ecx,0x8                        
	mov    DWORD PTR [esp],esi            
	mov    edx,DWORD PTR [esp+0x14]       
	mov    DWORD PTR [esp+0x4],edi        
	mov    esi,DWORD PTR [esp+0x10]       
	mov    edi,DWORD PTR [esp+0xc]        
	lea    eax,[edx+edx*1]                
avg_h264_qpel8_mc00_mmx2loop:         
	movq   mm0,QWORD PTR [edi]            
	movq   mm1,QWORD PTR [edi+edx*1]      
	pavgb  mm0,QWORD PTR [esi]            
	pavgb  mm1,QWORD PTR [esi+edx*1]      
	movq   QWORD PTR [edi],mm0            
	movq   QWORD PTR [edi+edx*1],mm1      
	add    esi,eax                        
	add    edi,eax                        
	movq   mm0,QWORD PTR [edi]            
	movq   mm1,QWORD PTR [edi+edx*1]      
	pavgb  mm0,QWORD PTR [esi]            
	pavgb  mm1,QWORD PTR [esi+edx*1]      
	add    esi,eax                        
	movq   QWORD PTR [edi],mm0            
	movq   QWORD PTR [edi+edx*1],mm1      
	add    edi,eax                        
	sub    ecx,0x4                        
	jne    avg_h264_qpel8_mc00_mmx2loop   
	mov    esi,DWORD PTR [esp]            
	mov    edi,DWORD PTR [esp+0x4]        
	add    esp,0x8                        
	ret
	}
}
void __declspec(naked) avg_h264_qpel16_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x10                             
	mov    edx,0x10                             
	mov    DWORD PTR [esp+0xc],ebp              
	mov    ecx,DWORD PTR [esp+0x18]             
	mov    ebp,DWORD PTR [esp+0x14]             
	mov    DWORD PTR [esp],ebx                  
	mov    ebx,DWORD PTR [esp+0x1c]             
	mov    DWORD PTR [esp+0x4],esi              
	mov    DWORD PTR [esp+0x8],edi              
	mov    esi,ecx                              
	mov    edi,ebp                              
	lea    eax,[ebx+ebx*1]                      
avg_h264_qpel16_mc00_mmx2_4b3aa:            
	movq   mm0,QWORD PTR [edi]                  
	movq   mm1,QWORD PTR [edi+ebx*1]            
	pavgb  mm0,QWORD PTR [esi]                  
	pavgb  mm1,QWORD PTR [esi+ebx*1]            
	movq   QWORD PTR [edi],mm0                  
	movq   QWORD PTR [edi+ebx*1],mm1            
	add    esi,eax                              
	add    edi,eax                              
	movq   mm0,QWORD PTR [edi]                  
	movq   mm1,QWORD PTR [edi+ebx*1]            
	pavgb  mm0,QWORD PTR [esi]                  
	pavgb  mm1,QWORD PTR [esi+ebx*1]            
	add    esi,eax                              
	movq   QWORD PTR [edi],mm0                  
	movq   QWORD PTR [edi+ebx*1],mm1            
	add    edi,eax                              
	sub    edx,0x4                              
	jne    avg_h264_qpel16_mc00_mmx2_4b3aa      
	mov    edx,0x10                             
	lea    esi,[ecx+0x8]                        
	lea    edi,[ebp+0x8]                        
	lea    eax,[ebx+ebx*1]                      
avg_h264_qpel16_mc00_mmx2_4b3ef:            
	movq   mm0,QWORD PTR [edi]                  
	movq   mm1,QWORD PTR [edi+ebx*1]            
	pavgb  mm0,QWORD PTR [esi]                  
	pavgb  mm1,QWORD PTR [esi+ebx*1]            
	movq   QWORD PTR [edi],mm0                  
	movq   QWORD PTR [edi+ebx*1],mm1            
	add    esi,eax                              
	add    edi,eax                              
	movq   mm0,QWORD PTR [edi]                  
	movq   mm1,QWORD PTR [edi+ebx*1]            
	pavgb  mm0,QWORD PTR [esi]                  
	pavgb  mm1,QWORD PTR [esi+ebx*1]            
	add    esi,eax                              
	movq   QWORD PTR [edi],mm0                  
	movq   QWORD PTR [edi+ebx*1],mm1            
	add    edi,eax                              
	sub    edx,0x4                              
	jne    avg_h264_qpel16_mc00_mmx2_4b3ef      
	mov    ebx,DWORD PTR [esp]                  
	mov    esi,DWORD PTR [esp+0x4]              
	mov    edi,DWORD PTR [esp+0x8]              
	mov    ebp,DWORD PTR [esp+0xc]              
	add    esp,0x10                             
	ret
	}
}

void __declspec(naked) avg_h264_qpel16_mc00_sse2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
 	sub    esp,0x8                          
 	mov    eax,DWORD PTR [esp+0x14]         
 	mov    DWORD PTR [esp],ebx              
 	mov    edx,DWORD PTR [esp+0x10]         
 	mov    DWORD PTR [esp+0x4],esi          
 	mov    ecx,DWORD PTR [esp+0xc]          
 	mov    esi,0x10                         
 	lea    ebx,[eax+eax*2]                  
avg_h264_qpel16_mc00_sse2loop:          
 	movdqu xmm0,XMMWORD PTR [edx]           
 	movdqu xmm1,XMMWORD PTR [edx+eax*1]     
 	movdqu xmm2,XMMWORD PTR [edx+eax*2]     
 	movdqu xmm3,XMMWORD PTR [edx+ebx*1]     
 	lea    edx,[edx+eax*4]                  
 	pavgb  xmm0,XMMWORD PTR [ecx]           
 	pavgb  xmm1,XMMWORD PTR [ecx+eax*1]     
 	pavgb  xmm2,XMMWORD PTR [ecx+eax*2]     
 	pavgb  xmm3,XMMWORD PTR [ecx+ebx*1]     
 	movdqa XMMWORD PTR [ecx],xmm0           
 	movdqa XMMWORD PTR [ecx+eax*1],xmm1     
 	movdqa XMMWORD PTR [ecx+eax*2],xmm2     
 	movdqa XMMWORD PTR [ecx+ebx*1],xmm3     
 	sub    esi,0x4                          
 	lea    ecx,[ecx+eax*4]                  
 	jne    avg_h264_qpel16_mc00_sse2loop    
 	mov    ebx,DWORD PTR [esp]              
 	mov    esi,DWORD PTR [esp+0x4]          
 	add    esp,0x8                          
 	ret
	}
}

void __declspec(naked) avg_h264_qpel4_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                             
	mov    DWORD PTR [esp],ebx                 
	mov    ecx,DWORD PTR [esp+0xc]             
	mov    ebx,0x4                             
	mov    DWORD PTR [esp+0x4],esi             
	mov    eax,DWORD PTR [esp+0x10]            
	mov    edx,DWORD PTR [esp+0x18]            
	mov    esi,DWORD PTR [esp+0x14]            
	pxor   mm7,mm7                             
	movq   mm4,QWORD PTR [ff_pw_5]                
	movq   mm5,QWORD PTR [ff_pw_16]                
avg_h264_qpel4_h_lowpass_3dnowflag:         
	movd   mm1,DWORD PTR [eax-0x1]             
	movd   mm2,DWORD PTR [eax]                 
	movd   mm3,DWORD PTR [eax+0x1]             
	movd   mm0,DWORD PTR [eax+0x2]             
	punpcklbw mm1,mm7                          
	punpcklbw mm2,mm7                          
	punpcklbw mm3,mm7                          
	punpcklbw mm0,mm7                          
	paddw  mm1,mm0                             
	paddw  mm2,mm3                             
	movd   mm0,DWORD PTR [eax-0x2]             
	movd   mm3,DWORD PTR [eax+0x3]             
	punpcklbw mm0,mm7                          
	punpcklbw mm3,mm7                          
	paddw  mm0,mm3                             
	psllw  mm2,0x2                             
	psubw  mm2,mm1                             
	pmullw mm2,mm4                             
	paddw  mm0,mm5                             
	paddw  mm0,mm2                             
	psraw  mm0,0x5                             
	packuswb mm0,mm0                           
	movd   mm6,DWORD PTR [ecx]                 
	pavgusb mm0,mm6                            
	movd   DWORD PTR [ecx],mm0                 
	add    eax,edx                             
	add    ecx,esi                             
	dec    ebx                                 
	jne    avg_h264_qpel4_h_lowpass_3dnowflag  
	mov    ebx,DWORD PTR [esp]                 
	mov    esi,DWORD PTR [esp+0x4]             
	add    esp,0x8                             
	ret
	}
}
void __declspec(naked) avg_h264_qpel4_h_lowpass_l2_3dnow(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{	
	sub    esp,0x8                                   
	mov    DWORD PTR [esp],esi                       
	mov    ecx,DWORD PTR [esp+0xc]                   
	mov    DWORD PTR [esp+0x4],edi                   
	mov    eax,DWORD PTR [esp+0x10]                  
	mov    edx,DWORD PTR [esp+0x14]                  
	mov    esi,DWORD PTR [esp+0x18]                  
	mov    edi,DWORD PTR [esp+0x1c]                  
	pxor   mm7,mm7                                   
	movq   mm4,QWORD PTR [ff_pw_5]                      
	movq   mm5,QWORD PTR [ff_pw_16]                     
	movd   mm1,DWORD PTR [eax-0x1]                   
	movd   mm2,DWORD PTR [eax]                       
	movd   mm3,DWORD PTR [eax+0x1]                   
	movd   mm0,DWORD PTR [eax+0x2]                   
	punpcklbw mm1,mm7                                
	punpcklbw mm2,mm7                                
	punpcklbw mm3,mm7                                
	punpcklbw mm0,mm7                                
	paddw  mm1,mm0                                   
	paddw  mm2,mm3                                   
	movd   mm0,DWORD PTR [eax-0x2]                   
	movd   mm3,DWORD PTR [eax+0x3]                   
	punpcklbw mm0,mm7                                
	punpcklbw mm3,mm7                                
	paddw  mm0,mm3                                   
	psllw  mm2,0x2                                   
	psubw  mm2,mm1                                   
	pmullw mm2,mm4                                   
	paddw  mm0,mm5                                   
	paddw  mm0,mm2                                   
	movd   mm3,DWORD PTR [edx]                       
	psraw  mm0,0x5                                   
	packuswb mm0,mm0                                 
	pavgusb mm0,mm3                                  
	movd   mm6,DWORD PTR [ecx]                       
	pavgusb mm0,mm6                                  
	movd   DWORD PTR [ecx],mm0                       
	add    eax,esi                                   
	add    ecx,esi                                   
	add    edx,edi                                   
	movd   mm1,DWORD PTR [eax-0x1]                   
	movd   mm2,DWORD PTR [eax]                       
	movd   mm3,DWORD PTR [eax+0x1]                   
	movd   mm0,DWORD PTR [eax+0x2]                   
	punpcklbw mm1,mm7                                
	punpcklbw mm2,mm7                                
	punpcklbw mm3,mm7                                
	punpcklbw mm0,mm7                                
	paddw  mm1,mm0                                   
	paddw  mm2,mm3                                   
	movd   mm0,DWORD PTR [eax-0x2]                   
	movd   mm3,DWORD PTR [eax+0x3]                   
	punpcklbw mm0,mm7                                
	punpcklbw mm3,mm7                                
	paddw  mm0,mm3                                   
	psllw  mm2,0x2                                   
	psubw  mm2,mm1                                   
	pmullw mm2,mm4                                   
	paddw  mm0,mm5                                   
	paddw  mm0,mm2                                   
	movd   mm3,DWORD PTR [edx]                       
	psraw  mm0,0x5                                   
	packuswb mm0,mm0                                 
	pavgusb mm0,mm3                                  
	movd   mm6,DWORD PTR [ecx]                       
	pavgusb mm0,mm6                                  
	movd   DWORD PTR [ecx],mm0                       
	add    eax,esi                                   
	add    ecx,esi                                   
	add    edx,edi                                   
	movd   mm1,DWORD PTR [eax-0x1]                   
	movd   mm2,DWORD PTR [eax]                       
	movd   mm3,DWORD PTR [eax+0x1]                   
	movd   mm0,DWORD PTR [eax+0x2]                   
	punpcklbw mm1,mm7                                
	punpcklbw mm2,mm7                                
	punpcklbw mm3,mm7                                
	punpcklbw mm0,mm7                                
	paddw  mm1,mm0                                   
	paddw  mm2,mm3                                   
	movd   mm0,DWORD PTR [eax-0x2]                   
	movd   mm3,DWORD PTR [eax+0x3]                   
	punpcklbw mm0,mm7                                
	punpcklbw mm3,mm7                                
	paddw  mm0,mm3                                   
	psllw  mm2,0x2                                   
	psubw  mm2,mm1                                   
	pmullw mm2,mm4                                   
	paddw  mm0,mm5                                   
	paddw  mm0,mm2                                   
	movd   mm3,DWORD PTR [edx]                       
	psraw  mm0,0x5                                   
	packuswb mm0,mm0                                 
	pavgusb mm0,mm3                                  
	movd   mm6,DWORD PTR [ecx]                       
	pavgusb mm0,mm6                                  
	movd   DWORD PTR [ecx],mm0                       
	add    eax,esi                                   
	add    ecx,esi                                   
	add    edx,edi                                   
	movd   mm1,DWORD PTR [eax-0x1]                   
	movd   mm2,DWORD PTR [eax]                       
	movd   mm3,DWORD PTR [eax+0x1]                   
	movd   mm0,DWORD PTR [eax+0x2]                   
	punpcklbw mm1,mm7                                
	punpcklbw mm2,mm7                                
	punpcklbw mm3,mm7                                
	punpcklbw mm0,mm7                                
	paddw  mm1,mm0                                   
	paddw  mm2,mm3                                   
	movd   mm0,DWORD PTR [eax-0x2]                   
	movd   mm3,DWORD PTR [eax+0x3]                   
	punpcklbw mm0,mm7                                
	punpcklbw mm3,mm7                                
	paddw  mm0,mm3                                   
	psllw  mm2,0x2                                   
	psubw  mm2,mm1                                   
	pmullw mm2,mm4                                   
	paddw  mm0,mm5                                   
	paddw  mm0,mm2                                   
	movd   mm3,DWORD PTR [edx]                       
	psraw  mm0,0x5                                   
	packuswb mm0,mm0                                 
	pavgusb mm0,mm3                                  
	movd   mm6,DWORD PTR [ecx]                       
	pavgusb mm0,mm6                                  
	movd   DWORD PTR [ecx],mm0                       
	add    eax,esi                                   
	add    ecx,esi                                   
	add    edx,edi                                   
	mov    esi,DWORD PTR [esp]                       
	mov    edi,DWORD PTR [esp+0x4]                   
	add    esp,0x8                                   
	ret                                              
	}
}
void __declspec(naked) avg_h264_qpel4_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                               
	mov    DWORD PTR [esp],esi                   
	mov    esi,DWORD PTR [esp+0x18]              
	mov    DWORD PTR [esp+0x4],edi               
	mov    ecx,DWORD PTR [esp+0xc]               
	mov    edi,DWORD PTR [esp+0x14]              
	lea    eax,[esi+esi*1]                       
	neg    eax                                   
	add    eax,DWORD PTR [esp+0x10]              
	pxor   mm7,mm7                               
	movd   mm0,DWORD PTR [eax]                   
	add    eax,esi                               
	movd   mm1,DWORD PTR [eax]                   
	add    eax,esi                               
	movd   mm2,DWORD PTR [eax]                   
	add    eax,esi                               
	movd   mm3,DWORD PTR [eax]                   
	add    eax,esi                               
	movd   mm4,DWORD PTR [eax]                   
	add    eax,esi                               
	punpcklbw mm0,mm7                            
	punpcklbw mm1,mm7                            
	punpcklbw mm2,mm7                            
	punpcklbw mm3,mm7                            
	punpcklbw mm4,mm7                            
	movq   mm6,mm2                               
	movd   mm5,DWORD PTR [eax]                   
	paddw  mm6,mm3                               
	psllw  mm6,0x2                               
	psubw  mm6,mm1                               
	psubw  mm6,mm4                               
	punpcklbw mm5,mm7                            
	pmullw mm6,QWORD PTR [ff_pw_5]                  
	paddw  mm0,QWORD PTR [ff_pw_16]                  
	add    eax,esi                               
	paddw  mm0,mm5                               
	paddw  mm6,mm0                               
	psraw  mm6,0x5                               
	packuswb mm6,mm6                             
	movd   mm0,DWORD PTR [ecx]                   
	pavgusb mm6,mm0                              
	movd   DWORD PTR [ecx],mm6                   
	add    ecx,edi                               
	movq   mm6,mm3                               
	movd   mm0,DWORD PTR [eax]                   
	paddw  mm6,mm4                               
	psllw  mm6,0x2                               
	psubw  mm6,mm2                               
	psubw  mm6,mm5                               
	punpcklbw mm0,mm7                            
	pmullw mm6,QWORD PTR [ff_pw_5]                  
	paddw  mm1,QWORD PTR [ff_pw_16]                  
	add    eax,esi                               
	paddw  mm1,mm0                               
	paddw  mm6,mm1                               
	psraw  mm6,0x5                               
	packuswb mm6,mm6                             
	movd   mm1,DWORD PTR [ecx]                   
	pavgusb mm6,mm1                              
	movd   DWORD PTR [ecx],mm6                   
	add    ecx,edi                               
	movq   mm6,mm4                               
	movd   mm1,DWORD PTR [eax]                   
	paddw  mm6,mm5                               
	psllw  mm6,0x2                               
	psubw  mm6,mm3                               
	psubw  mm6,mm0                               
	punpcklbw mm1,mm7                            
	pmullw mm6,QWORD PTR [ff_pw_5]                  
	paddw  mm2,QWORD PTR [ff_pw_16]                  
	add    eax,esi                               
	paddw  mm2,mm1                               
	paddw  mm6,mm2                               
	psraw  mm6,0x5                               
	packuswb mm6,mm6                             
	movd   mm2,DWORD PTR [ecx]                   
	pavgusb mm6,mm2                              
	movd   DWORD PTR [ecx],mm6                   
	add    ecx,edi                               
	movq   mm6,mm5                               
	movd   mm2,DWORD PTR [eax]                   
	paddw  mm6,mm0                               
	psllw  mm6,0x2                               
	psubw  mm6,mm4                               
	psubw  mm6,mm1                               
	punpcklbw mm2,mm7                            
	pmullw mm6,QWORD PTR [ff_pw_5]                  
	paddw  mm3,QWORD PTR [ff_pw_16]                  
	add    eax,esi                               
	paddw  mm3,mm2                               
	paddw  mm6,mm3                               
	psraw  mm6,0x5                               
	packuswb mm6,mm6                             
	movd   mm3,DWORD PTR [ecx]                   
	pavgusb mm6,mm3                              
	movd   DWORD PTR [ecx],mm6                   
	add    ecx,edi                               
	mov    esi,DWORD PTR [esp]                   
	mov    edi,DWORD PTR [esp+0x4]               
	add    esp,0x8                               
	ret                                          
	}
}
void __declspec(naked) avg_h264_qpel4_hv_lowpass_3dnow(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	__asm{
	sub    esp,0xc                                       
	mov    DWORD PTR [esp+0x4],esi                       
	mov    esi,DWORD PTR [esp+0x24]                      
	mov    edx,DWORD PTR [esp+0x14]                      
	mov    DWORD PTR [esp],ebx                           
	mov    DWORD PTR [esp+0x8],edi                       
	mov    edi,DWORD PTR [esp+0x10]                      
	mov    eax,esi                                       
	lea    ebx,[esi+esi*8]                               
	not    eax                                           
	neg    ebx                                           
	add    eax,eax                                       
	add    ebx,0x4                                       
	mov    ecx,edx                                       
	add    eax,DWORD PTR [esp+0x18]                      
	pxor   mm7,mm7                                       
	movd   mm0,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm1,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm2,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm3,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm4,DWORD PTR [eax]                           
	add    eax,esi                                       
	punpcklbw mm0,mm7                                    
	punpcklbw mm1,mm7                                    
	punpcklbw mm2,mm7                                    
	punpcklbw mm3,mm7                                    
	punpcklbw mm4,mm7                                    
	movq   mm6,mm2                                       
	movd   mm5,DWORD PTR [eax]                           
	paddw  mm6,mm3                                       
	psllw  mm6,0x2                                       
	paddw  mm0,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm1                                       
	psubw  mm6,mm4                                       
	punpcklbw mm5,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm0,mm5                                       
	add    eax,esi                                       
	paddw  mm6,mm0                                       
	movq   QWORD PTR [ecx],mm6                           
	movq   mm6,mm3                                       
	movd   mm0,DWORD PTR [eax]                           
	paddw  mm6,mm4                                       
	psllw  mm6,0x2                                       
	paddw  mm1,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm2                                       
	psubw  mm6,mm5                                       
	punpcklbw mm0,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm1,mm0                                       
	add    eax,esi                                       
	paddw  mm6,mm1                                       
	movq   QWORD PTR [ecx+0x18],mm6                      
	movq   mm6,mm4                                       
	movd   mm1,DWORD PTR [eax]                           
	paddw  mm6,mm5                                       
	psllw  mm6,0x2                                       
	paddw  mm2,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm3                                       
	psubw  mm6,mm0                                       
	punpcklbw mm1,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm2,mm1                                       
	add    eax,esi                                       
	paddw  mm6,mm2                                       
	movq   QWORD PTR [ecx+0x30],mm6                      
	movq   mm6,mm5                                       
	movd   mm2,DWORD PTR [eax]                           
	paddw  mm6,mm0                                       
	psllw  mm6,0x2                                       
	paddw  mm3,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm4                                       
	psubw  mm6,mm1                                       
	punpcklbw mm2,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm3,mm2                                       
	add    eax,esi                                       
	paddw  mm6,mm3                                       
	movq   QWORD PTR [ecx+0x48],mm6                      
	lea    ecx,[edx+0x8]                                 
	add    eax,ebx                                       
	pxor   mm7,mm7                                       
	movd   mm0,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm1,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm2,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm3,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm4,DWORD PTR [eax]                           
	add    eax,esi                                       
	punpcklbw mm0,mm7                                    
	punpcklbw mm1,mm7                                    
	punpcklbw mm2,mm7                                    
	punpcklbw mm3,mm7                                    
	punpcklbw mm4,mm7                                    
	movq   mm6,mm2                                       
	movd   mm5,DWORD PTR [eax]                           
	paddw  mm6,mm3                                       
	psllw  mm6,0x2                                       
	paddw  mm0,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm1                                       
	psubw  mm6,mm4                                       
	punpcklbw mm5,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm0,mm5                                       
	add    eax,esi                                       
	paddw  mm6,mm0                                       
	movq   QWORD PTR [ecx],mm6                           
	movq   mm6,mm3                                       
	movd   mm0,DWORD PTR [eax]                           
	paddw  mm6,mm4                                       
	psllw  mm6,0x2                                       
	paddw  mm1,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm2                                       
	psubw  mm6,mm5                                       
	punpcklbw mm0,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm1,mm0                                       
	add    eax,esi                                       
	paddw  mm6,mm1                                       
	movq   QWORD PTR [ecx+0x18],mm6                      
	movq   mm6,mm4                                       
	movd   mm1,DWORD PTR [eax]                           
	paddw  mm6,mm5                                       
	psllw  mm6,0x2                                       
	paddw  mm2,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm3                                       
	psubw  mm6,mm0                                       
	punpcklbw mm1,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm2,mm1                                       
	add    eax,esi                                       
	paddw  mm6,mm2                                       
	movq   QWORD PTR [ecx+0x30],mm6                      
	movq   mm6,mm5                                       
	movd   mm2,DWORD PTR [eax]                           
	paddw  mm6,mm0                                       
	psllw  mm6,0x2                                       
	paddw  mm3,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm4                                       
	psubw  mm6,mm1                                       
	punpcklbw mm2,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm3,mm2                                       
	add    eax,esi                                       
	paddw  mm6,mm3                                       
	movq   QWORD PTR [ecx+0x48],mm6                      
	add    eax,ebx                                       
	lea    ecx,[edx+0x10]                                
	pxor   mm7,mm7                                       
	movd   mm0,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm1,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm2,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm3,DWORD PTR [eax]                           
	add    eax,esi                                       
	movd   mm4,DWORD PTR [eax]                           
	add    eax,esi                                       
	punpcklbw mm0,mm7                                    
	punpcklbw mm1,mm7                                    
	punpcklbw mm2,mm7                                    
	punpcklbw mm3,mm7                                    
	punpcklbw mm4,mm7                                    
	movq   mm6,mm2                                       
	movd   mm5,DWORD PTR [eax]                           
	paddw  mm6,mm3                                       
	psllw  mm6,0x2                                       
	paddw  mm0,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm1                                       
	psubw  mm6,mm4                                       
	punpcklbw mm5,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm0,mm5                                       
	add    eax,esi                                       
	paddw  mm6,mm0                                       
	movq   QWORD PTR [ecx],mm6                           
	movq   mm6,mm3                                       
	movd   mm0,DWORD PTR [eax]                           
	paddw  mm6,mm4                                       
	psllw  mm6,0x2                                       
	paddw  mm1,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm2                                       
	psubw  mm6,mm5                                       
	punpcklbw mm0,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm1,mm0                                       
	add    eax,esi                                       
	paddw  mm6,mm1                                       
	movq   QWORD PTR [ecx+0x18],mm6                      
	movq   mm6,mm4                                       
	movd   mm1,DWORD PTR [eax]                           
	paddw  mm6,mm5                                       
	psllw  mm6,0x2                                       
	paddw  mm2,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm3                                       
	psubw  mm6,mm0                                       
	punpcklbw mm1,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm2,mm1                                       
	add    eax,esi                                       
	paddw  mm6,mm2                                       
	movq   QWORD PTR [ecx+0x30],mm6                      
	movq   mm6,mm5                                       
	movd   mm2,DWORD PTR [eax]                           
	paddw  mm6,mm0                                       
	psllw  mm6,0x2                                       
	paddw  mm3,QWORD PTR [ff_pw_16]                          
	psubw  mm6,mm4                                       
	psubw  mm6,mm1                                       
	punpcklbw mm2,mm7                                    
	pmullw mm6,QWORD PTR [ff_pw_5]                          
	paddw  mm3,mm2                                       
	add    eax,esi                                       
	paddw  mm6,mm3                                       
	movq   QWORD PTR [ecx+0x48],mm6                      
	mov    eax,edx                                       
	mov    esi,DWORD PTR [esp+0x1c]                      
	mov    ecx,edi                                       
	mov    edx,0x4                                       
avg_h264_qpel4_hv_lowpass_3dnowflag:                  
	movq   mm0,QWORD PTR [eax]                           
	paddw  mm0,QWORD PTR [eax+0xa]                       
	movq   mm1,QWORD PTR [eax+0x2]                       
	paddw  mm1,QWORD PTR [eax+0x8]                       
	movq   mm2,QWORD PTR [eax+0x4]                       
	paddw  mm2,QWORD PTR [eax+0x6]                       
	psubw  mm0,mm1                                       
	psraw  mm0,0x2                                       
	psubw  mm0,mm1                                       
	paddsw mm0,mm2                                       
	psraw  mm0,0x2                                       
	paddw  mm0,mm2                                       
	psraw  mm0,0x6                                       
	packuswb mm0,mm0                                     
	movd   mm7,DWORD PTR [ecx]                           
	pavgusb mm0,mm7                                      
	movd   DWORD PTR [ecx],mm0                           
	add    eax,0x18                                      
	add    ecx,esi                                       
	dec    edx                                           
	jne    avg_h264_qpel4_hv_lowpass_3dnowflag           
	mov    ebx,DWORD PTR [esp]                           
	mov    esi,DWORD PTR [esp+0x4]                       
	mov    edi,DWORD PTR [esp+0x8]                       
	add    esp,0xc                                       
	ret                                                  
	}
}
void __declspec(naked) avg_h264_qpel8_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                               
	mov    DWORD PTR [esp],ebx                   
	mov    ecx,DWORD PTR [esp+0xc]               
	mov    ebx,0x8                               
	mov    DWORD PTR [esp+0x4],esi               
	mov    eax,DWORD PTR [esp+0x10]              
	mov    edx,DWORD PTR [esp+0x18]              
	mov    esi,DWORD PTR [esp+0x14]              
	pxor   mm7,mm7                               
	movq   mm6,QWORD PTR [ff_pw_5]                  
avg_h264_qpel8_h_lowpass_3dnowflag:           
	movq   mm0,QWORD PTR [eax]                   
	movq   mm2,QWORD PTR [eax+0x1]               
	movq   mm1,mm0                               
	movq   mm3,mm2                               
	punpcklbw mm0,mm7                            
	punpckhbw mm1,mm7                            
	punpcklbw mm2,mm7                            
	punpckhbw mm3,mm7                            
	paddw  mm0,mm2                               
	paddw  mm1,mm3                               
	psllw  mm0,0x2                               
	psllw  mm1,0x2                               
	movq   mm2,QWORD PTR [eax-0x1]               
	movq   mm4,QWORD PTR [eax+0x2]               
	movq   mm3,mm2                               
	movq   mm5,mm4                               
	punpcklbw mm2,mm7                            
	punpckhbw mm3,mm7                            
	punpcklbw mm4,mm7                            
	punpckhbw mm5,mm7                            
	paddw  mm2,mm4                               
	paddw  mm5,mm3                               
	psubw  mm0,mm2                               
	psubw  mm1,mm5                               
	pmullw mm0,mm6                               
	pmullw mm1,mm6                               
	movd   mm2,DWORD PTR [eax-0x2]               
	movd   mm5,DWORD PTR [eax+0x7]               
	punpcklbw mm2,mm7                            
	punpcklbw mm5,mm7                            
	paddw  mm2,mm3                               
	paddw  mm4,mm5                               
	movq   mm5,QWORD PTR [ff_pw_16]                 
	paddw  mm2,mm5                               
	paddw  mm4,mm5                               
	paddw  mm0,mm2                               
	paddw  mm1,mm4                               
	psraw  mm0,0x5                               
	psraw  mm1,0x5                               
	packuswb mm0,mm1                             
	movq   mm5,QWORD PTR [ecx]                   
	pavgusb mm0,mm5                              
	movq   QWORD PTR [ecx],mm0                   
	add    eax,edx                               
	add    ecx,esi                               
	dec    ebx                                   
	jne    avg_h264_qpel8_h_lowpass_3dnowflag    
	mov    ebx,DWORD PTR [esp]                   
	mov    esi,DWORD PTR [esp+0x4]               
	add    esp,0x8                               
	ret                                          
	}
}
void avg_h264_qpel16_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	avg_h264_qpel8_h_lowpass_3dnow(dst , src , dstStride, srcStride); 
	avg_h264_qpel8_h_lowpass_3dnow(dst+8, src+8, dstStride, srcStride); 
	src += 8*srcStride;
	dst += 8*dstStride; 
	avg_h264_qpel8_h_lowpass_3dnow(dst , src , dstStride, srcStride); 
	avg_h264_qpel8_h_lowpass_3dnow(dst+8, src+8, dstStride, srcStride);
}
void __declspec(naked) avg_h264_qpel8_h_lowpass_l2_3dnow(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0xc                               
	mov    DWORD PTR [esp],ebx                   
	mov    ecx,DWORD PTR [esp+0x10]              
	mov    ebx,0x8                               
	mov    DWORD PTR [esp+0x4],esi               
	mov    eax,DWORD PTR [esp+0x14]              
	mov    DWORD PTR [esp+0x8],edi               
	mov    edx,DWORD PTR [esp+0x18]              
	mov    edi,DWORD PTR [esp+0x20]              
	mov    esi,DWORD PTR [esp+0x1c]              
	pxor   mm7,mm7                               
	movq   mm6,QWORD PTR [ff_pw_5]                 
avg_h264_qpel8_h_lowpass_l2_3dnowflag:        
	movq   mm0,QWORD PTR [eax]                   
	movq   mm2,QWORD PTR [eax+0x1]               
	movq   mm1,mm0                               
	movq   mm3,mm2                               
	punpcklbw mm0,mm7                            
	punpckhbw mm1,mm7                            
	punpcklbw mm2,mm7                            
	punpckhbw mm3,mm7                            
	paddw  mm0,mm2                               
	paddw  mm1,mm3                               
	psllw  mm0,0x2                               
	psllw  mm1,0x2                               
	movq   mm2,QWORD PTR [eax-0x1]               
	movq   mm4,QWORD PTR [eax+0x2]               
	movq   mm3,mm2                               
	movq   mm5,mm4                               
	punpcklbw mm2,mm7                            
	punpckhbw mm3,mm7                            
	punpcklbw mm4,mm7                            
	punpckhbw mm5,mm7                            
	paddw  mm2,mm4                               
	paddw  mm5,mm3                               
	psubw  mm0,mm2                               
	psubw  mm1,mm5                               
	pmullw mm0,mm6                               
	pmullw mm1,mm6                               
	movd   mm2,DWORD PTR [eax-0x2]               
	movd   mm5,DWORD PTR [eax+0x7]               
	punpcklbw mm2,mm7                            
	punpcklbw mm5,mm7                            
	paddw  mm2,mm3                               
	paddw  mm4,mm5                               
	movq   mm5,QWORD PTR [ff_pw_16]                  
	paddw  mm2,mm5                               
	paddw  mm4,mm5                               
	paddw  mm0,mm2                               
	paddw  mm1,mm4                               
	psraw  mm0,0x5                               
	psraw  mm1,0x5                               
	movq   mm4,QWORD PTR [edx]                   
	packuswb mm0,mm1                             
	pavgusb mm0,mm4                              
	movq   mm5,QWORD PTR [ecx]                   
	pavgusb mm0,mm5                              
	movq   QWORD PTR [ecx],mm0                   
	add    eax,esi                               
	add    ecx,esi                               
	add    edx,edi                               
	dec    ebx                                   
	jg     avg_h264_qpel8_h_lowpass_l2_3dnowflag 
	mov    ebx,DWORD PTR [esp]                   
	mov    esi,DWORD PTR [esp+0x4]               
	mov    edi,DWORD PTR [esp+0x8]               
	add    esp,0xc                               
	ret
	}
}
void __declspec(naked) avg_h264_qpel8or16_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
	__asm{
	sub    esp,0x10                                                     
	mov    edx,0xfffffffb                                               
	mov    DWORD PTR [esp],ebx                                          
	mov    ebx,DWORD PTR [esp+0x24]                                     
	mov    DWORD PTR [esp+0x4],esi                                      
	mov    esi,DWORD PTR [esp+0x20]                                     
	mov    DWORD PTR [esp+0x8],edi                                      
	mov    edi,DWORD PTR [esp+0x1c]                                     
	mov    DWORD PTR [esp+0xc],ebp                                      
	mov    ecx,DWORD PTR [esp+0x14]                                     
	sub    edx,ebx                                                      
	mov    ebp,ebx                                                      
	lea    eax,[esi+esi*1]                                              
	neg    eax                                                          
	imul   edx,esi                                                      
	add    eax,DWORD PTR [esp+0x18]                                     
	imul   ebp,edi                                                      
	pxor   mm7,mm7                                                      
	movd   mm0,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm1,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm2,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm3,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm4,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	punpcklbw mm0,mm7                                                   
	punpcklbw mm1,mm7                                                   
	punpcklbw mm2,mm7                                                   
	punpcklbw mm3,mm7                                                   
	punpcklbw mm4,mm7                                                   
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm0,DWORD PTR [ecx]                                          
	pavgusb mm6,mm0                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm1,DWORD PTR [ecx]                                          
	pavgusb mm6,mm1                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm2,DWORD PTR [ecx]                                          
	pavgusb mm6,mm2                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm3,DWORD PTR [ecx]                                          
	pavgusb mm6,mm3                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm4,mm3                                                      
	paddw  mm6,mm4                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm4,DWORD PTR [ecx]                                          
	pavgusb mm6,mm4                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm5,mm4                                                      
	paddw  mm6,mm5                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm5,DWORD PTR [ecx]                                          
	pavgusb mm6,mm5                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm0,DWORD PTR [ecx]                                          
	pavgusb mm6,mm0                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm1,DWORD PTR [ecx]                                          
	pavgusb mm6,mm1                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	cmp    ebx,0x10                                                     
	jne    avg_h264_qpel8or16_v_lowpass_3dnow_42d7e                     
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm2,DWORD PTR [ecx]                                          
	pavgusb mm6,mm2                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm3,DWORD PTR [ecx]                                          
	pavgusb mm6,mm3                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm4,mm3                                                      
	paddw  mm6,mm4                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm4,DWORD PTR [ecx]                                          
	pavgusb mm6,mm4                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm5,mm4                                                      
	paddw  mm6,mm5                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm5,DWORD PTR [ecx]                                          
	pavgusb mm6,mm5                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm0,DWORD PTR [ecx]                                          
	pavgusb mm6,mm0                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm1,DWORD PTR [ecx]                                          
	pavgusb mm6,mm1                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm2,DWORD PTR [ecx]                                          
	pavgusb mm6,mm2                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm3,DWORD PTR [ecx]                                          
	pavgusb mm6,mm3                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
avg_h264_qpel8or16_v_lowpass_3dnow_42d7e:                            
	sub    ecx,ebp                                                      
	lea    eax,[eax+edx*1+0x4]                                          
	add    ecx,0x4                                                      
	pxor   mm7,mm7                                                      
	movd   mm0,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm1,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm2,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm3,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm4,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	punpcklbw mm0,mm7                                                   
	punpcklbw mm1,mm7                                                   
	punpcklbw mm2,mm7                                                   
	punpcklbw mm3,mm7                                                   
	punpcklbw mm4,mm7                                                   
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm0,DWORD PTR [ecx]                                          
	pavgusb mm6,mm0                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm1,DWORD PTR [ecx]                                          
	pavgusb mm6,mm1                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm2,DWORD PTR [ecx]                                          
	pavgusb mm6,mm2                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm3,DWORD PTR [ecx]                                          
	pavgusb mm6,mm3                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm4,mm3                                                      
	paddw  mm6,mm4                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm4,DWORD PTR [ecx]                                          
	pavgusb mm6,mm4                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm5,mm4                                                      
	paddw  mm6,mm5                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm5,DWORD PTR [ecx]                                          
	pavgusb mm6,mm5                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm0,DWORD PTR [ecx]                                          
	pavgusb mm6,mm0                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm1,DWORD PTR [ecx]                                          
	pavgusb mm6,mm1                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	cmp    ebx,0x10                                                     
	jne    avg_h264_qpel8or16_v_lowpass_3dnow_431ab                     
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm2,DWORD PTR [ecx]                                          
	pavgusb mm6,mm2                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm3,DWORD PTR [ecx]                                          
	pavgusb mm6,mm3                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm4,mm3                                                      
	paddw  mm6,mm4                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm4,DWORD PTR [ecx]                                          
	pavgusb mm6,mm4                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm5,mm4                                                      
	paddw  mm6,mm5                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm5,DWORD PTR [ecx]                                          
	pavgusb mm6,mm5                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm0,mm5                                                      
	paddw  mm6,mm0                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm0,DWORD PTR [ecx]                                          
	pavgusb mm6,mm0                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm1,mm0                                                      
	paddw  mm6,mm1                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm1,DWORD PTR [ecx]                                          
	pavgusb mm6,mm1                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm2,mm1                                                      
	paddw  mm6,mm2                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm2,DWORD PTR [ecx]                                          
	pavgusb mm6,mm2                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,QWORD PTR [ff_pw_16]                                         
	add    eax,esi                                                      
	paddw  mm3,mm2                                                      
	paddw  mm6,mm3                                                      
	psraw  mm6,0x5                                                      
	packuswb mm6,mm6                                                    
	movd   mm3,DWORD PTR [ecx]                                          
	pavgusb mm6,mm3                                                     
	movd   DWORD PTR [ecx],mm6                                          
	add    ecx,edi                                                      
avg_h264_qpel8or16_v_lowpass_3dnow_431ab:	                          
	mov    ebx,DWORD PTR [esp]                                          
	mov    esi,DWORD PTR [esp+0x4]                                      
	mov    edi,DWORD PTR [esp+0x8]                                      
	mov    ebp,DWORD PTR [esp+0xc]                                      
	add    esp,0x10                                                     
	ret                                                                 
	}
}
void avg_h264_qpel8_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	avg_h264_qpel8or16_v_lowpass_3dnow(dst , src , dstStride, srcStride, 8);
}
void avg_h264_qpel16_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	avg_h264_qpel8or16_v_lowpass_3dnow(dst , src , dstStride, srcStride, 16);
	avg_h264_qpel8or16_v_lowpass_3dnow(dst+8, src+8, dstStride, srcStride, 16);
}
void avg_h264_qpel16_h_lowpass_l2_3dnow(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{ 
	avg_h264_qpel8_h_lowpass_l2_3dnow(dst , src , src2 , dstStride, src2Stride); 
	avg_h264_qpel8_h_lowpass_l2_3dnow(dst+8, src+8, src2+8, dstStride, src2Stride); 
	src += 8*dstStride; 
	dst += 8*dstStride; 
	src2 += 8*src2Stride; 
	avg_h264_qpel8_h_lowpass_l2_3dnow(dst , src , src2 , dstStride, src2Stride); 
	avg_h264_qpel8_h_lowpass_l2_3dnow(dst+8, src+8, src2+8, dstStride, src2Stride);
}
void __declspec(naked) avg_h264_qpel8or16_hv_lowpass_3dnow(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride, int size)
{
	__asm{
	push   ebp                                                            
	push   edi                                                            
	push   esi                                                            
	push   ebx                                                            
	sub    esp,0x8                                                        
	mov    edi,DWORD PTR [esp+0x34]                                       
	mov    ebp,DWORD PTR [esp+0x20]                                       
	mov    esi,DWORD PTR [esp+0x30]                                       
	lea    ebx,[edi+0x8]                                                  
	sar    ebx,0x2                                                        
	test   ebx,ebx                                                        
	je     avg_h264_qpel8or16_hv_lowpass_3dnow_459f6                      
	mov    eax,DWORD PTR [esp+0x24]                                       
	mov    edx,esi                                                        
	mov    ecx,ebp                                                        
	not    edx                                                            
	mov    DWORD PTR [esp+0x4],ebp                                        
	lea    eax,[eax+edx*2]                                                
	mov    edx,0xfffffffb                                                 
	sub    edx,edi                                                        
	imul   edx,esi                                                        
	add    edx,0x4                                                        
	mov    DWORD PTR [esp],edx                                            
	mov    ebp,DWORD PTR [esp]                                            
	xor    edx,edx                                                        
	nop                                                                   
avg_h264_qpel8or16_hv_lowpass_3dnow_45688:                             
	pxor   mm7,mm7                                                        
	movd   mm0,DWORD PTR [eax]                                            
	add    eax,esi                                                        
	movd   mm1,DWORD PTR [eax]                                            
	add    eax,esi                                                        
	movd   mm2,DWORD PTR [eax]                                            
	add    eax,esi                                                        
	movd   mm3,DWORD PTR [eax]                                            
	add    eax,esi                                                        
	movd   mm4,DWORD PTR [eax]                                            
	add    eax,esi                                                        
	punpcklbw mm0,mm7                                                     
	punpcklbw mm1,mm7                                                     
	punpcklbw mm2,mm7                                                     
	punpcklbw mm3,mm7                                                     
	punpcklbw mm4,mm7                                                     
	movq   mm6,mm2                                                        
	movd   mm5,DWORD PTR [eax]                                            
	paddw  mm6,mm3                                                        
	psllw  mm6,0x2                                                        
	paddw  mm0,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm1                                                        
	psubw  mm6,mm4                                                        
	punpcklbw mm5,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm0,mm5                                                        
	add    eax,esi                                                        
	paddw  mm6,mm0                                                        
	movq   QWORD PTR [ecx],mm6                                            
	movq   mm6,mm3                                                        
	movd   mm0,DWORD PTR [eax]                                            
	paddw  mm6,mm4                                                        
	psllw  mm6,0x2                                                        
	paddw  mm1,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm2                                                        
	psubw  mm6,mm5                                                        
	punpcklbw mm0,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm1,mm0                                                        
	add    eax,esi                                                        
	paddw  mm6,mm1                                                        
	movq   QWORD PTR [ecx+0x30],mm6                                       
	movq   mm6,mm4                                                        
	movd   mm1,DWORD PTR [eax]                                            
	paddw  mm6,mm5                                                        
	psllw  mm6,0x2                                                        
	paddw  mm2,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm3                                                        
	psubw  mm6,mm0                                                        
	punpcklbw mm1,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm2,mm1                                                        
	add    eax,esi                                                        
	paddw  mm6,mm2                                                        
	movq   QWORD PTR [ecx+0x60],mm6                                       
	movq   mm6,mm5                                                        
	movd   mm2,DWORD PTR [eax]                                            
	paddw  mm6,mm0                                                        
	psllw  mm6,0x2                                                        
	paddw  mm3,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm4                                                        
	psubw  mm6,mm1                                                        
	punpcklbw mm2,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm3,mm2                                                        
	add    eax,esi                                                        
	paddw  mm6,mm3                                                        
	movq   QWORD PTR [ecx+0x90],mm6                                       
	movq   mm6,mm0                                                        
	movd   mm3,DWORD PTR [eax]                                            
	paddw  mm6,mm1                                                        
	psllw  mm6,0x2                                                        
	paddw  mm4,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm5                                                        
	psubw  mm6,mm2                                                        
	punpcklbw mm3,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm4,mm3                                                        
	add    eax,esi                                                        
	paddw  mm6,mm4                                                        
	movq   QWORD PTR [ecx+0xc0],mm6                                       
	movq   mm6,mm1                                                        
	movd   mm4,DWORD PTR [eax]                                            
	paddw  mm6,mm2                                                        
	psllw  mm6,0x2                                                        
	paddw  mm5,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm0                                                        
	psubw  mm6,mm3                                                        
	punpcklbw mm4,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm5,mm4                                                        
	add    eax,esi                                                        
	paddw  mm6,mm5                                                        
	movq   QWORD PTR [ecx+0xf0],mm6                                       
	movq   mm6,mm2                                                        
	movd   mm5,DWORD PTR [eax]                                            
	paddw  mm6,mm3                                                        
	psllw  mm6,0x2                                                        
	paddw  mm0,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm1                                                        
	psubw  mm6,mm4                                                        
	punpcklbw mm5,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm0,mm5                                                        
	add    eax,esi                                                        
	paddw  mm6,mm0                                                        
	movq   QWORD PTR [ecx+0x120],mm6                                      
	movq   mm6,mm3                                                        
	movd   mm0,DWORD PTR [eax]                                            
	paddw  mm6,mm4                                                        
	psllw  mm6,0x2                                                        
	paddw  mm1,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm2                                                        
	psubw  mm6,mm5                                                        
	punpcklbw mm0,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm1,mm0                                                        
	add    eax,esi                                                        
	paddw  mm6,mm1                                                        
	movq   QWORD PTR [ecx+0x150],mm6                                      
	cmp    edi,0x10                                                       
	jne    avg_h264_qpel8or16_hv_lowpass_3dnow_459e2                      
	movq   mm6,mm4                                                        
	movd   mm1,DWORD PTR [eax]                                            
	paddw  mm6,mm5                                                        
	psllw  mm6,0x2                                                        
	paddw  mm2,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm3                                                        
	psubw  mm6,mm0                                                        
	punpcklbw mm1,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm2,mm1                                                        
	add    eax,esi                                                        
	paddw  mm6,mm2                                                        
	movq   QWORD PTR [ecx+0x180],mm6                                      
	movq   mm6,mm5                                                        
	movd   mm2,DWORD PTR [eax]                                            
	paddw  mm6,mm0                                                        
	psllw  mm6,0x2                                                        
	paddw  mm3,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm4                                                        
	psubw  mm6,mm1                                                        
	punpcklbw mm2,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm3,mm2                                                        
	add    eax,esi                                                        
	paddw  mm6,mm3                                                        
	movq   QWORD PTR [ecx+0x1b0],mm6                                      
	movq   mm6,mm0                                                        
	movd   mm3,DWORD PTR [eax]                                            
	paddw  mm6,mm1                                                        
	psllw  mm6,0x2                                                        
	paddw  mm4,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm5                                                        
	psubw  mm6,mm2                                                        
	punpcklbw mm3,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm4,mm3                                                        
	add    eax,esi                                                        
	paddw  mm6,mm4                                                        
	movq   QWORD PTR [ecx+0x1e0],mm6                                      
	movq   mm6,mm1                                                        
	movd   mm4,DWORD PTR [eax]                                            
	paddw  mm6,mm2                                                        
	psllw  mm6,0x2                                                        
	paddw  mm5,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm0                                                        
	psubw  mm6,mm3                                                        
	punpcklbw mm4,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm5,mm4                                                        
	add    eax,esi                                                        
	paddw  mm6,mm5                                                        
	movq   QWORD PTR [ecx+0x210],mm6                                      
	movq   mm6,mm2                                                        
	movd   mm5,DWORD PTR [eax]                                            
	paddw  mm6,mm3                                                        
	psllw  mm6,0x2                                                        
	paddw  mm0,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm1                                                        
	psubw  mm6,mm4                                                        
	punpcklbw mm5,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm0,mm5                                                        
	add    eax,esi                                                        
	paddw  mm6,mm0                                                        
	movq   QWORD PTR [ecx+0x240],mm6                                      
	movq   mm6,mm3                                                        
	movd   mm0,DWORD PTR [eax]                                            
	paddw  mm6,mm4                                                        
	psllw  mm6,0x2                                                        
	paddw  mm1,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm2                                                        
	psubw  mm6,mm5                                                        
	punpcklbw mm0,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm1,mm0                                                        
	add    eax,esi                                                        
	paddw  mm6,mm1                                                        
	movq   QWORD PTR [ecx+0x270],mm6                                      
	movq   mm6,mm4                                                        
	movd   mm1,DWORD PTR [eax]                                            
	paddw  mm6,mm5                                                        
	psllw  mm6,0x2                                                        
	paddw  mm2,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm3                                                        
	psubw  mm6,mm0                                                        
	punpcklbw mm1,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm2,mm1                                                        
	add    eax,esi                                                        
	paddw  mm6,mm2                                                        
	movq   QWORD PTR [ecx+0x2a0],mm6                                      
	movq   mm6,mm5                                                        
	movd   mm2,DWORD PTR [eax]                                            
	paddw  mm6,mm0                                                        
	psllw  mm6,0x2                                                        
	paddw  mm3,QWORD PTR [ff_pw_16]                                           
	psubw  mm6,mm4                                                        
	psubw  mm6,mm1                                                        
	punpcklbw mm2,mm7                                                     
	pmullw mm6,QWORD PTR [ff_pw_5]                                           
	paddw  mm3,mm2                                                        
	add    eax,esi                                                        
	paddw  mm6,mm3                                                        
	movq   QWORD PTR [ecx+0x2d0],mm6                                      
avg_h264_qpel8or16_hv_lowpass_3dnow_459e2:                             
	add    edx,0x1                                                        
	add    ecx,0x8                                                        
	add    eax,ebp                                                        
	cmp    edx,ebx                                                        
	jne    avg_h264_qpel8or16_hv_lowpass_3dnow_45688                      
	mov    ebp,DWORD PTR [esp+0x4]                                        
avg_h264_qpel8or16_hv_lowpass_3dnow_459f6:                             
	lea    eax,[edi+edi*2]                                                
	mov    ecx,DWORD PTR [esp+0x1c]                                       
	mov    edx,0x8                                                        
	neg    eax                                                            
	mov    esi,DWORD PTR [esp+0x28]                                       
	mov    ebx,edi                                                        
	add    eax,0x1                                                        
	shl    eax,0x4                                                        
	mov    DWORD PTR [esp],eax                                            
	mov    eax,DWORD PTR [esp+0x28]                                       
	sar    ebx,0x4                                                        
	imul   eax,edi                                                        
	sub    edx,eax                                                        
	mov    eax,ebp                                                        
	mov    ebp,edx                                                        
	nop                                                                   
	lea    esi,[esi+0x0]                                            
avg_h264_qpel8or16_hv_lowpass_3dnow_45a28:	
	mov    edx,edi                                                        
avg_h264_qpel8or16_hv_lowpass_3dnow_45a2a:                             
	movq   mm0,QWORD PTR [eax]                                            
	movq   mm3,QWORD PTR [eax+0x8]                                        
	movq   mm1,QWORD PTR [eax+0x2]                                        
	movq   mm4,QWORD PTR [eax+0xa]                                        
	paddw  mm0,mm4                                                        
	paddw  mm1,mm3                                                        
	paddw  mm3,QWORD PTR [eax+0x12]                                       
	paddw  mm4,QWORD PTR [eax+0x10]                                       
	movq   mm2,QWORD PTR [eax+0x4]                                        
	movq   mm5,QWORD PTR [eax+0xc]                                        
	paddw  mm2,QWORD PTR [eax+0x6]                                        
	paddw  mm5,QWORD PTR [eax+0xe]                                        
	psubw  mm0,mm1                                                        
	psubw  mm3,mm4                                                        
	psraw  mm0,0x2                                                        
	psraw  mm3,0x2                                                        
	psubw  mm0,mm1                                                        
	psubw  mm3,mm4                                                        
	paddsw mm0,mm2                                                        
	paddsw mm3,mm5                                                        
	psraw  mm0,0x2                                                        
	psraw  mm3,0x2                                                        
	paddw  mm0,mm2                                                        
	paddw  mm3,mm5                                                        
	psraw  mm0,0x6                                                        
	psraw  mm3,0x6                                                        
	packuswb mm0,mm3                                                      
	movq   mm7,QWORD PTR [ecx]                                            
	pavgusb mm0,mm7                                                       
	movq   QWORD PTR [ecx],mm0                                            
	add    eax,0x30                                                       
	add    ecx,esi                                                        
	dec    edx                                                            
	jne    avg_h264_qpel8or16_hv_lowpass_3dnow_45a2a                      
	sub    ebx,0x1                                                        
	add    ecx,ebp                                                        
	add    eax,DWORD PTR [esp]                                            
	cmp    ebx,0xffffffff                                                 
	jne    avg_h264_qpel8or16_hv_lowpass_3dnow_45a28                      
	add    esp,0x8                                                        
	pop    ebx                                                            
	pop    esi                                                            
	pop    edi                                                            
	pop    ebp                                                            
	ret                                                                   
	}
}

void avg_h264_qpel8_hv_lowpass_3dnow(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{ 
	avg_h264_qpel8or16_hv_lowpass_3dnow(dst , tmp , src , dstStride, tmpStride, srcStride, 8);
}
void avg_h264_qpel16_hv_lowpass_3dnow(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	avg_h264_qpel8or16_hv_lowpass_3dnow(dst , tmp , src , dstStride, tmpStride, srcStride, 16);
}
void __declspec(naked) avg_pixels4_l2_shift5_3dnow(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
	__asm{
	sub    esp,0x8                         
	mov    DWORD PTR [esp],esi             
	mov    edx,DWORD PTR [esp+0xc]         
	mov    DWORD PTR [esp+0x4],edi         
	mov    ecx,DWORD PTR [esp+0x10]        
	mov    eax,DWORD PTR [esp+0x14]        
	mov    esi,DWORD PTR [esp+0x1c]        
	mov    edi,DWORD PTR [esp+0x18]        
	movq   mm0,QWORD PTR [ecx]             
	movq   mm1,QWORD PTR [ecx+0x18]        
	psraw  mm0,0x5                         
	psraw  mm1,0x5                         
	packuswb mm0,mm0                       
	packuswb mm1,mm1                       
	pavgusb mm0,QWORD PTR [eax]            
	pavgusb mm1,QWORD PTR [eax+esi*1]      
	movd   mm4,DWORD PTR [edx]             
	pavgusb mm0,mm4                        
	movd   DWORD PTR [edx],mm0             
	movd   mm5,DWORD PTR [edx+edi*1]       
	pavgusb mm1,mm5                        
	movd   DWORD PTR [edx+edi*1],mm1       
	lea    eax,[eax+esi*2]                 
	lea    edx,[edx+edi*2]                 
	movq   mm0,QWORD PTR [ecx+0x30]        
	movq   mm1,QWORD PTR [ecx+0x48]        
	psraw  mm0,0x5                         
	psraw  mm1,0x5                         
	packuswb mm0,mm0                       
	packuswb mm1,mm1                       
	pavgusb mm0,QWORD PTR [eax]            
	pavgusb mm1,QWORD PTR [eax+esi*1]      
	movd   mm4,DWORD PTR [edx]             
	pavgusb mm0,mm4                        
	movd   DWORD PTR [edx],mm0             
	movd   mm5,DWORD PTR [edx+edi*1]       
	pavgusb mm1,mm5                        
	movd   DWORD PTR [edx+edi*1],mm1       
	mov    esi,DWORD PTR [esp]             
	mov    edi,DWORD PTR [esp+0x4]         
	add    esp,0x8                         
	ret                                    
	}
}
void __declspec(naked) avg_pixels8_l2_shift5_3dnow(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
	__asm{
 	sub    esp,0x14                           
 	mov    DWORD PTR [esp+0xc],edi            
 	mov    edi,DWORD PTR [esp+0x24]           
 	mov    DWORD PTR [esp+0x8],esi            
 	mov    esi,DWORD PTR [esp+0x28]           
 	mov    DWORD PTR [esp+0x4],ebx            
 	mov    edx,DWORD PTR [esp+0x18]           
 	mov    ecx,DWORD PTR [esp+0x1c]           
 	lea    eax,[edi+edi*1]                    
 	mov    ebx,DWORD PTR [esp+0x2c]           
 	mov    DWORD PTR [esp],eax                
 	mov    eax,DWORD PTR [esp+0x20]           
 	mov    DWORD PTR [esp+0x10],ebp           
 	lea    ebp,[esi+esi*1]                    
 	lea    esi,[esi+0x0]                
 avg_pixels8_l2_shift5_3dnowflag:	          
 	movq   mm0,QWORD PTR [ecx]                
 	movq   mm1,QWORD PTR [ecx+0x8]            
 	movq   mm2,QWORD PTR [ecx+0x30]           
 	movq   mm3,QWORD PTR [ecx+0x38]           
 	psraw  mm0,0x5                            
 	psraw  mm1,0x5                            
 	psraw  mm2,0x5                            
 	psraw  mm3,0x5                            
 	packuswb mm0,mm1                          
 	packuswb mm2,mm3                          
 	pavgusb mm0,QWORD PTR [eax]               
 	pavgusb mm2,QWORD PTR [eax+esi*1]         
 	movq   mm5,QWORD PTR [edx]                
 	pavgusb mm0,mm5                           
 	movq   QWORD PTR [edx],mm0                
 	movq   mm5,QWORD PTR [edx+edi*1]          
 	pavgusb mm2,mm5                           
 	movq   QWORD PTR [edx+edi*1],mm2          
 	add    eax,ebp                            
 	add    ecx,0x60                           
 	add    edx,DWORD PTR [esp]                
 	sub    ebx,0x2                            
 	jne    avg_pixels8_l2_shift5_3dnowflag    
 	mov    ebx,DWORD PTR [esp+0x4]            
 	mov    esi,DWORD PTR [esp+0x8]            
 	mov    edi,DWORD PTR [esp+0xc]            
 	mov    ebp,DWORD PTR [esp+0x10]           
 	add    esp,0x14                           
 	ret                                       
	}
}

void __declspec(naked) avg_h264_qpel4_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{		
	sub    esp,0x8                           
	mov    DWORD PTR [esp],ebx               
	mov    ecx,DWORD PTR [esp+0xc]           
	mov    ebx,0x4                           
	mov    DWORD PTR [esp+0x4],esi           
	mov    eax,DWORD PTR [esp+0x10]          
	mov    edx,DWORD PTR [esp+0x18]          
	mov    esi,DWORD PTR [esp+0x14]          
	pxor   mm7,mm7                           
	movq   mm4,QWORD PTR [ff_pw_5]              
	movq   mm5,QWORD PTR [ff_pw_16]            
avg_h264_qpel4_h_lowpass_mmx2flag:        
	movd   mm1,DWORD PTR [eax-0x1]           
	movd   mm2,DWORD PTR [eax]               
	movd   mm3,DWORD PTR [eax+0x1]           
	movd   mm0,DWORD PTR [eax+0x2]           
	punpcklbw mm1,mm7                        
	punpcklbw mm2,mm7                        
	punpcklbw mm3,mm7                        
	punpcklbw mm0,mm7                        
	paddw  mm1,mm0                           
	paddw  mm2,mm3                           
	movd   mm0,DWORD PTR [eax-0x2]           
	movd   mm3,DWORD PTR [eax+0x3]           
	punpcklbw mm0,mm7                        
	punpcklbw mm3,mm7                        
	paddw  mm0,mm3                           
	psllw  mm2,0x2                           
	psubw  mm2,mm1                           
	pmullw mm2,mm4                           
	paddw  mm0,mm5                           
	paddw  mm0,mm2                           
	psraw  mm0,0x5                           
	packuswb mm0,mm0                         
	movd   mm6,DWORD PTR [ecx]               
	pavgb  mm0,mm6                           
	movd   DWORD PTR [ecx],mm0               
	add    eax,edx                           
	add    ecx,esi                           
	dec    ebx                               
	jne    avg_h264_qpel4_h_lowpass_mmx2flag 
	mov    ebx,DWORD PTR [esp]               
	mov    esi,DWORD PTR [esp+0x4]           
	add    esp,0x8                           
	ret                                      
	}
}
void __declspec(naked) avg_h264_qpel4_h_lowpass_l2_mmx2(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0x8                      
	mov    DWORD PTR [esp],esi          
	mov    ecx,DWORD PTR [esp+0xc]      
	mov    DWORD PTR [esp+0x4],edi      
	mov    eax,DWORD PTR [esp+0x10]     
	mov    edx,DWORD PTR [esp+0x14]     
	mov    esi,DWORD PTR [esp+0x18]     
	mov    edi,DWORD PTR [esp+0x1c]     
	pxor   mm7,mm7                      
	movq   mm4,QWORD PTR [ff_pw_5]         
	movq   mm5,QWORD PTR [ff_pw_16]        
	movd   mm1,DWORD PTR [eax-0x1]      
	movd   mm2,DWORD PTR [eax]          
	movd   mm3,DWORD PTR [eax+0x1]      
	movd   mm0,DWORD PTR [eax+0x2]      
	punpcklbw mm1,mm7                   
	punpcklbw mm2,mm7                   
	punpcklbw mm3,mm7                   
	punpcklbw mm0,mm7                   
	paddw  mm1,mm0                      
	paddw  mm2,mm3                      
	movd   mm0,DWORD PTR [eax-0x2]      
	movd   mm3,DWORD PTR [eax+0x3]      
	punpcklbw mm0,mm7                   
	punpcklbw mm3,mm7                   
	paddw  mm0,mm3                      
	psllw  mm2,0x2                      
	psubw  mm2,mm1                      
	pmullw mm2,mm4                      
	paddw  mm0,mm5                      
	paddw  mm0,mm2                      
	movd   mm3,DWORD PTR [edx]          
	psraw  mm0,0x5                      
	packuswb mm0,mm0                    
	pavgb  mm0,mm3                      
	movd   mm6,DWORD PTR [ecx]          
	pavgb  mm0,mm6                      
	movd   DWORD PTR [ecx],mm0          
	add    eax,esi                      
	add    ecx,esi                      
	add    edx,edi                      
	movd   mm1,DWORD PTR [eax-0x1]      
	movd   mm2,DWORD PTR [eax]          
	movd   mm3,DWORD PTR [eax+0x1]      
	movd   mm0,DWORD PTR [eax+0x2]      
	punpcklbw mm1,mm7                   
	punpcklbw mm2,mm7                   
	punpcklbw mm3,mm7                   
	punpcklbw mm0,mm7                   
	paddw  mm1,mm0                      
	paddw  mm2,mm3                      
	movd   mm0,DWORD PTR [eax-0x2]      
	movd   mm3,DWORD PTR [eax+0x3]      
	punpcklbw mm0,mm7                   
	punpcklbw mm3,mm7                   
	paddw  mm0,mm3                      
	psllw  mm2,0x2                      
	psubw  mm2,mm1                      
	pmullw mm2,mm4                      
	paddw  mm0,mm5                      
	paddw  mm0,mm2                      
	movd   mm3,DWORD PTR [edx]          
	psraw  mm0,0x5                      
	packuswb mm0,mm0                    
	pavgb  mm0,mm3                      
	movd   mm6,DWORD PTR [ecx]          
	pavgb  mm0,mm6                      
	movd   DWORD PTR [ecx],mm0          
	add    eax,esi                      
	add    ecx,esi                      
	add    edx,edi                      
	movd   mm1,DWORD PTR [eax-0x1]      
	movd   mm2,DWORD PTR [eax]          
	movd   mm3,DWORD PTR [eax+0x1]      
	movd   mm0,DWORD PTR [eax+0x2]      
	punpcklbw mm1,mm7                   
	punpcklbw mm2,mm7                   
	punpcklbw mm3,mm7                   
	punpcklbw mm0,mm7                   
	paddw  mm1,mm0                      
	paddw  mm2,mm3                      
	movd   mm0,DWORD PTR [eax-0x2]      
	movd   mm3,DWORD PTR [eax+0x3]      
	punpcklbw mm0,mm7                   
	punpcklbw mm3,mm7                   
	paddw  mm0,mm3                      
	psllw  mm2,0x2                      
	psubw  mm2,mm1                      
	pmullw mm2,mm4                      
	paddw  mm0,mm5                      
	paddw  mm0,mm2                      
	movd   mm3,DWORD PTR [edx]          
	psraw  mm0,0x5                      
	packuswb mm0,mm0                    
	pavgb  mm0,mm3                      
	movd   mm6,DWORD PTR [ecx]          
	pavgb  mm0,mm6                      
	movd   DWORD PTR [ecx],mm0          
	add    eax,esi                      
	add    ecx,esi                      
	add    edx,edi                      
	movd   mm1,DWORD PTR [eax-0x1]      
	movd   mm2,DWORD PTR [eax]          
	movd   mm3,DWORD PTR [eax+0x1]      
	movd   mm0,DWORD PTR [eax+0x2]      
	punpcklbw mm1,mm7                   
	punpcklbw mm2,mm7                   
	punpcklbw mm3,mm7                   
	punpcklbw mm0,mm7                   
	paddw  mm1,mm0                      
	paddw  mm2,mm3                      
	movd   mm0,DWORD PTR [eax-0x2]      
	movd   mm3,DWORD PTR [eax+0x3]      
	punpcklbw mm0,mm7                   
	punpcklbw mm3,mm7                   
	paddw  mm0,mm3                      
	psllw  mm2,0x2                      
	psubw  mm2,mm1                      
	pmullw mm2,mm4                      
	paddw  mm0,mm5                      
	paddw  mm0,mm2                      
	movd   mm3,DWORD PTR [edx]          
	psraw  mm0,0x5                      
	packuswb mm0,mm0                    
	pavgb  mm0,mm3                      
	movd   mm6,DWORD PTR [ecx]          
	pavgb  mm0,mm6                      
	movd   DWORD PTR [ecx],mm0          
	add    eax,esi                      
	add    ecx,esi                      
	add    edx,edi                      
	mov    esi,DWORD PTR [esp]          
	mov    edi,DWORD PTR [esp+0x4]      
	add    esp,0x8                      
	ret                                 
	}
}
void __declspec(naked) avg_h264_qpel4_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                               
	mov    DWORD PTR [esp],esi                   
	mov    esi,DWORD PTR [esp+0x18]              
	mov    DWORD PTR [esp+0x4],edi               
	mov    ecx,DWORD PTR [esp+0xc]               
	mov    edi,DWORD PTR [esp+0x14]              
	lea    eax,[esi+esi*1]                       
	neg    eax                                   
	add    eax,DWORD PTR [esp+0x10]              
	pxor   mm7,mm7                               
	movd   mm0,DWORD PTR [eax]                   
	add    eax,esi                               
	movd   mm1,DWORD PTR [eax]                   
	add    eax,esi                               
	movd   mm2,DWORD PTR [eax]                   
	add    eax,esi                               
	movd   mm3,DWORD PTR [eax]                   
	add    eax,esi                               
	movd   mm4,DWORD PTR [eax]                   
	add    eax,esi                               
	punpcklbw mm0,mm7                            
	punpcklbw mm1,mm7                            
	punpcklbw mm2,mm7                            
	punpcklbw mm3,mm7                            
	punpcklbw mm4,mm7                            
	movq   mm6,mm2                               
	movd   mm5,DWORD PTR [eax]                   
	paddw  mm6,mm3                               
	psllw  mm6,0x2                               
	psubw  mm6,mm1                               
	psubw  mm6,mm4                               
	punpcklbw mm5,mm7                            
	pmullw mm6,QWORD PTR [ff_pw_5]                  
	paddw  mm0,QWORD PTR [ff_pw_16]                  
	add    eax,esi                               
	paddw  mm0,mm5                               
	paddw  mm6,mm0                               
	psraw  mm6,0x5                               
	packuswb mm6,mm6                             
	movd   mm0,DWORD PTR [ecx]                   
	pavgb  mm6,mm0                               
	movd   DWORD PTR [ecx],mm6                   
	add    ecx,edi                               
	movq   mm6,mm3                               
	movd   mm0,DWORD PTR [eax]                   
	paddw  mm6,mm4                               
	psllw  mm6,0x2                               
	psubw  mm6,mm2                               
	psubw  mm6,mm5                               
	punpcklbw mm0,mm7                            
	pmullw mm6,QWORD PTR [ff_pw_5]                  
	paddw  mm1,QWORD PTR [ff_pw_16]                  
	add    eax,esi                               
	paddw  mm1,mm0                               
	paddw  mm6,mm1                               
	psraw  mm6,0x5                               
	packuswb mm6,mm6                             
	movd   mm1,DWORD PTR [ecx]                   
	pavgb  mm6,mm1                               
	movd   DWORD PTR [ecx],mm6                   
	add    ecx,edi                               
	movq   mm6,mm4                               
	movd   mm1,DWORD PTR [eax]                   
	paddw  mm6,mm5                               
	psllw  mm6,0x2                               
	psubw  mm6,mm3                               
	psubw  mm6,mm0                               
	punpcklbw mm1,mm7                            
	pmullw mm6,QWORD PTR [ff_pw_5]                  
	paddw  mm2,QWORD PTR [ff_pw_16]                  
	add    eax,esi                               
	paddw  mm2,mm1                               
	paddw  mm6,mm2                               
	psraw  mm6,0x5                               
	packuswb mm6,mm6                             
	movd   mm2,DWORD PTR [ecx]                   
	pavgb  mm6,mm2                               
	movd   DWORD PTR [ecx],mm6                   
	add    ecx,edi                               
	movq   mm6,mm5                               
	movd   mm2,DWORD PTR [eax]                   
	paddw  mm6,mm0                               
	psllw  mm6,0x2                               
	psubw  mm6,mm4                               
	psubw  mm6,mm1                               
	punpcklbw mm2,mm7                            
	pmullw mm6,QWORD PTR [ff_pw_5]                  
	paddw  mm3,QWORD PTR [ff_pw_16]                  
	add    eax,esi                               
	paddw  mm3,mm2                               
	paddw  mm6,mm3                               
	psraw  mm6,0x5                               
	packuswb mm6,mm6                             
	movd   mm3,DWORD PTR [ecx]                   
	pavgb  mm6,mm3                               
	movd   DWORD PTR [ecx],mm6                   
	add    ecx,edi                               
	mov    esi,DWORD PTR [esp]                   
	mov    edi,DWORD PTR [esp+0x4]               
	add    esp,0x8                               
	ret                                         
	}
}
void __declspec(naked) avg_h264_qpel4_hv_lowpass_mmx2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	__asm{
	sub    esp,0xc                              
	mov    DWORD PTR [esp+0x4],esi              
	mov    esi,DWORD PTR [esp+0x24]             
	mov    edx,DWORD PTR [esp+0x14]             
	mov    DWORD PTR [esp],ebx                  
	mov    DWORD PTR [esp+0x8],edi              
	mov    edi,DWORD PTR [esp+0x10]             
	mov    eax,esi                              
	lea    ebx,[esi+esi*8]                      
	not    eax                                  
	neg    ebx                                  
	add    eax,eax                              
	add    ebx,0x4                              
	mov    ecx,edx                              
	add    eax,DWORD PTR [esp+0x18]             
	pxor   mm7,mm7                              
	movd   mm0,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm1,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm2,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm3,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm4,DWORD PTR [eax]                  
	add    eax,esi                              
	punpcklbw mm0,mm7                           
	punpcklbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpcklbw mm3,mm7                           
	punpcklbw mm4,mm7                           
	movq   mm6,mm2                              
	movd   mm5,DWORD PTR [eax]                  
	paddw  mm6,mm3                              
	psllw  mm6,0x2                              
	paddw  mm0,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm1                              
	psubw  mm6,mm4                              
	punpcklbw mm5,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm0,mm5                              
	add    eax,esi                              
	paddw  mm6,mm0                              
	movq   QWORD PTR [ecx],mm6                  
	movq   mm6,mm3                              
	movd   mm0,DWORD PTR [eax]                  
	paddw  mm6,mm4                              
	psllw  mm6,0x2                              
	paddw  mm1,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm2                              
	psubw  mm6,mm5                              
	punpcklbw mm0,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm1,mm0                              
	add    eax,esi                              
	paddw  mm6,mm1                              
	movq   QWORD PTR [ecx+0x18],mm6             
	movq   mm6,mm4                              
	movd   mm1,DWORD PTR [eax]                  
	paddw  mm6,mm5                              
	psllw  mm6,0x2                              
	paddw  mm2,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm3                              
	psubw  mm6,mm0                              
	punpcklbw mm1,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm2,mm1                              
	add    eax,esi                              
	paddw  mm6,mm2                              
	movq   QWORD PTR [ecx+0x30],mm6             
	movq   mm6,mm5                              
	movd   mm2,DWORD PTR [eax]                  
	paddw  mm6,mm0                              
	psllw  mm6,0x2                              
	paddw  mm3,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm4                              
	psubw  mm6,mm1                              
	punpcklbw mm2,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm3,mm2                              
	add    eax,esi                              
	paddw  mm6,mm3                              
	movq   QWORD PTR [ecx+0x48],mm6             
	lea    ecx,[edx+0x8]                        
	add    eax,ebx                              
	pxor   mm7,mm7                              
	movd   mm0,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm1,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm2,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm3,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm4,DWORD PTR [eax]                  
	add    eax,esi                              
	punpcklbw mm0,mm7                           
	punpcklbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpcklbw mm3,mm7                           
	punpcklbw mm4,mm7                           
	movq   mm6,mm2                              
	movd   mm5,DWORD PTR [eax]                  
	paddw  mm6,mm3                              
	psllw  mm6,0x2                              
	paddw  mm0,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm1                              
	psubw  mm6,mm4                              
	punpcklbw mm5,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm0,mm5                              
	add    eax,esi                              
	paddw  mm6,mm0                              
	movq   QWORD PTR [ecx],mm6                  
	movq   mm6,mm3                              
	movd   mm0,DWORD PTR [eax]                  
	paddw  mm6,mm4                              
	psllw  mm6,0x2                              
	paddw  mm1,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm2                              
	psubw  mm6,mm5                              
	punpcklbw mm0,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm1,mm0                              
	add    eax,esi                              
	paddw  mm6,mm1                              
	movq   QWORD PTR [ecx+0x18],mm6             
	movq   mm6,mm4                              
	movd   mm1,DWORD PTR [eax]                  
	paddw  mm6,mm5                              
	psllw  mm6,0x2                              
	paddw  mm2,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm3                              
	psubw  mm6,mm0                              
	punpcklbw mm1,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm2,mm1                              
	add    eax,esi                              
	paddw  mm6,mm2                              
	movq   QWORD PTR [ecx+0x30],mm6             
	movq   mm6,mm5                              
	movd   mm2,DWORD PTR [eax]                  
	paddw  mm6,mm0                              
	psllw  mm6,0x2                              
	paddw  mm3,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm4                              
	psubw  mm6,mm1                              
	punpcklbw mm2,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm3,mm2                              
	add    eax,esi                              
	paddw  mm6,mm3                              
	movq   QWORD PTR [ecx+0x48],mm6             
	add    eax,ebx                              
	lea    ecx,[edx+0x10]                       
	pxor   mm7,mm7                              
	movd   mm0,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm1,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm2,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm3,DWORD PTR [eax]                  
	add    eax,esi                              
	movd   mm4,DWORD PTR [eax]                  
	add    eax,esi                              
	punpcklbw mm0,mm7                           
	punpcklbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpcklbw mm3,mm7                           
	punpcklbw mm4,mm7                           
	movq   mm6,mm2                              
	movd   mm5,DWORD PTR [eax]                  
	paddw  mm6,mm3                              
	psllw  mm6,0x2                              
	paddw  mm0,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm1                              
	psubw  mm6,mm4                              
	punpcklbw mm5,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm0,mm5                              
	add    eax,esi                              
	paddw  mm6,mm0                              
	movq   QWORD PTR [ecx],mm6                  
	movq   mm6,mm3                              
	movd   mm0,DWORD PTR [eax]                  
	paddw  mm6,mm4                              
	psllw  mm6,0x2                              
	paddw  mm1,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm2                              
	psubw  mm6,mm5                              
	punpcklbw mm0,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm1,mm0                              
	add    eax,esi                              
	paddw  mm6,mm1                              
	movq   QWORD PTR [ecx+0x18],mm6             
	movq   mm6,mm4                              
	movd   mm1,DWORD PTR [eax]                  
	paddw  mm6,mm5                              
	psllw  mm6,0x2                              
	paddw  mm2,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm3                              
	psubw  mm6,mm0                              
	punpcklbw mm1,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm2,mm1                              
	add    eax,esi                              
	paddw  mm6,mm2                              
	movq   QWORD PTR [ecx+0x30],mm6             
	movq   mm6,mm5                              
	movd   mm2,DWORD PTR [eax]                  
	paddw  mm6,mm0                              
	psllw  mm6,0x2                              
	paddw  mm3,QWORD PTR [ff_pw_16]                 
	psubw  mm6,mm4                              
	psubw  mm6,mm1                              
	punpcklbw mm2,mm7                           
	pmullw mm6,QWORD PTR [ff_pw_5]                
	paddw  mm3,mm2                              
	add    eax,esi                              
	paddw  mm6,mm3                              
	movq   QWORD PTR [ecx+0x48],mm6             
	mov    eax,edx                              
	mov    esi,DWORD PTR [esp+0x1c]             
	mov    ecx,edi                              
	mov    edx,0x4                              
avg_h264_qpel4_hv_lowpass_mmx2flag:          
	movq   mm0,QWORD PTR [eax]                  
	paddw  mm0,QWORD PTR [eax+0xa]              
	movq   mm1,QWORD PTR [eax+0x2]              
	paddw  mm1,QWORD PTR [eax+0x8]              
	movq   mm2,QWORD PTR [eax+0x4]              
	paddw  mm2,QWORD PTR [eax+0x6]              
	psubw  mm0,mm1                              
	psraw  mm0,0x2                              
	psubw  mm0,mm1                              
	paddsw mm0,mm2                              
	psraw  mm0,0x2                              
	paddw  mm0,mm2                              
	psraw  mm0,0x6                              
	packuswb mm0,mm0                            
	movd   mm7,DWORD PTR [ecx]                  
	pavgb  mm0,mm7                              
	movd   DWORD PTR [ecx],mm0                  
	add    eax,0x18                             
	add    ecx,esi                              
	dec    edx                                  
	jne    avg_h264_qpel4_hv_lowpass_mmx2flag   
	mov    ebx,DWORD PTR [esp]                  
	mov    esi,DWORD PTR [esp+0x4]              
	mov    edi,DWORD PTR [esp+0x8]              
	add    esp,0xc                              
	ret                                         
	}
}
void __declspec(naked) avg_h264_qpel8_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                                  
	mov    DWORD PTR [esp],ebx                      
	mov    ecx,DWORD PTR [esp+0xc]                  
	mov    ebx,0x8                                  
	mov    DWORD PTR [esp+0x4],esi                  
	mov    eax,DWORD PTR [esp+0x10]                 
	mov    edx,DWORD PTR [esp+0x18]                 
	mov    esi,DWORD PTR [esp+0x14]                 
	pxor   mm7,mm7                                  
	movq   mm6,QWORD PTR [ff_pw_5]                   
avg_h264_qpel8_h_lowpass_mmx2flag:               
	movq   mm0,QWORD PTR [eax]                      
	movq   mm2,QWORD PTR [eax+0x1]                  
	movq   mm1,mm0                                  
	movq   mm3,mm2                                  
	punpcklbw mm0,mm7                               
	punpckhbw mm1,mm7                               
	punpcklbw mm2,mm7                               
	punpckhbw mm3,mm7                               
	paddw  mm0,mm2                                  
	paddw  mm1,mm3                                  
	psllw  mm0,0x2                                  
	psllw  mm1,0x2                                  
	movq   mm2,QWORD PTR [eax-0x1]                  
	movq   mm4,QWORD PTR [eax+0x2]                  
	movq   mm3,mm2                                  
	movq   mm5,mm4                                  
	punpcklbw mm2,mm7                               
	punpckhbw mm3,mm7                               
	punpcklbw mm4,mm7                               
	punpckhbw mm5,mm7                               
	paddw  mm2,mm4                                  
	paddw  mm5,mm3                                  
	psubw  mm0,mm2                                  
	psubw  mm1,mm5                                  
	pmullw mm0,mm6                                  
	pmullw mm1,mm6                                  
	movd   mm2,DWORD PTR [eax-0x2]                  
	movd   mm5,DWORD PTR [eax+0x7]                  
	punpcklbw mm2,mm7                               
	punpcklbw mm5,mm7                               
	paddw  mm2,mm3                                  
	paddw  mm4,mm5                                  
	movq   mm5,QWORD PTR [ff_pw_16]                     
	paddw  mm2,mm5                                  
	paddw  mm4,mm5                                  
	paddw  mm0,mm2                                  
	paddw  mm1,mm4                                  
	psraw  mm0,0x5                                  
	psraw  mm1,0x5                                  
	packuswb mm0,mm1                                
	movq   mm5,QWORD PTR [ecx]                      
	pavgb  mm0,mm5                                  
	movq   QWORD PTR [ecx],mm0                      
	add    eax,edx                                  
	add    ecx,esi                                  
	dec    ebx                                      
	jne    avg_h264_qpel8_h_lowpass_mmx2flag        
	mov    ebx,DWORD PTR [esp]                      
	mov    esi,DWORD PTR [esp+0x4]                  
	add    esp,0x8                                  
	ret                                             
	}
}
void avg_h264_qpel16_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	avg_h264_qpel8_h_lowpass_mmx2(dst , src , dstStride, srcStride);
	avg_h264_qpel8_h_lowpass_mmx2(dst+8, src+8, dstStride, srcStride);
	src += 8*srcStride;
	dst += 8*dstStride;
	avg_h264_qpel8_h_lowpass_mmx2(dst , src , dstStride, srcStride);
	avg_h264_qpel8_h_lowpass_mmx2(dst+8, src+8, dstStride, srcStride);
}
void __declspec(naked) avg_h264_qpel8_h_lowpass_l2_mmx2(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0xc                              
	mov    DWORD PTR [esp],ebx                  
	mov    ecx,DWORD PTR [esp+0x10]             
	mov    ebx,0x8                              
	mov    DWORD PTR [esp+0x4],esi              
	mov    eax,DWORD PTR [esp+0x14]             
	mov    DWORD PTR [esp+0x8],edi              
	mov    edx,DWORD PTR [esp+0x18]             
	mov    edi,DWORD PTR [esp+0x20]             
	mov    esi,DWORD PTR [esp+0x1c]             
	pxor   mm7,mm7                              
	movq   mm6,QWORD PTR [ff_pw_5]              
avg_h264_qpel8_h_lowpass_l2_mmx2flag:        
	movq   mm0,QWORD PTR [eax]                  
	movq   mm2,QWORD PTR [eax+0x1]              
	movq   mm1,mm0                              
	movq   mm3,mm2                              
	punpcklbw mm0,mm7                           
	punpckhbw mm1,mm7                           
	punpcklbw mm2,mm7                           
	punpckhbw mm3,mm7                           
	paddw  mm0,mm2                              
	paddw  mm1,mm3                              
	psllw  mm0,0x2                              
	psllw  mm1,0x2                              
	movq   mm2,QWORD PTR [eax-0x1]              
	movq   mm4,QWORD PTR [eax+0x2]              
	movq   mm3,mm2                              
	movq   mm5,mm4                              
	punpcklbw mm2,mm7                           
	punpckhbw mm3,mm7                           
	punpcklbw mm4,mm7                           
	punpckhbw mm5,mm7                           
	paddw  mm2,mm4                              
	paddw  mm5,mm3                              
	psubw  mm0,mm2                              
	psubw  mm1,mm5                              
	pmullw mm0,mm6                              
	pmullw mm1,mm6                              
	movd   mm2,DWORD PTR [eax-0x2]              
	movd   mm5,DWORD PTR [eax+0x7]              
	punpcklbw mm2,mm7                           
	punpcklbw mm5,mm7                           
	paddw  mm2,mm3                              
	paddw  mm4,mm5                              
	movq   mm5,QWORD PTR [ff_pw_16]                
	paddw  mm2,mm5                              
	paddw  mm4,mm5                              
	paddw  mm0,mm2                              
	paddw  mm1,mm4                              
	psraw  mm0,0x5                              
	psraw  mm1,0x5                              
	movq   mm4,QWORD PTR [edx]                  
	packuswb mm0,mm1                            
	pavgb  mm0,mm4                              
	movq   mm5,QWORD PTR [ecx]                  
	pavgb  mm0,mm5                              
	movq   QWORD PTR [ecx],mm0                  
	add    eax,esi                              
	add    ecx,esi                              
	add    edx,edi                              
	dec    ebx                                  
	jg     avg_h264_qpel8_h_lowpass_l2_mmx2flag 
	mov    ebx,DWORD PTR [esp]                  
	mov    esi,DWORD PTR [esp+0x4]              
	mov    edi,DWORD PTR [esp+0x8]              
	add    esp,0xc                              
	ret                                         
	}
}
void __declspec(naked) avg_h264_qpel8or16_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
	__asm{
	sub    esp,0x10                                                               
	mov    edx,0xfffffffb                                                         
	mov    DWORD PTR [esp],ebx                                                    
	mov    ebx,DWORD PTR [esp+0x24]                                               
	mov    DWORD PTR [esp+0x4],esi                                                
	mov    esi,DWORD PTR [esp+0x20]                                               
	mov    DWORD PTR [esp+0x8],edi                                                
	mov    edi,DWORD PTR [esp+0x1c]                                               
	mov    DWORD PTR [esp+0xc],ebp                                                
	mov    ecx,DWORD PTR [esp+0x14]                                               
	sub    edx,ebx                                                                
	mov    ebp,ebx                                                                
	lea    eax,[esi+esi*1]                                                        
	neg    eax                                                                    
	imul   edx,esi                                                                
	add    eax,DWORD PTR [esp+0x18]                                               
	imul   ebp,edi                                                                
	pxor   mm7,mm7                                                                
	movd   mm0,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	movd   mm1,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	movd   mm2,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	movd   mm3,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	movd   mm4,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	punpcklbw mm0,mm7                                                             
	punpcklbw mm1,mm7                                                             
	punpcklbw mm2,mm7                                                             
	punpcklbw mm3,mm7                                                             
	punpcklbw mm4,mm7                                                             
	movq   mm6,mm2                                                                
	movd   mm5,DWORD PTR [eax]                                                    
	paddw  mm6,mm3                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm1                                                                
	psubw  mm6,mm4                                                                
	punpcklbw mm5,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm0,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm0,mm5                                                                
	paddw  mm6,mm0                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm0,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm0                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm3                                                                
	movd   mm0,DWORD PTR [eax]                                                    
	paddw  mm6,mm4                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm2                                                                
	psubw  mm6,mm5                                                                
	punpcklbw mm0,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm1,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm1,mm0                                                                
	paddw  mm6,mm1                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm1,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm1                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm4                                                                
	movd   mm1,DWORD PTR [eax]                                                    
	paddw  mm6,mm5                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm3                                                                
	psubw  mm6,mm0                                                                
	punpcklbw mm1,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm2,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm2,mm1                                                                
	paddw  mm6,mm2                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm2,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm2                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm5                                                                
	movd   mm2,DWORD PTR [eax]                                                    
	paddw  mm6,mm0                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm4                                                                
	psubw  mm6,mm1                                                                
	punpcklbw mm2,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm3,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm3,mm2                                                                
	paddw  mm6,mm3                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm3,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm3                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm0                                                                
	movd   mm3,DWORD PTR [eax]                                                    
	paddw  mm6,mm1                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm5                                                                
	psubw  mm6,mm2                                                                
	punpcklbw mm3,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm4,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm4,mm3                                                                
	paddw  mm6,mm4                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm4,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm4                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm1                                                                
	movd   mm4,DWORD PTR [eax]                                                    
	paddw  mm6,mm2                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm0                                                                
	psubw  mm6,mm3                                                                
	punpcklbw mm4,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm5,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm5,mm4                                                                
	paddw  mm6,mm5                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm5,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm5                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm2                                                                
	movd   mm5,DWORD PTR [eax]                                                    
	paddw  mm6,mm3                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm1                                                                
	psubw  mm6,mm4                                                                
	punpcklbw mm5,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm0,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm0,mm5                                                                
	paddw  mm6,mm0                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm0,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm0                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm3                                                                
	movd   mm0,DWORD PTR [eax]                                                    
	paddw  mm6,mm4                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm2                                                                
	psubw  mm6,mm5                                                                
	punpcklbw mm0,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm1,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm1,mm0                                                                
	paddw  mm6,mm1                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm1,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm1                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	cmp    ebx,0x10                                                               
	jne    avg_h264_qpel8or16_v_lowpass_mmx2_4a22e                                
	movq   mm6,mm4                                                                
	movd   mm1,DWORD PTR [eax]                                                    
	paddw  mm6,mm5                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm3                                                                
	psubw  mm6,mm0                                                                
	punpcklbw mm1,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm2,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm2,mm1                                                                
	paddw  mm6,mm2                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm2,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm2                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm5                                                                
	movd   mm2,DWORD PTR [eax]                                                    
	paddw  mm6,mm0                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm4                                                                
	psubw  mm6,mm1                                                                
	punpcklbw mm2,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm3,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm3,mm2                                                                
	paddw  mm6,mm3                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm3,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm3                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm0                                                                
	movd   mm3,DWORD PTR [eax]                                                    
	paddw  mm6,mm1                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm5                                                                
	psubw  mm6,mm2                                                                
	punpcklbw mm3,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm4,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm4,mm3                                                                
	paddw  mm6,mm4                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm4,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm4                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm1                                                                
	movd   mm4,DWORD PTR [eax]                                                    
	paddw  mm6,mm2                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm0                                                                
	psubw  mm6,mm3                                                                
	punpcklbw mm4,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm5,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm5,mm4                                                                
	paddw  mm6,mm5                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm5,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm5                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm2                                                                
	movd   mm5,DWORD PTR [eax]                                                    
	paddw  mm6,mm3                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm1                                                                
	psubw  mm6,mm4                                                                
	punpcklbw mm5,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm0,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm0,mm5                                                                
	paddw  mm6,mm0                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm0,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm0                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm3                                                                
	movd   mm0,DWORD PTR [eax]                                                    
	paddw  mm6,mm4                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm2                                                                
	psubw  mm6,mm5                                                                
	punpcklbw mm0,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm1,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm1,mm0                                                                
	paddw  mm6,mm1                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm1,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm1                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm4                                                                
	movd   mm1,DWORD PTR [eax]                                                    
	paddw  mm6,mm5                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm3                                                                
	psubw  mm6,mm0                                                                
	punpcklbw mm1,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm2,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm2,mm1                                                                
	paddw  mm6,mm2                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm2,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm2                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm5                                                                
	movd   mm2,DWORD PTR [eax]                                                    
	paddw  mm6,mm0                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm4                                                                
	psubw  mm6,mm1                                                                
	punpcklbw mm2,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm3,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm3,mm2                                                                
	paddw  mm6,mm3                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm3,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm3                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
avg_h264_qpel8or16_v_lowpass_mmx2_4a22e:                                       
	sub    ecx,ebp                                                                
	lea    eax,[eax+edx*1+0x4]                                                    
	add    ecx,0x4                                                                
	pxor   mm7,mm7                                                                
	movd   mm0,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	movd   mm1,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	movd   mm2,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	movd   mm3,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	movd   mm4,DWORD PTR [eax]                                                    
	add    eax,esi                                                                
	punpcklbw mm0,mm7                                                             
	punpcklbw mm1,mm7                                                             
	punpcklbw mm2,mm7                                                             
	punpcklbw mm3,mm7                                                             
	punpcklbw mm4,mm7                                                             
	movq   mm6,mm2                                                                
	movd   mm5,DWORD PTR [eax]                                                    
	paddw  mm6,mm3                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm1                                                                
	psubw  mm6,mm4                                                                
	punpcklbw mm5,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm0,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm0,mm5                                                                
	paddw  mm6,mm0                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm0,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm0                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm3                                                                
	movd   mm0,DWORD PTR [eax]                                                    
	paddw  mm6,mm4                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm2                                                                
	psubw  mm6,mm5                                                                
	punpcklbw mm0,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm1,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm1,mm0                                                                
	paddw  mm6,mm1                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm1,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm1                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm4                                                                
	movd   mm1,DWORD PTR [eax]                                                    
	paddw  mm6,mm5                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm3                                                                
	psubw  mm6,mm0                                                                
	punpcklbw mm1,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm2,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm2,mm1                                                                
	paddw  mm6,mm2                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm2,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm2                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm5                                                                
	movd   mm2,DWORD PTR [eax]                                                    
	paddw  mm6,mm0                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm4                                                                
	psubw  mm6,mm1                                                                
	punpcklbw mm2,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm3,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm3,mm2                                                                
	paddw  mm6,mm3                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm3,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm3                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm0                                                                
	movd   mm3,DWORD PTR [eax]                                                    
	paddw  mm6,mm1                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm5                                                                
	psubw  mm6,mm2                                                                
	punpcklbw mm3,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm4,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm4,mm3                                                                
	paddw  mm6,mm4                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm4,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm4                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm1                                                                
	movd   mm4,DWORD PTR [eax]                                                    
	paddw  mm6,mm2                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm0                                                                
	psubw  mm6,mm3                                                                
	punpcklbw mm4,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm5,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm5,mm4                                                                
	paddw  mm6,mm5                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm5,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm5                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm2                                                                
	movd   mm5,DWORD PTR [eax]                                                    
	paddw  mm6,mm3                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm1                                                                
	psubw  mm6,mm4                                                                
	punpcklbw mm5,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm0,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm0,mm5                                                                
	paddw  mm6,mm0                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm0,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm0                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm3                                                                
	movd   mm0,DWORD PTR [eax]                                                    
	paddw  mm6,mm4                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm2                                                                
	psubw  mm6,mm5                                                                
	punpcklbw mm0,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm1,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm1,mm0                                                                
	paddw  mm6,mm1                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm1,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm1                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	cmp    ebx,0x10                                                               
	jne    avg_h264_qpel8or16_v_lowpass_mmx2_4a64b                                
	movq   mm6,mm4                                                                
	movd   mm1,DWORD PTR [eax]                                                    
	paddw  mm6,mm5                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm3                                                                
	psubw  mm6,mm0                                                                
	punpcklbw mm1,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm2,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm2,mm1                                                                
	paddw  mm6,mm2                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm2,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm2                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm5                                                                
	movd   mm2,DWORD PTR [eax]                                                    
	paddw  mm6,mm0                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm4                                                                
	psubw  mm6,mm1                                                                
	punpcklbw mm2,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm3,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm3,mm2                                                                
	paddw  mm6,mm3                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm3,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm3                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm0                                                                
	movd   mm3,DWORD PTR [eax]                                                    
	paddw  mm6,mm1                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm5                                                                
	psubw  mm6,mm2                                                                
	punpcklbw mm3,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm4,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm4,mm3                                                                
	paddw  mm6,mm4                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm4,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm4                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm1                                                                
	movd   mm4,DWORD PTR [eax]                                                    
	paddw  mm6,mm2                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm0                                                                
	psubw  mm6,mm3                                                                
	punpcklbw mm4,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm5,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm5,mm4                                                                
	paddw  mm6,mm5                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm5,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm5                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm2                                                                
	movd   mm5,DWORD PTR [eax]                                                    
	paddw  mm6,mm3                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm1                                                                
	psubw  mm6,mm4                                                                
	punpcklbw mm5,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm0,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm0,mm5                                                                
	paddw  mm6,mm0                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm0,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm0                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm3                                                                
	movd   mm0,DWORD PTR [eax]                                                    
	paddw  mm6,mm4                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm2                                                                
	psubw  mm6,mm5                                                                
	punpcklbw mm0,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm1,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm1,mm0                                                                
	paddw  mm6,mm1                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm1,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm1                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm4                                                                
	movd   mm1,DWORD PTR [eax]                                                    
	paddw  mm6,mm5                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm3                                                                
	psubw  mm6,mm0                                                                
	punpcklbw mm1,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm2,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm2,mm1                                                                
	paddw  mm6,mm2                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm2,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm2                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
	movq   mm6,mm5                                                                
	movd   mm2,DWORD PTR [eax]                                                    
	paddw  mm6,mm0                                                                
	psllw  mm6,0x2                                                                
	psubw  mm6,mm4                                                                
	psubw  mm6,mm1                                                                
	punpcklbw mm2,mm7                                                             
	pmullw mm6,QWORD PTR [ff_pw_5]                                                   
	paddw  mm3,QWORD PTR [ff_pw_16]                                                   
	add    eax,esi                                                                
	paddw  mm3,mm2                                                                
	paddw  mm6,mm3                                                                
	psraw  mm6,0x5                                                                
	packuswb mm6,mm6                                                              
	movd   mm3,DWORD PTR [ecx]                                                    
	pavgb  mm6,mm3                                                                
	movd   DWORD PTR [ecx],mm6                                                    
	add    ecx,edi                                                                
avg_h264_qpel8or16_v_lowpass_mmx2_4a64b:                                       
	mov    ebx,DWORD PTR [esp]                                                    
	mov    esi,DWORD PTR [esp+0x4]                                                
	mov    edi,DWORD PTR [esp+0x8]                                                
	mov    ebp,DWORD PTR [esp+0xc]                                                
	add    esp,0x10                                                               
	ret                                                                           
	}
}
void avg_h264_qpel8_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	avg_h264_qpel8or16_v_lowpass_mmx2(dst , src , dstStride, srcStride, 8);
}
void avg_h264_qpel16_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	avg_h264_qpel8or16_v_lowpass_mmx2(dst , src , dstStride, srcStride, 16); 
	avg_h264_qpel8or16_v_lowpass_mmx2(dst+8, src+8, dstStride, srcStride, 16);
}
void __declspec(naked) avg_h264_qpel16_h_lowpass_l2_mmx2(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0x1c                                            
	mov    DWORD PTR [esp+0x18],ebp                            
	mov    ebp,DWORD PTR [esp+0x24]                            
	mov    DWORD PTR [esp+0xc],ebx                             
	mov    ecx,DWORD PTR [esp+0x20]                            
	mov    ebx,0x8                                             
	mov    DWORD PTR [esp+0x10],esi                            
	mov    edx,DWORD PTR [esp+0x28]                            
	mov    DWORD PTR [esp+0x14],edi                            
	mov    esi,DWORD PTR [esp+0x2c]                            
	mov    edi,DWORD PTR [esp+0x30]                            
	mov    eax,ebp                                             
	pxor   mm7,mm7                                             
	movq   mm6,QWORD PTR [ff_pw_5]                                
avg_h264_qpel16_h_lowpass_l2_mmx2_4c748:                    
	movq   mm0,QWORD PTR [eax]                                 
	movq   mm2,QWORD PTR [eax+0x1]                             
	movq   mm1,mm0                                             
	movq   mm3,mm2                                             
	punpcklbw mm0,mm7                                          
	punpckhbw mm1,mm7                                          
	punpcklbw mm2,mm7                                          
	punpckhbw mm3,mm7                                          
	paddw  mm0,mm2                                             
	paddw  mm1,mm3                                             
	psllw  mm0,0x2                                             
	psllw  mm1,0x2                                             
	movq   mm2,QWORD PTR [eax-0x1]                             
	movq   mm4,QWORD PTR [eax+0x2]                             
	movq   mm3,mm2                                             
	movq   mm5,mm4                                             
	punpcklbw mm2,mm7                                          
	punpckhbw mm3,mm7                                          
	punpcklbw mm4,mm7                                          
	punpckhbw mm5,mm7                                          
	paddw  mm2,mm4                                             
	paddw  mm5,mm3                                             
	psubw  mm0,mm2                                             
	psubw  mm1,mm5                                             
	pmullw mm0,mm6                                             
	pmullw mm1,mm6                                             
	movd   mm2,DWORD PTR [eax-0x2]                             
	movd   mm5,DWORD PTR [eax+0x7]                             
	punpcklbw mm2,mm7                                          
	punpcklbw mm5,mm7                                          
	paddw  mm2,mm3                                             
	paddw  mm4,mm5                                             
	movq   mm5,QWORD PTR [ff_pw_16]                                
	paddw  mm2,mm5                                             
	paddw  mm4,mm5                                             
	paddw  mm0,mm2                                             
	paddw  mm1,mm4                                             
	psraw  mm0,0x5                                             
	psraw  mm1,0x5                                             
	movq   mm4,QWORD PTR [edx]                                 
	packuswb mm0,mm1                                           
	pavgb  mm0,mm4                                             
	movq   mm5,QWORD PTR [ecx]                                 
	pavgb  mm0,mm5                                             
	movq   QWORD PTR [ecx],mm0                                 
	add    eax,esi                                             
	add    ecx,esi                                             
	add    edx,edi                                             
	dec    ebx                                                 
	jg     avg_h264_qpel16_h_lowpass_l2_mmx2_4c748             
	mov    ecx,DWORD PTR [esp+0x20]                            
	lea    eax,[ebp+0x8]                                       
	mov    ebx,0x8                                             
	mov    edx,DWORD PTR [esp+0x28]                            
	add    ecx,0x8                                             
	add    edx,0x8                                             
	pxor   mm7,mm7                                             
	movq   mm6,QWORD PTR [ff_pw_5]                               
avg_h264_qpel16_h_lowpass_l2_mmx2_4c809:                    
	movq   mm0,QWORD PTR [eax]                                 
	movq   mm2,QWORD PTR [eax+0x1]                             
	movq   mm1,mm0                                             
	movq   mm3,mm2                                             
	punpcklbw mm0,mm7                                          
	punpckhbw mm1,mm7                                          
	punpcklbw mm2,mm7                                          
	punpckhbw mm3,mm7                                          
	paddw  mm0,mm2                                             
	paddw  mm1,mm3                                             
	psllw  mm0,0x2                                             
	psllw  mm1,0x2                                             
	movq   mm2,QWORD PTR [eax-0x1]                             
	movq   mm4,QWORD PTR [eax+0x2]                             
	movq   mm3,mm2                                             
	movq   mm5,mm4                                             
	punpcklbw mm2,mm7                                          
	punpckhbw mm3,mm7                                          
	punpcklbw mm4,mm7                                          
	punpckhbw mm5,mm7                                          
	paddw  mm2,mm4                                             
	paddw  mm5,mm3                                             
	psubw  mm0,mm2                                             
	psubw  mm1,mm5                                             
	pmullw mm0,mm6                                             
	pmullw mm1,mm6                                             
	movd   mm2,DWORD PTR [eax-0x2]                             
	movd   mm5,DWORD PTR [eax+0x7]                             
	punpcklbw mm2,mm7                                          
	punpcklbw mm5,mm7                                          
	paddw  mm2,mm3                                             
	paddw  mm4,mm5                                             
	movq   mm5,QWORD PTR [ff_pw_16]                                 
	paddw  mm2,mm5                                             
	paddw  mm4,mm5                                             
	paddw  mm0,mm2                                             
	paddw  mm1,mm4                                             
	psraw  mm0,0x5                                             
	psraw  mm1,0x5                                             
	movq   mm4,QWORD PTR [edx]                                 
	packuswb mm0,mm1                                           
	pavgb  mm0,mm4                                             
	movq   mm5,QWORD PTR [ecx]                                 
	pavgb  mm0,mm5                                             
	movq   QWORD PTR [ecx],mm0                                 
	add    eax,esi                                             
	add    ecx,esi                                             
	add    edx,edi                                             
	dec    ebx                                                 
	jg     avg_h264_qpel16_h_lowpass_l2_mmx2_4c809             
	mov    eax,DWORD PTR [esp+0x28]                            
	lea    ecx,[esi*8+0x0]                                     
	add    ebp,ecx                                             
	add    ecx,DWORD PTR [esp+0x20]                            
	mov    DWORD PTR [esp],ebp                                 
	lea    ebx,[eax+edi*8]                                     
	mov    eax,ebp                                             
	mov    DWORD PTR [esp+0x4],ecx                             
	mov    edx,ebx                                             
	mov    ebp,0x8                                             
	pxor   mm7,mm7                                             
	movq   mm6,QWORD PTR [ff_pw_5]                              
avg_h264_qpel16_h_lowpass_l2_mmx2_4c8d8:                    
	movq   mm0,QWORD PTR [eax]                                 
	movq   mm2,QWORD PTR [eax+0x1]                             
	movq   mm1,mm0                                             
	movq   mm3,mm2                                             
	punpcklbw mm0,mm7                                          
	punpckhbw mm1,mm7                                          
	punpcklbw mm2,mm7                                          
	punpckhbw mm3,mm7                                          
	paddw  mm0,mm2                                             
	paddw  mm1,mm3                                             
	psllw  mm0,0x2                                             
	psllw  mm1,0x2                                             
	movq   mm2,QWORD PTR [eax-0x1]                             
	movq   mm4,QWORD PTR [eax+0x2]                             
	movq   mm3,mm2                                             
	movq   mm5,mm4                                             
	punpcklbw mm2,mm7                                          
	punpckhbw mm3,mm7                                          
	punpcklbw mm4,mm7                                          
	punpckhbw mm5,mm7                                          
	paddw  mm2,mm4                                             
	paddw  mm5,mm3                                             
	psubw  mm0,mm2                                             
	psubw  mm1,mm5                                             
	pmullw mm0,mm6                                             
	pmullw mm1,mm6                                             
	movd   mm2,DWORD PTR [eax-0x2]                             
	movd   mm5,DWORD PTR [eax+0x7]                             
	punpcklbw mm2,mm7                                          
	punpcklbw mm5,mm7                                          
	paddw  mm2,mm3                                             
	paddw  mm4,mm5                                             
	movq   mm5,QWORD PTR [ff_pw_16]                                 
	paddw  mm2,mm5                                             
	paddw  mm4,mm5                                             
	paddw  mm0,mm2                                             
	paddw  mm1,mm4                                             
	psraw  mm0,0x5                                             
	psraw  mm1,0x5                                             
	movq   mm4,QWORD PTR [edx]                                 
	packuswb mm0,mm1                                           
	pavgb  mm0,mm4                                             
	movq   mm5,QWORD PTR [ecx]                                 
	pavgb  mm0,mm5                                             
	movq   QWORD PTR [ecx],mm0                                 
	add    eax,esi                                             
	add    ecx,esi                                             
	add    edx,edi                                             
	dec    ebp                                                 
	jg     avg_h264_qpel16_h_lowpass_l2_mmx2_4c8d8             
	mov    eax,DWORD PTR [esp]                                 
	lea    edx,[ebx+0x8]                                       
	mov    ebx,0x8                                             
	mov    ecx,DWORD PTR [esp+0x4]                             
	add    eax,0x8                                             
	add    ecx,0x8                                             
	pxor   mm7,mm7                                             
	movq   mm6,QWORD PTR [ff_pw_5]                               
avg_h264_qpel16_h_lowpass_l2_mmx2_4c998:                    
	movq   mm0,QWORD PTR [eax]                                 
	movq   mm2,QWORD PTR [eax+0x1]                             
	movq   mm1,mm0                                             
	movq   mm3,mm2                                             
	punpcklbw mm0,mm7                                          
	punpckhbw mm1,mm7                                          
	punpcklbw mm2,mm7                                          
	punpckhbw mm3,mm7                                          
	paddw  mm0,mm2                                             
	paddw  mm1,mm3                                             
	psllw  mm0,0x2                                             
	psllw  mm1,0x2                                             
	movq   mm2,QWORD PTR [eax-0x1]                             
	movq   mm4,QWORD PTR [eax+0x2]                             
	movq   mm3,mm2                                             
	movq   mm5,mm4                                             
	punpcklbw mm2,mm7                                          
	punpckhbw mm3,mm7                                          
	punpcklbw mm4,mm7                                          
	punpckhbw mm5,mm7                                          
	paddw  mm2,mm4                                             
	paddw  mm5,mm3                                             
	psubw  mm0,mm2                                             
	psubw  mm1,mm5                                             
	pmullw mm0,mm6                                             
	pmullw mm1,mm6                                             
	movd   mm2,DWORD PTR [eax-0x2]                             
	movd   mm5,DWORD PTR [eax+0x7]                             
	punpcklbw mm2,mm7                                          
	punpcklbw mm5,mm7                                          
	paddw  mm2,mm3                                             
	paddw  mm4,mm5                                             
	movq   mm5,QWORD PTR [ff_pw_16]
	paddw  mm2,mm5                                             
	paddw  mm4,mm5                                             
	paddw  mm0,mm2                                             
	paddw  mm1,mm4                                             
	psraw  mm0,0x5                                             
	psraw  mm1,0x5                                             
	movq   mm4,QWORD PTR [edx]                                 
	packuswb mm0,mm1                                           
	pavgb  mm0,mm4                                             
	movq   mm5,QWORD PTR [ecx]                                 
	pavgb  mm0,mm5                                             
	movq   QWORD PTR [ecx],mm0                                 
	add    eax,esi                                             
	add    ecx,esi                                             
	add    edx,edi                                             
	dec    ebx                                                 
	jg     avg_h264_qpel16_h_lowpass_l2_mmx2_4c998             
	mov    ebx,DWORD PTR [esp+0xc]                             
	mov    esi,DWORD PTR [esp+0x10]                            
	mov    edi,DWORD PTR [esp+0x14]                            
	mov    ebp,DWORD PTR [esp+0x18]                            
	add    esp,0x1c                                            
	ret                                                        
	}
}
void __declspec(naked) avg_h264_qpel8or16_hv_lowpass_mmx2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride, int size)
{
	__asm{
	push   ebp                                                          
	push   edi                                                          
	push   esi                                                          
	push   ebx                                                          
	sub    esp,0x8                                                      
	mov    edi,DWORD PTR [esp+0x34]                                     
	mov    ebp,DWORD PTR [esp+0x20]                                     
	mov    esi,DWORD PTR [esp+0x30]                                     
	lea    ebx,[edi+0x8]                                                
	sar    ebx,0x2                                                      
	test   ebx,ebx                                                      
	je     avg_h264_qpel8or16_hv_lowpass_mmx2_4ce06                     
	mov    eax,DWORD PTR [esp+0x24]                                     
	mov    edx,esi                                                      
	mov    ecx,ebp                                                      
	not    edx                                                          
	mov    DWORD PTR [esp+0x4],ebp                                      
	lea    eax,[eax+edx*2]                                              
	mov    edx,0xfffffffb                                               
	sub    edx,edi                                                      
	imul   edx,esi                                                      
	add    edx,0x4                                                      
	mov    DWORD PTR [esp],edx                                          
	mov    ebp,DWORD PTR [esp]                                          
	xor    edx,edx                                                      
	nop                                                                 
avg_h264_qpel8or16_hv_lowpass_mmx2_4ca98:                            
	pxor   mm7,mm7                                                      
	movd   mm0,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm1,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm2,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm3,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	movd   mm4,DWORD PTR [eax]                                          
	add    eax,esi                                                      
	punpcklbw mm0,mm7                                                   
	punpcklbw mm1,mm7                                                   
	punpcklbw mm2,mm7                                                   
	punpcklbw mm3,mm7                                                   
	punpcklbw mm4,mm7                                                   
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	paddw  mm0,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,mm5                                                      
	add    eax,esi                                                      
	paddw  mm6,mm0                                                      
	movq   QWORD PTR [ecx],mm6                                          
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	paddw  mm1,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,mm0                                                      
	add    eax,esi                                                      
	paddw  mm6,mm1                                                      
	movq   QWORD PTR [ecx+0x30],mm6                                     
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	paddw  mm2,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,mm1                                                      
	add    eax,esi                                                      
	paddw  mm6,mm2                                                      
	movq   QWORD PTR [ecx+0x60],mm6                                     
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	paddw  mm3,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,mm2                                                      
	add    eax,esi                                                      
	paddw  mm6,mm3                                                      
	movq   QWORD PTR [ecx+0x90],mm6                                     
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	paddw  mm4,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,mm3                                                      
	add    eax,esi                                                      
	paddw  mm6,mm4                                                      
	movq   QWORD PTR [ecx+0xc0],mm6                                     
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	paddw  mm5,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,mm4                                                      
	add    eax,esi                                                      
	paddw  mm6,mm5                                                      
	movq   QWORD PTR [ecx+0xf0],mm6                                     
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	paddw  mm0,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,mm5                                                      
	add    eax,esi                                                      
	paddw  mm6,mm0                                                      
	movq   QWORD PTR [ecx+0x120],mm6                                    
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	paddw  mm1,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,mm0                                                      
	add    eax,esi                                                      
	paddw  mm6,mm1                                                      
	movq   QWORD PTR [ecx+0x150],mm6                                    
	cmp    edi,0x10                                                     
	jne    avg_h264_qpel8or16_hv_lowpass_mmx2_4cdf2                     
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	paddw  mm2,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,mm1                                                      
	add    eax,esi                                                      
	paddw  mm6,mm2                                                      
	movq   QWORD PTR [ecx+0x180],mm6                                    
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	paddw  mm3,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,mm2                                                      
	add    eax,esi                                                      
	paddw  mm6,mm3                                                      
	movq   QWORD PTR [ecx+0x1b0],mm6                                    
	movq   mm6,mm0                                                      
	movd   mm3,DWORD PTR [eax]                                          
	paddw  mm6,mm1                                                      
	psllw  mm6,0x2                                                      
	paddw  mm4,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm5                                                      
	psubw  mm6,mm2                                                      
	punpcklbw mm3,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm4,mm3                                                      
	add    eax,esi                                                      
	paddw  mm6,mm4                                                      
	movq   QWORD PTR [ecx+0x1e0],mm6                                    
	movq   mm6,mm1                                                      
	movd   mm4,DWORD PTR [eax]                                          
	paddw  mm6,mm2                                                      
	psllw  mm6,0x2                                                      
	paddw  mm5,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm0                                                      
	psubw  mm6,mm3                                                      
	punpcklbw mm4,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm5,mm4                                                      
	add    eax,esi                                                      
	paddw  mm6,mm5                                                      
	movq   QWORD PTR [ecx+0x210],mm6                                    
	movq   mm6,mm2                                                      
	movd   mm5,DWORD PTR [eax]                                          
	paddw  mm6,mm3                                                      
	psllw  mm6,0x2                                                      
	paddw  mm0,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm1                                                      
	psubw  mm6,mm4                                                      
	punpcklbw mm5,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm0,mm5                                                      
	add    eax,esi                                                      
	paddw  mm6,mm0                                                      
	movq   QWORD PTR [ecx+0x240],mm6                                    
	movq   mm6,mm3                                                      
	movd   mm0,DWORD PTR [eax]                                          
	paddw  mm6,mm4                                                      
	psllw  mm6,0x2                                                      
	paddw  mm1,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm2                                                      
	psubw  mm6,mm5                                                      
	punpcklbw mm0,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm1,mm0                                                      
	add    eax,esi                                                      
	paddw  mm6,mm1                                                      
	movq   QWORD PTR [ecx+0x270],mm6                                    
	movq   mm6,mm4                                                      
	movd   mm1,DWORD PTR [eax]                                          
	paddw  mm6,mm5                                                      
	psllw  mm6,0x2                                                      
	paddw  mm2,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm3                                                      
	psubw  mm6,mm0                                                      
	punpcklbw mm1,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm2,mm1                                                      
	add    eax,esi                                                      
	paddw  mm6,mm2                                                      
	movq   QWORD PTR [ecx+0x2a0],mm6                                    
	movq   mm6,mm5                                                      
	movd   mm2,DWORD PTR [eax]                                          
	paddw  mm6,mm0                                                      
	psllw  mm6,0x2                                                      
	paddw  mm3,QWORD PTR [ff_pw_16]                                        
	psubw  mm6,mm4                                                      
	psubw  mm6,mm1                                                      
	punpcklbw mm2,mm7                                                   
	pmullw mm6,QWORD PTR [ff_pw_5]                                         
	paddw  mm3,mm2                                                      
	add    eax,esi                                                      
	paddw  mm6,mm3                                                      
	movq   QWORD PTR [ecx+0x2d0],mm6                                    
avg_h264_qpel8or16_hv_lowpass_mmx2_4cdf2:                            
	add    edx,0x1                                                      
	add    ecx,0x8                                                      
	add    eax,ebp                                                      
	cmp    edx,ebx                                                      
	jne    avg_h264_qpel8or16_hv_lowpass_mmx2_4ca98                     
	mov    ebp,DWORD PTR [esp+0x4]                                      
avg_h264_qpel8or16_hv_lowpass_mmx2_4ce06:                            
	lea    eax,[edi+edi*2]                                              
	mov    ecx,DWORD PTR [esp+0x1c]                                     
	mov    edx,0x8                                                      
	neg    eax                                                          
	mov    esi,DWORD PTR [esp+0x28]                                     
	mov    ebx,edi                                                      
	add    eax,0x1                                                      
	shl    eax,0x4                                                      
	mov    DWORD PTR [esp],eax                                          
	mov    eax,DWORD PTR [esp+0x28]                                     
	sar    ebx,0x4                                                      
	imul   eax,edi                                                      
	sub    edx,eax                                                      
	mov    eax,ebp                                                      
	mov    ebp,edx                                                      
	nop                                                                 
	lea    esi,[esi+0x0]                                          
avg_h264_qpel8or16_hv_lowpass_mmx2_4ce38:                            
	mov    edx,edi                                                      
avg_h264_qpel8or16_hv_lowpass_mmx2_4ce3a:                            
	movq   mm0,QWORD PTR [eax]                                          
	movq   mm3,QWORD PTR [eax+0x8]                                      
	movq   mm1,QWORD PTR [eax+0x2]                                      
	movq   mm4,QWORD PTR [eax+0xa]                                      
	paddw  mm0,mm4                                                      
	paddw  mm1,mm3                                                      
	paddw  mm3,QWORD PTR [eax+0x12]                                     
	paddw  mm4,QWORD PTR [eax+0x10]                                     
	movq   mm2,QWORD PTR [eax+0x4]                                      
	movq   mm5,QWORD PTR [eax+0xc]                                      
	paddw  mm2,QWORD PTR [eax+0x6]                                      
	paddw  mm5,QWORD PTR [eax+0xe]                                      
	psubw  mm0,mm1                                                      
	psubw  mm3,mm4                                                      
	psraw  mm0,0x2                                                      
	psraw  mm3,0x2                                                      
	psubw  mm0,mm1                                                      
	psubw  mm3,mm4                                                      
	paddsw mm0,mm2                                                      
	paddsw mm3,mm5                                                      
	psraw  mm0,0x2                                                      
	psraw  mm3,0x2                                                      
	paddw  mm0,mm2                                                      
	paddw  mm3,mm5                                                      
	psraw  mm0,0x6                                                      
	psraw  mm3,0x6                                                      
	packuswb mm0,mm3                                                    
	movq   mm7,QWORD PTR [ecx]                                          
	pavgb  mm0,mm7                                                      
	movq   QWORD PTR [ecx],mm0                                          
	add    eax,0x30                                                     
	add    ecx,esi                                                      
	dec    edx                                                          
	jne    avg_h264_qpel8or16_hv_lowpass_mmx2_4ce3a                     
	sub    ebx,0x1                                                      
	add    ecx,ebp                                                      
	add    eax,DWORD PTR [esp]                                          
	cmp    ebx,0xffffffff                                               
	jne    avg_h264_qpel8or16_hv_lowpass_mmx2_4ce38                     
	add    esp,0x8                                                      
	pop    ebx                                                          
	pop    esi                                                          
	pop    edi                                                          
	pop    ebp                                                          
	ret                                                                
	}
}
void avg_h264_qpel8_hv_lowpass_mmx2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	avg_h264_qpel8or16_hv_lowpass_mmx2(dst , tmp , src , dstStride, tmpStride, srcStride, 8);
}
void avg_h264_qpel16_hv_lowpass_mmx2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{ 
	avg_h264_qpel8or16_hv_lowpass_mmx2(dst , tmp , src , dstStride, tmpStride, srcStride, 16);
}
void __declspec(naked) avg_pixels4_l2_shift5_mmx2(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
	__asm{
	sub    esp,0x8                    
	mov    DWORD PTR [esp],esi        
	mov    edx,DWORD PTR [esp+0xc]    
	mov    DWORD PTR [esp+0x4],edi    
	mov    ecx,DWORD PTR [esp+0x10]   
	mov    eax,DWORD PTR [esp+0x14]   
	mov    esi,DWORD PTR [esp+0x1c]   
	mov    edi,DWORD PTR [esp+0x18]   
	movq   mm0,QWORD PTR [ecx]        
	movq   mm1,QWORD PTR [ecx+0x18]   
	psraw  mm0,0x5                    
	psraw  mm1,0x5                    
	packuswb mm0,mm0                  
	packuswb mm1,mm1                  
	pavgb  mm0,QWORD PTR [eax]        
	pavgb  mm1,QWORD PTR [eax+esi*1]  
	movd   mm4,DWORD PTR [edx]        
	pavgb  mm0,mm4                    
	movd   DWORD PTR [edx],mm0        
	movd   mm5,DWORD PTR [edx+edi*1]  
	pavgb  mm1,mm5                    
	movd   DWORD PTR [edx+edi*1],mm1  
	lea    eax,[eax+esi*2]            
	lea    edx,[edx+edi*2]            
	movq   mm0,QWORD PTR [ecx+0x30]   
	movq   mm1,QWORD PTR [ecx+0x48]   
	psraw  mm0,0x5                    
	psraw  mm1,0x5                    
	packuswb mm0,mm0                  
	packuswb mm1,mm1                  
	pavgb  mm0,QWORD PTR [eax]        
	pavgb  mm1,QWORD PTR [eax+esi*1]  
	movd   mm4,DWORD PTR [edx]        
	pavgb  mm0,mm4                    
	movd   DWORD PTR [edx],mm0        
	movd   mm5,DWORD PTR [edx+edi*1]  
	pavgb  mm1,mm5                    
	movd   DWORD PTR [edx+edi*1],mm1  
	mov    esi,DWORD PTR [esp]        
	mov    edi,DWORD PTR [esp+0x4]    
	add    esp,0x8                    
	ret
	}
}
void __declspec(naked) avg_pixels8_l2_shift5_mmx2(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
	__asm{
	sub    esp,0x14                                 
	mov    DWORD PTR [esp+0xc],edi                  
	mov    edi,DWORD PTR [esp+0x24]                 
	mov    DWORD PTR [esp+0x8],esi                  
	mov    esi,DWORD PTR [esp+0x28]                 
	mov    DWORD PTR [esp+0x4],ebx                  
	mov    edx,DWORD PTR [esp+0x18]                 
	mov    ecx,DWORD PTR [esp+0x1c]                 
	lea    eax,[edi+edi*1]                          
	mov    ebx,DWORD PTR [esp+0x2c]                 
	mov    DWORD PTR [esp],eax                      
	mov    eax,DWORD PTR [esp+0x20]                 
	mov    DWORD PTR [esp+0x10],ebp                 
	lea    ebp,[esi+esi*1]                          
	lea    esi,[esi+0x0]                      
avg_pixels8_l2_shift5_mmx2loop:                  
	movq   mm0,QWORD PTR [ecx]                      
	movq   mm1,QWORD PTR [ecx+0x8]                  
	movq   mm2,QWORD PTR [ecx+0x30]                 
	movq   mm3,QWORD PTR [ecx+0x38]                 
	psraw  mm0,0x5                                  
	psraw  mm1,0x5                                  
	psraw  mm2,0x5                                  
	psraw  mm3,0x5                                  
	packuswb mm0,mm1                                
	packuswb mm2,mm3                                
	pavgb  mm0,QWORD PTR [eax]                      
	pavgb  mm2,QWORD PTR [eax+esi*1]                
	movq   mm5,QWORD PTR [edx]                      
	pavgb  mm0,mm5                                  
	movq   QWORD PTR [edx],mm0                      
	movq   mm5,QWORD PTR [edx+edi*1]                
	pavgb  mm2,mm5                                  
	movq   QWORD PTR [edx+edi*1],mm2                
	add    eax,ebp                                  
	add    ecx,0x60                                 
	add    edx,DWORD PTR [esp]                      
	sub    ebx,0x2                                  
	jne    avg_pixels8_l2_shift5_mmx2loop           
	mov    ebx,DWORD PTR [esp+0x4]                  
	mov    esi,DWORD PTR [esp+0x8]                  
	mov    edi,DWORD PTR [esp+0xc]                  
	mov    ebp,DWORD PTR [esp+0x10]                 
	add    esp,0x14                                 
	ret                                             
	}
}

void __declspec(naked) avg_h264_qpel8or16_v_lowpass_sse2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
	__asm{
	sub    esp,0x8                                            
	mov    DWORD PTR [esp],esi                                
	mov    esi,DWORD PTR [esp+0x18]                           
	mov    DWORD PTR [esp+0x4],edi                            
	mov    ecx,DWORD PTR [esp+0xc]                            
	mov    edi,DWORD PTR [esp+0x14]                           
	lea    eax,[esi+esi*1]                                    
	neg    eax                                                
	add    eax,DWORD PTR [esp+0x10]                           
	pxor   xmm7,xmm7                                          
	movq   xmm0,QWORD PTR [eax]                               
	add    eax,esi                                            
	movq   xmm1,QWORD PTR [eax]                               
	add    eax,esi                                            
	movq   xmm2,QWORD PTR [eax]                               
	add    eax,esi                                            
	movq   xmm3,QWORD PTR [eax]                               
	add    eax,esi                                            
	movq   xmm4,QWORD PTR [eax]                               
	add    eax,esi                                            
	punpcklbw xmm0,xmm7                                       
	punpcklbw xmm1,xmm7                                       
	punpcklbw xmm2,xmm7                                       
	punpcklbw xmm3,xmm7                                       
	punpcklbw xmm4,xmm7                                       
	movdqa xmm6,xmm2                                          
	movq   xmm5,QWORD PTR [eax]                               
	paddw  xmm6,xmm3                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm1                                          
	psubw  xmm6,xmm4                                          
	punpcklbw xmm5,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm0,xmm5                                          
	paddw  xmm6,xmm0                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm0,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm0                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm3                                          
	movq   xmm0,QWORD PTR [eax]                               
	paddw  xmm6,xmm4                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm2                                          
	psubw  xmm6,xmm5                                          
	punpcklbw xmm0,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm1,xmm0                                          
	paddw  xmm6,xmm1                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm1,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm1                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm4                                          
	movq   xmm1,QWORD PTR [eax]                               
	paddw  xmm6,xmm5                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm3                                          
	psubw  xmm6,xmm0                                          
	punpcklbw xmm1,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm2,xmm1                                          
	paddw  xmm6,xmm2                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm2,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm2                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm5                                          
	movq   xmm2,QWORD PTR [eax]                               
	paddw  xmm6,xmm0                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm4                                          
	psubw  xmm6,xmm1                                          
	punpcklbw xmm2,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm3,xmm2                                          
	paddw  xmm6,xmm3                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm3,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm3                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm0                                          
	movq   xmm3,QWORD PTR [eax]                               
	paddw  xmm6,xmm1                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm5                                          
	psubw  xmm6,xmm2                                          
	punpcklbw xmm3,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm4,xmm3                                          
	paddw  xmm6,xmm4                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm4,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm4                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm1                                          
	movq   xmm4,QWORD PTR [eax]                               
	paddw  xmm6,xmm2                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm0                                          
	psubw  xmm6,xmm3                                          
	punpcklbw xmm4,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm5,xmm4                                          
	paddw  xmm6,xmm5                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm5,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm5                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm2                                          
	movq   xmm5,QWORD PTR [eax]                               
	paddw  xmm6,xmm3                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm1                                          
	psubw  xmm6,xmm4                                          
	punpcklbw xmm5,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm0,xmm5                                          
	paddw  xmm6,xmm0                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm0,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm0                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm3                                          
	movq   xmm0,QWORD PTR [eax]                               
	paddw  xmm6,xmm4                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm2                                          
	psubw  xmm6,xmm5                                          
	punpcklbw xmm0,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm1,xmm0                                          
	paddw  xmm6,xmm1                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm1,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm1                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	cmp    DWORD PTR [esp+0x1c],0x10                          
	jne    avg_h264_qpel8or16_v_lowpass_sse2end               
	movdqa xmm6,xmm4                                          
	movq   xmm1,QWORD PTR [eax]                               
	paddw  xmm6,xmm5                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm3                                          
	psubw  xmm6,xmm0                                          
	punpcklbw xmm1,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm2,xmm1                                          
	paddw  xmm6,xmm2                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm2,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm2                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm5                                          
	movq   xmm2,QWORD PTR [eax]                               
	paddw  xmm6,xmm0                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm4                                          
	psubw  xmm6,xmm1                                          
	punpcklbw xmm2,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm3,xmm2                                          
	paddw  xmm6,xmm3                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm3,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm3                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm0                                          
	movq   xmm3,QWORD PTR [eax]                               
	paddw  xmm6,xmm1                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm5                                          
	psubw  xmm6,xmm2                                          
	punpcklbw xmm3,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm4,xmm3                                          
	paddw  xmm6,xmm4                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm4,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm4                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm1                                          
	movq   xmm4,QWORD PTR [eax]                               
	paddw  xmm6,xmm2                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm0                                          
	psubw  xmm6,xmm3                                          
	punpcklbw xmm4,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm5,xmm4                                          
	paddw  xmm6,xmm5                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm5,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm5                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm2                                          
	movq   xmm5,QWORD PTR [eax]                               
	paddw  xmm6,xmm3                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm1                                          
	psubw  xmm6,xmm4                                          
	punpcklbw xmm5,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm0,xmm5                                          
	paddw  xmm6,xmm0                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm0,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm0                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm3                                          
	movq   xmm0,QWORD PTR [eax]                               
	paddw  xmm6,xmm4                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm2                                          
	psubw  xmm6,xmm5                                          
	punpcklbw xmm0,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm1,xmm0                                          
	paddw  xmm6,xmm1                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm1,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm1                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm4                                          
	movq   xmm1,QWORD PTR [eax]                               
	paddw  xmm6,xmm5                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm3                                          
	psubw  xmm6,xmm0                                          
	punpcklbw xmm1,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm2,xmm1                                          
	paddw  xmm6,xmm2                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm2,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm2                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
	movdqa xmm6,xmm5                                          
	movq   xmm2,QWORD PTR [eax]                               
	paddw  xmm6,xmm0                                          
	psllw  xmm6,0x2                                           
	psubw  xmm6,xmm4                                          
	psubw  xmm6,xmm1                                          
	punpcklbw xmm2,xmm7                                       
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                            
                                                           
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                           
                                                           
	add    eax,esi                                            
	paddw  xmm3,xmm2                                          
	paddw  xmm6,xmm3                                          
	psraw  xmm6,0x5                                           
	packuswb xmm6,xmm6                                        
	movq   xmm3,QWORD PTR [ecx]                               
	pavgb  xmm6,xmm3                                          
	movq   QWORD PTR [ecx],xmm6                               
	add    ecx,edi                                            
avg_h264_qpel8or16_v_lowpass_sse2end:                      
	mov    esi,DWORD PTR [esp]                                
	mov    edi,DWORD PTR [esp+0x4]                            
	add    esp,0x8                                            
	ret                                                       
	}
}
void avg_h264_qpel8_v_lowpass_sse2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	avg_h264_qpel8or16_v_lowpass_sse2(dst , src , dstStride, srcStride, 8);
}
void avg_h264_qpel16_v_lowpass_sse2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	avg_h264_qpel8or16_v_lowpass_sse2(dst , src , dstStride, srcStride, 16); 
	avg_h264_qpel8or16_v_lowpass_sse2(dst+8, src+8, dstStride, srcStride, 16);
}
void __declspec(naked) avg_h264_qpel8or16_hv_lowpass_sse2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride, int size)
{
	__asm{
	push   ebp                                                          
	push   edi                                                          
	push   esi                                                          
	push   ebx                                                          
	sub    esp,0x8                                                      
	mov    edi,DWORD PTR [esp+0x34]                                     
	mov    ebp,DWORD PTR [esp+0x20]                                     
	mov    esi,DWORD PTR [esp+0x30]                                     
	lea    ebx,[edi+0x8]                                                
	sar    ebx,0x3                                                      
	test   ebx,ebx                                                      
	je     avg_h264_qpel8or16_hv_lowpass_sse2_50301                     
	mov    eax,DWORD PTR [esp+0x24]                                     
	mov    edx,esi                                                      
	mov    ecx,ebp                                                      
	not    edx                                                          
	mov    DWORD PTR [esp+0x4],ebp                                      
	lea    eax,[eax+edx*2]                                              
	mov    edx,0xfffffffb                                               
	sub    edx,edi                                                      
	imul   edx,esi                                                      
	add    edx,0x8                                                      
	mov    DWORD PTR [esp],edx                                          
	mov    ebp,DWORD PTR [esp]                                          
	xor    edx,edx                                                      
	nop                                                                 
avg_h264_qpel8or16_hv_lowpass_sse2_4fec8:                            
	pxor   xmm7,xmm7                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm1,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm2,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm3,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm4,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	punpcklbw xmm0,xmm7                                                 
	punpcklbw xmm1,xmm7                                                 
	punpcklbw xmm2,xmm7                                                 
	punpcklbw xmm3,xmm7                                                 
	punpcklbw xmm4,xmm7                                                 
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx],xmm6                                       
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x30],xmm6                                  
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x60],xmm6                                  
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x90],xmm6                                  
                                                                     
	movdqa xmm6,xmm0                                                    
	movq   xmm3,QWORD PTR [eax]                                         
	paddw  xmm6,xmm1                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm5                                                    
	psubw  xmm6,xmm2                                                    
	punpcklbw xmm3,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm4,xmm3                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm4                                                    
	movdqa XMMWORD PTR [ecx+0xc0],xmm6                                  
                                                                     
	movdqa xmm6,xmm1                                                    
	movq   xmm4,QWORD PTR [eax]                                         
	paddw  xmm6,xmm2                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm0                                                    
	psubw  xmm6,xmm3                                                    
	punpcklbw xmm4,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm5,xmm4                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm5                                                    
	movdqa XMMWORD PTR [ecx+0xf0],xmm6                                  
                                                                     
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx+0x120],xmm6                                 
                                                                     
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x150],xmm6                                 
                                                                     
	cmp    edi,0x10                                                     
	jne    avg_h264_qpel8or16_hv_lowpass_sse2_502ed                     
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x180],xmm6                                 
                                                                     
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x1b0],xmm6                                 
                                                                     
	movdqa xmm6,xmm0                                                    
	movq   xmm3,QWORD PTR [eax]                                         
	paddw  xmm6,xmm1                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm5                                                    
	psubw  xmm6,xmm2                                                    
	punpcklbw xmm3,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm4,xmm3                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm4                                                    
	movdqa XMMWORD PTR [ecx+0x1e0],xmm6                                 
                                                                     
	movdqa xmm6,xmm1                                                    
	movq   xmm4,QWORD PTR [eax]                                         
	paddw  xmm6,xmm2                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm0                                                    
	psubw  xmm6,xmm3                                                    
	punpcklbw xmm4,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm5,xmm4                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm5                                                    
	movdqa XMMWORD PTR [ecx+0x210],xmm6                                 
                                                                     
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx+0x240],xmm6                                 
                                                                     
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x270],xmm6                                 
                                                                     
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x2a0],xmm6                                 
                                                                     
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x2d0],xmm6                                 
                                                                     
avg_h264_qpel8or16_hv_lowpass_sse2_502ed:                            
	add    edx,0x1                                                      
	add    ecx,0x10                                                     
	add    eax,ebp                                                      
	cmp    edx,ebx                                                      
	jne    avg_h264_qpel8or16_hv_lowpass_sse2_4fec8                     
	mov    ebp,DWORD PTR [esp+0x4]                                      
avg_h264_qpel8or16_hv_lowpass_sse2_50301:                            
	lea    eax,[edi+edi*2]                                              
	mov    ecx,DWORD PTR [esp+0x1c]                                     
	mov    edx,0x8                                                      
	neg    eax                                                          
	mov    esi,DWORD PTR [esp+0x28]                                     
	mov    ebx,edi                                                      
	add    eax,0x1                                                      
	shl    eax,0x4                                                      
	mov    DWORD PTR [esp],eax                                          
	mov    eax,DWORD PTR [esp+0x28]                                     
	sar    ebx,0x4                                                      
	imul   eax,edi                                                      
	sub    edx,eax                                                      
	mov    eax,ebp                                                      
	mov    ebp,edx                                                      
	xchg   ax,ax                                                        
avg_h264_qpel8or16_hv_lowpass_sse2_50330:                            
	mov    edx,edi                                                      
avg_h264_qpel8or16_hv_lowpass_sse2_50332:                            
	movq   mm0,QWORD PTR [eax]                                          
	movq   mm3,QWORD PTR [eax+0x8]                                      
	movq   mm1,QWORD PTR [eax+0x2]                                      
	movq   mm4,QWORD PTR [eax+0xa]                                      
	paddw  mm0,mm4                                                      
	paddw  mm1,mm3                                                      
	paddw  mm3,QWORD PTR [eax+0x12]                                     
	paddw  mm4,QWORD PTR [eax+0x10]                                     
	movq   mm2,QWORD PTR [eax+0x4]                                      
	movq   mm5,QWORD PTR [eax+0xc]                                      
	paddw  mm2,QWORD PTR [eax+0x6]                                      
	paddw  mm5,QWORD PTR [eax+0xe]                                      
	psubw  mm0,mm1                                                      
	psubw  mm3,mm4                                                      
	psraw  mm0,0x2                                                      
	psraw  mm3,0x2                                                      
	psubw  mm0,mm1                                                      
	psubw  mm3,mm4                                                      
	paddsw mm0,mm2                                                      
	paddsw mm3,mm5                                                      
	psraw  mm0,0x2                                                      
	psraw  mm3,0x2                                                      
	paddw  mm0,mm2                                                      
	paddw  mm3,mm5                                                      
	psraw  mm0,0x6                                                      
	psraw  mm3,0x6                                                      
	packuswb mm0,mm3                                                    
	movq   mm7,QWORD PTR [ecx]                                          
	pavgb  mm0,mm7                                                      
	movq   QWORD PTR [ecx],mm0                                          
	add    eax,0x30                                                     
	add    ecx,esi                                                      
	dec    edx                                                          
	jne    avg_h264_qpel8or16_hv_lowpass_sse2_50332                     
	sub    ebx,0x1                                                      
	add    ecx,ebp                                                      
	add    eax,DWORD PTR [esp]                                          
	cmp    ebx,0xffffffff                                               
	jne    avg_h264_qpel8or16_hv_lowpass_sse2_50330                     
	add    esp,0x8                                                      
	pop    ebx                                                          
	pop    esi                                                          
	pop    edi                                                          
	pop    ebp                                                          
	ret                                                                 
	}
}
void avg_h264_qpel8_hv_lowpass_sse2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
	avg_h264_qpel8or16_hv_lowpass_sse2(dst, tmp, src, dstStride, tmpStride, srcStride, 8);
}
void avg_h264_qpel16_hv_lowpass_sse2(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{ 
	avg_h264_qpel8or16_hv_lowpass_sse2(dst, tmp, src, dstStride, tmpStride, srcStride, 16);
}

void __declspec(naked) avg_h264_qpel8_h_lowpass_l2_ssse3(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0xc                               
	mov    DWORD PTR [esp],ebx                   
	mov    ecx,DWORD PTR [esp+0x10]              
	mov    ebx,0x8                               
	mov    DWORD PTR [esp+0x4],esi               
	mov    eax,DWORD PTR [esp+0x14]              
	mov    DWORD PTR [esp+0x8],edi               
	mov    edx,DWORD PTR [esp+0x18]              
	mov    edi,DWORD PTR [esp+0x20]              
	mov    esi,DWORD PTR [esp+0x1c]              
	pxor   xmm7,xmm7                             
	movdqa xmm6,XMMWORD PTR [ff_pw_5]             
                                              
avg_h264_qpel8_h_lowpass_l2_ssse3flag:        
	lddqu  xmm1,[eax-0x2]                        
	movdqa xmm0,xmm1                             
	punpckhbw xmm1,xmm7                          
	punpcklbw xmm0,xmm7                          
	movdqa xmm2,xmm1                             
	movdqa xmm3,xmm1                             
	movdqa xmm4,xmm1                             
	movdqa xmm5,xmm1                             
	palignr xmm4,xmm0,0x2                        
	palignr xmm3,xmm0,0x4                        
	palignr xmm2,xmm0,0x6                        
	palignr xmm1,xmm0,0x8                        
	palignr xmm5,xmm0,0xa                        
	paddw  xmm0,xmm5                             
	paddw  xmm2,xmm3                             
	paddw  xmm1,xmm4                             
	psllw  xmm2,0x2                              
	movq   xmm3,QWORD PTR [edx]                  
	psubw  xmm2,xmm1                             
	paddw  xmm0,XMMWORD PTR [ff_pw_16]             
                                              
	pmullw xmm2,xmm6                             
	paddw  xmm2,xmm0                             
	psraw  xmm2,0x5                              
	packuswb xmm2,xmm2                           
	pavgb  xmm2,xmm3                             
	movq   xmm4,QWORD PTR [ecx]                  
	pavgb  xmm2,xmm4                             
	movq   QWORD PTR [ecx],xmm2                  
	add    eax,esi                               
	add    ecx,esi                               
	add    edx,edi                               
	dec    ebx                                   
	jg     avg_h264_qpel8_h_lowpass_l2_ssse3flag 
	mov    ebx,DWORD PTR [esp]                   
	mov    esi,DWORD PTR [esp+0x4]               
	mov    edi,DWORD PTR [esp+0x8]               
	add    esp,0xc                               
	ret                                          
	}
}
void __declspec(naked) avg_h264_qpel16_h_lowpass_l2_ssse3(uint8_t *dst, uint8_t *src, uint8_t *src2, int dstStride, int src2Stride)
{
	__asm{
	sub    esp,0x1c                                           
	mov    DWORD PTR [esp+0x18],ebp                           
	mov    ebp,DWORD PTR [esp+0x24]                           
	mov    DWORD PTR [esp+0xc],ebx                            
	mov    ecx,DWORD PTR [esp+0x20]                           
	mov    ebx,0x8                                            
	mov    DWORD PTR [esp+0x10],esi                           
	mov    edx,DWORD PTR [esp+0x28]                           
	mov    DWORD PTR [esp+0x14],edi                           
	mov    esi,DWORD PTR [esp+0x2c]                           
	mov    edi,DWORD PTR [esp+0x30]                           
	mov    eax,ebp                                            
	pxor   xmm7,xmm7                                          
	movdqa xmm6,XMMWORD PTR [ff_pw_5]                           
                                                           
avg_h264_qpel16_h_lowpass_l2_ssse3_50baa:                  
	lddqu  xmm1,[eax-0x2]                                     
	movdqa xmm0,xmm1                                          
	punpckhbw xmm1,xmm7                                       
	punpcklbw xmm0,xmm7                                       
	movdqa xmm2,xmm1                                          
	movdqa xmm3,xmm1                                          
	movdqa xmm4,xmm1                                          
	movdqa xmm5,xmm1                                          
	palignr xmm4,xmm0,0x2                                     
	palignr xmm3,xmm0,0x4                                     
	palignr xmm2,xmm0,0x6                                     
	palignr xmm1,xmm0,0x8                                     
	palignr xmm5,xmm0,0xa                                     
	paddw  xmm0,xmm5                                          
	paddw  xmm2,xmm3                                          
	paddw  xmm1,xmm4                                          
	psllw  xmm2,0x2                                           
	movq   xmm3,QWORD PTR [edx]                               
	psubw  xmm2,xmm1                                          
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                            
                                                           
	pmullw xmm2,xmm6                                          
	paddw  xmm2,xmm0                                          
	psraw  xmm2,0x5                                           
	packuswb xmm2,xmm2                                        
	pavgb  xmm2,xmm3                                          
	movq   xmm4,QWORD PTR [ecx]                               
	pavgb  xmm2,xmm4                                          
	movq   QWORD PTR [ecx],xmm2                               
	add    eax,esi                                            
	add    ecx,esi                                            
	add    edx,edi                                            
	dec    ebx                                                
	jg     avg_h264_qpel16_h_lowpass_l2_ssse3_50baa           
	mov    ecx,DWORD PTR [esp+0x20]                           
	lea    eax,[ebp+0x8]                                      
	mov    ebx,0x8                                            
	mov    edx,DWORD PTR [esp+0x28]                           
	add    ecx,0x8                                            
	add    edx,0x8                                            
	pxor   xmm7,xmm7                                          
	movdqa xmm6,XMMWORD PTR [ff_pw_5]                      
                                                           
avg_h264_qpel16_h_lowpass_l2_ssse3_50c5a:                  
	lddqu  xmm1,[eax-0x2]                                     
	movdqa xmm0,xmm1                                          
	punpckhbw xmm1,xmm7                                       
	punpcklbw xmm0,xmm7                                       
	movdqa xmm2,xmm1                                          
	movdqa xmm3,xmm1                                          
	movdqa xmm4,xmm1                                          
	movdqa xmm5,xmm1                                          
	palignr xmm4,xmm0,0x2                                     
	palignr xmm3,xmm0,0x4                                     
	palignr xmm2,xmm0,0x6                                     
	palignr xmm1,xmm0,0x8                                     
	palignr xmm5,xmm0,0xa                                     
	paddw  xmm0,xmm5                                          
	paddw  xmm2,xmm3                                          
	paddw  xmm1,xmm4                                          
	psllw  xmm2,0x2                                           
	movq   xmm3,QWORD PTR [edx]                               
	psubw  xmm2,xmm1                                          
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                            
                                                           
	pmullw xmm2,xmm6                                          
	paddw  xmm2,xmm0                                          
	psraw  xmm2,0x5                                           
	packuswb xmm2,xmm2                                        
	pavgb  xmm2,xmm3                                          
	movq   xmm4,QWORD PTR [ecx]                               
	pavgb  xmm2,xmm4                                          
	movq   QWORD PTR [ecx],xmm2                               
	add    eax,esi                                            
	add    ecx,esi                                            
	add    edx,edi                                            
	dec    ebx                                                
	jg     avg_h264_qpel16_h_lowpass_l2_ssse3_50c5a           
	mov    eax,DWORD PTR [esp+0x28]                           
	lea    ecx,[esi*8+0x0]                                    
	add    ebp,ecx                                            
	add    ecx,DWORD PTR [esp+0x20]                           
	mov    DWORD PTR [esp],ebp                                
	lea    ebx,[eax+edi*8]                                    
	mov    eax,ebp                                            
	mov    DWORD PTR [esp+0x4],ecx                            
	mov    edx,ebx                                            
	mov    ebp,0x8                                            
	pxor   xmm7,xmm7                                          
	movdqa xmm6,XMMWORD PTR [ff_pw_5]                       
                                                           
avg_h264_qpel16_h_lowpass_l2_ssse3_50d18:                  
	lddqu  xmm1,[eax-0x2]                                     
	movdqa xmm0,xmm1                                          
	punpckhbw xmm1,xmm7                                       
	punpcklbw xmm0,xmm7                                       
	movdqa xmm2,xmm1                                          
	movdqa xmm3,xmm1                                          
	movdqa xmm4,xmm1                                          
	movdqa xmm5,xmm1                                          
	palignr xmm4,xmm0,0x2                                     
	palignr xmm3,xmm0,0x4                                     
	palignr xmm2,xmm0,0x6                                     
	palignr xmm1,xmm0,0x8                                     
	palignr xmm5,xmm0,0xa                                     
	paddw  xmm0,xmm5                                          
	paddw  xmm2,xmm3                                          
	paddw  xmm1,xmm4                                          
	psllw  xmm2,0x2                                           
	movq   xmm3,QWORD PTR [edx]                               
	psubw  xmm2,xmm1                                          
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                            
                                                           
	pmullw xmm2,xmm6                                          
	paddw  xmm2,xmm0                                          
	psraw  xmm2,0x5                                           
	packuswb xmm2,xmm2                                        
	pavgb  xmm2,xmm3                                          
	movq   xmm4,QWORD PTR [ecx]                               
	pavgb  xmm2,xmm4                                          
	movq   QWORD PTR [ecx],xmm2                               
	add    eax,esi                                            
	add    ecx,esi                                            
	add    edx,edi                                            
	dec    ebp                                                
	jg     avg_h264_qpel16_h_lowpass_l2_ssse3_50d18           
	mov    eax,DWORD PTR [esp]                                
	lea    edx,[ebx+0x8]                                      
	mov    ebx,0x8                                            
	mov    ecx,DWORD PTR [esp+0x4]                            
	add    eax,0x8                                            
	add    ecx,0x8                                            
	pxor   xmm7,xmm7                                          
	movdqa xmm6,XMMWORD PTR [ff_pw_5]                     
                                                           
avg_h264_qpel16_h_lowpass_l2_ssse3_50dc7:                  
	lddqu  xmm1,[eax-0x2]                                     
	movdqa xmm0,xmm1                                          
	punpckhbw xmm1,xmm7                                       
	punpcklbw xmm0,xmm7                                       
	movdqa xmm2,xmm1                                          
	movdqa xmm3,xmm1                                          
	movdqa xmm4,xmm1                                          
	movdqa xmm5,xmm1                                          
	palignr xmm4,xmm0,0x2                                     
	palignr xmm3,xmm0,0x4                                     
	palignr xmm2,xmm0,0x6                                     
	palignr xmm1,xmm0,0x8                                     
	palignr xmm5,xmm0,0xa                                     
	paddw  xmm0,xmm5                                          
	paddw  xmm2,xmm3                                          
	paddw  xmm1,xmm4                                          
	psllw  xmm2,0x2                                           
	movq   xmm3,QWORD PTR [edx]                               
	psubw  xmm2,xmm1                                          
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                            
                                                           
	pmullw xmm2,xmm6                                          
	paddw  xmm2,xmm0                                          
	psraw  xmm2,0x5                                           
	packuswb xmm2,xmm2                                        
	pavgb  xmm2,xmm3                                          
	movq   xmm4,QWORD PTR [ecx]                               
	pavgb  xmm2,xmm4                                          
	movq   QWORD PTR [ecx],xmm2                               
	add    eax,esi                                            
	add    ecx,esi                                            
	add    edx,edi                                            
	dec    ebx                                                
	jg     avg_h264_qpel16_h_lowpass_l2_ssse3_50dc7           
	mov    ebx,DWORD PTR [esp+0xc]                            
	mov    esi,DWORD PTR [esp+0x10]                           
	mov    edi,DWORD PTR [esp+0x14]                           
	mov    ebp,DWORD PTR [esp+0x18]                           
	add    esp,0x1c                                           
	ret
	}
}
void __declspec(naked) avg_h264_qpel8_h_lowpass_ssse3(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
	__asm{
	sub    esp,0x8                                 
	mov    edx,0x8                                 
	mov    DWORD PTR [esp],esi                     
	mov    ecx,DWORD PTR [esp+0xc]                 
	mov    DWORD PTR [esp+0x4],edi                 
	mov    eax,DWORD PTR [esp+0x10]                
	mov    edi,DWORD PTR [esp+0x18]                
	mov    esi,DWORD PTR [esp+0x14]                
	pxor   xmm7,xmm7                               
	movdqa xmm6,XMMWORD PTR [ff_pw_5]                 
                                                
avg_h264_qpel8_h_lowpass_ssse3flag:             
	lddqu  xmm1,[eax-0x2]                          
	movdqa xmm0,xmm1                               
	punpckhbw xmm1,xmm7                            
	punpcklbw xmm0,xmm7                            
	movdqa xmm2,xmm1                               
	movdqa xmm3,xmm1                               
	movdqa xmm4,xmm1                               
	movdqa xmm5,xmm1                               
	palignr xmm4,xmm0,0x2                          
	palignr xmm3,xmm0,0x4                          
	palignr xmm2,xmm0,0x6                          
	palignr xmm1,xmm0,0x8                          
	palignr xmm5,xmm0,0xa                          
	paddw  xmm0,xmm5                               
	paddw  xmm2,xmm3                               
	paddw  xmm1,xmm4                               
	psllw  xmm2,0x2                                
	psubw  xmm2,xmm1                               
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                
                                                
	pmullw xmm2,xmm6                               
	paddw  xmm2,xmm0                               
	psraw  xmm2,0x5                                
	packuswb xmm2,xmm2                             
	movq   xmm4,QWORD PTR [ecx]                    
	pavgb  xmm2,xmm4                               
	movq   QWORD PTR [ecx],xmm2                    
	add    eax,edi                                 
	add    ecx,esi                                 
	dec    edx                                     
	jne    avg_h264_qpel8_h_lowpass_ssse3flag      
	mov    esi,DWORD PTR [esp]                     
	mov    edi,DWORD PTR [esp+0x4]                 
	add    esp,0x8                                 
	ret                                            
	}
}

void __declspec(naked) avg_h264_qpel8or16_hv_lowpass_ssse3(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride, int size)
{
	__asm{	
	push   ebp                                                          
	push   edi                                                          
	push   esi                                                          
	push   ebx                                                          
	mov    edi,DWORD PTR [esp+0x2c]                                     
	mov    esi,DWORD PTR [esp+0x28]                                     
	lea    ebx,[edi+0x8]                                                
	sar    ebx,0x3                                                      
	test   ebx,ebx                                                      
	je     avg_h264_qpel8or16_hv_lowpass_ssse3_535cd                    
	mov    ebp,0xfffffffb                                               
	mov    eax,DWORD PTR [esp+0x1c]                                     
	mov    edx,esi                                                      
	sub    ebp,edi                                                      
	mov    ecx,DWORD PTR [esp+0x18]                                     
	not    edx                                                          
	imul   ebp,esi                                                      
	lea    eax,[eax+edx*2]                                              
	xor    edx,edx                                                      
	add    ebp,0x8                                                      
avg_h264_qpel8or16_hv_lowpass_ssse3_53198:                           
	pxor   xmm7,xmm7                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm1,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm2,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm3,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	movq   xmm4,QWORD PTR [eax]                                         
	add    eax,esi                                                      
	punpcklbw xmm0,xmm7                                                 
	punpcklbw xmm1,xmm7                                                 
	punpcklbw xmm2,xmm7                                                 
	punpcklbw xmm3,xmm7                                                 
	punpcklbw xmm4,xmm7                                                 
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx],xmm6                                       
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x30],xmm6                                  
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x60],xmm6                                  
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x90],xmm6                                  
                                                                     
	movdqa xmm6,xmm0                                                    
	movq   xmm3,QWORD PTR [eax]                                         
	paddw  xmm6,xmm1                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm5                                                    
	psubw  xmm6,xmm2                                                    
	punpcklbw xmm3,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm4,xmm3                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm4                                                    
	movdqa XMMWORD PTR [ecx+0xc0],xmm6                                  
                                                                     
	movdqa xmm6,xmm1                                                    
	movq   xmm4,QWORD PTR [eax]                                         
	paddw  xmm6,xmm2                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm0                                                    
	psubw  xmm6,xmm3                                                    
	punpcklbw xmm4,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm5,xmm4                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm5                                                    
	movdqa XMMWORD PTR [ecx+0xf0],xmm6                                  
                                                                     
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx+0x120],xmm6                                 
                                                                     
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x150],xmm6                                 
                                                                     
	cmp    edi,0x10                                                     
	jne    avg_h264_qpel8or16_hv_lowpass_ssse3_535bd                    
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x180],xmm6                                 
                                                                     
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x1b0],xmm6                                 
                                                                     
	movdqa xmm6,xmm0                                                    
	movq   xmm3,QWORD PTR [eax]                                         
	paddw  xmm6,xmm1                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm4,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm5                                                    
	psubw  xmm6,xmm2                                                    
	punpcklbw xmm3,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm4,xmm3                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm4                                                    
	movdqa XMMWORD PTR [ecx+0x1e0],xmm6                                 
                                                                     
	movdqa xmm6,xmm1                                                    
	movq   xmm4,QWORD PTR [eax]                                         
	paddw  xmm6,xmm2                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm5,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm0                                                    
	psubw  xmm6,xmm3                                                    
	punpcklbw xmm4,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm5,xmm4                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm5                                                    
	movdqa XMMWORD PTR [ecx+0x210],xmm6                                 
                                                                     
	movdqa xmm6,xmm2                                                    
	movq   xmm5,QWORD PTR [eax]                                         
	paddw  xmm6,xmm3                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm0,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm1                                                    
	psubw  xmm6,xmm4                                                    
	punpcklbw xmm5,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm0,xmm5                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm0                                                    
	movdqa XMMWORD PTR [ecx+0x240],xmm6                                 
                                                                     
	movdqa xmm6,xmm3                                                    
	movq   xmm0,QWORD PTR [eax]                                         
	paddw  xmm6,xmm4                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm1,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm2                                                    
	psubw  xmm6,xmm5                                                    
	punpcklbw xmm0,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm1,xmm0                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm1                                                    
	movdqa XMMWORD PTR [ecx+0x270],xmm6                                 
                                                                     
	movdqa xmm6,xmm4                                                    
	movq   xmm1,QWORD PTR [eax]                                         
	paddw  xmm6,xmm5                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm2,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm3                                                    
	psubw  xmm6,xmm0                                                    
	punpcklbw xmm1,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm2,xmm1                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm2                                                    
	movdqa XMMWORD PTR [ecx+0x2a0],xmm6                                 
                                                                     
	movdqa xmm6,xmm5                                                    
	movq   xmm2,QWORD PTR [eax]                                         
	paddw  xmm6,xmm0                                                    
	psllw  xmm6,0x2                                                     
	paddw  xmm3,XMMWORD PTR [ff_pw_16]                                      
                                                                     
	psubw  xmm6,xmm4                                                    
	psubw  xmm6,xmm1                                                    
	punpcklbw xmm2,xmm7                                                 
	pmullw xmm6,XMMWORD PTR [ff_pw_5]                                      
                                                                     
	paddw  xmm3,xmm2                                                    
	add    eax,esi                                                      
	paddw  xmm6,xmm3                                                    
	movdqa XMMWORD PTR [ecx+0x2d0],xmm6                                 
                                                                     
avg_h264_qpel8or16_hv_lowpass_ssse3_535bd:                           
	add    edx,0x1                                                      
	add    ecx,0x10                                                     
	add    eax,ebp                                                      
	cmp    edx,ebx                                                      
	jne    avg_h264_qpel8or16_hv_lowpass_ssse3_53198                    
avg_h264_qpel8or16_hv_lowpass_ssse3_535cd:                           
	cmp    edi,0x10                                                     
	je     avg_h264_qpel8or16_hv_lowpass_ssse3_53668                    
	mov    eax,DWORD PTR [esp+0x18]                                     
	mov    ecx,DWORD PTR [esp+0x14]                                     
	mov    esi,DWORD PTR [esp+0x20]                                     
avg_h264_qpel8or16_hv_lowpass_ssse3_535e2:                           
	movdqa xmm1,XMMWORD PTR [eax+0x10]                                  
	movdqa xmm0,XMMWORD PTR [eax]                                       
	movdqa xmm2,xmm1                                                    
	movdqa xmm3,xmm1                                                    
	movdqa xmm4,xmm1                                                    
	movdqa xmm5,xmm1                                                    
	palignr xmm5,xmm0,0xa                                               
	palignr xmm4,xmm0,0x8                                               
	palignr xmm3,xmm0,0x6                                               
	palignr xmm2,xmm0,0x4                                               
	palignr xmm1,xmm0,0x2                                               
	paddw  xmm0,xmm5                                                    
	paddw  xmm1,xmm4                                                    
	paddw  xmm2,xmm3                                                    
	psubw  xmm0,xmm1                                                    
	psraw  xmm0,0x2                                                     
	psubw  xmm0,xmm1                                                    
	paddw  xmm0,xmm2                                                    
	psraw  xmm0,0x2                                                     
	paddw  xmm0,xmm2                                                    
	psraw  xmm0,0x6                                                     
	packuswb xmm0,xmm0                                                  
	movq   xmm7,QWORD PTR [ecx]                                         
	pavgb  xmm0,xmm7                                                    
	movq   QWORD PTR [ecx],xmm0                                         
	add    eax,0x30                                                     
	add    ecx,esi                                                      
	dec    edi                                                          
	jne    avg_h264_qpel8or16_hv_lowpass_ssse3_535e2                    
	pop    ebx                                                          
	pop    esi                                                          
	pop    edi                                                          
	pop    ebp                                                          
	ret                                                                 
	lea    esi,[esi+0x0]                                          
avg_h264_qpel8or16_hv_lowpass_ssse3_53668:                           
	mov    eax,DWORD PTR [esp+0x18]                                     
	mov    edx,0x10                                                     
	mov    ecx,DWORD PTR [esp+0x14]                                     
	mov    esi,DWORD PTR [esp+0x20]                                     
avg_h264_qpel8or16_hv_lowpass_ssse3_53679:                           
	movdqa xmm4,XMMWORD PTR [eax+0x20]                                  
	movdqa xmm5,XMMWORD PTR [eax+0x10]                                  
	movdqa xmm7,XMMWORD PTR [eax]                                       
	movdqa xmm3,xmm4                                                    
	movdqa xmm2,xmm4                                                    
	movdqa xmm1,xmm4                                                    
	movdqa xmm0,xmm4                                                    
	palignr xmm0,xmm5,0xa                                               
	palignr xmm1,xmm5,0x8                                               
	palignr xmm2,xmm5,0x6                                               
	palignr xmm3,xmm5,0x4                                               
	palignr xmm4,xmm5,0x2                                               
	paddw  xmm0,xmm5                                                    
	paddw  xmm1,xmm4                                                    
	paddw  xmm2,xmm3                                                    
	movdqa xmm6,xmm5                                                    
	movdqa xmm4,xmm5                                                    
	movdqa xmm3,xmm5                                                    
	palignr xmm4,xmm7,0x8                                               
	palignr xmm6,xmm7,0x2                                               
	palignr xmm3,xmm7,0xa                                               
	paddw  xmm4,xmm6                                                    
	movdqa xmm6,xmm5                                                    
	palignr xmm5,xmm7,0x6                                               
	palignr xmm6,xmm7,0x4                                               
	paddw  xmm3,xmm7                                                    
	paddw  xmm5,xmm6                                                    
	psubw  xmm0,xmm1                                                    
	psubw  xmm3,xmm4                                                    
	psraw  xmm0,0x2                                                     
	psraw  xmm3,0x2                                                     
	psubw  xmm0,xmm1                                                    
	psubw  xmm3,xmm4                                                    
	paddw  xmm0,xmm2                                                    
	paddw  xmm3,xmm5                                                    
	psraw  xmm0,0x2                                                     
	psraw  xmm3,0x2                                                     
	paddw  xmm0,xmm2                                                    
	paddw  xmm3,xmm5                                                    
	psraw  xmm0,0x6                                                     
	psraw  xmm3,0x6                                                     
	packuswb xmm3,xmm0                                                  
	movdqa xmm7,XMMWORD PTR [ecx]                                       
	pavgb  xmm3,xmm7                                                    
	movdqa XMMWORD PTR [ecx],xmm3                                       
	add    eax,0x30                                                     
	add    ecx,esi                                                      
	dec    edx                                                          
	jne    avg_h264_qpel8or16_hv_lowpass_ssse3_53679                    
	pop    ebx                                                          
	pop    esi                                                          
	pop    edi                                                          
	pop    ebp                                                          
	ret                                                                 
	}
}

void avg_h264_qpel8_hv_lowpass_ssse3(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
    avg_h264_qpel8or16_hv_lowpass_ssse3(dst, tmp, src, dstStride, tmpStride, srcStride, 8);
}
void avg_h264_qpel16_hv_lowpass_ssse3(uint8_t *dst, int16_t *tmp, uint8_t *src, int dstStride, int tmpStride, int srcStride)
{
    avg_h264_qpel8or16_hv_lowpass_ssse3(dst, tmp, src, dstStride, tmpStride, srcStride, 16);
}

void avg_h264_qpel16_h_lowpass_ssse3(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{ 
	avg_h264_qpel8_h_lowpass_ssse3(dst , src , dstStride, srcStride);
	avg_h264_qpel8_h_lowpass_ssse3(dst+8, src+8, dstStride, srcStride);
	src += 8*srcStride;
	dst += 8*dstStride;
	avg_h264_qpel8_h_lowpass_ssse3(dst , src , dstStride, srcStride);
	avg_h264_qpel8_h_lowpass_ssse3(dst+8, src+8, dstStride, srcStride);
}




#define avg_h264_qpel8_h_lowpass_l2_sse2 avg_h264_qpel8_h_lowpass_l2_mmx2
#define avg_h264_qpel16_h_lowpass_l2_sse2 avg_h264_qpel16_h_lowpass_l2_mmx2
#define avg_h264_qpel8_v_lowpass_ssse3 avg_h264_qpel8_v_lowpass_sse2
#define avg_h264_qpel16_v_lowpass_ssse3 avg_h264_qpel16_v_lowpass_sse2
#define avg_h264_qpel8or16_hv2_lowpass_sse2 avg_h264_qpel8or16_hv2_lowpass_mmx2
#define avg_h264_qpel8_mc00_sse2 avg_h264_qpel8_mc00_mmx2


void avg_h264_qpel4_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src, 4, stride); 
     avg_pixels4_l2_3dnow(dst, src, temp, stride, stride, 4);
 }
 void avg_h264_qpel4_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel4_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void avg_h264_qpel4_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src, 4, stride); 
     avg_pixels4_l2_3dnow(dst, src+stride, temp, stride, stride, 4);
 }
 void avg_h264_qpel4_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel4_h_lowpass_l2_3dnow(dst, src, src, stride, stride);
 }
 void avg_h264_qpel4_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel4_h_lowpass_3dnow(dst, src, stride, stride);
 }
 void avg_h264_qpel4_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel4_h_lowpass_l2_3dnow(dst, src, src+1, stride, stride);
 }
 void avg_h264_qpel4_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src, 4, stride); 
     avg_h264_qpel4_h_lowpass_l2_3dnow(dst, src, temp, stride, 4);
 }
 void avg_h264_qpel4_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src+1, 4, stride); 
     avg_h264_qpel4_h_lowpass_l2_3dnow(dst, src, temp, stride, 4);
 }
 void avg_h264_qpel4_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src, 4, stride); 
     avg_h264_qpel4_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 4);
 }
 void avg_h264_qpel4_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
     put_h264_qpel4_v_lowpass_3dnow(temp, src+1, 4, stride); 
     avg_h264_qpel4_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 4);
 }
 void avg_h264_qpel4_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint16_t, temp)[4*(4<8?12:24)]; 
     avg_h264_qpel4_hv_lowpass_3dnow(dst, temp, src, stride, 4, stride);
 }
 void avg_h264_qpel4_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0);
     put_h264_qpel4_hv_lowpass_3dnow(halfHV, halfV, src, 4, 4, stride); 
     avg_h264_qpel4_h_lowpass_l2_3dnow(dst, src, halfHV, stride, 4);
 }
 void avg_h264_qpel4_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_3dnow(halfHV, halfV, src, 4, 4, stride);
     avg_h264_qpel4_h_lowpass_l2_3dnow(dst, src+stride, halfHV, stride, 4);
 }
 void avg_h264_qpel4_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_3dnow(halfHV, halfV, src, 4, 4, stride); 
     avg_pixels4_l2_shift5_3dnow(dst, halfV+2, halfHV, stride, 4, 4);
 }
 void avg_h264_qpel4_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 4*4); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel4_hv_lowpass_3dnow(halfHV, halfV, src, 4, 4, stride); 
     avg_pixels4_l2_shift5_3dnow(dst, halfV+3, halfHV, stride, 4, 4);
 }
 void avg_h264_qpel8_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src, 8, stride); 
     avg_pixels8_l2_3dnow(dst, src, temp, stride, stride, 8);
 }
 void avg_h264_qpel8_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel8_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void avg_h264_qpel8_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src, 8, stride); 
     avg_pixels8_l2_3dnow(dst, src+stride, temp, stride, stride, 8);
 }
 void avg_h264_qpel8_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel8_h_lowpass_l2_3dnow(dst, src, src, stride, stride);
 }
 void avg_h264_qpel8_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel8_h_lowpass_3dnow(dst, src, stride, stride);
 }
 void avg_h264_qpel8_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel8_h_lowpass_l2_3dnow(dst, src, src+1, stride, stride);
 }
 void avg_h264_qpel8_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src, 8, stride); 
     avg_h264_qpel8_h_lowpass_l2_3dnow(dst, src, temp, stride, 8);
 }
 void avg_h264_qpel8_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src+1, 8, stride);
     avg_h264_qpel8_h_lowpass_l2_3dnow(dst, src, temp, stride, 8);
 }
 void avg_h264_qpel8_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8];
     put_h264_qpel8_v_lowpass_3dnow(temp, src, 8, stride); 
     avg_h264_qpel8_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 8);
 }
 void avg_h264_qpel8_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
     put_h264_qpel8_v_lowpass_3dnow(temp, src+1, 8, stride); 
     avg_h264_qpel8_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 8);
 }
 void avg_h264_qpel8_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint16_t, temp)[8*(8<8?12:24)]; 
     avg_h264_qpel8_hv_lowpass_3dnow(dst, temp, src, stride, 8, stride);
 }
 void avg_h264_qpel8_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel8_hv_lowpass_3dnow(halfHV, halfV, src, 8, 8, stride); 
     avg_h264_qpel8_h_lowpass_l2_3dnow(dst, src, halfHV, stride, 8);
 }
 void avg_h264_qpel8_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel8_hv_lowpass_3dnow(halfHV, halfV, src, 8, 8, stride); 
     avg_h264_qpel8_h_lowpass_l2_3dnow(dst, src+stride, halfHV, stride, 8);
 }
 void avg_h264_qpel8_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0);
     put_h264_qpel8_hv_lowpass_3dnow(halfHV, halfV, src, 8, 8, stride); 
     avg_pixels8_l2_shift5_3dnow(dst, halfV+2, halfHV, stride, 8, 8);
 }
 void avg_h264_qpel8_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 8*8); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel8_hv_lowpass_3dnow(halfHV, halfV, src, 8, 8, stride); 
     avg_pixels8_l2_shift5_3dnow(dst, halfV+3, halfHV, stride, 8, 8);
 }
 void avg_h264_qpel16_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src, 16, stride); 
     avg_pixels16_l2_3dnow(dst, src, temp, stride, stride, 16);
 }
 void avg_h264_qpel16_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel16_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void avg_h264_qpel16_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src, 16, stride); 
     avg_pixels16_l2_3dnow(dst, src+stride, temp, stride, stride, 16);
 }
 void avg_h264_qpel16_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel16_h_lowpass_l2_3dnow(dst, src, src, stride, stride);
 }
 void avg_h264_qpel16_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel16_h_lowpass_3dnow(dst, src, stride, stride);
 }
 void avg_h264_qpel16_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     avg_h264_qpel16_h_lowpass_l2_3dnow(dst, src, src+1, stride, stride);
 }
 void avg_h264_qpel16_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src, 16, stride); 
     avg_h264_qpel16_h_lowpass_l2_3dnow(dst, src, temp, stride, 16);
 }
 void avg_h264_qpel16_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src+1, 16, stride); 
     avg_h264_qpel16_h_lowpass_l2_3dnow(dst, src, temp, stride, 16);
 }
 void avg_h264_qpel16_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src, 16, stride); 
     avg_h264_qpel16_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 16);
 }
 void avg_h264_qpel16_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*16]; 
     put_h264_qpel16_v_lowpass_3dnow(temp, src+1, 16, stride); 
     avg_h264_qpel16_h_lowpass_l2_3dnow(dst, src+stride, temp, stride, 16);
 }
 void avg_h264_qpel16_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint16_t, temp)[16*(16<8?12:24)]; 
     avg_h264_qpel16_hv_lowpass_3dnow(dst, temp, src, stride, 16, stride);
 }
 void avg_h264_qpel16_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 16*16); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel16_hv_lowpass_3dnow(halfHV, halfV, src, 16, 16, stride); 
     avg_h264_qpel16_h_lowpass_l2_3dnow(dst, src, halfHV, stride, 16);
 }
 void avg_h264_qpel16_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride){
     DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 16*16);
     assert(((int)temp & 7) == 0);
     put_h264_qpel16_hv_lowpass_3dnow(halfHV, halfV, src, 16, 16, stride);
     avg_h264_qpel16_h_lowpass_l2_3dnow(dst, src+stride, halfHV, stride, 16);
 }
 void avg_h264_qpel16_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 16*16);
     assert(((int)temp & 7) == 0); 
     put_h264_qpel16_hv_lowpass_3dnow(halfHV, halfV, src, 16, 16, stride); 
     avg_pixels16_l2_shift5_3dnow(dst, halfV+2, halfHV, stride, 16, 16);
 }
 void avg_h264_qpel16_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride){ 
     DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
     uint8_t * const halfHV= temp; 
     int16_t * const halfV= (int16_t*)(temp + 16*16); 
     assert(((int)temp & 7) == 0); 
     put_h264_qpel16_hv_lowpass_3dnow(halfHV, halfV, src, 16, 16, stride);
     avg_pixels16_l2_shift5_3dnow(dst, halfV+3, halfHV, stride, 16, 16);
 }
 void avg_h264_qpel4_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*4];
	 put_h264_qpel4_v_lowpass_mmx2(temp, src, 4, stride); 
	 avg_pixels4_l2_mmx2(dst, src, temp, stride, stride, 4);
 }
 void avg_h264_qpel4_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel4_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void avg_h264_qpel4_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*4];
	 put_h264_qpel4_v_lowpass_mmx2(temp, src, 4, stride);
	 avg_pixels4_l2_mmx2(dst, src+stride, temp, stride, stride, 4);
 }
 void avg_h264_qpel4_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel4_h_lowpass_l2_mmx2(dst, src, src, stride, stride);
 }
 void avg_h264_qpel4_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel4_h_lowpass_mmx2(dst, src, stride, stride);
 }
 void avg_h264_qpel4_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel4_h_lowpass_l2_mmx2(dst, src, src+1, stride, stride);
 }
 void avg_h264_qpel4_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
	 put_h264_qpel4_v_lowpass_mmx2(temp, src, 4, stride);
	 avg_h264_qpel4_h_lowpass_l2_mmx2(dst, src, temp, stride, 4);
 }
 void avg_h264_qpel4_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*4];
	 put_h264_qpel4_v_lowpass_mmx2(temp, src+1, 4, stride); 
	 avg_h264_qpel4_h_lowpass_l2_mmx2(dst, src, temp, stride, 4);
 }
 void avg_h264_qpel4_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*4]; 
	 put_h264_qpel4_v_lowpass_mmx2(temp, src, 4, stride);
	 avg_h264_qpel4_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 4);
 }
 void avg_h264_qpel4_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*4];
	 put_h264_qpel4_v_lowpass_mmx2(temp, src+1, 4, stride);
	 avg_h264_qpel4_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 4);
 }
 void avg_h264_qpel4_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint16_t, temp)[4*(4<8?12:24)];
	 avg_h264_qpel4_hv_lowpass_mmx2(dst, temp, src, stride, 4, stride);
 }
 void avg_h264_qpel4_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 4*4);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel4_hv_lowpass_mmx2(halfHV, halfV, src, 4, 4, stride);
	 avg_h264_qpel4_h_lowpass_l2_mmx2(dst, src, halfHV, stride, 4);
 }
 void avg_h264_qpel4_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 4*4); 
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel4_hv_lowpass_mmx2(halfHV, halfV, src, 4, 4, stride); 
	 avg_h264_qpel4_h_lowpass_l2_mmx2(dst, src+stride, halfHV, stride, 4);
 }
 void avg_h264_qpel4_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 4*4);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel4_hv_lowpass_mmx2(halfHV, halfV, src, 4, 4, stride);
	 avg_pixels4_l2_shift5_mmx2(dst, halfV+2, halfHV, stride, 4, 4);
 }
 void avg_h264_qpel4_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[4*(4<8?12:24)*2 + 4*4]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 4*4);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel4_hv_lowpass_mmx2(halfHV, halfV, src, 4, 4, stride);
	 avg_pixels4_l2_shift5_mmx2(dst, halfV+3, halfHV, stride, 4, 4);
 }
 void avg_h264_qpel8_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_mmx2(temp, src, 8, stride); 
	 avg_pixels8_l2_mmx2(dst, src, temp, stride, stride, 8);
 }
 void avg_h264_qpel8_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel8_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void avg_h264_qpel8_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_mmx2(temp, src, 8, stride);
	 avg_pixels8_l2_mmx2(dst, src+stride, temp, stride, stride, 8);
 }
 void avg_h264_qpel8_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel8_h_lowpass_l2_mmx2(dst, src, src, stride, stride);
 }
 void avg_h264_qpel8_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel8_h_lowpass_mmx2(dst, src, stride, stride);
 }
 void avg_h264_qpel8_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel8_h_lowpass_l2_mmx2(dst, src, src+1, stride, stride);
 }
 void avg_h264_qpel8_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_mmx2(temp, src, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_mmx2(dst, src, temp, stride, 8);
 }
 void avg_h264_qpel8_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_mmx2(temp, src+1, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_mmx2(dst, src, temp, stride, 8);
 }
 void avg_h264_qpel8_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_mmx2(temp, src, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 8);
 }
 void avg_h264_qpel8_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_mmx2(temp, src+1, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 8);
 }
 void avg_h264_qpel8_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint16_t, temp)[8*(8<8?12:24)]; 
	 avg_h264_qpel8_hv_lowpass_mmx2(dst, temp, src, stride, 8, stride);
 }
 void avg_h264_qpel8_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_mmx2(halfHV, halfV, src, 8, 8, stride);
	 avg_h264_qpel8_h_lowpass_l2_mmx2(dst, src, halfHV, stride, 8);
 }
 void avg_h264_qpel8_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_mmx2(halfHV, halfV, src, 8, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_mmx2(dst, src+stride, halfHV, stride, 8);
 }
 void avg_h264_qpel8_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_mmx2(halfHV, halfV, src, 8, 8, stride);
	 avg_pixels8_l2_shift5_mmx2(dst, halfV+2, halfHV, stride, 8, 8);
 }
 void avg_h264_qpel8_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_mmx2(halfHV, halfV, src, 8, 8, stride); 
	 avg_pixels8_l2_shift5_mmx2(dst, halfV+3, halfHV, stride, 8, 8);
 }
 void avg_h264_qpel16_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src, 16, stride); 
	 avg_pixels16_l2_mmx2(dst, src, temp, stride, stride, 16);
 }
 void avg_h264_qpel16_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel16_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void avg_h264_qpel16_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src, 16, stride);
	 avg_pixels16_l2_mmx2(dst, src+stride, temp, stride, stride, 16);
 }
 void avg_h264_qpel16_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel16_h_lowpass_l2_mmx2(dst, src, src, stride, stride);
 }
 void avg_h264_qpel16_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel16_h_lowpass_mmx2(dst, src, stride, stride);
 }
 void avg_h264_qpel16_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel16_h_lowpass_l2_mmx2(dst, src, src+1, stride, stride);
 }
 void avg_h264_qpel16_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_mmx2(dst, src, temp, stride, 16);
 }
 void avg_h264_qpel16_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src+1, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_mmx2(dst, src, temp, stride, 16);
 }
 void avg_h264_qpel16_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src, 16, stride);
	 avg_h264_qpel16_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 16);
 }
 void avg_h264_qpel16_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_mmx2(temp, src+1, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_mmx2(dst, src+stride, temp, stride, 16);
 }
 void avg_h264_qpel16_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint16_t, temp)[16*(16<8?12:24)];
	 avg_h264_qpel16_hv_lowpass_mmx2(dst, temp, src, stride, 16, stride);
 }
 void avg_h264_qpel16_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_mmx2(halfHV, halfV, src, 16, 16, stride);
	 avg_h264_qpel16_h_lowpass_l2_mmx2(dst, src, halfHV, stride, 16);
 }
 void avg_h264_qpel16_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_mmx2(halfHV, halfV, src, 16, 16, stride);
	 avg_h264_qpel16_h_lowpass_l2_mmx2(dst, src+stride, halfHV, stride, 16);
 }
 void avg_h264_qpel16_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel16_hv_lowpass_mmx2(halfHV, halfV, src, 16, 16, stride);
	 avg_pixels16_l2_shift5_mmx2(dst, halfV+2, halfHV, stride, 16, 16);
 }
 void avg_h264_qpel16_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(8, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel16_hv_lowpass_mmx2(halfHV, halfV, src, 16, 16, stride); 
	 avg_pixels16_l2_shift5_mmx2(dst, halfV+3, halfHV, stride, 16, 16);
 }
 void avg_h264_qpel8_mc01_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_sse2(temp, src, 8, stride); 
	 avg_pixels8_l2_sse2(dst, src, temp, stride, stride, 8);
 }
 void avg_h264_qpel8_mc02_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel8_v_lowpass_sse2(dst, src, stride, stride);
 }
 void avg_h264_qpel8_mc03_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_sse2(temp, src, 8, stride);
	 avg_pixels8_l2_sse2(dst, src+stride, temp, stride, stride, 8);
 }
 void avg_h264_qpel16_mc01_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_sse2(temp, src, 16, stride);
	 avg_pixels16_l2_sse2(dst, src, temp, stride, stride, 16);
 }
 void avg_h264_qpel16_mc02_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel16_v_lowpass_sse2(dst, src, stride, stride);
 }
 void avg_h264_qpel16_mc03_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_sse2(temp, src, 16, stride); 
	 avg_pixels16_l2_sse2(dst, src+stride, temp, stride, stride, 16);
 }
 void avg_h264_qpel8_mc11_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_sse2(temp, src, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_sse2(dst, src, temp, stride, 8);
 }
 void avg_h264_qpel8_mc31_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_sse2(temp, src+1, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_sse2(dst, src, temp, stride, 8);
 }
 void avg_h264_qpel8_mc13_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8];
	 put_h264_qpel8_v_lowpass_sse2(temp, src, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_sse2(dst, src+stride, temp, stride, 8);
 }
 void avg_h264_qpel8_mc33_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_sse2(temp, src+1, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_sse2(dst, src+stride, temp, stride, 8);
 }
 void avg_h264_qpel8_mc22_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint16_t, temp)[8*(8<8?12:24)];
	 avg_h264_qpel8_hv_lowpass_sse2(dst, temp, src, stride, 8, stride);
 }
 void avg_h264_qpel8_mc21_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_sse2(halfHV, halfV, src, 8, 8, stride);
	 avg_h264_qpel8_h_lowpass_l2_sse2(dst, src, halfHV, stride, 8);
 }
 void avg_h264_qpel8_mc23_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_sse2(halfHV, halfV, src, 8, 8, stride);
	 avg_h264_qpel8_h_lowpass_l2_sse2(dst, src+stride, halfHV, stride, 8);
 }
 void avg_h264_qpel8_mc12_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_sse2(halfHV, halfV, src, 8, 8, stride); 
	 avg_pixels8_l2_shift5_sse2(dst, halfV+2, halfHV, stride, 8, 8);
 }
 void avg_h264_qpel8_mc32_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_sse2(halfHV, halfV, src, 8, 8, stride); 
	 avg_pixels8_l2_shift5_sse2(dst, halfV+3, halfHV, stride, 8, 8);
 }
 void avg_h264_qpel16_mc11_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_sse2(temp, src, 16, stride);
	 avg_h264_qpel16_h_lowpass_l2_sse2(dst, src, temp, stride, 16);
 }
 void avg_h264_qpel16_mc31_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_sse2(temp, src+1, 16, stride);
	 avg_h264_qpel16_h_lowpass_l2_sse2(dst, src, temp, stride, 16);
 }
 void avg_h264_qpel16_mc13_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_sse2(temp, src, 16, stride);
	 avg_h264_qpel16_h_lowpass_l2_sse2(dst, src+stride, temp, stride, 16);
 }
 void avg_h264_qpel16_mc33_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_sse2(temp, src+1, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_sse2(dst, src+stride, temp, stride, 16);
 }
 void avg_h264_qpel16_mc22_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint16_t, temp)[16*(16<8?12:24)]; 
	 avg_h264_qpel16_hv_lowpass_sse2(dst, temp, src, stride, 16, stride);
 }
 void avg_h264_qpel16_mc21_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 16*16); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_sse2(halfHV, halfV, src, 16, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_sse2(dst, src, halfHV, stride, 16);
 }
 void avg_h264_qpel16_mc23_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_sse2(halfHV, halfV, src, 16, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_sse2(dst, src+stride, halfHV, stride, 16);
 }
 void avg_h264_qpel16_mc12_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_sse2(halfHV, halfV, src, 16, 16, stride);
	 avg_pixels16_l2_shift5_sse2(dst, halfV+2, halfHV, stride, 16, 16);
 }
 void avg_h264_qpel16_mc32_sse2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 16*16); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_sse2(halfHV, halfV, src, 16, 16, stride); 
	 avg_pixels16_l2_shift5_sse2(dst, halfV+3, halfHV, stride, 16, 16);
 }
void avg_h264_qpel8_mc10_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel8_h_lowpass_l2_ssse3(dst, src, src, stride, stride);
 }
 void avg_h264_qpel8_mc20_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel8_h_lowpass_ssse3(dst, src, stride, stride);
 }
 void avg_h264_qpel8_mc30_ssse3(uint8_t *dst, uint8_t *src, int stride)
 {
	 avg_h264_qpel8_h_lowpass_l2_ssse3(dst, src, src+1, stride, stride);
 }
 void avg_h264_qpel16_mc10_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel16_h_lowpass_l2_ssse3(dst, src, src, stride, stride);
 }
 void avg_h264_qpel16_mc20_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel16_h_lowpass_ssse3(dst, src, stride, stride);
 }
 void avg_h264_qpel16_mc30_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_h264_qpel16_h_lowpass_l2_ssse3(dst, src, src+1, stride, stride);
 }
 void avg_h264_qpel8_mc11_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_ssse3(temp, src, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_ssse3(dst, src, temp, stride, 8);
 }
 void avg_h264_qpel8_mc31_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_ssse3(temp, src+1, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_ssse3(dst, src, temp, stride, 8);
 }
 void avg_h264_qpel8_mc13_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_ssse3(temp, src, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_ssse3(dst, src+stride, temp, stride, 8);
 }
 void avg_h264_qpel8_mc33_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*8]; 
	 put_h264_qpel8_v_lowpass_ssse3(temp, src+1, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_ssse3(dst, src+stride, temp, stride, 8);
 }
 void avg_h264_qpel8_mc22_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint16_t, temp)[8*(8<8?12:24)];
	 avg_h264_qpel8_hv_lowpass_ssse3(dst, temp, src, stride, 8, stride);
 }
 void avg_h264_qpel8_mc21_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_ssse3(halfHV, halfV, src, 8, 8, stride); 
	 avg_h264_qpel8_h_lowpass_l2_ssse3(dst, src, halfHV, stride, 8);
 }
 void avg_h264_qpel8_mc23_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8); 
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_ssse3(halfHV, halfV, src, 8, 8, stride);
	 avg_h264_qpel8_h_lowpass_l2_ssse3(dst, src+stride, halfHV, stride, 8);
 }
 void avg_h264_qpel8_mc12_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel8_hv_lowpass_ssse3(halfHV, halfV, src, 8, 8, stride);
	 avg_pixels8_l2_shift5_ssse3(dst, halfV+2, halfHV, stride, 8, 8);
 }
 void avg_h264_qpel8_mc32_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[8*(8<8?12:24)*2 + 8*8];
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 8*8);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel8_hv_lowpass_ssse3(halfHV, halfV, src, 8, 8, stride); 
	 avg_pixels8_l2_shift5_ssse3(dst, halfV+3, halfHV, stride, 8, 8);
 }
 void avg_h264_qpel16_mc11_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_ssse3(temp, src, 16, stride);
	 avg_h264_qpel16_h_lowpass_l2_ssse3(dst, src, temp, stride, 16);
 }
 void avg_h264_qpel16_mc31_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_ssse3(temp, src+1, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_ssse3(dst, src, temp, stride, 16);
 }
 void avg_h264_qpel16_mc13_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16];
	 put_h264_qpel16_v_lowpass_ssse3(temp, src, 16, stride);
	 avg_h264_qpel16_h_lowpass_l2_ssse3(dst, src+stride, temp, stride, 16);
 }
 void avg_h264_qpel16_mc33_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*16]; 
	 put_h264_qpel16_v_lowpass_ssse3(temp, src+1, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_ssse3(dst, src+stride, temp, stride, 16);
 }
 void avg_h264_qpel16_mc22_ssse3(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint16_t, temp)[16*(16<8?12:24)]; 
	 avg_h264_qpel16_hv_lowpass_ssse3(dst, temp, src, stride, 16, stride);
 }
 void avg_h264_qpel16_mc21_ssse3(uint8_t *dst, uint8_t *src, int stride)
 {
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_ssse3(halfHV, halfV, src, 16, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_ssse3(dst, src, halfHV, stride, 16);
 }
 void avg_h264_qpel16_mc23_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16]; 
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 16*16);
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_ssse3(halfHV, halfV, src, 16, 16, stride); 
	 avg_h264_qpel16_h_lowpass_l2_ssse3(dst, src+stride, halfHV, stride, 16);
 }
 void avg_h264_qpel16_mc12_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp; 
	 int16_t * const halfV= (int16_t*)(temp + 16*16); 
	 assert(((int)temp & 7) == 0);
	 put_h264_qpel16_hv_lowpass_ssse3(halfHV, halfV, src, 16, 16, stride); 
	 avg_pixels16_l2_shift5_ssse3(dst, halfV+2, halfHV, stride, 16, 16);
 }
 void avg_h264_qpel16_mc32_ssse3(uint8_t *dst, uint8_t *src, int stride)
 { 
	 DECLARE_ALIGNED(16, uint8_t, temp)[16*(16<8?12:24)*2 + 16*16];
	 uint8_t * const halfHV= temp;
	 int16_t * const halfV= (int16_t*)(temp + 16*16); 
	 assert(((int)temp & 7) == 0); 
	 put_h264_qpel16_hv_lowpass_ssse3(halfHV, halfV, src, 16, 16, stride); 
	 avg_pixels16_l2_shift5_ssse3(dst, halfV+3, halfHV, stride, 16, 16);
 }
 //--------------------------------------------------------------------------
 void __declspec(naked) avg_pixels4_l2_3dnow(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                                
	mov    DWORD PTR [esp],ebx                    
	mov    edx,DWORD PTR [esp+0x10]               
	mov    DWORD PTR [esp+0x4],esi                
	mov    eax,DWORD PTR [esp+0x14]               
	mov    DWORD PTR [esp+0x8],edi                
	mov    ecx,DWORD PTR [esp+0x18]               
	mov    ebx,DWORD PTR [esp+0x24]               
	mov    esi,DWORD PTR [esp+0x20]               
	mov    edi,DWORD PTR [esp+0x1c]               
	test   ebx,0x1                                
	je     avg_pixels4_l2_3dnowflag               
	movd   mm0,DWORD PTR [eax]                    
	movd   mm1,DWORD PTR [ecx]                    
	add    eax,esi                                
	add    ecx,0x4                                
	pavgusb mm0,mm1                               
	pavgusb mm0,QWORD PTR [edx]                   
	movd   DWORD PTR [edx],mm0                    
	add    edx,edi                                
	dec    ebx                                    
avg_pixels4_l2_3dnowflag:                      
	movd   mm0,DWORD PTR [eax]                    
	add    eax,esi                                
	movd   mm1,DWORD PTR [eax]                    
	add    eax,esi                                
	pavgusb mm0,QWORD PTR [ecx]                   
	pavgusb mm1,QWORD PTR [ecx+0x4]               
	pavgusb mm0,QWORD PTR [edx]                   
	movd   DWORD PTR [edx],mm0                    
	add    edx,edi                                
	pavgusb mm1,QWORD PTR [edx]                   
	movd   DWORD PTR [edx],mm1                    
	add    edx,edi                                
	movd   mm0,DWORD PTR [eax]                    
	add    eax,esi                                
	movd   mm1,DWORD PTR [eax]                    
	add    eax,esi                                
	pavgusb mm0,QWORD PTR [ecx+0x8]               
	pavgusb mm1,QWORD PTR [ecx+0xc]               
	pavgusb mm0,QWORD PTR [edx]                   
	movd   DWORD PTR [edx],mm0                    
	add    edx,edi                                
	pavgusb mm1,QWORD PTR [edx]                   
	movd   DWORD PTR [edx],mm1                    
	add    edx,edi                                
	add    ecx,0x10                               
	sub    ebx,0x4                                
	jne    avg_pixels4_l2_3dnowflag               
	mov    ebx,DWORD PTR [esp]                    
	mov    esi,DWORD PTR [esp+0x4]                
	mov    edi,DWORD PTR [esp+0x8]                
	add    esp,0xc                                
	ret                                           
	}
}
void __declspec(naked) avg_pixels8_l2_3dnow(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                           
	mov    DWORD PTR [esp],ebx               
	mov    edx,DWORD PTR [esp+0x10]          
	mov    DWORD PTR [esp+0x4],esi           
	mov    eax,DWORD PTR [esp+0x14]          
	mov    DWORD PTR [esp+0x8],edi           
	mov    ecx,DWORD PTR [esp+0x18]          
	mov    ebx,DWORD PTR [esp+0x24]          
	mov    esi,DWORD PTR [esp+0x20]          
	mov    edi,DWORD PTR [esp+0x1c]          
	test   ebx,0x1                           
	je     avg_pixels8_l2_3dnowflag          
	movq   mm0,QWORD PTR [eax]               
	movq   mm1,QWORD PTR [ecx]               
	add    eax,esi                           
	add    ecx,0x8                           
	pavgusb mm0,mm1                          
	pavgusb mm0,QWORD PTR [edx]              
	movq   QWORD PTR [edx],mm0               
	add    edx,edi                           
	dec    ebx                               
avg_pixels8_l2_3dnowflag:                 
	movq   mm0,QWORD PTR [eax]               
	add    eax,esi                           
	movq   mm1,QWORD PTR [eax]               
	add    eax,esi                           
	pavgusb mm0,QWORD PTR [ecx]              
	pavgusb mm1,QWORD PTR [ecx+0x8]          
	pavgusb mm0,QWORD PTR [edx]              
	movq   QWORD PTR [edx],mm0               
	add    edx,edi                           
	pavgusb mm1,QWORD PTR [edx]              
	movq   QWORD PTR [edx],mm1               
	add    edx,edi                           
	movq   mm0,QWORD PTR [eax]               
	add    eax,esi                           
	movq   mm1,QWORD PTR [eax]               
	add    eax,esi                           
	pavgusb mm0,QWORD PTR [ecx+0x10]         
	pavgusb mm1,QWORD PTR [ecx+0x18]         
	pavgusb mm0,QWORD PTR [edx]              
	movq   QWORD PTR [edx],mm0               
	add    edx,edi                           
	pavgusb mm1,QWORD PTR [edx]              
	movq   QWORD PTR [edx],mm1               
	add    edx,edi                           
	add    ecx,0x20                          
	sub    ebx,0x4                           
	jne    avg_pixels8_l2_3dnowflag          
	mov    ebx,DWORD PTR [esp]               
	mov    esi,DWORD PTR [esp+0x4]           
	mov    edi,DWORD PTR [esp+0x8]           
	add    esp,0xc                           
	ret                                      
	}
}
void __declspec(naked) avg_pixels16_l2_3dnow(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                        
	mov    DWORD PTR [esp],ebx            
	mov    edx,DWORD PTR [esp+0x10]       
	mov    DWORD PTR [esp+0x4],esi        
	mov    eax,DWORD PTR [esp+0x14]       
	mov    DWORD PTR [esp+0x8],edi        
	mov    ecx,DWORD PTR [esp+0x18]       
	mov    ebx,DWORD PTR [esp+0x24]       
	mov    esi,DWORD PTR [esp+0x20]       
	mov    edi,DWORD PTR [esp+0x1c]       
	test   ebx,0x1                        
	je     avg_pixels16_l2_3dnowflag      
	movq   mm0,QWORD PTR [eax]            
	movq   mm1,QWORD PTR [eax+0x8]        
	pavgusb mm0,QWORD PTR [ecx]           
	pavgusb mm1,QWORD PTR [ecx+0x8]       
	add    eax,esi                        
	add    ecx,0x10                       
	pavgusb mm0,QWORD PTR [edx]           
	pavgusb mm1,QWORD PTR [edx+0x8]       
	movq   QWORD PTR [edx],mm0            
	movq   QWORD PTR [edx+0x8],mm1        
	add    edx,edi                        
	dec    ebx                            
avg_pixels16_l2_3dnowflag:             
	movq   mm0,QWORD PTR [eax]            
	movq   mm1,QWORD PTR [eax+0x8]        
	add    eax,esi                        
	pavgusb mm0,QWORD PTR [ecx]           
	pavgusb mm1,QWORD PTR [ecx+0x8]       
	pavgusb mm0,QWORD PTR [edx]           
	pavgusb mm1,QWORD PTR [edx+0x8]       
	movq   QWORD PTR [edx],mm0            
	movq   QWORD PTR [edx+0x8],mm1        
	add    edx,edi                        
	movq   mm0,QWORD PTR [eax]            
	movq   mm1,QWORD PTR [eax+0x8]        
	add    eax,esi                        
	pavgusb mm0,QWORD PTR [ecx+0x10]      
	pavgusb mm1,QWORD PTR [ecx+0x18]      
	pavgusb mm0,QWORD PTR [edx]           
	pavgusb mm1,QWORD PTR [edx+0x8]       
	movq   QWORD PTR [edx],mm0            
	movq   QWORD PTR [edx+0x8],mm1        
	add    edx,edi                        
	add    ecx,0x20                       
	sub    ebx,0x2                        
	jne    avg_pixels16_l2_3dnowflag      
	mov    ebx,DWORD PTR [esp]            
	mov    esi,DWORD PTR [esp+0x4]        
	mov    edi,DWORD PTR [esp+0x8]        
	add    esp,0xc                        
	ret                                   
	}
}
void __declspec(naked) avg_pixels4_l2_mmx2(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                    
	mov    DWORD PTR [esp],ebx        
	mov    edx,DWORD PTR [esp+0x10]   
	mov    DWORD PTR [esp+0x4],esi    
	mov    eax,DWORD PTR [esp+0x14]   
	mov    DWORD PTR [esp+0x8],edi    
	mov    ecx,DWORD PTR [esp+0x18]   
	mov    ebx,DWORD PTR [esp+0x24]   
	mov    esi,DWORD PTR [esp+0x20]   
	mov    edi,DWORD PTR [esp+0x1c]   
	test   ebx,0x1                    
	je     avg_pixels4_l2_mmx2flag    
	movd   mm0,DWORD PTR [eax]        
	movd   mm1,DWORD PTR [ecx]        
	add    eax,esi                    
	add    ecx,0x4                    
	pavgb  mm0,mm1                    
	pavgb  mm0,QWORD PTR [edx]        
	movd   DWORD PTR [edx],mm0        
	add    edx,edi                    
	dec    ebx                        
avg_pixels4_l2_mmx2flag:           
	movd   mm0,DWORD PTR [eax]        
	add    eax,esi                    
	movd   mm1,DWORD PTR [eax]        
	add    eax,esi                    
	pavgb  mm0,QWORD PTR [ecx]        
	pavgb  mm1,QWORD PTR [ecx+0x4]    
	pavgb  mm0,QWORD PTR [edx]        
	movd   DWORD PTR [edx],mm0        
	add    edx,edi                    
	pavgb  mm1,QWORD PTR [edx]        
	movd   DWORD PTR [edx],mm1        
	add    edx,edi                    
	movd   mm0,DWORD PTR [eax]        
	add    eax,esi                    
	movd   mm1,DWORD PTR [eax]        
	add    eax,esi                    
	pavgb  mm0,QWORD PTR [ecx+0x8]    
	pavgb  mm1,QWORD PTR [ecx+0xc]    
	pavgb  mm0,QWORD PTR [edx]        
	movd   DWORD PTR [edx],mm0        
	add    edx,edi                    
	pavgb  mm1,QWORD PTR [edx]        
	movd   DWORD PTR [edx],mm1        
	add    edx,edi                    
	add    ecx,0x10                   
	sub    ebx,0x4                    
	jne    avg_pixels4_l2_mmx2flag    
	mov    ebx,DWORD PTR [esp]        
	mov    esi,DWORD PTR [esp+0x4]    
	mov    edi,DWORD PTR [esp+0x8]    
	add    esp,0xc                    
	ret
	}
}
void __declspec(naked) avg_pixels8_l2_mmx2(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                 
	mov    DWORD PTR [esp],ebx     
	mov    edx,DWORD PTR [esp+0x10]
	mov    DWORD PTR [esp+0x4],esi 
	mov    eax,DWORD PTR [esp+0x14]
	mov    DWORD PTR [esp+0x8],edi 
	mov    ecx,DWORD PTR [esp+0x18]
	mov    ebx,DWORD PTR [esp+0x24]
	mov    esi,DWORD PTR [esp+0x20]
	mov    edi,DWORD PTR [esp+0x1c]
	test   ebx,0x1                 
	je     avg_pixels8_l2_mmx2flag 
	movq   mm0,QWORD PTR [eax]     
	movq   mm1,QWORD PTR [ecx]     
	add    eax,esi                 
	add    ecx,0x8                 
	pavgb  mm0,mm1                 
	pavgb  mm0,QWORD PTR [edx]     
	movq   QWORD PTR [edx],mm0     
	add    edx,edi                 
	dec    ebx                     
avg_pixels8_l2_mmx2flag:        
	movq   mm0,QWORD PTR [eax]     
	add    eax,esi                 
	movq   mm1,QWORD PTR [eax]     
	add    eax,esi                 
	pavgb  mm0,QWORD PTR [ecx]     
	pavgb  mm1,QWORD PTR [ecx+0x8] 
	pavgb  mm0,QWORD PTR [edx]     
	movq   QWORD PTR [edx],mm0     
	add    edx,edi                 
	pavgb  mm1,QWORD PTR [edx]     
	movq   QWORD PTR [edx],mm1     
	add    edx,edi                 
	movq   mm0,QWORD PTR [eax]     
	add    eax,esi                 
	movq   mm1,QWORD PTR [eax]     
	add    eax,esi                 
	pavgb  mm0,QWORD PTR [ecx+0x10]
	pavgb  mm1,QWORD PTR [ecx+0x18]
	pavgb  mm0,QWORD PTR [edx]     
	movq   QWORD PTR [edx],mm0     
	add    edx,edi                 
	pavgb  mm1,QWORD PTR [edx]     
	movq   QWORD PTR [edx],mm1     
	add    edx,edi                 
	add    ecx,0x20                
	sub    ebx,0x4                 
	jne    avg_pixels8_l2_mmx2flag 
	mov    ebx,DWORD PTR [esp]     
	mov    esi,DWORD PTR [esp+0x4] 
	mov    edi,DWORD PTR [esp+0x8] 
	add    esp,0xc                 
	ret                            
	}
}
void __declspec(naked) avg_pixels16_l2_mmx2(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm{
	sub    esp,0xc                     
	mov    DWORD PTR [esp],ebx         
	mov    edx,DWORD PTR [esp+0x10]    
	mov    DWORD PTR [esp+0x4],esi     
	mov    eax,DWORD PTR [esp+0x14]    
	mov    DWORD PTR [esp+0x8],edi     
	mov    ecx,DWORD PTR [esp+0x18]    
	mov    ebx,DWORD PTR [esp+0x24]    
	mov    esi,DWORD PTR [esp+0x20]    
	mov    edi,DWORD PTR [esp+0x1c]    
	test   ebx,0x1                     
	je     avg_pixels16_l2_mmx2flag    
	movq   mm0,QWORD PTR [eax]         
	movq   mm1,QWORD PTR [eax+0x8]     
	pavgb  mm0,QWORD PTR [ecx]         
	pavgb  mm1,QWORD PTR [ecx+0x8]     
	add    eax,esi                     
	add    ecx,0x10                    
	pavgb  mm0,QWORD PTR [edx]         
	pavgb  mm1,QWORD PTR [edx+0x8]     
	movq   QWORD PTR [edx],mm0         
	movq   QWORD PTR [edx+0x8],mm1     
	add    edx,edi                     
	dec    ebx                         
avg_pixels16_l2_mmx2flag:           
	movq   mm0,QWORD PTR [eax]         
	movq   mm1,QWORD PTR [eax+0x8]     
	add    eax,esi                     
	pavgb  mm0,QWORD PTR [ecx]         
	pavgb  mm1,QWORD PTR [ecx+0x8]     
	pavgb  mm0,QWORD PTR [edx]         
	pavgb  mm1,QWORD PTR [edx+0x8]     
	movq   QWORD PTR [edx],mm0         
	movq   QWORD PTR [edx+0x8],mm1     
	add    edx,edi                     
	movq   mm0,QWORD PTR [eax]         
	movq   mm1,QWORD PTR [eax+0x8]     
	add    eax,esi                     
	pavgb  mm0,QWORD PTR [ecx+0x10]    
	pavgb  mm1,QWORD PTR [ecx+0x18]    
	pavgb  mm0,QWORD PTR [edx]         
	pavgb  mm1,QWORD PTR [edx+0x8]     
	movq   QWORD PTR [edx],mm0         
	movq   QWORD PTR [edx+0x8],mm1     
	add    edx,edi                     
	add    ecx,0x20                    
	sub    ebx,0x2                     
	jne    avg_pixels16_l2_mmx2flag    
	mov    ebx,DWORD PTR [esp]         
	mov    esi,DWORD PTR [esp+0x4]     
	mov    edi,DWORD PTR [esp+0x8]     
	add    esp,0xc                     
	ret                                
	}
}

#define avg_pixels8_l2_sse2 avg_pixels8_l2_mmx2
#define avg_pixels16_l2_sse2 avg_pixels16_l2_mmx2
#define avg_pixels8_l2_ssse3 avg_pixels8_l2_mmx2
#define avg_pixels16_l2_ssse3 avg_pixels16_l2_mmx2

#define avg_pixels8_l2_shift5_sse2 avg_pixels8_l2_shift5_mmx2
#define avg_pixels16_l2_shift5_sse2 avg_pixels16_l2_shift5_mmx2
#define avg_pixels8_l2_shift5_ssse3 avg_pixels8_l2_shift5_mmx2
#define avg_pixels16_l2_shift5_ssse3 avg_pixels16_l2_shift5_mmx2

void avg_pixels16_l2_shift5_mmx2(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
    avg_pixels8_l2_shift5_mmx2(dst  , src16  , src8  , dstStride, src8Stride, h);
    avg_pixels8_l2_shift5_mmx2(dst+8, src16+8, src8+8, dstStride, src8Stride, h);
}

void avg_pixels16_l2_shift5_3dnow(uint8_t *dst, int16_t *src16, uint8_t *src8, int dstStride, int src8Stride, int h)
{
    avg_pixels8_l2_shift5_3dnow(dst  , src16  , src8  , dstStride, src8Stride, h);
    avg_pixels8_l2_shift5_3dnow(dst+8, src16+8, src8+8, dstStride, src8Stride, h);
}


#endif