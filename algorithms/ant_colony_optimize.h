#include "../data_structures/graph.h"
#include "../utilities/math_utils.h"


double aco(BaseGraph baseGraph, int num_ants, double max_capability, double alpha, double beta, double gamma, double ro, int max_trial){
  int MAX_NOT_BETTER_TRY = max_trial;

  ACOGraph graph(baseGraph);

  double result = LLONG_MAX;
  int not_better_try(0);

  int num_trial(0);
  while(not_better_try < MAX_NOT_BETTER_TRY){
    std::cout << "Trial " << num_trial++ << '\n';
    srand(time(NULL));
    
    vector<Path> paths;
    vector<bool> visited(graph.num_nodes, false);
    visited[graph.start_node.id] = true;
    int num_not_visited = graph.num_nodes-1;

    for (int k=0; k<num_ants && num_not_visited>0; ++k){
      Path path;
      path.add_node(graph.start_node);
      double capability = max_capability;
      Node current_node = graph.start_node;

      while(num_not_visited>0){
        vector<double> prob(graph.num_nodes); // prob[i] is probability of ant[k] go from current node to node[i]
        vector<std::pair<double, int>> cucumProb(1); // cucumlative the probabilities to generate a random choice of ant[k]

        for(int i=0; i<graph.num_nodes; ++i){
          if (!visited[i] && capability>=graph.nodes[i].quantity){
            prob[i] = pow(graph.pheromone[current_node.id][i], alpha) + pow(graph.heuristic[current_node.id][i], beta);
            cucumProb.push_back(std::make_pair(cucumProb.back().first+prob[i], i));
          }
        }
        if (cucumProb.size()==1){
          path.add_node(graph.start_node);
          break;
        }
        int chosen_id = (*std::upper_bound(cucumProb.begin(), cucumProb.end(), std::make_pair(randf() * cucumProb.back().first, -1))).second;
        path.add_node(graph.nodes[chosen_id]);
        capability -= graph.nodes[chosen_id].quantity;
        visited[chosen_id] = true;
        --num_not_visited;
        current_node = graph.nodes[chosen_id];
      }

      paths.push_back(path);
    }
    // Create delta matrix
    Matrix delta(graph.num_nodes, graph.num_nodes);
    for (Path &path : paths){
      for(int i=0; i<path.trace.size()-1; ++i){
        delta[i][i+1] += double(1)/path.total_distance;
        delta[i+1][i] += double(1)/path.total_distance;
      }
    }
    // Update pheromone matrix
    graph.pheromone *= (1-ro);
    graph.pheromone += delta;
    // Ignore if the route is not finished
    double current_result(0);
    for (Path &path : paths){
      std::cout << path;
      current_result += path.total_distance;
    }
    std::cout << "Trial's total distance: " << current_result << "\n\n";
    if (num_not_visited) continue;
    // Create result for the trial
    // Update final result
    std::cout << not_better_try << " " << result << " " << current_result << '\n';
    if (result <= current_result){
      ++not_better_try;
      continue;
    }
    result = current_result;
    not_better_try = 0;
  }
  return result;
}

