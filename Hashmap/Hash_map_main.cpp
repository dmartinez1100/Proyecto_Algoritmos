#include<iostream>
#include"Hash_Map.hpp"
using namespace std;

const string h="hola";
const int n=2;

int main() {
  Myhash<string,int> ashe;
  cout<<ashe.insert("l",n)<<endl;
  cout<<ashe.insert("lol",n)<<endl;
  cout<<ashe.insert("i",n)<<endl;
  cout<<ashe.insert("r",n)<<endl;
  cout<<ashe.insert("r",n)<<endl;
  cout<<ashe.insert("hola",n)<<endl;
  cout<<ashe.insert("hola",n)<<endl;
  cout<<"exitoso"<<endl;
  return 0;
}
