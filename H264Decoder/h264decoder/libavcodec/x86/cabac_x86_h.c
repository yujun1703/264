/*
from cabac_x86.h
*/

#define NAKED __declspec(naked)


#include "libavcodec/cabac.h"
#include "libavutil/attributes.h"
#include "libavutil/x86_cpu.h"
#include "config.h"

extern const uint8_t ff_h264_norm_shift[512];
extern uint8_t ff_h264_mlps_state[4*64];
extern uint8_t ff_h264_lps_range[4*2*64];  ///< rangeTabLPS

int __declspec(naked) get_cabac_inline_x86(CABACContext *c, uint8_t *const state)
{
	__asm {
	sub    esp,0x18
	// stack info
	// state		[esp+32]
	// c			[esp+28]
	// return_addr	[esp+24]
	//				[esp+20]			// ebp
	//				[esp+16]			// edi
	//				[esp+12]			// esi
	//				[esp+8 ]			// ebx
	//				[esp+4 ]
	//				[esp   ]

	mov    edx,DWORD PTR [esp+0x1c]      // edx= c    
	mov    DWORD PTR [esp+0x14],ebp      // save ebp to [esp+0x14]    
	mov    ebp,DWORD PTR [esp+0x20]      // ebp = state
	mov    DWORD PTR [esp+0x8],ebx       // save ebx to [esp+0x8]
	mov    DWORD PTR [esp+0xc],esi       // save esi to [esp+0xc]    
	mov    DWORD PTR [esp+0x10],edi      // save edi to [esp+0x10]
	mov    esi,DWORD PTR [edx]           // esi=c->low    
	mov    ebx,DWORD PTR [edx+0x4]       // ebx=c->range    
	movzx  edi,BYTE PTR [ebp+0x0]        // edi=*state    
	mov    eax,ebx                           
	and    ebx,0xc0                          
	movzx  ebx,BYTE PTR [ff_h264_lps_range+edi+ebx*2+0x0]      
                                          
	sub    eax,ebx                           
	mov    ecx,eax                           
	shl    eax,0x11                          
	sub    eax,esi                           
	sar    eax,0x1f                          
	sub    ebx,ecx                           
	and    ebx,eax                           
	add    ebx,ecx                           
	shl    ecx,0x11                          
	and    ecx,eax                           
	sub    esi,ecx                           
	xor    edi,eax                           
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+ebx+0x0]            
	shl    ebx,cl                            
	movzx  eax,BYTE PTR [ff_h264_mlps_state+edi+0x80]           
	shl    esi,cl                            
	mov    BYTE PTR [ebp+0x0],al             
	test   si,si                             
	jne    get_cabac_inline_x86end           
	mov    ecx,DWORD PTR [edx+0x10]          
	add    DWORD PTR [edx+0x10],0x2          
	movzx  eax,WORD PTR [ecx]                
	lea    ecx,[esi-0x1]                     
	xor    ecx,esi                           
	shr    ecx,0xf                           
	bswap  eax                               
	shr    eax,0xf                           
	movzx  ecx,BYTE PTR [ff_h264_norm_shift+ecx+0x0]            
	sub    eax,0xffff                        
	neg    ecx                               
	add    ecx,0x7                           
	shl    eax,cl                            
	add    esi,eax                           
get_cabac_inline_x86end:                  
	mov    eax,edi                           
	mov    DWORD PTR [edx],esi               
	and    eax,0x1                           
	mov    DWORD PTR [edx+0x4],ebx           
	mov    ebx,DWORD PTR [esp+0x8]           
	mov    esi,DWORD PTR [esp+0xc]           
	mov    edi,DWORD PTR [esp+0x10]          
	mov    ebp,DWORD PTR [esp+0x14]          
	add    esp,0x18                          
	ret                                      

	}
}


int __declspec(naked) get_cabac_bypass_sign_x86(CABACContext *c, int val)
{
	__asm {
		// stack info
		// val			[esp+8]
		// c            [esp+4]
		// return_Addr  [esp]

	sub    esp,0x8
		// current stack info
		// val			[esp+16]
		// c            [esp+12]
		// return_Addr  [esp+8]
		//              [esp+4]			// esi
        //              [esp]			// ebx

 	mov    DWORD PTR [esp+0x4],esi		// save esiµ½[esp+4]
 	mov    ecx,DWORD PTR [esp+0x10]     // ecx =val
 	mov    DWORD PTR [esp],ebx          // save ebxµ½[esp]
 	mov    esi,DWORD PTR [esp+0xc]		// ebx = c
 	
	mov    ebx,DWORD PTR [esi+0x4]      // ebx = c->range
 	mov    eax,DWORD PTR [esi]          // eax = c->low
 	shl    ebx,0x11                     
 	add    eax,eax                      
 	sub    eax,ebx                      
 	cdq                                 
 	and    ebx,edx                      
 	add    eax,ebx                      
 	xor    ecx,edx                      
 	sub    ecx,edx                      
 	test   ax,ax                        
 	jne    get_cabac_bypass_sign_x86end 
 	mov    ebx,DWORD PTR [esi+0x10]     // ebx = c->bytestream
 	sub    eax,0xffff                   
 	movzx  edx,WORD PTR [ebx]           
 	bswap  edx                          
 	shr    edx,0xf                      
 	add    ebx,0x2                      
 	add    eax,edx                      
 	mov    DWORD PTR [esi+0x10],ebx     
 get_cabac_bypass_sign_x86end:        
 	mov    DWORD PTR [esi],eax          
 	mov    eax,ecx                      
 	mov    ebx,DWORD PTR [esp]          
 	mov    esi,DWORD PTR [esp+0x4]      
 	add    esp,0x8                      
 	ret
	}
}