#include "commontypes.h"
#include "dsputil_mmx.h"

//extern unsigned char ff_pb_3_1[16];
//extern unsigned char ff_pb_1[16];
//extern unsigned char ff_pb_3[16];

void __declspec(naked) h264_loop_filter_strength_mmx2( int16_t bS[2][4][4], uint8_t nnz[40], int8_t ref[2][40], int16_t mv[2][40][2],   
                                                      int bidir, int edges, int step, int mask_mv0, int mask_mv1, int field )
{
    __asm{	
        push   ebp                                          
            push   edi                                          
            push   esi                                          
            push   ebx                                          
            sub    esp,0x4                                      
            mov    edx,DWORD PTR [esp+0x18]                     
        mov    ecx,DWORD PTR [esp+0x1c]                     
        mov    ebp,DWORD PTR [esp+0x24]                     
        movq   mm7,QWORD PTR [ff_pb_1]                         
        movq   mm6,QWORD PTR [ff_pb_3]                         
        mov    eax,DWORD PTR [esp+0x3c]                     
        test   eax,eax                                      
            je     h264_loop_filter_strength_mmx2_30            
            movq   mm6,[ff_pb_3_1]                              

h264_loop_filter_strength_mmx2_30:                

        movq   mm5,mm6                                      
            paddb  mm5,mm5                                      
            mov    ebx,DWORD PTR [esp+0x2c]                     
        mov    edi,DWORD PTR [esp+0x30]                     
        mov    esi,DWORD PTR [esp+0x38]                     
        shl    ebx,0x3                                      

            shl    edi,0x3                                      
            shl    esi,0x3                                      
            test   ebx,ebx                                      
            jle    h264_loop_filter_strength_mmx2_700           
            xor    eax,eax                                      
            cmp    DWORD PTR [esp+0x28],0x0                     
            jne    h264_loop_filter_strength_mmx2_280           
            mov    DWORD PTR [esp],ebx                          
            mov    ebx,DWORD PTR [esp+0x20]                     
        nop                                                 
h264_loop_filter_strength_mmx2_68:                
        pxor   mm0,mm0                                      
            test   eax,esi                                      
            jne    h264_loop_filter_strength_mmx2_9c            
            movd   mm0,DWORD PTR [ebx+eax*1+0xc]                
        psubb  mm0,QWORD PTR [ebx+eax*1+0x4]                
        movq   mm1,QWORD PTR [ebp+eax*4+0x30]               
        movq   mm2,QWORD PTR [ebp+eax*4+0x38]               
        psubw  mm1,QWORD PTR [ebp+eax*4+0x10]               
        psubw  mm2,QWORD PTR [ebp+eax*4+0x18]               
        packsswb mm1,mm2                                    
            paddb  mm1,mm6                                      
            psubusb mm1,mm5                                     
            packsswb mm1,mm1                                    
            por    mm0,mm1                                      

h264_loop_filter_strength_mmx2_9c:                
        movd   mm1,DWORD PTR [ecx+eax*1+0xc]                
        por    mm1,QWORD PTR [ecx+eax*1+0x4]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+eax*1+0x20],mm1               
            add    eax,edi                                      
            cmp    DWORD PTR [esp],eax                          
            jg     h264_loop_filter_strength_mmx2_68            
            mov    eax,DWORD PTR [esp+0x34]                     
        shl    eax,0x3                                      
h264_loop_filter_strength_mmx2_CC:                
        mov    esi,DWORD PTR [esp+0x20]                     
        xor    ebx,ebx                                      
            movd   mm0,DWORD PTR [esi+ebx*1+0xc]                
        psubb  mm0,QWORD PTR [esi+ebx*1+0xb]                
        movq   mm1,QWORD PTR [ebp+ebx*4+0x30]               
        movq   mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm1,QWORD PTR [ebp+ebx*4+0x2c]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x34]               
        packsswb mm1,mm2                                    
            paddb  mm1,mm6                                      
            psubusb mm1,mm5                                     
            packsswb mm1,mm1                                    
            por    mm0,mm1                                      
            movd   mm1,DWORD PTR [ecx+ebx*1+0xc]                
        por    mm1,QWORD PTR [ecx+ebx*1+0xb]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+ebx*1],mm1                    
            test   al,0x8                                       
            jne    h264_loop_filter_strength_mmx2_153           
            mov    bl,0x8                                       
            movd   mm0,DWORD PTR [esi+ebx*1+0xc]                
        psubb  mm0,QWORD PTR [esi+ebx*1+0xb]                
        movq   mm1,QWORD PTR [ebp+ebx*4+0x30]               
        movq   mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm1,QWORD PTR [ebp+ebx*4+0x2c]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x34]               
        packsswb mm1,mm2                                    
            paddb  mm1,mm6                                      
            psubusb mm1,mm5                                     
            packsswb mm1,mm1                                    
            por    mm0,mm1                                      
h264_loop_filter_strength_mmx2_153:               
        mov    ebx,0x8                                      
            movd   mm1,DWORD PTR [ecx+ebx*1+0xc]                
        por    mm1,QWORD PTR [ecx+ebx*1+0xb]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+ebx*1],mm1                    
            test   al,0x10                                      
            jne    h264_loop_filter_strength_mmx2_1b0           
            mov    bl,0x10                                      
            mov    esi,DWORD PTR [esp+0x20]                     
        movd   mm0,DWORD PTR [esi+ebx*1+0xc]                
        psubb  mm0,QWORD PTR [esi+ebx*1+0xb]                
        movq   mm1,QWORD PTR [ebp+ebx*4+0x30]               
        movq   mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm1,QWORD PTR [ebp+ebx*4+0x2c]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x34]               
        packsswb mm1,mm2                                    
            paddb  mm1,mm6                                      
            psubusb mm1,mm5                                     
            packsswb mm1,mm1                                    
            por    mm0,mm1                                      
h264_loop_filter_strength_mmx2_1b0:               
        mov    ebx,0x10                                     
            movd   mm1,DWORD PTR [ecx+ebx*1+0xc]                
        por    mm1,QWORD PTR [ecx+ebx*1+0xb]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+ebx*1],mm1                    
            test   al,0x18                                      
            jne    h264_loop_filter_strength_mmx2_210           
            mov    eax,0x18                                     
            mov    ebx,DWORD PTR [esp+0x20]                     
        movd   mm0,DWORD PTR [ebx+eax*1+0xc]                
        psubb  mm0,QWORD PTR [ebx+eax*1+0xb]                
        movq   mm1,QWORD PTR [ebp+eax*4+0x30]               
        movq   mm2,QWORD PTR [ebp+eax*4+0x38]               
        psubw  mm1,QWORD PTR [ebp+eax*4+0x2c]               
        psubw  mm2,QWORD PTR [ebp+eax*4+0x34]               
        packsswb mm1,mm2                                    
            paddb  mm1,mm6                                      
            psubusb mm1,mm5                                     
            packsswb mm1,mm1                                    
            por    mm0,mm1                                      
h264_loop_filter_strength_mmx2_210:               
        mov    eax,0x18                                     
            movd   mm1,DWORD PTR [ecx+eax*1+0xc]                
        por    mm1,QWORD PTR [ecx+eax*1+0xb]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+eax*1],mm1                    

            movq   mm0,QWORD PTR [edx]                          
        movq   mm1,QWORD PTR [edx+0x8]                      
        movq   mm2,QWORD PTR [edx+0x10]                     
        movq   mm3,QWORD PTR [edx+0x18]                     
        movq   mm4,mm0                                      
            punpcklwd mm0,mm1                                   
            punpckhwd mm4,mm1                                   
            movq   mm1,mm2                                      
            punpcklwd mm2,mm3                                   
            punpckhwd mm1,mm3                                   
            movq   mm3,mm0                                      
            punpckldq mm0,mm2                                   
            punpckhdq mm3,mm2                                   
            movq   mm2,mm4                                      
            punpckldq mm4,mm1                                   
            punpckhdq mm2,mm1                                   
            movq   QWORD PTR [edx],mm0                          
            movq   QWORD PTR [edx+0x8],mm3                      
            movq   QWORD PTR [edx+0x10],mm4                     
            movq   QWORD PTR [edx+0x18],mm2                     
            add    esp,0x4                                      
            pop    ebx                                          
            pop    esi                                          
            pop    edi                                          
            pop    ebp                                          
            ret                                                 
h264_loop_filter_strength_mmx2_280:               
        mov    DWORD PTR [esp],ebx                          
            mov    ebx,DWORD PTR [esp+0x20]                     
        nop                                                 
h264_loop_filter_strength_mmx2_288:               
        pxor   mm0,mm0                                      
            test   eax,esi                                      
            jne    h264_loop_filter_strength_mmx2_34b           
            movd   mm2,DWORD PTR [ebx+eax*1+0x4]                
        punpckldq mm2,DWORD PTR [ebx+eax*1+0x2c]            
        pshufw mm0,QWORD PTR [ebx+eax*1+0xc],0x44           
            pshufw mm1,QWORD PTR [ebx+eax*1+0x34],0x44          
            pshufw mm3,mm2,0x4e                                 
            psubb  mm0,mm2                                      
            psubb  mm1,mm3                                      
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+eax*4+0x10]               
        movq   mm2,QWORD PTR [ebp+eax*4+0x18]               
        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+eax*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+eax*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+eax*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+eax*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+eax*4+0xb0]               

        movq   mm2,QWORD PTR [ebp+eax*4+0xb8]               

        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+eax*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+eax*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+eax*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+eax*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            pshufw mm1,mm1,0x4e                                 
            por    mm0,mm1                                      
            pshufw mm1,mm0,0x4e                                 
            pminub mm0,mm1                                      
h264_loop_filter_strength_mmx2_34b:               
        movd   mm1,DWORD PTR [ecx+eax*1+0xc]                
        por    mm1,QWORD PTR [ecx+eax*1+0x4]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+eax*1+0x20],mm1               
            add    eax,edi                                      
            cmp    DWORD PTR [esp],eax                          
            jg     h264_loop_filter_strength_mmx2_288           
            mov    eax,DWORD PTR [esp+0x34]                     
        shl    eax,0x3                                      
h264_loop_filter_strength_mmx2_37f:               
        mov    esi,DWORD PTR [esp+0x20]                     
        xor    ebx,ebx                                      
            movd   mm2,DWORD PTR [esi+ebx*1+0xb]                
        punpckldq mm2,DWORD PTR [esi+ebx*1+0x33]            
        pshufw mm0,QWORD PTR [esi+ebx*1+0xc],0x44           
            pshufw mm1,QWORD PTR [esi+ebx*1+0x34],0x44          
            pshufw mm3,mm2,0x4e                                 
            psubb  mm0,mm2                                      
            psubb  mm1,mm3                                      
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+ebx*4+0x2c]               
        movq   mm2,QWORD PTR [ebp+ebx*4+0x34]               
        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+ebx*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+ebx*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+ebx*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+ebx*4+0xcc]               

        movq   mm2,QWORD PTR [ebp+ebx*4+0xd4]               

        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+ebx*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+ebx*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+ebx*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            pshufw mm1,mm1,0x4e                                 
            por    mm0,mm1                                      
            pshufw mm1,mm0,0x4e                                 
            pminub mm0,mm1                                      
            movd   mm1,DWORD PTR [ecx+ebx*1+0xc]                
        por    mm1,QWORD PTR [ecx+ebx*1+0xb]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+ebx*1],mm1                    
            test   al,0x8                                       
            jne    h264_loop_filter_strength_mmx2_520           
            mov    bl,0x8                                       
            movd   mm2,DWORD PTR [esi+ebx*1+0xb]                
        punpckldq mm2,DWORD PTR [esi+ebx*1+0x33]            
        pshufw mm0,QWORD PTR [esi+ebx*1+0xc],0x44           
            pshufw mm1,QWORD PTR [esi+ebx*1+0x34],0x44          
            pshufw mm3,mm2,0x4e                                 
            psubb  mm0,mm2                                      
            psubb  mm1,mm3                                      
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+ebx*4+0x2c]               
        movq   mm2,QWORD PTR [ebp+ebx*4+0x34]               
        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+ebx*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+ebx*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+ebx*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+ebx*4+0xcc]               

        movq   mm2,QWORD PTR [ebp+ebx*4+0xd4]               

        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+ebx*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+ebx*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+ebx*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            pshufw mm1,mm1,0x4e                                 
            por    mm0,mm1                                      
            pshufw mm1,mm0,0x4e                                 
            pminub mm0,mm1                                      
h264_loop_filter_strength_mmx2_520:               
        mov    ebx,0x8                                      
            movd   mm1,DWORD PTR [ecx+ebx*1+0xc]                
        por    mm1,QWORD PTR [ecx+ebx*1+0xb]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+ebx*1],mm1                    
            test   al,0x10                                      
            jne    h264_loop_filter_strength_mmx2_60c           
            mov    bl,0x10                                      
            mov    esi,DWORD PTR [esp+0x20]                     
        movd   mm2,DWORD PTR [esi+ebx*1+0xb]                
        punpckldq mm2,DWORD PTR [esi+ebx*1+0x33]            
        pshufw mm0,QWORD PTR [esi+ebx*1+0xc],0x44           
            pshufw mm1,QWORD PTR [esi+ebx*1+0x34],0x44          
            pshufw mm3,mm2,0x4e                                 
            psubb  mm0,mm2                                      
            psubb  mm1,mm3                                      
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+ebx*4+0x2c]               
        movq   mm2,QWORD PTR [ebp+ebx*4+0x34]               
        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+ebx*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+ebx*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+ebx*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+ebx*4+0xcc]               

        movq   mm2,QWORD PTR [ebp+ebx*4+0xd4]               

        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+ebx*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+ebx*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+ebx*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+ebx*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            pshufw mm1,mm1,0x4e                                 
            por    mm0,mm1                                      
            pshufw mm1,mm0,0x4e                                 
            pminub mm0,mm1                                      
h264_loop_filter_strength_mmx2_60c:               
        mov    ebx,0x10                                     
            movd   mm1,DWORD PTR [ecx+ebx*1+0xc]                
        por    mm1,QWORD PTR [ecx+ebx*1+0xb]                
        pminub mm1,mm7                                      
            pminub mm0,mm7                                      
            psllw  mm1,0x1                                      
            pxor   mm2,mm2                                      
            pmaxub mm1,mm0                                      
            punpcklbw mm1,mm2                                   
            movq   QWORD PTR [edx+ebx*1],mm1                    
            test   al,0x18                                      
            jne    h264_loop_filter_strength_mmx2_210           
            mov    eax,0x18                                     
            mov    ebx,DWORD PTR [esp+0x20]                     
        movd   mm2,DWORD PTR [ebx+eax*1+0xb]                
        punpckldq mm2,DWORD PTR [ebx+eax*1+0x33]            
        pshufw mm0,QWORD PTR [ebx+eax*1+0xc],0x44           
            pshufw mm1,QWORD PTR [ebx+eax*1+0x34],0x44          
            pshufw mm3,mm2,0x4e                                 
            psubb  mm0,mm2                                      
            psubb  mm1,mm3                                      
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+eax*4+0x2c]               
        movq   mm2,QWORD PTR [ebp+eax*4+0x34]               
        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+eax*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+eax*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+eax*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+eax*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            por    mm0,mm1                                      
            movq   mm1,QWORD PTR [ebp+eax*4+0xcc]               

        movq   mm2,QWORD PTR [ebp+eax*4+0xd4]               

        movq   mm3,mm1                                      
            movq   mm4,mm2                                      
            psubw  mm1,QWORD PTR [ebp+eax*4+0x30]               
        psubw  mm2,QWORD PTR [ebp+eax*4+0x38]               
        psubw  mm3,QWORD PTR [ebp+eax*4+0xd0]               

        psubw  mm4,QWORD PTR [ebp+eax*4+0xd8]               

        packsswb mm1,mm2                                    
            packsswb mm3,mm4                                    
            paddb  mm1,mm6                                      
            paddb  mm3,mm6                                      
            psubusb mm1,mm5                                     
            psubusb mm3,mm5                                     
            packsswb mm1,mm3                                    
            pshufw mm1,mm1,0x4e                                 
            por    mm0,mm1                                      
            pshufw mm1,mm0,0x4e                                 
            pminub mm0,mm1                                      
            jmp    h264_loop_filter_strength_mmx2_210           
h264_loop_filter_strength_mmx2_700:               
        mov    eax,DWORD PTR [esp+0x34]                     
        mov    ebx,DWORD PTR [esp+0x28]                     
        shl    eax,0x3                                      
            test   ebx,ebx                                      
            jne    h264_loop_filter_strength_mmx2_37f           
            jmp    h264_loop_filter_strength_mmx2_CC            
    }
}