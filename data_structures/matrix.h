#ifndef _matrix_h_
#define _matrix_h_
#endif

#include <vector>

class Matrix {
  public:
    int nrows, 
        ncols;
    std::vector<std::vector<double>> at;

    // constructors
    Matrix(){
      this->nrows = 0;
      this->ncols = 0;
    }

    Matrix(int nrows, int ncols){
      this->nrows = nrows;
      this->ncols = ncols;
      at.resize(nrows);
      for(int i=0; i<nrows; ++i)
        at[i] = std::vector<double>(ncols, 0);
    }

    Matrix(int nrows, int ncols, double defaultValue){
      this->nrows = nrows;
      this->ncols = ncols;
      at.resize(nrows);
      for(int i=0; i<nrows; ++i)
        at[i] = std::vector<double>(ncols, defaultValue);
    }

    Matrix(std::vector<std::vector<double>> other){
      ncols = 0;
      for(int i=0; i<other.size(); ++i) ncols = std::max(ncols, (int)other[i].size());
      nrows = other.size();
      at.resize(nrows);
      for(int i=0; i<nrows; ++i)
        for(int j=0; j<other[i].size(); ++j)
          at[i][j] = other[i][j];
    }

    // operators
    void operator = (const Matrix& other){
      this->nrows = other.nrows;
      this->ncols = other.ncols;
      this->at = other.at;
    }

    std::vector<double>& operator [] (int row){
      return at[row];
    }
    // multiple with scala
    void operator *= (double x){
      for(int i=0; i<nrows; ++i) 
        for(int j=0; j<ncols; ++j) 
          at[i][j] *= x;
    }

    void operator += (Matrix &other){
      assert(nrows == other.nrows && ncols == other.ncols);

      for(int i=0; i<nrows; ++i) 
        for(int j=0; j<ncols; ++j)
          at[i][j] += other[i][j];
    }

    // methods
    std::string toString(){
      std::string result = "";
      for(int i=0; i<nrows; ++i) 
        for(int j=0; j<ncols; ++j) 
          result += std::to_string(at[i][j]) + " \n"[j==nrows-1];
      return result;
    }
};

