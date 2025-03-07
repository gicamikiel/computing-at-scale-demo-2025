#include <vector>
#include <iostream>

class Base {
  public:
  virtual void speak() const = 0;
  void f() const {std::cout<<"f\n";}
  ~Base() { std::cout<<"Base Destructor\n";}
};

class Derived : public Base
{
  public:
  void speak() const override {std::cout<<"Hello from D1\n";}
  void f() const {std::cout<<"f in D1\n";}
  ~Derived() { std::cout<<"D1 Destructor\n";}
};

class Derived2 : public Base
{
  public:
  void speak() const override {std::cout<<"Hello from D2\n";}
  ~Derived2() { std::cout<<"D2 Destructor\n";}

};

int main() {

  std::vector<Base*> classes;
  classes.push_back(new Derived{});
  classes.push_back(new Derived2{});

  for (const auto* c : classes ) {
    c->speak();
    c->f();
  }
  for(auto* c : classes) {
    delete c;
  }

}