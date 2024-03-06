#ifndef Red_Black_Tree
#define Red_Black_Tree

using namespace std;

//Csomopont struktura,ezekbol fog felépüln az adatszerkezet
//Tartalma: kulcs,szín,nil(mely ha true, akkor null levél) szülő,maximum 2 utód(jobb és bal), és egy szabadon fenntartott infó mező.
//Ha valóban ki akarjuk használni a fa jó tulajdonságait, véleménzem szerint ez a legideálisabb megoldás, hisz template segitségével nem húzzuk skatulyába az adatszerkezetet.
//így felhasználó konkrtan barmilyen adatra felhasználhat.
template <typename T>
struct node{
    long long key;
    bool color;
    bool nil;
    node* right;
    node* left;
    node* parent;
    T info;
};

//Fa struktúra
template <typename T>
struct tree {
    node<T>* root;
    int size;
};

//Egy null csomopontot hoz létre
template <typename T>
node<T>* CreateNil(node<T>*);
//Csomópont létrehozása, melynek kulcsa van, de infó mezeje üres
template <typename T>
node<T>* CreateNode(long long);
//Csomópont létrehozása, melynek kulcsa van, és infó mezeje is információt tartalmaz.(típusa felhasználó függő) 
template <typename T>
node<T>* CreateNode(long long,T);

//Csomópont felszabadítása
template <typename T>
void FreeNode(node<T>*);

//Csomópont kiírása
template <typename T>
void PrintNode(node<T>*);

//Visszatéríti a csomópont színét
template <typename T>
bool GetColor(node<T>*);

//Visszatéríti a csomópont kulcsát
template <typename T>
long long GetKey(node<T>*);

//Kiválasztható egy csomópont és a részfáját kiirja
template <typename T>
void WoutTree(tree<T>*,node<T>*);

//Bejárja a fát és meghívja minden csomópontra a kiíráast
template <typename T>
void PrintTree(tree<T>* );

//Fa létrehozása
template <typename T>
tree<T>* CreateRBT();

//Rekuryívan törli a csomópontokat
template <typename T>
void FreeRBTNode(node<T>*);

//a fa gyökerére hívjuk meg a rekurzív törlést
template <typename T>
void FreeRBT(tree<T>*);

//Csomópont létehozása és beszúrása, melynek nincs infó mezeje, de kötelező a kulcs
template <typename T>
void InsertNode(tree<T>*, long long);

//Csomópont létrehozása és beszúrása, melynek van infó mezeje is
template <typename T>
void InsertNode(tree<T>*, long long, T);

//Már meglévő somópont beszúrása
template <typename T>
void InsertNode(tree<T>*, node<T>*);

//Forgat jobbra csomószerint
template <typename T>
void RotateRight(tree<T>*, node<T>*);

//Forgat balra csomó szerint
template <typename T>
void RotateLeft(tree<T>*, node<T>*);

//Beszúrást követően optimaliyálja a fát
template <typename T>
void InsertNodeResolved(tree<T>*, node<T>*);

//Visszatéríti egy részfa legnagyobb kulcsú elemét
template <typename T>
node<T>* GetMax(tree<T>*,node<T>*);

//Visszatéríti egy részfa legkisebb kulcsú elemét
template <typename T>
node<T>* GetMin(tree<T>*,node<T>*);

//Visszatéríti a fa legkisebb kulcsú elemét
template <typename T>
node<T>* GetMin(tree<T>*);

//Visszatéríti a fa legnagyobb kulcsú elemét
template <typename T>
node<T>* GetMax(tree<T>*);

//Adott kulcsú csomópontot keres egy részfában
template <typename T>
node<T>* Find(tree<T>*, long long);

//Adott kulcsú csomópontot keres a teljes fában
template <typename T>
node<T>* Find(tree<T>*, node<T>* , long long );

//Igazat/Hamisat térít vissza, attól függően, hogy eleme vagy nem egy adott kulcsú csomó a fának
template <typename T>
bool IsIn(tree<T>*, long long);

//Fa inorder kiírása
template <typename T>
void PrintInorder(tree<T>*);

//Részfa inorder kiírása
template <typename T>
void PrintInorder(node<T>*);

//Vissyatéríti egy adott kulcsú csomópont rangját
template <typename T>
long long GetRank(tree<T>*, long long);

//Rang kiszámítását segíti elő
template <typename T>
void Inorder(node<T>*,long long&,long long);

//Rang kiszámítását segíti elő
template <typename T>
void Inorder(tree<T>*,long long&,long long);

//Adott rangú elem keresérse
template <typename T>
node<T>* GetElement(tree<T>*, long long);

//Adott rangú elem keresése *segéd*
template <typename T>
node<T>* GetElement(node<T>*, long long, long long& );

//Sorba rendeyve az elemeket egy bizonyos kulcsú elem előtti elemet térít vissza
template <typename T>
node<T>* Before(tree<T>*, long long );

//Sorba rendeyve az elemeket egy bizonyos kulcsú elem utáni elemet térít vissza
template <typename T>
node<T>* After(tree<T>*, long long);

//Vissztéríti egy csomópont tstvérét, azaz, azt az elemet, kivel közős az őse
template <typename T>
node<T>* Brother(tree<T>*, node<T>*);

//Felcserél két csomópontot
template <typename T>
void SwapNode(tree<T>*, node<T>*, node<T>*);

//Töröl egy adott kulcsú elemet a fából
template <typename T>
void DeleteNode(tree<T>*, long long);

//Ha nincs ilyen él leáll, megnézi hány leszármazott van, ha csak1, caseö, ha tobb, megkeresi a legkisebb de az
//elemnél nagyobb elemet, ezt rámásolja a törlendőre
template <typename T>
void DeleteNode(tree<T>*, node<T>*, long long);

//megkeresi az egyetlen leszármazottat,felcseréli a kettőt,ha a csomópont piros, feketére szìnezzük,
//ha fekete már, akkor case 1
template <typename T>
void DeleteCase0(tree<T>*, node<T>* );

//ha a gyökér a duplán fekete, akkor vége, ha nem, case2
template <typename T>
void DeleteCase1(tree<T>*, node<T>*);

//forgatást és színezést végez, majd hívja a case3-at|
template <typename T>
void DeleteCase2(tree<T>*, node<T>*);

//Színez a testvért ha szükséges
template <typename T>
void DeleteCase3(tree<T>*, node<T>*);

//Hasonló a case3-hoy, csak más feltétel melett színez
template <typename T>
void DeleteCase4(tree<T>*, node<T>*);

//Forgatást végez,színek szerint 
template <typename T>
void DeleteCase5(tree<T>*, node<T>*);

//További színezés és megfelelő forgatás
template <typename T>
void DeleteCase6(tree<T>*, node<T>*);

#endif
