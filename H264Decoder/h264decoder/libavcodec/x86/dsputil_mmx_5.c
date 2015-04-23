#include "x86_opt.h"
#include "dsputil_mmx.h"



NAKED void put_mpeg4_qpel8_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        push   ebp                                               
            push   edi                                               
            push   esi                                               
            push   ebx                                               
            sub    esp,0x1c                                          
            mov    edi,DWORD PTR [esp+0x40]                          
        mov    ecx,DWORD PTR [esp+0x30]                          
        mov    eax,DWORD PTR [esp+0x34]                          
        test   edi,edi                                           
            jle    put_mpeg4_qpel8_h_lowpass_3dnow_64cb              
            lea    edx,[esp+0xc]                                     
        mov    DWORD PTR [esp+0x8],0x0                           

            mov    DWORD PTR [esp+0x4],edx                           
            mov    DWORD PTR [esp],ecx                               
            xchg   ax,ax                                             
put_mpeg4_qpel8_h_lowpass_3dnow_6250:                    
        movzx  edi,BYTE PTR [eax+0x2]                            
        movzx  edx,BYTE PTR [eax+0x4]                            
        movzx  esi,BYTE PTR [eax]                                
        movzx  ebx,BYTE PTR [eax+0x1]                            
        mov    ecx,edi                                           
            and    edi,0xff                                          
            movzx  ebp,cl                                            
            neg    edx                                               
            sub    dx,bp                                             
            add    edi,esi                                           
            lea    ebp,[ebx+esi*1]                                   
        lea    ebp,[ebp+ebp*4+0x0]                               
        lea    ebp,[edx+ebp*4]                                   
        movzx  edx,BYTE PTR [eax+0x3]                            
        lea    edi,[edi+edi*2]                                   
        add    edi,edi                                           
            sub    bp,di                                             
            lea    ebx,[edx+ebx*1]                                   
        lea    ebx,[ebx+ebx*2]                                   
        add    ebp,ebx                                           
            mov    WORD PTR [esp+0xc],bp                             
            movzx  esi,BYTE PTR [eax+0x1]                            
        movzx  edx,BYTE PTR [eax+0x5]                            
        movzx  ebx,BYTE PTR [eax]                                
        mov    ecx,esi                                           
            and    esi,0xff                                          
            movzx  edi,cl                                            
            neg    edx                                               
            sub    dx,di                                             
            movzx  edi,BYTE PTR [eax+0x2]                            
        lea    esi,[edi+esi*1]                                   
        lea    esi,[esi+esi*4]                                   
        lea    edx,[edx+esi*4]                                   
        movzx  esi,BYTE PTR [eax+0x3]                            
        add    esi,ebx                                           
            lea    esi,[esi+esi*2]                                   
        add    esi,esi                                           
            sub    dx,si                                             
            movzx  esi,BYTE PTR [eax+0x4]                            
        lea    ebx,[esi+ebx*1]                                   
        lea    ebx,[ebx+ebx*2]                                   
        add    edx,ebx                                           
            mov    WORD PTR [esp+0xe],dx                             
            movzx  ebx,BYTE PTR [eax]                                
        movzx  edx,BYTE PTR [eax+0x6]                            
        movzx  edi,BYTE PTR [eax+0x3]                            
        movzx  esi,bl                                            
            movzx  ebx,bl                                            
            neg    edx                                               
            sub    dx,si                                             
            movzx  esi,BYTE PTR [eax+0x2]                            
        lea    esi,[edi+esi*1]                                   
        movzx  edi,BYTE PTR [eax+0x4]                            
        lea    esi,[esi+esi*4]                                   
        lea    edx,[edx+esi*4]                                   
        movzx  esi,BYTE PTR [eax+0x1]                            
        lea    esi,[edi+esi*1]                                   
        lea    esi,[esi+esi*2]                                   
        add    esi,esi                                           
            sub    dx,si                                             
            movzx  esi,BYTE PTR [eax+0x5]                            
        lea    ebx,[esi+ebx*1]                                   
        lea    ebx,[ebx+ebx*2]                                   
        add    edx,ebx                                           
            mov    WORD PTR [esp+0x10],dx                            
            movzx  edx,BYTE PTR [eax+0x7]                            
        movzx  ebx,BYTE PTR [eax]                                
        movzx  esi,BYTE PTR [eax+0x4]                            
        neg    edx                                               
            sub    dx,bx                                             
            movzx  ebx,BYTE PTR [eax+0x3]                            
        lea    ebx,[esi+ebx*1]                                   
        movzx  esi,BYTE PTR [eax+0x5]                            
        lea    ebx,[ebx+ebx*4]                                   
        lea    edx,[edx+ebx*4]                                   
        movzx  ebx,BYTE PTR [eax+0x2]                            
        lea    ebx,[esi+ebx*1]                                   
        movzx  esi,BYTE PTR [eax+0x6]                            
        lea    ebx,[ebx+ebx*2]                                   
        add    ebx,ebx                                           
            sub    dx,bx                                             
            movzx  ebx,BYTE PTR [eax+0x1]                            
        lea    ebx,[esi+ebx*1]                                   
        lea    ebx,[ebx+ebx*2]                                   
        add    edx,ebx                                           
            mov    WORD PTR [esp+0x12],dx                            
            movzx  edx,BYTE PTR [eax+0x8]                            
        movzx  ebx,BYTE PTR [eax+0x1]                            
        movzx  esi,BYTE PTR [eax+0x5]                            
        neg    edx                                               
            sub    dx,bx                                             
            movzx  ebx,BYTE PTR [eax+0x4]                            
        lea    ebx,[esi+ebx*1]                                   
        movzx  esi,BYTE PTR [eax+0x6]                            
        lea    ebx,[ebx+ebx*4]                                   
        lea    edx,[edx+ebx*4]                                   
        movzx  ebx,BYTE PTR [eax+0x3]                            
        lea    ebx,[esi+ebx*1]                                   
        movzx  esi,BYTE PTR [eax+0x7]                            
        lea    ebx,[ebx+ebx*2]                                   
        add    ebx,ebx                                           
            sub    dx,bx                                             
            movzx  ebx,BYTE PTR [eax+0x2]                            
        lea    ebx,[esi+ebx*1]                                   
        lea    ebx,[ebx+ebx*2]                                   
        add    edx,ebx                                           
            mov    WORD PTR [esp+0x14],dx                            
            movzx  ebx,BYTE PTR [eax+0x8]                            
        movzx  esi,BYTE PTR [eax+0x2]                            
        movzx  edi,BYTE PTR [eax+0x6]                            
        movzx  edx,bl                                            
            movzx  ebx,bl                                            
            neg    edx                                               
            sub    dx,si                                             
            movzx  esi,BYTE PTR [eax+0x5]                            
        lea    esi,[edi+esi*1]                                   
        movzx  edi,BYTE PTR [eax+0x7]                            
        lea    esi,[esi+esi*4]                                   
        lea    edx,[edx+esi*4]                                   
        movzx  esi,BYTE PTR [eax+0x4]                            
        lea    esi,[edi+esi*1]                                   
        lea    esi,[esi+esi*2]                                   
        add    esi,esi                                           
            sub    dx,si                                             
            movzx  esi,BYTE PTR [eax+0x3]                            
        add    ebx,esi                                           
            lea    ebx,[ebx+ebx*2]                                   
        add    edx,ebx                                           
            mov    WORD PTR [esp+0x16],dx                            
            movzx  esi,BYTE PTR [eax+0x7]                            
        movzx  edi,BYTE PTR [eax+0x3]                            
        movzx  ebx,BYTE PTR [eax+0x8]                            
        mov    ecx,esi                                           
            and    esi,0xff                                          
            movzx  edx,cl                                            
            neg    edx                                               
            sub    dx,di                                             
            movzx  edi,BYTE PTR [eax+0x6]                            
        add    esi,edi                                           
            lea    esi,[esi+esi*4]                                   
        lea    edx,[edx+esi*4]                                   
        movzx  esi,BYTE PTR [eax+0x5]                            
        lea    esi,[ebx+esi*1]                                   
        lea    esi,[esi+esi*2]                                   
        add    esi,esi                                           
            sub    dx,si                                             
            movzx  esi,BYTE PTR [eax+0x4]                            
        lea    ebx,[esi+ebx*1]                                   
        lea    ebx,[ebx+ebx*2]                                   
        add    edx,ebx                                           
            mov    WORD PTR [esp+0x18],dx                            
            movzx  edi,BYTE PTR [eax+0x6]                            
        movzx  ebx,BYTE PTR [eax+0x7]                            
        movzx  esi,BYTE PTR [eax+0x8]                            
        movzx  ebp,BYTE PTR [eax+0x4]                            
        mov    ecx,edi                                           
            and    edi,0xff                                          
            movzx  edx,cl                                            
            mov    ecx,DWORD PTR [esp]                               
        neg    edx                                               
            add    edi,esi                                           
            sub    dx,bp                                             
            lea    ebp,[esi+ebx*1]                                   
        lea    ebp,[ebp+ebp*4+0x0]                               
        lea    ebp,[edx+ebp*4]                                   
        movzx  edx,BYTE PTR [eax+0x5]                            
        lea    edi,[edi+edi*2]                                   
        add    edi,edi                                           
            sub    bp,di                                             
            lea    ebx,[edx+ebx*1]                                   
        mov    edx,DWORD PTR [esp+0x4]                           
        lea    ebx,[ebx+ebx*2]                                   
        add    ebp,ebx                                           
            mov    WORD PTR [esp+0x1a],bp                            
            movq   mm0,QWORD PTR [edx]                               
        movq   mm1,QWORD PTR [edx+0x8]                           
        
			paddw  mm0,QWORD PTR [ff_pw_16]
            paddw  mm1,QWORD PTR [ff_pw_16]
            psraw  mm0,0x5                                           
            psraw  mm1,0x5                                           
            packuswb mm0,mm1                                         
            movq   QWORD PTR [ecx],mm0                               
            mov    edx,DWORD PTR [esp+0x38]                          
        add    DWORD PTR [esp+0x8],0x1                           
            add    eax,DWORD PTR [esp+0x3c]                          
        add    ecx,edx                                           
            mov    DWORD PTR [esp],ecx                               
            mov    ecx,DWORD PTR [esp+0x40]                          
        cmp    DWORD PTR [esp+0x8],ecx                           
            jne    put_mpeg4_qpel8_h_lowpass_3dnow_6250              
put_mpeg4_qpel8_h_lowpass_3dnow_64cb:                    
        add    esp,0x1c                                          
            pop    ebx                                               
            pop    esi                                               
            pop    edi                                               
            pop    ebp                                               
            ret                                                      

    }
}

NAKED void put_mpeg4_qpel8_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0xa4                                   
            mov    DWORD PTR [esp+0x94],ebx                   
            mov    ecx,DWORD PTR [esp+0xa8]                   
        mov    edx,esp                                    
            mov    DWORD PTR [esp+0x98],esi                   
            mov    ebx,DWORD PTR [esp+0xac]                   
        mov    esi,esp                                    
            mov    DWORD PTR [esp+0x9c],edi                   
            mov    eax,DWORD PTR [esp+0xb0]                   
        mov    edi,0x9                                    
            mov    DWORD PTR [esp+0xa0],ebp                   
            mov    ebp,DWORD PTR [esp+0xb4]                   
        pxor   mm7,mm7                                    
put_mpeg4_qpel8_v_lowpass_3dnow_7fba:             
        movq   mm0,QWORD PTR [ebx]                        
        movq   mm1,QWORD PTR [ebx]                        
        punpcklbw mm0,mm7                                 
            punpckhbw mm1,mm7                                 
            movq   QWORD PTR [esi],mm0                        
            movq   QWORD PTR [esi+0x48],mm1                   
            add    esi,0x8                                    
            add    ebx,ebp                                    
            dec    edi                                        
            jne    put_mpeg4_qpel8_v_lowpass_3dnow_7fba       
            imul   esi,eax,0xfffffffa                         
            mov    edi,0x2                                    
            lea    ebx,[eax+eax*1]                            
        add    esi,0x4                                    
put_mpeg4_qpel8_v_lowpass_3dnow_7fe3:             
        movq   mm0,QWORD PTR [edx]                        
        movq   mm1,QWORD PTR [edx+0x8]                    
        movq   mm2,QWORD PTR [edx+0x10]                   
        movq   mm3,QWORD PTR [edx+0x18]                   
        paddw  mm0,mm1                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm0                                    
            movq   mm0,QWORD PTR [edx+0x20]                   
        movq   mm5,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm0                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x8]                    
        movq   mm6,QWORD PTR [edx]                        
        paddw  mm5,mm3                                    
            paddw  mm6,mm2                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm1,mm2                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm1                                    
            movq   mm1,QWORD PTR [edx+0x28]                   
        movq   mm5,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm1                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx]                        
        movq   mm6,QWORD PTR [edx]                        
        paddw  mm5,mm0                                    
            paddw  mm6,mm3                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm2,mm3                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm2                                    
            movq   mm2,QWORD PTR [edx+0x30]                   
        movq   mm5,QWORD PTR [edx]                        
        paddw  mm5,mm2                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx]                        
        movq   mm6,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm1                                    
            paddw  mm6,mm0                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm3,mm0                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm3                                    
            movq   mm3,QWORD PTR [edx+0x38]                   
        movq   mm5,QWORD PTR [edx]                        
        paddw  mm5,mm3                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x8]                    
        movq   mm6,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm2                                    
            paddw  mm6,mm1                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm0,mm1                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm0                                    
            movq   mm0,QWORD PTR [edx+0x40]                   
        movq   mm5,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm0                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x10]                   
        movq   mm6,QWORD PTR [edx+0x18]                   
        paddw  mm5,mm3                                    
            paddw  mm6,mm2                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm1,mm2                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm1                                    
            movq   mm1,QWORD PTR [edx+0x40]                   
        movq   mm5,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm1                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x18]                   
        movq   mm6,QWORD PTR [edx+0x20]                   
        paddw  mm5,mm0                                    
            paddw  mm6,mm3                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm2,mm3                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm2                                    
            movq   mm2,QWORD PTR [edx+0x38]                   
        movq   mm5,QWORD PTR [edx+0x18]                   
        paddw  mm5,mm2                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x20]                   
        movq   mm6,QWORD PTR [edx+0x28]                   
        paddw  mm5,mm1                                    
            paddw  mm6,mm0                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm3,mm0                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm3                                    
            movq   mm3,QWORD PTR [edx+0x30]                   
        movq   mm5,QWORD PTR [edx+0x20]                   
        paddw  mm5,mm3                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x28]                   
        movq   mm6,QWORD PTR [edx+0x30]                   
        paddw  mm5,mm2                                    
            paddw  mm6,mm1                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    edx,0x48                                   
            add    ecx,esi                                    
            dec    edi                                        
            jne    put_mpeg4_qpel8_v_lowpass_3dnow_7fe3       
            mov    ebx,DWORD PTR [esp+0x94]                   
        mov    esi,DWORD PTR [esp+0x98]                   
        mov    edi,DWORD PTR [esp+0x9c]                   
        mov    ebp,DWORD PTR [esp+0xa0]                   
        add    esp,0xa4                                   
            ret                                               

    }
}

NAKED void put_mpeg4_qpel16_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        push   ebp                                                    
            push   edi                                                    
            push   esi                                                    
            push   ebx                                                    
            sub    esp,0x2c                                               
            mov    esi,DWORD PTR [esp+0x50]                               
        mov    ecx,DWORD PTR [esp+0x40]                               
        mov    eax,DWORD PTR [esp+0x44]                               
        test   esi,esi                                                
            jle    put_mpeg4_qpel16_h_lowpass_3dnow_6120                  
            lea    edx,[esp+0xc]                                          
        mov    DWORD PTR [esp+0x8],0x0                                

            mov    DWORD PTR [esp+0x4],edx                                
            mov    DWORD PTR [esp],ecx                                    
            xchg   ax,ax                                                  
put_mpeg4_qpel16_h_lowpass_3dnow_5c50:                        
        movzx  edi,BYTE PTR [eax+0x2]                                 
        movzx  edx,BYTE PTR [eax+0x4]                                 
        movzx  esi,BYTE PTR [eax]                                     
        movzx  ebx,BYTE PTR [eax+0x1]                                 
        mov    ecx,edi                                                
            and    edi,0xff                                               
            movzx  ebp,cl                                                 
            neg    edx                                                    
            sub    dx,bp                                                  
            add    edi,esi                                                
            lea    ebp,[ebx+esi*1]                                        
        lea    ebp,[ebp+ebp*4+0x0]                                    
        lea    ebp,[edx+ebp*4]                                        
        movzx  edx,BYTE PTR [eax+0x3]                                 
        lea    edi,[edi+edi*2]                                        
        add    edi,edi                                                
            sub    bp,di                                                  
            lea    ebx,[edx+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    ebp,ebx                                                
            mov    WORD PTR [esp+0xc],bp                                  
            movzx  esi,BYTE PTR [eax+0x1]                                 
        movzx  edx,BYTE PTR [eax+0x5]                                 
        movzx  ebx,BYTE PTR [eax]                                     
        mov    ecx,esi                                                
            and    esi,0xff                                               
            movzx  edi,cl                                                 
            neg    edx                                                    
            sub    dx,di                                                  
            movzx  edi,BYTE PTR [eax+0x2]                                 
        lea    esi,[edi+esi*1]                                        
        lea    esi,[esi+esi*4]                                        
        lea    edx,[edx+esi*4]                                        
        movzx  esi,BYTE PTR [eax+0x3]                                 
        add    esi,ebx                                                
            lea    esi,[esi+esi*2]                                        
        add    esi,esi                                                
            sub    dx,si                                                  
            movzx  esi,BYTE PTR [eax+0x4]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0xe],dx                                  
            movzx  ebx,BYTE PTR [eax]                                     
        movzx  edx,BYTE PTR [eax+0x6]                                 
        movzx  edi,BYTE PTR [eax+0x3]                                 
        movzx  esi,bl                                                 
            movzx  ebx,bl                                                 
            neg    edx                                                    
            sub    dx,si                                                  
            movzx  esi,BYTE PTR [eax+0x2]                                 
        lea    esi,[edi+esi*1]                                        
        movzx  edi,BYTE PTR [eax+0x4]                                 
        lea    esi,[esi+esi*4]                                        
        lea    edx,[edx+esi*4]                                        
        movzx  esi,BYTE PTR [eax+0x1]                                 
        lea    esi,[edi+esi*1]                                        
        lea    esi,[esi+esi*2]                                        
        add    esi,esi                                                
            sub    dx,si                                                  
            movzx  esi,BYTE PTR [eax+0x5]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x10],dx                                 
            movzx  edx,BYTE PTR [eax+0x7]                                 
        movzx  ebx,BYTE PTR [eax]                                     
        movzx  esi,BYTE PTR [eax+0x4]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x3]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x5]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0x2]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x6]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x1]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x12],dx                                 
            movzx  edx,BYTE PTR [eax+0x8]                                 
        movzx  ebx,BYTE PTR [eax+0x1]                                 
        movzx  esi,BYTE PTR [eax+0x5]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x4]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x6]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0x3]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x7]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x2]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x14],dx                                 
            movzx  edx,BYTE PTR [eax+0x9]                                 
        movzx  ebx,BYTE PTR [eax+0x2]                                 
        movzx  esi,BYTE PTR [eax+0x6]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x5]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x7]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0x4]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x8]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x3]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x16],dx                                 
            movzx  edx,BYTE PTR [eax+0xa]                                 
        movzx  ebx,BYTE PTR [eax+0x3]                                 
        movzx  esi,BYTE PTR [eax+0x7]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x6]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x8]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0x5]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x9]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x4]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x18],dx                                 
            movzx  edx,BYTE PTR [eax+0xb]                                 
        movzx  ebx,BYTE PTR [eax+0x4]                                 
        movzx  esi,BYTE PTR [eax+0x8]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x7]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0x9]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0x6]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xa]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x5]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x1a],dx                                 
            movzx  edx,BYTE PTR [eax+0xc]                                 
        movzx  ebx,BYTE PTR [eax+0x5]                                 
        movzx  esi,BYTE PTR [eax+0x9]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x8]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xa]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0x7]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xb]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x6]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x1c],dx                                 
            movzx  edx,BYTE PTR [eax+0xd]                                 
        movzx  ebx,BYTE PTR [eax+0x6]                                 
        movzx  esi,BYTE PTR [eax+0xa]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x9]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xb]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0x8]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xc]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x7]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x1e],dx                                 
            movzx  edx,BYTE PTR [eax+0xe]                                 
        movzx  ebx,BYTE PTR [eax+0x7]                                 
        movzx  esi,BYTE PTR [eax+0xb]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0xa]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xc]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0x9]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xd]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x8]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x20],dx                                 
            movzx  edx,BYTE PTR [eax+0xf]                                 
        movzx  ebx,BYTE PTR [eax+0x8]                                 
        movzx  esi,BYTE PTR [eax+0xc]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0xb]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xd]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0xa]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xe]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0x9]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x22],dx                                 
            movzx  edx,BYTE PTR [eax+0x10]                                
        movzx  ebx,BYTE PTR [eax+0x9]                                 
        movzx  esi,BYTE PTR [eax+0xd]                                 
        neg    edx                                                    
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0xc]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xe]                                 
        lea    ebx,[ebx+ebx*4]                                        
        lea    edx,[edx+ebx*4]                                        
        movzx  ebx,BYTE PTR [eax+0xb]                                 
        lea    ebx,[esi+ebx*1]                                        
        movzx  esi,BYTE PTR [eax+0xf]                                 
        lea    ebx,[ebx+ebx*2]                                        
        add    ebx,ebx                                                
            sub    dx,bx                                                  
            movzx  ebx,BYTE PTR [eax+0xa]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x24],dx                                 
            movzx  ebx,BYTE PTR [eax+0x10]                                
        movzx  esi,BYTE PTR [eax+0xa]                                 
        movzx  edi,BYTE PTR [eax+0xe]                                 
        movzx  edx,bl                                                 
            movzx  ebx,bl                                                 
            neg    edx                                                    
            sub    dx,si                                                  
            movzx  esi,BYTE PTR [eax+0xd]                                 
        lea    esi,[edi+esi*1]                                        
        movzx  edi,BYTE PTR [eax+0xf]                                 
        lea    esi,[esi+esi*4]                                        
        lea    edx,[edx+esi*4]                                        
        movzx  esi,BYTE PTR [eax+0xc]                                 
        lea    esi,[edi+esi*1]                                        
        lea    esi,[esi+esi*2]                                        
        add    esi,esi                                                
            sub    dx,si                                                  
            movzx  esi,BYTE PTR [eax+0xb]                                 
        add    ebx,esi                                                
            lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x26],dx                                 
            movzx  esi,BYTE PTR [eax+0xf]                                 
        movzx  edi,BYTE PTR [eax+0xb]                                 
        movzx  ebx,BYTE PTR [eax+0x10]                                
        mov    ecx,esi                                                
            and    esi,0xff                                               
            movzx  edx,cl                                                 
            neg    edx                                                    
            sub    dx,di                                                  
            movzx  edi,BYTE PTR [eax+0xe]                                 
        add    esi,edi                                                
            lea    esi,[esi+esi*4]                                        
        lea    edx,[edx+esi*4]                                        
        movzx  esi,BYTE PTR [eax+0xd]                                 
        lea    esi,[ebx+esi*1]                                        
        lea    esi,[esi+esi*2]                                        
        add    esi,esi                                                
            sub    dx,si                                                  
            movzx  esi,BYTE PTR [eax+0xc]                                 
        lea    ebx,[esi+ebx*1]                                        
        lea    ebx,[ebx+ebx*2]                                        
        add    edx,ebx                                                
            mov    WORD PTR [esp+0x28],dx                                 
            movzx  edi,BYTE PTR [eax+0xe]                                 
        movzx  ebx,BYTE PTR [eax+0xf]                                 
        movzx  esi,BYTE PTR [eax+0x10]                                
        movzx  ebp,BYTE PTR [eax+0xc]                                 
        mov    ecx,edi                                                
            and    edi,0xff                                               
            movzx  edx,cl                                                 
            mov    ecx,DWORD PTR [esp]                                    
        neg    edx                                                    
            add    edi,esi                                                
            sub    dx,bp                                                  
            lea    ebp,[esi+ebx*1]                                        
        lea    ebp,[ebp+ebp*4+0x0]                                    
        lea    ebp,[edx+ebp*4]                                        
        movzx  edx,BYTE PTR [eax+0xd]                                 
        lea    edi,[edi+edi*2]                                        
        add    edi,edi                                                
            sub    bp,di                                                  
            lea    ebx,[edx+ebx*1]                                        
        mov    edx,DWORD PTR [esp+0x4]                                
        lea    ebx,[ebx+ebx*2]                                        
        add    ebp,ebx                                                
            mov    WORD PTR [esp+0x2a],bp                                 
            movq   mm0,QWORD PTR [edx]                                    
        movq   mm1,QWORD PTR [edx+0x8]                                
        
			paddw  mm0,QWORD PTR [ff_pw_16]
            paddw  mm1,QWORD PTR [ff_pw_16]
            psraw  mm0,0x5                                                
            psraw  mm1,0x5                                                
            packuswb mm0,mm1                                              
            movq   QWORD PTR [ecx],mm0                                    
            movq   mm0,QWORD PTR [edx+0x10]                               
        movq   mm1,QWORD PTR [edx+0x18]                               
			
			paddw  mm0,QWORD PTR [ff_pw_16]                                   
            paddw  mm1,QWORD PTR [ff_pw_16]                                  
            psraw  mm0,0x5                                                
            psraw  mm1,0x5                                                
            packuswb mm0,mm1                                              
            movq   QWORD PTR [ecx+0x8],mm0                                
            mov    edx,DWORD PTR [esp+0x48]                               
        add    DWORD PTR [esp+0x8],0x1                                
            add    eax,DWORD PTR [esp+0x4c]                               
        add    ecx,edx                                                
            mov    DWORD PTR [esp],ecx                                    
            mov    ecx,DWORD PTR [esp+0x50]                               
        cmp    DWORD PTR [esp+0x8],ecx                                
            jne    put_mpeg4_qpel16_h_lowpass_3dnow_5c50                  
put_mpeg4_qpel16_h_lowpass_3dnow_6120:                        
        add    esp,0x2c        														            
            pop    ebx                                                    
            pop    esi                                                    
            pop    edi                                                    
            pop    ebp                                                    
            ret                                                           

    }
}

NAKED void put_mpeg4_qpel16_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0x234                               
            mov    DWORD PTR [esp+0x224],ebx               
            mov    ecx,DWORD PTR [esp+0x238]               
        mov    edx,esp                                 
            mov    DWORD PTR [esp+0x228],esi               
            mov    ebx,DWORD PTR [esp+0x23c]               
        mov    esi,esp                                 
            mov    DWORD PTR [esp+0x22c],edi               
            mov    eax,DWORD PTR [esp+0x240]               
        mov    edi,0x11                                
            mov    DWORD PTR [esp+0x230],ebp               
            mov    ebp,DWORD PTR [esp+0x244]               
        pxor   mm7,mm7                                 
put_mpeg4_qpel16_v_lowpass_3dnow_7a2a:         
        movq   mm0,QWORD PTR [ebx]                     
        movq   mm1,QWORD PTR [ebx]                     
        movq   mm2,QWORD PTR [ebx+0x8]                 
        movq   mm3,QWORD PTR [ebx+0x8]                 
        punpcklbw mm0,mm7                              
            punpckhbw mm1,mm7                              
            punpcklbw mm2,mm7                              
            punpckhbw mm3,mm7                              
            movq   QWORD PTR [esi],mm0                     
            movq   QWORD PTR [esi+0x88],mm1                
            movq   QWORD PTR [esi+0x110],mm2               
            movq   QWORD PTR [esi+0x198],mm3               
            add    esi,0x8                                 
            add    ebx,ebp                                 
            dec    edi                                     
            jne    put_mpeg4_qpel16_v_lowpass_3dnow_7a2a   
            imul   esi,eax,0xfffffff2                      
            mov    edi,0x4                                 
            lea    ebx,[eax+eax*1]                         
        add    esi,0x4                                 
put_mpeg4_qpel16_v_lowpass_3dnow_7a72:         
        movq   mm0,QWORD PTR [edx]                     
        movq   mm1,QWORD PTR [edx+0x8]                 
        movq   mm2,QWORD PTR [edx+0x10]                
        movq   mm3,QWORD PTR [edx+0x18]                
        paddw  mm0,mm1                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm0                                 
            movq   mm0,QWORD PTR [edx+0x20]                
        movq   mm5,QWORD PTR [edx+0x10]                
        paddw  mm5,mm0                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x8]                 
        movq   mm6,QWORD PTR [edx]                     
        paddw  mm5,mm3                                 
            paddw  mm6,mm2                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx],mm5                     
            paddw  mm1,mm2                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm1                                 
            movq   mm1,QWORD PTR [edx+0x28]                
        movq   mm5,QWORD PTR [edx+0x8]                 
        paddw  mm5,mm1                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx]                     
        movq   mm6,QWORD PTR [edx]                     
        paddw  mm5,mm0                                 
            paddw  mm6,mm3                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx+eax*1],mm5               
            add    ecx,ebx                                 
            paddw  mm2,mm3                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm2                                 
            movq   mm2,QWORD PTR [edx+0x30]                
        movq   mm5,QWORD PTR [edx]                     
        paddw  mm5,mm2                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx]                     
        movq   mm6,QWORD PTR [edx+0x8]                 
        paddw  mm5,mm1                                 
            paddw  mm6,mm0                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx],mm5                     
            paddw  mm3,mm0                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm3                                 
            movq   mm3,QWORD PTR [edx+0x38]                
        movq   mm5,QWORD PTR [edx]                     
        paddw  mm5,mm3                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x8]                 
        movq   mm6,QWORD PTR [edx+0x10]                
        paddw  mm5,mm2                                 
            paddw  mm6,mm1                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx+eax*1],mm5               
            add    ecx,ebx                                 
            paddw  mm0,mm1                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm0                                 
            movq   mm0,QWORD PTR [edx+0x40]                
        movq   mm5,QWORD PTR [edx+0x8]                 
        paddw  mm5,mm0                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x10]                
        movq   mm6,QWORD PTR [edx+0x18]                
        paddw  mm5,mm3                                 
            paddw  mm6,mm2                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx],mm5                     
            paddw  mm1,mm2                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm1                                 
            movq   mm1,QWORD PTR [edx+0x48]                
        movq   mm5,QWORD PTR [edx+0x10]                
        paddw  mm5,mm1                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x18]                
        movq   mm6,QWORD PTR [edx+0x20]                
        paddw  mm5,mm0                                 
            paddw  mm6,mm3                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx+eax*1],mm5               
            add    ecx,ebx                                 
            paddw  mm2,mm3                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm2                                 
            movq   mm2,QWORD PTR [edx+0x50]                
        movq   mm5,QWORD PTR [edx+0x18]                
        paddw  mm5,mm2                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x20]                
        movq   mm6,QWORD PTR [edx+0x28]                
        paddw  mm5,mm1                                 
            paddw  mm6,mm0                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx],mm5                     
            paddw  mm3,mm0                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm3                                 
            movq   mm3,QWORD PTR [edx+0x58]                
        movq   mm5,QWORD PTR [edx+0x20]                
        paddw  mm5,mm3                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x28]                
        movq   mm6,QWORD PTR [edx+0x30]                
        paddw  mm5,mm2                                 
            paddw  mm6,mm1                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx+eax*1],mm5               
            add    ecx,ebx                                 
            paddw  mm0,mm1                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm0                                 
            movq   mm0,QWORD PTR [edx+0x60]                
        movq   mm5,QWORD PTR [edx+0x28]                
        paddw  mm5,mm0                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x30]                
        movq   mm6,QWORD PTR [edx+0x38]                
        paddw  mm5,mm3                                 
            paddw  mm6,mm2                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx],mm5                     
            paddw  mm1,mm2                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm1                                 
            movq   mm1,QWORD PTR [edx+0x68]                
        movq   mm5,QWORD PTR [edx+0x30]                
        paddw  mm5,mm1                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x38]                
        movq   mm6,QWORD PTR [edx+0x40]                
        paddw  mm5,mm0                                 
            paddw  mm6,mm3                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx+eax*1],mm5               
            add    ecx,ebx                                 
            paddw  mm2,mm3                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm2                                 
            movq   mm2,QWORD PTR [edx+0x70]                
        movq   mm5,QWORD PTR [edx+0x38]                
        paddw  mm5,mm2                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x40]                
        movq   mm6,QWORD PTR [edx+0x48]                
        paddw  mm5,mm1                                 
            paddw  mm6,mm0                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx],mm5                     
            paddw  mm3,mm0                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm3                                 
            movq   mm3,QWORD PTR [edx+0x78]                
        movq   mm5,QWORD PTR [edx+0x40]                
        paddw  mm5,mm3                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x48]                
        movq   mm6,QWORD PTR [edx+0x50]                
        paddw  mm5,mm2                                 
            paddw  mm6,mm1                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx+eax*1],mm5               
            add    ecx,ebx                                 
            paddw  mm0,mm1                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm0                                 
            movq   mm0,QWORD PTR [edx+0x80]                
        movq   mm5,QWORD PTR [edx+0x48]                
        paddw  mm5,mm0                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x50]                
        movq   mm6,QWORD PTR [edx+0x58]                
        paddw  mm5,mm3                                 
            paddw  mm6,mm2                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx],mm5                     
            paddw  mm1,mm2                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm1                                 
            movq   mm1,QWORD PTR [edx+0x80]                
        movq   mm5,QWORD PTR [edx+0x50]                
        paddw  mm5,mm1                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x58]                
        movq   mm6,QWORD PTR [edx+0x60]                
        paddw  mm5,mm0                                 
            paddw  mm6,mm3                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx+eax*1],mm5               
            add    ecx,ebx                                 
            paddw  mm2,mm3                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm2                                 
            movq   mm2,QWORD PTR [edx+0x78]                
        movq   mm5,QWORD PTR [edx+0x58]                
        paddw  mm5,mm2                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x60]                
        movq   mm6,QWORD PTR [edx+0x68]                
        paddw  mm5,mm1                                 
            paddw  mm6,mm0                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx],mm5                     
            paddw  mm3,mm0                                 
            movq   mm4,QWORD PTR [ff_pw_20]                    
            pmullw mm4,mm3                                 
            movq   mm3,QWORD PTR [edx+0x70]                
        movq   mm5,QWORD PTR [edx+0x60]                
        paddw  mm5,mm3                                 
            psubw  mm4,mm5                                 
            movq   mm5,QWORD PTR [edx+0x68]                
        movq   mm6,QWORD PTR [edx+0x70]                
        paddw  mm5,mm2                                 
            paddw  mm6,mm1                                 
            paddw  mm6,mm6                                 
            psubw  mm5,mm6                                 
            pmullw mm5,QWORD PTR [ff_pw_3]                    
            paddw  mm4,QWORD PTR [ff_pw_16]                    
            paddw  mm5,mm4                                 
            psraw  mm5,0x5                                 
            packuswb mm5,mm5                               
            movd   DWORD PTR [ecx+eax*1],mm5               
            add    edx,0x88                                
            add    ecx,esi                                 
            dec    edi                                     
            jne    put_mpeg4_qpel16_v_lowpass_3dnow_7a72   
            mov    ebx,DWORD PTR [esp+0x224]               
        mov    esi,DWORD PTR [esp+0x228]               
        mov    edi,DWORD PTR [esp+0x22c]               
        mov    ebp,DWORD PTR [esp+0x230]               
        add    esp,0x234                               
            ret                                            

    }
}

NAKED void avg_mpeg4_qpel8_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        push   ebp                                           
            push   edi                                           
            push   esi                                           
            push   ebx                                           
            sub    esp,0x1c                                      
            mov    edx,DWORD PTR [esp+0x40]                      
        mov    ecx,DWORD PTR [esp+0x30]                      
        mov    eax,DWORD PTR [esp+0x34]                      
        test   edx,edx                                       
            jle    avg_mpeg4_qpel8_h_lowpass_3dnow_6f62          
            lea    edx,[esp+0xc]                                 
        mov    DWORD PTR [esp+0x8],0x0                       

            mov    DWORD PTR [esp+0x4],edx                       
            mov    DWORD PTR [esp],ecx                           
            xchg   ax,ax                                         
avg_mpeg4_qpel8_h_lowpass_3dnow_6ce0:                
        movzx  edi,BYTE PTR [eax+0x2]                        
        movzx  edx,BYTE PTR [eax+0x4]                        
        movzx  esi,BYTE PTR [eax]                            
        movzx  ebx,BYTE PTR [eax+0x1]                        
        mov    ecx,edi                                       
            and    edi,0xff                                      
            movzx  ebp,cl                                        
            neg    edx                                           
            sub    dx,bp                                         
            add    edi,esi                                       
            lea    ebp,[ebx+esi*1]                               
        lea    ebp,[ebp+ebp*4+0x0]                           
        lea    ebp,[edx+ebp*4]                               
        movzx  edx,BYTE PTR [eax+0x3]                        
        lea    edi,[edi+edi*2]                               
        add    edi,edi                                       
            sub    bp,di                                         
            lea    ebx,[edx+ebx*1]                               
        lea    ebx,[ebx+ebx*2]                               
        add    ebp,ebx                                       
            mov    WORD PTR [esp+0xc],bp                         
            movzx  esi,BYTE PTR [eax+0x1]                        
        movzx  edx,BYTE PTR [eax+0x5]                        
        movzx  ebx,BYTE PTR [eax]                            
        mov    ecx,esi                                       
            and    esi,0xff                                      
            movzx  edi,cl                                        
            neg    edx                                           
            sub    dx,di                                         
            movzx  edi,BYTE PTR [eax+0x2]                        
        lea    esi,[edi+esi*1]                               
        lea    esi,[esi+esi*4]                               
        lea    edx,[edx+esi*4]                               
        movzx  esi,BYTE PTR [eax+0x3]                        
        add    esi,ebx                                       
            lea    esi,[esi+esi*2]                               
        add    esi,esi                                       
            sub    dx,si                                         
            movzx  esi,BYTE PTR [eax+0x4]                        
        lea    ebx,[esi+ebx*1]                               
        lea    ebx,[ebx+ebx*2]                               
        add    edx,ebx                                       
            mov    WORD PTR [esp+0xe],dx                         
            movzx  ebx,BYTE PTR [eax]                            
        movzx  edx,BYTE PTR [eax+0x6]                        
        movzx  edi,BYTE PTR [eax+0x3]                        
        movzx  esi,bl                                        
            movzx  ebx,bl                                        
            neg    edx                                           
            sub    dx,si                                         
            movzx  esi,BYTE PTR [eax+0x2]                        
        lea    esi,[edi+esi*1]                               
        movzx  edi,BYTE PTR [eax+0x4]                        
        lea    esi,[esi+esi*4]                               
        lea    edx,[edx+esi*4]                               
        movzx  esi,BYTE PTR [eax+0x1]                        
        lea    esi,[edi+esi*1]                               
        lea    esi,[esi+esi*2]                               
        add    esi,esi                                       
            sub    dx,si                                         
            movzx  esi,BYTE PTR [eax+0x5]                        
        lea    ebx,[esi+ebx*1]                               
        lea    ebx,[ebx+ebx*2]                               
        add    edx,ebx                                       
            mov    WORD PTR [esp+0x10],dx                        
            movzx  edx,BYTE PTR [eax+0x7]                        
        movzx  ebx,BYTE PTR [eax]                            
        movzx  esi,BYTE PTR [eax+0x4]                        
        neg    edx                                           
            sub    dx,bx                                         
            movzx  ebx,BYTE PTR [eax+0x3]                        
        lea    ebx,[esi+ebx*1]                               
        movzx  esi,BYTE PTR [eax+0x5]                        
        lea    ebx,[ebx+ebx*4]                               
        lea    edx,[edx+ebx*4]                               
        movzx  ebx,BYTE PTR [eax+0x2]                        
        lea    ebx,[esi+ebx*1]                               
        movzx  esi,BYTE PTR [eax+0x6]                        
        lea    ebx,[ebx+ebx*2]                               
        add    ebx,ebx                                       
            sub    dx,bx                                         
            movzx  ebx,BYTE PTR [eax+0x1]                        
        lea    ebx,[esi+ebx*1]                               
        lea    ebx,[ebx+ebx*2]                               
        add    edx,ebx                                       
            mov    WORD PTR [esp+0x12],dx                        
            movzx  edx,BYTE PTR [eax+0x8]                        
        movzx  ebx,BYTE PTR [eax+0x1]                        
        movzx  esi,BYTE PTR [eax+0x5]                        
        neg    edx                                           
            sub    dx,bx                                         
            movzx  ebx,BYTE PTR [eax+0x4]                        
        lea    ebx,[esi+ebx*1]                               
        movzx  esi,BYTE PTR [eax+0x6]                        
        lea    ebx,[ebx+ebx*4]                               
        lea    edx,[edx+ebx*4]                               
        movzx  ebx,BYTE PTR [eax+0x3]                        
        lea    ebx,[esi+ebx*1]                               
        movzx  esi,BYTE PTR [eax+0x7]                        
        lea    ebx,[ebx+ebx*2]                               
        add    ebx,ebx                                       
            sub    dx,bx                                         
            movzx  ebx,BYTE PTR [eax+0x2]                        
        lea    ebx,[esi+ebx*1]                               
        lea    ebx,[ebx+ebx*2]                               
        add    edx,ebx                                       
            mov    WORD PTR [esp+0x14],dx                        
            movzx  ebx,BYTE PTR [eax+0x8]                        
        movzx  esi,BYTE PTR [eax+0x2]                        
        movzx  edi,BYTE PTR [eax+0x6]                        
        movzx  edx,bl                                        
            movzx  ebx,bl                                        
            neg    edx                                           
            sub    dx,si                                         
            movzx  esi,BYTE PTR [eax+0x5]                        
        lea    esi,[edi+esi*1]                               
        movzx  edi,BYTE PTR [eax+0x7]                        
        lea    esi,[esi+esi*4]                               
        lea    edx,[edx+esi*4]                               
        movzx  esi,BYTE PTR [eax+0x4]                        
        lea    esi,[edi+esi*1]                               
        lea    esi,[esi+esi*2]                               
        add    esi,esi                                       
            sub    dx,si                                         
            movzx  esi,BYTE PTR [eax+0x3]                        
        add    ebx,esi                                       
            lea    ebx,[ebx+ebx*2]                               
        add    edx,ebx                                       
            mov    WORD PTR [esp+0x16],dx                        
            movzx  esi,BYTE PTR [eax+0x7]                        
        movzx  edi,BYTE PTR [eax+0x3]                        
        movzx  ebx,BYTE PTR [eax+0x8]                        
        mov    ecx,esi                                       
            and    esi,0xff                                      
            movzx  edx,cl                                        
            neg    edx                                           
            sub    dx,di                                         
            movzx  edi,BYTE PTR [eax+0x6]                        
        add    esi,edi                                       
            lea    esi,[esi+esi*4]                               
        lea    edx,[edx+esi*4]                               
        movzx  esi,BYTE PTR [eax+0x5]                        
        lea    esi,[ebx+esi*1]                               
        lea    esi,[esi+esi*2]                               
        add    esi,esi                                       
            sub    dx,si                                         
            movzx  esi,BYTE PTR [eax+0x4]                        
        lea    ebx,[esi+ebx*1]                               
        lea    ebx,[ebx+ebx*2]                               
        add    edx,ebx                                       
            mov    WORD PTR [esp+0x18],dx                        
            movzx  edi,BYTE PTR [eax+0x6]                        
        movzx  ebx,BYTE PTR [eax+0x7]                        
        movzx  esi,BYTE PTR [eax+0x8]                        
        movzx  ebp,BYTE PTR [eax+0x4]                        
        mov    ecx,edi                                       
            and    edi,0xff                                      
            movzx  edx,cl                                        
            mov    ecx,DWORD PTR [esp]                           
        neg    edx                                           
            add    edi,esi                                       
            sub    dx,bp                                         
            lea    ebp,[esi+ebx*1]                               
        lea    ebp,[ebp+ebp*4+0x0]                           
        lea    ebp,[edx+ebp*4]                               
        movzx  edx,BYTE PTR [eax+0x5]                        
        lea    edi,[edi+edi*2]                               
        add    edi,edi                                       
            sub    bp,di                                         
            lea    ebx,[edx+ebx*1]                               
        mov    edx,DWORD PTR [esp+0x4]                       
        lea    ebx,[ebx+ebx*2]                               
        add    ebp,ebx                                       
            mov    WORD PTR [esp+0x1a],bp                        
            movq   mm0,QWORD PTR [edx]                           
        movq   mm1,QWORD PTR [edx+0x8]                       
        paddw  mm0,QWORD PTR [ff_pw_16]                         
            paddw  mm1,QWORD PTR [ff_pw_16]                          
            psraw  mm0,0x5                                       
            psraw  mm1,0x5                                       
            packuswb mm0,mm1                                     
            movq   mm1,QWORD PTR [ecx]                           
        pavgusb mm0,mm1                                      
            movq   QWORD PTR [ecx],mm0                           
            mov    edx,DWORD PTR [esp+0x38]                      
        add    DWORD PTR [esp+0x8],0x1                       
            add    eax,DWORD PTR [esp+0x3c]                      
        add    ecx,edx                                       
            mov    DWORD PTR [esp],ecx                           
            mov    ecx,DWORD PTR [esp+0x40]                      
        cmp    DWORD PTR [esp+0x8],ecx                       
            jne    avg_mpeg4_qpel8_h_lowpass_3dnow_6ce0          
avg_mpeg4_qpel8_h_lowpass_3dnow_6f62:                
        add    esp,0x1c                                      
            pop    ebx                                           
            pop    esi                                           
            pop    edi                                           
            pop    ebp                                           
            ret                                                  

    }
}

NAKED void avg_mpeg4_qpel8_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0xa4                                  
            mov    DWORD PTR [esp+0x94],ebx                  
            mov    ecx,DWORD PTR [esp+0xa8]                  
        mov    edx,esp                                   
            mov    DWORD PTR [esp+0x98],esi                  
            mov    ebx,DWORD PTR [esp+0xac]                  
        mov    esi,esp                                   
            mov    DWORD PTR [esp+0x9c],edi                  
            mov    eax,DWORD PTR [esp+0xb0]                  
        mov    edi,0x9                                   
            mov    DWORD PTR [esp+0xa0],ebp                  
            mov    ebp,DWORD PTR [esp+0xb4]                  
        pxor   mm7,mm7                                   
avg_mpeg4_qpel8_v_lowpass_3dnow_ff3a:            
        movq   mm0,QWORD PTR [ebx]                       
        movq   mm1,QWORD PTR [ebx]                       
        punpcklbw mm0,mm7                                
            punpckhbw mm1,mm7                                
            movq   QWORD PTR [esi],mm0                       
            movq   QWORD PTR [esi+0x48],mm1                  
            add    esi,0x8                                   
            add    ebx,ebp                                   
            dec    edi                                       
            jne    avg_mpeg4_qpel8_v_lowpass_3dnow_ff3a      
            imul   esi,eax,0xfffffffa                        
            mov    edi,0x2                                   
            lea    ebx,[eax+eax*1]                           
        add    esi,0x4                                   
avg_mpeg4_qpel8_v_lowpass_3dnow_ff63:            
        movq   mm0,QWORD PTR [edx]                       
        movq   mm1,QWORD PTR [edx+0x8]                   
        movq   mm2,QWORD PTR [edx+0x10]                  
        movq   mm3,QWORD PTR [edx+0x18]                  
        paddw  mm0,mm1                                   
            movq   mm4,QWORD PTR [ff_pw_20]                      
            pmullw mm4,mm0                                   
            movq   mm0,QWORD PTR [edx+0x20]                  
        movq   mm5,QWORD PTR [edx+0x10]                  
        paddw  mm5,mm0                                   
            psubw  mm4,mm5                                   
            movq   mm5,QWORD PTR [edx+0x8]                   
        movq   mm6,QWORD PTR [edx]                       
        paddw  mm5,mm3                                   
            paddw  mm6,mm2                                   
            paddw  mm6,mm6                                   
            psubw  mm5,mm6                                   
            pmullw mm5,QWORD PTR [ff_pw_3]                      
            paddw  mm4,QWORD PTR [ff_pw_16]                      
            paddw  mm5,mm4                                   
            psraw  mm5,0x5                                   
            packuswb mm5,mm5                                 
            movd   mm7,DWORD PTR [ecx]                       
        pavgusb mm5,mm7                                  
            movd   DWORD PTR [ecx],mm5                       
            paddw  mm1,mm2                                   
            movq   mm4,QWORD PTR [ff_pw_20]                      
            pmullw mm4,mm1                                   
            movq   mm1,QWORD PTR [edx+0x28]                  
        movq   mm5,QWORD PTR [edx+0x8]                   
        paddw  mm5,mm1                                   
            psubw  mm4,mm5                                   
            movq   mm5,QWORD PTR [edx]                       
        movq   mm6,QWORD PTR [edx]                       
        paddw  mm5,mm0                                   
            paddw  mm6,mm3                                   
            paddw  mm6,mm6                                   
            psubw  mm5,mm6                                   
            pmullw mm5,QWORD PTR [ff_pw_3]                      
            paddw  mm4,QWORD PTR [ff_pw_16]                      
            paddw  mm5,mm4                                   
            psraw  mm5,0x5                                   
            packuswb mm5,mm5                                 
            movd   mm7,DWORD PTR [ecx+eax*1]                 
        pavgusb mm5,mm7                                  
            movd   DWORD PTR [ecx+eax*1],mm5                 
            add    ecx,ebx                                   
            paddw  mm2,mm3                                   
            movq   mm4,QWORD PTR [ff_pw_20]                      
            pmullw mm4,mm2                                   
            movq   mm2,QWORD PTR [edx+0x30]                  
        movq   mm5,QWORD PTR [edx]                       
        paddw  mm5,mm2                                   
            psubw  mm4,mm5                                   
            movq   mm5,QWORD PTR [edx]                       
        movq   mm6,QWORD PTR [edx+0x8]                   
        paddw  mm5,mm1                                   
            paddw  mm6,mm0                                   
            paddw  mm6,mm6                                   
            psubw  mm5,mm6                                   
            pmullw mm5,QWORD PTR [ff_pw_3]                      
            paddw  mm4,QWORD PTR [ff_pw_16]                      
            paddw  mm5,mm4                                   
            psraw  mm5,0x5                                   
            packuswb mm5,mm5                                 
            movd   mm7,DWORD PTR [ecx]                       
        pavgusb mm5,mm7                                  
            movd   DWORD PTR [ecx],mm5                       
            paddw  mm3,mm0                                   
            movq   mm4,QWORD PTR [ff_pw_20]                      
            pmullw mm4,mm3                                   
            movq   mm3,QWORD PTR [edx+0x38]                  
        movq   mm5,QWORD PTR [edx]                       
        paddw  mm5,mm3                                   
            psubw  mm4,mm5                                   
            movq   mm5,QWORD PTR [edx+0x8]                   
        movq   mm6,QWORD PTR [edx+0x10]                  
        paddw  mm5,mm2                                   
            paddw  mm6,mm1                                   
            paddw  mm6,mm6                                   
            psubw  mm5,mm6                                   
            pmullw mm5,QWORD PTR [ff_pw_3]                      
            paddw  mm4,QWORD PTR [ff_pw_16]                      
            paddw  mm5,mm4                                   
            psraw  mm5,0x5                                   
            packuswb mm5,mm5                                 
            movd   mm7,DWORD PTR [ecx+eax*1]                 
        pavgusb mm5,mm7                                  
            movd   DWORD PTR [ecx+eax*1],mm5                 
            add    ecx,ebx                                   
            paddw  mm0,mm1                                   
            movq   mm4,QWORD PTR [ff_pw_20]                      
            pmullw mm4,mm0                                   
            movq   mm0,QWORD PTR [edx+0x40]                  
        movq   mm5,QWORD PTR [edx+0x8]                   
        paddw  mm5,mm0                                   
            psubw  mm4,mm5                                   
            movq   mm5,QWORD PTR [edx+0x10]                  
        movq   mm6,QWORD PTR [edx+0x18]                  
        paddw  mm5,mm3                                   
            paddw  mm6,mm2                                   
            paddw  mm6,mm6                                   
            psubw  mm5,mm6                                   
            pmullw mm5,QWORD PTR [ff_pw_3]                      
            paddw  mm4,QWORD PTR [ff_pw_16]                      
            paddw  mm5,mm4                                   
            psraw  mm5,0x5                                   
            packuswb mm5,mm5                                 
            movd   mm7,DWORD PTR [ecx]                       
        pavgusb mm5,mm7                                  
            movd   DWORD PTR [ecx],mm5                       
            paddw  mm1,mm2                                   
            movq   mm4,QWORD PTR [ff_pw_20]                      
            pmullw mm4,mm1                                   
            movq   mm1,QWORD PTR [edx+0x40]                  
        movq   mm5,QWORD PTR [edx+0x10]                  
        paddw  mm5,mm1                                   
            psubw  mm4,mm5                                   
            movq   mm5,QWORD PTR [edx+0x18]                  
        movq   mm6,QWORD PTR [edx+0x20]                  
        paddw  mm5,mm0                                   
            paddw  mm6,mm3                                   
            paddw  mm6,mm6                                   
            psubw  mm5,mm6                                   
            pmullw mm5,QWORD PTR [ff_pw_3]                      
            paddw  mm4,QWORD PTR [ff_pw_16]                      
            paddw  mm5,mm4                                   
            psraw  mm5,0x5                                   
            packuswb mm5,mm5                                 
            movd   mm7,DWORD PTR [ecx+eax*1]                 
        pavgusb mm5,mm7                                  
            movd   DWORD PTR [ecx+eax*1],mm5                 
            add    ecx,ebx                                   
            paddw  mm2,mm3                                   
            movq   mm4,QWORD PTR [ff_pw_20]                      
            pmullw mm4,mm2                                   
            movq   mm2,QWORD PTR [edx+0x38]                  
        movq   mm5,QWORD PTR [edx+0x18]                  
        paddw  mm5,mm2                                   
            psubw  mm4,mm5                                   
            movq   mm5,QWORD PTR [edx+0x20]                  
        movq   mm6,QWORD PTR [edx+0x28]                  
        paddw  mm5,mm1                                   
            paddw  mm6,mm0                                   
            paddw  mm6,mm6                                   
            psubw  mm5,mm6                                   
            pmullw mm5,QWORD PTR [ff_pw_3]                      
            paddw  mm4,QWORD PTR [ff_pw_16]                      
            paddw  mm5,mm4                                   
            psraw  mm5,0x5                                   
            packuswb mm5,mm5                                 
            movd   mm7,DWORD PTR [ecx]                       
        pavgusb mm5,mm7                                  
            movd   DWORD PTR [ecx],mm5                       
            paddw  mm3,mm0                                   
            movq   mm4,QWORD PTR [ff_pw_20]                      
            pmullw mm4,mm3                                   
            movq   mm3,QWORD PTR [edx+0x30]                  
        movq   mm5,QWORD PTR [edx+0x20]                  
        paddw  mm5,mm3                                   
            psubw  mm4,mm5                                   
            movq   mm5,QWORD PTR [edx+0x28]                  
        movq   mm6,QWORD PTR [edx+0x30]                  
        paddw  mm5,mm2                                   
            paddw  mm6,mm1                                   
            paddw  mm6,mm6                                   
            psubw  mm5,mm6                                   
            pmullw mm5,QWORD PTR [ff_pw_3]                      
            paddw  mm4,QWORD PTR [ff_pw_16]                      
            paddw  mm5,mm4                                   
            psraw  mm5,0x5                                   
            packuswb mm5,mm5                                 
            movd   mm7,DWORD PTR [ecx+eax*1]                 
        pavgusb mm5,mm7                                  
            movd   DWORD PTR [ecx+eax*1],mm5                 
            add    edx,0x48                                  
            add    ecx,esi                                   
            dec    edi                                       
            jne    avg_mpeg4_qpel8_v_lowpass_3dnow_ff63      
            mov    ebx,DWORD PTR [esp+0x94]                  
        mov    esi,DWORD PTR [esp+0x98]                  
        mov    edi,DWORD PTR [esp+0x9c]                  
        mov    ebp,DWORD PTR [esp+0xa0]                  
        add    esp,0xa4                                  
            ret                                              

    }
}

NAKED void avg_mpeg4_qpel16_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        push   ebp                                        
            push   edi                                        
            push   esi                                        
            push   ebx                                        
            sub    esp,0x2c                                   
            mov    ebp,DWORD PTR [esp+0x50]                   
        mov    ecx,DWORD PTR [esp+0x40]                   
        mov    eax,DWORD PTR [esp+0x44]                   
        test   ebp,ebp                                    
            jle    avg_mpeg4_qpel16_h_lowpass_3dnow__6baf     
            lea    edx,[esp+0xc]                              
        mov    DWORD PTR [esp+0x8],0x0                    

            mov    DWORD PTR [esp+0x4],edx                    
            mov    DWORD PTR [esp],ecx                        
            xchg   ax,ax                                      
avg_mpeg4_qpel16_h_lowpass_3dnow__66d0:           
        movzx  edi,BYTE PTR [eax+0x2]                     
        movzx  edx,BYTE PTR [eax+0x4]                     
        movzx  esi,BYTE PTR [eax]                         
        movzx  ebx,BYTE PTR [eax+0x1]                     
        mov    ecx,edi                                    
            and    edi,0xff                                   
            movzx  ebp,cl                                     
            neg    edx                                        
            sub    dx,bp                                      
            add    edi,esi                                    
            lea    ebp,[ebx+esi*1]                            
        lea    ebp,[ebp+ebp*4+0x0]                        
        lea    ebp,[edx+ebp*4]                            
        movzx  edx,BYTE PTR [eax+0x3]                     
        lea    edi,[edi+edi*2]                            
        add    edi,edi                                    
            sub    bp,di                                      
            lea    ebx,[edx+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    ebp,ebx                                    
            mov    WORD PTR [esp+0xc],bp                      
            movzx  esi,BYTE PTR [eax+0x1]                     
        movzx  edx,BYTE PTR [eax+0x5]                     
        movzx  ebx,BYTE PTR [eax]                         
        mov    ecx,esi                                    
            and    esi,0xff                                   
            movzx  edi,cl                                     
            neg    edx                                        
            sub    dx,di                                      
            movzx  edi,BYTE PTR [eax+0x2]                     
        lea    esi,[edi+esi*1]                            
        lea    esi,[esi+esi*4]                            
        lea    edx,[edx+esi*4]                            
        movzx  esi,BYTE PTR [eax+0x3]                     
        add    esi,ebx                                    
            lea    esi,[esi+esi*2]                            
        add    esi,esi                                    
            sub    dx,si                                      
            movzx  esi,BYTE PTR [eax+0x4]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0xe],dx                      
            movzx  ebx,BYTE PTR [eax]                         
        movzx  edx,BYTE PTR [eax+0x6]                     
        movzx  edi,BYTE PTR [eax+0x3]                     
        movzx  esi,bl                                     
            movzx  ebx,bl                                     
            neg    edx                                        
            sub    dx,si                                      
            movzx  esi,BYTE PTR [eax+0x2]                     
        lea    esi,[edi+esi*1]                            
        movzx  edi,BYTE PTR [eax+0x4]                     
        lea    esi,[esi+esi*4]                            
        lea    edx,[edx+esi*4]                            
        movzx  esi,BYTE PTR [eax+0x1]                     
        lea    esi,[edi+esi*1]                            
        lea    esi,[esi+esi*2]                            
        add    esi,esi                                    
            sub    dx,si                                      
            movzx  esi,BYTE PTR [eax+0x5]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x10],dx                     
            movzx  edx,BYTE PTR [eax+0x7]                     
        movzx  ebx,BYTE PTR [eax]                         
        movzx  esi,BYTE PTR [eax+0x4]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x3]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x5]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0x2]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x6]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x1]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x12],dx                     
            movzx  edx,BYTE PTR [eax+0x8]                     
        movzx  ebx,BYTE PTR [eax+0x1]                     
        movzx  esi,BYTE PTR [eax+0x5]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x4]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x6]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0x3]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x7]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x2]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x14],dx                     
            movzx  edx,BYTE PTR [eax+0x9]                     
        movzx  ebx,BYTE PTR [eax+0x2]                     
        movzx  esi,BYTE PTR [eax+0x6]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x5]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x7]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0x4]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x8]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x3]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x16],dx                     
            movzx  edx,BYTE PTR [eax+0xa]                     
        movzx  ebx,BYTE PTR [eax+0x3]                     
        movzx  esi,BYTE PTR [eax+0x7]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x6]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x8]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0x5]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x9]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x4]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x18],dx                     
            movzx  edx,BYTE PTR [eax+0xb]                     
        movzx  ebx,BYTE PTR [eax+0x4]                     
        movzx  esi,BYTE PTR [eax+0x8]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x7]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0x9]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0x6]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xa]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x5]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x1a],dx                     
            movzx  edx,BYTE PTR [eax+0xc]                     
        movzx  ebx,BYTE PTR [eax+0x5]                     
        movzx  esi,BYTE PTR [eax+0x9]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x8]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xa]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0x7]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xb]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x6]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x1c],dx                     
            movzx  edx,BYTE PTR [eax+0xd]                     
        movzx  ebx,BYTE PTR [eax+0x6]                     
        movzx  esi,BYTE PTR [eax+0xa]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x9]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xb]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0x8]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xc]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x7]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x1e],dx                     
            movzx  edx,BYTE PTR [eax+0xe]                     
        movzx  ebx,BYTE PTR [eax+0x7]                     
        movzx  esi,BYTE PTR [eax+0xb]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0xa]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xc]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0x9]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xd]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x8]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x20],dx                     
            movzx  edx,BYTE PTR [eax+0xf]                     
        movzx  ebx,BYTE PTR [eax+0x8]                     
        movzx  esi,BYTE PTR [eax+0xc]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0xb]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xd]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0xa]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xe]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0x9]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x22],dx                     
            movzx  edx,BYTE PTR [eax+0x10]                    
        movzx  ebx,BYTE PTR [eax+0x9]                     
        movzx  esi,BYTE PTR [eax+0xd]                     
        neg    edx                                        
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0xc]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xe]                     
        lea    ebx,[ebx+ebx*4]                            
        lea    edx,[edx+ebx*4]                            
        movzx  ebx,BYTE PTR [eax+0xb]                     
        lea    ebx,[esi+ebx*1]                            
        movzx  esi,BYTE PTR [eax+0xf]                     
        lea    ebx,[ebx+ebx*2]                            
        add    ebx,ebx                                    
            sub    dx,bx                                      
            movzx  ebx,BYTE PTR [eax+0xa]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x24],dx                     
            movzx  ebx,BYTE PTR [eax+0x10]                    
        movzx  esi,BYTE PTR [eax+0xa]                     
        movzx  edi,BYTE PTR [eax+0xe]                     
        movzx  edx,bl                                     
            movzx  ebx,bl                                     
            neg    edx                                        
            sub    dx,si                                      
            movzx  esi,BYTE PTR [eax+0xd]                     
        lea    esi,[edi+esi*1]                            
        movzx  edi,BYTE PTR [eax+0xf]                     
        lea    esi,[esi+esi*4]                            
        lea    edx,[edx+esi*4]                            
        movzx  esi,BYTE PTR [eax+0xc]                     
        lea    esi,[edi+esi*1]                            
        lea    esi,[esi+esi*2]                            
        add    esi,esi                                    
            sub    dx,si                                      
            movzx  esi,BYTE PTR [eax+0xb]                     
        add    ebx,esi                                    
            lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x26],dx                     
            movzx  esi,BYTE PTR [eax+0xf]                     
        movzx  edi,BYTE PTR [eax+0xb]                     
        movzx  ebx,BYTE PTR [eax+0x10]                    
        mov    ecx,esi                                    
            and    esi,0xff                                   
            movzx  edx,cl                                     
            neg    edx                                        
            sub    dx,di                                      
            movzx  edi,BYTE PTR [eax+0xe]                     
        add    esi,edi                                    
            lea    esi,[esi+esi*4]                            
        lea    edx,[edx+esi*4]                            
        movzx  esi,BYTE PTR [eax+0xd]                     
        lea    esi,[ebx+esi*1]                            
        lea    esi,[esi+esi*2]                            
        add    esi,esi                                    
            sub    dx,si                                      
            movzx  esi,BYTE PTR [eax+0xc]                     
        lea    ebx,[esi+ebx*1]                            
        lea    ebx,[ebx+ebx*2]                            
        add    edx,ebx                                    
            mov    WORD PTR [esp+0x28],dx                     
            movzx  edi,BYTE PTR [eax+0xe]                     
        movzx  ebx,BYTE PTR [eax+0xf]                     
        movzx  esi,BYTE PTR [eax+0x10]                    
        movzx  ebp,BYTE PTR [eax+0xc]                     
        mov    ecx,edi                                    
            and    edi,0xff                                   
            movzx  edx,cl                                     
            mov    ecx,DWORD PTR [esp]                        
        neg    edx                                        
            add    edi,esi                                    
            sub    dx,bp                                      
            lea    ebp,[esi+ebx*1]                            
        lea    ebp,[ebp+ebp*4+0x0]                        
        lea    ebp,[edx+ebp*4]                            
        movzx  edx,BYTE PTR [eax+0xd]                     
        lea    edi,[edi+edi*2]                            
        add    edi,edi                                    
            sub    bp,di                                      
            lea    ebx,[edx+ebx*1]                            
        mov    edx,DWORD PTR [esp+0x4]                    
        lea    ebx,[ebx+ebx*2]                            
        add    ebp,ebx                                    
            mov    WORD PTR [esp+0x2a],bp                     
            movq   mm0,QWORD PTR [edx]                        
        movq   mm1,QWORD PTR [edx+0x8]                    
        paddw  mm0,QWORD PTR [ff_pw_16]                        
            paddw  mm1,QWORD PTR [ff_pw_16]                        
            psraw  mm0,0x5                                    
            psraw  mm1,0x5                                    
            packuswb mm0,mm1                                  
            movq   mm1,QWORD PTR [ecx]                        
        pavgusb mm0,mm1                                   
            movq   QWORD PTR [ecx],mm0                        
            movq   mm0,QWORD PTR [edx+0x10]                   
        movq   mm1,QWORD PTR [edx+0x18]                   
        paddw  mm0,QWORD PTR [ff_pw_16]                       
            paddw  mm1,QWORD PTR [ff_pw_16]                        
            psraw  mm0,0x5                                    
            psraw  mm1,0x5                                    
            packuswb mm0,mm1                                  
            movq   mm1,QWORD PTR [ecx+0x8]                    
        pavgusb mm0,mm1                                   
            movq   QWORD PTR [ecx+0x8],mm0                    
            mov    edx,DWORD PTR [esp+0x48]                   
        add    DWORD PTR [esp+0x8],0x1                    
            add    eax,DWORD PTR [esp+0x4c]                   
        add    ecx,edx                                    
            mov    DWORD PTR [esp],ecx                        
            mov    ecx,DWORD PTR [esp+0x50]                   
        cmp    DWORD PTR [esp+0x8],ecx                    
            jne    avg_mpeg4_qpel16_h_lowpass_3dnow__66d0     
avg_mpeg4_qpel16_h_lowpass_3dnow__6baf:           
        add    esp,0x2c                                   
            pop    ebx                                        
            pop    esi                                        
            pop    edi                                        
            pop    ebp                                        
            ret                                               

    }
}

NAKED void avg_mpeg4_qpel16_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0x234                                  
            mov    DWORD PTR [esp+0x224],ebx                  
            mov    ecx,DWORD PTR [esp+0x238]                  
        mov    edx,esp                                    
            mov    DWORD PTR [esp+0x228],esi                  
            mov    ebx,DWORD PTR [esp+0x23c]                  
        mov    esi,esp                                    
            mov    DWORD PTR [esp+0x22c],edi                  
            mov    eax,DWORD PTR [esp+0x240]                  
        mov    edi,0x11                                   
            mov    DWORD PTR [esp+0x230],ebp                  
            mov    ebp,DWORD PTR [esp+0x244]                  
        pxor   mm7,mm7                                    
avg_mpeg4_qpel16_v_lowpass_3dnow__f92a:           
        movq   mm0,QWORD PTR [ebx]                        
        movq   mm1,QWORD PTR [ebx]                        
        movq   mm2,QWORD PTR [ebx+0x8]                    
        movq   mm3,QWORD PTR [ebx+0x8]                    
        punpcklbw mm0,mm7                                 
            punpckhbw mm1,mm7                                 
            punpcklbw mm2,mm7                                 
            punpckhbw mm3,mm7                                 
            movq   QWORD PTR [esi],mm0                        
            movq   QWORD PTR [esi+0x88],mm1                   
            movq   QWORD PTR [esi+0x110],mm2                  
            movq   QWORD PTR [esi+0x198],mm3                  
            add    esi,0x8                                    
            add    ebx,ebp                                    
            dec    edi                                        
            jne    avg_mpeg4_qpel16_v_lowpass_3dnow__f92a     
            imul   esi,eax,0xfffffff2                         
            mov    edi,0x4                                    
            lea    ebx,[eax+eax*1]                            
        add    esi,0x4                                    
avg_mpeg4_qpel16_v_lowpass_3dnow__f972:           
        movq   mm0,QWORD PTR [edx]                        
        movq   mm1,QWORD PTR [edx+0x8]                    
        movq   mm2,QWORD PTR [edx+0x10]                   
        movq   mm3,QWORD PTR [edx+0x18]                   
        paddw  mm0,mm1                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm0                                    
            movq   mm0,QWORD PTR [edx+0x20]                   
        movq   mm5,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm0                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x8]                    
        movq   mm6,QWORD PTR [edx]                        
        paddw  mm5,mm3                                    
            paddw  mm6,mm2                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm1,mm2                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm1                                    
            movq   mm1,QWORD PTR [edx+0x28]                   
        movq   mm5,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm1                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx]                        
        movq   mm6,QWORD PTR [edx]                        
        paddw  mm5,mm0                                    
            paddw  mm6,mm3                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm2,mm3                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm2                                    
            movq   mm2,QWORD PTR [edx+0x30]                   
        movq   mm5,QWORD PTR [edx]                        
        paddw  mm5,mm2                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx]                        
        movq   mm6,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm1                                    
            paddw  mm6,mm0                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm3,mm0                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm3                                    
            movq   mm3,QWORD PTR [edx+0x38]                   
        movq   mm5,QWORD PTR [edx]                        
        paddw  mm5,mm3                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x8]                    
        movq   mm6,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm2                                    
            paddw  mm6,mm1                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm0,mm1                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm0                                    
            movq   mm0,QWORD PTR [edx+0x40]                   
        movq   mm5,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm0                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x10]                   
        movq   mm6,QWORD PTR [edx+0x18]                   
        paddw  mm5,mm3                                    
            paddw  mm6,mm2                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm1,mm2                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm1                                    
            movq   mm1,QWORD PTR [edx+0x48]                   
        movq   mm5,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm1                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x18]                   
        movq   mm6,QWORD PTR [edx+0x20]                   
        paddw  mm5,mm0                                    
            paddw  mm6,mm3                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm2,mm3                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm2                                    
            movq   mm2,QWORD PTR [edx+0x50]                   
        movq   mm5,QWORD PTR [edx+0x18]                   
        paddw  mm5,mm2                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x20]                   
        movq   mm6,QWORD PTR [edx+0x28]                   
        paddw  mm5,mm1                                    
            paddw  mm6,mm0                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm3,mm0                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm3                                    
            movq   mm3,QWORD PTR [edx+0x58]                   
        movq   mm5,QWORD PTR [edx+0x20]                   
        paddw  mm5,mm3                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x28]                   
        movq   mm6,QWORD PTR [edx+0x30]                   
        paddw  mm5,mm2                                    
            paddw  mm6,mm1                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm0,mm1                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm0                                    
            movq   mm0,QWORD PTR [edx+0x60]                   
        movq   mm5,QWORD PTR [edx+0x28]                   
        paddw  mm5,mm0                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x30]                   
        movq   mm6,QWORD PTR [edx+0x38]                   
        paddw  mm5,mm3                                    
            paddw  mm6,mm2                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm1,mm2                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm1                                    
            movq   mm1,QWORD PTR [edx+0x68]                   
        movq   mm5,QWORD PTR [edx+0x30]                   
        paddw  mm5,mm1                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x38]                   
        movq   mm6,QWORD PTR [edx+0x40]                   
        paddw  mm5,mm0                                    
            paddw  mm6,mm3                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm2,mm3                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm2                                    
            movq   mm2,QWORD PTR [edx+0x70]                   
        movq   mm5,QWORD PTR [edx+0x38]                   
        paddw  mm5,mm2                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x40]                   
        movq   mm6,QWORD PTR [edx+0x48]                   
        paddw  mm5,mm1                                    
            paddw  mm6,mm0                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm3,mm0                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm3                                    
            movq   mm3,QWORD PTR [edx+0x78]                   
        movq   mm5,QWORD PTR [edx+0x40]                   
        paddw  mm5,mm3                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x48]                   
        movq   mm6,QWORD PTR [edx+0x50]                   
        paddw  mm5,mm2                                    
            paddw  mm6,mm1                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm0,mm1                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm0                                    
            movq   mm0,QWORD PTR [edx+0x80]                   
        movq   mm5,QWORD PTR [edx+0x48]                   
        paddw  mm5,mm0                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x50]                   
        movq   mm6,QWORD PTR [edx+0x58]                   
        paddw  mm5,mm3                                    
            paddw  mm6,mm2                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm1,mm2                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm1                                    
            movq   mm1,QWORD PTR [edx+0x80]                   
        movq   mm5,QWORD PTR [edx+0x50]                   
        paddw  mm5,mm1                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x58]                   
        movq   mm6,QWORD PTR [edx+0x60]                   
        paddw  mm5,mm0                                    
            paddw  mm6,mm3                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm2,mm3                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm2                                    
            movq   mm2,QWORD PTR [edx+0x78]                   
        movq   mm5,QWORD PTR [edx+0x58]                   
        paddw  mm5,mm2                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x60]                   
        movq   mm6,QWORD PTR [edx+0x68]                   
        paddw  mm5,mm1                                    
            paddw  mm6,mm0                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm3,mm0                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm3                                    
            movq   mm3,QWORD PTR [edx+0x70]                   
        movq   mm5,QWORD PTR [edx+0x60]                   
        paddw  mm5,mm3                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x68]                   
        movq   mm6,QWORD PTR [edx+0x70]                   
        paddw  mm5,mm2                                    
            paddw  mm6,mm1                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgusb mm5,mm7                                   
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    edx,0x88                                   
            add    ecx,esi                                    
            dec    edi                                        
            jne    avg_mpeg4_qpel16_v_lowpass_3dnow__f972     
            mov    ebx,DWORD PTR [esp+0x224]                  
        mov    esi,DWORD PTR [esp+0x228]                  
        mov    edi,DWORD PTR [esp+0x22c]                  
        mov    ebp,DWORD PTR [esp+0x230]                  
        add    esp,0x234                                  
            ret                                               

    }
}


NAKED void put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        push   ebp                                                 
            push   edi                                                 
            push   esi                                                 
            push   ebx                                                 
            sub    esp,0x1c                                            
            mov    esi,DWORD PTR [esp+0x40]                            
        mov    ecx,DWORD PTR [esp+0x30]                            
        mov    eax,DWORD PTR [esp+0x34]                            
        test   esi,esi                                             
            jle    put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow__79cb        
            lea    edx,[esp+0xc]                                       
        mov    DWORD PTR [esp+0x8],0x0                             

            mov    DWORD PTR [esp+0x4],edx                             
            mov    DWORD PTR [esp],ecx                                 
            xchg   ax,ax                                               
put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow__7750:              
        movzx  edi,BYTE PTR [eax+0x2]                              
        movzx  edx,BYTE PTR [eax+0x4]                              
        movzx  esi,BYTE PTR [eax]                                  
        movzx  ebx,BYTE PTR [eax+0x1]                              
        mov    ecx,edi                                             
            and    edi,0xff                                            
            movzx  ebp,cl                                              
            neg    edx                                                 
            sub    dx,bp                                               
            add    edi,esi                                             
            lea    ebp,[ebx+esi*1]                                     
        lea    ebp,[ebp+ebp*4+0x0]                                 
        lea    ebp,[edx+ebp*4]                                     
        movzx  edx,BYTE PTR [eax+0x3]                              
        lea    edi,[edi+edi*2]                                     
        add    edi,edi                                             
            sub    bp,di                                               
            lea    ebx,[edx+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    ebp,ebx                                             
            mov    WORD PTR [esp+0xc],bp                               
            movzx  esi,BYTE PTR [eax+0x1]                              
        movzx  edx,BYTE PTR [eax+0x5]                              
        movzx  ebx,BYTE PTR [eax]                                  
        mov    ecx,esi                                             
            and    esi,0xff                                            
            movzx  edi,cl                                              
            neg    edx                                                 
            sub    dx,di                                               
            movzx  edi,BYTE PTR [eax+0x2]                              
        lea    esi,[edi+esi*1]                                     
        lea    esi,[esi+esi*4]                                     
        lea    edx,[edx+esi*4]                                     
        movzx  esi,BYTE PTR [eax+0x3]                              
        add    esi,ebx                                             
            lea    esi,[esi+esi*2]                                     
        add    esi,esi                                             
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x4]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0xe],dx                               
            movzx  ebx,BYTE PTR [eax]                                  
        movzx  edx,BYTE PTR [eax+0x6]                              
        movzx  edi,BYTE PTR [eax+0x3]                              
        movzx  esi,bl                                              
            movzx  ebx,bl                                              
            neg    edx                                                 
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x2]                              
        lea    esi,[edi+esi*1]                                     
        movzx  edi,BYTE PTR [eax+0x4]                              
        lea    esi,[esi+esi*4]                                     
        lea    edx,[edx+esi*4]                                     
        movzx  esi,BYTE PTR [eax+0x1]                              
        lea    esi,[edi+esi*1]                                     
        lea    esi,[esi+esi*2]                                     
        add    esi,esi                                             
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x5]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x10],dx                              
            movzx  edx,BYTE PTR [eax+0x7]                              
        movzx  ebx,BYTE PTR [eax]                                  
        movzx  esi,BYTE PTR [eax+0x4]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x3]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x5]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x2]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x6]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x1]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x12],dx                              
            movzx  edx,BYTE PTR [eax+0x8]                              
        movzx  ebx,BYTE PTR [eax+0x1]                              
        movzx  esi,BYTE PTR [eax+0x5]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x4]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x6]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x3]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x7]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x2]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x14],dx                              
            movzx  ebx,BYTE PTR [eax+0x8]                              
        movzx  esi,BYTE PTR [eax+0x2]                              
        movzx  edi,BYTE PTR [eax+0x6]                              
        movzx  edx,bl                                              
            movzx  ebx,bl                                              
            neg    edx                                                 
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x5]                              
        lea    esi,[edi+esi*1]                                     
        movzx  edi,BYTE PTR [eax+0x7]                              
        lea    esi,[esi+esi*4]                                     
        lea    edx,[edx+esi*4]                                     
        movzx  esi,BYTE PTR [eax+0x4]                              
        lea    esi,[edi+esi*1]                                     
        lea    esi,[esi+esi*2]                                     
        add    esi,esi                                             
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x3]                              
        add    ebx,esi                                             
            lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x16],dx                              
            movzx  esi,BYTE PTR [eax+0x7]                              
        movzx  edi,BYTE PTR [eax+0x3]                              
        movzx  ebx,BYTE PTR [eax+0x8]                              
        mov    ecx,esi                                             
            and    esi,0xff                                            
            movzx  edx,cl                                              
            neg    edx                                                 
            sub    dx,di                                               
            movzx  edi,BYTE PTR [eax+0x6]                              
        add    esi,edi                                             
            lea    esi,[esi+esi*4]                                     
        lea    edx,[edx+esi*4]                                     
        movzx  esi,BYTE PTR [eax+0x5]                              
        lea    esi,[ebx+esi*1]                                     
        lea    esi,[esi+esi*2]                                     
        add    esi,esi                                             
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x4]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x18],dx                              
            movzx  edi,BYTE PTR [eax+0x6]                              
        movzx  ebx,BYTE PTR [eax+0x7]                              
        movzx  esi,BYTE PTR [eax+0x8]                              
        movzx  ebp,BYTE PTR [eax+0x4]                              
        mov    ecx,edi                                             
            and    edi,0xff                                            
            movzx  edx,cl                                              
            mov    ecx,DWORD PTR [esp]                                 
        neg    edx                                                 
            add    edi,esi                                             
            sub    dx,bp                                               
            lea    ebp,[esi+ebx*1]                                     
        lea    ebp,[ebp+ebp*4+0x0]                                 
        lea    ebp,[edx+ebp*4]                                     
        movzx  edx,BYTE PTR [eax+0x5]                              
        lea    edi,[edi+edi*2]                                     
        add    edi,edi                                             
            sub    bp,di                                               
            lea    ebx,[edx+ebx*1]                                     
        mov    edx,DWORD PTR [esp+0x4]                             
        lea    ebx,[ebx+ebx*2]                                     
        add    ebp,ebx                                             
            mov    WORD PTR [esp+0x1a],bp                              
            movq   mm0,QWORD PTR [edx]                                 
        movq   mm1,QWORD PTR [edx+0x8]                             
        paddw  mm0,QWORD PTR [ff_pw_15]                                
            paddw  mm1,QWORD PTR [ff_pw_15]                                
            psraw  mm0,0x5                                             
            psraw  mm1,0x5                                             
            packuswb mm0,mm1                                           
            movq   QWORD PTR [ecx],mm0                                 
            mov    edx,DWORD PTR [esp+0x38]                            
        add    DWORD PTR [esp+0x8],0x1                             
            add    eax,DWORD PTR [esp+0x3c]                            
        add    ecx,edx                                             
            mov    DWORD PTR [esp],ecx                                 
            mov    ecx,DWORD PTR [esp+0x40]                            
        cmp    DWORD PTR [esp+0x8],ecx                             
            jne    put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow__7750        
put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow__79cb:              
        add    esp,0x1c                                            
            pop    ebx                                                 
            pop    esi                                                 
            pop    edi                                                 
            pop    ebp                                                 
            ret                                                        

    }
}

NAKED void put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0xa4                                          
            mov    DWORD PTR [esp+0x94],ebx                          
            mov    ecx,DWORD PTR [esp+0xa8]                          
        mov    edx,esp                                           
            mov    DWORD PTR [esp+0x98],esi                          
            mov    ebx,DWORD PTR [esp+0xac]                          
        mov    esi,esp                                           
            mov    DWORD PTR [esp+0x9c],edi                          
            mov    eax,DWORD PTR [esp+0xb0]                          
        mov    edi,0x9                                           
            mov    DWORD PTR [esp+0xa0],ebp                          
            mov    ebp,DWORD PTR [esp+0xb4]                          
        pxor   mm7,mm7                                           
put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow__1829a:           
        movq   mm0,QWORD PTR [ebx]                               
        movq   mm1,QWORD PTR [ebx]                               
        punpcklbw mm0,mm7                                        
            punpckhbw mm1,mm7                                        
            movq   QWORD PTR [esi],mm0                               
            movq   QWORD PTR [esi+0x48],mm1                          
            add    esi,0x8                                           
            add    ebx,ebp                                           
            dec    edi                                               
            jne    put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow__1829a     
            imul   esi,eax,0xfffffffa                                
            mov    edi,0x2                                           
            lea    ebx,[eax+eax*1]                                   
        add    esi,0x4                                           
put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow__182c3:           
        movq   mm0,QWORD PTR [edx]                               
        movq   mm1,QWORD PTR [edx+0x8]                           
        movq   mm2,QWORD PTR [edx+0x10]                          
        movq   mm3,QWORD PTR [edx+0x18]                          
        paddw  mm0,mm1                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm0                                           
            movq   mm0,QWORD PTR [edx+0x20]                          
        movq   mm5,QWORD PTR [edx+0x10]                          
        paddw  mm5,mm0                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x8]                           
        movq   mm6,QWORD PTR [edx]                               
        paddw  mm5,mm3                                           
            paddw  mm6,mm2                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm1,mm2                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm1                                           
            movq   mm1,QWORD PTR [edx+0x28]                          
        movq   mm5,QWORD PTR [edx+0x8]                           
        paddw  mm5,mm1                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx]                               
        movq   mm6,QWORD PTR [edx]                               
        paddw  mm5,mm0                                           
            paddw  mm6,mm3                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm2,mm3                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm2                                           
            movq   mm2,QWORD PTR [edx+0x30]                          
        movq   mm5,QWORD PTR [edx]                               
        paddw  mm5,mm2                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx]                               
        movq   mm6,QWORD PTR [edx+0x8]                           
        paddw  mm5,mm1                                           
            paddw  mm6,mm0                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm3,mm0                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm3                                           
            movq   mm3,QWORD PTR [edx+0x38]                          
        movq   mm5,QWORD PTR [edx]                               
        paddw  mm5,mm3                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x8]                           
        movq   mm6,QWORD PTR [edx+0x10]                          
        paddw  mm5,mm2                                           
            paddw  mm6,mm1                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm0,mm1                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm0                                           
            movq   mm0,QWORD PTR [edx+0x40]                          
        movq   mm5,QWORD PTR [edx+0x8]                           
        paddw  mm5,mm0                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x10]                          
        movq   mm6,QWORD PTR [edx+0x18]                          
        paddw  mm5,mm3                                           
            paddw  mm6,mm2                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm1,mm2                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm1                                           
            movq   mm1,QWORD PTR [edx+0x40]                          
        movq   mm5,QWORD PTR [edx+0x10]                          
        paddw  mm5,mm1                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x18]                          
        movq   mm6,QWORD PTR [edx+0x20]                          
        paddw  mm5,mm0                                           
            paddw  mm6,mm3                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm2,mm3                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm2                                           
            movq   mm2,QWORD PTR [edx+0x38]                          
        movq   mm5,QWORD PTR [edx+0x18]                          
        paddw  mm5,mm2                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x20]                          
        movq   mm6,QWORD PTR [edx+0x28]                          
        paddw  mm5,mm1                                           
            paddw  mm6,mm0                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm3,mm0                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm3                                           
            movq   mm3,QWORD PTR [edx+0x30]                          
        movq   mm5,QWORD PTR [edx+0x20]                          
        paddw  mm5,mm3                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x28]                          
        movq   mm6,QWORD PTR [edx+0x30]                          
        paddw  mm5,mm2                                           
            paddw  mm6,mm1                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    edx,0x48                                          
            add    ecx,esi                                           
            dec    edi                                               
            jne    put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow__182c3     
            mov    ebx,DWORD PTR [esp+0x94]                          
        mov    esi,DWORD PTR [esp+0x98]                          
        mov    edi,DWORD PTR [esp+0x9c]                          
        mov    ebp,DWORD PTR [esp+0xa0]                          
        add    esp,0xa4                                          
            ret                                                      

    }
}


NAKED void put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        push   ebp                                                 
            push   edi                                                 
            push   esi                                                 
            push   ebx                                                 
            sub    esp,0x2c                                            
            mov    ebx,DWORD PTR [esp+0x50]                            
        mov    ecx,DWORD PTR [esp+0x40]                            
        mov    eax,DWORD PTR [esp+0x44]                            
        test   ebx,ebx                                             
            jle    put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow__7620       
            lea    edx,[esp+0xc]                                       
        mov    DWORD PTR [esp+0x8],0x0                             

            mov    DWORD PTR [esp+0x4],edx                             
            mov    DWORD PTR [esp],ecx                                 
            xchg   ax,ax                                               
put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow__7150:             
        movzx  edi,BYTE PTR [eax+0x2]                              
        movzx  edx,BYTE PTR [eax+0x4]                              
        movzx  esi,BYTE PTR [eax]                                  
        movzx  ebx,BYTE PTR [eax+0x1]                              
        mov    ecx,edi                                             
            and    edi,0xff                                            
            movzx  ebp,cl                                              
            neg    edx                                                 
            sub    dx,bp                                               
            add    edi,esi                                             
            lea    ebp,[ebx+esi*1]                                     
        lea    ebp,[ebp+ebp*4+0x0]                                 
        lea    ebp,[edx+ebp*4]                                     
        movzx  edx,BYTE PTR [eax+0x3]                              
        lea    edi,[edi+edi*2]                                     
        add    edi,edi                                             
            sub    bp,di                                               
            lea    ebx,[edx+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    ebp,ebx                                             
            mov    WORD PTR [esp+0xc],bp                               
            movzx  esi,BYTE PTR [eax+0x1]                              
        movzx  edx,BYTE PTR [eax+0x5]                              
        movzx  ebx,BYTE PTR [eax]                                  
        mov    ecx,esi                                             
            and    esi,0xff                                            
            movzx  edi,cl                                              
            neg    edx                                                 
            sub    dx,di                                               
            movzx  edi,BYTE PTR [eax+0x2]                              
        lea    esi,[edi+esi*1]                                     
        lea    esi,[esi+esi*4]                                     
        lea    edx,[edx+esi*4]                                     
        movzx  esi,BYTE PTR [eax+0x3]                              
        add    esi,ebx                                             
            lea    esi,[esi+esi*2]                                     
        add    esi,esi                                             
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x4]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0xe],dx                               
            movzx  ebx,BYTE PTR [eax]                                  
        movzx  edx,BYTE PTR [eax+0x6]                              
        movzx  edi,BYTE PTR [eax+0x3]                              
        movzx  esi,bl                                              
            movzx  ebx,bl                                              
            neg    edx                                                 
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x2]                              
        lea    esi,[edi+esi*1]                                     
        movzx  edi,BYTE PTR [eax+0x4]                              
        lea    esi,[esi+esi*4]                                     
        lea    edx,[edx+esi*4]                                     
        movzx  esi,BYTE PTR [eax+0x1]                              
        lea    esi,[edi+esi*1]                                     
        lea    esi,[esi+esi*2]                                     
        add    esi,esi                                             
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0x5]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x10],dx                              
            movzx  edx,BYTE PTR [eax+0x7]                              
        movzx  ebx,BYTE PTR [eax]                                  
        movzx  esi,BYTE PTR [eax+0x4]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x3]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x5]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x2]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x6]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x1]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x12],dx                              
            movzx  edx,BYTE PTR [eax+0x8]                              
        movzx  ebx,BYTE PTR [eax+0x1]                              
        movzx  esi,BYTE PTR [eax+0x5]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x4]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x6]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x3]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x7]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x2]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x14],dx                              
            movzx  edx,BYTE PTR [eax+0x9]                              
        movzx  ebx,BYTE PTR [eax+0x2]                              
        movzx  esi,BYTE PTR [eax+0x6]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x5]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x7]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x4]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x8]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x3]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x16],dx                              
            movzx  edx,BYTE PTR [eax+0xa]                              
        movzx  ebx,BYTE PTR [eax+0x3]                              
        movzx  esi,BYTE PTR [eax+0x7]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x6]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x8]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x5]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x9]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x4]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x18],dx                              
            movzx  edx,BYTE PTR [eax+0xb]                              
        movzx  ebx,BYTE PTR [eax+0x4]                              
        movzx  esi,BYTE PTR [eax+0x8]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x7]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0x9]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x6]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xa]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x5]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x1a],dx                              
            movzx  edx,BYTE PTR [eax+0xc]                              
        movzx  ebx,BYTE PTR [eax+0x5]                              
        movzx  esi,BYTE PTR [eax+0x9]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x8]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xa]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x7]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xb]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x6]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x1c],dx                              
            movzx  edx,BYTE PTR [eax+0xd]                              
        movzx  ebx,BYTE PTR [eax+0x6]                              
        movzx  esi,BYTE PTR [eax+0xa]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x9]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xb]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x8]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xc]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x7]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x1e],dx                              
            movzx  edx,BYTE PTR [eax+0xe]                              
        movzx  ebx,BYTE PTR [eax+0x7]                              
        movzx  esi,BYTE PTR [eax+0xb]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0xa]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xc]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0x9]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xd]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x8]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x20],dx                              
            movzx  edx,BYTE PTR [eax+0xf]                              
        movzx  ebx,BYTE PTR [eax+0x8]                              
        movzx  esi,BYTE PTR [eax+0xc]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0xb]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xd]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0xa]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xe]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0x9]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x22],dx                              
            movzx  edx,BYTE PTR [eax+0x10]                             
        movzx  ebx,BYTE PTR [eax+0x9]                              
        movzx  esi,BYTE PTR [eax+0xd]                              
        neg    edx                                                 
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0xc]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xe]                              
        lea    ebx,[ebx+ebx*4]                                     
        lea    edx,[edx+ebx*4]                                     
        movzx  ebx,BYTE PTR [eax+0xb]                              
        lea    ebx,[esi+ebx*1]                                     
        movzx  esi,BYTE PTR [eax+0xf]                              
        lea    ebx,[ebx+ebx*2]                                     
        add    ebx,ebx                                             
            sub    dx,bx                                               
            movzx  ebx,BYTE PTR [eax+0xa]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x24],dx                              
            movzx  ebx,BYTE PTR [eax+0x10]                             
        movzx  esi,BYTE PTR [eax+0xa]                              
        movzx  edi,BYTE PTR [eax+0xe]                              
        movzx  edx,bl                                              
            movzx  ebx,bl                                              
            neg    edx                                                 
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0xd]                              
        lea    esi,[edi+esi*1]                                     
        movzx  edi,BYTE PTR [eax+0xf]                              
        lea    esi,[esi+esi*4]                                     
        lea    edx,[edx+esi*4]                                     
        movzx  esi,BYTE PTR [eax+0xc]                              
        lea    esi,[edi+esi*1]                                     
        lea    esi,[esi+esi*2]                                     
        add    esi,esi                                             
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0xb]                              
        add    ebx,esi                                             
            lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x26],dx                              
            movzx  esi,BYTE PTR [eax+0xf]                              
        movzx  edi,BYTE PTR [eax+0xb]                              
        movzx  ebx,BYTE PTR [eax+0x10]                             
        mov    ecx,esi                                             
            and    esi,0xff                                            
            movzx  edx,cl                                              
            neg    edx                                                 
            sub    dx,di                                               
            movzx  edi,BYTE PTR [eax+0xe]                              
        add    esi,edi                                             
            lea    esi,[esi+esi*4]                                     
        lea    edx,[edx+esi*4]                                     
        movzx  esi,BYTE PTR [eax+0xd]                              
        lea    esi,[ebx+esi*1]                                     
        lea    esi,[esi+esi*2]                                     
        add    esi,esi                                             
            sub    dx,si                                               
            movzx  esi,BYTE PTR [eax+0xc]                              
        lea    ebx,[esi+ebx*1]                                     
        lea    ebx,[ebx+ebx*2]                                     
        add    edx,ebx                                             
            mov    WORD PTR [esp+0x28],dx                              
            movzx  edi,BYTE PTR [eax+0xe]                              
        movzx  ebx,BYTE PTR [eax+0xf]                              
        movzx  esi,BYTE PTR [eax+0x10]                             
        movzx  ebp,BYTE PTR [eax+0xc]                              
        mov    ecx,edi                                             
            and    edi,0xff                                            
            movzx  edx,cl                                              
            mov    ecx,DWORD PTR [esp]                                 
        neg    edx                                                 
            add    edi,esi                                             
            sub    dx,bp                                               
            lea    ebp,[esi+ebx*1]                                     
        lea    ebp,[ebp+ebp*4+0x0]                                 
        lea    ebp,[edx+ebp*4]                                     
        movzx  edx,BYTE PTR [eax+0xd]                              
        lea    edi,[edi+edi*2]                                     
        add    edi,edi                                             
            sub    bp,di                                               
            lea    ebx,[edx+ebx*1]                                     
        mov    edx,DWORD PTR [esp+0x4]                             
        lea    ebx,[ebx+ebx*2]                                     
        add    ebp,ebx                                             
            mov    WORD PTR [esp+0x2a],bp                              
            movq   mm0,QWORD PTR [edx]                                 
        movq   mm1,QWORD PTR [edx+0x8]                             
        paddw  mm0,QWORD PTR [ff_pw_15]                                
            paddw  mm1,QWORD PTR [ff_pw_15]                                
            psraw  mm0,0x5                                             
            psraw  mm1,0x5                                             
            packuswb mm0,mm1                                           
            movq   QWORD PTR [ecx],mm0                                 
            movq   mm0,QWORD PTR [edx+0x10]                            
        movq   mm1,QWORD PTR [edx+0x18]                            
        paddw  mm0,QWORD PTR [ff_pw_15]                                
            paddw  mm1,QWORD PTR [ff_pw_15]                                
            psraw  mm0,0x5                                             
            psraw  mm1,0x5                                             
            packuswb mm0,mm1                                           
            movq   QWORD PTR [ecx+0x8],mm0                             
            mov    edx,DWORD PTR [esp+0x48]                            
        add    DWORD PTR [esp+0x8],0x1                             
            add    eax,DWORD PTR [esp+0x4c]                            
        add    ecx,edx                                             
            mov    DWORD PTR [esp],ecx                                 
            mov    ecx,DWORD PTR [esp+0x50]                            
        cmp    DWORD PTR [esp+0x8],ecx                             
            jne    put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow__7150       
            add    esp,0x2c                                            
put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow__7620:             
        pop    ebx                                                 
            pop    esi                                                 
            pop    edi                                                 
            pop    ebp                                                 
            ret                                                        

    }
}

NAKED void put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0x234                                        
            mov    DWORD PTR [esp+0x224],ebx                        
            mov    ecx,DWORD PTR [esp+0x238]                        
        mov    edx,esp                                          
            mov    DWORD PTR [esp+0x228],esi                        
            mov    ebx,DWORD PTR [esp+0x23c]                        
        mov    esi,esp                                          
            mov    DWORD PTR [esp+0x22c],edi                        
            mov    eax,DWORD PTR [esp+0x240]                        
        mov    edi,0x11                                         
            mov    DWORD PTR [esp+0x230],ebp                        
            mov    ebp,DWORD PTR [esp+0x244]                        
        pxor   mm7,mm7                                          
put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow__17d0a:         
        movq   mm0,QWORD PTR [ebx]                              
        movq   mm1,QWORD PTR [ebx]                              
        movq   mm2,QWORD PTR [ebx+0x8]                          
        movq   mm3,QWORD PTR [ebx+0x8]                          
        punpcklbw mm0,mm7                                       
            punpckhbw mm1,mm7                                       
            punpcklbw mm2,mm7                                       
            punpckhbw mm3,mm7                                       
            movq   QWORD PTR [esi],mm0                              
            movq   QWORD PTR [esi+0x88],mm1                         
            movq   QWORD PTR [esi+0x110],mm2                        
            movq   QWORD PTR [esi+0x198],mm3                        
            add    esi,0x8                                          
            add    ebx,ebp                                          
            dec    edi                                              
            jne    put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow__17d0a   
            imul   esi,eax,0xfffffff2                               
            mov    edi,0x4                                          
            lea    ebx,[eax+eax*1]                                  
        add    esi,0x4                                          
put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow__17d52:         
        movq   mm0,QWORD PTR [edx]                              
        movq   mm1,QWORD PTR [edx+0x8]                          
        movq   mm2,QWORD PTR [edx+0x10]                         
        movq   mm3,QWORD PTR [edx+0x18]                         
        paddw  mm0,mm1                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm0                                          
            movq   mm0,QWORD PTR [edx+0x20]                         
        movq   mm5,QWORD PTR [edx+0x10]                         
        paddw  mm5,mm0                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x8]                          
        movq   mm6,QWORD PTR [edx]                              
        paddw  mm5,mm3                                          
            paddw  mm6,mm2                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm1,mm2                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm1                                          
            movq   mm1,QWORD PTR [edx+0x28]                         
        movq   mm5,QWORD PTR [edx+0x8]                          
        paddw  mm5,mm1                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx]                              
        movq   mm6,QWORD PTR [edx]                              
        paddw  mm5,mm0                                          
            paddw  mm6,mm3                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm2,mm3                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm2                                          
            movq   mm2,QWORD PTR [edx+0x30]                         
        movq   mm5,QWORD PTR [edx]                              
        paddw  mm5,mm2                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx]                              
        movq   mm6,QWORD PTR [edx+0x8]                          
        paddw  mm5,mm1                                          
            paddw  mm6,mm0                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm3,mm0                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm3                                          
            movq   mm3,QWORD PTR [edx+0x38]                         
        movq   mm5,QWORD PTR [edx]                              
        paddw  mm5,mm3                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x8]                          
        movq   mm6,QWORD PTR [edx+0x10]                         
        paddw  mm5,mm2                                          
            paddw  mm6,mm1                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm0,mm1                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm0                                          
            movq   mm0,QWORD PTR [edx+0x40]                         
        movq   mm5,QWORD PTR [edx+0x8]                          
        paddw  mm5,mm0                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x10]                         
        movq   mm6,QWORD PTR [edx+0x18]                         
        paddw  mm5,mm3                                          
            paddw  mm6,mm2                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm1,mm2                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm1                                          
            movq   mm1,QWORD PTR [edx+0x48]                         
        movq   mm5,QWORD PTR [edx+0x10]                         
        paddw  mm5,mm1                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x18]                         
        movq   mm6,QWORD PTR [edx+0x20]                         
        paddw  mm5,mm0                                          
            paddw  mm6,mm3                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm2,mm3                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm2                                          
            movq   mm2,QWORD PTR [edx+0x50]                         
        movq   mm5,QWORD PTR [edx+0x18]                         
        paddw  mm5,mm2                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x20]                         
        movq   mm6,QWORD PTR [edx+0x28]                         
        paddw  mm5,mm1                                          
            paddw  mm6,mm0                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm3,mm0                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm3                                          
            movq   mm3,QWORD PTR [edx+0x58]                         
        movq   mm5,QWORD PTR [edx+0x20]                         
        paddw  mm5,mm3                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x28]                         
        movq   mm6,QWORD PTR [edx+0x30]                         
        paddw  mm5,mm2                                          
            paddw  mm6,mm1                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm0,mm1                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm0                                          
            movq   mm0,QWORD PTR [edx+0x60]                         
        movq   mm5,QWORD PTR [edx+0x28]                         
        paddw  mm5,mm0                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x30]                         
        movq   mm6,QWORD PTR [edx+0x38]                         
        paddw  mm5,mm3                                          
            paddw  mm6,mm2                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm1,mm2                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm1                                          
            movq   mm1,QWORD PTR [edx+0x68]                         
        movq   mm5,QWORD PTR [edx+0x30]                         
        paddw  mm5,mm1                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x38]                         
        movq   mm6,QWORD PTR [edx+0x40]                         
        paddw  mm5,mm0                                          
            paddw  mm6,mm3                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm2,mm3                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm2                                          
            movq   mm2,QWORD PTR [edx+0x70]                         
        movq   mm5,QWORD PTR [edx+0x38]                         
        paddw  mm5,mm2                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x40]                         
        movq   mm6,QWORD PTR [edx+0x48]                         
        paddw  mm5,mm1                                          
            paddw  mm6,mm0                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm3,mm0                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm3                                          
            movq   mm3,QWORD PTR [edx+0x78]                         
        movq   mm5,QWORD PTR [edx+0x40]                         
        paddw  mm5,mm3                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x48]                         
        movq   mm6,QWORD PTR [edx+0x50]                         
        paddw  mm5,mm2                                          
            paddw  mm6,mm1                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm0,mm1                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm0                                          
            movq   mm0,QWORD PTR [edx+0x80]                         
        movq   mm5,QWORD PTR [edx+0x48]                         
        paddw  mm5,mm0                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x50]                         
        movq   mm6,QWORD PTR [edx+0x58]                         
        paddw  mm5,mm3                                          
            paddw  mm6,mm2                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm1,mm2                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm1                                          
            movq   mm1,QWORD PTR [edx+0x80]                         
        movq   mm5,QWORD PTR [edx+0x50]                         
        paddw  mm5,mm1                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x58]                         
        movq   mm6,QWORD PTR [edx+0x60]                         
        paddw  mm5,mm0                                          
            paddw  mm6,mm3                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm2,mm3                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm2                                          
            movq   mm2,QWORD PTR [edx+0x78]                         
        movq   mm5,QWORD PTR [edx+0x58]                         
        paddw  mm5,mm2                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x60]                         
        movq   mm6,QWORD PTR [edx+0x68]                         
        paddw  mm5,mm1                                          
            paddw  mm6,mm0                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm3,mm0                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm3                                          
            movq   mm3,QWORD PTR [edx+0x70]                         
        movq   mm5,QWORD PTR [edx+0x60]                         
        paddw  mm5,mm3                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x68]                         
        movq   mm6,QWORD PTR [edx+0x70]                         
        paddw  mm5,mm2                                          
            paddw  mm6,mm1                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_15]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    edx,0x88                                         
            add    ecx,esi                                          
            dec    edi                                              
            jne    put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow__17d52   
            mov    ebx,DWORD PTR [esp+0x224]                        
        mov    esi,DWORD PTR [esp+0x228]                        
        mov    edi,DWORD PTR [esp+0x22c]                        
        mov    ebp,DWORD PTR [esp+0x230]                        
        add    esp,0x234                                        
            ret                                                     

    }
}

NAKED void put_mpeg4_qpel8_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        sub    esp,0x8                               
            mov    DWORD PTR [esp],esi                   
            mov    ecx,DWORD PTR [esp+0xc]               
        mov    DWORD PTR [esp+0x4],edi               
            mov    eax,DWORD PTR [esp+0x10]              
        mov    edx,DWORD PTR [esp+0x1c]              
        mov    esi,DWORD PTR [esp+0x18]              
        mov    edi,DWORD PTR [esp+0x14]              
        pxor   mm7,mm7                               
put_mpeg4_qpel8_h_lowpass_mmx2__6151:        
        movq   mm0,QWORD PTR [eax]                   
        movq   mm1,mm0                               
            movq   mm2,mm0                               
            punpcklbw mm0,mm7                            
            punpckhbw mm1,mm7                            
            pshufw mm5,mm0,0x90                          
            pshufw mm6,mm0,0x41                          
            movq   mm3,mm2                               
            movq   mm4,mm2                               
            psllq  mm2,0x8                               
            psllq  mm3,0x10                              
            psllq  mm4,0x18                              
            punpckhbw mm2,mm7                            
            punpckhbw mm3,mm7                            
            punpckhbw mm4,mm7                            
            paddw  mm5,mm3                               
            paddw  mm6,mm2                               
            paddw  mm5,mm5                               
            psubw  mm6,mm5                               
            pshufw mm5,mm0,0x6                           
            pmullw mm6,QWORD PTR [ff_pw_3]
            paddw  mm0,mm4                               
            paddw  mm5,mm1                               
            pmullw mm0,QWORD PTR [ff_pw_20]
            psubw  mm0,mm5                               
            paddw  mm6,QWORD PTR [ff_pw_16]                
            paddw  mm0,mm6                               
            psraw  mm0,0x5                               
            movd   mm5,DWORD PTR [eax+0x5]               
        punpcklbw mm5,mm7                            
            pshufw mm6,mm5,0xf9                          
            paddw  mm1,mm5                               
            paddw  mm2,mm6                               
            pshufw mm6,mm5,0xbe                          
            pshufw mm5,mm5,0x6f                          
            paddw  mm3,mm6                               
            paddw  mm4,mm5                               
            paddw  mm2,mm2                               
            psubw  mm3,mm2                               
            pmullw mm1,QWORD PTR [ff_pw_20]                  
            pmullw mm3,QWORD PTR [ff_pw_3]                  
            psubw  mm3,mm4                               
            paddw  mm1,QWORD PTR [ff_pw_16]                  
            paddw  mm3,mm1                               
            psraw  mm3,0x5                               
            packuswb mm0,mm3                             
            movq   QWORD PTR [ecx],mm0                   
            add    eax,esi                               
            add    ecx,edi                               
            dec    edx                                   
            jne    put_mpeg4_qpel8_h_lowpass_mmx2__6151  
            mov    esi,DWORD PTR [esp]                   
        mov    edi,DWORD PTR [esp+0x4]               
        add    esp,0x8                               
            ret                                          

    }
}

void __declspec(naked) put_mpeg4_qpel8_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm{
        sub    esp,0xa4                                 
            mov    DWORD PTR [esp+0x94],ebx                 
            mov    ecx,DWORD PTR [esp+0xa8]                 
        mov    edx,esp                                  
            mov    DWORD PTR [esp+0x98],esi                 
            mov    ebx,DWORD PTR [esp+0xac]                 
        mov    esi,esp                                  
            mov    DWORD PTR [esp+0x9c],edi                 
            mov    eax,DWORD PTR [esp+0xb0]                 
        mov    edi,0x9                                  
            mov    DWORD PTR [esp+0xa0],ebp                 
            mov    ebp,DWORD PTR [esp+0xb4]                 
        pxor   mm7,mm7                                  
put_mpeg4_qpel8_v_lowpass_mmx2__20a0a:          
        movq   mm0,QWORD PTR [ebx]                      
        movq   mm1,QWORD PTR [ebx]                      
        punpcklbw mm0,mm7                               
            punpckhbw mm1,mm7                               
            movq   QWORD PTR [esi],mm0                      
            movq   QWORD PTR [esi+0x48],mm1                 
            add    esi,0x8                                  
            add    ebx,ebp                                  
            dec    edi                                      
            jne    put_mpeg4_qpel8_v_lowpass_mmx2__20a0a    
            imul   esi,eax,0xfffffffa                       
            mov    edi,0x2                                  
            lea    ebx,[eax+eax*1]                          
        add    esi,0x4                                  
put_mpeg4_qpel8_v_lowpass_mmx2__20a33:          
        movq   mm0,QWORD PTR [edx]                      
        movq   mm1,QWORD PTR [edx+0x8]                  
        movq   mm2,QWORD PTR [edx+0x10]                 
        movq   mm3,QWORD PTR [edx+0x18]                 
        paddw  mm0,mm1                                  
            movq   mm4,QWORD PTR [ff_pw_20]                     
        pmullw mm4,mm0                                  
            movq   mm0,QWORD PTR [edx+0x20]                 
        movq   mm5,QWORD PTR [edx+0x10]                 
        paddw  mm5,mm0                                  
            psubw  mm4,mm5                                  
            movq   mm5,QWORD PTR [edx+0x8]                  
        movq   mm6,QWORD PTR [edx]                      
        paddw  mm5,mm3                                  
            paddw  mm6,mm2                                  
            paddw  mm6,mm6                                  
            psubw  mm5,mm6                                  
            pmullw mm5,QWORD PTR [ff_pw_3]                     
        paddw  mm4,QWORD PTR [ff_pw_16]                    
        paddw  mm5,mm4                                  
            psraw  mm5,0x5                                  
            packuswb mm5,mm5                                
            movd   DWORD PTR [ecx],mm5                      
            paddw  mm1,mm2                                  
            movq   mm4,QWORD PTR [ff_pw_20]                     
        pmullw mm4,mm1                                  
            movq   mm1,QWORD PTR [edx+0x28]                 
        movq   mm5,QWORD PTR [edx+0x8]                  
        paddw  mm5,mm1                                  
            psubw  mm4,mm5                                  
            movq   mm5,QWORD PTR [edx]                      
        movq   mm6,QWORD PTR [edx]                      
        paddw  mm5,mm0                                  
            paddw  mm6,mm3                                  
            paddw  mm6,mm6                                  
            psubw  mm5,mm6                                  
            pmullw mm5,QWORD PTR [ff_pw_3]                     
        paddw  mm4,QWORD PTR [ff_pw_16]                    
        paddw  mm5,mm4                                  
            psraw  mm5,0x5                                  
            packuswb mm5,mm5                                
            movd   DWORD PTR [ecx+eax*1],mm5                
            add    ecx,ebx                                  
            paddw  mm2,mm3                                  
            movq   mm4,QWORD PTR [ff_pw_20]                     
        pmullw mm4,mm2                                  
            movq   mm2,QWORD PTR [edx+0x30]                 
        movq   mm5,QWORD PTR [edx]                      
        paddw  mm5,mm2                                  
            psubw  mm4,mm5                                  
            movq   mm5,QWORD PTR [edx]                      
        movq   mm6,QWORD PTR [edx+0x8]                  
        paddw  mm5,mm1                                  
            paddw  mm6,mm0                                  
            paddw  mm6,mm6                                  
            psubw  mm5,mm6                                  
            pmullw mm5,QWORD PTR [ff_pw_3]                     
        paddw  mm4,QWORD PTR [ff_pw_16]                    
        paddw  mm5,mm4                                  
            psraw  mm5,0x5                                  
            packuswb mm5,mm5                                
            movd   DWORD PTR [ecx],mm5                      
            paddw  mm3,mm0                                  
            movq   mm4,QWORD PTR [ff_pw_20]                     
        pmullw mm4,mm3                                  
            movq   mm3,QWORD PTR [edx+0x38]                 
        movq   mm5,QWORD PTR [edx]                      
        paddw  mm5,mm3                                  
            psubw  mm4,mm5                                  
            movq   mm5,QWORD PTR [edx+0x8]                  
        movq   mm6,QWORD PTR [edx+0x10]                 
        paddw  mm5,mm2                                  
            paddw  mm6,mm1                                  
            paddw  mm6,mm6                                  
            psubw  mm5,mm6                                  
            pmullw mm5,QWORD PTR [ff_pw_3]                     
        paddw  mm4,QWORD PTR [ff_pw_16]                    
        paddw  mm5,mm4                                  
            psraw  mm5,0x5                                  
            packuswb mm5,mm5                                
            movd   DWORD PTR [ecx+eax*1],mm5                
            add    ecx,ebx                                  
            paddw  mm0,mm1                                  
            movq   mm4,QWORD PTR [ff_pw_20]                     
        pmullw mm4,mm0                                  
            movq   mm0,QWORD PTR [edx+0x40]                 
        movq   mm5,QWORD PTR [edx+0x8]                  
        paddw  mm5,mm0                                  
            psubw  mm4,mm5                                  
            movq   mm5,QWORD PTR [edx+0x10]                 
        movq   mm6,QWORD PTR [edx+0x18]                 
        paddw  mm5,mm3                                  
            paddw  mm6,mm2                                  
            paddw  mm6,mm6                                  
            psubw  mm5,mm6                                  
            pmullw mm5,QWORD PTR [ff_pw_3]                     
        paddw  mm4,QWORD PTR [ff_pw_16]                    
        paddw  mm5,mm4                                  
            psraw  mm5,0x5                                  
            packuswb mm5,mm5                                
            movd   DWORD PTR [ecx],mm5                      
            paddw  mm1,mm2                                  
            movq   mm4,QWORD PTR [ff_pw_20]                     
        pmullw mm4,mm1                                  
            movq   mm1,QWORD PTR [edx+0x40]                 
        movq   mm5,QWORD PTR [edx+0x10]                 
        paddw  mm5,mm1                                  
            psubw  mm4,mm5                                  
            movq   mm5,QWORD PTR [edx+0x18]                 
        movq   mm6,QWORD PTR [edx+0x20]                 
        paddw  mm5,mm0                                  
            paddw  mm6,mm3                                  
            paddw  mm6,mm6                                  
            psubw  mm5,mm6                                  
            pmullw mm5,QWORD PTR [ff_pw_3]                     
        paddw  mm4,QWORD PTR [ff_pw_16]                    
        paddw  mm5,mm4                                  
            psraw  mm5,0x5                                  
            packuswb mm5,mm5                                
            movd   DWORD PTR [ecx+eax*1],mm5                
            add    ecx,ebx                                  
            paddw  mm2,mm3                                  
            movq   mm4,QWORD PTR [ff_pw_20]                     
        pmullw mm4,mm2                                  
            movq   mm2,QWORD PTR [edx+0x38]                 
        movq   mm5,QWORD PTR [edx+0x18]                 
        paddw  mm5,mm2                                  
            psubw  mm4,mm5                                  
            movq   mm5,QWORD PTR [edx+0x20]                 
        movq   mm6,QWORD PTR [edx+0x28]                 
        paddw  mm5,mm1                                  
            paddw  mm6,mm0                                  
            paddw  mm6,mm6                                  
            psubw  mm5,mm6                                  
            pmullw mm5,QWORD PTR [ff_pw_3]                     
        paddw  mm4,QWORD PTR [ff_pw_16]                    
        paddw  mm5,mm4                                  
            psraw  mm5,0x5                                  
            packuswb mm5,mm5                                
            movd   DWORD PTR [ecx],mm5                      
            paddw  mm3,mm0                                  
            movq   mm4,QWORD PTR [ff_pw_20]                     
        pmullw mm4,mm3                                  
            movq   mm3,QWORD PTR [edx+0x30]                 
        movq   mm5,QWORD PTR [edx+0x20]                 
        paddw  mm5,mm3                                  
            psubw  mm4,mm5                                  
            movq   mm5,QWORD PTR [edx+0x28]                 
        movq   mm6,QWORD PTR [edx+0x30]                 
        paddw  mm5,mm2                                  
            paddw  mm6,mm1                                  
            paddw  mm6,mm6                                  
            psubw  mm5,mm6                                  
            pmullw mm5,QWORD PTR [ff_pw_3]                     
        paddw  mm4,QWORD PTR [ff_pw_16]                    
        paddw  mm5,mm4                                  
            psraw  mm5,0x5                                  
            packuswb mm5,mm5                                
            movd   DWORD PTR [ecx+eax*1],mm5                
            add    edx,0x48                                 
            add    ecx,esi                                  
            dec    edi                                      
            jne    put_mpeg4_qpel8_v_lowpass_mmx2__20a33    
            mov    ebx,DWORD PTR [esp+0x94]                 
        mov    esi,DWORD PTR [esp+0x98]                 
        mov    edi,DWORD PTR [esp+0x9c]                 
        mov    ebp,DWORD PTR [esp+0xa0]                 
        add    esp,0xa4                                 
            ret                                             
    }
}


NAKED void put_mpeg4_qpel16_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        sub    esp,0x1c                                 
            mov    DWORD PTR [esp+0x14],esi                 
            mov    ecx,DWORD PTR [esp+0x20]                 
        mov    DWORD PTR [esp+0x18],edi                 
            mov    eax,DWORD PTR [esp+0x24]                 
        mov    edi,DWORD PTR [esp+0x30]                 
        mov    edx,DWORD PTR [esp+0x2c]                 
        mov    esi,DWORD PTR [esp+0x28]                 
        pxor   mm7,mm7                                  
put_mpeg4_qpel16_h_lowpass_mmx2__5a92:          
        movq   mm0,QWORD PTR [eax]                      
        movq   mm1,mm0                                  
            movq   mm2,mm0                                  
            punpcklbw mm0,mm7                               
            punpckhbw mm1,mm7                               
            pshufw mm5,mm0,0x90                             
            pshufw mm6,mm0,0x41                             
            movq   mm3,mm2                                  
            movq   mm4,mm2                                  
            psllq  mm2,0x8                                  
            psllq  mm3,0x10                                 
            psllq  mm4,0x18                                 
            punpckhbw mm2,mm7                               
            punpckhbw mm3,mm7                               
            punpckhbw mm4,mm7                               
            paddw  mm5,mm3                                  
            paddw  mm6,mm2                                  
            paddw  mm5,mm5                                  
            psubw  mm6,mm5                                  
            pshufw mm5,mm0,0x6                              
            pmullw mm6,QWORD ptr [ff_pw_3]
            paddw  mm0,mm4                                  
            paddw  mm5,mm1                                  
            pmullw mm0,QWORD PTR [ff_pw_20]                    
            psubw  mm0,mm5                                  
            paddw  mm6,QWORD PTR [ff_pw_16]                    
            paddw  mm0,mm6                                  
            psraw  mm0,0x5                                  
            movq   QWORD PTR [esp+0x8],mm0                  
            movq   mm0,QWORD PTR [eax+0x5]                  
        movq   mm5,mm0                                  
            movq   mm6,mm0                                  
            psrlq  mm0,0x8                                  
            psrlq  mm5,0x10                                 
            punpcklbw mm0,mm7                               
            punpcklbw mm5,mm7                               
            paddw  mm2,mm0                                  
            paddw  mm3,mm5                                  
            paddw  mm2,mm2                                  
            psubw  mm3,mm2                                  
            movq   mm2,mm6                                  
            psrlq  mm6,0x18                                 
            punpcklbw mm2,mm7                               
            punpcklbw mm6,mm7                               
            pmullw mm3,QWORD PTR [ff_pw_3]
            paddw  mm1,mm2                                  
            paddw  mm4,mm6                                  
            pmullw mm1,QWORD PTR [ff_pw_20]                     
            psubw  mm3,mm4                                  
            paddw  mm1,QWORD PTR [ff_pw_16]                     
            paddw  mm3,mm1                                  
            psraw  mm3,0x5                                  
            movq   mm1,QWORD PTR [esp+0x8]                  
        packuswb mm1,mm3                                
            movq   QWORD PTR [ecx],mm1                      
            movq   mm1,QWORD PTR [eax+0x9]                  
        movq   mm4,mm1                                  
            movq   mm3,mm1                                  
            psrlq  mm1,0x8                                  
            psrlq  mm4,0x10                                 
            punpcklbw mm1,mm7                               
            punpcklbw mm4,mm7                               
            paddw  mm5,mm1                                  
            paddw  mm0,mm4                                  
            paddw  mm5,mm5                                  
            psubw  mm0,mm5                                  
            movq   mm5,mm3                                  
            psrlq  mm3,0x18                                 
            pmullw mm0,QWORD PTR [ff_pw_3]                    
            punpcklbw mm3,mm7                               
            paddw  mm2,mm3                                  
            psubw  mm0,mm2                                  
            movq   mm2,mm5                                  
            punpcklbw mm2,mm7                               
            punpckhbw mm5,mm7                               
            paddw  mm6,mm2                                  
            pmullw mm6,QWORD PTR [ff_pw_20]                  
            paddw  mm0,QWORD PTR [ff_pw_16]                     
            paddw  mm0,mm6                                  
            psraw  mm0,0x5                                  
            paddw  mm3,mm5                                  
            pshufw mm6,mm5,0xf9                             
            paddw  mm6,mm4                                  
            pshufw mm4,mm5,0xbe                             
            pshufw mm5,mm5,0x6f                             
            paddw  mm4,mm1                                  
            paddw  mm5,mm2                                  
            paddw  mm6,mm6                                  
            psubw  mm4,mm6                                  
            pmullw mm3,QWORD PTR [ff_pw_20]                
            pmullw mm4,QWORD PTR [ff_pw_3]                     
            psubw  mm3,mm5                                  
            paddw  mm4,QWORD PTR [ff_pw_16]                     
            paddw  mm4,mm3                                  
            psraw  mm4,0x5                                  
            packuswb mm0,mm4                                
            movq   QWORD PTR [ecx+0x8],mm0                  
            add    eax,edx                                  
            add    ecx,esi                                  
            dec    edi                                      
            jne    put_mpeg4_qpel16_h_lowpass_mmx2__5a92    
            mov    esi,DWORD PTR [esp+0x14]                 
        mov    edi,DWORD PTR [esp+0x18]                 
        add    esp,0x1c                                 
            ret                                             

    }
}


NAKED void put_mpeg4_qpel16_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0x234                                        
            mov    DWORD PTR [esp+0x224],ebx                        
            mov    ecx,DWORD PTR [esp+0x238]                        
        mov    edx,esp                                          
            mov    DWORD PTR [esp+0x228],esi                        
            mov    ebx,DWORD PTR [esp+0x23c]                        
        mov    esi,esp                                          
            mov    DWORD PTR [esp+0x22c],edi                        
            mov    eax,DWORD PTR [esp+0x240]                        
        mov    edi,0x11                                         
            mov    DWORD PTR [esp+0x230],ebp                        
            mov    ebp,DWORD PTR [esp+0x244]                        
        pxor   mm7,mm7                                          
put_mpeg4_qpel16_v_lowpass_mmx2__2047a:                 
        movq   mm0,QWORD PTR [ebx]                              
        movq   mm1,QWORD PTR [ebx]                              
        movq   mm2,QWORD PTR [ebx+0x8]                          
        movq   mm3,QWORD PTR [ebx+0x8]                          
        punpcklbw mm0,mm7                                       
            punpckhbw mm1,mm7                                       
            punpcklbw mm2,mm7                                       
            punpckhbw mm3,mm7                                       
            movq   QWORD PTR [esi],mm0                              
            movq   QWORD PTR [esi+0x88],mm1                         
            movq   QWORD PTR [esi+0x110],mm2                        
            movq   QWORD PTR [esi+0x198],mm3                        
            add    esi,0x8                                          
            add    ebx,ebp                                          
            dec    edi                                              
            jne    put_mpeg4_qpel16_v_lowpass_mmx2__2047a           
            imul   esi,eax,0xfffffff2                               
            mov    edi,0x4                                          
            lea    ebx,[eax+eax*1]                                  
        add    esi,0x4                                          
put_mpeg4_qpel16_v_lowpass_mmx2__204c2:                 
        movq   mm0,QWORD PTR [edx]                              
        movq   mm1,QWORD PTR [edx+0x8]                          
        movq   mm2,QWORD PTR [edx+0x10]                         
        movq   mm3,QWORD PTR [edx+0x18]                         
        paddw  mm0,mm1                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm0                                          
            movq   mm0,QWORD PTR [edx+0x20]                         
        movq   mm5,QWORD PTR [edx+0x10]                         
        paddw  mm5,mm0                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x8]                          
        movq   mm6,QWORD PTR [edx]                              
        paddw  mm5,mm3                                          
            paddw  mm6,mm2                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm1,mm2                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm1                                          
            movq   mm1,QWORD PTR [edx+0x28]                         
        movq   mm5,QWORD PTR [edx+0x8]                          
        paddw  mm5,mm1                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx]                              
        movq   mm6,QWORD PTR [edx]                              
        paddw  mm5,mm0                                          
            paddw  mm6,mm3                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm2,mm3                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm2                                          
            movq   mm2,QWORD PTR [edx+0x30]                         
        movq   mm5,QWORD PTR [edx]                              
        paddw  mm5,mm2                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx]                              
        movq   mm6,QWORD PTR [edx+0x8]                          
        paddw  mm5,mm1                                          
            paddw  mm6,mm0                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm3,mm0                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm3                                          
            movq   mm3,QWORD PTR [edx+0x38]                         
        movq   mm5,QWORD PTR [edx]                              
        paddw  mm5,mm3                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x8]                          
        movq   mm6,QWORD PTR [edx+0x10]                         
        paddw  mm5,mm2                                          
            paddw  mm6,mm1                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm0,mm1                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm0                                          
            movq   mm0,QWORD PTR [edx+0x40]                         
        movq   mm5,QWORD PTR [edx+0x8]                          
        paddw  mm5,mm0                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x10]                         
        movq   mm6,QWORD PTR [edx+0x18]                         
        paddw  mm5,mm3                                          
            paddw  mm6,mm2                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm1,mm2                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm1                                          
            movq   mm1,QWORD PTR [edx+0x48]                         
        movq   mm5,QWORD PTR [edx+0x10]                         
        paddw  mm5,mm1                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x18]                         
        movq   mm6,QWORD PTR [edx+0x20]                         
        paddw  mm5,mm0                                          
            paddw  mm6,mm3                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm2,mm3                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm2                                          
            movq   mm2,QWORD PTR [edx+0x50]                         
        movq   mm5,QWORD PTR [edx+0x18]                         
        paddw  mm5,mm2                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x20]                         
        movq   mm6,QWORD PTR [edx+0x28]                         
        paddw  mm5,mm1                                          
            paddw  mm6,mm0                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm3,mm0                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm3                                          
            movq   mm3,QWORD PTR [edx+0x58]                         
        movq   mm5,QWORD PTR [edx+0x20]                         
        paddw  mm5,mm3                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x28]                         
        movq   mm6,QWORD PTR [edx+0x30]                         
        paddw  mm5,mm2                                          
            paddw  mm6,mm1                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm0,mm1                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm0                                          
            movq   mm0,QWORD PTR [edx+0x60]                         
        movq   mm5,QWORD PTR [edx+0x28]                         
        paddw  mm5,mm0                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x30]                         
        movq   mm6,QWORD PTR [edx+0x38]                         
        paddw  mm5,mm3                                          
            paddw  mm6,mm2                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm1,mm2                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm1                                          
            movq   mm1,QWORD PTR [edx+0x68]                         
        movq   mm5,QWORD PTR [edx+0x30]                         
        paddw  mm5,mm1                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x38]                         
        movq   mm6,QWORD PTR [edx+0x40]                         
        paddw  mm5,mm0                                          
            paddw  mm6,mm3                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm2,mm3                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm2                                          
            movq   mm2,QWORD PTR [edx+0x70]                         
        movq   mm5,QWORD PTR [edx+0x38]                         
        paddw  mm5,mm2                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x40]                         
        movq   mm6,QWORD PTR [edx+0x48]                         
        paddw  mm5,mm1                                          
            paddw  mm6,mm0                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm3,mm0                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm3                                          
            movq   mm3,QWORD PTR [edx+0x78]                         
        movq   mm5,QWORD PTR [edx+0x40]                         
        paddw  mm5,mm3                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x48]                         
        movq   mm6,QWORD PTR [edx+0x50]                         
        paddw  mm5,mm2                                          
            paddw  mm6,mm1                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm0,mm1                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm0                                          
            movq   mm0,QWORD PTR [edx+0x80]                         
        movq   mm5,QWORD PTR [edx+0x48]                         
        paddw  mm5,mm0                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x50]                         
        movq   mm6,QWORD PTR [edx+0x58]                         
        paddw  mm5,mm3                                          
            paddw  mm6,mm2                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm1,mm2                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm1                                          
            movq   mm1,QWORD PTR [edx+0x80]                         
        movq   mm5,QWORD PTR [edx+0x50]                         
        paddw  mm5,mm1                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x58]                         
        movq   mm6,QWORD PTR [edx+0x60]                         
        paddw  mm5,mm0                                          
            paddw  mm6,mm3                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    ecx,ebx                                          
            paddw  mm2,mm3                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm2                                          
            movq   mm2,QWORD PTR [edx+0x78]                         
        movq   mm5,QWORD PTR [edx+0x58]                         
        paddw  mm5,mm2                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x60]                         
        movq   mm6,QWORD PTR [edx+0x68]                         
        paddw  mm5,mm1                                          
            paddw  mm6,mm0                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx],mm5                              
            paddw  mm3,mm0                                          
            movq   mm4,QWORD PTR [ff_pw_20]                             
            pmullw mm4,mm3                                          
            movq   mm3,QWORD PTR [edx+0x70]                         
        movq   mm5,QWORD PTR [edx+0x60]                         
        paddw  mm5,mm3                                          
            psubw  mm4,mm5                                          
            movq   mm5,QWORD PTR [edx+0x68]                         
        movq   mm6,QWORD PTR [edx+0x70]                         
        paddw  mm5,mm2                                          
            paddw  mm6,mm1                                          
            paddw  mm6,mm6                                          
            psubw  mm5,mm6                                          
            pmullw mm5,QWORD PTR [ff_pw_3]                             
            paddw  mm4,QWORD PTR [ff_pw_16]                             
            paddw  mm5,mm4                                          
            psraw  mm5,0x5                                          
            packuswb mm5,mm5                                        
            movd   DWORD PTR [ecx+eax*1],mm5                        
            add    edx,0x88                                         
            add    ecx,esi                                          
            dec    edi                                              
            jne    put_mpeg4_qpel16_v_lowpass_mmx2__204c2           
            mov    ebx,DWORD PTR [esp+0x224]                        
        mov    esi,DWORD PTR [esp+0x228]                        
        mov    edi,DWORD PTR [esp+0x22c]                        
        mov    ebp,DWORD PTR [esp+0x230]                        
        add    esp,0x234                                        
            ret                                                     

    }
}




NAKED void avg_mpeg4_qpel8_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        sub    esp,0x8                               
            mov    DWORD PTR [esp],esi                   
            mov    ecx,DWORD PTR [esp+0xc]               
        mov    DWORD PTR [esp+0x4],edi               
            mov    eax,DWORD PTR [esp+0x10]              
        mov    edx,DWORD PTR [esp+0x1c]              
        mov    esi,DWORD PTR [esp+0x18]              
        mov    edi,DWORD PTR [esp+0x14]              
        pxor   mm7,mm7                               
avg_mpeg4_qpel8_h_lowpass_mmx2__6be1:        
        movq   mm0,QWORD PTR [eax]                   
        movq   mm1,mm0                               
            movq   mm2,mm0                               
            punpcklbw mm0,mm7                            
            punpckhbw mm1,mm7                            
            pshufw mm5,mm0,0x90                          
            pshufw mm6,mm0,0x41                          
            movq   mm3,mm2                               
            movq   mm4,mm2                               
            psllq  mm2,0x8                               
            psllq  mm3,0x10                              
            psllq  mm4,0x18                              
            punpckhbw mm2,mm7                            
            punpckhbw mm3,mm7                            
            punpckhbw mm4,mm7                            
            paddw  mm5,mm3                               
            paddw  mm6,mm2                               
            paddw  mm5,mm5                               
            psubw  mm6,mm5                               
            pshufw mm5,mm0,0x6                           
            pmullw mm6,QWORD PTR [ff_pw_3]
            paddw  mm0,mm4                               
            paddw  mm5,mm1                               
            pmullw mm0,QWORD PTR [ff_pw_20]
            psubw  mm0,mm5                               
            paddw  mm6,QWORD PTR [ff_pw_16]
            paddw  mm0,mm6                               
            psraw  mm0,0x5                               
            movd   mm5,DWORD PTR [eax+0x5]               
        punpcklbw mm5,mm7                            
            pshufw mm6,mm5,0xf9                          
            paddw  mm1,mm5                               
            paddw  mm2,mm6                               
            pshufw mm6,mm5,0xbe                          
            pshufw mm5,mm5,0x6f                          
            paddw  mm3,mm6                               
            paddw  mm4,mm5                               
            paddw  mm2,mm2                               
            psubw  mm3,mm2                               
            pmullw mm1,QWORD PTR [ff_pw_20]
            pmullw mm3,QWORD PTR [ff_pw_3]                  
            psubw  mm3,mm4                               
            paddw  mm1,QWORD PTR [ff_pw_16]
            paddw  mm3,mm1                               
            psraw  mm3,0x5                               
            packuswb mm0,mm3                             
            movq   mm4,QWORD PTR [ecx]                   
        pavgb  mm0,mm4                               
            movq   QWORD PTR [ecx],mm0                   
            add    eax,esi                               
            add    ecx,edi                               
            dec    edx                                   
            jne    avg_mpeg4_qpel8_h_lowpass_mmx2__6be1  
            mov    esi,DWORD PTR [esp]                   
        mov    edi,DWORD PTR [esp+0x4]               
        add    esp,0x8                               
            ret                                          

    }
}

NAKED void avg_mpeg4_qpel8_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0xa4                                   
            mov    DWORD PTR [esp+0x94],ebx                   
            mov    ecx,DWORD PTR [esp+0xa8]                   
        mov    edx,esp                                    
            mov    DWORD PTR [esp+0x98],esi                   
            mov    ebx,DWORD PTR [esp+0xac]                   
        mov    esi,esp                                    
            mov    DWORD PTR [esp+0x9c],edi                   
            mov    eax,DWORD PTR [esp+0xb0]                   
        mov    edi,0x9                                    
            mov    DWORD PTR [esp+0xa0],ebp                   
            mov    ebp,DWORD PTR [esp+0xb4]                   
        pxor   mm7,mm7                                    
avg_mpeg4_qpel8_v_lowpass_mmx2__2a22a:            
        movq   mm0,QWORD PTR [ebx]                        
        movq   mm1,QWORD PTR [ebx]                        
        punpcklbw mm0,mm7                                 
            punpckhbw mm1,mm7                                 
            movq   QWORD PTR [esi],mm0                        
            movq   QWORD PTR [esi+0x48],mm1                   
            add    esi,0x8                                    
            add    ebx,ebp                                    
            dec    edi                                        
            jne    avg_mpeg4_qpel8_v_lowpass_mmx2__2a22a      
            imul   esi,eax,0xfffffffa                         
            mov    edi,0x2                                    
            lea    ebx,[eax+eax*1]                            
        add    esi,0x4                                    
avg_mpeg4_qpel8_v_lowpass_mmx2__2a253:            
        movq   mm0,QWORD PTR [edx]                        
        movq   mm1,QWORD PTR [edx+0x8]                    
        movq   mm2,QWORD PTR [edx+0x10]                   
        movq   mm3,QWORD PTR [edx+0x18]                   
        paddw  mm0,mm1                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm0                                    
            movq   mm0,QWORD PTR [edx+0x20]                   
        movq   mm5,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm0                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x8]                    
        movq   mm6,QWORD PTR [edx]                        
        paddw  mm5,mm3                                    
            paddw  mm6,mm2                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgb  mm5,mm7                                    
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm1,mm2                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm1                                    
            movq   mm1,QWORD PTR [edx+0x28]                   
        movq   mm5,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm1                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx]                        
        movq   mm6,QWORD PTR [edx]                        
        paddw  mm5,mm0                                    
            paddw  mm6,mm3                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgb  mm5,mm7                                    
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm2,mm3                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm2                                    
            movq   mm2,QWORD PTR [edx+0x30]                   
        movq   mm5,QWORD PTR [edx]                        
        paddw  mm5,mm2                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx]                        
        movq   mm6,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm1                                    
            paddw  mm6,mm0                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgb  mm5,mm7                                    
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm3,mm0                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm3                                    
            movq   mm3,QWORD PTR [edx+0x38]                   
        movq   mm5,QWORD PTR [edx]                        
        paddw  mm5,mm3                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x8]                    
        movq   mm6,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm2                                    
            paddw  mm6,mm1                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgb  mm5,mm7                                    
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm0,mm1                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm0                                    
            movq   mm0,QWORD PTR [edx+0x40]                   
        movq   mm5,QWORD PTR [edx+0x8]                    
        paddw  mm5,mm0                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x10]                   
        movq   mm6,QWORD PTR [edx+0x18]                   
        paddw  mm5,mm3                                    
            paddw  mm6,mm2                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgb  mm5,mm7                                    
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm1,mm2                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm1                                    
            movq   mm1,QWORD PTR [edx+0x40]                   
        movq   mm5,QWORD PTR [edx+0x10]                   
        paddw  mm5,mm1                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x18]                   
        movq   mm6,QWORD PTR [edx+0x20]                   
        paddw  mm5,mm0                                    
            paddw  mm6,mm3                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgb  mm5,mm7                                    
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    ecx,ebx                                    
            paddw  mm2,mm3                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm2                                    
            movq   mm2,QWORD PTR [edx+0x38]                   
        movq   mm5,QWORD PTR [edx+0x18]                   
        paddw  mm5,mm2                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x20]                   
        movq   mm6,QWORD PTR [edx+0x28]                   
        paddw  mm5,mm1                                    
            paddw  mm6,mm0                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx]                        
        pavgb  mm5,mm7                                    
            movd   DWORD PTR [ecx],mm5                        
            paddw  mm3,mm0                                    
            movq   mm4,QWORD PTR [ff_pw_20]                       
            pmullw mm4,mm3                                    
            movq   mm3,QWORD PTR [edx+0x30]                   
        movq   mm5,QWORD PTR [edx+0x20]                   
        paddw  mm5,mm3                                    
            psubw  mm4,mm5                                    
            movq   mm5,QWORD PTR [edx+0x28]                   
        movq   mm6,QWORD PTR [edx+0x30]                   
        paddw  mm5,mm2                                    
            paddw  mm6,mm1                                    
            paddw  mm6,mm6                                    
            psubw  mm5,mm6                                    
            pmullw mm5,QWORD PTR [ff_pw_3]                       
            paddw  mm4,QWORD PTR [ff_pw_16]                       
            paddw  mm5,mm4                                    
            psraw  mm5,0x5                                    
            packuswb mm5,mm5                                  
            movd   mm7,DWORD PTR [ecx+eax*1]                  
        pavgb  mm5,mm7                                    
            movd   DWORD PTR [ecx+eax*1],mm5                  
            add    edx,0x48                                   
            add    ecx,esi                                    
            dec    edi                                        
            jne    avg_mpeg4_qpel8_v_lowpass_mmx2__2a253      
            mov    ebx,DWORD PTR [esp+0x94]                   
        mov    esi,DWORD PTR [esp+0x98]                   
        mov    edi,DWORD PTR [esp+0x9c]                   
        mov    ebp,DWORD PTR [esp+0xa0]                   
        add    esp,0xa4                                   
            ret                                               

    }
}



NAKED void avg_mpeg4_qpel16_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        sub    esp,0x1c                                
            mov    DWORD PTR [esp+0x14],esi                
            mov    ecx,DWORD PTR [esp+0x20]                
        mov    DWORD PTR [esp+0x18],edi                
            mov    eax,DWORD PTR [esp+0x24]                
        mov    edi,DWORD PTR [esp+0x30]                
        mov    edx,DWORD PTR [esp+0x2c]                
        mov    esi,DWORD PTR [esp+0x28]                
        pxor   mm7,mm7                                 
avg_mpeg4_qpel16_h_lowpass_mmx2__6502:         
        movq   mm0,QWORD PTR [eax]                     
        movq   mm1,mm0                                 
            movq   mm2,mm0                                 
            punpcklbw mm0,mm7                              
            punpckhbw mm1,mm7                              
            pshufw mm5,mm0,0x90                            
            pshufw mm6,mm0,0x41                            
            movq   mm3,mm2                                 
            movq   mm4,mm2                                 
            psllq  mm2,0x8                                 
            psllq  mm3,0x10                                
            psllq  mm4,0x18                                
            punpckhbw mm2,mm7                              
            punpckhbw mm3,mm7                              
            punpckhbw mm4,mm7                              
            paddw  mm5,mm3                                 
            paddw  mm6,mm2                                 
            paddw  mm5,mm5                                 
            psubw  mm6,mm5                                 
            pshufw mm5,mm0,0x6                             
            pmullw mm6,QWORD PTR [ff_pw_3]
            paddw  mm0,mm4                                 
            paddw  mm5,mm1                                 
            pmullw mm0,QWORD PTR [ff_pw_20]
            psubw  mm0,mm5                                 
            paddw  mm6,QWORD PTR [ff_pw_16]
            paddw  mm0,mm6                                 
            psraw  mm0,0x5                                 
            movq   QWORD PTR [esp+0x8],mm0                 
            movq   mm0,QWORD PTR [eax+0x5]                 
        movq   mm5,mm0                                 
            movq   mm6,mm0                                 
            psrlq  mm0,0x8                                 
            psrlq  mm5,0x10                                
            punpcklbw mm0,mm7                              
            punpcklbw mm5,mm7                              
            paddw  mm2,mm0                                 
            paddw  mm3,mm5                                 
            paddw  mm2,mm2                                 
            psubw  mm3,mm2                                 
            movq   mm2,mm6                                 
            psrlq  mm6,0x18                                
            punpcklbw mm2,mm7                              
            punpcklbw mm6,mm7                              
            pmullw mm3,QWORD PTR [ff_pw_3]
            paddw  mm1,mm2                                 
            paddw  mm4,mm6                                 
            pmullw mm1,QWORD PTR [ff_pw_20]
            psubw  mm3,mm4                                 
            paddw  mm1,QWORD PTR [ff_pw_16]
            paddw  mm3,mm1                                 
            psraw  mm3,0x5                                 
            movq   mm1,QWORD PTR [esp+0x8]                 
        packuswb mm1,mm3                               
            movq   mm4,QWORD PTR [ecx]                     
        pavgb  mm1,mm4                                 
            movq   QWORD PTR [ecx],mm1                     
            movq   mm1,QWORD PTR [eax+0x9]                 
        movq   mm4,mm1                                 
            movq   mm3,mm1                                 
            psrlq  mm1,0x8                                 
            psrlq  mm4,0x10                                
            punpcklbw mm1,mm7                              
            punpcklbw mm4,mm7                              
            paddw  mm5,mm1                                 
            paddw  mm0,mm4                                 
            paddw  mm5,mm5                                 
            psubw  mm0,mm5                                 
            movq   mm5,mm3                                 
            psrlq  mm3,0x18                                
            pmullw mm0,QWORD PTR [ff_pw_3]
            punpcklbw mm3,mm7                              
            paddw  mm2,mm3                                 
            psubw  mm0,mm2                                 
            movq   mm2,mm5                                 
            punpcklbw mm2,mm7                              
            punpckhbw mm5,mm7                              
            paddw  mm6,mm2                                 
            pmullw mm6,QWORD PTR [ff_pw_20]
            paddw  mm0,QWORD PTR [ff_pw_16]
            paddw  mm0,mm6                                 
            psraw  mm0,0x5                                 
            paddw  mm3,mm5                                 
            pshufw mm6,mm5,0xf9                            
            paddw  mm6,mm4                                 
            pshufw mm4,mm5,0xbe                            
            pshufw mm5,mm5,0x6f                            
            paddw  mm4,mm1                                 
            paddw  mm5,mm2                                 
            paddw  mm6,mm6                                 
            psubw  mm4,mm6                                 
            pmullw mm3,QWORD PTR [ff_pw_20]
            pmullw mm4,QWORD PTR [ff_pw_3]
            psubw  mm3,mm5                                 
            paddw  mm4,QWORD PTR [ff_pw_16]
            paddw  mm4,mm3                                 
            psraw  mm4,0x5                                 
            packuswb mm0,mm4                               
            movq   mm4,QWORD PTR [ecx+0x8]                 
        pavgb  mm0,mm4                                 
            movq   QWORD PTR [ecx+0x8],mm0                 
            add    eax,edx                                 
            add    ecx,esi                                 
            dec    edi                                     
            jne    avg_mpeg4_qpel16_h_lowpass_mmx2__6502   
            mov    esi,DWORD PTR [esp+0x14]                
        mov    edi,DWORD PTR [esp+0x18]                
        add    esp,0x1c                                
            ret                                            

    }
}
NAKED void avg_mpeg4_qpel16_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0x234                                    
            mov    DWORD PTR [esp+0x224],ebx                    
            mov    ecx,DWORD PTR [esp+0x238]                    
        mov    edx,esp                                      
            mov    DWORD PTR [esp+0x228],esi                    
            mov    ebx,DWORD PTR [esp+0x23c]                    
        mov    esi,esp                                      
            mov    DWORD PTR [esp+0x22c],edi                    
            mov    eax,DWORD PTR [esp+0x240]                    
        mov    edi,0x11                                     
            mov    DWORD PTR [esp+0x230],ebp                    
            mov    ebp,DWORD PTR [esp+0x244]                    
        pxor   mm7,mm7                                      
avg_mpeg4_qpel16_v_lowpass_mmx2__29c2a:             
        movq   mm0,QWORD PTR [ebx]                          
        movq   mm1,QWORD PTR [ebx]                          
        movq   mm2,QWORD PTR [ebx+0x8]                      
        movq   mm3,QWORD PTR [ebx+0x8]                      
        punpcklbw mm0,mm7                                   
            punpckhbw mm1,mm7                                   
            punpcklbw mm2,mm7                                   
            punpckhbw mm3,mm7                                   
            movq   QWORD PTR [esi],mm0                          
            movq   QWORD PTR [esi+0x88],mm1                     
            movq   QWORD PTR [esi+0x110],mm2                    
            movq   QWORD PTR [esi+0x198],mm3                    
            add    esi,0x8                                      
            add    ebx,ebp                                      
            dec    edi                                          
            jne    avg_mpeg4_qpel16_v_lowpass_mmx2__29c2a       
            imul   esi,eax,0xfffffff2                           
            mov    edi,0x4                                      
            lea    ebx,[eax+eax*1]                              
        add    esi,0x4                                      
avg_mpeg4_qpel16_v_lowpass_mmx2__29c72:             
        movq   mm0,QWORD PTR [edx]                          
        movq   mm1,QWORD PTR [edx+0x8]                      
        movq   mm2,QWORD PTR [edx+0x10]                     
        movq   mm3,QWORD PTR [edx+0x18]                     
        paddw  mm0,mm1                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm0                                      
            movq   mm0,QWORD PTR [edx+0x20]                     
        movq   mm5,QWORD PTR [edx+0x10]                     
        paddw  mm5,mm0                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x8]                      
        movq   mm6,QWORD PTR [edx]                          
        paddw  mm5,mm3                                      
            paddw  mm6,mm2                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx]                          
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx],mm5                          
            paddw  mm1,mm2                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm1                                      
            movq   mm1,QWORD PTR [edx+0x28]                     
        movq   mm5,QWORD PTR [edx+0x8]                      
        paddw  mm5,mm1                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx]                          
        movq   mm6,QWORD PTR [edx]                          
        paddw  mm5,mm0                                      
            paddw  mm6,mm3                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx+eax*1]                    
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx+eax*1],mm5                    
            add    ecx,ebx                                      
            paddw  mm2,mm3                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm2                                      
            movq   mm2,QWORD PTR [edx+0x30]                     
        movq   mm5,QWORD PTR [edx]                          
        paddw  mm5,mm2                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx]                          
        movq   mm6,QWORD PTR [edx+0x8]                      
        paddw  mm5,mm1                                      
            paddw  mm6,mm0                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx]                          
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx],mm5                          
            paddw  mm3,mm0                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm3                                      
            movq   mm3,QWORD PTR [edx+0x38]                     
        movq   mm5,QWORD PTR [edx]                          
        paddw  mm5,mm3                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x8]                      
        movq   mm6,QWORD PTR [edx+0x10]                     
        paddw  mm5,mm2                                      
            paddw  mm6,mm1                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx+eax*1]                    
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx+eax*1],mm5                    
            add    ecx,ebx                                      
            paddw  mm0,mm1                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm0                                      
            movq   mm0,QWORD PTR [edx+0x40]                     
        movq   mm5,QWORD PTR [edx+0x8]                      
        paddw  mm5,mm0                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x10]                     
        movq   mm6,QWORD PTR [edx+0x18]                     
        paddw  mm5,mm3                                      
            paddw  mm6,mm2                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx]                          
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx],mm5                          
            paddw  mm1,mm2                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm1                                      
            movq   mm1,QWORD PTR [edx+0x48]                     
        movq   mm5,QWORD PTR [edx+0x10]                     
        paddw  mm5,mm1                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x18]                     
        movq   mm6,QWORD PTR [edx+0x20]                     
        paddw  mm5,mm0                                      
            paddw  mm6,mm3                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx+eax*1]                    
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx+eax*1],mm5                    
            add    ecx,ebx                                      
            paddw  mm2,mm3                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm2                                      
            movq   mm2,QWORD PTR [edx+0x50]                     
        movq   mm5,QWORD PTR [edx+0x18]                     
        paddw  mm5,mm2                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x20]                     
        movq   mm6,QWORD PTR [edx+0x28]                     
        paddw  mm5,mm1                                      
            paddw  mm6,mm0                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx]                          
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx],mm5                          
            paddw  mm3,mm0                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm3                                      
            movq   mm3,QWORD PTR [edx+0x58]                     
        movq   mm5,QWORD PTR [edx+0x20]                     
        paddw  mm5,mm3                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x28]                     
        movq   mm6,QWORD PTR [edx+0x30]                     
        paddw  mm5,mm2                                      
            paddw  mm6,mm1                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx+eax*1]                    
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx+eax*1],mm5                    
            add    ecx,ebx                                      
            paddw  mm0,mm1                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm0                                      
            movq   mm0,QWORD PTR [edx+0x60]                     
        movq   mm5,QWORD PTR [edx+0x28]                     
        paddw  mm5,mm0                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x30]                     
        movq   mm6,QWORD PTR [edx+0x38]                     
        paddw  mm5,mm3                                      
            paddw  mm6,mm2                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx]                          
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx],mm5                          
            paddw  mm1,mm2                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm1                                      
            movq   mm1,QWORD PTR [edx+0x68]                     
        movq   mm5,QWORD PTR [edx+0x30]                     
        paddw  mm5,mm1                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x38]                     
        movq   mm6,QWORD PTR [edx+0x40]                     
        paddw  mm5,mm0                                      
            paddw  mm6,mm3                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx+eax*1]                    
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx+eax*1],mm5                    
            add    ecx,ebx                                      
            paddw  mm2,mm3                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm2                                      
            movq   mm2,QWORD PTR [edx+0x70]                     
        movq   mm5,QWORD PTR [edx+0x38]                     
        paddw  mm5,mm2                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x40]                     
        movq   mm6,QWORD PTR [edx+0x48]                     
        paddw  mm5,mm1                                      
            paddw  mm6,mm0                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx]                          
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx],mm5                          
            paddw  mm3,mm0                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm3                                      
            movq   mm3,QWORD PTR [edx+0x78]                     
        movq   mm5,QWORD PTR [edx+0x40]                     
        paddw  mm5,mm3                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x48]                     
        movq   mm6,QWORD PTR [edx+0x50]                     
        paddw  mm5,mm2                                      
            paddw  mm6,mm1                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx+eax*1]                    
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx+eax*1],mm5                    
            add    ecx,ebx                                      
            paddw  mm0,mm1                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm0                                      
            movq   mm0,QWORD PTR [edx+0x80]                     
        movq   mm5,QWORD PTR [edx+0x48]                     
        paddw  mm5,mm0                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x50]                     
        movq   mm6,QWORD PTR [edx+0x58]                     
        paddw  mm5,mm3                                      
            paddw  mm6,mm2                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx]                          
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx],mm5                          
            paddw  mm1,mm2                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm1                                      
            movq   mm1,QWORD PTR [edx+0x80]                     
        movq   mm5,QWORD PTR [edx+0x50]                     
        paddw  mm5,mm1                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x58]                     
        movq   mm6,QWORD PTR [edx+0x60]                     
        paddw  mm5,mm0                                      
            paddw  mm6,mm3                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx+eax*1]                    
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx+eax*1],mm5                    
            add    ecx,ebx                                      
            paddw  mm2,mm3                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm2                                      
            movq   mm2,QWORD PTR [edx+0x78]                     
        movq   mm5,QWORD PTR [edx+0x58]                     
        paddw  mm5,mm2                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x60]                     
        movq   mm6,QWORD PTR [edx+0x68]                     
        paddw  mm5,mm1                                      
            paddw  mm6,mm0                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx]                          
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx],mm5                          
            paddw  mm3,mm0                                      
            movq   mm4,QWORD PTR [ff_pw_20]                         
            pmullw mm4,mm3                                      
            movq   mm3,QWORD PTR [edx+0x70]                     
        movq   mm5,QWORD PTR [edx+0x60]                     
        paddw  mm5,mm3                                      
            psubw  mm4,mm5                                      
            movq   mm5,QWORD PTR [edx+0x68]                     
        movq   mm6,QWORD PTR [edx+0x70]                     
        paddw  mm5,mm2                                      
            paddw  mm6,mm1                                      
            paddw  mm6,mm6                                      
            psubw  mm5,mm6                                      
            pmullw mm5,QWORD PTR [ff_pw_3]                         
            paddw  mm4,QWORD PTR [ff_pw_16]                         
            paddw  mm5,mm4                                      
            psraw  mm5,0x5                                      
            packuswb mm5,mm5                                    
            movd   mm7,DWORD PTR [ecx+eax*1]                    
        pavgb  mm5,mm7                                      
            movd   DWORD PTR [ecx+eax*1],mm5                    
            add    edx,0x88                                     
            add    ecx,esi                                      
            dec    edi                                          
            jne    avg_mpeg4_qpel16_v_lowpass_mmx2__29c72       
            mov    ebx,DWORD PTR [esp+0x224]                    
        mov    esi,DWORD PTR [esp+0x228]                    
        mov    edi,DWORD PTR [esp+0x22c]                    
        mov    ebp,DWORD PTR [esp+0x230]                    
        add    esp,0x234                                    
            ret                                                 

    }
}
NAKED void put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        sub    esp,0x8                                      
            mov    DWORD PTR [esp],esi                          
            mov    ecx,DWORD PTR [esp+0xc]                      
        mov    DWORD PTR [esp+0x4],edi                      
            mov    eax,DWORD PTR [esp+0x10]                     
        mov    edx,DWORD PTR [esp+0x1c]                     
        mov    esi,DWORD PTR [esp+0x18]                     
        mov    edi,DWORD PTR [esp+0x14]                     
        pxor   mm7,mm7                                      
put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2__7651:        
        movq   mm0,QWORD PTR [eax]                          
        movq   mm1,mm0                                      
            movq   mm2,mm0                                      
            punpcklbw mm0,mm7                                   
            punpckhbw mm1,mm7                                   
            pshufw mm5,mm0,0x90                                 
            pshufw mm6,mm0,0x41                                 
            movq   mm3,mm2                                      
            movq   mm4,mm2                                      
            psllq  mm2,0x8                                      
            psllq  mm3,0x10                                     
            psllq  mm4,0x18                                     
            punpckhbw mm2,mm7                                   
            punpckhbw mm3,mm7                                   
            punpckhbw mm4,mm7                                   
            paddw  mm5,mm3                                      
            paddw  mm6,mm2                                      
            paddw  mm5,mm5                                      
            psubw  mm6,mm5                                      
            pshufw mm5,mm0,0x6                                  
            pmullw mm6,QWORD PTR [ff_pw_3]
            paddw  mm0,mm4                                      
            paddw  mm5,mm1                                      
            pmullw mm0,QWORD PTR [ff_pw_20]
            psubw  mm0,mm5                                      
            paddw  mm6,QWORD PTR [ff_pw_15]
            paddw  mm0,mm6                                      
            psraw  mm0,0x5                                      
            movd   mm5,DWORD PTR [eax+0x5]                      
        punpcklbw mm5,mm7                                   
            pshufw mm6,mm5,0xf9                                 
            paddw  mm1,mm5                                      
            paddw  mm2,mm6                                      
            pshufw mm6,mm5,0xbe                                 
            pshufw mm5,mm5,0x6f                                 
            paddw  mm3,mm6                                      
            paddw  mm4,mm5                                      
            paddw  mm2,mm2                                      
            psubw  mm3,mm2                                      
            pmullw mm1,QWORD PTR [ff_pw_20]
            pmullw mm3,QWORD PTR [ff_pw_3]
            psubw  mm3,mm4                                      
            paddw  mm1,QWORD PTR [ff_pw_15]
            paddw  mm3,mm1                                      
            psraw  mm3,0x5                                      
            packuswb mm0,mm3                                    
            movq   QWORD PTR [ecx],mm0                          
            add    eax,esi                                      
            add    ecx,edi                                      
            dec    edx                                          
            jne    put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2__7651  
            mov    esi,DWORD PTR [esp]                          
        mov    edi,DWORD PTR [esp+0x4]                      
        add    esp,0x8                                      
            ret                                                 

    }
}

NAKED void put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0xa4                                            
            mov    DWORD PTR [esp+0x94],ebx                            
            mov    ecx,DWORD PTR [esp+0xa8]                            
        mov    edx,esp                                             
            mov    DWORD PTR [esp+0x98],esi                            
            mov    ebx,DWORD PTR [esp+0xac]                            
        mov    esi,esp                                             
            mov    DWORD PTR [esp+0x9c],edi                            
            mov    eax,DWORD PTR [esp+0xb0]                            
        mov    edi,0x9                                             
            mov    DWORD PTR [esp+0xa0],ebp                            
            mov    ebp,DWORD PTR [esp+0xb4]                            
        pxor   mm7,mm7                                             
put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2__33e0a:              
        movq   mm0,QWORD PTR [ebx]                                 
        movq   mm1,QWORD PTR [ebx]                                 
        punpcklbw mm0,mm7                                          
            punpckhbw mm1,mm7                                          
            movq   QWORD PTR [esi],mm0                                 
            movq   QWORD PTR [esi+0x48],mm1                            
            add    esi,0x8                                             
            add    ebx,ebp                                             
            dec    edi                                                 
            jne    put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2__33e0a        
            imul   esi,eax,0xfffffffa                                  
            mov    edi,0x2                                             
            lea    ebx,[eax+eax*1]                                     
        add    esi,0x4                                             
put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2__33e33:              
        movq   mm0,QWORD PTR [edx]                                 
        movq   mm1,QWORD PTR [edx+0x8]                             
        movq   mm2,QWORD PTR [edx+0x10]                            
        movq   mm3,QWORD PTR [edx+0x18]                            
        paddw  mm0,mm1                                             
            movq   mm4,QWORD PTR [ff_pw_20]                                
            pmullw mm4,mm0                                             
            movq   mm0,QWORD PTR [edx+0x20]                            
        movq   mm5,QWORD PTR [edx+0x10]                            
        paddw  mm5,mm0                                             
            psubw  mm4,mm5                                             
            movq   mm5,QWORD PTR [edx+0x8]                             
        movq   mm6,QWORD PTR [edx]                                 
        paddw  mm5,mm3                                             
            paddw  mm6,mm2                                             
            paddw  mm6,mm6                                             
            psubw  mm5,mm6                                             
            pmullw mm5,QWORD PTR [ff_pw_3]                                
            paddw  mm4,QWORD PTR [ff_pw_15]                                
            paddw  mm5,mm4                                             
            psraw  mm5,0x5                                             
            packuswb mm5,mm5                                           
            movd   DWORD PTR [ecx],mm5                                 
            paddw  mm1,mm2                                             
            movq   mm4,QWORD PTR [ff_pw_20]                                
            pmullw mm4,mm1                                             
            movq   mm1,QWORD PTR [edx+0x28]                            
        movq   mm5,QWORD PTR [edx+0x8]                             
        paddw  mm5,mm1                                             
            psubw  mm4,mm5                                             
            movq   mm5,QWORD PTR [edx]                                 
        movq   mm6,QWORD PTR [edx]                                 
        paddw  mm5,mm0                                             
            paddw  mm6,mm3                                             
            paddw  mm6,mm6                                             
            psubw  mm5,mm6                                             
            pmullw mm5,QWORD PTR [ff_pw_3]                                
            paddw  mm4,QWORD PTR [ff_pw_15]                                
            paddw  mm5,mm4                                             
            psraw  mm5,0x5                                             
            packuswb mm5,mm5                                           
            movd   DWORD PTR [ecx+eax*1],mm5                           
            add    ecx,ebx                                             
            paddw  mm2,mm3                                             
            movq   mm4,QWORD PTR [ff_pw_20]                                
            pmullw mm4,mm2                                             
            movq   mm2,QWORD PTR [edx+0x30]                            
        movq   mm5,QWORD PTR [edx]                                 
        paddw  mm5,mm2                                             
            psubw  mm4,mm5                                             
            movq   mm5,QWORD PTR [edx]                                 
        movq   mm6,QWORD PTR [edx+0x8]                             
        paddw  mm5,mm1                                             
            paddw  mm6,mm0                                             
            paddw  mm6,mm6                                             
            psubw  mm5,mm6                                             
            pmullw mm5,QWORD PTR [ff_pw_3]                                
            paddw  mm4,QWORD PTR [ff_pw_15]                                
            paddw  mm5,mm4                                             
            psraw  mm5,0x5                                             
            packuswb mm5,mm5                                           
            movd   DWORD PTR [ecx],mm5                                 
            paddw  mm3,mm0                                             
            movq   mm4,QWORD PTR [ff_pw_20]                                
            pmullw mm4,mm3                                             
            movq   mm3,QWORD PTR [edx+0x38]                            
        movq   mm5,QWORD PTR [edx]                                 
        paddw  mm5,mm3                                             
            psubw  mm4,mm5                                             
            movq   mm5,QWORD PTR [edx+0x8]                             
        movq   mm6,QWORD PTR [edx+0x10]                            
        paddw  mm5,mm2                                             
            paddw  mm6,mm1                                             
            paddw  mm6,mm6                                             
            psubw  mm5,mm6                                             
            pmullw mm5,QWORD PTR [ff_pw_3]                                
            paddw  mm4,QWORD PTR [ff_pw_15]                                
            paddw  mm5,mm4                                             
            psraw  mm5,0x5                                             
            packuswb mm5,mm5                                           
            movd   DWORD PTR [ecx+eax*1],mm5                           
            add    ecx,ebx                                             
            paddw  mm0,mm1                                             
            movq   mm4,QWORD PTR [ff_pw_20]                                
            pmullw mm4,mm0                                             
            movq   mm0,QWORD PTR [edx+0x40]                            
        movq   mm5,QWORD PTR [edx+0x8]                             
        paddw  mm5,mm0                                             
            psubw  mm4,mm5                                             
            movq   mm5,QWORD PTR [edx+0x10]                            
        movq   mm6,QWORD PTR [edx+0x18]                            
        paddw  mm5,mm3                                             
            paddw  mm6,mm2                                             
            paddw  mm6,mm6                                             
            psubw  mm5,mm6                                             
            pmullw mm5,QWORD PTR [ff_pw_3]                                
            paddw  mm4,QWORD PTR [ff_pw_15]                                
            paddw  mm5,mm4                                             
            psraw  mm5,0x5                                             
            packuswb mm5,mm5                                           
            movd   DWORD PTR [ecx],mm5                                 
            paddw  mm1,mm2                                             
            movq   mm4,QWORD PTR [ff_pw_20]                                
            pmullw mm4,mm1                                             
            movq   mm1,QWORD PTR [edx+0x40]                            
        movq   mm5,QWORD PTR [edx+0x10]                            
        paddw  mm5,mm1                                             
            psubw  mm4,mm5                                             
            movq   mm5,QWORD PTR [edx+0x18]                            
        movq   mm6,QWORD PTR [edx+0x20]                            
        paddw  mm5,mm0                                             
            paddw  mm6,mm3                                             
            paddw  mm6,mm6                                             
            psubw  mm5,mm6                                             
            pmullw mm5,QWORD PTR [ff_pw_3]                                
            paddw  mm4,QWORD PTR [ff_pw_15]                                
            paddw  mm5,mm4                                             
            psraw  mm5,0x5                                             
            packuswb mm5,mm5                                           
            movd   DWORD PTR [ecx+eax*1],mm5                           
            add    ecx,ebx                                             
            paddw  mm2,mm3                                             
            movq   mm4,QWORD PTR [ff_pw_20]                                
            pmullw mm4,mm2                                             
            movq   mm2,QWORD PTR [edx+0x38]                            
        movq   mm5,QWORD PTR [edx+0x18]                            
        paddw  mm5,mm2                                             
            psubw  mm4,mm5                                             
            movq   mm5,QWORD PTR [edx+0x20]                            
        movq   mm6,QWORD PTR [edx+0x28]                            
        paddw  mm5,mm1                                             
            paddw  mm6,mm0                                             
            paddw  mm6,mm6                                             
            psubw  mm5,mm6                                             
            pmullw mm5,QWORD PTR [ff_pw_3]                                
            paddw  mm4,QWORD PTR [ff_pw_15]                                
            paddw  mm5,mm4                                             
            psraw  mm5,0x5                                             
            packuswb mm5,mm5                                           
            movd   DWORD PTR [ecx],mm5                                 
            paddw  mm3,mm0                                             
            movq   mm4,QWORD PTR [ff_pw_20]                                
            pmullw mm4,mm3                                             
            movq   mm3,QWORD PTR [edx+0x30]                            
        movq   mm5,QWORD PTR [edx+0x20]                            
        paddw  mm5,mm3                                             
            psubw  mm4,mm5                                             
            movq   mm5,QWORD PTR [edx+0x28]                            
        movq   mm6,QWORD PTR [edx+0x30]                            
        paddw  mm5,mm2                                             
            paddw  mm6,mm1                                             
            paddw  mm6,mm6                                             
            psubw  mm5,mm6                                             
            pmullw mm5,QWORD PTR [ff_pw_3]                                
            paddw  mm4,QWORD PTR [ff_pw_15]                                
            paddw  mm5,mm4                                             
            psraw  mm5,0x5                                             
            packuswb mm5,mm5                                           
            movd   DWORD PTR [ecx+eax*1],mm5                           
            add    edx,0x48                                            
            add    ecx,esi                                             
            dec    edi                                                 
            jne    put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2__33e33        
            mov    ebx,DWORD PTR [esp+0x94]                            
        mov    esi,DWORD PTR [esp+0x98]                            
        mov    edi,DWORD PTR [esp+0x9c]                            
        mov    ebp,DWORD PTR [esp+0xa0]                            
        add    esp,0xa4                                            
            ret                                                        

    }
}

NAKED void put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride, int h)
{
    __asm {
        sub    esp,0x1c                                     
            mov    DWORD PTR [esp+0x14],esi                     
            mov    ecx,DWORD PTR [esp+0x20]                     
        mov    DWORD PTR [esp+0x18],edi                     
            mov    eax,DWORD PTR [esp+0x24]                     
        mov    edi,DWORD PTR [esp+0x30]                     
        mov    edx,DWORD PTR [esp+0x2c]                     
        mov    esi,DWORD PTR [esp+0x28]                     
        pxor   mm7,mm7                                      
put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2__6f92:       
        movq   mm0,QWORD PTR [eax]                          
        movq   mm1,mm0                                      
            movq   mm2,mm0                                      
            punpcklbw mm0,mm7                                   
            punpckhbw mm1,mm7                                   
            pshufw mm5,mm0,0x90                                 
            pshufw mm6,mm0,0x41                                 
            movq   mm3,mm2                                      
            movq   mm4,mm2                                      
            psllq  mm2,0x8                                      
            psllq  mm3,0x10                                     
            psllq  mm4,0x18                                     
            punpckhbw mm2,mm7                                   
            punpckhbw mm3,mm7                                   
            punpckhbw mm4,mm7                                   
            paddw  mm5,mm3                                      
            paddw  mm6,mm2                                      
            paddw  mm5,mm5                                      
            psubw  mm6,mm5                                      
            pshufw mm5,mm0,0x6                                  
            pmullw mm6,QWORD PTR [ff_pw_3]
            paddw  mm0,mm4                                      
            paddw  mm5,mm1                                      
            pmullw mm0,QWORD PTR [ff_pw_20]
            psubw  mm0,mm5                                      
            paddw  mm6,QWORD PTR [ff_pw_15]
            paddw  mm0,mm6                                      
            psraw  mm0,0x5                                      
            movq   QWORD PTR [esp+0x8],mm0                      
            movq   mm0,QWORD PTR [eax+0x5]                      
        movq   mm5,mm0                                      
            movq   mm6,mm0                                      
            psrlq  mm0,0x8                                      
            psrlq  mm5,0x10                                     
            punpcklbw mm0,mm7                                   
            punpcklbw mm5,mm7                                   
            paddw  mm2,mm0                                      
            paddw  mm3,mm5                                      
            paddw  mm2,mm2                                      
            psubw  mm3,mm2                                      
            movq   mm2,mm6                                      
            psrlq  mm6,0x18                                     
            punpcklbw mm2,mm7                                   
            punpcklbw mm6,mm7                                   
            pmullw mm3,QWORD PTR [ff_pw_3]
            paddw  mm1,mm2                                      
            paddw  mm4,mm6                                      
            pmullw mm1,QWORD PTR [ff_pw_20]
            psubw  mm3,mm4                                      
            paddw  mm1,QWORD PTR [ff_pw_15]
            paddw  mm3,mm1                                      
            psraw  mm3,0x5                                      
            movq   mm1,QWORD PTR [esp+0x8]                      
        packuswb mm1,mm3                                    
            movq   QWORD PTR [ecx],mm1                          
            movq   mm1,QWORD PTR [eax+0x9]                      
        movq   mm4,mm1                                      
            movq   mm3,mm1                                      
            psrlq  mm1,0x8                                      
            psrlq  mm4,0x10                                     
            punpcklbw mm1,mm7                                   
            punpcklbw mm4,mm7                                   
            paddw  mm5,mm1                                      
            paddw  mm0,mm4                                      
            paddw  mm5,mm5                                      
            psubw  mm0,mm5                                      
            movq   mm5,mm3                                      
            psrlq  mm3,0x18                                     
            pmullw mm0,QWORD PTR [ff_pw_3]
            punpcklbw mm3,mm7                                   
            paddw  mm2,mm3                                      
            psubw  mm0,mm2                                      
            movq   mm2,mm5                                      
            punpcklbw mm2,mm7                                   
            punpckhbw mm5,mm7                                   
            paddw  mm6,mm2                                      
            pmullw mm6,QWORD PTR [ff_pw_20]
            paddw  mm0,QWORD PTR [ff_pw_15]                         
            paddw  mm0,mm6                                      
            psraw  mm0,0x5                                      
            paddw  mm3,mm5                                      
            pshufw mm6,mm5,0xf9                                 
            paddw  mm6,mm4                                      
            pshufw mm4,mm5,0xbe                                 
            pshufw mm5,mm5,0x6f                                 
            paddw  mm4,mm1                                      
            paddw  mm5,mm2                                      
            paddw  mm6,mm6                                      
            psubw  mm4,mm6                                      
            pmullw mm3,QWORD PTR [ff_pw_20]
            pmullw mm4,QWORD PTR [ff_pw_3]
            psubw  mm3,mm5                                      
            paddw  mm4,QWORD PTR [ff_pw_15]                         
            paddw  mm4,mm3                                      
            psraw  mm4,0x5                                      
            packuswb mm0,mm4                                    
            movq   QWORD PTR [ecx+0x8],mm0                      
            add    eax,edx                                      
            add    ecx,esi                                      
            dec    edi                                          
            jne    put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2__6f92 
            mov    esi,DWORD PTR [esp+0x14]                     
        mov    edi,DWORD PTR [esp+0x18]                     
        add    esp,0x1c                                     
            ret                                                 

    }
}
NAKED void put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(uint8_t *dst, uint8_t *src, int dstStride, int srcStride)
{
    __asm {
        sub    esp,0x234                                         
            mov    DWORD PTR [esp+0x224],ebx                         
            mov    ecx,DWORD PTR [esp+0x238]                         
        mov    edx,esp                                           
            mov    DWORD PTR [esp+0x228],esi                         
            mov    ebx,DWORD PTR [esp+0x23c]                         
        mov    esi,esp                                           
            mov    DWORD PTR [esp+0x22c],edi                         
            mov    eax,DWORD PTR [esp+0x240]                         
        mov    edi,0x11                                          
            mov    DWORD PTR [esp+0x230],ebp                         
            mov    ebp,DWORD PTR [esp+0x244]                         
        pxor   mm7,mm7                                           
put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2__3387a:           
        movq   mm0,QWORD PTR [ebx]                               
        movq   mm1,QWORD PTR [ebx]                               
        movq   mm2,QWORD PTR [ebx+0x8]                           
        movq   mm3,QWORD PTR [ebx+0x8]                           
        punpcklbw mm0,mm7                                        
            punpckhbw mm1,mm7                                        
            punpcklbw mm2,mm7                                        
            punpckhbw mm3,mm7                                        
            movq   QWORD PTR [esi],mm0                               
            movq   QWORD PTR [esi+0x88],mm1                          
            movq   QWORD PTR [esi+0x110],mm2                         
            movq   QWORD PTR [esi+0x198],mm3                         
            add    esi,0x8                                           
            add    ebx,ebp                                           
            dec    edi                                               
            jne    put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2__3387a     
            imul   esi,eax,0xfffffff2                                
            mov    edi,0x4                                           
            lea    ebx,[eax+eax*1]                                   
        add    esi,0x4                                           
put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2__338c2:           
        movq   mm0,QWORD PTR [edx]                               
        movq   mm1,QWORD PTR [edx+0x8]                           
        movq   mm2,QWORD PTR [edx+0x10]                          
        movq   mm3,QWORD PTR [edx+0x18]                          
        paddw  mm0,mm1                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm0                                           
            movq   mm0,QWORD PTR [edx+0x20]                          
        movq   mm5,QWORD PTR [edx+0x10]                          
        paddw  mm5,mm0                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x8]                           
        movq   mm6,QWORD PTR [edx]                               
        paddw  mm5,mm3                                           
            paddw  mm6,mm2                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm1,mm2                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm1                                           
            movq   mm1,QWORD PTR [edx+0x28]                          
        movq   mm5,QWORD PTR [edx+0x8]                           
        paddw  mm5,mm1                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx]                               
        movq   mm6,QWORD PTR [edx]                               
        paddw  mm5,mm0                                           
            paddw  mm6,mm3                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm2,mm3                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm2                                           
            movq   mm2,QWORD PTR [edx+0x30]                          
        movq   mm5,QWORD PTR [edx]                               
        paddw  mm5,mm2                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx]                               
        movq   mm6,QWORD PTR [edx+0x8]                           
        paddw  mm5,mm1                                           
            paddw  mm6,mm0                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm3,mm0                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm3                                           
            movq   mm3,QWORD PTR [edx+0x38]                          
        movq   mm5,QWORD PTR [edx]                               
        paddw  mm5,mm3                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x8]                           
        movq   mm6,QWORD PTR [edx+0x10]                          
        paddw  mm5,mm2                                           
            paddw  mm6,mm1                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm0,mm1                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm0                                           
            movq   mm0,QWORD PTR [edx+0x40]                          
        movq   mm5,QWORD PTR [edx+0x8]                           
        paddw  mm5,mm0                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x10]                          
        movq   mm6,QWORD PTR [edx+0x18]                          
        paddw  mm5,mm3                                           
            paddw  mm6,mm2                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm1,mm2                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm1                                           
            movq   mm1,QWORD PTR [edx+0x48]                          
        movq   mm5,QWORD PTR [edx+0x10]                          
        paddw  mm5,mm1                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x18]                          
        movq   mm6,QWORD PTR [edx+0x20]                          
        paddw  mm5,mm0                                           
            paddw  mm6,mm3                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm2,mm3                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm2                                           
            movq   mm2,QWORD PTR [edx+0x50]                          
        movq   mm5,QWORD PTR [edx+0x18]                          
        paddw  mm5,mm2                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x20]                          
        movq   mm6,QWORD PTR [edx+0x28]                          
        paddw  mm5,mm1                                           
            paddw  mm6,mm0                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm3,mm0                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm3                                           
            movq   mm3,QWORD PTR [edx+0x58]                          
        movq   mm5,QWORD PTR [edx+0x20]                          
        paddw  mm5,mm3                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x28]                          
        movq   mm6,QWORD PTR [edx+0x30]                          
        paddw  mm5,mm2                                           
            paddw  mm6,mm1                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm0,mm1                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm0                                           
            movq   mm0,QWORD PTR [edx+0x60]                          
        movq   mm5,QWORD PTR [edx+0x28]                          
        paddw  mm5,mm0                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x30]                          
        movq   mm6,QWORD PTR [edx+0x38]                          
        paddw  mm5,mm3                                           
            paddw  mm6,mm2                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm1,mm2                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm1                                           
            movq   mm1,QWORD PTR [edx+0x68]                          
        movq   mm5,QWORD PTR [edx+0x30]                          
        paddw  mm5,mm1                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x38]                          
        movq   mm6,QWORD PTR [edx+0x40]                          
        paddw  mm5,mm0                                           
            paddw  mm6,mm3                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm2,mm3                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm2                                           
            movq   mm2,QWORD PTR [edx+0x70]                          
        movq   mm5,QWORD PTR [edx+0x38]                          
        paddw  mm5,mm2                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x40]                          
        movq   mm6,QWORD PTR [edx+0x48]                          
        paddw  mm5,mm1                                           
            paddw  mm6,mm0                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm3,mm0                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm3                                           
            movq   mm3,QWORD PTR [edx+0x78]                          
        movq   mm5,QWORD PTR [edx+0x40]                          
        paddw  mm5,mm3                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x48]                          
        movq   mm6,QWORD PTR [edx+0x50]                          
        paddw  mm5,mm2                                           
            paddw  mm6,mm1                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm0,mm1                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm0                                           
            movq   mm0,QWORD PTR [edx+0x80]                          
        movq   mm5,QWORD PTR [edx+0x48]                          
        paddw  mm5,mm0                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x50]                          
        movq   mm6,QWORD PTR [edx+0x58]                          
        paddw  mm5,mm3                                           
            paddw  mm6,mm2                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm1,mm2                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm1                                           
            movq   mm1,QWORD PTR [edx+0x80]                          
        movq   mm5,QWORD PTR [edx+0x50]                          
        paddw  mm5,mm1                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x58]                          
        movq   mm6,QWORD PTR [edx+0x60]                          
        paddw  mm5,mm0                                           
            paddw  mm6,mm3                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    ecx,ebx                                           
            paddw  mm2,mm3                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm2                                           
            movq   mm2,QWORD PTR [edx+0x78]                          
        movq   mm5,QWORD PTR [edx+0x58]                          
        paddw  mm5,mm2                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x60]                          
        movq   mm6,QWORD PTR [edx+0x68]                          
        paddw  mm5,mm1                                           
            paddw  mm6,mm0                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx],mm5                               
            paddw  mm3,mm0                                           
            movq   mm4,QWORD PTR [ff_pw_20]                              
            pmullw mm4,mm3                                           
            movq   mm3,QWORD PTR [edx+0x70]                          
        movq   mm5,QWORD PTR [edx+0x60]                          
        paddw  mm5,mm3                                           
            psubw  mm4,mm5                                           
            movq   mm5,QWORD PTR [edx+0x68]                          
        movq   mm6,QWORD PTR [edx+0x70]                          
        paddw  mm5,mm2                                           
            paddw  mm6,mm1                                           
            paddw  mm6,mm6                                           
            psubw  mm5,mm6                                           
            pmullw mm5,QWORD PTR [ff_pw_3]                              
            paddw  mm4,QWORD PTR [ff_pw_15]                              
            paddw  mm5,mm4                                           
            psraw  mm5,0x5                                           
            packuswb mm5,mm5                                         
            movd   DWORD PTR [ecx+eax*1],mm5                         
            add    edx,0x88                                          
            add    ecx,esi                                           
            dec    edi                                               
            jne    put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2__338c2     
            mov    ebx,DWORD PTR [esp+0x224]                         
        mov    esi,DWORD PTR [esp+0x228]                         
        mov    edi,DWORD PTR [esp+0x22c]                         
        mov    ebp,DWORD PTR [esp+0x230]                         
        add    esp,0x234                                         
            ret                                                      

    }
}


//void put_qpel8_mc00_3dnow (uint8_t *dst, uint8_t *src, int stride){ put_pixels8_3dnow(dst, src, stride, 8);}
 void put_qpel8_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp; 
	 put_mpeg4_qpel8_h_lowpass_3dnow(half, src, 8, stride, 8); 
	 put_pixels8_l2_3dnow(dst, src, half, stride, stride, 8);
 }
 void put_qpel8_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_mpeg4_qpel8_h_lowpass_3dnow(dst, src, stride, stride, 8);
 }
 void put_qpel8_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_h_lowpass_3dnow(half, src, 8, stride, 8);
	 put_pixels8_l2_3dnow(dst, src+1, half, stride, stride, 8);
 }
 void put_qpel8_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_v_lowpass_3dnow(half, src, 8, stride);
	 put_pixels8_l2_3dnow(dst, src, half, stride, stride, 8);
 }
 void put_qpel8_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_mpeg4_qpel8_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_qpel8_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_v_lowpass_3dnow(half, src, 8, stride);
	 put_pixels8_l2_3dnow(dst, src+stride, half, stride, stride, 8);
 }
 void put_qpel8_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8);
	 put_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 put_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8);
	 put_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8);
	 put_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8);
	 put_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8);
	 put_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 void put_qpel8_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 void put_qpel8_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 //void put_qpel16_mc00_3dnow (uint8_t *dst, uint8_t *src, int stride){ put_pixels16_3dnow(dst, src, stride, 16);}
 void put_qpel16_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_h_lowpass_3dnow(half, src, 16, stride, 16); 
	 put_pixels16_l2_3dnow(dst, src, half, stride, stride, 16);
 }
 void put_qpel16_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_mpeg4_qpel16_h_lowpass_3dnow(dst, src, stride, stride, 16);
 }
 void put_qpel16_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_h_lowpass_3dnow(half, src, 16, stride, 16);
	 put_pixels16_l2_3dnow(dst, src+1, half, stride, stride, 16);
 }
 void put_qpel16_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_v_lowpass_3dnow(half, src, 16, stride);
	 put_pixels16_l2_3dnow(dst, src, half, stride, stride, 16);
 }
 void put_qpel16_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_mpeg4_qpel16_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_qpel16_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_v_lowpass_3dnow(half, src, 16, stride); 
	 put_pixels16_l2_3dnow(dst, src+stride, half, stride, stride, 16);
 }
 void put_qpel16_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 put_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17); 
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16); 
	 put_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 put_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 put_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 put_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 put_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 void put_qpel16_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17); 
	 put_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 void put_qpel16_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 //void avg_qpel8_mc00_3dnow (uint8_t *dst, uint8_t *src, int stride){ avg_pixels8_3dnow(dst, src, stride, 8);}
 void avg_qpel8_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp; 
	 put_mpeg4_qpel8_h_lowpass_3dnow(half, src, 8, stride, 8); 
	 avg_pixels8_l2_3dnow(dst, src, half, stride, stride, 8);
 }
 void avg_qpel8_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 avg_mpeg4_qpel8_h_lowpass_3dnow(dst, src, stride, stride, 8);
 }
 void avg_qpel8_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_h_lowpass_3dnow(half, src, 8, stride, 8); 
	 avg_pixels8_l2_3dnow(dst, src+1, half, stride, stride, 8);
 }
 void avg_qpel8_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp; 
	 put_mpeg4_qpel8_v_lowpass_3dnow(half, src, 8, stride); 
	 avg_pixels8_l2_3dnow(dst, src, half, stride, stride, 8);
 }
 void avg_qpel8_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 avg_mpeg4_qpel8_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void avg_qpel8_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_v_lowpass_3dnow(half, src, 8, stride); 
	 avg_pixels8_l2_3dnow(dst, src+stride, half, stride, stride, 8);
 }
 void avg_qpel8_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 avg_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8);
	 avg_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 avg_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 avg_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 avg_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8);
	 avg_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9); 
	 avg_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 void avg_qpel8_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9); 
	 avg_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 void avg_qpel8_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 avg_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 //void avg_qpel16_mc00_3dnow (uint8_t *dst, uint8_t *src, int stride){ avg_pixels16_3dnow(dst, src, stride, 16);}
 void avg_qpel16_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_h_lowpass_3dnow(half, src, 16, stride, 16);
	 avg_pixels16_l2_3dnow(dst, src, half, stride, stride, 16);
 }
 void avg_qpel16_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 avg_mpeg4_qpel16_h_lowpass_3dnow(dst, src, stride, stride, 16);
 }
 void avg_qpel16_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_h_lowpass_3dnow(half, src, 16, stride, 16);
	 avg_pixels16_l2_3dnow(dst, src+1, half, stride, stride, 16);
 }
 void avg_qpel16_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_v_lowpass_3dnow(half, src, 16, stride);
	 avg_pixels16_l2_3dnow(dst, src, half, stride, stride, 16);
 }
 void avg_qpel16_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 avg_mpeg4_qpel16_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void avg_qpel16_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp; 
	 put_mpeg4_qpel16_v_lowpass_3dnow(half, src, 16, stride); 
	 avg_pixels16_l2_3dnow(dst, src+stride, half, stride, stride, 16);
 }
 void avg_qpel16_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16); 
	 avg_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16); 
	 avg_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 avg_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16); 
	 avg_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 avg_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 avg_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 avg_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 void avg_qpel16_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17);
	 avg_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 void avg_qpel16_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 avg_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 void put_no_rnd_qpel8_mc00_3dnow (uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_no_rnd_pixels8_3dnow(dst, src, stride, 8);
 }
 void put_no_rnd_qpel8_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(half, src, 8, stride, 8);
	 put_no_rnd_pixels8_l2_3dnow(dst, src, half, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(dst, src, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(half, src, 8, stride, 8);
	 put_no_rnd_pixels8_l2_3dnow(dst, src+1, half, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(half, src, 8, stride); 
	 put_no_rnd_pixels8_l2_3dnow(dst, src, half, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_no_rnd_qpel8_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(half, src, 8, stride); 
	 put_no_rnd_pixels8_l2_3dnow(dst, src+stride, half, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_no_rnd_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9); 
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 put_no_rnd_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_no_rnd_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 put_no_rnd_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_no_rnd_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 put_no_rnd_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_no_rnd_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 put_no_rnd_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8); 
	 put_no_rnd_pixels8_l2_3dnow(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(halfHV, halfH, 8, 8);
	 put_no_rnd_pixels8_l2_3dnow(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9); 
	 put_no_rnd_pixels8_l2_3dnow(halfH, src, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 void put_no_rnd_qpel8_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_no_rnd_pixels8_l2_3dnow(halfH, src+1, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 void put_no_rnd_qpel8_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_3dnow(halfH, src, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_3dnow(dst, halfH, stride, 8);
 }
 void put_no_rnd_qpel16_mc00_3dnow (uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_no_rnd_pixels16_3dnow(dst, src, stride, 16);
 }
 void put_no_rnd_qpel16_mc10_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(half, src, 16, stride, 16);
	 put_no_rnd_pixels16_l2_3dnow(dst, src, half, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc20_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(dst, src, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc30_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(half, src, 16, stride, 16); 
	 put_no_rnd_pixels16_l2_3dnow(dst, src+1, half, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc01_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(half, src, 16, stride);
	 put_no_rnd_pixels16_l2_3dnow(dst, src, half, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc02_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(dst, src, stride, stride);
 }
 void put_no_rnd_qpel16_mc03_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(half, src, 16, stride); 
	 put_no_rnd_pixels16_l2_3dnow(dst, src+stride, half, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc11_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_no_rnd_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16); 
	 put_no_rnd_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc31_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17); 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16); 
	 put_no_rnd_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc13_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16); 
	 put_no_rnd_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc33_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 put_no_rnd_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc21_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16); 
	 put_no_rnd_pixels16_l2_3dnow(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc23_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17); 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(halfHV, halfH, 16, 16);
	 put_no_rnd_pixels16_l2_3dnow(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc12_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_3dnow(halfH, src, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 void put_no_rnd_qpel16_mc32_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_3dnow(halfH, src+1, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 void put_no_rnd_qpel16_mc22_3dnow(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_3dnow(halfH, src, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_3dnow(dst, halfH, stride, 16);
 }
 //void put_qpel8_mc00_mmx2 (uint8_t *dst, uint8_t *src, int stride){ put_pixels8_mmx2(dst, src, stride, 8);}
 void put_qpel8_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_h_lowpass_mmx2(half, src, 8, stride, 8); 
	 put_pixels8_l2_mmx2(dst, src, half, stride, stride, 8);
 }
 void put_qpel8_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_mpeg4_qpel8_h_lowpass_mmx2(dst, src, stride, stride, 8);
 }
 void put_qpel8_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_h_lowpass_mmx2(half, src, 8, stride, 8); 
	 put_pixels8_l2_mmx2(dst, src+1, half, stride, stride, 8);
 }
 void put_qpel8_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_v_lowpass_mmx2(half, src, 8, stride);
	 put_pixels8_l2_mmx2(dst, src, half, stride, stride, 8);
 }
 void put_qpel8_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_mpeg4_qpel8_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_qpel8_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_v_lowpass_mmx2(half, src, 8, stride);
	 put_pixels8_l2_mmx2(dst, src+stride, half, stride, stride, 8);
 }
 void put_qpel8_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9); 
	 put_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 put_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8); 
	 put_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8); 
	 put_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 put_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8); 
	 put_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 put_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_qpel8_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 void put_qpel8_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 void put_qpel8_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[9];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 //void put_qpel16_mc00_mmx2 (uint8_t *dst, uint8_t *src, int stride){ put_pixels16_mmx2(dst, src, stride, 16);}
 void put_qpel16_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_h_lowpass_mmx2(half, src, 16, stride, 16);
	 put_pixels16_l2_mmx2(dst, src, half, stride, stride, 16);
 }
 void put_qpel16_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_mpeg4_qpel16_h_lowpass_mmx2(dst, src, stride, stride, 16);
 }
 void put_qpel16_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_h_lowpass_mmx2(half, src, 16, stride, 16);
	 put_pixels16_l2_mmx2(dst, src+1, half, stride, stride, 16);
 }
 void put_qpel16_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_v_lowpass_mmx2(half, src, 16, stride);
	 put_pixels16_l2_mmx2(dst, src, half, stride, stride, 16);
 }
 void put_qpel16_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 put_mpeg4_qpel16_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_qpel16_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_v_lowpass_mmx2(half, src, 16, stride); 
	 put_pixels16_l2_mmx2(dst, src+stride, half, stride, stride, 16);
 }
 void put_qpel16_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 put_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16); 
	 put_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 put_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16); 
	 put_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 put_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 put_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_qpel16_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17); 
	 put_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17); 
	 put_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }
 void put_qpel16_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }
 void put_qpel16_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17); 
	 put_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }
 //void avg_qpel8_mc00_mmx2 (uint8_t *dst, uint8_t *src, int stride){ avg_pixels8_mmx2(dst, src, stride, 8);}
 void avg_qpel8_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_h_lowpass_mmx2(half, src, 8, stride, 8);
	 avg_pixels8_l2_mmx2(dst, src, half, stride, stride, 8);
 }
 void avg_qpel8_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_mpeg4_qpel8_h_lowpass_mmx2(dst, src, stride, stride, 8);
 }
 void avg_qpel8_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_h_lowpass_mmx2(half, src, 8, stride, 8);
	 avg_pixels8_l2_mmx2(dst, src+1, half, stride, stride, 8);
 }
 void avg_qpel8_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_v_lowpass_mmx2(half, src, 8, stride); 
	 avg_pixels8_l2_mmx2(dst, src, half, stride, stride, 8);
 }
 void avg_qpel8_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_mpeg4_qpel8_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void avg_qpel8_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel8_v_lowpass_mmx2(half, src, 8, stride);
	 avg_pixels8_l2_mmx2(dst, src+stride, half, stride, stride, 8);
 }
 void avg_qpel8_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9); 
	 put_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 avg_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8); 
	 avg_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8); 
	 avg_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8); 
	 avg_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9); 
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 avg_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 avg_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void avg_qpel8_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9);
	 avg_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 void avg_qpel8_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9);
	 avg_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 void avg_qpel8_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9); 
	 avg_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 //void avg_qpel16_mc00_mmx2 (uint8_t *dst, uint8_t *src, int stride){ avg_pixels16_mmx2(dst, src, stride, 16);}
 void avg_qpel16_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_h_lowpass_mmx2(half, src, 16, stride, 16);
	 avg_pixels16_l2_mmx2(dst, src, half, stride, stride, 16);
 }
 void avg_qpel16_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_mpeg4_qpel16_h_lowpass_mmx2(dst, src, stride, stride, 16);
 }
 void avg_qpel16_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_h_lowpass_mmx2(half, src, 16, stride, 16); 
	 avg_pixels16_l2_mmx2(dst, src+1, half, stride, stride, 16);
 }
 void avg_qpel16_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_v_lowpass_mmx2(half, src, 16, stride); 
	 avg_pixels16_l2_mmx2(dst, src, half, stride, stride, 16);
 }
 void avg_qpel16_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 avg_mpeg4_qpel16_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void avg_qpel16_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp;
	 put_mpeg4_qpel16_v_lowpass_mmx2(half, src, 16, stride);
	 avg_pixels16_l2_mmx2(dst, src+stride, half, stride, stride, 16);
 }
 void avg_qpel16_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 avg_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 avg_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 avg_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17); 
	 put_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16); 
	 avg_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 avg_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16); 
	 avg_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void avg_qpel16_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17); 
	 put_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17); 
	 avg_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }
 void avg_qpel16_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17); 
	 avg_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }
 void avg_qpel16_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 avg_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }
 void put_no_rnd_qpel8_mc00_mmx2 (uint8_t *dst, uint8_t *src, int stride)
 {
	 put_no_rnd_pixels8_mmx2(dst, src, stride, 8);
 }
 void put_no_rnd_qpel8_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(half, src, 8, stride, 8);
	 put_no_rnd_pixels8_l2_mmx2(dst, src, half, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(dst, src, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(half, src, 8, stride, 8); 
	 put_no_rnd_pixels8_l2_mmx2(dst, src+1, half, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8]; 
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(half, src, 8, stride);
	 put_no_rnd_pixels8_l2_mmx2(dst, src, half, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_no_rnd_qpel8_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[8];
	 uint8_t * const half= (uint8_t*)temp;
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(half, src, 8, stride); 
	 put_no_rnd_pixels8_l2_mmx2(dst, src+stride, half, stride, stride, 8);
 }
 void put_no_rnd_qpel8_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9); 
	 put_no_rnd_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9); 
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 put_no_rnd_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 64; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_no_rnd_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8); 
	 put_no_rnd_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9); 
	 put_no_rnd_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8); 
	 put_no_rnd_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_no_rnd_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 put_no_rnd_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 put_no_rnd_pixels8_l2_mmx2(dst, halfH, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half) + 64;
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(halfHV, halfH, 8, 8);
	 put_no_rnd_pixels8_l2_mmx2(dst, halfH+8, halfHV, stride, 8, 8);
 }
 void put_no_rnd_qpel8_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9];
	 uint8_t * const halfH= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_no_rnd_pixels8_l2_mmx2(halfH, src, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 void put_no_rnd_qpel8_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[8 + 9]; 
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9);
	 put_no_rnd_pixels8_l2_mmx2(halfH, src+1, halfH, 8, stride, 9);
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 void put_no_rnd_qpel8_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[9];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel8_h_lowpass_mmx2(halfH, src, 8, stride, 9); 
	 put_no_rnd_mpeg4_qpel8_v_lowpass_mmx2(dst, halfH, stride, 8);
 }
 void put_no_rnd_qpel16_mc00_mmx2 (uint8_t *dst, uint8_t *src, int stride)
 {
	 put_no_rnd_pixels16_mmx2(dst, src, stride, 16);
 }
 void put_no_rnd_qpel16_mc10_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(half, src, 16, stride, 16);
	 put_no_rnd_pixels16_l2_mmx2(dst, src, half, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc20_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(dst, src, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc30_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32];
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(half, src, 16, stride, 16);
	 put_no_rnd_pixels16_l2_mmx2(dst, src+1, half, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc01_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp; 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(half, src, 16, stride);
	 put_no_rnd_pixels16_l2_mmx2(dst, src, half, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc02_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(dst, src, stride, stride);
 }
 void put_no_rnd_qpel16_mc03_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t temp[32]; 
	 uint8_t * const half= (uint8_t*)temp;
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(half, src, 16, stride); 
	 put_no_rnd_pixels16_l2_mmx2(dst, src+stride, half, stride, stride, 16);
 }
 void put_no_rnd_qpel16_mc11_mmx2(uint8_t *dst, uint8_t *src, int stride)
 {
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 put_no_rnd_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc31_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17); 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16); 
	 put_no_rnd_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc13_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17); 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16); 
	 put_no_rnd_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc33_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2]; 
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17); 
	 put_no_rnd_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 put_no_rnd_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc21_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256;
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16); 
	 put_no_rnd_pixels16_l2_mmx2(dst, halfH, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc23_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[16*2 + 17*2];
	 uint8_t * const halfH= ((uint8_t*)half) + 256; 
	 uint8_t * const halfHV= ((uint8_t*)half); 
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17); 
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(halfHV, halfH, 16, 16);
	 put_no_rnd_pixels16_l2_mmx2(dst, halfH+16, halfHV, stride, 16, 16);
 }
 void put_no_rnd_qpel16_mc12_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_no_rnd_pixels16_l2_mmx2(halfH, src, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }
 void put_no_rnd_qpel16_mc32_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17); 
	 put_no_rnd_pixels16_l2_mmx2(halfH, src+1, halfH, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }
 void put_no_rnd_qpel16_mc22_mmx2(uint8_t *dst, uint8_t *src, int stride)
 { 
	 uint64_t half[17*2];
	 uint8_t * const halfH= ((uint8_t*)half);
	 put_no_rnd_mpeg4_qpel16_h_lowpass_mmx2(halfH, src, 16, stride, 17);
	 put_no_rnd_mpeg4_qpel16_v_lowpass_mmx2(dst, halfH, stride, 16);
 }