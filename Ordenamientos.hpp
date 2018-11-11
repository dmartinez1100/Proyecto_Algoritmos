#ifndef __libreria__hpp

#define __libreria__hpp

#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>
using namespace std;

//srand(time(NULL)); en el codigo para generar numeros
int numrandom(int rang1,int rang2);

void printvector(vector<int> & myvector);

vector<int> vectorrandom(int numeroelementos);

vector<int> vectorrandom(int numeroelementos,int rang1,int rang2);

void bogosort(vector<int> & myvector);

bool issorted(vector<int> & myvector);

void shuffle(vector<int> & myvector);

void selectionsort(vector<int> & myvector);

void quickSort(vector<int> & vector1,int i,int j);

void quickSort(vector<int> & vector1);

int partition(vector<int>  & vector1, int i, int j);
#endif


