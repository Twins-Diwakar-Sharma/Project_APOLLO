#ifndef H_LAYER_H
#define H_LAYER_H

#include "Algebra.h"
#include "Activation.h"

class Layer
{
    public:
        Vec neurons, error;
        const Activation& act;
        Layer(int i);
        Layer(int i, const Activation& a);
};


#endif
