#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
using namespace std;

int sprawdzanie_lukow(vector<pair<int, int>>& Hkopia, int n, int x, int czy_stary);
void transformacja(vector<vector<int>>& G, vector<pair<int, int>>& H, vector<pair<int, int>>& Hkopia, int v, int n);
int przeindeksowanie(vector<pair<int, int>>& H, int n);
int czy_1graf(vector<vector<int>>& G, int n);
int czy_sprzezony(vector<vector<int>>& G, int n);
bool porownanie_sprzezony(vector<int>& G1, vector<int>& G2);
void czyszczenie(vector<pair<int, int>>& H, int nowy, int stary);
void zapis_do_pliku(vector<vector<int>>& G, int liczba_wierzcholkow);

int main()
{
    int n, v;
    int test;
    ifstream graf;
    graf.open( "graf.txt" );
    graf >> n;
    graf >> v;
    vector<vector<int>> G(n);
    for(int i=0; i<n; i++)
    {
        int m;
        graf >> m;
        for(int j=0; j<m; j++)
        {
            int x;
            graf >> x;
            G[i].push_back(x-1);

        }
    }

    cout << "Lista nastepnikow:";
    for(int i=0; i<n; i++)
    {
        cout << endl << 1+i << ": ";
        for(size_t j=0; j<G[i].size(); j++ )
        cout << G[i][j]+1 << ", ";
    }
    test=czy_1graf(G, n);
    if(test!=0)
    {
        cout << endl << endl << "Graf wejsciowy nie jest 1-grafem! Wystepuja krawedzie wielokrotne!";
        return 0;
    }
    test=czy_sprzezony(G, n);
    if(test!=0)
    {
        cout << endl << endl << "Graf nie jest sprzezony!";
        return 0;
    }
    cout << endl << endl << "Graf jest sprzezony";

    if(test==0)
    {
        vector<pair<int,int>> H;
        int ih=0, jh=1;
        for(int i=0; i<n; i++)
        {
                H.push_back(make_pair(ih,jh));
                ih=ih+2;
                jh=jh+2;
        }
        vector<pair<int, int>> Hkopia=H;
        transformacja(G, H, Hkopia, v, n);
        int liczba_wierzcholkow = przeindeksowanie(H, n);
        vector<vector<int>> graf_oryginalny(liczba_wierzcholkow);
        for(int i=0; i<graf_oryginalny.size(); i++)
        {
            for(int i2=0; i2<H.size(); i2++)
            {
                if(H[i2].first==i)
                    graf_oryginalny[i].push_back(H[i2].second);
            }


        }
        int czy_liniowy=czy_1graf(graf_oryginalny, liczba_wierzcholkow);
        if(czy_liniowy!=0)
            cout << endl << "Graf nie jest liniowy";
        else
            cout << endl << "Graf jest liniowy" << endl;
        zapis_do_pliku(graf_oryginalny, liczba_wierzcholkow);
    }
    return 0;
}



int czy_1graf(vector<vector<int>>& G, int n)
{
    for(int i=0; i<n; i++)
    {
        set<int> test(G[i].begin(), G[i].end());
        if(test.size()!=G[i].size())
            return 1;
    }
    return 0;
}


int czy_sprzezony(vector<vector<int>>& G, int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int i2=i+1; i2<n; i2++)
        {
            if(!porownanie_sprzezony(G[i], G[i2]))
                return 2;
        }
    }
    return 0;
}


bool porownanie_sprzezony(vector<int>& G1, vector<int>& G2)
{

    set<int> S1(G1.begin(), G1.end());
    set<int> S2(G2.begin(), G2.end());

    if(S1==S2)
       return true;
    if(S1.empty())
        return true;
    if(S2.empty())
        return true;
    for(size_t j=0; j<G1.size(); j++)
        if(S2.count(G1[j])>0)
            return false;
    for(size_t j=0; j<G2.size(); j++)
        if(S1.count(G2[j])>0)
            return false;
    return true;
}


void transformacja(vector<vector<int>>& G, vector<pair<int, int>>& H, vector<pair<int, int>>& Hkopia, int v, int n)
{
    vector<pair<int,int>> kolejnosc;
    kolejnosc.reserve(v);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<G[i].size(); j++)
        {
            kolejnosc.push_back(make_pair(i, G[i][j]));
        }
    }
    for(int i=0; i<kolejnosc.size(); i++)
    {
        int x=kolejnosc[i].second;
        int stary=sprawdzanie_lukow(H, 2*v, x, 1);
        x=kolejnosc[i].first;
        int nowy=sprawdzanie_lukow(H, 2*v, x, 0);
        czyszczenie(H, nowy, stary);
    }
}


int sprawdzanie_lukow(vector<pair<int, int>>& Hkopia, int n, int x, int czy_stary)
{
    if(czy_stary==1)
        return Hkopia[x].first;
    else
        return Hkopia[x].second;
}


void czyszczenie(vector<pair<int, int>>& H, int nowy, int stary)
{
    for(int i=0; i<H.size(); i++)
    {
        if(H[i].first==stary)
            H[i].first=nowy;
        if(H[i].second==stary)
            H[i].second=nowy;
    }
}


int przeindeksowanie(vector<pair<int, int>>& H, int n)
{
    int liczba_wierzcholkow=0;
    for(int i=0; i<2*n; i++)
        {
            int potrzebny=0;
            for(int i2=0; i2<H.size(); i2++)
            {
                if(H[i2].first==i)
                {
                    potrzebny=1;
                }
                else if(H[i2].second==i)
                {
                    potrzebny=1;
                }
            }
            if(potrzebny==1)
            {
                liczba_wierzcholkow++;
            }
        }
    for(int i=0; i<liczba_wierzcholkow; i++)
        {
            int potrzebny=0;
            while(potrzebny==0)
            {
                for(int i2=0; i2<H.size(); i2++)
                {
                    if(H[i2].first==i)
                    {
                        potrzebny=1;
                    }
                    else if(H[i2].second==i)
                    {
                        potrzebny=1;
                    }
                }
                if(potrzebny==0)
                {
                    for(int i2=0; i2<H.size(); i2++)
                    {
                        if(H[i2].first>i)
                            H[i2].first--;
                        if(H[i2].second>i)
                            H[i2].second--;
                    }
                }
            }
        }
        return liczba_wierzcholkow;
}


void zapis_do_pliku(vector<vector<int>>& G, int liczba_wierzcholkow)
{
    int liczba_krawedzi=0;
    for(int i=0; i<liczba_wierzcholkow; i++)
        liczba_krawedzi=liczba_krawedzi+(int)G[i].size();
    ofstream zapis("wynik.txt");
    zapis << liczba_wierzcholkow << " " << liczba_krawedzi;
    for(int i=0; i<liczba_wierzcholkow; i++)
    {
        zapis << endl << G[i].size()<< " ";
        for(int j=0; j<G[i].size(); j++ )
            zapis << G[i][j]+1 << " ";
    }
    zapis.close();
}
