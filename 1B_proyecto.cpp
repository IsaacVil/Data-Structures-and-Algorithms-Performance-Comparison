//Proyecto 1B Isaac Villaloos Bonilla y Kevin Vega, 2024124285 y 2024800616.
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cctype> 
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h> 
#include <math.h>
#include <sstream>
#include <random>
using namespace std;
typedef struct T_Votante { //Se define la estructura para los votantes en Listas Enlazadas
	char cedula[10];
	char codelec[7];
	char sexo;
	char fecha[9];
	char numjun[6];
	char nombre[31];
	char papellido[27];
	char sapellido[27];
	T_Votante* PtrSiguiente;
}*PtrT_Votante;

typedef struct T_VotanteABB { //Para los abb y los avl
	char cedula[10];
	char codelec[7];
	char sexo;
	char fecha[9];
	char numjun[6];
	char nombre[31];
	char papellido[27];
	char sapellido[27];
	T_VotanteABB* izquierdo;
	T_VotanteABB* derecho;
	int altura;
}*ptrTVotanteabb;

////////////////////////////////////////////////////LISTA ENLAZADA////////////////////////////////////////////////////
//ListaV es una lista enlazada comun, nisiquiera un arbol binario de busqueda
void AgregarListaEnlazada(PtrT_Votante& ListaV, char agregado[118]) {
	PtrT_Votante Aux = new (T_Votante);
	Aux->PtrSiguiente = ListaV;
	ListaV = Aux;

	for (int ce = 0; ce < 9; ce++) {
		ListaV->cedula[ce] = agregado[ce];
	}
	ListaV->cedula[9] = '\0';

	for (int co = 10; co < 16; co++) {
		ListaV->codelec[co - 10] = agregado[co];
	}
	ListaV->codelec[6] = '\0';

	ListaV->sexo = agregado[17];


	for (int fe = 19; fe < 27; fe++) {
		ListaV->fecha[fe - 19] = agregado[fe];
	}
	ListaV->fecha[8] = '\0';

	for (int nu = 28; nu < 33; nu++) {
		ListaV->numjun[nu - 28] = agregado[nu];
	}
	ListaV->numjun[5] = '\0';

	for (int nom = 34; nom < 64; nom++) {
		ListaV->nombre[nom - 34] = agregado[nom];
	}
	ListaV->nombre[30] = '\0';

	for (int pa = 65; pa < 91; pa++) {
		ListaV->papellido[pa - 65] = agregado[pa];
	}
	ListaV->papellido[26] = '\0';

	for (int sa = 92; sa < 118; sa++) {
		ListaV->sapellido[sa - 92] = agregado[sa];
	}
	ListaV->sapellido[26] = '\0';

}

void CargarVotantesListaEnlazada(PtrT_Votante& ListaV) {
	int cont = 1;
	time_t inicio, fin;
	inicio = time(NULL);
	FILE* archivo;
	fopen_s(&archivo, "PADRON_COMPLETO.txt", "r");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
	}
	else {
		char agregado[119];
		while (fgets(agregado, 119, archivo) != NULL) {
			if (cont % 2 != 0) {
				AgregarListaEnlazada(ListaV, agregado);
			}
			cont++;
		}
		fclose(archivo);
	}

	fin = time(NULL);
	cout << "----------------------------Padron Cargado (Lista Enlazada)--------------------------------" << endl;
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padron Cargado (Lista Enlazada)--------------------------------" << endl;
	system("pause");
}

void LiberarVotantesListaEnlazada(PtrT_Votante& ListaV) {
	PtrT_Votante Aux = ListaV;
	time_t inicio, fin;

	inicio = time(NULL);

	while (Aux != NULL) {
		ListaV = ListaV->PtrSiguiente;
		delete(Aux);
		//Globalfree(Aux);
		Aux = ListaV;
	}

	fin = time(NULL);

	cout << "----------------------------Padron liberado (Lista Enlazada)--------------------------------" << endl;
	printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padron liberado (Lista Enlazada)--------------------------------" << endl;
	system("pause");
}


void inicializarvotantesListaEnlazada(PtrT_Votante& ListaV) {
	ListaV = NULL;
}

PtrT_Votante BuscarVotanteListaEnlazada(PtrT_Votante& Lista, char cual[9])
{
	bool encontro = false;
	PtrT_Votante Aux;
	Aux = Lista;

	while ((!encontro == true) && (Aux != NULL))
	{
		if (strncmp(Aux->cedula, cual, 9) == 0)
			encontro = true;
		else
			Aux = Aux->PtrSiguiente;
	}
	return Aux;
}
////////////////////////////////////////////////////ARBOL BINARIO DE BUSQUEDA//////////////////////////////////////////////////////////
ptrTVotanteabb crearvotanteabb(const char cedula[10], const char nombre[31], const char papellido[27], const char sapellido[27], const char numjun[6], char sexo, const char fecha[9], const char codelec[7]) {
	ptrTVotanteabb nuevo = new (T_VotanteABB);

	strcpy_s(nuevo->cedula, cedula);
	strcpy_s(nuevo->nombre, nombre);
	strcpy_s(nuevo->papellido, papellido);
	strcpy_s(nuevo->sapellido, sapellido);
	strcpy_s(nuevo->numjun, numjun);
	nuevo->sexo = sexo;
	strcpy_s(nuevo->fecha, fecha);
	strcpy_s(nuevo->codelec, codelec);

	nuevo->derecho = nullptr;
	nuevo->izquierdo = nullptr;
	nuevo->altura = 1;
	return nuevo;
}

void agregarabb(ptrTVotanteabb& listabb, ptrTVotanteabb& nuevo)
{
	if (listabb != nullptr) {
		if (atoi(listabb->cedula) > atoi(nuevo->cedula) && listabb->izquierdo != nullptr)
		{
			agregarabb(listabb->izquierdo, nuevo);
		}
		else if (atoi(listabb->cedula) > atoi(nuevo->cedula) && listabb->izquierdo == nullptr) {
			listabb->izquierdo = nuevo;
		}
		else if (atoi(listabb->cedula) < atoi(nuevo->cedula) && listabb->derecho != nullptr)
		{
			agregarabb(listabb->derecho, nuevo);
		}
		else if (atoi(listabb->cedula) < atoi(nuevo->cedula) && listabb->derecho == nullptr) {
			listabb->derecho = nuevo;
		}
	}
	else {
		listabb = nuevo;
	}
}


void eliminarabbcompleto(ptrTVotanteabb& ListaV) {
	if (ListaV != nullptr) {
		eliminarabbcompleto(ListaV->izquierdo);
		eliminarabbcompleto(ListaV->derecho);
		delete ListaV;
		ListaV = nullptr;
	}
}

void cargarvotantesabb(PtrT_Votante& ListaV, ptrTVotanteabb& listaabb) {
	PtrT_Votante aux = ListaV;
	time_t inicio, fin;
	inicio = time(NULL);
	while (aux != nullptr) {
		ptrTVotanteabb nuevo = crearvotanteabb(aux->cedula, aux->nombre, aux->papellido, aux->sapellido, aux->numjun, aux->sexo, aux->fecha, aux->codelec);
		agregarabb(listaabb, nuevo);
		aux = aux->PtrSiguiente;
	}
	fin = time(NULL);

	cout << "----------------------------Padron Cargado (ARBOL BINARIO DE BUSQUEDA)--------------------------------" << endl;
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padron Cargado (ARBOL BINARIO DE BUSQUEDA)--------------------------------" << endl;
	system("pause");
}

void cargarvotantesabb2(PtrT_Votante& ListaV, ptrTVotanteabb& listaabb) {
	PtrT_Votante aux = ListaV;
	while (aux != nullptr) {
		ptrTVotanteabb nuevo = crearvotanteabb(aux->cedula, aux->nombre, aux->papellido, aux->sapellido, aux->numjun, aux->sexo, aux->fecha, aux->codelec);
		agregarabb(listaabb, nuevo);
		aux = aux->PtrSiguiente;
	}
}

void eliminarabb(ptrTVotanteabb& arbol) {
	if (arbol != nullptr) //Cuando se meta de manera recursiva para buscar si es nulo no va a hacer nada
	{
		eliminarabb(arbol->izquierdo);
		eliminarabb(arbol->derecho);
		delete arbol;
	}
}

void printearIRDabb(ptrTVotanteabb arbol) {
	if (arbol != nullptr) {
		printearIRDabb(arbol->izquierdo);
		cout << arbol->cedula << ", ";
		cout << arbol->nombre << ", ";
		cout << arbol->papellido << ", ";
		cout << arbol->sapellido << ", ";
		cout << arbol->numjun << ", ";
		cout << arbol->sexo << ", ";
		cout << arbol->codelec << endl;
		printearIRDabb(arbol->derecho);
	}
}

void buscarabb(ptrTVotanteabb& listabb, const char cedula[10]) {
	if (listabb != nullptr) {
		if (atoi(listabb->cedula) > atoi(cedula)) {
			buscarabb(listabb->izquierdo, cedula);
		}
		else if (atoi(listabb->cedula) < atoi(cedula)) {
			buscarabb(listabb->derecho, cedula);
		}
		else if (atoi(listabb->cedula) == atoi(cedula)) {
			cout << "ENCONTRADO: " << endl;
			cout << listabb->cedula << ", ";
			cout << listabb->nombre << ", ";
			cout << listabb->papellido << ", ";
			cout << listabb->sapellido << ", ";
			cout << listabb->numjun << ", ";
			cout << listabb->sexo << ", ";
			cout << listabb->codelec << endl;
		}
	}
}

////////////////////////////////////////////////////////AVL///////////////////////////////////////////////////////////
typedef struct abb {
	int altura;
	char cedula[10];
	char codelec[7];
	char sexo;
	char fecha[9];
	char numjun[6];
	char nombre[31];
	char papellido[27];
	char sapellido[27];
	abb* izquierdo;
	abb* derecho;
}*abbptr;

int maxi(int a, int b)
{
	if (a > b) //Devuelve el que sea mas grande entre el hijo izquierdo o derecho
		return a;
	else
		return b;
}

int altura(abbptr Raiz)
{
	if (Raiz == NULL) //Si la raiz es nulo la altura es 0
		return 0;
	else
		return Raiz->altura; //Devuelve la altura
}

abbptr crearvotanteavl(const char cedula[10], const char nombre[31], const char papellido[27], const char sapellido[27], const char numjun[6], char sexo, const char fecha[9], const char codelec[7]) {
	abbptr nuevo = new (abb);

	strcpy_s(nuevo->cedula, cedula);
	strcpy_s(nuevo->nombre, nombre);
	strcpy_s(nuevo->papellido, papellido);
	strcpy_s(nuevo->sapellido, sapellido);
	strcpy_s(nuevo->numjun, numjun);
	nuevo->sexo = sexo;
	strcpy_s(nuevo->fecha, fecha);
	strcpy_s(nuevo->codelec, codelec);

	nuevo->derecho = nullptr;
	nuevo->izquierdo = nullptr;
	nuevo->altura = 1;
	return nuevo;
}

void RotarDerecha(abbptr& raiz)
{
	abbptr copiaizquierda = raiz->izquierdo; //Copiamos al nodo izquierdo
	abbptr hijodeizq = copiaizquierda->derecho; //Copiamos al nodo derecho del nodo izquierdo (porque aqui va a caer la raiz original)

	// hace rotacion
	copiaizquierda->derecho = raiz; //Por esto sacamos la copia, aca queda la raiz
	raiz->izquierdo = hijodeizq; //En la raiz izquierda (la cual no tiene elementos que perder pues aca estaba la copiaizq, se pone la copia antes sacada)

	// actualiza alturas
	raiz->altura = maxi(altura(raiz->izquierdo), altura(raiz->derecho)) + 1; //La altura de cada elemento es la altura mas grande de entre sus dos hijos + 1
	copiaizquierda->altura = maxi(altura(copiaizquierda->izquierdo), altura(copiaizquierda->derecho)) + 1;

	raiz = copiaizquierda; //actualizamos la raiz para que sea al que le hicimos la rotacion
}

void RotarIzquierda(abbptr& raiz)
{
	abbptr copiaderecha = raiz->derecho;
	abbptr hijodeder = copiaderecha->izquierdo;

	// hace rotacion
	copiaderecha->izquierdo = raiz;
	raiz->derecho = hijodeder;

	//actualiza alturas
	raiz->altura = maxi(altura(raiz->izquierdo), altura(raiz->derecho)) + 1;
	copiaderecha->altura = maxi(altura(copiaderecha->izquierdo), altura(copiaderecha->derecho)) + 1;

	// retorna nueva raiz
	raiz = copiaderecha;
}

int obtenerbalance(abbptr N)
{
	if (N == NULL)
		return 0;
	else
		return altura(N->izquierdo) - altura(N->derecho); //Si se dobla a derecha sera < -1 y si se dobla a la izquierda sera > 1
}

void insertaravl(abbptr& avl, abbptr nuevo)
{
	if (avl == nullptr) //Si no hay nada solo se hace un lista = nuevo (Esto sirve para la recursividad vista en la parte de abajo)
	{
		avl = nuevo;
	}
	else //Si no es vacio hay que tomar en cuenta unos casos
	{
		if (atoi(nuevo->cedula) > atoi(avl->cedula))  //Si codigo va a la derecha
		{
			insertaravl(avl->derecho, nuevo); //Se mete de manera recursiva
			avl->altura = maxi(altura(avl->izquierdo), altura(avl->derecho)) + 1; //Le actualizamos su altura
		}
		else if (atoi(nuevo->cedula) < atoi(avl->cedula)) //Si codigo va a la izquierda
		{
			insertaravl(avl->izquierdo, nuevo);
			avl->altura = maxi(altura(avl->derecho), altura(avl->izquierdo)) + 1; //Le actualizamos su altura
		}
		else //No hay <= porque no se permiten codigos repetidos
		{
			return; //Hacemos un return para que no haga ningun cálculo porque no vamos a añadir nada
		}
		int balance = obtenerbalance(avl); //Vemos si hubo desbalance
		if (balance > 1 || balance < -1) //Cualquiera de estos significa desbalance
		{
			//Caso 1: Rotación a la derecha (desbalanceado a la izquierda)
			if (balance > 1 && atoi(nuevo->cedula) < atoi(avl->izquierdo->cedula)) //Doblado a la izquierda
			{
				RotarDerecha(avl);
			}
			//Caso 2: Rotación a la izquierda (desbalanceado a la derecha)
			else if (balance < -1 && atoi(nuevo->cedula) > atoi(avl->derecho->cedula)) //Doblado a la derecha
			{
				RotarIzquierda(avl);
			}
			//Caso 3: Rotación izquierda-derecha
			else if (balance > 1 && atoi(nuevo->cedula) > atoi(avl->izquierdo->cedula))  //Doblado izquierda y luego derecha (HAY QUE HACER ROTACION DOBLE)   
			{
				RotarIzquierda(avl->izquierdo);
				RotarDerecha(avl);
			}
			//Caso 4: Rotación derecha-izquierda
			else if (balance < -1 && atoi(nuevo->cedula) < atoi(avl->derecho->cedula)) //Doblado derecha y luego izquierda (HAY QUE HACER ROTACION DOBLE)   
			{
				RotarDerecha(avl->derecho);
				RotarIzquierda(avl);
			}
		}
	}
}

void cargarvotantesavl(PtrT_Votante& ListaV, abbptr& listaabb) {
	PtrT_Votante aux = ListaV;
	time_t inicio, fin;
	inicio = time(NULL);
	while (aux != nullptr) {
		abbptr nuevo = crearvotanteavl(aux->cedula, aux->nombre, aux->papellido, aux->sapellido, aux->numjun, aux->sexo, aux->fecha, aux->codelec);
		insertaravl(listaabb, nuevo);
		aux = aux->PtrSiguiente;
	}
	fin = time(NULL);

	cout << "----------------------------Padron Cargado (ARBOL AVL)--------------------------------" << endl;
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padron Cargado (ARBOL AVL)--------------------------------" << endl;
	system("pause");
}

void cargarvotantesavl2(PtrT_Votante& ListaV, abbptr& listaabb) {
	PtrT_Votante aux = ListaV;
	while (aux != nullptr) {
		abbptr nuevo = crearvotanteavl(aux->cedula, aux->nombre, aux->papellido, aux->sapellido, aux->numjun, aux->sexo, aux->fecha, aux->codelec);
		insertaravl(listaabb, nuevo);
		aux = aux->PtrSiguiente;
	}
}

void eliminaravl(abbptr& arbol) {
	if (arbol != nullptr) //Cuando se meta de manera recursiva para buscar si es nulo no va a hacer nada
	{
		eliminaravl(arbol->izquierdo);
		eliminaravl(arbol->derecho);
		delete arbol;
	}
}

void buscaravl(abbptr& listabb, const char cedula[10]) {
	if (listabb != nullptr) {
		if (atoi(listabb->cedula) > atoi(cedula)) {
			buscaravl(listabb->izquierdo, cedula);
		}
		else if (atoi(listabb->cedula) < atoi(cedula)) {
			buscaravl(listabb->derecho, cedula);
		}
		else if (atoi(listabb->cedula) == atoi(cedula)) {
			cout << "ENCONTRADO: " << endl;
			cout << listabb->cedula << ", ";
			cout << listabb->nombre << ", ";
			cout << listabb->papellido << ", ";
			cout << listabb->sapellido << ", ";
			cout << listabb->numjun << ", ";
			cout << listabb->sexo << ", ";
			cout << listabb->codelec << endl;
		}
	}
}

void printearIRDavl(abbptr arbol) {
	if (arbol != nullptr) {
		printearIRDavl(arbol->izquierdo);
		cout << arbol->cedula << ", ";
		cout << arbol->nombre << ", ";
		cout << arbol->papellido << ", ";
		cout << arbol->sapellido << ", ";
		cout << arbol->numjun << ", ";
		cout << arbol->sexo << ", ";
		cout << arbol->codelec << endl;
		printearIRDavl(arbol->derecho);
	}
}

bool esCedulaValida(const char* cedula) {
	if (strlen(cedula) != 9) {
		return false;
	}
	for (int i = 0; i < 9; i++) {
		if (!isdigit(cedula[i])) {
			return false;
		}
	}
	return true;
}

PtrT_Votante crearnodoenlazada(PtrT_Votante aux) {
	PtrT_Votante nuevo = new T_Votante;
	strcpy_s(nuevo->cedula, sizeof(nuevo->cedula), aux->cedula);
	strcpy_s(nuevo->nombre, sizeof(nuevo->nombre), aux->nombre);
	strcpy_s(nuevo->papellido, sizeof(nuevo->papellido), aux->papellido);
	strcpy_s(nuevo->sapellido, sizeof(nuevo->sapellido), aux->sapellido);
	strcpy_s(nuevo->fecha, sizeof(nuevo->fecha), aux->fecha);
	strcpy_s(nuevo->codelec, sizeof(nuevo->codelec), aux->codelec);
	nuevo->sexo = aux->sexo;
	strcpy_s(nuevo->numjun, sizeof(nuevo->numjun), aux->numjun);
	return nuevo;
}

void copiarlistaenlazada(PtrT_Votante& llavemaestra, PtrT_Votante& llavecopia) {
	PtrT_Votante aux = llavemaestra;
	while (aux != nullptr) {
		PtrT_Votante nuevo = crearnodoenlazada(aux);
		nuevo->PtrSiguiente = llavecopia;
		llavecopia = nuevo;
		aux = aux->PtrSiguiente;
	}
}

void listarlistaenlazada(PtrT_Votante llavemaestra) {
	PtrT_Votante aux = llavemaestra;
	while (aux != nullptr) {
		cout << aux->cedula << ", ";
		cout << aux->nombre << ", ";
		cout << aux->papellido << ", ";
		cout << aux->sapellido << ", ";
		cout << aux->numjun << ", ";
		cout << aux->sexo << ", ";
		cout << aux->codelec << endl;
		aux = aux->PtrSiguiente;
	}
}

void buscarlistaenlazada(PtrT_Votante llavemaestra, const char cedula[10]) {
	PtrT_Votante aux = llavemaestra;
	while (aux != nullptr) {
		if (atoi(aux->cedula) == atoi(cedula)) {
			cout << aux->cedula << ", ";
			cout << aux->nombre << ", ";
			cout << aux->papellido << ", ";
			cout << aux->sapellido << ", ";
			cout << aux->numjun << ", ";
			cout << aux->sexo << ", ";
			cout << aux->codelec << endl;
			break;
		}
		aux = aux->PtrSiguiente;
	}
	cout << "NO FUE ENCONTRADO" << endl;
}

void eliminarLista(PtrT_Votante& lista) {
	PtrT_Votante actual = lista;
	while (actual != nullptr) {
		PtrT_Votante siguiente = actual->PtrSiguiente;
		delete actual;
		actual = siguiente;
	}
	lista = nullptr;
}




//--------------------------------------------------------------------------------BTREE-----------------------------------------------------------------------------------------
#define MAX 4
#define MIN 2


typedef struct NodoBtree {
	PtrT_Votante vot[MAX + 1];
	int count;
	NodoBtree* link[MAX + 1];
} *Ptr_Btree;

// Function to create a new B-Tree node
NodoBtree* crearnodo(PtrT_Votante votante, NodoBtree* hijo, Ptr_Btree Root) {
	NodoBtree* NuevoNodo = new NodoBtree;
	NuevoNodo->vot[1] = votante;
	NuevoNodo->count = 1;
	NuevoNodo->link[0] = Root;
	NuevoNodo->link[1] = hijo;
	return NuevoNodo;
}

// Function to insert into B-Tree node
void Colocarnodo(PtrT_Votante votante, int pos, NodoBtree* node, NodoBtree* hijo) {
	int j = node->count;
	while (j > pos) {
		node->vot[j + 1] = node->vot[j];
		node->link[j + 1] = node->link[j];
		j--;
	}
	node->vot[j + 1] = votante;
	node->link[j + 1] = hijo;
	node->count++;
}

// Function to split a B-Tree node
void PartirNodo(PtrT_Votante votante, PtrT_Votante* pval, int pos, NodoBtree* node, NodoBtree* hijo, NodoBtree** NuevoNodo) {
	int median = (pos > MIN) ? MIN + 1 : MIN;
	*NuevoNodo = new NodoBtree;
	int j = median + 1;
	while (j <= MAX) {
		(*NuevoNodo)->vot[j - median] = node->vot[j];
		(*NuevoNodo)->link[j - median] = node->link[j];
		j++;
	}
	node->count = median;
	(*NuevoNodo)->count = MAX - median;
	if (pos <= MIN) {
		Colocarnodo(votante, pos, node, hijo);
	}
	else {
		Colocarnodo(votante, pos - median, *NuevoNodo, hijo);
	}
	*pval = node->vot[node->count];
	(*NuevoNodo)->link[0] = node->link[node->count];
	node->count--;
}

// B-Tree insertion
int SetValorNodo(PtrT_Votante votante, PtrT_Votante* pval, NodoBtree* node, NodoBtree** hijo) {
	int pos;
	if (!node) {
		*pval = votante;
		*hijo = NULL;
		return 1;
	}

	if (atoi(votante->cedula) < atoi(node->vot[1]->cedula)) {
		pos = 0;
	}
	else {
		for (pos = node->count; (atoi(votante->cedula) < atoi(node->vot[pos]->cedula) && pos > 1); pos--);
		if (atoi(votante->cedula) == atoi(node->vot[pos]->cedula)) return 0;
	}

	if (SetValorNodo(votante, pval, node->link[pos], hijo)) {
		if (node->count < MAX) {
			Colocarnodo(*pval, pos, node, *hijo);
		}
		else {
			PartirNodo(*pval, pval, pos, node, *hijo, hijo);
			return 1;
		}
	}
	return 0;
}

void insertarBTREE(PtrT_Votante votante, Ptr_Btree& Root) {
	PtrT_Votante i;
	NodoBtree* hijo;
	int flag = SetValorNodo(votante, &i, Root, &hijo);
	if (flag) Root = crearnodo(i, hijo, Root);
}

// Display B-Tree
void desplegar(NodoBtree* minodo) {
	if (minodo) {
		for (int i = 0; i < minodo->count; i++) {
			desplegar(minodo->link[i]);
			cout << "Cedula: " << minodo->vot[i + 1]->cedula << ", ";
			cout << "Nombre: " << minodo->vot[i + 1]->nombre << ", ";
			cout << "Apellido: " << minodo->vot[i + 1]->papellido << ", ";
			cout << "Sexo: " << minodo->vot[i + 1]->sexo << ", ";
			cout << "Codigo: " << minodo->vot[i + 1]->codelec << endl;
		}
		desplegar(minodo->link[minodo->count]);
	}
}

double ListarBtree(Ptr_Btree BTREE) {
	time_t inicio, fin;
	inicio = time(NULL);
	desplegar(BTREE);
	fin = time(NULL);
	return difftime(fin, inicio);
}

// Search in B-Tree
void Buscar_Btree(int cedula, NodoBtree* minodo) {
	if (!minodo) {
		cout << "No encontrado\n";
		return;
	}

	int pos;
	if (cedula < atoi(minodo->vot[1]->cedula)) {
		pos = 0;
	}
	else {
		for (pos = minodo->count; (cedula < atoi(minodo->vot[pos]->cedula) && pos > 1); pos--);
		if (cedula == atoi(minodo->vot[pos]->cedula)) {
			cout << "ENCONTRADO: " << endl;
			cout << minodo->vot[pos]->cedula << ", ";
			cout << minodo->vot[pos]->nombre << ", ";
			cout << minodo->vot[pos]->papellido << ", ";
			cout << minodo->vot[pos]->sapellido << ", ";
			cout << minodo->vot[pos]->numjun << ", ";
			cout << minodo->vot[pos]->sexo << ", ";
			cout << minodo->vot[pos]->codelec << endl;
			return;
		}
	}
	Buscar_Btree(cedula, minodo->link[pos]);
}


// Función para buscar un votante en el B-Tree y mostrar sus datos en el formato requerido
void Buscar_Btree_formato(const char cedula[10], NodoBtree* minodo) {
	if (!minodo) {
		cout << "No se encontró el votante con cédula: " << cedula << endl;
		return;
	}

	int pos = 0;

	// Buscar la posición correcta en el nodo actual
	if (atoi(cedula) < atoi(minodo->vot[1]->cedula)) {
		pos = 0;
	}
	else {
		for (pos = minodo->count; (pos > 1 && atoi(cedula) < atoi(minodo->vot[pos]->cedula)); pos--);
		if (atoi(cedula) == atoi(minodo->vot[pos]->cedula)) {
			// Imprime los datos del votante en el formato requerido si la cédula coincide
			cout << "ENCONTRADO: ";
			cout << minodo->vot[pos]->cedula << ", ";
			cout << minodo->vot[pos]->nombre << ", ";
			cout << minodo->vot[pos]->papellido << ", ";
			cout << minodo->vot[pos]->sapellido << ", ";
			cout << minodo->vot[pos]->numjun << ", ";
			cout << minodo->vot[pos]->sexo << ", ";
			cout << minodo->vot[pos]->codelec << endl;
			return;
		}
	}

	// Si no se encuentra en el nodo actual, busca en el subárbol correspondiente
	if (minodo->link[pos] != nullptr) {
		Buscar_Btree_formato(cedula, minodo->link[pos]);
	}
	else {
		// Caso en el que la cédula no existe en el árbol
		cout << "No se encontró el votante con cédula: " << cedula << endl;
	}
}





// Delete B-Tree
void Borrar_BTREE(Ptr_Btree& Raiz) {
	if (Raiz != NULL) {
		for (int i = 0; i < Raiz->count + 1; i++) {
			Borrar_BTREE(Raiz->link[i]);
		}
		delete(Raiz);
		Raiz = NULL;
	}
}


void cargarvotantesBtree(PtrT_Votante& ListaV, Ptr_Btree& Btree) {
	PtrT_Votante aux = ListaV;
	time_t inicio, fin;
	inicio = time(NULL);
	while (aux != nullptr) {
		insertarBTREE(aux, Btree);
		aux = aux->PtrSiguiente;
	}
	fin = time(NULL);
	cout << "----------------------------Padrón Cargado (ÁRBOL BTREE)--------------------------------" << endl;
	printf("\nEl cargado del padrón ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padrón Cargado (ÁRBOL BTREE)--------------------------------" << endl;
	system("pause");
}

double Cargar2Btree(PtrT_Votante& lista, Ptr_Btree& Btree) {
	PtrT_Votante Aux = lista;
	time_t inicio = time(NULL);
	while (Aux != NULL) {
		insertarBTREE(Aux, Btree);
		Aux = Aux->PtrSiguiente;
	}
	time_t fin = time(NULL);
	return difftime(fin, inicio);
}

double BuscarBtree(NodoBtree* Btree, int cedula) {
	time_t inicio = time(NULL);
	Buscar_Btree(cedula, Btree);
	time_t fin = time(NULL);
	return difftime(fin, inicio);
}

double BorrarBtree(Ptr_Btree& Btree) {
	time_t inicio = time(NULL);
	Borrar_BTREE(Btree);
	time_t fin = time(NULL);
	return difftime(fin, inicio);
}





//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

float tiempocargaavl = 0;
float tiempocargaabb = 0;
float tiempocargabtree = 0;
float tiempocargalistaenlazada = 0;
float tiempolistaravl = 0;
float tiempolistarabb = 0;
float tiempolistarbtree = 0;
float tiempolistarlistaenlazada = 0;
float tiempobuscaravl = 0;
float tiempobuscarabb = 0;
float tiempobuscarbtree = 0;
float tiempobuscarlistaenlazada = 0;
float tiempodestruiravl = 0;
float tiempodestruirabb = 0;
float tiempodestruirbtree = 0;
float tiempodestruirlistaenlazada = 0;

int main()
{
	int opcion1 = 0;
	int opcion2 = 0;
	bool menu1 = true;
	bool menu2 = true;
	cout << "ESTAMOS CARGANDO LA LLAVE MAESTRA... " << endl;
	PtrT_Votante LlaveMaestra = nullptr;
	PtrT_Votante ListaEnlazada = nullptr;
	ptrTVotanteabb ListaABB = nullptr;
	abbptr ListaAVL = nullptr;
	Ptr_Btree BTREE = nullptr;
	CargarVotantesListaEnlazada(LlaveMaestra);

	while (menu1) {
		system("cls");
		menu2 = true;
		cout << "---------------------------------------------------" << endl;
		cout << "1) Lista Enlazada" << endl;
		cout << "2) Arbol Binario de Busqueda" << endl;
		cout << "3) Arbol AVL" << endl;
		cout << "4) Arbol BTREE" << endl;
		cout << "5) Medicion COMPLETA" << endl;
		cout << "6) Salir" << endl;
		cout << "ELIGE: ";
		cin >> opcion1;
		if (opcion1 == 1) {
			while (menu2) {
				system("cls");
				cout << "---------------------------------------------------" << endl;
				cout << "1) Cargar Lista Enlazada (copia de LlaveMaestra)" << endl;
				cout << "2) Listar Lista Enlazada (copia de LlaveMaestra)" << endl;
				cout << "3) Buscar Lista Enlazada (copia de LlaveMaestra)" << endl;
				cout << "4) Destruir Lista Enlazada (copia de LlaveMaestra)" << endl;
				cout << "5) Salir" << endl;
				cout << "ELIGE: ";
				cin >> opcion2;
				if (opcion2 == 1) {
					time_t inicio, fin;
					inicio = time(NULL);
					copiarlistaenlazada(LlaveMaestra, ListaEnlazada);
					fin = time(NULL);
					cout << "----------------------------Padron Copiado (LISTA ENLAZADA)--------------------------------" << endl;
					printf("\nEl listado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Padron Copiado (LISTA ENLAZADA)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 2) {
					time_t inicio, fin;
					inicio = time(NULL);
					listarlistaenlazada(ListaEnlazada);
					fin = time(NULL);
					cout << "----------------------------Padron Listado (LISTA ENLAZADA)--------------------------------" << endl;
					printf("\nEl listado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Padron Listado (LISTA ENLAZADA)--------------------------------" << endl;
					system("pause");

				}
				else if (opcion2 == 3) {
					char cedula[10];
					cout << "Elige una cedula de 9 dígitos para que busquemos: ";
					cin >> cedula;

					while (!esCedulaValida(cedula)) {
						cout << "Error: La cédula debe ser un número de 9 dígitos. Intenta nuevamente: ";
						cin >> cedula;
					}

					time_t inicio, fin;
					inicio = time(NULL);
					buscarlistaenlazada(ListaEnlazada, cedula);
					fin = time(NULL);
					cout << "----------------------------Cedula Encontrada (LISTA ENLAZADA)--------------------------------" << endl;
					printf("\nLa busqueda en el padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Cedula Encontrada (LISTA ENLAZADA)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 4) {
					time_t inicio, fin;
					inicio = time(NULL);
					eliminarLista(ListaEnlazada);
					fin = time(NULL);
					cout << "----------------------------Padron Destruido (LISTA ENLAZADA)--------------------------------" << endl;
					printf("\nLa busqueda en el padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Padron Destruido (LISTA ENLAZADA)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 5) {
					menu2 = false;
					opcion1 = 0;
				}
			}
		}
		else if (opcion1 == 2) {
			while (menu2) {
				system("cls");
				cout << "---------------------------------------------------" << endl;
				cout << "1) Cargar Arbol Binario de Busqueda" << endl;
				cout << "2) Listar Arbol Binario de Busqueda" << endl;
				cout << "3) Buscar Arbol Binario de Busqueda" << endl;
				cout << "4) Destruir Arbol Binario de Busqueda" << endl;
				cout << "5) Salir" << endl;
				cout << "ELIGE: ";
				cin >> opcion2;
				if (opcion2 == 1) {
					if (ListaABB != nullptr) {
						eliminarabb(ListaABB);
						ListaABB = nullptr;
					}
					cargarvotantesabb(LlaveMaestra, ListaABB);
				}
				else if (opcion2 == 2) {
					time_t inicio, fin;
					inicio = time(NULL);
					printearIRDabb(ListaABB);
					fin = time(NULL);
					cout << "----------------------------Padron Listado (ARBOL BINARIO DE BUSQUEDA)--------------------------------" << endl;
					printf("\nEl listado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Padron Listado (ARBOL BINARIO DE BUSQUEDA)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 3) {
					char cedula[10];
					cout << "Elige una cedula de 9 dígitos para que busquemos: ";
					cin >> cedula;

					while (!esCedulaValida(cedula)) {
						cout << "Error: La cédula debe ser un número de 9 dígitos. Intenta nuevamente: ";
						cin >> cedula;
					}

					time_t inicio, fin;
					inicio = time(NULL);
					buscarabb(ListaABB, cedula);
					fin = time(NULL);
					cout << "----------------------------Cedula Encontrada (ARBOL BINARIO DE BUSQUEDA)--------------------------------" << endl;
					printf("\nLa busqueda en el padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Cedula Encontrada (ARBOL BINARIO DE BUSQUEDA)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 4) {
					time_t inicio, fin;
					inicio = time(NULL);
					eliminarabb(ListaABB);
					ListaABB = nullptr;
					fin = time(NULL);
					cout << "----------------------------Padron Destruido (ARBOL BINARIO DE BUSQUEDA)--------------------------------" << endl;
					printf("\nLa destruccion del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Padron Destruido (ARBOL BINARIO DE BUSQUEDA)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 5) {
					menu2 = false;
					opcion1 = 0;
				}
			}
		}
		else if (opcion1 == 3) {
			while (menu2) {
				system("cls");
				cout << "---------------------------------------------------" << endl;
				cout << "1) Cargar Arbol AVL" << endl;
				cout << "2) Listar Arbol AVL" << endl;
				cout << "3) Buscar Arbol AVL" << endl;
				cout << "4) Destruir Arbol AVL" << endl;
				cout << "5) Salir" << endl;
				cout << "ELIGE: ";
				cin >> opcion2;
				if (opcion2 == 1) {
					if (ListaAVL != nullptr) {
						eliminaravl(ListaAVL);
						ListaAVL = nullptr;
					}
					cargarvotantesavl(LlaveMaestra, ListaAVL);
				}
				else if (opcion2 == 2) {
					time_t inicio, fin;
					inicio = time(NULL);
					printearIRDavl(ListaAVL);
					fin = time(NULL);
					cout << "----------------------------Padron Listado (ARBOL AVL)--------------------------------" << endl;
					printf("\nEl listado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Padron Listado (ARBOL AVL)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 3) {
					char cedula[10];
					cout << "Elige una cedula de 9 digitos para que busquemos: ";
					cin >> cedula;

					while (!esCedulaValida(cedula)) {
						cout << "La cedula debe ser un numero de 9 dígitos. Intenta nuevamente: ";
						cin >> cedula;
					}

					time_t inicio, fin;
					inicio = time(NULL);
					buscaravl(ListaAVL, cedula);
					fin = time(NULL);
					cout << "----------------------------Cedula Encontrada (ARBOL AVL)--------------------------------" << endl;
					printf("\nLa busqueda en el padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Cedula Encontrada (ARBOL AVL)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 4) {
					time_t inicio, fin;
					inicio = time(NULL);
					eliminaravl(ListaAVL);
					ListaAVL = nullptr;
					fin = time(NULL);
					cout << "----------------------------Padron Destruido (ARBOL AVL)--------------------------------" << endl;
					printf("\nLa destruccion del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
					cout << "----------------------------Padron Destruido (ARBOL AVL)--------------------------------" << endl;
					system("pause");
				}
				else if (opcion2 == 5) {
					menu2 = false;
					opcion1 = 0;
				}
			}
		}
		else if (opcion1 == 4) {
			while (menu2) {
				system("cls");
				cout << "---------------------------------------------------" << endl;
				cout << "1) Cargar Arbol BTREE" << endl;
				cout << "2) Listar Arbol BTREE" << endl;
				cout << "3) Buscar Arbol BTREE" << endl;
				cout << "4) Destruir Arbol BTREE" << endl;
				cout << "5) Salir" << endl;
				cout << "ELIGE: ";
				cin >> opcion2;
				if (opcion2 == 1) {

					if (BTREE != nullptr) {
						BorrarBtree(BTREE);
						BTREE = nullptr;
					}
					cargarvotantesBtree(LlaveMaestra,BTREE);
					
				}
				else if (opcion2 == 2) {
					desplegar(BTREE);

				}
				else if (opcion2 == 3) {
					int cedula;
					cout << "Ingrese cedula (9 digitos): ";
					cin >> cedula;
					double tiempo = BuscarBtree(BTREE, cedula);
					cout << "[BTREE] Busqueda realizada en: " << tiempo << " segundos.\n";
					system("pause");

				}
				else if (opcion2 == 4) {
					double tiempo = BorrarBtree(BTREE);
					cout << "[BTREE] Borrado completado en: " << tiempo << " segundos.\n";
					system("pause");

				}
				else if (opcion2 == 5) {
					menu2 = false;
					opcion1 = 0;
				}
			}
		}
		else if (opcion1 == 5) {
			while (menu2) {
				system("cls");
				cout << "---------------------------------------------------" << endl;
				cout << "1) Cargar TODOS para medir el tiempo" << endl;
				cout << "2) Listar TODOS para medir el tiempo" << endl;
				cout << "3) Buscar en TODOS los arboles para medir el tiempo" << endl;
				cout << "4) Destruir TODOS los arboles" << endl;
				cout << "5) Cargar, Listar, Buscar Y Destruir TODOS (CICLO COMPLETO)" << endl;
				cout << "ELIGE: ";
				cin >> opcion2;
				if (opcion2 == 1) {
					cout << "CARGANDO TODOS (ESTO PUEDE TARDAR UNOS MINUTOS) . . .";
					time_t inicio, fin;

					if (ListaEnlazada != nullptr) {
						eliminarLista(ListaEnlazada);
					}
					if (ListaABB != nullptr) {
						eliminarabb(ListaABB);
					}
					if (ListaAVL != nullptr) {
						eliminaravl(ListaAVL);
					}

					inicio = time(NULL);
					copiarlistaenlazada(LlaveMaestra, ListaEnlazada);
					fin = time(NULL);
					tiempocargalistaenlazada = difftime(fin, inicio);

					inicio = time(NULL);
					cargarvotantesabb2(LlaveMaestra, ListaABB);
					fin = time(NULL);
					tiempocargaabb = difftime(fin, inicio);

					inicio = time(NULL);
					cargarvotantesavl2(LlaveMaestra, ListaAVL);
					fin = time(NULL);
					tiempocargaavl = difftime(fin, inicio);

					inicio = time(NULL);
					cargarvotantesBtree(LlaveMaestra,BTREE);
					fin = time(NULL);
					tiempocargabtree = difftime(fin, inicio);

					system("cls");
					cout << "TIEMPOS ------------------------------------------------------------------" << endl;
					cout << "LISTA ENLAZADA: " << tiempocargalistaenlazada << " segundos" << endl;
					cout << "ARBOL BINARIO DE BUSQUEDA: " << tiempocargaabb << " segundos" << endl;
					cout << "ARBOL AVL: " << tiempocargaavl << " segundos" << endl;
					cout << "ARBOL BTREE: " << tiempocargabtree << " segundos" << endl;
					system("pause");
				}
				else if (opcion2 == 2) {
					cout << "LISTANDO TODOS (ESTO PUEDE TARDAR UNOS MINUTOS) . . .";
					time_t inicio, fin;

					inicio = time(NULL);
					listarlistaenlazada(ListaEnlazada);
					fin = time(NULL);
					tiempolistarlistaenlazada = difftime(fin, inicio);

					inicio = time(NULL);
					printearIRDabb(ListaABB);
					fin = time(NULL);
					tiempolistarabb = difftime(fin, inicio);

					inicio = time(NULL);
					printearIRDavl(ListaAVL);
					fin = time(NULL);
					tiempolistaravl = difftime(fin, inicio);

					inicio = time(NULL);
					desplegar(BTREE);
					fin = time(NULL);
					tiempolistarbtree = difftime(fin, inicio);

					system("cls");
					cout << "TIEMPOS ------------------------------------------------------------------" << endl;
					cout << "LISTA ENLAZADA: " << tiempolistarlistaenlazada << " segundos" << endl;
					cout << "ARBOL BINARIO DE BUSQUEDA: " << tiempolistarabb << " segundos" << endl;
					cout << "ARBOL AVL: " << tiempolistaravl << " segundos" << endl;
					cout << "ARBOL BTREE: " << tiempolistarbtree << " segundos" << endl;
					system("pause");
				}
				else if (opcion2 == 3) {
					char cedula[10];
					cout << "Elige una cedula de 9 digitos para que busquemos: ";
					cin >> cedula;

					while (!esCedulaValida(cedula)) {
						cout << "La cedula debe ser un numero de 9 dígitos. Intenta nuevamente: ";
						cin >> cedula;
					}

					cout << "BUSCANDO EN TODOS (ESTO PUEDE TARDAR UNOS MINUTOS) . . .";
					time_t inicio, fin;

					inicio = time(NULL);
					buscarlistaenlazada(ListaEnlazada, cedula);
					fin = time(NULL);
					tiempobuscarlistaenlazada = difftime(fin, inicio);

					inicio = time(NULL);
					buscarabb(ListaABB, cedula);
					fin = time(NULL);
					tiempobuscarabb = difftime(fin, inicio);

					inicio = time(NULL);
					buscaravl(ListaAVL, cedula);
					fin = time(NULL);
					tiempobuscaravl = difftime(fin, inicio);

					inicio = time(NULL);
					BuscarBtree(BTREE, atoi(cedula));
					fin = time(NULL);
					tiempobuscarbtree = difftime(fin, inicio);

					system("cls");
					cout << "TIEMPOS ------------------------------------------------------------------" << endl;
					cout << "LISTA ENLAZADA: " << tiempobuscarlistaenlazada << " segundos" << endl;
					cout << "ARBOL BINARIO DE BUSQUEDA: " << tiempobuscarabb << " segundos" << endl;
					cout << "ARBOL AVL: " << tiempobuscaravl << " segundos" << endl;
					cout << "ARBOL BTREE: " << tiempobuscarbtree << " segundos" << endl;
					system("pause");
				}
				else if (opcion2 == 4) {
					cout << "DESTRUYENDO A TODOS (ESTO PUEDE TARDAR UNOS MINUTOS) . . .";
					time_t inicio, fin;

					inicio = time(NULL);
					eliminarLista(ListaEnlazada);
					fin = time(NULL);
					tiempodestruirlistaenlazada = difftime(fin, inicio);

					inicio = time(NULL);
					eliminarabb(ListaABB);
					fin = time(NULL);
					tiempodestruirabb = difftime(fin, inicio);

					inicio = time(NULL);
					eliminaravl(ListaAVL);
					fin = time(NULL);
					tiempodestruiravl = difftime(fin, inicio);

					inicio = time(NULL);
					Borrar_BTREE(BTREE);
					fin = time(NULL);
					tiempodestruirbtree = difftime(fin, inicio);

					system("cls");
					cout << "TIEMPOS ------------------------------------------------------------------" << endl;
					cout << "LISTA ENLAZADA: " << tiempodestruirlistaenlazada << " segundos" << endl;
					cout << "ARBOL BINARIO DE BUSQUEDA: " << tiempodestruirabb << " segundos" << endl;
					cout << "ARBOL AVL: " << tiempodestruiravl << " segundos" << endl;
					cout << "ARBOL BTREE: " << tiempodestruirbtree << " segundos" << endl;
					system("pause");
				}
				else if (opcion2 == 5) {


					char cedula[10];
					cout << "Elige una cedula de 9 dígitos para buscar en el ciclo completo: ";
					cin >> cedula;

					// Validación de cédula
					while (!esCedulaValida(cedula)) {
						cout << "La cédula debe ser un número de 9 dígitos. Intenta nuevamente: ";
						cin >> cedula;
					}

					cout << "INICIANDO CICLO COMPLETO (CARGAR, LISTAR, BUSCAR, DESTRUIR)..." << endl;
					time_t inicio, fin;

					// Cargar en Lista Enlazada
					inicio = time(NULL);
					copiarlistaenlazada(LlaveMaestra, ListaEnlazada);
					fin = time(NULL);
					tiempocargalistaenlazada = difftime(fin, inicio);

					// Cargar en Árbol Binario de Búsqueda
					inicio = time(NULL);
					cargarvotantesabb2(LlaveMaestra, ListaABB);
					fin = time(NULL);
					tiempocargaabb = difftime(fin, inicio);

					// Cargar en Árbol AVL
					inicio = time(NULL);
					cargarvotantesavl2(LlaveMaestra, ListaAVL);
					fin = time(NULL);
					tiempocargaavl = difftime(fin, inicio);

					// Cargar en B-Tree
					inicio = time(NULL);
					cargarvotantesBtree(LlaveMaestra, BTREE);
					fin = time(NULL);
					tiempocargabtree = difftime(fin, inicio);

					// Listar Lista Enlazada
					inicio = time(NULL);
					listarlistaenlazada(ListaEnlazada);
					fin = time(NULL);
					tiempolistarlistaenlazada = difftime(fin, inicio);

					// Listar Árbol Binario de Búsqueda
					inicio = time(NULL);
					printearIRDabb(ListaABB);
					fin = time(NULL);
					tiempolistarabb = difftime(fin, inicio);

					// Listar Árbol AVL
					inicio = time(NULL);
					printearIRDavl(ListaAVL);
					fin = time(NULL);
					tiempolistaravl = difftime(fin, inicio);

					// Listar B-Tree
					inicio = time(NULL);
					desplegar(BTREE);
					fin = time(NULL);
					tiempolistarbtree = difftime(fin, inicio);

					// Buscar en Lista Enlazada
					inicio = time(NULL);
					buscarlistaenlazada(ListaEnlazada, cedula);
					fin = time(NULL);
					tiempobuscarlistaenlazada = difftime(fin, inicio);

					// Buscar en Árbol Binario de Búsqueda
					inicio = time(NULL);
					buscarabb(ListaABB, cedula);
					fin = time(NULL);
					tiempobuscarabb = difftime(fin, inicio);

					// Buscar en Árbol AVL
					inicio = time(NULL);
					buscaravl(ListaAVL, cedula);
					fin = time(NULL);
					tiempobuscaravl = difftime(fin, inicio);

					// Buscar en B-Tree
					inicio = time(NULL);
					BuscarBtree(BTREE, atoi(cedula));
					fin = time(NULL);
					tiempobuscarbtree = difftime(fin, inicio);

					// Destruir Lista Enlazada
					inicio = time(NULL);
					eliminarLista(ListaEnlazada);
					fin = time(NULL);
					tiempodestruirlistaenlazada = difftime(fin, inicio);

					// Destruir Árbol Binario de Búsqueda
					inicio = time(NULL);
					eliminarabb(ListaABB);
					fin = time(NULL);
					tiempodestruirabb = difftime(fin, inicio);

					// Destruir Árbol AVL
					inicio = time(NULL);
					eliminaravl(ListaAVL);
					fin = time(NULL);
					tiempodestruiravl = difftime(fin, inicio);

					// Destruir B-Tree
					inicio = time(NULL);
					Borrar_BTREE(BTREE);
					fin = time(NULL);
					tiempodestruirbtree = difftime(fin, inicio);

					// Mostrar resultados
					system("cls");
					cout << "TIEMPOS COMPLETOS (CARGA, LISTA, BUSCA, DESTRUYE) ----------------------------------------" << endl;
					cout << "CARGA:" << endl;
					cout << "  LISTA ENLAZADA: " << tiempocargalistaenlazada << " segundos" << endl;
					cout << "  ARBOL BINARIO DE BUSQUEDA: " << tiempocargaabb << " segundos" << endl;
					cout << "  ARBOL AVL: " << tiempocargaavl << " segundos" << endl;
					cout << "  ARBOL BTREE: " << tiempocargabtree << " segundos" << endl;
					cout << "LISTA:" << endl;
					cout << "  LISTA ENLAZADA: " << tiempolistarlistaenlazada << " segundos" << endl;
					cout << "  ARBOL BINARIO DE BUSQUEDA: " << tiempolistarabb << " segundos" << endl;
					cout << "  ARBOL AVL: " << tiempolistaravl << " segundos" << endl;
					cout << "  ARBOL BTREE: " << tiempolistarbtree << " segundos" << endl;
					cout << "BUSQUEDA:" << endl;
					cout << "  LISTA ENLAZADA: " << tiempobuscarlistaenlazada << " segundos" << endl;
					cout << "  ARBOL BINARIO DE BUSQUEDA: " << tiempobuscarabb << " segundos" << endl;
					cout << "  ARBOL AVL: " << tiempobuscaravl << " segundos" << endl;
					cout << "  ARBOL BTREE: " << tiempobuscarbtree << " segundos" << endl;
					cout << "DESTRUCCION:" << endl;
					cout << "  LISTA ENLAZADA: " << tiempodestruirlistaenlazada << " segundos" << endl;
					cout << "  ARBOL BINARIO DE BUSQUEDA: " << tiempodestruirabb << " segundos" << endl;
					cout << "  ARBOL AVL: " << tiempodestruiravl << " segundos" << endl;
					cout << "  ARBOL BTREE: " << tiempodestruirbtree << " segundos" << endl;
					cout << "------------------------------------------------------------------------------------------" << endl;
					system("pause");

				}
				else if (opcion2 == 6) {
					menu2 = false;
					opcion1 = 0;
				}
			}
		}
		else if (opcion1 == 6) {
			menu1 = false;
			system("cls");
			cout << "PROGRAMA FINALIZADO" << endl;
		}
	}
}