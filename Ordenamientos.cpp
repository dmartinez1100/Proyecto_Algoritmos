#include "Ordenamientos.hpp"
#include<time.h>
#include<stdlib.h>


int numrandom(int rang1,int rang2){
	return rang1+rand()%(rang2+1-rang1);

}

void printvector(vector<int> & myvector){
	cout<<'[';
	if(myvector.empty()) cout<<']';
	else{
	for(size_t i=0;i<myvector.size()-1;i++){
		cout<<myvector[i]<<", ";
		}
	cout<<myvector.at(myvector.size()-1)<<']';
	}
	cout<<"\n";
}

vector<int> vectorrandom(int numeroelementos){
	srand(time(NULL));
	vector<int> estevector;
	for(int i=0;i<numeroelementos;i++)
		estevector.push_back(numrandom(0,100));
	return estevector;
}
vector<int> vectorrandom(int numeroelementos,int rang1,int rang2){
	srand(time(NULL));
	vector<int> estevector;
	for(int i=0;i<numeroelementos;i++)
		estevector.push_back(numrandom(rang1,rang2));
	return estevector;
}
void bogosort(vector<int> & myvector){
	while(issorted(myvector)== false){
		shuffle(myvector);
		cout<<"sorting\n";
	}
}
bool issorted(vector<int> & myvector){
	for(size_t i=0;i<myvector.size()-1;i++){
		if (myvector[i]>myvector[i+1]){
			return false;}
	}
	return true;
}
void shuffle(vector<int> & myvector){
	for(size_t i=0;i<=myvector.size();i++){
		swap(myvector[i],myvector[numrandom(0,myvector.size()-1)]);
	}
}
void selectionsort(vector<int> & myvector){
	for(size_t i=0;i<myvector.size();i++){
		int minindex=i;
		for(size_t j=i+1;j<myvector.size();j++){
			if(myvector[j]<myvector[minindex])
				minindex=j;		
			}
		swap(myvector[i],myvector[minindex]);
	cout<<"ordenando "<<myvector.size()<<" elementos"<<endl;
	}
}
void quickSort(vector<int> & vector1, int i, int j){
  if(i<j){
    int par= partition(vector1, i,j);
    quickSort(vector1, i, par-1);
    quickSort(vector1, par+1, j);

  }
}
void quickSort(vector<int> & vector1){
	quickSort(vector1,0,vector1.size()-1);
}
int partition(vector<int>  & vector1, int i, int j){
  int pivot=vector1[j];
  int low = (i-1);
  for(int h= i; h<= j-1; h++){
    if(vector1[h]<= pivot){
      low++;
      swap(vector1[low], vector1[h]);
    }
  }
  swap(vector1[low+1], vector1[j]);
  return (low+1);
}
