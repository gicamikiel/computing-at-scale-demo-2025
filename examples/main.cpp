#include <iostream>
#include "vector.hpp"

int main(int argc, char** argv) {
  Vector v(10);
  for(int i=0; i<v.size(); ++i){
    v[i] = i;
  }
  //Vector v2(v);
  Vector v2(10);
  {
    Vector v3(100);
    for(int i=0; i<v3.size(); ++i){
      v3[i] = i;
    }
    v2 = std::move(v3);
    std::cout<<"V3 size: "<<v3.size()<<"\n";
  }

  for(int i=0; i<v2.size(); ++i){
    std::cout<<"("<<v2[i]<<") ";
  }
  std::cout<<"\n";

}