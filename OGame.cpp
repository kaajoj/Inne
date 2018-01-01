// Krazownik
// Cena: metal: 20000, krysztal: 7000, deuter: 2000
// Napisac program, ktory zapyta ile posiadasz metalu, krysztalu i deuteru.
// Po czym wypisze ile maksymalnie kraowników mozemy kupic za posiadane surowce.

#include <iostream>
#include <cmath>

using namespace std;

float metal, krysztal, deuter;      // zmienne przechowujace ilosc surowcow
int m,k,d;                        // zmienne wykorzystane do obliczenia ile mozna kupic krazownikow za poszczegolny surowiec (nie trzeba float i funkcji trunc() nawet)
int w;                            // zmienna do wyznaczenia najwiekszej liczby z m,k,d

int main()
{
    cout << "Ile posiadasz metalu?" << endl;
    cin >> metal;
    cout << "Ile posiadasz krysztalu?" << endl;
    cin >> krysztal;
    cout << "Ile posiadasz deuteru?" << endl;
    cin >> deuter;

    m=metal/20000;
    k=krysztal/7000;
    d=deuter/2000;

    w=m;
    if (w>k) w=k;
    if (w>d) w=d;

    if (trunc(w)==0) cout<<"Nie stac Cie na nowe statki!"<<endl;
    else if (trunc(w)<0) cout<<"Niepoprawne dane!"<<endl;
    else cout<<"Mozesz kupic krazownikow: "<<trunc(w)<<endl;

    return 0;
}
