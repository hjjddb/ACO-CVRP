#include <ctime>
#include <random>

double randf(){
  srand(time(NULL));
  return (double)rand()/RAND_MAX;
}