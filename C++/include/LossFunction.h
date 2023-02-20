/*
 * =====================================================================================
 *
 *       Filename:  Lossfunction.h
 *
 *    Description:  Define loss/cost function either using
 *                      given namespace functions
 *                      or define your own custom loss function
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

#ifndef H_LOSS_FUNCTION_H
#define H_LOSS_FUNCTION_H

#include <functional>
#include <cmath>

struct LossFunction
{
    std::function<float(float,float)> fx, dfx;

    LossFunction(std::function<float(float,float)> func, 
                std::function<float(float,float)> diff);

    LossFunction(const LossFunction&);
};

namespace loss {
    extern LossFunction meanSquared;
}

#endif
