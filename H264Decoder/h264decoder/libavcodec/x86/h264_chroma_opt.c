#include "dsputil_mmx.h"

typedef unsigned char uint8_t;
typedef unsigned char pixel;

//extern short ff_pw_32[8];
//extern short ff_pw_64[8];
//extern short ff_pw_4[8];
//extern short ff_pw_8[8];


void __declspec(naked) ff_put_h264_chroma_mc8_mmx_rnd(uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
        mov edi, [esp + 16 + 4 + 5*4]            
                                                 
        mov ebp, edi                             
        or ebp, esi                              
        jne $at_least_one_non_zero               
                                                 
        lea esi, [edx*2 ]                        
$next4rows:
        movq mm0, [ecx ]                         
        movq mm1, [ecx+edx]                      
        add ecx, esi                             
        movq [eax ], mm0                         
        movq [eax+edx], mm1                      
        add eax, esi                             
        movq mm0, [ecx ]                         
        movq mm1, [ecx+edx]                      
        add ecx, esi                             
        movq [eax ], mm0                         
        movq [eax+edx], mm1                      
        add eax, esi                             
        sub ebx, 4                               
        jne $next4rows                           
        pop ebp                                  
        pop edi                                  
        pop esi                                  
        pop ebx                                  
        ret                                      
                                                 
$at_least_one_non_zero:
                                                 
        test edi, edi                            
        mov ebp, 1                               
        je $my_is_zero                           
        test esi, esi                            
        mov ebp, edx                             
        jne $both_non_zero   

$my_is_zero:                                                
        or esi, edi                                                                               
        movd mm5, esi                            
        movq mm4, [ff_pw_8]                      
        movq mm6, [ff_pw_4+0*8]                  
                                                 
        punpcklwd mm5, mm5                       
                                                 
        punpckldq mm5, mm5                       
                                                 
        pxor mm7, mm7                            
                                                 
        psubw mm4, mm5                           
                                                 
$next1drow:                                
        movq mm0, [ecx ]                         
        movq mm2, [ecx+ebp]                      
                                                 
        movq mm1, mm0                            
        movq mm3, mm2                            
                                                 
        punpcklbw mm0, mm7                       
                                                 
        punpckhbw mm1, mm7                       
                                                 
        punpcklbw mm2, mm7                       
                                                 
        punpckhbw mm3, mm7                       
                                                 
        pmullw mm0, mm4                          
                                                 
        pmullw mm1, mm4                          
                                                 
        pmullw mm2, mm5                          
                                                 
        pmullw mm3, mm5                          
                                                 
                                                 
        paddw mm0, mm6                           
                                                 
        paddw mm1, mm6                           
                                                 
        paddw mm0, mm2                           
                                                 
        paddw mm1, mm3                           
                                                 
        psrlw mm0, 3                             
                                                 
        psrlw mm1, 3                             
                                                 
        packuswb mm0, mm1                        
        movq [eax], mm0                          
                                                 
        add eax, edx                             
        add ecx, edx                             
        dec ebx                                  
        jne $next1drow                           
        pop ebp                                  
        pop edi                                  
        pop esi                                  
        pop ebx                                  
        ret                                      
                                                 
$both_non_zero:                            
        movd mm4, esi                            
        movd mm6, edi                            
        mov ebp, esp                             
        and esp, ~(8-1)                          
        sub esp, 16                              
                                                 
                                                 
        punpcklwd mm4, mm4                       
                                                 
        punpcklwd mm6, mm6                       
                                                 
        punpckldq mm4, mm4                       
                                                 
        punpckldq mm6, mm6                       
        movq mm5, mm4                            
                                                 
        pmullw mm4, mm6                          
                                                 
        psllw mm5, 3                             
                                                 
        psllw mm6, 3                             
        movq mm7, mm5                            
                                                 
        paddw mm7, mm6                           
        movq [esp+8], mm4                        
                                                 
        psubw mm5, mm4                           
                                                 
        psubw mm6, mm4                           
                                                 
        paddw mm4, [ff_pw_64]                    
                                                 
        psubw mm4, mm7                           
                                                 
        pxor mm7, mm7                            
        movq [esp ], mm4                         
                                                 
        movq mm0, [ecx ]                         
        movq mm1, [ecx+1]                        
$next2drow:
        add ecx, edx                             
                                                 
        movq mm2, mm0                            
        movq mm3, mm1                            
                                                 
        punpckhbw mm0, mm7                       
                                                 
        punpcklbw mm1, mm7                       
                                                 
        punpcklbw mm2, mm7                       
                                                 
        punpckhbw mm3, mm7                       
                                                 
        pmullw mm0, [esp]                        
                                                 
        pmullw mm2, [esp]                        
                                                 
        pmullw mm1, mm5                          
                                                 
        pmullw mm3, mm5                          
                                                 
        paddw mm2, mm1                           
                                                 
        paddw mm3, mm0                           
                                                 
        movq mm0, [ecx]                          
        movq mm1, mm0                            
                                                 
        punpcklbw mm0, mm7                       
                                                 
        punpckhbw mm1, mm7                       
                                                 
        pmullw mm0, mm6                          
                                                 
        pmullw mm1, mm6                          
                                                 
        paddw mm2, mm0                           
                                                 
        paddw mm3, mm1                           
                                                 
        movq mm1, [ecx+1]                        
        movq mm0, mm1                            
        movq mm4, mm1                            
                                                 
        punpcklbw mm0, mm7                       
                                                 
        punpckhbw mm4, mm7                       
                                                 
        pmullw mm0, [esp+8]                      
                                                 
        pmullw mm4, [esp+8]                      
                                                 
        paddw mm2, mm0                           
                                                 
        paddw mm3, mm4                           
        movq mm0, [ecx]
        paddw mm2, [ff_pw_32+0*8]                
        paddw mm3, [ff_pw_32+0*8]                                                 
        psrlw mm2, 6                                                 
        psrlw mm3, 6                                                 
        packuswb mm2, mm3                        
        movq [eax], mm2                          
                                                 
        add eax, edx                             
        dec ebx                                  
        jne $next2drow
        mov esp, ebp
        pop ebp
        pop edi
        pop esi
        pop ebx
        ret
	}
}
void __declspec(naked) ff_avg_h264_chroma_mc8_mmx2_rnd(uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
      mov edi, [esp + 16 + 4 + 5*4]                 
                                                    
      mov ebp, edi                                  
      or ebp, esi                                   
      jne $at_least_one_non_zero                    
                                                    
      lea esi, [edx*2 ]                             
$next4rows:
      movq mm0, [ecx ]                              
      movq mm1, [ecx+edx]                           
      add ecx, esi                                  
                                                    
      pavgb mm0, [eax ]                             
                                                    
      pavgb mm1, [eax+edx]                          
      movq [eax ], mm0                              
      movq [eax+edx], mm1                           
      add eax, esi                                  
      movq mm0, [ecx ]                              
      movq mm1, [ecx+edx]                           
      add ecx, esi                                  
                                                    
      pavgb mm0, [eax ]                             
                                                    
      pavgb mm1, [eax+edx]                          
      movq [eax ], mm0                              
      movq [eax+edx], mm1                           
      add eax, esi                                  
      sub ebx, 4                                    
      jne $next4rows                                
      pop ebp                                       
      pop edi                                       
      pop esi                                       
      pop ebx                                       
      ret                                           
                                                    
$at_least_one_non_zero:                                                    
      test edi, edi                                 
      mov ebp, 1                                    
      je $my_is_zero                                
      test esi, esi                                 
      mov ebp, edx                                  
      jne $both_non_zero                            
$my_is_zero:
                                                    
      or esi, edi                                   
                                                    
                                                    
      movd mm5, esi                                 
      movq mm4, [ff_pw_8]                           
      movq mm6, [ff_pw_4+0*8]                       
                                                    
      punpcklwd mm5, mm5                            
                                                    
      punpckldq mm5, mm5                            
                                                    
      pxor mm7, mm7                                 
                                                    
      psubw mm4, mm5                                
                                                    
$next1drow:
      movq mm0, [ecx ]                              
      movq mm2, [ecx+ebp]                           
                                                    
      movq mm1, mm0                                 
      movq mm3, mm2                                 
                                                    
      punpcklbw mm0, mm7                            
                                                    
      punpckhbw mm1, mm7                            
                                                    
      punpcklbw mm2, mm7                            
                                                    
      punpckhbw mm3, mm7                            
                                                    
      pmullw mm0, mm4                               
                                                    
      pmullw mm1, mm4                               
                                                    
      pmullw mm2, mm5                               
                                                    
      pmullw mm3, mm5                               
                                                    
                                                    
      paddw mm0, mm6                                
                                                    
      paddw mm1, mm6                                
                                                    
      paddw mm0, mm2                                
                                                    
      paddw mm1, mm3                                
                                                    
      psrlw mm0, 3                                  
                                                    
      psrlw mm1, 3                                  
                                                    
      packuswb mm0, mm1                             
                                                    
      pavgb mm0, [eax]                              
      movq [eax], mm0                               
                                                    
      add eax, edx                                  
      add ecx, edx                                  
      dec ebx                                       
      jne $next1drow                                
      pop ebp                                       
      pop edi                                       
      pop esi                                       
      pop ebx                                       
      ret                                           
                                                    
$both_non_zero:                                 
      movd mm4, esi                                 
      movd mm6, edi                                 
      mov ebp, esp                                  
      and esp, ~(8-1)                               
      sub esp, 16                                   
                                                    
                                                    
      punpcklwd mm4, mm4                            
                                                    
      punpcklwd mm6, mm6                            
                                                    
      punpckldq mm4, mm4                            
                                                    
      punpckldq mm6, mm6                            
      movq mm5, mm4                                 
                                                    
      pmullw mm4, mm6                               
                                                    
      psllw mm5, 3                                  
                                                    
      psllw mm6, 3                                  
      movq mm7, mm5                                 
                                                    
      paddw mm7, mm6                                
      movq [esp+8], mm4                             
                                                    
      psubw mm5, mm4                                
                                                    
      psubw mm6, mm4                                
                                                    
      paddw mm4, [ff_pw_64]                         
                                                    
      psubw mm4, mm7                                
                                                    
      pxor mm7, mm7                                 
      movq [esp ], mm4                              
                                                    
      movq mm0, [ecx ]                              
      movq mm1, [ecx+1]                             
$next2drow:                                     
      add ecx, edx                                  
                                                    
      movq mm2, mm0                                 
      movq mm3, mm1                                 
                                                    
      punpckhbw mm0, mm7                            
                                                    
      punpcklbw mm1, mm7                            
                                                    
      punpcklbw mm2, mm7                            
                                                    
      punpckhbw mm3, mm7                            
                                                    
      pmullw mm0, [esp]                             
                                                    
      pmullw mm2, [esp]                             
                                                    
      pmullw mm1, mm5                               
                                                    
      pmullw mm3, mm5                               
                                                    
      paddw mm2, mm1                                
                                                    
      paddw mm3, mm0                                
                                                    
      movq mm0, [ecx]                               
      movq mm1, mm0                                 
                                                    
      punpcklbw mm0, mm7                            
                                                    
      punpckhbw mm1, mm7                            
                                                    
      pmullw mm0, mm6                               
                                                    
      pmullw mm1, mm6                               
                                                    
      paddw mm2, mm0                                
                                                    
      paddw mm3, mm1                                
                                                    
      movq mm1, [ecx+1]                             
      movq mm0, mm1                                 
      movq mm4, mm1                                 
                                                    
      punpcklbw mm0, mm7                            
                                                    
      punpckhbw mm4, mm7                            
                                                    
      pmullw mm0, [esp+8]                           
                                                    
      pmullw mm4, [esp+8]                           
                                                    
      paddw mm2, mm0                                
                                                    
      paddw mm3, mm4                                
      movq mm0, [ecx]                               
                                                    
                                                    
      paddw mm2, [ff_pw_32+0*8]                     
                                                    
      paddw mm3, [ff_pw_32+0*8]                     
                                                    
      psrlw mm2, 6                                  
                                                    
      psrlw mm3, 6                                  
                                                    
      packuswb mm2, mm3                             
                                                    
      pavgb mm2, [eax]                              
      movq [eax], mm2                               
                                                    
      add eax, edx                                  
      dec ebx                                       
      jne $next2drow                                
      mov esp, ebp                                  
      pop ebp                                       
      pop edi                                       
      pop esi                                       
      pop ebx                                       
      ret                                           
	}
}
void __declspec(naked) ff_avg_h264_chroma_mc8_3dnow_rnd (uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
   mov edi, [esp + 16 + 4 + 5*4]                   
                                                   
   mov ebp, edi                                    
   or ebp, esi                                     
   jne $at_least_one_non_zero                      
                                                   
   lea esi, [edx*2 ]                               
$next4rows:                                       
   movq mm0, [ecx ]                                
   movq mm1, [ecx+edx]                             
   add ecx, esi                                    
   pavgusb mm0, [eax ]                             
   pavgusb mm1, [eax+edx]                          
   movq [eax ], mm0                                
   movq [eax+edx], mm1                             
   add eax, esi                                    
   movq mm0, [ecx ]                                
   movq mm1, [ecx+edx]                             
   add ecx, esi                                    
   pavgusb mm0, [eax ]                             
   pavgusb mm1, [eax+edx]                          
   movq [eax ], mm0                                
   movq [eax+edx], mm1                             
   add eax, esi                                    
   sub ebx, 4                                      
   jne $next4rows                                  
   pop ebp                                         
   pop edi                                         
   pop esi                                         
   pop ebx                                         
   ret                                             
                                                   
$at_least_one_non_zero:
                                                   
   test edi, edi                                   
   mov ebp, 1                                      
   je $my_is_zero                                  
   test esi, esi                                   
   mov ebp, edx                                    
   jne $both_non_zero                              
$my_is_zero:                                      
                                                   
   or esi, edi                                     
                                                   
                                                   
   movd mm5, esi                                   
   movq mm4, [ff_pw_8]                             
   movq mm6, [ff_pw_4+0*8]                         
                                                   
   punpcklwd mm5, mm5                              
                                                   
   punpckldq mm5, mm5                              
                                                   
   pxor mm7, mm7                                   
                                                   
   psubw mm4, mm5                                  
                                                   
$next1drow:                                       
   movq mm0, [ecx ]                                
   movq mm2, [ecx+ebp]                             
                                                   
   movq mm1, mm0                                   
   movq mm3, mm2                                   
                                                   
   punpcklbw mm0, mm7                              
                                                   
   punpckhbw mm1, mm7                              
                                                   
   punpcklbw mm2, mm7                              
                                                   
   punpckhbw mm3, mm7                              
                                                   
   pmullw mm0, mm4                                 
                                                   
   pmullw mm1, mm4                                 
                                                   
   pmullw mm2, mm5                                 
                                                   
   pmullw mm3, mm5                                 
                                                   
                                                   
   paddw mm0, mm6                                  
                                                   
   paddw mm1, mm6                                  
                                                   
   paddw mm0, mm2                                  
                                                   
   paddw mm1, mm3                                  
                                                   
   psrlw mm0, 3                                    
                                                   
   psrlw mm1, 3                                    
                                                   
   packuswb mm0, mm1                               
   pavgusb mm0, [eax]                              
   movq [eax], mm0                                 
                                                   
   add eax, edx                                    
   add ecx, edx                                    
   dec ebx                                         
   jne $next1drow                                  
   pop ebp                                         
   pop edi                                         
   pop esi                                         
   pop ebx                                         
   ret                                             
                                                   
$both_non_zero:                                   
   movd mm4, esi                                   
   movd mm6, edi                                   
   mov ebp, esp                                    
   and esp, ~(8-1)                                 
   sub esp, 16                                     
                                                   
                                                   
   punpcklwd mm4, mm4                              
                                                   
   punpcklwd mm6, mm6                              
                                                   
   punpckldq mm4, mm4                              
                                                   
   punpckldq mm6, mm6                              
   movq mm5, mm4                                   
                                                   
   pmullw mm4, mm6                                 
                                                   
   psllw mm5, 3                                    
                                                   
   psllw mm6, 3                                    
   movq mm7, mm5                                   
                                                   
   paddw mm7, mm6                                  
   movq [esp+8], mm4                               
                                                   
   psubw mm5, mm4                                  
                                                   
   psubw mm6, mm4                                  
                                                   
   paddw mm4, [ff_pw_64]                           
                                                   
   psubw mm4, mm7                                  
                                                   
   pxor mm7, mm7                                   
   movq [esp ], mm4                                
                                                   
   movq mm0, [ecx ]                                
   movq mm1, [ecx+1]                               
$next2drow:                                       
   add ecx, edx                                    
                                                   
   movq mm2, mm0                                   
   movq mm3, mm1                                   
                                                   
   punpckhbw mm0, mm7                              
                                                   
   punpcklbw mm1, mm7                              
                                                   
   punpcklbw mm2, mm7                              
                                                   
   punpckhbw mm3, mm7                              
                                                   
   pmullw mm0, [esp]                               
                                                   
   pmullw mm2, [esp]                               
                                                   
   pmullw mm1, mm5                                 
                                                   
   pmullw mm3, mm5                                 
                                                   
   paddw mm2, mm1                                  
                                                   
   paddw mm3, mm0                                  
                                                   
   movq mm0, [ecx]                                 
   movq mm1, mm0                                   
                                                   
   punpcklbw mm0, mm7                              
                                                   
   punpckhbw mm1, mm7                              
                                                   
   pmullw mm0, mm6                                 
                                                   
   pmullw mm1, mm6                                 
                                                   
   paddw mm2, mm0                                  
                                                   
   paddw mm3, mm1                                  
                                                   
   movq mm1, [ecx+1]                               
   movq mm0, mm1                                   
   movq mm4, mm1                                   
                                                   
   punpcklbw mm0, mm7                              
                                                   
   punpckhbw mm4, mm7                              
                                                   
   pmullw mm0, [esp+8]                             
                                                   
   pmullw mm4, [esp+8]                             
                                                   
   paddw mm2, mm0                                  
                                                   
   paddw mm3, mm4                                  
   movq mm0, [ecx]                                 
                                                   
                                                   
   paddw mm2, [ff_pw_32+0*8]                       
                                                   
   paddw mm3, [ff_pw_32+0*8]                       
                                                   
   psrlw mm2, 6                                    
                                                   
   psrlw mm3, 6                                    
                                                   
   packuswb mm2, mm3                               
   pavgusb mm2, [eax]                              
   movq [eax], mm2                                 
                                                   
   add eax, edx                                    
   dec ebx                                         
   jne $next2drow                                  
   mov esp, ebp                                    
   pop ebp                                         
   pop edi                                         
   pop esi                                         
   pop ebx                                         
   ret
	}
}
void __declspec(naked) ff_put_h264_chroma_mc4_mmx(uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
  mov edi, [esp + 12 + 4 + 5*4]                       
                                                      
                                                      
  pxor mm7, mm7                                       
  movd mm2, esi                                       
  movd mm3, edi                                       
  movq mm4, [ff_pw_8]                                 
  movq mm5, [ff_pw_8]                                 
                                                      
  punpcklwd mm2, mm2                                  
                                                      
  punpcklwd mm3, mm3                                  
                                                      
  punpcklwd mm2, mm2                                  
                                                      
  punpcklwd mm3, mm3                                  
                                                      
  psubw mm4, mm2                                      
                                                      
  psubw mm5, mm3                                      
                                                      
                                                      
  movd mm0, [ecx ]                                    
  movd mm6, [ecx+1]                                   
  add ecx, edx                                        
                                                      
  punpcklbw mm0, mm7                                  
                                                      
  punpcklbw mm6, mm7                                  
                                                      
  pmullw mm0, mm4                                     
                                                      
  pmullw mm6, mm2                                     
                                                      
  paddw mm6, mm0                                      
                                                      
$next2rows:                                           
  movd mm0, [ecx ]                                    
  movd mm1, [ecx+1]                                   
  add ecx, edx                                        
                                                      
  punpcklbw mm0, mm7                                  
                                                      
  punpcklbw mm1, mm7                                  
                                                      
  pmullw mm0, mm4                                     
                                                      
  pmullw mm1, mm2                                     
                                                      
  paddw mm1, mm0                                      
  movq mm0, mm1                                       
                                                      
                                                      
  pmullw mm6, mm5                                     
                                                      
  pmullw mm1, mm3                                     
                                                      
  paddw mm6, [ff_pw_32+0*8]                           
                                                      
  paddw mm1, mm6                                      
                                                      
  psrlw mm1, 6                                        
                                                      
  packuswb mm1, mm1                                   
  movd [eax], mm1                                     
  add eax, edx                                        
                                                      
  movd mm6, [ecx ]                                    
  movd mm1, [ecx+1]                                   
  add ecx, edx                                        
                                                      
  punpcklbw mm6, mm7                                  
                                                      
  punpcklbw mm1, mm7                                  
                                                      
  pmullw mm6, mm4                                     
                                                      
  pmullw mm1, mm2                                     
                                                      
  paddw mm1, mm6                                      
  movq mm6, mm1                                       
                                                      
  pmullw mm0, mm5                                     
                                                      
  pmullw mm1, mm3                                     
                                                      
  paddw mm0, [ff_pw_32+0*8]                           
                                                      
  paddw mm1, mm0                                      
                                                      
  psrlw mm1, 6                                        
                                                      
  packuswb mm1, mm1                                   
  movd [eax], mm1                                     
  add eax, edx                                        
  sub ebx, 2                                          
  jnz $next2rows                                      
  pop edi                                             
  pop esi                                             
  pop ebx                                             
  ret
	}
}
void __declspec(naked) ff_avg_h264_chroma_mc4_mmx2      (uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
  mov edi, [esp + 12 + 4 + 5*4]                   
                                                  
                                                  
  pxor mm7, mm7                                   
  movd mm2, esi                                   
  movd mm3, edi                                   
  movq mm4, [ff_pw_8]                             
  movq mm5, [ff_pw_8]                             
                                                  
  punpcklwd mm2, mm2                              
                                                  
  punpcklwd mm3, mm3                              
                                                  
  punpcklwd mm2, mm2                              
                                                  
  punpcklwd mm3, mm3                              
                                                  
  psubw mm4, mm2                                  
                                                  
  psubw mm5, mm3                                  
                                                  
                                                  
  movd mm0, [ecx ]                                
  movd mm6, [ecx+1]                               
  add ecx, edx                                    
                                                  
  punpcklbw mm0, mm7                              
                                                  
  punpcklbw mm6, mm7                              
                                                  
  pmullw mm0, mm4                                 
                                                  
  pmullw mm6, mm2                                 
                                                  
  paddw mm6, mm0                                  
                                                  
$next2rows:                                       
  movd mm0, [ecx ]                                
  movd mm1, [ecx+1]                               
  add ecx, edx                                    
                                                  
  punpcklbw mm0, mm7                              
                                                  
  punpcklbw mm1, mm7                              
                                                  
  pmullw mm0, mm4                                 
                                                  
  pmullw mm1, mm2                                 
                                                  
  paddw mm1, mm0                                  
  movq mm0, mm1                                   
                                                  
                                                  
  pmullw mm6, mm5                                 
                                                  
  pmullw mm1, mm3                                 
                                                  
  paddw mm6, [ff_pw_32+0*8]                       
                                                  
  paddw mm1, mm6                                  
                                                  
  psrlw mm1, 6                                    
                                                  
  packuswb mm1, mm1                               
  movd mm6, [eax]                                 
                                                  
  pavgb mm1, mm6                                  
  movd [eax], mm1                                 
  add eax, edx                                    
                                                  
  movd mm6, [ecx ]                                
  movd mm1, [ecx+1]                               
  add ecx, edx                                    
                                                  
  punpcklbw mm6, mm7                              
                                                  
  punpcklbw mm1, mm7                              
                                                  
  pmullw mm6, mm4                                 
                                                  
  pmullw mm1, mm2                                 
                                                  
  paddw mm1, mm6                                  
  movq mm6, mm1                                   
                                                  
  pmullw mm0, mm5                                 
                                                  
  pmullw mm1, mm3                                 
                                                  
  paddw mm0, [ff_pw_32+0*8]                       
                                                  
  paddw mm1, mm0                                  
                                                  
  psrlw mm1, 6                                    
                                                  
  packuswb mm1, mm1                               
  movd mm0, [eax]                                 
                                                  
  pavgb mm1, mm0                                  
  movd [eax], mm1                                 
  add eax, edx                                    
  sub ebx, 2                                      
  jnz $next2rows                                  
  pop edi                                         
  pop esi                                         
  pop ebx                                         
  ret
	}
}
void __declspec(naked) ff_avg_h264_chroma_mc4_3dnow     (uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
  mov edi, [esp + 12 + 4 + 5*4]             
                                            
                                            
  pxor mm7, mm7                             
  movd mm2, esi                             
  movd mm3, edi                             
  movq mm4, [ff_pw_8]                       
  movq mm5, [ff_pw_8]                       
                                            
  punpcklwd mm2, mm2                        
                                            
  punpcklwd mm3, mm3                        
                                            
  punpcklwd mm2, mm2                        
                                            
  punpcklwd mm3, mm3                        
                                            
  psubw mm4, mm2                            
                                            
  psubw mm5, mm3                            
                                            
                                            
  movd mm0, [ecx ]                          
  movd mm6, [ecx+1]                         
  add ecx, edx                              
                                            
  punpcklbw mm0, mm7                        
                                            
  punpcklbw mm6, mm7                        
                                            
  pmullw mm0, mm4                           
                                            
  pmullw mm6, mm2                           
                                            
  paddw mm6, mm0                            
                                            
$next2rows:
  movd mm0, [ecx ]                          
  movd mm1, [ecx+1]                         
  add ecx, edx                              
                                            
  punpcklbw mm0, mm7                        
                                            
  punpcklbw mm1, mm7                        
                                            
  pmullw mm0, mm4                           
                                            
  pmullw mm1, mm2                           
                                            
  paddw mm1, mm0                            
  movq mm0, mm1                             
                                            
                                            
  pmullw mm6, mm5                           
                                            
  pmullw mm1, mm3                           
                                            
  paddw mm6, [ff_pw_32+0*8]                 
                                            
  paddw mm1, mm6                            
                                            
  psrlw mm1, 6                              
                                            
  packuswb mm1, mm1                         
  movd mm6, [eax]                           
  pavgusb mm1, mm6                          
  movd [eax], mm1                           
  add eax, edx                              
                                            
  movd mm6, [ecx ]                          
  movd mm1, [ecx+1]                         
  add ecx, edx                              
                                            
  punpcklbw mm6, mm7                        
                                            
  punpcklbw mm1, mm7                        
                                            
  pmullw mm6, mm4                           
                                            
  pmullw mm1, mm2                           
                                            
  paddw mm1, mm6                            
  movq mm6, mm1                             
                                            
  pmullw mm0, mm5                           
                                            
  pmullw mm1, mm3                           
                                            
  paddw mm0, [ff_pw_32+0*8]                 
                                            
  paddw mm1, mm0                            
                                            
  psrlw mm1, 6                              
                                            
  packuswb mm1, mm1                         
  movd mm0, [eax]                           
  pavgusb mm1, mm0                          
  movd [eax], mm1                           
  add eax, edx                              
  sub ebx, 2                                
  jnz $next2rows                            
  pop edi                                   
  pop esi                                   
  pop ebx                                   
  ret                                       



	}
}
void __declspec(naked) ff_put_h264_chroma_mc2_mmx2(uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
   mov edi, [esp + 16 + 4 + 5*4]                 
                                                 
                                                 
   mov ebp, esi                                  
   shl esi, 16                                   
   sub esi, ebp                                  
   add esi, 8                                    
   imul edi, esi                                 
   shl esi, 3                                    
   sub esi, edi                                  
                                                 
   movd mm5, esi                                 
   movd mm6, edi                                 
                                                 
   punpckldq mm5, mm5                            
                                                 
   punpckldq mm6, mm6                            
                                                 
   pxor mm7, mm7                                 
   movd mm2, [ecx]                               
                                                 
   punpcklbw mm2, mm7                            
   pshufw mm2, mm2, 0x94                         
                                                 
$nextrow:                                       
   add ecx, edx                                  
   movq mm1, mm2                                 
                                                 
   pmaddwd mm1, mm5                              
   movd mm0, [ecx]                               
                                                 
   punpcklbw mm0, mm7                            
   pshufw mm0, mm0, 0x94                         
   movq mm2, mm0                                 
                                                 
   pmaddwd mm0, mm6                              
                                                 
   paddw mm1, [ff_pw_32]                         
                                                 
   paddw mm1, mm0                                
                                                 
   psrlw mm1, 6                                  
                                                 
   packssdw mm1, mm7                             
                                                 
   packuswb mm1, mm7                             
   movd edi, mm1                                 
   mov [eax], di                                 
   add eax, edx                                  
   sub ebx, 1                                    
   jnz $nextrow                                  
   pop ebp                                       
   pop edi                                       
   pop esi                                       
   pop ebx                                       
   ret                                           

	}
}
void __declspec(naked) ff_avg_h264_chroma_mc2_mmx2      (uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
   mov edi, [esp + 16 + 4 + 5*4]                  
                                                  
                                                  
   mov ebp, esi                                   
   shl esi, 16                                    
   sub esi, ebp                                   
   add esi, 8                                     
   imul edi, esi                                  
   shl esi, 3                                     
   sub esi, edi                                   
                                                  
   movd mm5, esi                                  
   movd mm6, edi                                  
                                                  
   punpckldq mm5, mm5                             
                                                  
   punpckldq mm6, mm6                             
                                                  
   pxor mm7, mm7                                  
   movd mm2, [ecx]                                
                                                  
   punpcklbw mm2, mm7                             
   pshufw mm2, mm2, 0x94                          
                                                  
$nextrow:                                        
   add ecx, edx                                   
   movq mm1, mm2                                  
                                                  
   pmaddwd mm1, mm5                               
   movd mm0, [ecx]                                
                                                  
   punpcklbw mm0, mm7                             
   pshufw mm0, mm0, 0x94                          
   movq mm2, mm0                                  
                                                  
   pmaddwd mm0, mm6                               
                                                  
   paddw mm1, [ff_pw_32]                          
                                                  
   paddw mm1, mm0                                 
                                                  
   psrlw mm1, 6                                   
                                                  
   packssdw mm1, mm7                              
                                                  
   packuswb mm1, mm7                              
   movd mm3, [eax]                                
                                                  
   pavgb mm1, mm3                                 
   movd edi, mm1                                  
   mov [eax], di                                  
   add eax, edx                                   
   sub ebx, 1                                     
   jnz $nextrow                                   
   pop ebp                                        
   pop edi                                        
   pop esi                                        
   pop ebx                                        
   ret                                            

	}
}
void __declspec(naked) ff_put_h264_chroma_mc8_ssse3_rnd (uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
  mov edi, [esp + 16 + 4 + 5*4]                         
                                                        
  mov ebp, edi                                          
  or ebp, esi                                           
  jne $at_least_one_non_zero                            
                                                        
  lea esi, [edx*2 ]                                     
$next4rows:                                             
  movq mm0, [ecx ]                                      
  movq mm1, [ecx+edx]                                   
  add ecx, esi                                          
  movq [eax ], mm0                                      
  movq [eax+edx], mm1                                   
  add eax, esi                                          
  movq mm0, [ecx ]                                      
  movq mm1, [ecx+edx]                                   
  add ecx, esi                                          
  movq [eax ], mm0                                      
  movq [eax+edx], mm1                                   
  add eax, esi                                          
  sub ebx, 4                                            
  jne $next4rows                                        
  pop ebp                                               
  pop edi                                               
  pop esi                                               
  pop ebx                                               
  ret                                                   
                                                        
$at_least_one_non_zero:
  test edi, edi                                         
  je $my_is_zero                                        
  test esi, esi                                         
  je $mx_is_zero                                        
                                                        
                                                        
  mov ebp, esi                                          
  shl esi, 8                                            
  sub esi, ebp                                          
  mov ebp, 8                                            
  add esi, 8                                            
  sub ebp, edi                                          
  imul ebp, esi                                         
  imul esi, edi                                         
                                                        
  movd xmm7, ebp                                        
  movd xmm6, esi                                        
  movdqa xmm5, [ff_pw_32]                               
  movq xmm0, qword ptr [ecx ]                                     
  movq xmm1, qword ptr [ecx+1]                                    
  pshuflw xmm7, xmm7, 0                                 
  pshuflw xmm6, xmm6, 0                                 
                                                        
  punpcklbw xmm0, xmm1                                  
                                                        
  movlhps xmm7, xmm7                                    
                                                        
  movlhps xmm6, xmm6                                    
                                                        
$next2rows:                                             
  movq xmm1, qword ptr[ecx+edx*1 ]                               
  movq xmm2, qword ptr[ecx+edx*1+1]                              
  movq xmm3, qword ptr[ecx+edx*2 ]                               
  movq xmm4, qword ptr[ecx+edx*2+1]                              
  lea ecx, [ecx+edx*2]                                  
                                                        
  punpcklbw xmm1, xmm2                                  
  movdqa xmm2, xmm1                                     
                                                        
  punpcklbw xmm3, xmm4                                  
  movdqa xmm4, xmm3                                     
                                                        
  pmaddubsw xmm0, xmm7                                  
                                                        
  pmaddubsw xmm1, xmm6                                  
                                                        
  pmaddubsw xmm2, xmm7                                  
                                                        
  pmaddubsw xmm3, xmm6                                  
                                                        
  paddw xmm0, xmm5                                      
                                                        
  paddw xmm2, xmm5                                      
                                                        
  paddw xmm1, xmm0                                      
                                                        
  paddw xmm3, xmm2                                      
                                                        
  psrlw xmm1, 6                                         
  movdqa xmm0, xmm4                                     
                                                        
  psrlw xmm3, 6                                         
                                                        
  packuswb xmm1, xmm3                                   
  movq qword ptr[eax ], xmm1                                     
  movhps [eax+edx], xmm1                                
  sub ebx, 2                                            
  lea eax, [eax+edx*2]                                  
  jg $next2rows                                         
  pop ebp                                               
  pop edi                                               
  pop esi                                               
  pop ebx                                               
  ret                                                   
                                                        
$my_is_zero:                                            
  mov edi, esi                                          
  shl esi, 8                                            
  add esi, 8                                            
  sub esi, edi                                          
  movd xmm7, esi                                        
  movdqa xmm6, [ff_pw_4]                                
  pshuflw xmm7, xmm7, 0                                 
                                                        
  movlhps xmm7, xmm7                                    
                                                        
$next2xrows:                                            
  movq xmm0, qword ptr[ecx ]                                     
  movq xmm1, qword ptr[ecx +1]                                   
  movq xmm2, qword ptr[ecx+edx ]                                 
  movq xmm3, qword ptr[ecx+edx+1]                                
                                                        
  punpcklbw xmm0, xmm1                                  
                                                        
  punpcklbw xmm2, xmm3                                  
                                                        
  pmaddubsw xmm0, xmm7                                  
                                                        
  pmaddubsw xmm2, xmm7                                  
                                                        
  paddw xmm0, xmm6                                      
                                                        
  paddw xmm2, xmm6                                      
                                                        
  psrlw xmm0, 3                                         
                                                        
  psrlw xmm2, 3                                         
                                                        
  packuswb xmm0, xmm2                                   
  movq qword ptr[eax ], xmm0                                     
  movhps [eax+edx], xmm0                                
  sub ebx, 2                                            
  lea eax, [eax+edx*2]                                  
  lea ecx, [ecx+edx*2]                                  
  jg $next2xrows                                        
  pop ebp                                               
  pop edi                                               
  pop esi                                               
  pop ebx                                               
  ret                                                   
                                                        
$mx_is_zero:                                            
  mov esi, edi                                          
  shl edi, 8                                            
  add edi, 8                                            
  sub edi, esi                                          
  movd xmm7, edi                                        
  movdqa xmm6, [ff_pw_4]                                
  pshuflw xmm7, xmm7, 0                                 
                                                        
  movlhps xmm7, xmm7                                    
                                                        
$next2yrows:                                            
  movq xmm0, qword ptr[ecx ]                                     
  movq xmm1, qword ptr[ecx+edx ]                                 
  movdqa xmm2, xmm1                                     
  movq xmm3, qword ptr[ecx+edx*2]                                
  lea ecx, [ecx+edx*2]                                  
                                                        
  punpcklbw xmm0, xmm1                                  
                                                        
  punpcklbw xmm2, xmm3                                  
                                                        
  pmaddubsw xmm0, xmm7                                  
                                                        
  pmaddubsw xmm2, xmm7                                  
                                                        
  paddw xmm0, xmm6                                      
                                                        
  paddw xmm2, xmm6                                      
                                                        
  psrlw xmm0, 3                                         
                                                        
  psrlw xmm2, 3                                         
                                                        
  packuswb xmm0, xmm2                                   
  movq qword ptr[eax ], xmm0                                     
  movhps [eax+edx], xmm0                                
  sub ebx, 2                                            
  lea eax, [eax+edx*2]                                  
  jg $next2yrows                                        
  pop ebp                                               
  pop edi                                               
  pop esi                                               
  pop ebx                                               
  ret                                                   

	}
}
void __declspec(naked) ff_put_h264_chroma_mc4_ssse3     (uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
  mov edi, [esp + 16 + 4 + 5*4]               
                                              
  mov ebp, esi                                
  shl esi, 8                                  
  sub esi, ebp                                
  mov ebp, 8                                  
  add esi, 8                                  
  sub ebp, edi                                
  imul ebp, esi                               
  imul esi, edi                               
                                              
  movd mm7, ebp                               
  movd mm6, esi                               
  movq mm5, [ff_pw_32]                        
  movd mm0, [ecx ]                            
  pshufw mm7, mm7, 0                          
                                              
  punpcklbw mm0, [ecx+1]                      
  pshufw mm6, mm6, 0                          
                                              
$next2rows:                                   
  movd mm1, [ecx+edx*1 ]                      
  movd mm3, [ecx+edx*2 ]                      
                                              
  punpcklbw mm1, [ecx+edx*1+1]                
                                              
  punpcklbw mm3, [ecx+edx*2+1]                
  lea ecx, [ecx+edx*2]                        
  movq mm2, mm1                               
  movq mm4, mm3                               
                                              
  pmaddubsw mm0, mm7                          
                                              
  pmaddubsw mm1, mm6                          
                                              
  pmaddubsw mm2, mm7                          
                                              
  pmaddubsw mm3, mm6                          
                                              
  paddw mm0, mm5                              
                                              
  paddw mm2, mm5                              
                                              
  paddw mm1, mm0                              
                                              
  paddw mm3, mm2                              
                                              
  psrlw mm1, 6                                
  movq mm0, mm4                               
                                              
  psrlw mm3, 6                                
                                              
  packuswb mm1, mm1                           
                                              
  packuswb mm3, mm3                           
  movd [eax ], mm1                            
  movd [eax+edx], mm3                         
  sub ebx, 2                                  
  lea eax, [eax+edx*2]                        
  jg $next2rows                               
  pop ebp                                     
  pop edi                                     
  pop esi                                     
  pop ebx                                     
  ret
	}
}
void __declspec(naked) ff_avg_h264_chroma_mc8_ssse3_rnd (uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
  mov edi, [esp + 16 + 4 + 5*4]                
                                               
  mov ebp, edi                                 
  or ebp, esi                                  
  jne $at_least_one_non_zero                   
                                               
  lea esi, [edx*2 ]                            
$next4rows:                                    
  movq mm0, [ecx ]                             
  movq mm1, [ecx+edx]                          
  add ecx, esi                                 
                                               
  pavgb mm0, [eax ]                            
                                               
  pavgb mm1, [eax+edx]                         
  movq [eax ], mm0                             
  movq [eax+edx], mm1                          
  add eax, esi                                 
  movq mm0, [ecx ]                             
  movq mm1, [ecx+edx]                          
  add ecx, esi                                 
                                               
  pavgb mm0, [eax ]                            
                                               
  pavgb mm1, [eax+edx]                         
  movq [eax ], mm0                             
  movq [eax+edx], mm1                          
  add eax, esi                                 
  sub ebx, 4                                   
  jne $next4rows                               
  pop ebp                                      
  pop edi                                      
  pop esi                                      
  pop ebx                                      
  ret                                          
                                               
$at_least_one_non_zero:                        
  test edi, edi                                
  je $my_is_zero                               
  test esi, esi                                
  je $mx_is_zero                               
                                               
                                               
  mov ebp, esi                                 
  shl esi, 8                                   
  sub esi, ebp                                 
  mov ebp, 8                                   
  add esi, 8                                   
  sub ebp, edi                                 
  imul ebp, esi                                
  imul esi, edi                                
                                               
  movd xmm7, ebp                               
  movd xmm6, esi                               
  movdqa xmm5, [ff_pw_32]                      
  movq xmm0, qword ptr[ecx ]                            
  movq xmm1, qword ptr[ecx+1]                           
  pshuflw xmm7, xmm7, 0                        
  pshuflw xmm6, xmm6, 0                        
                                               
  punpcklbw xmm0, xmm1                         
                                               
  movlhps xmm7, xmm7                           
                                               
  movlhps xmm6, xmm6                           
                                               
$next2rows:                                    
  movq xmm1, qword ptr[ecx+edx*1 ]                      
  movq xmm2, qword ptr[ecx+edx*1+1]                     
  movq xmm3, qword ptr[ecx+edx*2 ]                      
  movq xmm4, qword ptr[ecx+edx*2+1]                     
  lea ecx, [ecx+edx*2]                         
                                               
  punpcklbw xmm1, xmm2                         
  movdqa xmm2, xmm1                            
                                               
  punpcklbw xmm3, xmm4                         
  movdqa xmm4, xmm3                            
                                               
  pmaddubsw xmm0, xmm7                         
                                               
  pmaddubsw xmm1, xmm6                         
                                               
  pmaddubsw xmm2, xmm7                         
                                               
  pmaddubsw xmm3, xmm6                         
                                               
  paddw xmm0, xmm5                             
                                               
  paddw xmm2, xmm5                             
                                               
  paddw xmm1, xmm0                             
                                               
  paddw xmm3, xmm2                             
                                               
  psrlw xmm1, 6                                
  movdqa xmm0, xmm4                            
                                               
  psrlw xmm3, 6                                
  movq xmm2, qword ptr[eax ]                            
  movhps xmm2, [eax+edx]                       
                                               
  packuswb xmm1, xmm3                          
                                               
  pavgb xmm1, xmm2                             
  movq qword ptr[eax ], xmm1                            
  movhps [eax+edx], xmm1                       
  sub ebx, 2                                   
  lea eax, [eax+edx*2]                         
  jg $next2rows                                
  pop ebp                                      
  pop edi                                      
  pop esi                                      
  pop ebx                                      
  ret                                          
                                               
$my_is_zero:                                   
  mov edi, esi                                 
  shl esi, 8                                   
  add esi, 8                                   
  sub esi, edi                                 
  movd xmm7, esi                               
  movdqa xmm6, [ff_pw_4]                       
  pshuflw xmm7, xmm7, 0                        
                                               
  movlhps xmm7, xmm7                           
                                               
$next2xrows:                                   
  movq xmm0, qword ptr[ecx ]                            
  movq xmm1, qword ptr[ecx +1]                          
  movq xmm2, qword ptr[ecx+edx ]                        
  movq xmm3, qword ptr[ecx+edx+1]                       
                                               
  punpcklbw xmm0, xmm1                         
                                               
  punpcklbw xmm2, xmm3                         
                                               
  pmaddubsw xmm0, xmm7                         
                                               
  pmaddubsw xmm2, xmm7                         
  movq xmm4, qword ptr[eax ]                            
  movhps xmm4, [eax+edx]                       
                                               
  paddw xmm0, xmm6                             
                                               
  paddw xmm2, xmm6                             
                                               
  psrlw xmm0, 3                                
                                               
  psrlw xmm2, 3                                
                                               
  packuswb xmm0, xmm2                          
                                               
  pavgb xmm0, xmm4                             
  movq qword ptr[eax ], xmm0                            
  movhps [eax+edx], xmm0                       
  sub ebx, 2                                   
  lea eax, [eax+edx*2]                         
  lea ecx, [ecx+edx*2]                         
  jg $next2xrows                               
  pop ebp                                      
  pop edi                                      
  pop esi                                      
  pop ebx                                      
  ret                                          
                                               
$mx_is_zero:                                   
  mov esi, edi                                 
  shl edi, 8                                   
  add edi, 8                                   
  sub edi, esi                                 
  movd xmm7, edi                               
  movdqa xmm6, [ff_pw_4]                       
  pshuflw xmm7, xmm7, 0                        
                                               
  movlhps xmm7, xmm7                           
                                               
$next2yrows:                                   
  movq xmm0, qword ptr[ecx ]                            
  movq xmm1, qword ptr[ecx+edx ]                        
  movdqa xmm2, xmm1                            
  movq xmm3, qword ptr[ecx+edx*2]                       
  lea ecx, [ecx+edx*2]                         
                                               
  punpcklbw xmm0, xmm1                         
                                               
  punpcklbw xmm2, xmm3                         
                                               
  pmaddubsw xmm0, xmm7                         
                                               
  pmaddubsw xmm2, xmm7                         
  movq xmm4, qword ptr[eax ]                            
  movhps xmm4, [eax+edx]                       
                                               
  paddw xmm0, xmm6                             
                                               
  paddw xmm2, xmm6                             
                                               
  psrlw xmm0, 3                                
                                               
  psrlw xmm2, 3                                
                                               
  packuswb xmm0, xmm2                          
                                               
  pavgb xmm0, xmm4                             
  movq qword ptr[eax ], xmm0                            
  movhps [eax+edx], xmm0                       
  sub ebx, 2                                   
  lea eax, [eax+edx*2]                         
  jg $next2yrows                               
  pop ebp                                      
  pop edi                                      
  pop esi                                      
  pop ebx                                      
  ret                                          


	}
}
void __declspec(naked) ff_avg_h264_chroma_mc4_ssse3     (uint8_t *dst, uint8_t *src,int stride, int h, int x, int y)
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
   mov edi, [esp + 16 + 4 + 5*4]                   
                                                   
   mov ebp, esi                                    
   shl esi, 8                                      
   sub esi, ebp                                    
   mov ebp, 8                                      
   add esi, 8                                      
   sub ebp, edi                                    
   imul ebp, esi                                   
   imul esi, edi                                   
                                                   
   movd mm7, ebp                                   
   movd mm6, esi                                   
   movq mm5, [ff_pw_32]                            
   movd mm0, [ecx ]                                
   pshufw mm7, mm7, 0                              
                                                   
   punpcklbw mm0, [ecx+1]                          
   pshufw mm6, mm6, 0                              
                                                   
$next2rows:                                       
   movd mm1, [ecx+edx*1 ]                          
   movd mm3, [ecx+edx*2 ]                          
                                                   
   punpcklbw mm1, [ecx+edx*1+1]                    
                                                   
   punpcklbw mm3, [ecx+edx*2+1]                    
   lea ecx, [ecx+edx*2]                            
   movq mm2, mm1                                   
   movq mm4, mm3                                   
                                                   
   pmaddubsw mm0, mm7                              
                                                   
   pmaddubsw mm1, mm6                              
                                                   
   pmaddubsw mm2, mm7                              
                                                   
   pmaddubsw mm3, mm6                              
                                                   
   paddw mm0, mm5                                  
                                                   
   paddw mm2, mm5                                  
                                                   
   paddw mm1, mm0                                  
                                                   
   paddw mm3, mm2                                  
                                                   
   psrlw mm1, 6                                    
   movq mm0, mm4                                   
                                                   
   psrlw mm3, 6                                    
                                                   
   packuswb mm1, mm1                               
                                                   
   packuswb mm3, mm3                               
                                                   
   pavgb mm1, [eax ]                               
                                                   
   pavgb mm3, [eax+edx]                            
   movd [eax ], mm1                                
   movd [eax+edx], mm3                             
   sub ebx, 2                                      
   lea eax, [eax+edx*2]                            
   jg $next2rows                                   
   pop ebp                                         
   pop edi                                         
   pop esi                                         
   pop ebx                                         
   ret                                             

	}
}

#if SUPPORT_BIT10
void __declspec(naked) ff_put_h264_chroma_mc2_10_mmxext(pixel *dst, pixel *src, int stride, int h, int mx, int my)
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
  mov edi, [esp + 16 + 4 + 5*4]              
                                             
  mov ebp, esi                               
  shl esi, 16                                
  sub esi, ebp                               
  add esi, 8                                 
  imul edi, esi                              
  shl esi, 3                                 
  sub esi, edi                               
                                             
  movd mm5, esi                              
  movd mm6, edi                              
                                             
  punpckldq mm5, mm5                         
                                             
  punpckldq mm6, mm6                         
                                             
  pxor mm7, mm7                              
  pshufw mm2, [ecx], 0x94                    
                                             
$nextrow:                                    
  add ecx, edx                               
  movq mm1, mm2                              
                                             
  pmaddwd mm1, mm5                           
  pshufw mm0, [ecx], 0x94                    
  movq mm2, mm0                              
                                             
  pmaddwd mm0, mm6                           
                                             
  paddw mm1, [ff_pw_32]                      
                                             
  paddw mm1, mm0                             
                                             
  psrlw mm1, 6                               
                                             
  packssdw mm1, mm7                          
  movd [eax], mm1                            
  add eax, edx                               
  dec ebx                                    
  jnz $nextrow                               
  pop ebp                                    
  pop edi                                    
  pop esi                                    
  pop ebx                                    
  ret                                        

	}
}
void __declspec(naked) ff_avg_h264_chroma_mc2_10_mmxext(pixel *dst, pixel *src, int stride, int h, int mx, int my)
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
   mov edi, [esp + 16 + 4 + 5*4]            
                                            
   mov ebp, esi                             
   shl esi, 16                              
   sub esi, ebp                             
   add esi, 8                               
   imul edi, esi                            
   shl esi, 3                               
   sub esi, edi                             
                                            
   movd mm5, esi                            
   movd mm6, edi                            
                                            
   punpckldq mm5, mm5                       
                                            
   punpckldq mm6, mm6                       
                                            
   pxor mm7, mm7                            
   pshufw mm2, [ecx], 0x94                  
                                            
$nextrow:                                  
   add ecx, edx                             
   movq mm1, mm2                            
                                            
   pmaddwd mm1, mm5                         
   pshufw mm0, [ecx], 0x94                  
   movq mm2, mm0                            
                                            
   pmaddwd mm0, mm6                         
                                            
   paddw mm1, [ff_pw_32]                    
                                            
   paddw mm1, mm0                           
                                            
   psrlw mm1, 6                             
                                            
   packssdw mm1, mm7                        
   movq mm3, [eax]                          
                                            
   pavgw mm1, mm3                           
   movd [eax], mm1                          
   add eax, edx                             
   dec ebx                                  
   jnz $nextrow                             
   pop ebp                                  
   pop edi                                  
   pop esi                                  
   pop ebx                                  
   ret                                      
	}
}

void __declspec(naked) ff_put_h264_chroma_mc4_10_mmxext(pixel *dst, pixel *src, int stride, int h, int mx, int my)
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
   mov edi, [esp + 12 + 4 + 5*4]                             
                                                             
   movd mm2, [esp + 12 + 20]                                 
   movd mm3, [esp + 12 + 24]                                 
   movq mm4, [ff_pw_8]                                       
   movq mm5, mm4                                             
   pshufw mm2, mm2, (0)*0x55                                 
   pshufw mm3, mm3, (0)*0x55                                 
                                                             
   psubw mm4, mm2                                            
                                                             
   psubw mm5, mm3                                            
                                                             
   movq mm0, [ecx ]                                          
   movq mm6, [ecx+2]                                         
   add ecx, edx                                              
                                                             
   pmullw mm0, mm4                                           
                                                             
   pmullw mm6, mm2                                           
                                                             
   paddw mm6, mm0                                            
                                                             
$next2rows:                                                 
   movq mm0, [ecx ]                                          
   movq mm1, [ecx+2]                                         
   add ecx, edx                                              
                                                             
   pmullw mm0, mm4                                           
                                                             
   pmullw mm1, mm2                                           
                                                             
   paddw mm1, mm0                                            
   movq mm0, mm1                                             
                                                             
                                                             
   pmullw mm6, mm5                                           
                                                             
   pmullw mm1, mm3                                           
                                                             
   paddw mm6, [ff_pw_32]                                     
                                                             
   paddw mm1, mm6                                            
                                                             
   psrlw mm1, 6                                              
   movq [eax], mm1                                           
   add eax, edx                                              
   movq mm6, [ecx ]                                          
   movq mm1, [ecx+2]                                         
   add ecx, edx                                              
                                                             
   pmullw mm6, mm4                                           
                                                             
   pmullw mm1, mm2                                           
                                                             
   paddw mm1, mm6                                            
   movq mm6, mm1                                             
                                                             
                                                             
   pmullw mm0, mm5                                           
                                                             
   pmullw mm1, mm3                                           
                                                             
   paddw mm0, [ff_pw_32]                                     
                                                             
   paddw mm1, mm0                                            
                                                             
   psrlw mm1, 6                                              
   movq [eax], mm1                                           
   add eax, edx                                              
   sub ebx, 2                                                
   jnz $next2rows                                            
   pop edi                                                   
   pop esi                                                   
   pop ebx                                                   
   ret                                                       

	}
}

void __declspec(naked) ff_avg_h264_chroma_mc4_10_mmxext(pixel *dst, pixel *src, int stride, int h, int mx, int my)
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
   mov edi, [esp + 12 + 4 + 5*4]            
                                            
   movd mm2, [esp + 12 + 20]                
   movd mm3, [esp + 12 + 24]                
   movq mm4, [ff_pw_8]                      
   movq mm5, mm4                            
   pshufw mm2, mm2, (0)*0x55                
   pshufw mm3, mm3, (0)*0x55                
                                            
   psubw mm4, mm2                           
                                            
   psubw mm5, mm3                           
                                            
   movq mm0, [ecx ]                         
   movq mm6, [ecx+2]                        
   add ecx, edx                             
                                            
   pmullw mm0, mm4                          
                                            
   pmullw mm6, mm2                          
                                            
   paddw mm6, mm0                           
                                            
$next2rows:                                
   movq mm0, [ecx ]                         
   movq mm1, [ecx+2]                        
   add ecx, edx                             
                                            
   pmullw mm0, mm4                          
                                            
   pmullw mm1, mm2                          
                                            
   paddw mm1, mm0                           
   movq mm0, mm1                            
                                            
                                            
   pmullw mm6, mm5                          
                                            
   pmullw mm1, mm3                          
                                            
   paddw mm6, [ff_pw_32]                    
                                            
   paddw mm1, mm6                           
                                            
   psrlw mm1, 6                             
   movq mm6, [eax]                          
                                            
   pavgw mm1, mm6                           
   movq [eax], mm1                          
   add eax, edx                             
   movq mm6, [ecx ]                         
   movq mm1, [ecx+2]                        
   add ecx, edx                             
                                            
   pmullw mm6, mm4                          
                                            
   pmullw mm1, mm2                          
                                            
   paddw mm1, mm6                           
   movq mm6, mm1                            
                                            
                                            
   pmullw mm0, mm5                          
                                            
   pmullw mm1, mm3                          
                                            
   paddw mm0, [ff_pw_32]                    
                                            
   paddw mm1, mm0                           
                                            
   psrlw mm1, 6                             
   movq mm0, [eax]                          
                                            
   pavgw mm1, mm0                           
   movq [eax], mm1                          
   add eax, edx                             
   sub ebx, 2                               
   jnz $next2rows                           
   pop edi                                  
   pop esi                                  
   pop ebx                                  
   ret
	}
}
void __declspec(naked) ff_put_h264_chroma_mc8_10_sse2(pixel *dst, pixel *src, int stride, int h, int mx, int my)
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
  mov edi, [esp + 16 + 4 + 5*4]                             
                                                            
  mov ebp, edi                                              
  or ebp, esi                                               
  jne $at_least_one_non_zero                                
                                                            
  lea esi, [edx+edx*2 ]                                         
  lea edi, [edx*4 ]                                         
$next4rows:                                                 
  movdqu xmm0, [ecx ]                                       
  movdqu xmm1, [ecx+edx ]                                   
  movdqa [eax ], xmm0                                       
  movdqa [eax+edx ], xmm1                                   
  movdqu xmm0, [ecx+edx*2]                                  
  movdqu xmm1, [ecx+esi ]                                   
  movdqa [eax+edx*2], xmm0                                  
  movdqa [eax+esi ], xmm1                                   
  add ecx, edi                                              
  add eax, edi                                              
  sub ebx, 4                                                
  jne $next4rows                                            
  pop ebp                                                   
  pop edi                                                   
  pop esi                                                   
  pop ebx                                                   
  ret                                                       
                                                            
$at_least_one_non_zero:                                     
  mov ebp, 2                                                
  test edi, edi                                             
  je $x_interpolation                                       
  mov ebp, edx                                              
  test esi, esi                                             
  jne $xy_interpolation                                     

$x_interpolation:
  or esi, edi                                               
  movd xmm5, esi                                            
  movdqa xmm4, [ff_pw_8]                                    
  movdqa xmm6, [ff_pw_4]                                    
  pshuflw xmm5, xmm5, (0)*0x55                              
                                                            
  punpcklqdq xmm5, xmm5                                     
                                                            
  psubw xmm4, xmm5                                          
                                                            
$next1drow:                                                 
  movdqu xmm0, [ecx ]                                       
  movdqu xmm2, [ecx+ebp]                                    
                                                            
                                                            
  pmullw xmm0, xmm4                                         
                                                            
  pmullw xmm2, xmm5                                         
                                                            
                                                            
  paddw xmm0, xmm6                                          
                                                            
  paddw xmm0, xmm2                                          
                                                            
  psrlw xmm0, 3                                             
  movdqa [eax], xmm0                                        
                                                            
  add eax, edx                                              
  add ecx, edx                                              
  dec ebx                                                   
  jne $next1drow                                            
  pop ebp                                                   
  pop edi                                                   
  pop esi                                                   
  pop ebx                                                   
  ret                                                       
                                                            
$xy_interpolation:                                          
  movd xmm4, [esp + 16 + 20]                                
  movd xmm6, [esp + 16 + 24]                                
                                                            
  pshuflw xmm4, xmm4, (0)*0x55                              
                                                            
  punpcklqdq xmm4, xmm4                                     
  pshuflw xmm6, xmm6, (0)*0x55                              
                                                            
  punpcklqdq xmm6, xmm6                                     
                                                            
  movdqa xmm5, xmm4                                         
  psllw xmm5, 3                                             
                                                            
  pmullw xmm4, xmm6                                         
                                                            
  psllw xmm6, 3                                             
                                                            
  movdqa xmm1, xmm5                                         
  paddw xmm1, xmm6                                          
  movdqa xmm7, xmm4                                         
                                                            
  psubw xmm5, xmm4                                          
                                                            
  psubw xmm6, xmm4                                          
                                                            
  paddw xmm4, [ff_pw_64]                                    
                                                            
  psubw xmm4, xmm1                                          
                                                            
  movdqu xmm0, [ecx ]                                       
  movdqu xmm1, [ecx+2]                                      
$next2drow:                                                 
  add ecx, edx                                              
                                                            
                                                            
  movdqa xmm2, xmm0                                         
  pmullw xmm2, xmm4                                         
                                                            
  pmullw xmm1, xmm5                                         
                                                            
  paddw xmm2, xmm1                                          
                                                            
  movdqu xmm0, [ecx]                                        
  movdqu xmm1, [ecx+2]                                      
                                                            
  movdqa xmm3, xmm0                                         
  pmullw xmm3, xmm6                                         
                                                            
  paddw xmm2, xmm3                                          
                                                            
  movdqa xmm3, xmm1                                         
  pmullw xmm3, xmm7                                         
                                                            
  paddw xmm2, xmm3                                          
                                                            
                                                            
  paddw xmm2, [ff_pw_32]                                    
                                                            
  psrlw xmm2, 6                                             
  movdqa [eax], xmm2                                        
                                                            
  add eax, edx                                              
  dec ebx                                                   
  jne $next2drow                                            
  pop ebp                                                   
  pop edi                                                   
  pop esi                                                   
  pop ebx                                                   
  ret
	}
}
void __declspec(naked) ff_avg_h264_chroma_mc8_10_sse2(pixel *dst, pixel *src, int stride, int h, int mx, int my)
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
   mov edi, [esp + 16 + 4 + 5*4]                        
                                                        
   mov ebp, edi                                         
   or ebp, esi                                          
   jne $at_least_one_non_zero                           
                                                        
   lea esi, [edx+edx*2 ]                                    
   lea edi, [edx*4 ]                                    
$next4rows:                                            
   movdqu xmm0, [ecx ]                                  
   movdqu xmm1, [ecx+edx ]                              
                                                        
   pavgw xmm0, [eax ]                                   
                                                        
   pavgw xmm1, [eax+edx ]                               
   movdqa [eax ], xmm0                                  
   movdqa [eax+edx ], xmm1                              
   movdqu xmm0, [ecx+edx*2]                             
   movdqu xmm1, [ecx+esi ]                              
                                                        
   pavgw xmm0, [eax+edx*2]                              
                                                        
   pavgw xmm1, [eax+esi ]                               
   movdqa [eax+edx*2], xmm0                             
   movdqa [eax+esi ], xmm1                              
   add ecx, edi                                         
   add eax, edi                                         
   sub ebx, 4                                           
   jne $next4rows                                       
   pop ebp                                              
   pop edi                                              
   pop esi                                              
   pop ebx                                              
   ret                                                  
                                                        
$at_least_one_non_zero:                                
   mov ebp, 2                                           
   test edi, edi                                        
   je $x_interpolation                                  
   mov ebp, edx                                         
   test esi, esi                                        
   jne $xy_interpolation                                
$x_interpolation:                                      
                                                        
   or esi, edi                                          
   movd xmm5, esi                                       
   movdqa xmm4, [ff_pw_8]                               
   movdqa xmm6, [ff_pw_4]                               
   pshuflw xmm5, xmm5, (0)*0x55                         
                                                        
   punpcklqdq xmm5, xmm5                                
                                                        
   psubw xmm4, xmm5                                     
                                                        
$next1drow:                                            
   movdqu xmm0, [ecx ]                                  
   movdqu xmm2, [ecx+ebp]                               
                                                        
                                                        
   pmullw xmm0, xmm4                                    
                                                        
   pmullw xmm2, xmm5                                    
                                                        
                                                        
   paddw xmm0, xmm6                                     
                                                        
   paddw xmm0, xmm2                                     
                                                        
   psrlw xmm0, 3                                        
                                                        
   pavgw xmm0, [eax]                                    
   movdqa [eax], xmm0                                   
                                                        
   add eax, edx                                         
   add ecx, edx                                         
   dec ebx                                              
   jne $next1drow                                       
   pop ebp                                              
   pop edi                                              
   pop esi                                              
   pop ebx                                              
   ret                                                  
                                                        
$xy_interpolation:                                     
   movd xmm4, [esp + 16 + 20]                           
   movd xmm6, [esp + 16 + 24]                           
                                                        
   pshuflw xmm4, xmm4, (0)*0x55                         
                                                        
   punpcklqdq xmm4, xmm4                                
   pshuflw xmm6, xmm6, (0)*0x55                         
                                                        
   punpcklqdq xmm6, xmm6                                
                                                        
   movdqa xmm5, xmm4                                    
   psllw xmm5, 3                                        
                                                        
   pmullw xmm4, xmm6                                    
                                                        
   psllw xmm6, 3                                        
                                                        
   movdqa xmm1, xmm5                                    
   paddw xmm1, xmm6                                     
   movdqa xmm7, xmm4                                    
                                                        
   psubw xmm5, xmm4                                     
                                                        
   psubw xmm6, xmm4                                     
                                                        
   paddw xmm4, [ff_pw_64]                               
                                                        
   psubw xmm4, xmm1                                     
                                                        
   movdqu xmm0, [ecx ]                                  
   movdqu xmm1, [ecx+2]                                 
$next2drow:                                            
   add ecx, edx                                         
                                                        
                                                        
   movdqa xmm2, xmm0                                    
   pmullw xmm2, xmm4                                    
                                                        
   pmullw xmm1, xmm5                                    
                                                        
   paddw xmm2, xmm1                                     
                                                        
   movdqu xmm0, [ecx]                                   
   movdqu xmm1, [ecx+2]                                 
                                                        
   movdqa xmm3, xmm0                                    
   pmullw xmm3, xmm6                                    
                                                        
   paddw xmm2, xmm3                                     
                                                        
   movdqa xmm3, xmm1                                    
   pmullw xmm3, xmm7                                    
                                                        
   paddw xmm2, xmm3                                     
                                                        
                                                        
   paddw xmm2, [ff_pw_32]                               
                                                        
   psrlw xmm2, 6                                        
                                                        
   pavgw xmm2, [eax]                                    
   movdqa [eax], xmm2                                   
                                                        
   add eax, edx                                         
   dec ebx                                              
   jne $next2drow                                       
   pop ebp                                              
   pop edi                                              
   pop esi                                              
   pop ebx                                              
   ret                                                  

	}
}
#endif