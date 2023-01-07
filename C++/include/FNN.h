#ifndef H_FEEDFORWARD_NEURAL_NETWORK_H
#define H_FEEDFORWARD_NEURAL_NETWORK_H

#include "Algebra.h"
#include "Layer.h"
#include "Dataset.h"
#include <vector>
#include <fstream>
#include <sstream>

class FNN
{
    public:
  //  private:
         std::vector<Layer> layers;
         std::vector<Mat> weights, dw;
         std::vector<Vec> biases, db;
         Vec& input;
         MNIST dataset;
         float alpha = 0.15f;

 //   public:
        FNN(Vec&); // if I change the image, should its reference change too in inside fnn ?
        FNN(FNN&);
        FNN(FNN&&);
        ~FNN();
  
        FNN& operator=(FNN&);
        FNN& operator=(FNN&&);
        void push_back_layer(Layer&);
        void push_back_layer(Layer&&);
        void push_back_WeightsAndBiases();

        void forwardPass();
        void backwardPass();
        void gradientDescend();

        void train(int epoch, std::string imagePath, std::string labelPath);        
        void test(std::string imagePath, std::string labelPath);
        
};

/*
FNN operator+(Layer& l, Layer& r);
FNN operator+(Layer& l, Layer&& r);
FNN operator+(Layer&& l, Layer& r);
FNN operator+(Layer&& l, Layer&& r);
*/
FNN operator+(FNN&, Layer&);
FNN operator+(FNN&, Layer&&);
FNN operator+(FNN&&, Layer&);
FNN operator+(FNN&&, Layer&&);

FNN operator+(Vec&, Layer&);
FNN operator+(Vec&, Layer&&);

FNN operator+(Vec&, int);

FNN operator+(FNN&, int);
FNN operator+(FNN&&, int);


Layer operator/(int,const Activation&);


#endif
