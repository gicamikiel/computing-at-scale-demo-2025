#include <sstream>
#include <cassert>

class Vector {
	public:

	Vector() : data_(nullptr), size_(0) {
		std::cout<<"default constructor\n";
	}
	explicit Vector(int size) {
		std::cout<<"size constructor\n";
		size_ = size;
		data_ = new double[size];
	}

	// copy constructor
	// argument v must have &, or else C++ will copy v and use copy constructor (circular)
	// we are not modifying the original so we use const
	// "const Vector& v" equivalent to "Vector const & v"
	// const applies to the thing to the left of it, except here where it applies everywhere(?)
	Vector(const Vector& v) : data_(new double[v.size()]), size_(v.size()) {
		std::cout<<"copy constructor\n";
		assert(v.size() == size_);
		for(int i=0; i<v.size(); ++i) {
			data_[i] = v[i];
		}
	}

	// use when other will not be used anymore
	// efficient transfer of resources
	// lvalue (named obj) rvalue (temp obj)
	// z = x + y (z is lvalue, x+y is rvalue)
	// void f(int&& x) x is rvalue reference
	// void g(int& x) x is lvalue reference
	// void h(int x) x is a lvalue
	Vector(Vector&& other) : data_(nullptr), size_(0) {
		std::cout<<"move constructor\n";
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
	}

	~Vector() noexcept {
		std::cout<<"destructor\n";
		//print();
		if(data_) delete data_;
	}

	// note: we want value semantic or deep copy
	// note: if we use Vector v, c++ makes a copy!!!!!!!
	// note: if we use Vector& v, it does not!!!!!!!!
	Vector& operator=(Vector other) {
		std::cout<<"copy assignment\n";
		// could get away with Vector v
		// uses copy constructor
		// if exception throws here, other grows out of scope, and no memory leak
		// no code reuse, reuses code in copy constructor
		// good default choice, but may cost performance
		std::swap(data_, other.data_); // swapping the address (fine to do this because v is a copy)
		std::swap(size_, other.size_); // swapping
		return *this;

		// use when using Vector& v
		/*
		if(this != &other) {
			size_ = other.size_;
			data_ = new double[size_];
			for(int i=0; i<other.size(); ++i) {
				data_[i] = other[i];
				// if exception throws here, we have a memory leak
			}
		}
		return *this;
		*/    
	}

	// not needed if you use copy and swap idiom?
	/*
	Vector& operator=(Vector&& other) {
		std::swap(data_, other.data_); // swapping the address (fine to do this because v is a copy)
		std::swap(size_, other.size_); // swapping
		return *this;
	}
	*/

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

	void print() {
		for(int i=0; i<size_; ++i) {
			std::cout << data_[i] << " ";
		}
		std::cout << "\n";
	}

	private:
	// note, if we use default constructor
	// we get mix of value and reference semantics
	// because data_ is guaranteed to agree between two vector objects
	// but then size_ is copied by value and might change
	double* data_;
	int size_;
};