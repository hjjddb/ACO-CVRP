#include <vector>
#include <iostream>

using std::vector;
using std::cout;

class Matrix {
  public:
    vector<vector<double>> row;

    Matrix(){
      row.resize(2);
      for(int i=0; i<2; ++i) row[i].resize(2);
      for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) row[i][j] = 9;
    }

    vector<double> operator [] (int x){
      return row[x];
    }
};

int main(){
  Matrix x;
  cout << x[0][0];
}