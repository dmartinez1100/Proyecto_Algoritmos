#include<iostream>
#include<future>
#include<chrono>
#include<time.h>
using namespace std;

void fiboconthread(int n);
void fibosinthread(int end);

void tiempofibosinthread(int n);
void tiempofiboconthread(int n);

const int numerofibo = 21; // 21 ----> 5 segs(thread)  	43----> 6 segs(no thread)
bool compararthreads = true;

//variables globales para guardar el resultado;
int fibosin=0;
int fibocon=0;

int main(){
	if(compararthreads){
		cout<<"fibo("<<numerofibo<<") usando threads: "<<flush;
		tiempofiboconthread(numerofibo);
	}
	cout<<"\nfibo("<<numerofibo<<") sin usar threads: "<<flush;
	tiempofibosinthread(numerofibo);

    return 0;
}
//calcula el tiempo del algoritmo usando threads
void tiempofiboconthread(int n){
	clock_t t=clock();
	fiboconthread(n);
	cout<<fibocon<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}
//metodo que toma el tiempo del algoritmo sin thread
void tiempofibosinthread(int n){
	clock_t t=clock();
	fibosinthread(n);
	cout<<fibosin<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}

//sucesion de Fibonacci usando threads, crea 2 threads por recursion (extremadamente ineficiente)
	//input: entero n
	//output: void
void fiboconthread(int n){
	thread fn1;
	thread fn2;
	if(0<=n && n<=1)
		fibocon += n;
	else{
		fn1= thread(fiboconthread,n-1);
		fn2= thread(fiboconthread,n-2);
		fn1.join();
		fn2.join();
	}
}
//sucesion de Fibonacci
	//input: entero n
	//output: void
void fibosinthread(int end){
	if(end<=1)
		fibosin += end;
	else{
		fibosinthread(end-1);
		fibosinthread(end-2);
	}
}
