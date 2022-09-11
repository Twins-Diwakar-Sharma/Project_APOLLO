/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/23/2022 07:25:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include "Activation.h"
#include "FNN.h"

int main()
{
    float six = act::sigmoid.fx(0.125f);
    std::cout << six << std::endl; 
    Layer l = {10, act::sigmoid};       
    FNN f = Layer(10,act::sigmoid) + Layer(20,act::sigmoid);

    FNN fnn = 10/act::sigmoid + 20/act::sigmoid + 30/act::sigmoid;

    Vec input(10);

    FNN f2 = input + 10 + 20/act::sigmoid + 30;
    

    return 1;
}

