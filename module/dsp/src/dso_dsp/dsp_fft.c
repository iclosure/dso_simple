
/*
 * ***************************************************
 *                  │╖  ╓ ╔══╗ ╥ ╔══╕│
 *                  │╚══╝ ╜  ╙ ╨ ╚══╛│
 *                          DSO
 *     Universal graphic software for embedded applications
 *
 *     Copyright (c) 2011, Unic Inc., China, Sc
 *  DSO is protected by international copyright laws. Knowledge of the
 *  source code may not be used to write a similar product. This file may
 *  only be used in accordance with a license and should not be redistributed
 *  in any way. We appreciate your understanding and fairness.
 * 
 *  Project : DSC--C-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : dsp_fft.c
 Purpose     : FFT serial functions
   ----------------------------------------------------------------------
 */

#include "dsp.h"
#include <math.h>
#include "GUI_Protected.h"


/* == 函数定义 == */

/********************************************************
*          Name : dsp_fft
*      Function : 计算实序列的基二快速傅里叶变换.
*        Inputs : x[] -- 浮点数实型一维数组. 长度为n. 待转换实序列首地址 ( 开始时存放要变换数据的实部，最后存放变换结果的 );
*                 m   -- 整型变量。数据长度的对数值。必须是2的整数次幂，即n=2^M.
*                 flag -- 是否转换为实际值,flag=1表示是
*        Output : None.
*   Description : >x前n/2+1个值, 其存储顺序为[ Re(0),Re(1),...,Re(n/2),Im(n/2-1),...,Im(1)].
*                  其中Re(0)=X(0),Re(n/2)=X(n/2). 根据X(k)的共轭对称性很容易写出后半部分的值.
*                 >某点 n 所表示的频率为 : Fn=(n-1)*Fs/N. 由此可以看出, Fn 所能分辨到的频率为 Fs/N (其中 N 为采样点数).
*
*       Version : v1.0
*        Author : L.K.H.
*          date : 2011/02/25
********************************************************/
int FFT_sin(int angle);

void dsp_fft0(I16 data[], I8 m)
{
	int i=0,k, m1,m2,m3, n1,n2,n4;
	unsigned int angle, iADDj;
	unsigned int tp1,tp2;
	int j=0;    // 由于j在计算过程中可能会很大,要进行类型调整
	int iSUBj;
	int xt, t1,t2, ss,cc;
	int *x=(int*)malloc(FFTN(m)*sizeof(int));

	n1 = FFTN(m)-1;
	for(i=0; i<=n1; i++)
		x[i] = data[i];

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

	n2 = 1;  // 由此限定了 e 的最大值为 e = 2*pi / (4 * 1), 即 pi/2.
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
				// angle = j*2*pi/n1 * (1024/(pi/2))=j*4096/n1
				angle = (j<<12) / n1;  
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
	// ******fftNDIV2次以下的谐波进行分析****** 
	// 换算成实际的幅度(由于左右对称, 这里可以选择只计算需要的前一半数据)
	// 假设原始信号的峰值为 A, 那么 FFT的结果的每个点 (除了第一个点直流分量之外) 的模值就是 A的 1/N 倍.
	// 而第一个点就是直流分量, 它的模值就是直流分量的 2/N 倍.
	for(i=1; i<FFTN(m-1); i++)
	{
		k = FFTN(m) - i;
		x[i] = (int) sqrt(x[i]*x[i] + x[k]*x[k]);  // 计算FFT变换后的模量，并存到x的前
		data[i] = x[i] / FFTN(m-1);
	}

	data[0] =  abs(x[0]) / FFTN(m-1);    // 直流分量 
}
/**/
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

/********************************************************
*          Name : dsp_ifft
*      Function : 计算共轭对称实序列的基二快速傅里叶反变换，其变换结果是实数.
*        Inputs : x[] -- 浮点数实型一组数组. 长度为n. 待转换实序列首地址 ( 开始时存放要变换数据的实部，最后存放变换结果的 );
*                 m   -- 整型变量。数据长度的对数值。必须是2的整数次幂，即n=2^m.
*        Output : None.
*   Description : x[]的存储顺序为[ Re(0),Re(1),...,Re(n/2),Im(n/2-1),...,Im(1)]。
*                 其中Re(0)=X(0),Re(n/2)=X(n/2)。根据X(k)的共轭对称性很容易写出后半部分的值。
*                 最后存放变换结果x(i)(i=0,1,...,n-1)，这里x[i]是实数.
*
*       Version : v1.0
*        Author : L.K.H.s
*          date : 2011/03/06
********************************************************/
void dsp_ifft(int x[], I8 m)
{
    int i,j,k,i1,i2,i3,i4,i5,i6,i7,i8,n2,n4,n8,id,is;
    int t1,t2,t3,t4,t5,cc1,cc3,ss1,ss3;
    unsigned int angle,angle3;
    
    n2 = FFTN(m+1);
    for(k=1; k<m; k++)
    {
        is = 0;
        id = n2;
        n2 >>= 1;  // n2 = FFTN(m+1) / (2^k).
        n4 = n2 >> 2;
        n8 = n2 >> 3;
        do {
            for(i=is; i<FFTN(m); i+=id)
            {
                i1 = i;
                i2 = i1 + n4;
                i3 = i2 + n4;
                i4 = i3 + n4;
                t1    = x[i1] - x[i3];
                x[i1] = x[i1] + x[i3];
                x[i2] = 2 * x[i2];
                x[i3] = t1 - 2 * x[i4];
                x[i4] = t1 + 2 * x[i4];
                if(n4 == 1) continue;
                i1 += n8;
                i2 += n8;
                i3 += n8;
                i4 += n8;
                t1 = (x[i2] - x[i1]) * 985/1393;  // 985/1393= 1/sqrt(2)
                t2 = (x[i4] + x[i3]) * 985/1393;
                x[i1] = x[i1] + x[i2];
                x[i2] = x[i4] - x[i3];
                x[i3] = 2 * (- t2 - t1);
                x[i4] = 2 * (- t2 + t1);
            }

            is = (id << 1) - n2;
            id <<= 2;
        } while( is < FFTN(m)-1);
        
        for(j=1; j<n8; j++)
        {
			angle  = (j<<12) / n2;  // angle = j*2*pi/n2 * (1024/(pi/2))=j*4096/n2
			angle3 = 3 * angle;
			ss1 = TRIG_sin(angle);
            cc1 = TRIG_sin(angle+TRIG_90DEG);
            ss3 = TRIG_sin(angle3);
			cc3 = TRIG_sin(angle3+TRIG_90DEG);
            is = 0;
            id = n2 << 1;
            do {
                for(i=is; i<FFTN(m); i=i+id)
                {
                    i1 = i + j;
                    i2 = i1 + n4;
                    i3 = i2 + n4;
                    i4 = i3 + n4;
                    i5 = i + n4 - j;
                    i6 = i5 + n4;
                    i7 = i6 + n4;
                    i8 = i7 + n4;
                    t1 = x[i1] - x[i6];
                    x[i1] = x[i1] + x[i6];
                    t2    = x[i5] - x[i2];
                    x[i5] = x[i2] + x[i5];
                    t3    = x[i8] + x[i3];
                    x[i6] = x[i8] - x[i3];
                    t4    = x[i4] + x[i7];
                    x[i2] = x[i4] - x[i7];
                    t5 = t1 - t4;
                    t1 = t1 + t4;
                    t4 = t2 - t3;
                    t2 = t2 + t3;
                    x[i3] = (  t5*cc1 + t4*ss1) >>10;
                    x[i7] = (- t4*cc1 + t5*ss1) >>10;
                    x[i4] = (  t1*cc3 - t2*ss3) >>10;
                    x[i8] = (  t2*cc3 + t1*ss3) >>10;
                }

                is = (id << 1) - n2;
                id <<= 2;
            } while(is < FFTN(m)-1);
        }
    }

    is = 0;
    id = 4;
    do {
        for(i=is; i<FFTN(m); i+=id)
        {
            i1 = i + 1;
            t1 = x[i];
            x[i]  = t1 + x[i1];
            x[i1] = t1 - x[i1];
        }

        is = (id - 1) << 1;
        id <<= 2;
    } while(is < FFTN(m)-1);

    for(j=0,i=0; i<FFTN(m)-1; i++)
    {
        if(i < j)
        {
            t1 = x[j];
            x[j] = x[i];
            x[i] = t1;
        }
		
        k = FFTN(m-1);
        while(k < (j+1))
        {
            j = j - k;
            k = k >> 1;
        }

        j = j + k;
    }
    
    for(i=0; i<FFTN(m); i++)
        x[i] /= FFTN(m);
}

//////////////////////////////////////
//////////////////////////////////////
void dsp_rfft(float x[], I16 m, I8 flag)
{
    int i,k, m1,m2,m3, n1,n2,n4;
    unsigned int angle, iADDj;
    unsigned int tp1,tp2;
    int j;    // 由于j在计算过程中可能会很大,要进行类型调整
    int iSUBj;
    float xt, t1,t2,ss,cc;
	
    n1 = FFTN(m)-1;
    for(j=0,i=0; i<n1; i++)
    {
		
        if(i < j)
        {
            xt   = x[j];
            x[j] = x[i];
            x[i] = xt;
        }
		
        k = FFTN(m-1);  // k = fftN >> 1, fftN / 2 , 基II.
        while( k <= j )
        {
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
                angle = (j<<12) / n1; // angle = j*2*pi/n1 * (1024/(pi/2))=j*4096/n1
                ss = FFT_sin(angle)/1024.0;
                cc = FFT_sin(TRIG_90DEG-angle)/1024.0;
                iSUBj = i - j;
                iADDj = i + j;
                m1 = iSUBj + n2;
                m2 = iADDj + n2;
                m3 = iSUBj + n1;
                t1 = cc*x[m2] + ss*x[m3];
                t2 = ss*x[m2] - cc*x[m3];
                x[m3]    =   x[m1]    - t2;
                x[m2]    = - x[m1]    - t2;
                x[m1]    =   x[iADDj] - t1;
                x[iADDj] += t1;
            } 
        }
    }
    
    if(flag)
    {
        // ******fftNDIV2次以下的谐波进行分析****** 
        // 换算成实际的幅度(由于左右对称, 这里可以选择只计算需要的前一半数据)
        // 假设原始信号的峰值为 A, 那么 FFT的结果的每个点 (除了第一个点直流分量之外) 的模值就是 A的 1/N 倍.
        // 而第一个点就是直流分量, 它的模值就是直流分量的 2/N 倍.
        for(i=1; i<FFTN(m-1); i++)
        {
            unsigned int index = FFTN(m) - i;
            x[i] = sqrt(x[i]*x[i] + x[index]*x[index]);  // 计算FFT变换后的模量，并存到x的前
            x[i] /= FFTN(m-1);
        }
        
        x[0] =  fabs(x[0]) / FFTN(m-1);    // 直流分量   
    }
    
}


void dsp_rifft(float x[], I16 m)
{
    int i,j,k,i1,i2,i3,i4,i5,i6,i7,i8,n2,n4,n8,id,is;
    float t1,t2,t3,t4,t5,cc1,cc3,ss1,ss3;
    unsigned int angle,angle3;
    
    n2 = FFTN(m+1);
    for(k=1; k<m; k++)
    {
        is = 0;
        id = n2;
        n2 >>= 1;  // n2 = FFTN(m+1) / (2^k).
        n4 = n2 >> 2;
        n8 = n2 >> 3;
        do {
            for(i=is; i<FFTN(m); i+=id)
            {
                i1 = i;
                i2 = i1 + n4;
                i3 = i2 + n4;
                i4 = i3 + n4;
                t1    = x[i1] - x[i3];
                x[i1] = x[i1] + x[i3];
                x[i2] = 2 * x[i2];
                x[i3] = t1 - 2 * x[i4];
                x[i4] = t1 + 2 * x[i4];
                if(n4 == 1) continue;
                i1 += n8;
                i2 += n8;
                i3 += n8;
                i4 += n8;
                t1 = (x[i2] - x[i1]) * 985/1393;  // 985/1393= 1/sqrt(2)
                t2 = (x[i4] + x[i3]) * 985/1393;
                x[i1] = x[i1] + x[i2];
                x[i2] = x[i4] - x[i3];
                x[i3] = 2 * (- t2 - t1);
                x[i4] = 2 * (- t2 + t1);
            }

            is = (id << 1) - n2;
            id <<= 2;
        } while( is < FFTN(m)-1);
        
        for(j=1; j<n8; j++)
        {
			angle  = (j<<12) / n2;  // angle = j*2*pi/n2 * (1024/(pi/2))=j*4096/n2
			angle3 = 3 * angle;
			ss1 = TRIG_sin(angle) / 1024.0;
            cc1 = TRIG_sin(angle+TRIG_90DEG) / 1024.0;
            ss3 = TRIG_sin(angle3) / 1024.0;
			cc3 = TRIG_sin(angle3+TRIG_90DEG) / 1024.0;
            is = 0;
            id = n2 << 1;
            do {
                for(i=is; i<FFTN(m); i=i+id)
                {
                    i1 = i + j;
                    i2 = i1 + n4;
                    i3 = i2 + n4;
                    i4 = i3 + n4;
                    i5 = i + n4 - j;
                    i6 = i5 + n4;
                    i7 = i6 + n4;
                    i8 = i7 + n4;
                    t1 = x[i1] - x[i6];
                    x[i1] = x[i1] + x[i6];
                    t2    = x[i5] - x[i2];
                    x[i5] = x[i2] + x[i5];
                    t3    = x[i8] + x[i3];
                    x[i6] = x[i8] - x[i3];
                    t4    = x[i4] + x[i7];
                    x[i2] = x[i4] - x[i7];
                    t5 = t1 - t4;
                    t1 = t1 + t4;
                    t4 = t2 - t3;
                    t2 = t2 + t3;
                    x[i3] =   t5 * cc1 + t4 * ss1;
                    x[i7] = - t4 * cc1 + t5 * ss1;
                    x[i4] =   t1 * cc3 - t2 * ss3;
                    x[i8] =   t2 * cc3 + t1 * ss3;
                }

                is = (id << 1) - n2;
                id <<= 2;
            } while(is < FFTN(m)-1);
        }
    }

    is = 0;
    id = 4;
    do {
        for(i=is; i<FFTN(m); i+=id)
        {
            i1 = i + 1;
            t1 = x[i];
            x[i]  = t1 + x[i1];
            x[i1] = t1 - x[i1];
        }

        is = (id - 1) << 1;
        id <<= 2;
    } while(is < FFTN(m)-1);

    for(j=0,i=0; i<FFTN(m)-1; i++)
    {
        if(i < j)
        {
            t1 = x[j];
            x[j] = x[i];
            x[i] = t1;
        }
		
        k = FFTN(m-1);
        while(k < (j+1))
        {
            j = j - k;
            k = k >> 1;
        }

        j = j + k;
    }
    
    for(i=0; i<FFTN(m); i++)
        x[i] /= FFTN(m);
}


/*********************************************************
 *           FFT & IFFT 测试函数
 */

#include <stdlib.h>
#include <stdio.h>

#ifdef SampleN
#undef SampleN
#undef Nt
#undef f0
#undef fs
#endif
 
#define SampleM    (10)
#define SampleN    (FFTN(SampleM))   //  采样点数
#define Nt         (4)
#define f0         (256)
#define fs         ((SampleN) * (f0) / (Nt))

#ifndef pi 
#define pi  3.1415926535897932  // (pi ?= 355/113)
#endif /* #ifndef pi  */

void dsp_fft_test(void)
{
    int i;
    float t=0.0;
	float fData[SampleN];
	I16 data[SampleN];
	int data1[SampleN];
	FILE *fp;
	
    for(i=0; i<SampleN ; i++, t+=1.0/fs) {
        fData[i] = 128*(0.5 + 0.8*cos(2.*pi*f0*t+0.0*pi/180.0) +0.2*cos(2.*pi*2048*100*t+45.0*pi/180.0) + 0.1*cos(2.*pi*0.*t) + 0.05*cos(rand()*100));  // 直流分量为 6.
		//fData[i] = 128+128*((0.8*sin(2.*pi*f0*t)) + 0.4*cos(2.*pi*500.*t));
		data1[i] = (int) (fData[i]*0.8);
	}
	
    //dsp_rfft(fData,SampleM,1);
	for(i=0; i<SampleN>>1; i++)
		data[i] = - fData[i];
	GUI_SetColor(GUI_BLACK);
	GUI_DrawGraph(data,SampleN>>1,0,250);
	
	dsp_fft(data1,SampleM,0);
	for(i=0; i<SampleN>>1; i++)
		data[i] = - data1[i]*3/0.8;
	GUI_SetColor(GUI_RED);
	GUI_DrawGraph(data,SampleN>>1,0,435);

	fp = fopen("fft_test.txt","wb");

	for(i=0; i<SampleN/2; i++) {
		fprintf(fp,"%d\r\n",data1[i]);
	}
}

