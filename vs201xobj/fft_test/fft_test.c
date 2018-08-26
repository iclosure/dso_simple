// fft_test.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef signed char		I8	; /**/
typedef unsigned char	U8	; /**/
typedef signed short	I16	; /**/
typedef unsigned short  U16	; /**/
typedef signed long		I32	; /**/
typedef unsigned long	U32	; /**/
typedef I16				I16P; /**/
typedef U16				U16P; /**/

#define FFTN(M)     (1L<<(M))

void dsp_fft(int x[], I8 m, I8 flag);
void dsp_fft_test(void);

int main(int argc, char* argv[])
{
	dsp_fft_test();
	return 0;
}

 
#define SampleM    (10)
#define SampleN    (FFTN(SampleM))   //  采样点数
#define Nt         (2)
#define f0         (200)
//#define fs         ((SampleN) * (f0) / (Nt))

#ifndef pi
#define pi  3.141592653
#endif /*pi*/


// 从外部RAM读取256点字节型数据[可能是A/D采样数据]
void dsp_fft_test(void)
{
    int i;
    float t=0.0;
	int fftdata[1024];
	I16 drdata[600];
	float fs = 1024;
	//float f0 = 50;
	FILE *fp;
	
    for(i=0; i<1024; i++, t+=1.0/fs) {
		//for(i=0,t=0; i<1024; i++, t+=1.0/fs) {
        //fftdata[i] = 100.0 + 100.0*(6.0 + 3.0*cos(2.0*pi*fs*t+0.0*pi/180.0) + 4.5*cos(2.0*pi*200*rand()*t+0.0*pi/180.0)+ 0.5*cos(2.0*pi*1000*t+0.0*pi/180.0));
		//fftdata[i] = 100.0*(6.0 + 3.0*cos(2.0*pi*fs*t+0.0*pi/180.0) + 10*cos(rand()*100)+ 0.5*cos(2.0*pi*1000*t+0.0*pi/180.0));
        //fftdata[i] = 128*(0.5 + 0.3*cos(2.*pi*50.*t) +0.2*cos(2.*pi*75.*t) + 0.8*cos(2.*pi*2000.*t) + 0.08*cos(rand()*100));  // 直流分量为 6.
		//fftdata[i] = 25 + 25*(6.0 + 3.0 * cos(2.0*pi*fs*t+0.0*pi/180.0) + 1.2*cos(rand()*100*t));
		fftdata[i] = 100/2+100*(0.5*sin(2.*pi*50*t) + 0.2*sin(2.*pi*75*t) + 0.8*sin(2.*pi*200.*t));
	}
	
	dsp_fft(fftdata,10,1);

	fp = fopen("fft_test.txt","wb");
	for(i=0; i<600; i++)
		fprintf(fp,"%d,\r\n",fftdata[i]);
}


#define TRIG_90DEG     (1024)
#define TRIG_45DEG     ((TRIG_90DEG)>>1)
#define TRIG_180DEG    ((TRIG_90DEG)<<1)
#define TRIG_360DEG    ((TRIG_90DEG)<<2)
#define TRIG_360DEG_1  ((TRIG_360DEG)-1)

/*********************************************************************
*
*       sin / cos (internal)
*
*  Angle : 90/1024?
*  Data  : 1/1024
*/
static const U16 aSin[] = {
  0,       /*  1/16 *90?*/
  100,     /*  1/16 *90?*/
  200,     /*  2/16 *90?*/
  297,     /*  3/16 *90?*/
  392,     /*  4/16 *90?*/
  483,     /*  5/16 *90?*/
  569,     /*  6/16 *90?*/
  650,     /*  7/16 *90?*/
  724,     /*  8/16 *90?*/
  792,     /*  9/16 *90?*/
  851,     /* 10/16 *90?*/
  903,     /* 11/16 *90?*/
  946,     /* 12/16 *90?*/
  980,     /* 13/16 *90?*/
  1004,    /* 14/16 *90?*/
  1019,    /* 15/16 *90?*/
  1024     /* 16/16 *90?*/
};

/*******************************************************
*       FFT_sin [用户添加 只用于 void FFT(int x[], int m, int flag)]
*/
/* angle :0 ~ 1024/4 [that is 0 to pi/4] */
int FFT_sin(int angle) {
	int i;
	U16 factor;
	U32 t;
	
	i = angle>>6;
    factor = 64 - (angle&63);
    t = aSin[i]*factor;
    if (factor != 64)
		t += aSin[i+1]*(64-factor);
	return (t+32) >>6;   /* divide,incl. rounding [???????: t = t/64+0.5 = (t+32)>>6]*/
}

void dsp_fft(int x[], I8 m, I8 flag)
{
    int i=0,k, m1,m2,m3, n1,n2,n4;
    unsigned int angle, iADDj;
    unsigned int tp1,tp2;
    int j=0;    // 由于j在计算过程中可能会很大,要进行类型调整
    int iSUBj;
    int xt, t1,t2, ss,cc;
	
    n1 = FFTN(m)-1;
    for(; i<n1; i++)
    {
        if(i < j) {
            xt   = x[j];
            x[j] = x[i];
            x[i] = xt;
        }
		
        k = FFTN(m-1);  // k = fftN >> 1, fftN / 2 , 基II.
        while(k <= j) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }
	
    for(i=0; i<FFTN(m); i+=2)
    {
        xt     = x[i];
        x[i]   = xt + x[i+1];
        x[i+1] = xt - x[i+1];
    }
	
    n2 = 1;  // 由此限定了 e 的最大值为 e = piMUL2 / (4 * 1), 即 piMUL2/4 .
    for(k=2; k<=m; k++)
    {
        n4 = n2;
        n2 = n2 << 1;
        n1 = n2 << 1;
        for(i=0; i<FFTN(m); i+=n1)
        {
            tp1 = i + n2;
            tp2 = tp1 + n4;
            xt     = x[i];
            x[i]   = xt + x[tp1];
            x[tp1] = xt - x[tp1];
            x[tp2] = - x[tp2];
            for(j=1; j<n4; j++)
            {
                angle = (j<<12) / n1;  // angle = j*2*pi/n1 * (1024/(pi/2))=j*4096/n1
                ss = FFT_sin(angle);
                cc = FFT_sin(TRIG_90DEG - angle);
                iSUBj = i - j;
                iADDj = i + j;
                m1 = iSUBj + n2;
                m2 = iADDj + n2;
                m3 = iSUBj + n1;
                t1 = (cc*x[m2] + ss*x[m3]) >>10;
                t2 = (ss*x[m2] - cc*x[m3]) >>10;
                x[m3]    =   x[m1]    - t2;
                x[m2]    = - x[m1]    - t2;
                x[m1]    =   x[iADDj] - t1;
                x[iADDj] =   x[iADDj] + t1;
            } 
        }
    }
    
    if(flag)
    {
        // ******fftNDIV2次以下的谐波进行分析****** 
        // 换算成实际的幅度(由于左右对称, 这里可以选择只计算需要的前一半数据)
        // 假设原始信号的峰值为 A, 那么 FFT的结果的每个点 (除了第一个点直流分量之外) 的模值就是 A的 1/N 倍.
        // 而第一个点就是直流分量, 它的模值就是直流分量的 2/N 倍.
		unsigned int index;
        for(i=1; i<FFTN(m-1); i++)
        {
            index = FFTN(m) - i;
            x[i] = (int) sqrt(x[i]*x[i] + x[index]*x[index]);  // 计算FFT变换后的模量，并存到x的前
            x[i] /= FFTN(m-1);
        }
        
        x[0] =  abs(x[0]) / FFTN(m-1);    // 直流分量
    }
    
}

