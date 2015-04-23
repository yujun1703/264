#ifndef FFMPEG_H264_AVC_DECODER_
#define FFMPEG_H264_AVC_DECODER_

#ifdef __cplusplus 
extern "C" { 
#endif

typedef enum _decode_status
{
    dec_success,
    dec_padding,
    dec_mem_shortage, 
    dec_failed
} dec_stats;

dec_stats ffh264_create_decoder(void ** pp);

dec_stats ffh264_release_decoder(void** pp);

dec_stats ffh264_decode
(
    void* decoder, 
    unsigned char* stream, unsigned int length, 
    unsigned char* pout,  unsigned int* plen,
    unsigned int* pwidth, unsigned int* pheight,
    unsigned int* p_frame_count
);

unsigned int ffh264_get_version();

#ifdef __cplusplus 
} 
#endif

#endif