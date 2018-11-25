#ifdef heap_hpp
#include<iostream>
#include<math.h>
using namespace std;
template <typename DataType>
BinaryHeap<DataType>::BinaryHeap(int capacity) {
    count = 0;
    array = std::vector<DataType>(capacity);
}

/**
 * Inserta elem, permite duplicados
 */
template <typename DataType>
void BinaryHeap<DataType>::insert(const DataType & elem) {
  count++;
  array[count] = elem;
  size_t aux = count;
  for(size_t i = floor(count/2); i >= 1; i/=2){
    if(array[aux] <= array[i]){
      swap(array[aux],array[i]);
      aux = i;
    }
    else
      break;
  }
}

/**
 * Retorna verdadero si el heap esta vacio, falso de lo contrario
 */
template <typename DataType>
bool BinaryHeap<DataType>::isEmpty() const {
    return count == 0;
}

/**
 * Retorna el elemento minimo en el heap.
 * Lanza una excepcion si el heap esta vacio
 */
template <typename DataType>
const DataType & BinaryHeap<DataType>::findMin() const {
    if (count > 0) {
        return array[1];
    } else {
        throw std::underflow_error("Tried to find element in empty heap");
    }
}

/**
 * Elimina el elemento minimo del heap.
 * Lanza excepcion si el heapesta vacio.
 */
template <typename DataType>
void BinaryHeap<DataType>::deleteMin() {
  if(count > 0){
  percolateDown(1);
  count--;
  }
  else
  throw std::underflow_error("Tried to delete min in empty heap");
}

/**
 * Metodo privado para percolar hacia abajo un hueco creado
 * (e.g. al eliminar un eemento).
 */
template <typename DataType>
void BinaryHeap<DataType>::percolateDown(int hole) {

  unsigned izq = 2*hole;
  unsigned der = (2*hole)+1;
  if(der <= count){ // si hijo dereho existe obligatoriamente el izquierdo existe
    if(array[izq] < array[der]){ // hijo izq < der
      array[hole] = array[izq];
      percolateDown(izq);
    }
    else{
      array[hole] = array[der];
      percolateDown(der);
    }
  }
  else if(izq <= count){   // si hijo izquierdo existe pero no el derecho
    array[hole] = array[izq];
    percolateDown(izq);
  }
    else //no tiene hijos luego es unma hoja
      array[hole] = array[count];
}
/**
 * Muestra todos los elementos del heap en salida estandar
 */
template <typename DataType>
void BinaryHeap<DataType>::display() const {
    for(unsigned int i = 1; i <= count; ++i ){
        std::cout << array[i];
        std::cout << std::endl;
    }
}

#endif /* heap_hpp */
