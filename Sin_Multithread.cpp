#include<iostream>
#include<vector>
#include<chrono>
#include<time.h>
using namespace std;

void multiplicarescalar(int escalar,vector<int>& myvector);
void sumarvector(vector<int>& vector1,vector<int>& myvector);
int productopunto(vector<int>& vector1,vector<int>& myvector);
void printvector(vector<int> & myvector);

int main(){
	//creamos los vectores
	cout<<"------------Sin Thread------------"<<endl;
	vector<int> myvector(100000000,1);
	vector<int> myvector2(100000000,2);
	
	//imprimimos los vectores (solo cuando son pequenos)
	//printvector(myvector);
	//printvector(myvector2);

	//hacemos la operacion suma
	cout<<"Probemos la complejidad computacional sumando dos vectores de "<<myvector.size()<<" enteros."<<flush<<endl;
	sumarvector(myvector,myvector2);
	//printvector(myvector);

	//hacemos el producto punto
	cout<<"Ahora probemos la complejidad computacional del producto punto."<<flush<<endl;
	int j=productopunto(myvector,myvector2);
	cout<<"Producto sin thread: "<<j<<endl<<flush;
}
int productopunto(vector<int>& vector1,vector<int>& myvector){ //producto punto de un vector
	clock_t t=clock();
	int answer=0;
	for(size_t i=0;i<vector1.size();i++){
		answer+= vector1[i]*myvector[i];
	}
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
	return answer;
}
void sumarvector(vector<int>& vector1,vector<int>& myvector){ //suma de un vector
	clock_t t=clock();
	for(size_t i=0;i<vector1.size();i++)
		vector1[i]=myvector[i]+vector1[i];
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}
void multiplicarescalar(int escalar,vector<int>& myvector){//multiplica un escalar por un vector(sin threads)
	for(size_t i=0;i<myvector.size();i++)
		myvector[i]=myvector[i]*escalar;
	cout<<"vector multiplicado por el escalar: "<<escalar<<endl;
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