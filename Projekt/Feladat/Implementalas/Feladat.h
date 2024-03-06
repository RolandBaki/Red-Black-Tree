#ifndef FELADAT_HEADER
#define FELADAT_HEADER

#include "RBTrees.h"
#include <string>
#include <vector>

//Car string, mely tartalmazza a gépjárm? rendszámát,színét,márkáját,meg a büntetés id?pontjat
struct car {
	string Rendszam;
	string Szin;
	string Marka;
	string Tipus;
	int nap, honap, ev, hatramaradt;
	long long kulcs;
};

//A rendsyámból kulcsot késyít a csomópontoknak
long long ConvertToKey(string Rendszam);

//Autó típusát dönti el
void TypeSelector(string& tipus);

//Gépjárm?vet ad az adatbázishoz
void AddCar(tree<car>* rbt);

//Megkeresi az adott gépjárm?vet az adatbázisban
void IsInCar(tree<car>* rbt);

//Képet rajzol
void Sport(node<car>* nd);
//Képet rajzol
void Motor(node<car>* nd);
//Képet rajzol
void Kamion(node<car>* nd);
//Képet rajzol
void Antik(node<car>* nd);
//Képet rajzol
void Sima(node<car>* nd);
//Képet rajzol
void Terepjaro(node<car>* nd);

//Kiírja a gépjárm? adatait
void Print(node<car>* nd,int,tree<car>*);

//Tartalmayya a reedszám lekér? és auto kiíró m?veletet
void PrintCar(tree<car>* rbt);

//Gépjárm?vet töröl
void DeleteCar(tree<car>* rbt);

//Kiirja az adatbázis minden elemét
void PrintBase(node<car>* nd,tree<car>*);

//Kiirásban segít
void PrintBase2(node<car>* nd,tree<car>*);

//Csokkenti az "Immunis" id?t, szükség esetén töröl
void Set2(node<car>* nd, tree<car>* rbt);
//Csokkenti az "Immunis" id?t, szükség esetén töröl
void Set(node<car>* nd, tree<car>* rbt, vector<long long>&);

//Létrehozza az adatbáyist,és a standard bemenetr?l helyes 1 gépjárm?vet bele
void CreateDataBase(tree<car>* rbt);

//Fileból olvas be információkat
void CreateDataBaseFromFile(string filename, tree<car>* rbt);
//Fileból olvas be információkat
void CreateDataBaseFromFile(tree<car>* rbt);

//Kuryord helyezi
void MoveCursor(int x, int y);

//Kurzort helyezi
void Here2(int option);
//A kuryort helyezi választásokkal
void Here(int option);


//F?oldalt tartalmazza
void Main(tree<car>* rbt);

//Válaszlehetöségeket sorol fel
void Main2(tree<car>* rbt);

//Létrehozza az bináris fát és megnyitja a f?oldalt
void Start();

#endif
