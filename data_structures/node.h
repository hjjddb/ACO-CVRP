#include <math.h>
#include <string>

class Node {
  public:
    int id;
    double x,
           y,
           quantity;

    Node(){
      id = -1;
      x = 0;
      y = 0;
      quantity = 0;
    }

    Node(int id, double x, double y, double quantity){
      this->id = id;
      this->x = x;
      this->y = y;
      this->quantity = quantity;
    }

    double distance(Node other){
      /*
      Using Euclide distance
      */
      return sqrt(pow(x-other.x, 2) + pow(y-other.y, 2));
    }

    std::string toString() {
      return "coordinates: (" + std::to_string(x) + ", " + std::to_string(y) + "), quantity: " + std::to_string(quantity) + "\n";
    }
};

double distance(Node a, Node b){
  return a.distance(b);
}