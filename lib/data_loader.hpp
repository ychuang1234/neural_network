#ifndef DATA_LOADER_H
#define DATA_LOADER_H 1
//#define InputN 64		// number of neurons in the input layer
#define HN 25			// number of neurons in the hidden layer
//#define OutN 64			// number of neurons in the output layer
//#define datanum 500		// number of training samples
template <class I,class O>
class data_loader{
public:
	typedef struct{
	    I input;
	    O teach;
    }data;
    data *dataset;
    data_loader();
    data_loader(int,int,int);
    data_loader(int,int,int,int,int);
};

//template specialization for double
template <> 
data_loader<double,double>::data_loader(int,int,int);
template <>
data_loader<double,double>::data_loader(int,int,int,int,int);
#endif