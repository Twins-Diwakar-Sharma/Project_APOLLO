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
    for(int i=0; i<neurons.size(); i++)
    {
        neurons[i] = activation.fx(neurons[i]);
    }
}


float Layer::activate(int index)
{
    return activation.fx(neurons[index]);
}

float Layer::deactivate(int index)
{
    return activation.dfx(neurons[index]);
}
