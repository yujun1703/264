#define NAKED __declspec(naked)
typedef unsigned char  uint8_t;

NAKED void ff_h264_weight_16_mmx2(uint8_t *dst, int stride, int height, int log2_denom, int weight, int offset)
{
	__asm {
		push ebx                                   
		push esi                                   
		push edi                                   
		mov eax, [esp + 12 + 4 + 0*4]              
		mov ecx, [esp + 12 + 4 + 1*4]              
		mov edx, [esp + 12 + 4 + 2*4]              
		mov ebx, [esp + 12 + 4 + 3*4]              
		mov esi, [esp + 12 + 4 + 4*4]              
		mov edi, [esp + 12 + 4 + 5*4]              

		;line 75+1 libavcodec/x86/h264_weight.asm   
		add edi, edi                               
		;line 75+0 libavcodec/x86/h264_weight.asm   
		inc edi                                    
		movd mm3, esi                              
		movd mm5, edi                              
		movd mm6, ebx                              

		pslld mm5, mm6                             

		psrld mm5, 1                               
		pshufw mm3, mm3, 0                         
		pshufw mm5, mm5, 0                         

		pxor mm7, mm7                              
		;line 76+1 libavcodec/x86/h264_weight.asm   
nextrow:                                    
		movd mm0, [eax+0]                          
		;line 77+0 libavcodec/x86/h264_weight.asm   
		movd mm1, [eax+4]                          

		punpcklbw mm0, mm7                         

		punpcklbw mm1, mm7                         

		pmullw mm0, mm3                            

		pmullw mm1, mm3                            

		paddsw mm0, mm5                            

		paddsw mm1, mm5                            

		psraw mm0, mm6                             

		psraw mm1, mm6                             

		packuswb mm0, mm1                          
		;line 78+1 libavcodec/x86/h264_weight.asm   
		movq [eax ], mm0                           
		movd mm0, [eax+8]                          
		;line 79+0 libavcodec/x86/h264_weight.asm   
		movd mm1, [eax+12]                         

		punpcklbw mm0, mm7                         

		punpcklbw mm1, mm7                         

		pmullw mm0, mm3                            

		pmullw mm1, mm3                            

		paddsw mm0, mm5                            

		paddsw mm1, mm5                            

		psraw mm0, mm6                             

		psraw mm1, mm6                             

		packuswb mm0, mm1                          
		;line 80+1 libavcodec/x86/h264_weight.asm   
		movq [eax+8], mm0                          
		add eax, ecx                               
		dec edx                                    
		jnz nextrow                               
		pop edi                                    
		;line 84+0 libavcodec/x86/h264_weight.asm   
		pop esi                                    
		pop ebx                                    
		ret
	}
}

NAKED void ff_h264_weight_8_mmx2(uint8_t *dst, int stride, int height, int log2_denom, int weight, int offset)
{
	__asm {
		push ebx                               
		push esi                               
		push edi                               
		mov eax, [esp + 12 + 4 + 0*4]          
		mov ecx, [esp + 12 + 4 + 1*4]          
		mov edx, [esp + 12 + 4 + 2*4]          
		mov ebx, [esp + 12 + 4 + 3*4]          
		mov esi, [esp + 12 + 4 + 4*4]          
		mov edi, [esp + 12 + 4 + 5*4]          

		add edi, edi                           
		inc edi                                
		movd mm3, esi                          
		movd mm5, edi                          
		movd mm6, ebx                          

		pslld mm5, mm6                         

		psrld mm5, 1                           
		pshufw mm3, mm3, 0                     
		pshufw mm5, mm5, 0                     

		pxor mm7, mm7                          
nextrow:                                
		movd mm0, [eax+0]                      
		movd mm1, [eax+8/2]                    

		punpcklbw mm0, mm7                     

		punpcklbw mm1, mm7                     

		pmullw mm0, mm3                        

		pmullw mm1, mm3                        

		paddsw mm0, mm5                        

		paddsw mm1, mm5                        

		psraw mm0, mm6                         

		psraw mm1, mm6                         

		packuswb mm0, mm1                      
		movq [eax], mm0                        
		add eax, ecx                           
		dec edx                                
		jnz nextrow                           
		pop edi                                
		pop esi                                
		pop ebx                                
		ret
	}
}

NAKED void ff_h264_weight_16_sse2(uint8_t *dst, int stride, int height, int log2_denom, int weight, int offset)
{
	__asm {
		push ebx                                    
		push esi                                    
		push edi                                    
		mov eax, [esp + 12 + 4 + 0*4]               
		mov ecx, [esp + 12 + 4 + 1*4]               
		mov edx, [esp + 12 + 4 + 2*4]               
		mov ebx, [esp + 12 + 4 + 3*4]               
		mov esi, [esp + 12 + 4 + 4*4]               
		mov edi, [esp + 12 + 4 + 5*4]               

		add edi, edi                                
		inc edi                                     
		movd xmm3, esi                              
		movd xmm5, edi                              
		movd xmm6, ebx                              

		pslld xmm5, xmm6                            

		psrld xmm5, 1                               
		pshuflw xmm3, xmm3, 0                       
		pshuflw xmm5, xmm5, 0                       

		punpcklqdq xmm3, xmm3                       

		punpcklqdq xmm5, xmm5                       

		pxor xmm7, xmm7                             
nextrow:                                     
		movq xmm0, qword ptr[eax+0]                          
		movq xmm1, qword ptr[eax+16/2]                       

		punpcklbw xmm0, xmm7                        

		punpcklbw xmm1, xmm7                        

		pmullw xmm0, xmm3                           

		pmullw xmm1, xmm3                           

		paddsw xmm0, xmm5                           

		paddsw xmm1, xmm5                           

		psraw xmm0, xmm6                            

		psraw xmm1, xmm6                            

		packuswb xmm0, xmm1                         
		movdqa [eax], xmm0                          
		add eax, ecx                                
		dec edx                                     
		jnz nextrow                                
		pop edi                                     
		pop esi                                     
		pop ebx                                     
		ret
	}
}

NAKED void ff_h264_weight_4_mmx2(uint8_t *dst, int stride, int height, int log2_denom, int weight, int offset)
{
	__asm {
		push ebx                                   
		push esi                                   
		push edi                                   
		mov eax, [esp + 12 + 4 + 0*4]              
		mov ecx, [esp + 12 + 4 + 1*4]              
		mov edx, [esp + 12 + 4 + 2*4]              
		mov ebx, [esp + 12 + 4 + 3*4]              
		mov esi, [esp + 12 + 4 + 4*4]              
		mov edi, [esp + 12 + 4 + 5*4]              

		add edi, edi                               
		inc edi                                    
		movd mm3, esi                              
		movd mm5, edi                              
		movd mm6, ebx                              

		pslld mm5, mm6                             

		psrld mm5, 1                               
		pshufw mm3, mm3, 0                         
		pshufw mm5, mm5, 0                         

		pxor mm7, mm7                              
		sar edx, 1                                 
		lea ebx, [ecx*2]                           
nextrow:                                    
		movd mm0, [eax+0]                          
		movd mm1, [eax+ecx]                        

		punpcklbw mm0, mm7                         

		punpcklbw mm1, mm7                         

		pmullw mm0, mm3                            

		pmullw mm1, mm3                            

		paddsw mm0, mm5                            

		paddsw mm1, mm5                            

		psraw mm0, mm6                             

		psraw mm1, mm6                             

		packuswb mm0, mm1                          
		movd [eax], mm0                            

		psrlq mm0, 32                              
		movd [eax+ecx], mm0                        
		add eax, ebx                               
		dec edx                                    
		jnz nextrow                               
		pop edi                                    
		pop esi                                    
		pop ebx                                    
		ret
	}
}

NAKED void ff_h264_weight_8_sse2(uint8_t *dst, int stride, int height, int log2_denom, int weight, int offset)
{
	__asm {
		push ebx                              
		push esi                              
		push edi                              
		mov eax, [esp + 12 + 4 + 0*4]         
		mov ecx, [esp + 12 + 4 + 1*4]         
		mov edx, [esp + 12 + 4 + 2*4]         
		mov ebx, [esp + 12 + 4 + 3*4]         
		mov esi, [esp + 12 + 4 + 4*4]         
		mov edi, [esp + 12 + 4 + 5*4]         

		add edi, edi                          
		inc edi                               
		movd xmm3, esi                        
		movd xmm5, edi                        
		movd xmm6, ebx                        

		pslld xmm5, xmm6                      

		psrld xmm5, 1                         
		pshuflw xmm3, xmm3, 0                 
		pshuflw xmm5, xmm5, 0                 

		punpcklqdq xmm3, xmm3                 

		punpcklqdq xmm5, xmm5                 

		pxor xmm7, xmm7                       
		sar edx, 1                            
		lea ebx, [ecx*2]                      
nextrow:                               
		movq xmm0, qword ptr[eax+0]                    
		movq xmm1, qword ptr[eax+ecx]                  

		punpcklbw xmm0, xmm7                  

		punpcklbw xmm1, xmm7                  

		pmullw xmm0, xmm3                     

		pmullw xmm1, xmm3                     

		paddsw xmm0, xmm5                     

		paddsw xmm1, xmm5                     

		psraw xmm0, xmm6                      

		psraw xmm1, xmm6                      

		packuswb xmm0, xmm1                   
		movq qword ptr[eax], xmm0                      
		movhps [eax+ecx], xmm0                
		add eax, ebx                          
		dec edx                               
		jnz nextrow                          
		pop edi                               
		pop esi                               
		pop ebx                               
		ret
	}
}

NAKED void ff_h264_biweight_16_mmx2(uint8_t *dst, uint8_t *src, int stride, int height, int log2_denom, int weightd, int weights, int offset)
{
	__asm {
		push ebx                                  
		push esi                                  
		push edi                                  
		push ebp                                  
		mov eax, [esp + 16 + 4 + 0*4]             
		mov ecx, [esp + 16 + 4 + 1*4]             
		mov edx, [esp + 16 + 4 + 2*4]             
		mov ebx, [esp + 16 + 4 + 3*4]             
		mov esi, [esp + 16 + 4 + 4*4]             
		mov edi, [esp + 16 + 4 + 5*4]             
		mov ebp, [esp + 16 + 4 + 6*4]             

		;line 179+1 libavcodec/x86/h264_weight.asm 
		mov ebx, [esp + 16 + 32]                  
		;line 179+0 libavcodec/x86/h264_weight.asm 
		add ebx, 1                                
		or ebx, 1                                 
		add esi, 1                                
		movd mm3, edi                             
		movd mm4, ebp                             
		movd mm5, ebx                             
		movd mm6, esi                             

		pslld mm5, mm6                            

		psrld mm5, 1                              
		pshufw mm3, mm3, 0                        
		pshufw mm4, mm4, 0                        
		pshufw mm5, mm5, 0                        

		pxor mm7, mm7                             
		;line 180+1 libavcodec/x86/h264_weight.asm 
		mov ebx, [esp + 16 + 16]                  

nextrow:                                   
		movd mm0, [eax+0]                         
		;line 182+0 libavcodec/x86/h264_weight.asm 
		movd mm1, [ecx+0]                         

		punpcklbw mm0, mm7                        

		punpcklbw mm1, mm7                        

		pmullw mm0, mm3                           

		pmullw mm1, mm4                           

		paddsw mm0, mm1                           
		;line 183+1 libavcodec/x86/h264_weight.asm 
		movd mm1, [eax+4]                         
		;line 183+0 libavcodec/x86/h264_weight.asm 
		movd mm2, [ecx+4]                         

		punpcklbw mm1, mm7                        

		punpcklbw mm2, mm7                        

		pmullw mm1, mm3                           

		pmullw mm2, mm4                           

		paddsw mm1, mm2                           
		;line 184+1 libavcodec/x86/h264_weight.asm 

		;line 184+0 libavcodec/x86/h264_weight.asm 
		paddsw mm0, mm5                           

		paddsw mm1, mm5                           

		psraw mm0, mm6                            

		psraw mm1, mm6                            

		packuswb mm0, mm1                         
		;line 185+1 libavcodec/x86/h264_weight.asm 
		movq [eax], mm0                           
		movd mm0, [eax+8]                         
		;line 186+0 libavcodec/x86/h264_weight.asm 
		movd mm1, [ecx+8]                         

		punpcklbw mm0, mm7                        

		punpcklbw mm1, mm7                        

		pmullw mm0, mm3                           

		pmullw mm1, mm4                           

		paddsw mm0, mm1                           
		;line 187+1 libavcodec/x86/h264_weight.asm 
		movd mm1, [eax+12]                        
		;line 187+0 libavcodec/x86/h264_weight.asm 
		movd mm2, [ecx+12]                        

		punpcklbw mm1, mm7                        

		punpcklbw mm2, mm7                        

		pmullw mm1, mm3                           

		pmullw mm2, mm4                           

		paddsw mm1, mm2                           
		;line 188+1 libavcodec/x86/h264_weight.asm 

		;line 188+0 libavcodec/x86/h264_weight.asm 
		paddsw mm0, mm5                           

		paddsw mm1, mm5                           

		psraw mm0, mm6                            

		psraw mm1, mm6                            

		packuswb mm0, mm1                         
		;line 189+1 libavcodec/x86/h264_weight.asm 
		movq [eax+8], mm0                         
		add eax, edx                              
		add ecx, edx                              
		dec ebx                                   
		jnz nextrow                              
		pop ebp                                   
		;line 194+0 libavcodec/x86/h264_weight.asm 
		pop edi                                   
		pop esi                                   
		pop ebx                                   
		ret
	}
}

NAKED void ff_h264_biweight_8_mmx2(uint8_t *dst, uint8_t *src, int stride, int height, int log2_denom, int weightd, int weights, int offset)
{
	__asm {
		push ebx                                 
		push esi                                 
		push edi                                 
		push ebp                                 
		mov eax, [esp + 16 + 4 + 0*4]            
		mov ecx, [esp + 16 + 4 + 1*4]            
		mov edx, [esp + 16 + 4 + 2*4]            
		mov ebx, [esp + 16 + 4 + 3*4]            
		mov esi, [esp + 16 + 4 + 4*4]            
		mov edi, [esp + 16 + 4 + 5*4]            
		mov ebp, [esp + 16 + 4 + 6*4]            

		mov ebx, [esp + 16 + 32]                 
		add ebx, 1                               
		or ebx, 1                                
		add esi, 1                               
		movd mm3, edi                            
		movd mm4, ebp                            
		movd mm5, ebx                            
		movd mm6, esi                            

		pslld mm5, mm6                           

		psrld mm5, 1                             
		pshufw mm3, mm3, 0                       
		pshufw mm4, mm4, 0                       
		pshufw mm5, mm5, 0                       

		pxor mm7, mm7                            
		mov ebx, [esp + 16 + 16]                 
nextrow:                                  
		movd mm0, [eax+0]                        
		movd mm1, [ecx+0]                        

		punpcklbw mm0, mm7                       

		punpcklbw mm1, mm7                       

		pmullw mm0, mm3                          

		pmullw mm1, mm4                          

		paddsw mm0, mm1                          
		movd mm1, [eax+8/2]                      
		movd mm2, [ecx+8/2]                      

		punpcklbw mm1, mm7                       

		punpcklbw mm2, mm7                       

		pmullw mm1, mm3                          

		pmullw mm2, mm4                          

		paddsw mm1, mm2                          

		paddsw mm0, mm5                          

		paddsw mm1, mm5                          

		psraw mm0, mm6                           

		psraw mm1, mm6                           

		packuswb mm0, mm1                        
		movq [eax], mm0                          
		add eax, edx                             
		add ecx, edx                             
		dec ebx                                  
		jnz nextrow                             
		pop ebp                                  
		pop edi                                  
		pop esi                                  
		pop ebx                                  
		ret
	}
}

NAKED void ff_h264_biweight_16_sse2(uint8_t *dst, uint8_t *src, int stride, int height, int log2_denom, int weightd, int weights, int offset)
{
	__asm {
		push ebx                              
		push esi                              
		push edi                              
		push ebp                              
		mov eax, [esp + 16 + 4 + 0*4]         
		mov ecx, [esp + 16 + 4 + 1*4]         
		mov edx, [esp + 16 + 4 + 2*4]         
		mov ebx, [esp + 16 + 4 + 3*4]         
		mov esi, [esp + 16 + 4 + 4*4]         
		mov edi, [esp + 16 + 4 + 5*4]         
		mov ebp, [esp + 16 + 4 + 6*4]         

		mov ebx, [esp + 16 + 32]              
		add ebx, 1                            
		or ebx, 1                             
		add esi, 1                            
		movd xmm3, edi                        
		movd xmm4, ebp                        
		movd xmm5, ebx                        
		movd xmm6, esi                        

		pslld xmm5, xmm6                      

		psrld xmm5, 1                         
		pshuflw xmm3, xmm3, 0                 
		pshuflw xmm4, xmm4, 0                 
		pshuflw xmm5, xmm5, 0                 

		punpcklqdq xmm3, xmm3                 

		punpcklqdq xmm4, xmm4                 

		punpcklqdq xmm5, xmm5                 

		pxor xmm7, xmm7                       
		mov ebx, [esp + 16 + 16]              
nextrow:                               
		movq xmm0, qword ptr[eax+0]                    
		movq xmm1, qword ptr[ecx+0]                    

		punpcklbw xmm0, xmm7                  

		punpcklbw xmm1, xmm7                  

		pmullw xmm0, xmm3                     

		pmullw xmm1, xmm4                     

		paddsw xmm0, xmm1                     
		movq xmm1, qword ptr[eax+16/2]                 
		movq xmm2, qword ptr[ecx+16/2]                 

		punpcklbw xmm1, xmm7                  

		punpcklbw xmm2, xmm7                  

		pmullw xmm1, xmm3                     

		pmullw xmm2, xmm4                     

		paddsw xmm1, xmm2                     

		paddsw xmm0, xmm5                     

		paddsw xmm1, xmm5                     

		psraw xmm0, xmm6                      

		psraw xmm1, xmm6                      

		packuswb xmm0, xmm1                   
		movdqa [eax], xmm0                    
		add eax, edx                          
		add ecx, edx                          
		dec ebx                               
		jnz nextrow                          
		pop ebp                               
		pop edi                               
		pop esi                               
		pop ebx                               
		ret
	}
}

NAKED void ff_h264_biweight_4_mmx2(uint8_t *dst, uint8_t *src, int stride, int height, int log2_denom, int weightd, int weights, int offset)
{
	__asm {
		push ebx                                      
		push esi                                      
		push edi                                      
		push ebp                                      
		mov eax, [esp + 16 + 4 + 0*4]                 
		mov ecx, [esp + 16 + 4 + 1*4]                 
		mov edx, [esp + 16 + 4 + 2*4]                 
		mov ebx, [esp + 16 + 4 + 3*4]                 
		mov esi, [esp + 16 + 4 + 4*4]                 
		mov edi, [esp + 16 + 4 + 5*4]                 
		mov ebp, [esp + 16 + 4 + 6*4]                 

		mov ebx, [esp + 16 + 32]                      
		add ebx, 1                                    
		or ebx, 1                                     
		add esi, 1                                    
		movd mm3, edi                                 
		movd mm4, ebp                                 
		movd mm5, ebx                                 
		movd mm6, esi                                 

		pslld mm5, mm6                                

		psrld mm5, 1                                  
		pshufw mm3, mm3, 0                            
		pshufw mm4, mm4, 0                            
		pshufw mm5, mm5, 0                            

		pxor mm7, mm7                                 
		mov ebx, [esp + 16 + 16]                      
		sar ebx, 1                                    
		lea esi, [edx*2]                              
nextrow:                                       
		movd mm0, [eax+0]                             
		movd mm1, [ecx+0]                             

		punpcklbw mm0, mm7                            

		punpcklbw mm1, mm7                            

		pmullw mm0, mm3                               

		pmullw mm1, mm4                               

		paddsw mm0, mm1                               
		movd mm1, [eax+edx]                           
		movd mm2, [ecx+edx]                           

		punpcklbw mm1, mm7                            

		punpcklbw mm2, mm7                            

		pmullw mm1, mm3                               

		pmullw mm2, mm4                               

		paddsw mm1, mm2                               

		paddsw mm0, mm5                               

		paddsw mm1, mm5                               

		psraw mm0, mm6                                

		psraw mm1, mm6                                

		packuswb mm0, mm1                             
		movd [eax], mm0                               

		psrlq mm0, 32                                 
		movd [eax+edx], mm0                           
		add eax, esi                                  
		add ecx, esi                                  
		dec ebx                                       
		jnz nextrow                                  
		pop ebp                                       
		pop edi                                       
		pop esi                                       
		pop ebx                                       
		ret                                           

	}
}

NAKED void ff_h264_biweight_8_sse2(uint8_t *dst, uint8_t *src, int stride, int height, int log2_denom, int weightd, int weights, int offset)
{
	__asm {
		push ebx                           
		push esi                           
		push edi                           
		push ebp                           
		mov eax, [esp + 16 + 4 + 0*4]      
		mov ecx, [esp + 16 + 4 + 1*4]      
		mov edx, [esp + 16 + 4 + 2*4]      
		mov ebx, [esp + 16 + 4 + 3*4]      
		mov esi, [esp + 16 + 4 + 4*4]      
		mov edi, [esp + 16 + 4 + 5*4]      
		mov ebp, [esp + 16 + 4 + 6*4]      

		mov ebx, [esp + 16 + 32]           
		add ebx, 1                         
		or ebx, 1                          
		add esi, 1                         
		movd xmm3, edi                     
		movd xmm4, ebp                     
		movd xmm5, ebx                     
		movd xmm6, esi                     

		pslld xmm5, xmm6                   

		psrld xmm5, 1                      
		pshuflw xmm3, xmm3, 0              
		pshuflw xmm4, xmm4, 0              
		pshuflw xmm5, xmm5, 0              

		punpcklqdq xmm3, xmm3              

		punpcklqdq xmm4, xmm4              

		punpcklqdq xmm5, xmm5              

		pxor xmm7, xmm7                    
		mov ebx, [esp + 16 + 16]           
		sar ebx, 1                         
		lea esi, [edx*2]                   

nextrow:                            
		movq xmm0, qword ptr[eax+0]                 
		movq xmm1, qword ptr[ecx+0]                 

		punpcklbw xmm0, xmm7               

		punpcklbw xmm1, xmm7               

		pmullw xmm0, xmm3                  

		pmullw xmm1, xmm4                  

		paddsw xmm0, xmm1                  
		movq xmm1, qword ptr[eax+edx]               
		movq xmm2, qword ptr[ecx+edx]               

		punpcklbw xmm1, xmm7               

		punpcklbw xmm2, xmm7               

		pmullw xmm1, xmm3                  

		pmullw xmm2, xmm4                  

		paddsw xmm1, xmm2                  

		paddsw xmm0, xmm5                  

		paddsw xmm1, xmm5                  

		psraw xmm0, xmm6                   

		psraw xmm1, xmm6                   

		packuswb xmm0, xmm1                
		movq qword ptr[eax], xmm0                   
		movhps [eax+edx], xmm0             
		add eax, esi                       
		add ecx, esi                       
		dec ebx                            
		jnz nextrow                       
		pop ebp                            
		pop edi                            
		pop esi                            
		pop ebx                            
		ret                                

	}
}

NAKED void ff_h264_biweight_16_ssse3(uint8_t *dst, uint8_t *src, int stride, int height, int log2_denom, int weightd, int weights, int offset)
{
	__asm {
		push ebx                                 
		push esi                                 
		push edi                                 
		push ebp                                 
		mov eax, [esp + 16 + 4 + 0*4]            
		mov ecx, [esp + 16 + 4 + 1*4]            
		mov edx, [esp + 16 + 4 + 2*4]            
		mov ebx, [esp + 16 + 4 + 3*4]            
		mov esi, [esp + 16 + 4 + 4*4]            
		mov edi, [esp + 16 + 4 + 5*4]            
		mov ebp, [esp + 16 + 4 + 6*4]            

		;line 288+1 libavcodec/x86/h264_weight.asm
		mov ebx, [esp + 16 + 32]                 
		;line 288+0 libavcodec/x86/h264_weight.asm
		add ebx, 1                               
		or ebx, 1                                
		add esi, 1                               
		cmp edi, 128                             
		jne normal                              
		sar edi, 1                               
		sar ebp, 1                               
		sar ebx, 1                               
		sub esi, 1

normal:                                   
		movd xmm4, edi                           
		movd xmm0, ebp                           
		movd xmm5, ebx                           
		movd xmm6, esi                           

		pslld xmm5, xmm6                         

		psrld xmm5, 1                            

		punpcklbw xmm4, xmm0                     
		pshuflw xmm4, xmm4, 0                    
		pshuflw xmm5, xmm5, 0                    

		punpcklqdq xmm4, xmm4                    

		punpcklqdq xmm5, xmm5                    
		;line 289+1 libavcodec/x86/h264_weight.asm
		mov ebx, [esp + 16 + 16]                 

nextrow:                                  
		movq xmm0, qword ptr[eax]                         
		movq xmm2, qword ptr[eax+8]                       
		movq xmm3, qword ptr[ecx+8]                       

		;line 295+0 libavcodec/x86/h264_weight.asm
		punpcklbw xmm0, [ecx]                    
		;line 296+1 libavcodec/x86/h264_weight.asm

		;line 296+0 libavcodec/x86/h264_weight.asm
		punpcklbw xmm2, xmm3                     
		;line 297+1 libavcodec/x86/h264_weight.asm

		;line 297+0 libavcodec/x86/h264_weight.asm
		pmaddubsw xmm0, xmm4                     

		pmaddubsw xmm2, xmm4                     

		paddsw xmm0, xmm5                        

		paddsw xmm2, xmm5                        

		psraw xmm0, xmm6                         

		psraw xmm2, xmm6                         

		packuswb xmm0, xmm2                      
		;line 298+1 libavcodec/x86/h264_weight.asm
		movdqa [eax], xmm0                       
		add eax, edx                             
		add ecx, edx                             
		dec ebx                                  
		jnz nextrow                             
		pop ebp                                  
		;line 303+0 libavcodec/x86/h264_weight.asm
		pop edi                                  
		pop esi                                  
		pop ebx                                  
		ret                                      

	}
}

NAKED void ff_h264_biweight_8_ssse3(uint8_t *dst, uint8_t *src, int stride, int height, int log2_denom, int weightd, int weights, int offset)
{
	__asm {
		push ebx                                 
		push esi                                 
		push edi                                 
		push ebp                                 
		mov eax, [esp + 16 + 4 + 0*4]            
		mov ecx, [esp + 16 + 4 + 1*4]            
		mov edx, [esp + 16 + 4 + 2*4]            
		mov ebx, [esp + 16 + 4 + 3*4]            
		mov esi, [esp + 16 + 4 + 4*4]            
		mov edi, [esp + 16 + 4 + 5*4]            
		mov ebp, [esp + 16 + 4 + 6*4]            

		;line 307+1 libavcodec/x86/h264_weight.asm
		mov ebx, [esp + 16 + 32]                 
		;line 307+0 libavcodec/x86/h264_weight.asm
		add ebx, 1                               
		or ebx, 1                                
		add esi, 1                               
		cmp edi, 128                             
		jne normal                              
		sar edi, 1                               
		sar ebp, 1                               
		sar ebx, 1                               
		sub esi, 1                               
normal:                                   
		movd xmm4, edi                           
		movd xmm0, ebp                           
		movd xmm5, ebx                           
		movd xmm6, esi                           

		pslld xmm5, xmm6                         

		psrld xmm5, 1                            

		punpcklbw xmm4, xmm0                     
		pshuflw xmm4, xmm4, 0                    
		pshuflw xmm5, xmm5, 0                    

		punpcklqdq xmm4, xmm4                    

		punpcklqdq xmm5, xmm5                    
		;line 308+1 libavcodec/x86/h264_weight.asm
		mov ebx, [esp + 16 + 16]                 
		sar ebx, 1                               
		lea esi, [edx*2]                         

nextrow:                                  
		movq xmm0, qword ptr[eax]                         
		movq xmm1, qword ptr[ecx]                         
		movq xmm2, qword ptr[eax+edx]                     
		movq xmm3, qword ptr[ecx+edx]                     

		;line 317+0 libavcodec/x86/h264_weight.asm
		punpcklbw xmm0, xmm1                     
		;line 318+1 libavcodec/x86/h264_weight.asm

		;line 318+0 libavcodec/x86/h264_weight.asm
		punpcklbw xmm2, xmm3                     
		;line 319+1 libavcodec/x86/h264_weight.asm

		;line 319+0 libavcodec/x86/h264_weight.asm
		pmaddubsw xmm0, xmm4                     

		pmaddubsw xmm2, xmm4                     

		paddsw xmm0, xmm5                        

		paddsw xmm2, xmm5                        

		psraw xmm0, xmm6                         

		psraw xmm2, xmm6                         

		packuswb xmm0, xmm2                      
		;line 320+1 libavcodec/x86/h264_weight.asm
		movq qword ptr[eax], xmm0                         
		movhps [eax+edx], xmm0                   
		add eax, esi                             
		add ecx, esi                             
		dec ebx                                  
		jnz nextrow                             
		pop ebp                                  
		;line 326+0 libavcodec/x86/h264_weight.asm
		pop edi                                  
		pop esi                                  
		pop ebx                                  
		ret
	}
}

