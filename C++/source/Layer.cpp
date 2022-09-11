#include "Layer.h"

Layer::Layer(int i) : 
    neurons(i), error(i), act(act::sigmoid)
{

}

Layer::Layer(int i, const Activation& a) :
    neurons(i), error(i), act(a)
{

}

