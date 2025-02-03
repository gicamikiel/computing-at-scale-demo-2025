#include <sstream>
#include <cassert>

class Noisy {
	public: 
	Noisy(int number) : number_(number) {
		std::cout<<"number constructor " << number_ <<"\n";
	}

	Noisy(const Noisy& other) : number_(other.number_) {
		std::cout<<"copy constructor " << number_ <<"\n";
	}

	Noisy(Noisy&& other) {
		// is this correct?
		number_ = other.number_;

		std::cout<<"move constructor " << number_ <<"\n";
	}

	~Noisy() noexcept {
		std::cout<<"destructor " << number_ <<"\n";
	}

	// move AND copy assignment
	Noisy& operator=(Noisy other) {
		number_ *= -1;
		std::swap(number_, other.number_);
		std::cout<<"copy assignment " << number_ <<"\n";
		return *this;
	}

	void print() {
		std::cout << number_ << "\n";
	}

	private:
	int number_ = -1;
};