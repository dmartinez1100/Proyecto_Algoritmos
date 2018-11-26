//Created by: David Martinez y Miguel Castillo
#include<iostream>
#include<thread>
#include<future>
#include<chrono>
#include<vector>
#include<time.h>
#include<cmath>
using namespace std;

const int NUM_THREADS=1;
const unsigned Vec_Size=static_cast<unsigned>(1*pow(10, 8)); //recomendado 10^8 (12 segs) 8 threads
int Producto_Punto=0;
int numeros_primos=0;
int prime_method = 9*pow(10, 4); //2*10^5

void sumarvector2(vector<int>& vector1,vector<int>& myvector,int n,int y);
void sumarvector(vector<int>& vector1,vector<int>& myvector);

void productopunto(vector<int>& vector1,vector<int>& myvector);
void productopunto2(vector<int>& vector1,vector<int>& myvector,int n,int y);

void printvector(vector<int> & myvector);
double HarmonicNumber_left(double begin,double end);
double HarmonicNumber_right(double begin,double end);
void HarmonicNumber_differnce_sums(double n);
double HarmonicNumberaux(double begin,double end);

void PrimeNumbersaux(int begin,int end);
void PrimeNumbers(int end);
bool isPrime(int i);

int main(){
	
	cout<<"Threads que usaremos: "<<NUM_THREADS;
	cout<<"             Hardware Threads: "<< std::thread::hardware_concurrency()<<endl;
	//creamos los vectores
	vector<int> myvector(Vec_Size,1);
	vector<int> myvector2(Vec_Size,2);

	//imprimimos los vectores (solo cuando son pequenos)
	//printvector(myvector);
	//printvector(myvector2);
	
	//hacemos la operacion suma
	cout<<"\n\nProbemos la complejidad computacional sumando dos vectores de "<<Vec_Size<<" enteros."<<flush<<endl;
	cout<<"----------> O(N) <----------\n";
	sumarvector(myvector,myvector2);
	//printvector(myvector); //imprime el vector sumado (solo cuando es un vector pequeno)
	
	//hacemos el producto punto
	cout<<"\n\nAhora probemos la complejidad computacional del producto punto."<<flush<<endl;
	cout<<"----------> O(N) <----------\n";
	productopunto(myvector,myvector2);

	double r=5e8; // con 5e8 (5 segs aprox)
	cout<<"\n\nDiferencia entre la suma deln-esimo numero armonico (de izq. a der.) y el n-esimo numero armonico (de der. a izq.).\nLo haremos con n = "<<r<<flush<<endl;
	cout<<"----------> O(N) <----------\n";
	HarmonicNumber_differnce_sums(r);//*/
	cout<<"\n\n¿ Cuantos numeros primos hay de [ 1 , 2x10^5 ] ? --------> O(N^2)"<<flush<<endl;
	cout<<"Numeros Primos: "<<flush;
	PrimeNumbers(prime_method);

  return 0;
}

void sumarvector(vector<int>& vector1,vector<int>& myvector){ //suma de dos vectores con dos threads
	clock_t t=clock();
	int tamano_thread = Vec_Size/NUM_THREADS;
	int begin,end;
	
	//iniciamos threads
	vector<thread>th;
	for (unsigned n = 0; n < NUM_THREADS; n++){
		begin = n*tamano_thread;
		end = (n+1)*tamano_thread;
        th.push_back(std::thread(sumarvector2, std::ref(vector1),std::ref(myvector),begin,end));
	}
	for (unsigned n = 0; n < NUM_THREADS; n++)
        th[n].join();
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}

void sumarvector2(vector<int>& vector1,vector<int>& myvector,int n,int y){ //suma parcial de un vector
	for(int i=n;i<y;i++)
		vector1[i]=myvector[i]+vector1[i];
}

void productopunto2(vector<int>& vector1,vector<int>& myvector,int n,int y){ //producto punto desde index n hasta index y de un vector
	for(int i=n;i<y;i++){
		Producto_Punto+= vector1[i]*myvector[i]*std::exp(-std::pow(std::tanh(1235563466), std::acos(-1.0L) / 12.3456L));
	}
}
void productopunto(vector<int>& vector1,vector<int>& myvector){ //producto punto usando n threads
	clock_t t=clock();
	
	int tamano_thread = Vec_Size/NUM_THREADS;
	int begin,end;
	
	//iniciamos future
	vector<thread> th;
	for (unsigned n = 0; n < NUM_THREADS; n++){
		begin = n*tamano_thread;
		end = (n+1)*tamano_thread;
        th.push_back(thread(productopunto2, std::ref(vector1),std::ref(myvector),begin,end));
	}
	
	for (unsigned n = 0;n<NUM_THREADS; n++)   
		th[n].join();
		
	//cout<<"Producto: "<<Producto_Punto<<endl;
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


void HarmonicNumber_differnce_sums(double n){
	clock_t t=clock();
	
	int tamano_thread = (int)n/NUM_THREADS;
	int begin,end;
	double answer=0;
	
	//iniciamos future
	vector<future<double>> th;
	for (unsigned n = 0; n < NUM_THREADS; n++){
		begin = (int)n*tamano_thread;
		end = ((int)n+1)*tamano_thread;
        th.push_back(async(HarmonicNumberaux,begin,end));
	}
	for (unsigned n = 0;n<NUM_THREADS; n++)   
		answer +=th[n].get();

	cout<<"Diferencia entre resultados: "<<answer<<flush<<endl;
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}

double HarmonicNumberaux(double begin,double end){
    return HarmonicNumber_right(begin,end)-HarmonicNumber_left(begin,end);
}

double HarmonicNumber_right(double beg,double end){
    double result = 0;
    for(int i =beg; i<=end; i++){
        result += (double)1/i;
    }
    return result;
}

double HarmonicNumber_left(double beg,double end){
    double result = 0;
    for(int i=(int)end; i>=(int)beg; i--){
        result += (double)1/i;
    }
    return result;
}
void PrimeNumbers(int number){
	clock_t t=clock();
	int tamano_thread = floor(number/NUM_THREADS);
	int begin,end;
	
	//iniciamos thread
	vector<thread> th;
	for (unsigned n = 0; n < NUM_THREADS; n++){
		begin = n*tamano_thread;
		end = (n+1)*tamano_thread;
		if(n == NUM_THREADS-1)end = number;
        th.push_back(thread(PrimeNumbersaux,begin,end));
	}
	
	for (unsigned n = 0;n<NUM_THREADS; n++)   
		th[n].join();
		
	cout<<numeros_primos<<endl;
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;
}
void PrimeNumbersaux(int begin,int end){
	if(begin == 0)begin++;
	for(int i=begin; i<end;i++)
		if(isPrime(i)){
			numeros_primos++;
		}
}
bool isPrime(int i){
	bool flag=true;
	for(int j=2;j<i;j++){
		if((i%j)==0) flag= false;
	}
	return flag;
}
