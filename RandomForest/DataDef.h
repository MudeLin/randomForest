#ifndef DATADEF_
#define DATADEF_
#include <stdlib.h>
#include <vector>
#include <list>
using namespace std;
const int MAX_FEATURE = 3400;
const int MAX_DATA_SIZE = 40100;
const int NUM_CLASS = 10;
const int NUM_THREAD = 1;
/*880 min*/
typedef struct Node{
	int feature_index;
	int split_val;
	int label;
} Node;

typedef struct DataIndexSet{
	vector<int> indexs;
	int size;
}DataIndexSet;

typedef struct DataSet{
	int data[MAX_DATA_SIZE][MAX_FEATURE];
	int dataSize;
	int featureSize;
	int labelCol;
} DataSet;

typedef struct Index_Value_Label{
	int index;
	int value;
	int label;
} SingleNode;

#endif

