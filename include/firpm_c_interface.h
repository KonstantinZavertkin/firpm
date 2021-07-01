#ifndef _FIRPM_C_INTERFACE_H_
#define _FIRPM_C_INTERFACE_H_

#ifdef _WINDOWS
   #ifdef EXPORTS
      #define Shared_Library_Export __declspec( dllexport )
   #else
      #define Shared_Library_Export __declspec( dllimport )
   #endif
#else
   #define Shared_Library_Export
#endif

#ifdef __cplusplus
extern "C" {
#endif

//! order - filter order
//! ptrF - pointer to array of frequencies
//! ptrA - pointer to array of amplitudes
//! ptrW - pointer to array of weights
//! fArrSize - length of ptrF in elements
//! filterCoefficients - pointer to array of result filter coefficients (length: order + 1),
//! messageBuffer - pointer to null terminated string, used to send error messages
//! messageBufferSize - length of messageBuffer
//! returns 0 if success
//! Memory for all arrays must be allocated before calling the function
Shared_Library_Export int firpm_double( unsigned int order, 
                                        double* ptrF, 
                                        double* ptrA, 
                                        double* ptrW, 
                                        unsigned int fArrSize, 
                                        double* filterCoefficients, 
                                        char* messageBuffer, 
                                        unsigned int messageBufferSize );

#ifdef __cplusplus
};
#endif

int firpm_double_impl( unsigned int order, 
                       double* ptrF, 
                       double* ptrA, 
                       double* ptrW, 
                       unsigned int fArrSize, 
                       double* filterCoefficients );

#endif // _FIRPM_C_H_
