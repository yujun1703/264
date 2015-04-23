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
#define H264_CSP_VFLIP          0x1000  // ͼ���Ƿ���
// ��ɫ���þ���:
// ���ͼ�����ɫ�ռ� YUV420, ������ csp = H264_CSP_I420
// ���ͼ�����ɫ�ռ� RGB24, ������ csp = H264_CSP_RGB
// �������RGB��ͼ����������ɫ���ԣ����볢�� H264_CSP_BGR
// ���ͼ�����ɫ�ռ� RGB24, ����ͼ���ǵ����ģ������� csp = (H264_CSP_RGB | H264_CSP_VFLIP);
// 

typedef struct CodecContext
{
	int width;               // in:  ͼ���
	int height;              // in:  ͼ���
	int csp;                 // in:  ������ɫ�ռ�
	unsigned char * data_in; // in:  ԭʼ����
	int data_in_size;        // in:  һ֡ԭʼ���ݵĴ�С
	unsigned char * buffer;  // out: �������ݻ�����
	int buffer_in_size;      // in:  �������ݻ������ռ��С
	int buffer_out_size;     // out: �������������Ч����
	int frame_rate;          // in:  ֡��
	int key_frame_interval;  // in:  �������ؼ�֡��࣬������0��ȡĬ��ֵ
	int key_frame;           // out: �Ƿ�ؼ�֡��0Ϊ�ǹؼ�֡��1Ϊ�ǹؼ�֡

} H264CodecContext;

int  H264EncoderOpen (H264CodecContext * ctx);
int  H264EncoderEncode(H264CodecContext * ctx);
void H264EncoderClose(H264CodecContext * ctx);

#ifdef __cplusplus
}
#endif

#endif
