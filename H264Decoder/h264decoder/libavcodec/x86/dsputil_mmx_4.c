#include "x86_opt.h"
#include "dsputil_mmx.h"


//extern uint64_t ff_bone;

NAKED void put_pixels8_x2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                          
			mov    DWORD PTR [esp],esi              
			mov    ecx,DWORD PTR [esp+0x18]         
		mov    DWORD PTR [esp+0x4],edi          
			mov    esi,DWORD PTR [esp+0x10]         
		mov    edi,DWORD PTR [esp+0xc]          
		mov    edx,DWORD PTR [esp+0x14]         
		lea    eax,[edx+edx*1]                  
put_pixels8_x2_mmx2_2aad:
		movq   mm0,QWORD PTR [esi]              
		movq   mm1,QWORD PTR [esi+edx*1]        
		pavgb  mm0,QWORD PTR [esi+0x1]          
		pavgb  mm1,QWORD PTR [esi+edx*1+0x1]    
		movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			add    esi,eax                          
			add    edi,eax                          
			movq   mm0,QWORD PTR [esi]              
		movq   mm1,QWORD PTR [esi+edx*1]        
		pavgb  mm0,QWORD PTR [esi+0x1]          
		pavgb  mm1,QWORD PTR [esi+edx*1+0x1]    
		add    esi,eax                          
			movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			add    edi,eax                          
			sub    ecx,0x4                          
			jne    put_pixels8_x2_mmx2_2aad         
			mov    esi,DWORD PTR [esp]              
		mov    edi,DWORD PTR [esp+0x4]          
		add    esp,0x8                          
			ret                                     

	}
}


NAKED void put_no_rnd_pixels8_l2_mmx2(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm {
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
		pcmpeqb mm6,mm6                          
			test   ebx,0x1                           
			je     put_no_rnd_pixels8_l2_mmx2_3b6e   
			movq   mm0,QWORD PTR [eax]               
		movq   mm1,QWORD PTR [ecx]               
		add    eax,esi                           
			add    ecx,0x8                           
			pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			pavgb  mm0,mm1                           
			pxor   mm0,mm6                           
			movq   QWORD PTR [edx],mm0               
			add    edx,edi                           
			dec    ebx                               
put_no_rnd_pixels8_l2_mmx2_3b6e:         
		movq   mm0,QWORD PTR [eax]               
		add    eax,esi                           
			movq   mm1,QWORD PTR [eax]               
		add    eax,esi                           
			movq   mm2,QWORD PTR [ecx]               
		movq   mm3,QWORD PTR [ecx+0x8]           
		pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			pxor   mm2,mm6                           
			pxor   mm3,mm6                           
			pavgb  mm0,mm2                           
			pavgb  mm1,mm3                           
			pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			movq   QWORD PTR [edx],mm0               
			add    edx,edi                           
			movq   QWORD PTR [edx],mm1               
			add    edx,edi                           
			movq   mm0,QWORD PTR [eax]               
		add    eax,esi                           
			movq   mm1,QWORD PTR [eax]               
		add    eax,esi                           
			movq   mm2,QWORD PTR [ecx+0x10]          
		movq   mm3,QWORD PTR [ecx+0x18]          
		pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			pxor   mm2,mm6                           
			pxor   mm3,mm6                           
			pavgb  mm0,mm2                           
			pavgb  mm1,mm3                           
			pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			movq   QWORD PTR [edx],mm0               
			add    edx,edi                           
			movq   QWORD PTR [edx],mm1               
			add    edx,edi                           
			add    ecx,0x20                          
			sub    ebx,0x4                           
			jne    put_no_rnd_pixels8_l2_mmx2_3b6e   
			mov    ebx,DWORD PTR [esp]               
		mov    esi,DWORD PTR [esp+0x4]           
		mov    edi,DWORD PTR [esp+0x8]           
		add    esp,0xc                           
			ret                                      

	}	
}





NAKED void put_pixels16_x2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
    __asm {
		sub    esp,0x8                          
			mov    DWORD PTR [esp],esi              
			mov    ecx,DWORD PTR [esp+0x18]         
		mov    DWORD PTR [esp+0x4],edi          
			mov    esi,DWORD PTR [esp+0x10]         
		mov    edi,DWORD PTR [esp+0xc]          
		mov    edx,DWORD PTR [esp+0x14]         
		lea    eax,[edx+edx*1]                  
put_pixels16_x2_mmx2_2b1d:              
		movq   mm0,QWORD PTR [esi]              
		movq   mm1,QWORD PTR [esi+edx*1]        
		movq   mm2,QWORD PTR [esi+0x8]          
		movq   mm3,QWORD PTR [esi+edx*1+0x8]    
		pavgb  mm0,QWORD PTR [esi+0x1]          
		pavgb  mm1,QWORD PTR [esi+edx*1+0x1]    
		pavgb  mm2,QWORD PTR [esi+0x9]          
		pavgb  mm3,QWORD PTR [esi+edx*1+0x9]    
		movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			movq   QWORD PTR [edi+0x8],mm2          
			movq   QWORD PTR [edi+edx*1+0x8],mm3    
			add    esi,eax                          
			add    edi,eax                          
			movq   mm0,QWORD PTR [esi]              
		movq   mm1,QWORD PTR [esi+edx*1]        
		movq   mm2,QWORD PTR [esi+0x8]          
		movq   mm3,QWORD PTR [esi+edx*1+0x8]    
		pavgb  mm0,QWORD PTR [esi+0x1]          
		pavgb  mm1,QWORD PTR [esi+edx*1+0x1]    
		pavgb  mm2,QWORD PTR [esi+0x9]          
		pavgb  mm3,QWORD PTR [esi+edx*1+0x9]    
		add    esi,eax                          
			movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			movq   QWORD PTR [edi+0x8],mm2          
			movq   QWORD PTR [edi+edx*1+0x8],mm3    
			add    edi,eax                          
			sub    ecx,0x4                          
			jne    put_pixels16_x2_mmx2_2b1d        
			mov    esi,DWORD PTR [esp]              
		mov    edi,DWORD PTR [esp+0x4]          
		add    esp,0x8                          
			ret                                     

    }
	
}





NAKED void put_no_rnd_pixels16_l2_mmx2(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
{
	__asm {
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
		pcmpeqb mm6,mm6                         
			test   ebx,0x1                          
			je     put_no_rnd_pixels16_l2_mmx2_3f86 
			movq   mm0,QWORD PTR [eax]              
		movq   mm1,QWORD PTR [eax+0x8]          
		movq   mm2,QWORD PTR [ecx]              
		movq   mm3,QWORD PTR [ecx+0x8]          
		pxor   mm0,mm6                          
			pxor   mm1,mm6                          
			pxor   mm2,mm6                          
			pxor   mm3,mm6                          
			pavgb  mm0,mm2                          
			pavgb  mm1,mm3                          
			pxor   mm0,mm6                          
			pxor   mm1,mm6                          
			add    eax,esi                          
			add    ecx,0x10                         
			movq   QWORD PTR [edx],mm0              
			movq   QWORD PTR [edx+0x8],mm1          
			add    edx,edi                          
			dec    ebx                              
put_no_rnd_pixels16_l2_mmx2_3f86:       
		movq   mm0,QWORD PTR [eax]              
		movq   mm1,QWORD PTR [eax+0x8]          
		add    eax,esi                          
			movq   mm2,QWORD PTR [ecx]              
		movq   mm3,QWORD PTR [ecx+0x8]          
		pxor   mm0,mm6                          
			pxor   mm1,mm6                          
			pxor   mm2,mm6                          
			pxor   mm3,mm6                          
			pavgb  mm0,mm2                          
			pavgb  mm1,mm3                          
			pxor   mm0,mm6                          
			pxor   mm1,mm6                          
			movq   QWORD PTR [edx],mm0              
			movq   QWORD PTR [edx+0x8],mm1          
			add    edx,edi                          
			movq   mm0,QWORD PTR [eax]              
		movq   mm1,QWORD PTR [eax+0x8]          
		add    eax,esi                          
			movq   mm2,QWORD PTR [ecx+0x10]         
		movq   mm3,QWORD PTR [ecx+0x18]         
		pxor   mm0,mm6                          
			pxor   mm1,mm6                          
			pxor   mm2,mm6                          
			pxor   mm3,mm6                          
			pavgb  mm0,mm2                          
			pavgb  mm1,mm3                          
			pxor   mm0,mm6                          
			pxor   mm1,mm6                          
			movq   QWORD PTR [edx],mm0              
			movq   QWORD PTR [edx+0x8],mm1          
			add    edx,edi                          
			add    ecx,0x20                         
			sub    ebx,0x2                          
			jne    put_no_rnd_pixels16_l2_mmx2_3f86 
			mov    ebx,DWORD PTR [esp]              
		mov    esi,DWORD PTR [esp+0x4]          
		mov    edi,DWORD PTR [esp+0x8]          
		add    esp,0xc                          
			ret                                     

	}
}


NAKED void put_no_rnd_pixels8_x2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                         
			mov    DWORD PTR [esp],esi             
			mov    ecx,DWORD PTR [esp+0x18]        
		mov    DWORD PTR [esp+0x4],edi         
			mov    esi,DWORD PTR [esp+0x10]        
		mov    edi,DWORD PTR [esp+0xc]         
		movq   mm6,QWORD PTR [ff_bone]            
			mov    edx,DWORD PTR [esp+0x14]        
		lea    eax,[edx+edx*1]                 
put_no_rnd_pixels8_x2_mmx2_2bc4:       
		movq   mm0,QWORD PTR [esi]             
		movq   mm2,QWORD PTR [esi+edx*1]       
		movq   mm1,QWORD PTR [esi+0x1]         
		movq   mm3,QWORD PTR [esi+edx*1+0x1]   
		add    esi,eax                         
			psubusb mm0,mm6                        
			psubusb mm2,mm6                        
			pavgb  mm0,mm1                         
			pavgb  mm2,mm3                         
			movq   QWORD PTR [edi],mm0             
			movq   QWORD PTR [edi+edx*1],mm2       
			movq   mm0,QWORD PTR [esi]             
		movq   mm1,QWORD PTR [esi+0x1]         
		movq   mm2,QWORD PTR [esi+edx*1]       
		movq   mm3,QWORD PTR [esi+edx*1+0x1]   
		add    edi,eax                         
			add    esi,eax                         
			psubusb mm0,mm6                        
			psubusb mm2,mm6                        
			pavgb  mm0,mm1                         
			pavgb  mm2,mm3                         
			movq   QWORD PTR [edi],mm0             
			movq   QWORD PTR [edi+edx*1],mm2       
			add    edi,eax                         
			sub    ecx,0x4                         
			jne    put_no_rnd_pixels8_x2_mmx2_2bc4 
			mov    esi,DWORD PTR [esp]             
		mov    edi,DWORD PTR [esp+0x4]         
		add    esp,0x8                         
			ret                                    

	}
}

NAKED void put_no_rnd_pixels8_x2_exact_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                                
			mov    eax,DWORD PTR [esp+0x14]               
		mov    DWORD PTR [esp],ebx                    
			mov    ecx,DWORD PTR [esp+0x10]               
		mov    DWORD PTR [esp+0x4],esi                
			mov    ebx,DWORD PTR [esp+0xc]                
		mov    edx,DWORD PTR [esp+0x18]               
		lea    esi,[eax+eax*2]                        
		pcmpeqb mm6,mm6                               
put_no_rnd_pixels8_x2_exact_mmx2_2c50:        
		movq   mm0,QWORD PTR [ecx]                    
		movq   mm2,QWORD PTR [ecx+eax*1]              
		movq   mm1,QWORD PTR [ecx+0x1]                
		movq   mm3,QWORD PTR [ecx+eax*1+0x1]          
		pxor   mm0,mm6                                
			pxor   mm2,mm6                                
			pxor   mm1,mm6                                
			pxor   mm3,mm6                                
			pavgb  mm0,mm1                                
			pavgb  mm2,mm3                                
			pxor   mm0,mm6                                
			pxor   mm2,mm6                                
			movq   QWORD PTR [ebx],mm0                    
			movq   QWORD PTR [ebx+eax*1],mm2              
			movq   mm0,QWORD PTR [ecx+eax*2]              
		movq   mm1,QWORD PTR [ecx+eax*2+0x1]          
		movq   mm2,QWORD PTR [ecx+esi*1]              
		movq   mm3,QWORD PTR [ecx+esi*1+0x1]          
		pxor   mm0,mm6                                
			pxor   mm1,mm6                                
			pxor   mm2,mm6                                
			pxor   mm3,mm6                                
			pavgb  mm0,mm1                                
			pavgb  mm2,mm3                                
			pxor   mm0,mm6                                
			pxor   mm2,mm6                                
			movq   QWORD PTR [ebx+eax*2],mm0              
			movq   QWORD PTR [ebx+esi*1],mm2              
			lea    ecx,[ecx+eax*4]                        
		lea    ebx,[ebx+eax*4]                        
		sub    edx,0x4                                
			jg     put_no_rnd_pixels8_x2_exact_mmx2_2c50  
			mov    ebx,DWORD PTR [esp]                    
		mov    esi,DWORD PTR [esp+0x4]                
		add    esp,0x8                                
			ret                                           

	}
}

NAKED void put_pixels8_y2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                       
			mov    DWORD PTR [esp],esi           
			mov    ecx,DWORD PTR [esp+0x18]      
		mov    DWORD PTR [esp+0x4],edi       
			mov    esi,DWORD PTR [esp+0x10]      
		mov    edi,DWORD PTR [esp+0xc]       
		mov    edx,DWORD PTR [esp+0x14]      
		lea    eax,[edx+edx*1]               
		movq   mm0,QWORD PTR [esi]           
		sub    edi,edx                       
put_pixels8_y2_mmx2_2cf2:            
		movq   mm1,QWORD PTR [esi+edx*1]     
		movq   mm2,QWORD PTR [esi+eax*1]     
		add    esi,eax                       
			pavgb  mm0,mm1                       
			pavgb  mm1,mm2                       
			movq   QWORD PTR [edi+edx*1],mm0     
			movq   QWORD PTR [edi+eax*1],mm1     
			movq   mm1,QWORD PTR [esi+edx*1]     
		movq   mm0,QWORD PTR [esi+eax*1]     
		add    edi,eax                       
			add    esi,eax                       
			pavgb  mm2,mm1                       
			pavgb  mm1,mm0                       
			movq   QWORD PTR [edi+edx*1],mm2     
			movq   QWORD PTR [edi+eax*1],mm1     
			add    edi,eax                       
			sub    ecx,0x4                       
			jne    put_pixels8_y2_mmx2_2cf2      
			mov    esi,DWORD PTR [esp]           
		mov    edi,DWORD PTR [esp+0x4]       
		add    esp,0x8                       
			ret                                  

	}
}


NAKED void put_no_rnd_pixels8_y2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                          
			mov    DWORD PTR [esp],esi              
			mov    ecx,DWORD PTR [esp+0x18]         
		mov    DWORD PTR [esp+0x4],edi          
			mov    esi,DWORD PTR [esp+0x10]         
		mov    edi,DWORD PTR [esp+0xc]          
		movq   mm6,QWORD PTR [ff_bone]
			mov    edx,DWORD PTR [esp+0x14]         
		lea    eax,[edx+edx*1]                  
		movq   mm0,QWORD PTR [esi]              
		sub    edi,edx                          
put_no_rnd_pixels8_y2_mmx2_2d69:        
		movq   mm1,QWORD PTR [esi+edx*1]        
		movq   mm2,QWORD PTR [esi+eax*1]        
		add    esi,eax                          
			psubusb mm1,mm6                         
			pavgb  mm0,mm1                          
			pavgb  mm1,mm2                          
			movq   QWORD PTR [edi+edx*1],mm0        
			movq   QWORD PTR [edi+eax*1],mm1        
			movq   mm1,QWORD PTR [esi+edx*1]        
		movq   mm0,QWORD PTR [esi+eax*1]        
		add    edi,eax                          
			add    esi,eax                          
			psubusb mm1,mm6                         
			pavgb  mm2,mm1                          
			pavgb  mm1,mm0                          
			movq   QWORD PTR [edi+edx*1],mm2        
			movq   QWORD PTR [edi+eax*1],mm1        
			add    edi,eax                          
			sub    ecx,0x4                          
			jne    put_no_rnd_pixels8_y2_mmx2_2d69  
			mov    esi,DWORD PTR [esp]              
		mov    edi,DWORD PTR [esp+0x4]          
		add    esp,0x8                          
			ret                                     

	}
}

NAKED void put_no_rnd_pixels8_y2_exact_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                                 
			mov    eax,DWORD PTR [esp+0x14]                
		mov    DWORD PTR [esp],ebx                     
			mov    ecx,DWORD PTR [esp+0x10]                
		mov    DWORD PTR [esp+0x4],esi                 
			mov    ebx,DWORD PTR [esp+0xc]                 
		mov    edx,DWORD PTR [esp+0x18]                
		lea    esi,[eax+eax*2]                         
		movq   mm0,QWORD PTR [ecx]                     
		pcmpeqb mm6,mm6                                
			add    ecx,eax                                 
			pxor   mm0,mm6                                 
put_no_rnd_pixels8_y2_exact_mmx2_2de8:         
		movq   mm1,QWORD PTR [ecx]                     
		movq   mm2,QWORD PTR [ecx+eax*1]               
		pxor   mm1,mm6                                 
			pxor   mm2,mm6                                 
			pavgb  mm0,mm1                                 
			pavgb  mm1,mm2                                 
			pxor   mm0,mm6                                 
			pxor   mm1,mm6                                 
			movq   QWORD PTR [ebx],mm0                     
			movq   QWORD PTR [ebx+eax*1],mm1               
			movq   mm1,QWORD PTR [ecx+eax*2]               
		movq   mm0,QWORD PTR [ecx+esi*1]               
		pxor   mm1,mm6                                 
			pxor   mm0,mm6                                 
			pavgb  mm2,mm1                                 
			pavgb  mm1,mm0                                 
			pxor   mm2,mm6                                 
			pxor   mm1,mm6                                 
			movq   QWORD PTR [ebx+eax*2],mm2               
			movq   QWORD PTR [ebx+esi*1],mm1               
			lea    ecx,[ecx+eax*4]                         
		lea    ebx,[ebx+eax*4]                         
		sub    edx,0x4                                 
			jg     put_no_rnd_pixels8_y2_exact_mmx2_2de8   
			mov    ebx,DWORD PTR [esp]                     
		mov    esi,DWORD PTR [esp+0x4]                 
		add    esp,0x8                                 
			ret                                            

	}
}

NAKED void avg_pixels8_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                      
			mov    DWORD PTR [esp],esi          
			mov    ecx,DWORD PTR [esp+0x18]     
		mov    DWORD PTR [esp+0x4],edi      
			mov    esi,DWORD PTR [esp+0x10]     
		mov    edi,DWORD PTR [esp+0xc]      
		mov    edx,DWORD PTR [esp+0x14]     
		lea    eax,[edx+edx*1]              
avg_pixels8_mmx2_2e5d:              
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
			jne    avg_pixels8_mmx2_2e5d        
			mov    esi,DWORD PTR [esp]          
		mov    edi,DWORD PTR [esp+0x4]      
		add    esp,0x8                      
			ret                                 

	}
}

NAKED void avg_pixels8_x2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                        
			mov    DWORD PTR [esp],esi            
			mov    ecx,DWORD PTR [esp+0x18]       
		mov    DWORD PTR [esp+0x4],edi        
			mov    esi,DWORD PTR [esp+0x10]       
		mov    edi,DWORD PTR [esp+0xc]        
		mov    edx,DWORD PTR [esp+0x14]       
		lea    eax,[edx+edx*1]                
avg_pixels8_x2_mmx2_2ebd:             
		movq   mm0,QWORD PTR [esi]            
		movq   mm2,QWORD PTR [esi+edx*1]      
		pavgb  mm0,QWORD PTR [esi+0x1]        
		pavgb  mm2,QWORD PTR [esi+edx*1+0x1]  
		pavgb  mm0,QWORD PTR [edi]            
		pavgb  mm2,QWORD PTR [edi+edx*1]      
		add    esi,eax                        
			movq   QWORD PTR [edi],mm0            
			movq   QWORD PTR [edi+edx*1],mm2      
			movq   mm0,QWORD PTR [esi]            
		movq   mm2,QWORD PTR [esi+edx*1]      
		pavgb  mm0,QWORD PTR [esi+0x1]        
		pavgb  mm2,QWORD PTR [esi+edx*1+0x1]  
		add    edi,eax                        
			add    esi,eax                        
			pavgb  mm0,QWORD PTR [edi]            
		pavgb  mm2,QWORD PTR [edi+edx*1]      
		movq   QWORD PTR [edi],mm0            
			movq   QWORD PTR [edi+edx*1],mm2      
			add    edi,eax                        
			sub    ecx,0x4                        
			jne    avg_pixels8_x2_mmx2_2ebd       
			mov    esi,DWORD PTR [esp]            
		mov    edi,DWORD PTR [esp+0x4]        
		add    esp,0x8                        
			ret                                   

	}
}

NAKED void avg_pixels8_y2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                       
			mov    DWORD PTR [esp],esi           
			mov    ecx,DWORD PTR [esp+0x18]      
		mov    DWORD PTR [esp+0x4],edi       
			mov    esi,DWORD PTR [esp+0x10]      
		mov    edi,DWORD PTR [esp+0xc]       
		mov    edx,DWORD PTR [esp+0x14]      
		lea    eax,[edx+edx*1]               
		movq   mm0,QWORD PTR [esi]           
		sub    edi,edx                       
avg_pixels8_y2_mmx2_2f42:            
		movq   mm1,QWORD PTR [esi+edx*1]     
		movq   mm2,QWORD PTR [esi+eax*1]     
		add    esi,eax                       
			pavgb  mm0,mm1                       
			pavgb  mm1,mm2                       
			movq   mm3,QWORD PTR [edi+edx*1]     
		movq   mm4,QWORD PTR [edi+eax*1]     
		pavgb  mm0,mm3                       
			pavgb  mm1,mm4                       
			movq   QWORD PTR [edi+edx*1],mm0     
			movq   QWORD PTR [edi+eax*1],mm1     
			movq   mm1,QWORD PTR [esi+edx*1]     
		movq   mm0,QWORD PTR [esi+eax*1]     
		pavgb  mm2,mm1                       
			pavgb  mm1,mm0                       
			add    edi,eax                       
			add    esi,eax                       
			movq   mm3,QWORD PTR [edi+edx*1]     
		movq   mm4,QWORD PTR [edi+eax*1]     
		pavgb  mm2,mm3                       
		pavgb  mm1,mm4                       
		movq   QWORD PTR [edi+edx*1],mm2     
		movq   QWORD PTR [edi+eax*1],mm1     
		add    edi,eax                       
		sub    ecx,0x4                       
		jne    avg_pixels8_y2_mmx2_2f42      
		mov    esi,DWORD PTR [esp]           
		mov    edi,DWORD PTR [esp+0x4]       
		add    esp,0x8                       
		ret                                  

	}
}



NAKED void avg_pixels8_xy2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		sub    esp,0x8                          
			mov    DWORD PTR [esp],esi              
			mov    ecx,DWORD PTR [esp+0x18]         
		mov    DWORD PTR [esp+0x4],edi          
			mov    esi,DWORD PTR [esp+0x10]         
		mov    edi,DWORD PTR [esp+0xc]          
		movq   mm6,QWORD PTR [ff_bone]
			mov    edx,DWORD PTR [esp+0x14]         
		lea    eax,[edx+edx*1]                  
		movq   mm0,QWORD PTR [esi]              
		pavgb  mm0,QWORD PTR [esi+0x1]          
		nop                                     

avg_pixels8_xy2_mmx2_2fe0:              
		movq   mm2,QWORD PTR [esi+eax*1]        
		movq   mm1,QWORD PTR [esi+edx*1]        
		psubusb mm2,mm6                         
			pavgb  mm1,QWORD PTR [esi+edx*1+0x1]    
		pavgb  mm2,QWORD PTR [esi+eax*1+0x1]    
		add    esi,eax                          
			pavgb  mm0,mm1                          
			pavgb  mm1,mm2                          
			pavgb  mm0,QWORD PTR [edi]              
		pavgb  mm1,QWORD PTR [edi+edx*1]        
		movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			movq   mm1,QWORD PTR [esi+edx*1]        
		movq   mm0,QWORD PTR [esi+eax*1]        
		pavgb  mm1,QWORD PTR [esi+edx*1+0x1]    
		pavgb  mm0,QWORD PTR [esi+eax*1+0x1]    
		add    edi,eax                          
			add    esi,eax                          
			pavgb  mm2,mm1                          
			pavgb  mm1,mm0                          
			pavgb  mm2,QWORD PTR [edi]              
		pavgb  mm1,QWORD PTR [edi+edx*1]        
		movq   QWORD PTR [edi],mm2              
			movq   QWORD PTR [edi+edx*1],mm1        
			add    edi,eax                          
			sub    ecx,0x4                          
			jne    avg_pixels8_xy2_mmx2_2fe0        
			mov    esi,DWORD PTR [esp]              
		mov    edi,DWORD PTR [esp+0x4]          
		add    esp,0x8                          
			ret                                     

	}	
}

NAKED void avg_pixels4_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm {
		push   ebp                           
			push   edi                           
			push   esi                           
			push   ebx                           
			sub    esp,0x4                       
			mov    ecx,DWORD PTR [esp+0x20]      
		mov    ebp,DWORD PTR [esp+0x18]      
		mov    edx,DWORD PTR [esp+0x24]      
		lea    eax,[ecx*4+0x0]               
		mov    DWORD PTR [esp],eax           
			lea    ebx,[ecx+ecx*2]               
		xor    eax,eax                       
			lea    esi,[esi+0x0]                 
avg_pixels4_mmx2_44d8:               
		mov    esi,DWORD PTR [esp+0x1c]      
		lea    edi,[ebp+eax*1+0x0]           
		add    esi,eax                       
			movd   mm0,DWORD PTR [edi]           
		movd   mm1,DWORD PTR [edi+ecx*1]     
		movd   mm2,DWORD PTR [edi+ecx*2]     
		movd   mm3,DWORD PTR [edi+ebx*1]     
		pavgb  mm0,QWORD PTR [esi]           
		pavgb  mm1,QWORD PTR [esi+ecx*1]     
		pavgb  mm2,QWORD PTR [esi+ecx*2]     
		pavgb  mm3,QWORD PTR [esi+ebx*1]     
		movd   DWORD PTR [edi],mm0           
			movd   DWORD PTR [edi+ecx*1],mm1     
			movd   DWORD PTR [edi+ecx*2],mm2     
			movd   DWORD PTR [edi+ebx*1],mm3     
			sub    edx,0x4                       
			add    eax,DWORD PTR [esp]           
		test   edx,edx                       
			jg     avg_pixels4_mmx2_44d8         
			add    esp,0x4                       
			pop    ebx                           
			pop    esi                           
			pop    edi                           
			pop    ebp                           
			ret                                  

	}
}


void put_no_rnd_pixels16_x2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	put_no_rnd_pixels8_x2_mmx2(block , pixels , line_size, h);
	put_no_rnd_pixels8_x2_mmx2(block+8, pixels+8, line_size, h);
}

void put_pixels16_y2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	put_pixels8_y2_mmx2(block , pixels , line_size, h);
	put_pixels8_y2_mmx2(block+8, pixels+8, line_size, h);
}

void put_no_rnd_pixels16_y2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	put_no_rnd_pixels8_y2_mmx2(block , pixels , line_size, h);
	put_no_rnd_pixels8_y2_mmx2(block+8, pixels+8, line_size, h);
}

void avg_pixels16_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	avg_pixels8_mmx2(block , pixels , line_size, h);
	avg_pixels8_mmx2(block+8, pixels+8, line_size, h);
}

void avg_pixels16_x2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	avg_pixels8_x2_mmx2(block , pixels , line_size, h);
	avg_pixels8_x2_mmx2(block+8, pixels+8, line_size, h);
}

void avg_pixels16_y2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	avg_pixels8_y2_mmx2(block , pixels , line_size, h);
	avg_pixels8_y2_mmx2(block+8, pixels+8, line_size, h);
}

void avg_pixels16_xy2_mmx2(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	avg_pixels8_xy2_mmx2(block , pixels , line_size, h);
	avg_pixels8_xy2_mmx2(block+8, pixels+8, line_size, h);
}

NAKED void avg_2tap_qpel16_l3_mmx2(uint8_t *dst, uint8_t *src, int stride, int h, int off1, int off2)
{ 
	__asm {
		sub    esp,0xc                       
			mov    eax,DWORD PTR [esp+0x10]      
		mov    edx,DWORD PTR [esp+0x14]      
		mov    DWORD PTR [esp],ebx           
			mov    ecx,DWORD PTR [esp+0x1c]      
		mov    DWORD PTR [esp+0x4],esi       
			mov    ebx,DWORD PTR [esp+0x20]      
		mov    DWORD PTR [esp+0x8],edi       
			mov    esi,DWORD PTR [esp+0x24]      
		mov    edi,DWORD PTR [esp+0x18]      
		sub    eax,edx                       
avg_2tap_qpel16_l3_mmx2_4bc8:        
		movq   mm0,QWORD PTR [edx+ebx*1]     
		movq   mm1,QWORD PTR [edx+ebx*1+0x8] 
		pavgb  mm0,QWORD PTR [edx+esi*1]     
		pavgb  mm1,QWORD PTR [edx+esi*1+0x8] 
		pavgb  mm0,QWORD PTR [edx]           
		pavgb  mm1,QWORD PTR [edx+0x8]       
		pavgb  mm0,QWORD PTR [edx+eax*1]     
		pavgb  mm1,QWORD PTR [edx+eax*1+0x8] 
		movq   QWORD PTR [edx+eax*1],mm0     
			movq   QWORD PTR [edx+eax*1+0x8],mm1 
			add    edx,edi                       
			dec    ecx                           
			jne    avg_2tap_qpel16_l3_mmx2_4bc8  
			mov    ebx,DWORD PTR [esp]           
		mov    esi,DWORD PTR [esp+0x4]       
		mov    edi,DWORD PTR [esp+0x8]       
		add    esp,0xc                       
			ret                                  

	}
}

NAKED void avg_2tap_qpel8_l3_mmx2(uint8_t *dst, uint8_t *src, int stride, int h, int off1, int off2)
{
	__asm {
		sub    esp,0xc                     
			mov    eax,DWORD PTR [esp+0x10]    
		mov    edx,DWORD PTR [esp+0x14]    
		mov    DWORD PTR [esp],ebx         
			mov    ecx,DWORD PTR [esp+0x1c]    
		mov    DWORD PTR [esp+0x4],esi     
			mov    ebx,DWORD PTR [esp+0x20]    
		mov    DWORD PTR [esp+0x8],edi     
			mov    esi,DWORD PTR [esp+0x24]    
		mov    edi,DWORD PTR [esp+0x18]    
		sub    eax,edx                     
avg_2tap_qpel8_l3_mmx2_4c38:       
		movq   mm0,QWORD PTR [edx+ebx*1]   
		pavgb  mm0,QWORD PTR [edx+esi*1]   
		pavgb  mm0,QWORD PTR [edx]         
		pavgb  mm0,QWORD PTR [edx+eax*1]   
		movq   QWORD PTR [edx+eax*1],mm0   
			add    edx,edi                     
			dec    ecx                         
			jne    avg_2tap_qpel8_l3_mmx2_4c38 
			mov    ebx,DWORD PTR [esp]         
		mov    esi,DWORD PTR [esp+0x4]     
		mov    edi,DWORD PTR [esp+0x8]     
		add    esp,0xc                     
			ret                                

	}
}

NAKED void put_2tap_qpel16_l3_mmx2(uint8_t *dst, uint8_t *src, int stride, int h, int off1, int off2)
{
	__asm {
		sub    esp,0xc                       
			mov    eax,DWORD PTR [esp+0x10]      
		mov    edx,DWORD PTR [esp+0x14]      
		mov    DWORD PTR [esp],ebx           
			mov    ecx,DWORD PTR [esp+0x1c]      
		mov    DWORD PTR [esp+0x4],esi       
			mov    ebx,DWORD PTR [esp+0x20]      
		mov    DWORD PTR [esp+0x8],edi       
			mov    esi,DWORD PTR [esp+0x24]      
		mov    edi,DWORD PTR [esp+0x18]      
		sub    eax,edx                       
put_2tap_qpel16_l3_mmx2_4c88:        
		movq   mm0,QWORD PTR [edx+ebx*1]     
		movq   mm1,QWORD PTR [edx+ebx*1+0x8] 
		pavgb  mm0,QWORD PTR [edx+esi*1]     
		pavgb  mm1,QWORD PTR [edx+esi*1+0x8] 
		pavgb  mm0,QWORD PTR [edx]           
		pavgb  mm1,QWORD PTR [edx+0x8]       
		movq   QWORD PTR [edx+eax*1],mm0     
			movq   QWORD PTR [edx+eax*1+0x8],mm1 
			add    edx,edi                       
			dec    ecx                           
			jne    put_2tap_qpel16_l3_mmx2_4c88  
			mov    ebx,DWORD PTR [esp]           
		mov    esi,DWORD PTR [esp+0x4]       
		mov    edi,DWORD PTR [esp+0x8]       
		add    esp,0xc                       
			ret                                  

	}
}

NAKED void put_2tap_qpel8_l3_mmx2(uint8_t *dst, uint8_t *src, int stride, int h, int off1, int off2)
{
	__asm {
		sub    esp,0xc                     
			mov    eax,DWORD PTR [esp+0x10]    
		mov    edx,DWORD PTR [esp+0x14]    
		mov    DWORD PTR [esp],ebx         
			mov    ecx,DWORD PTR [esp+0x1c]    
		mov    DWORD PTR [esp+0x4],esi     
			mov    ebx,DWORD PTR [esp+0x20]    
		mov    DWORD PTR [esp+0x8],edi     
			mov    esi,DWORD PTR [esp+0x24]    
		mov    edi,DWORD PTR [esp+0x18]    
		sub    eax,edx                     
put_2tap_qpel8_l3_mmx2_4ce8:       
		movq   mm0,QWORD PTR [edx+ebx*1]   
		pavgb  mm0,QWORD PTR [edx+esi*1]   
		pavgb  mm0,QWORD PTR [edx]         
		movq   QWORD PTR [edx+eax*1],mm0   
			add    edx,edi                     
			dec    ecx                         
			jne    put_2tap_qpel8_l3_mmx2_4ce8 
			mov    ebx,DWORD PTR [esp]         
		mov    esi,DWORD PTR [esp+0x4]     
		mov    edi,DWORD PTR [esp+0x8]     
		add    esp,0xc                     
			ret                                

	}
}





