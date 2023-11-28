/*
Funciones.h 
Autor: Juan Pablo Chávez Leal
Matricula: A01705408
*/

#ifndef FUNCIONES_H
#define FUNCIONES_H

class Funciones{
public:

int sumaIterativa(int val);
int sumaRecursiva(int val);
int sumaDirecta(int val);
};


int Funciones::sumaIterativa(int val){
    int acum=0;
    for (int i=0;i<=val;i++){
        acum+=i;
    }
    return acum;
}

int Funciones::sumaRecursiva(int val){
    if (val<=0){return val;}
    else {
        return val+sumaRecursiva(val-1);
    }
}

int Funciones::sumaDirecta(int val){
    return (val*(val+1))/2;
}

#endif