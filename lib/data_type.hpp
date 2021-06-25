#ifndef DATA_TYPE_H
#define DATA_TYPE_H 1
#include <vector>
template <typename T>
class activation_function{
	T sigmoid(T);
};
template <typename T> class _1D_vector;
template <typename T> class _2D_vector;
template <typename T> class _3D_vector;
/*1D*/
template<typename T>
std::ostream& operator<< ( std::ostream&, _1D_vector<T>&);

template<typename T>
_1D_vector<T> operator+ (_1D_vector<T>&, _1D_vector<T>&);

template<typename T>
_1D_vector<T> operator- (_1D_vector<T>&, _1D_vector<T>&);

template<typename T>
_1D_vector<T> dot (_1D_vector<T>&, _1D_vector<T>&);
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
	void push(T&);
	void push(_1D_vector<T>&);
	std::vector<_2D_vector<T>> reshape(int,int);
	T& operator[](int);
	_1D_vector<T> operator= (_1D_vector<T>);
	T dot_sum( _1D_vector<T>&);
	friend _1D_vector<T> dot <>( _1D_vector<T>&, _1D_vector<T>&);
    friend std::ostream& operator<< <>(std::ostream&,_1D_vector&);
    friend _1D_vector<T> operator+ <> (_1D_vector&,_1D_vector&);
    friend _1D_vector<T> operator- <> (_1D_vector&,_1D_vector&);
};

/*2D*/

template<typename T>
std::ostream& operator<< (std::ostream&, _2D_vector<T>&);

template<typename T>
_2D_vector<T> operator+ (_2D_vector<T>&, _2D_vector<T>&);

template<typename T>
_2D_vector<T> operator- (_2D_vector<T>&, _2D_vector<T>&);

template<typename T>
_2D_vector<T> operator* (_2D_vector<T>&, _2D_vector<T>&);

template<typename T>
_2D_vector<T> dot (_2D_vector<T>&, _2D_vector<T>&);

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
	_1D_vector<T>& flat();
	void push(_1D_vector<T>&);
	void push(_2D_vector<T>&);
	_1D_vector<T>& operator[](int);
	_2D_vector<T> operator= (_2D_vector<T>);
	T dot_sum(_2D_vector<T>&);
	friend _2D_vector<T> dot <>(_2D_vector<T>&,_2D_vector<T>&);
    friend std::ostream& operator<< <>(std::ostream&,_2D_vector&);
    friend _2D_vector<T> operator+ <> (_2D_vector&,_2D_vector&);
    friend _2D_vector<T> operator- <> (_2D_vector&,_2D_vector&);
    friend _2D_vector<T> operator* <> (_2D_vector&,_2D_vector&);
};
/*3D*/
/*
template <typename T> class _3D_vector;
template<typename T>
std::ostream& operator<< (std::ostream&, _3D_vector<T>&);

template<typename T>
_3D_vector<T> operator+ (_3D_vector<T>&, _3D_vector<T>&);

template<typename T>
_3D_vector<T> operator- (_3D_vector<T>&, _3D_vector<T>&);

template <typename T>
class _3D_vector{
private:
	std::vector<_2D_vector<T>> data;
public:
	_3D_vector();
	_3D_vector(int);
	_3D_vector(int,int);
	_3D_vector(int,int,int);
	_3D_vector(T*,int,int,int);
	int length();
	_2D_vector<T> operator[](int);
	_3D_vector<T> operator= (_3D_vector<T>);
    friend std::ostream& operator<< <>(std::ostream&,_3D_vector&);
    friend _3D_vector<T> operator+ <> (_3D_vector&,_3D_vector&);
    friend _3D_vector<T> operator- <> (_3D_vector&,_3D_vector&);
};
*/

/*tensor*/

#endif