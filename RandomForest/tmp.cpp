//*
//#include "DecisionTree.h"
//#include <iostream>
//#include <algorithm>
//#include <math.h>
//#include <stdlib.h>
//#include <queue>
//#include <fstream>
//#include <time.h>
//#include <sstream>
//#include "LoadData.h"
//
//using namespace std;
//
//static const double EPSILON = 0.000001;
//const int Max_Node = 142200;
//
//double calcShannonEntropy(const DataSet *dataSet,const DataIndexSet *indexSet){
//	double entropy = 0.0;
//	int votes[NUM_CLASS] = {0};
//	int colLabel = dataSet->labelCol;
//	int N = indexSet->size;
//	list<int>::const_iterator itr = (indexSet->indexs).begin();
//	for(;itr != (indexSet->indexs).end(); itr++){
//		int sampleIndex = *itr;
//		int curLabel = (dataSet->data)[sampleIndex][colLabel];
//		votes[curLabel] += 1;
//	}
//	/*
//	for(int i = 0;i < N;i++){
//		int sampleIndex = (indexSet->indexs)[i];
//		int curLabel = (dataSet->data)[sampleIndex][colLabel];
//		votes[curLabel] += 1;
//	}
//	*/
//	for(int i = 0;i < NUM_CLASS;i++){
//		double p = double(votes[i]/N);
//		entropy = entropy + (-p * log(p) );
//	}
//	return entropy;
//}
//double calcInfoGain(const DataSet *dataSet,const DataIndexSet *indexSet,const DataIndexSet *leftChild,const DataIndexSet *rightChild){
//	double infoGain = 0.0;
//	int Nl = leftChild->size;
//	int Nr = rightChild->size;
//	int N = indexSet->size;
//	double parentEntropy = calcShannonEntropy(dataSet,indexSet);
//	double leftEntropy = calcShannonEntropy(dataSet,leftChild);
//	double rightEntropy = calcShannonEntropy(dataSet,rightChild	);
//	infoGain = parentEntropy - (double(Nl)/N)*leftEntropy - (double(Nr)/N)*rightEntropy;
//	return infoGain;
//}
//double calcChildGiniIndex(const DataSet *dataSet, const DataIndexSet *indexSet){
//	int colLabel = dataSet->labelCol;
//	int votes[NUM_CLASS] = {0};
//	int N = indexSet->size;
//
//	list<int>::const_iterator itr = (indexSet->indexs).begin();
//	for(;itr != (indexSet->indexs).end(); itr++){
//		int sampleIndex = *itr;
//		int curLabel = (dataSet->data)[sampleIndex][colLabel];
//		votes[curLabel] += 1;
//	}
//	/*
//	for(int i = 0 ;i < N ;i++){
//		int sampleIndex = (indexSet->indexs)[i];
//		int curLabel = (dataSet->data)[sampleIndex][colLabel];
//		votes[curLabel] += 1;
//	
//	}
//	*/
//	double giniIndex = 1.0;
//	double p;
//	
//	for(int i = 0; i< NUM_CLASS;i++){
//		p = double(votes[i])/N;
//		giniIndex = giniIndex - p*p; 
//	}
//	
//	return giniIndex;
//}
//
//double calcParentGiniIndex(const DataSet *dataSet,const DataIndexSet *parent,const DataIndexSet *leftChild ,const  DataIndexSet *rightChild){
//	double pGiniIndex = 0.0;
//	int N = parent->size;
//	int Nl = leftChild->size;
//	int Nr = rightChild->size;
//	double lGiniIndex = calcChildGiniIndex(dataSet,leftChild);
//	double rGiniIndex = calcChildGiniIndex(dataSet,rightChild);
//	
//	pGiniIndex = double(Nl)/N * lGiniIndex + double(Nr)/N * rGiniIndex;
//	return pGiniIndex;
//}
//
//bool cmp(const SingleNode &a,const SingleNode &b){
//	return (a.value < b.value);
//}
//void extractValueSet(const DataSet *dataSet,const DataIndexSet *curDataIndexSet,const int curFeatureIndex, vector<SingleNode> *tmpSet){
//	(*tmpSet) = vector<SingleNode>(curDataIndexSet->size);
//	list<int>::const_iterator itr = (curDataIndexSet->indexs).begin();
//	int i = 0;
//	for(; itr != (curDataIndexSet->indexs).end(); itr ++,i++){
//		int curIndex = *itr;
//		(*tmpSet)[i].index = curIndex;
//		(*tmpSet)[i].label = (*dataSet).data[curIndex][1];
//		(*tmpSet)[i].value = (*dataSet).data[curIndex][curFeatureIndex]; 
//	}
//}
//void splitDataIndexSet(const vector<SingleNode> *tmpSet ,const int curIndex, DataIndexSet *rSet){
//	rSet -> size = 0;
//	rSet ->indexs =  list<int>();
//	int N = (int)(tmpSet->size());
//	/* cur tmp set i is origin Index*/
//	for(int i = curIndex;i < N;i++){
//		rSet->indexs.push_back((*tmpSet)[i].index);
//	}
//	rSet->size = (int)(rSet->indexs.size());
//
//}
//
//int chooseBestSplitValue(vector<SingleNode> *tmpSet,const DataSet *dataSet,const DataIndexSet *curDataIndexSet,double &curMinGini){
//	sort(tmpSet->begin(),tmpSet->end(),cmp);
//	
//	int N = (int)(tmpSet->size());
//	int preValue = (*tmpSet)[0].value;
//	DataIndexSet *lSet = new DataIndexSet();
//	
//	lSet->indexs = list<int>();
//	lSet->size = 0;
//
//	(lSet->indexs).push_back(((*tmpSet)[0]).index);
//	lSet->size += 1;
//	double ministGini = 1.0;
//	int bestSplitValue = (*tmpSet)[0].value;
//	bool allEqualFlag = true;
//
//	for(int i = 1;i < N;i++){
// 		int curValue = (*tmpSet)[i].value;
//		if(preValue == curValue ){
//			(lSet->indexs).push_back( ((*tmpSet)[i]).index);
//			lSet->size += 1;
//			continue;
//		}else{
//			allEqualFlag = false;
//			DataIndexSet *rSet = new DataIndexSet();
//			splitDataIndexSet(tmpSet,i,rSet);
//			double gini = calcParentGiniIndex(dataSet,curDataIndexSet,lSet,rSet);
//			delete rSet;
//
//			if( abs((gini - 0.0)) < 1.0*EPSILON){
//				bestSplitValue = preValue;
//				ministGini = gini;
//				break;
//			}else{
//				if( gini < ministGini ){
//					ministGini = gini;
//					bestSplitValue = preValue;
//
//				}
//			}
//			preValue = curValue;
//		}
//		(lSet->indexs).push_back( ((*tmpSet)[i]).index);
//		lSet->size += 1;
//	}
//	delete lSet;
//	if(allEqualFlag){
//		ministGini = calcChildGiniIndex(dataSet,curDataIndexSet);
//	}
//	curMinGini = ministGini;
//	return bestSplitValue;
//}
//
//int voteForLabel(const DataSet *dataSet,const DataIndexSet *curDataIndexSet){
//	int vote[NUM_CLASS] = {0};
//	int size = curDataIndexSet->size;
//	if(size == 0){
//		cout<<"Are you kidding size must gt 0"<<endl;
//		return -1;
//	}
//	int MaxLabel = -1,MaxVotes = 0;
//	int labelCol = dataSet->labelCol;
//	list<int>::const_iterator itr = (curDataIndexSet->indexs).begin();
//
//	for(; itr != (curDataIndexSet->indexs).end() ;itr ++){
//
//		int sampleIndex = *itr;
//		int curLabel = (dataSet->data)[ sampleIndex][labelCol]; 
//		vote[curLabel] += 1;
//		if(vote[curLabel] > MaxVotes){
//			MaxLabel = curLabel;
//			MaxVotes = vote[curLabel];
//		}
//	}
//	return MaxLabel;
//}
//
//Node chooseBestSplitNode(const DataSet *dataSet,const DataIndexSet *curDataSetIndex,const vector<int> *featureIndexes,const int minN,const double minMinus){
//	Node splitNode;
//	splitNode.feature_index = -1;
//	splitNode.split_val = -1;
//	splitNode.label =  -1;
//	if(curDataSetIndex->size <= minN){
//		splitNode.label = voteForLabel(dataSet,curDataSetIndex);
//		return splitNode;
//	}
//	/* idCol = 0, labelCol = 1*/
//	double ministGini = 1.0;
//	int minGini_feat = 0;
//	int minGini_val = 0;
//	double curNodeGini = calcChildGiniIndex(dataSet,curDataSetIndex);
//
//	if( abs(curNodeGini - 0.0) < 1.0*EPSILON){
//		splitNode.label = voteForLabel(dataSet,curDataSetIndex);
//		return splitNode;
//	}
//
//	for(int i = 0;i < (int)featureIndexes->size();i++){
//		int curFeatureIndex = (*featureIndexes)[i];
//
//		vector<SingleNode> *tmpSet = new vector<SingleNode>();
//		extractValueSet(dataSet,curDataSetIndex,curFeatureIndex,tmpSet);
//		double curMinGini = 1.0;
//
//		int splitVal = chooseBestSplitValue(tmpSet,dataSet,curDataSetIndex,curMinGini);
//		
//		delete tmpSet;		
//
//		if( abs((curMinGini - 0.0)) < 1.0 *EPSILON){
//			ministGini = curMinGini;
//			minGini_feat = curFeatureIndex;
//			minGini_val = splitVal;
//			break;
//		}else{
//			if( curMinGini < ministGini   ){
// 				ministGini = curMinGini;
//				minGini_feat = curFeatureIndex;
//				minGini_val = splitVal;
//				
//			}
//		}
//	}
//	if( abs(curNodeGini - ministGini)  < minMinus ){
//		splitNode.label = voteForLabel(dataSet,curDataSetIndex);
//		return splitNode;
//	}
//	splitNode.feature_index = minGini_feat;
//	splitNode.split_val = minGini_val;
//		
//	return splitNode;
//}
//
//void splitDataIndex(const DataSet *dataSet,const DataIndexSet *curIndexSet,const Node &splitNode ,DataIndexSet *lSet, DataIndexSet *rSet){
//	
//	lSet->indexs =  list<int>();
//	rSet->indexs =  list<int>();
//
//	int featureIndex = splitNode.feature_index;
//	int splitVal = splitNode.split_val;
//	/*
//	for(int i = 0;i < curIndexSet->size;i++){
//		int sampleIndex = (curIndexSet->indexs)[i];
//		*/
//	list<int>::const_iterator itr = (curIndexSet->indexs).begin();
//
//	for(; itr != (curIndexSet->indexs).end() ;itr ++){
//		int sampleIndex = *itr;
//		if( (dataSet->data)[sampleIndex][featureIndex] <= splitVal){
//			(lSet->indexs).push_back( sampleIndex );
//		}else{
//			(rSet->indexs).push_back( sampleIndex );
//		 }
//	}
//	lSet->size = (int)(lSet->indexs).size();
//	rSet->size = (int)(rSet->indexs).size();
//}
//void writeDtreeToFile(const vector<Node> &dTree,const int threadIndex ,const string dtFilePath = "data\\dtree")
//{
//	ofstream ofs;
//	 
//	try{
//		stringstream ss;
//
//		ss<<dtFilePath<<threadIndex<<".csv";
//
//		ofs.open(ss.str().c_str(),std::ofstream::out | std::ofstream::trunc);
//
//		//if(ofs.is_open()){
//			//cout<<"Open: "<<ss.str()<<endl;
//		//}
//		ofs<<"Feature,val,label"<<endl;
//		//cout<<"Feature,val,label"<<endl;
//		for(int i = 0;i < (int)dTree.size();i++){
//			ofs<<dTree[i].feature_index<<","<<dTree[i].split_val<<","<<dTree[i].label<<endl;
//			
//		}
//		ofs.close();
//	}catch(ofstream::failure ex){
//		cout<<"Can not save dtree in disk"<<endl;
//	}
//
//}
//void getSampleFeature(const int numOffeature, vector<int> *featureIndexSet){
//	int sampleSize = 55; /* sqrt(numberoffeature) */
//	
//	vector<int>::iterator itr;
//	for(int i = 0;i < sampleSize; i ++){
//		int sampleI;
//		while(true){
//			sampleI = (rand() % (numOffeature)) + 2 ;
//			itr = find(featureIndexSet->begin(),featureIndexSet->end(),sampleI);
//			if(itr == featureIndexSet->end()){
//				break;
//			}
//		}
//		featureIndexSet->push_back(sampleI);
//	}
//}
//
//void getSampleIndexes(const DataSet *dataset, DataIndexSet *sampleIndexes,const double sampleRate,const int threadIndex){
//	int size = (int) (double(dataset->dataSize) * sampleRate);
//	//srand(time(NULL));
//	int seed = threadIndex * 10;
//	srand(seed);
//	for(int i = 0;i <size;i++){
//		int sampleI = rand() % (dataset->dataSize);
//		sampleIndexes->indexs.push_back(sampleI);
//	}
//	sampleIndexes->size = (int)(sampleIndexes->indexs).size();
//}
//
//void trainTree(const DataSet *dataSet,vector<Node> &dtree, const double tolS,const int tolN, const int threadIndex){
//	
//	vector<DataIndexSet> indexVec = vector<DataIndexSet>(Max_Node);
//	
//	dtree = vector<Node>(Max_Node);
//
//	DataIndexSet *sampleIndexes = new DataIndexSet();
//	double sampleRate = 0.8;
//	getSampleIndexes(dataSet,sampleIndexes,sampleRate,threadIndex);
//	indexVec[0] = (*sampleIndexes);
//	
//	delete sampleIndexes;
//
//	int numOfFeature = (dataSet->featureSize) -2;
//		
//	
//	DataIndexSet *emptySet = new DataIndexSet();
//	emptySet->size = -1;
//
//	for(int i = 0 ;i < Max_Node;i++){
//		cout<<i<<endl;
//		DataIndexSet *curIndexSet = &indexVec[i];
//		if( curIndexSet->size == -1){
//			continue;
//		}
//		if( (2*i + 1 )>= Max_Node || (2*i + 2 )>= Max_Node){
//			Node leafNode = Node();
//			leafNode.feature_index = -1;
//			leafNode.split_val = -1;
//			leafNode.label = voteForLabel(dataSet,curIndexSet);
//			dtree[i] = leafNode; /*add current node to dtree , IMPORTANT*/
//			continue;
//		}
//		vector<int> *sampleFeatureIndexes = new vector<int>();
//		getSampleFeature(numOfFeature,sampleFeatureIndexes);
//	
//		Node splitNode = chooseBestSplitNode(dataSet,curIndexSet,sampleFeatureIndexes,tolN,tolS);
//		delete sampleFeatureIndexes;
//
//		dtree[i] = splitNode;
//		
//		/*tree node */
//		if(splitNode.label == -1){
//			DataIndexSet *lIndexes = new DataIndexSet();
//			DataIndexSet *rIndexes = new DataIndexSet(); 
//			
//			splitDataIndex(dataSet,curIndexSet,splitNode,lIndexes,rIndexes);
//			indexVec[2*i + 1] = (*lIndexes);
// 			indexVec[2*i + 2] = (*rIndexes);
//			//cout<<"Left size:"<<lIndexes->size<<endl;
//			//cout<<"Rigt size:"<<rIndexes->size<<endl;
//			delete lIndexes;
//			delete rIndexes;
//		/*leaf node */
//		}else{
//			queue<int> qu = queue<int>();
//			qu.push(i);
//			while(! qu.empty()){
//				int curI = qu.front();
//				qu.pop();
//
//				indexVec[curI] = (*emptySet);
//				if ( 2*curI +1 < Max_Node)
//				{
//					qu.push(2*curI +1);
//					if ( 2*curI +2 < Max_Node )
//					{
//							qu.push(2*curI + 2);
//					}
//
//				}
//					
//			}
//		}
//	}
//	delete emptySet;	
//	writeDtreeToFile(dtree,threadIndex);
//}
//
//void predictOnASample(const int sample[], const vector<Node> &dTree,int &predictLabel,const int threadIndex){
//	int curNodeIndex = 0;
//	//cout<<threadIndex<<" "<<"A judge: ";
//	while(true){
//		int judgeFea = dTree[curNodeIndex].feature_index;
//		int judgeVal = dTree[curNodeIndex].split_val;
//		int judgeLabel = dTree[curNodeIndex].label;
//		
//		//cout<< curNodeIndex<<"Label:"<<judgeLabel<<endl;
//		if( judgeLabel != -1){
//			predictLabel = judgeLabel;
//			break;
//		}else{
//			/* first element is id ,missing label*/
//			int sampleVal = sample[judgeFea - 1 ];
//			if(sampleVal <= judgeVal){
//				/*left side*/
//				curNodeIndex = 2*curNodeIndex +1;
//			}else{
//				/*right side*/
//				curNodeIndex = 2*curNodeIndex + 2;
//			}
//		}
//		if(curNodeIndex >= Max_Node){
//			cout<<"Error :"<<"Label not found"<<endl;
//			break;
//		}
//
//	}
//}
//void savePredictToDistk(const DataSet *testData,const vector<int> &predictLabels,const int threadIndex,const string outputPath = "data\\output"){
//	int numOfTestCases = (int)(testData -> dataSize);
//	ofstream ofs;
//	try{
//		stringstream ss;
//
//		ss << outputPath << threadIndex << ".csv";
//		
//		ofs.open(ss.str().c_str(),std::ofstream::out | std::ofstream::trunc);
//		//if(ofs.is_open()){
//			//cout<<"Open: "<<ss.str()<<endl;
//		//}
//		ofs<<"Id,label"<<endl;
//		for(int i = 0;i < numOfTestCases;i ++){
//			int castId = (testData->data)[i][0];
//			int predictLabel = predictLabels[i];
//			ofs<<castId<<","<<predictLabel<<endl;
//		}
//		ofs.close();
//	}catch (ofstream::failure ex){
//		cout<<"Cannot writ to predict file"<<endl;
//	}
//}
//void getTrainedNode(vector<Node> &dtree,const int threadIndex){
//	stringstream ss;
//	ss << "data\\dtree"<<threadIndex<<".csv";
//	DataSet *dataSet = new DataSet();
//	LoadData(ss.str().c_str(),dataSet);
//	for(int i = 0;i <dataSet->dataSize ;i ++){
//		Node node;
//		node.feature_index = dataSet->data[i][0];
//		node.split_val = dataSet->data[i][1];
//		node.label = dataSet->data[i][2];
//		dtree.push_back(node);
//	}
//	delete dataSet;
//}
//*precondtidion feature col size must fixed origin train Data*/
//void predictOnDataSet(const DataSet *testDataSet, const vector<Node> &dTree, const int threadIndex){
//	vector<int> *predictLabels = new vector<int>();
//	int numOfTestCases = (int)(testDataSet->dataSize);
//	
//	for(int i = 0;i <numOfTestCases;i++){
//		int curLabel = -1;
//		predictOnASample(((testDataSet->data)[i]),dTree,curLabel,threadIndex);
//		predictLabels->push_back(curLabel);
//	}
//	savePredictToDistk(testDataSet,(*predictLabels),threadIndex);
//	delete predictLabels;
//}
//
