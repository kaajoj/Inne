// Karol Nowak
// Grupa: I6X1N1
// Nr albumu: 67471

// silnia metoda interacyjna

#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
    setlocale(LC_ALL, "");

    int n;
    long double silnia=1;           // max dla silni z 1754

    cout << "Podaj liczbê dla której ma byæ obliczona silnia: " << endl << endl;
    cin >> n;


    for (int i=1;i<=n;i++) {
    silnia*=i;
    }

    cout << endl << "Wynik: " << silnia << endl << endl;

    system("pause");
    return 0;
}

