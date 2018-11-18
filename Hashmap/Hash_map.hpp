#include<iostream>
#include<list>
using namespace std;

#ifndef _Hash_map_hpp
#define _Hash_map_hpp

const size_t PRIME_INITIAL_DIMENSION = 5;
template<typename dataType> class hashfunction;

template<>
class hashfunction<string>{
public:
  size_t operator()(const string & key){
    return static_cast<size_t>(key.length());
  }
};

template<typename KeyType,typename dataType>
class Myhash{
private:
  struct Pair{
    KeyType key;
    dataType data;
    Pair* link;
  };
  size_t count;
  size_t nbuckets;
  list<Pair*>*table;
  size_t hashing(const KeyType & key);
public:
  Myhash();

  bool find(const KeyType & key)const;
  bool insert(const KeyType & key,const dataType & data);
  bool remove(const KeyType & key);
  void clear();
  void display()const;
};
#include "Hash_map.cpp"
#endif
