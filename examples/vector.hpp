#include <sstream>
#include <cassert>

class Vector {
  public:

  Vector() : data_(nullptr), size_(0) {}
  explicit Vector(int size) {
    size_ = size;
    data_ = new double[size];
  }

  // copy constructor
  // argument v must have &, or else C++ will copy v and use copy constructor (circular)
  // we are not modifying the original so we use const
  // "const Vector& v" equivalent to "Vector const & v"
  // const applies to the thing to the left of it, except here where it applies everywhere(?)
  Vector(const Vector& v) : data_(new double[v.size()]), size_(v.size()) {
    assert(v.size() == size_);
    for(int i=0; i<v.size(); ++i) {
      data_[i] = v[i];
    }
  }

  ~Vector() noexcept {
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