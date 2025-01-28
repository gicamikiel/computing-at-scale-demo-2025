#include <iostream>
#include "vector.hpp"

int main(int argc, char** argv) {
  Vector v(10);
  for(int i=0; i<v.size(); ++i){
    v[i] = i;
  }
  Vector v2(v);

  for(int i=0; i<v.size(); ++i){
    std::cout<<"("<<v[i]<<","<<v2[i]<<") ";
  }
  std::cout<<"\n";

}