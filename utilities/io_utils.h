#include <fstream>

#include "../extended_libraries/rapidxml-1.13/rapidxml.hpp"
#include "../data_structures/graph.h"

BaseGraph read_input(std::string xml_path){
  std::ifstream file(xml_path);
  vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  buffer.push_back('\0');

  rapidxml::xml_document<> doc;
  doc.parse<0>(&buffer[0]);
  rapidxml::xml_node<> *nodes = doc.first_node("instance")->first_node("network")->first_node("nodes")->first_node("node"),
             *fleet = doc.first_node("instance")->first_node("fleet"),
             *requests = doc.first_node("instance")->first_node("requests")->first_node("request"); 

  vector<Node> graph_nodes; 
  int start_node_id = -1,
      num_nodes = atoi(fleet->first_node("vehicle_profile")->first_node("departure_node")->value()),
      capability = atof(fleet->first_node("vehicle_profile")->first_node("capacity")->value());
  
  for (int i=0; nodes; nodes=nodes->next_sibling(), ++i){
    double cx = atof(nodes->first_node("cx")->value()),
           cy = atof(nodes->first_node("cy")->value());
    int type = atoi(nodes->first_attribute("type")->value());
    if (!type) start_node_id = i;
    graph_nodes.push_back(Node(i, cx, cy, 0));
  }
  int i(0);
  for (; requests; requests=requests->next_sibling()){
    graph_nodes[i++].quantity = atof(requests->first_node("quantity")->value());
  }
  
  BaseGraph graph(graph_nodes);
  graph.start_node = graph_nodes[start_node_id];
  graph.max_capability = capability;
  return graph;
}
