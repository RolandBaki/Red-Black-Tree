#include <iostream>
#include "RBTrees.h"


using namespace std;

#define RED true
#define BLACK false

//Csomópont létrehozása, melynek kulcsa van, de infó mezeje üres
template <typename T>
node<T>* CreateNode(long long _key)
{
	node<T>* nd = new node<T>;
	nd->color = RED;
	nd->key =_key;
	nd->left = CreateNil<T>(nd);
	nd->right = CreateNil<T>(nd);
	nd->nil = false;
	return nd;
}

//Csomópont létrehozása, melynek kulcsa van, és infó mezeje is információt tartalmaz.(típusa felhasználó függő) 
template <typename T>
node<T>* CreateNode(long long _key,T info)
{
	node<T>* nd = new node<T>;
	nd->color = RED;
	nd->key = _key;
	nd->left = CreateNil<T>(nd);
	nd->right = CreateNil<T>(nd);
	nd->nil = false;
	nd->info = info;
	return nd;
}
//Egy null csomopontot hoz létre
template <typename T>
node<T>* CreateNil(node<T>* parent)
{
	node<T>* nd = new node<T>;
	nd->color = BLACK;
	nd->key = 0;
	nd->parent = parent;
	nd->left = nullptr;
	nd->right = nullptr;
	nd->nil = true;
	return nd;
}

//Csomópont felszabadítása
template <typename T>
void FreeNode(node<T>* nd)
{
	delete nd;
}

//Csomópont kiírása
template <typename T>
void PrintNode(node<T>*nd)
{
	if (nd != nullptr)
	{
		cout << endl;
		if (nd->nil)
		{
			cout << "egy level" << endl;
		}
		cout << "Csomopont erteke: " << GetKey(nd) << endl;
		cout << "A csomopont szine:";
		if (GetColor(nd))
		{
			cout << "BLACK" << endl;
		}
		else
		{
			cout << "RED" << endl;
		}

	}
}

//Visszatéríti a csomópont színét
template <typename T>
bool GetColor(node<T>* nd)
{
	return nd->color;
}

//Visszatéríti a csomópont kulcsát
template <typename T>
long long GetKey(node<T>* nd)
{
	return nd->key;
}

//Fa létrehozása
template <typename T>
tree<T>* CreateRBT()
{	
	tree<T>* rb = new tree<T>;
	rb->root = nullptr;
	rb->size = 0;
	return rb;
}

//Rekurzívan törli a csomópontokat
template <typename T>
void FreeRBTNode(node<T>* nd)
{
	FreeNode<T>(nd->right);
	FreeNode<T>(nd->left);
	delete nd;
}

//a fa gyökerére hívjuk meg a rekurzív törlést
template <typename T>
void FreeRBT(tree<T>* rbt)
{
	if (rbt == nullptr)
	{
		return;
	}
	if (rbt->root != nullptr)
	{
		FreeRBTNode<T>(rbt->root);
	}
	delete rbt;
}

//Forgat balra
template <typename T>
void RotateLeft(tree<T>* rbt, node<T>* nd)
{
	if (nd->right->nil)
	{
		return;
	}
	node<T>* y = nd->right;
	
	nd->right = y->left;
	if (!y->left->nil)
	{
		y->left->parent = nd;
	}
		
	y->parent = nd->parent;

	if (nd->parent == nullptr) {
		rbt->root = y;
	}
	else if (nd == nd->parent->left) {
		nd->parent->left = y;
	}
	else {
		nd->parent->right = y;
	}
		y->left = nd;
		nd->parent = y;
}

//Forgat jobbra
template <typename T>
void RotateRight(tree<T>* rbt, node<T>* nd)
{
	if (nd->left->nil)
	{
		return;
	}

	node<T>* y = nd->left;

	nd->left = y->right;

	if (!y->right->nil)
	{
		y->right->parent = nd;
	}

	y->parent = nd->parent;
	if (nd->parent == nullptr) {
		rbt->root = y;
	}
	else if (nd == nd->parent->left) {
		nd->parent->left = y;
	}
	else {
		nd->parent->right = y;
	}

	y->right = nd;
	nd->parent = y;
}

//Csomópont létehozása és beszúrása, melynek nincs infó mezeje, de kötelező a kulcs
template <typename T>
void InsertNode(tree<T>* rbt, long long key)
{
		node<T>* nd = CreateNode<T>(key);
		rbt->size++;
		InsertNodeResolved<T>(rbt, nd);

}


//Csomópont létrehozása és beszúrása, melynek van infó mezeje is
template <typename T>
void InsertNode(tree<T>* rbt, long long key,T a)
{
	node<T>* nd = CreateNode<T>(key,a);
	rbt->size++;
	InsertNodeResolved<T>(rbt, nd);

}

//Már meglévő somópont beszúrása
template <typename T>
void InsertNode(tree<T>* rbt, node<T>* nd)
{
	if (nd == nullptr)
	{
		return;
	}

	if (rbt->root == nullptr)
	{
		rbt->root = nd;
		rbt->root->parent = nullptr;
		return;
	}

	node<T>* p = rbt->root;
	node<T>* before =nullptr;

	while (!p->nil)
	{
		before = p;
		if (nd->key < p->key)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	if (before!=nullptr)
	{
		if (nd->key < before->key)
		{
			before->left = nd;
			nd->parent = before;
		}
		else
		{
			before->right = nd;
			nd->parent = before;
		}
	}
	else
	{
		rbt->root = nd;
		nd->parent = nullptr;
	}
}

//Beszúrja a csomópontot és egyensúlyozza a fát
template <typename T>
void InsertNodeResolved(tree<T>* rbt, node<T>* nd)
{
	if (nd == nullptr)
	{
		return;
	}
	InsertNode<T>(rbt, nd);
	nd->color = RED;

	if (nd->parent == nullptr)
	{
		rbt->root->color = BLACK;
		return;
	}

	while (nd != rbt->root && nd->parent->color == RED)
	{
		if (nd->parent == nd->parent->parent->left)
		{
			node<T>* y = nd->parent->parent->right;

			bool color;
			if (y->nil)
			{
				color = BLACK;
			}
			else
			{
				color = y->color;
			}

			if (color == RED)
			{
				nd->parent->color = BLACK;
				y->color = BLACK;
				nd->parent->parent->color = RED;
				nd = nd->parent->parent;
			}
			else
			{
				if (nd == nd->parent->right)
				{
					nd = nd->parent;
					RotateLeft(rbt, nd);
				}
				nd->parent->color = BLACK;
				nd->parent->parent->color = RED;
				RotateRight<T>(rbt, nd->parent->parent);
			}
		}
		else
		{
			node<T>* y = nd->parent->parent->left;

			bool color;
			if (y->nil)
			{
				color = BLACK;
			}
			else
			{
				color = y->color;
			}

			if (color == RED)
			{
				nd->parent->color = BLACK;
				y->color = BLACK;
				nd->parent->parent->color = RED;
				nd = nd->parent->parent;
			}
			else
			{
				if (nd == nd->parent->left)
				{
					nd = nd->parent;
					RotateRight<T>(rbt, nd);
				}
				nd->parent->color = BLACK;
				nd->parent->parent->color = RED;
				RotateLeft<T>(rbt, nd->parent->parent);
			}
		}
	}
	rbt->root->color = BLACK;
}

//Visszatéríti egy részfa legnagyobb kulcsú elemét
template <typename T>
node<T>* GetMax(tree<T>* rbt,node<T>* nd)
{
	node<T>* max = nd;
	while (!max->right->nil) {
		max = max->right;
	}
	return max;
}

//Visszatéríti egy részfa legkisebb kulcsú elemét
template <typename T>
node<T>* GetMin(tree<T>* rbt,node<T>* nd)
{
	node<T>* min = nd;
	while (!min->left->nil) {
		min = min->left;
	}
	return min;
}

//Visszatéríti a fa legkisebb kulcsú elemét
template <typename T>
node<T>* GetMin(tree<T>* rbt)
{
	node<T>* min = rbt->root;
	while (!min->left->nil) {
		min = min->left;
	}
	//cout << min->key;
	return min;
}

//Visszatéríti a fa legnagyobb kulcsú elemét
template <typename T>
node<T>* GetMax(tree<T>* rbt)
{
	node<T>* max = rbt->root;
	while (!max->right->nil) {
		max = max->right;
	}
	return max;
}

//Kiválasztható egy csomópont és a részfáját kiirja
template <typename T>
void WoutTree(tree<T>* rbt, node<T>* nd)
{
	if (!nd->nil)
	{
		PrintNode<T>(nd);
		WoutTree<T>(rbt, nd->left);
		WoutTree<T>(rbt, nd->right);
	}
}

//Bejárja a fát és meghívja minden csomópontra a kiíráast
template <typename T>
void PrintTree(tree<T>* rbt)
{
	if (rbt->root != nullptr)
	{
		WoutTree<T>(rbt, rbt->root);
	}
}

//Adott kulcsú csomópontot keres egy részfában
template <typename T>
node<T>* Find(tree<T>* rbt, long long key)
{
	if (rbt->root == nullptr)
	{
		return nullptr;
	}

	return Find<T>(rbt, rbt->root, key);
}

//Adott kulcsú csomópontot keres a teljes fában
template <typename T>
node<T>* Find(tree<T>* rbt, node<T>* nd, long long key)
{
	if (nd->nil)
	{
		return nd;
	}

	if (nd->key == key)

	{
		return nd;
	}
	else
	{
		if (nd->key > key)
		{
			return Find(rbt, nd->left, key);
		}
		else
		{
			return Find(rbt, nd->right, key);
		}
	}
}

//Igazat/Hamisat térít vissza, attól függően, hogy eleme vagy nem egy adott kulcsú csomó a fának
template <typename T>
bool IsIn(tree<T>*rbt, long long key)
{
	node<T>* nd = rbt->root;
	while (nd != nullptr && nd->key != key)
	{
		if (key > nd->key)
			nd = nd->right;
		else
			nd = nd->left;
	}
	if (nd != nullptr)
		if (nd->key == key)
			return true;
	return false;
}

//Vissztéríti egy csomópont tstvérét, azaz, azt az elemet, kivel közős az őse
template <typename T>
node<T>* Brother(tree<T>* rbt, node<T>* nd)
{
	if (nd->parent == nullptr)
	{
		return nullptr;
	}

	if (nd->parent->left == nd)
	{
		return nd->parent->right;
	}
	else
	{
		return nd->parent->left;
	}
}

//Felcserél két csomópontot
template <typename T>
void SwapNode(tree<T>* rbt, node<T>* nd, node<T>* Son)
{
	Son->parent = nd->parent;
	if (nd->parent == nullptr)
	{
		rbt->root = Son;
	}
	else
	{
		if (nd->parent->left == nd)
		{
			nd->parent->left = Son;
		}
		else
		{
			nd->parent->right = Son;
		}
	}
}

//Töröl egy adott kulcsú elemet a fából
template <typename T>
void DeleteNode(tree<T> * rbt, long long key)
{
	if (IsIn(rbt, key))
	{
		DeleteNode<T>(rbt, rbt->root, key);
		rbt->size--;
	}
	else
	{
		cout << key << " Nem eleme az adatszerkezetnek" << endl;
	}
}

//Ha nincs ilyen él leáll, megnézi hány leszármazott van, ha csak1, caseö, ha tobb, megkeresi a legkisebb de az
//elemnél nagyobb elemet, ezt rámásolja a törlendőre
template <typename T>
void DeleteNode(tree<T>* rbt, node<T>* nd, long long kulcs)
{
	if (nd == nullptr || nd->nil)
	{
		return;
	}

	if (nd->key == kulcs)
	{
		if (nd->right->nil || nd->left->nil)
		{
			DeleteCase0<T>(rbt, nd);
		}
		else
		{
			node<T> * SmallBig = GetMin(rbt, nd->right);
			nd->key = SmallBig->key;
			nd->info = SmallBig->info;
			DeleteNode<T>(rbt, nd->right, SmallBig->key);
		}
	}
	if (nd->key < kulcs)
	{
		DeleteNode<T>(rbt, nd->right, kulcs);
	}
	else
	{
		DeleteNode<T>(rbt, nd->left, kulcs);
	}
}

//megkeresi az egyetlen leszármazottat,felcseréli a kettőt,ha a csomópont piros, feketére szìnezzük,
//ha fekete már, akkor case 1
template <typename T>
void DeleteCase0(tree<T>* rbt, node<T>* nd)
{
	node<T>* Son;
	if (nd->right->nil)
	{
		Son = nd->left;
	}
	else
	{
		Son = nd->right;
	}
	SwapNode<T>(rbt, nd, Son);
	if (nd->color == BLACK)
	{
		if (Son->color == RED)
		{
			Son->color = BLACK;
		}
		else
		{
			DeleteCase1<T>(rbt, Son);
		}
	}
}

//ha a gyökér a duplán fekete, akkor vége, ha nem, case2
template <typename T>
void DeleteCase1(tree<T>* rbt, node<T>* DoubleBlack)
{
	if (DoubleBlack->parent == nullptr)
	{
		rbt->root = DoubleBlack;
		return;
	}
	DeleteCase2<T>(rbt, DoubleBlack);
}

//forgatást és színezést végez, majd hívja a case3-at|
template <typename T>
void DeleteCase2(tree<T>* rbt, node<T>* DoubleBlack)
{
	if (DoubleBlack->parent != nullptr)
	{  
		node<T>* Bro = Brother<T>(rbt, DoubleBlack);
		if (Bro->color == RED)
		{
			DoubleBlack->parent->color = RED;
			Bro->color = BLACK;
			if (DoubleBlack->parent->left == DoubleBlack)
			{
				RotateLeft<T>(rbt, DoubleBlack->parent);
			}
			else
			{
				RotateRight<T>(rbt, DoubleBlack->parent);
			}
		}
		DeleteCase3<T>(rbt, DoubleBlack);
	}
}

//Színez a testvért ha szükséges
template <typename T>
void DeleteCase3(tree<T>* rbt, node<T>* DoubleBlack)
{
	node<T>* Bro = Brother<T>(rbt, DoubleBlack);
	if (DoubleBlack->parent->color == BLACK && Bro->color == BLACK && Bro->left->color == BLACK && Bro->right->color == BLACK)
	{
		Bro->color = RED;
		DeleteCase1<T>(rbt, DoubleBlack->parent);
	}
	else
	{
		DeleteCase4<T>(rbt, DoubleBlack);
	}
}

//Hasonló a case3-hoy, csak más feltétel melett színez
template <typename T>
void DeleteCase4(tree<T>* rbt, node<T>* DoubleBlack)
{
	node<T>* Bro = Brother<T>(rbt, DoubleBlack);
	if (DoubleBlack->parent->color == RED && Bro->color == BLACK && Bro->left->color == BLACK && Bro->right->color == BLACK)
	{
		Bro->color = RED;
		DoubleBlack->parent->color = BLACK;
		return;
	}
	else
	{
		DeleteCase5<T>(rbt, DoubleBlack);
	}
}

//Forgatást végez,színek szerint 
template <typename T>
void DeleteCase5(tree<T>* rbt, node<T>* DoubleBlack)
{
	node<T>* Bro = Brother<T>(rbt, DoubleBlack);
	if (Bro == nullptr || Bro->parent == nullptr)return;
	if (Bro->color == BLACK)
	{
		if (DoubleBlack->parent->left == DoubleBlack && Bro->right->color == BLACK && Bro->left->color == RED)
		{
			RotateRight<T>(rbt, Bro);
			Bro->left->color = BLACK;
			Bro->left->parent->color = RED;
		}
		else if (DoubleBlack->parent->right == DoubleBlack && Bro->left->color == BLACK && Bro->right->color == RED)
		{
			RotateLeft<T>(rbt, Bro);
			Bro->right->color = BLACK;
			Bro->right->parent->color = RED;
		}
	}
	DeleteCase6<T>(rbt, DoubleBlack);
}

//További színezés és megfelelő forgatás
template <typename T>
void DeleteCase6(tree<T>* rbt, node<T>* DoubleBlack)
{
	node<T>* Bro = Brother<T>(rbt, DoubleBlack);
	if (Bro==nullptr || Bro->parent == nullptr )return;
	Bro->color = Bro->parent->color;
	Bro->parent->color = BLACK;
	if (DoubleBlack->parent->left == DoubleBlack)
	{
		Bro->right->color = BLACK;
		RotateLeft<T>(rbt, Bro->parent);
	}
	else
	{
		Bro->left->color = BLACK;
		RotateRight<T>(rbt, Bro->parent);
	}
	if (Bro->parent == nullptr)
	{
		rbt->root = Bro;
	}
}

//Sorba rendeyve az elemeket egy bizonyos kulcsú elem előtti elemet térít vissza
template <typename T>
node<T>* Before(tree<T>*rbt,long long key)
{
	if (!IsIn(rbt, key))
		return nullptr;
	long long h = GetRank<T>(rbt, key);
	return GetElement<T>(rbt, h - 1);
}

//Sorba rendeyve az elemeket egy bizonyos kulcsú elem utáni elemet térít vissza
template <typename T>
node<T>* After(tree<T>* rbt, long long key)
{
	if (!IsIn(rbt, key))
		return nullptr;
	long long h=GetRank<T>(rbt, key);
	return GetElement<T>(rbt, h + 1);
}

//Fa inorder kiírása
template <typename T>
void PrintInorder(tree<T>* rbt)
{
	PrintInorder<T>(rbt->root);
}
template <typename T>
//Részfa inorder kiírása
void PrintInorder(node<T>* nd) 
{
	if (nd == nullptr) {
		return;
	}
	PrintInorder<T>(nd->left);
	if (!nd->nil)
	PrintNode<T>(nd);
	PrintInorder<T>(nd->right);
}

//Vissyatéríti egy adott kulcsú csomópont rangját
template <typename T>
long long GetRank(tree<T>* rbt, long long key)
{
	long long rank = 1;
	if (!IsIn(rbt, key))
	{
		cout << key << " nincs benne az adatszerkezetben" << endl;
		return 0;
	}
		Inorder<T>(rbt, rank, key);
		return rank;
}

//Rang kiszámítását segíti elő
template <typename T>
void Inorder(tree<T>* rbt, long long& rank, long long key)
{
	Inorder<T>(rbt->root,rank,key);
}

//Rang kiszámítását segíti elő
template <typename T>
void Inorder(node<T>* nd, long long&rank, long long key)
{
	if (nd == nullptr) {
		return;
	}
	if (nd->key == key)
		return;
	Inorder<T>(nd->left,rank,key);
	if (!nd->nil and nd->key<key)
		rank++;
	Inorder<T>(nd->right,rank,key);
}

//Adott rangú elem keresérse
template <typename T>
node<T>* GetElement(tree<T>* rbt, long long number)
{
	if (rbt->size >= number)
	{
		long long rank = 0;
		return GetElement<T>(rbt->root, number, rank);
	}
	cout << "Nincs ennyi elem" << endl;
	return 0;
}

//Adott rangú elem keresése *segéd*
template <typename T>
node<T>* GetElement(node<T>* nd, long long number, long long& rank)
{
	if (nd == nullptr || nd->nil) {
		return nullptr;
	}
	node<T>* result = nullptr;
	result = GetElement<T>(nd->left, number, rank);
	if (result != nullptr) {
		return result;
	}
	rank++;
	if (rank == number) {
		return nd;
	}
	result = GetElement<T>(nd->right, number, rank);
	if (result != nullptr) {
		return result;
	}
	return nullptr;
}