#include "../data_structures/graph.h"

class HungarianSolver {
  public:
    BiGraph graph;
    vector<int> solution;

    HungarianSolver(BiGraph graph){
      this->graph = graph;
      solution = getSolution();
    }

    vector<int> getSolution();
};