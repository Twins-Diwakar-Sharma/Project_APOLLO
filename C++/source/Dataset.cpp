#include "Dataset.h"

Dataset::Dataset(std::string imagePath, std::string labelPath): imagePath(imagePath), labelPath(labelPath)
{}

Dataset::~Dataset()
{}

void Dataset::getConfig(std::ifstream& inp, int& magicNo, int& totalImages, int& row, int& col){} 

void Dataset::getLabelConfig(std::ifstream& file, int& magicNo, int& totalLabels)
{}

Vec Dataset::getNextDatasetImage(std::ifstream& file, int row, int col){return Vec();}

Mat Dataset::getNextDatasetImageMat(std::ifstream& file, int row, int col){return Mat();}

int Dataset::getNextDatasetLabel(std::ifstream& file){return 0;}



MNIST::MNIST(std::string imagePath, std::string labelPath) : Dataset(imagePath, labelPath)
{
}

MNIST::~MNIST()
{}

int MNIST::reverseInt(int i)
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;

}

int MNIST::getNextDatasetNum(std::ifstream& file)
{
   int number=0;
   file.read((char*)&number,sizeof(number));
   return reverseInt(number);
}

void MNIST::getConfig(std::ifstream& inp, int& magicNo, int& totalImages, int& row, int& col)
{
    magicNo = getNextDatasetNum(inp);
    totalImages = getNextDatasetNum(inp);
    row = getNextDatasetNum(inp);
    col = getNextDatasetNum(inp);
}

void MNIST::getLabelConfig(std::ifstream& file, int& magicNo, int& totalLabels)
{
   magicNo = getNextDatasetNum(file);
   totalLabels = getNextDatasetNum(file);
}

Vec MNIST::getNextDatasetImage(std::ifstream& file, int row, int col)
{
    Vec ret(row*col);
    unsigned char temp=0;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            file.read((char*)&temp,sizeof(temp));
            int pixel = (int)temp;
            ret[i*col + j] = (float)pixel/255.0f;
        }
    }
    return ret;
}

Mat MNIST::getNextDatasetImageMat(std::ifstream& file, int row, int col)
{
    Mat ret(row,col);
    unsigned char temp=0;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            file.read((char*)&temp,sizeof(temp));
            int pixel = (int)temp;
            ret[i][j] = (float)pixel/255.0f;
        }
    }
    return ret;
}

int MNIST::getNextDatasetLabel(std::ifstream& file)
{
  unsigned char temp = 0;
  file.read((char*)&temp,sizeof(temp));
  int value = (int)temp;
  return temp;
}
