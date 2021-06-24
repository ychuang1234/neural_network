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
    int datanum;
    data *dataset;
    int start_id;
    int batch_size;
    vector<I> batch_x;
    vector<O> batch_y;
    data_loader();
    data_loader(int,int,int);
    data_loader(int,int,int,int,int);
    int load_batch();


};

//template specialization for double
template <> 
data_loader<double,double>::data_loader(int,int,int);
template <>
data_loader<double,double>::data_loader(int,int,int,int,int);
#endif