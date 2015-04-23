#define NAKED __declspec(naked)
#include "dsputil_mmx.h"

//extern __declspec(align(16)) char tm_shuf[16];// = {0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80};
extern __declspec(align(16)) short pw_ff00[8];// = {0xff00};
extern __declspec(align(16)) short pw_0to7[8];// =   {0x0000,  0x0001,  0x0002,  0x0003,  0x0004,  0x0005,  0x0006,  0x0007};
extern __declspec(align(16)) short pw_1to8[8];// =   {0x0001,  0x0002,  0x0003,  0x0004,  0x0005,  0x0006,  0x0007,  0x0008};
extern __declspec(align(16)) short pw_m8tom1[8];// = {0xfff8,  0xfff9,  0xfffa,  0xfffb,  0xfffc,  0xfffd,  0xfffe,  0xffff};
extern __declspec(align(16)) short pw_m4to4[8];// =  { -4, -3, -2, -1,  1,  2,  3,  4};
extern __declspec(align(16)) char  plane_shuf[16];// = { -8, -7, -6, -5, -4, -3, -2, -1, 1,  2,  3,  4,  5,  6,  7,  8};
extern __declspec(align(16)) char  plane8_shuf[16];// = { -4, -3, -2, -1,  0,  0,  0,  0, 1,  2,  3,  4,  0,  0,  0,  0};

//extern xmm_reg ff_pb_1;

#undef PTR
NAKED void ff_pred16x16_vertical_mmx (uint8_t *src, int stride)
{
	__asm {
		mov    eax,DWORD PTR [esp+0x4]            
		mov    ecx,DWORD PTR [esp+0x8]            
		sub    eax,ecx                           
		mov    edx,0x8                           
		movq   mm0,QWORD PTR [eax]               
		movq   mm1,QWORD PTR [eax+0x8]

ff_pred16x16_vertical_mmx_flagi:
		movq   QWORD PTR [eax+ecx*1],mm0
		movq   QWORD PTR [eax+ecx*1+0x8],mm1
		movq   QWORD PTR [eax+ecx*2],mm0
		movq   QWORD PTR [eax+ecx*2+0x8],mm1
		lea    eax,[eax+ecx*2]
		dec    edx            
		jg     ff_pred16x16_vertical_mmx_flagi
		repz ret
	}
}

NAKED void ff_pred16x16_vertical_sse (uint8_t *src, int stride)
{
	__asm {
		mov    eax,DWORD PTR [esp+0x4]            
		mov    ecx,DWORD PTR [esp+0x8]

		sub    eax,ecx                            

		mov    edx,0x4                            

		movaps xmm0,XMMWORD PTR [eax]

ff_pred16x16_vertical_sse_flagi:
		movaps XMMWORD PTR [eax+ecx*1],xmm0       

		movaps XMMWORD PTR [eax+ecx*2],xmm0       

		lea    eax,[eax+ecx*2]                    

		movaps XMMWORD PTR [eax+ecx*1],xmm0       

		movaps XMMWORD PTR [eax+ecx*2],xmm0       

		lea    eax,[eax+ecx*2]                    

		dec    edx                                

		jg     ff_pred16x16_vertical_sse_flagi

		repz ret             

	}
}

NAKED void ff_pred16x16_horizontal_mmx(uint8_t *src, int stride)
{
    __asm {mov    eax,DWORD PTR [esp+0x4]         
    mov    ecx,DWORD PTR [esp+0x8]         
    mov    edx,0x8

ff_pred16x16_horizontal_mmx__6d:       
    movd   mm0,DWORD PTR [eax-0x4]         
    movd   mm1,DWORD PTR [eax+ecx*1-0x4]   
    punpcklbw mm0,mm0                      
        punpcklbw mm1,mm1                      
        punpckhwd mm0,mm0                      
        punpckhwd mm1,mm1                      
        punpckhdq mm0,mm0                      
        punpckhdq mm1,mm1                      
        movq   QWORD PTR [eax+0x8],mm0         
        movq   QWORD PTR [eax+ecx*1+0x8],mm1   
        movq   QWORD PTR [eax],mm0             
        movq   QWORD PTR [eax+ecx*1],mm1       
        lea    eax,[eax+ecx*2]                 
    dec    edx                             
        jg     ff_pred16x16_horizontal_mmx__6d 
        repz ret
	}
}

NAKED void ff_pred16x16_horizontal_mmxext(uint8_t *src, int stride)
{
	__asm{
        mov    eax,DWORD PTR [esp+0x4]            
        mov    ecx,DWORD PTR [esp+0x8]            
        mov    edx,0x8                            

ff_pred16x16_horizontal_mmxext_loop:      
        movd   mm0,DWORD PTR [eax-0x4]            
        movd   mm1,DWORD PTR [eax+ecx*1-0x4]      
        punpcklbw mm0,mm0                         
            punpcklbw mm1,mm1                         
            pshufw mm0,mm0,0xff                       
            pshufw mm1,mm1,0xff                       
            movq   QWORD PTR [eax+0x8],mm0            
            movq   QWORD PTR [eax+ecx*1+0x8],mm1      
            movq   QWORD PTR [eax],mm0                
            movq   QWORD PTR [eax+ecx*1],mm1          
            lea    eax,[eax+ecx*2]                    
        dec    edx                                
            jg     ff_pred16x16_horizontal_mmxext_loop
            repz ret                                  

    }
}


NAKED void ff_pred16x16_horizontal_ssse3 (uint8_t *src, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]
		mov ecx, [esp + 0 + 4 + 1*4]

		mov edx, 8                  
			movdqa xmm2, [ff_pb_3]

ff_pred16x16_horizontal_ssse3_loop_i:                       
		movd xmm0, [eax+ecx*0-4]    
		movd xmm1, [eax+ecx*1-4]    


		pshufb xmm0, xmm2           

			pshufb xmm1, xmm2           

			movdqa [eax+ecx*0], xmm0    
			movdqa [eax+ecx*1], xmm1    
			lea eax, [eax+ecx*2]        
		dec edx                     
			jg ff_pred16x16_horizontal_ssse3_loop_i                    
			rep ret
	}
}

NAKED void ff_pred16x16_dc_mmxext (uint8_t *src, int stride)
{
	__asm {
        push   ebx                           
            push   esi                           
            push   edi                           
            push   ebp                           
            mov    eax,DWORD PTR [esp+0x14]      
        mov    ecx,DWORD PTR [esp+0x18]      
        mov    esi,eax                       
            sub    eax,ecx                       
            pxor   mm0,mm0                       
            pxor   mm1,mm1                       
            psadbw mm0,QWORD PTR [eax]           
        psadbw mm1,QWORD PTR [eax+0x8]       
        dec    eax                           
            movzx  edi,BYTE PTR [eax+ecx*1]      
        paddw  mm0,mm1                       
            movd   ebp,mm0                       
            lea    eax,[eax+ecx*2]               
        movzx  edx,BYTE PTR [eax]            
        movzx  ebx,BYTE PTR [eax+ecx*1]      
        add    edi,edx                       
            add    ebp,ebx                       
            lea    eax,[eax+ecx*2]               
        movzx  edx,BYTE PTR [eax]            
        movzx  ebx,BYTE PTR [eax+ecx*1]      
        add    edi,edx                       
            add    ebp,ebx                       
            lea    eax,[eax+ecx*2]               
        movzx  edx,BYTE PTR [eax]            
        movzx  ebx,BYTE PTR [eax+ecx*1]      
        add    edi,edx                       
            add    ebp,ebx                       
            lea    eax,[eax+ecx*2]               
        movzx  edx,BYTE PTR [eax]            
        movzx  ebx,BYTE PTR [eax+ecx*1]      
        add    edi,edx                       
            add    ebp,ebx                       
            lea    eax,[eax+ecx*2]               
        movzx  edx,BYTE PTR [eax]            
        movzx  ebx,BYTE PTR [eax+ecx*1]      
        add    edi,edx                       
            add    ebp,ebx                       
            lea    eax,[eax+ecx*2]               
        movzx  edx,BYTE PTR [eax]            
        movzx  ebx,BYTE PTR [eax+ecx*1]      
        add    edi,edx                       
            add    ebp,ebx                       
            lea    eax,[eax+ecx*2]               
        movzx  edx,BYTE PTR [eax]            
        movzx  ebx,BYTE PTR [eax+ecx*1]      
        add    edi,edx                       
            add    ebp,ebx                       
            lea    eax,[eax+ecx*2]               
        movzx  edx,BYTE PTR [eax]            
        add    edi,ebp                       
            lea    edx,[edx+edi*1+0x10]          
        shr    edx,0x5                       
            movd   mm0,edx                       
            punpcklbw mm0,mm0                    
            pshufw mm0,mm0,0x0                   
            mov    ebx,0x8                       

ff_pred16x16_dc_mmxext_loop:         
        movq   QWORD PTR [esi],mm0           
            movq   QWORD PTR [esi+0x8],mm0       
            movq   QWORD PTR [esi+ecx*1],mm0     
            movq   QWORD PTR [esi+ecx*1+0x8],mm0 
            lea    esi,[esi+ecx*2]               
        dec    ebx                           
            jg     ff_pred16x16_dc_mmxext_loop   
            pop    ebp                           
            pop    edi                           
            pop    esi                           
            pop    ebx                           
            ret                                  

	}
}

NAKED void ff_pred16x16_dc_sse2 (uint8_t *src, int stride)
{
	__asm {
        push   ebx                          
            push   esi                          
            push   edi                          
            push   ebp                          
            mov    eax,DWORD PTR [esp+0x14]     
        mov    ecx,DWORD PTR [esp+0x18]     
        mov    esi,eax                      
            sub    eax,ecx                      
            pxor   mm0,mm0                      
            pxor   mm1,mm1                      
            psadbw mm0,QWORD PTR [eax]          
        psadbw mm1,QWORD PTR [eax+0x8]      
        dec    eax                          
            movzx  edi,BYTE PTR [eax+ecx*1]     
        paddw  mm0,mm1                      
            movd   ebp,mm0                      
            lea    eax,[eax+ecx*2]              
        movzx  edx,BYTE PTR [eax]           
        movzx  ebx,BYTE PTR [eax+ecx*1]     
        add    edi,edx                      
            add    ebp,ebx                      
            lea    eax,[eax+ecx*2]              
        movzx  edx,BYTE PTR [eax]           
        movzx  ebx,BYTE PTR [eax+ecx*1]     
        add    edi,edx                      
            add    ebp,ebx                      
            lea    eax,[eax+ecx*2]              
        movzx  edx,BYTE PTR [eax]           
        movzx  ebx,BYTE PTR [eax+ecx*1]     
        add    edi,edx                      
            add    ebp,ebx                      
            lea    eax,[eax+ecx*2]              
        movzx  edx,BYTE PTR [eax]           
        movzx  ebx,BYTE PTR [eax+ecx*1]     
        add    edi,edx                      
            add    ebp,ebx                      
            lea    eax,[eax+ecx*2]              
        movzx  edx,BYTE PTR [eax]           
        movzx  ebx,BYTE PTR [eax+ecx*1]     
        add    edi,edx                      
            add    ebp,ebx                      
            lea    eax,[eax+ecx*2]              
        movzx  edx,BYTE PTR [eax]           
        movzx  ebx,BYTE PTR [eax+ecx*1]     
        add    edi,edx                      
            add    ebp,ebx                      
            lea    eax,[eax+ecx*2]              
        movzx  edx,BYTE PTR [eax]           
        movzx  ebx,BYTE PTR [eax+ecx*1]     
        add    edi,edx                      
            add    ebp,ebx                      
            lea    eax,[eax+ecx*2]              
        movzx  edx,BYTE PTR [eax]           
        add    edi,ebp                      
            lea    edx,[edx+edi*1+0x10]         
        shr    edx,0x5                      
            movd   xmm0,edx                     
            punpcklbw xmm0,xmm0                 
            pshuflw xmm0,xmm0,0x0               
            punpcklqdq xmm0,xmm0                
            mov    ebx,0x4                      

ff_pred16x16_dc_sse2_loop:          
        movdqa XMMWORD PTR [esi],xmm0       
            movdqa XMMWORD PTR [esi+ecx*1],xmm0 
            lea    esi,[esi+ecx*2]              
        movdqa XMMWORD PTR [esi],xmm0       
            movdqa XMMWORD PTR [esi+ecx*1],xmm0 
            lea    esi,[esi+ecx*2]              
        dec    ebx                          
            jg     ff_pred16x16_dc_sse2_loop    
            pop    ebp                          
            pop    edi                          
            pop    esi                          
            pop    ebx                          
            ret

	}
}

NAKED void ff_pred16x16_dc_ssse3 (uint8_t *src, int stride)
{
	__asm{
		push ebx                        
		push esi                        
		push edi                        
		push ebp                        
		mov eax, [esp + 16 + 4 + 0*4]   
		mov ecx, [esp + 16 + 4 + 1*4]   

		mov esi, eax                    
		sub eax, ecx                    

		pxor mm0, mm0                   

		pxor mm1, mm1                   

		psadbw mm0, [eax+0]             

		psadbw mm1, [eax+8]             
		dec eax                         
		movzx edi, byte ptr [eax+ecx*1]     

		paddw mm0, mm1                  
		movd ebp, mm0                   
		lea eax, [eax+ecx*2]            
		movzx edx, byte ptr [eax+ecx*0]     
		movzx ebx, byte ptr [eax+ecx*1]     
		add edi, edx                    
		add ebp, ebx                    
		lea eax, [eax+ecx*2]            
		movzx edx, byte ptr [eax+ecx*0]     
		movzx ebx, byte ptr [eax+ecx*1]     
		add edi, edx                    
		add ebp, ebx                    
		lea eax, [eax+ecx*2]            
		movzx edx, byte ptr [eax+ecx*0]     
		movzx ebx, byte ptr [eax+ecx*1]     
		add edi, edx                    
		add ebp, ebx                    
		lea eax, [eax+ecx*2]            
		movzx edx, byte ptr [eax+ecx*0]     
		movzx ebx, byte ptr [eax+ecx*1]     
		add edi, edx                    
		add ebp, ebx                    
		lea eax, [eax+ecx*2]            
		movzx edx, byte ptr [eax+ecx*0]     
		movzx ebx, byte ptr [eax+ecx*1]     
		add edi, edx                    
		add ebp, ebx                    
		lea eax, [eax+ecx*2]            
		movzx edx, byte ptr [eax+ecx*0]     
		movzx ebx, byte ptr [eax+ecx*1]     
		add edi, edx                    
		add ebp, ebx                    
		lea eax, [eax+ecx*2]            
		movzx edx, byte ptr [eax+ecx*0]     
		movzx ebx, byte ptr [eax+ecx*1]     
		add edi, edx                    
		add ebp, ebx                    
		lea eax, [eax+ecx*2]            
		movzx edx, byte ptr [eax+ecx*0]     
		add edi, ebp                    
		lea edx, [edx+edi+16]           
		shr edx, 5                      

		pxor xmm1, xmm1                 
		movd xmm0, edx                  

		pshufb xmm0, xmm1               

		mov ebx, 4                      
		ff_pred16x16_dc_sse2__loop_i:                           
		movdqa [esi+ecx*0], xmm0        
		movdqa [esi+ecx*1], xmm0        
		lea esi, [esi+ecx*2]            
		movdqa [esi+ecx*0], xmm0        
		movdqa [esi+ecx*1], xmm0        
		lea esi, [esi+ecx*2]            
		dec ebx                         
		jg ff_pred16x16_dc_sse2__loop_i                        
		pop ebp                         
		pop edi                         
		pop esi                         
		pop ebx                         
		ret                             
	}
}


NAKED void ff_pred16x16_plane_h264_mmx (uint8_t *src, int stride)
{
	__asm {
		push ebx                            
		push esi                            
		push edi                            
		push ebp                            
		mov eax, [esp + 16 + 4 + 0*4]       
		mov ecx, [esp + 16 + 4 + 1*4]       

		mov edx, ecx                        
		neg ecx                             

		movd mm0, [eax+ecx -1]              

		pxor mm4, mm4                       
		movd mm1, [eax+ecx +3 ]             
		movd mm2, [eax+ecx +8 ]             
		movd mm3, [eax+ecx +12]             

		punpcklbw mm0, mm4                  

		punpcklbw mm1, mm4                  

		punpcklbw mm2, mm4                  

		punpcklbw mm3, mm4                  

		pmullw mm0, [pw_m8tom1 ]            

		pmullw mm1, [pw_m8tom1+8]           

		pmullw mm2, [pw_1to8 ]              

		pmullw mm3, [pw_1to8 +8]            

		paddw mm0, mm2                      

		paddw mm1, mm3                      

		paddw mm0, mm1                      
		movq mm1, mm0                       

		psrlq mm1, 32                       

		paddw mm0, mm1                      
		movq mm1, mm0                       

		psrlq mm1, 16                       

		paddw mm0, mm1                      

		lea esi, [eax+edx*8-1]              
		lea ebx, [eax+edx*4-1]              
		add esi, edx                        


		movzx eax, byte ptr [ebx+edx*2 ]        
		movzx edi, byte ptr [esi+ecx ]          
		sub edi, eax                        

		movzx eax, byte ptr [ebx+edx ]          
		movzx ebp, byte ptr [esi ]              
		sub ebp, eax                        
		lea edi, [edi+ebp*2]                

		movzx eax, byte ptr [ebx+ecx ]          
		movzx ebp, byte ptr [esi+edx*2 ]        
		sub ebp, eax                        
		lea edi, [edi+ebp*4]                

		movzx eax, byte ptr [ebx ]              
		movzx ebp, byte ptr [esi+edx ]          
		sub ebp, eax                        
		lea edi, [edi+ebp*4]                
		sub edi, ebp                        

		lea eax, [ebx+ecx*4]                
		lea ebx, [esi+edx*4]                

		movzx esi, byte ptr [eax+edx ]          
		movzx ebp, byte ptr [ebx ]              
		sub ebp, esi                        
		lea edi, [edi+ebp*4]                
		lea edi, [edi+ebp*2]                

		movzx esi, byte ptr [eax ]              
		movzx ebp, byte ptr [ebx +edx ]         
		sub ebp, esi                        
		lea edi, [edi+ebp*8]                
		sub edi, ebp                        

		movzx esi, byte ptr [eax+ecx ]          
		movzx ebp, byte ptr [ebx +edx*2]        
		sub ebp, esi                        
		lea edi, [edi+ebp*8]                

		movzx esi, byte ptr [eax+edx*2]         
		movzx ebp, byte ptr [ebx +ecx ]         
		sub ebp, esi                        
		lea edi, [edi+ebp*4]                
		add edi, ebp                        

		mov eax, [esp + 16 + 4]             

		lea edi, [edi*4 + edi +32]                 
		sar edi, 6                          

		movzx esi, byte ptr [eax+ecx +15]       
		movzx ebx, byte ptr [ebx+edx*2 ]        
		lea ebx, [ebx+esi+1]                
		shl ebx, 4                          

		movd ecx, mm0                       
		movsx ecx, cx                       
		lea ecx, [ecx*4 + ecx + 32]                 
		sar ecx, 6                          
		movd mm0, ecx                       

		add ecx, edi                        
		add ebx, ecx                        
		shl ecx, 3                          
		sub ebx, ecx                        

		movd mm1, edi                       
		movd mm3, ebx                       

		punpcklwd mm0, mm0                  

		punpcklwd mm1, mm1                  

		punpcklwd mm3, mm3                  

		punpckldq mm0, mm0                  

		punpckldq mm1, mm1                  

		punpckldq mm3, mm3                  
		movq mm2, mm0                       
		movq mm5, mm0                       

		pmullw mm0, [pw_0to7]               

		psllw mm5, 3                        

		psllw mm2, 2                        
		movq mm6, mm5                       

		paddw mm6, mm2                      

		paddw mm0, mm3                      

		paddw mm2, mm0                      

		paddw mm5, mm0                      

		paddw mm6, mm0                      

		mov esi, 8                          
		ff_pred16x16_plane_h264_mmx__loop_i:                                
		movq mm3, mm0                       
		movq mm4, mm2                       

		psraw mm3, 5                        

		psraw mm4, 5                        

		packuswb mm3, mm4
		movq [eax], mm3                     
		movq mm3, mm5                       
		movq mm4, mm6                       

		psraw mm3, 5                        

		psraw mm4, 5                        

		packuswb mm3, mm4                   
		movq [eax+8], mm3                   

		paddw mm0, mm1                      

		paddw mm2, mm1                      

		paddw mm5, mm1                      

		paddw mm6, mm1                      

		movq mm3, mm0                       
		movq mm4, mm2                       

		psraw mm3, 5                        

		psraw mm4, 5                        

		packuswb mm3, mm4                   
		movq [eax+edx], mm3                 
		movq mm3, mm5                       
		movq mm4, mm6                       

		psraw mm3, 5                        

		psraw mm4, 5                        

		packuswb mm3, mm4                   
		movq [eax+edx+8], mm3               

		paddw mm0, mm1                      

		paddw mm2, mm1                      

		paddw mm5, mm1                      

		paddw mm6, mm1                      

		lea eax, [eax+edx*2]                
		dec esi                             
		jg ff_pred16x16_plane_h264_mmx__loop_i                            
		pop ebp                             
		pop edi                             
		pop esi                             
		pop ebx                             
		ret
	}
}

NAKED void ff_pred16x16_plane_h264_mmx2 (uint8_t *src, int stride)
{
	__asm {
		push ebx                           
			push esi                           
			push edi                           
			push ebp                           
			mov eax, [esp + 16 + 4 + 0*4]      
		mov ecx, [esp + 16 + 4 + 1*4]      

		mov edx, ecx                       
			neg ecx                            

			movd mm0, [eax+ecx -1]             

		pxor mm4, mm4                      
			movd mm1, [eax+ecx +3 ]            
		movd mm2, [eax+ecx +8 ]            
		movd mm3, [eax+ecx +12]            

		punpcklbw mm0, mm4                 

			punpcklbw mm1, mm4                 

			punpcklbw mm2, mm4                 

			punpcklbw mm3, mm4                 

			pmullw mm0, [pw_m8tom1 ]           

		pmullw mm1, [pw_m8tom1+8]          

		pmullw mm2, [pw_1to8 ]             

		pmullw mm3, [pw_1to8 +8]           

		paddw mm0, mm2                     

			paddw mm1, mm3                     

			paddw mm0, mm1                     
			pshufw mm1, mm0, 0xE               

			paddw mm0, mm1                     
			pshufw mm1, mm0, 0x1               

			paddw mm0, mm1                     

			lea esi, [eax+edx*8-1]             
		lea ebx, [eax+edx*4-1]             
		add esi, edx                       


			movzx eax, byte ptr [ebx+edx*2 ]       
		movzx edi, byte ptr [esi+ecx ]         
		sub edi, eax                       

			movzx eax, byte ptr [ebx+edx ]         
		movzx ebp, byte ptr [esi ]             
		sub ebp, eax                       
			lea edi, [edi+ebp*2]               

		movzx eax, byte ptr [ebx+ecx ]         
		movzx ebp, byte ptr [esi+edx*2 ]       
		sub ebp, eax                       
			lea edi, [edi+ebp*4]               

		movzx eax, byte ptr [ebx ]             
		movzx ebp, byte ptr [esi+edx ]         
		sub ebp, eax                       
			lea edi, [edi+ebp*4]               
		sub edi, ebp                       

			lea eax, [ebx+ecx*4]               
		lea ebx, [esi+edx*4]               

		movzx esi, byte ptr [eax+edx ]         
		movzx ebp, byte ptr [ebx ]             
		sub ebp, esi                       
			lea edi, [edi+ebp*4]               
		lea edi, [edi+ebp*2]               

		movzx esi, byte ptr [eax ]             
		movzx ebp, byte ptr [ebx +edx ]        
		sub ebp, esi                       
			lea edi, [edi+ebp*8]               
		sub edi, ebp                       

			movzx esi, byte ptr [eax+ecx ]         
		movzx ebp, byte ptr [ebx +edx*2]       
		sub ebp, esi                       
			lea edi, [edi+ebp*8]               

		movzx esi, byte ptr [eax+edx*2]        
		movzx ebp, byte ptr [ebx +ecx ]        
		sub ebp, esi                       
			lea edi, [edi+ebp*4]               
		add edi, ebp                       

			mov eax, [esp + 16 + 4]            

		lea edi, [edi*4 + edi + 32]                
		sar edi, 6                         

			movzx esi, byte ptr [eax+ecx +15]      
		movzx ebx, byte ptr [ebx+edx*2 ]       
		lea ebx, [ebx+esi+1]               
		shl ebx, 4                         

			movd ecx, mm0                      
			movsx ecx, cx                      
			lea ecx, [ecx*4 + ecx + 32]                
		sar ecx, 6                         
			movd mm0, ecx                      

			add ecx, edi                       
			add ebx, ecx                       
			shl ecx, 3                         
			sub ebx, ecx                       

			movd mm1, edi                      
			movd mm3, ebx                      
			pshufw mm0, mm0, 0x0               
			pshufw mm1, mm1, 0x0               
			pshufw mm3, mm3, 0x0               
			movq mm2, mm0                      
			movq mm5, mm0                      

			pmullw mm0, [pw_0to7]              

		psllw mm5, 3                       

			psllw mm2, 2                       
			movq mm6, mm5                      

			paddw mm6, mm2                     

			paddw mm0, mm3                     

			paddw mm2, mm0                     

			paddw mm5, mm0                     

			paddw mm6, mm0                     

			mov esi, 8                         
ff_pred16x16_plane_h264_mmx2__loop_i:                               
		movq mm3, mm0                      
			movq mm4, mm2                      

			psraw mm3, 5                       

			psraw mm4, 5                       

			packuswb mm3, mm4                  
			movq [eax], mm3                    
			movq mm3, mm5                      
			movq mm4, mm6                      

			psraw mm3, 5                       

			psraw mm4, 5                       

			packuswb mm3, mm4                  
			movq [eax+8], mm3                  

			paddw mm0, mm1                     

			paddw mm2, mm1                     

			paddw mm5, mm1                     

			paddw mm6, mm1                     

			movq mm3, mm0                      
			movq mm4, mm2                      

			psraw mm3, 5                       

			psraw mm4, 5                       

			packuswb mm3, mm4                  
			movq [eax+edx], mm3                
			movq mm3, mm5                      
			movq mm4, mm6                      

			psraw mm3, 5                       

			psraw mm4, 5                       

			packuswb mm3, mm4                  
			movq [eax+edx+8], mm3              

			paddw mm0, mm1                     

			paddw mm2, mm1                     

			paddw mm5, mm1                     

			paddw mm6, mm1                     

			lea eax, [eax+edx*2]               
		dec esi                            
			jg ff_pred16x16_plane_h264_mmx2__loop_i                           
			pop ebp                            
			pop edi                            
			pop esi                            
			pop ebx                            
			ret                                

	}
}

NAKED void ff_pred16x16_plane_h264_sse2 (uint8_t *src, int stride)
{
	__asm {
		push ebx                        
			push esi                        
			push edi                        
			push ebp                        
			mov eax, [esp + 16 + 4 + 0*4]   
		mov ecx, [esp + 16 + 4 + 1*4]   

		mov edx, ecx                    
			neg ecx                         

			movq xmm0, qword ptr [eax+ecx -1]         

		pxor xmm2, xmm2                 
			movq xmm1, qword ptr [eax+ecx +8]         

		punpcklbw xmm0, xmm2            

			punpcklbw xmm1, xmm2            

			pmullw xmm0, [pw_m8tom1]        

		pmullw xmm1, [pw_1to8]          

		paddw xmm0, xmm1                

			movhlps xmm1, xmm0              

			paddw xmm0, xmm1                
			pshuflw xmm1, xmm0, 0xE         

			paddw xmm0, xmm1                
			pshuflw xmm1, xmm0, 0x1         

			paddw xmm0, xmm1                

			lea esi, [eax+edx*8-1]          
		lea ebx, [eax+edx*4-1]          
		add esi, edx                    


			movzx eax, byte ptr [ebx+edx*2 ]    
		movzx edi, byte ptr [esi+ecx ]      
		sub edi, eax                    

			movzx eax, byte ptr [ebx+edx ]      
		movzx ebp, byte ptr [esi ]          
		sub ebp, eax                    
			lea edi, [edi+ebp*2]            

		movzx eax, byte ptr [ebx+ecx ]      
		movzx ebp, byte ptr [esi+edx*2 ]    
		sub ebp, eax                    
			lea edi, [edi+ebp*4]            

		movzx eax, byte ptr [ebx ]          
		movzx ebp, byte ptr [esi+edx ]      
		sub ebp, eax                    
			lea edi, [edi+ebp*4]            
		sub edi, ebp                    

			lea eax, [ebx+ecx*4]            
		lea ebx, [esi+edx*4]            

		movzx esi, byte ptr [eax+edx ]      
		movzx ebp, byte ptr [ebx ]          
		sub ebp, esi                    
			lea edi, [edi+ebp*4]            
		lea edi, [edi+ebp*2]            

		movzx esi, byte ptr [eax ]          
		movzx ebp, byte ptr [ebx +edx ]     
		sub ebp, esi                    
			lea edi, [edi+ebp*8]            
		sub edi, ebp                    

			movzx esi, byte ptr [eax+ecx ]      
		movzx ebp, byte ptr [ebx +edx*2]    
		sub ebp, esi                    
			lea edi, [edi+ebp*8]            

		movzx esi, byte ptr [eax+edx*2]     
		movzx ebp, byte ptr [ebx +ecx ]     
		sub ebp, esi                    
			lea edi, [edi+ebp*4]            
		add edi, ebp                    

			mov eax, [esp + 16 + 4]         

		lea edi, [edi*4 + edi + 32]             
		sar edi, 6                      

			movzx esi, byte ptr [eax+ecx +15]   
		movzx ebx, byte ptr [ebx+edx*2 ]    
		lea ebx, [ebx+esi+1]            
		shl ebx, 4                      

			movd ecx, xmm0                  
			movsx ecx, cx                   
			lea ecx, [ecx*4 + ecx + 32]             
		sar ecx, 6                      
			movd xmm0, ecx                  

			add ecx, edi                    
			add ebx, ecx                    
			shl ecx, 3                      
			sub ebx, ecx                    

			movd xmm1, edi                  
			movd xmm3, ebx                  
			pshuflw xmm0, xmm0, 0x0         
			pshuflw xmm1, xmm1, 0x0         
			pshuflw xmm3, xmm3, 0x0         

			punpcklqdq xmm0, xmm0           

			punpcklqdq xmm1, xmm1           

			punpcklqdq xmm3, xmm3           
			movdqa xmm2, xmm0               

			pmullw xmm0, [pw_0to7]          

		psllw xmm2, 3                   

			paddw xmm0, xmm3                

			paddw xmm2, xmm0                

			mov esi, 8                      
ff_pred16x16_plane_h264_sse2__loop_i:                            
		movdqa xmm3, xmm0               
			movdqa xmm4, xmm2               

			psraw xmm3, 5                   

			psraw xmm4, 5                   

			packuswb xmm3, xmm4             
			movdqa [eax], xmm3              

			paddw xmm0, xmm1                

			paddw xmm2, xmm1                

			movdqa xmm3, xmm0               
			movdqa xmm4, xmm2               

			psraw xmm3, 5                   

			psraw xmm4, 5                   

			packuswb xmm3, xmm4             
			movdqa [eax+edx], xmm3          

			paddw xmm0, xmm1                

			paddw xmm2, xmm1                

			lea eax, [eax+edx*2]            
		dec esi                         
			jg ff_pred16x16_plane_h264_sse2__loop_i                        
			pop ebp                         
			pop edi                         
			pop esi                         
			pop ebx                         
			ret                             

	}
}

NAKED void ff_pred16x16_plane_h264_ssse3 (uint8_t *src, int stride)
{
	__asm {
		push ebx                           
			push esi                           
			push edi                           
			push ebp                           
			mov eax, [esp + 16 + 4 + 0*4]      
		mov ecx, [esp + 16 + 4 + 1*4]      

		mov edx, ecx                       
			neg ecx                            

			movq xmm0, qword ptr[eax+ecx -1]            
		movhps xmm0, [eax+ecx +8]          

		pmaddubsw xmm0, [plane_shuf]     

		movhlps xmm1, xmm0                 

			paddw xmm0, xmm1                   
			pshuflw xmm1, xmm0, 0xE            

			paddw xmm0, xmm1                   
			pshuflw xmm1, xmm0, 0x1            

			paddw xmm0, xmm1                   

			lea esi, [eax+edx*8-1]             
		lea ebx, [eax+edx*4-1]             
		add esi, edx                       


			movzx eax, byte ptr [ebx+edx*2 ]       
		movzx edi, byte ptr [esi+ecx ]         
		sub edi, eax                       

			movzx eax, byte ptr [ebx+edx ]         
		movzx ebp, byte ptr [esi ]             
		sub ebp, eax                       
			lea edi, [edi+ebp*2]               

		movzx eax, byte ptr [ebx+ecx ]         
		movzx ebp, byte ptr [esi+edx*2 ]       
		sub ebp, eax                       
			lea edi, [edi+ebp*4]               

		movzx eax, byte ptr [ebx ]             
		movzx ebp, byte ptr [esi+edx ]         
		sub ebp, eax                       
			lea edi, [edi+ebp*4]               
		sub edi, ebp                       

			lea eax, [ebx+ecx*4]               
		lea ebx, [esi+edx*4]               

		movzx esi, byte ptr [eax+edx ]         
		movzx ebp, byte ptr [ebx ]             
		sub ebp, esi                       
			lea edi, [edi+ebp*4]               
		lea edi, [edi+ebp*2]               

		movzx esi, byte ptr [eax ]             
		movzx ebp, byte ptr [ebx +edx ]        
		sub ebp, esi                       
			lea edi, [edi+ebp*8]               
		sub edi, ebp                       

			movzx esi, byte ptr [eax+ecx ]         
		movzx ebp, byte ptr [ebx +edx*2]       
		sub ebp, esi                       
			lea edi, [edi+ebp*8]               

		movzx esi, byte ptr [eax+edx*2]        
		movzx ebp, byte ptr [ebx +ecx ]        
		sub ebp, esi                       
			lea edi, [edi+ebp*4]               
		add edi, ebp                       

			mov eax, [esp + 16 + 4]            

		lea edi, [edi*4 + edi + 32]                
		sar edi, 6                         

			movzx esi, byte ptr [eax+ecx +15]      
		movzx ebx, byte ptr [ebx+edx*2 ]       
		lea ebx, [ebx+esi+1]               
		shl ebx, 4                         

			movd ecx, xmm0                     
			movsx ecx, cx                      
			lea ecx, [ecx*4 + ecx + 32]                
		sar ecx, 6                         
			movd xmm0, ecx                     

			add ecx, edi                       
			add ebx, ecx                       
			shl ecx, 3                         
			sub ebx, ecx                       

			movd xmm1, edi                     
			movd xmm3, ebx                     
			pshuflw xmm0, xmm0, 0x0            
			pshuflw xmm1, xmm1, 0x0            
			pshuflw xmm3, xmm3, 0x0            

			punpcklqdq xmm0, xmm0              

			punpcklqdq xmm1, xmm1              

			punpcklqdq xmm3, xmm3              
			movdqa xmm2, xmm0                  

			pmullw xmm0, [pw_0to7]             

		psllw xmm2, 3                      

			paddw xmm0, xmm3                   

			paddw xmm2, xmm0                   

			mov esi, 8                         
ff_pred16x16_plane_h264_ssse3__loop_i:                               
		movdqa xmm3, xmm0                  
			movdqa xmm4, xmm2                  

			psraw xmm3, 5                      

			psraw xmm4, 5                      

			packuswb xmm3, xmm4                
			movdqa [eax], xmm3                 

			paddw xmm0, xmm1                   

			paddw xmm2, xmm1                   

			movdqa xmm3, xmm0                  
			movdqa xmm4, xmm2                  

			psraw xmm3, 5                      

			psraw xmm4, 5                      

			packuswb xmm3, xmm4                
			movdqa [eax+edx], xmm3             

			paddw xmm0, xmm1                   

			paddw xmm2, xmm1                   

			lea eax, [eax+edx*2]               
		dec esi                            
			jg ff_pred16x16_plane_h264_ssse3__loop_i                           
			pop ebp                            
			pop edi                            
			pop esi                            
			pop ebx                            
			ret                                

	}
}


NAKED void ff_pred8x8_plane_mmx (uint8_t *src, int stride)
{
	__asm {
		push ebx                                    
			push esi                                    
			push edi                                    
			push ebp                                    
			mov eax, [esp + 16 + 4 + 0*4]               
		mov ecx, [esp + 16 + 4 + 1*4]               

		mov edx, ecx                                
			neg ecx                                     

			movd mm0, [eax+ecx -1]                      

		pxor mm2, mm2                               
			movd mm1, [eax+ecx +4 ]                     

		punpcklbw mm0, mm2                          

			punpcklbw mm1, mm2                          

			pmullw mm0, [pw_m4to4]                      

		pmullw mm1, [pw_m4to4+8]                    

		paddw mm0, mm1                              

			movq mm1, mm0                               

			psrlq mm1, 32                               

			paddw mm0, mm1                              

			movq mm1, mm0                               

			psrlq mm1, 16                               

			paddw mm0, mm1                              

			lea esi, [eax+edx*4-1]                      
		lea ebx, [eax -1]                           
		add esi, edx                                


			movzx eax, byte ptr [ebx+edx*2 ]                
		movzx edi, byte ptr [esi+ecx ]                  
		sub edi, eax                                

			movzx eax, byte ptr [ebx ]                      
		movzx ebp, byte ptr [esi+edx ]                  
		sub ebp, eax                                
			lea edi, [edi+ebp*4]                        
		sub edi, ebp                                

			movzx eax, byte ptr [ebx+ecx ]                  
		movzx ebp, byte ptr [esi+edx*2 ]                
		sub ebp, eax                                
			lea edi, [edi+ebp*4]                        

		movzx eax, byte ptr [ebx+edx ]                  
		movzx ebp, byte ptr [esi ]                      
		sub ebp, eax                                
			lea ebp, [edi+ebp*2]                        

		lea edi, [ebp*8 + ebp + 16]                         
		lea edi, [edi+ebp*8]                        
		sar edi, 5                                  

			mov eax, [esp + 16 + 4]                     

		movzx ebx, byte ptr [esi+edx*2 ]                
		movzx esi, byte ptr [eax+ecx +7]                
		lea ebx, [ebx+esi+1]                        
		shl ebx, 4                                  
			movd ecx, mm0                               
			movsx ecx, cx                               
			imul ecx, 17                                
			add ecx, 16                                 
			sar ecx, 5                                  
			movd mm0, ecx                               
			add ecx, edi                                
			sub ebx, ecx                                
			add ecx, ecx                                
			sub ebx, ecx                                

			movd mm1, edi                               
			movd mm3, ebx                               

			punpcklwd mm0, mm0                          

			punpcklwd mm1, mm1                          

			punpcklwd mm3, mm3                          

			punpckldq mm0, mm0                          

			punpckldq mm1, mm1                          

			punpckldq mm3, mm3                          
			movq mm2, mm0                               

			pmullw mm0, [pw_0to7]                       

		paddw mm0, mm3                              

			psllw mm2, 2                                

			paddw mm2, mm0                              

			mov esi, 4
ff_pred8x8_plane_mmx__loop_i:                                        
		movq mm3, mm0                               
			movq mm4, mm2                               

			paddw mm0, mm1                              

			paddw mm2, mm1                              

			psraw mm3, 5                                

			psraw mm4, 5                                
			movq mm5, mm0                               
			movq mm6, mm2                               

			paddw mm0, mm1                              

			paddw mm2, mm1                              

			psraw mm5, 5                                

			psraw mm6, 5                                

			packuswb mm3, mm4                           

			packuswb mm5, mm6                           
			movq [eax], mm3                             
			movq [eax+edx], mm5                         

			lea eax, [eax+edx*2]                        
		dec esi                                     
			jg ff_pred8x8_plane_mmx__loop_i                                    
			pop ebp                                     
			pop edi                                     
			pop esi                                     
			pop ebx                                     
			ret                                         

	}
}

NAKED void ff_pred8x8_plane_mmx2 (uint8_t *src, int stride)
{
	__asm {
		push ebx                                    
			push esi                                    
			push edi                                    
			push ebp                                    
			mov eax, [esp + 16 + 4 + 0*4]               
		mov ecx, [esp + 16 + 4 + 1*4]               

		mov edx, ecx                                
			neg ecx                                     

			movd mm0, [eax+ecx -1]                      

		pxor mm2, mm2                               
			movd mm1, [eax+ecx +4 ]                     

		punpcklbw mm0, mm2                          

			punpcklbw mm1, mm2                          

			pmullw mm0, [pw_m4to4]                      

		pmullw mm1, [pw_m4to4+8]                    

		paddw mm0, mm1                              

			pshufw mm1, mm0, 0xE                        

			paddw mm0, mm1                              

			pshufw mm1, mm0, 0x1                        

			paddw mm0, mm1                              

			lea esi, [eax+edx*4-1]                      
		lea ebx, [eax -1]                           
		add esi, edx                                


			movzx eax, byte ptr [ebx+edx*2 ]                
		movzx edi, byte ptr [esi+ecx ]                  
		sub edi, eax                                

			movzx eax, byte ptr [ebx ]                      
		movzx ebp, byte ptr [esi+edx ]                  
		sub ebp, eax                                
			lea edi, [edi+ebp*4]                        
		sub edi, ebp                                

			movzx eax, byte ptr [ebx+ecx ]                  
		movzx ebp, byte ptr [esi+edx*2 ]                
		sub ebp, eax                                
			lea edi, [edi+ebp*4]                        

		movzx eax, byte ptr [ebx+edx ]                  
		movzx ebp, byte ptr [esi ]                      
		sub ebp, eax                                
			lea ebp, [edi+ebp*2]                        

		lea edi, [ebp*8 + ebp + 16]                         
		lea edi, [edi+ebp*8]                        
		sar edi, 5                                  

			mov eax, [esp + 16 + 4]                     

		movzx ebx, byte ptr [esi+edx*2 ]                
		movzx esi, byte ptr [eax+ecx +7]                
		lea ebx, [ebx+esi+1]                        
		shl ebx, 4                                  
			movd ecx, mm0                               
			movsx ecx, cx                               
			imul ecx, 17                                
			add ecx, 16                                 
			sar ecx, 5                                  
			movd mm0, ecx                               
			add ecx, edi                                
			sub ebx, ecx                                
			add ecx, ecx                                
			sub ebx, ecx                                

			movd mm1, edi                               
			movd mm3, ebx                               
			pshufw mm0, mm0, 0x0                        
			pshufw mm1, mm1, 0x0                        
			pshufw mm3, mm3, 0x0                        
			movq mm2, mm0                               

			pmullw mm0, [pw_0to7]                       

		paddw mm0, mm3                              

			psllw mm2, 2                                

			paddw mm2, mm0                              

			mov esi, 4
ff_pred8x8_plane_mmx2__loop_i:                                        
		movq mm3, mm0                               
			movq mm4, mm2                               

			paddw mm0, mm1                              

			paddw mm2, mm1                              

			psraw mm3, 5                                

			psraw mm4, 5                                
			movq mm5, mm0                               
			movq mm6, mm2                               

			paddw mm0, mm1                              

			paddw mm2, mm1                              

			psraw mm5, 5                                

			psraw mm6, 5                                

			packuswb mm3, mm4                           

			packuswb mm5, mm6                           
			movq [eax], mm3                             
			movq [eax+edx], mm5                         

			lea eax, [eax+edx*2]                        
		dec esi                                     
			jg ff_pred8x8_plane_mmx2__loop_i                                    
			pop ebp                                     
			pop edi                                     
			pop esi                                     
			pop ebx                                     
			ret                                         

	}
}

NAKED void ff_pred8x8_plane_sse2 (uint8_t *src, int stride)
{
	__asm{
		push ebx                                
			push esi                                
			push edi                                
			push ebp                                
			mov eax, [esp + 16 + 4 + 0*4]           
		mov ecx, [esp + 16 + 4 + 1*4]           

		mov edx, ecx                            
			neg ecx                                 

			movd xmm0, [eax+ecx -1]                 

		pxor xmm2, xmm2                         
			movd xmm1, [eax+ecx +4]                 

		punpckldq xmm0, xmm1                    

			punpcklbw xmm0, xmm2                    

			pmullw xmm0, [pw_m4to4]                 

		movhlps xmm1, xmm0                      

			paddw xmm0, xmm1                        

			pshuflw xmm1, xmm0, 0xE                 

			paddw xmm0, xmm1                        

			pshuflw xmm1, xmm0, 0x1                 

			paddw xmm0, xmm1                        

			lea esi, [eax+edx*4-1]                  
		lea ebx, [eax -1]                       
		add esi, edx                            


			movzx eax, byte ptr [ebx+edx*2 ]            
		movzx edi, byte ptr [esi+ecx ]              
		sub edi, eax                            

			movzx eax, byte ptr [ebx ]                  
		movzx ebp, byte ptr [esi+edx ]              
		sub ebp, eax                            
			lea edi, [edi+ebp*4]                    
		sub edi, ebp                            

			movzx eax, byte ptr [ebx+ecx ]              
		movzx ebp, byte ptr [esi+edx*2 ]            
		sub ebp, eax                            
			lea edi, [edi+ebp*4]                    

		movzx eax, byte ptr [ebx+edx ]              
		movzx ebp, byte ptr [esi ]                  
		sub ebp, eax                            
			lea ebp, [edi+ebp*2]                    

		lea edi, [ebp*8 + ebp + 16]                     
		lea edi, [edi+ebp*8]                    
		sar edi, 5                              

			mov eax, [esp + 16 + 4]                 

		movzx ebx, byte ptr [esi+edx*2 ]            
		movzx esi, byte ptr [eax+ecx +7]            
		lea ebx, [ebx+esi+1]                    
		shl ebx, 4                              
			movd ecx, xmm0                          
			movsx ecx, cx                           
			imul ecx, 17                            
			add ecx, 16                             
			sar ecx, 5                              
			movd xmm0, ecx                          
			add ecx, edi                            
			sub ebx, ecx                            
			add ecx, ecx                            
			sub ebx, ecx                            

			movd xmm1, edi                          
			movd xmm3, ebx                          
			pshuflw xmm0, xmm0, 0x0                 
			pshuflw xmm1, xmm1, 0x0                 
			pshuflw xmm3, xmm3, 0x0                 

			punpcklqdq xmm0, xmm0                   

			punpcklqdq xmm1, xmm1                   

			punpcklqdq xmm3, xmm3                   

			pmullw xmm0, [pw_0to7]                  

		paddw xmm0, xmm3                        

			mov esi, 4
ff_pred8x8_plane_sse2__loop_i:                                    
		movdqa xmm3, xmm0                       

			paddw xmm0, xmm1                        

			psraw xmm3, 5                           
			movdqa xmm4, xmm0                       

			paddw xmm0, xmm1                        

			psraw xmm4, 5                           

			packuswb xmm3, xmm4                     
			movq qword ptr[eax], xmm3                        
			movhps [eax+edx], xmm3                  

			lea eax, [eax+edx*2]                    
		dec esi                                 
			jg ff_pred8x8_plane_sse2__loop_i                                
			pop ebp                                 
			pop edi                                 
			pop esi                                 
			pop ebx                                 
			ret                                     

	}
}

NAKED void ff_pred8x8_plane_ssse3 (uint8_t *src, int stride)
{
	__asm {
		push ebx                               
			push esi                               
			push edi                               
			push ebp                               
			mov eax, [esp + 16 + 4 + 0*4]          
		mov ecx, [esp + 16 + 4 + 1*4]          

		mov edx, ecx                           
			neg ecx                                

			movd xmm0, [eax+ecx -1]                
		movhps xmm0, [eax+ecx +4]              

		pmaddubsw xmm0, [plane8_shuf]        

		movhlps xmm1, xmm0                     

			paddw xmm0, xmm1                       


			pshuflw xmm1, xmm0, 0x1                

			paddw xmm0, xmm1                       

			lea esi, [eax+edx*4-1]                 
		lea ebx, [eax -1]                      
		add esi, edx                           


			movzx eax, byte ptr [ebx+edx*2 ]           
		movzx edi, byte ptr [esi+ecx ]             
		sub edi, eax                           

			movzx eax, byte ptr [ebx ]                 
		movzx ebp, byte ptr [esi+edx ]             
		sub ebp, eax                           
			lea edi, [edi+ebp*4]                   
		sub edi, ebp                           

			movzx eax, byte ptr [ebx+ecx ]             
		movzx ebp, byte ptr [esi+edx*2 ]           
		sub ebp, eax                           
			lea edi, [edi+ebp*4]                   

		movzx eax, byte ptr [ebx+edx ]             
		movzx ebp, byte ptr [esi ]                 
		sub ebp, eax                           
			lea ebp, [edi+ebp*2]                   

		lea edi, [ebp*8 + ebp + 16]                    
		lea edi, [edi+ebp*8]                   
		sar edi, 5                             

			mov eax, [esp + 16 + 4]                

		movzx ebx, byte ptr [esi+edx*2 ]           
		movzx esi, byte ptr [eax+ecx +7]           
		lea ebx, [ebx+esi+1]                   
		shl ebx, 4                             
			movd ecx, xmm0                         
			movsx ecx, cx                          
			imul ecx, 17                           
			add ecx, 16                            
			sar ecx, 5                             
			movd xmm0, ecx                         
			add ecx, edi                           
			sub ebx, ecx                           
			add ecx, ecx                           
			sub ebx, ecx                           

			movd xmm1, edi                         
			movd xmm3, ebx                         
			pshuflw xmm0, xmm0, 0x0                
			pshuflw xmm1, xmm1, 0x0                
			pshuflw xmm3, xmm3, 0x0                

			punpcklqdq xmm0, xmm0                  

			punpcklqdq xmm1, xmm1                  

			punpcklqdq xmm3, xmm3                  

			pmullw xmm0, [pw_0to7]                 

		paddw xmm0, xmm3                       

			mov esi, 4
ff_pred8x8_plane_ssse3__loop_i:                                   
		movdqa xmm3, xmm0                      

			paddw xmm0, xmm1                       

			psraw xmm3, 5                          
			movdqa xmm4, xmm0                      

			paddw xmm0, xmm1                       

			psraw xmm4, 5                          

			packuswb xmm3, xmm4                    
			movq qword ptr[eax], xmm3                       
			movhps [eax+edx], xmm3                 

			lea eax, [eax+edx*2]                   
		dec esi                                
			jg ff_pred8x8_plane_ssse3__loop_i                               
			pop ebp                                
			pop edi                                
			pop esi                                
			pop ebx                                
			ret                                    

	}
}

NAKED void ff_pred8x8_vertical_mmx (uint8_t *src, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]
		mov ecx, [esp + 0 + 4 + 1*4]

		;;line 783+1 libavcodec/x86/h2
			sub eax, ecx                
			movq mm0, [eax]             
		;;line 789+1 libavcodec/x86/h2
			movq [eax+ecx*1], mm0       
			;;line 789+0 libavcodec/x86/h2
			movq [eax+ecx*2], mm0       
			lea eax, [eax+ecx*2]        
		movq [eax+ecx*1], mm0       
			movq [eax+ecx*2], mm0       
			lea eax, [eax+ecx*2]        
		movq [eax+ecx*1], mm0       
			movq [eax+ecx*2], mm0       
			lea eax, [eax+ecx*2]        
		;;line 790+1 libavcodec/x86/h2
			movq [eax+ecx*1], mm0       
			movq [eax+ecx*2], mm0       
			ret                         

	}
}

NAKED void ff_pred8x8_horizontal_mmx (uint8_t *src, int stride)
{
	__asm {
        mov    eax,DWORD PTR [esp+0x4]               
        mov    ecx,DWORD PTR [esp+0x8]               
        mov    edx,0x4                               

            ff_pred8x8_horizontal_mmx_loop:                                   
        movd   mm0,DWORD PTR [eax-0x4]               
        movd   mm1,DWORD PTR [eax+ecx*1-0x4]         
        punpcklbw mm0,mm0                            
            punpcklbw mm1,mm1                            
            punpckhwd mm0,mm0                            
            punpckhwd mm1,mm1                            
            punpckhdq mm0,mm0                            
            punpckhdq mm1,mm1                            
            movq   QWORD PTR [eax],mm0                   
            movq   QWORD PTR [eax+ecx*1],mm1             
            lea    eax,[eax+ecx*2]                       
        dec    edx                                   
            jg     ff_pred8x8_horizontal_mmx_loop 
            repz ret                                     

	}
}

NAKED void ff_pred8x8_horizontal_mmxext (uint8_t *src, int stride)
{
	__asm {
        mov    eax,DWORD PTR [esp+0x4]           
        mov    ecx,DWORD PTR [esp+0x8]           
        mov    edx,0x4                           

ff_pred8x8_horizontal_mmxext_loop:       
        movd   mm0,DWORD PTR [eax-0x4]           
        movd   mm1,DWORD PTR [eax+ecx*1-0x4]     
        punpcklbw mm0,mm0                        
            punpcklbw mm1,mm1                        
            pshufw mm0,mm0,0xff                      
            pshufw mm1,mm1,0xff                      
            movq   QWORD PTR [eax],mm0               
            movq   QWORD PTR [eax+ecx*1],mm1         
            lea    eax,[eax+ecx*2]                   
        dec    edx                               
            jg     ff_pred8x8_horizontal_mmxext_loop 
            repz ret
    }
}

NAKED void ff_pred8x8_horizontal_ssse3 (uint8_t *src, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]   
		mov ecx, [esp + 0 + 4 + 1*4]   

		mov edx, 4                     
			movq mm2, [ff_pb_3]            
ff_pred8x8_horizontal_ssse3__loop_i:                          
		movd mm0, [eax+ecx*0-4]        
		movd mm1, [eax+ecx*1-4]        

		pshufb mm0, mm2                

			pshufb mm1, mm2                
			movq [eax+ecx*0], mm0          
			movq [eax+ecx*1], mm1          
			lea eax, [eax+ecx*2]           
		dec edx                        
			jg ff_pred8x8_horizontal_ssse3__loop_i                       
			rep ret                        

	}
}

NAKED void ff_pred8x8_top_dc_mmxext (uint8_t *src, int stride)
{
	__asm {
		push ebx                                        
			push esi                                        
			mov eax, [esp + 8 + 4 + 0*4]                    
		mov ecx, [esp + 8 + 4 + 1*4]                    

		;;line 840+1 libavcodec/x86/h264_intrapredadsdmd    
			sub eax, ecx                                    
			movq mm0, [eax]                                 

		;;line 842+0 libavcodec/x86/h264_intrapredadsdmd    
			pxor mm1, mm1                                   
			;;line 843+1 libavcodec/x86/h264_intrapredadsdmd    

			;;line 843+0 libavcodec/x86/h264_intrapredadsdmd    
			pxor mm2, mm2                                   
			;line 844+1 libavcodec/x86/h264_intrapredadsdmd    
			lea edx, [eax+ecx*2]                            

		;;line 845+0 libavcodec/x86/h264_intrapredadsdmd    
			punpckhbw mm1, mm0                              
			;;line 846+1 libavcodec/x86/h264_intrapredadsdmd    

			;;line 846+0 libavcodec/x86/h264_intrapredadsdmd    
			punpcklbw mm0, mm2                              
			;;line 847+1 libavcodec/x86/h264_intrapredadsdmd    

			;;line 847+0 libavcodec/x86/h264_intrapredadsdmd    
			psadbw mm1, mm2                                 
			;;line 848+1 libavcodec/x86/h264_intrapredadsdmd    
			lea ebx, [edx+ecx*2]                            

		;;line 849+0 libavcodec/x86/h264_intrapredadsdmd    
			psadbw mm0, mm2                                 
			;;line 850+1 libavcodec/x86/h264_intrapredadsdmd    

			;;line 850+0 libavcodec/x86/h264_intrapredadsdmd    
			psrlw mm1, 1                                    
			;;line 851+1 libavcodec/x86/h264_intrapredadsdmd    

			;;line 851+0 libavcodec/x86/h264_intrapredadsdmd    
			psrlw mm0, 1                                    
			;;line 852+1 libavcodec/x86/h264_intrapredadsdmd    

			;;line 852+0 libavcodec/x86/h264_intrapredadsdmd    
			pavgw mm1, mm2                                  
			;;line 853+1 libavcodec/x86/h264_intrapredadsdmd    
			lea esi, [ebx+ecx*2]                            

		;;line 854+0 libavcodec/x86/h264_intrapredadsdmd    
			pavgw mm0, mm2                                  
			;;line 855+1 libavcodec/x86/h264_intrapredadsdmd    
			pshufw mm1, mm1, 0                              
			pshufw mm0, mm0, 0                              

			;;line 857+0 libavcodec/x86/h264_intrapredadsdmd    
			packuswb mm0, mm1                               
			;;line 858+1 libavcodec/x86/h264_intrapredadsdmd    
			movq [eax+ecx*1], mm0                           
			movq [eax+ecx*2], mm0                           
			lea eax, [ebx+ecx*2]                            
		movq [edx+ecx*1], mm0                           
			movq [edx+ecx*2], mm0                           
			movq [ebx+ecx*1], mm0                           
			movq [ebx+ecx*2], mm0                           
			movq [eax+ecx*1], mm0                           
			movq [eax+ecx*2], mm0                           
			pop esi                                         
			;;line 867+0 libavcodec/x86/h264_intrapredadsdmd    
			pop ebx                                         
			ret                                             

	}
}

NAKED void ff_pred8x8_dc_mmxext (uint8_t *src, int stride)
{
	__asm {
		push ebx                                    
			push esi                                    
			mov eax, [esp + 8 + 4 + 0*4]                
		mov ecx, [esp + 8 + 4 + 1*4]                

		;;line 875+1 libavcodec/x86/h264_intrapredadsdmd
			sub eax, ecx                                

			;;line 876+0 libavcodec/x86/h264_intrapredadsdmd
			pxor mm7, mm7                               
			;;line 877+1 libavcodec/x86/h264_intrapredadsdmd
			movd mm0, [eax+0]                           
		movd mm1, [eax+4]                           

		;;line 879+0 libavcodec/x86/h264_intrapredadsdmd
			psadbw mm0, mm7                             
			;;line 880+1 libavcodec/x86/h264_intrapredadsdmd
			mov esi, eax                                

			;;line 881+0 libavcodec/x86/h264_intrapredadsdmd
			psadbw mm1, mm7                             
			;;line 882+1 libavcodec/x86/h264_intrapredadsdmd

			movzx edx, byte ptr [eax+ecx*1-1]               
		movzx ebx, byte ptr [eax+ecx*2-1]               
		lea eax, [eax+ecx*2]                        
		add edx, ebx                                
			movzx ebx, byte ptr [eax+ecx*1-1]               
		add edx, ebx                                
			movzx ebx, byte ptr [eax+ecx*2-1]               
		add edx, ebx                                
			lea eax, [eax+ecx*2]                        
		movd mm2, edx                               
			movzx edx, byte ptr [eax+ecx*1-1]               
		movzx ebx, byte ptr [eax+ecx*2-1]               
		lea eax, [eax+ecx*2]                        
		add edx, ebx                                
			movzx ebx, byte ptr [eax+ecx*1-1]               
		add edx, ebx                                
			movzx ebx, byte ptr [eax+ecx*2-1]               
		add edx, ebx                                
			movd mm3, edx                               


			;;line 903+0 libavcodec/x86/h264_intrapredadsdmd
			punpcklwd mm0, mm1                          
			;;line 904+1 libavcodec/x86/h264_intrapredadsdmd
			mov eax, esi                                

			;;line 905+0 libavcodec/x86/h264_intrapredadsdmd
			punpcklwd mm2, mm3                          
			;;line 906+1 libavcodec/x86/h264_intrapredadsdmd

			;;line 906+0 libavcodec/x86/h264_intrapredadsdmd
			punpckldq mm0, mm2                          
			;;line 907+1 libavcodec/x86/h264_intrapredadsdmd
			pshufw mm3, mm0, 11110110b                   
			lea edx, [eax+ecx*2]                        
		pshufw mm0, mm0, 01110100b                   

			;;line 910+0 libavcodec/x86/h264_intrapredadsdmd
			paddw mm0, mm3                              
			;;line 911+1 libavcodec/x86/h264_intrapredadsdmd
			lea ebx, [edx+ecx*2]                        

		;;line 912+0 libavcodec/x86/h264_intrapredadsdmd
			psrlw mm0, 2                                
			;;line 913+1 libavcodec/x86/h264_intrapredadsdmd

			;;line 913+0 libavcodec/x86/h264_intrapredadsdmd
			pavgw mm0, mm7                              
			;;line 914+1 libavcodec/x86/h264_intrapredadsdmd
			lea esi, [ebx+ecx*2]                        

		;;line 915+0 libavcodec/x86/h264_intrapredadsdmd
			packuswb mm0, mm0                           
			;;line 916+1 libavcodec/x86/h264_intrapredadsdmd

			;;line 916+0 libavcodec/x86/h264_intrapredadsdmd
			punpcklbw mm0, mm0                          
			;;line 917+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm1, mm0                               

			;;line 918+0 libavcodec/x86/h264_intrapredadsdmd
			punpcklbw mm0, mm0                          
			;;line 919+1 libavcodec/x86/h264_intrapredadsdmd

			;;line 919+0 libavcodec/x86/h264_intrapredadsdmd
			punpckhbw mm1, mm1                          
			;;line 920+1 libavcodec/x86/h264_intrapredadsdmd
			movq [eax+ecx*1], mm0                       
			movq [eax+ecx*2], mm0                       
			movq [edx+ecx*1], mm0                       
			movq [edx+ecx*2], mm0                       
			movq [ebx+ecx*1], mm1                       
			movq [ebx+ecx*2], mm1                       
			movq [esi+ecx*1], mm1                       
			movq [esi+ecx*2], mm1                       
			pop esi                                     
			;;line 928+0 libavcodec/x86/h264_intrapredadsdmd
			pop ebx                                     
			ret                                         

	}
}

NAKED void ff_pred8x8l_top_dc_mmxext (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                       
			mov eax, [esp + 4 + 4 + 0*4]   
		mov ecx, [esp + 4 + 4 + 1*4]   
		mov edx, [esp + 4 + 4 + 2*4]   
		mov ebx, [esp + 4 + 4 + 3*4]   

		sub eax, ebx                   

			pxor mm7, mm7                  
			movq mm0, [eax-8]              
		movq mm3, [eax]                
		movq mm1, [eax+8]              
		movq mm2, mm3                  
			movq mm4, mm3                  

			psllq mm2, (8-7)*8             

			psrlq mm0, 7*8                 

			por mm2, mm0                   

			psllq mm1, (8-1)*8             

			psrlq mm4, 1*8                 

			por mm1, mm4                   
			test ecx, ecx                  
			jz ff_pred8x8_top_dc_mmxext__fix_lt_2                   
			test edx, edx                  
			jz ff_pred8x8_top_dc_mmxext__fix_tr_1                   
			jmp ff_pred8x8_top_dc_mmxext__body                      
ff_pred8x8_top_dc_mmxext__fix_lt_2:                      
		movq mm5, mm3                  

			pxor mm5, mm2                  

			psllq mm5, 56                  

			psrlq mm5, 56                  

			pxor mm2, mm5                  
			test edx, edx                  
			jnz ff_pred8x8_top_dc_mmxext__body                      
ff_pred8x8_top_dc_mmxext__fix_tr_1:                      
		movq mm5, mm3                  

			pxor mm5, mm1                  

			psrlq mm5, 56                  

			psllq mm5, 56                  

			pxor mm1, mm5                  
ff_pred8x8_top_dc_mmxext__body:                           
			movq mm5, mm2                  

			pavgb mm2, mm1                 

			pxor mm1, mm5                  
			movq mm0, mm3                  

			pand mm1, [ff_pb_1]            

		psubusb mm2, mm1               

			pavgb mm0, mm2                 

			psadbw mm7, mm0                

			paddw mm7, [ff_pw_4]           

		psrlw mm7, 3                   
			pshufw mm7, mm7, 0             

			packuswb mm7, mm7              
			movq [eax+ebx*1], mm7          
			movq [eax+ebx*2], mm7          
			lea eax, [eax+ebx*2]           
		movq [eax+ebx*1], mm7          
			movq [eax+ebx*2], mm7          
			lea eax, [eax+ebx*2]           
		movq [eax+ebx*1], mm7          
			movq [eax+ebx*2], mm7          
			lea eax, [eax+ebx*2]           
		movq [eax+ebx*1], mm7          
			movq [eax+ebx*2], mm7          
			pop ebx                        
			ret                            

	}
}

NAKED void ff_pred8x8l_top_dc_ssse3 (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                        
			mov eax, [esp + 4 + 4 + 0*4]    
		mov ecx, [esp + 4 + 4 + 1*4]    
		mov edx, [esp + 4 + 4 + 2*4]    
		mov ebx, [esp + 4 + 4 + 3*4]    

		sub eax, ebx                    

			pxor mm7, mm7                   
			movq mm0, [eax-8]               
		movq mm3, [eax]                 
		movq mm1, [eax+8]               
		movq mm2, mm3                   
			movq mm4, mm3                   

			palignr mm2, mm0, 7             

			palignr mm1, mm4, 1             
			test ecx, ecx                   
			jz ff_pred8x8l_top_dc_ssse3_fix_lt_2                    
			test edx, edx                   
			jz ff_pred8x8l_top_dc_ssse3_fix_tr_1                    
			jmp ff_pred8x8l_top_dc_ssse3_body                       
ff_pred8x8l_top_dc_ssse3_fix_lt_2:                       
		movq mm5, mm3                   

			pxor mm5, mm2                   

			psllq mm5, 56                   

			psrlq mm5, 56                   

			pxor mm2, mm5                   
			test edx, edx                   
			jnz  ff_pred8x8l_top_dc_ssse3_body                       
ff_pred8x8l_top_dc_ssse3_fix_tr_1:                       
		movq mm5, mm3                   

			pxor mm5, mm1                   

			psrlq mm5, 56                   

			psllq mm5, 56                   

			pxor mm1, mm5                   
ff_pred8x8l_top_dc_ssse3_body:                            
			movq mm5, mm2                   

			pavgb mm2, mm1                  

			pxor mm1, mm5                   
			movq mm0, mm3                   

			pand mm1, [ff_pb_1]             

		psubusb mm2, mm1                

			pavgb mm0, mm2                  

			psadbw mm7, mm0                 

			paddw mm7, [ff_pw_4]            

		psrlw mm7, 3                    
			pshufw mm7, mm7, 0              

			packuswb mm7, mm7               
			movq [eax+ebx*1], mm7           
			movq [eax+ebx*2], mm7           
			lea eax, [eax+ebx*2]            
		movq [eax+ebx*1], mm7           
			movq [eax+ebx*2], mm7           
			lea eax, [eax+ebx*2]            
		movq [eax+ebx*1], mm7           
			movq [eax+ebx*2], mm7           
			lea eax, [eax+ebx*2]            
		movq [eax+ebx*1], mm7           
			movq [eax+ebx*2], mm7           
			pop ebx                         
			ret
	}
}

NAKED void ff_pred8x8l_dc_mmxext (uint8_t *src, int has_topleft, int has_topright, int stride)
{
    __asm {
        push   ebx                                  
            push   esi                                  
            mov    eax,DWORD PTR [esp+0xc]              
        mov    ecx,DWORD PTR [esp+0x10]             
        mov    edx,DWORD PTR [esp+0x14]             
        mov    ebx,DWORD PTR [esp+0x18]             
        sub    eax,ebx                              
            lea    esi,[eax+ebx*2]                      
        movq   mm0,QWORD PTR [eax+ebx*1-0x8]        
        punpckhbw mm0,QWORD PTR [eax-0x8]           
        movq   mm1,QWORD PTR [esi+ebx*1-0x8]        
        punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8]     
        mov    esi,eax                              
            punpckhwd mm1,mm0                           
            lea    eax,[eax+ebx*4]                      
        movq   mm2,QWORD PTR [eax+ebx*1-0x8]        
        punpckhbw mm2,QWORD PTR [eax-0x8]           
        lea    eax,[eax+ebx*2]                      
        movq   mm3,QWORD PTR [eax+ebx*1-0x8]        
        punpckhbw mm3,QWORD PTR [eax-0x8]           
        punpckhwd mm3,mm2                           
            punpckhdq mm3,mm1                           
            lea    eax,[eax+ebx*2]                      
        movq   mm0,QWORD PTR [eax-0x8]              
        movq   mm1,QWORD PTR [esi]                  
        mov    eax,esi                              
            movq   mm4,mm3                              
            movq   mm2,mm3                              
            psllq  mm4,0x8                              
            psrlq  mm0,0x38                             
            por    mm4,mm0                              
            psllq  mm1,0x38                             
            psrlq  mm2,0x8                              
            por    mm1,mm2                              
            test   ecx,ecx                              
            jne    ff_pred8x8l_dc_mmxext_do_left        

ff_pred8x8l_dc_mmxext_fix_lt_1:             
        movq   mm5,mm3                              
            pxor   mm5,mm4                              
            psrlq  mm5,0x38                             
            psllq  mm5,0x30                             
            pxor   mm1,mm5                              
            jmp    ff_pred8x8l_dc_mmxext_do_left        

ff_pred8x8l_dc_mmxext_fix_lt_2:             
        movq   mm5,mm3                              
            pxor   mm5,mm2                              
            psllq  mm5,0x38                             
            psrlq  mm5,0x38                             
            pxor   mm2,mm5                              
            test   edx,edx                              
            jne    ff_pred8x8l_dc_mmxext_body           

ff_pred8x8l_dc_mmxext_fix_tr_1:             
        movq   mm5,mm3                              
            pxor   mm5,mm1                              
            psrlq  mm5,0x38                             
            psllq  mm5,0x38                             
            pxor   mm1,mm5                              
            jmp    ff_pred8x8l_dc_mmxext_body           

ff_pred8x8l_dc_mmxext_do_left:              
        movq   mm0,mm4                              
            movq   mm5,mm1                              
            pavgb  mm1,mm4                              
            pxor   mm4,mm5                              
            movq   mm2,mm3                              
            pand   mm4,[ff_pb_1]                 
        psubusb mm1,mm4                             
            pavgb  mm2,mm1                              
            movq   mm4,mm0                              
            movq   mm7,mm2                              
            movq   mm5,mm3                              
            pavgb  mm3,mm0                              
            pxor   mm0,mm5                              
            movq   mm1,mm4                              
            pand   mm0,[ff_pb_1]                 
        psubusb mm3,mm0                             
            pavgb  mm1,mm3                              
            psllq  mm1,0x38                             
            movq   mm3,mm1                              
            psllq  mm7,0x8                              
            psrlq  mm3,0x38                             
            por    mm7,mm3                              
            movq   mm0,QWORD PTR [eax-0x8]              
        movq   mm3,QWORD PTR [eax]                  
        movq   mm1,QWORD PTR [eax+0x8]              
        movq   mm2,mm3                              
            movq   mm4,mm3                              
            psllq  mm2,0x8                              
            psrlq  mm0,0x38                             
            por    mm2,mm0                              
            psllq  mm1,0x38                             
            psrlq  mm4,0x8                              
            por    mm1,mm4                              
            test   ecx,ecx                              
            je     ff_pred8x8l_dc_mmxext_fix_lt_2       
            test   edx,edx                              
            je     ff_pred8x8l_dc_mmxext_fix_tr_1       

ff_pred8x8l_dc_mmxext_body:                 
        lea    ecx,[eax+ebx*2]                      
        movq   mm5,mm2                              
            pavgb  mm2,mm1                              
            pxor   mm1,mm5                              
            movq   mm6,mm3                              
            pand   mm1,[ff_pb_1]                 
        psubusb mm2,mm1                             
            pavgb  mm6,mm2                              
            pxor   mm0,mm0                              
            pxor   mm1,mm1                              
            lea    edx,[ecx+ebx*2]                      
        psadbw mm0,mm7                              
            psadbw mm1,mm6                              
            paddw  mm0,[ff_pw_8]                 
        paddw  mm0,mm1                              
            lea    esi,[edx+ebx*2]                      
        psrlw  mm0,0x4                              
            pshufw mm0,mm0,0x0                          
            packuswb mm0,mm0                            
            movq   QWORD PTR [eax+ebx*1],mm0            
            movq   QWORD PTR [eax+ebx*2],mm0            
            movq   QWORD PTR [ecx+ebx*1],mm0            
            movq   QWORD PTR [ecx+ebx*2],mm0            
            movq   QWORD PTR [edx+ebx*1],mm0            
            movq   QWORD PTR [edx+ebx*2],mm0            
            movq   QWORD PTR [esi+ebx*1],mm0            
            movq   QWORD PTR [esi+ebx*2],mm0            
            pop    esi                                  
            pop    ebx                                  
            ret                                         
    }
}

NAKED void ff_pred8x8l_dc_ssse3 (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                         
			push esi                         
			mov eax, [esp + 8 + 4 + 0*4]     
		mov ecx, [esp + 8 + 4 + 1*4]     
		mov edx, [esp + 8 + 4 + 2*4]     
		mov ebx, [esp + 8 + 4 + 3*4]     

		sub eax, ebx                     
			lea esi, [eax+ebx*2]             
		movq mm0, [eax+ebx*1-8]          

		punpckhbw mm0, [eax+ebx*0-8]     
		movq mm1, [esi+ebx*1-8]          

		punpckhbw mm1, [eax+ebx*2-8]     
		mov esi, eax                     

			punpckhwd mm1, mm0               
			lea eax, [eax+ebx*4]             
		movq mm2, [eax+ebx*1-8]          

		punpckhbw mm2, [eax+ebx*0-8]     
		lea eax, [eax+ebx*2]             
		movq mm3, [eax+ebx*1-8]          

		punpckhbw mm3, [eax+ebx*0-8]     

		punpckhwd mm3, mm2               

			punpckhdq mm3, mm1               
			lea eax, [eax+ebx*2]             
		movq mm0, [eax+ebx*0-8]          
		movq mm1, [esi]                  
		mov eax, esi                     
			movq mm4, mm3                    
			movq mm2, mm3                    

			palignr mm4, mm0, 7              

			palignr mm1, mm2, 1              
			test ecx, ecx                    
			jnz ff_pred8x8l_dc_ssse3__do_left                     
ff_pred8x8l_dc_ssse3__fix_lt_1:                        
		movq mm5, mm3                    

			pxor mm5, mm4                    

			psrlq mm5, 56                    

			psllq mm5, 48                    

			pxor mm1, mm5                    
			jmp ff_pred8x8l_dc_ssse3__do_left                     
ff_pred8x8l_dc_ssse3__fix_lt_2:                        
		movq mm5, mm3                    

			pxor mm5, mm2                    

			psllq mm5, 56                    

			psrlq mm5, 56                    

			pxor mm2, mm5                    
			test edx, edx                    
			jnz ff_pred8x8l_dc_ssse3__body                        
ff_pred8x8l_dc_ssse3__fix_tr_1:                        
		movq mm5, mm3                    

			pxor mm5, mm1                    

			psrlq mm5, 56                    

			psllq mm5, 56                    

			pxor mm1, mm5                    
			jmp ff_pred8x8l_dc_ssse3__body                        
ff_pred8x8l_dc_ssse3__do_left:                         
		movq mm0, mm4                    
			movq mm5, mm1                    

			pavgb mm1, mm4                   

			pxor mm4, mm5                    
			movq mm2, mm3                    

			pand mm4, [ff_pb_1]              

		psubusb mm1, mm4                 

			pavgb mm2, mm1                   
			movq mm4, mm0                    
			movq mm7, mm2                    
			movq mm5, mm3                    

			pavgb mm3, mm0                   

			pxor mm0, mm5                    
			movq mm1, mm4                    

			pand mm0, [ff_pb_1]              

		psubusb mm3, mm0                 

			pavgb mm1, mm3                   

			psllq mm1, 56                    

			palignr mm7, mm1, 7              
			movq mm0, [eax-8]                
		movq mm3, [eax]                  
		movq mm1, [eax+8]                
		movq mm2, mm3                    
			movq mm4, mm3                    

			palignr mm2, mm0, 7              

			palignr mm1, mm4, 1              
			test ecx, ecx                    
			jz ff_pred8x8l_dc_ssse3__fix_lt_2                     
			test edx, edx                    
			jz ff_pred8x8l_dc_ssse3__fix_tr_1                     
ff_pred8x8l_dc_ssse3__body:                             
			lea ecx, [eax+ebx*2]             
		movq mm5, mm2                    

			pavgb mm2, mm1                   

			pxor mm1, mm5                    
			movq mm6, mm3                    

			pand mm1, [ff_pb_1]              

		psubusb mm2, mm1                 

			pavgb mm6, mm2                   

			pxor mm0, mm0                    

			pxor mm1, mm1                    
			lea edx, [ecx+ebx*2]             

		psadbw mm0, mm7                  

			psadbw mm1, mm6                  

			paddw mm0, [ff_pw_8]             

		paddw mm0, mm1                   
			lea esi, [edx+ebx*2]             

		psrlw mm0, 4                     
			pshufw mm0, mm0, 0               

			packuswb mm0, mm0                
			movq [eax+ebx*1], mm0            
			movq [eax+ebx*2], mm0            
			movq [ecx+ebx*1], mm0            
			movq [ecx+ebx*2], mm0            
			movq [edx+ebx*1], mm0            
			movq [edx+ebx*2], mm0            
			movq [esi+ebx*1], mm0            
			movq [esi+ebx*2], mm0            
			pop esi                          
			pop ebx                          
			ret                              

	}
}

NAKED void ff_pred8x8l_horizontal_mmxext (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
        push   ebx                              
            mov    eax,DWORD PTR [esp+0x8]          
        mov    ecx,DWORD PTR [esp+0xc]          
        mov    edx,DWORD PTR [esp+0x10]         
        mov    ebx,DWORD PTR [esp+0x14]         
        sub    eax,ebx                          
            lea    edx,[eax+ebx*2]                  
        movq   mm0,QWORD PTR [eax+ebx*1-0x8]    
        test   ecx,ecx                          
            lea    ecx,[eax+ebx*1]                  
        cmovne ecx,eax                          
            punpckhbw mm0,QWORD PTR [ecx-0x8]       
        movq   mm1,QWORD PTR [edx+ebx*1-0x8]    
        punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8] 
        mov    edx,eax                          
            punpckhwd mm1,mm0                       
            lea    eax,[eax+ebx*4]                  
        movq   mm2,QWORD PTR [eax+ebx*1-0x8]    
        punpckhbw mm2,QWORD PTR [eax-0x8]       
        lea    eax,[eax+ebx*2]                  
        movq   mm3,QWORD PTR [eax+ebx*1-0x8]    
        punpckhbw mm3,QWORD PTR [eax-0x8]       
        punpckhwd mm3,mm2                       
            punpckhdq mm3,mm1                       
            lea    eax,[eax+ebx*2]                  
        movq   mm0,QWORD PTR [eax-0x8]          
        movq   mm1,QWORD PTR [ecx-0x8]          
        mov    eax,edx                          
            movq   mm4,mm3                          
            movq   mm2,mm3                          
            psllq  mm4,0x8                          
            psrlq  mm0,0x38                         
            por    mm4,mm0                          
            psllq  mm1,0x38                         
            psrlq  mm2,0x8                          
            por    mm1,mm2                          
            movq   mm0,mm4                          
            movq   mm5,mm1                          
            pavgb  mm1,mm4                          
            pxor   mm4,mm5                          
            movq   mm2,mm3                          
            pand   mm4,QWORD PTR [ff_pb_1]          
        psubusb mm1,mm4                         
            pavgb  mm2,mm1                          
            movq   mm4,mm0                          
            movq   mm7,mm2                          
            movq   mm5,mm3                          
            pavgb  mm3,mm0                          
            pxor   mm0,mm5                          
            movq   mm1,mm4                          
            pand   mm0,QWORD PTR [ff_pb_1]          
        psubusb mm3,mm0                         
            pavgb  mm1,mm3                          
            psllq  mm1,0x38                         
            movq   mm3,mm1                          
            psllq  mm7,0x8                          
            psrlq  mm3,0x38                         
            por    mm7,mm3                          
            movq   mm3,mm7                          
            lea    ecx,[eax+ebx*2]                  
        movq   mm7,mm3                          
            punpckhbw mm3,mm3                       
            punpcklbw mm7,mm7                       
            pshufw mm0,mm3,0xff                     
            pshufw mm1,mm3,0xaa                     
            lea    edx,[ecx+ebx*2]                  
        pshufw mm2,mm3,0x55                     
            pshufw mm3,mm3,0x0                      
            pshufw mm4,mm7,0xff                     
            pshufw mm5,mm7,0xaa                     
            pshufw mm6,mm7,0x55                     
            pshufw mm7,mm7,0x0                      
            movq   QWORD PTR [eax+ebx*1],mm0        
            movq   QWORD PTR [eax+ebx*2],mm1        
            movq   QWORD PTR [ecx+ebx*1],mm2        
            movq   QWORD PTR [ecx+ebx*2],mm3        
            movq   QWORD PTR [edx+ebx*1],mm4        
            movq   QWORD PTR [edx+ebx*2],mm5        
            lea    eax,[edx+ebx*2]                  
        movq   QWORD PTR [eax+ebx*1],mm6        
            movq   QWORD PTR [eax+ebx*2],mm7        
            pop    ebx                              
            ret                                     

    }
}

NAKED void ff_pred8x8l_horizontal_ssse3 (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                      
			mov eax, [esp + 4 + 4 + 0*4]  
		mov ecx, [esp + 4 + 4 + 1*4]  
		mov edx, [esp + 4 + 4 + 2*4]  
		mov ebx, [esp + 4 + 4 + 3*4]  

		sub eax, ebx                  
			lea edx, [eax+ebx*2]          
		movq mm0, [eax+ebx*1-8]       
		test ecx, ecx                 
			lea ecx, [eax+ebx]            
		cmovnz ecx, eax               

			punpckhbw mm0, [ecx+ebx*0-8]  
		movq mm1, [edx+ebx*1-8]       

		punpckhbw mm1, [eax+ebx*2-8]  
		mov edx, eax                  

			punpckhwd mm1, mm0            
			lea eax, [eax+ebx*4]          
		movq mm2, [eax+ebx*1-8]       

		punpckhbw mm2, [eax+ebx*0-8]  
		lea eax, [eax+ebx*2]          
		movq mm3, [eax+ebx*1-8]       

		punpckhbw mm3, [eax+ebx*0-8]  

		punpckhwd mm3, mm2            

			punpckhdq mm3, mm1            
			lea eax, [eax+ebx*2]          
		movq mm0, [eax+ebx*0-8]       
		movq mm1, [ecx+ebx*0-8]       
		mov eax, edx                  
			movq mm4, mm3                 
			movq mm2, mm3                 

			palignr mm4, mm0, 7           

			palignr mm1, mm2, 1           
			movq mm0, mm4                 
			movq mm5, mm1                 

			pavgb mm1, mm4                

			pxor mm4, mm5                 
			movq mm2, mm3                 

			pand mm4, [ff_pb_1]           

		psubusb mm1, mm4              

			pavgb mm2, mm1                
			movq mm4, mm0                 
			movq mm7, mm2                 
			movq mm5, mm3                 

			pavgb mm3, mm0                

			pxor mm0, mm5                 
			movq mm1, mm4                 

			pand mm0, [ff_pb_1]           

		psubusb mm3, mm0              

			pavgb mm1, mm3                

			psllq mm1, 56                 

			palignr mm7, mm1, 7           
			movq mm3, mm7                 
			lea ecx, [eax+ebx*2]          
		movq mm7, mm3                 

			punpckhbw mm3, mm3            

			punpcklbw mm7, mm7            
			pshufw mm0, mm3, 0xff         
			pshufw mm1, mm3, 0xaa         
			lea edx, [ecx+ebx*2]          
		pshufw mm2, mm3, 0x55         
			pshufw mm3, mm3, 0x00         
			pshufw mm4, mm7, 0xff         
			pshufw mm5, mm7, 0xaa         
			pshufw mm6, mm7, 0x55         
			pshufw mm7, mm7, 0x00         
			movq [eax+ebx*1], mm0         
			movq [eax+ebx*2], mm1         
			movq [ecx+ebx*1], mm2         
			movq [ecx+ebx*2], mm3         
			movq [edx+ebx*1], mm4         
			movq [edx+ebx*2], mm5         
			lea eax, [edx+ebx*2]          
		movq [eax+ebx*1], mm6         
			movq [eax+ebx*2], mm7         
			pop ebx                       
			ret                           

	}
}

NAKED void ff_pred8x8l_vertical_mmxext (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                       
			mov eax, [esp + 4 + 4 + 0*4]   
		mov ecx, [esp + 4 + 4 + 1*4]   
		mov edx, [esp + 4 + 4 + 2*4]   
		mov ebx, [esp + 4 + 4 + 3*4]   

		sub eax, ebx                   
			movq mm0, [eax-8]              
		movq mm3, [eax]                
		movq mm1, [eax+8]              
		movq mm2, mm3                  
			movq mm4, mm3                  

			psllq mm2, (8-7)*8             

			psrlq mm0, 7*8                 

			por mm2, mm0                   

			psllq mm1, (8-1)*8             

			psrlq mm4, 1*8                 

			por mm1, mm4                   
			test ecx, ecx                  
			jz ff_pred8x8l_vertical_mmxext__fix_lt_2                   
			test edx, edx                  
			jz ff_pred8x8l_vertical_mmxext__fix_tr_1                   
			jmp ff_pred8x8l_vertical_mmxext__body                      
ff_pred8x8l_vertical_mmxext__fix_lt_2:                      
		movq mm5, mm3                  

			pxor mm5, mm2                  

			psllq mm5, 56                  

			psrlq mm5, 56                  

			pxor mm2, mm5                  
			test edx, edx                  
			jnz ff_pred8x8l_vertical_mmxext__body                      
ff_pred8x8l_vertical_mmxext__fix_tr_1:                      
		movq mm5, mm3                  

			pxor mm5, mm1                  

			psrlq mm5, 56                  

			psllq mm5, 56                  

			pxor mm1, mm5                  
ff_pred8x8l_vertical_mmxext__body:                           
			movq mm5, mm2                  

			pavgb mm2, mm1                 

			pxor mm1, mm5                  
			movq mm0, mm3                  

			pand mm1, [ff_pb_1]            

		psubusb mm2, mm1               

			pavgb mm0, mm2                 
			movq [eax+ebx*1], mm0          
			movq [eax+ebx*2], mm0          
			lea eax, [eax+ebx*2]           
		movq [eax+ebx*1], mm0          
			movq [eax+ebx*2], mm0          
			lea eax, [eax+ebx*2]           
		movq [eax+ebx*1], mm0          
			movq [eax+ebx*2], mm0          
			lea eax, [eax+ebx*2]           
		movq [eax+ebx*1], mm0          
			movq [eax+ebx*2], mm0          
			pop ebx                        
			ret                            

	}
}

NAKED void ff_pred8x8l_vertical_ssse3 (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                      
			mov eax, [esp + 4 + 4 + 0*4]  
		mov ecx, [esp + 4 + 4 + 1*4]  
		mov edx, [esp + 4 + 4 + 2*4]  
		mov ebx, [esp + 4 + 4 + 3*4]  

		sub eax, ebx                  
			movq mm0, [eax-8]             
		movq mm3, [eax]               
		movq mm1, [eax+8]             
		movq mm2, mm3                 
			movq mm4, mm3                 

			palignr mm2, mm0, 7           

			palignr mm1, mm4, 1           
			test ecx, ecx                 
			jz ff_pred8x8l_vertical_ssse3__fix_lt_2                  
			test edx, edx                 
			jz ff_pred8x8l_vertical_ssse3__fix_tr_1                  
			jmp ff_pred8x8l_vertical_ssse3__body                     
ff_pred8x8l_vertical_ssse3__fix_lt_2:                     
		movq mm5, mm3                 

			pxor mm5, mm2                 

			psllq mm5, 56                 

			psrlq mm5, 56                 

			pxor mm2, mm5                 
			test edx, edx                 
			jnz ff_pred8x8l_vertical_ssse3__body                     
ff_pred8x8l_vertical_ssse3__fix_tr_1:                     
		movq mm5, mm3                 

			pxor mm5, mm1                 

			psrlq mm5, 56                 

			psllq mm5, 56                 

			pxor mm1, mm5                 
ff_pred8x8l_vertical_ssse3__body:                          
			movq mm5, mm2                 

			pavgb mm2, mm1                

			pxor mm1, mm5                 
			movq mm0, mm3                 

			pand mm1, [ff_pb_1]           

		psubusb mm2, mm1              

			pavgb mm0, mm2                
			movq [eax+ebx*1], mm0         
			movq [eax+ebx*2], mm0         
			lea eax, [eax+ebx*2]          
		movq [eax+ebx*1], mm0         
			movq [eax+ebx*2], mm0         
			lea eax, [eax+ebx*2]          
		movq [eax+ebx*1], mm0         
			movq [eax+ebx*2], mm0         
			lea eax, [eax+ebx*2]          
		movq [eax+ebx*1], mm0         
			movq [eax+ebx*2], mm0         
			pop ebx                       
			ret                           

	}
}

NAKED void ff_pred8x8l_down_left_mmxext (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm{
		push ebx                                    
			push esi                                    
			mov eax, [esp + 8 + 4 + 0*4]                
		mov ecx, [esp + 8 + 4 + 1*4]                
		mov edx, [esp + 8 + 4 + 2*4]                
		mov ebx, [esp + 8 + 4 + 3*4]                

		;line 1370+1 libavcodec/x86/h264_intrapredadsdmd
			sub eax, ebx                                
			movq mm0, [eax-8]                           
		movq mm3, [eax]                             
		movq mm1, [eax+8]                           
		movq mm2, mm3                               
			movq mm4, mm3                               

			;line 1376+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm2, (8-7)*8                          

			psrlq mm0, 7*8                              

			por mm2, mm0                                
			;line 1377+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1377+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, (8-1)*8                          

			psrlq mm4, 1*8                              

			por mm1, mm4                                
			;line 1378+1 libavcodec/x86/h264_intrapredadsdmd
			test ecx, ecx                               
			jz ff_pred8x8l_down_left_mmxext__fix_lt_2                                
			test edx, edx                               
			jz ff_pred8x8l_down_left_mmxext__fix_tr_1                                
			jmp ff_pred8x8l_down_left_mmxext__do_top                                 
ff_pred8x8l_down_left_mmxext__fix_lt_2:                                   
		movq mm5, mm3                               

			;line 1385+0 libavcodec/x86/h264_intrapredadsdmd
			pxor mm5, mm2                               
			;line 1386+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1386+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm5, 56                               
			;line 1387+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1387+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm5, 56                               
			;line 1388+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1388+0 libavcodec/x86/h264_intrapredadsdmd
			pxor mm2, mm5                               
			;line 1389+1 libavcodec/x86/h264_intrapredadsdmd
			test edx, edx                               
			jnz ff_pred8x8l_down_left_mmxext__do_top                                 
ff_pred8x8l_down_left_mmxext__fix_tr_1:                                   
		movq mm5, mm3                               

			;line 1393+0 libavcodec/x86/h264_intrapredadsdmd
			pxor mm5, mm1                               
			;line 1394+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1394+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm5, 56                               
			;line 1395+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1395+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm5, 56                               
			;line 1396+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1396+0 libavcodec/x86/h264_intrapredadsdmd
			pxor mm1, mm5                               
			;line 1397+1 libavcodec/x86/h264_intrapredadsdmd
			jmp ff_pred8x8l_down_left_mmxext__do_top                                 
ff_pred8x8l_down_left_mmxext__fix_tr_2:                                   

		;line 1399+0 libavcodec/x86/h264_intrapredadsdmd
			punpckhbw mm3, mm3                          
			;line 1400+1 libavcodec/x86/h264_intrapredadsdmd
			pshufw mm1, mm3, 0xFF                       
			jmp ff_pred8x8l_down_left_mmxext__do_topright                            
ff_pred8x8l_down_left_mmxext__do_top:                                     
		movq mm5, mm2                               
			;line 1403+0 libavcodec/x86/h264_intrapredadsdmd

			pavgb mm2, mm1                              

			pxor mm1, mm5                               
			movq mm4, mm3                               

			pand mm1, [ff_pb_1]                         

		psubusb mm2, mm1                            

			pavgb mm4, mm2                              
			;line 1404+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm7, mm4                               
			test edx, edx                               
			jz ff_pred8x8l_down_left_mmxext__fix_tr_2                                
			movq mm0, [eax+8]                           
		movq mm5, mm0                               
			movq mm2, mm0                               
			movq mm4, mm0                               

			;line 1411+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm5, 56                               
			;line 1412+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1412+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm2, (8-7)*8                          

			psrlq mm3, 7*8                              

			por mm2, mm3                                
			;line 1413+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1413+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm5, (8-1)*8                          

			psrlq mm4, 1*8                              

			por mm5, mm4                                
			;line 1414+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm4, mm2                               
			;line 1414+0 libavcodec/x86/h264_intrapredadsdmd

			pavgb mm2, mm5                              

			pxor mm5, mm4                               
			movq mm1, mm0                               

			pand mm5, [ff_pb_1]                         

		psubusb mm2, mm5                            

			pavgb mm1, mm2                              
			;line 1415+1 libavcodec/x86/h264_intrapredadsdmd
ff_pred8x8l_down_left_mmxext__do_topright:                                
		lea ecx, [eax+ebx*2]                        
		movq mm6, mm1                               

			;line 1418+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm1, 56                               
			;line 1419+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm4, mm1                               
			lea edx, [ecx+ebx*2]                        
		movq mm2, mm6                               
			movq mm0, mm7                               
			;line 1422+0 libavcodec/x86/h264_intrapredadsdmd

			psllq mm2, (8-1)*8                          

			psrlq mm0, 1*8                              

			por mm2, mm0                                
			;line 1423+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm3, mm6                               
			movq mm0, mm7                               
			;line 1424+0 libavcodec/x86/h264_intrapredadsdmd

			psllq mm3, (8-7)*8                          

			psrlq mm0, 7*8                              

			por mm3, mm0                                
			;line 1425+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm0, mm6                               
			;line 1425+0 libavcodec/x86/h264_intrapredadsdmd

			psllq mm4, (8-1)*8                          

			psrlq mm0, 1*8                              

			por mm4, mm0                                
			;line 1426+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm5, mm7                               
			movq mm1, mm7                               
			movq mm7, mm6                               
			lea esi, [edx+ebx*2]                        

		;line 1430+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, 8                                
			;line 1431+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm6, mm1                               
			;line 1431+0 libavcodec/x86/h264_intrapredadsdmd

			pavgb mm1, mm2                              

			pxor mm2, mm6                               
			movq mm0, mm5                               

			pand mm2, [ff_pb_1]                         

		psubusb mm1, mm2                            

			pavgb mm0, mm1                              
			;line 1432+1 libavcodec/x86/h264_intrapredadsdmd
			movq mm6, mm3                               
			;line 1432+0 libavcodec/x86/h264_intrapredadsdmd

			pavgb mm3, mm4                              

			pxor mm4, mm6                               
			movq mm1, mm7                               

			pand mm4, [ff_pb_1]                         

		psubusb mm3, mm4                            

			pavgb mm1, mm3                              
			;line 1433+1 libavcodec/x86/h264_intrapredadsdmd
			movq [esi+ebx*2], mm1                       
			movq mm2, mm0                               

			;line 1435+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, 8                                
			;line 1436+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1436+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm2, 56                               
			;line 1437+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1437+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm0, 8                                
			;line 1438+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1438+0 libavcodec/x86/h264_intrapredadsdmd
			por mm1, mm2                                
			;line 1439+1 libavcodec/x86/h264_intrapredadsdmd
			movq [esi+ebx*1], mm1                       
			movq mm2, mm0                               

			;line 1441+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, 8                                
			;line 1442+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1442+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm2, 56                               
			;line 1443+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1443+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm0, 8                                
			;line 1444+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1444+0 libavcodec/x86/h264_intrapredadsdmd
			por mm1, mm2                                
			;line 1445+1 libavcodec/x86/h264_intrapredadsdmd
			movq [edx+ebx*2], mm1                       
			movq mm2, mm0                               

			;line 1447+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, 8                                
			;line 1448+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1448+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm2, 56                               
			;line 1449+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1449+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm0, 8                                
			;line 1450+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1450+0 libavcodec/x86/h264_intrapredadsdmd
			por mm1, mm2                                
			;line 1451+1 libavcodec/x86/h264_intrapredadsdmd
			movq [edx+ebx*1], mm1                       
			movq mm2, mm0                               

			;line 1453+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, 8                                
			;line 1454+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1454+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm2, 56                               
			;line 1455+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1455+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm0, 8                                
			;line 1456+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1456+0 libavcodec/x86/h264_intrapredadsdmd
			por mm1, mm2                                
			;line 1457+1 libavcodec/x86/h264_intrapredadsdmd
			movq [ecx+ebx*2], mm1                       
			movq mm2, mm0                               

			;line 1459+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, 8                                
			;line 1460+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1460+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm2, 56                               
			;line 1461+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1461+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm0, 8                                
			;line 1462+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1462+0 libavcodec/x86/h264_intrapredadsdmd
			por mm1, mm2                                
			;line 1463+1 libavcodec/x86/h264_intrapredadsdmd
			movq [ecx+ebx*1], mm1                       
			movq mm2, mm0                               

			;line 1465+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, 8                                
			;line 1466+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1466+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm2, 56                               
			;line 1467+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1467+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm0, 8                                
			;line 1468+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1468+0 libavcodec/x86/h264_intrapredadsdmd
			por mm1, mm2                                
			;line 1469+1 libavcodec/x86/h264_intrapredadsdmd
			movq [eax+ebx*2], mm1                       

			;line 1470+0 libavcodec/x86/h264_intrapredadsdmd
			psllq mm1, 8                                
			;line 1471+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1471+0 libavcodec/x86/h264_intrapredadsdmd
			psrlq mm0, 56                               
			;line 1472+1 libavcodec/x86/h264_intrapredadsdmd

			;line 1472+0 libavcodec/x86/h264_intrapredadsdmd
			por mm1, mm0                                
			;line 1473+1 libavcodec/x86/h264_intrapredadsdmd
			movq [eax+ebx*1], mm1                       
			pop esi                                     
			;line 1474+0 libavcodec/x86/h264_intrapredadsdmd
			pop ebx                                     
			ret                                         

	}
}

NAKED void ff_pred8x8l_down_left_sse2 (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                        
			mov eax, [esp + 4 + 4 + 0*4]    
		mov ecx, [esp + 4 + 4 + 1*4]    
		mov edx, [esp + 4 + 4 + 2*4]    
		mov ebx, [esp + 4 + 4 + 3*4]    

		sub eax, ebx                    
			movq mm0, [eax-8]               
		movq mm3, [eax]                 
		movq mm1, [eax+8]               
		movq mm2, mm3                   
			movq mm4, mm3                   

			psllq mm2, (8-7)*8              

			psrlq mm0, 7*8                  

			por mm2, mm0                    

			psllq mm1, (8-1)*8              

			psrlq mm4, 1*8                  

			por mm1, mm4                    
			test ecx, ecx                   
			jz ff_pred8x8l_down_left_sse2__fix_lt_2                    
			test edx, edx                   
			jz ff_pred8x8l_down_left_sse2__fix_tr_1                    
			jmp ff_pred8x8l_down_left_sse2__do_top                     
ff_pred8x8l_down_left_sse2__fix_lt_2:                       
		movq mm5, mm3                   

			pxor mm5, mm2                   

			psllq mm5, 56                   

			psrlq mm5, 56                   

			pxor mm2, mm5                   
			test edx, edx                   
			jnz ff_pred8x8l_down_left_sse2__do_top                     
ff_pred8x8l_down_left_sse2__fix_tr_1:                       
		movq mm5, mm3                   

			pxor mm5, mm1                   

			psrlq mm5, 56                   

			psllq mm5, 56                   

			pxor mm1, mm5                   
			jmp ff_pred8x8l_down_left_sse2__do_top                     
ff_pred8x8l_down_left_sse2__fix_tr_2:                       

		punpckhbw mm3, mm3              
			pshufw mm1, mm3, 0xFF           
			jmp ff_pred8x8l_down_left_sse2__do_topright                
ff_pred8x8l_down_left_sse2__do_top:                         
		movq mm5, mm2                   

			pavgb mm2, mm1                  

			pxor mm1, mm5                   
			movq mm4, mm3                   

			pand mm1, [ff_pb_1]             

		psubusb mm2, mm1                

			pavgb mm4, mm2                  
			movq2dq xmm3, mm4               
			test edx, edx                   
			jz ff_pred8x8l_down_left_sse2__fix_tr_2                    
			movq mm0, [eax+8]               
		movq mm5, mm0                   
			movq mm2, mm0                   
			movq mm4, mm0                   

			psrlq mm5, 56                   

			psllq mm2, (8-7)*8              

			psrlq mm3, 7*8                  

			por mm2, mm3                    

			psllq mm5, (8-1)*8              

			psrlq mm4, 1*8                  

			por mm5, mm4                    
			movq mm4, mm2                   

			pavgb mm2, mm5                  

			pxor mm5, mm4                   
			movq mm1, mm0                   

			pand mm5, [ff_pb_1]             

		psubusb mm2, mm5                

			pavgb mm1, mm2                  
ff_pred8x8l_down_left_sse2__do_topright:                    
		movq2dq xmm4, mm1               

			psrlq mm1, 56                   
			movq2dq xmm5, mm1               
			lea ecx, [eax+ebx*2]            

		pslldq xmm4, 8                  

			por xmm3, xmm4                  
			movdqa xmm2, xmm3               

			psrldq xmm2, 1                  

			pslldq xmm5, 15                 

			por xmm2, xmm5                  
			lea edx, [ecx+ebx*2]            
		movdqa xmm1, xmm3               

			pslldq xmm1, 1                  
			movdqa xmm4, xmm1               

			pavgb xmm1, xmm2                

			pxor xmm2, xmm4                 
			movdqa xmm0, xmm3               

			pand xmm2, [ff_pb_1]            

		psubusb xmm1, xmm2              

			pavgb xmm0, xmm1                

			psrldq xmm0, 1                  
			movq qword ptr[eax+ebx*1], xmm0          

			psrldq xmm0, 1                  
			movq qword ptr[eax+ebx*2], xmm0          

			psrldq xmm0, 1                  
			lea eax, [edx+ebx*2]            
		movq qword ptr[ecx+ebx*1], xmm0          

			psrldq xmm0, 1                  
			movq qword ptr[ecx+ebx*2], xmm0          

			psrldq xmm0, 1                  
			movq qword ptr [edx+ebx*1], xmm0          

			psrldq xmm0, 1                  
			movq  qword ptr [edx+ebx*2], xmm0          

			psrldq xmm0, 1                  
			movq  qword ptr [eax+ebx*1], xmm0          

			psrldq xmm0, 1                  
			movq  qword ptr [eax+ebx*2], xmm0          
			pop ebx                         
			ret                             

	}
}

NAKED void ff_pred8x8l_down_left_ssse3 (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                                              
			mov eax, [esp + 4 + 4 + 0*4]                          
		mov ecx, [esp + 4 + 4 + 1*4]                          
		mov edx, [esp + 4 + 4 + 2*4]                          
		mov ebx, [esp + 4 + 4 + 3*4]                          

		sub eax, ebx                                          
			movq mm0, [eax-8]                                     
		movq mm3, [eax]                                       
		movq mm1, [eax+8]                                     
		movq mm2, mm3                                         
			movq mm4, mm3                                         

			palignr mm2, mm0, 7                                   

			palignr mm1, mm4, 1                                   
			test ecx, ecx                                         
			jz ff_pred8x8l_down_left_ssse3__fix_lt_2                                          
			test edx, edx                                         
			jz ff_pred8x8l_down_left_ssse3__fix_tr_1                                          
			jmp ff_pred8x8l_down_left_ssse3__do_top                                           
ff_pred8x8l_down_left_ssse3__fix_lt_2:                                             
		movq mm5, mm3                                         

			pxor mm5, mm2                                         

			psllq mm5, 56                                         

			psrlq mm5, 56                                         

			pxor mm2, mm5                                         
			test edx, edx                                         
			jnz ff_pred8x8l_down_left_ssse3__do_top                                           
ff_pred8x8l_down_left_ssse3__fix_tr_1:                                             
		movq mm5, mm3                                         

			pxor mm5, mm1                                         

			psrlq mm5, 56                                         

			psllq mm5, 56                                         

			pxor mm1, mm5                                         
			jmp ff_pred8x8l_down_left_ssse3__do_top                                           
ff_pred8x8l_down_left_ssse3__fix_tr_2:                                             

		punpckhbw mm3, mm3                                    
			pshufw mm1, mm3, 0xFF                                 
			jmp ff_pred8x8l_down_left_ssse3__do_topright                                      
ff_pred8x8l_down_left_ssse3__do_top:                                               
		movq mm5, mm2                                         

			pavgb mm2, mm1                                        

			pxor mm1, mm5                                         
			movq mm4, mm3                                         

			pand mm1, [ff_pb_1]                                   

		psubusb mm2, mm1                                      

			pavgb mm4, mm2                                        
			movq2dq xmm3, mm4                                     
			test edx, edx                                         
			jz ff_pred8x8l_down_left_ssse3__fix_tr_2                                          
			movq mm0, [eax+8]                                     
		movq mm5, mm0                                         
			movq mm2, mm0                                         
			movq mm4, mm0                                         

			psrlq mm5, 56                                         

			palignr mm2, mm3, 7                                   

			palignr mm5, mm4, 1                                   
			movq mm4, mm2                                         

			pavgb mm2, mm5                                        

			pxor mm5, mm4                                         
			movq mm1, mm0                                         

			pand mm5, [ff_pb_1]                                   

		psubusb mm2, mm5                                      

			pavgb mm1, mm2                                        
ff_pred8x8l_down_left_ssse3__do_topright:                                          
		movq2dq xmm4, mm1                                     

			psrlq mm1, 56                                         
			movq2dq xmm5, mm1                                     
			lea ecx, [eax+ebx*2]                                  

		pslldq xmm4, 8                                        

			por xmm3, xmm4                                        
			movdqa xmm2, xmm3                                     

			psrldq xmm2, 1                                        

			pslldq xmm5, 15                                       

			por xmm2, xmm5                                        
			lea edx, [ecx+ebx*2]                                  
		movdqa xmm1, xmm3                                     

			pslldq xmm1, 1                                        
			movdqa xmm4, xmm1                                     

			pavgb xmm1, xmm2                                      

			pxor xmm2, xmm4                                       
			movdqa xmm0, xmm3                                     

			pand xmm2, [ff_pb_1]                                  

		psubusb xmm1, xmm2                                    

			pavgb xmm0, xmm1                                      

			psrldq xmm0, 1                                        
			movq  qword ptr [eax+ebx*1], xmm0                                

			psrldq xmm0, 1                                        
			movq  qword ptr [eax+ebx*2], xmm0                                

			psrldq xmm0, 1                                        
			lea eax, [edx+ebx*2]                                  
		movq  qword ptr [ecx+ebx*1], xmm0                                

			psrldq xmm0, 1                                        
			movq  qword ptr [ecx+ebx*2], xmm0                                

			psrldq xmm0, 1                                        
			movq  qword ptr [edx+ebx*1], xmm0                                

			psrldq xmm0, 1                                        
			movq  qword ptr [edx+ebx*2], xmm0                                

			psrldq xmm0, 1                                        
			movq  qword ptr [eax+ebx*1], xmm0                                

			psrldq xmm0, 1                                        
			movq  qword ptr [eax+ebx*2], xmm0                                
			pop ebx                                               
			ret                                                   

	}
}

NAKED void ff_pred8x8l_down_right_mmxext (uint8_t *src, int has_topleft, int has_topright, int stride)
{
    __asm {
        push   ebx                                     
            push   esi                                     
            mov    eax,DWORD PTR [esp+0xc]                 
        mov    ecx,DWORD PTR [esp+0x10]                
        mov    edx,DWORD PTR [esp+0x14]                
        mov    ebx,DWORD PTR [esp+0x18]                
        sub    eax,ebx                                 
            lea    esi,[eax+ebx*2]                         
        movq   mm0,QWORD PTR [eax+ebx*1-0x8]           
        punpckhbw mm0,QWORD PTR [eax-0x8]              
        movq   mm1,QWORD PTR [esi+ebx*1-0x8]           
        punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8]        
        mov    esi,eax                                 
            punpckhwd mm1,mm0                              
            lea    eax,[eax+ebx*4]                         
        movq   mm2,QWORD PTR [eax+ebx*1-0x8]           
        punpckhbw mm2,QWORD PTR [eax-0x8]              
        lea    eax,[eax+ebx*2]                         
        movq   mm3,QWORD PTR [eax+ebx*1-0x8]           
        punpckhbw mm3,QWORD PTR [eax-0x8]              
        punpckhwd mm3,mm2                              
            punpckhdq mm3,mm1                              
            lea    eax,[eax+ebx*2]                         
        movq   mm0,QWORD PTR [eax-0x8]                 
        movq   mm1,QWORD PTR [esi]                     
        mov    eax,esi                                 
            movq   mm4,mm3                                 
            movq   mm2,mm3                                 
            psllq  mm4,0x8                                 
            psrlq  mm0,0x38                                
            por    mm4,mm0                                 
            psllq  mm1,0x38                                
            psrlq  mm2,0x8                                 
            por    mm1,mm2                                 
            test   ecx,ecx                                 
            je     ff_pred8x8l_down_right_mmxext_fix_lt_1  

ff_pred8x8l_down_right_mmxext_do_left:         
        movq   mm0,mm4                                 
            movq   mm5,mm1                                 
            pavgb  mm1,mm4                                 
            pxor   mm4,mm5                                 
            movq   mm2,mm3                                 
            pand   mm4,QWORD PTR [ff_pb_1]                 
        psubusb mm1,mm4                                
            pavgb  mm2,mm1                                 
            movq   mm4,mm0                                 
            movq   mm7,mm2                                 
            movq   mm6,mm2                                 
            movq   mm5,mm3                                 
            pavgb  mm3,mm0                                 
            pxor   mm0,mm5                                 
            movq   mm1,mm4                                 
            pand   mm0,QWORD PTR [ff_pb_1]                 
        psubusb mm3,mm0                                
            pavgb  mm1,mm3                                 
            psllq  mm1,0x38                                
            movq   mm3,mm1                                 
            psllq  mm7,0x8                                 
            psrlq  mm3,0x38                                
            por    mm7,mm3                                 
            movq   mm0,QWORD PTR [eax-0x8]                 
        movq   mm3,QWORD PTR [eax]                     
        movq   mm1,QWORD PTR [eax+0x8]                 
        movq   mm2,mm3                                 
            movq   mm4,mm3                                 
            psllq  mm2,0x8                                 
            psrlq  mm0,0x38                                
            por    mm2,mm0                                 
            psllq  mm1,0x38                                
            psrlq  mm4,0x8                                 
            por    mm1,mm4                                 
            test   ecx,ecx                                 
            je     ff_pred8x8l_down_right_mmxext_fix_lt_2  
            test   edx,edx                                 
            je     ff_pred8x8l_down_right_mmxext_fix_tr_1  

ff_pred8x8l_down_right_mmxext_do_top:          
        movq   mm5,mm2                                 
            pavgb  mm2,mm1                                 
            pxor   mm1,mm5                                 
            movq   mm4,mm3                                 
            pand   mm1,QWORD PTR [ff_pb_1]                 
        psubusb mm2,mm1                                
            pavgb  mm4,mm2                                 
            movq   mm5,mm4                                 
            jmp    ff_pred8x8l_down_right_mmxext_body      

ff_pred8x8l_down_right_mmxext_fix_lt_1:        
        movq   mm5,mm3                                 
            pxor   mm5,mm4                                 
            psrlq  mm5,0x38                                
            psllq  mm5,0x30                                
            pxor   mm1,mm5                                 
            jmp    ff_pred8x8l_down_right_mmxext_do_left   

ff_pred8x8l_down_right_mmxext_fix_lt_2:        
        movq   mm5,mm3                                 
            pxor   mm5,mm2                                 
            psllq  mm5,0x38                                
            psrlq  mm5,0x38                                
            pxor   mm2,mm5                                 
            test   edx,edx                                 
            jne    ff_pred8x8l_down_right_mmxext_do_top    

ff_pred8x8l_down_right_mmxext_fix_tr_1:        
        movq   mm5,mm3                                 
            pxor   mm5,mm1                                 
            psrlq  mm5,0x38                                
            psllq  mm5,0x38                                
            pxor   mm1,mm5                                 
            jmp    ff_pred8x8l_down_right_mmxext_do_top    

ff_pred8x8l_down_right_mmxext_body:            
        lea    ecx,[eax+ebx*2]                         
        movq   mm1,mm7                                 
            movq   mm7,mm5                                 
            movq   mm5,mm6                                 
            movq   mm2,mm7                                 
            lea    edx,[ecx+ebx*2]                         
        movq   mm0,mm6                                 
            psllq  mm2,0x38                                
            psrlq  mm0,0x8                                 
            por    mm2,mm0                                 
            movq   mm3,mm7                                 
            movq   mm0,mm6                                 
            psllq  mm3,0x8                                 
            psrlq  mm0,0x38                                
            por    mm3,mm0                                 
            movq   mm4,mm7                                 
            lea    esi,[edx+ebx*2]                         
        psrlq  mm4,0x8                                 
            movq   mm6,mm1                                 
            pavgb  mm1,mm2                                 
            pxor   mm2,mm6                                 
            movq   mm0,mm5                                 
            pand   mm2,QWORD PTR [ff_pb_1]                 
        psubusb mm1,mm2                                
            pavgb  mm0,mm1                                 
            movq   mm6,mm3                                 
            pavgb  mm3,mm4                                 
            pxor   mm4,mm6                                 
            movq   mm1,mm7                                 
            pand   mm4,QWORD PTR [ff_pb_1]                 
        psubusb mm3,mm4                                
            pavgb  mm1,mm3                                 
            movq   QWORD PTR [esi+ebx*2],mm0               
            movq   mm2,mm1                                 
            psrlq  mm0,0x8                                 
            psllq  mm2,0x38                                
            psrlq  mm1,0x8                                 
            por    mm0,mm2                                 
            movq   QWORD PTR [esi+ebx*1],mm0               
            movq   mm2,mm1                                 
            psrlq  mm0,0x8                                 
            psllq  mm2,0x38                                
            psrlq  mm1,0x8                                 
            por    mm0,mm2                                 
            movq   QWORD PTR [edx+ebx*2],mm0               
            movq   mm2,mm1                                 
            psrlq  mm0,0x8                                 
            psllq  mm2,0x38                                
            psrlq  mm1,0x8                                 
            por    mm0,mm2                                 
            movq   QWORD PTR [edx+ebx*1],mm0               
            movq   mm2,mm1                                 
            psrlq  mm0,0x8                                 
            psllq  mm2,0x38                                
            psrlq  mm1,0x8                                 
            por    mm0,mm2                                 
            movq   QWORD PTR [ecx+ebx*2],mm0               
            movq   mm2,mm1                                 
            psrlq  mm0,0x8                                 
            psllq  mm2,0x38                                
            psrlq  mm1,0x8                                 
            por    mm0,mm2                                 
            movq   QWORD PTR [ecx+ebx*1],mm0               
            movq   mm2,mm1                                 
            psrlq  mm0,0x8                                 
            psllq  mm2,0x38                                
            psrlq  mm1,0x8                                 
            por    mm0,mm2                                 
            movq   QWORD PTR [eax+ebx*2],mm0               
            psrlq  mm0,0x8                                 
            psllq  mm1,0x38                                
            por    mm0,mm1                                 
            movq   QWORD PTR [eax+ebx*1],mm0               
            pop    esi                                     
            pop    ebx                                     
            ret                                            

    }
}

NAKED void ff_pred8x8l_down_right_sse2 (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
        push   ebx                                   
            push   esi                                   
            mov    eax,DWORD PTR [esp+0xc]               
        mov    ecx,DWORD PTR [esp+0x10]              
        mov    edx,DWORD PTR [esp+0x14]              
        mov    ebx,DWORD PTR [esp+0x18]              
        sub    eax,ebx                               
            lea    esi,[eax+ebx*2]                       
        movq   mm0,QWORD PTR [eax+ebx*1-0x8]         
        punpckhbw mm0,QWORD PTR [eax-0x8]            
        movq   mm1,QWORD PTR [esi+ebx*1-0x8]         
        punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8]      
        mov    esi,eax                               
            punpckhwd mm1,mm0                            
            lea    eax,[eax+ebx*4]                       
        movq   mm2,QWORD PTR [eax+ebx*1-0x8]         
        punpckhbw mm2,QWORD PTR [eax-0x8]            
        lea    eax,[eax+ebx*2]                       
        movq   mm3,QWORD PTR [eax+ebx*1-0x8]         
        punpckhbw mm3,QWORD PTR [eax-0x8]            
        punpckhwd mm3,mm2                            
            punpckhdq mm3,mm1                            
            lea    eax,[eax+ebx*2]                       
        movq   mm0,QWORD PTR [eax-0x8]               
        movq   mm1,QWORD PTR [esi]                   
        mov    eax,esi                               
            movq   mm4,mm3                               
            movq   mm2,mm3                               
            psllq  mm4,0x8                               
            psrlq  mm0,0x38                              
            por    mm4,mm0                               
            psllq  mm1,0x38                              
            psrlq  mm2,0x8                               
            por    mm1,mm2                               
            test   ecx,ecx                               
            je     ff_pred8x8l_down_right_sse2_fix_lt_1  
            jmp    ff_pred8x8l_down_right_sse2_do_left   

ff_pred8x8l_down_right_sse2_fix_lt_1:        
        movq   mm5,mm3                               
            pxor   mm5,mm4                               
            psrlq  mm5,0x38                              
            psllq  mm5,0x30                              
            pxor   mm1,mm5                               
            jmp    ff_pred8x8l_down_right_sse2_do_left   

ff_pred8x8l_down_right_sse2_fix_lt_2:        
        movq   mm5,mm3                               
            pxor   mm5,mm2                               
            psllq  mm5,0x38                              
            psrlq  mm5,0x38                              
            pxor   mm2,mm5                               
            test   edx,edx                               
            jne    ff_pred8x8l_down_right_sse2_do_top    

ff_pred8x8l_down_right_sse2_fix_tr_1:        
        movq   mm5,mm3                               
            pxor   mm5,mm1                               
            psrlq  mm5,0x38                              
            psllq  mm5,0x38                              
            pxor   mm1,mm5                               
            jmp    ff_pred8x8l_down_right_sse2_do_top    

ff_pred8x8l_down_right_sse2_do_left:         
        movq   mm0,mm4                               
            movq   mm5,mm1                               
            pavgb  mm1,mm4                               
            pxor   mm4,mm5                               
            movq   mm2,mm3                               
            pand   mm4,QWORD PTR [ff_pb_1]               
        psubusb mm1,mm4                              
            pavgb  mm2,mm1                               
            movq   mm4,mm0                               
            movq   mm7,mm2                               
            movq2dq xmm3,mm2                             
            movq   mm5,mm3                               
            pavgb  mm3,mm0                               
            pxor   mm0,mm5                               
            movq   mm1,mm4                               
            pand   mm0,QWORD PTR [ff_pb_1]               
        psubusb mm3,mm0                              
            pavgb  mm1,mm3                               
            psllq  mm1,0x38                              
            movq   mm3,mm1                               
            psllq  mm7,0x8                               
            psrlq  mm3,0x38                              
            por    mm7,mm3                               
            movq2dq xmm1,mm7                             
            movq   mm0,QWORD PTR [eax-0x8]               
        movq   mm3,QWORD PTR [eax]                   
        movq   mm1,QWORD PTR [eax+0x8]               
        movq   mm2,mm3                               
            movq   mm4,mm3                               
            psllq  mm2,0x8                               
            psrlq  mm0,0x38                              
            por    mm2,mm0                               
            psllq  mm1,0x38                              
            psrlq  mm4,0x8                               
            por    mm1,mm4                               
            test   ecx,ecx                               
            je     ff_pred8x8l_down_right_sse2_fix_lt_2  
            test   edx,edx                               
            je     ff_pred8x8l_down_right_sse2_fix_tr_1  

ff_pred8x8l_down_right_sse2_do_top:          
        movq   mm5,mm2                               
            pavgb  mm2,mm1                               
            pxor   mm1,mm5                               
            movq   mm4,mm3                               
            pand   mm1,QWORD PTR [ff_pb_1]               
        psubusb mm2,mm1                              
            pavgb  mm4,mm2                               
            movq2dq xmm4,mm4                             
            lea    ecx,[eax+ebx*2]                       
        movdqa xmm0,xmm3                             
            pslldq xmm4,0x8                              
            por    xmm3,xmm4                             
            lea    edx,[ecx+ebx*2]                       
        pslldq xmm4,0x1                              
            por    xmm1,xmm4                             
            psrldq xmm0,0x7                              
            pslldq xmm0,0xf                              
            psrldq xmm0,0x7                              
            por    xmm1,xmm0                             
            lea    eax,[edx+ebx*2]                       
        movdqa xmm2,xmm3                             
            psrldq xmm2,0x1                              
            movdqa xmm4,xmm1                             
            pavgb  xmm1,xmm2                             
            pxor   xmm2,xmm4                             
            movdqa xmm0,xmm3                             
            pand   xmm2,XMMWORD PTR [ff_pb_1]            

        psubusb xmm1,xmm2                            
            pavgb  xmm0,xmm1                             
            movdqa xmm1,xmm0                             
            psrldq xmm1,0x1                              
            movq   QWORD PTR [eax+ebx*2],xmm0            
            movq   QWORD PTR [eax+ebx*1],xmm1            
            psrldq xmm0,0x2                              
            psrldq xmm1,0x2                              
            movq   QWORD PTR [edx+ebx*2],xmm0            
            movq   QWORD PTR [edx+ebx*1],xmm1            
            psrldq xmm0,0x2                              
            psrldq xmm1,0x2                              
            movq   QWORD PTR [ecx+ebx*2],xmm0            
            movq   QWORD PTR [ecx+ebx*1],xmm1            
            psrldq xmm0,0x2                              
            psrldq xmm1,0x2                              
            movq   QWORD PTR [esi+ebx*2],xmm0            
            movq   QWORD PTR [esi+ebx*1],xmm1            
            pop    esi                                   
            pop    ebx                                   
            ret                                          

    }
}

NAKED void ff_pred8x8l_down_right_ssse3 (uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                           
			push esi                           
			mov eax, [esp + 8 + 4 + 0*4]       
		mov ecx, [esp + 8 + 4 + 1*4]       
		mov edx, [esp + 8 + 4 + 2*4]       
		mov ebx, [esp + 8 + 4 + 3*4]       

		sub eax, ebx                       
			lea esi, [eax+ebx*2]               
		movq mm0, [eax+ebx*1-8]            

		punpckhbw mm0, [eax+ebx*0-8]       
		movq mm1, [esi+ebx*1-8]            

		punpckhbw mm1, [eax+ebx*2-8]       
		mov esi, eax                       

			punpckhwd mm1, mm0                 
			lea eax, [eax+ebx*4]               
		movq mm2, [eax+ebx*1-8]            

		punpckhbw mm2, [eax+ebx*0-8]       
		lea eax, [eax+ebx*2]               
		movq mm3, [eax+ebx*1-8]            

		punpckhbw mm3, [eax+ebx*0-8]       

		punpckhwd mm3, mm2                 

			punpckhdq mm3, mm1                 
			lea eax, [eax+ebx*2]               
		movq mm0, [eax+ebx*0-8]            
		movq mm1, [esi]                    
		mov eax, esi                       
			movq mm4, mm3                      
			movq mm2, mm3                      

			palignr mm4, mm0, 7                

			palignr mm1, mm2, 1                
			test ecx, ecx                      
			jz  ff_pred8x8l_down_right_ssse3__fix_lt_1                       
			jmp  ff_pred8x8l_down_right_ssse3__do_left                       
ff_pred8x8l_down_right_ssse3__fix_lt_1:                          
		movq mm5, mm3                      

			pxor mm5, mm4                      

			psrlq mm5, 56                      

			psllq mm5, 48                      

			pxor mm1, mm5                      
			jmp  ff_pred8x8l_down_right_ssse3__do_left                       
ff_pred8x8l_down_right_ssse3__fix_lt_2:                          
		movq mm5, mm3                      

			pxor mm5, mm2                      

			psllq mm5, 56                      

			psrlq mm5, 56                      

			pxor mm2, mm5                      
			test edx, edx                      
			jnz  ff_pred8x8l_down_right_ssse3__do_top                        
ff_pred8x8l_down_right_ssse3__fix_tr_1:                          
		movq mm5, mm3                      

			pxor mm5, mm1                      

			psrlq mm5, 56                      

			psllq mm5, 56                      

			pxor mm1, mm5                      
			jmp  ff_pred8x8l_down_right_ssse3__do_top                        
ff_pred8x8l_down_right_ssse3__do_left:                           
		movq mm0, mm4                      
			movq mm5, mm1                      

			pavgb mm1, mm4                     

			pxor mm4, mm5                      
			movq mm2, mm3                      

			pand mm4, [ff_pb_1]                

		psubusb mm1, mm4                   

			pavgb mm2, mm1                     
			movq mm4, mm0                      
			movq mm7, mm2                      
			movq2dq xmm3, mm2                  
			movq mm5, mm3                      

			pavgb mm3, mm0                     

			pxor mm0, mm5                      
			movq mm1, mm4                      

			pand mm0, [ff_pb_1]                

		psubusb mm3, mm0                   

			pavgb mm1, mm3                     

			psllq mm1, 56                      

			palignr mm7, mm1, 7                
			movq2dq xmm1, mm7                  
			movq mm0, [eax-8]                  
		movq mm3, [eax]                    
		movq mm1, [eax+8]                  
		movq mm2, mm3                      
			movq mm4, mm3                      

			palignr mm2, mm0, 7                

			palignr mm1, mm4, 1                
			test ecx, ecx                      
			jz  ff_pred8x8l_down_right_ssse3__fix_lt_2                       
			test edx, edx                      
			jz  ff_pred8x8l_down_right_ssse3__fix_tr_1                       
ff_pred8x8l_down_right_ssse3__do_top:                            
		movq mm5, mm2                      

			pavgb mm2, mm1                     

			pxor mm1, mm5                      
			movq mm4, mm3                      

			pand mm1, [ff_pb_1]                

		psubusb mm2, mm1                   

			pavgb mm4, mm2                     
			movq2dq xmm4, mm4                  
			lea ecx, [eax+ebx*2]               
		movdqa xmm0, xmm3                  

			pslldq xmm4, 8                     

			por xmm3, xmm4                     
			lea edx, [ecx+ebx*2]               

		pslldq xmm4, 1                     

			por xmm1, xmm4                     

			psrldq xmm0, 7                     

			pslldq xmm0, 15                    

			psrldq xmm0, 7                     

			por xmm1, xmm0                     
			lea eax, [edx+ebx*2]               
		movdqa xmm2, xmm3                  

			psrldq xmm2, 1                     
			movdqa xmm4, xmm1                  

			pavgb xmm1, xmm2                   

			pxor xmm2, xmm4                    
			movdqa xmm0, xmm3                  

			pand xmm2, [ff_pb_1]               

		psubusb xmm1, xmm2                 

			pavgb xmm0, xmm1                   
			movdqa xmm1, xmm0                  

			psrldq xmm1, 1                     
			movq  qword ptr [eax+ebx*2], xmm0             
			movq  qword ptr [eax+ebx*1], xmm1             

			psrldq xmm0, 2                     

			psrldq xmm1, 2                     
			movq  qword ptr [edx+ebx*2], xmm0             
			movq  qword ptr [edx+ebx*1], xmm1             

			psrldq xmm0, 2                     

			psrldq xmm1, 2                     
			movq  qword ptr [ecx+ebx*2], xmm0             
			movq  qword ptr [ecx+ebx*1], xmm1             

			psrldq xmm0, 2                     

			psrldq xmm1, 2                     
			movq  qword ptr [esi+ebx*2], xmm0             
			movq  qword ptr [esi+ebx*1], xmm1             
			pop esi                            
			pop ebx                            
			ret                                

	}
}

NAKED void ff_pred8x8l_vertical_right_mmxext(uint8_t *src, int has_topleft, int has_topright, int stride)
{
    __asm {
        push   ebx                                         
            push   esi                                         
            mov    eax,DWORD PTR [esp+0xc]                     
        mov    ecx,DWORD PTR [esp+0x10]                    
        mov    edx,DWORD PTR [esp+0x14]                    
        mov    ebx,DWORD PTR [esp+0x18]                    
        sub    eax,ebx                                     
            lea    esi,[eax+ebx*2]                             
        movq   mm0,QWORD PTR [eax+ebx*1-0x8]               
        punpckhbw mm0,QWORD PTR [eax-0x8]                  
        movq   mm1,QWORD PTR [esi+ebx*1-0x8]               
        punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8]            
        mov    esi,eax                                     
            punpckhwd mm1,mm0                                  
            lea    eax,[eax+ebx*4]                             
        movq   mm2,QWORD PTR [eax+ebx*1-0x8]               
        punpckhbw mm2,QWORD PTR [eax-0x8]                  
        lea    eax,[eax+ebx*2]                             
        movq   mm3,QWORD PTR [eax+ebx*1-0x8]               
        punpckhbw mm3,QWORD PTR [eax-0x8]                  
        punpckhwd mm3,mm2                                  
            punpckhdq mm3,mm1                                  
            lea    eax,[eax+ebx*2]                             
        movq   mm0,QWORD PTR [eax-0x8]                     
        movq   mm1,QWORD PTR [esi]                         
        mov    eax,esi                                     
            movq   mm4,mm3                                     
            movq   mm2,mm3                                     
            psllq  mm4,0x8                                     
            psrlq  mm0,0x38                                    
            por    mm4,mm0                                     
            psllq  mm1,0x38                                    
            psrlq  mm2,0x8                                     
            por    mm1,mm2                                     
            test   ecx,ecx                                     
            je     ff_pred8x8l_vertical_right_mmxext_fix_lt_1  
            jmp    ff_pred8x8l_vertical_right_mmxext_do_left   

ff_pred8x8l_vertical_right_mmxext_fix_lt_1:        
        movq   mm5,mm3                                     
            pxor   mm5,mm4                                     
            psrlq  mm5,0x38                                    
            psllq  mm5,0x30                                    
            pxor   mm1,mm5                                     
            jmp    ff_pred8x8l_vertical_right_mmxext_do_left   

ff_pred8x8l_vertical_right_mmxext_fix_lt_2:        
        movq   mm5,mm3                                     
            pxor   mm5,mm2                                     
            psllq  mm5,0x38                                    
            psrlq  mm5,0x38                                    
            pxor   mm2,mm5                                     
            test   edx,edx                                     
            jne    ff_pred8x8l_vertical_right_mmxext_do_top    

ff_pred8x8l_vertical_right_mmxext_fix_tr_1:        
        movq   mm5,mm3                                     
            pxor   mm5,mm1                                     
            psrlq  mm5,0x38                                    
            psllq  mm5,0x38                                    
            pxor   mm1,mm5                                     
            jmp    ff_pred8x8l_vertical_right_mmxext_do_top    

ff_pred8x8l_vertical_right_mmxext_do_left:         
        movq   mm0,mm4                                     
            movq   mm5,mm1                                     
            pavgb  mm1,mm4                                     
            pxor   mm4,mm5                                     
            movq   mm2,mm3                                     
            pand   mm4,QWORD PTR [ff_pb_1]                     
        psubusb mm1,mm4                                    
            pavgb  mm2,mm1                                     
            movq   mm7,mm2                                     
            movq   mm0,QWORD PTR [eax-0x8]                     
        movq   mm3,QWORD PTR [eax]                         
        movq   mm1,QWORD PTR [eax+0x8]                     
        movq   mm2,mm3                                     
            movq   mm4,mm3                                     
            psllq  mm2,0x8                                     
            psrlq  mm0,0x38                                    
            por    mm2,mm0                                     
            psllq  mm1,0x38                                    
            psrlq  mm4,0x8                                     
            por    mm1,mm4                                     
            test   ecx,ecx                                     
            je     ff_pred8x8l_vertical_right_mmxext_fix_lt_2  
            test   edx,edx                                     
            je     ff_pred8x8l_vertical_right_mmxext_fix_tr_1  

ff_pred8x8l_vertical_right_mmxext_do_top:          
        movq   mm5,mm2                                     
            pavgb  mm2,mm1                                     
            pxor   mm1,mm5                                     
            movq   mm6,mm3                                     
            pand   mm1,QWORD PTR [ff_pb_1]                     
        psubusb mm2,mm1                                    
            pavgb  mm6,mm2                                     
            lea    ecx,[eax+ebx*2]                             
        movq   mm2,mm6                                     
            movq   mm3,mm6                                     
            movq   mm0,mm7                                     
            psllq  mm3,0x8                                     
            psrlq  mm0,0x38                                    
            por    mm3,mm0                                     
            movq   mm1,mm7                                     
            psllq  mm6,0x10                                    
            psrlq  mm1,0x30                                    
            por    mm6,mm1                                     
            movq   mm4,mm3                                     
            pavgb  mm3,mm2                                     
            lea    edx,[ecx+ebx*2]                             
        movq   mm5,mm6                                     
            pavgb  mm6,mm2                                     
            pxor   mm2,mm5                                     
            movq   mm0,mm4                                     
            pand   mm2,QWORD PTR [ff_pb_1]                     
        psubusb mm6,mm2                                    
            pavgb  mm0,mm6                                     
            movq   QWORD PTR [eax+ebx*1],mm3                   
            movq   QWORD PTR [eax+ebx*2],mm0                   
            movq   mm5,mm0                                     
            movq   mm6,mm3                                     
            movq   mm1,mm7                                     
            movq   mm2,mm1                                     
            psllq  mm2,0x8                                     
            movq   mm3,mm1                                     
            psllq  mm3,0x10                                    
            lea    esi,[edx+ebx*2]                             
        movq   mm4,mm1                                     
            pavgb  mm1,mm3                                     
            pxor   mm3,mm4                                     
            movq   mm0,mm2                                     
            pand   mm3,QWORD PTR [ff_pb_1]                     
        psubusb mm1,mm3                                    
            pavgb  mm0,mm1                                     
            movq   mm2,mm0                                     
            psllq  mm6,0x8                                     
            psrlq  mm2,0x38                                    
            por    mm6,mm2                                     
            movq   QWORD PTR [ecx+ebx*1],mm6                   
            psllq  mm0,0x8                                     
            movq   mm1,mm0                                     
            psllq  mm5,0x8                                     
            psrlq  mm1,0x38                                    
            por    mm5,mm1                                     
            movq   QWORD PTR [ecx+ebx*2],mm5                   
            psllq  mm0,0x8                                     
            movq   mm2,mm0                                     
            psllq  mm6,0x8                                     
            psrlq  mm2,0x38                                    
            por    mm6,mm2                                     
            movq   QWORD PTR [edx+ebx*1],mm6                   
            psllq  mm0,0x8                                     
            movq   mm1,mm0                                     
            psllq  mm5,0x8                                     
            psrlq  mm1,0x38                                    
            por    mm5,mm1                                     
            movq   QWORD PTR [edx+ebx*2],mm5                   
            psllq  mm0,0x8                                     
            movq   mm2,mm0                                     
            psllq  mm6,0x8                                     
            psrlq  mm2,0x38                                    
            por    mm6,mm2                                     
            movq   QWORD PTR [esi+ebx*1],mm6                   
            psllq  mm0,0x8                                     
            movq   mm1,mm0                                     
            psllq  mm5,0x8                                     
            psrlq  mm1,0x38                                    
            por    mm5,mm1                                     
            movq   QWORD PTR [esi+ebx*2],mm5                   
            pop    esi                                         
            pop    ebx                                         
            ret
    }
}

NAKED void ff_pred8x8l_vertical_right_sse2(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
        push   ebx                                            
            push   esi                                            
            mov    eax,DWORD PTR [esp+0xc]                        
        mov    ecx,DWORD PTR [esp+0x10]                       
        mov    edx,DWORD PTR [esp+0x14]                       
        mov    ebx,DWORD PTR [esp+0x18]                       
        sub    eax,ebx                                        
            lea    esi,[eax+ebx*2]                                
        movq   mm0,QWORD PTR [eax+ebx*1-0x8]                  
        punpckhbw mm0,QWORD PTR [eax-0x8]                     
        movq   mm1,QWORD PTR [esi+ebx*1-0x8]                  
        punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8]               
        mov    esi,eax                                        
            punpckhwd mm1,mm0                                     
            lea    eax,[eax+ebx*4]                                
        movq   mm2,QWORD PTR [eax+ebx*1-0x8]                  
        punpckhbw mm2,QWORD PTR [eax-0x8]                     
        lea    eax,[eax+ebx*2]                                
        movq   mm3,QWORD PTR [eax+ebx*1-0x8]                  
        punpckhbw mm3,QWORD PTR [eax-0x8]                     
        punpckhwd mm3,mm2                                     
            punpckhdq mm3,mm1                                     
            lea    eax,[eax+ebx*2]                                
        movq   mm0,QWORD PTR [eax-0x8]                        
        movq   mm1,QWORD PTR [esi]                            
        mov    eax,esi                                        
            movq   mm4,mm3                                        
            movq   mm2,mm3                                        
            psllq  mm4,0x8                                        
            psrlq  mm0,0x38                                       
            por    mm4,mm0                                        
            psllq  mm1,0x38                                       
            psrlq  mm2,0x8                                        
            por    mm1,mm2                                        
            test   ecx,ecx                                        
            jne    ff_pred8x8l_vertical_right_sse2_do_left        

ff_pred8x8l_vertical_right_sse2_fix_lt_1:             
        movq   mm5,mm3                                        
            pxor   mm5,mm4                                        
            psrlq  mm5,0x38                                       
            psllq  mm5,0x30                                       
            pxor   mm1,mm5                                        
            jmp    ff_pred8x8l_vertical_right_sse2_do_left        

ff_pred8x8l_vertical_right_sse2_fix_lt_2:             
        movq   mm5,mm3                                        
            pxor   mm5,mm2                                        
            psllq  mm5,0x38                                       
            psrlq  mm5,0x38                                       
            pxor   mm2,mm5                                        
            test   edx,edx                                        
            jne    ff_pred8x8l_vertical_right_sse2_do_top         

ff_pred8x8l_vertical_right_sse2_fix_tr_1:             
        movq   mm5,mm3                                        
            pxor   mm5,mm1                                        
            psrlq  mm5,0x38                                       
            psllq  mm5,0x38                                       
            pxor   mm1,mm5                                        
            jmp    ff_pred8x8l_vertical_right_sse2_do_top         

ff_pred8x8l_vertical_right_sse2_do_left:              
        movq   mm0,mm4                                        
            movq   mm5,mm1                                        
            pavgb  mm1,mm4                                        
            pxor   mm4,mm5                                        
            movq   mm2,mm3                                        
            pand   mm4,QWORD PTR [ff_pb_1]                        
        psubusb mm1,mm4                                       
            pavgb  mm2,mm1                                        
            movq2dq xmm0,mm2                                      
            movq   mm0,QWORD PTR [eax-0x8]                        
        movq   mm3,QWORD PTR [eax]                            
        movq   mm1,QWORD PTR [eax+0x8]                        
        movq   mm2,mm3                                        
            movq   mm4,mm3                                        
            psllq  mm2,0x8                                        
            psrlq  mm0,0x38                                       
            por    mm2,mm0                                        
            psllq  mm1,0x38                                       
            psrlq  mm4,0x8                                        
            por    mm1,mm4                                        
            test   ecx,ecx                                        
            je     ff_pred8x8l_vertical_right_sse2_fix_lt_2       
            test   edx,edx                                        
            je     ff_pred8x8l_vertical_right_sse2_fix_tr_1       

ff_pred8x8l_vertical_right_sse2_do_top:               
        movq   mm5,mm2                                        
            pavgb  mm2,mm1                                        
            pxor   mm1,mm5                                        
            movq   mm6,mm3                                        
            pand   mm1,QWORD PTR [ff_pb_1]                        
        psubusb mm2,mm1                                       
            pavgb  mm6,mm2                                        
            lea    ecx,[eax+ebx*2]                                
        movq2dq xmm4,mm6                                      
            pslldq xmm4,0x8                                       
            por    xmm0,xmm4                                      
            movdqa xmm6,XMMWORD PTR [pw_ff00]                     

        movdqa xmm1,xmm0                                      
            lea    edx,[ecx+ebx*2]                                
        movdqa xmm2,xmm0                                      
            movdqa xmm3,xmm0                                      
            pslldq xmm0,0x1                                       
            pslldq xmm1,0x2                                       
            pavgb  xmm2,xmm0                                      
            movdqa xmm5,xmm3                                      
            pavgb  xmm3,xmm1                                      
            pxor   xmm1,xmm5                                      
            movdqa xmm4,xmm0                                      
            pand   xmm1,XMMWORD PTR [ff_pb_1]                     

        psubusb xmm3,xmm1                                     
            pavgb  xmm4,xmm3                                      
            pandn  xmm6,xmm4                                      
            movdqa xmm5,xmm4                                      
            psrlw  xmm4,0x8                                       
            packuswb xmm6,xmm4                                    
            movhlps xmm4,xmm6                                     
            movhps QWORD PTR [eax+ebx*2],xmm5                     
            movhps QWORD PTR [eax+ebx*1],xmm2                     
            psrldq xmm5,0x4                                       
            movss  xmm5,xmm6                                      
            psrldq xmm2,0x4                                       
            movss  xmm2,xmm4                                      
            lea    eax,[edx+ebx*2]                                
        psrldq xmm5,0x1                                       
            psrldq xmm2,0x1                                       
            movq   QWORD PTR [eax+ebx*2],xmm5                     
            movq   QWORD PTR [eax+ebx*1],xmm2                     
            psrldq xmm5,0x1                                       
            psrldq xmm2,0x1                                       
            movq   QWORD PTR [edx+ebx*2],xmm5                     
            movq   QWORD PTR [edx+ebx*1],xmm2                     
            psrldq xmm5,0x1                                       
            psrldq xmm2,0x1                                       
            movq   QWORD PTR [ecx+ebx*2],xmm5                     
            movq   QWORD PTR [ecx+ebx*1],xmm2                     
            pop    esi                                            
            pop    ebx                                            
            ret                                                   

    }
}

NAKED void ff_pred8x8l_vertical_right_ssse3(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                             
			push esi                             
			mov eax, [esp + 8 + 4 + 0*4]         
		mov ecx, [esp + 8 + 4 + 1*4]         
		mov edx, [esp + 8 + 4 + 2*4]         
		mov ebx, [esp + 8 + 4 + 3*4]         



		sub eax, ebx                         
			lea esi, [eax+ebx*2]                 
		movq mm0, [eax+ebx*1-8]              

		punpckhbw mm0, [eax+ebx*0-8]         
		movq mm1, [esi+ebx*1-8]              

		punpckhbw mm1, [eax+ebx*2-8]         
		mov esi, eax                         

			punpckhwd mm1, mm0                   
			lea eax, [eax+ebx*4]                 
		movq mm2, [eax+ebx*1-8]              

		punpckhbw mm2, [eax+ebx*0-8]         
		lea eax, [eax+ebx*2]                 
		movq mm3, [eax+ebx*1-8]              

		punpckhbw mm3, [eax+ebx*0-8]         

		punpckhwd mm3, mm2                   

			punpckhdq mm3, mm1                   
			lea eax, [eax+ebx*2]                 
		movq mm0, [eax+ebx*0-8]              
		movq mm1, [esi]                      
		mov eax, esi                         
			movq mm4, mm3                        
			movq mm2, mm3                        

			palignr mm4, mm0, 7                  

			palignr mm1, mm2, 1                  
			test ecx, ecx                        
			jnz  ff_pred8x8l_vertical_right_ssse3__do_left                         
ff_pred8x8l_vertical_right_ssse3__fix_lt_1:                            
		movq mm5, mm3                        

			pxor mm5, mm4                        

			psrlq mm5, 56                        

			psllq mm5, 48                        

			pxor mm1, mm5                        
			jmp  ff_pred8x8l_vertical_right_ssse3__do_left                         
ff_pred8x8l_vertical_right_ssse3__fix_lt_2:                            
		movq mm5, mm3                        

			pxor mm5, mm2                        

			psllq mm5, 56                        

			psrlq mm5, 56                        

			pxor mm2, mm5                        
			test edx, edx                        
			jnz  ff_pred8x8l_vertical_right_ssse3__do_top                          
ff_pred8x8l_vertical_right_ssse3__fix_tr_1:                            
		movq mm5, mm3                        

			pxor mm5, mm1                        

			psrlq mm5, 56                        

			psllq mm5, 56                        

			pxor mm1, mm5                        
			jmp  ff_pred8x8l_vertical_right_ssse3__do_top                          
ff_pred8x8l_vertical_right_ssse3__do_left:                             
		movq mm0, mm4                        
			movq mm5, mm1                        

			pavgb mm1, mm4                       

			pxor mm4, mm5                        
			movq mm2, mm3                        

			pand mm4, [ff_pb_1]                  

		psubusb mm1, mm4                     

			pavgb mm2, mm1                       
			movq2dq xmm0, mm2                    
			movq mm0, [eax-8]                    
		movq mm3, [eax]                      
		movq mm1, [eax+8]                    
		movq mm2, mm3                        
			movq mm4, mm3                        

			palignr mm2, mm0, 7                  

			palignr mm1, mm4, 1                  
			test ecx, ecx                        
			jz  ff_pred8x8l_vertical_right_ssse3__fix_lt_2                         
			test edx, edx                        
			jz  ff_pred8x8l_vertical_right_ssse3__fix_tr_1                         
ff_pred8x8l_vertical_right_ssse3__do_top:                               
			movq mm5, mm2                        

			pavgb mm2, mm1                       

			pxor mm1, mm5                        
			movq mm6, mm3                        

			pand mm1, [ff_pb_1]                  

		psubusb mm2, mm1                     

			pavgb mm6, mm2                       
			lea ecx, [eax+ebx*2]                 
		movq2dq xmm4, mm6                    

			pslldq xmm4, 8                       

			por xmm0, xmm4                       
			movdqa xmm6, [pw_ff00]               
		movdqa xmm1, xmm0                    
			lea edx, [ecx+ebx*2]                 
		movdqa xmm2, xmm0                    
			movdqa xmm3, xmm0                    

			pslldq xmm0, 1                       

			pslldq xmm1, 2                       

			pavgb xmm2, xmm0                     
			movdqa xmm5, xmm3                    

			pavgb xmm3, xmm1                     

			pxor xmm1, xmm5                      
			movdqa xmm4, xmm0                    

			pand xmm1, [ff_pb_1]                 

		psubusb xmm3, xmm1                   

			pavgb xmm4, xmm3                     

			pandn xmm6, xmm4                     
			movdqa xmm5, xmm4                    

			psrlw xmm4, 8                        

			packuswb xmm6, xmm4                  

			movhlps xmm4, xmm6                   
			movhps [eax+ebx*2], xmm5             
			movhps [eax+ebx*1], xmm2             

			psrldq xmm5, 4                       

			movss xmm5, xmm6                     

			psrldq xmm2, 4                       

			movss xmm2, xmm4                     
			lea eax, [edx+ebx*2]                 

		psrldq xmm5, 1                       

			psrldq xmm2, 1                       
			movq  qword ptr [eax+ebx*2], xmm5               
			movq  qword ptr [eax+ebx*1], xmm2               

			psrldq xmm5, 1                       

			psrldq xmm2, 1                       
			movq  qword ptr [edx+ebx*2], xmm5               
			movq  qword ptr [edx+ebx*1], xmm2               

			psrldq xmm5, 1                       

			psrldq xmm2, 1                       
			movq  qword ptr [ecx+ebx*2], xmm5               
			movq  qword ptr [ecx+ebx*1], xmm2               
			pop esi                              
			pop ebx                              
			ret                                  

	}
}

NAKED void ff_pred8x8l_vertical_left_sse2(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                           
			mov eax, [esp + 4 + 4 + 0*4]       
		mov ecx, [esp + 4 + 4 + 1*4]       
		mov edx, [esp + 4 + 4 + 2*4]       
		mov ebx, [esp + 4 + 4 + 3*4]       

		sub eax, ebx                       
			movq mm0, [eax-8]                  
		movq mm3, [eax]                    
		movq mm1, [eax+8]                  
		movq mm2, mm3                      
			movq mm4, mm3                      

			psllq mm2, (8-7)*8                 

			psrlq mm0, 7*8                     

			por mm2, mm0                       

			psllq mm1, (8-1)*8                 

			psrlq mm4, 1*8                     

			por mm1, mm4                       
			test ecx, ecx                      
			jz  ff_pred8x8l_vertical_left_sse2__fix_lt_2                       
			test edx, edx                      
			jz  ff_pred8x8l_vertical_left_sse2__fix_tr_1                       
			jmp  ff_pred8x8l_vertical_left_sse2__do_top                        
ff_pred8x8l_vertical_left_sse2__fix_lt_2:                          
		movq mm5, mm3                      

			pxor mm5, mm2                      

			psllq mm5, 56                      

			psrlq mm5, 56                      

			pxor mm2, mm5                      
			test edx, edx                      
			jnz  ff_pred8x8l_vertical_left_sse2__do_top                        
ff_pred8x8l_vertical_left_sse2__fix_tr_1:                          
		movq mm5, mm3                      

			pxor mm5, mm1                      

			psrlq mm5, 56                      

			psllq mm5, 56                      

			pxor mm1, mm5                      
			jmp  ff_pred8x8l_vertical_left_sse2__do_top                        
ff_pred8x8l_vertical_left_sse2__fix_tr_2:                          

		punpckhbw mm3, mm3                 
			pshufw mm1, mm3, 0xFF              
			jmp  ff_pred8x8l_vertical_left_sse2__do_topright                   
ff_pred8x8l_vertical_left_sse2__do_top:                            
		movq mm5, mm2                      

			pavgb mm2, mm1                     

			pxor mm1, mm5                      
			movq mm4, mm3                      

			pand mm1, [ff_pb_1]                

		psubusb mm2, mm1                   

			pavgb mm4, mm2                     
			movq2dq xmm4, mm4                  
			test edx, edx                      
			jz  ff_pred8x8l_vertical_left_sse2__fix_tr_2                       
			movq mm0, [eax+8]                  
		movq mm5, mm0                      
			movq mm2, mm0                      
			movq mm4, mm0                      

			psrlq mm5, 56                      

			psllq mm2, (8-7)*8                 

			psrlq mm3, 7*8                     

			por mm2, mm3                       

			psllq mm5, (8-1)*8                 

			psrlq mm4, 1*8                     

			por mm5, mm4                       
			movq mm4, mm2                      

			pavgb mm2, mm5                     

			pxor mm5, mm4                      
			movq mm1, mm0                      

			pand mm5, [ff_pb_1]                

		psubusb mm2, mm5                   

			pavgb mm1, mm2                     
ff_pred8x8l_vertical_left_sse2__do_topright:                       
		movq2dq xmm3, mm1                  
			lea ecx, [eax+ebx*2]               

		pslldq xmm3, 8                     

			por xmm4, xmm3                     
			movdqa xmm2, xmm4                  
			movdqa xmm1, xmm4                  
			movdqa xmm3, xmm4                  

			psrldq xmm2, 1                     

			pslldq xmm1, 1                     

			pavgb xmm3, xmm2                   
			lea edx, [ecx+ebx*2]               
		movdqa xmm5, xmm1                  

			pavgb xmm1, xmm2                   

			pxor xmm2, xmm5                    
			movdqa xmm0, xmm4                  

			pand xmm2, [ff_pb_1]               

		psubusb xmm1, xmm2                 

			pavgb xmm0, xmm1                   

			psrldq xmm0, 1                     
			movq  qword ptr [eax+ebx*1], xmm3             
			movq  qword ptr [eax+ebx*2], xmm0             
			lea eax, [edx+ebx*2]               

		psrldq xmm3, 1                     

			psrldq xmm0, 1                     
			movq  qword ptr [ecx+ebx*1], xmm3             
			movq  qword ptr [ecx+ebx*2], xmm0             

			psrldq xmm3, 1                     

			psrldq xmm0, 1                     
			movq  qword ptr [edx+ebx*1], xmm3             
			movq  qword ptr [edx+ebx*2], xmm0             

			psrldq xmm3, 1                     

			psrldq xmm0, 1                     
			movq  qword ptr [eax+ebx*1], xmm3             
			movq  qword ptr [eax+ebx*2], xmm0             
			pop ebx                            
			ret                                

	}
}

NAKED void ff_pred8x8l_vertical_left_ssse3(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                             
			mov eax, [esp + 4 + 4 + 0*4]         
		mov ecx, [esp + 4 + 4 + 1*4]         
		mov edx, [esp + 4 + 4 + 2*4]         
		mov ebx, [esp + 4 + 4 + 3*4]         

		sub eax, ebx                         
			movq mm0, [eax-8]                    
		movq mm3, [eax]                      
		movq mm1, [eax+8]                    
		movq mm2, mm3                        
			movq mm4, mm3                        

			palignr mm2, mm0, 7                  

			palignr mm1, mm4, 1                  
			test ecx, ecx                        
			jz  ff_pred8x8l_vertical_left_ssse3__fix_lt_2                         
			test edx, edx                        
			jz  ff_pred8x8l_vertical_left_ssse3__fix_tr_1                         
			jmp  ff_pred8x8l_vertical_left_ssse3__do_top                          
ff_pred8x8l_vertical_left_ssse3__fix_lt_2:                            
		movq mm5, mm3                        

			pxor mm5, mm2                        

			psllq mm5, 56                        

			psrlq mm5, 56                        

			pxor mm2, mm5                        
			test edx, edx                        
			jnz  ff_pred8x8l_vertical_left_ssse3__do_top                          
ff_pred8x8l_vertical_left_ssse3__fix_tr_1:                            
		movq mm5, mm3                        

			pxor mm5, mm1                        

			psrlq mm5, 56                        

			psllq mm5, 56                        

			pxor mm1, mm5                        
			jmp  ff_pred8x8l_vertical_left_ssse3__do_top                          
ff_pred8x8l_vertical_left_ssse3__fix_tr_2:                            

		punpckhbw mm3, mm3                   
			pshufw mm1, mm3, 0xFF                
			jmp  ff_pred8x8l_vertical_left_ssse3__do_topright                     
ff_pred8x8l_vertical_left_ssse3__do_top:                              
		movq mm5, mm2                        

			pavgb mm2, mm1                       

			pxor mm1, mm5                        
			movq mm4, mm3                        

			pand mm1, [ff_pb_1]                  

		psubusb mm2, mm1                     

			pavgb mm4, mm2                       
			movq2dq xmm4, mm4                    
			test edx, edx                        
			jz  ff_pred8x8l_vertical_left_ssse3__fix_tr_2                         
			movq mm0, [eax+8]                    
		movq mm5, mm0                        
			movq mm2, mm0                        
			movq mm4, mm0                        

			psrlq mm5, 56                        

			palignr mm2, mm3, 7                  

			palignr mm5, mm4, 1                  
			movq mm4, mm2                        

			pavgb mm2, mm5                       

			pxor mm5, mm4                        
			movq mm1, mm0                        

			pand mm5, [ff_pb_1]                  

		psubusb mm2, mm5                     

			pavgb mm1, mm2                       
ff_pred8x8l_vertical_left_ssse3__do_topright:                         
		movq2dq xmm3, mm1                    
			lea ecx, [eax+ebx*2]                 

		pslldq xmm3, 8                       

			por xmm4, xmm3                       
			movdqa xmm2, xmm4                    
			movdqa xmm1, xmm4                    
			movdqa xmm3, xmm4                    

			psrldq xmm2, 1                       

			pslldq xmm1, 1                       

			pavgb xmm3, xmm2                     
			lea edx, [ecx+ebx*2]                 
		movdqa xmm5, xmm1                    

			pavgb xmm1, xmm2                     

			pxor xmm2, xmm5                      
			movdqa xmm0, xmm4                    

			pand xmm2, [ff_pb_1]                 

		psubusb xmm1, xmm2                   

			pavgb xmm0, xmm1                     

			psrldq xmm0, 1                       
			movq  qword ptr [eax+ebx*1], xmm3               
			movq  qword ptr [eax+ebx*2], xmm0               
			lea eax, [edx+ebx*2]                 

		psrldq xmm3, 1                       

			psrldq xmm0, 1                       
			movq  qword ptr [ecx+ebx*1], xmm3               
			movq  qword ptr [ecx+ebx*2], xmm0               

			psrldq xmm3, 1                       

			psrldq xmm0, 1                       
			movq  qword ptr [edx+ebx*1], xmm3               
			movq  qword ptr [edx+ebx*2], xmm0               

			psrldq xmm3, 1                       

			psrldq xmm0, 1                       
			movq  qword ptr [eax+ebx*1], xmm3               
			movq  qword ptr [eax+ebx*2], xmm0               
			pop ebx                              
			ret                                  

	}
}

NAKED void ff_pred8x8l_horizontal_up_mmxext(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
        push   ebx                                
            mov    eax,DWORD PTR [esp+0x8]            
        mov    ecx,DWORD PTR [esp+0xc]            
        mov    edx,DWORD PTR [esp+0x10]           
        mov    ebx,DWORD PTR [esp+0x14]           
        sub    eax,ebx                            
            lea    edx,[eax+ebx*2]                    
        movq   mm0,QWORD PTR [eax+ebx*1-0x8]      
        test   ecx,ecx                            
            lea    ecx,[eax+ebx*1]                    
        cmovne ecx,eax                            
            punpckhbw mm0,QWORD PTR [ecx-0x8]         
        movq   mm1,QWORD PTR [edx+ebx*1-0x8]      
        punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8]   
        mov    edx,eax                            
            punpckhwd mm1,mm0                         
            lea    eax,[eax+ebx*4]                    
        movq   mm2,QWORD PTR [eax+ebx*1-0x8]      
        punpckhbw mm2,QWORD PTR [eax-0x8]         
        lea    eax,[eax+ebx*2]                    
        movq   mm3,QWORD PTR [eax+ebx*1-0x8]      
        punpckhbw mm3,QWORD PTR [eax-0x8]         
        punpckhwd mm3,mm2                         
            punpckhdq mm3,mm1                         
            lea    eax,[eax+ebx*2]                    
        movq   mm0,QWORD PTR [eax-0x8]            
        movq   mm1,QWORD PTR [ecx-0x8]            
        mov    eax,edx                            
            movq   mm4,mm3                            
            movq   mm2,mm3                            
            psllq  mm4,0x8                            
            psrlq  mm0,0x38                           
            por    mm4,mm0                            
            psllq  mm1,0x38                           
            psrlq  mm2,0x8                            
            por    mm1,mm2                            
            movq   mm0,mm4                            
            movq   mm5,mm1                            
            pavgb  mm1,mm4                            
            pxor   mm4,mm5                            
            movq   mm2,mm3                            
            pand   mm4,QWORD PTR [ff_pb_1]               
        psubusb mm1,mm4                           
            pavgb  mm2,mm1                            
            movq   mm4,mm0                            
            movq   mm7,mm2                            
            movq   mm5,mm3                            
            pavgb  mm3,mm0                            
            pxor   mm0,mm5                            
            movq   mm1,mm4                            
            pand   mm0,QWORD PTR [ff_pb_1]               
        psubusb mm3,mm0                           
            pavgb  mm1,mm3                            
            psllq  mm1,0x38                           
            movq   mm3,mm1                            
            psllq  mm7,0x8                            
            psrlq  mm3,0x38                           
            por    mm7,mm3                            
            lea    ecx,[eax+ebx*2]                    
        pshufw mm0,mm7,0x1b                       
            psllq  mm7,0x38                           
            movq   mm2,mm0                            
            psllw  mm0,0x8                            
            psrlw  mm2,0x8                            
            por    mm2,mm0                            
            movq   mm3,mm2                            
            movq   mm4,mm2                            
            movq   mm5,mm2                            
            psrlq  mm2,0x8                            
            psrlq  mm3,0x10                           
            lea    edx,[ecx+ebx*2]                    
        por    mm2,mm7                            
            punpckhbw mm7,mm7                         
            por    mm3,mm7                            
            pavgb  mm4,mm2                            
            movq   mm6,mm3                            
            pavgb  mm3,mm5                            
            pxor   mm5,mm6                            
            movq   mm1,mm2                            
            pand   mm5,QWORD PTR [ff_pb_1]               
        psubusb mm3,mm5                           
            pavgb  mm1,mm3                            
            movq   mm5,mm4                            
            punpcklbw mm4,mm1                         
            punpckhbw mm5,mm1                         
            movq   mm6,mm5                            
            movq   mm7,mm5                            
            movq   mm0,mm5                            
            movq   mm1,mm4                            
            psllq  mm5,0x30                           
            psrlq  mm1,0x10                           
            por    mm5,mm1                            
            pshufw mm1,mm6,0xf9                       
            movq   mm2,mm4                            
            psllq  mm6,0x20                           
            psrlq  mm2,0x20                           
            por    mm6,mm2                            
            pshufw mm2,mm7,0xfe                       
            movq   mm3,mm4                            
            psllq  mm7,0x10                           
            psrlq  mm3,0x30                           
            por    mm7,mm3                            
            pshufw mm3,mm0,0xff                       
            movq   QWORD PTR [eax+ebx*1],mm4          
            movq   QWORD PTR [eax+ebx*2],mm5          
            lea    eax,[edx+ebx*2]                    
        movq   QWORD PTR [ecx+ebx*1],mm6          
            movq   QWORD PTR [ecx+ebx*2],mm7          
            movq   QWORD PTR [edx+ebx*1],mm0          
            movq   QWORD PTR [edx+ebx*2],mm1          
            movq   QWORD PTR [eax+ebx*1],mm2          
            movq   QWORD PTR [eax+ebx*2],mm3          
            pop    ebx                                
            ret
	}
}

NAKED void ff_pred8x8l_horizontal_up_ssse3(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                             
			mov eax, [esp + 4 + 4 + 0*4]         
		mov ecx, [esp + 4 + 4 + 1*4]         
		mov edx, [esp + 4 + 4 + 2*4]         
		mov ebx, [esp + 4 + 4 + 3*4]         

		sub eax, ebx                         
			lea edx, [eax+ebx*2]                 
		movq mm0, [eax+ebx*1-8]              
		test ecx, ecx                        
			lea ecx, [eax+ebx]                   
		cmovnz ecx, eax                      

			punpckhbw mm0, [ecx+ebx*0-8]         
		movq mm1, [edx+ebx*1-8]              

		punpckhbw mm1, [eax+ebx*2-8]         
		mov edx, eax                         

			punpckhwd mm1, mm0                   
			lea eax, [eax+ebx*4]                 
		movq mm2, [eax+ebx*1-8]              

		punpckhbw mm2, [eax+ebx*0-8]         
		lea eax, [eax+ebx*2]                 
		movq mm3, [eax+ebx*1-8]              

		punpckhbw mm3, [eax+ebx*0-8]         

		punpckhwd mm3, mm2                   

			punpckhdq mm3, mm1                   
			lea eax, [eax+ebx*2]                 
		movq mm0, [eax+ebx*0-8]              
		movq mm1, [ecx+ebx*0-8]              
		mov eax, edx                         
			movq mm4, mm3                        
			movq mm2, mm3                        

			palignr mm4, mm0, 7                  

			palignr mm1, mm2, 1                  
			movq mm0, mm4                        
			movq mm5, mm1                        

			pavgb mm1, mm4                       

			pxor mm4, mm5                        
			movq mm2, mm3                        

			pand mm4, [ff_pb_1]                  

		psubusb mm1, mm4                     

			pavgb mm2, mm1                       
			movq mm4, mm0                        
			movq mm7, mm2                        
			movq mm5, mm3                        

			pavgb mm3, mm0                       

			pxor mm0, mm5                        
			movq mm1, mm4                        

			pand mm0, [ff_pb_1]                  

		psubusb mm3, mm0                     

			pavgb mm1, mm3                       

			psllq mm1, 56                        

			palignr mm7, mm1, 7                  
			lea ecx, [eax+ebx*2]                 
		pshufw mm0, mm7, 00011011b            

			psllq mm7, 56                        
			movq mm2, mm0                        

			psllw mm0, 8                         

			psrlw mm2, 8                         

			por mm2, mm0                         
			movq mm3, mm2                        
			movq mm4, mm2                        
			movq mm5, mm2                        

			psrlq mm2, 8                         

			psrlq mm3, 16                        
			lea edx, [ecx+ebx*2]                 

		por mm2, mm7                         

			punpckhbw mm7, mm7                   

			por mm3, mm7                         

			pavgb mm4, mm2                       
			movq mm6, mm3                        

			pavgb mm3, mm5                       

			pxor mm5, mm6                        
			movq mm1, mm2                        

			pand mm5, [ff_pb_1]                  

		psubusb mm3, mm5                     

			pavgb mm1, mm3                       
			movq mm5, mm4                        

			punpcklbw mm4, mm1                   

			punpckhbw mm5, mm1                   
			movq mm6, mm5                        
			movq mm7, mm5                        
			movq mm0, mm5                        

			palignr mm5, mm4, 2                  
			pshufw mm1, mm6, 11111001b            

			palignr mm6, mm4, 4                  
			pshufw mm2, mm7, 11111110b            

			palignr mm7, mm4, 6                  
			pshufw mm3, mm0, 11111111b            
			movq [eax+ebx*1], mm4                
			movq [eax+ebx*2], mm5                
			lea eax, [edx+ebx*2]                 
		movq [ecx+ebx*1], mm6                
			movq [ecx+ebx*2], mm7                
			movq [edx+ebx*1], mm0                
			movq [edx+ebx*2], mm1                
			movq [eax+ebx*1], mm2                
			movq [eax+ebx*2], mm3                
			pop ebx                              
			ret                                  

	}
}

NAKED void ff_pred8x8l_horizontal_down_mmxext(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm 
    {
    push   ebx                                          
    push   esi                                          
    mov    eax,DWORD PTR [esp+0xc]                      
    mov    ecx,DWORD PTR [esp+0x10]                     
    mov    edx,DWORD PTR [esp+0x14]                     
    mov    ebx,DWORD PTR [esp+0x18]                     
    sub    eax,ebx                                      
    lea    esi,[eax+ebx*2]                              
    movq   mm0,QWORD PTR [eax+ebx*1-0x8]                
    punpckhbw mm0,QWORD PTR [eax-0x8]                   
    movq   mm1,QWORD PTR [esi+ebx*1-0x8]                
    punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8]             
    mov    esi,eax                                      
    punpckhwd mm1,mm0                                   
    lea    eax,[eax+ebx*4]                              
    movq   mm2,QWORD PTR [eax+ebx*1-0x8]                
    punpckhbw mm2,QWORD PTR [eax-0x8]                   
    lea    eax,[eax+ebx*2]                              
    movq   mm3,QWORD PTR [eax+ebx*1-0x8]                
    punpckhbw mm3,QWORD PTR [eax-0x8]                   
    punpckhwd mm3,mm2                                   
    punpckhdq mm3,mm1                                   
    lea    eax,[eax+ebx*2]                              
    movq   mm0,QWORD PTR [eax-0x8]                      
    movq   mm1,QWORD PTR [esi]                          
    mov    eax,esi                                      
    movq   mm4,mm3                                      
    movq   mm2,mm3                                      
    psllq  mm4,0x8                                      
    psrlq  mm0,0x38                                     
    por    mm4,mm0                                      
    psllq  mm1,0x38                                     
    psrlq  mm2,0x8                                      
    por    mm1,mm2                                      
    test   ecx,ecx                                      
    jne    ff_pred8x8l_horizontal_down_mmxext_do_left   

    ff_pred8x8l_horizontal_down_mmxext_fix_lt_1:        
    movq   mm5,mm3                                      
    pxor   mm5,mm4                                      
    psrlq  mm5,0x38                                     
    psllq  mm5,0x30                                     
    pxor   mm1,mm5                                      
    jmp    ff_pred8x8l_horizontal_down_mmxext_do_left   

    ff_pred8x8l_horizontal_down_mmxext_fix_lt_2:        
    movq   mm5,mm3                                      
    pxor   mm5,mm2                                      
    psllq  mm5,0x38                                     
    psrlq  mm5,0x38                                     
    pxor   mm2,mm5                                      
    test   edx,edx                                      
    jne    ff_pred8x8l_horizontal_down_mmxext_do_top    

    ff_pred8x8l_horizontal_down_mmxext_fix_tr_1:        
    movq   mm5,mm3                                      
    pxor   mm5,mm1                                      
    psrlq  mm5,0x38                                     
    psllq  mm5,0x38                                     
    pxor   mm1,mm5                                      
    jmp    ff_pred8x8l_horizontal_down_mmxext_do_top    

    ff_pred8x8l_horizontal_down_mmxext_do_left:         
    movq   mm0,mm4                                      
    movq   mm5,mm1                                      
    pavgb  mm1,mm4                                      
    pxor   mm4,mm5                                      
    movq   mm2,mm3                                      
    pand   mm4,QWORD PTR [ff_pb_1]                         
    psubusb mm1,mm4                                     
    pavgb  mm2,mm1                                      
    movq   mm4,mm0                                      
    movq   mm7,mm2                                      
    movq   mm6,mm2                                      
    movq   mm5,mm3                                      
    pavgb  mm3,mm0                                      
    pxor   mm0,mm5                                      
    movq   mm1,mm4                                      
    pand   mm0,QWORD PTR [ff_pb_1]                         
    psubusb mm3,mm0                                     
    pavgb  mm1,mm3                                      
    psllq  mm1,0x38                                     
    movq   mm3,mm1                                      
    psllq  mm7,0x8                                      
    psrlq  mm3,0x38                                     
    por    mm7,mm3                                      
    movq   mm0,QWORD PTR [eax-0x8]                      
    movq   mm3,QWORD PTR [eax]                          
    movq   mm1,QWORD PTR [eax+0x8]                      
    movq   mm2,mm3                                      
    movq   mm4,mm3                                      
    psllq  mm2,0x8                                      
    psrlq  mm0,0x38                                     
    por    mm2,mm0                                      
    psllq  mm1,0x38                                     
    psrlq  mm4,0x8                                      
    por    mm1,mm4                                      
    test   ecx,ecx                                      
    je     ff_pred8x8l_horizontal_down_mmxext_fix_lt_2  
    test   edx,edx                                      
    je     ff_pred8x8l_horizontal_down_mmxext_fix_tr_1  

    ff_pred8x8l_horizontal_down_mmxext_do_top:          
    movq   mm5,mm2                                      
    pavgb  mm2,mm1                                      
    pxor   mm1,mm5                                      
    movq   mm4,mm3                                      
    pand   mm1,QWORD PTR [ff_pb_1]                         
    psubusb mm2,mm1                                     
    pavgb  mm4,mm2                                      
    movq   mm5,mm4                                      
    lea    ecx,[eax+ebx*2]                              
    psllq  mm7,0x38                                     
    movq   mm2,mm5                                      
    movq   mm3,mm6                                      
    movq   mm4,mm2                                      
    movq   mm5,mm6                                      
    psllq  mm2,0x8                                      
    psrlq  mm5,0x38                                     
    por    mm2,mm5                                      
    movq   mm0,mm7                                      
    psllq  mm6,0x8                                      
    psrlq  mm0,0x38                                     
    por    mm6,mm0                                      
    lea    edx,[ecx+ebx*2]                              
    movq   mm7,mm3                                      
    psllq  mm4,0x38                                     
    psrlq  mm7,0x8                                      
    por    mm4,mm7                                      
    movq   mm5,mm3                                      
    pavgb  mm3,mm6                                      
    movq   mm7,mm4                                      
    pavgb  mm4,mm6                                      
    pxor   mm6,mm7                                      
    movq   mm0,mm5                                      
    pand   mm6,QWORD PTR [ff_pb_1]                         
    psubusb mm4,mm6                                     
    pavgb  mm0,mm4                                      
    movq   mm4,mm2                                      
    movq   mm1,mm2                                      
    lea    esi,[edx+ebx*2]                              
    psrlq  mm4,0x10                                     
    psrlq  mm1,0x8                                      
    movq   mm5,mm4                                      
    pavgb  mm4,mm2                                      
    pxor   mm2,mm5                                      
    movq   mm6,mm1                                      
    pand   mm2,QWORD PTR [ff_pb_1]                         
    psubusb mm4,mm2                                     
    pavgb  mm6,mm4                                      
    movq   mm7,mm3                                      
    punpcklbw mm3,mm0                                   
    punpckhbw mm7,mm0                                   
    movq   mm1,mm7                                      
    movq   mm0,mm7                                      
    movq   mm4,mm7                                      
    movq   QWORD PTR [esi+ebx*2],mm3                    
    movq   mm5,mm3                                      
    psllq  mm7,0x30                                     
    psrlq  mm5,0x10                                     
    por    mm7,mm5                                      
    movq   QWORD PTR [esi+ebx*1],mm7                    
    movq   mm5,mm3                                      
    psllq  mm1,0x20                                     
    psrlq  mm5,0x20                                     
    por    mm1,mm5                                      
    movq   QWORD PTR [edx+ebx*2],mm1                    
    psllq  mm0,0x10                                     
    psrlq  mm3,0x30                                     
    por    mm0,mm3                                      
    movq   QWORD PTR [edx+ebx*1],mm0                    
    movq   mm2,mm6                                      
    movq   mm3,mm6                                      
    movq   QWORD PTR [ecx+ebx*2],mm4                    
    movq   mm5,mm4                                      
    psllq  mm6,0x30                                     
    psrlq  mm5,0x10                                     
    por    mm6,mm5                                      
    movq   QWORD PTR [ecx+ebx*1],mm6                    
    movq   mm5,mm4                                      
    psllq  mm2,0x20                                     
    psrlq  mm5,0x20                                     
    por    mm2,mm5                                      
    movq   QWORD PTR [eax+ebx*2],mm2                    
    psllq  mm3,0x10                                     
    psrlq  mm4,0x30                                     
    por    mm3,mm4                                      
    movq   QWORD PTR [eax+ebx*1],mm3                    
    pop    esi                                          
    pop    ebx                                          
    ret
    }
}

NAKED void ff_pred8x8l_horizontal_down_sse2(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
        push   ebx                                              
            push   esi                                              
            mov    eax,DWORD PTR [esp+0xc]                          
        mov    ecx,DWORD PTR [esp+0x10]                         
        mov    edx,DWORD PTR [esp+0x14]                         
        mov    ebx,DWORD PTR [esp+0x18]                         
        sub    eax,ebx                                          
            lea    esi,[eax+ebx*2]                                  
        movq   mm0,QWORD PTR [eax+ebx*1-0x8]                    
        punpckhbw mm0,QWORD PTR [eax-0x8]                       
        movq   mm1,QWORD PTR [esi+ebx*1-0x8]                    
        punpckhbw mm1,QWORD PTR [eax+ebx*2-0x8]                 
        mov    esi,eax                                          
            punpckhwd mm1,mm0                                       
            lea    eax,[eax+ebx*4]                                  
        movq   mm2,QWORD PTR [eax+ebx*1-0x8]                    
        punpckhbw mm2,QWORD PTR [eax-0x8]                       
        lea    eax,[eax+ebx*2]                                  
        movq   mm3,QWORD PTR [eax+ebx*1-0x8]                    
        punpckhbw mm3,QWORD PTR [eax-0x8]                       
        punpckhwd mm3,mm2                                       
            punpckhdq mm3,mm1                                       
            lea    eax,[eax+ebx*2]                                  
        movq   mm0,QWORD PTR [eax-0x8]                          
        movq   mm1,QWORD PTR [esi]                              
        mov    eax,esi                                          
            movq   mm4,mm3                                          
            movq   mm2,mm3                                          
            psllq  mm4,0x8                                          
            psrlq  mm0,0x38                                         
            por    mm4,mm0                                          
            psllq  mm1,0x38                                         
            psrlq  mm2,0x8                                          
            por    mm1,mm2                                          
            test   ecx,ecx                                          
            jne    ff_pred8x8l_horizontal_down_sse2_do_left         

ff_pred8x8l_horizontal_down_sse2_fix_lt_1:              
        movq   mm5,mm3                                          
            pxor   mm5,mm4                                          
            psrlq  mm5,0x38                                         
            psllq  mm5,0x30                                         
            pxor   mm1,mm5                                          
            jmp    ff_pred8x8l_horizontal_down_sse2_do_left         

ff_pred8x8l_horizontal_down_sse2_fix_lt_2:              
        movq   mm5,mm3                                          
            pxor   mm5,mm2                                          
            psllq  mm5,0x38                                         
            psrlq  mm5,0x38                                         
            pxor   mm2,mm5                                          
            test   edx,edx                                          
            jne    ff_pred8x8l_horizontal_down_sse2_do_top          

ff_pred8x8l_horizontal_down_sse2_fix_tr_1:              
        movq   mm5,mm3                                          
            pxor   mm5,mm1                                          
            psrlq  mm5,0x38                                         
            psllq  mm5,0x38                                         
            pxor   mm1,mm5                                          
            jmp    ff_pred8x8l_horizontal_down_sse2_do_top          

ff_pred8x8l_horizontal_down_sse2_fix_tr_2:              
        punpckhbw mm3,mm3                                       
            pshufw mm1,mm3,0xff                                     
            jmp    ff_pred8x8l_horizontal_down_sse2_do_topright     

ff_pred8x8l_horizontal_down_sse2_do_left:               
        movq   mm0,mm4                                          
            movq   mm5,mm1                                          
            pavgb  mm1,mm4                                          
            pxor   mm4,mm5                                          
            movq   mm2,mm3                                          
            pand   mm4,QWORD PTR [ff_pb_1]                            
            psubusb mm1,mm4                                         
            pavgb  mm2,mm1                                          
            movq2dq xmm0,mm2                                        
            pslldq xmm0,0x8                                         
            movq   mm4,mm0                                          
            movq   mm5,mm3                                          
            pavgb  mm3,mm0                                          
            pxor   mm0,mm5                                          
            movq   mm1,mm4                                          
            pand   mm0,QWORD PTR [ff_pb_1]                             
            psubusb mm3,mm0                                         
            pavgb  mm1,mm3                                          
            movq2dq xmm2,mm1                                        
            pslldq xmm2,0xf                                         
            psrldq xmm2,0x8                                         
            por    xmm0,xmm2                                        
            movq   mm0,QWORD PTR [eax-0x8]                          
        movq   mm3,QWORD PTR [eax]                              
        movq   mm1,QWORD PTR [eax+0x8]                          
        movq   mm2,mm3                                          
            movq   mm4,mm3                                          
            psllq  mm2,0x8                                          
            psrlq  mm0,0x38                                         
            por    mm2,mm0                                          
            psllq  mm1,0x38                                         
            psrlq  mm4,0x8                                          
            por    mm1,mm4                                          
            test   ecx,ecx                                          
            je     ff_pred8x8l_horizontal_down_sse2_fix_lt_2        
            test   edx,edx                                          
            je     ff_pred8x8l_horizontal_down_sse2_fix_tr_1        

ff_pred8x8l_horizontal_down_sse2_do_top:                
        movq   mm5,mm2                                          
            pavgb  mm2,mm1                                          
            pxor   mm1,mm5                                          
            movq   mm4,mm3                                          
            pand   mm1,QWORD PTR [ff_pb_1]                             
            psubusb mm2,mm1                                         
            pavgb  mm4,mm2                                          
            movq2dq xmm1,mm4                                        
            test   edx,edx                                          
            je     ff_pred8x8l_horizontal_down_sse2_fix_tr_2        
            movq   mm0,QWORD PTR [eax+0x8]                          
        movq   mm5,mm0                                          
            movq   mm2,mm0                                          
            movq   mm4,mm0                                          
            psrlq  mm5,0x38                                         
            psllq  mm2,0x8                                          
            psrlq  mm3,0x38                                         
            por    mm2,mm3                                          
            psllq  mm5,0x38                                         
            psrlq  mm4,0x8                                          
            por    mm5,mm4                                          
            movq   mm4,mm2                                          
            pavgb  mm2,mm5                                          
            pxor   mm5,mm4                                          
            movq   mm1,mm0                                          
            pand   mm5,QWORD PTR [ff_pb_1]                            
            psubusb mm2,mm5                                         
            pavgb  mm1,mm2                                          

ff_pred8x8l_horizontal_down_sse2_do_topright:           
        movq2dq xmm5,mm1                                        
            pslldq xmm5,0x8                                         
            por    xmm1,xmm5                                        
            lea    edx,[esi+ebx*2]                                  
        movdqa xmm2,xmm1                                        
            movdqa xmm3,xmm1                                        
            movdqa xmm4,xmm0                                        
            pslldq xmm1,0x9                                         
            psrldq xmm4,0x7                                         
            por    xmm1,xmm4                                        
            movdqa xmm5,xmm0                                        
            pslldq xmm2,0x7                                         
            psrldq xmm5,0x9                                         
            por    xmm2,xmm5                                        
            lea    ecx,[edx+ebx*2]                                  
        pslldq xmm3,0x8                                         
            psrldq xmm0,0x8                                         
            por    xmm3,xmm0                                        
            movdqa xmm4,xmm1                                        
            pavgb  xmm4,xmm3                                        
            lea    eax,[ecx+ebx*2]                                  
        movdqa xmm5,xmm1                                        
            pavgb  xmm1,xmm2                                        
            pxor   xmm2,xmm5                                        
            movdqa xmm0,xmm3                                        
            pand   xmm2,XMMWORD PTR [ff_pb_1]                          

            psubusb xmm1,xmm2                                       
            pavgb  xmm0,xmm1                                        
            punpcklbw xmm4,xmm0                                     
            movhlps xmm0,xmm4                                       
            movq   QWORD PTR [eax+ebx*2],xmm4                       
            movq   QWORD PTR [edx+ebx*2],xmm0                       
            psrldq xmm4,0x2                                         
            psrldq xmm0,0x2                                         
            movq   QWORD PTR [eax+ebx*1],xmm4                       
            movq   QWORD PTR [edx+ebx*1],xmm0                       
            psrldq xmm4,0x2                                         
            psrldq xmm0,0x2                                         
            movq   QWORD PTR [ecx+ebx*2],xmm4                       
            movq   QWORD PTR [esi+ebx*2],xmm0                       
            psrldq xmm4,0x2                                         
            psrldq xmm0,0x2                                         
            movq   QWORD PTR [ecx+ebx*1],xmm4                       
            movq   QWORD PTR [esi+ebx*1],xmm0                       
            pop    esi                                              
            pop    ebx                                              
            ret                                                     

    }
}

NAKED void ff_pred8x8l_horizontal_down_ssse3(uint8_t *src, int has_topleft, int has_topright, int stride)
{
	__asm {
		push ebx                              
			push esi                              
			mov eax, [esp + 8 + 4 + 0*4]          
		mov ecx, [esp + 8 + 4 + 1*4]          
		mov edx, [esp + 8 + 4 + 2*4]          
		mov ebx, [esp + 8 + 4 + 3*4]          

		sub eax, ebx                          
			lea esi, [eax+ebx*2]                  
		movq mm0, [eax+ebx*1-8]               

		punpckhbw mm0, [eax+ebx*0-8]          
		movq mm1, [esi+ebx*1-8]               

		punpckhbw mm1, [eax+ebx*2-8]          
		mov esi, eax                          

			punpckhwd mm1, mm0                    
			lea eax, [eax+ebx*4]                  
		movq mm2, [eax+ebx*1-8]               

		punpckhbw mm2, [eax+ebx*0-8]          
		lea eax, [eax+ebx*2]                  
		movq mm3, [eax+ebx*1-8]               

		punpckhbw mm3, [eax+ebx*0-8]          

		punpckhwd mm3, mm2                    

			punpckhdq mm3, mm1                    
			lea eax, [eax+ebx*2]                  
		movq mm0, [eax+ebx*0-8]               
		movq mm1, [esi]                       
		mov eax, esi                          
			movq mm4, mm3                         
			movq mm2, mm3                         

			palignr mm4, mm0, 7                   

			palignr mm1, mm2, 1                   
			test ecx, ecx                         
			jnz  ff_pred8x8l_horizontal_down_ssse3__do_left                          
ff_pred8x8l_horizontal_down_ssse3__fix_lt_1:                             
		movq mm5, mm3                         

			pxor mm5, mm4                         

			psrlq mm5, 56                         

			psllq mm5, 48                         

			pxor mm1, mm5                         
			jmp  ff_pred8x8l_horizontal_down_ssse3__do_left                          
ff_pred8x8l_horizontal_down_ssse3__fix_lt_2:                             
		movq mm5, mm3                         

			pxor mm5, mm2                         

			psllq mm5, 56                         

			psrlq mm5, 56                         

			pxor mm2, mm5                         
			test edx, edx                         
			jnz  ff_pred8x8l_horizontal_down_ssse3__do_top                           
ff_pred8x8l_horizontal_down_ssse3__fix_tr_1:                             
		movq mm5, mm3                         

			pxor mm5, mm1                         

			psrlq mm5, 56                         

			psllq mm5, 56                         

			pxor mm1, mm5                         
			jmp  ff_pred8x8l_horizontal_down_ssse3__do_top                           
ff_pred8x8l_horizontal_down_ssse3__fix_tr_2:                             

		punpckhbw mm3, mm3                    
			pshufw mm1, mm3, 0xFF                 
			jmp  ff_pred8x8l_horizontal_down_ssse3__do_topright                      
ff_pred8x8l_horizontal_down_ssse3__do_left:                              
		movq mm0, mm4                         
			movq mm5, mm1                         

			pavgb mm1, mm4                        

			pxor mm4, mm5                         
			movq mm2, mm3                         

			pand mm4, [ff_pb_1]                   

		psubusb mm1, mm4                      

			pavgb mm2, mm1                        
			movq2dq xmm0, mm2                     

			pslldq xmm0, 8                        
			movq mm4, mm0                         
			movq mm5, mm3                         

			pavgb mm3, mm0                        

			pxor mm0, mm5                         
			movq mm1, mm4                         

			pand mm0, [ff_pb_1]                   

		psubusb mm3, mm0                      

			pavgb mm1, mm3                        
			movq2dq xmm2, mm1                     

			pslldq xmm2, 15                       

			psrldq xmm2, 8                        

			por xmm0, xmm2                        
			movq mm0, [eax-8]                     
		movq mm3, [eax]                       
		movq mm1, [eax+8]                     
		movq mm2, mm3                         
			movq mm4, mm3                         

			palignr mm2, mm0, 7                   

			palignr mm1, mm4, 1                   
			test ecx, ecx                         
			jz  ff_pred8x8l_horizontal_down_ssse3__fix_lt_2                          
			test edx, edx                         
			jz  ff_pred8x8l_horizontal_down_ssse3__fix_tr_1                          
ff_pred8x8l_horizontal_down_ssse3__do_top:                               
		movq mm5, mm2                         

			pavgb mm2, mm1                        

			pxor mm1, mm5                         
			movq mm4, mm3                         

			pand mm1, [ff_pb_1]                   

		psubusb mm2, mm1                      

			pavgb mm4, mm2                        
			movq2dq xmm1, mm4                     
			test edx, edx                         
			jz  ff_pred8x8l_horizontal_down_ssse3__fix_tr_2                          
			movq mm0, [eax+8]                     
		movq mm5, mm0                         
			movq mm2, mm0                         
			movq mm4, mm0                         

			psrlq mm5, 56                         

			palignr mm2, mm3, 7                   

			palignr mm5, mm4, 1                   
			movq mm4, mm2                         

			pavgb mm2, mm5                        

			pxor mm5, mm4                         
			movq mm1, mm0                         

			pand mm5, [ff_pb_1]                   

		psubusb mm2, mm5                      

			pavgb mm1, mm2                        
ff_pred8x8l_horizontal_down_ssse3__do_topright:                          
		movq2dq xmm5, mm1                     

			pslldq xmm5, 8                        

			por xmm1, xmm5                        
			lea edx, [esi+ebx*2]                  
		movdqa xmm2, xmm1                     
			movdqa xmm3, xmm1                     

			palignr xmm1, xmm0, 7                 

			palignr xmm2, xmm0, 9                 
			lea ecx, [edx+ebx*2]                  

		palignr xmm3, xmm0, 8                 
			movdqa xmm4, xmm1                     

			pavgb xmm4, xmm3                      
			lea eax, [ecx+ebx*2]                  
		movdqa xmm5, xmm1                     

			pavgb xmm1, xmm2                      

			pxor xmm2, xmm5                       
			movdqa xmm0, xmm3                     

			pand xmm2, [ff_pb_1]                  

		psubusb xmm1, xmm2                    

			pavgb xmm0, xmm1                      

			punpcklbw xmm4, xmm0                  

			movhlps xmm0, xmm4                    
			movq  qword ptr [eax+ebx*2], xmm4                
			movq  qword ptr [edx+ebx*2], xmm0                

			psrldq xmm4, 2                        

			psrldq xmm0, 2                        
			movq  qword ptr [eax+ebx*1], xmm4                
			movq  qword ptr [edx+ebx*1], xmm0                

			psrldq xmm4, 2                        

			psrldq xmm0, 2                        
			movq qword ptr[ecx+ebx*2], xmm4                
			movq qword ptr[esi+ebx*2], xmm0                

			psrldq xmm4, 2                        

			psrldq xmm0, 2                        
			movq qword ptr[ecx+ebx*1], xmm4                
			movq qword ptr[esi+ebx*1], xmm0                
			pop esi                               
			pop ebx                               
			ret                                   

	}
}

NAKED void ff_pred4x4_dc_mmxext (uint8_t *src, const uint8_t *topright, int stride)
{
	__asm {
        push   ebx                          
            push   esi                          
            mov    eax,DWORD PTR [esp+0xc]      
        mov    ecx,DWORD PTR [esp+0x10]     
        mov    edx,DWORD PTR [esp+0x14]     
        pxor   mm7,mm7                      
            mov    esi,eax                      
            sub    eax,edx                      
            movd   mm0,DWORD PTR [eax]          
        psadbw mm0,mm7                      
            movzx  ecx,BYTE PTR [eax+edx*1-0x1] 
        movd   ebx,mm0                      
            add    ebx,ecx                      
            movzx  ecx,BYTE PTR [eax+edx*2-0x1] 
        lea    eax,[eax+edx*2]              
        add    ebx,ecx                      
            movzx  ecx,BYTE PTR [eax+edx*1-0x1] 
        add    ebx,ecx                      
            movzx  ecx,BYTE PTR [eax+edx*2-0x1] 
        add    ebx,ecx                      
            add    ebx,0x4                      
            shr    ebx,0x3                      
            imul   ebx,ebx,0x1010101            
            mov    DWORD PTR [esi],ebx          
            mov    DWORD PTR [eax],ebx          
            mov    DWORD PTR [eax+edx*1],ebx    
            mov    DWORD PTR [eax+edx*2],ebx    
            pop    esi                          
            pop    ebx                          
            ret
	}
}

NAKED void ff_pred4x4_down_left_mmxext (uint8_t *src, const uint8_t *topright, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]                    
		mov ecx, [esp + 0 + 4 + 1*4]                    
		mov edx, [esp + 0 + 4 + 2*4]                    

		;line 2612+1 libavcodec/x86/h264_intrapredadsdmd   
			sub eax, edx                                    
			movq mm1, [eax]                                 

		;line 2614+0 libavcodec/x86/h264_intrapredadsdmd   
			punpckldq mm1, [ecx]                            
		;line 2615+1 libavcodec/x86/h264_intrapredadsdmd   
			movq mm2, mm1                                   
			movq mm3, mm1                                   

			;line 2617+0 libavcodec/x86/h264_intrapredadsdmd   
			psllq mm1, 8                                    
			;line 2618+1 libavcodec/x86/h264_intrapredadsdmd   

			;line 2618+0 libavcodec/x86/h264_intrapredadsdmd   
			pxor mm2, mm1                                   
			;line 2619+1 libavcodec/x86/h264_intrapredadsdmd   

			;line 2619+0 libavcodec/x86/h264_intrapredadsdmd   
			psrlq mm2, 8                                    
			;line 2620+1 libavcodec/x86/h264_intrapredadsdmd   

			;line 2620+0 libavcodec/x86/h264_intrapredadsdmd   
			pxor mm2, mm3                                   
			;line 2621+1 libavcodec/x86/h264_intrapredadsdmd   
			movq mm4, mm1                                   
			;line 2621+0 libavcodec/x86/h264_intrapredadsdmd   

			pavgb mm1, mm2                                  

			pxor mm2, mm4                                   
			movq mm0, mm3                                   

			pand mm2, [ff_pb_1]                             

		psubusb mm1, mm2                                

			pavgb mm0, mm1                                  
			;line 2622+1 libavcodec/x86/h264_intrapredadsdmd   
			lea ecx, [eax+edx*2]                            

		;line 2623+0 libavcodec/x86/h264_intrapredadsdmd   
			psrlq mm0, 8                                    
			;line 2624+1 libavcodec/x86/h264_intrapredadsdmd   
			movd [eax+edx*1], mm0                           

			;line 2625+0 libavcodec/x86/h264_intrapredadsdmd   
			psrlq mm0, 8                                    
			;line 2626+1 libavcodec/x86/h264_intrapredadsdmd   
			movd [eax+edx*2], mm0                           

			;line 2627+0 libavcodec/x86/h264_intrapredadsdmd   
			psrlq mm0, 8                                    
			;line 2628+1 libavcodec/x86/h264_intrapredadsdmd   
			movd [ecx+edx*1], mm0                           

			;line 2629+0 libavcodec/x86/h264_intrapredadsdmd   
			psrlq mm0, 8                                    
			;line 2630+1 libavcodec/x86/h264_intrapredadsdmd   
			movd [ecx+edx*2], mm0                           
			ret                                             

	}
}

NAKED void ff_pred4x4_vertical_left_mmxext(uint8_t *src, const uint8_t *topright, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]                         
		mov ecx, [esp + 0 + 4 + 1*4]                         
		mov edx, [esp + 0 + 4 + 2*4]                         

		;line 2639+1 libavcodec/x86/h264_intrapredadsdmd        
			sub eax, edx                                         
			movq mm1, [eax]                                      

		;line 2641+0 libavcodec/x86/h264_intrapredadsdmd        
			punpckldq mm1, [ecx]                                 
		;line 2642+1 libavcodec/x86/h264_intrapredadsdmd        
			movq mm3, mm1                                        
			movq mm2, mm1                                        

			;line 2644+0 libavcodec/x86/h264_intrapredadsdmd        
			psrlq mm3, 8                                         
			;line 2645+1 libavcodec/x86/h264_intrapredadsdmd        

			;line 2645+0 libavcodec/x86/h264_intrapredadsdmd        
			psrlq mm2, 16                                        
			;line 2646+1 libavcodec/x86/h264_intrapredadsdmd        
			movq mm4, mm3                                        

			;line 2647+0 libavcodec/x86/h264_intrapredadsdmd        
			pavgb mm4, mm1                                       
			;line 2648+1 libavcodec/x86/h264_intrapredadsdmd        
			movq mm5, mm1                                        
			;line 2648+0 libavcodec/x86/h264_intrapredadsdmd        

			pavgb mm1, mm2                                       

			pxor mm2, mm5                                        
			movq mm0, mm3                                        

			pand mm2, [ff_pb_1]                                  

		psubusb mm1, mm2                                     

			pavgb mm0, mm1                                       
			;line 2649+1 libavcodec/x86/h264_intrapredadsdmd        
			lea ecx, [eax+edx*2]                                 
		movd [eax+edx*1], mm4                                
			movd [eax+edx*2], mm0                                

			;line 2652+0 libavcodec/x86/h264_intrapredadsdmd        
			psrlq mm4, 8                                         
			;line 2653+1 libavcodec/x86/h264_intrapredadsdmd        

			;line 2653+0 libavcodec/x86/h264_intrapredadsdmd        
			psrlq mm0, 8                                         
			;line 2654+1 libavcodec/x86/h264_intrapredadsdmd        
			movd [ecx+edx*1], mm4                                
			movd [ecx+edx*2], mm0                                
			ret                                                  

	}
}

NAKED void ff_pred4x4_horizontal_up_mmxext(uint8_t *src, const uint8_t *topright, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]                     
		mov ecx, [esp + 0 + 4 + 1*4]                     
		mov edx, [esp + 0 + 4 + 2*4]
		
			sub eax, edx                                     
			lea ecx, [eax+edx*2]                             
		movd mm0, [eax+edx*1-4]                          

		
			punpcklbw mm0, [eax+edx*2-4]                     
		
			movd mm1, [ecx+edx*1-4]                          

		
			punpcklbw mm1, [ecx+edx*2-4]                     
		

		
			punpckhwd mm0, mm1                               
		
			movq mm1, mm0                                    

		
			punpckhbw mm1, mm1                               
		
			pshufw mm1, mm1, 0xFF                            

		
			punpckhdq mm0, mm1                               
		
			movq mm2, mm0                                    
			movq mm3, mm0                                    
			movq mm7, mm0                                    

		
			psrlq mm2, 16                                    
		
			psrlq mm3, 8                                     
		
			pavgb mm7, mm3                                   
		
			movq mm5, mm0                                    
		

			pavgb mm0, mm2                                   

			pxor mm2, mm5                                    
			movq mm4, mm3                                    

			pand mm2, [ff_pb_1]                              

		psubusb mm0, mm2                                 

			pavgb mm4, mm0                                   
						
			punpcklbw mm7, mm4                               
			
			movd [eax+edx*1], mm7                            

			
			psrlq mm7, 16                                    
			
			movd [eax+edx*2], mm7                            

			psrlq mm7, 16                                    

			movd [ecx+edx*1], mm7                            
			movd [ecx+edx*2], mm1                            
			ret                                              

	}
}

NAKED void ff_pred4x4_horizontal_down_mmxext(uint8_t *src, const uint8_t *topright, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]                     
		mov ecx, [esp + 0 + 4 + 1*4]                     
		mov edx, [esp + 0 + 4 + 2*4]                     

		;line 2698+1 libavcodec/x86/h264_intrapredadsdmd    
			sub eax, edx                                     
			lea ecx, [eax+edx*2]                             
		movd mm0, [eax-4]                                

		;line 2701+0 libavcodec/x86/h264_intrapredadsdmd    
			punpckldq mm0, [eax]                             
		;line 2702+1 libavcodec/x86/h264_intrapredadsdmd    

			;line 2702+0 libavcodec/x86/h264_intrapredadsdmd    
			psllq mm0, 8                                     
			;line 2703+1 libavcodec/x86/h264_intrapredadsdmd    
			movd mm1, [ecx+edx*2-4]                          

		;line 2704+0 libavcodec/x86/h264_intrapredadsdmd    
			punpcklbw mm1, [ecx+edx*1-4]                     
		;line 2705+1 libavcodec/x86/h264_intrapredadsdmd    
			movd mm2, [eax+edx*2-4]                          

		;line 2706+0 libavcodec/x86/h264_intrapredadsdmd    
			punpcklbw mm2, [eax+edx*1-4]                     
		;line 2707+1 libavcodec/x86/h264_intrapredadsdmd    

			;line 2707+0 libavcodec/x86/h264_intrapredadsdmd    
			punpckhwd mm1, mm2                               
			;line 2708+1 libavcodec/x86/h264_intrapredadsdmd    

			;line 2708+0 libavcodec/x86/h264_intrapredadsdmd    
			punpckhdq mm1, mm0                               
			;line 2709+1 libavcodec/x86/h264_intrapredadsdmd    
			movq mm0, mm1                                    
			movq mm2, mm1                                    
			movq mm5, mm1                                    

			;line 2712+0 libavcodec/x86/h264_intrapredadsdmd    
			psrlq mm0, 16                                    
			;line 2713+1 libavcodec/x86/h264_intrapredadsdmd    

			;line 2713+0 libavcodec/x86/h264_intrapredadsdmd    
			psrlq mm2, 8                                     
			;line 2714+1 libavcodec/x86/h264_intrapredadsdmd    

			;line 2714+0 libavcodec/x86/h264_intrapredadsdmd    
			pavgb mm5, mm2                                   
			;line 2715+1 libavcodec/x86/h264_intrapredadsdmd    
			movq mm4, mm1                                    
			;line 2715+0 libavcodec/x86/h264_intrapredadsdmd    

			pavgb mm1, mm0                                   

			pxor mm0, mm4                                    
			movq mm3, mm2                                    

			pand mm0, [ff_pb_1]                              

		psubusb mm1, mm0                                 

			pavgb mm3, mm1                                   
			;line 2716+1 libavcodec/x86/h264_intrapredadsdmd    

			;line 2716+0 libavcodec/x86/h264_intrapredadsdmd    
			punpcklbw mm5, mm3                               
			;line 2717+1 libavcodec/x86/h264_intrapredadsdmd    

			;line 2717+0 libavcodec/x86/h264_intrapredadsdmd    
			psrlq mm3, 32                                    
			;line 2718+1 libavcodec/x86/h264_intrapredadsdmd    
			movq mm4, mm5                                    
			;line 2718+0 libavcodec/x86/h264_intrapredadsdmd    

			psllq mm3, (8-6)*8                               

			psrlq mm4, 6*8                                   

			por mm3, mm4                                     
			;line 2719+1 libavcodec/x86/h264_intrapredadsdmd    
			movd [ecx+edx*2], mm5                            

			;line 2720+0 libavcodec/x86/h264_intrapredadsdmd    
			psrlq mm5, 16                                    
			;line 2721+1 libavcodec/x86/h264_intrapredadsdmd    
			movd [ecx+edx*1], mm5                            

			;line 2722+0 libavcodec/x86/h264_intrapredadsdmd    
			psrlq mm5, 16                                    
			;line 2723+1 libavcodec/x86/h264_intrapredadsdmd    
			movd [eax+edx*2], mm5                            
			movd [eax+edx*1], mm3                            
			ret                                              

	}
}

NAKED void ff_pred4x4_vertical_right_mmxext(uint8_t *src, const uint8_t *topright, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]                    
		mov ecx, [esp + 0 + 4 + 1*4]                    
		mov edx, [esp + 0 + 4 + 2*4]                    

		;line 2734+1 libavcodec/x86/h264_intrapredadsdmd   
			sub eax, edx                                    
			lea ecx, [eax+edx*2]                            
		movd mm0, [eax]                                 
		movq mm5, mm0                                   
			movq mm1, [eax-8]                               
		;line 2738+0 libavcodec/x86/h264_intrapredadsdmd   

			psllq mm0, (8-7)*8                              

			psrlq mm1, 7*8                                  

			por mm0, mm1                                    
			;line 2739+1 libavcodec/x86/h264_intrapredadsdmd   

			;line 2739+0 libavcodec/x86/h264_intrapredadsdmd   
			pavgb mm5, mm0                                  
			;line 2740+1 libavcodec/x86/h264_intrapredadsdmd   
			movq mm1, [eax+edx*1-8]                         
		;line 2740+0 libavcodec/x86/h264_intrapredadsdmd   

			psllq mm0, (8-7)*8                              

			psrlq mm1, 7*8                                  

			por mm0, mm1                                    
			;line 2741+1 libavcodec/x86/h264_intrapredadsdmd   
			movq mm1, mm0                                   
			movq mm2, [eax+edx*2-8]                         
		;line 2742+0 libavcodec/x86/h264_intrapredadsdmd   

			psllq mm0, (8-7)*8                              

			psrlq mm2, 7*8                                  

			por mm0, mm2                                    
			;line 2743+1 libavcodec/x86/h264_intrapredadsdmd   
			movq mm2, mm0                                   
			movq mm3, [ecx+edx*1-8]                         
		;line 2744+0 libavcodec/x86/h264_intrapredadsdmd   

			psllq mm0, (8-7)*8                              

			psrlq mm3, 7*8                                  

			por mm0, mm3                                    
			;line 2745+1 libavcodec/x86/h264_intrapredadsdmd   
			movq mm4, mm1                                   
			;line 2745+0 libavcodec/x86/h264_intrapredadsdmd   

			pavgb mm1, mm0                                  

			pxor mm0, mm4                                   
			movq mm3, mm2                                   

			pand mm0, [ff_pb_1]                             

		psubusb mm1, mm0                                

			pavgb mm3, mm1                                  
			;line 2746+1 libavcodec/x86/h264_intrapredadsdmd   
			movq mm1, mm3                                   

			;line 2747+0 libavcodec/x86/h264_intrapredadsdmd   
			psrlq mm3, 16                                   
			;line 2748+1 libavcodec/x86/h264_intrapredadsdmd   

			;line 2748+0 libavcodec/x86/h264_intrapredadsdmd   
			psllq mm1, 48                                   
			;line 2749+1 libavcodec/x86/h264_intrapredadsdmd   
			movd [eax+edx*1], mm5                           
			movd [eax+edx*2], mm3                           
			movq mm2, mm1                                   
			;line 2751+0 libavcodec/x86/h264_intrapredadsdmd   

			psllq mm5, (8-7)*8                              

			psrlq mm2, 7*8                                  

			por mm5, mm2                                    
			;line 2752+1 libavcodec/x86/h264_intrapredadsdmd   

			;line 2752+0 libavcodec/x86/h264_intrapredadsdmd   
			psllq mm1, 8                                    
			;line 2753+1 libavcodec/x86/h264_intrapredadsdmd   
			movd [ecx+edx*1], mm5                           

			;line 2754+0 libavcodec/x86/h264_intrapredadsdmd   
			psllq mm3, (8-7)*8                              

			psrlq mm1, 7*8                                  

			por mm3, mm1                                    
			;line 2755+1 libavcodec/x86/h264_intrapredadsdmd   
			movd [ecx+edx*2], mm3                           
			ret                                             

	}
}

NAKED void ff_pred4x4_down_right_mmxext (uint8_t *src, const uint8_t *topright, int stride)
{
	__asm {
		mov eax, [esp + 0 + 4 + 0*4]                        
		mov ecx, [esp + 0 + 4 + 1*4]                        
		mov edx, [esp + 0 + 4 + 2*4]                        

		;line 2765+1 libavcodec/x86/h264_intrapredadsdmd       
			sub eax, edx                                        
			lea ecx, [eax+edx*2]                                
		movq mm1, [ecx-8]                                   
		movq mm2, [eax+edx*1-8]                             

		;;line 2769+0 libavcodec/x86/h264_intrapredadsdmd       
			punpckhbw mm2, [eax-8]                              
		;;line 2770+1 libavcodec/x86/h264_intrapredadsdmd       
			movd mm3, [eax]                                     

		;;line 2771+0 libavcodec/x86/h264_intrapredadsdmd       
			punpckhwd mm1, mm2                                  
			;;line 2772+1 libavcodec/x86/h264_intrapredadsdmd       

			;;line 2772+0 libavcodec/x86/h264_intrapredadsdmd       
			psllq mm3, (8-5)*8                                  

			psrlq mm1, 5*8                                      

			por mm3, mm1                                        
			;			;line 2773+1 libavcodec/x86/h264_intrapredadsdmd       
			movq mm1, mm3                                       
			movq mm4, [ecx+edx*1-8]                             
		;		;line 2774+0 libavcodec/x86/h264_intrapredadsdmd       

			psllq mm3, (8-7)*8                                  

			psrlq mm4, 7*8                                      

			por mm3, mm4                                        
			;	;line 2775+1 libavcodec/x86/h264_intrapredadsdmd       
			movq mm2, mm3                                       
			movq mm4, [ecx+edx*2-8]                             
		;;line 2776+0 libavcodec/x86/h264_intrapredadsdmd       

			psllq mm3, (8-7)*8                                  

			psrlq mm4, 7*8                                      

			por mm3, mm4                                        
			;;line 2777+1 libavcodec/x86/h264_intrapredadsdmd       
			movq mm4, mm3                                       
			;;line 2777+0 libavcodec/x86/h264_intrapredadsdmd       

			pavgb mm3, mm1                                      

			pxor mm1, mm4                                       
			movq mm0, mm2                                       

			pand mm1, [ff_pb_1]                                 

		psubusb mm3, mm1                                    

			pavgb mm0, mm3                                      
			;;line 2778+1 libavcodec/x86/h264_intrapredadsdmd       
			movd [ecx+edx*2], mm0                               

			;;line 2779+0 libavcodec/x86/h264_intrapredadsdmd       
			psrlq mm0, 8                                        
			;;line 2780+1 libavcodec/x86/h264_intrapredadsdmd       
			movd [ecx+edx*1], mm0                               

			;;line 2781+0 libavcodec/x86/h264_intrapredadsdmd       
			psrlq mm0, 8                                        
			;;line 2782+1 libavcodec/x86/h264_intrapredadsdmd       
			movd [eax+edx*2], mm0                               

			;;line 2783+0 libavcodec/x86/h264_intrapredadsdmd       
			psrlq mm0, 8                                        
			;;line 2784+1 libavcodec/x86/h264_intrapredadsdmd       
			movd [eax+edx*1], mm0                               
			ret
	}
}