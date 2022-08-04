#ifndef H_ACTIVATION_H
#define H_ACTIVATION_H

#include <math.h>
#include <string>
#include <iostream>
  
struct Activation
{
   float(*fx)(float);

   float(*dfx)(float);

   Activation( float(*func)(float) , float(*diff)(float));

};

namespace act{
    extern Activation sigmoid;
};

#endif
