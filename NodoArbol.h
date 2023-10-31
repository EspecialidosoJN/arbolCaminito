#pragma once
#include <list>
using namespace std;
class NodoArbol
{
public:
	int X,Y;          //J En que consistiria tomar este nodo
	NodoArbol* Padre;           //J Nodo padre en caso de no ser el inicial
	list <NodoArbol*> Hijos;    //J Nodos hijos, pueden ser 2,3,o 4 en el contexto, pero el codigo en teoria da para más si se adapta
	void girarHijos();          //J Hace que el front de la lista de hijos se combierta en el back, la lista de c++ no soporta indice
	void generarHijo(int X, int Y);//J Los numeros del Mapa
	void imprimir();            //J Imprime el Mapa y la cantidad de hijos del Nodo, Lo use para pruebas de funcionalidad de nodo
};

