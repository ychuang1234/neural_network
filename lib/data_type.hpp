#ifndef DATA_TYPE_H
#define DATA_TYPE_H 1
template <typename T>
class _1D_vector;

template<typename T>
std::ostream& operator<< ( std::ostream& os, _1D_vector<T>& L);

template<typename T>
_1D_vector<T> operator+ (_1D_vector<T>&lhs, _1D_vector<T>&rhs);

template<typename T>
_1D_vector<T> operator- (_1D_vector<T>&lhs, _1D_vector<T>&rhs);

//template<typename T> 
//T &operator[] (int i);

template <typename T>
class _1D_vector{
private:
	std::vector<T> data;
public:
	_1D_vector(int len);
	_1D_vector(T* start,int len);
	int length();
	T& operator[](int);
    friend std::ostream& operator<< <>(std::ostream& os,_1D_vector& L);
    friend _1D_vector<T> operator+ <> (_1D_vector&lhs,_1D_vector&rhs);
    friend _1D_vector<T> operator- <> (_1D_vector&lhs,_1D_vector&rhs);
};

#endif