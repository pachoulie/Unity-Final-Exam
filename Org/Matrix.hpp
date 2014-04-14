#ifndef MATRIX_HPP
#define MATRIX_HPP

//#include <varargs.h>

template<typename T>
class Matrix
{
public:
	Matrix(int rows, int column);
	~Matrix();

	void	values(int, ...);
	T	&getAt(int, int);
	inline int	x() { return _x; }
	inline int y() { return _y; }
	void	dump();

private:
	T		**_values;
	int		_x;
	int		_y;
};

#endif