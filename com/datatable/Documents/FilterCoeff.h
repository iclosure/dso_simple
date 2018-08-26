
#ifndef FILTER_COEFF_H
#define FILTER_COEFF_H

/*
 * The type for FIR digital filter is : LowPass
 * The Filter order number is         : 25 orders
 * The low cutoff freqency FL is      : 1000 Hz
 * The sample freqency fs is          : 1024 Hz
 * The window is                      : Hamming
 */

#define FIRorder    25      /* The Filter order number. */

#define FIR_COEFFMAG     (1024)   /* 系数放大倍数 */

static const int FilterCoeff[FIRorder] = {
2, 2, 4, 6, 10, 
15, 20, 26, 32, 38, 
42, 46, 47, 47, 46, 
42, 38, 32, 26, 20, 
15, 10, 6, 4, 2, 
};


#endif  /* FILTER_COEFF_H */
