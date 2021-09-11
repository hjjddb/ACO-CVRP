#include "../data_structures/graph.h"
#include "../utilities/math_utils.h"

using std::cout;


class Result {
  public:
    double total_distance;
    vector<Path> paths;

    Result(){
      this->total_distance = LLONG_MAX;
      paths.clear();
    }

    Result(vector<Path> paths){
      this->total_distance = 0;
      for (Path &path : paths)
        this->total_distance += path.total_distance;
      this->paths = paths;
    }

    std::string to_string() {
      std::string res = "routers:\n";
      for (Path &path: paths){
        res += "\t" + path.to_string();
      }
      res += "total_distance " + std::to_string(total_distance);
      return res;
    }

    bool operator < (const Result &other){
      return this->total_distance <= other.total_distance;
    }
};

std::ostream &operator << (std::ostream &cout, Result &result){
  cout << result.to_string();
  return cout;
} 


Result aco(BaseGraph baseGraph, int num_ants, double alpha, double beta, double gamma, double ro, int max_trial){
  int MAX_NOT_BETTER_TRY = max_trial;

  ACOGraph graph(baseGraph);

  Result result;
  int not_better_try(0);
  int num_trial(0);
  cout << "Trial cofiguration:" << 
          "\n\t num_vehicile(s): " << num_ants <<
          "\n\t alpha: " << alpha << 
          "\n\t beta: " << beta <<
          "\n\t gamma: " << gamma << 
          "\n\t ro: " << ro << '\n';
  while(not_better_try < MAX_NOT_BETTER_TRY){
    // cout << "Trial " << num_trial++ << '\n';
    srand(time(NULL));
    
    vector<Path> paths;
    vector<bool> visited(graph.num_nodes, false);
    visited[graph.start_node.id] = true;
    int num_not_visited = graph.num_nodes-1;

    for (int k=0; k<num_ants && num_not_visited>0; ++k){
      Path path;
      path.add_node(graph.start_node);
      double capability = graph.max_capability;
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
    // for (Path &path: paths)
    //   std::cout << path << '\n';
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
    // Create result for the trial
    Result current_result(paths);
    if (result < current_result || num_not_visited){
      ++not_better_try;
      continue;
    }
    result = Result(paths);
    // cout << "Trial's result: \n" << current_result << "\n\n";
    not_better_try = 0;
  }
  return result;
}

