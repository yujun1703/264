#include "dsputil_mmx.h"

//typedef unsigned char uint8_t;
//typedef char int8_t;
//typedef short int16_t;
//typedef short DCTELEM;

//extern short ff_pw_32[8];
//extern short ff_pw_1[8];
//extern int   pd_32[4];
//extern short   pw_pixel_max[8];
//extern uint8_t scan8_mem[16*3];


void __declspec(naked) ff_h264_idct_add_8_mmx(uint8_t *dst, int16_t *block, int stride)
{
    __asm{
        mov eax, [esp + 0 + 4 + 0*4]                
        mov ecx, [esp + 0 + 4 + 1*4]                
        mov edx, [esp + 0 + 4 + 2*4]                

        movq mm0, [ecx]                             
        movq mm1, [ecx+8]                           
        movq mm2, [ecx+16]                          
        movq mm3, [ecx+24]                          

        movq mm4, mm1                               
            psraw mm4, 1                                

            movq mm5, mm3                               
            psraw mm5, 1                                

            paddw mm5, mm1                              

            psubw mm4, mm3                              

            movq mm3, mm2                               

            paddw mm2, mm0                              

            psubw mm0, mm3                              

            movq mm3, mm5                               

            paddw mm5, mm2                              

            psubw mm2, mm3                              
            movq mm3, mm4                               

            paddw mm4, mm0                              

            psubw mm0, mm3                              

            movq mm6, [ff_pw_32]                        
        movq mm1, mm5                               

            punpcklwd mm5, mm4                          

            punpckhwd mm1, mm4                          
            movq mm4, mm0                               

            punpcklwd mm0, mm2                          

            punpckhwd mm4, mm2                          
            movq mm2, mm5                               

            punpckldq mm5, mm0                          

            punpckhdq mm2, mm0                          
            movq mm0, mm1                               

            punpckldq mm1, mm4                          

            punpckhdq mm0, mm4                          

            paddw mm5, mm6                              

            movq mm4, mm2                               
            psraw mm4, 1                                

            movq mm3, mm0                               
            psraw mm3, 1                                

            paddw mm3, mm2                              

            psubw mm4, mm0                              

            movq mm0, mm1                               

            paddw mm1, mm5                              

            psubw mm5, mm0                              

            movq mm0, mm3                               

            paddw mm3, mm1                              

            psubw mm1, mm0                              
            movq mm0, mm4                               

            paddw mm4, mm5                              

            psubw mm5, mm0                              

            pxor mm7, mm7                               

            movd mm2, [eax]                             
        movd mm0, [eax+edx]                         

        psraw mm3, 6                                

            psraw mm4, 6                                

            punpcklbw mm2, mm7                          

            punpcklbw mm0, mm7                          

            paddw mm2, mm3                              

            paddw mm0, mm4                              

            packuswb mm2, mm7                           

            packuswb mm0, mm7                           
            movd [eax], mm2                             
            movd [eax+edx], mm0                         
            lea eax, [eax+edx*2]                        
        movd mm2, [eax]                             
        movd mm0, [eax+edx]                         

        psraw mm5, 6                                

            psraw mm1, 6                                

            punpcklbw mm2, mm7                          

            punpcklbw mm0, mm7                          

            paddw mm2, mm5                              

            paddw mm0, mm1                              

            packuswb mm2, mm7                           

            packuswb mm0, mm7                           
            movd [eax], mm2                             
            movd [eax+edx], mm0                         

            ret                                         
    }
}



void __declspec(naked) ff_h264_idct_dc_add_8_mmx2(uint8_t *dst, int16_t *block, int stride)
{
    __asm{
        mov eax, [esp + 0 + 4 + 0*4]                    
        mov ecx, [esp + 0 + 4 + 1*4]                    
        mov edx, [esp + 0 + 4 + 2*4]                    

        movsx ecx, word ptr[ecx]                           

        add ecx, 32                                     
            sar ecx, 6                                      
            movd mm0, ecx                                   
            lea ecx, [edx+edx*2]                                
        pshufw mm0, mm0, 0                              

            pxor mm1, mm1                                   

            psubw mm1, mm0                                  

            packuswb mm0, mm0                               

            packuswb mm1, mm1                               

            movd mm2, [eax ]                                

        movd mm3, [eax+edx ]                            
        movd mm4, [eax+edx*2]                           
        movd mm5, [eax+ecx ]                            

        paddusb mm2, mm0                                

            paddusb mm3, mm0                                

            paddusb mm4, mm0                                

            paddusb mm5, mm0                                

            psubusb mm2, mm1                                

            psubusb mm3, mm1                                

            psubusb mm4, mm1                                

            psubusb mm5, mm1                                
            movd [eax ], mm2                                
            movd [eax+edx ], mm3                            
            movd [eax+edx*2], mm4                           
            movd [eax+ecx ], mm5                            

            ret                                             
    }
}


void __declspec(naked) ff_h264_idct8_dc_add_8_mmx2(uint8_t *dst, int16_t *block, int stride)
{
    __asm{
        mov eax, [esp + 0 + 4 + 0*4]                   
        mov ecx, [esp + 0 + 4 + 1*4]                   
        mov edx, [esp + 0 + 4 + 2*4]                   

        movsx ecx, word ptr[ecx]                          

        add ecx, 32                                    
            sar ecx, 6                                     
            movd mm0, ecx                                  
            lea ecx, [edx+edx*2]                               
        pshufw mm0, mm0, 0                             

            pxor mm1, mm1                                  

            psubw mm1, mm0                                 

            packuswb mm0, mm0                              

            packuswb mm1, mm1                              

            movq mm2, [eax ]                               

        movq mm3, [eax+edx ]                           
        movq mm4, [eax+edx*2]                          
        movq mm5, [eax+ecx ]                           

        paddusb mm2, mm0                               

            paddusb mm3, mm0                               

            paddusb mm4, mm0                               

            paddusb mm5, mm0                               

            psubusb mm2, mm1                               

            psubusb mm3, mm1                               

            psubusb mm4, mm1                               

            psubusb mm5, mm1                               
            movq [eax ], mm2                               
            movq [eax+edx ], mm3                           
            movq [eax+edx*2], mm4                          
            movq [eax+ecx ], mm5                           

            lea eax, [eax+edx*4]                           
        movq mm2, [eax ]                               

        movq mm3, [eax+edx ]                           
        movq mm4, [eax+edx*2]                          
        movq mm5, [eax+ecx ]                           

        paddusb mm2, mm0                               

            paddusb mm3, mm0                               

            paddusb mm4, mm0                               

            paddusb mm5, mm0                               

            psubusb mm2, mm1                               

            psubusb mm3, mm1                               

            psubusb mm4, mm1                               

            psubusb mm5, mm1                               
            movq [eax ], mm2                               
            movq [eax+edx ], mm3                           
            movq [eax+edx*2], mm4                          
            movq [eax+ecx ], mm5                           

            ret
    }
}


void __declspec(naked) ff_h264_idct8_add_8_mmx(uint8_t *dst, int16_t *block, int stride)
{
    __asm{
        push ebx                                  
            mov eax, [esp + 4 + 4 + 0*4]              
        mov ecx, [esp + 4 + 4 + 1*4]              
        mov edx, [esp + 4 + 4 + 2*4]              

        add esp, -128                             

            add word ptr[ecx], 32                        
            movq mm7, [ecx+112]                       

        movq mm6, [ecx+ 96]                       
        movq mm5, [ecx+ 80]                       
        movq mm3, [ecx+ 48]                       
        movq mm2, [ecx+ 32]                       
        movq mm1, [ecx+ 16]                       
        movq mm0, mm1                             

            psraw mm1, 1                              
            movq mm4, mm5                             

            psraw mm4, 1                              

            paddw mm4, mm5                            

            paddw mm1, mm0                            

            paddw mm4, mm7                            

            paddw mm1, mm5                            

            psubw mm4, mm0                            

            paddw mm1, mm3                            


            psubw mm0, mm3                            

            psubw mm5, mm3                            

            psraw mm3, 1                              

            paddw mm0, mm7                            

            psubw mm5, mm7                            

            psraw mm7, 1                              

            psubw mm0, mm3                            

            psubw mm5, mm7                            

            movq mm7, mm1                             

            psraw mm1, 2                              
            movq mm3, mm4                             

            psraw mm3, 2                              

            paddw mm3, mm0                            

            psraw mm0, 2                              

            paddw mm1, mm5                            

            psraw mm5, 2                              

            psubw mm0, mm4                            

            psubw mm7, mm5                            

            movq mm5, mm6                             

            psraw mm6, 1                              
            movq mm4, mm2                             

            psraw mm4, 1                              

            paddw mm6, mm2                            

            psubw mm4, mm5                            

            movq mm2, [ecx]                           
        movq mm5, [ecx+ 64]                       

        paddw mm5, mm2                            

            paddw mm2, mm2                            

            psubw mm2, mm5                            

            paddw mm6, mm5                            

            paddw mm5, mm5                            

            psubw mm5, mm6                            

            paddw mm4, mm2                            

            paddw mm2, mm2                            

            psubw mm2, mm4                            

            paddw mm7, mm6                            

            paddw mm6, mm6                            

            psubw mm6, mm7                            

            paddw mm0, mm4                            

            paddw mm4, mm4                            

            psubw mm4, mm0                            

            paddw mm3, mm2                            

            paddw mm2, mm2                            

            psubw mm2, mm3                            

            paddw mm1, mm5                            

            paddw mm5, mm5                            

            psubw mm5, mm1                            
            movq [ecx], mm6                           
            movq mm6, mm7                             

            punpcklwd mm7, mm0                        

            punpckhwd mm6, mm0                        
            movq mm0, mm3                             

            punpcklwd mm3, mm1                        

            punpckhwd mm0, mm1                        
            movq mm1, mm7                             

            punpckldq mm7, mm3                        

            punpckhdq mm1, mm3                        
            movq mm3, mm6                             

            punpckldq mm6, mm0                        

            punpckhdq mm3, mm0                        
            movq mm0, [ecx]                           
        movq [esp ], mm7                          
            movq [esp+16], mm1                        
            movq [esp+32], mm6                        
            movq [esp+48], mm3                        
            movq mm3, mm5                             

            punpcklwd mm5, mm2                        

            punpckhwd mm3, mm2                        
            movq mm2, mm4                             

            punpcklwd mm4, mm0                        

            punpckhwd mm2, mm0                        
            movq mm0, mm5                             

            punpckldq mm5, mm4                        

            punpckhdq mm0, mm4                        
            movq mm4, mm3                             

            punpckldq mm3, mm2                        

            punpckhdq mm4, mm2                        
            movq [esp+ 8], mm5                        
            movq [esp+24], mm0                        
            movq [esp+40], mm3                        
            movq [esp+56], mm4                        

            movq mm4, [ecx+8+112]                     

        movq mm3, [ecx+8+ 96]                     
        movq mm0, [ecx+8+ 80]                     
        movq mm2, [ecx+8+ 48]                     
        movq mm6, [ecx+8+ 32]                     
        movq mm1, [ecx+8+ 16]                     
        movq mm7, mm1                             

            psraw mm1, 1                              
            movq mm5, mm0                             

            psraw mm5, 1                              

            paddw mm5, mm0                            

            paddw mm1, mm7                            

            paddw mm5, mm4                            

            paddw mm1, mm0                            

            psubw mm5, mm7                            

            paddw mm1, mm2                            


            psubw mm7, mm2                            

            psubw mm0, mm2                            

            psraw mm2, 1                              

            paddw mm7, mm4                            

            psubw mm0, mm4                            

            psraw mm4, 1                              

            psubw mm7, mm2                            

            psubw mm0, mm4                            

            movq mm4, mm1                             

            psraw mm1, 2                              
            movq mm2, mm5                             

            psraw mm2, 2                              

            paddw mm2, mm7                            

            psraw mm7, 2                              

            paddw mm1, mm0                            

            psraw mm0, 2                              

            psubw mm7, mm5                            

            psubw mm4, mm0                            

            movq mm0, mm3                             

            psraw mm3, 1                              
            movq mm5, mm6                             

            psraw mm5, 1                              

            paddw mm3, mm6                            

            psubw mm5, mm0                            

            movq mm6, [ecx+8]                         
        movq mm0, [ecx+8+ 64]                     

        paddw mm0, mm6                            

            paddw mm6, mm6                            

            psubw mm6, mm0                            

            paddw mm3, mm0                            

            paddw mm0, mm0                            

            psubw mm0, mm3                            

            paddw mm5, mm6                            

            paddw mm6, mm6                            

            psubw mm6, mm5                            

            paddw mm4, mm3                            

            paddw mm3, mm3                            

            psubw mm3, mm4                            

            paddw mm7, mm5                            

            paddw mm5, mm5                            

            psubw mm5, mm7                            

            paddw mm2, mm6                            

            paddw mm6, mm6                            

            psubw mm6, mm2                            

            paddw mm1, mm0                            

            paddw mm0, mm0                            

            psubw mm0, mm1                            
            movq [ecx+8], mm3                         
            movq mm3, mm4                             

            punpcklwd mm4, mm7                        

            punpckhwd mm3, mm7                        
            movq mm7, mm2                             

            punpcklwd mm2, mm1                        

            punpckhwd mm7, mm1                        
            movq mm1, mm4                             

            punpckldq mm4, mm2                        

            punpckhdq mm1, mm2                        
            movq mm2, mm3                             

            punpckldq mm3, mm7                        

            punpckhdq mm2, mm7                        
            movq mm7, [ecx+8]                         
        movq [esp+64 ], mm4                       
            movq [esp+64+16], mm1                     
            movq [esp+64+32], mm3                     
            movq [esp+64+48], mm2                     
            movq mm2, mm0                             

            punpcklwd mm0, mm6                        

            punpckhwd mm2, mm6                        
            movq mm6, mm5                             

            punpcklwd mm5, mm7                        

            punpckhwd mm6, mm7                        
            movq mm7, mm0                             

            punpckldq mm0, mm5                        

            punpckhdq mm7, mm5                        
            movq mm5, mm2                             

            punpckldq mm2, mm6                        

            punpckhdq mm5, mm6                        
            movq [esp+64+ 8], mm0                     
            movq [esp+64+24], mm7                     
            movq [esp+64+40], mm2                     
            movq [esp+64+56], mm5                     

            lea ebx, [eax+4]                          
        movq mm5, [esp+112]                       

        movq mm2, [esp+ 96]                       
        movq mm7, [esp+ 80]                       
        movq mm6, [esp+ 48]                       
        movq mm3, [esp+ 32]                       
        movq mm1, [esp+ 16]                       
        movq mm4, mm1                             

            psraw mm1, 1                              
            movq mm0, mm7                             

            psraw mm0, 1                              

            paddw mm0, mm7                            

            paddw mm1, mm4                            

            paddw mm0, mm5                            

            paddw mm1, mm7                            

            psubw mm0, mm4                            

            paddw mm1, mm6                            


            psubw mm4, mm6                            

            psubw mm7, mm6                            

            psraw mm6, 1                              

            paddw mm4, mm5                            

            psubw mm7, mm5                            

            psraw mm5, 1                              

            psubw mm4, mm6                            

            psubw mm7, mm5                            

            movq mm5, mm1                             

            psraw mm1, 2                              
            movq mm6, mm0                             

            psraw mm6, 2                              

            paddw mm6, mm4                            

            psraw mm4, 2                              

            paddw mm1, mm7                            

            psraw mm7, 2                              

            psubw mm4, mm0                            

            psubw mm5, mm7                            

            movq mm7, mm2                             

            psraw mm2, 1                              
            movq mm0, mm3                             

            psraw mm0, 1                              

            paddw mm2, mm3                            

            psubw mm0, mm7                            

            movq mm3, [esp]                           
        movq mm7, [esp+ 64]                       

        paddw mm7, mm3                            

            paddw mm3, mm3                            

            psubw mm3, mm7                            

            paddw mm2, mm7                            

            paddw mm7, mm7                            

            psubw mm7, mm2                            

            paddw mm0, mm3                            

            paddw mm3, mm3                            

            psubw mm3, mm0                            

            paddw mm5, mm2                            

            paddw mm2, mm2                            

            psubw mm2, mm5                            

            paddw mm4, mm0                            

            paddw mm0, mm0                            

            psubw mm0, mm4                            

            paddw mm6, mm3                            

            paddw mm3, mm3                            

            psubw mm3, mm6                            

            paddw mm1, mm7                            

            paddw mm7, mm7                            

            psubw mm7, mm1                            
            movq [esp ], mm3                          
            movq [esp+16], mm0                        
            movq [esp+32], mm2                        


            pxor mm2, mm2                             
            movd mm3, [eax]                           
        movd mm0, [eax+edx]                       

        psraw mm5, 6                              

            psraw mm4, 6                              

            punpcklbw mm3, mm2                        

            punpcklbw mm0, mm2                        

            paddw mm3, mm5                            

            paddw mm0, mm4                            

            packuswb mm3, mm2                         

            packuswb mm0, mm2                         
            movd [eax], mm3                           
            movd [eax+edx], mm0                       
            lea eax, [eax+edx*2]                      
        movd mm3, [eax]                           
        movd mm0, [eax+edx]                       

        psraw mm6, 6                              

            psraw mm1, 6                              

            punpcklbw mm3, mm2                        

            punpcklbw mm0, mm2                        

            paddw mm3, mm6                            

            paddw mm0, mm1                            

            packuswb mm3, mm2                         

            packuswb mm0, mm2                         
            movd [eax], mm3                           
            movd [eax+edx], mm0                       
            movq mm5, [esp ]                          
        movq mm4, [esp+16]                        
        movq mm6, [esp+32]                        
        lea eax, [eax+edx*2]                      
        movd mm3, [eax]                           
        movd mm0, [eax+edx]                       

        psraw mm7, 6                              

            psraw mm5, 6                              

            punpcklbw mm3, mm2                        

            punpcklbw mm0, mm2                        

            paddw mm3, mm7                            

            paddw mm0, mm5                            

            packuswb mm3, mm2                         

            packuswb mm0, mm2                         
            movd [eax], mm3                           
            movd [eax+edx], mm0                       
            lea eax, [eax+edx*2]                      
        movd mm3, [eax]                           
        movd mm0, [eax+edx]                       

        psraw mm4, 6                              

            psraw mm6, 6                              

            punpcklbw mm3, mm2                        

            punpcklbw mm0, mm2                        

            paddw mm3, mm4                            

            paddw mm0, mm6                            

            packuswb mm3, mm2                         

            packuswb mm0, mm2                         
            movd [eax], mm3                           
            movd [eax+edx], mm0                       

            movq mm2, [esp+8+112]                     

        movq mm0, [esp+8+ 96]                     
        movq mm3, [esp+8+ 80]                     
        movq mm1, [esp+8+ 48]                     
        movq mm6, [esp+8+ 32]                     
        movq mm4, [esp+8+ 16]                     
        movq mm5, mm4                             

            psraw mm4, 1                              
            movq mm7, mm3                             

            psraw mm7, 1                              

            paddw mm7, mm3                            

            paddw mm4, mm5                            

            paddw mm7, mm2                            

            paddw mm4, mm3                            

            psubw mm7, mm5                            

            paddw mm4, mm1                            


            psubw mm5, mm1                            

            psubw mm3, mm1                            

            psraw mm1, 1                              

            paddw mm5, mm2                            

            psubw mm3, mm2                            

            psraw mm2, 1                              

            psubw mm5, mm1                            

            psubw mm3, mm2                            

            movq mm2, mm4                             

            psraw mm4, 2                              
            movq mm1, mm7                             

            psraw mm1, 2                              

            paddw mm1, mm5                            

            psraw mm5, 2                              

            paddw mm4, mm3                            

            psraw mm3, 2                              

            psubw mm5, mm7                            

            psubw mm2, mm3                            

            movq mm3, mm0                             

            psraw mm0, 1                              
            movq mm7, mm6                             

            psraw mm7, 1                              

            paddw mm0, mm6                            

            psubw mm7, mm3                            

            movq mm6, [esp+8]                         
        movq mm3, [esp+8+ 64]                     

        paddw mm3, mm6                            

            paddw mm6, mm6                            

            psubw mm6, mm3                            

            paddw mm0, mm3                            

            paddw mm3, mm3                            

            psubw mm3, mm0                            

            paddw mm7, mm6                            

            paddw mm6, mm6                            

            psubw mm6, mm7                            

            paddw mm2, mm0                            

            paddw mm0, mm0                            

            psubw mm0, mm2                            

            paddw mm5, mm7                            

            paddw mm7, mm7                            

            psubw mm7, mm5                            

            paddw mm1, mm6                            

            paddw mm6, mm6                            

            psubw mm6, mm1                            

            paddw mm4, mm3                            

            paddw mm3, mm3                            

            psubw mm3, mm4                            
            movq [esp+8 ], mm6                        
            movq [esp+8+16], mm7                      
            movq [esp+8+32], mm0                      


            pxor mm0, mm0                             
            movd mm6, [ebx]                           
        movd mm7, [ebx+edx]                       

        psraw mm2, 6                              

            psraw mm5, 6                              

            punpcklbw mm6, mm0                        

            punpcklbw mm7, mm0                        

            paddw mm6, mm2                            

            paddw mm7, mm5                            

            packuswb mm6, mm0                         

            packuswb mm7, mm0                         
            movd [ebx], mm6                           
            movd [ebx+edx], mm7                       
            lea ebx, [ebx+edx*2]                      
        movd mm6, [ebx]                           
        movd mm7, [ebx+edx]                       

        psraw mm1, 6                              

            psraw mm4, 6                              

            punpcklbw mm6, mm0                        

            punpcklbw mm7, mm0                        

            paddw mm6, mm1                            

            paddw mm7, mm4                            

            packuswb mm6, mm0                         

            packuswb mm7, mm0                         
            movd [ebx], mm6                           
            movd [ebx+edx], mm7                       
            movq mm2, [esp+8 ]                        
        movq mm5, [esp+8+16]                      
        movq mm1, [esp+8+32]                      
        lea ebx, [ebx+edx*2]                      
        movd mm6, [ebx]                           
        movd mm7, [ebx+edx]                       

        psraw mm3, 6                              

            psraw mm2, 6                              

            punpcklbw mm6, mm0                        

            punpcklbw mm7, mm0                        

            paddw mm6, mm3                            

            paddw mm7, mm2                            

            packuswb mm6, mm0                         

            packuswb mm7, mm0                         
            movd [ebx], mm6                           
            movd [ebx+edx], mm7                       
            lea ebx, [ebx+edx*2]                      
        movd mm6, [ebx]                           
        movd mm7, [ebx+edx]                       

        psraw mm5, 6                              

            psraw mm1, 6                              

            punpcklbw mm6, mm0                        

            punpcklbw mm7, mm0                        

            paddw mm6, mm5                            

            paddw mm7, mm1                            

            packuswb mm6, mm0                         

            packuswb mm7, mm0                         
            movd [ebx], mm6                           
            movd [ebx+edx], mm7                       


            sub esp, -128                             
            pop ebx                                   

            ret                                       

    }
}

void __declspec(naked) ff_h264_idct8_add_8_sse2(uint8_t *dst, int16_t *block, int stride)
{
    __asm{
        push ebx                                   
            mov eax, [esp + 4 + 4 + 0*4]               
        mov ecx, [esp + 4 + 4 + 1*4]               
        mov edx, [esp + 4 + 4 + 2*4]               


        movdqa xmm7, [ecx+112]                     

        movdqa xmm6, [ecx+ 96]                     
        movdqa xmm5, [ecx+ 80]                     
        movdqa xmm3, [ecx+ 48]                     
        movdqa xmm2, [ecx+ 32]                     
        movdqa xmm1, [ecx+ 16]                     
        movdqa xmm0, xmm1                          

            psraw xmm1, 1                              
            movdqa xmm4, xmm5                          

            psraw xmm4, 1                              

            paddw xmm4, xmm5                           

            paddw xmm1, xmm0                           

            paddw xmm4, xmm7                           

            paddw xmm1, xmm5                           

            psubw xmm4, xmm0                           

            paddw xmm1, xmm3                           


            psubw xmm0, xmm3                           

            psubw xmm5, xmm3                           

            psraw xmm3, 1                              

            paddw xmm0, xmm7                           

            psubw xmm5, xmm7                           

            psraw xmm7, 1                              

            psubw xmm0, xmm3                           

            psubw xmm5, xmm7                           

            movdqa xmm7, xmm1                          

            psraw xmm1, 2                              
            movdqa xmm3, xmm4                          

            psraw xmm3, 2                              

            paddw xmm3, xmm0                           

            psraw xmm0, 2                              

            paddw xmm1, xmm5                           

            psraw xmm5, 2                              

            psubw xmm0, xmm4                           

            psubw xmm7, xmm5                           

            movdqa xmm5, xmm6                          

            psraw xmm6, 1                              
            movdqa xmm4, xmm2                          

            psraw xmm4, 1                              

            paddw xmm6, xmm2                           

            psubw xmm4, xmm5                           

            movdqa xmm2, [ecx]                         
        movdqa xmm5, [ecx+ 64]                     

        paddw xmm5, xmm2                           

            paddw xmm2, xmm2                           

            psubw xmm2, xmm5                           

            paddw xmm6, xmm5                           

            paddw xmm5, xmm5                           

            psubw xmm5, xmm6                           

            paddw xmm4, xmm2                           

            paddw xmm2, xmm2                           

            psubw xmm2, xmm4                           

            paddw xmm7, xmm6                           

            paddw xmm6, xmm6                           

            psubw xmm6, xmm7                           

            paddw xmm0, xmm4                           

            paddw xmm4, xmm4                           

            psubw xmm4, xmm0                           

            paddw xmm3, xmm2                           

            paddw xmm2, xmm2                           

            psubw xmm2, xmm3                           

            paddw xmm1, xmm5                           

            paddw xmm5, xmm5                           

            psubw xmm5, xmm1                           



            movdqa [ecx], xmm4                         
            movdqa xmm4, xmm7                          

            punpcklwd xmm7, xmm0                       

            punpckhwd xmm4, xmm0                       
            movdqa [ecx+16], xmm4                      
            movdqa xmm0, [ecx]                         
        movdqa xmm4, xmm3                          

            punpcklwd xmm3, xmm1                       

            punpckhwd xmm4, xmm1                       
            movdqa xmm1, xmm5                          

            punpcklwd xmm5, xmm2                       

            punpckhwd xmm1, xmm2                       
            movdqa xmm2, xmm0                          

            punpcklwd xmm0, xmm6                       

            punpckhwd xmm2, xmm6                       
            movdqa xmm6, xmm7                          

            punpckldq xmm7, xmm3                       

            punpckhdq xmm6, xmm3                       
            movdqa [ecx], xmm6                         
            movdqa xmm3, [ecx+16]                      
        movdqa xmm6, xmm3                          

            punpckldq xmm3, xmm4                       

            punpckhdq xmm6, xmm4                       
            movdqa xmm4, xmm5                          

            punpckldq xmm5, xmm0                       

            punpckhdq xmm4, xmm0                       
            movdqa xmm0, xmm1                          

            punpckldq xmm1, xmm2                       

            punpckhdq xmm0, xmm2                       
            movdqa xmm2, xmm7                          

            punpcklqdq xmm7, xmm5                      

            punpckhqdq xmm2, xmm5                      
            movdqa xmm5, xmm3                          

            punpcklqdq xmm3, xmm1                      

            punpckhqdq xmm5, xmm1                      
            movdqa [ecx+16], xmm3                      
            movdqa xmm1, [ecx]                         
        movdqa xmm3, xmm1                          

            punpcklqdq xmm1, xmm4                      

            punpckhqdq xmm3, xmm4                      
            movdqa xmm4, xmm6                          

            punpcklqdq xmm6, xmm0                      

            punpckhqdq xmm4, xmm0                      
            movdqa xmm0, [ecx+16]                      

        paddw xmm7, [ff_pw_32]                     

        movdqa [ecx ], xmm7                        
            movdqa [ecx+16], xmm0                      
            movdqa xmm7, xmm2                          

            psraw xmm2, 1                              
            movdqa xmm0, xmm5                          

            psraw xmm0, 1                              

            paddw xmm0, xmm5                           

            paddw xmm2, xmm7                           

            paddw xmm0, xmm4                           

            paddw xmm2, xmm5                           

            psubw xmm0, xmm7                           

            paddw xmm2, xmm3                           


            psubw xmm7, xmm3                           

            psubw xmm5, xmm3                           

            psraw xmm3, 1                              

            paddw xmm7, xmm4                           

            psubw xmm5, xmm4                           

            psraw xmm4, 1                              

            psubw xmm7, xmm3                           

            psubw xmm5, xmm4                           

            movdqa xmm4, xmm2                          

            psraw xmm2, 2                              
            movdqa xmm3, xmm0                          

            psraw xmm3, 2                              

            paddw xmm3, xmm7                           

            psraw xmm7, 2                              

            paddw xmm2, xmm5                           

            psraw xmm5, 2                              

            psubw xmm7, xmm0                           

            psubw xmm4, xmm5                           

            movdqa xmm5, xmm6                          

            psraw xmm6, 1                              
            movdqa xmm0, xmm1                          

            psraw xmm0, 1                              

            paddw xmm6, xmm1                           

            psubw xmm0, xmm5                           

            movdqa xmm1, [ecx]                         
        movdqa xmm5, [ecx+ 16]                     

        paddw xmm5, xmm1                           

            paddw xmm1, xmm1                           

            psubw xmm1, xmm5                           

            paddw xmm6, xmm5                           

            paddw xmm5, xmm5                           

            psubw xmm5, xmm6                           

            paddw xmm0, xmm1                           

            paddw xmm1, xmm1                           

            psubw xmm1, xmm0                           

            paddw xmm4, xmm6                           

            paddw xmm6, xmm6                           

            psubw xmm6, xmm4                           

            paddw xmm7, xmm0                           

            paddw xmm0, xmm0                           

            psubw xmm0, xmm7                           

            paddw xmm3, xmm1                           

            paddw xmm1, xmm1                           

            psubw xmm1, xmm3                           

            paddw xmm2, xmm5                           

            paddw xmm5, xmm5                           

            psubw xmm5, xmm2                           
            movdqa [ecx ], xmm0                        
            movdqa [ecx+16], xmm6                      


            pxor xmm6, xmm6                            
            lea ebx, [edx+edx*2]                           
        movq xmm0, qword ptr[eax ]                          

        punpcklbw xmm0, xmm6                       

            psraw xmm4, 6                              

            paddsw xmm4, xmm0                          

            packuswb xmm4, xmm4                        
            movq qword ptr[eax ], xmm4                          
            movq xmm0, qword ptr[eax+edx ]                      

        punpcklbw xmm0, xmm6                       

            psraw xmm7, 6                              

            paddsw xmm7, xmm0                          

            packuswb xmm7, xmm7                        
            movq qword ptr[eax+edx ], xmm7                      
            movq xmm0,qword ptr [eax+edx*2]                     

        punpcklbw xmm0, xmm6                       

            psraw xmm3, 6                              

            paddsw xmm3, xmm0                          

            packuswb xmm3, xmm3                        
            movq qword ptr[eax+edx*2], xmm3                     
            movq xmm0, qword ptr[eax+ebx ]                      

        punpcklbw xmm0, xmm6                       

            psraw xmm2, 6                              

            paddsw xmm2, xmm0                          

            packuswb xmm2, xmm2                        
            movq qword ptr[eax+ebx ], xmm2                      
            movdqa xmm4, [ecx ]                        
        movdqa xmm7, [ecx+16]                      
        lea eax, [eax+edx*4]                       
        movq xmm0,qword ptr [eax ]                          

        punpcklbw xmm0, xmm6                       

            psraw xmm5, 6                              

            paddsw xmm5, xmm0                          

            packuswb xmm5, xmm5                        
            movq qword ptr[eax ], xmm5                          
            movq xmm0,qword ptr [eax+edx ]                      

        punpcklbw xmm0, xmm6                       

            psraw xmm1, 6                              

            paddsw xmm1, xmm0                          

            packuswb xmm1, xmm1                        
            movq qword ptr[eax+edx ], xmm1                      
            movq xmm0, qword ptr[eax+edx*2]                     

        punpcklbw xmm0, xmm6                       

            psraw xmm4, 6                              

            paddsw xmm4, xmm0                          

            packuswb xmm4, xmm4                        
            movq qword ptr[eax+edx*2], xmm4                     
            movq xmm0, qword ptr[eax+ebx ]                      

        punpcklbw xmm0, xmm6                       

            psraw xmm7, 6                              

            paddsw xmm7, xmm0                          

            packuswb xmm7, xmm7                        
            movq qword ptr[eax+ebx ], xmm7                      

            pop ebx                                    

            ret
    }
}

void __declspec(naked) ff_h264_idct8_add4_8_mmx(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        sub esp, 132                               

            xor edi, edi                               

ff_h264_idct8_add4_8_mmxnextblock:
        movzx ebp, byte ptr[scan8_mem+edi]            
        movzx ebp, byte ptr[esi+ebp]                  
        test ebp, ebp                              
            jz ff_h264_idct8_add4_8_mmxnextskipblock                              
            mov ebp, dword ptr[ecx+edi*4]                 
        add ebp, eax                               
            add word ptr[edx], 32                         
            movq mm7, [edx+112]                        

        movq mm6, [edx+ 96]                        
        movq mm5, [edx+ 80]                        
        movq mm3, [edx+ 48]                        
        movq mm2, [edx+ 32]                        
        movq mm1, [edx+ 16]                        
        movq mm0, mm1                              

            psraw mm1, 1                               
            movq mm4, mm5                              

            psraw mm4, 1                               

            paddw mm4, mm5                             

            paddw mm1, mm0                             

            paddw mm4, mm7                             

            paddw mm1, mm5                             

            psubw mm4, mm0                             

            paddw mm1, mm3                             


            psubw mm0, mm3                             

            psubw mm5, mm3                             

            psraw mm3, 1                               

            paddw mm0, mm7                             

            psubw mm5, mm7                             

            psraw mm7, 1                               

            psubw mm0, mm3                             

            psubw mm5, mm7                             

            movq mm7, mm1                              

            psraw mm1, 2                               
            movq mm3, mm4                              

            psraw mm3, 2                               

            paddw mm3, mm0                             

            psraw mm0, 2                               

            paddw mm1, mm5                             

            psraw mm5, 2                               

            psubw mm0, mm4                             

            psubw mm7, mm5                             

            movq mm5, mm6                              

            psraw mm6, 1                               
            movq mm4, mm2                              

            psraw mm4, 1                               

            paddw mm6, mm2                             

            psubw mm4, mm5                             

            movq mm2, [edx]                            
        movq mm5, [edx+ 64]                        

        paddw mm5, mm2                             

            paddw mm2, mm2                             

            psubw mm2, mm5                             

            paddw mm6, mm5                             

            paddw mm5, mm5                             

            psubw mm5, mm6                             

            paddw mm4, mm2                             

            paddw mm2, mm2                             

            psubw mm2, mm4                             

            paddw mm7, mm6                             

            paddw mm6, mm6                             

            psubw mm6, mm7                             

            paddw mm0, mm4                             

            paddw mm4, mm4                             

            psubw mm4, mm0                             

            paddw mm3, mm2                             

            paddw mm2, mm2                             

            psubw mm2, mm3                             

            paddw mm1, mm5                             

            paddw mm5, mm5                             

            psubw mm5, mm1                             
            movq [edx], mm6                            
            movq mm6, mm7                              

            punpcklwd mm7, mm0                         

            punpckhwd mm6, mm0                         
            movq mm0, mm3                              

            punpcklwd mm3, mm1                         

            punpckhwd mm0, mm1                         
            movq mm1, mm7                              

            punpckldq mm7, mm3                         

            punpckhdq mm1, mm3                         
            movq mm3, mm6                              

            punpckldq mm6, mm0                         

            punpckhdq mm3, mm0                         
            movq mm0, [edx]                            
        movq [esp ], mm7                           
            movq [esp+16], mm1                         
            movq [esp+32], mm6                         
            movq [esp+48], mm3                         
            movq mm3, mm5                              

            punpcklwd mm5, mm2                         

            punpckhwd mm3, mm2                         
            movq mm2, mm4                              

            punpcklwd mm4, mm0                         

            punpckhwd mm2, mm0                         
            movq mm0, mm5                              

            punpckldq mm5, mm4                         

            punpckhdq mm0, mm4                         
            movq mm4, mm3                              

            punpckldq mm3, mm2                         

            punpckhdq mm4, mm2                         
            movq [esp+ 8], mm5                         
            movq [esp+24], mm0                         
            movq [esp+40], mm3                         
            movq [esp+56], mm4                         

            movq mm4, [edx+8+112]                      

        movq mm3, [edx+8+ 96]                      
        movq mm0, [edx+8+ 80]                      
        movq mm2, [edx+8+ 48]                      
        movq mm6, [edx+8+ 32]                      
        movq mm1, [edx+8+ 16]                      
        movq mm7, mm1                              

            psraw mm1, 1                               
            movq mm5, mm0                              

            psraw mm5, 1                               

            paddw mm5, mm0                             

            paddw mm1, mm7                             

            paddw mm5, mm4                             

            paddw mm1, mm0                             

            psubw mm5, mm7                             

            paddw mm1, mm2                             


            psubw mm7, mm2                             

            psubw mm0, mm2                             

            psraw mm2, 1                               

            paddw mm7, mm4                             

            psubw mm0, mm4                             

            psraw mm4, 1                               

            psubw mm7, mm2                             

            psubw mm0, mm4                             

            movq mm4, mm1                              

            psraw mm1, 2                               
            movq mm2, mm5                              

            psraw mm2, 2                               

            paddw mm2, mm7                             

            psraw mm7, 2                               

            paddw mm1, mm0                             

            psraw mm0, 2                               

            psubw mm7, mm5                             

            psubw mm4, mm0                             

            movq mm0, mm3                              

            psraw mm3, 1                               
            movq mm5, mm6                              

            psraw mm5, 1                               

            paddw mm3, mm6                             

            psubw mm5, mm0                             

            movq mm6, [edx+8]                          
        movq mm0, [edx+8+ 64]                      

        paddw mm0, mm6                             

            paddw mm6, mm6                             

            psubw mm6, mm0                             

            paddw mm3, mm0                             

            paddw mm0, mm0                             

            psubw mm0, mm3                             

            paddw mm5, mm6                             

            paddw mm6, mm6                             

            psubw mm6, mm5                             

            paddw mm4, mm3                             

            paddw mm3, mm3                             

            psubw mm3, mm4                             

            paddw mm7, mm5                             

            paddw mm5, mm5                             

            psubw mm5, mm7                             

            paddw mm2, mm6                             

            paddw mm6, mm6                             

            psubw mm6, mm2                             

            paddw mm1, mm0                             

            paddw mm0, mm0                             

            psubw mm0, mm1                             
            movq [edx+8], mm3                          
            movq mm3, mm4                              

            punpcklwd mm4, mm7                         

            punpckhwd mm3, mm7                         
            movq mm7, mm2                              

            punpcklwd mm2, mm1                         

            punpckhwd mm7, mm1                         
            movq mm1, mm4                              

            punpckldq mm4, mm2                         

            punpckhdq mm1, mm2                         
            movq mm2, mm3                              

            punpckldq mm3, mm7                         

            punpckhdq mm2, mm7                         
            movq mm7, [edx+8]                          
        movq [esp+64 ], mm4                        
            movq [esp+64+16], mm1                      
            movq [esp+64+32], mm3                      
            movq [esp+64+48], mm2                      
            movq mm2, mm0                              

            punpcklwd mm0, mm6                         

            punpckhwd mm2, mm6                         
            movq mm6, mm5                              

            punpcklwd mm5, mm7                         

            punpckhwd mm6, mm7                         
            movq mm7, mm0                              

            punpckldq mm0, mm5                         

            punpckhdq mm7, mm5                         
            movq mm5, mm2                              

            punpckldq mm2, mm6                         

            punpckhdq mm5, mm6                         
            movq [esp+64+ 8], mm0                      
            movq [esp+64+24], mm7                      
            movq [esp+64+40], mm2                      
            movq [esp+64+56], mm5                      

            movq mm5, [esp+112]                        

        movq mm2, [esp+ 96]                        
        movq mm7, [esp+ 80]                        
        movq mm6, [esp+ 48]                        
        movq mm3, [esp+ 32]                        
        movq mm1, [esp+ 16]                        
        movq mm4, mm1                              

            psraw mm1, 1                               
            movq mm0, mm7                              

            psraw mm0, 1                               

            paddw mm0, mm7                             

            paddw mm1, mm4                             

            paddw mm0, mm5                             

            paddw mm1, mm7                             

            psubw mm0, mm4                             

            paddw mm1, mm6                             


            psubw mm4, mm6                             

            psubw mm7, mm6                             

            psraw mm6, 1                               

            paddw mm4, mm5                             

            psubw mm7, mm5                             

            psraw mm5, 1                               

            psubw mm4, mm6                             

            psubw mm7, mm5                             

            movq mm5, mm1                              

            psraw mm1, 2                               
            movq mm6, mm0                              

            psraw mm6, 2                               

            paddw mm6, mm4                             

            psraw mm4, 2                               

            paddw mm1, mm7                             

            psraw mm7, 2                               

            psubw mm4, mm0                             

            psubw mm5, mm7                             

            movq mm7, mm2                              

            psraw mm2, 1                               
            movq mm0, mm3                              

            psraw mm0, 1                               

            paddw mm2, mm3                             

            psubw mm0, mm7                             

            movq mm3, [esp]                            
        movq mm7, [esp+ 64]                        

        paddw mm7, mm3                             

            paddw mm3, mm3                             

            psubw mm3, mm7                             

            paddw mm2, mm7                             

            paddw mm7, mm7                             

            psubw mm7, mm2                             

            paddw mm0, mm3                             

            paddw mm3, mm3                             

            psubw mm3, mm0                             

            paddw mm5, mm2                             

            paddw mm2, mm2                             

            psubw mm2, mm5                             

            paddw mm4, mm0                             

            paddw mm0, mm0                             

            psubw mm0, mm4                             

            paddw mm6, mm3                             

            paddw mm3, mm3                             

            psubw mm3, mm6                             

            paddw mm1, mm7                             

            paddw mm7, mm7                             

            psubw mm7, mm1                             
            movq [esp ], mm3                           
            movq [esp+16], mm0                         
            movq [esp+32], mm2                         


            pxor mm2, mm2                              
            movd mm3, [ebp]                            
        movd mm0, [ebp+ebx]                        

        psraw mm5, 6                               

            psraw mm4, 6                               

            punpcklbw mm3, mm2                         

            punpcklbw mm0, mm2                         

            paddw mm3, mm5                             

            paddw mm0, mm4                             

            packuswb mm3, mm2                          

            packuswb mm0, mm2                          
            movd [ebp], mm3                            
            movd [ebp+ebx], mm0                        
            lea ebp, [ebp+ebx*2]                       
        movd mm3, [ebp]                            
        movd mm0, [ebp+ebx]                        

        psraw mm6, 6                               

            psraw mm1, 6                               

            punpcklbw mm3, mm2                         

            punpcklbw mm0, mm2                         

            paddw mm3, mm6                             

            paddw mm0, mm1                             

            packuswb mm3, mm2                          

            packuswb mm0, mm2                          
            movd [ebp], mm3                            
            movd [ebp+ebx], mm0                        
            movq mm5, [esp ]                           
        movq mm4, [esp+16]                         
        movq mm6, [esp+32]                         
        lea ebp, [ebp+ebx*2]                       
        movd mm3, [ebp]                            
        movd mm0, [ebp+ebx]                        

        psraw mm7, 6                               

            psraw mm5, 6                               

            punpcklbw mm3, mm2                         

            punpcklbw mm0, mm2                         

            paddw mm3, mm7                             

            paddw mm0, mm5                             

            packuswb mm3, mm2                          

            packuswb mm0, mm2                          
            movd [ebp], mm3                            
            movd [ebp+ebx], mm0                        
            lea ebp, [ebp+ebx*2]                       
        movd mm3, [ebp]                            
        movd mm0, [ebp+ebx]                        

        psraw mm4, 6                               

            psraw mm6, 6                               

            punpcklbw mm3, mm2                         

            punpcklbw mm0, mm2                         

            paddw mm3, mm4                             

            paddw mm0, mm6                             

            packuswb mm3, mm2                          

            packuswb mm0, mm2                          
            movd [ebp], mm3                            
            movd [ebp+ebx], mm0                        

            mov ebp, dword ptr[ecx+edi*4]                 
        lea ebp, [eax+ebp+4]                       
        movq mm2, [esp+8+112]                      

        movq mm0, [esp+8+ 96]                      
        movq mm3, [esp+8+ 80]                      
        movq mm1, [esp+8+ 48]                      
        movq mm6, [esp+8+ 32]                      
        movq mm4, [esp+8+ 16]                      
        movq mm5, mm4                              

            psraw mm4, 1                               
            movq mm7, mm3                              

            psraw mm7, 1                               

            paddw mm7, mm3                             

            paddw mm4, mm5                             

            paddw mm7, mm2                             

            paddw mm4, mm3                             

            psubw mm7, mm5                             

            paddw mm4, mm1                             


            psubw mm5, mm1                             

            psubw mm3, mm1                             

            psraw mm1, 1                               

            paddw mm5, mm2                             

            psubw mm3, mm2                             

            psraw mm2, 1                               

            psubw mm5, mm1                             

            psubw mm3, mm2                             

            movq mm2, mm4                              

            psraw mm4, 2                               
            movq mm1, mm7                              

            psraw mm1, 2                               

            paddw mm1, mm5                             

            psraw mm5, 2                               

            paddw mm4, mm3                             

            psraw mm3, 2                               

            psubw mm5, mm7                             

            psubw mm2, mm3                             

            movq mm3, mm0                              

            psraw mm0, 1                               
            movq mm7, mm6                              

            psraw mm7, 1                               

            paddw mm0, mm6                             

            psubw mm7, mm3                             

            movq mm6, [esp+8]                          
        movq mm3, [esp+8+ 64]                      

        paddw mm3, mm6                             

            paddw mm6, mm6                             

            psubw mm6, mm3                             

            paddw mm0, mm3                             

            paddw mm3, mm3                             

            psubw mm3, mm0                             

            paddw mm7, mm6                             

            paddw mm6, mm6                             

            psubw mm6, mm7                             

            paddw mm2, mm0                             

            paddw mm0, mm0                             

            psubw mm0, mm2                             

            paddw mm5, mm7                             

            paddw mm7, mm7                             

            psubw mm7, mm5                             

            paddw mm1, mm6                             

            paddw mm6, mm6                             

            psubw mm6, mm1                             

            paddw mm4, mm3                             

            paddw mm3, mm3                             

            psubw mm3, mm4                             
            movq [esp+8 ], mm6                         
            movq [esp+8+16], mm7                       
            movq [esp+8+32], mm0                       


            pxor mm0, mm0                              
            movd mm6, [ebp]                            
        movd mm7, [ebp+ebx]                        

        psraw mm2, 6                               

            psraw mm5, 6                               

            punpcklbw mm6, mm0                         

            punpcklbw mm7, mm0                         

            paddw mm6, mm2                             

            paddw mm7, mm5                             

            packuswb mm6, mm0                          

            packuswb mm7, mm0                          
            movd [ebp], mm6                            
            movd [ebp+ebx], mm7                        
            lea ebp, [ebp+ebx*2]                       
        movd mm6, [ebp]                            
        movd mm7, [ebp+ebx]                        

        psraw mm1, 6                               

            psraw mm4, 6                               

            punpcklbw mm6, mm0                         

            punpcklbw mm7, mm0                         

            paddw mm6, mm1                             

            paddw mm7, mm4                             

            packuswb mm6, mm0                          

            packuswb mm7, mm0                          
            movd [ebp], mm6                            
            movd [ebp+ebx], mm7                        
            movq mm2, [esp+8 ]                         
        movq mm5, [esp+8+16]                       
        movq mm1, [esp+8+32]                       
        lea ebp, [ebp+ebx*2]                       
        movd mm6, [ebp]                            
        movd mm7, [ebp+ebx]                        

        psraw mm3, 6                               

            psraw mm2, 6                               

            punpcklbw mm6, mm0                         

            punpcklbw mm7, mm0                         

            paddw mm6, mm3                             

            paddw mm7, mm2                             

            packuswb mm6, mm0                          

            packuswb mm7, mm0                          
            movd [ebp], mm6                            
            movd [ebp+ebx], mm7                        
            lea ebp, [ebp+ebx*2]                       
        movd mm6, [ebp]                            
        movd mm7, [ebp+ebx]                        

        psraw mm5, 6                               

            psraw mm1, 6                               

            punpcklbw mm6, mm0                         

            punpcklbw mm7, mm0                         

            paddw mm6, mm5                             

            paddw mm7, mm1                             

            packuswb mm6, mm0                          

            packuswb mm7, mm0                          
            movd [ebp], mm6                            
            movd [ebp+ebx], mm7                        

ff_h264_idct8_add4_8_mmxnextskipblock:
        add edi, 4                                 
            sub edx, -128                              
            cmp edi, 16                                
            jl ff_h264_idct8_add4_8_mmxnextblock
            add esp, 132                               
            pop ebp                                    

            pop edi                                    
            pop esi                                    
            pop ebx                                    
            ret                                        


    }
}

void __declspec(naked) ff_h264_idct8_add4_8_mmx2(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        sub esp, 132                                  

            xor edi, edi                                  

ff_h264_idct8_add4_8_mmx2nextblock:                                     
        movzx ebp, byte ptr[scan8_mem+edi]               
        movzx ebp, byte ptr[esi+ebp]                     
        test ebp, ebp                                 
            jz ff_h264_idct8_add4_8_mmx2skipblock                                 
            cmp ebp, 1                                    
            jnz ff_h264_idct8_add4_8_mmx2no_dc                                    
            movsx ebp, word ptr[edx]                         
        test ebp, ebp                                 
            jz ff_h264_idct8_add4_8_mmx2no_dc                                     
            add ebp, 32                                   

            sar ebp, 6                                    
            movd mm0, ebp                                 
            lea ebp, [ebx+ebx*2]                              
        pshufw mm0, mm0, 0                            

            pxor mm1, mm1                                 

            psubw mm1, mm0                                

            packuswb mm0, mm0                             

            packuswb mm1, mm1                             

            mov ecx, dword ptr[ecx+edi*4]                    
        lea ecx, [eax+ecx]                            
        movq mm2, [ecx ]                              

        movq mm3, [ecx+ebx ]                          
        movq mm4, [ecx+ebx*2]                         
        movq mm5, [ecx+ebp ]                          

        paddusb mm2, mm0                              

            paddusb mm3, mm0                              

            paddusb mm4, mm0                              

            paddusb mm5, mm0                              

            psubusb mm2, mm1                              

            psubusb mm3, mm1                              

            psubusb mm4, mm1                              

            psubusb mm5, mm1                              
            movq [ecx ], mm2                              
            movq [ecx+ebx ], mm3                          
            movq [ecx+ebx*2], mm4                         
            movq [ecx+ebp ], mm5                          

            lea ecx, [ecx+ebx*4]                          
        movq mm2, [ecx ]                              

        movq mm3, [ecx+ebx ]                          
        movq mm4, [ecx+ebx*2]                         
        movq mm5, [ecx+ebp ]                          

        paddusb mm2, mm0                              

            paddusb mm3, mm0                              

            paddusb mm4, mm0                              

            paddusb mm5, mm0                              

            psubusb mm2, mm1                              

            psubusb mm3, mm1                              

            psubusb mm4, mm1                              

            psubusb mm5, mm1                              
            movq [ecx ], mm2                              
            movq [ecx+ebx ], mm3                          
            movq [ecx+ebx*2], mm4                         
            movq [ecx+ebp ], mm5                          

            mov ecx, [esp + 148 + 8]                      

        add edi, 4                                    
            sub edx, -128                                 
            cmp edi, 16                                   
            jl ff_h264_idct8_add4_8_mmx2nextblock                                 

            add esp, 132                                  
            pop ebp                                       

            pop edi                                       
            pop esi                                       
            pop ebx                                       
            ret                                           

ff_h264_idct8_add4_8_mmx2no_dc:
        mov ebp, dword ptr[ecx+edi*4]                    
        add ebp, eax                                  
            add word ptr[edx], 32                            
            movq mm7, [edx+112]                           

        movq mm6, [edx+ 96]                           
        movq mm5, [edx+ 80]                           
        movq mm3, [edx+ 48]                           
        movq mm2, [edx+ 32]                           
        movq mm1, [edx+ 16]                           
        movq mm0, mm1                                 

            psraw mm1, 1                                  
            movq mm4, mm5                                 

            psraw mm4, 1                                  

            paddw mm4, mm5                                

            paddw mm1, mm0                                

            paddw mm4, mm7                                

            paddw mm1, mm5                                

            psubw mm4, mm0                                

            paddw mm1, mm3                                


            psubw mm0, mm3                                

            psubw mm5, mm3                                

            psraw mm3, 1                                  

            paddw mm0, mm7                                

            psubw mm5, mm7                                

            psraw mm7, 1                                  

            psubw mm0, mm3                                

            psubw mm5, mm7                                

            movq mm7, mm1                                 

            psraw mm1, 2                                  
            movq mm3, mm4                                 

            psraw mm3, 2                                  

            paddw mm3, mm0                                

            psraw mm0, 2                                  

            paddw mm1, mm5                                

            psraw mm5, 2                                  

            psubw mm0, mm4                                

            psubw mm7, mm5                                

            movq mm5, mm6                                 

            psraw mm6, 1                                  
            movq mm4, mm2                                 

            psraw mm4, 1                                  

            paddw mm6, mm2                                

            psubw mm4, mm5                                

            movq mm2, [edx]                               
        movq mm5, [edx+ 64]                           

        paddw mm5, mm2                                

            paddw mm2, mm2                                

            psubw mm2, mm5                                

            paddw mm6, mm5                                

            paddw mm5, mm5                                

            psubw mm5, mm6                                

            paddw mm4, mm2                                

            paddw mm2, mm2                                

            psubw mm2, mm4                                

            paddw mm7, mm6                                

            paddw mm6, mm6                                

            psubw mm6, mm7                                

            paddw mm0, mm4                                

            paddw mm4, mm4                                

            psubw mm4, mm0                                

            paddw mm3, mm2                                

            paddw mm2, mm2                                

            psubw mm2, mm3                                

            paddw mm1, mm5                                

            paddw mm5, mm5                                

            psubw mm5, mm1                                
            movq [edx], mm6                               
            movq mm6, mm7                                 

            punpcklwd mm7, mm0                            

            punpckhwd mm6, mm0                            
            movq mm0, mm3                                 

            punpcklwd mm3, mm1                            

            punpckhwd mm0, mm1                            
            movq mm1, mm7                                 

            punpckldq mm7, mm3                            

            punpckhdq mm1, mm3                            
            movq mm3, mm6                                 

            punpckldq mm6, mm0                            

            punpckhdq mm3, mm0                            
            movq mm0, [edx]                               
        movq [esp ], mm7                              
            movq [esp+16], mm1                            
            movq [esp+32], mm6                            
            movq [esp+48], mm3                            
            movq mm3, mm5                                 

            punpcklwd mm5, mm2                            

            punpckhwd mm3, mm2                            
            movq mm2, mm4                                 

            punpcklwd mm4, mm0                            

            punpckhwd mm2, mm0                            
            movq mm0, mm5                                 

            punpckldq mm5, mm4                            

            punpckhdq mm0, mm4                            
            movq mm4, mm3                                 

            punpckldq mm3, mm2                            

            punpckhdq mm4, mm2                            
            movq [esp+ 8], mm5                            
            movq [esp+24], mm0                            
            movq [esp+40], mm3                            
            movq [esp+56], mm4                            

            movq mm4, [edx+8+112]                         

        movq mm3, [edx+8+ 96]                         
        movq mm0, [edx+8+ 80]                         
        movq mm2, [edx+8+ 48]                         
        movq mm6, [edx+8+ 32]                         
        movq mm1, [edx+8+ 16]                         
        movq mm7, mm1                                 

            psraw mm1, 1                                  
            movq mm5, mm0                                 

            psraw mm5, 1                                  

            paddw mm5, mm0                                

            paddw mm1, mm7                                

            paddw mm5, mm4                                

            paddw mm1, mm0                                

            psubw mm5, mm7                                

            paddw mm1, mm2                                


            psubw mm7, mm2                                

            psubw mm0, mm2                                

            psraw mm2, 1                                  

            paddw mm7, mm4                                

            psubw mm0, mm4                                

            psraw mm4, 1                                  

            psubw mm7, mm2                                

            psubw mm0, mm4                                

            movq mm4, mm1                                 

            psraw mm1, 2                                  
            movq mm2, mm5                                 

            psraw mm2, 2                                  

            paddw mm2, mm7                                

            psraw mm7, 2                                  

            paddw mm1, mm0                                

            psraw mm0, 2                                  

            psubw mm7, mm5                                

            psubw mm4, mm0                                

            movq mm0, mm3                                 

            psraw mm3, 1                                  
            movq mm5, mm6                                 

            psraw mm5, 1                                  

            paddw mm3, mm6                                

            psubw mm5, mm0                                

            movq mm6, [edx+8]                             
        movq mm0, [edx+8+ 64]                         

        paddw mm0, mm6                                

            paddw mm6, mm6                                

            psubw mm6, mm0                                

            paddw mm3, mm0                                

            paddw mm0, mm0                                

            psubw mm0, mm3                                

            paddw mm5, mm6                                

            paddw mm6, mm6                                

            psubw mm6, mm5                                

            paddw mm4, mm3                                

            paddw mm3, mm3                                

            psubw mm3, mm4                                

            paddw mm7, mm5                                

            paddw mm5, mm5                                

            psubw mm5, mm7                                

            paddw mm2, mm6                                

            paddw mm6, mm6                                

            psubw mm6, mm2                                

            paddw mm1, mm0                                

            paddw mm0, mm0                                

            psubw mm0, mm1                                
            movq [edx+8], mm3                             
            movq mm3, mm4                                 

            punpcklwd mm4, mm7                            

            punpckhwd mm3, mm7                            
            movq mm7, mm2                                 

            punpcklwd mm2, mm1                            

            punpckhwd mm7, mm1                            
            movq mm1, mm4                                 

            punpckldq mm4, mm2                            

            punpckhdq mm1, mm2                            
            movq mm2, mm3                                 

            punpckldq mm3, mm7                            

            punpckhdq mm2, mm7                            
            movq mm7, [edx+8]                             
        movq [esp+64 ], mm4                           
            movq [esp+64+16], mm1                         
            movq [esp+64+32], mm3                         
            movq [esp+64+48], mm2                         
            movq mm2, mm0                                 

            punpcklwd mm0, mm6                            

            punpckhwd mm2, mm6                            
            movq mm6, mm5                                 

            punpcklwd mm5, mm7                            

            punpckhwd mm6, mm7                            
            movq mm7, mm0                                 

            punpckldq mm0, mm5                            

            punpckhdq mm7, mm5                            
            movq mm5, mm2                                 

            punpckldq mm2, mm6                            

            punpckhdq mm5, mm6                            
            movq [esp+64+ 8], mm0                         
            movq [esp+64+24], mm7                         
            movq [esp+64+40], mm2                         
            movq [esp+64+56], mm5                         

            movq mm5, [esp+112]                           

        movq mm2, [esp+ 96]                           
        movq mm7, [esp+ 80]                           
        movq mm6, [esp+ 48]                           
        movq mm3, [esp+ 32]                           
        movq mm1, [esp+ 16]                           
        movq mm4, mm1                                 

            psraw mm1, 1                                  
            movq mm0, mm7                                 

            psraw mm0, 1                                  

            paddw mm0, mm7                                

            paddw mm1, mm4                                

            paddw mm0, mm5                                

            paddw mm1, mm7                                

            psubw mm0, mm4                                

            paddw mm1, mm6                                


            psubw mm4, mm6                                

            psubw mm7, mm6                                

            psraw mm6, 1                                  

            paddw mm4, mm5                                

            psubw mm7, mm5                                

            psraw mm5, 1                                  

            psubw mm4, mm6                                

            psubw mm7, mm5                                

            movq mm5, mm1                                 

            psraw mm1, 2                                  
            movq mm6, mm0                                 

            psraw mm6, 2                                  

            paddw mm6, mm4                                

            psraw mm4, 2                                  

            paddw mm1, mm7                                

            psraw mm7, 2                                  

            psubw mm4, mm0                                

            psubw mm5, mm7                                

            movq mm7, mm2                                 

            psraw mm2, 1                                  
            movq mm0, mm3                                 

            psraw mm0, 1                                  

            paddw mm2, mm3                                

            psubw mm0, mm7                                

            movq mm3, [esp]                               
        movq mm7, [esp+ 64]                           

        paddw mm7, mm3                                

            paddw mm3, mm3                                

            psubw mm3, mm7                                

            paddw mm2, mm7                                

            paddw mm7, mm7                                

            psubw mm7, mm2                                

            paddw mm0, mm3                                

            paddw mm3, mm3                                

            psubw mm3, mm0                                

            paddw mm5, mm2                                

            paddw mm2, mm2                                

            psubw mm2, mm5                                

            paddw mm4, mm0                                

            paddw mm0, mm0                                

            psubw mm0, mm4                                

            paddw mm6, mm3                                

            paddw mm3, mm3                                

            psubw mm3, mm6                                

            paddw mm1, mm7                                

            paddw mm7, mm7                                

            psubw mm7, mm1                                
            movq [esp ], mm3                              
            movq [esp+16], mm0                            
            movq [esp+32], mm2                            


            pxor mm2, mm2                                 
            movd mm3, [ebp]                               
        movd mm0, [ebp+ebx]                           

        psraw mm5, 6                                  

            psraw mm4, 6                                  

            punpcklbw mm3, mm2                            

            punpcklbw mm0, mm2                            

            paddw mm3, mm5                                

            paddw mm0, mm4                                

            packuswb mm3, mm2                             

            packuswb mm0, mm2                             
            movd [ebp], mm3                               
            movd [ebp+ebx], mm0                           
            lea ebp, [ebp+ebx*2]                          
        movd mm3, [ebp]                               
        movd mm0, [ebp+ebx]                           

        psraw mm6, 6                                  

            psraw mm1, 6                                  

            punpcklbw mm3, mm2                            

            punpcklbw mm0, mm2                            

            paddw mm3, mm6                                

            paddw mm0, mm1                                

            packuswb mm3, mm2                             

            packuswb mm0, mm2                             
            movd [ebp], mm3                               
            movd [ebp+ebx], mm0                           
            movq mm5, [esp ]                              
        movq mm4, [esp+16]                            
        movq mm6, [esp+32]                            
        lea ebp, [ebp+ebx*2]                          
        movd mm3, [ebp]                               
        movd mm0, [ebp+ebx]                           

        psraw mm7, 6                                  

            psraw mm5, 6                                  

            punpcklbw mm3, mm2                            

            punpcklbw mm0, mm2                            

            paddw mm3, mm7                                

            paddw mm0, mm5                                

            packuswb mm3, mm2                             

            packuswb mm0, mm2                             
            movd [ebp], mm3                               
            movd [ebp+ebx], mm0                           
            lea ebp, [ebp+ebx*2]                          
        movd mm3, [ebp]                               
        movd mm0, [ebp+ebx]                           

        psraw mm4, 6                                  

            psraw mm6, 6                                  

            punpcklbw mm3, mm2                            

            punpcklbw mm0, mm2                            

            paddw mm3, mm4                                

            paddw mm0, mm6                                

            packuswb mm3, mm2                             

            packuswb mm0, mm2                             
            movd [ebp], mm3                               
            movd [ebp+ebx], mm0                           

            mov ebp, dword ptr[ecx+edi*4]                    
        lea ebp, [eax+ebp+4]                          
        movq mm2, [esp+8+112]                         

        movq mm0, [esp+8+ 96]                         
        movq mm3, [esp+8+ 80]                         
        movq mm1, [esp+8+ 48]                         
        movq mm6, [esp+8+ 32]                         
        movq mm4, [esp+8+ 16]                         
        movq mm5, mm4                                 

            psraw mm4, 1                                  
            movq mm7, mm3                                 

            psraw mm7, 1                                  

            paddw mm7, mm3                                

            paddw mm4, mm5                                

            paddw mm7, mm2                                

            paddw mm4, mm3                                

            psubw mm7, mm5                                

            paddw mm4, mm1                                


            psubw mm5, mm1                                

            psubw mm3, mm1                                

            psraw mm1, 1                                  

            paddw mm5, mm2                                

            psubw mm3, mm2                                

            psraw mm2, 1                                  

            psubw mm5, mm1                                

            psubw mm3, mm2                                

            movq mm2, mm4                                 

            psraw mm4, 2                                  
            movq mm1, mm7                                 

            psraw mm1, 2                                  

            paddw mm1, mm5                                

            psraw mm5, 2                                  

            paddw mm4, mm3                                

            psraw mm3, 2                                  

            psubw mm5, mm7                                

            psubw mm2, mm3                                

            movq mm3, mm0                                 

            psraw mm0, 1                                  
            movq mm7, mm6                                 

            psraw mm7, 1                                  

            paddw mm0, mm6                                

            psubw mm7, mm3                                

            movq mm6, [esp+8]                             
        movq mm3, [esp+8+ 64]                         

        paddw mm3, mm6                                

            paddw mm6, mm6                                

            psubw mm6, mm3                                

            paddw mm0, mm3                                

            paddw mm3, mm3                                

            psubw mm3, mm0                                

            paddw mm7, mm6                                

            paddw mm6, mm6                                

            psubw mm6, mm7                                

            paddw mm2, mm0                                

            paddw mm0, mm0                                

            psubw mm0, mm2                                

            paddw mm5, mm7                                

            paddw mm7, mm7                                

            psubw mm7, mm5                                

            paddw mm1, mm6                                

            paddw mm6, mm6                                

            psubw mm6, mm1                                

            paddw mm4, mm3                                

            paddw mm3, mm3                                

            psubw mm3, mm4                                
            movq [esp+8 ], mm6                            
            movq [esp+8+16], mm7                          
            movq [esp+8+32], mm0                          


            pxor mm0, mm0                                 
            movd mm6, [ebp]                               
        movd mm7, [ebp+ebx]                           

        psraw mm2, 6                                  

            psraw mm5, 6                                  

            punpcklbw mm6, mm0                            

            punpcklbw mm7, mm0                            

            paddw mm6, mm2                                

            paddw mm7, mm5                                

            packuswb mm6, mm0                             

            packuswb mm7, mm0                             
            movd [ebp], mm6                               
            movd [ebp+ebx], mm7                           
            lea ebp, [ebp+ebx*2]                          
        movd mm6, [ebp]                               
        movd mm7, [ebp+ebx]                           

        psraw mm1, 6                                  

            psraw mm4, 6                                  

            punpcklbw mm6, mm0                            

            punpcklbw mm7, mm0                            

            paddw mm6, mm1                                

            paddw mm7, mm4                                

            packuswb mm6, mm0                             

            packuswb mm7, mm0                             
            movd [ebp], mm6                               
            movd [ebp+ebx], mm7                           
            movq mm2, [esp+8 ]                            
        movq mm5, [esp+8+16]                          
        movq mm1, [esp+8+32]                          
        lea ebp, [ebp+ebx*2]                          
        movd mm6, [ebp]                               
        movd mm7, [ebp+ebx]                           

        psraw mm3, 6                                  

            psraw mm2, 6                                  

            punpcklbw mm6, mm0                            

            punpcklbw mm7, mm0                            

            paddw mm6, mm3                                

            paddw mm7, mm2                                

            packuswb mm6, mm0                             

            packuswb mm7, mm0                             
            movd [ebp], mm6                               
            movd [ebp+ebx], mm7                           
            lea ebp, [ebp+ebx*2]                          
        movd mm6, [ebp]                               
        movd mm7, [ebp+ebx]                           

        psraw mm5, 6                                  

            psraw mm1, 6                                  

            punpcklbw mm6, mm0                            

            punpcklbw mm7, mm0                            

            paddw mm6, mm5                                

            paddw mm7, mm1                                

            packuswb mm6, mm0                             

            packuswb mm7, mm0                             
            movd [ebp], mm6                               
            movd [ebp+ebx], mm7                           

ff_h264_idct8_add4_8_mmx2skipblock:                                     
        add edi, 4                                    
            sub edx, -128                                 
            cmp edi, 16                                   
            jl ff_h264_idct8_add4_8_mmx2nextblock                                 

            add esp, 132                                  
            pop ebp                                       

            pop edi                                       
            pop esi                                       
            pop ebx                                       
            ret                                           

    }
}

void __declspec(naked) ff_h264_idct8_add4_8_sse2(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        xor edi, edi                                         

ff_h264_idct8_add4_8_sse2nextblock:
        movzx ebp, byte ptr[scan8_mem+edi]                      
        movzx ebp, byte ptr[esi+ebp]                            
        test ebp, ebp                                        
            jz ff_h264_idct8_add4_8_sse2skipblock                                        
            cmp ebp, 1                                           
            jnz ff_h264_idct8_add4_8_sse2no_dc                                           
            movsx ebp, word ptr[edx]                                
        test ebp, ebp                                        
            jz ff_h264_idct8_add4_8_sse2no_dc                                            

            add ebp, 32                                          

            sar ebp, 6                                           
            movd mm0, ebp                                        
            lea ebp, [ebx+ebx*2]                                     
        pshufw mm0, mm0, 0                                   

            pxor mm1, mm1                                        

            psubw mm1, mm0                                       

            packuswb mm0, mm0                                    

            packuswb mm1, mm1                                    

            mov ecx, dword ptr[ecx+edi*4]                           
        add ecx, eax                                         
            movq mm2, [ecx ]                                     

        movq mm3, [ecx+ebx ]                                 
        movq mm4, [ecx+ebx*2]                                
        movq mm5, [ecx+ebp ]                                 

        paddusb mm2, mm0                                     

            paddusb mm3, mm0                                     

            paddusb mm4, mm0                                     

            paddusb mm5, mm0                                     

            psubusb mm2, mm1                                     

            psubusb mm3, mm1                                     

            psubusb mm4, mm1                                     

            psubusb mm5, mm1                                     
            movq [ecx ], mm2                                     
            movq [ecx+ebx ], mm3                                 
            movq [ecx+ebx*2], mm4                                
            movq [ecx+ebp ], mm5                                 

            lea ecx, [ecx+ebx*4]                                 
        movq mm2, [ecx ]                                     

        movq mm3, [ecx+ebx ]                                 
        movq mm4, [ecx+ebx*2]                                
        movq mm5, [ecx+ebp ]                                 

        paddusb mm2, mm0                                     

            paddusb mm3, mm0                                     

            paddusb mm4, mm0                                     

            paddusb mm5, mm0                                     

            psubusb mm2, mm1                                     

            psubusb mm3, mm1                                     

            psubusb mm4, mm1                                     

            psubusb mm5, mm1                                     
            movq [ecx ], mm2                                     
            movq [ecx+ebx ], mm3                                 
            movq [ecx+ebx*2], mm4                                
            movq [ecx+ebp ], mm5                                 

            mov ecx, [esp + 16 + 8]                              

        add edi, 4                                           
            sub edx, -128                                        
            cmp edi, 16                                          
            jl ff_h264_idct8_add4_8_sse2nextblock                                        
            pop ebp                                              

            pop edi                                              
            pop esi                                              
            pop ebx                                              
            ret                                                  

ff_h264_idct8_add4_8_sse2no_dc:

        mov ecx, dword ptr[ecx+edi*4]                           
        add ecx, eax                                         
            movdqa xmm7, [edx+112]                               

        movdqa xmm6, [edx+ 96]                               
        movdqa xmm5, [edx+ 80]                               
        movdqa xmm3, [edx+ 48]                               
        movdqa xmm2, [edx+ 32]                               
        movdqa xmm1, [edx+ 16]                               
        movdqa xmm0, xmm1                                    

            psraw xmm1, 1                                        
            movdqa xmm4, xmm5                                    

            psraw xmm4, 1                                        

            paddw xmm4, xmm5                                     

            paddw xmm1, xmm0                                     

            paddw xmm4, xmm7                                     

            paddw xmm1, xmm5                                     

            psubw xmm4, xmm0                                     

            paddw xmm1, xmm3                                     


            psubw xmm0, xmm3                                     

            psubw xmm5, xmm3                                     

            psraw xmm3, 1                                        

            paddw xmm0, xmm7                                     

            psubw xmm5, xmm7                                     

            psraw xmm7, 1                                        

            psubw xmm0, xmm3                                     

            psubw xmm5, xmm7                                     

            movdqa xmm7, xmm1                                    

            psraw xmm1, 2                                        
            movdqa xmm3, xmm4                                    

            psraw xmm3, 2                                        

            paddw xmm3, xmm0                                     

            psraw xmm0, 2                                        

            paddw xmm1, xmm5                                     

            psraw xmm5, 2                                        

            psubw xmm0, xmm4                                     

            psubw xmm7, xmm5                                     

            movdqa xmm5, xmm6                                    

            psraw xmm6, 1                                        
            movdqa xmm4, xmm2                                    

            psraw xmm4, 1                                        

            paddw xmm6, xmm2                                     

            psubw xmm4, xmm5                                     

            movdqa xmm2, [edx]                                   
        movdqa xmm5, [edx+ 64]                               

        paddw xmm5, xmm2                                     

            paddw xmm2, xmm2                                     

            psubw xmm2, xmm5                                     

            paddw xmm6, xmm5                                     

            paddw xmm5, xmm5                                     

            psubw xmm5, xmm6                                     

            paddw xmm4, xmm2                                     

            paddw xmm2, xmm2                                     

            psubw xmm2, xmm4                                     

            paddw xmm7, xmm6                                     

            paddw xmm6, xmm6                                     

            psubw xmm6, xmm7                                     

            paddw xmm0, xmm4                                     

            paddw xmm4, xmm4                                     

            psubw xmm4, xmm0                                     

            paddw xmm3, xmm2                                     

            paddw xmm2, xmm2                                     

            psubw xmm2, xmm3                                     

            paddw xmm1, xmm5                                     

            paddw xmm5, xmm5                                     

            psubw xmm5, xmm1                                     



            movdqa [edx], xmm4                                   
            movdqa xmm4, xmm7                                    

            punpcklwd xmm7, xmm0                                 

            punpckhwd xmm4, xmm0                                 
            movdqa [edx+16], xmm4                                
            movdqa xmm0, [edx]                                   
        movdqa xmm4, xmm3                                    

            punpcklwd xmm3, xmm1                                 

            punpckhwd xmm4, xmm1                                 
            movdqa xmm1, xmm5                                    

            punpcklwd xmm5, xmm2                                 

            punpckhwd xmm1, xmm2                                 
            movdqa xmm2, xmm0                                    

            punpcklwd xmm0, xmm6                                 

            punpckhwd xmm2, xmm6                                 
            movdqa xmm6, xmm7                                    

            punpckldq xmm7, xmm3                                 

            punpckhdq xmm6, xmm3                                 
            movdqa [edx], xmm6                                   
            movdqa xmm3, [edx+16]                                
        movdqa xmm6, xmm3                                    

            punpckldq xmm3, xmm4                                 

            punpckhdq xmm6, xmm4                                 
            movdqa xmm4, xmm5                                    

            punpckldq xmm5, xmm0                                 

            punpckhdq xmm4, xmm0                                 
            movdqa xmm0, xmm1                                    

            punpckldq xmm1, xmm2                                 

            punpckhdq xmm0, xmm2                                 
            movdqa xmm2, xmm7                                    

            punpcklqdq xmm7, xmm5                                

            punpckhqdq xmm2, xmm5                                
            movdqa xmm5, xmm3                                    

            punpcklqdq xmm3, xmm1                                

            punpckhqdq xmm5, xmm1                                
            movdqa [edx+16], xmm3                                
            movdqa xmm1, [edx]                                   
        movdqa xmm3, xmm1                                    

            punpcklqdq xmm1, xmm4                                

            punpckhqdq xmm3, xmm4                                
            movdqa xmm4, xmm6                                    

            punpcklqdq xmm6, xmm0                                

            punpckhqdq xmm4, xmm0                                
            movdqa xmm0, [edx+16]                                

        paddw xmm7, [ff_pw_32]                               

        movdqa [edx ], xmm7                                  
            movdqa [edx+16], xmm0                                
            movdqa xmm7, xmm2                                    

            psraw xmm2, 1                                        
            movdqa xmm0, xmm5                                    

            psraw xmm0, 1                                        

            paddw xmm0, xmm5                                     

            paddw xmm2, xmm7                                     

            paddw xmm0, xmm4                                     

            paddw xmm2, xmm5                                     

            psubw xmm0, xmm7                                     

            paddw xmm2, xmm3                                     


            psubw xmm7, xmm3                                     

            psubw xmm5, xmm3                                     

            psraw xmm3, 1                                        

            paddw xmm7, xmm4                                     

            psubw xmm5, xmm4                                     

            psraw xmm4, 1                                        

            psubw xmm7, xmm3                                     

            psubw xmm5, xmm4                                     

            movdqa xmm4, xmm2                                    

            psraw xmm2, 2                                        
            movdqa xmm3, xmm0                                    

            psraw xmm3, 2                                        

            paddw xmm3, xmm7                                     

            psraw xmm7, 2                                        

            paddw xmm2, xmm5                                     

            psraw xmm5, 2                                        

            psubw xmm7, xmm0                                     

            psubw xmm4, xmm5                                     

            movdqa xmm5, xmm6                                    

            psraw xmm6, 1                                        
            movdqa xmm0, xmm1                                    

            psraw xmm0, 1                                        

            paddw xmm6, xmm1                                     

            psubw xmm0, xmm5                                     

            movdqa xmm1, [edx]                                   
        movdqa xmm5, [edx+ 16]                               

        paddw xmm5, xmm1                                     

            paddw xmm1, xmm1                                     

            psubw xmm1, xmm5                                     

            paddw xmm6, xmm5                                     

            paddw xmm5, xmm5                                     

            psubw xmm5, xmm6                                     

            paddw xmm0, xmm1                                     

            paddw xmm1, xmm1                                     

            psubw xmm1, xmm0                                     

            paddw xmm4, xmm6                                     

            paddw xmm6, xmm6                                     

            psubw xmm6, xmm4                                     

            paddw xmm7, xmm0                                     

            paddw xmm0, xmm0                                     

            psubw xmm0, xmm7                                     

            paddw xmm3, xmm1                                     

            paddw xmm1, xmm1                                     

            psubw xmm1, xmm3                                     

            paddw xmm2, xmm5                                     

            paddw xmm5, xmm5                                     

            psubw xmm5, xmm2                                     
            movdqa [edx ], xmm0                                  
            movdqa [edx+16], xmm6                                


            pxor xmm6, xmm6                                      
            lea ebp, [ebx+ebx*2]                                     
        movq xmm0, qword ptr[ecx ]                                    

        punpcklbw xmm0, xmm6                                 

            psraw xmm4, 6                                        

            paddsw xmm4, xmm0                                    

            packuswb xmm4, xmm4                                  
            movq qword ptr[ecx ], xmm4                                    
            movq xmm0, qword ptr[ecx+ebx ]                                

        punpcklbw xmm0, xmm6                                 

            psraw xmm7, 6                                        

            paddsw xmm7, xmm0                                    

            packuswb xmm7, xmm7                                  
            movq qword ptr[ecx+ebx ], xmm7                                
            movq xmm0, qword ptr[ecx+ebx*2]                               

        punpcklbw xmm0, xmm6                                 

            psraw xmm3, 6                                        

            paddsw xmm3, xmm0                                    

            packuswb xmm3, xmm3                                  
            movq qword ptr[ecx+ebx*2], xmm3                               
            movq xmm0, qword ptr[ecx+ebp ]                                

        punpcklbw xmm0, xmm6                                 

            psraw xmm2, 6                                        

            paddsw xmm2, xmm0                                    

            packuswb xmm2, xmm2                                  
            movq qword ptr[ecx+ebp ], xmm2                                
            movdqa xmm4, [edx ]                                  
        movdqa xmm7, [edx+16]                                
        lea ecx, [ecx+ebx*4]                                 
        movq xmm0, qword ptr[ecx ]                                    

        punpcklbw xmm0, xmm6                                 

            psraw xmm5, 6                                        

            paddsw xmm5, xmm0                                    

            packuswb xmm5, xmm5                                  
            movq qword ptr[ecx ], xmm5                                    
            movq xmm0, qword ptr[ecx+ebx ]                                

        punpcklbw xmm0, xmm6                                 

            psraw xmm1, 6                                        

            paddsw xmm1, xmm0                                    

            packuswb xmm1, xmm1                                  
            movq qword ptr[ecx+ebx ], xmm1                                
            movq xmm0,qword ptr [ecx+ebx*2]                               

        punpcklbw xmm0, xmm6                                 

            psraw xmm4, 6                                        

            paddsw xmm4, xmm0                                    

            packuswb xmm4, xmm4                                  
            movq qword ptr[ecx+ebx*2], xmm4                               
            movq xmm0, qword ptr[ecx+ebp ]                                

        punpcklbw xmm0, xmm6                                 

            psraw xmm7, 6                                        

            paddsw xmm7, xmm0                                    

            packuswb xmm7, xmm7                                  
            movq qword ptr[ecx+ebp ], xmm7                                

            mov ecx, [esp + 16 + 8]                              

ff_h264_idct8_add4_8_sse2skipblock:
        add edi, 4                                           
            sub edx, -128                                        
            cmp edi, 16                                          
            jl ff_h264_idct8_add4_8_sse2nextblock                                        
            pop ebp                                              

            pop edi                                              
            pop esi                                              
            pop ebx                                              
            ret
    }
}
void __declspec(naked) ff_h264_idct_add16_8_mmx(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        xor edi, edi                                     

ff_h264_idct_add16_8_mmxnextblock:                                        
        movzx ebp, byte ptr[scan8_mem+edi]                  
        movzx ebp, byte ptr[esi+ebp]                        
        test ebp, ebp                                    
            jz ff_h264_idct_add16_8_mmxskipblock                                    
            mov ebp, dword ptr[ecx+edi*4]                       
        lea ebp, [eax+ebp]                               


        movq mm0, [edx]                                  
        movq mm1, [edx+8]                                
        movq mm2, [edx+16]                               
        movq mm3, [edx+24]                               


        movq mm4, mm1                                    
            psraw mm4, 1                                     

            movq mm5, mm3                                    
            psraw mm5, 1                                     

            paddw mm5, mm1                                   

            psubw mm4, mm3                                   

            movq mm3, mm2                                    

            paddw mm2, mm0                                   

            psubw mm0, mm3                                   

            movq mm3, mm5                                    

            paddw mm5, mm2                                   

            psubw mm2, mm3                                   
            movq mm3, mm4                                    

            paddw mm4, mm0                                   

            psubw mm0, mm3                                   








            movq mm6, [ff_pw_32]                             
        movq mm1, mm5                                    

            punpcklwd mm5, mm4                               

            punpckhwd mm1, mm4                               
            movq mm4, mm0                                    

            punpcklwd mm0, mm2                               

            punpckhwd mm4, mm2                               
            movq mm2, mm5                                    

            punpckldq mm5, mm0                               

            punpckhdq mm2, mm0                               
            movq mm0, mm1                                    

            punpckldq mm1, mm4                               

            punpckhdq mm0, mm4                               

            paddw mm5, mm6                                   

            movq mm4, mm2                                    
            psraw mm4, 1                                     

            movq mm3, mm0                                    
            psraw mm3, 1                                     

            paddw mm3, mm2                                   

            psubw mm4, mm0                                   

            movq mm0, mm1                                    

            paddw mm1, mm5                                   

            psubw mm5, mm0                                   

            movq mm0, mm3                                    

            paddw mm3, mm1                                   

            psubw mm1, mm0                                   
            movq mm0, mm4                                    

            paddw mm4, mm5                                   

            psubw mm5, mm0                                   









            pxor mm7, mm7                                    

            movd mm2, [ebp]                                  
        movd mm0, [ebp+ebx]                              

        psraw mm3, 6                                     

            psraw mm4, 6                                     

            punpcklbw mm2, mm7                               

            punpcklbw mm0, mm7                               

            paddw mm2, mm3                                   

            paddw mm0, mm4                                   

            packuswb mm2, mm7                                

            packuswb mm0, mm7                                
            movd [ebp], mm2                                  
            movd [ebp+ebx], mm0                              
            lea ebp, [ebp+ebx*2]                             
        movd mm2, [ebp]                                  
        movd mm0, [ebp+ebx]                              

        psraw mm5, 6                                     

            psraw mm1, 6                                     

            punpcklbw mm2, mm7                               

            punpcklbw mm0, mm7                               

            paddw mm2, mm5                                   

            paddw mm0, mm1                                   

            packuswb mm2, mm7                                

            packuswb mm0, mm7                                
            movd [ebp], mm2                                  
            movd [ebp+ebx], mm0                              

ff_h264_idct_add16_8_mmxskipblock:                                        
        inc edi                                          
            add edx, 32                                      
            cmp edi, 16                                      
            jl ff_h264_idct_add16_8_mmxnextblock                                    
            pop ebp                                          

            pop edi                                          
            pop esi                                          
            pop ebx                                          
            ret                                              

    }
}
void __declspec(naked) ff_h264_idct_add16_8_mmx2(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        xor edi, edi                                 

ff_h264_idct_add16_8_mmx2nextblock:                                    
        movzx ebp, byte ptr[scan8_mem+edi]              
        movzx ebp, byte ptr[esi+ebp]                    
        test ebp, ebp                                
            jz ff_h264_idct_add16_8_mmx2skipblock                                
            cmp ebp, 1                                   
            jnz ff_h264_idct_add16_8_mmx2no_dc                                   
            movsx ebp, word ptr[edx]                        
        test ebp, ebp                                
            jz ff_h264_idct_add16_8_mmx2no_dc                                    
            add ebp, 32                                  

            sar ebp, 6                                   
            movd mm0, ebp                                
            lea ebp, [ebx+ebx*2]                             
        pshufw mm0, mm0, 0                           

            pxor mm1, mm1                                

            psubw mm1, mm0                               

            packuswb mm0, mm0                            

            packuswb mm1, mm1                            

            mov ecx, dword ptr[ecx+edi*4]                   
        lea ecx, [eax+ecx]                           
        movd mm2, [ecx ]                             

        movd mm3, [ecx+ebx ]                         
        movd mm4, [ecx+ebx*2]                        
        movd mm5, [ecx+ebp ]                         

        paddusb mm2, mm0                             

            paddusb mm3, mm0                             

            paddusb mm4, mm0                             

            paddusb mm5, mm0                             

            psubusb mm2, mm1                             

            psubusb mm3, mm1                             

            psubusb mm4, mm1                             

            psubusb mm5, mm1                             
            movd [ecx ], mm2                             
            movd [ecx+ebx ], mm3                         
            movd [ecx+ebx*2], mm4                        
            movd [ecx+ebp ], mm5                         

            mov ecx, [esp + 16 + 8]                      

        inc edi                                      
            add edx, 32                                  
            cmp edi, 16                                  
            jl ff_h264_idct_add16_8_mmx2nextblock                                
            pop ebp                                      

            pop edi                                      
            pop esi                                      
            pop ebx                                      
            ret                                          

ff_h264_idct_add16_8_mmx2no_dc:                                        
        mov ebp, dword ptr[ecx+edi*4]                   
        add ebp, eax                                 


            movq mm0, [edx]                              
        movq mm1, [edx+8]                            
        movq mm2, [edx+16]                           
        movq mm3, [edx+24]                           


        movq mm4, mm1                                
            psraw mm4, 1                                 

            movq mm5, mm3                                
            psraw mm5, 1                                 

            paddw mm5, mm1                               

            psubw mm4, mm3                               

            movq mm3, mm2                                

            paddw mm2, mm0                               

            psubw mm0, mm3                               

            movq mm3, mm5                                

            paddw mm5, mm2                               

            psubw mm2, mm3                               
            movq mm3, mm4                                

            paddw mm4, mm0                               

            psubw mm0, mm3                               








            movq mm6, [ff_pw_32]                         
        movq mm1, mm5                                

            punpcklwd mm5, mm4                           

            punpckhwd mm1, mm4                           
            movq mm4, mm0                                

            punpcklwd mm0, mm2                           

            punpckhwd mm4, mm2                           
            movq mm2, mm5                                

            punpckldq mm5, mm0                           

            punpckhdq mm2, mm0                           
            movq mm0, mm1                                

            punpckldq mm1, mm4                           

            punpckhdq mm0, mm4                           

            paddw mm5, mm6                               

            movq mm4, mm2                                
            psraw mm4, 1                                 

            movq mm3, mm0                                
            psraw mm3, 1                                 

            paddw mm3, mm2                               

            psubw mm4, mm0                               

            movq mm0, mm1                                

            paddw mm1, mm5                               

            psubw mm5, mm0                               

            movq mm0, mm3                                

            paddw mm3, mm1                               

            psubw mm1, mm0                               
            movq mm0, mm4                                

            paddw mm4, mm5                               

            psubw mm5, mm0                               









            pxor mm7, mm7                                

            movd mm2, [ebp]                              
        movd mm0, [ebp+ebx]                          

        psraw mm3, 6                                 

            psraw mm4, 6                                 

            punpcklbw mm2, mm7                           

            punpcklbw mm0, mm7                           

            paddw mm2, mm3                               

            paddw mm0, mm4                               

            packuswb mm2, mm7                            

            packuswb mm0, mm7                            
            movd [ebp], mm2                              
            movd [ebp+ebx], mm0                          
            lea ebp, [ebp+ebx*2]                         
        movd mm2, [ebp]                              
        movd mm0, [ebp+ebx]                          

        psraw mm5, 6                                 

            psraw mm1, 6                                 

            punpcklbw mm2, mm7                           

            punpcklbw mm0, mm7                           

            paddw mm2, mm5                               

            paddw mm0, mm1                               

            packuswb mm2, mm7                            

            packuswb mm0, mm7                            
            movd [ebp], mm2                              
            movd [ebp+ebx], mm0                          

ff_h264_idct_add16_8_mmx2skipblock:                                    
        inc edi                                      
            add edx, 32                                  
            cmp edi, 16                                  
            jl ff_h264_idct_add16_8_mmx2nextblock                                
            pop ebp                                      

            pop edi                                      
            pop esi                                      
            pop ebx                                      
            ret                                          
    }
}
void __declspec(naked) x264_add8x4_idct_sse2(void)
{
    __asm{
        movq xmm0, qword ptr[edx+ 0]                                         
        movq xmm1, qword ptr[edx+ 8]                                         
        movq xmm2, qword ptr[edx+16]                                         
        movq xmm3, qword ptr[edx+24]                                         
        movhps xmm0, qword ptr[edx+32]                                       
        movhps xmm1, qword ptr[edx+40]                                       
        movhps xmm2, qword ptr[edx+48]                                       
        movhps xmm3, qword ptr[edx+56]                                       


        movdqa xmm4, xmm1                                           
            psraw xmm4, 1                                               

            movdqa xmm5, xmm3                                           
            psraw xmm5, 1                                               

            paddw xmm5, xmm1                                            

            psubw xmm4, xmm3                                            

            movdqa xmm3, xmm2                                           

            paddw xmm2, xmm0                                            

            psubw xmm0, xmm3                                            

            movdqa xmm3, xmm5                                           

            paddw xmm5, xmm2                                            

            psubw xmm2, xmm3                                            
            movdqa xmm3, xmm4                                           

            paddw xmm4, xmm0                                            

            psubw xmm0, xmm3                                            


            movdqa xmm1, xmm5                                           

            punpcklwd xmm5, xmm4                                        

            punpckhwd xmm1, xmm4                                        
            movdqa xmm4, xmm0                                           

            punpcklwd xmm0, xmm2                                        

            punpckhwd xmm4, xmm2                                        
            movdqa xmm2, xmm5                                           

            punpckldq xmm5, xmm0                                        

            punpckhdq xmm2, xmm0                                        
            movdqa xmm0, xmm1                                           

            punpckldq xmm1, xmm4                                        

            punpckhdq xmm0, xmm4                                        
            movdqa xmm4, xmm5                                           

            punpcklqdq xmm5, xmm1                                       

            punpckhqdq xmm4, xmm1                                       
            movdqa xmm1, xmm2                                           

            punpcklqdq xmm2, xmm0                                       

            punpckhqdq xmm1, xmm0                                       



            paddw xmm5, [ff_pw_32]                                      



        movdqa xmm0, xmm4                                           
            psraw xmm0, 1                                               

            movdqa xmm3, xmm1                                           
            psraw xmm3, 1                                               

            paddw xmm3, xmm4                                            

            psubw xmm0, xmm1                                            

            movdqa xmm1, xmm2                                           

            paddw xmm2, xmm5                                            

            psubw xmm5, xmm1                                            

            movdqa xmm1, xmm3                                           

            paddw xmm3, xmm2                                            

            psubw xmm2, xmm1                                            
            movdqa xmm1, xmm0                                           

            paddw xmm0, xmm5                                            

            psubw xmm5, xmm1                                            











            pxor xmm7, xmm7                                             

            movq xmm4, qword ptr[eax]                                            

        movq xmm1, qword ptr[eax+ebx]                                        

        psraw xmm3, 6                                               

            psraw xmm0, 6                                               

            punpcklbw xmm4, xmm7                                        

            punpcklbw xmm1, xmm7                                        

            paddw xmm4, xmm3                                            

            paddw xmm1, xmm0                                            

            packuswb xmm4, xmm7                                         

            packuswb xmm1, xmm7                                         
            movq qword ptr[eax], xmm4                                            
            movq qword ptr[eax+ebx], xmm1                                        

            lea eax, [eax+ebx*2]                                        
        movq xmm4, qword ptr[eax]                                            

        movq xmm1, qword ptr[eax+ebx]                                        

        psraw xmm5, 6                                               

            psraw xmm2, 6                                               

            punpcklbw xmm4, xmm7                                        

            punpcklbw xmm1, xmm7                                        

            paddw xmm4, xmm5                                            

            paddw xmm1, xmm2                                            

            packuswb xmm4, xmm7                                         

            packuswb xmm1, xmm7                                         
            movq qword ptr[eax], xmm4                                            
            movq qword ptr[eax+ebx], xmm1                                        

            ret
    }
}
void __declspec(naked) ff_h264_idct_add16_8_sse2(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
{
    __asm{
        push ebx                                         
            push esi                                         
            mov eax, [esp + 8 + 4 + 0*4]                     
        mov ecx, [esp + 8 + 4 + 1*4]                     
        mov edx, [esp + 8 + 4 + 2*4]                     
        mov ebx, [esp + 8 + 4 + 3*4]                     
        mov esi, [esp + 8 + 4 + 4*4]                     




        movzx eax, word ptr[esi+0xc]                        

        test eax, eax                                    
            jz ff_h264_idct_add16_8_sse2cycle0end                                    
            mov eax, dword ptr[ecx+0*8]                         
        add eax, [esp + 8 + 4]                           

        call x264_add8x4_idct_sse2                       
ff_h264_idct_add16_8_sse2cycle0end:                                        
        add edx, 64                                      

            movzx eax, word ptr[esi+0x14]                       

        test eax, eax                                    
            jz ff_h264_idct_add16_8_sse2cycle1end                                    
            mov eax, dword ptr[ecx+1*8]                         
        add eax, [esp + 8 + 4]                           

        call x264_add8x4_idct_sse2                       
ff_h264_idct_add16_8_sse2cycle1end:                                        
        add edx, 64                                      

            movzx eax, word ptr[esi+0xe]                        

        test eax, eax                                    
            jz ff_h264_idct_add16_8_sse2cycle2end                                    
            mov eax, dword ptr[ecx+2*8]                         
        add eax, [esp + 8 + 4]                           

        call x264_add8x4_idct_sse2                       
ff_h264_idct_add16_8_sse2cycle2end:                                        
        add edx, 64                                      

            movzx eax, word ptr[esi+0x16]                       

        test eax, eax                                    
            jz ff_h264_idct_add16_8_sse2cycle3end                                    
            mov eax, dword ptr[ecx+3*8]                         
        add eax, [esp + 8 + 4]                           

        call x264_add8x4_idct_sse2                       
ff_h264_idct_add16_8_sse2cycle3end:                                        
        add edx, 64                                      

            movzx eax, word ptr[esi+0x1c]                       

        test eax, eax                                    
            jz ff_h264_idct_add16_8_sse2cycle4end                                    
            mov eax, dword ptr[ecx+4*8]                         
        add eax, [esp + 8 + 4]                           

        call x264_add8x4_idct_sse2                       
ff_h264_idct_add16_8_sse2cycle4end:                                        
        add edx, 64                                      

            movzx eax, word ptr[esi+0x24]                       

        test eax, eax                                    
            jz ff_h264_idct_add16_8_sse2cycle5end                                    
            mov eax, dword ptr[ecx+5*8]                         
        add eax, [esp + 8 + 4]                           

        call x264_add8x4_idct_sse2                       
ff_h264_idct_add16_8_sse2cycle5end:                                        
        add edx, 64                                      

            movzx eax, word ptr[esi+0x1e]                       

        test eax, eax                                    
            jz ff_h264_idct_add16_8_sse2cycle6end                                    
            mov eax, dword ptr[ecx+6*8]                         
        add eax, [esp + 8 + 4]                           

        call x264_add8x4_idct_sse2                       
ff_h264_idct_add16_8_sse2cycle6end:                                        
        add edx, 64                                      

            movzx eax, word ptr[esi+0x26]                       

        test eax, eax                                    
            jz ff_h264_idct_add16_8_sse2cycle7end                                    
            mov eax, dword ptr[ecx+7*8]                         
        add eax, [esp + 8 + 4]                           

        call x264_add8x4_idct_sse2                       
ff_h264_idct_add16_8_sse2cycle7end:                                        

        pop esi                                          

            pop ebx                                          
            ret                                              
    }
}

void __declspec(naked) ff_h264_idct_add16intra_8_mmx(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        xor edi, edi                                     

ff_h264_idct_add16intra_8_mmxnextblock:                                        
        movzx ebp, byte ptr[scan8_mem+edi]                  
        movzx ebp, byte ptr[esi+ebp]                        
        or bp, word ptr[edx]                                
        test ebp, ebp                                    
            jz ff_h264_idct_add16intra_8_mmxskipblock                                    
            mov ebp, dword ptr[ecx+edi*4]                       
        add ebp, eax                                     


            movq mm0, [edx]                                  
        movq mm1, [edx+8]                                
        movq mm2, [edx+16]                               
        movq mm3, [edx+24]                               


        movq mm4, mm1                                    
            psraw mm4, 1                                     

            movq mm5, mm3                                    
            psraw mm5, 1                                     

            paddw mm5, mm1                                   

            psubw mm4, mm3                                   

            movq mm3, mm2                                    

            paddw mm2, mm0                                   

            psubw mm0, mm3                                   

            movq mm3, mm5                                    

            paddw mm5, mm2                                   

            psubw mm2, mm3                                   
            movq mm3, mm4                                    

            paddw mm4, mm0                                   

            psubw mm0, mm3                                   

            movq mm6, [ff_pw_32]                             
        movq mm1, mm5                                    

            punpcklwd mm5, mm4                               

            punpckhwd mm1, mm4                               
            movq mm4, mm0                                    

            punpcklwd mm0, mm2                               

            punpckhwd mm4, mm2                               
            movq mm2, mm5                                    

            punpckldq mm5, mm0                               

            punpckhdq mm2, mm0                               
            movq mm0, mm1                                    

            punpckldq mm1, mm4                               

            punpckhdq mm0, mm4                               

            paddw mm5, mm6                                   

            movq mm4, mm2                                    
            psraw mm4, 1                                     

            movq mm3, mm0                                    
            psraw mm3, 1                                     

            paddw mm3, mm2                                   

            psubw mm4, mm0                                   

            movq mm0, mm1                                    

            paddw mm1, mm5                                   

            psubw mm5, mm0                                   

            movq mm0, mm3                                    

            paddw mm3, mm1                                   

            psubw mm1, mm0                                   
            movq mm0, mm4                                    

            paddw mm4, mm5                                   

            psubw mm5, mm0                                   

            pxor mm7, mm7                                    

            movd mm2, [ebp]                                  
        movd mm0, [ebp+ebx]                              

        psraw mm3, 6                                     

            psraw mm4, 6                                     

            punpcklbw mm2, mm7                               

            punpcklbw mm0, mm7                               

            paddw mm2, mm3                                   

            paddw mm0, mm4                                   

            packuswb mm2, mm7                                

            packuswb mm0, mm7                                
            movd [ebp], mm2                                  
            movd [ebp+ebx], mm0                              
            lea ebp, [ebp+ebx*2]                             
        movd mm2, [ebp]                                  
        movd mm0, [ebp+ebx]                              

        psraw mm5, 6                                     

            psraw mm1, 6                                     

            punpcklbw mm2, mm7                               

            punpcklbw mm0, mm7                               

            paddw mm2, mm5                                   

            paddw mm0, mm1                                   

            packuswb mm2, mm7                                

            packuswb mm0, mm7                                
            movd [ebp], mm2                                  
            movd [ebp+ebx], mm0                              

ff_h264_idct_add16intra_8_mmxskipblock:                                        
        inc edi                                          
            add edx, 32                                      
            cmp edi, 16                                      
            jl ff_h264_idct_add16intra_8_mmxnextblock                                    
            pop ebp                                          

            pop edi                                          
            pop esi                                          
            pop ebx                                          
            ret                                              

    }
}
void __declspec(naked) ff_h264_idct_add16intra_8_mmx2(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        xor edi, edi                                    

ff_h264_idct_add16intra_8_mmx2nextblock:
        movzx ebp, byte ptr[scan8_mem+edi]                 
        movzx ebp, byte ptr[esi+ebp]                       
        test ebp, ebp                                   
            jz ff_h264_idct_add16intra_8_mmx2try_dc                                      
            mov ebp, dword ptr[ecx+edi*4]                      
        lea ebp, [eax+ebp]                              


        movq mm0, [edx]                                 
        movq mm1, [edx+8]                               
        movq mm2, [edx+16]                              
        movq mm3, [edx+24]                              


        movq mm4, mm1                                   
            psraw mm4, 1                                    

            movq mm5, mm3                                   
            psraw mm5, 1                                    

            paddw mm5, mm1                                  

            psubw mm4, mm3                                  

            movq mm3, mm2                                   

            paddw mm2, mm0                                  

            psubw mm0, mm3                                  

            movq mm3, mm5                                   

            paddw mm5, mm2                                  

            psubw mm2, mm3                                  
            movq mm3, mm4                                   

            paddw mm4, mm0                                  

            psubw mm0, mm3                                  

            movq mm6, [ff_pw_32]                            
        movq mm1, mm5                                   

            punpcklwd mm5, mm4                              

            punpckhwd mm1, mm4                              
            movq mm4, mm0                                   

            punpcklwd mm0, mm2                              

            punpckhwd mm4, mm2                              
            movq mm2, mm5                                   

            punpckldq mm5, mm0                              

            punpckhdq mm2, mm0                              
            movq mm0, mm1                                   

            punpckldq mm1, mm4                              

            punpckhdq mm0, mm4                              

            paddw mm5, mm6                                  

            movq mm4, mm2                                   
            psraw mm4, 1                                    

            movq mm3, mm0                                   
            psraw mm3, 1                                    

            paddw mm3, mm2                                  

            psubw mm4, mm0                                  

            movq mm0, mm1                                   

            paddw mm1, mm5                                  

            psubw mm5, mm0                                  

            movq mm0, mm3                                   

            paddw mm3, mm1                                  

            psubw mm1, mm0                                  
            movq mm0, mm4                                   

            paddw mm4, mm5                                  

            psubw mm5, mm0                                  

            pxor mm7, mm7                                   

            movd mm2, [ebp]                                 
        movd mm0, [ebp+ebx]                             

        psraw mm3, 6                                    

            psraw mm4, 6                                    

            punpcklbw mm2, mm7                              

            punpcklbw mm0, mm7                              

            paddw mm2, mm3                                  

            paddw mm0, mm4                                  

            packuswb mm2, mm7                               

            packuswb mm0, mm7                               
            movd [ebp], mm2                                 
            movd [ebp+ebx], mm0                             
            lea ebp, [ebp+ebx*2]                            
        movd mm2, [ebp]                                 
        movd mm0, [ebp+ebx]                             

        psraw mm5, 6                                    

            psraw mm1, 6                                    

            punpcklbw mm2, mm7                              

            punpcklbw mm0, mm7                              

            paddw mm2, mm5                                  

            paddw mm0, mm1                                  

            packuswb mm2, mm7                               

            packuswb mm0, mm7                               
            movd [ebp], mm2                                 
            movd [ebp+ebx], mm0                             

            inc edi                                         
            add edx, 32                                     
            cmp edi, 16                                     
            jl ff_h264_idct_add16intra_8_mmx2nextblock                                   
            pop ebp                                         

            pop edi                                         
            pop esi                                         
            pop ebx                                         
            ret                                             

ff_h264_idct_add16intra_8_mmx2try_dc:
        movsx ebp, word ptr[edx]                           
        test ebp, ebp                                   
            jz ff_h264_idct_add16intra_8_mmx2skipblock                                   
            add ebp, 32                                     

            sar ebp, 6                                      
            movd mm3, ebp                                   
            lea ebp, [ebx+ebx*2]                                
        pshufw mm3, mm3, 0                              

            pxor mm4, mm4                                   

            psubw mm4, mm3                                  

            packuswb mm3, mm3                               

            packuswb mm4, mm4                               

            mov ecx, dword ptr[ecx+edi*4]                      
        add ecx, eax                                    
            movd mm5, [ecx ]                                

        movd mm1, [ecx+ebx ]                            
        movd mm2, [ecx+ebx*2]                           
        movd mm0, [ecx+ebp ]                            

        paddusb mm5, mm3                                

            paddusb mm1, mm3                                

            paddusb mm2, mm3                                

            paddusb mm0, mm3                                

            psubusb mm5, mm4                                

            psubusb mm1, mm4                                

            psubusb mm2, mm4                                

            psubusb mm0, mm4                                
            movd [ecx ], mm5                                
            movd [ecx+ebx ], mm1                            
            movd [ecx+ebx*2], mm2                           
            movd [ecx+ebp ], mm0                            

            mov ecx, [esp + 16 + 8]                         

ff_h264_idct_add16intra_8_mmx2skipblock:                                       
        inc edi                                         
            add edx, 32                                     
            cmp edi, 16                                     
            jl ff_h264_idct_add16intra_8_mmx2nextblock                                   
            pop ebp                                         

            pop edi                                         
            pop esi                                         
            pop ebx                                         
            ret                                             

    }
}

void __declspec(naked) h264_idct_dc_add8_mmx2()
{
    __asm{
        movd mm0, [edx ]                                  


        punpcklwd mm0, [edx+32]                           



        paddsw mm0, [ff_pw_32]                            



        psraw mm0, 6                                      


            punpcklwd mm0, mm0                                

            pxor mm1, mm1                                     

            psubw mm1, mm0

            packuswb mm0, mm1                                 

            pshufw mm1, mm0, 0xFA                             


            punpcklwd mm0, mm0                                

            lea ebp, [ebx+ebx*2]                                  
        movq mm2, [eax ]                                  

        movq mm3, [eax+ebx ]                              
        movq mm4, [eax+ebx*2]                             
        movq mm5, [eax+ebp ]                              

        paddusb mm2, mm0                                  

            paddusb mm3, mm0                                  

            paddusb mm4, mm0                                  

            paddusb mm5, mm0                                  

            psubusb mm2, mm1                                  

            psubusb mm3, mm1                                  

            psubusb mm4, mm1                                  

            psubusb mm5, mm1                                  
            movq [eax ], mm2                                  
            movq [eax+ebx ], mm3                              
            movq [eax+ebx*2], mm4                             
            movq [eax+ebp ], mm5                              

            ret                                               
    }
}

void __declspec(naked) ff_h264_idct_add16intra_8_sse2(uint8_t *dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        movzx eax, word ptr[esi+0xc]                  

        test eax, eax                              
            jz ff_h264_idct_add16intra_8_sse2try0dc                                 
            mov eax, dword ptr[ecx+0*8]                   
        add eax, [esp + 16 + 4]                    

        call x264_add8x4_idct_sse2                 
            jmp ff_h264_idct_add16intra_8_sse2cycle0end                             
ff_h264_idct_add16intra_8_sse2try0dc:                                     
        movsx eax, word ptr[edx ]                     
        or ax, word ptr[edx+32]                       
        jz ff_h264_idct_add16intra_8_sse2cycle0end                              
            mov eax, dword ptr[ecx+0*8]                   
        add eax, [esp + 16 + 4]                    

        call h264_idct_dc_add8_mmx2                
ff_h264_idct_add16intra_8_sse2cycle0end:
        add edx, 64                                

            movzx eax, word ptr[esi+0x14]                 

        test eax, eax                              
            jz ff_h264_idct_add16intra_8_sse2try1dc                                 
            mov eax, dword ptr[ecx+1*8]                   
        add eax, [esp + 16 + 4]                    

        call x264_add8x4_idct_sse2                 
            jmp ff_h264_idct_add16intra_8_sse2cycle1end                             
ff_h264_idct_add16intra_8_sse2try1dc:                                     
        movsx eax, word ptr[edx ]                     
        or ax, word ptr[edx+32]                       
        jz ff_h264_idct_add16intra_8_sse2cycle1end                              
            mov eax, dword ptr[ecx+1*8]                   
        add eax, [esp + 16 + 4]                    

        call h264_idct_dc_add8_mmx2                
ff_h264_idct_add16intra_8_sse2cycle1end:
        add edx, 64                                

            movzx eax, word ptr[esi+0xe]                  

        test eax, eax                              
            jz ff_h264_idct_add16intra_8_sse2try2dc                                 
            mov eax, dword ptr[ecx+2*8]                   
        add eax, [esp + 16 + 4]                    

        call x264_add8x4_idct_sse2                 
            jmp ff_h264_idct_add16intra_8_sse2cycle2end                             
ff_h264_idct_add16intra_8_sse2try2dc:
        movsx eax, word ptr[edx ]                     
        or ax, word ptr[edx+32]                       
        jz ff_h264_idct_add16intra_8_sse2cycle2end                              
            mov eax, dword ptr[ecx+2*8]                   
        add eax, [esp + 16 + 4]                    

        call h264_idct_dc_add8_mmx2                
ff_h264_idct_add16intra_8_sse2cycle2end:
        add edx, 64                                

            movzx eax, word ptr[esi+0x16]                 

        test eax, eax                              
            jz ff_h264_idct_add16intra_8_sse2try3dc                                 
            mov eax, dword ptr[ecx+3*8]                   
        add eax, [esp + 16 + 4]                    

        call x264_add8x4_idct_sse2                 
            jmp ff_h264_idct_add16intra_8_sse2cycle3end                             
ff_h264_idct_add16intra_8_sse2try3dc:
        movsx eax, word ptr[edx ]                     
        or ax, word ptr[edx+32]                       
        jz ff_h264_idct_add16intra_8_sse2cycle3end                              
            mov eax, dword ptr[ecx+3*8]                   
        add eax, [esp + 16 + 4]                    

        call h264_idct_dc_add8_mmx2                
ff_h264_idct_add16intra_8_sse2cycle3end:
        add edx, 64                                

            movzx eax, word ptr[esi+0x1c]                 

        test eax, eax                              
            jz ff_h264_idct_add16intra_8_sse2try4dc                                 
            mov eax, dword ptr[ecx+4*8]                   
        add eax, [esp + 16 + 4]                    

        call x264_add8x4_idct_sse2                 
            jmp ff_h264_idct_add16intra_8_sse2cycle4end                             
ff_h264_idct_add16intra_8_sse2try4dc:                                     
        movsx eax, word ptr[edx ]                     
        or ax, word ptr[edx+32]                       
        jz ff_h264_idct_add16intra_8_sse2cycle4end                              
            mov eax, dword ptr[ecx+4*8]                   
        add eax, [esp + 16 + 4]                    

        call h264_idct_dc_add8_mmx2                
ff_h264_idct_add16intra_8_sse2cycle4end:                                  
        add edx, 64                                

            movzx eax, word ptr[esi+0x24]                 

        test eax, eax                              
            jz ff_h264_idct_add16intra_8_sse2try5dc                                 
            mov eax, dword ptr[ecx+5*8]                   
        add eax, [esp + 16 + 4]                    

        call x264_add8x4_idct_sse2                 
            jmp ff_h264_idct_add16intra_8_sse2cycle5end                             
ff_h264_idct_add16intra_8_sse2try5dc:                                     
        movsx eax, word ptr[edx ]                     
        or ax, word ptr[edx+32]                       
        jz ff_h264_idct_add16intra_8_sse2cycle5end                              
            mov eax, dword ptr[ecx+5*8]                   
        add eax, [esp + 16 + 4]                    

        call h264_idct_dc_add8_mmx2                
ff_h264_idct_add16intra_8_sse2cycle5end:                                  
        add edx, 64                                

            movzx eax, word ptr[esi+0x1e]                 

        test eax, eax                              
            jz ff_h264_idct_add16intra_8_sse2try6dc                                 
            mov eax, dword ptr[ecx+6*8]                   
        add eax, [esp + 16 + 4]                    

        call x264_add8x4_idct_sse2                 
            jmp ff_h264_idct_add16intra_8_sse2cycle6end                             
ff_h264_idct_add16intra_8_sse2try6dc:                                     
        movsx eax, word ptr[edx ]                     
        or ax, word ptr[edx+32]                       
        jz ff_h264_idct_add16intra_8_sse2cycle6end                              
            mov eax, dword ptr[ecx+6*8]                   
        add eax, [esp + 16 + 4]                    

        call h264_idct_dc_add8_mmx2                
ff_h264_idct_add16intra_8_sse2cycle6end:                                  
        add edx, 64                                

            movzx eax, word ptr[esi+0x26]                 

        test eax, eax                              
            jz ff_h264_idct_add16intra_8_sse2try7dc                                 
            mov eax, dword ptr[ecx+7*8]                   
        add eax, [esp + 16 + 4]                    

        call x264_add8x4_idct_sse2                 
            jmp ff_h264_idct_add16intra_8_sse2cycle7end                             
ff_h264_idct_add16intra_8_sse2try7dc:                                     
        movsx eax, word ptr[edx ]                     
        or ax, word ptr[edx+32]                       
        jz ff_h264_idct_add16intra_8_sse2cycle7end                              
            mov eax, dword ptr[ecx+7*8]                   
        add eax, [esp + 16 + 4]                    

        call h264_idct_dc_add8_mmx2                
ff_h264_idct_add16intra_8_sse2cycle7end:                                  

        pop ebp                                    

            pop edi                                    
            pop esi                                    
            pop ebx                                    
            ret                                        

    }
}
void __declspec(naked) h264_idct_add8_mmx_plane()
{
    __asm{
h264_idct_add8_mmx_planenextblock:                                               
        movzx ebp, byte ptr[scan8_mem+edi]                         
        movzx ebp, byte ptr[esi+ebp]                               
        or bp, word ptr[edx]                                       
        test ebp, ebp                                           
            jz h264_idct_add8_mmx_planeskipblock                                           

            mov eax, [esp + 16 + 8]                                 
        mov eax, [eax]                                          
        add eax, dword ptr[ecx+edi*4]                              



        movq mm0, [edx]                                         
        movq mm1, [edx+8]                                       
        movq mm2, [edx+16]                                      
        movq mm3, [edx+24]                                      


        movq mm4, mm1                                           
            psraw mm4, 1                                            

            movq mm5, mm3                                           
            psraw mm5, 1                                            

            paddw mm5, mm1                                          

            psubw mm4, mm3                                          

            movq mm3, mm2                                           

            paddw mm2, mm0                                          

            psubw mm0, mm3                                          

            movq mm3, mm5                                           

            paddw mm5, mm2                                          

            psubw mm2, mm3                                          
            movq mm3, mm4                                           

            paddw mm4, mm0                                          

            psubw mm0, mm3                                          








            movq mm6, [ff_pw_32]                                    
        movq mm1, mm5                                           

            punpcklwd mm5, mm4                                      

            punpckhwd mm1, mm4                                      
            movq mm4, mm0                                           

            punpcklwd mm0, mm2                                      

            punpckhwd mm4, mm2                                      
            movq mm2, mm5                                           

            punpckldq mm5, mm0                                      

            punpckhdq mm2, mm0                                      
            movq mm0, mm1                                           

            punpckldq mm1, mm4                                      

            punpckhdq mm0, mm4                                      

            paddw mm5, mm6                                          

            movq mm4, mm2                                           
            psraw mm4, 1                                            

            movq mm3, mm0                                           
            psraw mm3, 1                                            

            paddw mm3, mm2                                          

            psubw mm4, mm0                                          

            movq mm0, mm1                                           

            paddw mm1, mm5                                          

            psubw mm5, mm0                                          

            movq mm0, mm3                                           

            paddw mm3, mm1                                          

            psubw mm1, mm0                                          
            movq mm0, mm4                                           

            paddw mm4, mm5                                          

            psubw mm5, mm0                                          









            pxor mm7, mm7                                           

            movd mm2, [eax]                                         
        movd mm0, [eax+ebx]                                     

        psraw mm3, 6                                            

            psraw mm4, 6                                            

            punpcklbw mm2, mm7                                      

            punpcklbw mm0, mm7                                      

            paddw mm2, mm3                                          

            paddw mm0, mm4                                          

            packuswb mm2, mm7                                       

            packuswb mm0, mm7                                       
            movd [eax], mm2                                         
            movd [eax+ebx], mm0                                     
            lea eax, [eax+ebx*2]                                    
        movd mm2, [eax]                                         
        movd mm0, [eax+ebx]                                     

        psraw mm5, 6                                            

            psraw mm1, 6                                            

            punpcklbw mm2, mm7                                      

            punpcklbw mm0, mm7                                      

            paddw mm2, mm5                                          

            paddw mm0, mm1                                          

            packuswb mm2, mm7                                       

            packuswb mm0, mm7                                       
            movd [eax], mm2                                         
            movd [eax+ebx], mm0                                     

h264_idct_add8_mmx_planeskipblock:                                               
        inc edi                                                 
            add edx, 32                                             
            test edi, 3                                             
            jnz h264_idct_add8_mmx_planenextblock                                          
            rep ret
    }
}

void __declspec(naked) ff_h264_idct_add8_8_mmx(uint8_t **dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        mov edi, 16                                       
            add edx, 512                                                     

            call h264_idct_add8_mmx_plane                     

            mov edi, 32                                       
            add edx, 384                                      

            add dword ptr[esp + 16 + 4], 4



            call h264_idct_add8_mmx_plane                     

            pop ebp                                           

            pop edi                                           
            pop esi                                           
            pop ebx                                           
            ret                                               

    }
}
void __declspec(naked)  h264_idct_add8_mmx2_plane()
{
    __asm{
h264_idct_add8_mmx2_planenextblock:
        movzx ebp, byte ptr[scan8_mem+edi]                      
        movzx ebp, byte ptr[esi+ebp]                            
        test ebp, ebp                                        
            jz h264_idct_add8_mmx2_planetry_dc                                           

            mov eax, [esp + 16 + 8]                              
        mov eax, [eax]                                       
        add eax, dword ptr[ecx+edi*4]                           



        movq mm0, [edx]                                      
        movq mm1, [edx+8]                                    
        movq mm2, [edx+16]                                   
        movq mm3, [edx+24]                                   


        movq mm4, mm1                                        
            psraw mm4, 1                                         

            movq mm5, mm3                                        
            psraw mm5, 1                                         

            paddw mm5, mm1                                       

            psubw mm4, mm3                                       

            movq mm3, mm2                                        

            paddw mm2, mm0                                       

            psubw mm0, mm3                                       

            movq mm3, mm5                                        

            paddw mm5, mm2                                       

            psubw mm2, mm3                                       
            movq mm3, mm4                                        

            paddw mm4, mm0                                       

            psubw mm0, mm3                                       








            movq mm6, [ff_pw_32]                                 
        movq mm1, mm5                                        

            punpcklwd mm5, mm4                                   

            punpckhwd mm1, mm4                                   
            movq mm4, mm0                                        

            punpcklwd mm0, mm2                                   

            punpckhwd mm4, mm2                                   
            movq mm2, mm5                                        

            punpckldq mm5, mm0                                   

            punpckhdq mm2, mm0                                   
            movq mm0, mm1                                        

            punpckldq mm1, mm4                                   

            punpckhdq mm0, mm4                                   

            paddw mm5, mm6                                       

            movq mm4, mm2                                        
            psraw mm4, 1                                         

            movq mm3, mm0                                        
            psraw mm3, 1                                         

            paddw mm3, mm2                                       

            psubw mm4, mm0                                       

            movq mm0, mm1                                        

            paddw mm1, mm5                                       

            psubw mm5, mm0                                       

            movq mm0, mm3                                        

            paddw mm3, mm1                                       

            psubw mm1, mm0                                       
            movq mm0, mm4                                        

            paddw mm4, mm5                                       

            psubw mm5, mm0                                       









            pxor mm7, mm7                                        

            movd mm2, [eax]                                      
        movd mm0, [eax+ebx]                                  

        psraw mm3, 6                                         

            psraw mm4, 6                                         

            punpcklbw mm2, mm7                                   

            punpcklbw mm0, mm7                                   

            paddw mm2, mm3                                       

            paddw mm0, mm4                                       

            packuswb mm2, mm7                                    

            packuswb mm0, mm7                                    
            movd [eax], mm2                                      
            movd [eax+ebx], mm0                                  
            lea eax, [eax+ebx*2]                                 
        movd mm2, [eax]                                      
        movd mm0, [eax+ebx]                                  

        psraw mm5, 6                                         

            psraw mm1, 6                                         

            punpcklbw mm2, mm7                                   

            punpcklbw mm0, mm7                                   

            paddw mm2, mm5                                       

            paddw mm0, mm1                                       

            packuswb mm2, mm7                                    

            packuswb mm0, mm7                                    
            movd [eax], mm2                                      
            movd [eax+ebx], mm0                                  

            inc edi                                              
            add edx, 32                                          
            test edi, 3                                          
            jnz h264_idct_add8_mmx2_planenextblock                                       
            rep ret                                              
h264_idct_add8_mmx2_planetry_dc:                                               
        movsx ebp, word ptr[edx]                                
        test ebp, ebp                                        
            jz h264_idct_add8_mmx2_planeskipblock                                        
            add ebp, 32                                          

            sar ebp, 6                                           
            movd mm3, ebp                                        
            lea ebp, [ebx+ebx*2]                                     
        pshufw mm3, mm3, 0                                   

            pxor mm4, mm4                                        

            psubw mm4, mm3                                       

            packuswb mm3, mm3                                    

            packuswb mm4, mm4                                    

            mov eax, [esp + 16 + 8]                              
        mov eax, [eax]                                       
        add eax, dword ptr[ecx+edi*4]                           

        movd mm5, [eax ]                                     

        movd mm1, [eax+ebx ]                                 
        movd mm2, [eax+ebx*2]                                
        movd mm0, [eax+ebp ]                                 

        paddusb mm5, mm3                                     

            paddusb mm1, mm3                                     

            paddusb mm2, mm3                                     

            paddusb mm0, mm3                                     

            psubusb mm5, mm4                                     

            psubusb mm1, mm4                                     

            psubusb mm2, mm4                                     

            psubusb mm0, mm4                                     
            movd [eax ], mm5                                     
            movd [eax+ebx ], mm1                                 
            movd [eax+ebx*2], mm2                                
            movd [eax+ebp ], mm0                                 

h264_idct_add8_mmx2_planeskipblock:                                            
        inc edi                                              
            add edx, 32                                          
            test edi, 3                                          
            jnz h264_idct_add8_mmx2_planenextblock                                       
            rep ret
    }
}




void __declspec(naked) ff_h264_idct_add8_8_mmx2(uint8_t **dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        mov edi, 16                                   
            add edx, 512                                  



            call h264_idct_add8_mmx2_plane                

            mov edi, 32                                   
            add edx, 384   
            add dword ptr[esp + 16 + 4], 4   
            call h264_idct_add8_mmx2_plane   
            pop ebp                                       

            pop edi                                       
            pop esi                                       
            pop ebx                                       
            ret
    }
}
void __declspec(naked) ff_h264_idct_add8_8_sse2(uint8_t **dst, const int *block_offset,DCTELEM *block, int stride, const uint8_t nnzc[6*8])
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


        add edx, 512                                                 

            movzx eax, word ptr[esi+0x34]                                   

        test eax, eax                                                
            jz ff_h264_idct_add8_8_sse2try0dc                                                   
            mov eax, [esp + 16 + 4]                                      
        mov eax, [eax]                                               
        add eax, dword ptr[ecx+(0&1)*8+64*(1+(0>>1))]                   

        call x264_add8x4_idct_sse2                                   
            jmp ff_h264_idct_add8_8_sse2cycle0end                                               
ff_h264_idct_add8_8_sse2try0dc:                                                       
        movsx eax, word ptr[edx ]                                       
        or ax, word ptr[edx+32]                                         
        jz ff_h264_idct_add8_8_sse2cycle0end                                                
            mov eax, [esp + 16 + 4]                                      
        mov eax, [eax]                                               
        add eax, dword ptr[ecx+(0&1)*8+64*(1+(0>>1))]                   

        call h264_idct_dc_add8_mmx2                                  
ff_h264_idct_add8_8_sse2cycle0end:
        add edx, 64                                                  

            movzx eax, word ptr[esi+0x3c]                                   

        test eax, eax                                                
            jz ff_h264_idct_add8_8_sse2try1dc                                                   
            mov eax, [esp + 16 + 4]                                      
        mov eax, [eax]                                               
        add eax, dword ptr[ecx+(1&1)*8+64*(1+(1>>1))]                   

        call x264_add8x4_idct_sse2                                   
            jmp ff_h264_idct_add8_8_sse2cycle1end                                               
ff_h264_idct_add8_8_sse2try1dc:
        movsx eax, word ptr[edx ]                                       
        or ax, word ptr[edx+32]                                         
        jz ff_h264_idct_add8_8_sse2cycle1end                                                
            mov eax, [esp + 16 + 4]                                      
        mov eax, [eax]                                               
        add eax, dword ptr[ecx+(1&1)*8+64*(1+(1>>1))]                   

        call h264_idct_dc_add8_mmx2                                  
ff_h264_idct_add8_8_sse2cycle1end:
        add edx, 384+64                                              

            add dword ptr[esp + 16 + 4], 4                                  

            movzx eax, word ptr[esi+0x5c]                                   

        test eax, eax                                                
            jz ff_h264_idct_add8_8_sse2try2dc                                                   
            mov eax, [esp + 16 + 4]                                      
        mov eax, [eax]                                               
        add eax, dword ptr[ecx+(2&1)*8+64*(1+(2>>1))]                   

        call x264_add8x4_idct_sse2                                   
            jmp ff_h264_idct_add8_8_sse2cycle2end                                               
ff_h264_idct_add8_8_sse2try2dc:
        movsx eax, word ptr[edx ]                                       
        or ax, word ptr[edx+32]                                         
        jz ff_h264_idct_add8_8_sse2cycle2end                                                
            mov eax, [esp + 16 + 4]                                      
        mov eax, [eax]                                               
        add eax, dword ptr[ecx+(2&1)*8+64*(1+(2>>1))]                   

        call h264_idct_dc_add8_mmx2                                  
ff_h264_idct_add8_8_sse2cycle2end:
        add edx, 64                                                  

            movzx eax, word ptr[esi+0x64]                                   

        test eax, eax                                                
            jz ff_h264_idct_add8_8_sse2try3dc                                                   
            mov eax, [esp + 16 + 4]                                      
        mov eax, [eax]                                               
        add eax, dword ptr[ecx+(3&1)*8+64*(1+(3>>1))]                   

        call x264_add8x4_idct_sse2                                   
            jmp ff_h264_idct_add8_8_sse2cycle3end                                               
ff_h264_idct_add8_8_sse2try3dc:                                                       
        movsx eax, word ptr[edx ]                                       
        or ax, word ptr[edx+32]                                         
        jz ff_h264_idct_add8_8_sse2cycle3end                                                
            mov eax, [esp + 16 + 4]                                      
        mov eax, [eax]                                               
        add eax, dword ptr[ecx+(3&1)*8+64*(1+(3>>1))]                   

        call h264_idct_dc_add8_mmx2                                  
ff_h264_idct_add8_8_sse2cycle3end:                                                    

        pop ebp  
            pop edi                                                      
            pop esi                                                      
            pop ebx                                                      
            ret
    }
}

void __declspec(naked) ff_h264_luma_dc_dequant_idct_mmx(DCTELEM *output, DCTELEM *input, int qmul)
{
    __asm{
        push ebx                                                     
            mov eax, [esp + 4 + 4 + 0*4]                                 
        mov ecx, [esp + 4 + 4 + 1*4]                                 
        mov edx, [esp + 4 + 4 + 2*4]                                 



        movq mm3, [ecx+24]                                           
        movq mm2, [ecx+16]                                           
        movq mm1, [ecx+ 8]                                           
        movq mm0, [ecx+ 0]                                           
        movq mm4, mm3                                                

            paddw mm3, mm2                                               

            psubw mm2, mm4                                               
            movq mm4, mm1                                                

            paddw mm1, mm0                                               

            psubw mm0, mm4                                               
            movq mm4, mm3                                                

            paddw mm3, mm1                                               

            psubw mm1, mm4                                               
            movq mm4, mm2                                                

            paddw mm2, mm0                                               

            psubw mm0, mm4                                               
            movq mm4, mm3                                                

            punpcklwd mm3, mm1                                           

            punpckhwd mm4, mm1                                           
            movq mm1, mm0                                                

            punpcklwd mm0, mm2                                           

            punpckhwd mm1, mm2                                           
            movq mm2, mm3                                                

            punpckldq mm3, mm0                                           

            punpckhdq mm2, mm0                                           
            movq mm0, mm4                                                

            punpckldq mm4, mm1                                           

            punpckhdq mm0, mm1                                           
            movq mm1, mm0                                                

            paddw mm0, mm4                                               

            psubw mm4, mm1                                               
            movq mm1, mm2                                                

            paddw mm2, mm3                                               

            psubw mm3, mm1                                               
            movq mm1, mm0                                                

            paddw mm0, mm2                                               

            psubw mm2, mm1                                               
            movq mm1, mm4                                                

            paddw mm4, mm3                                               

            psubw mm3, mm1                                               



            cmp edx, 32767                                               
            jg ff_h264_luma_dc_dequant_idct_mmxbig_qmul                  
            add edx, 128 << 16                                           
            movq mm7, [ff_pw_1]                                          
        movq mm1, mm0                                                

            punpcklwd mm0, mm7                                           

            punpckhwd mm1, mm7                                           
            movq mm5, mm2                                                

            punpcklwd mm2, mm7                                           

            punpckhwd mm5, mm7                                           
            movd mm7, edx                                                

            punpckldq mm7, mm7                                           

            pmaddwd mm0, mm7                                             

            pmaddwd mm2, mm7                                             

            pmaddwd mm1, mm7                                             

            pmaddwd mm5, mm7                                             

            psrad mm0, 8                                                 

            psrad mm2, 8                                                 

            psrad mm1, 8                                                 

            psrad mm5, 8                                                 

            packssdw mm0, mm1                                            

            packssdw mm2, mm5                                            
            movd ecx, mm0                                                

            psrlq mm0, 32                                                
            movd ebx, mm0                                                
            mov [eax+0*32], cx                                           
            mov [eax+4*32], bx                                           
            shr ecx, 16                                                  
            shr ebx, 16                                                  
            mov [eax+1*32], cx                                           
            mov [eax+5*32], bx                                           
            movd ecx, mm2                                                

            psrlq mm2, 32                                                
            movd ebx, mm2                                                
            mov [eax+2*32], cx                                           
            mov [eax+6*32], bx                                           
            shr ecx, 16                                                  
            shr ebx, 16                                                  
            mov [eax+3*32], cx                                           
            mov [eax+7*32], bx                                           

            movq mm7, [ff_pw_1]                                          
        movq mm1, mm3                                                

            punpcklwd mm3, mm7                                           

            punpckhwd mm1, mm7                                           
            movq mm5, mm4                                                

            punpcklwd mm4, mm7                                           

            punpckhwd mm5, mm7                                           
            movd mm7, edx                                                

            punpckldq mm7, mm7                                           

            pmaddwd mm3, mm7                                             

            pmaddwd mm4, mm7                                             

            pmaddwd mm1, mm7                                             

            pmaddwd mm5, mm7                                             

            psrad mm3, 8                                                 

            psrad mm4, 8                                                 

            psrad mm1, 8                                                 

            psrad mm5, 8                                                 

            packssdw mm3, mm1                                            

            packssdw mm4, mm5                                            
            movd ecx, mm3                                                

            psrlq mm3, 32                                                
            movd ebx, mm3                                                
            mov [eax+8*32], cx                                           
            mov [eax+12*32], bx                                          
            shr ecx, 16                                                  
            shr ebx, 16                                                  
            mov [eax+9*32], cx                                           
            mov [eax+13*32], bx                                          
            movd ecx, mm4                                                

            psrlq mm4, 32                                                
            movd ebx, mm4                                                
            mov [eax+10*32], cx                                          
            mov [eax+14*32], bx                                          
            shr ecx, 16                                                  
            shr ebx, 16                                                  
            mov [eax+11*32], cx                                          
            mov [eax+15*32], bx                                          
            pop ebx                                                      
            ret                                                          
ff_h264_luma_dc_dequant_idct_mmxbig_qmul:                     
        bsr ecx, edx                                                 
            add edx, 128 << 16                                           
            mov ebx, 7                                                   
            cmp ecx, ebx                                                 
            cmovg ecx, ebx                                               
            inc ebx                                                      
            shr edx, cl                                                  
            sub ebx, ecx                                                 
            movd mm6, ebx                                                
            movq mm7, [ff_pw_1]                                          
        movq mm1, mm0                                                

            punpcklwd mm0, mm7                                           

            punpckhwd mm1, mm7                                           
            movq mm5, mm2                                                

            punpcklwd mm2, mm7                                           

            punpckhwd mm5, mm7                                           
            movd mm7, edx                                                

            punpckldq mm7, mm7                                           

            pmaddwd mm0, mm7                                             

            pmaddwd mm2, mm7                                             

            pmaddwd mm1, mm7                                             

            pmaddwd mm5, mm7                                             

            psrad mm0, mm6                                               

            psrad mm2, mm6                                               

            psrad mm1, mm6                                               

            psrad mm5, mm6                                               

            packssdw mm0, mm1                                            

            packssdw mm2, mm5                                            
            movd ecx, mm0                                                

            psrlq mm0, 32                                                
            movd ebx, mm0                                                
            mov [eax+0*32], cx                                           
            mov [eax+4*32], bx                                           
            shr ecx, 16                                                  
            shr ebx, 16                                                  
            mov [eax+1*32], cx                                           
            mov [eax+5*32], bx                                           
            movd ecx, mm2                                                

            psrlq mm2, 32                                                
            movd ebx, mm2                                                
            mov [eax+2*32], cx                                           
            mov [eax+6*32], bx                                           
            shr ecx, 16                                                  
            shr ebx, 16                                                  
            mov [eax+3*32], cx                                           
            mov [eax+7*32], bx                                           

            movq mm7, [ff_pw_1]                                          
        movq mm1, mm3                                                

            punpcklwd mm3, mm7                                           

            punpckhwd mm1, mm7                                           
            movq mm5, mm4                                                

            punpcklwd mm4, mm7                                           

            punpckhwd mm5, mm7                                           
            movd mm7, edx                                                

            punpckldq mm7, mm7                                           

            pmaddwd mm3, mm7                                             

            pmaddwd mm4, mm7                                             

            pmaddwd mm1, mm7                                             

            pmaddwd mm5, mm7                                             

            psrad mm3, mm6                                               

            psrad mm4, mm6                                               

            psrad mm1, mm6                                               

            psrad mm5, mm6                                               

            packssdw mm3, mm1                                            

            packssdw mm4, mm5                                            
            movd ecx, mm3                                                

            psrlq mm3, 32                                                
            movd ebx, mm3                                                
            mov [eax+8*32], cx                                           
            mov [eax+12*32], bx                                          
            shr ecx, 16                                                  
            shr ebx, 16                                                  
            mov [eax+9*32], cx                                           
            mov [eax+13*32], bx                                          
            movd ecx, mm4                                                

            psrlq mm4, 32                                                
            movd ebx, mm4                                                
            mov [eax+10*32], cx                                          
            mov [eax+14*32], bx                                          
            shr ecx, 16                                                  
            shr ebx, 16                                                  
            mov [eax+11*32], cx                                          
            mov [eax+15*32], bx                                          
            pop ebx                                                      
            ret
    }
}
void __declspec(naked) ff_h264_luma_dc_dequant_idct_sse2(DCTELEM *output, DCTELEM *input, int qmul)
{
    __asm{
        push ebx                                                    
            mov eax, [esp + 4 + 4 + 0*4]                                
        mov ecx, [esp + 4 + 4 + 1*4]                                
        mov edx, [esp + 4 + 4 + 2*4]                                



        movq mm3, [ecx+24]                                          
        movq mm2, [ecx+16]                                          
        movq mm1, [ecx+ 8]                                          
        movq mm0, [ecx+ 0]                                          
        movq mm4, mm3                                               

            paddw mm3, mm2                                              

            psubw mm2, mm4                                              
            movq mm4, mm1                                               

            paddw mm1, mm0                                              

            psubw mm0, mm4                                              
            movq mm4, mm3                                               

            paddw mm3, mm1                                              

            psubw mm1, mm4                                              
            movq mm4, mm2                                               

            paddw mm2, mm0                                              

            psubw mm0, mm4                                              
            movq mm4, mm3                                               

            punpcklwd mm3, mm1                                          

            punpckhwd mm4, mm1                                          
            movq mm1, mm0                                               

            punpcklwd mm0, mm2                                          

            punpckhwd mm1, mm2                                          
            movq mm2, mm3                                               

            punpckldq mm3, mm0                                          

            punpckhdq mm2, mm0                                          
            movq mm0, mm4                                               

            punpckldq mm4, mm1                                          

            punpckhdq mm0, mm1                                          
            movq mm1, mm0                                               

            paddw mm0, mm4                                              

            psubw mm4, mm1                                              
            movq mm1, mm2                                               

            paddw mm2, mm3                                              

            psubw mm3, mm1                                              
            movq mm1, mm0                                               

            paddw mm0, mm2                                              

            psubw mm2, mm1                                              
            movq mm1, mm4                                               

            paddw mm4, mm3                                              

            psubw mm3, mm1                                              



            cmp edx, 32767                                              
            jg ff_h264_luma_dc_dequant_idct_sse2big_qmul                
            add edx, 128 << 16                                          
            movd xmm4, edx                                              
            movq xmm5, qword ptr[ff_pw_1]                                        
        pshufd xmm4, xmm4, 0                                        
            movq2dq xmm0, mm0                                           
            movq2dq xmm1, mm2                                           
            movq2dq xmm2, mm3                                           
            movq2dq xmm3, mm4                                           

            punpcklwd xmm0, xmm5                                        

            punpcklwd xmm1, xmm5                                        

            punpcklwd xmm2, xmm5                                        

            punpcklwd xmm3, xmm5                                        

            pmaddwd xmm0, xmm4                                          

            pmaddwd xmm1, xmm4                                          

            pmaddwd xmm2, xmm4                                          

            pmaddwd xmm3, xmm4                                          

            psrad xmm0, 8                                               

            psrad xmm1, 8                                               

            psrad xmm2, 8                                               

            psrad xmm3, 8                                               

            packssdw xmm0, xmm1                                         

            packssdw xmm2, xmm3                                         
            movd ecx, xmm0                                              

            psrldq xmm0, 4                                              
            movd ebx, xmm0                                              

            psrldq xmm0, 4                                              
            mov [eax+0*32], cx                                          
            mov [eax+4*32], bx                                          
            shr ecx, 16                                                 
            shr ebx, 16                                                 
            mov [eax+1*32], cx                                          
            mov [eax+5*32], bx                                          
            movd ecx, xmm0                                              

            psrldq xmm0, 4                                              
            movd ebx, xmm0                                              
            mov [eax+2*32], cx                                          
            mov [eax+6*32], bx                                          
            shr ecx, 16                                                 
            shr ebx, 16                                                 
            mov [eax+3*32], cx                                          
            mov [eax+7*32], bx                                          
            movd ecx, xmm2                                              

            psrldq xmm2, 4                                              
            movd ebx, xmm2                                              

            psrldq xmm2, 4                                              
            mov [eax+8*32], cx                                          
            mov [eax+12*32], bx                                         
            shr ecx, 16                                                 
            shr ebx, 16                                                 
            mov [eax+9*32], cx                                          
            mov [eax+13*32], bx                                         
            movd ecx, xmm2                                              

            psrldq xmm2, 4                                              
            movd ebx, xmm2                                              
            mov [eax+10*32], cx                                         
            mov [eax+14*32], bx                                         
            shr ecx, 16                                                 
            shr ebx, 16                                                 
            mov [eax+11*32], cx                                         
            mov [eax+15*32], bx                                         
            pop ebx                                                     
            ret                                                         
ff_h264_luma_dc_dequant_idct_sse2big_qmul:                   
        bsr ecx, edx                                                
            add edx, 128 << 16                                          
            mov ebx, 7                                                  
            cmp ecx, ebx                                                
            cmovg ecx, ebx                                              
            inc ebx                                                     
            shr edx, cl                                                 
            sub ebx, ecx                                                
            movd xmm6, ebx                                              
            movd xmm4, edx                                              
            movq xmm5, qword ptr [ff_pw_1]                                        
        pshufd xmm4, xmm4, 0                                        
            movq2dq xmm0, mm0                                           
            movq2dq xmm1, mm2                                           
            movq2dq xmm2, mm3                                           
            movq2dq xmm3, mm4                                           

            punpcklwd xmm0, xmm5                                        

            punpcklwd xmm1, xmm5                                        

            punpcklwd xmm2, xmm5                                        

            punpcklwd xmm3, xmm5                                        

            pmaddwd xmm0, xmm4                                          

            pmaddwd xmm1, xmm4                                          

            pmaddwd xmm2, xmm4                                          

            pmaddwd xmm3, xmm4                                          

            psrad xmm0, xmm6                                            

            psrad xmm1, xmm6                                            

            psrad xmm2, xmm6                                            

            psrad xmm3, xmm6                                            

            packssdw xmm0, xmm1                                         

            packssdw xmm2, xmm3                                         
            movd ecx, xmm0                                              

            psrldq xmm0, 4                                              
            movd ebx, xmm0                                              

            psrldq xmm0, 4                                              
            mov [eax+0*32], cx                                          
            mov [eax+4*32], bx                                          
            shr ecx, 16                                                 
            shr ebx, 16                                                 
            mov [eax+1*32], cx                                          
            mov [eax+5*32], bx                                          
            movd ecx, xmm0                                              

            psrldq xmm0, 4                                              
            movd ebx, xmm0                                              
            mov [eax+2*32], cx                                          
            mov [eax+6*32], bx                                          
            shr ecx, 16                                                 
            shr ebx, 16                                                 
            mov [eax+3*32], cx                                          
            mov [eax+7*32], bx                                          
            movd ecx, xmm2                                              

            psrldq xmm2, 4                                              
            movd ebx, xmm2                                              

            psrldq xmm2, 4                                              
            mov [eax+8*32], cx                                          
            mov [eax+12*32], bx                                         
            shr ecx, 16                                                 
            shr ebx, 16                                                 
            mov [eax+9*32], cx                                          
            mov [eax+13*32], bx                                         
            movd ecx, xmm2                                              

            psrldq xmm2, 4                                              
            movd ebx, xmm2                                              
            mov [eax+10*32], cx                                         
            mov [eax+14*32], bx                                         
            shr ecx, 16                                                 
            shr ebx, 16                                                 
            mov [eax+11*32], cx                                         
            mov [eax+15*32], bx                                         
            pop ebx                                                     
            ret                                                         

    }
}