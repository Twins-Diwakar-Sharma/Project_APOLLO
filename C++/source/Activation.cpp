#include "Activation.h"

Activation::Activation(std::function<float(float)> func, std::function<float(float)> diff) : fx(func), dfx(diff)
{}

Activation::Activation(const Activation& act): fx(act.fx), dfx(act.dfx)
{}

Activation act::sigmoid( 
        [](float f)->float
        {
             return (1.0f/(1.0f + exp(-f))); 
        }, 
        [](float f)->float
        {
            return f * (1.0f - f);
        }
);



