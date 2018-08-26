#ifndef BITMAPTYPE_H_
#define BITMAPTYPE_H_

#include "integer.h"


typedef struct tagBITMAPFILEHEADERINFO	BITMAPFILEHEADER_INFO	;  /*λͼ���ļ�ͷ�ṹ*/
typedef struct tagBITMAPINFOHEADERINFO	BITMAPINFOHEADER_INFO	;  /*λͼ���ļ�ͷ�ṹ*/
typedef struct tagRGBQUADINFO			RGBQUAD_INFO			;  /*λͼ�ĵ�ɫ��ṹ*/
typedef struct tagBMPHEADERINFO			BMPHEADER_INFO			;  /*λͼͷ��Ϣ*/

/************************************************************
 *
 *                   bmp data type
 */
#pragma pack(1)	// ��һ��������Ҫ����Ϊ�����õ��Ķ�д���ǿ��д
// λͼ���ļ�ͷ�ṹ
typedef struct tagBITMAPFILEHEADERINFO { // bmfh
	WORD	bfType;	            // λͼ�ļ�������, ����Ϊ"BM"(0x4D42) 
	DWORD	bfSize;			    // λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
	WORD	bfReserved1;		// λͼ�ļ������֣�����Ϊ0
	WORD	bfReserved2;		// λͼ�ļ������֣�����Ϊ0
	DWORD	bfOffBits;			// λͼ���ݵ���ʼλ�ã��������λͼ�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
} tBITMAPFILEHEADERINFO;

// λͼ����Ϣͷ�ṹ
typedef struct tagBITMAPINFOHEADERINFO { // bmih
	DWORD	biSize;				// λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
	LONG	biWidth;			// λͼ�Ŀ�ȣ�������Ϊ��λ
	LONG	biHeight;			// λͼ�ĸ߶ȣ�������Ϊ��λ
	WORD	biPlanes;			// Ŀ���豸�ļ��𣬱���Ϊ1
	WORD	biBitCount;			// ÿ�����������λ����������1(˫ɫ),4(16ɫ)��8(256ɫ)��24(���ɫ)֮һ
	DWORD	biCompression;		// λͼѹ�����ͣ������� 0(��ѹ��),1(BI_RLE8ѹ������)��2(BI_RLE4ѹ������)֮һ
	DWORD	biSizeImage;		// λͼ�Ĵ�С�����ֽ�Ϊ��λ
	LONG	biXPelsPerMeter;	// λͼˮƽ�ֱ���
	LONG	biYPelsPerMeter;	// λͼ��ֱ�ֱ���
	DWORD	biClrUsed;			// λͼʵ��ʹ�õ���ɫ���е���ɫ��
	DWORD	biClrImportant;		// λͼ��ʾ��������Ҫ����ɫ��
} tBITMAPINFOHEADER_INFO;
// λͼ�ĵ�ɫ��ṹ
typedef struct tagRGBQUADINFO { // rgbq
    BYTE    R;
    BYTE    G;
    BYTE    B;
    BYTE    Res;
} tRGBQUAD_INFO;
// λͼͷ��Ϣ
/* windows style*/
typedef struct tagBMPHEADERINFO{
	/* BITMAPFILEHEADER*/
	WORD	bfType;
	DWORD	bfSize;
	WORD	bfReserved1;
	WORD	bfReserved2;
	DWORD	bfOffBits;
	/* BITMAPINFOHEADER*/
	DWORD	biSize;
	LONG	biWidth;
	LONG	biHeight;
	WORD	biPlanes;
	WORD	biBitCount;
	DWORD	biCompression;
	DWORD	biSizeImage;
	LONG	biXPelsPerMeter;
	LONG	biYPelsPerMeter;
	DWORD	biClrUsed;
	DWORD	biClrImportant;
} tBMPHEADER_INFO;
#pragma pack()



#endif /*BITMAPTYPE_H_*/
