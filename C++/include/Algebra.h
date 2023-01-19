#ifndef H_AL_Z3BR0_H
#define H_AL_Z3BR0_H

#include <iostream>
#include <functional>
#include <random>
#include <cmath>

class Vec
{
    private:
        float* data;
        int size_;

    public:
        
        Vec();
        Vec(int size_);
        Vec(const Vec&); // l value copy constructor
        Vec(Vec&&); // r value copy constructor
        ~Vec();

        int size();

        Vec& operator=(Vec&); //l value assignment
        Vec& operator=(Vec&&); // r value assignment

        float& operator[](int i);
 
       friend Vec operator+(Vec&, Vec&);
       friend Vec operator+(Vec&, Vec&&);
       friend Vec operator+(Vec&&, Vec&);
       friend Vec operator+(Vec&&, Vec&&);

       friend Vec operator-(Vec&,Vec&);
       friend Vec operator-(Vec&, Vec&&);
       friend Vec operator-(Vec&&, Vec&);
       friend Vec operator-(Vec&&, Vec&&);

       friend Vec operator*(float,Vec&);
       friend Vec operator*(float,Vec&&);

       friend Vec operator*(Vec&, float);
       friend Vec operator*(Vec&&, float);      

       void operator+=(Vec&);
       void operator+=(Vec&&);

        void reset();

        friend std::ostream& operator<<(std::ostream&, Vec&);
};

class Mat
{
    private:
        float** data;
        int row_, col_;

    public:

        Mat();
        Mat(int row, int col);
        Mat(const Mat&);
        Mat(Mat&&);
        ~Mat();
        int row();
        int col();
        void getDimension(int& r, int& c);

        Mat& operator=(Mat&);
        Mat& operator=(Mat&&);

        float* operator[](int);
 
       friend Vec operator*(Mat&,Vec&);
       friend Vec operator*(Mat&,Vec&&);
       friend Vec operator*(Mat&&,Vec&);
       friend Vec operator*(Mat&&,Vec&&);

       friend Mat operator*(float, Mat&);
       friend Mat operator*(float, Mat&&);

       void operator+=(Mat&);
       void operator+=(Mat&&);

       void reset();
       friend std::ostream& operator<<(std::ostream&, Mat&);

};

namespace randomize
{
    void normal(Mat&);
    void normal(Vec&);
};

void matXvec(const Mat& m, const Vec& v, Vec& ans);

#endif

