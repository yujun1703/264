/*
 * Copyright (c) 2001 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * @file
 * libavcodec API use example.
 *
 * Note that libavcodec only handles codecs (mpeg, mpeg4, etc...),
 * not file formats (avi, vob, mp4, mov, mkv, mxf, flv, mpegts, mpegps, etc...). See library 'libavformat' for the
 * format handling
 */
#define  _CRT_SECURE_NO_WARNINGS

//#include "libavutil/imgutils.h"
//#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
//#include "libavutil/mathematics.h"
//#include "libavutil/samplefmt.h"

#include "ffmpeg-h264-decoder.h"

#define SAFE_AV_FREE( ptr ) if ( NULL != ptr ) { av_free( ptr ); ptr = NULL;}

//version
static unsigned int g_Version = 2012053100;

typedef struct _h264_decoder
{
    AVCodec* ex_codec;
    AVCodecContext* ex_avctx;
    AVFrame* ex_picture;
    AVPacket ex_avpkt;
} h264_decoder;

extern AVCodec ff_h264_decoder;
extern void av_free(void *ptr);
extern void *av_malloc(size_t size);

static AVCodec* ff_create_h264_decoder()
{
    AVCodec* h = av_malloc( sizeof(AVCodec) );
    if ( NULL != h )
    {
        memcpy(h, &ff_h264_decoder, sizeof(ff_h264_decoder));
    }
    
    return h;
}

static void ff_release_h264_decoder(AVCodec** pp)
{
    if ( NULL != pp )
    {
        if ( NULL != *pp )
        {
            av_free( *pp );
            *pp = NULL;
        }
    }
}


static void release_h264_decoder(h264_decoder** pp)
{
	if ( NULL != pp )
	{
    	h264_decoder* p = *pp;
		if ( NULL != p )
		{
		    int ret = avcodec_close( p->ex_avctx );
            
			SAFE_AV_FREE( p->ex_picture );
			SAFE_AV_FREE( p->ex_avctx   );
			SAFE_AV_FREE( p->ex_codec   );
			SAFE_AV_FREE( *pp );
			*pp = NULL;
		}
	}
}

static h264_decoder* create_h264_decoder()
{
    h264_decoder* h = av_malloc( sizeof(h264_decoder) );
    
    if ( NULL != h )
    {
        AVCodec        *codec = NULL;
        AVCodecContext *avctx = NULL;
        AVFrame        *picture = NULL;
    
        av_init_packet( &(h->ex_avpkt) );

        picture = avcodec_alloc_frame();        
        codec = ff_create_h264_decoder();
        if ( NULL == picture || NULL == codec )
        {
            goto failed;
        }
        
        avctx = avcodec_alloc_context3( codec );
        if ( avctx == NULL )
        {
            goto failed;
        }        

        if( codec->capabilities&CODEC_CAP_TRUNCATED )
        {
            avctx->flags|= CODEC_FLAG_TRUNCATED; /* we do not send complete frames */
        }

        //zhs
        avctx->flags2 |= CODEC_FLAG2_CHUNKS;
        
        /* For some codecs, such as msmpeg4 and mpeg4, width and height
           MUST be initialized there because this information is not
           available in the bitstream. */
        
        /* open it */
        if (avcodec_open2(avctx, codec) < 0) 
        {
            goto failed;            
        }

        h->ex_avctx = avctx;
        h->ex_codec = codec;
        h->ex_picture = picture;
    }

    return h;
failed:
    release_h264_decoder( &h );
    return NULL;
}

static dec_stats h264_decode_frame
(
    h264_decoder* decoder, 
    unsigned char* stream, unsigned int stream_length, 
    unsigned char* pout,  unsigned int* pout_len,
    unsigned int* pwidth, unsigned int *pheight,
    unsigned int* p_frame_count)
{
    int got_picture, len;    
    unsigned int actual_outbuf_len = 0;
    AVCodecContext* avctx;
    AVFrame*        picture;
    AVPacket*       avpkt;
    static unsigned int frame = 0;
    unsigned char* out_ptr;
    dec_stats ret;
    
    out_ptr = pout;

    avctx = decoder->ex_avctx;
    picture = decoder->ex_picture;
    avpkt = &(decoder->ex_avpkt);

    avpkt->data = stream;
    avpkt->size = stream_length;

    len = avcodec_decode_video2(avctx, picture, &got_picture, avpkt);
    if ( 0 > len )
    {
        *pout_len = 0;
        ret = dec_failed;
        goto exit;
    }

    if ( 0==got_picture )
    {
        *pout_len = 0;
        ret = dec_padding;
    }
    else
    {
        int h, stride, cpy_length;
        int width = avctx->width;
        int height = avctx->height;            
        unsigned int curr_frame_size = (width * height * 3)/2; //todo set by yuv-format
        unsigned char* ptr;

        if ( curr_frame_size > *pout_len )
        {
            ret = dec_mem_shortage;
            goto exit;
        }

        ptr = picture->data[ 0 ];
        stride = picture->linesize[0];
        cpy_length = width;
        for ( h = 0; h < height; h++)
        {
            memcpy(out_ptr, ptr, cpy_length);
            out_ptr += cpy_length;
            ptr += stride;
        }

        ptr = picture->data[ 1 ];
        stride = picture->linesize[1];
        cpy_length = width/2;
        for ( h = 0; h < height/2; h++)
        {
            memcpy(out_ptr, ptr,cpy_length);
            out_ptr += cpy_length;
            ptr += stride;
        }

        ptr = picture->data[ 2 ];
        stride = picture->linesize[2];
        cpy_length = width/2;
        for ( h = 0; h < height/2; h++)
        {
            memcpy(out_ptr, ptr, cpy_length);
            out_ptr += cpy_length;
            ptr += stride;
        }

        frame++;

        *pout_len = curr_frame_size;

        if ( p_frame_count )
            *p_frame_count = frame;

        if ( pwidth )
            *pwidth = avctx->width;

        if ( pheight )
            *pheight = avctx->height;

        ret = dec_success;
    }

exit:
    return ret;
}


dec_stats ffh264_create_decoder(void ** pp)
{
    h264_decoder* h = create_h264_decoder();
    
    if ( NULL == pp || NULL == h ) 
        return dec_failed;

    *pp = h;

    return dec_success;
}

dec_stats ffh264_release_decoder(void** pp)
{    
    if ( NULL == pp )
        return dec_failed;

    release_h264_decoder( (h264_decoder**)pp );

    return dec_success;
}

dec_stats ffh264_decode
(
    void* decoder, 
    unsigned char* stream, unsigned int length, 
    unsigned char* pout,  unsigned int *plen,
    unsigned int* pwidth, unsigned int* pheight,
    unsigned int* p_frame_count)
{
    if ( NULL == decoder || NULL==stream || 0>length || NULL==pout || NULL==plen ) 
        return dec_failed;

    return h264_decode_frame((h264_decoder*)decoder, stream, length, pout, plen, pwidth, pheight, p_frame_count);
}

unsigned int ffh264_get_version( )
{
    return g_Version;
}

