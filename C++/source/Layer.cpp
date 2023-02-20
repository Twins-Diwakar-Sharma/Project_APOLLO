#include "Layer.h"

Layer::Layer(int i) : 
    neurons(i), error(i), activation(act::sigmoid)
{

}

Layer::Layer(int i, const Activation& a) :
    neurons(i), error(i), activation(a)
{

}

void Layer::activate()
{
    neurons = activation.fx(neurons);
}

Vec Layer::deactivate()
{
    return activation.dfx(neurons);
}
