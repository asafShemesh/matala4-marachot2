#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <string>

class Complex {
public:
    double real;  // Real part of the complex number
    double imag;  // Imaginary part of the complex number

    /// @brief Constructor for Complex numbers.
    /// @param r Real part (default is 0.0).
    /// @param i Imaginary part (default is 0.0).
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    /// @brief Overloaded output stream operator to display complex numbers.
    /// @param os Output stream to which the complex number is written.
    /// @param c Complex number to be displayed.
    /// @return Reference to the output stream.
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }

    /// @brief Equality operator to compare two complex numbers.
    /// @param other Another complex number to compare against.
    /// @return True if both real and imaginary parts are equal.
    bool operator==(const Complex& other) const {
        return (real == other.real && imag == other.imag);
    }

    /// @brief Less than operator to compare two complex numbers.
    /// @param other Another complex number to compare against.
    /// @return True if the magnitude of this complex number is less than the other.
    bool operator<(const Complex& other) const {
        return (real * real + imag * imag) < (other.real * real + other.imag * imag);
    }

    /// @brief Convert the complex number to a string for display.
    /// @return String representation of the complex number.
    std::string toString() const {
        return std::to_string(real) + " + " + std::to_string(imag) + "i";
    }
};

#endif // COMPLEX_HPP
