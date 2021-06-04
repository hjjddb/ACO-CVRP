#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdio.h>

#include "utilities/io_utils.h"
// #include "utilities/math_utils.h"
#include "algorithms/ant_colony_optimize.h"

// using namespace std;
using std::ifstream;
using std::vector;
using std::cout;
using std::string;

// template<class T> using orderedSet = tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;


// vector<int> findBestMatch(BiGraph biGraph, string option){
//   if (option == "HUNGARIAN") return HungarianSolver(biGraph).solution;
// }

int main(){
  freopen("test.out", "w", stdout);
  BaseGraph graph = read_input("data/CMT01.xml");
  ACOGraph aco_graph(graph);
  // cout << aco_graph.saving.toString();
  // cout << graph.toString();
  cout << aco(graph, 5, 160, 1, 1, 1, 0, 100) << '\n';
  cout << "Done!\n";
}