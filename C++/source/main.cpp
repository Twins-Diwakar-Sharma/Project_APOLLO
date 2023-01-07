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

   fnn.train(2,"res/trainImages", "res/trainLabels");
   std::cout << " %%%%%%%%%%%%%% train ends %%%%%%%%%%%%%%% " << std::endl;
   fnn.test("res/trainImages", "res/trainLabels");
   
    
    

    return 0;
}

