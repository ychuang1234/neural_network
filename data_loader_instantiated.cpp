#include "lib\data_loader.cpp"
#include "lib\data_type.cpp"
template class data_loader<double>;
template class data_loader<int>;
/*1D vector*/
template class _1D_vector<int>;
template class data_loader<_1D_vector<int>>;
template class _1D_vector<double>;
template class data_loader<_1D_vector<double>>;
/*2D vector*/
template class _2D_vector<int>;
template class data_loader<_2D_vector<int>>;
template class _2D_vector<double>;
template class data_loader<_2D_vector<double>>;