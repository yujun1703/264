#include "x86_opt.h"
#include "dsputil_mmx.h"

//extern uint64_t ff_bone;

NAKED void put_pixels8_x2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
put_pixels8_x2_3dnow_1ddd:              
		movq   mm0,QWORD PTR [esi]              
		movq   mm1,QWORD PTR [esi+edx*1]        
		pavgusb mm0,QWORD PTR [esi+0x1]         
		pavgusb mm1,QWORD PTR [esi+edx*1+0x1]   
		movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			add    esi,eax                          
			add    edi,eax                          
			movq   mm0,QWORD PTR [esi]              
		movq   mm1,QWORD PTR [esi+edx*1]        
		pavgusb mm0,QWORD PTR [esi+0x1]         
		pavgusb mm1,QWORD PTR [esi+edx*1+0x1]   
		add    esi,eax                          
			movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			add    edi,eax                          
			sub    ecx,0x4                          
			jne    put_pixels8_x2_3dnow_1ddd        
			mov    esi,DWORD PTR [esp]              
		mov    edi,DWORD PTR [esp+0x4]          
		add    esp,0x8                          
			ret                                     

	}
}


NAKED void put_no_rnd_pixels8_l2_3dnow(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
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
			je     put_no_rnd_pixels8_l2_3dnow_26cf    
			movq   mm0,QWORD PTR [eax]                 
		movq   mm1,QWORD PTR [ecx]                 
		add    eax,esi                             
			add    ecx,0x8                             
			pxor   mm0,mm6                             
			pxor   mm1,mm6                             
			pavgusb mm0,mm1                            
			pxor   mm0,mm6                             
			movq   QWORD PTR [edx],mm0                 
			add    edx,edi                             
			dec    ebx                                 
put_no_rnd_pixels8_l2_3dnow_26cf:          
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
			pavgusb mm0,mm2                            
			pavgusb mm1,mm3                            
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
			pavgusb mm0,mm2                            
			pavgusb mm1,mm3                            
			pxor   mm0,mm6                             
			pxor   mm1,mm6                             
			movq   QWORD PTR [edx],mm0                 
			add    edx,edi                             
			movq   QWORD PTR [edx],mm1                 
			add    edx,edi                             
			add    ecx,0x20                            
			sub    ebx,0x4                             
			jne    put_no_rnd_pixels8_l2_3dnow_26cf    
			mov    ebx,DWORD PTR [esp]                 
		mov    esi,DWORD PTR [esp+0x4]             
		mov    edi,DWORD PTR [esp+0x8]             
		add    esp,0xc                             
			ret                                        

	}
}




NAKED void put_pixels16_x2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	__asm{
		sub    esp,0x8                          
			mov    DWORD PTR [esp],esi              
			mov    ecx,DWORD PTR [esp+0x18]         
		mov    DWORD PTR [esp+0x4],edi          
			mov    esi,DWORD PTR [esp+0x10]         
		mov    edi,DWORD PTR [esp+0xc]          
		mov    edx,DWORD PTR [esp+0x14]         
		lea    eax,[edx+edx*1]                  
put_pixels16_x2_3dnow_1e4d:             
		movq   mm0,QWORD PTR [esi]              
		movq   mm1,QWORD PTR [esi+edx*1]        
		movq   mm2,QWORD PTR [esi+0x8]          
		movq   mm3,QWORD PTR [esi+edx*1+0x8]    
		pavgusb mm0,QWORD PTR [esi+0x1]         
		pavgusb mm1,QWORD PTR [esi+edx*1+0x1]   
		pavgusb mm2,QWORD PTR [esi+0x9]         
		pavgusb mm3,QWORD PTR [esi+edx*1+0x9]   
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
		pavgusb mm0,QWORD PTR [esi+0x1]         
		pavgusb mm1,QWORD PTR [esi+edx*1+0x1]   
		pavgusb mm2,QWORD PTR [esi+0x9]         
		pavgusb mm3,QWORD PTR [esi+edx*1+0x9]   
		add    esi,eax                          
			movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			movq   QWORD PTR [edi+0x8],mm2          
			movq   QWORD PTR [edi+edx*1+0x8],mm3    
			add    edi,eax                          
			sub    ecx,0x4                          
			jne    put_pixels16_x2_3dnow_1e4d       
			mov    esi,DWORD PTR [esp]              
		mov    edi,DWORD PTR [esp+0x4]          
		add    esp,0x8                          
			ret                                     

	}	
}





NAKED void put_no_rnd_pixels16_l2_3dnow(uint8_t *dst, uint8_t *src1, uint8_t *src2, int dstStride, int src1Stride, int h)
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
			je     put_no_rnd_pixels16_l2_3dnow_2b38 
			movq   mm0,QWORD PTR [eax]               
		movq   mm1,QWORD PTR [eax+0x8]           
		movq   mm2,QWORD PTR [ecx]               
		movq   mm3,QWORD PTR [ecx+0x8]           
		pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			pxor   mm2,mm6                           
			pxor   mm3,mm6                           
			pavgusb mm0,mm2                          
			pavgusb mm1,mm3                          
			pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			add    eax,esi                           
			add    ecx,0x10                          
			movq   QWORD PTR [edx],mm0               
			movq   QWORD PTR [edx+0x8],mm1           
			add    edx,edi                           
			dec    ebx                               
put_no_rnd_pixels16_l2_3dnow_2b38:       
		movq   mm0,QWORD PTR [eax]               
		movq   mm1,QWORD PTR [eax+0x8]           
		add    eax,esi                           
			movq   mm2,QWORD PTR [ecx]               
		movq   mm3,QWORD PTR [ecx+0x8]           
		pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			pxor   mm2,mm6                           
			pxor   mm3,mm6                           
			pavgusb mm0,mm2                          
			pavgusb mm1,mm3                          
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
			pavgusb mm0,mm2                          
			pavgusb mm1,mm3                          
			pxor   mm0,mm6                           
			pxor   mm1,mm6                           
			movq   QWORD PTR [edx],mm0               
			movq   QWORD PTR [edx+0x8],mm1           
			add    edx,edi                           
			add    ecx,0x20                          
			sub    ebx,0x2                           
			jne    put_no_rnd_pixels16_l2_3dnow_2b38 
			mov    ebx,DWORD PTR [esp]               
		mov    esi,DWORD PTR [esp+0x4]           
		mov    edi,DWORD PTR [esp+0x8]           
		add    esp,0xc                           
			ret                                      

	}
}

/* GL: this function does incorrect rounding if overflow */
NAKED void put_no_rnd_pixels8_x2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
put_no_rnd_pixels8_x2_3dnow_1f04:      
		movq   mm0,QWORD PTR [esi]             
		movq   mm2,QWORD PTR [esi+edx*1]       
		movq   mm1,QWORD PTR [esi+0x1]         
		movq   mm3,QWORD PTR [esi+edx*1+0x1]   
		add    esi,eax                         
			psubusb mm0,mm6                        
			psubusb mm2,mm6                        
			pavgusb mm0,mm1                        
			pavgusb mm2,mm3                        
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
			pavgusb mm0,mm1                        
			pavgusb mm2,mm3                        
			movq   QWORD PTR [edi],mm0             
			movq   QWORD PTR [edi+edx*1],mm2       
			add    edi,eax                         
			sub    ecx,0x4                         
			jne    put_no_rnd_pixels8_x2_3dnow_1f04
			mov    esi,DWORD PTR [esp]             
		mov    edi,DWORD PTR [esp+0x4]         
		add    esp,0x8                         
			ret                                    

	}
	
}

NAKED void put_no_rnd_pixels8_x2_exact_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
put_no_rnd_pixels8_x2_exact_3dnow_1f90:        
		movq   mm0,QWORD PTR [ecx]                     
		movq   mm2,QWORD PTR [ecx+eax*1]               
		movq   mm1,QWORD PTR [ecx+0x1]                 
		movq   mm3,QWORD PTR [ecx+eax*1+0x1]           
		pxor   mm0,mm6                                 
			pxor   mm2,mm6                                 
			pxor   mm1,mm6                                 
			pxor   mm3,mm6                                 
			pavgusb mm0,mm1                                
			pavgusb mm2,mm3                                
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
			pavgusb mm0,mm1                                
			pavgusb mm2,mm3                                
			pxor   mm0,mm6                                 
			pxor   mm2,mm6                                 
			movq   QWORD PTR [ebx+eax*2],mm0               
			movq   QWORD PTR [ebx+esi*1],mm2               
			lea    ecx,[ecx+eax*4]                         
		lea    ebx,[ebx+eax*4]                         
		sub    edx,0x4                                 
			jg     put_no_rnd_pixels8_x2_exact_3dnow_1f90  
			mov    ebx,DWORD PTR [esp]                     
		mov    esi,DWORD PTR [esp+0x4]                 
		add    esp,0x8                                 
			ret                                            

	}
}

NAKED void put_pixels8_y2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
put_pixels8_y2_3dnow_2032:        
		movq   mm1,QWORD PTR [esi+edx*1]  
		movq   mm2,QWORD PTR [esi+eax*1]  
		add    esi,eax                    
			pavgusb mm0,mm1                   
			pavgusb mm1,mm2                   
			movq   QWORD PTR [edi+edx*1],mm0  
			movq   QWORD PTR [edi+eax*1],mm1  
			movq   mm1,QWORD PTR [esi+edx*1]  
		movq   mm0,QWORD PTR [esi+eax*1]  
		add    edi,eax                    
			add    esi,eax                    
			pavgusb mm2,mm1                   
			pavgusb mm1,mm0                   
			movq   QWORD PTR [edi+edx*1],mm2  
			movq   QWORD PTR [edi+eax*1],mm1  
			add    edi,eax                    
			sub    ecx,0x4                    
			jne    put_pixels8_y2_3dnow_2032  
			mov    esi,DWORD PTR [esp]        
		mov    edi,DWORD PTR [esp+0x4]    
		add    esp,0x8                    
			ret                               

	}
}

/* GL: this function does incorrect rounding if overflow */
NAKED void put_no_rnd_pixels8_y2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
put_no_rnd_pixels8_y2_3dnow_20a9:        
		movq   mm1,QWORD PTR [esi+edx*1]         
		movq   mm2,QWORD PTR [esi+eax*1]         
		add    esi,eax                           
			psubusb mm1,mm6                          
			pavgusb mm0,mm1                          
			pavgusb mm1,mm2                          
			movq   QWORD PTR [edi+edx*1],mm0         
			movq   QWORD PTR [edi+eax*1],mm1         
			movq   mm1,QWORD PTR [esi+edx*1]         
		movq   mm0,QWORD PTR [esi+eax*1]         
		add    edi,eax                           
			add    esi,eax                           
			psubusb mm1,mm6                          
			pavgusb mm2,mm1                          
			pavgusb mm1,mm0                          
			movq   QWORD PTR [edi+edx*1],mm2         
			movq   QWORD PTR [edi+eax*1],mm1         
			add    edi,eax                           
			sub    ecx,0x4                           
			jne    put_no_rnd_pixels8_y2_3dnow_20a9  
			mov    esi,DWORD PTR [esp]               
		mov    edi,DWORD PTR [esp+0x4]           
		add    esp,0x8                           
			ret                                      

	}
}

NAKED void put_no_rnd_pixels8_y2_exact_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
put_no_rnd_pixels8_y2_exact_3dnow_2128:       
		movq   mm1,QWORD PTR [ecx]                    
		movq   mm2,QWORD PTR [ecx+eax*1]              
		pxor   mm1,mm6                                
			pxor   mm2,mm6                                
			pavgusb mm0,mm1                               
			pavgusb mm1,mm2                               
			pxor   mm0,mm6                                
			pxor   mm1,mm6                                
			movq   QWORD PTR [ebx],mm0                    
			movq   QWORD PTR [ebx+eax*1],mm1              
			movq   mm1,QWORD PTR [ecx+eax*2]              
		movq   mm0,QWORD PTR [ecx+esi*1]              
		pxor   mm1,mm6                                
			pxor   mm0,mm6                                
			pavgusb mm2,mm1                               
			pavgusb mm1,mm0                               
			pxor   mm2,mm6                                
			pxor   mm1,mm6                                
			movq   QWORD PTR [ebx+eax*2],mm2              
			movq   QWORD PTR [ebx+esi*1],mm1              
			lea    ecx,[ecx+eax*4]                        
		lea    ebx,[ebx+eax*4]                        
		sub    edx,0x4                                
			jg     put_no_rnd_pixels8_y2_exact_3dnow_2128 
			mov    ebx,DWORD PTR [esp]                    
		mov    esi,DWORD PTR [esp+0x4]                
		add    esp,0x8                                
			ret                                           

	}
}

NAKED void avg_pixels8_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
avg_pixels8_3dnow_21ad:              
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
			jne    avg_pixels8_3dnow_21ad        
			mov    esi,DWORD PTR [esp]           
		mov    edi,DWORD PTR [esp+0x4]       
		add    esp,0x8                       
			ret                                  

	}
}

NAKED void avg_pixels8_x2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
avg_pixels8_x2_3dnow_221d:            
		movq   mm0,QWORD PTR [esi]            
		movq   mm2,QWORD PTR [esi+edx*1]      
		pavgusb mm0,QWORD PTR [esi+0x1]       
		pavgusb mm2,QWORD PTR [esi+edx*1+0x1] 
		pavgusb mm0,QWORD PTR [edi]           
		pavgusb mm2,QWORD PTR [edi+edx*1]     
		add    esi,eax                        
			movq   QWORD PTR [edi],mm0            
			movq   QWORD PTR [edi+edx*1],mm2      
			movq   mm0,QWORD PTR [esi]            
		movq   mm2,QWORD PTR [esi+edx*1]      
		pavgusb mm0,QWORD PTR [esi+0x1]       
		pavgusb mm2,QWORD PTR [esi+edx*1+0x1] 
		add    edi,eax                        
			add    esi,eax                        
			pavgusb mm0,QWORD PTR [edi]           
		pavgusb mm2,QWORD PTR [edi+edx*1]     
		movq   QWORD PTR [edi],mm0            
			movq   QWORD PTR [edi+edx*1],mm2      
			add    edi,eax                        
			sub    ecx,0x4                        
			jne    avg_pixels8_x2_3dnow_221d      
			mov    esi,DWORD PTR [esp]            
		mov    edi,DWORD PTR [esp+0x4]        
		add    esp,0x8                        
			ret                                   

	}
}

NAKED void avg_pixels8_y2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
avg_pixels8_y2_3dnow_22a2:         
		movq   mm1,QWORD PTR [esi+edx*1]   
		movq   mm2,QWORD PTR [esi+eax*1]   
		add    esi,eax                     
			pavgusb mm0,mm1                    
			pavgusb mm1,mm2                    
			movq   mm3,QWORD PTR [edi+edx*1]   
		movq   mm4,QWORD PTR [edi+eax*1]   
		pavgusb mm0,mm3                    
			pavgusb mm1,mm4                    
			movq   QWORD PTR [edi+edx*1],mm0   
			movq   QWORD PTR [edi+eax*1],mm1   
			movq   mm1,QWORD PTR [esi+edx*1]   
		movq   mm0,QWORD PTR [esi+eax*1]   
		pavgusb mm2,mm1                    
			pavgusb mm1,mm0                    
			add    edi,eax                     
			add    esi,eax                     
			movq   mm3,QWORD PTR [edi+edx*1]   
		movq   mm4,QWORD PTR [edi+eax*1]   
		pavgusb mm2,mm3                    
			pavgusb mm1,mm4                    
			movq   QWORD PTR [edi+edx*1],mm2   
			movq   QWORD PTR [edi+eax*1],mm1   
			add    edi,eax                     
			sub    ecx,0x4                     
			jne    avg_pixels8_y2_3dnow_22a2   
			mov    esi,DWORD PTR [esp]         
		mov    edi,DWORD PTR [esp+0x4]     
		add    esp,0x8                     
			ret                                

	}
}

/* Note this is not correctly rounded, but this function is only
* used for B-frames so it does not matter. */
NAKED void avg_pixels8_xy2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
		pavgusb mm0,QWORD PTR [esi+0x1]         

avg_pixels8_xy2_3dnow_2340:             
		movq   mm2,QWORD PTR [esi+eax*1]        
		movq   mm1,QWORD PTR [esi+edx*1]        
		psubusb mm2,mm6                         
			pavgusb mm1,QWORD PTR [esi+edx*1+0x1]   
		pavgusb mm2,QWORD PTR [esi+eax*1+0x1]   
		add    esi,eax                          
			pavgusb mm0,mm1                         
			pavgusb mm1,mm2                         
			pavgusb mm0,QWORD PTR [edi]             
		pavgusb mm1,QWORD PTR [edi+edx*1]       
		movq   QWORD PTR [edi],mm0              
			movq   QWORD PTR [edi+edx*1],mm1        
			movq   mm1,QWORD PTR [esi+edx*1]        
		movq   mm0,QWORD PTR [esi+eax*1]        
		pavgusb mm1,QWORD PTR [esi+edx*1+0x1]   
		pavgusb mm0,QWORD PTR [esi+eax*1+0x1]   
		add    edi,eax                          
			add    esi,eax                          
			pavgusb mm2,mm1                         
			pavgusb mm1,mm0                         
			pavgusb mm2,QWORD PTR [edi]             
		pavgusb mm1,QWORD PTR [edi+edx*1]       
		movq   QWORD PTR [edi],mm2              
			movq   QWORD PTR [edi+edx*1],mm1        
			add    edi,eax                          
			sub    ecx,0x4                          
			jne    avg_pixels8_xy2_3dnow_2340       
			mov    esi,DWORD PTR [esp]              
		mov    edi,DWORD PTR [esp+0x4]          
		add    esp,0x8                          
			ret                                     

	}
}

NAKED void avg_pixels4_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
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
avg_pixels4_3dnow_30c8:             
		mov    esi,DWORD PTR [esp+0x1c]     
		lea    edi,[ebp+eax*1+0x0]          
		add    esi,eax                      
			movd   mm0,DWORD PTR [edi]          
		movd   mm1,DWORD PTR [edi+ecx*1]    
		movd   mm2,DWORD PTR [edi+ecx*2]    
		movd   mm3,DWORD PTR [edi+ebx*1]    
		pavgusb mm0,QWORD PTR [esi]         
		pavgusb mm1,QWORD PTR [esi+ecx*1]   
		pavgusb mm2,QWORD PTR [esi+ecx*2]   
		pavgusb mm3,QWORD PTR [esi+ebx*1]   
		movd   DWORD PTR [edi],mm0          
			movd   DWORD PTR [edi+ecx*1],mm1    
			movd   DWORD PTR [edi+ecx*2],mm2    
			movd   DWORD PTR [edi+ebx*1],mm3    
			sub    edx,0x4                      
			add    eax,DWORD PTR [esp]          
		test   edx,edx                      
			jg     avg_pixels4_3dnow_30c8       
			add    esp,0x4                      
			pop    ebx                          
			pop    esi                          
			pop    edi                          
			pop    ebp                          
			ret                                 

	}
}

//FIXME the following could be optimized too ...
void put_no_rnd_pixels16_x2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h){
	put_no_rnd_pixels8_x2_3dnow(block  , pixels  , line_size, h);
	put_no_rnd_pixels8_x2_3dnow(block+8, pixels+8, line_size, h);
}
void put_pixels16_y2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	put_pixels8_y2_3dnow(block  , pixels  , line_size, h);
	put_pixels8_y2_3dnow(block+8, pixels+8, line_size, h);
}

void put_no_rnd_pixels16_y2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	put_no_rnd_pixels8_y2_3dnow(block  , pixels  , line_size, h);
	put_no_rnd_pixels8_y2_3dnow(block+8, pixels+8, line_size, h);
}

void avg_pixels16_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	avg_pixels8_3dnow(block  , pixels  , line_size, h);
	avg_pixels8_3dnow(block+8, pixels+8, line_size, h);
}

void avg_pixels16_x2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	avg_pixels8_x2_3dnow(block  , pixels  , line_size, h);
	avg_pixels8_x2_3dnow(block+8, pixels+8, line_size, h);
}

void avg_pixels16_y2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	avg_pixels8_y2_3dnow(block  , pixels  , line_size, h);
	avg_pixels8_y2_3dnow(block+8, pixels+8, line_size, h);
}

void avg_pixels16_xy2_3dnow(uint8_t *block, const uint8_t *pixels, int line_size, int h)
{
	avg_pixels8_xy2_3dnow(block  , pixels  , line_size, h);
	avg_pixels8_xy2_3dnow(block+8, pixels+8, line_size, h);
}


NAKED void avg_2tap_qpel16_l3_3dnow(uint8_t *dst, uint8_t *src, int stride, int h, int off1, int off2)
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
avg_2tap_qpel16_l3_3dnow_3818:        
		movq   mm0,QWORD PTR [edx+ebx*1]      
		movq   mm1,QWORD PTR [edx+ebx*1+0x8]  
		pavgusb mm0,QWORD PTR [edx+esi*1]     
		pavgusb mm1,QWORD PTR [edx+esi*1+0x8] 
		pavgusb mm0,QWORD PTR [edx]           
		pavgusb mm1,QWORD PTR [edx+0x8]       
		pavgusb mm0,QWORD PTR [edx+eax*1]     
		pavgusb mm1,QWORD PTR [edx+eax*1+0x8] 
		movq   QWORD PTR [edx+eax*1],mm0      
			movq   QWORD PTR [edx+eax*1+0x8],mm1  
			add    edx,edi                        
			dec    ecx                            
			jne    avg_2tap_qpel16_l3_3dnow_3818  
			mov    ebx,DWORD PTR [esp]            
		mov    esi,DWORD PTR [esp+0x4]        
		mov    edi,DWORD PTR [esp+0x8]        
		add    esp,0xc                        
			ret                                   

	}
}

NAKED void avg_2tap_qpel8_l3_3dnow(uint8_t *dst, uint8_t *src, int stride, int h, int off1, int off2)
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
avg_2tap_qpel8_l3_3dnow_3888:       
		movq   mm0,QWORD PTR [edx+ebx*1]    
		pavgusb mm0,QWORD PTR [edx+esi*1]   
		pavgusb mm0,QWORD PTR [edx]         
		pavgusb mm0,QWORD PTR [edx+eax*1]   
		movq   QWORD PTR [edx+eax*1],mm0    
			add    edx,edi                      
			dec    ecx                          
			jne    avg_2tap_qpel8_l3_3dnow_3888 
			mov    ebx,DWORD PTR [esp]          
		mov    esi,DWORD PTR [esp+0x4]      
		mov    edi,DWORD PTR [esp+0x8]      
		add    esp,0xc                      
			ret                                 

	}
}

NAKED void put_2tap_qpel16_l3_3dnow(uint8_t *dst, uint8_t *src, int stride, int h, int off1, int off2)
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
put_2tap_qpel16_l3_3dnow_38e8:         
		movq   mm0,QWORD PTR [edx+ebx*1]       
		movq   mm1,QWORD PTR [edx+ebx*1+0x8]   
		pavgusb mm0,QWORD PTR [edx+esi*1]      
		pavgusb mm1,QWORD PTR [edx+esi*1+0x8]  
		pavgusb mm0,QWORD PTR [edx]            
		pavgusb mm1,QWORD PTR [edx+0x8]        
		movq   QWORD PTR [edx+eax*1],mm0       
			movq   QWORD PTR [edx+eax*1+0x8],mm1   
			add    edx,edi                         
			dec    ecx                             
			jne    put_2tap_qpel16_l3_3dnow_38e8   
			mov    ebx,DWORD PTR [esp]             
		mov    esi,DWORD PTR [esp+0x4]         
		mov    edi,DWORD PTR [esp+0x8]         
		add    esp,0xc                         
			ret                                    

	}
}

NAKED void put_2tap_qpel8_l3_3dnow(uint8_t *dst, uint8_t *src, int stride, int h, int off1, int off2)
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
put_2tap_qpel8_l3_3dnow_3958:        
		movq   mm0,QWORD PTR [edx+ebx*1]     
		pavgusb mm0,QWORD PTR [edx+esi*1]    
		pavgusb mm0,QWORD PTR [edx]          
		movq   QWORD PTR [edx+eax*1],mm0     
			add    edx,edi                       
			dec    ecx                           
			jne    put_2tap_qpel8_l3_3dnow_3958  
			mov    ebx,DWORD PTR [esp]           
		mov    esi,DWORD PTR [esp+0x4]       
		mov    edi,DWORD PTR [esp+0x8]       
		add    esp,0xc                       
			ret                                  

	}
}