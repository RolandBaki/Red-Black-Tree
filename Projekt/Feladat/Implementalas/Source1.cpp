#include <iostream>
#include "pf_keresofa.h"

#define FEKETE -1
#define PIROS 1

using namespace std;

void deletePFCsomopont(pf_keresofa*, csomopont*, int kulcs);
void deleteEset0(pf_keresofa*, csomopont*);

void deleteEset1(pf_keresofa*, csomopont*);
void deleteEset2(pf_keresofa*, csomopont*);
void deleteEset3(pf_keresofa*, csomopont*);
void deleteEset4(pf_keresofa*, csomopont*);
void deleteEset5(pf_keresofa*, csomopont*);
void deleteEset6(pf_keresofa*, csomopont*);

//CSOMOPONT:

// letrehoz egy NULL levelet, aminek szine fekete, es kulcsa 0
csomopont* createNULL(csomopont* szulo)
{
    csomopont* csp = new csomopont;
    csp->szulo = szulo;
    csp->jobb = nullptr;
    csp->bal = nullptr;
    csp->szin = FEKETE;
    csp->kulcs = 0;
    csp->nullLevel = true;
    return csp;
}

// letrehoz egy kozonseges szintelen, a kivant kulcsnak megfelelo csomopontot
csomopont* createCsomopont(int _kulcs)
{
    csomopont* csp = new csomopont;
    csp->kulcs = _kulcs;
    csp->jobb = createNULL(csp);
    csp->bal = createNULL(csp);
    csp->nullLevel = false;
    return csp;
}

// felszabadit egy csomopontot
void freeCsomopont(csomopont* csp)
{
    delete csp;
}

// kiirja a csomopont kulcsat es szinet
void kiirCsomopont(csomopont* csp)
{
    if (csp == nullptr)
    {
        return;
    }

    if (csp->szin == FEKETE)
    {
        cout << csp->kulcs << ":FEKETE" << endl;
    }
    else
    {
        cout << csp->kulcs << ":PIROS" << endl;
    }
}

// visszateriti egy csomopont szinet
int getSzin(csomopont* csp)
{
    if (csp == nullptr)
    {
        return 0;
    }
    return csp->szin;
}

// visszateriti egy csomopont kulcsat
int getKulcs(csomopont* csp)
{
    if (csp == nullptr)
    {
        return 0;
    }
    return csp->kulcs;
}

//PIROS-FEKETE-KERESOFA:

// letrehozz egy piros-fekete fat, a gyokeret null-ra allitja
pf_keresofa* createPF()
{
    pf_keresofa* pf = new pf_keresofa;
    pf->gyoker = nullptr;
    return pf;
}

// piros-fekete fa felszabaditasa
void freePFCsomopont(csomopont* csp)
{
    freeCsomopont(csp->bal);
    freeCsomopont(csp->jobb);
    delete csp;
}

// felszabaditja a piros-fekete fat alkoto osszes csomopontot, majd a gyokeret is
void freePF(pf_keresofa* pf)
{
    if (pf == nullptr)
    {
        return;
    }
    if (pf->gyoker != nullptr)
    {
        freePFCsomopont(pf->gyoker);
    }
    delete pf;
}

// beszur a megfelelo helyre egy kozonseges szintelen csomopontot, szinezest nem valtoztatja
void insertPFCsomopont(pf_keresofa* pf, csomopont* csp)
{
    if (csp == nullptr)
    {
        return;
    }

    if (pf->gyoker == nullptr)
    {
        pf->gyoker = csp;
        pf->gyoker->szulo = nullptr;
        return;
    }

    csomopont* p = pf->gyoker;
    csomopont* elozo = nullptr;
    while (!p->nullLevel)
    {
        elozo = p;
        if (csp->kulcs < p->kulcs)
        {
            p = p->bal;
        }
        else
        {
            p = p->jobb;
        }
    }

    if (csp->kulcs < elozo->kulcs)
    {
        elozo->bal = csp;
        csp->szulo = elozo;
    }
    else
    {
        elozo->jobb = csp;
        csp->szulo = elozo;
    }
}

// adott csomopont szerint jobbra forgat, megtartva a fa piros-fekete tulajdonsagat
void forgatjobbra(pf_keresofa* pf, csomopont* csp)
{
    if (csp->bal->nullLevel)
    {
        return;
    }

    csomopont* _csp = csp->bal;
    csp->bal = _csp->jobb;

    if (!_csp->jobb->nullLevel)
    {
        _csp->jobb->szulo = csp;
    }

    _csp->szulo = csp->szulo;

    if (csp->szulo == nullptr)
    {
        pf->gyoker = _csp;
    }
    else
    {
        if (csp == csp->szulo->bal)
        {
            csp->szulo->bal = _csp;
        }
        else
        {
            csp->szulo->jobb = _csp;
        }
    }
    _csp->jobb = csp;
    csp->szulo = _csp;
}

// adott csomopont szerint balra forgat, megtartva a fa piros-fekete tulajdonsagat
void forgatbalra(pf_keresofa* pf, csomopont* csp)
{
    if (csp->jobb->nullLevel)
    {
        return;
    }

    csomopont* _csp = csp->jobb;
    csp->jobb = _csp->bal;

    if (!_csp->bal->nullLevel)
    {
        _csp->bal->szulo = csp;
    }

    _csp->szulo = csp->szulo;

    if (csp->szulo == nullptr)
    {
        pf->gyoker = _csp;
    }
    else
    {
        if (csp == csp->szulo->bal)
        {
            csp->szulo->bal = _csp;
        }
        else
        {
            csp->szulo->jobb = _csp;
        }
    }
    _csp->bal = csp;
    csp->szulo = _csp;
}

// letrehozza a megadott kulcsnak megfelelo csomopontot, majd meghivja ra a beszurast
void insertPF(pf_keresofa* pf, int kulcs)
{
    csomopont* csp = createCsomopont(kulcs);
    insertPF(pf, csp);
}

// beszuro fuggveny, eloszor beszurja a helyere a kivant csomopontot, majd szinezesekkel es atforgatasokkal visszaallitja a fa piros-fekete tulajdonsagat
void insertPF(pf_keresofa* pf, csomopont* csp)
{
    if (csp == nullptr)
    {
        return;
    }

    insertPFCsomopont(pf, csp);
    csp->szin = PIROS;

    if (csp->szulo == nullptr || csp->szulo->szulo == nullptr)
    {
        pf->gyoker->szin = FEKETE;
        return;
    }

    while (csp != pf->gyoker && csp->szulo->szin == PIROS)
    {
        if (csp->szulo == csp->szulo->szulo->bal)
        {
            csomopont* _csp = csp->szulo->szulo->jobb;

            int _szin;
            if (_csp->nullLevel)
            {
                _szin = FEKETE;
            }
            else
            {
                _szin = _csp->szin;
            }

            if (_szin == PIROS)
            {
                csp->szulo->szin = FEKETE;
                _csp->szin = FEKETE;
                _csp->szulo->szin = PIROS;
                csp = csp->szulo->szulo;
            }
            else
            {
                if (csp == csp->szulo->jobb)
                {
                    csp = csp->szulo;
                    forgatbalra(pf, csp);
                }
                csp->szulo->szin = FEKETE;
                csp->szulo->szulo->szin = PIROS;
                forgatjobbra(pf, csp->szulo->szulo);
            }
        }
        else
        {
            csomopont* _csp = csp->szulo->szulo->bal;

            int szin;
            if (_csp->nullLevel)
            {
                szin = FEKETE;
            }
            else
            {
                szin = _csp->szin;
            }

            if (szin == PIROS)
            {
                _csp->szulo->szin = PIROS;
                _csp->szin = FEKETE;
                csp->szulo->szin = FEKETE;
                csp = csp->szulo->szulo;
            }
            else
            {
                if (csp == csp->szulo->bal)
                {
                    csp = csp->szulo;
                    forgatjobbra(pf, csp);
                }
                csp->szulo->szulo->szin = PIROS;
                csp->szulo->szin = FEKETE;
                forgatbalra(pf, csp->szulo->szulo);
            }
        }
    }
    pf->gyoker->szin = FEKETE;
}

// visszateriti az adott csomoponttol szamitva a legnagyobb csomopontot
csomopont* maxPF(pf_keresofa* pf, csomopont* csp)
{
    csomopont* tmp = csp;
    csomopont* elozo = nullptr;
    while (!tmp->nullLevel)
    {
        elozo = tmp;
        tmp = tmp->jobb;
    }
    return !elozo->nullLevel ? elozo : tmp;
}

// visszateriti az adott csomoponttol szamitva a legkisebb csomopontot
csomopont* minPF(pf_keresofa* pf, csomopont* csp)
{
    csomopont* tmp = csp;
    csomopont* elozo = nullptr;
    while (!tmp->nullLevel)
    {
        elozo = tmp;
        tmp = tmp->bal;
    }
    return !elozo->nullLevel ? elozo : tmp;
}

// kiirja inorder sorrendben, egymas ala a piros-fekete fat alkoto csomopontokat
void kiirPFCsomopont(pf_keresofa* pf, csomopont* csp)
{
    if (!csp->nullLevel)
    {
        kiirCsomopont(csp);
        kiirPFCsomopont(pf, csp->bal);
        kiirPFCsomopont(pf, csp->jobb);
    }
}

// kiirja a piros-fekete fa tartalmat
void kiirPF(pf_keresofa* pf)
{
    if (pf == nullptr)
    {
        return;
    }
    kiirPFCsomopont(pf, pf->gyoker);
}

// binaris keresest vegez a fa elemein
csomopont* keresPFCsomopont(pf_keresofa* pf, csomopont* csp, int kulcs)
{
    if (csp->nullLevel)
    {
        return csp;
    }

    if (csp->kulcs == kulcs)
    {
        return csp;
    }
    else
    {
        if (csp->kulcs > kulcs)
        {
            return keresPFCsomopont(pf, csp->bal, kulcs);
        }
        else
        {
            return keresPFCsomopont(pf, csp->jobb, kulcs);
        }
    }
}

// megkeresi es visszateriti a kivant kulcsu csomopontot a fabol
csomopont* keresPF(pf_keresofa* pf, int kulcs)
{
    if (pf->gyoker == nullptr)
    {
        return nullptr;
    }

    return keresPFCsomopont(pf, pf->gyoker, kulcs);
}

// visszateriti a kivant csomopont testveret
csomopont* testverPF(pf_keresofa* pf, csomopont* csp)
{
    if (csp->szulo == nullptr)
    {
        return nullptr;
    }

    if (csp->szulo->bal == csp)
    {
        return csp->szulo->jobb;
    }
    else
    {
        return csp->szulo->bal;
    }
}

// a fa szinezese fuggvenyeben visszateriti a kivant kulcsu elem szinet
int getSzinPF(pf_keresofa* pf, int kulcs)
{
    csomopont* csp = keresPF(pf, kulcs);
    return getSzin(csp);
}

void felcserelCsomopont(pf_keresofa* pf, csomopont* csp, csomopont* leszarmazott)
{
    leszarmazott->szulo = csp->szulo;
    if (csp->szulo == nullptr)
    {
        pf->gyoker = leszarmazott;
    }
    else
    {
        if (csp->szulo->bal == csp)
        {
            csp->szulo->bal = leszarmazott;
        }
        else
        {
            csp->szulo->jobb = leszarmazott;
        }
    }
}

// torli a kivant kulcsu elemet a fabol
void deletePF(pf_keresofa* pf, int kulcs)
{
    deletePFCsomopont(pf, pf->gyoker, kulcs);
}

// kereso illetve torlo algoritmus, megkeresi a torolni kivan csomopontot, majd ramasolja a "succesorjanak" kulcsat, ezt addig vegzi, amig a torlendo csomopontnak
// 0 vagy 1 leszarmazottja nem lesz
void deletePFCsomopont(pf_keresofa* pf, csomopont* csp, int kulcs)
{
    if (csp == nullptr || csp->nullLevel)
    {
        return;
    }

    if (csp->kulcs == kulcs)
    {
        if (csp->jobb->nullLevel || csp->bal->nullLevel)
        {
            deleteEset0(pf, csp);
        }
        else
        {
            csomopont* legkisebbNagyobb = minPF(pf, csp->jobb);
            csp->kulcs = legkisebbNagyobb->kulcs;
            deletePFCsomopont(pf, csp->jobb, legkisebbNagyobb->kulcs);
        }
    }
    if (csp->kulcs < kulcs)
    {
        deletePFCsomopont(pf, csp->jobb, kulcs);
    }
    else
    {
        deletePFCsomopont(pf, csp->bal, kulcs);
    }
}

// megvizsgalja, hogy a torolni kivant csomopont kitorolheto-e ugy, hogy ne serulojon az a tulajdonsag, miszerint a gyokertol kiindulva minden
// agon ugyan annyi fekete csomopont talalhato, ha talal olyan csomopontot ami "duplan fekete" akkor meghivja ra a 6 kisebb metodust a szinezes
// helyreallitasa erdekeben
void deleteEset0(pf_keresofa* pf, csomopont* csp)
{
    csomopont* leszarmazott;
    if (csp->jobb->nullLevel)
    {
        leszarmazott = csp->bal;
    }
    else
    {
        leszarmazott = csp->jobb;
    }
    felcserelCsomopont(pf, csp, leszarmazott);
    if (csp->szin == FEKETE)
    {
        if (leszarmazott->szin == PIROS)
        {
            leszarmazott->szin = FEKETE;
        }
        else
        {
            deleteEset1(pf, leszarmazott);
        }
    }
}

// szinezes helyreallitasa: "kilepo eset"
void deleteEset1(pf_keresofa* pf, csomopont* duplanFeketeCsp)
{
    if (duplanFeketeCsp->szulo == nullptr)
    {
        pf->gyoker = duplanFeketeCsp;
        return;
    }
    deleteEset2(pf, duplanFeketeCsp);
}

// szinezes helyreallitasa: feladat feljebb tolasa
void deleteEset2(pf_keresofa* pf, csomopont* duplanFeketeCsp)
{
    csomopont* testverCsp = testverPF(pf, duplanFeketeCsp);
    if (testverCsp->szin == PIROS)
    {
        if (testverCsp->szulo->bal == testverCsp)
        {
            forgatjobbra(pf, testverCsp->szulo);
            testverCsp->szin = FEKETE;
            testverCsp->szulo->szin = PIROS;
        }
        else
        {
            forgatbalra(pf, testverCsp->szulo);
            testverCsp->szin = FEKETE;
            testverCsp->szulo->szin = PIROS;
        }
        if (testverCsp->szulo == nullptr)
        {
            pf->gyoker = testverCsp;
        }
    }
    deleteEset3(pf, duplanFeketeCsp);
}

// szinezes helyreallitasa: potencialis "kilepo eset"
void deleteEset3(pf_keresofa* pf, csomopont* duplanFeketeCsp)
{
    csomopont* testverCsp = testverPF(pf, duplanFeketeCsp);
    if (duplanFeketeCsp->szulo->szin == FEKETE && testverCsp->szin == FEKETE && testverCsp->bal->szin == FEKETE && testverCsp->jobb->szin == FEKETE)
    {
        testverCsp->szin = PIROS;
        deleteEset1(pf, duplanFeketeCsp->szulo);
    }
    else
    {
        deleteEset4(pf, duplanFeketeCsp);
    }
}

// szinezes helyreallitasa: "kilepo eset"
void deleteEset4(pf_keresofa* pf, csomopont* duplanFeketeCsp)
{
    csomopont* testverCsp = testverPF(pf, duplanFeketeCsp);
    if (duplanFeketeCsp->szulo->szin == PIROS && testverCsp->szin == FEKETE && testverCsp->bal->szin == FEKETE && testverCsp->jobb->szin == FEKETE)
    {
        testverCsp->szin = PIROS;
        duplanFeketeCsp->szulo->szin = FEKETE;
        return;
    }
    else
    {
        deleteEset5(pf, duplanFeketeCsp);
    }
}

// szinezes helyreallitasa: feladat feljebb tolasa
void deleteEset5(pf_keresofa* pf, csomopont* duplanFeketeCsp)
{
    csomopont* testverCsp = testverPF(pf, duplanFeketeCsp);
    if (testverCsp->szin == FEKETE)
    {
        if (duplanFeketeCsp->szulo->bal == duplanFeketeCsp && testverCsp->jobb->szin == FEKETE && testverCsp->bal->szin == PIROS)
        {
            forgatjobbra(pf, testverCsp);
            testverCsp->bal->szin = FEKETE;
            testverCsp->bal->szulo->szin = PIROS;
        }
        else if (duplanFeketeCsp->szulo->jobb == duplanFeketeCsp && testverCsp->bal->szin == FEKETE && testverCsp->jobb->szin == PIROS)
        {
            forgatbalra(pf, testverCsp);
            testverCsp->jobb->szin = FEKETE;
            testverCsp->jobb->szulo->szin = PIROS;
        }
    }
    deleteEset6(pf, duplanFeketeCsp);
}

// szinezes helyreallitasa: "kilepo eset"
void deleteEset6(pf_keresofa* pf, csomopont* duplanFeketeCsp)
{
    csomopont* testverCsp = testverPF(pf, duplanFeketeCsp);
    testverCsp->szin = testverCsp->szulo->szin;
    testverCsp->szulo->szin = FEKETE;
    if (duplanFeketeCsp->szulo->bal == duplanFeketeCsp)
    {
        testverCsp->jobb->szin = FEKETE;
        forgatbalra(pf, testverCsp->szulo);
    }
    else
    {
        testverCsp->bal->szin = FEKETE;
        forgatjobbra(pf, testverCsp->szulo);
    }
    if (testverCsp->szulo == nullptr)
    {
        pf->gyoker = testverCsp;
    }
}