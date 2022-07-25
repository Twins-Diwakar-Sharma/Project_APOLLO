#include "Activation.h"

Activation::Activation(float(*func)(float), float(*diff)(float)) : fx(func), dfx(diff)
{}

Activation act::sigmoid = Activation( [](float f)->float{
             return (1.0f/(1.0f + exp(-f))); 
        }, [](float f)->float{
            return f * (1.0f - f);
        });



