#ifndef H_ACTIVATION_H
#define H_ACTIVATION_H

#include <math.h>
#include <string>
#include <iostream>
#include <functional>
  
struct Activation
{

   std::function<float(float)> fx, dfx;

   Activation(std::function<float(float)> func, std::function<float(float)> diff);
   Activation(const Activation&);
};

namespace act{
    extern Activation sigmoid;
};

#endif
