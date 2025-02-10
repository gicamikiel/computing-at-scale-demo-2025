#include <iostream>
#include "vector.hpp"
#include "noisy.hpp"

void constructor_assignment() {
  Vector<double> v(10);
  for(int i=0; i<v.size(); ++i){
    v[i] = i;
  }
  Vector<double> v2(v);

  for(int i=0; i<v.size(); ++i){
    std::cout<<v[i]<<" ";
  }
  std::cout<<"\n";

  Vector<double> v3;
  v3 = v;
}

void move_semantic() {
  Vector<double> v2; // default constructor
  {
    Vector<double> v3(10); // size constructor
    for(int i=0; i<v3.size(); ++i) {
      v3[i] = i;
    }
    v2 = std::move(v3); // move constructor, copy assignment
  }
}

void destructor_test() {
  Vector<double> v2;
  {
    Vector<double> v3(10);
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

void noisy_curly() {
  Noisy n1{1};
  auto n2 = Noisy{2};
  Noisy n3 = {3};
  n1 = n2;
  n2 = std::move(n3);
  auto n4{std::move(n1)};
}

void value(Noisy n){}
void ref(Noisy& n){}
void cref(const Noisy& n){}
void rref(Noisy&& n){}

/*
void noisy_curly_2() {
  Noisy n1{1}, n2{2}, n3{3};
  value(n1);
  value(std::move(n1));
  value(Noisy{4});
  ref(Noisy{5});
  cref(Noisy{6});
  rref(n2); // any moves?
  rref(std::move(n3));
}
*/

int main(int argc, char** argv) {
  destructor_test();
  //move_semantic();
  //noisy_curly();
  std::cout << "\n";
  //noisy();
}