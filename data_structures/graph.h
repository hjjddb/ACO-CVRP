#pragma once

#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <iostream>
#include <set> 

#include "matrix.h"
#include "path.h"

using std::vector;
using std::set;
using std::to_string;


class BaseGraph {
  public:
    int num_nodes;
    Node start_node;
    vector<Node> nodes;
    Matrix distances;

    BaseGraph(){
      num_nodes = 0;
      start_node = Node();
    }

    Matrix get_distances(vector<Node> nodes){
      Matrix matrix(num_nodes, num_nodes);
      for (int i=0; i<nodes.size(); ++i)
        for(int j=i+1; j<nodes.size(); ++j){
          matrix[i][j] = matrix[j][i] = distance(nodes[i], nodes[j]);
        }
      return matrix;
    }

    BaseGraph(std::vector<Node> nodes){
      this->nodes = nodes;
      this->num_nodes = nodes.size();
      distances = get_distances(nodes);
    }


    std::string toString(){
      std::string output = "";
      output += "Number of nodes: " + to_string(num_nodes) + "\n";
      output += "Node list: \n";
      for(int i=0; i<nodes.size(); ++i)
        output += "\t" + nodes[i].toString();
      output += "Adjacenct Matrix: \n";
      for(int i=0; i<num_nodes; ++i)
        for(int j=0; j<num_nodes; ++j)
          output += to_string(distances[i][j]) + " \n"[j==num_nodes-1];
      return output;
    }

    Path dfs(Node current_node, vector<bool> visited, Path path){
      visited[current_node.id] = true;
      path.trace.push_back(current_node);
      path.total_distance += distances[path.trace.back().id][current_node.id];
      // LOCAL CHEAPEST INSERTION
      double min_path = (*max_element(distances[current_node.id].begin(), distances[current_node.id].end()))+1;
      Node next_node;
      for(int id=0; id<num_nodes; ++id){
        if (!visited[id] && min_path > distances[current_node.id][id]){
          min_path = distances[current_node.id][id];
          next_node = nodes[id];
        }
      }
      if (next_node.id == -1){
        path.total_distance += distances[current_node.id][start_node.id];
        return path;
      }
      return dfs(next_node, visited, path);
    }
};

class ACOGraph : public BaseGraph {
  public: 
    Matrix heuristic;
    Matrix pheromone;
    Matrix probabilities;
    Matrix saving;

    ACOGraph(BaseGraph graph){
      num_nodes = graph.num_nodes;
      nodes = graph.nodes;
      start_node = graph.start_node;
      distances = graph.distances;
      heuristic = get_heuristic();
      pheromone = get_pheromone();
      probabilities = get_probabilities();
      saving = get_saving();
    }

    Matrix get_heuristic(){
      Matrix matrix(num_nodes, num_nodes);
      for(int i=0; i<num_nodes; ++i) 
        for(int j=i+1; j<num_nodes; ++j)
          matrix[i][j] = matrix[j][i] = 1/distances[i][j];
      return matrix;
    }

    Matrix get_pheromone(){
      Matrix matrix(num_nodes, num_nodes, 1);
      // vector<bool> visited(num_nodes, true);
      // Path path;
      // path.trace.push_back(1);
      // vector<Path> full_paths;
      // for(int i=0; i<num_nodes; ++i){
      //   if (i != start_node){
      //     full_paths.push_back(dfs(i, visited, path));
      //   }
      // }

      // for (int i=0; i<full_paths.size(); ++i){
      //   for(int j=0; j<full_paths[i].trace.size()-1; ++j){
      //     matrix[full_paths[i].trace[j]][full_paths[i].trace[j+1]] += 1/full_paths[i].total_distances;
      //     matrix[full_paths[i].trace[j+1]][full_paths[i].trace[j]] += 1/full_paths[i].total_distances;
      //   }
      // }
      return matrix;
    }

    void update_pheromone_matrix();

    Matrix get_probabilities(){
      Matrix matrix(num_nodes, num_nodes);
    //   for(int i=0; i<num_nodes; ++i)
    //     for(int j=0; j<num_nodes; ++j){
          
    //     } 
      return matrix;
    }

    Matrix get_saving(){
      Matrix matrix(num_nodes, num_nodes);
      for(int i=0; i<num_nodes; ++i)
        for(int j=0; j<num_nodes; ++j){
          matrix[i][j] = distances[i][start_node.id] + distances[j][start_node.id] - distances[i][j];
        }
      return matrix;
    }
};

class BiGraph {
  public:
    vector<Node> left_nodes,
                 right_nodes;
    int num_left_nodes, 
        num_right_nodes;
    vector<vector<double>> distances;

    BiGraph(){

    }

    BiGraph(vector<Node> left_nodes, vector<Node> right_nodes){
      this->left_nodes = left_nodes;
      this->right_nodes = right_nodes;
      this->num_left_nodes = left_nodes.size();
      this->num_right_nodes = right_nodes.size();
      distances = get_distances();
    }

    vector<vector<double>> get_distances(){
      vector<vector<double>> matrix(num_left_nodes, vector<double>(num_right_nodes));
      for(int i=0; i<num_left_nodes; ++i) 
        for(int j=0; j<num_right_nodes; ++j)
          matrix[i][j] = distance(left_nodes[i], right_nodes[j]);
      return matrix;
    }
};