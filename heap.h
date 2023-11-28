#ifndef HEAP_H_
#define HEAP_H_
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
template <class T>
class Heap {
private:
    T *data;
    unsigned int tam;
    unsigned int cntr;
    unsigned int parent(unsigned int) const;
    unsigned int left(unsigned int) const;
    unsigned int right(unsigned int) const;
    void heapify(unsigned int);
    void swap(unsigned int, unsigned int);
public:
    Heap(unsigned int) ;
    ~Heap();
    bool empty() const;
    bool full() const;
    T pop() ;
    void clear();
    void push (T val);
    int top ();
    int size ();
    string toString() const;
};
template <class T>
Heap<T>::Heap(unsigned int sze) {
tam = sze;
data = new T[tam];
cntr = 0;
}
template <class T>
Heap<T>::~Heap() {
delete [] data;
data = 0;
tam = 0;
cntr = 0;
}
template <class T>
bool Heap<T>::empty() const {
return (cntr == 0);
}
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
return (pos - 1) / 2;
}
template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
return ((2 * pos) + 1);
}
template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
return ((2 * pos) + 2);
}
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
T aux = data[i];
data[i] = data[j];
data[j] = aux;
}
template <class T>
void Heap<T>::heapify(unsigned int pos) {
unsigned int le = left(pos);
unsigned int ri = right(pos);
unsigned int min = pos;
if (le <= cntr && data[le] < data[min]) {
min = le;
}
if (ri <= cntr && data[ri] < data[min]) {
min = ri;
}
if (min != pos) {
swap(pos, min);
heapify(min);
}
}
template <class T>
void Heap<T>::push(T val) {
unsigned int pos;
pos = cntr;
cntr++;
while (pos > 0 && val < data[parent(pos)]) {
data[pos] = data[parent(pos)];
pos = parent(pos);
}
data[pos] = val;
}
template <class T>
T Heap<T>::pop() {
T aux = data[0];
data[0] = data[--cntr];
heapify(0);
return aux;
}
template <class T>
void Heap<T>::clear() {
cntr = 0;
}
template <class T>
string Heap<T>::toString() const {
stringstream aux;
aux << "["; for (unsigned int i = 0; i < cntr; i++) {
if (i != 0) {
aux << " ";
} aux << data[i];
} aux << "]";
return aux.str();
}
template <class T>
int Heap<T>::top (){
 return data[0];
}

template <class T>
int Heap<T>::size (){
 return cntr;
}
#endif /* HEAP_H_ */