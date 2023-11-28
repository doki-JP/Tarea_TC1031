/*
Nombre: Juan Pablo Chávez Leal
Matrícula: A01705408

*/

#ifndef DLIST_H_
#define DLIST_H_
#include <string>
#include <sstream>

template <class T> class DList;

/* Clase DLink */
template <class T>
class DLink { // Clase nodo
private:
    T value;
    DLink<T> *previous;
    DLink<T> *next;

    DLink(T val) : value(val), previous(0), next(0) {}
    DLink(T val, DLink<T> *prev, DLink<T> *nxt) : value(val), previous(prev), next(nxt) {}
    DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

    friend class DList<T>;
};

/* Clase DList */
template <class T>
class DList {
public:
    DList();
    DList(const DList<T> &);
    ~DList();

    std::string toStringForward() const;
    std::string toStringBackward() const;
    void insertion(T);
    void addFirst(T);
    bool empty() const;
    int search(T);
    void update(T, T);
    void deleteAt(T);
    void clear();

private:
    DLink<T> *head;
    DLink<T> *tail;
    int size;

};

/* Métodos DList */
template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
    clear();
}

template <class T>
bool DList<T>::empty() const {
    return (head == 0 && tail == 0);
}

template <class T>
void DList<T>::update(T index, T val) {
    DLink<T> *p;
    int auxc = 0;
    p = head;
    while (auxc < index) {
        p = p->next;
        auxc++;
    }
    p->value = val;
}

template <class T>
int DList<T>::search(T val) {
    DLink<T> *p;
    int auxc = 0;
    p = head;
    while (p != 0) {
        if (p->value == val) {
            return auxc;
        }
        auxc++;
        p = p->next;
    }
    return -1;
}

template <class T>
void DList<T>::deleteAt(T index) {
    DLink<T> *p, *q;
    int auxc = 0;

    if (index == 0) {
        p = head;
        head = p->next;
        if (head != 0) {
            head->previous = 0;
        } else {
            tail = 0;
        }
        delete p;
    } else {
        p = head;
        while (auxc < index) {
            q = p;
            p = p->next;
            auxc++;
        }
        q->next = p->next;
        if (p->next != 0) {
            p->next->previous = q;
        } else {
            tail = q;
        }
        delete p;
    }
    size--;
}



template <class T>
void DList<T>::addFirst(T val) {
    DLink<T> *newDLink;
    newDLink = new DLink<T>(val);
    if (empty()) {
        newDLink->next = head;
        head = newDLink;
        tail = newDLink;
        size++;
    } else {
        newDLink->next = head;
        head->previous = newDLink;
        head = newDLink;
        size++;
    }
}

template <class T>
void DList<T>::clear() {
    DLink<T> *p, *q;
    p = head;
    while (p != 0) {
        q = p->next;
        delete p;
        p = q;
    }
    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
DList<T>::DList(const DList<T> &source) {
    DLink<T> *p, *q;
    if (source.empty()) {
        size = 0;
        head = 0;
        tail = 0;
    } else {
        p = source.head;
        head = new DLink<T>(p->value);
        q = head;
        p = p->next;
        while (p != 0) {
            q->next = new DLink<T>(p->value, q, 0);
            p = p->next;
            q = q->next;
        }
        size = source.size;
    }
}

template <class T>
void DList<T>::insertion(T val) {
    DLink<T> *newDLink, *p;
    newDLink = new DLink<T>(val);
    if (empty()) {
        addFirst(val);
    } else {
        tail->next = newDLink;
        newDLink->previous = tail;
        tail = newDLink;
    }
    size++;
}

template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *p;
    p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T> *p;
    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}
#endif