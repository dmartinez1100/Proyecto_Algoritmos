#include <iostream>
#include<list>
using namespace std;

#ifdef _Hash_map_hpp

template<typename KeyType,typename dataType>
size_t Myhash<KeyType,dataType>::hashing(const KeyType & key){
  hashfunction<KeyType> hashprueba;
  return hashprueba(key) % nbuckets;
}

template<typename KeyType,typename dataType>
Myhash<KeyType,dataType>::Myhash(){
  nbuckets = PRIME_INITIAL_DIMENSION;
  table=new list<Pair*>;
  for(size_t i=0;i<nbuckets;i++)
  table->push_back(nullptr);
  count=0;
}

template<typename KeyType,typename dataType>
void Myhash<KeyType,dataType>::clear(){
  for(auto i=table->begin();i!=table->end();i++)
    delete *i;
}
template<typename KeyType,typename dataType>
bool Myhash<KeyType,dataType>::insert(const KeyType & key,const dataType & data){
  int bucket= hashing(key) % nbuckets;
  cout<<"hash: "<<bucket<<endl;
  auto j=table->begin();
  for(int i=0;i<bucket;i++)
    j++;
  Pair* aux = *j;
  if(aux==nullptr){
    (*j)=new Pair();
    (*j)->key=key;
    (*j)->data=data;
    count++;
    return true;
  }
  else{
    if(aux->key==key){
      aux->data=data;
      return false;
    }
    for(;aux->link != nullptr;aux=aux->link){
      if(aux->link->key==key) {
        aux->link->data=data;
        return false;
      }
    }
    aux->link=new Pair();
    aux->link->data=data;
    aux->link->key=key;
    count++;
    return true;
  }
}
#endif
