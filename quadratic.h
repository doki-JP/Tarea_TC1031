#ifndef HASH_H_
#define HASH_H_

/*
Alumno: Juan Pablo Chávez Leal

Tarea: HASH | Quadratic

Matrícula: A01705408
*/

#include <string>
#include <sstream>
template<class Key, class Value>
class Quadratic{

private:
    unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;
    
    Key *keys;
	Key initialValue;
	Value *values;

    long indexOf(const Key) const;
public:
    Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	bool put(Key, Value) ;
	std::string toString() const;
	Value get(const Key);
	bool full() const;

};

template<class Key, class Value>
Quadratic<Key,Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key)){
	size = sze;
	keys = new Key[size];
	if (keys == 0) {
		return;
	}
	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	values = new Value[size];
	if (values == 0) {
		return;
	}
	for (int i = 0; i  < sze; i++){
        values[i] = 0;
    }
	func = f;
	count = 0;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v)  {
	unsigned int index, inicio, count = 1;
	long pos;
	if (full()) {
		return false;
	}
	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return true;
	}
	inicio = index = func(k) % size;
	do {
		if (keys[index] == initialValue) {
			keys[index] = k;
			values[index] = v;
			count++;
			return true;
		}
        index = (inicio + count * count) % size;
        count++;
	} while (inicio != index);
	return false;
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;
	start = i = func(k) % size;
	do {
		if (keys[i] == k) {
			return i;
		}
		i = (i + 1) % size;
	} while (start != i);
	return -1;
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		return values[pos];
	}
	return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;

	for (unsigned int i = 0; i < size; i++) {
		if(keys[i] != initialValue)
			aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
	}
	return aux.str();
}

#endif