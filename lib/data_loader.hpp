#ifndef DATA_LOADER_H
#define DATA_LOADER_H 1
#define InputN 64		// number of neurons in the input layer
#define HN 25			// number of neurons in the hidden layer
#define OutN 64			// number of neurons in the output layer
#define datanum 500		// number of training samples
template <class T>
class data_loader{
public:
	typedef struct{
	    T input[InputN];
	    T teach[OutN];
    }data;
    data dataset[datanum];
    data_loader();
};

//template specialization for double
template <>
data_loader<double>::data_loader();

#endif