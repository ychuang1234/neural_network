#ifndef DATA_TYPE_H
#define DATA_TYPE_H 1
#include <vector>
template <typename T>
class _1D_vector;

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
	_1D_vector(int len);
	_1D_vector(T* start,int len);
	int length();
	T& operator[](int);
	_1D_vector<T> operator= (_1D_vector<T>&);
    friend std::ostream& operator<< <>(std::ostream&,_1D_vector&);
    friend _1D_vector<T> operator+ <> (_1D_vector&,_1D_vector&);
    friend _1D_vector<T> operator- <> (_1D_vector&,_1D_vector&);
};

#endif