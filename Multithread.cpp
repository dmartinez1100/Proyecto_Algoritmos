//Created by: David Martinez y Miguel Castillo
#include<iostream>
#include<thread>
#include<future>
#include<chrono>
#include<vector>
#include<time.h>
using namespace std;


void multiplicarescalar(int escalar,vector<int>& myvector);
void sumarvector2(vector<int>& vector1,vector<int>& myvector,int n,int y);
void sumarvector(vector<int>& vector1,vector<int>& myvector);
void productopuntoconthread(vector<int>& vector1,vector<int>& myvector);
int productopunto(vector<int>& vector1,vector<int>& myvector,int n,int y);
void printvector(vector<int> & myvector);
int main(){

	//creamos los vectores
	cout<<"------------Con Thread------------"<<endl;
	vector<int> myvector(100000000,1);
	vector<int> myvector2(100000000,2);

	//imprimimos los vectores (solo cuando son pequenos)
	//printvector(myvector);
	//printvector(myvector2);

	//hacemos la operacion suma
	cout<<"Probemos la complejidad computacional sumando dos vectores de "<<myvector.size()<<" enteros."<<flush<<endl;
	sumarvector(myvector,myvector2);
	//printvector(myvector); //imprime el vector sumado (solo cuando es un vector pequeno)

	//hacemos el producto punto
	cout<<"Ahora probemos la complejidad computacional del producto punto."<<flush<<endl;
	cout<<"Producto con thread: "<<flush;
	productopuntoconthread(myvector,myvector2);

  return 0;
}

void multiplicarescalar(int escalar,vector<int>& myvector){//multiplica un escalar por un vector(sin threads)
	for(size_t i=0;i<myvector.size();i++)
		myvector[i]=myvector[i]*escalar;
	cout<<"vector multiplicado por el escalar: "<<escalar<<endl;
}
void sumarvector(vector<int>& vector1,vector<int>& myvector){ //suma de dos vectores con dos threads
	clock_t t=clock();
	if(vector1.size()!=myvector.size())throw runtime_error("no puedes sumar vectores de distinto orden");
	int i=myvector.size()/2;
	thread f1(sumarvector2,ref(vector1),ref(myvector),0,i);
	thread f2(sumarvector2,ref(vector1),ref(myvector),i,myvector.size()/1);
	f1.join();
	f2.join();
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}

void sumarvector2(vector<int>& vector1,vector<int>& myvector,int n,int y){ //suma parcial de un vector
	for(int i=n;i<y;i++)
		vector1[i]=myvector[i]+vector1[i];
}

int productopunto(vector<int>& vector1,vector<int>& myvector,int n,int y){ //producto punto desde index n hasta index y de un vector
	int answer=0;
	for(int i=n;i<y;i++){
		answer+= vector1[i]*myvector[i];
	}
	return answer;
}
void productopuntoconthread(vector<int>& vector1,vector<int>& myvector){ //producto punto usando 2 threads
	clock_t t=clock();
	int i=myvector.size()/2;
	future<int> f1=async(launch::async,productopunto,ref(vector1),ref(myvector),0,i);
	future<int> f2=async(launch::async,productopunto,ref(vector1),ref(myvector),i,myvector.size()/1);
	int answer=f1.get()+f2.get();
	cout<<answer<<endl;
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
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
