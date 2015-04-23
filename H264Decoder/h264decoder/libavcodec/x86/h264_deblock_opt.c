#include "dsputil_mmx.h"

//typedef unsigned char uint8_t;
//typedef char int8_t;


//extern uint8_t ff_pb_A1[16];
//extern uint8_t ff_pb_3[16];
//extern uint8_t ff_pb_1[16];
//extern uint8_t ff_pb_0[16];
//
//extern short   ff_pw_4[8];
//extern short   ff_pw_3[8];
//extern short   ff_pw_2[8];
//extern short   pw_pixel_max[8];


// 1
void __declspec(naked) ff_deblock_v_chroma_8_mmxext(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
		push ebx                                                    
		push esi                                                    
		push edi                                                    
		mov eax, [esp + 12 + 4 + 0*4]                               
		mov ecx, [esp + 12 + 4 + 1*4]                               
		mov edx, [esp + 12 + 4 + 2*4]                               
		mov ebx, [esp + 12 + 4 + 3*4]                               
		mov esi, [esp + 12 + 4 + 4*4]                               

		dec edx                                                     
		dec ebx                                                     
		mov edi, eax                                                
		sub edi, ecx                                                
		sub edi, ecx                                                
		movq mm0, [edi]                                             
		movq mm1, [edi+ecx]                                         
		movq mm2, [eax]                                             
		movq mm3, [eax+ecx]                                         

		movd mm4, edx                                      

		movd mm5, ebx                                      
		pshufw mm4, mm4, (0)*0x55                          
		pshufw mm5, mm5, (0)*0x55                          
		                                                   
		packuswb mm4, mm4		                                                   
		packuswb mm5, mm5                                  
		movq mm6, mm2                                      
		movq mm7, mm1		                                                   
		psubusb mm6, mm1		                                                   
		psubusb mm7, mm2		                                                   
		por mm7, mm6                                       
		                                                   
		psubusb mm7, mm4                                   
		movq mm6, mm1                                      
		movq mm4, mm0                                      
		                                                   
		psubusb mm6, mm0                                   
		                                                   
		psubusb mm4, mm1                                   
		                                                   
		por mm4, mm6                                       
		                                                   
		psubusb mm4, mm5                                   
		                                                   
		por mm7, mm4                                       
		movq mm6, mm2                                      
		movq mm4, mm3                                      
		                                                   
		psubusb mm6, mm3                                   
		                                                   
		psubusb mm4, mm2                                   
		                                                   
		por mm4, mm6                                       
		                                                   
		psubusb mm4, mm5                                   
		                                                   
		por mm7, mm4                                       
		                                                   
		pxor mm6, mm6                                      
		                                                   
		pcmpeqb mm7, mm6
		movd mm6, [esi]
		punpcklbw mm6, mm6
		pand mm7, mm6
		pcmpeqb mm4, mm4                                   
		movq mm5, mm1                                      
		pxor mm5, mm2                                      
		pxor mm3, mm4                                      
		pand mm5, [ff_pb_1]                                
		pavgb mm3, mm0                                     
		pxor mm4, mm1                                      
		pavgb mm3, [ff_pb_3]                               
		pavgb mm4, mm2                                     
		pavgb mm3, mm5                                     
		movq mm6, [ff_pb_A1]                               
		paddusb mm3, mm4                                   
		psubusb mm6, mm3                                   
		psubusb mm3, [ff_pb_A1]                            
		pminub mm6, mm7                                    
		pminub mm3, mm7                                    
		psubusb mm1, mm6                                   
		psubusb mm2, mm3                                   
		paddusb mm1, mm3                                   
		paddusb mm2, mm6                                   

		movq [edi+ecx], mm1                                         
		movq [eax], mm2                                             
		pop edi                                                     
		pop esi                                                     
		pop ebx                                                     
		ret
	 }
}

// 3
void __declspec(naked) ff_deblock_h_chroma_8_mmxext(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
       push ebx                                                
       push esi                                                
       push edi                                                
       push ebp                                                
       mov eax, [esp + 16 + 4 + 0*4]                           
       mov ecx, [esp + 16 + 4 + 1*4]                           
       mov edx, [esp + 16 + 4 + 2*4]                           
       mov ebx, [esp + 16 + 4 + 3*4]                           
       mov esi, [esp + 16 + 4 + 4*4]                           
                                                               
       dec edx                                                 
       dec ebx                                                 
       sub eax, 2                                              
       lea ebp, [ecx+ecx*2]                                        
       mov edi, eax                                            
       add eax, ebp                                            
       movd mm0, [edi]                                         
       movd mm2, [edi+ecx]                                     
       movd mm1, [edi+ecx*2]                                   
       movd mm3, [eax]                                         
                                                               
       punpcklbw mm0, mm2                                      
                                                               
       punpcklbw mm1, mm3                                      
       movq mm2, mm0                                           
                                                               
       punpcklwd mm0, mm1                                      
                                                               
       punpckhwd mm2, mm1                                      
                                                               
       movd mm4, [eax+ecx]                                     
       movd mm6, [eax+ecx*2]                                   
       movd mm5, [eax+ebp]                                     
       movd mm7, [eax+ecx*4]                                   
                                                               
       punpcklbw mm4, mm6                                      
                                                               
       punpcklbw mm5, mm7                                      
       movq mm6, mm4                                           
                                                               
       punpcklwd mm4, mm5                                      
                                                               
       punpckhwd mm6, mm5                                      
                                                               
                                                               
       movq mm1, mm0                                           
       punpckhdq mm1, mm4                                      
                                                               
       movq mm3, mm2                                           
       punpckhdq mm3, mm6                                      
                                                               
       punpckldq mm0, mm4                                      
                                                               
       punpckldq mm2, mm6                                      
       movq [esp + 16 + 4], mm0                                
       movq [esp + 16 + 12], mm3                               
       movd mm4, edx                                           
       movd mm5, ebx                                           
       pshufw mm4, mm4, (0)*0x55                               
       pshufw mm5, mm5, (0)*0x55                               
                                                               
       packuswb mm4, mm4                                       
                                                               
       packuswb mm5, mm5                                       
       movq mm6, mm2                                           
       movq mm7, mm1                                           
                                                               
       psubusb mm6, mm1                                        
                                                               
       psubusb mm7, mm2                                        
                                                               
       por mm7, mm6                                            
                                                               
       psubusb mm7, mm4                                        
       movq mm6, mm1                                           
       movq mm4, mm0                                           
                                                               
       psubusb mm6, mm0                                        
                                                               
       psubusb mm4, mm1                                        
                                                               
       por mm4, mm6                                            
                                                               
       psubusb mm4, mm5                                        
                                                               
       por mm7, mm4                                            
       movq mm6, mm2                                           
       movq mm4, mm3                                           
                                                               
       psubusb mm6, mm3                                        
                                                               
       psubusb mm4, mm2                                        
                                                               
       por mm4, mm6                                            
                                                               
       psubusb mm4, mm5                                        
                                                               
       por mm7, mm4                                            
                                                               
       pxor mm6, mm6                                           
                                                               
       pcmpeqb mm7, mm6                                        
       movd mm6, [esi]                                         
                                                               
       punpcklbw mm6, mm6                                      
                                                               
       pand mm7, mm6                                           
                                                               
       pcmpeqb mm4, mm4                                        
                                                               
       movq mm5, mm1                                           
       pxor mm5, mm2                                           
                                                               
       pxor mm3, mm4                                           
                                                               
       pand mm5, [ff_pb_1]                                     
                                                               
       pavgb mm3, mm0                                          
                                                               
       pxor mm4, mm1                                           
                                                               
       pavgb mm3, [ff_pb_3]                                    
                                                               
       pavgb mm4, mm2                                          
                                                               
       pavgb mm3, mm5                                          
       movq mm6, [ff_pb_A1]                                    
                                                               
       paddusb mm3, mm4                                        
                                                               
       psubusb mm6, mm3                                        
                                                               
       psubusb mm3, [ff_pb_A1]                                 
                                                               
       pminub mm6, mm7                                         
                                                               
       pminub mm3, mm7                                         
                                                               
       psubusb mm1, mm6                                        
                                                               
       psubusb mm2, mm3                                        
                                                               
       paddusb mm1, mm3                                        
                                                               
       paddusb mm2, mm6                                        
       movq mm0, [esp + 16 + 4]                                
       movq mm3, [esp + 16 + 12]                               
                                                               
       movq mm4, mm0                                           
       punpckhdq mm4, mm0                                      
                                                               
       movq mm5, mm1                                           
       punpckhdq mm5, mm1                                      
                                                               
       movq mm6, mm2                                           
       punpckhdq mm6, mm2                                      
                                                               
                                                               
       punpcklbw mm0, mm1                                      
                                                               
       punpcklbw mm2, mm3                                      
                                                               
       movq mm1, mm0                                           
       punpcklwd mm1, mm2                                      
                                                               
       punpckhwd mm0, mm2                                      
       movd [edi], mm1                                         
                                                               
       punpckhdq mm1, mm1                                      
       movd [edi+ecx], mm1                                     
       movd [edi+ecx*2], mm0                                   
                                                               
       punpckhdq mm0, mm0                                      
       movd [eax], mm0                                         
                                                               
                                                               
       punpckhdq mm3, mm3                                      
                                                               
       punpcklbw mm4, mm5                                      
                                                               
       punpcklbw mm6, mm3                                      
                                                               
       movq mm5, mm4                                           
       punpcklwd mm5, mm6                                      
                                                               
       punpckhwd mm4, mm6                                      
       movd [eax+ecx], mm5                                     
                                                               
       punpckhdq mm5, mm5                                      
       movd [eax+ecx*2], mm5                                   
       movd [eax+ebp], mm4                                     
                                                               
       punpckhdq mm4, mm4                                      
       movd [eax+ecx*4], mm4                                   
       pop ebp                                                 
       pop edi                                                 
       pop esi                                                 
       pop ebx                                                 
       ret
	 }
}

void __declspec(naked) ff_deblock_v8_luma_8_mmxext(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
   push ebx                      
   push esi                      
   mov eax, [esp + 8 + 4 + 0*4]  
   mov ecx, [esp + 8 + 4 + 1*4]  
   mov edx, [esp + 8 + 4 + 2*4]  
   mov ebx, [esp + 8 + 4 + 3*4]  
   mov esi, [esp + 8 + 4 + 4*4]  
                                 
   lea esi, [ecx+ecx*2]
   dec edx                       
   neg esi                       
   dec ebx                       
   add esi, eax                  
   sub esp, 20                   
                                 
   movq mm0, [esi+ecx]           
   movq mm1, [esi+2*ecx]         
   movq mm2, [eax]               
   movq mm3, [eax+ecx]           
   movd mm4, edx                 
   movd mm5, ebx                 
   pshufw mm4, mm4, (0)*0x55     
   pshufw mm5, mm5, (0)*0x55     
                                 
   packuswb mm4, mm4             
                                 
   packuswb mm5, mm5             
   movq mm6, mm2                 
   movq mm7, mm1                 
                                 
   psubusb mm6, mm1              
                                 
   psubusb mm7, mm2              
                                 
   por mm7, mm6                  
                                 
   psubusb mm7, mm4              
   movq mm6, mm1                 
   movq mm4, mm0                 
                                 
   psubusb mm6, mm0              
                                 
   psubusb mm4, mm1              
                                 
   por mm4, mm6                  
                                 
   psubusb mm4, mm5              
                                 
   por mm7, mm4                  
   movq mm6, mm2                 
   movq mm4, mm3                 
                                 
   psubusb mm6, mm3              
                                 
   psubusb mm4, mm2              
                                 
   por mm4, mm6                  
                                 
   psubusb mm4, mm5              
                                 
   por mm7, mm4                  
                                 
   pxor mm6, mm6                 
                                 
   pcmpeqb mm7, mm6              
                                 
   mov ebx, dword ptr[esp + 28 + 20]
                                 
   pcmpeqb mm3, mm3              
   movd mm4, [ebx]               
                                 
   punpcklbw mm4, mm4            
                                 
   punpcklbw mm4, mm4            
   movq [esp+8], mm4             
                                 
   pcmpgtb mm4, mm3              
   movq mm3, [esi]               
                                 
   pand mm4, mm7                 
   movq [esp], mm4               
                                 
   movq mm7, mm3                 
   movq mm6, mm1                 
                                 
   psubusb mm7, mm1              
                                 
   psubusb mm6, mm3              
                                 
   psubusb mm7, mm5              
                                 
   psubusb mm6, mm5              
                                 
   pcmpeqb mm6, mm7              
                                 
   pand mm6, mm4                 
                                 
   pand mm4, [esp+8]             
                                 
   movq mm7, mm4                 
   psubb mm7, mm6                
                                 
   pand mm6, mm4                 
                                 
   movq mm4, mm1                 
   pavgb mm4, mm2                
                                 
   pavgb mm3, mm4                
                                 
   pxor mm4, [esi]               
                                 
   pand mm4, [ff_pb_1]           
                                 
   psubusb mm3, mm4              
                                 
   movq mm4, mm0                 
   psubusb mm4, mm6              
                                 
   paddusb mm6, mm0              
                                 
   pmaxub mm3, mm4               
                                 
   pminub mm3, mm6               
   movq [esi+ecx], mm3           
                                 
   movq mm4, [eax+2*ecx]         
   movq mm3, mm4                 
   movq mm6, mm2                 
                                 
   psubusb mm3, mm2              
                                 
   psubusb mm6, mm4              
                                 
   psubusb mm3, mm5              
                                 
   psubusb mm6, mm5              
                                 
   pcmpeqb mm6, mm3              
                                 
   pand mm6, [esp]               
   movq mm5, [esp+8]             
                                 
   psubb mm7, mm6                
                                 
   pand mm5, mm6                 
   movq mm3, [eax+ecx]           
                                 
   movq mm6, mm1                 
   pavgb mm6, mm2                
                                 
   pavgb mm4, mm6                
                                 
   pxor mm6, [eax+2*ecx]         
                                 
   pand mm6, [ff_pb_1]           
                                 
   psubusb mm4, mm6              
                                 
   movq mm6, mm3                 
   psubusb mm6, mm5              
                                 
   paddusb mm5, mm3              
                                 
   pmaxub mm4, mm6               
                                 
   pminub mm4, mm5               
   movq [eax+ecx], mm4           
                                 
                                 
   pcmpeqb mm4, mm4              
                                 
   movq mm5, mm1                 
   pxor mm5, mm2                 
                                 
   pxor mm3, mm4                 
                                 
   pand mm5, [ff_pb_1]           
                                 
   pavgb mm3, mm0                
                                 
   pxor mm4, mm1                 
                                 
   pavgb mm3, [ff_pb_3]          
                                 
   pavgb mm4, mm2                
                                 
   pavgb mm3, mm5                
   movq mm6, [ff_pb_A1]          
                                 
   paddusb mm3, mm4              
                                 
   psubusb mm6, mm3              
                                 
   psubusb mm3, [ff_pb_A1]       
                                 
   pminub mm6, mm7               
                                 
   pminub mm3, mm7               
                                 
   psubusb mm1, mm6              
                                 
   psubusb mm2, mm3              
                                 
   paddusb mm1, mm3              
                                 
   paddusb mm2, mm6              
   movq [esi+2*ecx], mm1         
   movq [eax], mm2               
   add esp, 20                   
   pop esi                       
   pop ebx                       
   ret                           

	}
}

// 6
void __declspec(naked) ff_deblock_h_luma_8_mmxext(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
     push ebx                                   
     push esi                                   
                                                
     mov eax, dword ptr[esp + 8 + 4]               
     mov ebx, [esp + 8 + 8]                     
     lea esi, [ebx+ebx*2]                           
     sub eax, 4                                 
     lea ecx, [eax+esi]                         
     sub esp, 112                               
                                                
                                                
     movq mm0, [eax]                            
     movq mm1, [eax+ebx]                        
     movq mm2, [eax+ebx*2]                      
     movq mm3, [ecx]                            
     movq mm4, [ecx+ebx]                        
     movq mm5, [ecx+ebx*2]                      
     movq mm6, [ecx+esi]                        
     movq mm7, mm0                              
                                                
     punpcklbw mm0, mm1                         
                                                
     punpckhbw mm7, mm1                         
     movq mm1, mm2                              
                                                
     punpcklbw mm2, mm3                         
                                                
     punpckhbw mm1, mm3                         
     movq mm3, mm4                              
                                                
     punpcklbw mm4, mm5                         
                                                
     punpckhbw mm3, mm5                         
     movq [esp+12+0x10], mm1                    
                                                
     movq mm5, mm6                              
     punpckhbw mm5, [ecx+ebx*4]                 
                                                
     punpcklbw mm6, [ecx+ebx*4]                 
     movq mm1, mm0                              
                                                
     punpcklwd mm0, mm2                         
                                                
     punpckhwd mm1, mm2                         
     movq mm2, mm4                              
                                                
     punpcklwd mm4, mm6                         
                                                
     punpckhwd mm2, mm6                         
                                                
     punpckhdq mm0, mm4                         
     movq [esp+12+0x00], mm0                    
                                                
     movq mm6, mm7                              
     punpckhwd mm6, [esp+12+0x10]               
                                                
     punpcklwd mm7, [esp+12+0x10]               
     movq mm0, mm3                              
                                                
     punpcklwd mm3, mm5                         
                                                
     punpckhwd mm0, mm5                         
     movq mm5, mm7                              
                                                
     punpckldq mm7, mm3                         
                                                
     punpckhdq mm5, mm3                         
     movq mm3, mm1                              
                                                
     punpckldq mm1, mm2                         
                                                
     punpckhdq mm3, mm2                         
                                                
     punpckldq mm6, mm0                         
     movq [esp+12+0x10], mm1                    
     movq [esp+12+0x20], mm3                    
     movq [esp+12+0x30], mm7                    
     movq [esp+12+0x40], mm5                    
     movq [esp+12+0x50], mm6                    
     lea eax, [eax+ebx*8]                       
     lea ecx, [ecx+ebx*8]                       
     movq mm0, [eax]                            
     movq mm1, [eax+ebx]                        
     movq mm2, [eax+ebx*2]                      
     movq mm3, [ecx]                            
     movq mm4, [ecx+ebx]                        
     movq mm5, [ecx+ebx*2]                      
     movq mm6, [ecx+esi]                        
     movq mm7, mm0                              
                                                
     punpcklbw mm0, mm1                         
                                                
     punpckhbw mm7, mm1                         
     movq mm1, mm2                              
                                                
     punpcklbw mm2, mm3                         
                                                
     punpckhbw mm1, mm3                         
     movq mm3, mm4                              
                                                
     punpcklbw mm4, mm5                         
                                                
     punpckhbw mm3, mm5                         
     movq [esp+12+8+0x10], mm1                  
                                                
     movq mm5, mm6                              
     punpckhbw mm5, [ecx+ebx*4]                 
                                                
     punpcklbw mm6, [ecx+ebx*4]                 
     movq mm1, mm0                              
                                                
     punpcklwd mm0, mm2                         
                                                
     punpckhwd mm1, mm2                         
     movq mm2, mm4                              
                                                
     punpcklwd mm4, mm6                         
                                                
     punpckhwd mm2, mm6                         
                                                
     punpckhdq mm0, mm4                         
     movq [esp+12+8+0x00], mm0                  
                                                
     movq mm6, mm7                              
     punpckhwd mm6, [esp+12+8+0x10]             
                                                
     punpcklwd mm7, [esp+12+8+0x10]             
     movq mm0, mm3                              
                                                
     punpcklwd mm3, mm5                         
                                                
     punpckhwd mm0, mm5                         
     movq mm5, mm7                              
                                                
     punpckldq mm7, mm3                         
                                                
     punpckhdq mm5, mm3                         
     movq mm3, mm1                              
                                                
     punpckldq mm1, mm2                         
                                                
     punpckhdq mm3, mm2                         
                                                
     punpckldq mm6, mm0                         
     movq [esp+12+8+0x10], mm1                  
     movq [esp+12+8+0x20], mm3                  
     movq [esp+12+8+0x30], mm7                  
     movq [esp+12+8+0x40], mm5                  
     movq [esp+12+8+0x50], mm6                  
                                                
                                                
     lea eax, [esp+12+0x30]                     
     push dword ptr[esp + 120 + 20]                
     push dword ptr[esp + 124 + 16]                
     push dword ptr[esp + 128 + 12]                
     push 16                              
     push eax                             
                                                
     call ff_deblock_v8_luma_8_mmxext           
     add dword ptr[esp ], 8                        
     add dword ptr[esp+16], 2                      
                                                
     call ff_deblock_v8_luma_8_mmxext           
     add esp, 20                                
                                                
                                                
     mov eax, dword ptr[esp + 120 + 4]             
     sub eax, 2                                 
                                                
     movq mm0, [esp+12+0x10]                    
     movq mm1, [esp+12+0x20]                    
     lea ecx, [eax+esi]                         
     movq mm2, [esp+12+0x30]                    
     movq mm3, [esp+12+0x40]                    
                                                
     movq mm4, mm0                              
     punpckhdq mm4, mm0                         
                                                
     movq mm5, mm1                              
     punpckhdq mm5, mm1                         
                                                
     movq mm6, mm2                              
     punpckhdq mm6, mm2                         
                                                
                                                
     punpcklbw mm0, mm1                         
                                                
     punpcklbw mm2, mm3                         
                                                
     movq mm1, mm0                              
     punpcklwd mm1, mm2                         
                                                
     punpckhwd mm0, mm2                         
     movd [eax], mm1                            
                                                
     punpckhdq mm1, mm1                         
     movd [eax+ebx], mm1                        
     movd [eax+ebx*2], mm0                      
                                                
     punpckhdq mm0, mm0                         
     movd [ecx], mm0                            
                                                
                                                
     punpckhdq mm3, mm3                         
                                                
     punpcklbw mm4, mm5                         
                                                
     punpcklbw mm6, mm3                         
                                                
     movq mm5, mm4                              
     punpcklwd mm5, mm6                         
                                                
     punpckhwd mm4, mm6                         
     movd [ecx+ebx], mm5                        
                                                
     punpckhdq mm5, mm5                         
     movd [ecx+ebx*2], mm5                      
     movd [ecx+esi], mm4                        
                                                
     punpckhdq mm4, mm4                         
     movd [ecx+ebx*4], mm4                      
                                                
     lea eax, [eax+ebx*8]                       
     lea ecx, [ecx+ebx*8]                       
     movq mm0, [esp+12+0x18]                    
     movq mm1, [esp+12+0x28]                    
     movq mm2, [esp+12+0x38]                    
     movq mm3, [esp+12+0x48]                    
                                                
     movq mm4, mm0                              
     punpckhdq mm4, mm0                         
                                                
     movq mm5, mm1                              
     punpckhdq mm5, mm1                         
                                                
     movq mm6, mm2                              
     punpckhdq mm6, mm2                         
                                                
                                                
     punpcklbw mm0, mm1                         
                                                
     punpcklbw mm2, mm3                         
                                                
     movq mm1, mm0                              
     punpcklwd mm1, mm2                         
                                                
     punpckhwd mm0, mm2                         
     movd [eax], mm1                            
                                                
     punpckhdq mm1, mm1                         
     movd [eax+ebx], mm1                        
     movd [eax+ebx*2], mm0                      
                                                
     punpckhdq mm0, mm0                         
     movd [ecx], mm0                            
                                                
                                                
     punpckhdq mm3, mm3                         
                                                
     punpcklbw mm4, mm5                         
                                                
     punpcklbw mm6, mm3                         
                                                
     movq mm5, mm4                              
     punpcklwd mm5, mm6                         
                                                
     punpckhwd mm4, mm6                         
     movd [ecx+ebx], mm5                        
                                                
     punpckhdq mm5, mm5                         
     movd [ecx+ebx*2], mm5                      
     movd [ecx+esi], mm4                        
                                                
     punpckhdq mm4, mm4                         
     movd [ecx+ebx*4], mm4                      
                                                
     add esp, 112                               
     pop esi                                    
     pop ebx                                    
     ret                                        

	 }
}

void __declspec(naked) ff_deblock_v_luma_8_sse2(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
	push ebp
	push ebx
    push esi
	mov	 ebp,esp
// stack info.
// tc0				[ebp+12+5*4]
// beta				[ebp+12+4*4]
// alpha			[ebp+12+3*4]
// stride			[ebp+12+2*4]
// pix				[ebp+12+1*4]
// return_addr		[ebp+12]
// ebp				[ebp+8]
// ebx				[ebp+4]
// esi				[ebp]
	sub	 esp,(15+32)
	and  esp,0xfffffff0 // align esp
                                    
    mov eax, [ebp + 12 + 1*4]
    mov ecx, [ebp + 12 + 2*4]
    mov edx, [ebp + 12 + 3*4]
    mov ebx, [ebp + 12 + 4*4]
    mov esi, [ebp + 12 + 5*4]
                                                
    lea esi, [ecx+ecx*2]                            
    dec edx                                     
    neg esi                                     
    dec ebx                                     
    add esi, eax                                
    
                                                
    movdqa xmm0, [esi+ecx]                      
    movdqa xmm1, [esi+2*ecx]                    
    movdqa xmm2, [eax]                          
    movdqa xmm3, [eax+ecx]                      
    movd xmm4, edx                              
    movd xmm5, ebx                              
    pshuflw xmm4, xmm4, (0)*0x55                
                                                
    punpcklqdq xmm4, xmm4                       
    pshuflw xmm5, xmm5, (0)*0x55                
                                                
    punpcklqdq xmm5, xmm5                       
                                                
    packuswb xmm4, xmm4                         
                                                
    packuswb xmm5, xmm5                         
    movdqa xmm6, xmm2                           
    movdqa xmm7, xmm1                           
                                                
    psubusb xmm6, xmm1                          
                                                
    psubusb xmm7, xmm2                          
                                                
    por xmm7, xmm6                              
                                                
    psubusb xmm7, xmm4                          
    movdqa xmm6, xmm1                           
    movdqa xmm4, xmm0                           
                                                
    psubusb xmm6, xmm0                          
                                                
    psubusb xmm4, xmm1                          
                                                
    por xmm4, xmm6                              
                                                
    psubusb xmm4, xmm5                          
                                                
    por xmm7, xmm4                              
    movdqa xmm6, xmm2                           
    movdqa xmm4, xmm3                           
                                                
    psubusb xmm6, xmm3                          
                                                
    psubusb xmm4, xmm2                          
                                                
    por xmm4, xmm6                              
                                                
    psubusb xmm4, xmm5                          
                                                
    por xmm7, xmm4                              
                                                
    pxor xmm6, xmm6                             
                                                
    pcmpeqb xmm7, xmm6                          
                                                
    mov ebx, dword ptr[ebp + 32]   //tc0    
                                                
    pcmpeqb xmm3, xmm3                          
    movd xmm4, [ebx]                            
                                                
    punpcklbw xmm4, xmm4                        
                                                
    punpcklbw xmm4, xmm4                        
    movdqa [esp+16], xmm4                       
                                                
    pcmpgtb xmm4, xmm3                          
    movdqa xmm3, [esi]                          
                                                
    pand xmm4, xmm7                             
    movdqa [esp], xmm4                          
                                                
    movdqa xmm7, xmm3                           
    movdqa xmm6, xmm1                           
                                                
    psubusb xmm7, xmm1                          
                                                
    psubusb xmm6, xmm3                          
                                                
    psubusb xmm7, xmm5                          
                                                
    psubusb xmm6, xmm5                          
                                                
    pcmpeqb xmm6, xmm7                          
                                                
    pand xmm6, xmm4                             
                                                
    pand xmm4, [esp+16]                         
                                                
    movdqa xmm7, xmm4                           
    psubb xmm7, xmm6                            
                                                
    pand xmm6, xmm4                             
                                                
    movdqa xmm4, xmm1                           
    pavgb xmm4, xmm2                            
                                                
    pavgb xmm3, xmm4                            
                                                
    pxor xmm4, [esi]                            
                                                
    pand xmm4, [ff_pb_1]                        
                                                
    psubusb xmm3, xmm4                          
                                                
    movdqa xmm4, xmm0                           
    psubusb xmm4, xmm6                          
                                                
    paddusb xmm6, xmm0                          
                                                
    pmaxub xmm3, xmm4                           
                                                
    pminub xmm3, xmm6                           
    movdqa [esi+ecx], xmm3                      
                                                
    movdqa xmm4, [eax+2*ecx]                    
    movdqa xmm3, xmm4                           
    movdqa xmm6, xmm2                           
                                                
    psubusb xmm3, xmm2                          
                                                
    psubusb xmm6, xmm4                          
                                                
    psubusb xmm3, xmm5                          
                                                
    psubusb xmm6, xmm5                          
                                                
    pcmpeqb xmm6, xmm3                          
                                                
    pand   xmm6, [esp]                            
    movdqa xmm5, [esp+16]                       
                                                
    psubb xmm7, xmm6                            
                                                
    pand xmm5, xmm6                             
    movdqa xmm3, [eax+ecx]                      
                                                
    movdqa xmm6, xmm1                           
    pavgb xmm6, xmm2                            
                                                
    pavgb xmm4, xmm6                            
                                                
    pxor xmm6, [eax+2*ecx]                      
                                                
    pand xmm6, [ff_pb_1]                        
                                                
    psubusb xmm4, xmm6                          
                                                
    movdqa xmm6, xmm3                           
    psubusb xmm6, xmm5                          
                                                
    paddusb xmm5, xmm3                          
                                                
    pmaxub xmm4, xmm6                           
                                                
    pminub xmm4, xmm5                           
    movdqa [eax+ecx], xmm4                      
                                                
                                                
    pcmpeqb xmm4, xmm4                          
                                                
    movdqa xmm5, xmm1                           
    pxor xmm5, xmm2                             
                                                
    pxor xmm3, xmm4                             
                                                
    pand xmm5, [ff_pb_1]                        
                                                
    pavgb xmm3, xmm0                            
                                                
    pxor xmm4, xmm1                             
                                                
    pavgb xmm3, [ff_pb_3]                       
                                                
    pavgb xmm4, xmm2                            
                                                
    pavgb xmm3, xmm5                            
    movdqa xmm6, [ff_pb_A1]                     
                                                
    paddusb xmm3, xmm4                          
                                                
    psubusb xmm6, xmm3                          
                                                
    psubusb xmm3, [ff_pb_A1]                    
                                                
    pminub xmm6, xmm7                           
                                                
    pminub xmm3, xmm7                           
                                                
    psubusb xmm1, xmm6                          
                                                
    psubusb xmm2, xmm3                          
                                                
    paddusb xmm1, xmm3                          
                                                
    paddusb xmm2, xmm6                          
    movdqa [esi+2*ecx], xmm1                    
    movdqa [eax], xmm2                          

	mov	 esp,ebp
    pop  esi
    pop  ebx
	pop  ebp
    ret                                         
	 }
}
void __declspec(naked) ff_deblock_h_luma_8_sse2(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
   push ebp
   push ebx                                          
   push esi
   mov  ebp,esp
   //stack info.
   // tc0			[ebp+12+20]
   // beta			[ebp+12+16]
   // alpha			[ebp+12+12]
   // stride		[ebp+12+8]
   // pix			[ebp+12+4]
   // return_addr	[ebp+12]
   // ebx			[ebp+8]
   // esi			[ebp+4]
   // ebp			[ebp]
                                                     
   mov eax, dword ptr[ebp + 12 + 4]                      
   mov ebx, [ebp + 12 + 8]                            
   lea esi, [ebx+ebx*2]                                  
   sub eax, 4                                        
   lea ecx, [eax+esi]

   sub	esp,112
   and	esp,0xfffffff0
                                                     
                                                     
   movq mm0, [eax]                                   
   movq mm1, [eax+ebx]                               
   movq mm2, [eax+ebx*2]                             
   movq mm3, [ecx]                                   
   movq mm4, [ecx+ebx]                               
   movq mm5, [ecx+ebx*2]                             
   movq mm6, [ecx+esi]                               
   movq mm7, mm0                                     
                                                     
   punpcklbw mm0, mm1                                
                                                     
   punpckhbw mm7, mm1                                
   movq mm1, mm2                                     
                                                     
   punpcklbw mm2, mm3                                
                                                     
   punpckhbw mm1, mm3                                
   movq mm3, mm4                                     
                                                     
   punpcklbw mm4, mm5                                
                                                     
   punpckhbw mm3, mm5                                
   movq [esp+0x10], mm1                           
                                                     
   movq mm5, mm6                                     
   punpckhbw mm5, [ecx+ebx*4]                        
                                                     
   punpcklbw mm6, [ecx+ebx*4]                        
   movq mm1, mm0                                     
                                                     
   punpcklwd mm0, mm2                                
                                                     
   punpckhwd mm1, mm2                                
   movq mm2, mm4                                     
                                                     
   punpcklwd mm4, mm6                                
                                                     
   punpckhwd mm2, mm6                                
                                                     
   punpckhdq mm0, mm4                                
   movq [esp+0x00], mm0                           
                                                     
   movq mm6, mm7                                     
   punpckhwd mm6, [esp+0x10]                      
                                                     
   punpcklwd mm7, [esp+0x10]                      
   movq mm0, mm3                                     
                                                     
   punpcklwd mm3, mm5                                
                                                     
   punpckhwd mm0, mm5                                
   movq mm5, mm7                                     
                                                     
   punpckldq mm7, mm3                                
                                                     
   punpckhdq mm5, mm3                                
   movq mm3, mm1                                     
                                                     
   punpckldq mm1, mm2                                
                                                     
   punpckhdq mm3, mm2                                
                                                     
   punpckldq mm6, mm0                                
   movq [esp+0x10], mm1                           
   movq [esp+0x20], mm3                           
   movq [esp+0x30], mm7                           
   movq [esp+0x40], mm5                           
   movq [esp+0x50], mm6                           
   lea eax, [eax+ebx*8]                              
   lea ecx, [ecx+ebx*8]                              
   movq mm0, [eax]                                   
   movq mm1, [eax+ebx]                               
   movq mm2, [eax+ebx*2]                             
   movq mm3, [ecx]                                   
   movq mm4, [ecx+ebx]                               
   movq mm5, [ecx+ebx*2]                             
   movq mm6, [ecx+esi]                               
   movq mm7, mm0                                     
                                                     
   punpcklbw mm0, mm1                                
                                                     
   punpckhbw mm7, mm1                                
   movq mm1, mm2                                     
                                                     
   punpcklbw mm2, mm3                                
                                                     
   punpckhbw mm1, mm3                                
   movq mm3, mm4                                     
                                                     
   punpcklbw mm4, mm5                                
                                                     
   punpckhbw mm3, mm5                                
   movq [esp+8+0x10], mm1                         
                                                     
   movq mm5, mm6                                     
   punpckhbw mm5, [ecx+ebx*4]                        
                                                     
   punpcklbw mm6, [ecx+ebx*4]                        
   movq mm1, mm0                                     
                                                     
   punpcklwd mm0, mm2                                
                                                     
   punpckhwd mm1, mm2                                
   movq mm2, mm4                                     
                                                     
   punpcklwd mm4, mm6                                
                                                     
   punpckhwd mm2, mm6                                
                                                     
   punpckhdq mm0, mm4                                
   movq [esp+8+0x00], mm0                         
                                                     
   movq mm6, mm7                                     
   punpckhwd mm6, [esp+8+0x10]                    
                                                     
   punpcklwd mm7, [esp+8+0x10]                    
   movq mm0, mm3                                     
                                                     
   punpcklwd mm3, mm5                                
                                                     
   punpckhwd mm0, mm5                                
   movq mm5, mm7                                     
                                                     
   punpckldq mm7, mm3                                
                                                     
   punpckhdq mm5, mm3                                
   movq mm3, mm1                                     
                                                     
   punpckldq mm1, mm2                                
                                                     
   punpckhdq mm3, mm2                                
                                                     
   punpckldq mm6, mm0                                
   movq [esp+8+0x10], mm1                         
   movq [esp+8+0x20], mm3                         
   movq [esp+8+0x30], mm7                         
   movq [esp+8+0x40], mm5                         
   movq [esp+8+0x50], mm6                         
                                                     
                                                     
   lea eax, [esp+0x30]                            
   push dword ptr[ebp+12+20]                       
   push dword ptr[ebp+12+16]
   push dword ptr[ebp+12+12]
   push 16                                     
   push eax                                    
                                                     
   call ff_deblock_v_luma_8_sse2                     
   add esp, 20                                       
                                                     
                                                     
   mov eax, dword ptr[ebp+12+4]                    
   sub eax, 2                                        
                                                     
   movq mm0, [esp+0x10]                           
   movq mm1, [esp+0x20]                           
   lea ecx, [eax+esi]                                
   movq mm2, [esp+0x30]                           
   movq mm3, [esp+0x40]                           
                                                     
   movq mm4, mm0                                     
   punpckhdq mm4, mm0                                
                                                     
   movq mm5, mm1                                     
   punpckhdq mm5, mm1                                
                                                     
   movq mm6, mm2                                     
   punpckhdq mm6, mm2                                
                                                     
                                                     
   punpcklbw mm0, mm1                                
                                                     
   punpcklbw mm2, mm3                                
                                                     
   movq mm1, mm0                                     
   punpcklwd mm1, mm2                                
                                                     
   punpckhwd mm0, mm2                                
   movd [eax], mm1                                   
                                                     
   punpckhdq mm1, mm1                                
   movd [eax+ebx], mm1                               
   movd [eax+ebx*2], mm0                             
                                                     
   punpckhdq mm0, mm0                                
   movd [ecx], mm0                                   
                                                     
                                                     
   punpckhdq mm3, mm3                                
                                                     
   punpcklbw mm4, mm5                                
                                                     
   punpcklbw mm6, mm3                                
                                                     
   movq mm5, mm4                                     
   punpcklwd mm5, mm6                                
                                                     
   punpckhwd mm4, mm6                                
   movd [ecx+ebx], mm5                               
                                                     
   punpckhdq mm5, mm5                                
   movd [ecx+ebx*2], mm5                             
   movd [ecx+esi], mm4                               
                                                     
   punpckhdq mm4, mm4                                
   movd [ecx+ebx*4], mm4                             
                                                     
   lea eax, [eax+ebx*8]                              
   lea ecx, [ecx+ebx*8]                              
   movq mm0, [esp+0x18]                           
   movq mm1, [esp+0x28]                           
   movq mm2, [esp+0x38]                           
   movq mm3, [esp+0x48]                           
                                                     
   movq mm4, mm0                                     
   punpckhdq mm4, mm0                                
                                                     
   movq mm5, mm1                                     
   punpckhdq mm5, mm1                                
                                                     
   movq mm6, mm2                                     
   punpckhdq mm6, mm2                                
                                                     
                                                     
   punpcklbw mm0, mm1                                
                                                     
   punpcklbw mm2, mm3                                
                                                     
   movq mm1, mm0                                     
   punpcklwd mm1, mm2                                
                                                     
   punpckhwd mm0, mm2                                
   movd [eax], mm1                                   
                                                     
   punpckhdq mm1, mm1                                
   movd [eax+ebx], mm1                               
   movd [eax+ebx*2], mm0                             
                                                     
   punpckhdq mm0, mm0                                
   movd [ecx], mm0                                   
                                                     
                                                     
   punpckhdq mm3, mm3                                
                                                     
   punpcklbw mm4, mm5                                
                                                     
   punpcklbw mm6, mm3                                
                                                     
   movq mm5, mm4                                     
   punpcklwd mm5, mm6                                
                                                     
   punpckhwd mm4, mm6                                
   movd [ecx+ebx], mm5                               
                                                     
   punpckhdq mm5, mm5                                
   movd [ecx+ebx*2], mm5                             
   movd [ecx+esi], mm4                               
                                                     
   punpckhdq mm4, mm4                                
   movd [ecx+ebx*4], mm4                             
                                                     
   mov  esp,ebp   
   pop esi                                           
   pop ebx                                           
   pop ebp
   ret
	}
}
void __declspec(naked) ff_deblock_v_chroma_10_mmxext(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
	 push ebx                                
     push esi                                
     push edi                                
     push ebp                                
     mov eax, [esp + 16 + 4 + 0*4]           
     mov ecx, [esp + 16 + 4 + 1*4]           
     mov edx, [esp + 16 + 4 + 2*4]           
     mov ebx, [esp + 16 + 4 + 3*4]           
     mov esi, [esp + 16 + 4 + 4*4]           
                                             
     mov edi, eax                            
     sub eax, ecx                            
     sub eax, ecx                            
     shl edx, 2                              
     shl ebx, 2                              
     mov ebp, 16/8                           
ff_deblock_v_chroma_10_mmxextloop:                                   
     movq mm0, [eax]                         
     movq mm1, [eax+ecx]                     
     movq mm2, [edi]                         
     movq mm3, [edi+ecx]                     
     movd mm4, edx                           
     movd mm5, ebx                           
     pshufw mm4, mm4, (0)*0x55               
     pshufw mm5, mm5, (0)*0x55               
                                             
     movq mm7, mm2                           
     psubusw mm7, mm1                        
                                             
     movq mm6, mm1                           
     psubusw mm6, mm2                        
                                             
     por mm6, mm7                            
                                             
     psubw mm6, mm4                          
                                             
     movq mm7, mm1                           
     psubusw mm7, mm0                        
                                             
     movq mm4, mm0                           
     psubusw mm4, mm1                        
                                             
     por mm4, mm7                            
                                             
     psubw mm4, mm5                          
                                             
     pand mm6, mm4                           
                                             
     movq mm7, mm3                           
     psubusw mm7, mm2                        
                                             
     movq mm4, mm2                           
     psubusw mm4, mm3                        
                                             
     por mm4, mm7                            
                                             
     psubw mm4, mm5                          
                                             
     pxor mm7, mm7                           
                                             
     pand mm6, mm4                           
                                             
     pcmpgtw mm7, mm6                        
                                             
     pxor mm4, mm4                           
     movd mm6, [esi]                         
                                             
     punpcklbw mm6, mm6                      
                                             
     punpcklwd mm6, mm6                      
                                             
     psraw mm6, 6                            
                                             
     psubw mm6, [ff_pw_3]                    
                                             
     pmaxsw mm6, mm4                         
                                             
     pand mm7, mm6                           
                                             
     psubw mm0, mm3                          
                                             
     pxor mm6, mm6                           
                                             
     paddw mm0, [ff_pw_4]                    
                                             
     psubw mm6, mm7                          
                                             
     movq mm5, mm2                           
     psubw mm5, mm1                          
                                             
     psllw mm5, 2                            
                                             
     paddw mm0, mm5                          
                                             
     psraw mm0, 3                            
     movq mm5, [pw_pixel_max]                
                                             
     pmaxsw mm0, mm6                         
                                             
     pminsw mm0, mm7                         
                                             
     pxor mm6, mm6                           
                                             
     paddw mm1, mm0                          
                                             
     psubw mm2, mm0                          
                                             
     pmaxsw mm1, mm6                         
                                             
     pminsw mm1, mm5                         
                                             
     pmaxsw mm2, mm6                         
                                             
     pminsw mm2, mm5                         
     movq [eax+1*ecx], mm1                   
     movq [eax+2*ecx], mm2                   
     add eax, 8                              
     add edi, 8                              
     add esi, 8/4                            
     dec ebp                                 
     jg ff_deblock_v_chroma_10_mmxextloop                                
     pop ebp                                 
     pop edi                                 
     pop esi                                 
     pop ebx                                 
     ret                                     

	 }
}
void __declspec(naked) ff_deblock_v_luma_10_mmxext(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
    push ebx                           
    push esi                           
    mov eax, [esp + 8 + 4 + 0*4]       
    mov ecx, [esp + 8 + 4 + 1*4]       
    mov edx, [esp + 8 + 4 + 2*4]       
    mov ebx, [esp + 8 + 4 + 3*4]       
    mov esi, [esp + 8 + 4 + 4*4]       
                                       
    sub esp, 44                        
    shl edx, 2                         
    shl ebx, 2                         
    movd mm4, edx                      
    movd mm5, ebx                      
    pshufw mm4, mm4, (0)*0x55          
    pshufw mm5, mm5, (0)*0x55          
    mov ebx, 32/8                      
    mov edx, eax                       
    sub eax, ecx                       
    movq [esp+8*3], mm4                
    sub eax, ecx                       
    movq [esp+8*4], mm5                
    sub eax, ecx                       
ff_deblock_v_luma_10_mmxextloop:                              
    movq mm0, [eax+ecx]                
    movq mm1, [eax+ecx*2]              
    movq mm2, [edx]                    
    movq mm3, [edx+ecx]                
                                       
                                       
    movq mm7, mm2                      
    psubusw mm7, mm1                   
                                       
    movq mm4, mm1                      
    psubusw mm4, mm2                   
                                       
    por mm4, mm7                       
                                       
    psubw mm4, [esp+8*3]               
                                       
    movq mm7, mm1                      
    psubusw mm7, mm0                   
                                       
    movq mm6, mm0                      
    psubusw mm6, mm1                   
                                       
    por mm6, mm7                       
                                       
    psubw mm6, [esp+8*4]               
                                       
    pand mm4, mm6                      
                                       
    movq mm7, mm3                      
    psubusw mm7, mm2                   
                                       
    movq mm6, mm2                      
    psubusw mm6, mm3                   
                                       
    por mm6, mm7                       
                                       
    psubw mm6, [esp+8*4]               
                                       
    pxor mm7, mm7                      
                                       
    pand mm4, mm6                      
                                       
    pcmpgtw mm7, mm4                   
    movd mm6, [esi]                    
                                       
    punpcklbw mm6, mm6                 
    pshufw mm6, mm6, 0                 
                                       
    psraw mm6, 6                       
    movq [esp], mm6                    
                                       
    movq mm5, [eax]                    
                                       
    movq mm4, mm1                      
    psubusw mm4, mm5                   
                                       
    movq mm6, mm5                      
    psubusw mm6, mm1                   
                                       
    por mm6, mm4                       
                                       
    pxor mm4, mm4                      
                                       
    psubw mm6, [esp+8*4]               
                                       
    pcmpgtw mm4, mm6                   
                                       
    pxor mm6, mm6                      
    movq [esp+8], mm4                  
                                       
    pcmpgtw mm6, [esp]                 
                                       
    pand mm4, [esp]                    
                                       
    pandn mm6, mm7                     
                                       
    pand mm4, mm6                      
                                       
    movq mm6, mm1                      
    pavgw mm6, mm2                     
                                       
    paddw mm5, mm6                     
                                       
    pxor mm6, mm6                      
                                       
    psraw mm5, 1                       
                                       
    psubw mm6, mm4                     
                                       
    psubw mm5, mm0                     
                                       
    pmaxsw mm5, mm6                    
                                       
    pminsw mm5, mm4                    
                                       
    paddw mm5, mm0                     
    movq [eax+ecx], mm5                
                                       
    movq mm5, [edx+ecx*2]              
                                       
    movq mm4, mm2                      
    psubusw mm4, mm5                   
                                       
    movq mm6, mm5                      
    psubusw mm6, mm2                   
                                       
    por mm6, mm4                       
                                       
    pxor mm4, mm4                      
                                       
    psubw mm6, [esp+8*4]               
                                       
    pcmpgtw mm4, mm6                   
                                       
    pxor mm6, mm6                      
    movq [esp+8*2], mm4                
                                       
    pcmpgtw mm6, [esp]                 
                                       
    pand mm4, [esp]                    
                                       
    pandn mm6, mm7                     
                                       
    pand mm4, mm6                      
                                       
    movq mm6, mm1                      
    pavgw mm6, mm2                     
                                       
    paddw mm5, mm6                     
                                       
    pxor mm6, mm6                      
                                       
    psraw mm5, 1                       
                                       
    psubw mm6, mm4                     
                                       
    psubw mm5, mm3                     
                                       
    pmaxsw mm5, mm6                    
                                       
    pminsw mm5, mm4                    
                                       
    paddw mm5, mm3                     
    movq [edx+ecx], mm5                
                                       
                                       
    pxor mm5, mm5                      
    movq mm6, [esp]                    
                                       
    pcmpgtw mm5, [esp]                 
                                       
    psubw mm6, [esp+8]                 
                                       
    pandn mm5, mm7                     
                                       
    psubw mm6, [esp+8*2]               
                                       
    pand mm5, mm6                      
                                       
    psubw mm0, mm3                     
                                       
    pxor mm6, mm6                      
                                       
    paddw mm0, [ff_pw_4]               
                                       
    psubw mm6, mm5                     
                                       
    movq mm7, mm2                      
    psubw mm7, mm1                     
                                       
    psllw mm7, 2                       
                                       
    paddw mm0, mm7                     
                                       
    psraw mm0, 3                       
    movq mm7, [pw_pixel_max]           
                                       
    pmaxsw mm0, mm6                    
                                       
    pminsw mm0, mm5                    
                                       
    pxor mm6, mm6                      
                                       
    paddw mm1, mm0                     
                                       
    psubw mm2, mm0                     
                                       
    pmaxsw mm1, mm6                    
                                       
    pminsw mm1, mm7                    
                                       
    pmaxsw mm2, mm6                    
                                       
    pminsw mm2, mm7                    
    movq [eax+ecx*2], mm1              
    movq [edx], mm2                    
                                       
    add eax, 8                         
    add edx, 8                         
    add esi, 8/8                       
    dec ebx                            
    jg  ff_deblock_v_luma_10_mmxextloop
    add esp, 44                        
    pop esi                            
    pop ebx                            
    ret
	 }
}
void __declspec(naked) ff_deblock_h_luma_10_mmxext(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
   push ebx                                    
   push esi                                    
   push edi                                    
   mov eax, [esp + 12 + 4 + 0*4]               
   mov ecx, [esp + 12 + 4 + 1*4]               
   mov edx, [esp + 12 + 4 + 2*4]               
   mov ebx, [esp + 12 + 4 + 3*4]               
   mov esi, [esp + 12 + 4 + 4*4]               
                                               
   sub esp, 56                                 
   shl edx, 2                                  
   shl ebx, 2                                  
   movd mm4, edx                               
   movd mm5, ebx                               
   pshufw mm4, mm4, (0)*0x55                   
   pshufw mm5, mm5, (0)*0x55                   
   mov ebx, ecx                                
   movq [esp+8*5], mm4                         
   add ebx, ecx                                
   mov edi, 32/8                               
   movq [esp+8*6], mm5                         
   add ebx, ecx                                
ff_deblock_h_luma_10_mmxextloop:                                       
   movq mm2, [eax-8]                           
   movq mm7, [eax+0]                           
   movq mm5, [eax+ecx-8]                       
   movq mm3, [eax+ecx+0]                       
   movq mm0, [eax+ecx*2-8]                     
   movq mm6, [eax+ecx*2+0]                     
   movq mm1, [eax+ebx-8]                       
   movq mm4, mm2                               
                                               
   punpcklwd mm2, mm5                          
                                               
   punpckhwd mm4, mm5                          
   movq mm5, mm0                               
                                               
   punpcklwd mm0, mm1                          
                                               
   punpckhwd mm5, mm1                          
   movq mm1, mm2                               
                                               
   punpckldq mm2, mm0                          
                                               
   punpckhdq mm1, mm0                          
   movq mm0, mm4                               
                                               
   punpckldq mm4, mm5                          
                                               
   punpckhdq mm0, mm5                          
   movq mm2, [eax+ebx]                         
   movq mm5, mm7                               
                                               
   punpcklwd mm7, mm3                          
                                               
   punpckhwd mm5, mm3                          
   movq mm3, mm6                               
                                               
   punpcklwd mm6, mm2                          
                                               
   punpckhwd mm3, mm2                          
   movq mm2, mm7                               
                                               
   punpckldq mm7, mm6                          
                                               
   punpckhdq mm2, mm6                          
   movq mm6, mm5                               
                                               
   punpckldq mm5, mm3                          
                                               
   punpckhdq mm6, mm3                          
                                               
   movq [esp+8*4], mm5                         
                                               
   movq mm6, mm7                               
   psubusw mm6, mm0                            
                                               
   movq mm3, mm0                               
   psubusw mm3, mm7                            
                                               
   por mm3, mm6                                
                                               
   psubw mm3, [esp+8*5]                        
                                               
   movq mm6, mm0                               
   psubusw mm6, mm4                            
                                               
   movq mm5, mm4                               
   psubusw mm5, mm0                            
                                               
   por mm5, mm6                                
                                               
   psubw mm5, [esp+8*6]                        
                                               
   pand mm3, mm5                               
                                               
   movq mm6, mm2                               
   psubusw mm6, mm7                            
                                               
   movq mm5, mm7                               
   psubusw mm5, mm2                            
                                               
   por mm5, mm6                                
                                               
   psubw mm5, [esp+8*6]                        
                                               
   pxor mm6, mm6                               
                                               
   pand mm3, mm5                               
                                               
   pcmpgtw mm6, mm3                            
   movd mm5, [esi]                             
                                               
   punpcklbw mm5, mm5                          
   pshufw mm5, mm5, 0                          
                                               
   psraw mm5, 6                                
   movq [esp], mm5                             
                                               
                                               
   movq mm3, mm0                               
   psubusw mm3, mm1                            
                                               
   movq mm5, mm1                               
   psubusw mm5, mm0                            
                                               
   por mm5, mm3                                
                                               
   pxor mm3, mm3                               
                                               
   psubw mm5, [esp+8*6]                        
                                               
   pcmpgtw mm3, mm5                            
                                               
   pxor mm5, mm5                               
   movq [esp+8], mm3                           
                                               
   pcmpgtw mm5, [esp]                          
                                               
   pand mm3, [esp]                             
                                               
   pandn mm5, mm6                              
                                               
   pand mm3, mm5                               
                                               
   movq mm5, mm0                               
   pavgw mm5, mm7                              
                                               
   paddw mm1, mm5                              
                                               
   pxor mm5, mm5                               
                                               
   psraw mm1, 1                                
                                               
   psubw mm5, mm3                              
                                               
   psubw mm1, mm4                              
                                               
   pmaxsw mm1, mm5                             
                                               
   pminsw mm1, mm3                             
                                               
   paddw mm1, mm4                              
   movq [esp+8*3], mm1                         
                                               
   movq mm1, [esp+8*4]                         
                                               
   movq mm3, mm7                               
   psubusw mm3, mm1                            
                                               
   movq mm5, mm1                               
   psubusw mm5, mm7                            
                                               
   por mm5, mm3                                
                                               
   pxor mm3, mm3                               
                                               
   psubw mm5, [esp+8*6]                        
                                               
   pcmpgtw mm3, mm5                            
                                               
   pxor mm5, mm5                               
   movq [esp+8*2], mm3                         
                                               
   pcmpgtw mm5, [esp]                          
                                               
   pand mm3, [esp]                             
                                               
   pandn mm5, mm6                              
                                               
   pand mm3, mm5                               
                                               
   movq mm5, mm0                               
   pavgw mm5, mm7                              
                                               
   paddw mm1, mm5                              
                                               
   pxor mm5, mm5                               
                                               
   psraw mm1, 1                                
                                               
   psubw mm5, mm3                              
                                               
   psubw mm1, mm2                              
                                               
   pmaxsw mm1, mm5                             
                                               
   pminsw mm1, mm3                             
                                               
   paddw mm1, mm2                              
   movq [esp+8*4], mm1                         
                                               
                                               
   pxor mm1, mm1                               
   movq mm5, [esp]                             
                                               
   pcmpgtw mm1, [esp]                          
                                               
   psubw mm5, [esp+8]                          
                                               
   pandn mm1, mm6                              
                                               
   psubw mm5, [esp+8*2]                        
                                               
   pand mm1, mm5                               
                                               
   psubw mm4, mm2                              
                                               
   pxor mm5, mm5                               
                                               
   paddw mm4, [ff_pw_4]                        
                                               
   psubw mm5, mm1                              
                                               
   movq mm6, mm7                               
   psubw mm6, mm0                              
                                               
   psllw mm6, 2                                
                                               
   paddw mm4, mm6                              
                                               
   psraw mm4, 3                                
   movq mm6, [pw_pixel_max]                    
                                               
   pmaxsw mm4, mm5                             
                                               
   pminsw mm4, mm1                             
                                               
   pxor mm5, mm5                               
                                               
   paddw mm0, mm4                              
                                               
   psubw mm7, mm4                              
                                               
   pmaxsw mm0, mm5                             
                                               
   pminsw mm0, mm6                             
                                               
   pmaxsw mm7, mm5                             
                                               
   pminsw mm7, mm6                             
   movq mm4, [esp+8*3]                         
   movq mm2, [esp+8*4]                         
   movq mm3, mm4                               
                                               
   punpcklwd mm4, mm0                          
                                               
   punpckhwd mm3, mm0                          
   movq mm0, mm7                               
                                               
   punpcklwd mm7, mm2                          
                                               
   punpckhwd mm0, mm2                          
   movq mm2, mm4                               
                                               
   punpckldq mm4, mm7                          
                                               
   punpckhdq mm2, mm7                          
   movq mm7, mm3                               
                                               
   punpckldq mm3, mm0                          
                                               
   punpckhdq mm7, mm0                          
   movq [eax-4], mm4                           
   movq [eax+ecx-4], mm2                       
   movq [eax+ecx*2-4], mm3                     
   movq [eax+ebx-4], mm7                       
                                               
   add esi, 8/8                                
   lea eax, [eax+ecx*(8/2)]                    
   lea edx, [edx+ecx*(8/2)]                    
   dec edi                                     
   jg ff_deblock_h_luma_10_mmxextloop                                   
   add esp, 56                                 
   pop edi                                     
   pop esi                                     
   pop ebx                                     
   ret                                         

	 }
}
void __declspec(naked) ff_deblock_v_chroma_10_sse2(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
   push ebx                                  
   push esi                                  
   push edi                                  
   mov eax, [esp + 12 + 4 + 0*4]             
   mov ecx, [esp + 12 + 4 + 1*4]             
   mov edx, [esp + 12 + 4 + 2*4]             
   mov ebx, [esp + 12 + 4 + 3*4]             
   mov esi, [esp + 12 + 4 + 4*4]             
                                             
   mov edi, eax                              
   sub eax, ecx                              
   sub eax, ecx                              
   shl edx, 2                                
   shl ebx, 2                                
   movdqa xmm0, [eax]                        
   movdqa xmm1, [eax+ecx]                    
   movdqa xmm2, [edi]                        
   movdqa xmm3, [edi+ecx]                    
   movd xmm4, edx                            
   movd xmm5, ebx                            
   pshuflw xmm4, xmm4, (0)*0x55              
                                             
   punpcklqdq xmm4, xmm4                     
   pshuflw xmm5, xmm5, (0)*0x55              
                                             
   punpcklqdq xmm5, xmm5                     
                                             
   movdqa xmm7, xmm2                         
   psubusw xmm7, xmm1                        
                                             
   movdqa xmm6, xmm1                         
   psubusw xmm6, xmm2                        
                                             
   por xmm6, xmm7                            
                                             
   psubw xmm6, xmm4                          
                                             
   movdqa xmm7, xmm1                         
   psubusw xmm7, xmm0                        
                                             
   movdqa xmm4, xmm0                         
   psubusw xmm4, xmm1                        
                                             
   por xmm4, xmm7                            
                                             
   psubw xmm4, xmm5                          
                                             
   pand xmm6, xmm4                           
                                             
   movdqa xmm7, xmm3                         
   psubusw xmm7, xmm2                        
                                             
   movdqa xmm4, xmm2                         
   psubusw xmm4, xmm3                        
                                             
   por xmm4, xmm7                            
                                             
   psubw xmm4, xmm5                          
                                             
   pxor xmm7, xmm7                           
                                             
   pand xmm6, xmm4                           
                                             
   pcmpgtw xmm7, xmm6                        
                                             
   pxor xmm4, xmm4                           
   movd xmm6, [esi]                          
                                             
   punpcklbw xmm6, xmm6                      
                                             
   punpcklwd xmm6, xmm6                      
                                             
   psraw xmm6, 6                             
                                             
   psubw xmm6, [ff_pw_3]                     
                                             
   pmaxsw xmm6, xmm4                         
                                             
   pand xmm7, xmm6                           
                                             
   psubw xmm0, xmm3                          
                                             
   pxor xmm6, xmm6                           
                                             
   paddw xmm0, [ff_pw_4]                     
                                             
   psubw xmm6, xmm7                          
                                             
   movdqa xmm5, xmm2                         
   psubw xmm5, xmm1                          
                                             
   psllw xmm5, 2                             
                                             
   paddw xmm0, xmm5                          
                                             
   psraw xmm0, 3                             
   movdqa xmm5, [pw_pixel_max]               
                                             
   pmaxsw xmm0, xmm6                         
                                             
   pminsw xmm0, xmm7                         
                                             
   pxor xmm6, xmm6                           
                                             
   paddw xmm1, xmm0                          
                                             
   psubw xmm2, xmm0                          
                                             
   pmaxsw xmm1, xmm6                         
                                             
   pminsw xmm1, xmm5                         
                                             
   pmaxsw xmm2, xmm6                         
                                             
   pminsw xmm2, xmm5                         
   movdqa [eax+1*ecx], xmm1                  
   movdqa [eax+2*ecx], xmm2                  
   pop edi                                   
   pop esi                                   
   pop ebx                                   
   ret                                       

	 }
}
void __declspec(naked) ff_deblock_v_luma_10_sse2(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
   push ebx                             
   push esi                             
   mov eax, [esp + 8 + 4 + 0*4]         
   mov ecx, [esp + 8 + 4 + 1*4]         
   mov edx, [esp + 8 + 4 + 2*4]         
   mov ebx, [esp + 8 + 4 + 3*4]         
   mov esi, [esp + 8 + 4 + 4*4]         
                                        
   sub esp, 84                          
   shl edx, 2                           
   shl ebx, 2                           
   movd xmm4, edx                       
   movd xmm5, ebx                       
   pshuflw xmm4, xmm4, (0)*0x55         
                                        
   punpcklqdq xmm4, xmm4                
   pshuflw xmm5, xmm5, (0)*0x55         
                                        
   punpcklqdq xmm5, xmm5                
   mov ebx, 32/16                       
   mov edx, eax                         
   sub eax, ecx                         
   movdqa [esp+16*3], xmm4              
   sub eax, ecx                         
   movdqa [esp+16*4], xmm5              
   sub eax, ecx                         
ff_deblock_v_luma_10_sse2loop:                                
   movdqa xmm0, [eax+ecx]               
   movdqa xmm1, [eax+ecx*2]             
   movdqa xmm2, [edx]                   
   movdqa xmm3, [edx+ecx]               
                                        
                                        
   movdqa xmm7, xmm2                    
   psubusw xmm7, xmm1                   
                                        
   movdqa xmm4, xmm1                    
   psubusw xmm4, xmm2                   
                                        
   por xmm4, xmm7                       
                                        
   psubw xmm4, [esp+16*3]               
                                        
   movdqa xmm7, xmm1                    
   psubusw xmm7, xmm0                   
                                        
   movdqa xmm6, xmm0                    
   psubusw xmm6, xmm1                   
                                        
   por xmm6, xmm7                       
                                        
   psubw xmm6, [esp+16*4]               
                                        
   pand xmm4, xmm6                      
                                        
   movdqa xmm7, xmm3                    
   psubusw xmm7, xmm2                   
                                        
   movdqa xmm6, xmm2                    
   psubusw xmm6, xmm3                   
                                        
   por xmm6, xmm7                       
                                        
   psubw xmm6, [esp+16*4]               
                                        
   pxor xmm7, xmm7                      
                                        
   pand xmm4, xmm6                      
                                        
   pcmpgtw xmm7, xmm4                   
   movd xmm6, [esi]                     
                                        
   punpcklbw xmm6, xmm6                 
   pshuflw xmm6, xmm6, 01010000         
   pshufd xmm6, xmm6, 01010000          
                                        
   psraw xmm6, 6                        
   movdqa [esp], xmm6                   
                                        
   movdqa xmm5, [eax]                   
                                        
   movdqa xmm4, xmm1                    
   psubusw xmm4, xmm5                   
                                        
   movdqa xmm6, xmm5                    
   psubusw xmm6, xmm1                   
                                        
   por xmm6, xmm4                       
                                        
   pxor xmm4, xmm4                      
                                        
   psubw xmm6, [esp+16*4]               
                                        
   pcmpgtw xmm4, xmm6                   
                                        
   pxor xmm6, xmm6                      
   movdqa [esp+16], xmm4                
                                        
   pcmpgtw xmm6, [esp]                  
                                        
   pand xmm4, [esp]                     
                                        
   pandn xmm6, xmm7                     
                                        
   pand xmm4, xmm6                      
                                        
   movdqa xmm6, xmm1                    
   pavgw xmm6, xmm2                     
                                        
   paddw xmm5, xmm6                     
                                        
   pxor xmm6, xmm6                      
                                        
   psraw xmm5, 1                        
                                        
   psubw xmm6, xmm4                     
                                        
   psubw xmm5, xmm0                     
                                        
   pmaxsw xmm5, xmm6                    
                                        
   pminsw xmm5, xmm4                    
                                        
   paddw xmm5, xmm0                     
   movdqa [eax+ecx], xmm5               
                                        
   movdqa xmm5, [edx+ecx*2]             
                                        
   movdqa xmm4, xmm2                    
   psubusw xmm4, xmm5                   
                                        
   movdqa xmm6, xmm5                    
   psubusw xmm6, xmm2                   
                                        
   por xmm6, xmm4                       
                                        
   pxor xmm4, xmm4                      
                                        
   psubw xmm6, [esp+16*4]               
                                        
   pcmpgtw xmm4, xmm6                   
                                        
   pxor xmm6, xmm6                      
   movdqa [esp+16*2], xmm4              
                                        
   pcmpgtw xmm6, [esp]                  
                                        
   pand xmm4, [esp]                     
                                        
   pandn xmm6, xmm7                     
                                        
   pand xmm4, xmm6                      
                                        
   movdqa xmm6, xmm1                    
   pavgw xmm6, xmm2                     
                                        
   paddw xmm5, xmm6                     
                                        
   pxor xmm6, xmm6                      
                                        
   psraw xmm5, 1                        
                                        
   psubw xmm6, xmm4                     
                                        
   psubw xmm5, xmm3                     
                                        
   pmaxsw xmm5, xmm6                    
                                        
   pminsw xmm5, xmm4                    
                                        
   paddw xmm5, xmm3                     
   movdqa [edx+ecx], xmm5               
                                        
                                        
   pxor xmm5, xmm5                      
   movdqa xmm6, [esp]                   
                                        
   pcmpgtw xmm5, [esp]                  
                                        
   psubw xmm6, [esp+16]                 
                                        
   pandn xmm5, xmm7                     
                                        
   psubw xmm6, [esp+16*2]               
                                        
   pand xmm5, xmm6                      
                                        
   psubw xmm0, xmm3                     
                                        
   pxor xmm6, xmm6                      
                                        
   paddw xmm0, [ff_pw_4]                
                                        
   psubw xmm6, xmm5                     
                                        
   movdqa xmm7, xmm2                    
   psubw xmm7, xmm1                     
                                        
   psllw xmm7, 2                        
                                        
   paddw xmm0, xmm7                     
                                        
   psraw xmm0, 3                        
   movdqa xmm7, [pw_pixel_max]          
                                        
   pmaxsw xmm0, xmm6                    
                                        
   pminsw xmm0, xmm5                    
                                        
   pxor xmm6, xmm6                      
                                        
   paddw xmm1, xmm0                     
                                        
   psubw xmm2, xmm0                     
                                        
   pmaxsw xmm1, xmm6                    
                                        
   pminsw xmm1, xmm7                    
                                        
   pmaxsw xmm2, xmm6                    
                                        
   pminsw xmm2, xmm7                    
   movdqa [eax+ecx*2], xmm1             
   movdqa [edx], xmm2                   
                                        
   add eax, 16                          
   add edx, 16                          
   add esi, 16/8                        
   dec ebx                              
   jg  ff_deblock_v_luma_10_sse2loop
   add esp, 84                          
   pop esi                              
   pop ebx                              
   ret                                  
                                        

	 }
}
void __declspec(naked) ff_deblock_h_luma_10_sse2(uint8_t *pix, int stride,int alpha, int beta, int8_t *tc0)
{
	__asm{
     push ebx                                  
     push esi                                  
     push edi                                  
     mov eax, [esp + 12 + 4 + 0*4]             
     mov ecx, [esp + 12 + 4 + 1*4]             
     mov edx, [esp + 12 + 4 + 2*4]             
     mov ebx, [esp + 12 + 4 + 3*4]             
     mov esi, [esp + 12 + 4 + 4*4]             
                                               
     sub esp, 112                              
     shl edx, 2                                
     shl ebx, 2                                
     movd xmm4, edx                            
     movd xmm5, ebx                            
     pshuflw xmm4, xmm4, (0)*0x55              
                                               
     punpcklqdq xmm4, xmm4                     
     pshuflw xmm5, xmm5, (0)*0x55              
                                               
     punpcklqdq xmm5, xmm5                     
     mov ebx, ecx                              
     movdqa [esp+16*5], xmm4                   
     add ebx, ecx                              
     mov edi, 32/16                            
     movdqa [esp+16*6], xmm5                   
     add ebx, ecx                              
     mov edx, eax                              
     add edx, ebx                              
ff_deblock_h_luma_10_sse2loop:                                     
     movdqu xmm5, [eax-8]                      
     movdqu xmm0, [eax+ecx-8]                  
     movdqu xmm2, [eax+ecx*2-8]                
     movdqu xmm3, [edx-8]                      
     movdqa xmm6, xmm5                         
                                               
     punpcklwd xmm5, xmm0                      
                                               
     punpckhwd xmm6, xmm0                      
     movdqa xmm0, xmm2                         
                                               
     punpcklwd xmm2, xmm3                      
                                               
     punpckhwd xmm0, xmm3                      
     movdqa xmm3, xmm5                         
                                               
     punpckldq xmm5, xmm2                      
                                               
     punpckhdq xmm3, xmm2                      
     movdqa xmm2, xmm6                         
                                               
     punpckldq xmm6, xmm0                      
                                               
     punpckhdq xmm2, xmm0                      
     movdqa [esp], xmm2                        
                                               
     movdqu xmm4, [edx+ecx-8]                  
     movdqu xmm1, [edx+ecx*2-8]                
     movdqu xmm2, [edx+ebx-8]                  
     movdqu xmm7, [edx+ecx*4-8]                
     movdqa xmm0, xmm4                         
                                               
     punpcklwd xmm4, xmm1                      
                                               
     punpckhwd xmm0, xmm1                      
     movdqa xmm1, xmm2                         
                                               
     punpcklwd xmm2, xmm7                      
                                               
     punpckhwd xmm1, xmm7                      
     movdqa xmm7, xmm4                         
                                               
     punpckldq xmm4, xmm2                      
                                               
     punpckhdq xmm7, xmm2                      
     movdqa xmm2, xmm0                         
                                               
     punpckldq xmm0, xmm1                      
                                               
     punpckhdq xmm2, xmm1                      
                                               
     movdqa xmm1, [esp]                        
                                               
     punpcklqdq xmm1, xmm2                     
                                               
     punpckhqdq xmm5, xmm4                     
     movdqa xmm2, xmm3                         
                                               
     punpcklqdq xmm3, xmm7                     
                                               
     punpckhqdq xmm2, xmm7                     
     movdqa xmm7, xmm6                         
                                               
     punpcklqdq xmm6, xmm0                     
                                               
     punpckhqdq xmm7, xmm0                     
                                               
     movdqa [esp+16*4], xmm1                   
                                               
     movdqa xmm0, xmm6                         
     psubusw xmm0, xmm2                        
                                               
     movdqa xmm4, xmm2                         
     psubusw xmm4, xmm6                        
                                               
     por xmm4, xmm0                            
                                               
     psubw xmm4, [esp+16*5]                    
                                               
     movdqa xmm0, xmm2                         
     psubusw xmm0, xmm3                        
                                               
     movdqa xmm1, xmm3                         
     psubusw xmm1, xmm2                        
                                               
     por xmm1, xmm0                            
                                               
     psubw xmm1, [esp+16*6]                    
                                               
     pand xmm4, xmm1                           
                                               
     movdqa xmm0, xmm7                         
     psubusw xmm0, xmm6                        
                                               
     movdqa xmm1, xmm6                         
     psubusw xmm1, xmm7                        
                                               
     por xmm1, xmm0                            
                                               
     psubw xmm1, [esp+16*6]                    
                                               
     pxor xmm0, xmm0                           
                                               
     pand xmm4, xmm1                           
                                               
     pcmpgtw xmm0, xmm4                        
     movd xmm1, [esi]                          
                                               
     punpcklbw xmm1, xmm1                      
     pshuflw xmm1, xmm1, 01010000              
     pshufd xmm1, xmm1, 01010000               
                                               
     psraw xmm1, 6                             
     movdqa [esp], xmm1                        
                                               
                                               
     movdqa xmm4, xmm2                         
     psubusw xmm4, xmm5                        
                                               
     movdqa xmm1, xmm5                         
     psubusw xmm1, xmm2                        
                                               
     por xmm1, xmm4                            
                                               
     pxor xmm4, xmm4                           
                                               
     psubw xmm1, [esp+16*6]                    
                                               
     pcmpgtw xmm4, xmm1                        
                                               
     pxor xmm1, xmm1                           
     movdqa [esp+16], xmm4                     
                                               
     pcmpgtw xmm1, [esp]                       
                                               
     pand xmm4, [esp]                          
                                               
     pandn xmm1, xmm0                          
                                               
     pand xmm4, xmm1                           
                                               
     movdqa xmm1, xmm2                         
     pavgw xmm1, xmm6                          
                                               
     paddw xmm5, xmm1                          
                                               
     pxor xmm1, xmm1                           
                                               
     psraw xmm5, 1                             
                                               
     psubw xmm1, xmm4                          
                                               
     psubw xmm5, xmm3                          
                                               
     pmaxsw xmm5, xmm1                         
                                               
     pminsw xmm5, xmm4                         
                                               
     paddw xmm5, xmm3                          
     movdqa [esp+16*3], xmm5                   
                                               
     movdqa xmm5, [esp+16*4]                   
                                               
     movdqa xmm4, xmm6                         
     psubusw xmm4, xmm5                        
                                               
     movdqa xmm1, xmm5                         
     psubusw xmm1, xmm6                        
                                               
     por xmm1, xmm4                            
                                               
     pxor xmm4, xmm4                           
                                               
     psubw xmm1, [esp+16*6]                    
                                               
     pcmpgtw xmm4, xmm1                        
                                               
     pxor xmm1, xmm1                           
     movdqa [esp+16*2], xmm4                   
                                               
     pcmpgtw xmm1, [esp]                       
                                               
     pand xmm4, [esp]                          
                                               
     pandn xmm1, xmm0                          
                                               
     pand xmm4, xmm1                           
                                               
     movdqa xmm1, xmm2                         
     pavgw xmm1, xmm6                          
                                               
     paddw xmm5, xmm1                          
                                               
     pxor xmm1, xmm1                           
                                               
     psraw xmm5, 1                             
                                               
     psubw xmm1, xmm4                          
                                               
     psubw xmm5, xmm7                          
                                               
     pmaxsw xmm5, xmm1                         
                                               
     pminsw xmm5, xmm4                         
                                               
     paddw xmm5, xmm7                          
     movdqa [esp+16*4], xmm5                   
                                               
                                               
     pxor xmm5, xmm5                           
     movdqa xmm1, [esp]                        
                                               
     pcmpgtw xmm5, [esp]                       
                                               
     psubw xmm1, [esp+16]                      
                                               
     pandn xmm5, xmm0                          
                                               
     psubw xmm1, [esp+16*2]                    
                                               
     pand xmm5, xmm1                           
                                               
     psubw xmm3, xmm7                          
                                               
     pxor xmm1, xmm1                           
                                               
     paddw xmm3, [ff_pw_4]                     
                                               
     psubw xmm1, xmm5                          
                                               
     movdqa xmm0, xmm6                         
     psubw xmm0, xmm2                          
                                               
     psllw xmm0, 2                             
                                               
     paddw xmm3, xmm0                          
                                               
     psraw xmm3, 3                             
     movdqa xmm0, [pw_pixel_max]               
                                               
     pmaxsw xmm3, xmm1                         
                                               
     pminsw xmm3, xmm5                         
                                               
     pxor xmm1, xmm1                           
                                               
     paddw xmm2, xmm3                          
                                               
     psubw xmm6, xmm3                          
                                               
     pmaxsw xmm2, xmm1                         
                                               
     pminsw xmm2, xmm0                         
                                               
     pmaxsw xmm6, xmm1                         
                                               
     pminsw xmm6, xmm0                         
     movdqa xmm3, [esp+16*3]                   
     movdqa xmm7, [esp+16*4]                   
     movdqa xmm4, xmm3                         
                                               
     punpcklwd xmm3, xmm2                      
                                               
     punpckhwd xmm4, xmm2                      
     movdqa xmm2, xmm6                         
                                               
     punpcklwd xmm6, xmm7                      
                                               
     punpckhwd xmm2, xmm7                      
     movdqa xmm7, xmm3                         
                                               
     punpckldq xmm3, xmm6                      
                                               
     punpckhdq xmm7, xmm6                      
     movdqa xmm6, xmm4                         
                                               
     punpckldq xmm4, xmm2                      
                                               
     punpckhdq xmm6, xmm2                      
     movq qword ptr[eax-4], xmm3                        
     movhps [eax+ecx-4], xmm3                  
     movq qword ptr[eax+ecx*2-4], xmm7                  
     movhps [edx-4], xmm7                      
     movq qword ptr[edx+ecx-4], xmm4                    
     movhps [edx+ecx*2-4], xmm4                
     movq qword ptr[edx+ebx-4], xmm6                    
     movhps [edx+ecx*4-4], xmm6                
                                               
     add esi, 16/8                             
     lea eax, [eax+ecx*(16/2)]                 
     lea edx, [edx+ecx*(16/2)]                 
     dec edi                                   
     jg  ff_deblock_h_luma_10_sse2loop
     add esp, 112                              
     pop edi                                   
     pop esi                                   
     pop ebx                                   
     ret                                       

	 }
}

// 2
void __declspec(naked) ff_deblock_v_chroma_intra_8_mmxext(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
   push ebx                                            
   push esi                                            
   mov eax, [esp + 8 + 4 + 0*4]                        
   mov ecx, [esp + 8 + 4 + 1*4]                        
   mov edx, [esp + 8 + 4 + 2*4]                        
   mov ebx, [esp + 8 + 4 + 3*4]                        
                                                       
   dec edx                                             
   dec ebx                                             
   mov esi, eax                                        
   sub esi, ecx                                        
   sub esi, ecx                                        
   movq mm0, [esi]                                     
   movq mm1, [esi+ecx]                                 
   movq mm2, [eax]                                     
   movq mm3, [eax+ecx]                                 
                                                       
   movd mm4, edx                                  

   movd mm5, ebx                                  
   pshufw mm4, mm4, (0)*0x55                      
   pshufw mm5, mm5, (0)*0x55                      
                                                  
   packuswb mm4, mm4                              
                                                  
   packuswb mm5, mm5                              
   movq mm6, mm2                                  
   movq mm7, mm1                                  
                                                  
   psubusb mm6, mm1                               
                                                  
   psubusb mm7, mm2                               
                                                  
   por mm7, mm6                                   
                                                  
   psubusb mm7, mm4                               
   movq mm6, mm1                                  
   movq mm4, mm0                                  
                                                  
   psubusb mm6, mm0                               
                                                  
   psubusb mm4, mm1                               
                                                  
   por mm4, mm6                                   
                                                  
   psubusb mm4, mm5                               
                                                  
   por mm7, mm4                                   
   movq mm6, mm2                                  
   movq mm4, mm3                                  
                                                  
   psubusb mm6, mm3                               
                                                  
   psubusb mm4, mm2                               
                                                  
   por mm4, mm6                                   
                                                  
   psubusb mm4, mm5                               
                                                  
   por mm7, mm4                                   
                                                  
   pxor mm6, mm6                                  
                                                  
   pcmpeqb mm7, mm6                               
  
   movq mm5, mm1                                  
   movq mm6, mm2                                  
   movq mm4, mm1                                  
  
                                                  
   pxor mm4, mm3                                  
                                                  
   pand mm4, [ff_pb_1]                            
                                                  
   pavgb mm1, mm3                                 
                                                  
   psubusb mm1, mm4                               
                                                  
   pavgb mm1, mm0                                 
  
   movq mm4, mm2                                  
  
                                                  
   pxor mm4, mm0                                  
                                                  
   pand mm4, [ff_pb_1]                            
                                                  
   pavgb mm2, mm0                                 
                                                  
   psubusb mm2, mm4                               
                                                  
   pavgb mm2, mm3                                 
  
                                                  
  
   psubb mm1, mm5                                 
  
                                                  
  
   psubb mm2, mm6                                 
  
                                                  
  
   pand mm1, mm7                                  
  
                                                  
  
   pand mm2, mm7                                  
  
                                                  
  
   paddb mm1, mm5                                 
  
                                                  
  
   paddb mm2, mm6                                 
  
   movq [esi+ecx], mm1                                 
   movq [eax], mm2                                     
   pop esi                                             

   pop ebx                                             
   ret                                                 

	 }
}

// 4
void __declspec(naked) ff_deblock_h_chroma_intra_8_mmxext(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
    push ebx                                       
    push esi                                       
    push edi                                       
    mov eax, [esp + 12 + 4 + 0*4]                  
    mov ecx, [esp + 12 + 4 + 1*4]                  
    mov edx, [esp + 12 + 4 + 2*4]                  
    mov ebx, [esp + 12 + 4 + 3*4]                  
                                                   
   
    dec edx                                        
   
    dec ebx                                        
    sub eax, 2                                     
    lea edi, [ecx+ecx*2]                               
    mov esi, eax                                   
    add eax, edi                                   
   
    movd mm0, [esi]                                
   
    movd mm2, [esi+ecx]                            
    movd mm1, [esi+ecx*2]                          
    movd mm3, [eax]                                
                                                   
    punpcklbw mm0, mm2                             
                                                   
    punpcklbw mm1, mm3                             
    movq mm2, mm0                                  
                                                   
    punpcklwd mm0, mm1                             
                                                   
    punpckhwd mm2, mm1                             
                                                   
    movd mm4, [eax+ecx]                            
    movd mm6, [eax+ecx*2]                          
    movd mm5, [eax+edi]                            
    movd mm7, [eax+ecx*4]                          
                                                   
    punpcklbw mm4, mm6                             
                                                   
    punpcklbw mm5, mm7                             
    movq mm6, mm4                                  
                                                   
    punpcklwd mm4, mm5                             
                                                   
    punpckhwd mm6, mm5                             
                                                   
                                                   
    movq mm1, mm0                                  
    punpckhdq mm1, mm4                             
                                                   
    movq mm3, mm2                                  
    punpckhdq mm3, mm6                             
                                                   
    punpckldq mm0, mm4                             
                                                   
    punpckldq mm2, mm6                             
   
                                                   
   
   movd mm4, edx                                      
  
   movd mm5, ebx                                      
   pshufw mm4, mm4, (0)*0x55                          
   pshufw mm5, mm5, (0)*0x55                          
                                                      
   packuswb mm4, mm4                                  
                                                      
   packuswb mm5, mm5                                  
   movq mm6, mm2                                      
   movq mm7, mm1                                      
                                                      
   psubusb mm6, mm1                                   
                                                      
   psubusb mm7, mm2                                   
                                                      
   por mm7, mm6                                       
                                                      
   psubusb mm7, mm4                                   
   movq mm6, mm1                                      
   movq mm4, mm0                                      
                                                      
   psubusb mm6, mm0                                   
                                                      
   psubusb mm4, mm1                                   
                                                      
   por mm4, mm6                                       
                                                      
   psubusb mm4, mm5                                   
                                                      
   por mm7, mm4                                       
   movq mm6, mm2                                      
   movq mm4, mm3                                      
                                                      
   psubusb mm6, mm3                                   
                                                      
   psubusb mm4, mm2                                   
                                                      
   por mm4, mm6                                       
                                                      
   psubusb mm4, mm5                                   
                                                      
   por mm7, mm4                                       
                                                      
   pxor mm6, mm6                                      
                                                      
   pcmpeqb mm7, mm6                                   
  
   movq mm5, mm1                                      
   movq mm6, mm2                                      
   movq mm4, mm1                                      
  
                                                      
   pxor mm4, mm3                                      
                                                      
   pand mm4, [ff_pb_1]                                
                                                      
   pavgb mm1, mm3                                     
                                                      
   psubusb mm1, mm4                                   
                                                      
   pavgb mm1, mm0                                     
  
   movq mm4, mm2                                      
  
                                                      
   pxor mm4, mm0                                      
                                                      
   pand mm4, [ff_pb_1]                                
                                                      
   pavgb mm2, mm0                                     
                                                      
   psubusb mm2, mm4                                   
                                                      
   pavgb mm2, mm3                                     
  
                                                      
  
   psubb mm1, mm5                                     
  
                                                      
  
   psubb mm2, mm6                                     
  
                                                      
  
   pand mm1, mm7                                      
  
                                                      
  
   pand mm2, mm7                                      
  
                                                      
  
   paddb mm1, mm5                                     
  
                                                      
  
   paddb mm2, mm6                                     
  
                                                   
   
    movq mm4, mm0                                  
    punpckhdq mm4, mm0                             
                                                   
    movq mm5, mm1                                  
    punpckhdq mm5, mm1                             
                                                   
    movq mm6, mm2                                  
    punpckhdq mm6, mm2                             
                                                   
                                                   
    punpcklbw mm0, mm1                             
                                                   
    punpcklbw mm2, mm3                             
                                                   
    movq mm1, mm0                                  
    punpcklwd mm1, mm2                             
                                                   
    punpckhwd mm0, mm2                             
    movd [esi], mm1                                
                                                   
    punpckhdq mm1, mm1                             
    movd [esi+ecx], mm1                            
    movd [esi+ecx*2], mm0                          
                                                   
    punpckhdq mm0, mm0                             
    movd [eax], mm0                                
                                                   
                                                   
    punpckhdq mm3, mm3                             
                                                   
    punpcklbw mm4, mm5                             
                                                   
    punpcklbw mm6, mm3                             
                                                   
    movq mm5, mm4                                  
    punpcklwd mm5, mm6                             
                                                   
    punpckhwd mm4, mm6                             
    movd [eax+ecx], mm5                            
                                                   
    punpckhdq mm5, mm5                             
    movd [eax+ecx*2], mm5                          
    movd [eax+edi], mm4                            
                                                   
    punpckhdq mm4, mm4                             
    movd [eax+ecx*4], mm4                          
   
    pop edi                                        
   
    pop esi                                        
    pop ebx                                        
    ret
	 }
}
// 5
//void ff_deblock_v_luma_8_mmxext(uint8_t *pix, int stride, int alpha, int beta, int8_t *tc0)
//{
//    if((tc0[0] & tc0[1]) >= 0)
//        ff_deblock_v8_luma_8_mmxext(pix+0, stride, alpha, beta, tc0);
//    if((tc0[2] & tc0[3]) >= 0)
//        ff_deblock_v8_luma_8_mmxext(pix+8, stride, alpha, beta, tc0+2);
//}

void __declspec(naked) ff_deblock_v8_luma_intra_8_mmxext(uint8_t *pix, int stride, int alpha, int beta)
{
	__asm{
   push ebx                                     
   push esi                                     
   push edi                                     
   mov eax, [esp + 12 + 4 + 0*4]                
   mov ecx, [esp + 12 + 4 + 1*4]                
   mov edx, [esp + 12 + 4 + 2*4]                
   mov ebx, [esp + 12 + 4 + 3*4]                
                                                
   sub esp, 0x60                                
   lea esi, [ecx*4]                             
   lea edi, [ecx+ecx*2]
   dec edx                                      
   jl  ff_deblock_v8_luma_intra_8_mmxextEnd                                      
   neg esi                                      
   dec ebx                                      
   jl  ff_deblock_v8_luma_intra_8_mmxextEnd
   add esi, eax                                 
   movq mm0, [esi+2*ecx]                        
   movq mm1, [esi+edi]                          
   movq mm2, [eax]                              
   movq mm3, [eax+ecx]                          
   movd mm4, edx                                
   movd mm5, ebx                                
   pshufw mm4, mm4, (0)*0x55                    
   pshufw mm5, mm5, (0)*0x55                    
                                                
   packuswb mm4, mm4                            
                                                
   packuswb mm5, mm5                            
   movq [esp+16*1+((12+4)&15)], mm4             
   movq mm6, mm2                                
   movq mm7, mm1                                
                                                
   psubusb mm6, mm1                             
                                                
   psubusb mm7, mm2                             
                                                
   por mm7, mm6                                 
                                                
   psubusb mm7, mm4                             
   movq mm6, mm1                                
   movq mm4, mm0                                
                                                
   psubusb mm6, mm0                             
                                                
   psubusb mm4, mm1                             
                                                
   por mm4, mm6                                 
                                                
   psubusb mm4, mm5                             
                                                
   por mm7, mm4                                 
   movq mm6, mm2                                
   movq mm4, mm3                                
                                                
   psubusb mm6, mm3                             
                                                
   psubusb mm4, mm2                             
                                                
   por mm4, mm6                                 
                                                
   psubusb mm4, mm5                             
                                                
   por mm7, mm4                                 
                                                
   pxor mm6, mm6                                
                                                
   pcmpeqb mm7, mm6                             
   movq mm4, [esp+16*1+((12+4)&15)]             
   movq [esp+16*2+((12+4)&15)], mm7             
                                                
   pavgb mm4, [ff_pb_0]                         
                                                
   pavgb mm4, [ff_pb_1]                         
   movq mm7, mm2                                
   movq mm6, mm1                                
                                                
   psubusb mm7, mm1                             
                                                
   psubusb mm6, mm2                             
                                                
   psubusb mm7, mm4                             
                                                
   psubusb mm6, mm4                             
                                                
   pcmpeqb mm6, mm7                             
                                                
   pand mm6, [esp+16*2+((12+4)&15)]             
   movq mm7, [esi+ecx]                          
   movq mm4, mm1                                
                                                
   psubusb mm7, mm1                             
                                                
   psubusb mm4, [esi+ecx]                       
                                                
   psubusb mm7, mm5                             
                                                
   psubusb mm4, mm5                             
                                                
   pcmpeqb mm4, mm7                             
                                                
   pand mm4, mm6                                
   movq [esp+16*3+((12+4)&15)], mm4             
   movq mm7, [eax+2*ecx]                        
   movq mm4, mm2                                
                                                
   psubusb mm7, mm2                             
                                                
   psubusb mm4, [eax+2*ecx]                     
                                                
   psubusb mm7, mm5                             
                                                
   psubusb mm4, mm5                             
                                                
   pcmpeqb mm4, mm7                             
                                                
   pand mm4, mm6                                
   movq [esp+16*4+((12+4)&15)], mm4             
   movq mm4, [esi+ecx]                          
   movq mm5, mm1                                
                                                
   pavgb mm4, mm0                               
                                                
   pavgb mm5, mm2                               
                                                
   pavgb mm4, mm5                               
   movq [esp+16*1+((12+4)&15)], mm5             
   movq mm6, [esi+ecx]                          
   movq mm7, mm1                                
                                                
   paddb mm6, mm0                               
                                                
   paddb mm7, mm2                               
                                                
   paddb mm6, mm7                               
   movq mm7, mm6                                
   movq [esp+16*0+((12+4)&15)], mm6             
                                                
   psrlw mm6, 1                                 
                                                
   pavgb mm6, [ff_pb_0]                         
                                                
   pxor mm6, mm4                                
                                                
   pand mm6, [ff_pb_1]                          
                                                
   psubb mm4, mm6                               
                                                
   movq mm5, [esi+ecx]                          
   movq mm6, [esi+ecx]                          
                                                
   pavgb mm5, mm3                               
                                                
   psubb mm6, mm3                               
                                                
   paddb mm7, mm7                               
                                                
   psubb mm7, mm6                               
                                                
   pand mm6, [ff_pb_1]                          
                                                
   psubb mm5, mm6                               
                                                
   pavgb mm5, mm0                               
                                                
   pavgb mm5, [esp+16*1+((12+4)&15)]            
                                                
   psrlw mm7, 2                                 
                                                
   pavgb mm7, [ff_pb_0]                         
                                                
   pxor mm7, mm5                                
                                                
   pand mm7, [ff_pb_1]                          
                                                
   psubb mm5, mm7                               
                                                
                                                
   movq mm7, mm1                                
   pxor mm7, mm3                                
                                                
   movq mm6, mm1                                
   pavgb mm6, mm3                               
                                                
   pand mm7, [ff_pb_1]                          
                                                
   psubb mm6, mm7                               
                                                
   pavgb mm6, mm0                               
                                                
                                                
   pxor mm5, mm6                                
                                                
   pxor mm6, mm1                                
                                                
   pand mm5, [esp+16*3+((12+4)&15)]             
                                                
   pand mm6, [esp+16*2+((12+4)&15)]             
                                                
   pxor mm5, mm6                                
                                                
   pxor mm5, mm1                                
   movq [esi+edi], mm5                          
                                                
   movq mm5, [esi]                              
                                                
   movq mm6, [esi+ecx]                          
   paddb mm6, mm5                               
                                                
   pavgb mm5, [esi+ecx]                         
                                                
   pavgb mm5, mm4                               
                                                
   paddb mm6, mm6                               
                                                
   paddb mm6, [esp+16*0+((12+4)&15)]            
                                                
   psrlw mm6, 2                                 
                                                
   pavgb mm6, [ff_pb_0]                         
                                                
   pxor mm6, mm5                                
                                                
   pand mm6, [ff_pb_1]                          
                                                
   psubb mm5, mm6                               
                                                
                                                
   pxor mm4, mm0                                
                                                
   pxor mm5, [esi+ecx]                          
                                                
   pand mm4, [esp+16*3+((12+4)&15)]             
                                                
   pand mm5, [esp+16*3+((12+4)&15)]             
                                                
   pxor mm4, mm0                                
                                                
   pxor mm5, [esi+ecx]                          
   movq [esi+2*ecx], mm4                        
   movq [esi+ecx], mm5                          
   movq mm4, [eax+2*ecx]                        
   movq mm5, mm2                                
                                                
   pavgb mm4, mm3                               
                                                
   pavgb mm5, mm1                               
                                                
   pavgb mm4, mm5                               
   movq [esp+16*1+((12+4)&15)], mm5             
   movq mm6, [eax+2*ecx]                        
   movq mm7, mm2                                
                                                
   paddb mm6, mm3                               
                                                
   paddb mm7, mm1                               
                                                
   paddb mm6, mm7                               
   movq mm7, mm6                                
   movq [esp+16*0+((12+4)&15)], mm6             
                                                
   psrlw mm6, 1                                 
                                                
   pavgb mm6, [ff_pb_0]                         
                                                
   pxor mm6, mm4                                
                                                
   pand mm6, [ff_pb_1]                          
                                                
   psubb mm4, mm6                               
                                                
   movq mm5, [eax+2*ecx]                        
   movq mm6, [eax+2*ecx]                        
                                                
   pavgb mm5, mm0                               
                                                
   psubb mm6, mm0                               
                                                
   paddb mm7, mm7                               
                                                
   psubb mm7, mm6                               
                                                
   pand mm6, [ff_pb_1]                          
                                                
   psubb mm5, mm6                               
                                                
   pavgb mm5, mm3                               
                                                
   pavgb mm5, [esp+16*1+((12+4)&15)]            
                                                
   psrlw mm7, 2                                 
                                                
   pavgb mm7, [ff_pb_0]                         
                                                
   pxor mm7, mm5                                
                                                
   pand mm7, [ff_pb_1]                          
                                                
   psubb mm5, mm7                               
                                                
                                                
   movq mm7, mm2                                
   pxor mm7, mm0                                
                                                
   movq mm6, mm2                                
   pavgb mm6, mm0                               
                                                
   pand mm7, [ff_pb_1]                          
                                                
   psubb mm6, mm7                               
                                                
   pavgb mm6, mm3                               
                                                
                                                
   pxor mm5, mm6                                
                                                
   pxor mm6, mm2                                
                                                
   pand mm5, [esp+16*4+((12+4)&15)]             
                                                
   pand mm6, [esp+16*2+((12+4)&15)]             
                                                
   pxor mm5, mm6                                
                                                
   pxor mm5, mm2                                
   movq [eax], mm5                              
                                                
   movq mm5, [eax+edi]                          
                                                
   movq mm6, [eax+2*ecx]                        
   paddb mm6, mm5                               
                                                
   pavgb mm5, [eax+2*ecx]                       
                                                
   pavgb mm5, mm4                               
                                                
   paddb mm6, mm6                               
                                                
   paddb mm6, [esp+16*0+((12+4)&15)]            
                                                
   psrlw mm6, 2                                 
                                                
   pavgb mm6, [ff_pb_0]                         
                                                
   pxor mm6, mm5                                
                                                
   pand mm6, [ff_pb_1]                          
                                                
   psubb mm5, mm6                               
                                                
                                                
   pxor mm4, mm3                                
                                                
   pxor mm5, [eax+2*ecx]                        
                                                
   pand mm4, [esp+16*4+((12+4)&15)]             
                                                
   pand mm5, [esp+16*4+((12+4)&15)]             
                                                
   pxor mm4, mm3                                
                                                
   pxor mm5, [eax+2*ecx]                        
   movq [eax+ecx], mm4                          
   movq [eax+2*ecx], mm5                        
ff_deblock_v8_luma_intra_8_mmxextEnd:                                         
   add esp, 0x60                                
   pop edi                                      
   pop esi                                      
   pop ebx                                      
   ret                                          

	}
}

// 7
void ff_deblock_v_luma_intra_8_mmxext(uint8_t *pix, int stride, int alpha, int beta)
{
    ff_deblock_v8_luma_intra_8_mmxext(pix+0, stride, alpha, beta);
    ff_deblock_v8_luma_intra_8_mmxext(pix+8, stride, alpha, beta);
}

// 8
void __declspec(naked) ff_deblock_h_luma_intra_8_mmxext(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
   push ebx                                    
   mov eax, [esp + 4 + 4 + 0*4]                
   mov ecx, [esp + 4 + 4 + 1*4]                
                                               
   lea ebx, [ecx+ecx*2]                            
   sub eax, 4                                  
   lea edx, [eax+ebx]                          
   sub esp, 136                                
                                               
                                               
   movq mm0, [eax]                             
   movq mm1, [eax+ecx]                         
   movq mm2, [eax+ecx*2]                       
   movq mm3, [edx]                             
   movq mm4, [edx+ecx]                         
   movq mm5, [edx+ecx*2]                       
   movq mm6, [edx+ebx]                         
   movq mm7, mm0                               
                                               
   punpcklbw mm0, mm1                          
                                               
   punpckhbw mm7, mm1                          
   movq mm1, mm2                               
                                               
   punpcklbw mm2, mm3                          
                                               
   punpckhbw mm1, mm3                          
   movq mm3, mm4                               
                                               
   punpcklbw mm4, mm5                          
                                               
   punpckhbw mm3, mm5                          
                                               
   movq mm5, mm6                               
   punpckhbw mm5, [edx+ecx*4]                  
                                               
   punpcklbw mm6, [edx+ecx*4]                  
   movq [esp], mm3                             
   movq mm3, mm0                               
                                               
   punpcklwd mm0, mm2                          
                                               
   punpckhwd mm3, mm2                          
   movq mm2, mm4                               
                                               
   punpcklwd mm4, mm6                          
                                               
   punpckhwd mm2, mm6                          
   movq mm6, mm7                               
                                               
   punpcklwd mm7, mm1                          
                                               
   punpckhwd mm6, mm1                          
   movq [esp+0x10*2], mm2                      
   movq mm2, [esp]                             
   movq mm1, mm2                               
                                               
   punpcklwd mm2, mm5                          
                                               
   punpckhwd mm1, mm5                          
   movq mm5, mm0                               
                                               
   punpckldq mm0, mm4                          
                                               
   punpckhdq mm5, mm4                          
   movq mm4, mm7                               
                                               
   punpckldq mm7, mm2                          
                                               
   punpckhdq mm4, mm2                          
   movq [esp], mm0                             
   movq [esp+0x10], mm5                        
   movq [esp+0x30+0x10], mm7                   
   movq [esp+0x30+0x10*2], mm4                 
                                               
   movq mm0, mm3                               
   punpckhdq mm0, [esp+0x10*2]                 
                                               
   punpckldq mm3, [esp+0x10*2]                 
   movq mm5, mm6                               
                                               
   punpckldq mm6, mm1                          
                                               
   punpckhdq mm5, mm1                          
   movq [esp+0x10*2], mm3                      
   movq [esp+0x30], mm0                        
   movq [esp+0x30+0x30], mm6                   
   movq [esp+0x30+0x10*4], mm5                 
   lea eax, [eax+ecx*8]                        
   lea edx, [edx+ecx*8]                        
   movq mm0, [eax]                             
   movq mm1, [eax+ecx]                         
   movq mm2, [eax+ecx*2]                       
   movq mm3, [edx]                             
   movq mm4, [edx+ecx]                         
   movq mm5, [edx+ecx*2]                       
   movq mm6, [edx+ebx]                         
   movq mm7, mm0                               
                                               
   punpcklbw mm0, mm1                          
                                               
   punpckhbw mm7, mm1                          
   movq mm1, mm2                               
                                               
   punpcklbw mm2, mm3                          
                                               
   punpckhbw mm1, mm3                          
   movq mm3, mm4                               
                                               
   punpcklbw mm4, mm5                          
                                               
   punpckhbw mm3, mm5                          
                                               
   movq mm5, mm6                               
   punpckhbw mm5, [edx+ecx*4]                  
                                               
   punpcklbw mm6, [edx+ecx*4]                  
   movq [esp+8], mm3                           
   movq mm3, mm0                               
                                               
   punpcklwd mm0, mm2                          
                                               
   punpckhwd mm3, mm2                          
   movq mm2, mm4                               
                                               
   punpcklwd mm4, mm6                          
                                               
   punpckhwd mm2, mm6                          
   movq mm6, mm7                               
                                               
   punpcklwd mm7, mm1                          
                                               
   punpckhwd mm6, mm1                          
   movq [esp+8+0x10*2], mm2                    
   movq mm2, [esp+8]                           
   movq mm1, mm2                               
                                               
   punpcklwd mm2, mm5                          
                                               
   punpckhwd mm1, mm5                          
   movq mm5, mm0                               
                                               
   punpckldq mm0, mm4                          
                                               
   punpckhdq mm5, mm4                          
   movq mm4, mm7                               
                                               
   punpckldq mm7, mm2                          
                                               
   punpckhdq mm4, mm2                          
   movq [esp+8], mm0                           
   movq [esp+8+0x10], mm5                      
   movq [esp+0x38+0x10], mm7                   
   movq [esp+0x38+0x10*2], mm4                 
                                               
   movq mm0, mm3                               
   punpckhdq mm0, [esp+8+0x10*2]               
                                               
   punpckldq mm3, [esp+8+0x10*2]               
   movq mm5, mm6                               
                                               
   punpckldq mm6, mm1                          
                                               
   punpckhdq mm5, mm1                          
   movq [esp+8+0x10*2], mm3                    
   movq [esp+0x38], mm0                        
   movq [esp+0x38+0x30], mm6                   
   movq [esp+0x38+0x10*4], mm5                 
                                               
   lea eax, [esp+0x40]                         
   push dword ptr[esp + 140 + 16]                 
   push dword ptr[esp + 144 + 12]                 
   push 16                               
   push eax                                    
                                               
   call ff_deblock_v8_luma_intra_8_mmxext      
   add dword ptr[esp], 8                          
                                               
   call ff_deblock_v8_luma_intra_8_mmxext      
   add esp, 16                                 
                                               
   mov ecx, [esp + 140 + 8]                    
   mov eax, dword ptr[esp + 140 + 4]              
   lea ebx, [ecx+ecx*2]                            
   sub eax, 4                                  
   lea edx, [eax+ebx]                          
                                               
   movq mm0, [esp]                             
   movq mm1, [esp+0x10]                        
   movq mm2, [esp+0x10*2]                      
   movq mm3, [esp+0x30]                        
   movq mm4, [esp+0x30+0x10]                   
   movq mm5, [esp+0x30+0x10*2]                 
   movq mm6, [esp+0x30+0x30]                   
   movq mm7, mm0                               
                                               
   punpcklbw mm0, mm1                          
                                               
   punpckhbw mm7, mm1                          
   movq mm1, mm2                               
                                               
   punpcklbw mm2, mm3                          
                                               
   punpckhbw mm1, mm3                          
   movq mm3, mm4                               
                                               
   punpcklbw mm4, mm5                          
                                               
   punpckhbw mm3, mm5                          
                                               
   movq mm5, mm6                               
   punpckhbw mm5, [esp+0x30+0x10*4]            
                                               
   punpcklbw mm6, [esp+0x30+0x10*4]            
   movq [eax], mm3                             
   movq mm3, mm0                               
                                               
   punpcklwd mm0, mm2                          
                                               
   punpckhwd mm3, mm2                          
   movq mm2, mm4                               
                                               
   punpcklwd mm4, mm6                          
                                               
   punpckhwd mm2, mm6                          
   movq mm6, mm7                               
                                               
   punpcklwd mm7, mm1                          
                                               
   punpckhwd mm6, mm1                          
   movq [eax+ecx*2], mm2                       
   movq mm2, [eax]                             
   movq mm1, mm2                               
                                               
   punpcklwd mm2, mm5                          
                                               
   punpckhwd mm1, mm5                          
   movq mm5, mm0                               
                                               
   punpckldq mm0, mm4                          
                                               
   punpckhdq mm5, mm4                          
   movq mm4, mm7                               
                                               
   punpckldq mm7, mm2                          
                                               
   punpckhdq mm4, mm2                          
   movq [eax], mm0                             
   movq [eax+ecx], mm5                         
   movq [edx+ecx], mm7                         
   movq [edx+ecx*2], mm4                       
                                               
   movq mm0, mm3                               
   punpckhdq mm0, [eax+ecx*2]                  
                                               
   punpckldq mm3, [eax+ecx*2]                  
   movq mm5, mm6                               
                                               
   punpckldq mm6, mm1                          
                                               
   punpckhdq mm5, mm1                          
   movq [eax+ecx*2], mm3                       
   movq [edx], mm0                             
   movq [edx+ebx], mm6                         
   movq [edx+ecx*4], mm5                       
   lea eax, [eax+ecx*8]                        
   lea edx, [edx+ecx*8]                        
   movq mm0, [esp+8]                           
   movq mm1, [esp+8+0x10]                      
   movq mm2, [esp+8+0x10*2]                    
   movq mm3, [esp+0x38]                        
   movq mm4, [esp+0x38+0x10]                   
   movq mm5, [esp+0x38+0x10*2]                 
   movq mm6, [esp+0x38+0x30]                   
   movq mm7, mm0                               
                                               
   punpcklbw mm0, mm1                          
                                               
   punpckhbw mm7, mm1                          
   movq mm1, mm2                               
                                               
   punpcklbw mm2, mm3                          
                                               
   punpckhbw mm1, mm3                          
   movq mm3, mm4                               
                                               
   punpcklbw mm4, mm5                          
                                               
   punpckhbw mm3, mm5                          
                                               
   movq mm5, mm6                               
   punpckhbw mm5, [esp+0x38+0x10*4]            
                                               
   punpcklbw mm6, [esp+0x38+0x10*4]            
   movq [eax], mm3                             
   movq mm3, mm0                               
                                               
   punpcklwd mm0, mm2                          
                                               
   punpckhwd mm3, mm2                          
   movq mm2, mm4                               
                                               
   punpcklwd mm4, mm6                          
                                               
   punpckhwd mm2, mm6                          
   movq mm6, mm7                               
                                               
   punpcklwd mm7, mm1                          
                                               
   punpckhwd mm6, mm1                          
   movq [eax+ecx*2], mm2                       
   movq mm2, [eax]                             
   movq mm1, mm2                               
                                               
   punpcklwd mm2, mm5                          
                                               
   punpckhwd mm1, mm5                          
   movq mm5, mm0                               
                                               
   punpckldq mm0, mm4                          
                                               
   punpckhdq mm5, mm4                          
   movq mm4, mm7                               
                                               
   punpckldq mm7, mm2                          
                                               
   punpckhdq mm4, mm2                          
   movq [eax], mm0                             
   movq [eax+ecx], mm5                         
   movq [edx+ecx], mm7                         
   movq [edx+ecx*2], mm4                       
                                               
   movq mm0, mm3                               
   punpckhdq mm0, [eax+ecx*2]                  
                                               
   punpckldq mm3, [eax+ecx*2]                  
   movq mm5, mm6                               
                                               
   punpckldq mm6, mm1                          
                                               
   punpckhdq mm5, mm1                          
   movq [eax+ecx*2], mm3                       
   movq [edx], mm0                             
   movq [edx+ebx], mm6                         
   movq [edx+ecx*4], mm5                       
   add esp, 136                                
   pop ebx                                     
   ret
	 }
}
void __declspec(naked) ff_deblock_v_luma_intra_8_sse2(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
   push ebp
   push ebx                                 
   push esi                                 
   push edi
   mov  ebp,esp
   //stack info.
   // beta
   // alpha
   // stride
   // pix
   // return_addr		[ebp+16]
   // ebp				[ebp+12]
   // ebx				[ebp+8]
   // esi				[ebp+4]
   // edi				[ebp]   

   mov eax, [esp + 16 + 4 + 0*4]            
   mov ecx, [esp + 16 + 4 + 1*4]            
   mov edx, [esp + 16 + 4 + 2*4]            
   mov ebx, [esp + 16 + 4 + 3*4]

   sub esp,(96+15)
   and esp,0xfffffff0
                                            
                       
   lea esi, [ecx*4]                         
   lea edi, [ecx+ecx*2]                         
   dec edx                                  
   jl  ff_deblock_v_luma_intra_8_sse2end                                  
   neg esi                                  
   dec ebx                                  
   jl  ff_deblock_v_luma_intra_8_sse2end
   add esi, eax                             
   movdqa xmm0, [esi+2*ecx]                 
   movdqa xmm1, [esi+edi]                   
   movdqa xmm2, [eax]                       
   movdqa xmm3, [eax+ecx]                   
   movd xmm4, edx                           
   movd xmm5, ebx                           
   pshuflw xmm4, xmm4, (0)*0x55             
                                            
   punpcklqdq xmm4, xmm4                    
   pshuflw xmm5, xmm5, (0)*0x55             
                                            
   punpcklqdq xmm5, xmm5                    
                                            
   packuswb xmm4, xmm4                      
                                            
   packuswb xmm5, xmm5                      
   movdqa [esp+16*1+((12+4)&15)], xmm4      
   movdqa xmm6, xmm2                        
   movdqa xmm7, xmm1                        
                                            
   psubusb xmm6, xmm1                       
                                            
   psubusb xmm7, xmm2                       
                                            
   por xmm7, xmm6                           
                                            
   psubusb xmm7, xmm4                       
   movdqa xmm6, xmm1                        
   movdqa xmm4, xmm0                        
                                            
   psubusb xmm6, xmm0                       
                                            
   psubusb xmm4, xmm1                       
                                            
   por xmm4, xmm6                           
                                            
   psubusb xmm4, xmm5                       
                                            
   por xmm7, xmm4                           
   movdqa xmm6, xmm2                        
   movdqa xmm4, xmm3                        
                                            
   psubusb xmm6, xmm3                       
                                            
   psubusb xmm4, xmm2                       
                                            
   por xmm4, xmm6                           
                                            
   psubusb xmm4, xmm5                       
                                            
   por xmm7, xmm4                           
                                            
   pxor xmm6, xmm6                          
                                            
   pcmpeqb xmm7, xmm6                       
   movdqa xmm4, [esp+16*1+((12+4)&15)]      
   movdqa [esp+16*2+((12+4)&15)], xmm7      
                                            
   pavgb xmm4, [ff_pb_0]                    
                                            
   pavgb xmm4, [ff_pb_1]                    
   movdqa xmm7, xmm2                        
   movdqa xmm6, xmm1                        
                                            
   psubusb xmm7, xmm1                       
                                            
   psubusb xmm6, xmm2                       
                                            
   psubusb xmm7, xmm4                       
                                            
   psubusb xmm6, xmm4                       
                                            
   pcmpeqb xmm6, xmm7                       
                                            
   pand xmm6, [esp+16*2+((12+4)&15)]        
   movdqa xmm7, [esi+ecx]                   
   movdqa xmm4, xmm1                        
                                            
   psubusb xmm7, xmm1                       
                                            
   psubusb xmm4, [esi+ecx]                  
                                            
   psubusb xmm7, xmm5                       
                                            
   psubusb xmm4, xmm5                       
                                            
   pcmpeqb xmm4, xmm7                       
                                            
   pand xmm4, xmm6                          
   movdqa [esp+16*3+((12+4)&15)], xmm4      
   movdqa xmm7, [eax+2*ecx]                 
   movdqa xmm4, xmm2                        
                                            
   psubusb xmm7, xmm2                       
                                            
   psubusb xmm4, [eax+2*ecx]                
                                            
   psubusb xmm7, xmm5                       
                                            
   psubusb xmm4, xmm5                       
                                            
   pcmpeqb xmm4, xmm7                       
                                            
   pand xmm4, xmm6                          
   movdqa [esp+16*4+((12+4)&15)], xmm4      
   movdqa xmm4, [esi+ecx]                   
   movdqa xmm5, xmm1                        
                                            
   pavgb xmm4, xmm0                         
                                            
   pavgb xmm5, xmm2                         
                                            
   pavgb xmm4, xmm5                         
   movdqa [esp+16*1+((12+4)&15)], xmm5      
   movdqa xmm6, [esi+ecx]                   
   movdqa xmm7, xmm1                        
                                            
   paddb xmm6, xmm0                         
                                            
   paddb xmm7, xmm2                         
                                            
   paddb xmm6, xmm7                         
   movdqa xmm7, xmm6                        
   movdqa [esp+16*0+((12+4)&15)], xmm6      
                                            
   psrlw xmm6, 1                            
                                            
   pavgb xmm6, [ff_pb_0]                    
                                            
   pxor xmm6, xmm4                          
                                            
   pand xmm6, [ff_pb_1]                     
                                            
   psubb xmm4, xmm6                         
                                            
   movdqa xmm5, [esi+ecx]                   
   movdqa xmm6, [esi+ecx]                   
                                            
   pavgb xmm5, xmm3                         
                                            
   psubb xmm6, xmm3                         
                                            
   paddb xmm7, xmm7                         
                                            
   psubb xmm7, xmm6                         
                                            
   pand xmm6, [ff_pb_1]                     
                                            
   psubb xmm5, xmm6                         
                                            
   pavgb xmm5, xmm0                         
                                            
   pavgb xmm5, [esp+16*1+((12+4)&15)]       
                                            
   psrlw xmm7, 2                            
                                            
   pavgb xmm7, [ff_pb_0]                    
                                            
   pxor xmm7, xmm5                          
                                            
   pand xmm7, [ff_pb_1]                     
                                            
   psubb xmm5, xmm7                         
                                            
                                            
   movdqa xmm7, xmm1                        
   pxor xmm7, xmm3                          
                                            
   movdqa xmm6, xmm1                        
   pavgb xmm6, xmm3                         
                                            
   pand xmm7, [ff_pb_1]                     
                                            
   psubb xmm6, xmm7                         
                                            
   pavgb xmm6, xmm0                         
                                            
                                            
   pxor xmm5, xmm6                          
                                            
   pxor xmm6, xmm1                          
                                            
   pand xmm5, [esp+16*3+((12+4)&15)]        
                                            
   pand xmm6, [esp+16*2+((12+4)&15)]        
                                            
   pxor xmm5, xmm6                          
                                            
   pxor xmm5, xmm1                          
   movdqa [esi+edi], xmm5                   
                                            
   movdqa xmm5, [esi]                       
                                            
   movdqa xmm6, [esi+ecx]                   
   paddb xmm6, xmm5                         
                                            
   pavgb xmm5, [esi+ecx]                    
                                            
   pavgb xmm5, xmm4                         
                                            
   paddb xmm6, xmm6                         
                                            
   paddb xmm6, [esp+16*0+((12+4)&15)]       
                                            
   psrlw xmm6, 2                            
                                            
   pavgb xmm6, [ff_pb_0]                    
                                            
   pxor xmm6, xmm5                          
                                            
   pand xmm6, [ff_pb_1]                     
                                            
   psubb xmm5, xmm6                         
                                            
                                            
   pxor xmm4, xmm0                          
                                            
   pxor xmm5, [esi+ecx]                     
                                            
   pand xmm4, [esp+16*3+((12+4)&15)]        
                                            
   pand xmm5, [esp+16*3+((12+4)&15)]        
                                            
   pxor xmm4, xmm0                          
                                            
   pxor xmm5, [esi+ecx]                     
   movdqa [esi+2*ecx], xmm4                 
   movdqa [esi+ecx], xmm5                   
   movdqa xmm4, [eax+2*ecx]                 
   movdqa xmm5, xmm2                        
                                            
   pavgb xmm4, xmm3                         
                                            
   pavgb xmm5, xmm1                         
                                            
   pavgb xmm4, xmm5                         
   movdqa [esp+16*1+((12+4)&15)], xmm5      
   movdqa xmm6, [eax+2*ecx]                 
   movdqa xmm7, xmm2                        
                                            
   paddb xmm6, xmm3                         
                                            
   paddb xmm7, xmm1                         
                                            
   paddb xmm6, xmm7                         
   movdqa xmm7, xmm6                        
   movdqa [esp+16*0+((12+4)&15)], xmm6      
                                            
   psrlw xmm6, 1                            
                                            
   pavgb xmm6, [ff_pb_0]                    
                                            
   pxor xmm6, xmm4                          
                                            
   pand xmm6, [ff_pb_1]                     
                                            
   psubb xmm4, xmm6                         
                                            
   movdqa xmm5, [eax+2*ecx]                 
   movdqa xmm6, [eax+2*ecx]                 
                                            
   pavgb xmm5, xmm0                         
                                            
   psubb xmm6, xmm0                         
                                            
   paddb xmm7, xmm7                         
                                            
   psubb xmm7, xmm6                         
                                            
   pand xmm6, [ff_pb_1]                     
                                            
   psubb xmm5, xmm6                         
                                            
   pavgb xmm5, xmm3                         
                                            
   pavgb xmm5, [esp+16*1+((12+4)&15)]       
                                            
   psrlw xmm7, 2                            
                                            
   pavgb xmm7, [ff_pb_0]                    
                                            
   pxor xmm7, xmm5                          
                                            
   pand xmm7, [ff_pb_1]                     
                                            
   psubb xmm5, xmm7                         
                                            
                                            
   movdqa xmm7, xmm2                        
   pxor xmm7, xmm0                          
                                            
   movdqa xmm6, xmm2                        
   pavgb xmm6, xmm0                         
                                            
   pand xmm7, [ff_pb_1]                     
                                            
   psubb xmm6, xmm7                         
                                            
   pavgb xmm6, xmm3                         
                                            
                                            
   pxor xmm5, xmm6                          
                                            
   pxor xmm6, xmm2                          
                                            
   pand xmm5, [esp+16*4+((12+4)&15)]        
                                            
   pand xmm6, [esp+16*2+((12+4)&15)]        
                                            
   pxor xmm5, xmm6                          
                                            
   pxor xmm5, xmm2                          
   movdqa [eax], xmm5                       
                                            
   movdqa xmm5, [eax+edi]                   
                                            
   movdqa xmm6, [eax+2*ecx]                 
   paddb xmm6, xmm5                         
                                            
   pavgb xmm5, [eax+2*ecx]                  
                                            
   pavgb xmm5, xmm4                         
                                            
   paddb xmm6, xmm6                         
                                            
   paddb xmm6, [esp+16*0+((12+4)&15)]       
                                            
   psrlw xmm6, 2                            
                                            
   pavgb xmm6, [ff_pb_0]                    
                                            
   pxor xmm6, xmm5                          
                                            
   pand xmm6, [ff_pb_1]                     
                                            
   psubb xmm5, xmm6                                            
                                            
   pxor xmm4, xmm3                          
                                            
   pxor xmm5, [eax+2*ecx]                   
                                            
   pand xmm4, [esp+16*4+((12+4)&15)]        
                                            
   pand xmm5, [esp+16*4+((12+4)&15)]        
                                            
   pxor xmm4, xmm3                          
                                            
   pxor xmm5, [eax+2*ecx]                   
   movdqa [eax+ecx], xmm4                   
   movdqa [eax+2*ecx], xmm5                 
ff_deblock_v_luma_intra_8_sse2end:                                     
   mov esp,ebp                            
   pop edi                                  
   pop esi                                  
   pop ebx
   pop ebp
   ret
	 }
}
void __declspec(naked) ff_deblock_h_luma_intra_8_sse2(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
	push ebp
    push ebx
	mov  ebp,esp
	// stack info.
	// beta				[ebp+8+16]
	// alpha			[ebp+8+12]
	// stride			[ebp+8+8]
	// pix				[ebp+8+4]
	// return_addr		[ebp+8]
	// ebp				[ebp+4]
	// ebx				[ebp]
	

    mov eax, [ebp + 8 + 4 + 0*4]                     
    mov ecx, [ebp + 8 + 4 + 1*4]                     
                                                     
    lea ebx, [ecx+ecx*2]                                 
    sub eax, 4                                       
    lea edx, [eax+ebx]                               
    sub esp, 136
	and esp,0xfffffff0	// esp 16 byte align                                                     
                                                     
    movq mm0, [eax]                                  
    movq mm1, [eax+ecx]                              
    movq mm2, [eax+ecx*2]                            
    movq mm3, [edx]                                  
    movq mm4, [edx+ecx]                              
    movq mm5, [edx+ecx*2]                            
    movq mm6, [edx+ebx]                              
    movq mm7, mm0                                    
                                                     
    punpcklbw mm0, mm1                               
                                                     
    punpckhbw mm7, mm1                               
    movq mm1, mm2                                    
                                                     
    punpcklbw mm2, mm3                               
                                                     
    punpckhbw mm1, mm3                               
    movq mm3, mm4                                    
                                                     
    punpcklbw mm4, mm5                               
                                                     
    punpckhbw mm3, mm5                               
                                                     
    movq mm5, mm6                                    
    punpckhbw mm5, [edx+ecx*4]                       
                                                     
    punpcklbw mm6, [edx+ecx*4]                       
    movq [esp], mm3                                  
    movq mm3, mm0                                    
                                                     
    punpcklwd mm0, mm2                               
                                                     
    punpckhwd mm3, mm2                               
    movq mm2, mm4                                    
                                                     
    punpcklwd mm4, mm6                               
                                                     
    punpckhwd mm2, mm6                               
    movq mm6, mm7                                    
                                                     
    punpcklwd mm7, mm1                               
                                                     
    punpckhwd mm6, mm1                               
    movq [esp+0x10*2], mm2                           
    movq mm2, [esp]                                  
    movq mm1, mm2                                    
                                                     
    punpcklwd mm2, mm5                               
                                                     
    punpckhwd mm1, mm5                               
    movq mm5, mm0                                    
                                                     
    punpckldq mm0, mm4                               
                                                     
    punpckhdq mm5, mm4                               
    movq mm4, mm7                                    
                                                     
    punpckldq mm7, mm2                               
                                                     
    punpckhdq mm4, mm2                               
    movq [esp], mm0                                  
    movq [esp+0x10], mm5                             
    movq [esp+0x30+0x10], mm7                        
    movq [esp+0x30+0x10*2], mm4                      
                                                     
    movq mm0, mm3                                    
    punpckhdq mm0, [esp+0x10*2]                      
                                                     
    punpckldq mm3, [esp+0x10*2]                      
    movq mm5, mm6                                    
                                                     
    punpckldq mm6, mm1                               
                                                     
    punpckhdq mm5, mm1                               
    movq [esp+0x10*2], mm3                           
    movq [esp+0x30], mm0                             
    movq [esp+0x30+0x30], mm6                        
    movq [esp+0x30+0x10*4], mm5                      
    lea eax, [eax+ecx*8]                             
    lea edx, [edx+ecx*8]                             
    movq mm0, [eax]                                  
    movq mm1, [eax+ecx]                              
    movq mm2, [eax+ecx*2]                            
    movq mm3, [edx]                                  
    movq mm4, [edx+ecx]                              
    movq mm5, [edx+ecx*2]                            
    movq mm6, [edx+ebx]                              
    movq mm7, mm0                                    
                                                     
    punpcklbw mm0, mm1                               
                                                     
    punpckhbw mm7, mm1                               
    movq mm1, mm2                                    
                                                     
    punpcklbw mm2, mm3                               
                                                     
    punpckhbw mm1, mm3                               
    movq mm3, mm4                                    
                                                     
    punpcklbw mm4, mm5                               
                                                     
    punpckhbw mm3, mm5                               
                                                     
    movq mm5, mm6                                    
    punpckhbw mm5, [edx+ecx*4]                       
                                                     
    punpcklbw mm6, [edx+ecx*4]                       
    movq [esp+8], mm3                                
    movq mm3, mm0                                    
                                                     
    punpcklwd mm0, mm2                               
                                                     
    punpckhwd mm3, mm2                               
    movq mm2, mm4                                    
                                                     
    punpcklwd mm4, mm6                               
                                                     
    punpckhwd mm2, mm6                               
    movq mm6, mm7                                    
                                                     
    punpcklwd mm7, mm1                               
                                                     
    punpckhwd mm6, mm1                               
    movq [esp+8+0x10*2], mm2                         
    movq mm2, [esp+8]                                
    movq mm1, mm2                                    
                                                     
    punpcklwd mm2, mm5                               
                                                     
    punpckhwd mm1, mm5                               
    movq mm5, mm0                                    
                                                     
    punpckldq mm0, mm4                               
                                                     
    punpckhdq mm5, mm4                               
    movq mm4, mm7                                    
                                                     
    punpckldq mm7, mm2                               
                                                     
    punpckhdq mm4, mm2                               
    movq [esp+8], mm0                                
    movq [esp+8+0x10], mm5                           
    movq [esp+0x38+0x10], mm7                        
    movq [esp+0x38+0x10*2], mm4                      
                                                     
    movq mm0, mm3                                    
    punpckhdq mm0, [esp+8+0x10*2]                    
                                                     
    punpckldq mm3, [esp+8+0x10*2]                    
    movq mm5, mm6                                    
                                                     
    punpckldq mm6, mm1                               
                                                     
    punpckhdq mm5, mm1                               
    movq [esp+8+0x10*2], mm3                         
    movq [esp+0x38], mm0                             
    movq [esp+0x38+0x30], mm6                        
    movq [esp+0x38+0x10*4], mm5                      
                                                     
    lea eax, [esp+0x40]                              
    push dword ptr[ebp+8+16]                      
    push dword ptr[ebp+8+12]                      
    push 16                                    
    push eax                                         
                                                     
    call ff_deblock_v_luma_intra_8_sse2              
    add esp, 16                                      
                                                     
    mov ecx, [ebp+8+8]                         
    mov eax, [ebp+8+4]                   
    lea ebx, [ecx+ecx*2]                                 
    sub eax, 4                                       
    lea edx, [eax+ebx]                               
                                                     
    movq mm0, [esp]                                  
    movq mm1, [esp+0x10]                             
    movq mm2, [esp+0x10*2]                           
    movq mm3, [esp+0x30]                             
    movq mm4, [esp+0x30+0x10]                        
    movq mm5, [esp+0x30+0x10*2]                      
    movq mm6, [esp+0x30+0x30]                        
    movq mm7, mm0                                    
                                                     
    punpcklbw mm0, mm1                               
                                                     
    punpckhbw mm7, mm1                               
    movq mm1, mm2                                    
                                                     
    punpcklbw mm2, mm3                               
                                                     
    punpckhbw mm1, mm3                               
    movq mm3, mm4                                    
                                                     
    punpcklbw mm4, mm5                               
                                                     
    punpckhbw mm3, mm5                               
                                                     
    movq mm5, mm6                                    
    punpckhbw mm5, [esp+0x30+0x10*4]                 
                                                     
    punpcklbw mm6, [esp+0x30+0x10*4]                 
    movq [eax], mm3                                  
    movq mm3, mm0                                    
                                                     
    punpcklwd mm0, mm2                               
                                                     
    punpckhwd mm3, mm2                               
    movq mm2, mm4                                    
                                                     
    punpcklwd mm4, mm6                               
                                                     
    punpckhwd mm2, mm6                               
    movq mm6, mm7                                    
                                                     
    punpcklwd mm7, mm1                               
                                                     
    punpckhwd mm6, mm1                               
    movq [eax+ecx*2], mm2                            
    movq mm2, [eax]                                  
    movq mm1, mm2                                    
                                                     
    punpcklwd mm2, mm5                               
                                                     
    punpckhwd mm1, mm5                               
    movq mm5, mm0                                    
                                                     
    punpckldq mm0, mm4                               
                                                     
    punpckhdq mm5, mm4                               
    movq mm4, mm7                                    
                                                     
    punpckldq mm7, mm2                               
                                                     
    punpckhdq mm4, mm2                               
    movq [eax], mm0                                  
    movq [eax+ecx], mm5                              
    movq [edx+ecx], mm7                              
    movq [edx+ecx*2], mm4                            
                                                     
    movq mm0, mm3                                    
    punpckhdq mm0, [eax+ecx*2]                       
                                                     
    punpckldq mm3, [eax+ecx*2]                       
    movq mm5, mm6                                    
                                                     
    punpckldq mm6, mm1                               
                                                     
    punpckhdq mm5, mm1                               
    movq [eax+ecx*2], mm3                            
    movq [edx], mm0                                  
    movq [edx+ebx], mm6                              
    movq [edx+ecx*4], mm5                            
    lea eax, [eax+ecx*8]                             
    lea edx, [edx+ecx*8]                             
    movq mm0, [esp+8]                                
    movq mm1, [esp+8+0x10]                           
    movq mm2, [esp+8+0x10*2]                         
    movq mm3, [esp+0x38]                             
    movq mm4, [esp+0x38+0x10]                        
    movq mm5, [esp+0x38+0x10*2]                      
    movq mm6, [esp+0x38+0x30]                        
    movq mm7, mm0                                    
                                                     
    punpcklbw mm0, mm1                               
                                                     
    punpckhbw mm7, mm1                               
    movq mm1, mm2                                    
                                                     
    punpcklbw mm2, mm3                               
                                                     
    punpckhbw mm1, mm3                               
    movq mm3, mm4                                    
                                                     
    punpcklbw mm4, mm5                               
                                                     
    punpckhbw mm3, mm5                               
                                                     
    movq mm5, mm6                                    
    punpckhbw mm5, [esp+0x38+0x10*4]                 
                                                     
    punpcklbw mm6, [esp+0x38+0x10*4]                 
    movq [eax], mm3                                  
    movq mm3, mm0                                    
                                                     
    punpcklwd mm0, mm2                               
                                                     
    punpckhwd mm3, mm2                               
    movq mm2, mm4                                    
                                                     
    punpcklwd mm4, mm6                               
                                                     
    punpckhwd mm2, mm6                               
    movq mm6, mm7                                    
                                                     
    punpcklwd mm7, mm1                               
                                                     
    punpckhwd mm6, mm1                               
    movq [eax+ecx*2], mm2                            
    movq mm2, [eax]                                  
    movq mm1, mm2                                    
                                                     
    punpcklwd mm2, mm5                               
                                                     
    punpckhwd mm1, mm5                               
    movq mm5, mm0                                    
                                                     
    punpckldq mm0, mm4                               
                                                     
    punpckhdq mm5, mm4                               
    movq mm4, mm7                                    
                                                     
    punpckldq mm7, mm2                               
                                                     
    punpckhdq mm4, mm2                               
    movq [eax], mm0                                  
    movq [eax+ecx], mm5                              
    movq [edx+ecx], mm7                              
    movq [edx+ecx*2], mm4                            
                                                     
    movq mm0, mm3                                    
    punpckhdq mm0, [eax+ecx*2]                       
                                                     
    punpckldq mm3, [eax+ecx*2]                       
    movq mm5, mm6                                    
                                                     
    punpckldq mm6, mm1                               
                                                     
    punpckhdq mm5, mm1                               
    movq [eax+ecx*2], mm3                            
    movq [edx], mm0                                  
    movq [edx+ebx], mm6                              
    movq [edx+ecx*4], mm5                            
    
	mov esp,ebp
    pop ebx
	pop ebp
    ret
	 }
}
void __declspec(naked) ff_deblock_v_chroma_intra_10_mmxext(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
   push ebx                               
   push esi                               
   push edi                               
   mov eax, [esp + 12 + 4 + 0*4]          
   mov ecx, [esp + 12 + 4 + 1*4]          
   mov edx, [esp + 12 + 4 + 2*4]          
   mov ebx, [esp + 12 + 4 + 3*4]          
                                          
   mov esi, eax                           
   sub eax, ecx                           
   sub eax, ecx                           
   shl edx, 2                             
   shl ebx, 2                             
   mov edi, 16/8                          
ff_deblock_v_chroma_intra_10_mmxextloop:                                  
   movq mm0, [eax]                        
   movq mm1, [eax+ecx]                    
   movq mm2, [esi]                        
   movq mm3, [esi+ecx]                    
   movd mm4, edx                          
   movd mm5, ebx                          
   pshufw mm4, mm4, (0)*0x55              
   pshufw mm5, mm5, (0)*0x55              
                                          
   movq mm7, mm2                          
   psubusw mm7, mm1                       
                                          
   movq mm6, mm1                          
   psubusw mm6, mm2                       
                                          
   por mm6, mm7                           
                                          
   psubw mm6, mm4                         
                                          
   movq mm7, mm1                          
   psubusw mm7, mm0                       
                                          
   movq mm4, mm0                          
   psubusw mm4, mm1                       
                                          
   por mm4, mm7                           
                                          
   psubw mm4, mm5                         
                                          
   pand mm6, mm4                          
                                          
   movq mm7, mm3                          
   psubusw mm7, mm2                       
                                          
   movq mm4, mm2                          
   psubusw mm4, mm3                       
                                          
   por mm4, mm7                           
                                          
   psubw mm4, mm5                         
                                          
   pxor mm7, mm7                          
                                          
   pand mm6, mm4                          
                                          
   pcmpgtw mm7, mm6                       
   movq mm5, [ff_pw_2]                    
                                          
   paddw mm5, mm0                         
                                          
   paddw mm5, mm3                         
                                          
   movq mm6, mm5                          
   paddw mm6, mm2                         
                                          
   paddw mm5, mm1                         
                                          
   paddw mm5, mm0                         
                                          
   paddw mm6, mm3                         
                                          
   psraw mm5, 2                           
                                          
   psraw mm6, 2                           
                                          
   psubw mm5, mm1                         
                                          
   psubw mm6, mm2                         
                                          
   pand mm5, mm7                          
                                          
   pand mm6, mm7                          
                                          
   paddw mm1, mm5                         
                                          
   paddw mm2, mm6                         
   movq [eax+1*ecx], mm1                  
   movq [eax+2*ecx], mm2                  
   add eax, 8                             
   add esi, 8                             
   dec edi                                
   jg  ff_deblock_v_chroma_intra_10_mmxextloop
   pop edi                                
   pop esi                                
   pop ebx                                
   ret                                    

	 }
}

void __declspec(naked) ff_deblock_v_luma_intra_10_mmxext(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
  push ebx                                            
  push esi                                            
  push edi                                            
  push ebp                                            
  mov eax, [esp + 16 + 4 + 0*4]                       
  mov ecx, [esp + 16 + 4 + 1*4]                       
  mov edx, [esp + 16 + 4 + 2*4]                       
  mov ebx, [esp + 16 + 4 + 3*4]                       
                                                      
  sub esp, 3*8+((4*3) % 8)-(16&15)                    
  lea esi, [ecx*4]                                    
  lea edi, [ecx+ecx*2]                                    
  neg esi                                             
  add esi, eax                                        
  mov ebp, 32/8                                       
  shl edx, 2                                          
  shl ebx, 2                                          
ff_deblock_v_luma_intra_10_mmxextloop:                                               
  movq mm0, [esi+ecx*2]                               
  movq mm1, [esi+edi]                                 
  movq mm2, [eax]                                     
  movq mm3, [eax+ecx]                                 
  movd mm4, edx                                       
  movd mm5, ebx                                       
  pshufw mm4, mm4, (0)*0x55                           
  pshufw mm5, mm5, (0)*0x55                           
  movq [esp+8*(4-4)], mm4                             
                                                      
  movq mm4, mm2                                       
  psubusw mm4, mm1                                    
                                                      
  movq mm6, mm1                                       
  psubusw mm6, mm2                                    
                                                      
  por mm6, mm4                                        
                                                      
  psubw mm6, [esp+8*(4-4)]                            
                                                      
  movq mm4, mm1                                       
  psubusw mm4, mm0                                    
                                                      
  movq mm7, mm0                                       
  psubusw mm7, mm1                                    
                                                      
  por mm7, mm4                                        
                                                      
  psubw mm7, mm5                                      
                                                      
  pand mm6, mm7                                       
                                                      
  movq mm4, mm3                                       
  psubusw mm4, mm2                                    
                                                      
  movq mm7, mm2                                       
  psubusw mm7, mm3                                    
                                                      
  por mm7, mm4                                        
                                                      
  psubw mm7, mm5                                      
                                                      
  pxor mm4, mm4                                       
                                                      
  pand mm6, mm7                                       
                                                      
  pcmpgtw mm4, mm6                                    
  movq mm7, [esp+8*(4-4)]                             
  movq [esp+8*(5-4)], mm4                             
                                                      
  psrlw mm7, 2                                        
                                                      
  paddw mm7, [ff_pw_2]                                
                                                      
  movq mm6, mm2                                       
  psubusw mm6, mm1                                    
                                                      
  movq mm4, mm1                                       
  psubusw mm4, mm2                                    
                                                      
  por mm4, mm6                                        
                                                      
  pxor mm6, mm6                                       
                                                      
  psubw mm4, mm7                                      
                                                      
  pcmpgtw mm6, mm4                                    
                                                      
  pand mm6, [esp+8*(5-4)]                             
  movq mm7, [eax+ecx*2]                               
  movq [esp+8*(4-4)], mm6                             
                                                      
  movq mm6, mm2                                       
  psubusw mm6, mm7                                    
                                                      
  movq mm4, mm7                                       
  psubusw mm4, mm2                                    
                                                      
  por mm4, mm6                                        
                                                      
  pxor mm6, mm6                                       
                                                      
  psubw mm4, mm5                                      
                                                      
  pcmpgtw mm6, mm4                                    
                                                      
  pand mm6, [esp+8*(4-4)]                             
  movq mm7, [esi+ecx]                                 
  movq [esp+8*(6-4)], mm6                             
                                                      
  movq mm6, mm1                                       
  psubusw mm6, mm7                                    
                                                      
  movq mm4, mm7                                       
  psubusw mm4, mm1                                    
                                                      
  por mm4, mm6                                        
                                                      
  pxor mm6, mm6                                       
                                                      
  psubw mm4, mm5                                      
                                                      
  pcmpgtw mm6, mm4                                    
                                                      
  pand mm6, [esp+8*(4-4)]                             
  movq [esp+8*(4-4)], mm6                             
  movq mm4, mm7                                       
  movq mm6, [esi]                                     
                                                      
  paddw mm4, mm0                                      
                                                      
  paddw mm6, mm7                                      
                                                      
  paddw mm4, mm1                                      
                                                      
  paddw mm6, mm6                                      
                                                      
  paddw mm4, mm2                                      
                                                      
  paddw mm6, [ff_pw_2]                                
                                                      
  paddw mm4, [ff_pw_2]                                
                                                      
  paddw mm6, mm4                                      
                                                      
                                                      
  psrlw mm6, 3                                        
                                                      
  movq mm5, mm4                                       
  psrlw mm5, 2                                        
                                                      
  psubw mm6, mm7                                      
                                                      
  psubw mm5, mm0                                      
                                                      
  pand mm6, [esp+8*(4-4)]                             
                                                      
  pand mm5, [esp+8*(4-4)]                             
                                                      
  paddw mm6, mm7                                      
                                                      
  paddw mm5, mm0                                      
  movq [esi+2*ecx], mm5                               
                                                      
                                                      
  movq mm5, mm4                                       
  psubw mm5, mm7                                      
                                                      
  paddw mm4, mm4                                      
                                                      
  psubw mm5, mm2                                      
                                                      
  psubw mm4, mm7                                      
                                                      
  paddw mm5, mm3                                      
                                                      
  paddw mm5, mm0                                      
                                                      
  paddw mm4, mm3                                      
                                                      
  psrlw mm5, 2                                        
                                                      
  psrlw mm4, 3                                        
                                                      
                                                      
  pxor mm4, mm5                                       
                                                      
  pxor mm5, mm1                                       
                                                      
  pand mm4, [esp+8*(4-4)]                             
                                                      
  pand mm5, [esp+8*(5-4)]                             
                                                      
  pxor mm4, mm5                                       
                                                      
  pxor mm4, mm1                                       
  movq [esi+edi], mm4                                 
  movq [esi+ecx], mm6                                 
  movq mm7, [eax+ecx*2]                               
  movq mm4, mm7                                       
  movq mm6, [eax+edi]                                 
                                                      
  paddw mm4, mm3                                      
                                                      
  paddw mm6, mm7                                      
                                                      
  paddw mm4, mm2                                      
                                                      
  paddw mm6, mm6                                      
                                                      
  paddw mm4, mm1                                      
                                                      
  paddw mm6, [ff_pw_2]                                
                                                      
  paddw mm4, [ff_pw_2]                                
                                                      
  paddw mm6, mm4                                      
                                                      
                                                      
  psrlw mm6, 3                                        
                                                      
  movq mm5, mm4                                       
  psrlw mm5, 2                                        
                                                      
  psubw mm6, mm7                                      
                                                      
  psubw mm5, mm3                                      
                                                      
  pand mm6, [esp+8*(6-4)]                             
                                                      
  pand mm5, [esp+8*(6-4)]                             
                                                      
  paddw mm6, mm7                                      
                                                      
  paddw mm5, mm3                                      
  movq [eax+ecx], mm5                                 
                                                      
                                                      
  movq mm5, mm4                                       
  psubw mm5, mm7                                      
                                                      
  paddw mm4, mm4                                      
                                                      
  psubw mm5, mm1                                      
                                                      
  psubw mm4, mm7                                      
                                                      
  paddw mm5, mm0                                      
                                                      
  paddw mm5, mm3                                      
                                                      
  paddw mm4, mm0                                      
                                                      
  psrlw mm5, 2                                        
                                                      
  psrlw mm4, 3                                        
                                                      
                                                      
  pxor mm4, mm5                                       
                                                      
  pxor mm5, mm2                                       
                                                      
  pand mm4, [esp+8*(6-4)]                             
                                                      
  pand mm5, [esp+8*(5-4)]                             
                                                      
  pxor mm4, mm5                                       
                                                      
  pxor mm4, mm2                                       
  movq [eax], mm4                                     
  movq [eax+2*ecx], mm6                               
  add eax, 8                                          
  add esi, 8                                          
  dec ebp                                             
  jg  ff_deblock_v_luma_intra_10_mmxextloop
  add esp, 3*8+((4*3) % 8)-(16&15)                    
  pop ebp                                             
  pop edi                                             
  pop esi                                             
  pop ebx                                             
  ret                                                 

	 }
}
void __declspec(naked) ff_deblock_h_luma_intra_10_mmxext(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
   push ebx                                           
   push esi                                           
   push edi                                           
   push ebp                                           
   mov eax, [esp + 16 + 4 + 0*4]                      
   mov ecx, [esp + 16 + 4 + 1*4]                      
   mov edx, [esp + 16 + 4 + 2*4]                      
   mov ebx, [esp + 16 + 4 + 3*4]                      
                                                      
   sub esp, 8*8+((4*3) % 8)-(16&15)                   
   lea esi, [ecx+ecx*2]                                   
   mov edi, 32/8                                      
   shl edx, 2                                         
   shl ebx, 2                                         
ff_deblock_h_luma_intra_10_mmxextloop:                                              
   movq mm4, [eax-8]                                  
   movq mm5, [eax+ecx-8]                              
   movq mm0, [eax+ecx*2-8]                            
   movq mm1, [eax+esi-8]                              
   movq mm2, mm4                                      
                                                      
   punpcklwd mm4, mm5                                 
                                                      
   punpckhwd mm2, mm5                                 
   movq mm5, mm0                                      
                                                      
   punpcklwd mm0, mm1                                 
                                                      
   punpckhwd mm5, mm1                                 
   movq mm1, mm4                                      
                                                      
   punpckldq mm4, mm0                                 
                                                      
   punpckhdq mm1, mm0                                 
   movq mm0, mm2                                      
                                                      
   punpckldq mm2, mm5                                 
                                                      
   punpckhdq mm0, mm5                                 
   movq [esp+8*(4-4)], mm4                            
   movq [esp+8*(5-4)], mm1                            
                                                      
   movq mm5, [eax]                                    
   movq mm3, [eax+ecx]                                
   movq mm4, [eax+ecx*2]                              
   movq mm1, [eax+esi]                                
   movq mm6, mm5                                      
                                                      
   punpcklwd mm5, mm3                                 
                                                      
   punpckhwd mm6, mm3                                 
   movq mm3, mm4                                      
                                                      
   punpcklwd mm4, mm1                                 
                                                      
   punpckhwd mm3, mm1                                 
   movq mm1, mm5                                      
                                                      
   punpckldq mm5, mm4                                 
                                                      
   punpckhdq mm1, mm4                                 
   movq mm4, mm6                                      
                                                      
   punpckldq mm6, mm3                                 
                                                      
   punpckhdq mm4, mm3                                 
   movq [esp+8*(6-4)], mm6                            
   movq [esp+8*(7-4)], mm4                            
   movd mm6, edx                                      
   movd mm4, ebx                                      
   pshufw mm6, mm6, (0)*0x55                          
   pshufw mm4, mm4, (0)*0x55                          
   movq [esp+8*(8-4)], mm6                            
                                                      
   movq mm6, mm5                                      
   psubusw mm6, mm0                                   
                                                      
   movq mm3, mm0                                      
   psubusw mm3, mm5                                   
                                                      
   por mm3, mm6                                       
                                                      
   psubw mm3, [esp+8*(8-4)]                           
                                                      
   movq mm6, mm0                                      
   psubusw mm6, mm2                                   
                                                      
   movq mm7, mm2                                      
   psubusw mm7, mm0                                   
                                                      
   por mm7, mm6                                       
                                                      
   psubw mm7, mm4                                     
                                                      
   pand mm3, mm7                                      
                                                      
   movq mm6, mm1                                      
   psubusw mm6, mm5                                   
                                                      
   movq mm7, mm5                                      
   psubusw mm7, mm1                                   
                                                      
   por mm7, mm6                                       
                                                      
   psubw mm7, mm4                                     
                                                      
   pxor mm6, mm6                                      
                                                      
   pand mm3, mm7                                      
                                                      
   pcmpgtw mm6, mm3                                   
   movq mm7, [esp+8*(8-4)]                            
   movq [esp+8*(9-4)], mm6                            
                                                      
   psrlw mm7, 2                                       
                                                      
   paddw mm7, [ff_pw_2]                               
                                                      
   movq mm3, mm5                                      
   psubusw mm3, mm0                                   
                                                      
   movq mm6, mm0                                      
   psubusw mm6, mm5                                   
                                                      
   por mm6, mm3                                       
                                                      
   pxor mm3, mm3                                      
                                                      
   psubw mm6, mm7                                     
                                                      
   pcmpgtw mm3, mm6                                   
                                                      
   pand mm3, [esp+8*(9-4)]                            
   movq mm7, [esp+8*(6-4)]                            
   movq [esp+8*(8-4)], mm3                            
                                                      
   movq mm3, mm5                                      
   psubusw mm3, mm7                                   
                                                      
   movq mm6, mm7                                      
   psubusw mm6, mm5                                   
                                                      
   por mm6, mm3                                       
                                                      
   pxor mm3, mm3                                      
                                                      
   psubw mm6, mm4                                     
                                                      
   pcmpgtw mm3, mm6                                   
                                                      
   pand mm3, [esp+8*(8-4)]                            
   movq mm7, [esp+8*(5-4)]                            
   movq [esp+8*(10-4)], mm3                           
                                                      
   movq mm3, mm0                                      
   psubusw mm3, mm7                                   
                                                      
   movq mm6, mm7                                      
   psubusw mm6, mm0                                   
                                                      
   por mm6, mm3                                       
                                                      
   pxor mm3, mm3                                      
                                                      
   psubw mm6, mm4                                     
                                                      
   pcmpgtw mm3, mm6                                   
                                                      
   pand mm3, [esp+8*(8-4)]                            
   movq [esp+8*(8-4)], mm3                            
                                                      
   movq mm6, mm7                                      
   movq mm3, [esp+8*(4-4)]                            
                                                      
   paddw mm6, mm2                                     
                                                      
   paddw mm3, mm7                                     
                                                      
   paddw mm6, mm0                                     
                                                      
   paddw mm3, mm3                                     
                                                      
   paddw mm6, mm5                                     
                                                      
   paddw mm3, [ff_pw_2]                               
                                                      
   paddw mm6, [ff_pw_2]                               
                                                      
   paddw mm3, mm6                                     
                                                      
                                                      
   psrlw mm3, 3                                       
                                                      
   movq mm4, mm6                                      
   psrlw mm4, 2                                       
                                                      
   psubw mm3, mm7                                     
                                                      
   psubw mm4, mm2                                     
                                                      
   pand mm3, [esp+8*(8-4)]                            
                                                      
   pand mm4, [esp+8*(8-4)]                            
                                                      
   paddw mm3, mm7                                     
                                                      
   paddw mm4, mm2                                     
   movq [esp+8*(5-4)], mm4                            
                                                      
                                                      
   movq mm4, mm6                                      
   psubw mm4, mm7                                     
                                                      
   paddw mm6, mm6                                     
                                                      
   psubw mm4, mm5                                     
                                                      
   psubw mm6, mm7                                     
                                                      
   paddw mm4, mm1                                     
                                                      
   paddw mm4, mm2                                     
                                                      
   paddw mm6, mm1                                     
                                                      
   psrlw mm4, 2                                       
                                                      
   psrlw mm6, 3                                       
                                                      
                                                      
   pxor mm6, mm4                                      
                                                      
   pxor mm4, mm0                                      
                                                      
   pand mm6, [esp+8*(8-4)]                            
                                                      
   pand mm4, [esp+8*(9-4)]                            
                                                      
   pxor mm6, mm4                                      
                                                      
   pxor mm6, mm0                                      
   movq [esp+8*(8-4)], mm6                            
   movq [esp+8*(11-4)], mm3                           
   movq mm7, [esp+8*(6-4)]                            
   movq mm6, mm7                                      
   movq mm3, [esp+8*(7-4)]                            
                                                      
   paddw mm6, mm1                                     
                                                      
   paddw mm3, mm7                                     
                                                      
   paddw mm6, mm5                                     
                                                      
   paddw mm3, mm3                                     
                                                      
   paddw mm6, mm0                                     
                                                      
   paddw mm3, [ff_pw_2]                               
                                                      
   paddw mm6, [ff_pw_2]                               
                                                      
   paddw mm3, mm6                                     
                                                      
                                                      
   psrlw mm3, 3                                       
                                                      
   movq mm4, mm6                                      
   psrlw mm4, 2                                       
                                                      
   psubw mm3, mm7                                     
                                                      
   psubw mm4, mm1                                     
                                                      
   pand mm3, [esp+8*(10-4)]                           
                                                      
   pand mm4, [esp+8*(10-4)]                           
                                                      
   paddw mm3, mm7                                     
                                                      
   paddw mm4, mm1                                     
   movq [esp+8*(6-4)], mm4                            
                                                      
                                                      
   movq mm4, mm6                                      
   psubw mm4, mm7                                     
                                                      
   paddw mm6, mm6                                     
                                                      
   psubw mm4, mm0                                     
                                                      
   psubw mm6, mm7                                     
                                                      
   paddw mm4, mm2                                     
                                                      
   paddw mm4, mm1                                     
                                                      
   paddw mm6, mm2                                     
                                                      
   psrlw mm4, 2                                       
                                                      
   psrlw mm6, 3                                       
                                                      
                                                      
   pxor mm6, mm4                                      
                                                      
   pxor mm4, mm5                                      
                                                      
   pand mm6, [esp+8*(10-4)]                           
                                                      
   pand mm4, [esp+8*(9-4)]                            
                                                      
   pxor mm6, mm4                                      
                                                      
   pxor mm6, mm5                                      
                                                      
                                                      
                                                      
   movq mm5, [esp+8*(4-4)]                            
   movq mm2, [esp+8*(11-4)]                           
   movq mm0, [esp+8*(5-4)]                            
   movq mm1, [esp+8*(8-4)]                            
   movq mm4, [esp+8*(6-4)]                            
                                                      
   movq mm7, mm5                                      
                                                      
   punpcklwd mm5, mm2                                 
                                                      
   punpckhwd mm7, mm2                                 
   movq mm2, mm0                                      
                                                      
   punpcklwd mm0, mm1                                 
                                                      
   punpckhwd mm2, mm1                                 
   movq mm1, mm5                                      
                                                      
   punpckldq mm5, mm0                                 
                                                      
   punpckhdq mm1, mm0                                 
   movq mm0, mm7                                      
                                                      
   punpckldq mm7, mm2                                 
                                                      
   punpckhdq mm0, mm2                                 
   movq [eax-8], mm5                                  
   movq [eax+ecx-8], mm1                              
   movq [eax+ecx*2-8], mm7                            
   movq [eax+esi-8], mm0                              
   movq mm5, [esp+8*(7-4)]                            
   movq mm2, mm6                                      
                                                      
   punpcklwd mm6, mm4                                 
                                                      
   punpckhwd mm2, mm4                                 
   movq mm4, mm3                                      
                                                      
   punpcklwd mm3, mm5                                 
                                                      
   punpckhwd mm4, mm5                                 
   movq mm5, mm6                                      
                                                      
   punpckldq mm6, mm3                                 
                                                      
   punpckhdq mm5, mm3                                 
   movq mm3, mm2                                      
                                                      
   punpckldq mm2, mm4                                 
                                                      
   punpckhdq mm3, mm4                                 
   movq [eax], mm6                                    
   movq [eax+ecx], mm5                                
   movq [eax+ecx*2], mm2                              
   movq [eax+esi], mm3                                
                                                      
   lea eax, [eax+ecx*(8/2)]                           
   dec edi                                            
   jg  ff_deblock_h_luma_intra_10_mmxextloop
   add esp, 8*8+((4*3) % 8)-(16&15)                   
   pop ebp                                            
   pop edi                                            
   pop esi                                            
   pop ebx                                            
   ret                                                

	 }
}
void __declspec(naked) ff_deblock_v_chroma_intra_10_sse2(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
  push ebx                                       
  push esi                                       
  mov eax, [esp + 8 + 4 + 0*4]                   
  mov ecx, [esp + 8 + 4 + 1*4]                   
  mov edx, [esp + 8 + 4 + 2*4]                   
  mov ebx, [esp + 8 + 4 + 3*4]                   
                                                 
  mov esi, eax                                   
  sub eax, ecx                                   
  sub eax, ecx                                   
  shl edx, 2                                     
  shl ebx, 2                                     
  movdqa xmm0, [eax]                             
  movdqa xmm1, [eax+ecx]                         
  movdqa xmm2, [esi]                             
  movdqa xmm3, [esi+ecx]                         
  movd xmm4, edx                                 
  movd xmm5, ebx                                 
  pshuflw xmm4, xmm4, (0)*0x55                   
                                                 
  punpcklqdq xmm4, xmm4                          
  pshuflw xmm5, xmm5, (0)*0x55                   
                                                 
  punpcklqdq xmm5, xmm5                          
                                                 
  movdqa xmm7, xmm2                              
  psubusw xmm7, xmm1                             
                                                 
  movdqa xmm6, xmm1                              
  psubusw xmm6, xmm2                             
                                                 
  por xmm6, xmm7                                 
                                                 
  psubw xmm6, xmm4                               
                                                 
  movdqa xmm7, xmm1                              
  psubusw xmm7, xmm0                             
                                                 
  movdqa xmm4, xmm0                              
  psubusw xmm4, xmm1                             
                                                 
  por xmm4, xmm7                                 
                                                 
  psubw xmm4, xmm5                               
                                                 
  pand xmm6, xmm4                                
                                                 
  movdqa xmm7, xmm3                              
  psubusw xmm7, xmm2                             
                                                 
  movdqa xmm4, xmm2                              
  psubusw xmm4, xmm3                             
                                                 
  por xmm4, xmm7                                 
                                                 
  psubw xmm4, xmm5                               
                                                 
  pxor xmm7, xmm7                                
                                                 
  pand xmm6, xmm4                                
                                                 
  pcmpgtw xmm7, xmm6                             
  movdqa xmm5, [ff_pw_2]                         
                                                 
  paddw xmm5, xmm0                               
                                                 
  paddw xmm5, xmm3                               
                                                 
  movdqa xmm6, xmm5                              
  paddw xmm6, xmm2                               
                                                 
  paddw xmm5, xmm1                               
                                                 
  paddw xmm5, xmm0                               
                                                 
  paddw xmm6, xmm3                               
                                                 
  psraw xmm5, 2                                  
                                                 
  psraw xmm6, 2                                  
                                                 
  psubw xmm5, xmm1                               
                                                 
  psubw xmm6, xmm2                               
                                                 
  pand xmm5, xmm7                                
                                                 
  pand xmm6, xmm7                                
                                                 
  paddw xmm1, xmm5                               
                                                 
  paddw xmm2, xmm6                               
  movdqa [eax+1*ecx], xmm1                       
  movdqa [eax+2*ecx], xmm2                       
  pop esi                                        
  pop ebx                                        
  ret
	 }
}
void __declspec(naked) ff_deblock_v_luma_intra_10_sse2(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
   push ebx                                    
   push esi                                    
   push edi                                    
   push ebp                                    
   mov eax, [esp + 16 + 4 + 0*4]               
   mov ecx, [esp + 16 + 4 + 1*4]               
   mov edx, [esp + 16 + 4 + 2*4]               
   mov ebx, [esp + 16 + 4 + 3*4]               
                                               
   sub esp, 3*16+((4*3) % 16)-(16&15)          
   lea esi, [ecx*4]                            
   lea edi, [ecx+ecx*2]                            
   neg esi                                     
   add esi, eax                                
   mov ebp, 32/16                              
   shl edx, 2                                  
   shl ebx, 2                                  
ff_deblock_v_luma_intra_10_sse2loop:                                       
   movdqa xmm0, [esi+ecx*2]                    
   movdqa xmm1, [esi+edi]                      
   movdqa xmm2, [eax]                          
   movdqa xmm3, [eax+ecx]                      
   movd xmm4, edx                              
   movd xmm5, ebx                              
   pshuflw xmm4, xmm4, (0)*0x55                
                                               
   punpcklqdq xmm4, xmm4                       
   pshuflw xmm5, xmm5, (0)*0x55                
                                               
   punpcklqdq xmm5, xmm5                       
   movdqa [esp+16*(4-4)], xmm4                 
                                               
   movdqa xmm4, xmm2                           
   psubusw xmm4, xmm1                          
                                               
   movdqa xmm6, xmm1                           
   psubusw xmm6, xmm2                          
                                               
   por xmm6, xmm4                              
                                               
   psubw xmm6, [esp+16*(4-4)]                  
                                               
   movdqa xmm4, xmm1                           
   psubusw xmm4, xmm0                          
                                               
   movdqa xmm7, xmm0                           
   psubusw xmm7, xmm1                          
                                               
   por xmm7, xmm4                              
                                               
   psubw xmm7, xmm5                            
                                               
   pand xmm6, xmm7                             
                                               
   movdqa xmm4, xmm3                           
   psubusw xmm4, xmm2                          
                                               
   movdqa xmm7, xmm2                           
   psubusw xmm7, xmm3                          
                                               
   por xmm7, xmm4                              
                                               
   psubw xmm7, xmm5                            
                                               
   pxor xmm4, xmm4                             
                                               
   pand xmm6, xmm7                             
                                               
   pcmpgtw xmm4, xmm6                          
   movdqa xmm7, [esp+16*(4-4)]                 
   movdqa [esp+16*(5-4)], xmm4                 
                                               
   psrlw xmm7, 2                               
                                               
   paddw xmm7, [ff_pw_2]                       
                                               
   movdqa xmm6, xmm2                           
   psubusw xmm6, xmm1                          
                                               
   movdqa xmm4, xmm1                           
   psubusw xmm4, xmm2                          
                                               
   por xmm4, xmm6                              
                                               
   pxor xmm6, xmm6                             
                                               
   psubw xmm4, xmm7                            
                                               
   pcmpgtw xmm6, xmm4                          
                                               
   pand xmm6, [esp+16*(5-4)]                   
   movdqa xmm7, [eax+ecx*2]                    
   movdqa [esp+16*(4-4)], xmm6                 
                                               
   movdqa xmm6, xmm2                           
   psubusw xmm6, xmm7                          
                                               
   movdqa xmm4, xmm7                           
   psubusw xmm4, xmm2                          
                                               
   por xmm4, xmm6                              
                                               
   pxor xmm6, xmm6                             
                                               
   psubw xmm4, xmm5                            
                                               
   pcmpgtw xmm6, xmm4                          
                                               
   pand xmm6, [esp+16*(4-4)]                   
   movdqa xmm7, [esi+ecx]                      
   movdqa [esp+16*(6-4)], xmm6                 
                                               
   movdqa xmm6, xmm1                           
   psubusw xmm6, xmm7                          
                                               
   movdqa xmm4, xmm7                           
   psubusw xmm4, xmm1                          
                                               
   por xmm4, xmm6                              
                                               
   pxor xmm6, xmm6                             
                                               
   psubw xmm4, xmm5                            
                                               
   pcmpgtw xmm6, xmm4                          
                                               
   pand xmm6, [esp+16*(4-4)]                   
   movdqa [esp+16*(4-4)], xmm6                 
   movdqa xmm4, xmm7                           
   movdqa xmm6, [esi]                          
                                               
   paddw xmm4, xmm0                            
                                               
   paddw xmm6, xmm7                            
                                               
   paddw xmm4, xmm1                            
                                               
   paddw xmm6, xmm6                            
                                               
   paddw xmm4, xmm2                            
                                               
   paddw xmm6, [ff_pw_2]                       
                                               
   paddw xmm4, [ff_pw_2]                       
                                               
   paddw xmm6, xmm4                            
                                               
                                               
   psrlw xmm6, 3                               
                                               
   movdqa xmm5, xmm4                           
   psrlw xmm5, 2                               
                                               
   psubw xmm6, xmm7                            
                                               
   psubw xmm5, xmm0                            
                                               
   pand xmm6, [esp+16*(4-4)]                   
                                               
   pand xmm5, [esp+16*(4-4)]                   
                                               
   paddw xmm6, xmm7                            
                                               
   paddw xmm5, xmm0                            
   movdqa [esi+2*ecx], xmm5                    
                                               
                                               
   movdqa xmm5, xmm4                           
   psubw xmm5, xmm7                            
                                               
   paddw xmm4, xmm4                            
                                               
   psubw xmm5, xmm2                            
                                               
   psubw xmm4, xmm7                            
                                               
   paddw xmm5, xmm3                            
                                               
   paddw xmm5, xmm0                            
                                               
   paddw xmm4, xmm3                            
                                               
   psrlw xmm5, 2                               
                                               
   psrlw xmm4, 3                               
                                               
                                               
   pxor xmm4, xmm5                             
                                               
   pxor xmm5, xmm1                             
                                               
   pand xmm4, [esp+16*(4-4)]                   
                                               
   pand xmm5, [esp+16*(5-4)]                   
                                               
   pxor xmm4, xmm5                             
                                               
   pxor xmm4, xmm1                             
   movdqa [esi+edi], xmm4                      
   movdqa [esi+ecx], xmm6                      
   movdqa xmm7, [eax+ecx*2]                    
   movdqa xmm4, xmm7                           
   movdqa xmm6, [eax+edi]                      
                                               
   paddw xmm4, xmm3                            
                                               
   paddw xmm6, xmm7                            
                                               
   paddw xmm4, xmm2                            
                                               
   paddw xmm6, xmm6                            
                                               
   paddw xmm4, xmm1                            
                                               
   paddw xmm6, [ff_pw_2]                       
                                               
   paddw xmm4, [ff_pw_2]                       
                                               
   paddw xmm6, xmm4                            
                                               
                                               
   psrlw xmm6, 3                               
                                               
   movdqa xmm5, xmm4                           
   psrlw xmm5, 2                               
                                               
   psubw xmm6, xmm7                            
                                               
   psubw xmm5, xmm3                            
                                               
   pand xmm6, [esp+16*(6-4)]                   
                                               
   pand xmm5, [esp+16*(6-4)]                   
                                               
   paddw xmm6, xmm7                            
                                               
   paddw xmm5, xmm3                            
   movdqa [eax+ecx], xmm5                      
                                               
                                               
   movdqa xmm5, xmm4                           
   psubw xmm5, xmm7                            
                                               
   paddw xmm4, xmm4                            
                                               
   psubw xmm5, xmm1                            
                                               
   psubw xmm4, xmm7                            
                                               
   paddw xmm5, xmm0                            
                                               
   paddw xmm5, xmm3                            
                                               
   paddw xmm4, xmm0                            
                                               
   psrlw xmm5, 2                               
                                               
   psrlw xmm4, 3                               
                                               
                                               
   pxor xmm4, xmm5                             
                                               
   pxor xmm5, xmm2                             
                                               
   pand xmm4, [esp+16*(6-4)]                   
                                               
   pand xmm5, [esp+16*(5-4)]                   
                                               
   pxor xmm4, xmm5                             
                                               
   pxor xmm4, xmm2                             
   movdqa [eax], xmm4                          
   movdqa [eax+2*ecx], xmm6                    
   add eax, 16                                 
   add esi, 16                                 
   dec ebp                                     
   jg  ff_deblock_v_luma_intra_10_sse2loop
   add esp, 3*16+((4*3) % 16)-(16&15)          
   pop ebp                                     
   pop edi                                     
   pop esi                                     
   pop ebx                                     
   ret
	 }
}
void __declspec(naked) ff_deblock_h_luma_intra_10_sse2(uint8_t *pix, int stride,int alpha, int beta)
{
	__asm{
   push ebx                                       
   push esi                                       
   push edi                                       
   push ebp                                       
   mov eax, [esp + 16 + 4 + 0*4]                  
   mov ecx, [esp + 16 + 4 + 1*4]                  
   mov edx, [esp + 16 + 4 + 2*4]                  
   mov ebx, [esp + 16 + 4 + 3*4]                  
                                                  
   sub esp, 8*16+((4*3) % 16)-(16&15)             
   lea esi, [ecx*4]                               
   lea edi, [ecx+ecx*2]                               
   add esi, eax                                   
   mov ebp, 32/16                                 
   shl edx, 2                                     
   shl ebx, 2                                     
ff_deblock_h_luma_intra_10_sse2loop:                                          
   movdqu xmm4, [eax-8]                           
   movdqu xmm5, [eax+ecx-8]                       
   movdqu xmm0, [eax+ecx*2-8]                     
   movdqu xmm1, [eax+edi-8]                       
   movdqu xmm2, [esi-8]                           
   movdqu xmm3, [esi+ecx-8]                       
   movdqu xmm6, [esi+ecx*2-8]                     
   movdqu xmm7, [esi+edi-8]                       
                                                  
                                                  
                                                  
   movdqa [esp+16*(4-4)], xmm6                    
   movdqa xmm6, xmm4                              
                                                  
   punpcklwd xmm4, xmm5                           
                                                  
   punpckhwd xmm6, xmm5                           
   movdqa [esp+16*(5-4)], xmm6                    
   movdqa xmm5, [esp+16*(4-4)]                    
   movdqa xmm6, xmm0                              
                                                  
   punpcklwd xmm0, xmm1                           
                                                  
   punpckhwd xmm6, xmm1                           
   movdqa xmm1, xmm2                              
                                                  
   punpcklwd xmm2, xmm3                           
                                                  
   punpckhwd xmm1, xmm3                           
   movdqa xmm3, xmm5                              
                                                  
   punpcklwd xmm5, xmm7                           
                                                  
   punpckhwd xmm3, xmm7                           
   movdqa xmm7, xmm4                              
                                                  
   punpckldq xmm4, xmm0                           
                                                  
   punpckhdq xmm7, xmm0                           
   movdqa [esp+16*(4-4)], xmm7                    
   movdqa xmm0, [esp+16*(5-4)]                    
   movdqa xmm7, xmm0                              
                                                  
   punpckldq xmm0, xmm6                           
                                                  
   punpckhdq xmm7, xmm6                           
   movdqa xmm6, xmm2                              
                                                  
   punpckldq xmm2, xmm5                           
                                                  
   punpckhdq xmm6, xmm5                           
   movdqa xmm5, xmm1                              
                                                  
   punpckldq xmm1, xmm3                           
                                                  
   punpckhdq xmm5, xmm3                           
   movdqa xmm3, xmm4                              
                                                  
   punpcklqdq xmm4, xmm2                          
                                                  
   punpckhqdq xmm3, xmm2                          
   movdqa xmm2, xmm0                              
                                                  
   punpcklqdq xmm0, xmm1                          
                                                  
   punpckhqdq xmm2, xmm1                          
   movdqa [esp+16*(5-4)], xmm0                    
   movdqa xmm1, [esp+16*(4-4)]                    
   movdqa xmm0, xmm1                              
                                                  
   punpcklqdq xmm1, xmm6                          
                                                  
   punpckhqdq xmm0, xmm6                          
   movdqa xmm6, xmm7                              
                                                  
   punpcklqdq xmm7, xmm5                          
                                                  
   punpckhqdq xmm6, xmm5                          
   movdqa xmm5, [esp+16*(5-4)]                    
   movdqa [esp+16*(4-4)], xmm4                    
   movdqa [esp+16*(5-4)], xmm3                    
   movdqa [esp+16*(6-4)], xmm7                    
   movdqa [esp+16*(7-4)], xmm6                    
   movd xmm4, edx                                 
   movd xmm3, ebx                                 
   pshuflw xmm4, xmm4, (0)*0x55                   
                                                  
   punpcklqdq xmm4, xmm4                          
   pshuflw xmm3, xmm3, (0)*0x55                   
                                                  
   punpcklqdq xmm3, xmm3                          
   movdqa [esp+16*(8-4)], xmm4                    
                                                  
   movdqa xmm4, xmm5                              
   psubusw xmm4, xmm0                             
                                                  
   movdqa xmm7, xmm0                              
   psubusw xmm7, xmm5                             
                                                  
   por xmm7, xmm4                                 
                                                  
   psubw xmm7, [esp+16*(8-4)]                     
                                                  
   movdqa xmm4, xmm0                              
   psubusw xmm4, xmm1                             
                                                  
   movdqa xmm6, xmm1                              
   psubusw xmm6, xmm0                             
                                                  
   por xmm6, xmm4                                 
                                                  
   psubw xmm6, xmm3                               
                                                  
   pand xmm7, xmm6                                
                                                  
   movdqa xmm4, xmm2                              
   psubusw xmm4, xmm5                             
                                                  
   movdqa xmm6, xmm5                              
   psubusw xmm6, xmm2                             
                                                  
   por xmm6, xmm4                                 
                                                  
   psubw xmm6, xmm3                               
                                                  
   pxor xmm4, xmm4                                
                                                  
   pand xmm7, xmm6                                
                                                  
   pcmpgtw xmm4, xmm7                             
   movdqa xmm6, [esp+16*(8-4)]                    
   movdqa [esp+16*(9-4)], xmm4                    
                                                  
   psrlw xmm6, 2                                  
                                                  
   paddw xmm6, [ff_pw_2]                          
                                                  
   movdqa xmm7, xmm5                              
   psubusw xmm7, xmm0                             
                                                  
   movdqa xmm4, xmm0                              
   psubusw xmm4, xmm5                             
                                                  
   por xmm4, xmm7                                 
                                                  
   pxor xmm7, xmm7                                
                                                  
   psubw xmm4, xmm6                               
                                                  
   pcmpgtw xmm7, xmm4                             
                                                  
   pand xmm7, [esp+16*(9-4)]                      
   movdqa xmm6, [esp+16*(6-4)]                    
   movdqa [esp+16*(8-4)], xmm7                    
                                                  
   movdqa xmm7, xmm5                              
   psubusw xmm7, xmm6                             
                                                  
   movdqa xmm4, xmm6                              
   psubusw xmm4, xmm5                             
                                                  
   por xmm4, xmm7                                 
                                                  
   pxor xmm7, xmm7                                
                                                  
   psubw xmm4, xmm3                               
                                                  
   pcmpgtw xmm7, xmm4                             
                                                  
   pand xmm7, [esp+16*(8-4)]                      
   movdqa xmm6, [esp+16*(5-4)]                    
   movdqa [esp+16*(10-4)], xmm7                   
                                                  
   movdqa xmm7, xmm0                              
   psubusw xmm7, xmm6                             
                                                  
   movdqa xmm4, xmm6                              
   psubusw xmm4, xmm0                             
                                                  
   por xmm4, xmm7                                 
                                                  
   pxor xmm7, xmm7                                
                                                  
   psubw xmm4, xmm3                               
                                                  
   pcmpgtw xmm7, xmm4                             
                                                  
   pand xmm7, [esp+16*(8-4)]                      
   movdqa [esp+16*(8-4)], xmm7                    
                                                  
   movdqa xmm4, xmm6                              
   movdqa xmm7, [esp+16*(4-4)]                    
                                                  
   paddw xmm4, xmm1                               
                                                  
   paddw xmm7, xmm6                               
                                                  
   paddw xmm4, xmm0                               
                                                  
   paddw xmm7, xmm7                               
                                                  
   paddw xmm4, xmm5                               
                                                  
   paddw xmm7, [ff_pw_2]                          
                                                  
   paddw xmm4, [ff_pw_2]                          
                                                  
   paddw xmm7, xmm4                               
                                                  
                                                  
   psrlw xmm7, 3                                  
                                                  
   movdqa xmm3, xmm4                              
   psrlw xmm3, 2                                  
                                                  
   psubw xmm7, xmm6                               
                                                  
   psubw xmm3, xmm1                               
                                                  
   pand xmm7, [esp+16*(8-4)]                      
                                                  
   pand xmm3, [esp+16*(8-4)]                      
                                                  
   paddw xmm7, xmm6                               
                                                  
   paddw xmm3, xmm1                               
   movdqa [esp+16*(5-4)], xmm3                    
                                                  
                                                  
   movdqa xmm3, xmm4                              
   psubw xmm3, xmm6                               
                                                  
   paddw xmm4, xmm4                               
                                                  
   psubw xmm3, xmm5                               
                                                  
   psubw xmm4, xmm6                               
                                                  
   paddw xmm3, xmm2                               
                                                  
   paddw xmm3, xmm1                               
                                                  
   paddw xmm4, xmm2                               
                                                  
   psrlw xmm3, 2                                  
                                                  
   psrlw xmm4, 3                                  
                                                  
                                                  
   pxor xmm4, xmm3                                
                                                  
   pxor xmm3, xmm0                                
                                                  
   pand xmm4, [esp+16*(8-4)]                      
                                                  
   pand xmm3, [esp+16*(9-4)]                      
                                                  
   pxor xmm4, xmm3                                
                                                  
   pxor xmm4, xmm0                                
   movdqa [esp+16*(8-4)], xmm4                    
   movdqa [esp+16*(11-4)], xmm7                   
   movdqa xmm6, [esp+16*(6-4)]                    
   movdqa xmm4, xmm6                              
   movdqa xmm7, [esp+16*(7-4)]                    
                                                  
   paddw xmm4, xmm2                               
                                                  
   paddw xmm7, xmm6                               
                                                  
   paddw xmm4, xmm5                               
                                                  
   paddw xmm7, xmm7                               
                                                  
   paddw xmm4, xmm0                               
                                                  
   paddw xmm7, [ff_pw_2]                          
                                                  
   paddw xmm4, [ff_pw_2]                          
                                                  
   paddw xmm7, xmm4                               
                                                  
                                                  
   psrlw xmm7, 3                                  
                                                  
   movdqa xmm3, xmm4                              
   psrlw xmm3, 2                                  
                                                  
   psubw xmm7, xmm6                               
                                                  
   psubw xmm3, xmm2                               
                                                  
   pand xmm7, [esp+16*(10-4)]                     
                                                  
   pand xmm3, [esp+16*(10-4)]                     
                                                  
   paddw xmm7, xmm6                               
                                                  
   paddw xmm3, xmm2                               
   movdqa [esp+16*(6-4)], xmm3                    
                                                  
                                                  
   movdqa xmm3, xmm4                              
   psubw xmm3, xmm6                               
                                                  
   paddw xmm4, xmm4                               
                                                  
   psubw xmm3, xmm0                               
                                                  
   psubw xmm4, xmm6                               
                                                  
   paddw xmm3, xmm1                               
                                                  
   paddw xmm3, xmm2                               
                                                  
   paddw xmm4, xmm1                               
                                                  
   psrlw xmm3, 2                                  
                                                  
   psrlw xmm4, 3                                  
                                                  
                                                  
   pxor xmm4, xmm3                                
                                                  
   pxor xmm3, xmm5                                
                                                  
   pand xmm4, [esp+16*(10-4)]                     
                                                  
   pand xmm3, [esp+16*(9-4)]                      
                                                  
   pxor xmm4, xmm3                                
                                                  
   pxor xmm4, xmm5                                
                                                  
   movdqa xmm5, [esp+16*(4-4)]                    
   movdqa xmm1, [esp+16*(11-4)]                   
   movdqa xmm0, [esp+16*(5-4)]                    
   movdqa xmm2, [esp+16*(8-4)]                    
   movdqa xmm3, [esp+16*(6-4)]                    
                                                  
   movdqa xmm6, xmm5                              
                                                  
   punpcklwd xmm5, xmm1                           
                                                  
   punpckhwd xmm6, xmm1                           
   movdqa xmm1, xmm0                              
                                                  
   punpcklwd xmm0, xmm2                           
                                                  
   punpckhwd xmm1, xmm2                           
   movdqa xmm2, xmm5                              
                                                  
   punpckldq xmm5, xmm0                           
                                                  
   punpckhdq xmm2, xmm0                           
   movdqa xmm0, xmm6                              
                                                  
   punpckldq xmm6, xmm1                           
                                                  
   punpckhdq xmm0, xmm1                           
   movdqa xmm1, xmm5                              
                                                  
   punpcklqdq xmm5, xmm6                          
                                                  
   punpckhqdq xmm1, xmm6                          
   movdqa xmm6, xmm2                              
                                                  
   punpcklqdq xmm2, xmm0                          
                                                  
   punpckhqdq xmm6, xmm0                          
   movq qword ptr[eax-8], xmm5                             
   movq qword ptr[eax+ecx-8], xmm1                         
   movq qword ptr[eax+ecx*2-8], xmm2                       
   movq qword ptr[eax+edi-8], xmm6                         
   movhps [esi-8], xmm5                           
   movhps [esi+ecx-8], xmm1                       
   movhps [esi+ecx*2-8], xmm2                     
   movhps [esi+edi-8], xmm6                       
   movdqa xmm5, [esp+16*(7-4)]                    
   movdqa xmm0, xmm4                              
                                                  
   punpcklwd xmm4, xmm3                           
                                                  
   punpckhwd xmm0, xmm3                           
   movdqa xmm3, xmm7                              
                                                  
   punpcklwd xmm7, xmm5                           
                                                  
   punpckhwd xmm3, xmm5                           
   movdqa xmm5, xmm4                              
                                                  
   punpckldq xmm4, xmm7
                                                  
   punpckhdq xmm5, xmm7
   movdqa xmm7, xmm0                              
                                                  
   punpckldq xmm0, xmm3                           
                                                  
   punpckhdq xmm7, xmm3                           
   movdqa xmm3, xmm4                              
                                                  
   punpcklqdq xmm4, xmm0                          
                                                  
   punpckhqdq xmm3, xmm0                          
   movdqa xmm0, xmm5                              
                                                  
   punpcklqdq xmm5, xmm7                          
                                                  
   punpckhqdq xmm0, xmm7                          
   movq qword ptr[eax], xmm4                               
   movq qword ptr[eax+ecx], xmm3                           
   movq qword ptr[eax+ecx*2], xmm5                         
   movq qword ptr[eax+edi], xmm0                           
   movhps [esi], xmm4                             
   movhps [esi+ecx], xmm3                         
   movhps [esi+ecx*2], xmm5                       
   movhps [esi+edi], xmm0                         
                                                  
   lea eax, [eax+ecx*(16/2)]                      
   lea esi, [esi+ecx*(16/2)]                      
   dec ebp                                        
   jg  ff_deblock_h_luma_intra_10_sse2loop
   add esp, 8*16+((4*3) % 16)-(16&15)             
   pop ebp                                        
   pop edi                                        
   pop esi                                        
   pop ebx                                        
   ret
 }
}