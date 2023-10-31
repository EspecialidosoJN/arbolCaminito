#include "NodoArbol.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <cctype>
#include <cstring>
#include <stdlib.h>
using namespace std;

void NodoArbol::generarHijo(int X,int Y)
{
	NodoArbol* Nuevo = new NodoArbol(); //J Se crea el nodo
	Nuevo->X = X;
	Nuevo->Y = Y;
	Nuevo->Padre = this;				//J Se le asigna com padre al nodo donde se invoca el proceso
	
	
	this->Hijos.push_back(Nuevo);       //J Se registra en la lista de hijos
	//J Aqui no le hago delete porque si no se perderia todo lo que se acaba de guardar en la lista
}
void NodoArbol::girarHijos()
{
	this->Hijos.push_back(this->Hijos.front()); //J Coloca el frente de hijos al final
	this->Hijos.pop_front();                    //J Previene duplicar el dato que se colocó atras
}
void NodoArbol::imprimir()
{
	cout << "\nX: "<<this->X<<" Y: "<<this->Y<<"\n";
}
