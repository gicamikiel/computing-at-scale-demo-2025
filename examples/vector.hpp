#include <sstream>
#include <cassert>

class Vector {
  public:

  Vector() : data_(nullptr), size_(0) {
    std::cout<<"default constructor\n";
  }
  explicit Vector(int size) {
    std::cout<<"constructor with size\n";
    size_ = size;
    data_ = new double[size];
  }

  // copy constructor
  Vector(const Vector & v) : data_(new double[v.size()]), size_(v.size())  {
    std::cout<<"Calling copy constructor\n";
    assert(v.size() == size_);
    std::copy(&(v.data_[0]), &(v.data_[size_]), &(data_[0]));
  }

  /*
  Vector& operator=(Vector other) {
    std::cout<<"copy assignment\n";
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    return *this;
  }
  */

  Vector& operator=(const Vector& other){
    std::cout<<"copy assignment\n";
    Vector tmp(other);
    std::swap(data_, tmp.data_);
    std::swap(size_, tmp.size_);
    return *this;
  }

  // move constructor
  Vector(Vector&& other){
    std::cout<<"move constructor";
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }
  Vector& operator=(Vector&& other) {
    std::cout<<"move assignment\n";
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
    return *this;
  }


  ~Vector() noexcept {
    std::cout<<"destructor\n";
    delete data_;
  }

  // TODO operator[]
  [[nodiscard]]
  double& operator[](int idx) {
    if(idx >= size_) {
      std::stringstream ss;
      ss << "idx "<<idx<< " is out of bounds for a size " << size_;
      throw std::runtime_error(ss.str());
    }
    return data_[idx];
  }

  [[nodiscard]]
  const double& operator[](int idx) const {
    if(idx >= size_) {
      std::stringstream ss;
      ss << "idx "<<idx<< " is out of bounds for a size " << size_;
      throw std::runtime_error(ss.str());
    }
    return data_[idx];
  }

  [[nodiscard]]
  int size() const noexcept { return size_;}

  // what does the push_back function look like. Push back is like append for a python list.
  // what does copy construction look like

  private:
  double* data_;
  int size_;
};