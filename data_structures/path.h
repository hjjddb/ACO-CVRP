#include <vector>

#include "node.h"

class Path {
  public:
    std::vector<Node> trace;
    double total_distance;

    Path(){
      trace.clear();
      total_distance = 0;
    }

    void add_node(Node node){
      trace.push_back(node);
      if (!trace.empty()) total_distance += distance(trace.back(), node);
    }
};
