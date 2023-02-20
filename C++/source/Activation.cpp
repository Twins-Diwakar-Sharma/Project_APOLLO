#include "Activation.h"

Activation::Activation(std::function<Vec(Vec&)> func, std::function<Vec(Vec&)> diff) : fx(func), dfx(diff)
{}

Activation::Activation(const Activation& act): fx(act.fx), dfx(act.dfx)
{}

Activation act::sigmoid( 
        [](Vec& in) -> Vec
        {
            Vec out(in.size());
            for(int i=0; i<in.size(); i++)
                out[i] = (1.0f/(1.0f + exp(-in[i]))); 
            return out;
        }, 
        [](Vec& in) -> Vec
        {
            Vec out(in.size());
            for(int i=0; i<in.size(); i++)
                out[i] = in[i] * (1.0f - in[i]);

            return out;
        }
);

Activation act::softmax(
    [](Vec& in) -> Vec
    {
        Vec out(in.size());
        double sum = 0;
        for(int i=0; i<in.size(); i++)
            sum += exp(in[i]);
        for(int i=0; i<in.size(); i++)
            out[i] = exp(in[i])/sum;

        return out;
    },
    [](Vec& in) -> Vec
    {
        Vec out(in.size());
        for(int i=0; i<in.size(); i++)
            out[i] = in[i] * (1.0f - in[i]);
        return out;
    }
);



