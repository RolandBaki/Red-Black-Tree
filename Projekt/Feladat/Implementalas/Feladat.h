#ifndef FELADAT_HEADER
#define FELADAT_HEADER

#include "RBTrees.h"
#include <string>
#include <vector>

//Car string, mely tartalmazza a g�pj�rm? rendsz�m�t,sz�n�t,m�rk�j�t,meg a b�ntet�s id?pontjat
struct car {
	string Rendszam;
	string Szin;
	string Marka;
	string Tipus;
	int nap, honap, ev, hatramaradt;
	long long kulcs;
};

//A rendsy�mb�l kulcsot k�sy�t a csom�pontoknak
long long ConvertToKey(string Rendszam);

//Aut� t�pus�t d�nti el
void TypeSelector(string& tipus);

//G�pj�rm?vet ad az adatb�zishoz
void AddCar(tree<car>* rbt);

//Megkeresi az adott g�pj�rm?vet az adatb�zisban
void IsInCar(tree<car>* rbt);

//K�pet rajzol
void Sport(node<car>* nd);
//K�pet rajzol
void Motor(node<car>* nd);
//K�pet rajzol
void Kamion(node<car>* nd);
//K�pet rajzol
void Antik(node<car>* nd);
//K�pet rajzol
void Sima(node<car>* nd);
//K�pet rajzol
void Terepjaro(node<car>* nd);

//Ki�rja a g�pj�rm? adatait
void Print(node<car>* nd,int,tree<car>*);

//Tartalmayya a reedsz�m lek�r? �s auto ki�r� m?veletet
void PrintCar(tree<car>* rbt);

//G�pj�rm?vet t�r�l
void DeleteCar(tree<car>* rbt);

//Kiirja az adatb�zis minden elem�t
void PrintBase(node<car>* nd,tree<car>*);

//Kiir�sban seg�t
void PrintBase2(node<car>* nd,tree<car>*);

//Csokkenti az "Immunis" id?t, sz�ks�g eset�n t�r�l
void Set2(node<car>* nd, tree<car>* rbt);
//Csokkenti az "Immunis" id?t, sz�ks�g eset�n t�r�l
void Set(node<car>* nd, tree<car>* rbt, vector<long long>&);

//L�trehozza az adatb�yist,�s a standard bemenetr?l helyes 1 g�pj�rm?vet bele
void CreateDataBase(tree<car>* rbt);

//Fileb�l olvas be inform�ci�kat
void CreateDataBaseFromFile(string filename, tree<car>* rbt);
//Fileb�l olvas be inform�ci�kat
void CreateDataBaseFromFile(tree<car>* rbt);

//Kuryord helyezi
void MoveCursor(int x, int y);

//Kurzort helyezi
void Here2(int option);
//A kuryort helyezi v�laszt�sokkal
void Here(int option);


//F?oldalt tartalmazza
void Main(tree<car>* rbt);

//V�laszlehet�s�geket sorol fel
void Main2(tree<car>* rbt);

//L�trehozza az bin�ris f�t �s megnyitja a f?oldalt
void Start();

#endif
