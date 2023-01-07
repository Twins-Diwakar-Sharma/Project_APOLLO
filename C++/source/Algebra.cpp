/*
 * =====================================================================================
 *
 *       Filename:  Algebra.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/20/2021 04:11:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Algebra.h"

Vec::Vec()
{
    this->size_ = 0;
    data = nullptr;
}

Vec::Vec(int size_)
{
    this->size_ = size_;
    data = new float[size_];
    for(int i=0; i<size_; i++)
        data[i] = 0;
}

Vec::~Vec()
{
    delete [] data;
}

Vec::Vec(const Vec& vec)
{
    size_ = vec.size_;
    data = new float[size_];
    for(int i=0; i<size_; i++)
        data[i] = vec.data[i]; 
}

Vec::Vec(Vec&& vec)
{
    size_ = vec.size_;
    data = vec.data;
    vec.data = nullptr;   
}

Vec& Vec::operator=(Vec& vec)
{
    if(size_!=vec.size_)
    {   
        size_ = vec.size_;
        if(data != nullptr)
            delete [] data;
        data = new float[size_];
    }
    for(int i=0; i<size_; i++)
        data[i] = vec.data[i];
    return *this;
}

Vec& Vec::operator=(Vec&& vec)
{
    // we need to delete this->data before we replace it with new data to prevent memory leaks
    // so we have to write delete [] this->data,
    // but we can be clever in doing so ..
    // we know that vec is going to be deleted so we point vec.data to content of this->data
    // this we compiler will delete previous data while deleting vec and we dont have to bother

    this->size_ = vec.size_;
    float* toDelete = this->data;
    data = vec.data;
    vec.data = toDelete;
    return *this;
}

float& Vec::operator[](int i)
{
    if(i >= size_)
        std::cerr<<"Requested index "<<i<<" out of bounds "<<std::endl;
    else if(i < 0)
        std::cerr<<"negative index ? seriously ? Are you that noob"<<std::endl;
    else 
        return data[i];
}

Vec operator+(Vec& a, Vec& b)
{

    if(a.size_ != b.size_)
    {   
        std::cerr<<"cannot add !! size not same"<<std::endl;
        return Vec(0);
    }

    Vec v(a.size_);
    for(int i=0; i<v.size_; i++)
        v[i] = a[i]+b[i];

    return v;
}
 
Vec operator+(Vec& a, Vec&& b)
{
    if(a.size_ != b.size_)
    {   
        std::cerr<<"cannot add !! size not same"<<std::endl;
        return Vec(0);
    }
    
    for(int i=0; i<a.size_; i++)
        b[i] = a[i] + b[i];
    
    return std::move(b);
}
 
Vec operator+(Vec&& a, Vec& b)
{
    if(a.size_ != b.size_)
    {   
        std::cerr<<"cannot add !! size not same"<<std::endl;
        return Vec(0);
    }
    
    for(int i=0; i<a.size_; i++)
        a[i] = a[i] + b[i];
    
    return std::move(a);
}
 
Vec operator+(Vec&& a, Vec&& b)
{
    if(a.size_ != b.size_)
    {   
        std::cerr<<"cannot add !! size not same"<<std::endl;
        return Vec(0);
    }
    
    for(int i=0; i<a.size_; i++)
        b[i] = a[i] + b[i];
   
    return std::move(b);
}


int Vec::size()
{
    return size_;
}

Vec operator-(Vec& a, Vec& b)
{

    if(a.size_ != b.size_)
    {
        std::cerr << "size of vectors donnot match" << std::endl;
    }
    Vec res(a.size_);
    for(int i=0; i<res.size_; i++)
    {
        res.data[i] = a.data[i] - b.data[i];
    }
    return res;
}

Vec operator-(Vec& a, Vec&& b)
{
    if(a.size_ != b.size_)
    {
        std::cerr << "size of vectors donnot match" << std::endl;
        return Vec(0);
    }

    // b is temporary, so we will use it instead
    for(int i=0; i<a.size_; i++)
    {
        b.data[i] = a.data[i] - b.data[i];
    }
    return std::move(b);
}

Vec operator-(Vec&& a, Vec& b)
{
    if(a.size_ != b.size_)
    {
        std::cerr << "size of vectors donnot match" << std::endl;
        return Vec(0);
    }   
    // a is temporary, so we will use it instead
    for(int i=0; i<a.size_; i++)
    {
        a.data[i] = a.data[i] - b.data[i];
    }
    return std::move(a);
}

Vec operator-(Vec&& a, Vec&& b)
{
    if(a.size_ != b.size_)
    {
        std::cerr << "size of vectors donnot match" << std::endl;
        return Vec(0);
    }   
    // a is temporary, so we will use it instead
    for(int i=0; i<a.size_; i++)
    {
        a.data[i] = a.data[i] - b.data[i];
    }
    return std::move(a);
}

Vec operator*(float f, Vec& vec)
{
    Vec res(vec.size_);
    for(int i=0; i<vec.size_; i++)
    {
        res.data[i] = f*vec.data[i];
    }
    return res;
}

Vec operator*(float f, Vec&& vec)
{
    // use temp vec
    for(int i=0; i<vec.size_; i++)
    {
        vec.data[i] = f*vec.data[i];
    }
    return std::move(vec);
}

Vec operator*(Vec& v, float f)
{
    Vec res(v.size_); 
    for(int i=0; i<v.size_; i++)
    {
        res.data[i] = f*v.data[i];
    }
    return res;
}

Vec operator*(Vec&& vec, float f)
{
    // use temp vec
    for(int i=0; i<vec.size_; i++)
    {
        vec.data[i] = f*vec.data[i];
    }
    return std::move(vec);
}

void Vec::operator+=(Vec& vec)
{
    if(vec.size_ != size_)
    {
        std::cerr << "Error in vec operator +=, size of vector is not same " << std::endl;
    }
    else
    {
        for(int i=0; i<size_; i++)
            data[i] += vec.data[i];
    }
}

void Vec::operator+=(Vec&& vec)
{
    if(vec.size_ != size_)
    {
        std::cerr << "Error in vec operator +=, size of vector is not same " << std::endl;
    }
}

void Vec::reset()
{
    for(int i=0; i<size_; i++)
        data[i] = 0;
}

std::ostream& operator<<(std::ostream& of, Vec& vec)
{
    for(int i=0; i<vec.size(); i++)
    {
        of << vec[i] << " ";
    }
    return of;
}

Mat::Mat()
{
    row_ =0; col_=0;
    data = nullptr;
}

Mat::Mat(int row_,int col_)
{
    this->row_ = row_;
    this->col_ = col_;

    data = new float*[row_];
    for(int i=0; i<row_; i++)
    {
        data[i] = new float[col_];
    }

    for(int i=0; i<row_; i++)
    {
        for(int j=0; j<col_; j++)
        {
            data[i][j] = 0;
        }
    }
}

Mat::~Mat()
{
    for(int i=0; i<row_; i++)
        delete [] data[i];

    delete [] data;
}


Mat::Mat(const Mat& mat)
{
    this->row_ = mat.row_;
    this->col_ = mat.col_;

    data = new float*[row_];
    for(int i=0; i<row_; i++)
        data[i] = new float[col_];

    for(int i=0; i<row_; i++)
        for(int j=0; j<col_; j++)
            data[i][j] = mat.data[i][j];
}

Mat::Mat(Mat&& mat)
{
    row_ = mat.row_;    col_ = mat.col_; 
    data = mat.data;   
    mat.data = nullptr;
}

Vec operator*(Mat& mat, Vec& vec)
{
    if(mat.col_ == vec.size())
    {
       Vec res(mat.row_);
       for(int i=0; i<mat.row_; i++)
           for(int j=0; j<mat.col_; j++)
               res[i] += vec[j]*mat.data[i][j];
       return res;
    }
    else
    {
        std::cerr << "Matrix and Vector size is not compatible" << std::endl;
        return Vec(0);
    }
}

Vec operator*(Mat& mat, Vec&& vec)
{
    if(mat.col_ == vec.size())
    {
       Vec res(mat.row_);
       for(int i=0; i<mat.row_; i++)
           for(int j=0; j<mat.col_; j++)
               res[i] += vec[j]*mat.data[i][j];
       return res;
    }
    else
    {
        std::cerr << "Matrix and Vector size is not compatible" << std::endl;
        return Vec(0);
    }
}

Vec operator*(Mat&& mat, Vec& vec)
{
    if(mat.col_ == vec.size())
    {
       Vec res(mat.row_);
       for(int i=0; i<mat.row_; i++)
           for(int j=0; j<mat.col_; j++)
               res[i] += vec[j]*mat.data[i][j];
       return res;
    }
    else
    {
        std::cerr << "Matrix and Vector size is not compatible" << std::endl;
        return Vec(0);
    }
}

Vec operator*(Mat&& mat, Vec&& vec)
{
    if(mat.col_ == vec.size())
    {
       Vec res(mat.row_);
       for(int i=0; i<mat.row_; i++)
           for(int j=0; j<mat.col_; j++)
               res[i] += vec[j]*mat.data[i][j];
       return res;
    }
    else
    {
        std::cerr << "Matrix and Vector size is not compatible" << std::endl;
        return Vec(0);
    }
}



int Mat::row()
{
    return row_;
}

int Mat::col()
{
    return col_;
}

void Mat::getDimension(int& r, int& c)
{
    r = row_;    c = col_;
}

Mat& Mat::operator=(Mat& m)
{
    
    if((row_!=m.row_ || col_!=m.col_))
    {
        if(data != nullptr)
        {
           for(int i=0; i<col_; i++)
               delete [] data[i];
           delete [] data;
        }
    
         this->row_ = m.row_;
        this->col_ = m.col_;
       data = new float*[row_];
        for(int i=0; i<row_; i++)
        {
            data[i] = new float[col_];
        }
     
    }
    
    for(int i=0; i<m.row_; i++)
        for(int j=0; j<m.col_; j++)
            data[i][j] = m.data[i][j];

    return *this;
}

Mat& Mat::operator=(Mat&& m)
{
    this->row_ = m.row_;
    this->col_ = m.col_;

    float** temp = this->data;
    data = m.data;
    m.data = temp;

    return *this;
}

float* Mat::operator[](int i)
{
    if(i<row_ && i>=0)
        return data[i];
   else
        std::cerr<<"out of bounds exception for row no "<<i<<std::endl;
}

Mat operator*(float f, Mat& mat)
{
   Mat ret(mat.row(),mat.col());
   for(int i=0; i<mat.row(); i++) 
       for(int j=0; j<mat.col(); j++)
            ret[i][j] = mat[i][j] * f;

   return ret;
   
}

Mat operator*(float f, Mat&& mat)
{
    for(int i=0; i<mat.row(); i++)
        for(int j=0; j<mat.col(); j++)
            mat[i][j] = mat[i][j] * f;

    return std::move(mat);
}


void Mat::operator+=(Mat& m)
{
   if(m.row_ != row_ || m.col_ != col_)
       std::cerr << "Incompatible matrix size for += " << std::endl;
   else
   {
       for(int i=0; i<row_; i++)
           for(int j=0; j<col_; j++)
               data[i][j] += m[i][j];
   }
}

void Mat::operator+=(Mat&& m)
{
    if(m.row_ != row_ || m.col_ != col_)
       std::cerr << "Incompatible matrix size for += " << std::endl;
   else
   {
       for(int i=0; i<row_; i++)
           for(int j=0; j<col_; j++)
               data[i][j] += m[i][j];
   }
}


void Mat::reset()
{
    for(int i=0; i<row_; i++)
        for(int j=0; j<col_; j++)
            data[i][j] = 0;
}


std::ostream& operator<<(std::ostream& os, Mat& mat)
{
    os << std::endl;
    for(int i=0; i<mat.row_; i++)
    {
        for(int j=0; j<mat.col_; j++)
        {
            os << mat.data[i][j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;
}


void randomize::normal(Mat& m)
{
    std::random_device rd;
    std::mt19937 gen(rd()); 
    double sd = 1.0/(sqrt(m.col()));
    std::normal_distribution<float> norDist(0,sd);
    for(int r=0; r<m.row(); r++)
    {
        for(int c=0; c<m.col(); c++)
        {
            m[r][c] = norDist(gen);
        }
    }
}

void randomize::normal(Vec& v)
{
    std::random_device rd;
    std::mt19937 gen(rd()); 
    double sd = 1.0/(sqrt(v.size()));
    std::normal_distribution<float> norDist(0,sd);
    for(int r=0; r<v.size(); r++)
    {
        v[r] = norDist(gen);
    }

}
