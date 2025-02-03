#include <iostream>
#include "vector.hpp"
#include "noisy.hpp"

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
  Vector v2; // default constructor
  {
    Vector v3(10); // size constructor
    for(int i=0; i<v3.size(); ++i) {
      v3[i] = i;
    }
    v2 = std::move(v3); // move constructor, copy assignment
  }
}

void destructor_test() {
  Vector v2;
  {
    Vector v3(10);
    for(int i=0; i<v3.size(); ++i) {
      v3[i] = i;
    }
    v2 = std::move(v3);
  }
}

void noisy() {
  Noisy n1(1);
  Noisy n2(2);
  n1.print();
  n2.print();

  n2 = std::move(n1); 
  n2.print();
  //n2.print();
}

int main(int argc, char** argv) {
  //destructor_test();
  //move_semantic();
  noisy();
}