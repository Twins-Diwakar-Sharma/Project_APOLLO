#include "FNN.h"

FNN::FNN() : input(new Vec(1))
{}

FNN::FNN(Vec& v) : input(v)
{}

FNN::FNN(FNN& f) : input(new Vec(1))
{
    for(int i=0; i<f.layers.size(); i++)
        layers.push_back(f.layers[i]);
}

FNN::FNN(FNN&& f) : input(new Vec(1))
{
    layers = std::move(f.layers);
}

FNN::~FNN()
{}

FNN& FNN::operator=(FNN& f)
{
    if(&f == this)
        return *this;
    for(int i=0; i<f.layers.size(); i++)
        layers.push_back(f.layers[i]);

    return *this;
}

FNN& FNN::operator=(FNN&& f)
{
    if(&f == this)
        return *this;
    layers = std::move(f.layers);
    return *this;
}

void FNN::push_back_WeightsAndBiases()
{
    if(layers.size() > 1)
    {
        int rows = layers[layers.size()-1].neurons.getSize(); 
        int cols = layers[layers.size()-2].neurons.getSize();

        weights.emplace_back(rows,cols);
        randomize::normal(weights.back());
        
        dw.emplace_back(rows,cols);
        randomize::normal(dw.back());
        
        biases.emplace_back(rows);
        randomize::normal(biases.back());

        db.emplace_back(rows);
        randomize::normal(db.back());
    }
}

void FNN::push_back(Layer& l)
{
    layers.emplace_back(l.neurons.getSize(), l.act);
}

void FNN::push_back(Layer&& l)
{
    layers.push_back(l);
}

FNN operator+(Layer& l, Layer& r)
{
    FNN f;
    f.push_back(l);
    f.push_back(r);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Layer& l, Layer&& r)
{
    FNN f;
    f.push_back(l);
    f.push_back(r);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Layer&& l, Layer& r)
{
    FNN f;
    f.push_back(l);
    f.push_back(r);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Layer&& l, Layer&& r)
{
    FNN f;
    f.push_back(l);
    f.push_back(r);
    f.push_back_WeightsAndBiases();
    return f;
}


FNN operator+(FNN& f, Layer& l)
{
    FNN newF(f);
    newF.push_back(l);
    newF.push_back_WeightsAndBiases();
    return newF;
}

FNN operator+(FNN& f, Layer&& l)
{
    FNN newF(f);
    newF.push_back(l);
    newF.push_back_WeightsAndBiases();
    return newF;
}

FNN operator+(FNN&& f, Layer& l)
{
    f.push_back(l);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(FNN&& f, Layer&& l)
{
    f.push_back(l);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Vec& in, Layer& l)
{
    FNN f(in);
    f.push_back(l);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Vec& in, Layer&& l)
{
    FNN f(in);
    f.push_back(l);
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(Vec& in, int i)
{
    FNN f(in);
    f.push_back(i); //implicit conversion
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(FNN& f, int i)
{
    f.push_back(i); //implicit conversion ?
    f.push_back_WeightsAndBiases();
    return f;
}

FNN operator+(FNN&& f, int i)
{
    f.push_back(i); //implicit conversion ?
    f.push_back_WeightsAndBiases();
    return f;
}


Layer operator/(int size, const Activation& a)
{
    return {size,a};
}
