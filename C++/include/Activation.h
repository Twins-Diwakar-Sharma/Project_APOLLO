#ifndef H_ACTIVATION_H
#define H_ACTIVATION_H

#include <math.h>
#include <string>
#include <iostream>
#include <functional>
#include "Algebra.h"
  
struct Activation
{

   std::function<Vec(Vec&)> fx, dfx;

   Activation(std::function<Vec(Vec&)> func, std::function<Vec(Vec&)> diff);
   Activation(const Activation&);
};

namespace act{
    extern Activation sigmoid;
    extern Activation softmax;
};

#endif
