/*
    sorts.h
    Fecha: 6/09/23
    Autor: Juan Pablo Chávez Leal
    Matricula: a01705408

*/
#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
using namespace std;

template<typename T>
class Sorts {
public:
    void swap(vector<T>&, int, int);

    void ordenaSeleccion(vector<T>& );

    void ordenaBurbuja(vector<T>& );

    void ordenaMerge(vector<T>&);
    void copyArray(vector<T>&, vector<T>&, int , int);
    void mergeSplit(vector<T>&, vector<T>&, int , int);
    void mergeArray(vector<T>&, vector<T>&, int, int, int);
    
    int busqSecuencial(vector<T>, int);
    int busqBinaria(vector<T> , int );

    Sorts() {};

};

template <class T>
void Sorts<T>::swap(vector<T> &arr, int i, int j){
    T aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &arr){

    for(int i = 0; i <= arr.size() - 1; i++){
        int min = i;
        for(int j = i; j <= arr.size() - 1; j++){
            if(arr[min] > arr[j]){
                min = j;
            }
        }
        swap(arr,i,min);
    }

}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<T>& arr){
    for(int i = arr.size() - 1; i > 0 ; i--){
        for(int j = 0; j < i; j++ ){
            if(arr[j] > arr[j+1]){
                swap(arr, j,j+1);
            }
        }
    }
}

template<class T>
void Sorts<T>::ordenaMerge(vector<T> &arr){
    vector<T> tmp(arr.size());

    mergeSplit(arr,tmp,0,arr.size()-1);
}

template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high){
    for(int i = low; i <= high; i++ ){
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high){
    int mid;

    if((high - low) < 1){
        return;
    }
    mid = (high + low) / 2;
    mergeSplit(A,B,low,mid);
    mergeSplit(A,B,mid+1,high);
    mergeArray(A,B,low,mid,high);
    copyArray(A,B,low,high);
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high){
    int i = low, k = low, j = mid + 1;

    while(i <= mid && j <= high){
        if(A[i] < A[j]){
            B[k] = A[i];
            i++;
        }else{
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if(i > mid){
        for(; j <= high ; j++){
            B[k++] = A[j];
        }
    }else{
        for(; i <= mid ; i++){
            B[k++] = A[i];
        }
    }

}

template <class T>
int Sorts<T>::busqSecuencial(vector<T> arr,int val){

    for(int i = 0; i <= arr.size()-1; i++){
        if(arr[i] == val){
            return i;
        }
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(vector<T> arr, int val){
    int low = 0; 
    int high = arr.size() - 1;

    while(low <= high){
        int mid = (high + low) / 2;
        if(arr[mid] == val){
            return mid;
        }
        if(arr[mid] < val){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    return -1;
}
#endif