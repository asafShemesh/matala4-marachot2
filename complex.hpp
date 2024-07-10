//asaf0604@gmail.com  325362457
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <QString>

class Complex
{
public:
    double real; // Real part of the complex number
    double imag; // Imaginary part of the complex number

    /// @brief Constructor for Complex numbers.
    /// @param r Real part (default is 0.0).
    /// @param i Imaginary part (default is 0.0).
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    /// @brief Overloaded output stream operator to display complex numbers.
    /// @param os Output stream.
    /// @param c Complex number to output.
    /// @return Reference to the output stream.
    friend std::ostream &operator<<(std::ostream &os, const Complex &c)
    {
        os << c.real << " + " << c.imag << "i";
        return os;
    }

    /// @brief Equality operator to compare two complex numbers.
    /// @param other Another complex number to compare with.
    /// @return True if both real and imaginary parts are equal.
    bool operator==(const Complex &other) const
    {
        return (real == other.real && imag == other.imag);
    }

    /// @brief Less than operator to compare two complex numbers.
    /// @param other Another complex number to compare with.
    /// @return True if the magnitude of this complex number is less than the other.
    bool operator<(const Complex &other) const
    {
        return (real * real + imag * imag) < (other.real * other.real + other.imag * other.imag);
    }

    /// @brief Convert the complex number to a QString.
    /// @return QString representation of the complex number.
    QString toString() const
    {
        return QString::number(real) + " + " + QString::number(imag) + "i";
    }
};

#endif 
