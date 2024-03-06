#include <iostream>
#include "RBTrees.h"
#include "RBTrees.cpp"
#include "Feladat.h"
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

#define IMMUNITAS 5
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

//A rendsyámból kulcsot késyít a csomópontoknak
long long ConvertToKey(string Rendszam)
{
    long long key=0;
    int H = Rendszam.length();
    for (int i = 0; i < H; i++)
    {
        if (Rendszam[i] <= 97)
            key = key*100+Rendszam[i] - 32;
        else
            key = key * 100 + Rendszam[i];
    }
    return key;
}

//A kuryort helyezi választásokkal
void Here(int option)
{
    if (option == 1)
    {
        MoveCursor(21, 59);
        cout << " ";
    }
    else
        if (option == 2)
        {
            MoveCursor(22, 59);
            cout << " ";
        }
        else
            if (option == 3)
            {
                MoveCursor(23, 59);
                cout << " ";
            }
            else
                if (option == 4)
                {
                    MoveCursor(24, 59);
                    cout << " ";
                }
                else
                    if (option == 5)
                    {
                        MoveCursor(25, 59);
                        cout << " ";
                    }
                    else
                        if (option == 6)
                        {
                            MoveCursor(26, 59);
                            cout << " ";
                        }

         


}

//Autó típusát dönti el
void TypeSelector(string& tipus)
{
    char key = 1;
    do
    {
        int option = 1;
        MoveCursor(20, 60);
        cout << "Az auto tipusa:" << endl;
        MoveCursor(21, 60);
        cout <<  " SPORT" << endl;
        MoveCursor(22, 60);
        cout << " MOTOR" << endl;
        MoveCursor(23, 60);
        cout <<  " KAMION" << endl;
        MoveCursor(24, 60);
        cout <<  " TEREPJARO" << endl;
        MoveCursor(25, 60);
        cout << " ANTIK" << endl;
        MoveCursor(26, 60);
        cout <<  " SIMA" << endl;
        do
        {
           
            switch (_getch())
            {
            case KEY_UP:
                option = (option == 1) ? 3 : option - 1;
                Here(option);
                break;

            case KEY_DOWN:
                option = (option == 6) ? 1 : option + 1;
                Here(option);
                break;

            case ENTER:
                switch (option)
                {
                case 1:
                    tipus = "Sport";
                    break;
                case 2:
                    tipus = "Motor";
                    break;
                case 3:
                    tipus = "Kamion";
                    break;
                case 4:
                    tipus = "Terepjaro";
                    break;
                case 5:
                    tipus = "Antik";
                    break;
                case 6:
                    tipus = "Sima";
                    break;
                }
                return;
            }
        } while (true);

    } while (key == '1');
}

//Gépjárm?vet ad az adatbázishoz
void AddCar(tree<car>* rbt)
{
    system("cls");
    string Rendszam, Szin, Marka,Tipus;
    int nap, honap, ev;
    long long kulcs;
    system("color 1f");
    cout << "\033[1;36m";
    MoveCursor(14, 60);
    cout << "> A gepjarmu rendszama: ";
    cin>>Rendszam; cout << endl;
    MoveCursor(16, 60);
    cout << "> A gepjarmu szine: ";
    cin >> Szin; cout << endl;
    MoveCursor(18, 60);
    cout << "> A gepjarmu markaja: ";
    cin >> Marka; cout << endl;
    MoveCursor(20, 60);
    TypeSelector(Tipus);
    cout << endl;
    do {
        MoveCursor(28, 60);
        cout << "> A nap, melyen eszlelted *szam* : ";
        cin >> nap; cout << endl;
    } while (nap < 1 or nap > 31);
    do {
        MoveCursor(30, 60);
        cout << "> A honap, melyen eszlelted *szam*: ";
        cin >> honap; cout << endl;
    } while (honap < 1 or honap > 12);
    MoveCursor(32, 60);
    cout << "> Az ev, melyen eszlelted *szam*: ";
    cin >> ev; cout << endl;

   kulcs = ConvertToKey(Rendszam);
   car k;
   k.Rendszam = Rendszam;
   k.Szin = Szin;
   k.nap = nap;
   k.Marka = Marka;
   k.kulcs = kulcs;
   k.honap = honap;
   k.hatramaradt = IMMUNITAS;
   k.ev = ev;
   k.Tipus = Tipus;
   InsertNode<car>(rbt, kulcs, k);
   system("cls");
   MoveCursor(15, 60);
   cout << "Sikeresen hozza adtad,nyomj entert!";
   char x=_getch();
}

//Megkeresi az adott gépjárm?vet az adatbázisban
void IsInCar(tree<car>* rbt)
{
    system("cls");
    cout << "\033[1;36m";
    MoveCursor(1, 60);
    cout << "BENNT VAN-E AZ AUTO AZ ADATBAZISBAN?";

    string Rendszam;
    MoveCursor(15, 60);
    cout << "Add meg a rendszamot:"; cin >> Rendszam;
    MoveCursor(17, 60);
    if (IsIn<car>(rbt,ConvertToKey(Rendszam)))
    {
        cout << "*****IGEN*****";
        char x=_getch();
        return;
    }
    cout << "*****NEM*****";
    char x=_getch();
    return;
}

//Képet rajzol
void Sport(node<car>* nd)
{
    ifstream file("Sport1.txt");
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
    cout << "]" << nd->info.Rendszam << "[w] : /  : |= ====================== = | : /  : [w] :" << endl;
    ifstream file2("Sport2.txt");
    while (getline(file2, line)) {
        cout << line << '\n';
    }
    file2.close();
    
}
//Képet rajzol
void Motor(node<car>* nd)
{
    ifstream file("Motor1.txt");
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
    cout <<"       /_-~                       _-/'          )~/ "<< nd->info.Rendszam << endl;
    ifstream file2("Motor2.txt");
    while (getline(file2, line)) {
        cout << line << '\n';
    }
    file2.close();
}
//Képet rajzol
void Kamion(node<car>* nd)
{
    ifstream file("Kamion1.txt");
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
    cout << ":      |`.    | | " << nd->info.Rendszam <<"||     ,'|     :" <<endl;
    ifstream file2("Kamion2.txt");
    while (getline(file2, line)) {
        cout << line << '\n';
    }
    file2.close();
}
//Képet rajzol
void Antik(node<car>* nd)
{
    ifstream file("Antik1.txt");
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
    cout << "' .---.`.| / / \\ || // \ \  \  \-----"<< nd->info.Rendszam << "--------; : .   \\ ||//   . : \ " <<endl;
    ifstream file2("Antik2.txt");
    while (getline(file2, line)) {
        cout << line << '\n';
    }
    file2.close();
}
//Képet rajzol
void Sima(node<car>* nd)
{
    ifstream file("Sima1.txt");
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
    cout << "[_________|" << nd->info.Rendszam<<"_________]" << endl;
    ifstream file2("Sima2.txt");
    while (getline(file2, line)) {
        cout << line << '\n';
    }
    file2.close();
}
//Képet rajzol
void Terepjaro(node<car>* nd)
{
    ifstream file("Terepjaro1.txt");
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
    cout << "  \__/~ /     `-,.; ; o |\___[~~~]" << nd->info.Rendszam<<"[~~~]__:" << endl;
    ifstream file2("Terepjaro2.txt");
    while (getline(file2, line)) {
        cout << line << '\n';
    }
    file2.close();
}

//Kiírja a gépjárm? adatait
void Print(node<car>* nd,int opcio,tree<car>*rbt)
{

    if(!nd->nil)
    {
        if (nd->info.Tipus == "Terepjaro")
            Terepjaro(nd);
        else
            if (nd->info.Tipus == "Sport")
                Sport(nd);
            else
                if (nd->info.Tipus == "Motor")
                    Motor(nd);
                else
                    if (nd->info.Tipus == "Kamion")
                        Kamion(nd);
                    else
                        if (nd->info.Tipus == "Antik")
                            Antik(nd);
                        else
                            if (nd->info.Tipus == "Sima")
                                Sima(nd);
        cout << "Rendszam: " << nd->info.Rendszam << endl;
        cout << "Szine: " << nd->info.Szin << endl;
        cout << "Markaja: " << nd->info.Marka << endl;
        cout << "Tipusa: " << nd->info.Tipus << endl;
        cout << "Buntetes idopontja: " << nd->info.nap << ":" << nd->info.nap << ":" << nd->info.ev << endl;
        cout << "Hatramaradt ido: " << nd->info.hatramaradt;
        if (opcio == 1)
            _getch();
    }
    else
    {
        cout << "NINCS ILYEN AUTO";
        _getch();
    }
    
}

//Tartalmayya a reedszám lekér? és auto kiíró m?veletet
void PrintCar(tree<car>*rbt)
{
    system("cls");
    MoveCursor(1, 60);
    cout << "GEPJARMU ADAT KIIRAS";

    string Rendszam;
    MoveCursor(15, 60);
    cout << "Add meg a rendszamot:"; cin >> Rendszam;
    MoveCursor(17, 60);
    Print(Find<car>(rbt, ConvertToKey(Rendszam)),1,rbt);
    return;
}

//Kurzort helyezi
void Here2(int option)
{
    if (option == 1)
    {
        MoveCursor(16, 59);
        cout << " ";
    }
    else
        if (option == 2)
        {
            MoveCursor(17, 59);
            cout << " ";
        }
        else
            if (option == 3)
            {
                MoveCursor(18, 59);
                cout << " ";
            }
            else
                if (option == 4)
                {
                    MoveCursor(19, 59);
                    cout << " ";
                }
                else
                    if (option == 5)
                    {
                        MoveCursor(20, 59);
                        cout << " ";
                    }
                    else
                        if (option == 6)
                        {
                            MoveCursor(21,59);
                            cout << " ";
                        }
                        else
                            if (option == 7)
                            {
                                MoveCursor(22, 59);
                                cout << " ";
                            }
}

//Gépjárm?vet töröl
void DeleteCar(tree<car>* rbt)
{
    system("cls");
    system("color 1f");
    cout << "\033[1;36m";
    MoveCursor(14, 60);
    string rendszam;
    cout << "Add meg a rendszamot: "; cin >> rendszam;
    DeleteNode(rbt, ConvertToKey(rendszam));
    MoveCursor(16, 60);
    cout << "Kesz is, nyomj egy entert";
    _getch();
}

//Kiirja az adatbázis minden elemét
void PrintBase(node<car>* nd,tree<car>*rbt)
{
    system("cls");
    PrintBase2(nd,rbt);
    _getch();
}
//Kiirásban segít
void PrintBase2(node<car>* nd,tree<car>*rbt)
{
    if (nd == nullptr) {
        return;
    }
    PrintBase2(nd->left,rbt);
    if (!nd->nil)
        Print(nd,0,rbt);
    PrintBase2(nd->right,rbt);
}

//Csokkenti az "Immunis" id?t, szükség esetén töröl
void Set2(node<car>* nd, tree<car>* rbt)
{
    vector<long long> seged;
    Set(nd, rbt,seged);
    system("cls");
    system("color 1f");
    cout << "\033[1;36m";
    MoveCursor(14, 60);
    for (int i = 0; i < seged.size(); i++)
        DeleteNode(rbt, seged[i]);
    cout << "FRISSITES ELVEGEZVE";
    char x=_getch();

}
//Csokkenti az "Immunis" id?t, szükség esetén töröl
void Set(node<car>* nd,tree<car>* rbt,vector<long long>& seged)
{
    if (nd == nullptr) {
        return;
    }
    Set(nd->left,rbt,seged);
    Set(nd->right, rbt,seged);
    if (!nd->nil)
    {
        if (nd->info.hatramaradt == 0)
        {
            seged.push_back(nd->key);
            nd->info.hatramaradt--;
        }
        else
            nd->info.hatramaradt--;
    }
    
}

//Válaszlehetöségeket sorol fel
void Main2(tree<car>* rbt)
{
    system("cls");
    system("color 1f");
    cout << "\033[1;36m";
    MoveCursor(14, 60);
    cout << "Valassz muveletet:";

    while (true)
    {
        int option = 1;
        MoveCursor(16, 60);
        cout << " Gepjarmu hozzaadas" << endl;
        MoveCursor(17, 60);
        cout << " Ellenorizzuk, hogy bent van-e a gapjarmu" << endl;
        MoveCursor(18, 60);
        cout << " Gepjarmu adatainak kiirasa" << endl;
        MoveCursor(19, 60);
        cout << " Gepjarmu torlese az adatbazisbol" << endl;
        MoveCursor(20, 60);
        cout << " Osszes gepjarmu kiirasa" << endl;
        MoveCursor(21, 60);
        cout << " Munkaido kezdete van(Adatszerkezet frissitese)" << endl;
        MoveCursor(22, 60);
        cout << " KILEP" << endl;

        do
        {


            switch (_getch())
            {
            case KEY_UP:
                option = (option == 1) ? 7 : option - 1;
                Here2(option);
                break;

            case KEY_DOWN:
                option = (option == 7) ? 1 : option + 1;
                Here2(option);
                break;

            case ENTER:
                switch (option)
                {
                case 1:
                    AddCar(rbt);
                    Main2(rbt);
                    break;
                case 2:
                    IsInCar(rbt);
                    Main2(rbt);
                    break;
                case 3:
                    PrintCar(rbt);
                    Main2(rbt);
                    break;
                case 4:
                    DeleteCar(rbt);
                    Main2(rbt);
                    break;
                case 5:
                    PrintBase(rbt->root,rbt);
                    Main2(rbt);
                    break;
                case 6:
                    Set2(rbt->root,rbt);
                    Main2(rbt);
                    break;
                case 7:
                    exit(0);
                }
                break;
            }


        } while (true);
    }
}
 
//Létrehozza az adatbáyist,és a standard bemenetr?l helyes 1 gépjárm?vet bele
void CreateDataBase(tree<car>* rbt)
{
    AddCar(rbt);
    Main2(rbt);
}

//Fileból olvas be információkat
void CreateDataBaseFromFile(tree<car>* rbt)
{
    system("cls");
    system("color 1f");
    cout << "\033[1;36m";
    string filename;
    MoveCursor(15, 60);
    cout << "Add meg a filenevet: ";
    cin >> filename;
    CreateDataBaseFromFile(filename, rbt);
    Main2(rbt);
}
//Fileból olvas be információkat
void CreateDataBaseFromFile(string filename,tree<car>* rbt)
{
    ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file!" << endl;
        return;
    }
    int szam; long long kulcs;
    car k;
    while (infile >> k.Rendszam >> k.Szin >> k.Marka>> szam>> k.nap >> k.honap >> k.ev) 
    {
        if (szam == 1)k.Tipus = "Sima";
        if (szam == 2)k.Tipus = "Sport";
        if (szam == 3)k.Tipus = "Motor";
        if (szam == 4)k.Tipus = "Kamion";
        if (szam == 5)k.Tipus = "Terepjaro";
        if (szam == 6)k.Tipus = "Antik";
        kulcs = ConvertToKey(k.Rendszam);
        k.kulcs = kulcs;
        k.hatramaradt = IMMUNITAS;
        InsertNode<car>(rbt, kulcs, k);
    }
    infile.close();
}

//Kuryord helyezi
void MoveCursor(int x, int y)
{
    printf("\033[%d;%dH", x, y);
}

//F?oldalt tartalmazza
void Main(tree<car>* rbt)
{
    int option = 1;

    do
    {
        system("color 1f");
        system("cls");
        cout << "\033[1;36m";
        MoveCursor(14, 60);
        cout << "SZOLGALATRA KESZEN?" << endl;
        MoveCursor(15, 60);
        cout << "KERLEK VALASSZ:" << endl<<endl;
        MoveCursor(19, 57);
        cout << ((option == 1) ? "  > " : "    ") << "Ures adatbazis letrehozasa" << endl<<endl;
        MoveCursor(21, 57);
        cout << ((option == 2) ? "  > " : "    ") << "Textfile-bol valo olvasas" << endl<<endl;
        MoveCursor(23, 57);
        cout << ((option == 3) ? "  > " : "    ") << "Kilepes" << endl;

        switch (_getch())
        {
        case KEY_UP:
            option = (option == 1) ? 3 : option - 1;
            break;

        case KEY_DOWN:
            option = (option == 3) ? 1 : option + 1;
            break;

        case ENTER:
            switch (option)
            {
            case 1:
                CreateDataBase(rbt);
                break;

            case 2:
                CreateDataBaseFromFile(rbt);
                break;

            case 3:
                return;
                break;
            }
            break;
        }
    } while (true);

}

//Létrehozza az bináris fát és megnyitja a f?oldalt
void Start()
{
    int i;
    system("cls");
    cout << "NYISD MEG TELJES KEPERNYOBEN, MAJD NYOMJ EGY ENTERT";
    i=_getch();
    tree<car>* base = CreateRBT<car>();
    //DataBase.num = 1;
    Main(base);
}