#ifndef H_DATASET_H
#define H_DATASET_H
#include "Algebra.h"
#include <fstream>

class MNIST 
{
public:

    int reverseInt(int i);

    int getNextDatasetNum(std::ifstream& file);

    void getConfig(std::ifstream& inp, int& magicNo, int& totalImages, int& row, int& col);

    void getLabelConfig(std::ifstream& file, int& magicNo, int& totalLabels);

    Vec getNextDatasetImage(std::ifstream& file, int row, int col);

    int getNextDatasetLabel(std::ifstream& file);
};

#endif
