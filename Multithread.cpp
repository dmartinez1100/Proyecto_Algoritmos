//Created by: David Martinez y Miguel Castillo
#include<iostream>
#include<thread>
#include<future>
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
void productopuntosinthread(vector<int>& vector1,vector<int>& myvector);
void productopuntoconthread(vector<int>& vector1,vector<int>& myvector);
int productopunto(vector<int>& vector1,vector<int>& myvector,int n,int y);

int main(){

	//creamos los vectores (n enteros random,rango 1,rango2)
	cout<<"Creando vectores...\nNOTA: Si es muy grande puede tardar unos segundos."<<endl;
	srand(time(NULL));
	vector<int> myvector=vectorrandom(100000000);
	pausefor(1);//pausa de 1 segundo para generar el segundo vector distinto al primero
	vector<int> myvector2=vectorrandom(100000000);//vector de n enteros rango[1,100]

	//imprimimos los vectores (solo cuando son pequenos)
	//printvector(myvector);
	//printvector(myvector2);

	//hacemos la operacion suma comparando el uso de threads sin su uso
	cout<<"Probemos la complejidad computacional sumando dos vectores de "<<myvector.size()<<" enteros."<<flush<<endl;
	cout<<"Suma con thread:"<<flush<<endl;
	pausefor(1);
	sumarvector(myvector,myvector2);
	cout<<"suma sin thread:"<<endl;
	pausefor(1);
	sumarsinthread(myvector,myvector2);
	//printvector(myvector); //imprime el vector sumado (solo cuando es un vector pequeno)

	//hacemos el producto punto comparando el uso de threads sin su uso
	cout<<"Ahora probemos la complejidad computacional del producto punto."<<flush<<endl;
	pausefor(2);
	cout<<"Producto con thread: "<<flush;
	pausefor(1);
	productopuntoconthread(myvector,myvector2);
	cout<<"Producto sin thread: "<<flush;
	pausefor(1);
	productopuntosinthread(myvector,myvector2);

  return 0;
}

void pausefor(int n){ //metodo que genera una pausa
	std::this_thread::sleep_for(std::chrono::seconds(n));
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

void sumarsinthread(vector<int>& vector1,vector<int>& myvector){ //suma de dos vectores sin usar threads
	clock_t t=clock();
	sumarvector2(ref(vector1),ref(myvector),0,myvector.size()/1);
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}

void productopuntosinthread(vector<int>& vector1,vector<int>& myvector){//producto punto de un vector sin usar threads
	clock_t t=clock();
	int answer=productopunto(vector1,myvector,0,vector1.size());
	cout<<answer<<endl;
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
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
