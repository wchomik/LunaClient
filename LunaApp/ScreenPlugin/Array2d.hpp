#pragma once

#include <memory>

template<typename T>
class Array2D {
public:
    Array2D();
    Array2D(size_t columns, size_t rows);
    T & operator()(size_t column, size_t row){
        return mData[column + row * mDimensions[0]];
    }
    T * data(){ return mData.get(); }
    size_t columns() const { return mDimensions[0]; }
    size_t rows() const { return mDimensions[1]; }
private:
    size_t mDimensions[2];
    std::unique_ptr<T[]> mData;
};

template<typename T>
Array2D<T>::Array2D() :
    mDimensions{0, 0}
{}

template<typename T>
Array2D<T>::Array2D(size_t columns, size_t rows) :
    mDimensions{columns, rows},
    mData(std::make_unique<T[]>(columns * rows))
{
    for (size_t i = 0; i < this->columns(); ++i) {
        for (size_t j = 0; j < this->rows(); ++j) {
            (*this)(i, j).setZero();
        }
    }
}
