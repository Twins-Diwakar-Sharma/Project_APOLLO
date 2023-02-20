/*
 * =====================================================================================
 *
 *       Filename:  Lossfunction.cpp
 *
 *    Description:  Isme tera ghata ... nera kcuh nhi jata 
 *
 *        Version:  1.0
 *        Created:  01/18/2023 11:39:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Divyanshu_Diwakar Sharma 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "LossFunction.h" 


LossFunction::LossFunction(std::function<float(float,float)> func,
                std::function<float(float,float)> diff) : 
    fx(func), dfx(diff)
{}

LossFunction::LossFunction(const LossFunction& loss) :
    fx(loss.fx), dfx(loss.dfx)
{}

LossFunction loss::meanSquared (
        [](float target, float output) -> float
        {
           return (target-output) * (target-output); 
        },
        [](float target, float output) -> float
        {
            return -2*(target-output);
        }

);

LossFunction loss::crossEntropy (
        [](float target, float output) -> float
        {
            return -target * log(output);
        },
        [](float target, float output) -> float
        {
            return -target/output;
        }
);
