#include <bits/stdc++.h>
using namespace std;

class Complex
{
private:
    double _real;
    double _imag;

public:
    Complex(double _real = 0, double _imag = 0);
    Complex(const Complex &_complex);
    double &real();
    double &imag();
    Complex real(const double &_real);
    Complex imag(const double &_imag);
    Complex operator+(const Complex &_complex);
    Complex operator-(const Complex &_complex);
    Complex operator*(const Complex &_complex);
    Complex operator/(const Complex &_complex);
    friend ostream &operator<<(ostream &out, const Complex &_complex);
    friend istream &operator>>(istream &in, const Complex &_complex);
};

Complex::Complex(double _ireal, double _iimag) : _real(_ireal), _imag(_iimag) {}

Complex::Complex(const Complex &_complex) : _real(_complex._real), _imag(_complex._imag) {}

double &Complex::real()
{
    return _real;
}

double &Complex::imag()
{
    return _imag;
}

Complex Complex::real(const double &_ireal)
{
    _real = _ireal;
    return *this;
}

Complex Complex::imag(const double &_iimag)
{
    _imag = _iimag;
    return *this;
}

Complex Complex::operator+(const Complex &_complex)
{
    Complex tmp(_real + _complex._real, _imag + _complex._imag);
    return tmp;
}

Complex Complex::operator-(const Complex &_complex)
{
    Complex tmp(_real - _complex._real, _imag - _complex._imag);
    return tmp;
}

Complex Complex::operator*(const Complex &_complex)
{
    Complex tmp(_real * _complex._real - _imag * _complex._imag, _real * _complex._imag + _imag * _complex._real);
    return tmp;
}

Complex Complex::operator/(const Complex &_complex)
{
    Complex tmp((_real * _complex._real + _imag * _complex._imag) / (_complex._real * _complex._real + _complex._imag * _complex._imag), (_real * _complex._real - _imag * _complex._imag) / (_complex._real * _complex._real + _complex._imag * _complex._imag));
}