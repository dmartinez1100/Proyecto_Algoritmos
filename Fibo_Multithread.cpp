#include<iostream>
#include<future>
using namespace std;
int fiboconthread(int n);
int fibosinthread(int n);

int main(){
	cout<<"fibo(24) usando threads: "<<flush;
	cout<<fiboconthread(24)<<" "<<flush;
	cout<<"\nfibo(24) sin usar threads: "<<flush;
	cout<<fibosinthread(24)<<" "<<flush;
	cout<<endl;
    return 0;
}

int fiboconthread(int n){
	future<int> fn;
	int x;
	if(n<=1)
		return n;
	else
		fn= async(launch::async,fiboconthread,n-1);
		x=fn.get();
		return x+fiboconthread(n-2);
}

int fibosinthread(int n){
	if(n<=1)
		return n;
	else
		return fibosinthread(n-1)+fibosinthread(n-2);
}
