#ifndef DATA_TYPE_H
#define DATA_TYPE_H 1
#include <vector>
template <typename T> class _1D_vector;

template<typename T>
std::ostream& operator<< ( std::ostream&, _1D_vector<T>&);

template<typename T>
_1D_vector<T> operator+ (_1D_vector<T>&, _1D_vector<T>&);

template<typename T>
_1D_vector<T> operator- (_1D_vector<T>&, _1D_vector<T>&);

template <typename T>
class _1D_vector{
private:
	std::vector<T> data;
public:
	_1D_vector();
	_1D_vector(int);
	_1D_vector(int,int);
	_1D_vector(T*,int);
	int length();
	T& operator[](int);
	_1D_vector<T> operator= (_1D_vector<T>);
    friend std::ostream& operator<< <>(std::ostream&,_1D_vector&);
    friend _1D_vector<T> operator+ <> (_1D_vector&,_1D_vector&);
    friend _1D_vector<T> operator- <> (_1D_vector&,_1D_vector&);
};


template <typename T> class _2D_vector;
template<typename T>
std::ostream& operator<< (std::ostream&, _2D_vector<T>&);

template<typename T>
_2D_vector<T> operator+ (_2D_vector<T>&, _2D_vector<T>&);

template<typename T>
_2D_vector<T> operator- (_2D_vector<T>&, _2D_vector<T>&);

template <typename T>
class _2D_vector{
private:
	std::vector<_1D_vector<T>> data;
public:
	_2D_vector();
	_2D_vector(int);
	_2D_vector(int,int);
	_2D_vector(T*,int,int);
	int length();
	_1D_vector<T>& operator[](int);
	_2D_vector<T> operator= (_2D_vector<T>);
    friend std::ostream& operator<< <>(std::ostream&,_2D_vector&);
    friend _2D_vector<T> operator+ <> (_2D_vector&,_2D_vector&);
    friend _2D_vector<T> operator- <> (_2D_vector&,_2D_vector&);
};

#endif