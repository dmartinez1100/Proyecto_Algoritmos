#include<iostream>
#include<thread>
#include<chrono>
#include "Ordenamientos.hpp"
#include<vector>
#include<time.h>
using namespace std;
void pausefor(int n);
void multiplicarescalar(int escalar,vector<int>& myvector);
void sumarvector2(vector<int>& vector1,vector<int>& myvector,int n,int y);
void sumarvector(vector<int>& vector1,vector<int>& myvector);
void sumarsinthread(vector<int>& vector1,vector<int>& myvector);

int main(){
	vector<int> myvector;
	vector<int> myvector2;
	for(int i=0;i<100000000;i++){
		myvector.push_back(i);
		myvector2.push_back(i);
	}
	//printvector(myvector);
	//printvector(myvector);
	cout<<"suma con thread"<<flush<<endl;
	sumarvector(myvector,myvector2);
	cout<<"suma sin thread"<<flush<<endl;
	sumarsinthread(myvector,myvector2);
	//printvector(myvector);
  return 0;
}
void pausefor(int n){
	std::this_thread::sleep_for(std::chrono::seconds(n));
}
void multiplicarescalar(int escalar,vector<int>& myvector){
	for(size_t i=0;i<myvector.size();i++)
		myvector[i]=myvector[i]*escalar;
	cout<<"vector multiplicado por el escalar: "<<escalar<<endl;
}
void sumarvector(vector<int>& vector1,vector<int>& myvector){
	clock_t t=clock();
	if(vector1.size()!=myvector.size())throw runtime_error("no puedes sumar vectores de distinto orden");
	int i=myvector.size()/2;
	thread f1(sumarvector2,ref(vector1),ref(myvector),0,i);
	thread f2(sumarvector2,ref(vector1),ref(myvector),i,myvector.size()/1);
	f1.join();
	f2.join();
	cout<<"tiempo: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}

void sumarvector2(vector<int>& vector1,vector<int>& myvector,int n,int y){
	for(int i=n;i<y;i++)
		vector1[i]=myvector[i]+vector1[i];
}
void sumarsinthread(vector<int>& vector1,vector<int>& myvector){
	clock_t t=clock();
	sumarvector2(ref(vector1),ref(myvector),0,myvector.size()/1);
	cout<<"tiempo: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}
