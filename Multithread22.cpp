#include<iostream>
#include<thread>
#include<chrono>
#include<future>
using namespace std;
int fibo(int n);
int fibonop(int n);

int main(){
	cout<<fibo(24)<<" "<<flush;
	//cout<<fibonop(24)<<" "<<flush;
	cout<<endl;
    return 0;
}

int fibo(int n){
	//cout<<n<<" ";
	future<int> fn;
	int x;
	if(n<=1)
		return n;
	else
		fn= async(launch::async,fibo,n-1);
		x=fn.get();
		return x+fibo(n-2);
}

int fibonop(int n){
	//cout<<n<<" ";
	if(n<=1)
		return n;
	else
		return fibonop(n-1)+fibonop(n-2);
}
