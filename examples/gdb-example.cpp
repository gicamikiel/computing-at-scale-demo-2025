// Example program to show off gdb debugging
#include <iostream>
#include <vector>
#include <span> 
#include <algorithm>

// Compute square of a number
double square(double x) {
    return x * x;
}

// Compute sum of squares (calls square)
double sum_of_squares(std::span<double> arr) {
    double sum = 0.0;
    for (double x : arr) {
        sum += square(x);  // Indirect call to square
    }
    return sum;
}

// Wrapper function that could do preprocessing, but for now just calls sum_of_squares
double process_data(std::span<double> arr) {
    std::transform(arr.begin(), arr.end(), arr.begin(), [](double x) { return x + 1; });
    return sum_of_squares(arr);
}

int main() {
    int n;
    std::cout << "Enter number of elements: ";
    std::cin >> n;

    std::vector<double> data(n);

    std::cout << "Enter " << n << " floating-point numbers: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    // Main calls process_data, which calls sum_of_squares, which calls square
    double result = process_data(data);

    std::cout << "Sum of squares: " << result << std::endl;

    return 0;
}