#include <cstdlib>
#include <exception>
#include <iostream>
#include <cstdarg>
#include "Matrix.hpp"

template<typename T>
Matrix<T>::Matrix(int x, int y)
	: _values(NULL),
	_x(x),
	_y(y)
{
	_values = new T*[y];
	for (int i = 0; i < y; ++i)
		_values[i] = new T[x];
}

template<typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < _y; ++i)
		delete[] _values[i];
	delete[] _values;
}

template<typename T>
T	&Matrix<T>::getAt(int x, int y)
{
	return _values[y][x];
}

template<typename T>
void	Matrix<T>::values(int nb, ...)
{
	if (nb != _y * _x)
		throw std::exception("Can't fill properly");

	va_list ap;
	
	va_start(ap, nb);
	for (int y = 0; y < _y; ++y)
	{

		for (int x = 0; x < _x; ++x)
		{
			T val = va_arg(ap, T);
			std::cerr << val << std::endl;
			_values[y][x] = val;
		}
	}
	va_end(ap);
}

template<>
void	Matrix<float>::values(int nb, ...)
{
	if (nb != _y * _x)
		throw std::exception("Can't fill properly");

	va_list ap;

	va_start(ap, nb);
	for (int y = 0; y < _y; ++y)
	{
		for (int x = 0; x < _x; ++x)
		{
			double val = va_arg(ap, double);
			
			_values[y][x] = (float)val;
		}
	}
	va_end(ap);
}

template<typename T>
void	Matrix<T>::dump()
{
	for (int j = 0; j < _y; ++j)
	{
		for (int i = 0; i < _x; ++i)
			std::cerr << _values[j][i];
		std::cerr << std::endl;
	}
}

template class Matrix<int>;
template class Matrix<float>;