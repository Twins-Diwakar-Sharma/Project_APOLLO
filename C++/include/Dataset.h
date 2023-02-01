#ifndef H_DATASET_H
#define H_DATASET_H
#include "Algebra.h"
#include <fstream>
#include <string>

class Dataset
{
    public:
        std::string imagePath, labelPath;

        Dataset(std::string imagePath, std::string labelPath);
        ~Dataset();
        virtual void getConfig(std::ifstream& inp, int& magicNo, int& totalImages, int& row, int& col) = 0;
    virtual void getLabelConfig(std::ifstream& file, int& magicNo, int& totalLabels) = 0;

    virtual Vec getNextDatasetImage(std::ifstream& file, int row, int col)= 0;
    virtual Mat getNextDatasetImageMat(std::ifstream& file, int row, int col);
    virtual int getNextDatasetLabel(std::ifstream& file) = 0;

};

class MNIST : public Dataset
{
private:
    int reverseInt(int i);
    int getNextDatasetNum(std::ifstream& file);
public:
    MNIST(std::string imagePath, std::string labelPath);
    ~MNIST();

    void getConfig(std::ifstream& inp, int& magicNo, int& totalImages, int& row, int& col);

    void getLabelConfig(std::ifstream& file, int& magicNo, int& totalLabels);

    Vec getNextDatasetImage(std::ifstream& file, int row, int col);
    Mat getNextDatasetImageMat(std::ifstream& file, int row, int col);
    int getNextDatasetLabel(std::ifstream& file);
};

#endif
