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

};

std::ostream &operator << (std::ostream &cout, const Path &path){
  std::string result = "";
  for(int i=0; i<path.trace.size(); ++i) cout << path.trace[i].id << " \n"[i==path.trace.size()-1];
  cout << path.total_distance << "\n";
  return cout;
}