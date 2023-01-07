#ifndef H_LAYER_H
#define H_LAYER_H

#include "Algebra.h"
#include "Activation.h"

class Layer
{
    public:
        Vec neurons, error;
        const Activation& activation;
        Layer(int i);
        Layer(int i, const Activation& a);
        void activate();
        float activate(int index);
        float deactivate(int index);
};


#endif
