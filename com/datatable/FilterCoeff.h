
#ifndef FILTER_COEFF_H
#define FILTER_COEFF_H

/*
 * The type for FIR digital filter is : LowPass
 * The Filter order number is         : 50 orders
 * The low cutoff freqency FL is      : 1200 Hz
 * The sample freqency fs is          : 1024 Hz
 * The window is                      : Hanning
 */

#define FIRorder    50      /* The Filter order number. */

#define FIR_COEFFMAG     (1024)   /* 系数放大倍数 */

static const int FilterCoeff[FIRorder] = {
0, 0, 0, 0, 0, 
0, 2, 1, -2, -5, 
-3, 5, 11, 5, -11, 
-20, -7, 22, 36, 9, 
-45, -70, -10, 133, 286, 
2400, 286, 133, -10, -70, 
-45, 9, 36, 22, -7, 
-20, -11, 5, 11, 5, 
-3, -5, -2, 1, 2, 
0, 0, 0, 0, 0, 
};


#endif  /* FILTER_COEFF_H */
