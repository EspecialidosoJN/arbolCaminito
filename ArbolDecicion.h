#pragma once
#include <iostream>
#include <sstream>
#include <string.h>
#include <cctype>
#include <cstring>
#include <stdlib.h>
#include "NodoArbol.h"
class ArbolDecicion
{public:
	ArbolDecicion();
	NodoArbol Raiz;
	char Mapa[80][15];
	bool imprimirNodosCreados = false;
	void formarHojas(NodoArbol* Padre);
	void busquedaPorAmplitud();
	void busquedaPorProfundidad();
	bool validarDestino(NodoArbol* nodo, NodoArbol* destino);
	bool MapaUnico(NodoArbol* nodo, list<NodoArbol*> probadas);
	void imprimirMapa();
	list<NodoArbol*> Visitados; //J Para evitar que la memoria valga chorizo

};

