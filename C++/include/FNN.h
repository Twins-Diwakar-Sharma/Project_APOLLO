#ifndef H_FEEDFORWARD_NEURAL_NETWORK_H
#define H_FEEDFORWARD_NEURAL_NETWORK_H

#include "Algebra.h"
#include "Layer.h"
#include "Dataset.h"
#include "LossFunction.h"
#include <vector>
#include <fstream>
#include <sstream>

class FNN
{
   
    private:
         std::vector<Layer> layers;
         std::vector<Mat> weights, dw;
         std::vector<Vec> biases, db;
         Vec& input;
         MNIST dataset;
         float alpha = 0.15f;
         LossFunction lossFxn;

    public:
        FNN(Vec&);
        FNN(FNN&);
        FNN(FNN&&);
        ~FNN();
  
        FNN& operator=(FNN&);
        FNN& operator=(FNN&&);
        void push_back_layer(Layer&);
        void push_back_layer(Layer&&);
        void push_back_WeightsAndBiases();

        void setLearningRate(float alpha);
        void setLossFunction(const LossFunction& l);
        void setCustomLoss(std::function<float(float, float)>& fx, std::function<float(float,float)>& dfx);

        void forwardPass();
        void backwardPass();
        void gradientDescend();

        void train(std::string imagePath, std::string labelPath, int batchSize, int epoch);
        void test(std::string imagePath, std::string labelPath);
        
};

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
