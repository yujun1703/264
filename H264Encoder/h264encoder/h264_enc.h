#ifndef _H264_ENC_H
#define _H264_ENC_H 1

#ifdef __cplusplus
extern "C" {
#endif

#define H264_CSP_I420           0x0001  // yuv 4:2:0 planar
#define H264_CSP_I422           0x0002  // yuv 4:2:2 planar
#define H264_CSP_I444           0x0003  // yuv 4:4:4 planar
#define H264_CSP_YV12           0x0004  // yuv 4:2:0 planar
#define H264_CSP_YUYV           0x0005  // yuv 4:2:2 packed
#define H264_CSP_RGB            0x0006  // rgb 24bits
#define H264_CSP_BGR            0x0007  // bgr 24bits
#define H264_CSP_BGRA           0x0008  // bgr 32bits
#define H264_CSP_VFLIP          0x1000  // 图像是否倒立
// 颜色设置举例:
// 如果图像的颜色空间 YUV420, 则设置 csp = H264_CSP_I420
// 如果图像的颜色空间 RGB24, 则设置 csp = H264_CSP_RGB
// 如果输入RGB的图像解码出来颜色不对，则请尝试 H264_CSP_BGR
// 如果图像的颜色空间 RGB24, 并且图像是倒立的，则设置 csp = (H264_CSP_RGB | H264_CSP_VFLIP);
// 

typedef struct CodecContext
{
	int width;               // in:  图像宽
	int height;              // in:  图像高
	int csp;                 // in:  设置颜色空间
	unsigned char * data_in; // in:  原始数据
	int data_in_size;        // in:  一帧原始数据的大小
	unsigned char * buffer;  // out: 编码数据缓冲区
	int buffer_in_size;      // in:  编码数据缓冲区空间大小
	int buffer_out_size;     // out: 编码后码流的有效长度
	int frame_rate;          // in:  帧率
	int key_frame_interval;  // in:  设置最大关键帧间距，若等于0则取默认值
	int key_frame;           // out: 是否关键帧，0为非关键帧，1为是关键帧

} H264CodecContext;

int  H264EncoderOpen (H264CodecContext * ctx);
int  H264EncoderEncode(H264CodecContext * ctx);
void H264EncoderClose(H264CodecContext * ctx);

#ifdef __cplusplus
}
#endif

#endif
