#include <iostream>
#include "vector.hpp"

void constructor_assignment() {
  Vector v(10);
  for(int i=0; i<v.size(); ++i){
    v[i] = i;
  }
  Vector v2(v);

  for(int i=0; i<v.size(); ++i){
    std::cout<<v[i]<<" ";
  }
  std::cout<<"\n";

  Vector v3;
  v3 = v;
}

void move_semantic() {
  Vector v2;
  {
    Vector v3(100);
    for(int i=0; i<v3.size(); ++i) {
      v3[i] = i;
    }
    v2 = std::move(v3);
  }
}

int main(int argc, char** argv) {
  move_semantic();
}