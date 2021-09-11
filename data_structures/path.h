#include <vector>
#include <string> 
#include <iostream>

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
      if (!trace.empty())
        total_distance += distance(trace.back(), node);
      trace.push_back(node);
    }

    std::string to_string(){
      std::string res = "route: ";
      for(int i=0; i<trace.size(); ++i) res += std::to_string(trace[i].id) + " \n"[i==trace.size()-1];
      // res += std::to_string(total_distance) + "\n";
      return res;
    }

};

std::ostream &operator << (std::ostream &cout, Path &path){
  cout << path.to_string();
  return cout;
}