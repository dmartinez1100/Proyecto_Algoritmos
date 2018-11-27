//26 de noviembre del 2018
//Code created by: David Martinez y Miguel Castillo
//
//***********************************************************************************************************************************************************************************

//Incluimos las librerías que necesitaremos...
#include<iostream>
#include<thread>
#include<future>
#include<chrono>
#include<vector>
#include<time.h>
#include<cmath>
using namespace std;


//*********************************************************************************************************************************************************************
//DECLARACION DE VARIABLES Y FUNCIONES
//*********************************************************************************************************************************************************************

const int NUM_THREADS=1;// Declaramos la constante que representará el numero de threads que se usarán

const unsigned Vec_Size=static_cast<unsigned>(1*pow(10, 8)); 


int Producto_Punto=0;//Variable global para funcion del producto punto
int numeros_primos=0;//Variable global para funcion que calcula numeros primos hasta n
int prime_method = 9*pow(10, 4);

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
//*********************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************

//PROGRAMA PRINCIPAL
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

	double r=5e8; // con 5e8 
	cout<<"\n\nDiferencia entre la suma deln-esimo numero armonico (de izq. a der.) y el n-esimo numero armonico (de der. a izq.).\nLo haremos con n = "<<r<<flush<<endl;
	cout<<"----------> O(N) <----------\n";
	HarmonicNumber_differnce_sums(r);//*/
	cout<<"\n\n� Cuantos numeros primos hay de [ 1 , 2x10^5 ] ? --------> O(N^2)"<<flush<<endl;
	cout<<"Numeros Primos: "<<flush;
	PrimeNumbers(prime_method);

  return 0;
}

//*************************************************************************************************************************************************************
//FUNCIONES
//*************************************************************************************************************************************************************

//Funcion que suma dos vectores: vector1 y myvector
void sumarvector(vector<int>& vector1,vector<int>& myvector){ //suma de dos vectores con cantidad de threads declarada al principio
	clock_t t=clock();//tiempo incial
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
        th[n].join();//inciamos threads para que cumplan con su tarea
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;//diferencia entre tiempo final y tiempo inicial
}


//Funcion auxiliar
void sumarvector2(vector<int>& vector1,vector<int>& myvector,int n,int y){ //suma parcial de un vector
	for(int i=n;i<y;i++)
		vector1[i]=myvector[i]+vector1[i];
}

//*************************************************************************************************************************************************************
//*************************************************************************************************************************************************************

//Funcion auxiliar que calcula el producto punto entre dos vetores: vector1 y myvector, desde index n hasta index y index y
void productopunto2(vector<int>& vector1,vector<int>& myvector,int n,int y){ 
	for(int i=n;i<y;i++){
		Producto_Punto+= vector1[i]*myvector[i]*std::exp(-std::pow(std::tanh(1235563466), std::acos(-1.0L) / 12.3456L));
	}
}


//Funcionque calcula el producto punto entre dos vectores: vector1 y myvector
void productopunto(vector<int>& vector1,vector<int>& myvector){ //producto punto usando n threads
	clock_t t=clock();//tiempo incial
	
	int tamano_thread = Vec_Size/NUM_THREADS;
	int begin,end;
	
	//iniciamos threads
	vector<thread> th;
	for (unsigned n = 0; n < NUM_THREADS; n++){
		begin = n*tamano_thread;
		end = (n+1)*tamano_thread;
        th.push_back(thread(productopunto2, std::ref(vector1),std::ref(myvector),begin,end));
	}
	
	for (unsigned n = 0;n<NUM_THREADS; n++)   
		th[n].join();//inciamos threads para que cumplan con su tarea
		
	
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;//diferencia entre tiempo final y tiempo inicial
}

//*************************************************************************************************************************************************************
//*************************************************************************************************************************************************************

//Función para imprimir un vector
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

//*************************************************************************************************************************************************************
//*************************************************************************************************************************************************************

//Funcion para calcular el n-ésimo numero armónico
void HarmonicNumber_differnce_sums(double n){
	clock_t t=clock();//tiempo incial
	
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
		answer +=th[n].get();//Obtenemos los valores retornados por cada future y los sumamos a una variable answer

	cout<<"Diferencia entre resultados: "<<answer<<flush<<endl;
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;//diferencia entre tiempo final y tiempo inicial
}


//Funcion que calcula la diferencia entre la suma de izq. a der. y la suma de der. a izq. 
double HarmonicNumberaux(double begin,double end){
    return HarmonicNumber_right(begin,end)-HarmonicNumber_left(begin,end);
}


//Funcion que calcula el n-ésimo numero comenzando la suma de izquierda a derecha
double HarmonicNumber_right(double beg,double end){
    double result = 0;
    for(int i =beg; i<=end; i++){
        result += (double)1/i;
    }
    return result;
}


//Funcion que calcula el n-ésimo numero comenzando la suma de derecha a izquierda
double HarmonicNumber_left(double beg,double end){
    double result = 0;
    for(int i=(int)end; i>=(int)beg; i--){
        result += (double)1/i;
    }
    return result;
}

//*************************************************************************************************************************************************************
//*************************************************************************************************************************************************************


//Funcion que calcula la cantidad de numeros primos desde 1 hasta number
void PrimeNumbers(int number){
	clock_t t=clock();//tiempo inicial
	int tamano_thread = floor(number/NUM_THREADS);
	int begin,end;
	
	//iniciamos thread
	vector<thread> th;//vector de threads
	for (unsigned n = 0; n < NUM_THREADS; n++){
		begin = n*tamano_thread;
		end = (n+1)*tamano_thread;
		if(n == NUM_THREADS-1)end = number;
        th.push_back(thread(PrimeNumbersaux,begin,end));
	}
	
	for (unsigned n = 0;n<NUM_THREADS; n++)   
		th[n].join();//inciamos threads para que cumplan con su tarea
		
	cout<<numeros_primos<<endl;
	cout<<"  Tiempo de ejecucion: "<<(double)(clock()-t)/CLOCKS_PER_SEC<<flush<<endl;//diferencia entre tiempo final y tiempo inicial
}


//Funcion auxiliar para saber cuanto numeros primos hay desde begin hasta end
void PrimeNumbersaux(int begin,int end){
	if(begin == 0)begin++;
	for(int i=begin; i<end;i++){
		if(isPrime(i)){
			numeros_primos++;//si i es primo, se le suma 1 a la variable global
		}
	}
}

//Funcion que dice si un numero i es primo o no
bool isPrime(int i){
	bool flag=true;
	for(int j=2;j<i;j++){
		if((i%j)==0) flag= false;
	}
	return flag;
}



//*************************************************************************************************************************************************************
//*************************************************************************************************************************************************************