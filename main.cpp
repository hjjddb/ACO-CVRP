#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdio.h>
#include <climits>
#include "utilities/io_utils.h"
// #include "utilities/math_utils.h"
#include "algorithms/ant_colony_optimize.h"

// using namespace std;
using std::cout;
using std::ifstream;
using std::string;
using std::vector;

// template<class T> using orderedSet = tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// vector<int> findBestMatch(BiGraph biGraph, string option){
//   if (option == "HUNGARIAN") return HungarianSolver(biGraph).solution;
// }

int main(int argc, char **argv)
{
  string output = string(argv[1]) + ".out";
  freopen(output.c_str(), "w", stdout);
  BaseGraph graph = read_input(argv[1]);
  ACOGraph aco_graph(graph);
  // cout << aco_graph.saving.toString();
  // cout << graph.toString();
  Result final_result;
  int num_tried = 0;
  for (int num_ants = graph.num_nodes / 12; num_ants <= graph.num_nodes && num_tried < 500; ++num_ants)
  {
    double alpha(2), beta(5), gamma(9), ro(0.8);
    // for (double alpha = 0; alpha <= 20; alpha += 0.2)
    //   for (double beta = 0; beta <= 20; beta += 0.2)
    //     for (double gamma = 0; gamma <= 20; gamma += 0.2)
    //       for (double ro = 0; ro <= 1; ro += 0.01)
    {
      Result current_result = aco(graph, num_ants, alpha, beta, gamma, ro, 10);
      if (current_result < final_result)
      {
        final_result = current_result;
        num_tried = 0;
      }
    }
    ++num_tried;
    // cout << "result with " + std::to_string(num_ants) + " vehicle(s):\n";
    //   cout << final_result << '\n';
  }
  cout << "\nFinal result: \n"
       << final_result << "\nDone!\n";
}