typedef unsigned char uint8_t;
typedef unsigned char pixel;

void __declspec(naked) put_qpel16_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                        
	mov    DWORD PTR [esp],ebx            
	mov    edx,DWORD PTR [esp+0x10]       
	mov    DWORD PTR [esp+0x4],esi        
	mov    ecx,DWORD PTR [esp+0xc]        
	mov    esi,0x10                       
	mov    ebx,DWORD PTR [esp+0x14]       
	lea    eax,[ebx+ebx*1]                
                                       
put_qpel16_mc00_mmx2loop:             
	movq   mm0,QWORD PTR [edx]            
	movq   mm4,QWORD PTR [edx+0x8]        
	movq   mm1,QWORD PTR [edx+ebx*1]      
	movq   mm5,QWORD PTR [edx+ebx*1+0x8]  
	movq   QWORD PTR [ecx],mm0            
	movq   QWORD PTR [ecx+0x8],mm4        
	movq   QWORD PTR [ecx+ebx*1],mm1      
	movq   QWORD PTR [ecx+ebx*1+0x8],mm5  
	add    edx,eax                        
	add    ecx,eax                        
	movq   mm0,QWORD PTR [edx]            
	movq   mm4,QWORD PTR [edx+0x8]        
	movq   mm1,QWORD PTR [edx+ebx*1]      
	movq   mm5,QWORD PTR [edx+ebx*1+0x8]  
	movq   QWORD PTR [ecx],mm0            
	movq   QWORD PTR [ecx+0x8],mm4        
	movq   QWORD PTR [ecx+ebx*1],mm1      
	movq   QWORD PTR [ecx+ebx*1+0x8],mm5  
	add    edx,eax                        
	add    ecx,eax                        
	sub    esi,0x4                        
	jne    put_qpel16_mc00_mmx2loop       
	mov    ebx,DWORD PTR [esp]            
	mov    esi,DWORD PTR [esp+0x4]        
	add    esp,0x8                        
	ret
	}
}

void __declspec(naked) avg_qpel16_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x10                      
	mov    edx,0x10                      
	mov    DWORD PTR [esp+0xc],ebp       
	mov    ecx,DWORD PTR [esp+0x18]      
	mov    ebp,DWORD PTR [esp+0x14]      
	mov    DWORD PTR [esp],ebx           
	mov    ebx,DWORD PTR [esp+0x1c]      
	mov    DWORD PTR [esp+0x4],esi       
	mov    DWORD PTR [esp+0x8],edi       
	mov    esi,ecx                       
	mov    edi,ebp                       
	lea    eax,[ebx+ebx*1]               
avg_qpel16_mc00_mmx2_2a1fa:          
	movq   mm0,QWORD PTR [edi]           
	movq   mm1,QWORD PTR [edi+ebx*1]     
	pavgb  mm0,QWORD PTR [esi]           
	pavgb  mm1,QWORD PTR [esi+ebx*1]     
	movq   QWORD PTR [edi],mm0           
	movq   QWORD PTR [edi+ebx*1],mm1     
	add    esi,eax                       
	add    edi,eax                       
	movq   mm0,QWORD PTR [edi]           
	movq   mm1,QWORD PTR [edi+ebx*1]     
	pavgb  mm0,QWORD PTR [esi]           
	pavgb  mm1,QWORD PTR [esi+ebx*1]     
	add    esi,eax                       
	movq   QWORD PTR [edi],mm0           
	movq   QWORD PTR [edi+ebx*1],mm1     
	add    edi,eax                       
	sub    edx,0x4                       
	jne    avg_qpel16_mc00_mmx2_2a1fa    
	mov    edx,0x10                      
	lea    esi,[ecx+0x8]                 
	lea    edi,[ebp+0x8]                 
	lea    eax,[ebx+ebx*1]               
avg_qpel16_mc00_mmx2_2a23f:          
	movq   mm0,QWORD PTR [edi]           
	movq   mm1,QWORD PTR [edi+ebx*1]     
	pavgb  mm0,QWORD PTR [esi]           
	pavgb  mm1,QWORD PTR [esi+ebx*1]     
	movq   QWORD PTR [edi],mm0           
	movq   QWORD PTR [edi+ebx*1],mm1     
	add    esi,eax                       
	add    edi,eax                       
	movq   mm0,QWORD PTR [edi]           
	movq   mm1,QWORD PTR [edi+ebx*1]     
	pavgb  mm0,QWORD PTR [esi]           
	pavgb  mm1,QWORD PTR [esi+ebx*1]     
	add    esi,eax                       
	movq   QWORD PTR [edi],mm0           
	movq   QWORD PTR [edi+ebx*1],mm1     
	add    edi,eax                       
	sub    edx,0x4                       
	jne    avg_qpel16_mc00_mmx2_2a23f    
	mov    ebx,DWORD PTR [esp]           
	mov    esi,DWORD PTR [esp+0x4]       
	mov    edi,DWORD PTR [esp+0x8]       
	mov    ebp,DWORD PTR [esp+0xc]       
	add    esp,0x10                      
	ret
	}
}
void __declspec(naked) put_qpel8_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                   
	mov    DWORD PTR [esp],ebx       
	mov    edx,DWORD PTR [esp+0x10]  
	mov    DWORD PTR [esp+0x4],esi   
	mov    ecx,DWORD PTR [esp+0xc]   
	mov    esi,0x8                   
	mov    ebx,DWORD PTR [esp+0x14]  
	lea    eax,[ebx+ebx*1]           
                                  
put_qpel8_mc00_mmx2loop:         
	movq   mm0,QWORD PTR [edx]       
	movq   mm1,QWORD PTR [edx+ebx*1] 
	movq   QWORD PTR [ecx],mm0       
	movq   QWORD PTR [ecx+ebx*1],mm1 
	add    edx,eax                   
	add    ecx,eax                   
	movq   mm0,QWORD PTR [edx]       
	movq   mm1,QWORD PTR [edx+ebx*1] 
	movq   QWORD PTR [ecx],mm0       
	movq   QWORD PTR [ecx+ebx*1],mm1 
	add    edx,eax                   
	add    ecx,eax                   
	sub    esi,0x4                   
	jne    put_qpel8_mc00_mmx2loop   
	mov    ebx,DWORD PTR [esp]       
	mov    esi,DWORD PTR [esp+0x4]   
	add    esp,0x8                   
	ret
	}
}
void __declspec(naked) avg_qpel8_mc00_mmx2(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                       
	mov    ecx,0x8                       
	mov    DWORD PTR [esp],esi           
	mov    edx,DWORD PTR [esp+0x14]      
	mov    DWORD PTR [esp+0x4],edi       
	mov    esi,DWORD PTR [esp+0x10]      
	mov    edi,DWORD PTR [esp+0xc]       
	lea    eax,[edx+edx*1]               
avg_qpel8_mc00_mmx2loop:             
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
	jne    avg_qpel8_mc00_mmx2loop       
	mov    esi,DWORD PTR [esp]           
	mov    edi,DWORD PTR [esp+0x4]       
	add    esp,0x8                       
	ret
	}
}
void __declspec(naked) put_qpel16_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                        
	mov    DWORD PTR [esp],ebx            
	mov    edx,DWORD PTR [esp+0x10]       
	mov    DWORD PTR [esp+0x4],esi        
	mov    ecx,DWORD PTR [esp+0xc]        
	mov    esi,0x10                       
	mov    ebx,DWORD PTR [esp+0x14]       
	lea    eax,[ebx+ebx*1]                
                                       
put_qpel16_mc00_3dnowloop:            
	movq   mm0,QWORD PTR [edx]            
	movq   mm4,QWORD PTR [edx+0x8]        
	movq   mm1,QWORD PTR [edx+ebx*1]      
	movq   mm5,QWORD PTR [edx+ebx*1+0x8]  
	movq   QWORD PTR [ecx],mm0            
	movq   QWORD PTR [ecx+0x8],mm4        
	movq   QWORD PTR [ecx+ebx*1],mm1      
	movq   QWORD PTR [ecx+ebx*1+0x8],mm5  
	add    edx,eax                        
	add    ecx,eax                        
	movq   mm0,QWORD PTR [edx]            
	movq   mm4,QWORD PTR [edx+0x8]        
	movq   mm1,QWORD PTR [edx+ebx*1]      
	movq   mm5,QWORD PTR [edx+ebx*1+0x8]  
	movq   QWORD PTR [ecx],mm0            
	movq   QWORD PTR [ecx+0x8],mm4        
	movq   QWORD PTR [ecx+ebx*1],mm1      
	movq   QWORD PTR [ecx+ebx*1+0x8],mm5  
	add    edx,eax                        
	add    ecx,eax                        
	sub    esi,0x4                        
	jne    put_qpel16_mc00_3dnowloop      
	mov    ebx,DWORD PTR [esp]            
	mov    esi,DWORD PTR [esp+0x4]        
	add    esp,0x8                        
	ret                                   
	}
}
void __declspec(naked) avg_qpel16_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x10                        
	mov    edx,0x10                        
	mov    DWORD PTR [esp+0xc],ebp         
	mov    ecx,DWORD PTR [esp+0x18]        
	mov    ebp,DWORD PTR [esp+0x14]        
	mov    DWORD PTR [esp],ebx             
	mov    ebx,DWORD PTR [esp+0x1c]        
	mov    DWORD PTR [esp+0x4],esi         
	mov    DWORD PTR [esp+0x8],edi         
	mov    esi,ecx                         
	mov    edi,ebp                         
	lea    eax,[ebx+ebx*1]                 
avg_qpel16_mc00_3dnow_1027a:           
	movq   mm0,QWORD PTR [edi]             
	movq   mm1,QWORD PTR [edi+ebx*1]       
	pavgusb mm0,QWORD PTR [esi]            
	pavgusb mm1,QWORD PTR [esi+ebx*1]      
	movq   QWORD PTR [edi],mm0             
	movq   QWORD PTR [edi+ebx*1],mm1       
	add    esi,eax                         
	add    edi,eax                         
	movq   mm0,QWORD PTR [edi]             
	movq   mm1,QWORD PTR [edi+ebx*1]       
	pavgusb mm0,QWORD PTR [esi]            
	pavgusb mm1,QWORD PTR [esi+ebx*1]      
	add    esi,eax                         
	movq   QWORD PTR [edi],mm0             
	movq   QWORD PTR [edi+ebx*1],mm1       
	add    edi,eax                         
	sub    edx,0x4                         
	jne    avg_qpel16_mc00_3dnow_1027a     
	mov    edx,0x10                        
	lea    esi,[ecx+0x8]                   
	lea    edi,[ebp+0x8]                   
	lea    eax,[ebx+ebx*1]                 
avg_qpel16_mc00_3dnow_102c3:           
	movq   mm0,QWORD PTR [edi]             
	movq   mm1,QWORD PTR [edi+ebx*1]       
	pavgusb mm0,QWORD PTR [esi]            
	pavgusb mm1,QWORD PTR [esi+ebx*1]      
	movq   QWORD PTR [edi],mm0             
	movq   QWORD PTR [edi+ebx*1],mm1       
	add    esi,eax                         
	add    edi,eax                         
	movq   mm0,QWORD PTR [edi]             
	movq   mm1,QWORD PTR [edi+ebx*1]       
	pavgusb mm0,QWORD PTR [esi]            
	pavgusb mm1,QWORD PTR [esi+ebx*1]      
	add    esi,eax                         
	movq   QWORD PTR [edi],mm0             
	movq   QWORD PTR [edi+ebx*1],mm1       
	add    edi,eax                         
	sub    edx,0x4                         
	jne    avg_qpel16_mc00_3dnow_102c3     
	mov    ebx,DWORD PTR [esp]             
	mov    esi,DWORD PTR [esp+0x4]         
	mov    edi,DWORD PTR [esp+0x8]         
	mov    ebp,DWORD PTR [esp+0xc]         
	add    esp,0x10                        
	ret
	}
}
void __declspec(naked) put_qpel8_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                    
	mov    DWORD PTR [esp],ebx        
	mov    edx,DWORD PTR [esp+0x10]   
	mov    DWORD PTR [esp+0x4],esi    
	mov    ecx,DWORD PTR [esp+0xc]    
	mov    esi,0x8                    
	mov    ebx,DWORD PTR [esp+0x14]   
	lea    eax,[ebx+ebx*1]            
	                                  
put_qpel8_mc00_3dnowloop:         
	movq   mm0,QWORD PTR [edx]        
	movq   mm1,QWORD PTR [edx+ebx*1]  
	movq   QWORD PTR [ecx],mm0        
	movq   QWORD PTR [ecx+ebx*1],mm1  
	add    edx,eax                    
	add    ecx,eax                    
	movq   mm0,QWORD PTR [edx]        
	movq   mm1,QWORD PTR [edx+ebx*1]  
	movq   QWORD PTR [ecx],mm0        
	movq   QWORD PTR [ecx+ebx*1],mm1  
	add    edx,eax                    
	add    ecx,eax                    
	sub    esi,0x4                    
	jne    put_qpel8_mc00_3dnowloop   
	mov    ebx,DWORD PTR [esp]        
	mov    esi,DWORD PTR [esp+0x4]    
	add    esp,0x8                    
	ret
	}
}
void __declspec(naked) avg_qpel8_mc00_3dnow(uint8_t *dst, uint8_t *src, int stride)
{
	__asm{
	sub    esp,0x8                    
	mov    ecx,0x8                    
	mov    DWORD PTR [esp],esi        
	mov    edx,DWORD PTR [esp+0x14]   
	mov    DWORD PTR [esp+0x4],edi    
	mov    esi,DWORD PTR [esp+0x10]   
	mov    edi,DWORD PTR [esp+0xc]    
	lea    eax,[edx+edx*1]            
avg_qpel8_mc00_3dnowloop:         
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
	jne    avg_qpel8_mc00_3dnowloop   
	mov    esi,DWORD PTR [esp]        
	mov    edi,DWORD PTR [esp+0x4]    
	add    esp,0x8                    
	ret
	}
}
