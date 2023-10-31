#include "ArbolDecicion.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <cctype>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include "NodoArbol.h"
#include "windows.h"
using namespace std;

void gotoxy(int x, int y)
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}


void ArbolDecicion::busquedaPorAmplitud()
{
	HANDLE HC = GetStdHandle(STD_OUTPUT_HANDLE);
	NodoArbol Destino;
	char memoria;
	bool entradaValida = false, Modorapido = false;
	int TY, TX;
	do
	{
		cout << "Desea activar el modo rapido 1 si 0 no: ";
		cin >> Modorapido;
	} while (!cin.good());
	system("cls");
	imprimirMapa();
	do
	{
		entradaValida = true;
		cout << "El sugerido para predeterminado es 79. Ingresa un valor X destino entero del 0 al 79: ";
		cin >> TX;
		if (TX<0 || TX>79)
		{
			entradaValida = false;
		}
	} while (!cin.good() || !entradaValida);

	do
	{
		entradaValida = true;
		cout << "El sugerido para predeterminado es 0. Ingresa un valor Y destino entero del 0 al 14: ";
		cin >> TY;
		if (TY < 0 || TY>14)
		{
			entradaValida = false;
		}
	} while (!cin.good() || !entradaValida);
	Destino.Y = TY;
	Destino.X = TX;


	do
	{
		entradaValida = true;
		cout << "El sugerido para predeterminado es 0. Ingresa un valor X Origen entero del 0 al 79: ";
		cin >> TX;
		if (TX < 0 || TX>79)
		{
			entradaValida = false;
		}
	} while (!cin.good() || !entradaValida);
	do
	{
		entradaValida = true;
		cout << "El sugerido para predeterminado es 14 o 0. Ingresa un valor Y Origen entero del 0 al 14: ";
		cin >> TY;
		if (TY < 0 || TY>14)
		{
			entradaValida = false;
		}
	} while (!cin.good() || !entradaValida);
	this->Raiz.X = TX;
	this->Raiz.Y = TY;


	list<NodoArbol*>* Actual;
	list<NodoArbol*>* Proxima;
	list<NodoArbol*>* Temporal;
	NodoArbol* vista = nullptr;
	bool encontrado = false;
	bool sinrespuesta = false;
	Actual = new list<NodoArbol*>();
	Proxima = new list<NodoArbol*>();
	Actual->push_back(&this->Raiz);
	
	
	
	int tamanoActual = 0;

	while (!encontrado)
	{
		tamanoActual = Actual->size();
		for (int i = 0; i < tamanoActual; i++)  //J recorre los nodos del nivel actual
		{
			vista = Actual->front();
			if (validarDestino(vista, &Destino))
			{
				//cout << "\nEncontro\n";
				//system("pause");
				encontrado = true;
				break;
			}
			else
			{

				//if(MapaUnico(vista,Visitados))
				//{
				formarHojas(vista);
				//Proxima->insert(Proxima->end(), vista->Hijos.begin(), vista->Hijos.end());            //J ****************Esta linea no la entiendo bien, epica candidata en caso de que no sirva esta cosa****************


				//cout << "\nEsta vista genero " << vista->Hijos.size() << "\n";
				//vista->imprimir();
				//system("pause");
				for (int k = 0; k < vista->Hijos.size(); k++)
				{
					//if (MapaUnico(vista->Hijos.front(), Visitados)) //Si el hijo en turno no esta contemplado ya en Proxima, habia un error aqui que me hizo perder 1 hora 10 minutos :c más que duplico lo que tarde en hacer todo este metodo
					//{
					Proxima->push_front(vista->Hijos.front());
					this->Mapa[vista->Hijos.front()->X][vista->Hijos.front()->Y] = '.';
					vista->girarHijos();
					//}
				}
				if (!Modorapido)
				{
					system("cls");
					memoria = this->Mapa[vista->X][vista->Y];
					this->Mapa[vista->X][vista->Y] = 'V';
					imprimirMapa();
					cout << Proxima->size();
					//system("pause");
					this->Mapa[vista->X][vista->Y] = memoria;
				}


				//}
				Visitados.push_back(vista);//J Antes estaba hasta arriba, pero siempre se encontraba a si mismo en el primer nodo...
				


				Actual->pop_front();
				//prueba de que se expande la lista
				/*
				int tamanoTemporal = 0;
				tamanoTemporal = Proxima->size();
				for (int borrame = 0; borrame < tamanoTemporal; borrame++)
				{
					Proxima->front()->imprimir();
					Proxima->pop_front();
				}
				*/
			}
		}

		if (Proxima->size()==0 && !encontrado)
		{
			system("cls");
			imprimirMapa();
			cout << "\nNo encontro por proxima size 0\n";
			system("pause");
			system("cls");
			encontrado = true;
			sinrespuesta = true;
		}

		Temporal = Actual;
		Actual = Proxima;
		Proxima = Temporal;
		//prueba de que se expande la lista
				/*
		int tamanoTemporal = 0;
		tamanoTemporal = Actual->size();
		for (int borrame = 0; borrame < tamanoTemporal; borrame++)
		{
			Actual->front()->imprimir();
			Actual->pop_front();
		}
		*/
		//imprimirMapa();
		cout << "\n Cantidad de nodos visitados: "<<Visitados.size()<<" La proxima mide: " << Proxima->size() << " (<-deberia ser 0 a menos que encuentre) La actual que tomo a la que era proxima mide: " << Actual->size() << endl;
		//for(int k = 0; k< Proxima->size(); k++)
		//{
		//	Proxima->front()->imprimir();
		//	Proxima->push_back(Proxima->front());
		//	Proxima->pop_front();
		//}
		if (!Modorapido)
		{
			system("pause");
			system("cls");
		}
	}
	//cout << "\n Resuelto|Fin\n"<<endl;

	if (!sinrespuesta)
	{
		system("cls");
		this->imprimirMapa();
		SetConsoleTextAttribute(HC, 48);
		do
		{
			gotoxy(vista->X, vista->Y);
			if (vista->Padre != nullptr)
				cout << "O";
			else
				cout << "A";


			vista = vista->Padre;
		} while (vista != nullptr);
	}
	else
	{
		cout << "\n sin respuesta \n";
		system("pause");
	}
	gotoxy(0, 16);
	SetConsoleTextAttribute(HC, 15);
	//cout << "Inicio del puzzle" << endl;
	cout << "\n Cantidad de nodos visitados: " << Visitados.size() << endl;
	system("pause");





}

bool ArbolDecicion::MapaUnico(NodoArbol* nodo, list<NodoArbol*> visitados)
{
	int tamano = visitados.size();
	if (tamano == 0)
		return true;
	NodoArbol* ActualDeVisitados;
	for (int E =0; E<tamano;E++)
	{
		ActualDeVisitados = visitados.front();
		
		if (!(nodo->X == ActualDeVisitados->X && nodo->Y == ActualDeVisitados->Y))
		{
			visitados.pop_front();
		}
		else
		{
			//cout << "p\n";
			return false; //J Si se encuentra uno igual, retorna 0 para indicar que ese nodo ya esta el la lista
		}
	}
	return true;//J Confirma que se trata de un Mapa unico
}

bool ArbolDecicion::validarDestino(NodoArbol* nodo, NodoArbol* destino)
{
	if (nodo->X == destino->X && nodo->Y == destino->Y)
		return 1;
	else
		return 0;
}

void ArbolDecicion::imprimirMapa()
{
	for (int i = 0; i < 15; i++)
	{
		for (int ii = 0; ii < 80; ii++)
		{
			cout << this->Mapa[ii][i];
		}
		cout << "\n";
	}
}




ArbolDecicion::ArbolDecicion()                              //J de momento no esta implementado el generador aleatorio, aqui se establece el estado inicial
{
	srand(time(NULL));
	int a = 0;
	char Bloque;
	char manual;
	

	for (int i = 0; i < 15; i++)
	{
		for (int ii = 0; ii < 80; ii++)
		{
			this->Mapa[ii][i] = ' ';
		}
	}


	cout << "Se utiliza una matriz de caracteres como tablero. Los '-' (signo de menos) representan terreno transitable, los '.' colocados durante ejecucion representan nodos evaluados. Se preguntaran las coordenadas destino despues, es posible no encontrar el destino.\nPara dibujar caracter por caracter 80*15 ingrese a, de lo contrario se usara el mapa por defecto: ";
	cin >> manual;
	if (manual == 'a')
	{
		for (int Y = 0; Y<15; Y++)
		{
			for (int X = 0; X<80; X++)
			{
				do
				{
					cout << "\n\nEl mapa se muestra cada 80 caracteres, recomendado hacer la primer linea en programa y despues block de notas crtl c crtl v, es un 80x15\nIngrese uno o varios caracteres simples, '-' indica terreno transitable: ";
					gotoxy(80, 19);
					cout << "|";
					gotoxy(0,19);
					cin >> Bloque;
				} while (!cin.good());
				this->Mapa[X][Y] = Bloque;
			}
			system("cls");
			imprimirMapa();
		}


		
		
	}
	else
	{
		string mapaDefecto = "---------------------------------------------------------NNNNNNNNN--------------NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN---NNNNNNNNN--------------NNNNNNNNNNNNNNNNNNNNNNN--------------------------------NNNNNNNNNNN--------------NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN----NNNNNNNNNN----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------NNNNNNNN------NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN----NNNNNNNN--NN----------------------------------------------------NNNNNNNN--------------------------------------------------------------------------NNNN---------------------------------------------------------------------------NNNNNNNNN---------------NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN-----------------------N-----N-----N-----N-----N-----N-----N------N----NNNNNNNNNNNNNN---------------N--N--N--N--N--N--N--N--N--N--N--N--N--N--N-----N----NNNNNNNNNNNN---------------N--N--N--N--N--N--N--N--N--N--N--N--N--N--N-----N----NNNNNNNNNNNN---------------N-----N-----N-----N-----N-----N-----N-----N-----N------------------------";
		for (int Y = 0; Y < 15; Y++)
		{
			for (int X = 0; X < 80; X++)
			{
				this->Mapa[X][Y] = mapaDefecto[X + Y*80];
			}
		}
	}
	system("cls");
}
void ArbolDecicion::formarHojas(NodoArbol* Padre)
{
	//if (this->Mapa[][] == '-')

	if (Padre->X - 1 >= 0 && Padre->Y - 1 >= 0)//izquierda arriba
	{
		if (this->Mapa[Padre->X - 1][Padre->Y - 1] == '-')
			Padre->generarHijo(Padre->X - 1, Padre->Y - 1);
	}

	if (Padre->X + 1 < 80 && Padre->Y - 1 >= 0)//derecha arriba
	{
		if (this->Mapa[Padre->X + 1][Padre->Y - 1] == '-')
			Padre->generarHijo(Padre->X + 1, Padre->Y - 1);
	}

	if (Padre->X + 1 < 80 && Padre->Y + 1 < 15)//derecha abajo
	{
		if (this->Mapa[Padre->X + 1][Padre->Y + 1] == '-')
			Padre->generarHijo(Padre->X + 1, Padre->Y + 1);
	}

	if (Padre->X - 1 >= 0 && Padre->Y + 1 < 15)//izquierda abajo
	{
		if (this->Mapa[Padre->X - 1][Padre->Y + 1] == '-')
			Padre->generarHijo(Padre->X - 1, Padre->Y + 1);
	}



	//Primero se generan las diagonales para que se evaluen primero y se priorize la toma de decición diagonal sobre individual sus 2 componentes
	//if (this->Mapa[][] == '-')
	if (Padre->Y - 1 >= 0)//arriba
	{
		if (this->Mapa[Padre->X][Padre->Y - 1]=='-')
		Padre->generarHijo(Padre->X, Padre->Y-1);
	}

	if (Padre->X + 1 < 80)//derecha
	{
		if (this->Mapa[Padre->X + 1][Padre->Y]=='-')
		Padre->generarHijo(Padre->X + 1, Padre->Y);
	}

	if (Padre->Y + 1 < 15)//abajo
	{
		if (this->Mapa[Padre->X][Padre->Y + 1] == '-')
		Padre->generarHijo(Padre->X, Padre->Y + 1);
	}

	if (Padre->X - 1 >= 0)//izquierda
	{
		if (this->Mapa[Padre->X - 1][Padre->Y] == '-')
		Padre->generarHijo(Padre->X - 1, Padre->Y);
	}
	

}

void ArbolDecicion::busquedaPorProfundidad()
{
	NodoArbol* Vista, *ProximaVista = nullptr    ;
	NodoArbol Destino;
	char memoria;
	bool entradaValida = false, Modorapido = false, SinRespuesta = false;
	int TY, TX;
	HANDLE HC = GetStdHandle(STD_OUTPUT_HANDLE);

	do
	{
		cout << "Desea activar el modo rapido 1 si 0 no: ";
		cin >> Modorapido;
	} while (!cin.good());
	system("cls");
	imprimirMapa();
	do
	{
		entradaValida = true;
		cout << "El sugerido para predeterminado es 79. Ingresa un valor X destino entero del 0 al 79: ";
		cin >> TX;
		if (TX < 0 || TX>79)
		{
			entradaValida = false;
		}
	} while (!cin.good() || !entradaValida);

	do
	{
		entradaValida = true;
		cout << "El sugerido para predeterminado es 0. Ingresa un valor Y destino entero del 0 al 14: ";
		cin >> TY;
		if (TY < 0 || TY>14)
		{
			entradaValida = false;
		}
	} while (!cin.good() || !entradaValida);
	Destino.Y = TY;
	Destino.X = TX;


	do
	{
		entradaValida = true;
		cout << "El sugerido para predeterminado es 0. Ingresa un valor X Origen entero del 0 al 79: ";
		cin >> TX;
		if (TX < 0 || TX>79)
		{
			entradaValida = false;
		}
	} while (!cin.good() || !entradaValida);
	do
	{
		entradaValida = true;
		cout << "El sugerido para predeterminado es 14 o 0. Ingresa un valor Y Origen entero del 0 al 14: ";
		cin >> TY;
		if (TY < 0 || TY>14)
		{
			entradaValida = false;
		}
	} while (!cin.good() || !entradaValida);
	this->Raiz.X = TX;
	this->Raiz.Y = TY;




	Vista = &Raiz;
	int contador = 0;
	while (!validarDestino(Vista,&Destino) && !SinRespuesta)
	{
		//cout << contador << "\n";
		//contador++;
		//system("pause");
		if (Vista->Hijos.size() > 0)
		{
			ProximaVista = Vista->Hijos.front();
			Vista->Hijos.pop_front();
		}
		else
		{
			formarHojas(Vista);
			for (int k = 0; k < Vista->Hijos.size(); k++)
			{
				this->Mapa[Vista->Hijos.front()->X][Vista->Hijos.front()->Y] = '.';
				Vista->girarHijos();
			}
			if (Vista->Hijos.size() > 0)
			{
				ProximaVista = Vista->Hijos.front();
				Vista->Hijos.pop_front();
			}
			else
			{
				if (Vista->Padre == nullptr)
				{
					this->Mapa[Vista->X][Vista->Y] = 'F';
					imprimirMapa();
					cout << "No hay respuesta\n";
					SinRespuesta = true;
					system("pause");
				}
				else
				{
					ProximaVista = Vista->Padre;
					delete Vista;
				}
			}
		}
		//memoria = this->Mapa[Vista->X][Vista->Y];
		//this->Mapa[Vista->X][Vista->Y] = '.';
		Vista = ProximaVista;

	}
	if (!SinRespuesta)
	{
		system("cls");
		this->imprimirMapa();
		SetConsoleTextAttribute(HC, 48);
		do
		{
			gotoxy(Vista->X, Vista->Y);
			if (Vista->Padre != nullptr)
				cout << "O";
			else
				cout << "A";


			Vista = Vista->Padre;
		} while (Vista != nullptr);
	}
	else
	{
		system("cls");
		cout << "\n sin respuesta \n";
		system("pause");
	}
	gotoxy(0, 16);
	SetConsoleTextAttribute(HC, 15);
}



