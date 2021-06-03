#include "../../data_structures/graph.h"
#include "../../utilities/math_utils.h"


double aco(BaseGraph baseGraph, int num_ants, double max_capability, double alpha, double beta, double gamma, double ro){
  int MAX_NOT_BETTER_TRY = 10;

  ACOGraph graph(baseGraph);

  double result = __LONG_LONG_MAX__;
  int not_better_try(0);

  // while(not_better_try < MAX_NOT_BETTER_TRY){
    srand(time(NULL));
    
    vector<Path> paths;
    vector<bool> visited(graph.num_nodes, false);
    visited[graph.start_node.id] = true;
    int num_not_visited = graph.num_nodes-1;

    for (int ant=0; ant<num_ants; ++ant){
    //   // initialize 
      double capability = max_capability;

      Matrix probability(graph.num_nodes, graph.num_nodes);
      Path path;
      path.add_node(graph.start_node);
      Node current_node = graph.start_node;
      std::vector<std::pair<double, int>> cucumlativeProbability(1, {0, -1});

      // std::cout << graph.saving.toString() << '\n';

      while(num_not_visited && max_capability){
        for (int id=0; id<graph.num_nodes; ++id){
          if (visited[id] || max_capability < graph.nodes[id].quantity) probability[current_node.id][id] = 0;
          else {
            probability[current_node.id][id] = pow(graph.pheromone[current_node.id][id], alpha) * pow(graph.heuristic[current_node.id][id], beta);// * pow(graph.saving[current_node.id][id], gamma);
            cucumlativeProbability.push_back(std::make_pair(cucumlativeProbability.back().first + probability[current_node.id][id], id));
          }
        }
        std::cout << probability.toString() << '\n';

        int next_id = std::lower_bound(cucumlativeProbability.begin(), cucumlativeProbability.end(), std::make_pair(randf()*cucumlativeProbability.back().first, -1)) - cucumlativeProbability.begin();
        std::cout << next_id << '\n';
        if (next_id == -1) break;
        Node next_node = graph.nodes[next_id];
        visited[next_node.id] = true;
        path.add_node(next_node);
        max_capability -= next_node.quantity;
        current_node = next_node;
        --num_not_visited;
      }
      path.add_node(graph.start_node);
      paths.push_back(path);

      // pheromone update
      graph.pheromone *= (1-ro); // pheromone evaporation
      Matrix delta(graph.num_nodes, graph.num_nodes);
      for(int i=0; i<path.trace.size()-1; ++i){
        delta[path.trace[i].id][path.trace[i+1].id] += 1/path.total_distance;
        delta[path.trace[i+1].id][path.trace[i].id] += 1/path.total_distance;
      }
      graph.pheromone += delta;
    }
    // std::cout << graph.pheromone.toString() << '\n';

    double current_result = 0;
    for (Path &path : paths){
      current_result += path.total_distance;
    }

    // Update result
    std::cout << not_better_try << " " << result << " " << current_result << '\n';
    if (result <= current_result){
      ++not_better_try;
      // continue;
    }
    // if (num_not_visited) continue;
    std::cout << num_not_visited << '\n';
    if (num_not_visited==0) result = current_result;
    // not_better_try = 0;
  // }
  return result;
}

