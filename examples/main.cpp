#include <iostream>
#include "vector.hpp"

void pass_by_reference(Vector& v) {
  std::cout<<v[0]<<"\n";
}
void pass_by_const_reference(const Vector& v) {
  std::cout<<v[0]<<"\n";
}
void pass_by_value(Vector v) {
  std::cout<<v[0]<<"\n";
}


int main(int argc, char** argv) {
  Vector v(10);
  for(int i=0; i<v.size(); ++i){
    v[i] = i;
  }
  pass_by_reference(v);
  pass_by_value(v);
  pass_by_const_reference(v);

  return 0;
}