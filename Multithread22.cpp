#include<iostream>
#include<thread>
#include<chrono>
#include<future>
using namespace std;
int fibo(int n);

int main(){
    for(int value=0 ;value<=12;value++)
	cout<<fibo(value)<<" ";
	cout<<endl;
    return 0;
}

int fibo(int n){
	if(n<=1)
		return n;
	else
		return fibo(n-1)+fibo(n-2);
}
