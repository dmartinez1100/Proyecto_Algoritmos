#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

int main(){
  int value=1;
  value++;
  auto f=[](int value){
    std::this_thread::sleep_for(std::chrono::seconds(value));
      cout<<"segundos: "<<value<<flush<<endl;
  };
auto g=[](int value){
    for(auto j=0;j<value;j++){}cout<<"proceso del for: "<<endl;
  };
      std::thread t1(f,1);
    std::thread t2(f,2);
    std::thread t3(f,0);
    std::thread t4(g,1500000000000);
    std::thread t5(f,54745745735);
    t1.join();
    t2.join();
    t4.join();
    t3.join();
    t5.join();
  return 0;
}
