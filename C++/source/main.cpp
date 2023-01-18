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
   
    Layer l = {10, act::sigmoid};       

    Vec input(28*28);

    FNN fnn = input + 50/act::sigmoid + 20/act::sigmoid + 10/act::sigmoid;
    fnn.setLearningRate(0.01);

   fnn.train("res/trainImages", "res/trainLabels", 5, 2); // learning rate then epoch
   std::cout << " %%%%%%%%%%%%%% train ends %%%%%%%%%%%%%%% " << std::endl;
   fnn.test("res/trainImages", "res/trainLabels");
   
    
    

    return 0;
}

