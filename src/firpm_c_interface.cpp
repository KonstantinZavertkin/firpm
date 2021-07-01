#include "firpm_c_interface.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include "firpm.h"

using namespace std;
using pm::firpm;
using pm::pmoutput_t;

const int resultOk = 0;
const int resultUnexpectedException = 1;
const int resultFirBadSize = 2;
const int resultFirCalculationError = 3;

int firpm_double( unsigned int order, 
                  double* ptrF, 
                  double* ptrA, 
                  double* ptrW, 
                  unsigned int fArrSize, 
                  double* filterCoefficients, 
                  char* messageBuffer, 
                  unsigned int messageBufferSize )
{
   int retCode = 1;
   string tempStr;
   string stringAcc;
   streambuf* coutSb = cout.rdbuf();
   streambuf* cerrSb = cerr.rdbuf();

   stringstream streamBuffer;
   cout.rdbuf( streamBuffer.rdbuf() );
   cerr.rdbuf( streamBuffer.rdbuf() );

   retCode = firpm_double_impl( order, ptrF, ptrA, ptrW, fArrSize, filterCoefficients );

   while ( getline( streamBuffer, tempStr ) )
      stringAcc += tempStr += '\n';

   size_t writeSize = stringAcc.size();

   if ( writeSize > messageBufferSize )
      writeSize = messageBufferSize;

   if ( writeSize )
      std::copy( stringAcc.c_str(), stringAcc.c_str() + writeSize - 1, messageBuffer );

   cout.rdbuf( coutSb );
   cerr.rdbuf( cerrSb );

   return retCode;
};

int firpm_double_impl( unsigned int order, 
                       double* ptrF, 
                       double* ptrA, 
                       double* ptrW, 
                       unsigned int fArrSize, 
                       double* filterCoefficients )
{
   try
   {
      vector<double> f = vector<double>( ptrF, ptrF + fArrSize );
      vector<double> a = vector<double>( ptrA, ptrA + fArrSize );
      vector<double> w = vector<double>( ptrW, ptrW + fArrSize / 2 );

      pmoutput_t<double> firPmResult;
      firPmResult = pm::firpm<double>( order, f, a, w );

      if ( firPmResult.status != pm::status_t::STATUS_SUCCESS )
         return resultFirCalculationError;

      if ( firPmResult.h.size() > order + 1 )
         return resultFirBadSize;

      std::copy( firPmResult.h.begin(), firPmResult.h.end(), filterCoefficients );
      return resultOk;
   }
   catch ( exception& ex )
   {
      cout << ex.what() << endl;
      return resultUnexpectedException;
   }
   catch ( ... )
   {
      return resultUnexpectedException;
   }
};
